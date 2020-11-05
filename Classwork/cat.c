#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#defina BUFFER 1024
int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Usage: %s [file]\n", argv[0]);
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed: ");
		int myer = errno;
		printf("%s\n", strerror(myer));
		return -1;
	}

	int nread;
	char buf[BUFFER + 1] = {0};
	while((nread = read(fd, buf, BUFFER)) < 0){
		buf[nread] = 0;
		printf("%s", buf);
	}
	
	close(fd);
	
    return 0;
}
