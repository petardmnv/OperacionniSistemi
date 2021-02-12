#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void *count_numbers(void *number){
	int *arr = (int *) number;
	int *result = malloc(sizeof(int));
	*result = 0;
	for(int i = arr[0] + 1; i <= arr[1]; ++i){
		result += i;
	}
	free(arr);
	pthread_exit(result);
}
int main(int argc, char const *argv[])
{
	int counted_number = 0;

	int threads_count = atoi(argv[1]);
	pthread_t threads[threads_count];
	int number = atoi(argv[2]);

	int segment = (int) number / threads_count;
	int starting_from = 0;
	for (int i = 0; i < threads_count; ++i){
		int *arr = malloc(sizeof(int) * 2);
		arr[0] = starting_from + 1;
		if (i == threads_count - 1){
			starting_from = number;
		}
		else{
			starting_from += segment;
		}
		arr[1] = starting_from;

		//printf("%d\n", starting_from);
		int rv = pthread_create(&threads[i], NULL, &count_numbers, (void *)&arr);
		if(rv){
            printf("ERROR; pthread_create() return %d - %s \n", rv, strerror(rv));
	        exit(-1);
	    }

	    int *result;
	    pthread_join(threads[i], (void **) &result);
        counted_number += *result;
	}

    printf("%d\n", counted_number);
	return 0;
}