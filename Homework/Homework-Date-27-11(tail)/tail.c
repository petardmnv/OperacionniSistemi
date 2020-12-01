//------------------------------------------------------------------------
// NAME: Petar Damianov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE: Program that implements tail command
// ...
//------------------------------------------------------------------------
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
// FUNCTION: open_file
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
// Does first part of the main logic. Read from file descriptor and write data from buff to result - returning value. 
// PARAMETERS: fd - file descriptor, file_path - file path used in error handling.
// 
//------------------------------------------------------------------------

char * read_file(int fd, char* file_path){
	int result_size = 1;
	char* result = (char*) malloc(result_size);


	ssize_t r;
	char buff[MAXBUFF] = {0};
	while((r = read(fd, buff, MAXBUFF)) > 0){
		result_size += strlen(buff);
		result = (char* ) realloc(result, result_size);
		strcat(result, buff);
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
// Does second part of the main logic. Write into terminal from result. 
// PARAMETERS: fd - file descriptor, file_path - file path used in error handling.
// 
//------------------------------------------------------------------------
int write_file(int fd, char* file_path){
	/*Some logic:
	I have to print less or eq 10 lines
	Data stored (? where ?):
		result: str - I am using use malloc and realloc cuz I am dumb ass*/
	char* result = read_file(fd, file_path);

	if (result == NULL){
		return -1;
	}
	int new_lines = 0;
	int is_read = 0;
	if (result[strlen(result) - 1] == '\n'){
		new_lines --;
	}
	for (int i = strlen(result) - 1; i >= 0; --i){
		if (result[i] == '\n'){
			new_lines ++;
		}
		if (new_lines == 10){
			//print the correct number of bytes from result
			ssize_t w = write(STDOUT_FILENO, result + i + 1, strlen(result) - i - 1);
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
	free(result);
	return 0;
}
//------------------------------------------------------------------------
// FUNCTION: print_title
// Prints ==> file_path <==
// PARAMETERS: file_path - file path used in printing file name.
// 
//------------------------------------------------------------------------
void print_title(char* file_path){
	char first_spliter[4] = "==> ";
	char second_spliter[5] = " <==\n";
	write(STDOUT_FILENO, &first_spliter, 4);
	write(STDOUT_FILENO, file_path, strlen(file_path));
	write(STDOUT_FILENO, &second_spliter, 5);
}

//------------------------------------------------------------------------
// FUNCTION: close_file
// Closes file by given file descriptor 
// PARAMETERS: fd - file descriptor used for closing the file, file_path - file path used in error handling.
// 
//------------------------------------------------------------------------
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
	// tail without arguments
	if (argc == 1){
		write_file(0, "standart input");
	}


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
			print_title(path);
		}

		if (write_file(fd, path) == -1){
			continue;
		}
		
		if (fd != 0){
			close_file(fd, path);
		}

		if (i < argc - 2){
			write(STDOUT_FILENO, &new_line, 1);
		}
	}
	return 0;
}