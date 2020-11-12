#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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

	int hread;
	int hwrite; 
	char buf[BUFFER] = {0};
	while((hread = read(fd, buf, BUFFER)) > 0){
		//Zapisah outputa v drug fail i fidqh 4e printira 1024 - strlen(buf)
		// simvola - '\0'
		//Taka 4e ve4e printira do strlen(buf)
		hwrite = write(STDOUT_FILENO, buf, strlen(buf));
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
