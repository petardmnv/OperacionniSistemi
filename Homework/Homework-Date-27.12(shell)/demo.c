#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char names[100] = "  Peho Stavri\nVqra Krum Martin Qsen Cveti";
	const char s[3] = " \n";
	char* token;
	token = strtok(names, s);
	while (token != NULL){
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
	return 0;
}