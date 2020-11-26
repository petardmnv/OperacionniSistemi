#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys\types.h"
#include "sys\wait.h"


int main(int argc, char const *argv[])
{
	int status = 0;
	pid_t pid;
	pid = fork();
	char** myargv;
	myargv = malloc(5);
	for (int i = 0; i < 5; ++i)
	{
		myargv[i] = malloc(strlen(argv) + 1);
	}
	if (pid < 0){
		perror("Errorr");
		return -1;
	}
	else if (pid == 0){
		execl("usr/bin/head", "head", "test1.txt", "text2.txt", (char*)NULL);
	}
	else {

	}

	return 0;
}