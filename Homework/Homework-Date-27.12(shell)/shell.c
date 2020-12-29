//------------------------------------------------------------------------
// NAME: Petar Damianov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: shell.c
// FILE PURPOSE: Program that implements shell interpreter
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
// converts C-string to C-strings using strtok:)
// PARAMETERS: const char *cmdline - comands read from terminal 
// 
//------------------------------------------------------------------------
char **parse_cmdline(const char *cmdline){
	int cmdline_length = strlen(cmdline);
	char *non_const_cmdline = malloc(cmdline_length);

	strcpy(non_const_cmdline, cmdline);

	char **parsed_string = (char**) malloc(sizeof(char*));
	int parsing_count = 1;

	char* token;
	token = strtok(non_const_cmdline, " \n");
	while (token != NULL){
		//That is usless :(
		int token_length = strlen(token) + 1;
		parsed_string[parsing_count - 1] = malloc(token_length);
		strncpy(parsed_string[parsing_count - 1], token, token_length);
		token = strtok(NULL, " \n");
		parsing_count += 1;
		parsed_string = (char**) realloc(parsed_string, sizeof(char*) * (parsing_count + 1));
	}

	parsed_string[parsing_count] = NULL;
	free(non_const_cmdline);
	return parsed_string;
}

//------------------------------------------------------------------------
// FUNCTION: main
// Function does the main logic - creating process and executing commands from 
// arguments using execvp. 
// PARAMETERS: const char *cmdline - comands read from terminal 
// 
//------------------------------------------------------------------------
int main(int argc, char const *argv[]){
	while(1){
		char *dollar_sign = "$ ";
		if ((write(STDOUT_FILENO, dollar_sign, 2)) < 0){
			perror("write");
			return -1;
		}
		size_t b = 0;
		char *buff = NULL;
		if ((getline(&buff, &b, stdin)) == -1){
			free(buff);
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
			free(arguments);
			exit(0); 
		}else {
			if (waitpid(pid, &status, 0) != pid){
				perror("waitpid");
			}
		}
		free(buff);
	}
	return 0;
}