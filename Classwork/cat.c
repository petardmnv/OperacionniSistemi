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
		printf("Usage: ./a.out file.txt \n");
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed: ");
		return -1;
	}

	int nread;
	char buf[BUFFER + 1] = {0};
	while((nread = read(fd, buf, BUFFER)) > 0){
		write(STDOUT_FILENO, &buf, BUFFER);
	}
	
	close(fd);
	
    return 0;
}
