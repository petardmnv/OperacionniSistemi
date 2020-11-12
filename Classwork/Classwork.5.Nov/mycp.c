#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER 1024
int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("Usage: ./a.out resourcefile.txt resultfile.txt or path\n");
		return -1;
	}
	int fd;
	
	if ((fd = open(argv[1], O_RDONLY)) < 0){
		perror("open() failed: ");
		return -1;
	}
	
	int nf;
	//Polu4avam gre6ka kogato faila koito podam ne su6testvuva
	//dori kogato izpolzvam i tazi komandi | O_CREAT | O_WRONLY
	//mi kazva 4e nqmam prava nad faila
	if ((nf = open(argv[2], O_WRONLY)) < 0){
		perror("new file open() failed: ");
		return -1;
	}
	ssize_t hread;
	ssize_t hwrite; 
	char buf[BUFFER] = {0};
	while((hread = read(fd, buf, BUFFER)) > 0){
		hwrite = write(nf, buf, strlen(buf));
		if (hwrite < 0){
			perror("write() failed: ");
			break;
		}
	}
	if (hread < 0){
		perror("read() failed: ");
		return -1;
	}
	
	if (close(fd) == -1){
		perror("close() failed: ");
		return -1;
	}
	
    return 0;
}
