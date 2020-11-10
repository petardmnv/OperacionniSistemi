#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (argc != 3){
		perror("Usage: ./a.out file1.txt file2.txt");
		return -1;
	}
	
	int f;
	
	if ((f = open(argv[1], O_APPEND | O_CREAT | O_WRONLY)) == -1){
		perror("first file open() failed: ");
		return -1;
	}
	
	int s;
	if ((s = open(argv[2], O_RDONLY)) == -1){
		perror("second file open() failed: ");
		return -1;
	}
	
	ssize_t secondread = 1;
	char buf;
	while(secondread > 0){
		secondread = read(s, &buf, 1);
		
		if (secondread < 0){
			perror("read() failed: ");
			return -1;
		}
		
		if ((write(f, &buf, 1)) < 0){
			perror("write() failed: ");
			return -1;
		}
	}
	close(f);
	close(s);
	//Trqbva li da proverqvam dali sa se zatvorili failovete?
	return 0;
}
