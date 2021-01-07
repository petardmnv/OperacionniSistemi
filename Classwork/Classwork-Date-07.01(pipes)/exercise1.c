#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/fcntl.h>

int main(int argc, char const *argv[])
{
	// Check argc
	//if argc == 1 -> read from cmd and save data to output.txt 
	// else  read from argv[1]

	if (argc == 1){
		ssize_t r;
		char buff[1024] = {0};
		while((r = read(STDIN_FILENO, &buff, 1024)) > 0){
			int fd;
			if ((fd = open("output.txt", O_RDWR | O_APPEND)) == -1){
				perror("Failed open");
			}
			ssize_t w = write(fd, &buff, r);
			if (w == -1){
				perror("Failed write");
			}
			if (r == -1){
				perror("Failed read");
				break;
			}
			else if (r == 0){
				break;
			}
		}
	}
	return 0;
}