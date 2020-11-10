#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (argc != 2){
		perror("Usage: ./a.out file1.txt file2.txt");
		return -1;
	}
	
	int f;
	
	if ((f = open(argv[1], O_RDONLY)) == -1){
		perror("first file open() failed: ");
		return -1;
	}
	off_t fseek = lseek(f, -4, SEEK_END);
	if (fseek < 0){
		perror("first file lseek() failed: ");
		return -1;
	}
	ssize_t fread = 1;
	char buf = 0;
		while(fread > 0){
		fread = read(f, &buf, 1);
		write(STDOUT_FILENO, &buf, 1);
	}
	if (fread < 0){
		perror("read() failed: ");
		return -1;
	}
	
	return 0;
	
}
	
	
