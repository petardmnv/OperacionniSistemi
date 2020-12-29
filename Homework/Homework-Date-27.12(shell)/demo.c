#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

char **parsing(const char*cmdline){
	char **parsed_string = (char**) malloc(sizeof(char*));

	int word_length = 0;
	int word_count = 1;
	int i = 0;
	while(*cmdline){
		if ((cmdline[i] == ' ') || (cmdline[i] == '\n')){
			if (word_length > 0){
				parsed_string = realloc(parsed_string, sizeof(char*) * word_count);
				parsed_string[word_count - 1] = malloc(word_length);
				strncpy(parsed_string[word_count - 1], *cmdline - word_length, word_length);
				word_count += 1;
			}
			word_length = 0;
		}
		else{
			word_length += 1;
		}
		*cmdline++;
		i += 1;
	}
	if (word_length > 0){
		parsed_string = realloc(parsed_string, sizeof(char*) * word_count);
		parsed_string[word_count - 1] = malloc(word_length);
		strncpy(parsed_string[word_count - 1], cmdline + i - word_length, word_length);
		word_count += 1;
	}
	parsed_string[word_count - 1] = NULL;
	return parsed_string;
}

int main(int argc, char const *argv[]){
	char names[200] = "  Peho Stavri \n Vqra Krum Martin Qsen Cveti\n qnko  \n Icko";
	printf("%ld\n", strlen(names));
	char **parsed = parsing(names); 
	for (int i = 0; i < 9; ++i){
		printf("%s\n", parsed[i]);
	}
		/*printf("%ld\n", strlen(names));
	const char s[3] = " \n";
	char* token;
	token = strtok(names, s);
	while (token != NULL){
		printf("%s\n", token);
		token = strtok(NULL, s);
	}*/
	/*char name[20] = "Peter";
	char fullname[20] = "GoshoDamianov";
	strcat(fullname, fullname + 5);
	strcpy(name, fullname + 5);
	printf("%s\n", name);
	while(1){
		print_dollar();
		size_t b = 0;
		char *buff = NULL;
		//int result_size = 0;
		//r = read(0, buff, BUFF);
		if ((getline(&buff, &b, stdin)) == -1){
			perror("read");
			return -1;
		}
	}*/
	return 0;
}