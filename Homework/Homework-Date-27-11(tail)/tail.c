#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define MAXBUFF 1024
//------------------------------------------------------------------------
// NAME: Petar Damianov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE: Program that implements tail command
// ...
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: open_file(char* file_path)
// Opens file by given file_path.
// PARAMETERS: file_path - file path needed in open().
// 
//------------------------------------------------------------------------
int open_file(char* file_path){
	int fd;
	if ((fd = open(file_path, O_RDONLY)) == -1){
		//This is retarded:'(
		char err[100] = "tail: cannot open '";
		strcat(err, file_path);
		strcat(err, "' for reading");
		perror(err);
		return -1;
	}
	return fd;
}
//------------------------------------------------------------------------
// FUNCTION: read_file
// Does part of the main logic. Read from file descriptor and write into terminal 
// PARAMETERS: fd - file descriptor, file_path - file path used in error handling.
// 
//------------------------------------------------------------------------

char * read_file(int fd, char* file_path){
	int result_size = 1;
	char* result = (char* ) malloc(result_size * sizeof(result));


	ssize_t r;
	char buff[MAXBUFF] = {0};
	while((r = read(fd, buff, MAXBUFF)) > 0){
		result_size += MAXBUFF;
		result = (char* ) realloc(result, result_size * sizeof(result));
		strcat(result, buff);
		//buff clear
		memset(buff, 0, MAXBUFF);

	}

	if (r == -1){
		//This is retarded:'(
		char err[100] = "tail: error reading '";
		strcat(err, file_path);
		strcat(err, "'");
		perror(err);
		return NULL;
	}
	return result;
}
//------------------------------------------------------------------------
// FUNCTION: write_file
// Does part of the main logic. Read from file descriptor and write into terminal 
// PARAMETERS: fd - file descriptor, file_path - file path used in error handling.
// 
//------------------------------------------------------------------------
int write_file(int fd, char* file_path){
	/*Some logic:
	I have to print less or eq 10 lines
	Data stored (? where ?):
		result: str - I am using use malloc and realloc cuz I don't know the file size*/
	char* result = read_file(fd, file_path);

	if (result == NULL){
		return -1;
	}
	int new_lines = 0;
	int is_read = 0;
	for (int i = strlen(result); i >= 0; --i){
		if (result[i] == '\n'){
			new_lines ++;
		}
		if (new_lines == 10){
			//This is bullshit:(
			ssize_t w = write(STDOUT_FILENO, result + i + 1, strlen(result));
			if (w == -1){
				//This is retarded:'(
				char err[100] = "tail: error writing '";
				strcat(err, file_path);
				strcat(err, "'");
				perror(err);
				return -1;
			}
			is_read = 1;
			break;
		}
	}
	if (is_read == 0){
		ssize_t w = write(STDOUT_FILENO, result, strlen(result));
		if (w == -1){
			//This is retarded:'(
			char err[100] = "tail: error writing '";
			strcat(err, file_path);
			strcat(err, "'");
			perror(err);
			return -1;
		}
	}
	//clear result for the next function call. 
	memset(result, 0, strlen(result));
	free(result);
	return 0;
}

void print(int fd, char* file_path){
	char first_spliter[4] = "==> ";
	char second_spliter[5] = " <==\n";
	write(STDOUT_FILENO, &first_spliter, 4);
	write(STDOUT_FILENO, file_path, strlen(file_path));
	write(STDOUT_FILENO, &second_spliter, 5);
}

int close_file(int fd, char* file_path){
	if (close(fd) == -1){
		//This is retarded:'(
		char err[100] = "tail: error reading '";
		strcat(err, file_path);
		strcat(err, "'");
		perror(err);
		return -1;
	}
	return 0;
}
int main(int argc, char *argv[]){
	/*Basic program logic: 
	open file
	check if open ok
	read from file
	check if read ok
	write ...
	check if write ok
	close ... 
	check if close ok
	*/
	char new_line = '\n';


	for (int i = 0; i < argc - 1; ++i){
		char* path = argv[i + 1];
		int fd;
		if (strcmp(argv[i + 1], "-") == 0){
			fd = 0;
			path = "standard input";
		}else{
			if ((fd = open_file(path)) == -1){
				continue;
			}
		}
		if (argc != 2){
			print(fd, path);
		}
		if (write_file(fd, path) == -1){
			continue;
		}
		close_file(fd, path);
		if (i < argc - 2){
			write(STDOUT_FILENO, &new_line, 1);
		}
	}
	return 0;
}