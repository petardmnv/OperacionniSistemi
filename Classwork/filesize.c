#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER 1024
int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Usage: ./a.out [file]\n");
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed:");
		return -1;
	}
	off_t  size = lseek(fd, 0, SEEK_END);
	printf("Size of current file: %ld\n", size);
	close(fd);
	
	return 0;
}
