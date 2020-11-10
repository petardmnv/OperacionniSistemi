#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
	
	int fh; 
	
	if ((fh = open("a.txt", O_RDONLY)) == -1){
		perror("open() failed: ");
		return -1;
	}
	
	ssize_t fread;
	int line_counter = 0;
	char buf;
	while((fread = read(fh, &buf, 1)) > 0){
		if (buf == '\n'){
			line_counter++;
			if (line_counter == 10){
				break;
			}
		}
		write(STDOUT_FILENO, &buf, 1);
	} 
	char nl = '\n';
	write(STDOUT_FILENO, &nl, 1);
	close(fh);
	return 0;
}
