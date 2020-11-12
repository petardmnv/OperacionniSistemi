#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 2){
		perror("Usage: ./a.out file.txt \n");
		return -1;
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed: ");
		return -1;
	}

	ssize_t fread;
	off_t seek;
	char word;
	unsigned char next;
	while ((fread = read(fd, &word, 1)) > 0){
		ssize_t cwrite = write(STDOUT_FILENO, &word, 1);
		if (cwrite < 0){
			perror("write() failed:");
			return -1;
		}
		fread = read(fd, &next, 1);
		if (next == 0) break;
		seek = lseek(fd, next, SEEK_SET);
		if (seek < 0){
			perror("lseek() failed: ");
			return -1;
		}
	}
	close(fd);
	return 0;
}

