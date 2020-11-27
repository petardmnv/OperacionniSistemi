#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAXBUFF 25
//------------------------------------------------------------------------
// NAME: Ivan Ivanov
// CLASS: XIa
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: xxxxxx.yyy.zzz (unix file name)
// FILE PURPOSE:
// няколко реда, които описват накратко
// предназначението на файла
// ...
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// FUNCTION: xxyyzz (име на функцията)
// предназначение на функцията
// PARAMETERS:
// списък с параметрите на функцията
// и тяхното значение
//------------------------------------------------------------------------



//Output:
/*$ tail a.txt b.txt
==> a.txt <==
two
three
four
five
six
seven
eight
nine
ten
eleven

==> b.txt <==
1
2
3
4
5
6
7*/


/*No file error - open failed:
tail: cannot open 'aa' for reading: No such file or directory
tail: cannot open 'bb' for reading: No such file or directory*/

/* File read error:
tail: error reading '/tmp/': Is a directory*/


/*File write failed:
tail: error writing 'standard output': No space left on device
*/

/*File close error
tail: error reading 'b.txt': Input/output error
*/


/* operator "-":
Do not understanding..... Going to cheat(;)}
*/

/* Lastly: MAKEFILE - Eazy 
*/


int open_file(char* file_path){
	int fd;
	char err[100] = "tail: cannot open '";
	if ((fd = open(file_path, O_RDONLY)) == -1){
		//This is retarded;(
		strcat(err, file_path);
		strcat(err, "' for reading: ");
		strcat(err, strerror(errno));
		strcat(err, "\n");
		write(STDERR_FILENO, err, strlen(err));
		return -1;
	}
	return fd;
}
/*int read_file(char* file){
	if (1){
	}
	return 0;
}
// write(){}*/

int close_file(int fd, char* file_path){
	char err[100] = "tail: error reading '";
	if (close(fd) == -1){
		//This is retarded;(
		strcat(err, file_path);
		strcat(err, "': ");
		strcat(err, strerror(errno));
		strcat(err, "\n");
		write(STDERR_FILENO, err, strlen(err));
		return -1;
	}
	return 0;
}
int main(int argc, char *argv[]){
	/*Program logic: 
	open files
	check if open ok
	read from files
	check if read ok
	write ...
	check if write ok
	close ... 
	check if close ok
	...
	*/
	int nf = open("output.txt", S_IRWXU | O_RDWR | O_CREAT);
	if (nf < 0){
		perror("open failed.");
	}
	int fd[argc - 1];
	for (int i = 1; i < argc; ++i){
		fd[i - 1] = open_file(argv[i]);
	}
	/*Logic:
	Ihave to print less or eq 10 lines
	Starting at the end of the file and counting new lines "\n" I thought that it would be easyar.
	Data stored (? where ?):
		result: str - but I don't know size of file so that is not gonna be OK in every case
		result.txt: file I don't need to know Data will be stored and at the end of the program will be printed
		in each insetion seek = lseek(fd, 0, SEEK_SET) 
	*/

	int new_lines = 0;
	ssize_t r;
	off_t offset = -10;
	lseek(fd[0], offset, SEEK_END);
	char buff[MAXBUFF] = {0};
	while((r = read(fd[0], buff, MAXBUFF)) > 0){
		for (int i = strlen(buff); i >= 0 ; --i){
			if (buff[i] == '\n'){
				new_lines ++;
			}
			if (new_lines == 10){
				write(nf, buff + i, MAXBUFF);
				break;
			}
		}
		ssize_t w = write(nf, buff, MAXBUFF);
		if (w < 0){
			perror("write failed.");
		}

	}

	while((r = read(nf, buff, MAXBUFF)) > 0){
		ssize_t w = write(STDOUT_FILENO, buff, MAXBUFF);
		if (w < 0){
			perror("write2 failed.");
		}
	}

	for (int i = 0; i < argc - 1; ++i){
		close_file(fd[i], argv[i + 1]);
	}
	return 0;
}