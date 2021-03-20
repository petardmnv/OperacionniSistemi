all: starcraft3

starcraft3.o: starcraft3.c
	gcc -Wall -Werror -Wpedantic -pthread -std=c11 -c starcraft3.c

starcraft3: starcraft3.o
	gcc -Wall -Werror -Wpedantic -pthread -std=c11 starcraft3.o -o starcraft3

clean:
	rm *.o starcraft3