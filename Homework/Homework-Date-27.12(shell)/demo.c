#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char names[100] = "Peho Stavri Vqra Krum Martin Qsen Cveti";
	const char s[2] = " ";
	char* token;
	token = strtok(names, s);
	while (token != NULL){
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
	return 0;
}