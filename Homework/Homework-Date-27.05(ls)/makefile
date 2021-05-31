all: ls

ls.o: ls.c
	gcc -Wall -Werror -Wpedantic -c ls.c

ls: ls.o
	gcc -Wall -Werror -Wpedantic ls.o -o ls

clean:
	rm *.o ls