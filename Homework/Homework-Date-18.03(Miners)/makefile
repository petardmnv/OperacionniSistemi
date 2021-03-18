all: miners

miners.o: miners.c
	gcc -Wall -Werror -Wpedantic -pthread -std=c11 -c miners.c

miners: miners.o
	gcc -Wall -Werror -Wpedantic -pthread -std=c11 miners.o -o miners

clean:
	rm *.o miners