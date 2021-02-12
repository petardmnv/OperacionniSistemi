#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define MAXBUFF 1000


void *count_beans(void *array){
	//pass
}
int main(int argc, char const *argv[])
{
	int black_beans = 0;
	int white_beans = 0;
	int fd;
	if ((fd = open("new_beans.txt", O_RDONLY)) == -1){
		perror("Failed reading ...");
		return -1;
	}


	ssize_t r;
	char buff[MAXBUFF] = {0};
	int length = 0;
	while((r = read(fd, buff, MAXBUFF)) > 0){
		length += r;
		for (int i = 0; i <= r; ++i){
			if (buff[i] == '0'){
				white_beans++;
			}else if (buff[i] == '1'){
				black_beans++;
			}
		}
	}
	if (r < 0){
		perror("Reading fiole failed ...");
		return -1;
	}
	printf("White beans are : %d\nBlack beans are: %d", white_beans, black_beans);
	printf("\n%d\n", length);

	if (close(fd) == -1){
		perror("Closing file failed ...");
		return -1;
	}
	return 0;
}	