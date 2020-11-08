#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER 1024
int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Usage: ./a.out [bmp file]\n");
	}
	
	int fh;
	
	if ((fh = open(argv[1], O_RDONLY)) == -1)	{
		perror("Error open() file.");
		return -1;
	}
	
	/*int bmp_size = 0;
	int bmp_height = 0;
	int bmp_weight = 0;*/
	
	off_t  size = lseek(fh, 2, SEEK_SET);
	
	int fread;
	char buf[1025];
	fread = read(fh, buf, 1024);
	printf("%d\n", int(buf[size]));
	
	close(fh);
	return 0;
}
