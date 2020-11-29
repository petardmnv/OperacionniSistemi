all: tail

tail.o: tail.c
	gcc -Wall -pedantic -std=c11 -c tail.c

tail: tail.o
	gcc -Wall -pedantic -std=c11 tail.o -o tail

clean:
	rm *.o tail