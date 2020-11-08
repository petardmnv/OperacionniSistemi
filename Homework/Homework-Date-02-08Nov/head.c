#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER 16
int main(int argc, char *argv[]){
	if (argc < 2 || argc > 3){
		printf("Usage: %s [file]\n", argv[0]);
	}
	
	int fh; 
	
	if ((fh = open(argv[1], O_RDONLY)) == -1){
		perror("open() failed: ");
		return -1;
	}
	
	int fread;
	int line_counter = 0;
	char buf[BUFFER + 1] = {0};
	while((fread = read(fh, buf, 1)) > 0){
		if (*buf == '\n'){
			line_counter++;
		}
		printf("%s", buf);
		if (line_counter == 10){
			break;
		}
	} 
	close(fh);
	return 0;
}
