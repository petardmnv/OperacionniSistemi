// logic head + ==> име-на-файл <== on every new file.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


void head(int fh){
	int fread;
	int line_counter = 0;
	char buf[2];
	while((fread = read(fh, buf, 1)) > 0){
		if (*buf == '\n'){
			line_counter++;
		}
		write(STDOUT_FILENO, &buf, 1);
		if (line_counter == 10){
			break;
		}
	} 
}
int open_state(char *filepath){
	int fh; 
	if ((fh = open(filepath, O_RDONLY)) == -1){
		perror("open() failed: ");
		return -1;
	}
	return 1;
}
int main(int argc, char *argv[]){
	char nl = '\n';
	char first_f[4] = "==> ";
	char last_f[5] = " <==\n";
	if (argc < 2){
		perror("Usage: ./a.out file.txt file2.txt....\n");
		return -1;
	}
	int fh; 
	
	for (int i = 1; i < argc; ++i){
		fh = open(argv[i], O_RDONLY);
		if (open_state(argv[i]) == 1){
			if (argc > 2){
				write(STDOUT_FILENO, &first_f, 4);
				write(STDOUT_FILENO, argv[i], strlen(argv[i]));
				write(STDOUT_FILENO, &last_f, 5);
			}
			head(fh);
			if (i < argc - 1){
				write(STDOUT_FILENO, &nl, 1);
			}
		}
		close(fh);
	}
	return 0;
}
