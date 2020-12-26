#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void print_dollar(){
	char dollar_sign[3] = "$ ";
	write(0, &dollar_sign, 2);
}

int main(int argc, char const *argv[]){
	/*char names[100] = "  Peho Stavri\nVqra Krum Martin Qsen Cveti";
	const char s[3] = " \n";
	char* token;
	token = strtok(names, s);
	while (token != NULL){
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
	char name[20] = "Peter";
	char fullname[20] = "GoshoDamianov";
	strcat(fullname, fullname + 5);
	strcpy(name, fullname + 5);
	printf("%s\n", name);*/
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
	}
	return 0;
}