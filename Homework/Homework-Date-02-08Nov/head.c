#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
	if (argc < 2 || argc > 3){
		perror("Usage: ./a.out file.txt\n");
		return -1;
	}
	
	int fh; 
	
	if ((fh = open(argv[1], O_RDONLY)) == -1){
		perror("open() failed: ");
		return -1;
	}
	
	int fread;
	int line_counter = 0;
	char buf[1];
	while((fread = read(fh, buf, 1)) > 0){
		if (*buf == '\n'){
			line_counter++;
		}
		write(STDOUT_FILENO, &buf, 1);
		if (line_counter == 10){
			break;
		}
	} 
	char nl = '\n';
	write(STDOUT_FILENO, &nl, 1);
	close(fh);
	return 0;
}
