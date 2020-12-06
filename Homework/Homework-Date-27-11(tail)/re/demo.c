#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define MAXBUFF 21


int main(int argc, char  *argv[]){
	char* file_path = argv[1];
	int nf = open(argv[1], O_RDONLY);
	if (nf < 0){
		perror("open failed.");
		return -1;
	}
	/*char data[200];
	ssize_t r;
	char buff[MAXBUFF] = {0};	

	int offset = -MAXBUFF;
	off_t l = lseek(nf , offset, SEEK_END);
	if (l == -1){
		perror("Seek 1 error()");
	}
	int new_lines = 0;
	while((r = read(nf, buff, MAXBUFF)) > 0){
		ssize_t w = write(STDOUT_FILENO, buff, MAXBUFF);
		if (w < 0){
			perror("write2 failed.");
		}
		for (int i = strlen(buff) - 1; i >= 0; --i){
			if (buff[i] == '\n'){
				new_lines ++;
			}
			if (new_lines == 10){	
				strcat(data, buff + i + 1);
				if (w == -1){
				//This is retarded:'(
					char err[100] = "tail: error writing '";
					strcat(err, file_path);
					strcat(err, "'");
					perror(err);
					return -1;
				}
				break;
			}
		}
		strcat(data, buff);
		memset(buff, 0, MAXBUFF);
		offset += -MAXBUFF;
		lseek(nf, offset, SEEK_END);

	}*/

	ssize_t r;
	off_t l = lseek(nf, 0, SEEK_END);
	if (l == -1){
		perror("Seek 2 error()");
		return -1;
	}
	off_t i = -1;
	char buff;
	r = read(nf, &buff, 1);



		i += 1;
		printf("WOW%ld\n", i);
		/*off_t l1 = lseek(nf, l - i, SEEK_SET);
		if (l1 == -1){
			perror("Seek 1 error()");
			return -1;
		}*/
		ssize_t w = write(STDOUT_FILENO, &buff, 1);
		if (w < 0){
			perror("write2 failed.");
			return -1;
		}

	if (close(nf) == -1){
		perror("close() error");
		return -1;
	}
	//printf("%s\n", data);
	return 0;
}