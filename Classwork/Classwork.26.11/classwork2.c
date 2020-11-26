#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys\types.h"
#include "sys\wait.h"
#include "errno.h"
#include "sys\stat"


int main(int argc, char const *argv[])
{
	int status = 0;
	pid_t pid;
	pid = fork();
	char fname[] = "romanes.txt"
	dhar data[] = "Romanes ent domus."
	if (pid < 0){
		perror("Errorr");
		return -1;
	}
	else if (pid == 0){
		if ()
	}
	else {
		if(waitpid(pid, &status, 0) != pid){

		}
	}
	
	return 0;
}