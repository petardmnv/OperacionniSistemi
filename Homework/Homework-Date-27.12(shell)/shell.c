//------------------------------------------------------------------------
// NAME: Petar Damianov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: shell.c
// FILE PURPOSE: Program that implements shell interpreter
// ...
//------------------------------------------------------------------------


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

//------------------------------------------------------------------------
// FUNCTION: **parse_cmdline
// converts C-string to C-strings
// PARAMETERS: const char *cmdline - comands read from terminal 
// 
//------------------------------------------------------------------------
char **parse_cmdline(const char *cmdline){
	char split_by[3] = " \n";

	char *non_const_cmdline = malloc(strlen(cmdline));
	strcpy(non_const_cmdline, cmdline);

	//15ti red e tumna indiq:)
	char **parsed_string = (char**) malloc(sizeof(char*));
	int parsing_count = 0;

	char* token;
	token = strtok(non_const_cmdline, split_by);
	while (token != NULL){
		parsing_count += 1;

		parsed_string = (char**) realloc(parsed_string, sizeof(char*) * parsing_count);
		parsed_string[parsing_count - 1] = malloc(strlen(token));
		parsed_string[parsing_count - 1] = token;

		token = strtok(NULL, split_by);
	}

	parsed_string = (char**) realloc(parsed_string, sizeof(char*) * (parsing_count + 1));
	parsed_string[parsing_count] = NULL;

	return parsed_string;
}


//------------------------------------------------------------------------
// FUNCTION: print_dollar
// prints dollar sigh
// PARAMETERS: N/A
// 
//------------------------------------------------------------------------
void print_dollar(){
	char dollar_sign[3] = "$ ";
	if ((write(0, &dollar_sign, 2)) < 0){
		perror("write");
	}
}

int main(int argc, char const *argv[]){
	while(1){
		print_dollar();
		size_t b = 0;
		char *buff = NULL;
		if ((getline(&buff, &b, stdin)) == -1){
			perror("read");
			return -1;
		}
		pid_t pid;
		pid = fork();
		int status;

		if (pid < 0){
			status = -1;
			perror("fork");
		}else if (pid == 0){
			char **arguments = parse_cmdline(buff); 
			int returned_status = execvp(arguments[0], arguments);
			if (returned_status == -1){
				perror(arguments[0]);
				exit(-1);
			}
			exit(0); 
		}else {
			if (waitpid(pid, &status, 0) != pid){
				status = -1;
			}
			if (status == -1){
				perror("waitpid");
			}
		}
	}
	return 0;
}