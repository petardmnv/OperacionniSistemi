// Peho 
// Malko e grozno
// ama kot takova
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//Copied race_cond.c. Cuz I am lazy b.
#define BUFFER_SIZE 10000

char data[BUFFER_SIZE];
pthread_mutex_t lock; 

/* THREAD 1 */
void *read_from_terminal(void *p){
    //read from terminal
    pthread_mutex_lock(&lock);
    ssize_t r;
    char buff[BUFFER_SIZE] = {0};
    while((r = read(STDIN_FILENO, buff, BUFFER_SIZE)) > 0){
        if (r == -1){
            printf("Read failed.");
        }
        strcat(data, buff);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

/* THREAD 2 */
void* read_from_buffer(void *p){
    //write data to terminal
    pthread_mutex_lock(&lock);
    ssize_t w = write(STDOUT_FILENO, data, strlen(data));
    if (w == -1){
        printf("Write failed.");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}


int main(int argc, char *argv[])
{
    int rc;
    pthread_t thr1, thr2;

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

    rc = pthread_create(&thr1, NULL, &read_from_terminal, NULL);
	if(rc){
        printf("ERROR: thread 1 pthread_create() return %d - %s \n", rc, strerror(rc));
        return 1;
    }

    rc = pthread_create(&thr2, NULL, &read_from_buffer, NULL);
    if(rc){
        printf("ERROR: thread 2 pthread_create() return %d - %s \n", rc, strerror(rc));
        return 1;
	}
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    return 0;
}
