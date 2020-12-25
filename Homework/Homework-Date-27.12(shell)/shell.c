#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#define BUFF 10

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

int main(int argc, char const *argv[]){
	pid_t pid;
	int status;
	char dollar_sign[2] = "$";
	write(0, &dollar_sign, 2);

	//in function
	char* buffer = 0;

	ssize_t r;
	char buff[BUFF] = {0};

	char* result = (char*) malloc(sizeof(char*));
	int result_size = 0;

	while((r = read(0, buff, BUFF)) > 0){
		if (r < 0){
			perror("Read failed: ");
			return -1;
		}
		result_size += r;
		result = (char*) realloc(result, result_size * sizeof(char*));
		strcat(result, buff);
		memset(buff, 0, BUFF);
	}
	if (r < 0){
		perror("Read failed: ");
		return -1;
	}
	printf("%s\n", parse_cmdline(result)[2]);
	pid = fork();

	if (pid < 0){
		status = -1;
		perror("fork: ");
	}else if (pid == 0){
		//#TODO
		exit(0); 
	}else {
		waitpid();
	}
	free(result);
	return 0;
}