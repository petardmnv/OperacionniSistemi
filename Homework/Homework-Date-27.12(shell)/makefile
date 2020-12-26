all: shell

shell.o: shell.c
	gcc -Wall -pedantic -std=c11 -c shell.c

shell: shell.o
	gcc -Wall -pedantic -std=c11 shell.o -o shell

clean:
	rm *.o shell