#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define MAXBUFF 10


int main(int argc, char  *argv[])
{
	/*int nf = open(argv[1], O_RDWR | O_CREAT);
	if (nf < 0){
		perror("open failed.");
	}

	ssize_t r;
	char buff[MAXBUFF] = {0};
	while((r = read(nf, buff, MAXBUFF)) > 0){
		ssize_t w = write(STDOUT_FILENO, buff, MAXBUFF);
		if (w < 0){
			perror("write2 failed.");
		}	
		memset(buff, 0, MAXBUFF);	
	}

	close(nf);*/
	
	/*int size = MAXBUFF;
	char* res = malloc(size * sizeof(res));
	strcat(res, "asdfghhj");
	printf("%s\n and size - %ld\n", res, strlen(res));
	res = realloc(res, (size + MAXBUFF) * sizeof(res));
	size += MAXBUFF;
	strcat(res, "asdfghjkl");
	printf("%s\n and size - %ld\n", res, strlen(res));
	printf("Size: %d\n", size);*/
	return 0;
}