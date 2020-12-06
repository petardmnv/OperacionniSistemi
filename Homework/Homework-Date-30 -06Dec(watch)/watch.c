#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *argv2[argc];
	int status;
	for(int i = 1; i < argc; i++){
		argv2[i - 1] = argv[i];
	}
	
	argv2[argc - 1] = NULL;
	
	while(1) {	

		pid_t pid = fork();
		pid = -1;

		if(pid == -1){
			perror("fork");
			status = -1;
			return status;
		
		}else if(pid == 0){
			int err;
			if((err = execv(argv[1], argv2)) == -1){
				perror(argv2[0]);
				status = -1;
				return status;
			}
			
			exit(pid);
		}else{
			if (waitpid(pid, &status, 0) != pid){
				status = -1;
				perror("waitpid() error");
			}
			
			sleep(2);
		}
	}
	
	return 0;
}
