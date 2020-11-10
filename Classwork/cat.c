#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER 1024
int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("Usage: ./a.out file.txt \n");
		return -1;
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed: ");
		return -1;
	}

	int hread = 1;
	int hwrite; 
	char buf[BUFFER] = {0};
	while((hread = read(fd, buf, BUFFER)) > 0){
		
		hwrite = write(STDOUT_FILENO, buf, BUFFER);
		if (hwrite < 0){
			perror("write() failed: ");
			break;
		}
	}
	if (hread < 0){
		perror("read() failed: ");
		return -1;
	}
	
	if (close(fd) == -1){
		perror("close() failed: ");
		return -1;
	}
	
    return 0;
}
