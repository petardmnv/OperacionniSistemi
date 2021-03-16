#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int Gold = 0;

pthread_mutex_t lock; 
/* THREAD 1 - miner*/
void *get_gold(void *p){
    //read from terminal
    pthread_mutex_lock(&lock);
    int *miner_id = (int*) p;
    Gold += 10;
    printf("Miner %d gathered 10 gold\n", *miner_id);
    pthread_mutex_unlock(&lock);
    sleep(2);
    return NULL;
}

/* THREAD 2 - merchant*/
void* sell_gold(void *p){
    pthread_mutex_lock(&lock);
	int *seller_id = (int*) p;
    if (Gold >= 10) {
    	Gold -= 10;
    	printf("Trader %d sold 10 gold\n", *seller_id);
    }else {
    	printf("The warehouse is empty, cannot sell!\n");
    }
    pthread_mutex_unlock(&lock);
    sleep(2);
    return NULL;
}


int main(int argc, char *argv[])
{

	/*

	After every mined or selled gold people are resting for 2 seconds - sleep()

	Every miner produces 10kg gold
	Every seller is selliong 10kg gold

	Every mine has current gold resourse

	if there is no more gold and seller wants to sell gold print - "The warehouse is empty, cannot sell!"

	After every action you print - "Miner Ngathered 10 gold" and "Trader N sold 10 gold"

	Afret 20 minings and selling program ends and prints current gold 
	
	*/

	int returned_value;

	if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	}
	int miners_count = 1;
	int merchants_count = 1;

	// Find miners and merchants count
	if (argc == 3){
		miners_count = atoi(argv[1]);
		merchants_count = atoi(argv[2]);
	}

	pthread_t miner[miners_count], merchant[merchants_count];

    for (int m = 0; m < miners_count; ++m){
		returned_value = pthread_create(&miner, NULL, &get_gold, &m);
		if(returned_value){
	        printf("ERROR: miner pthread_create() return %d - %s \n", returned_value, strerror(returned_value));
	       	return 1;
	    }
    }

    for (int t = 0; t < merchants_count; ++t){
       	returned_value = pthread_create(&merchant, NULL, &sell_gold, &t);
		if(returned_value){
		   	printf("ERROR: merchant pthread_create() return %d - %s \n", returned_value, strerror(returned_value));
		    return 1;
		}
    }

    //TODO multiple threads joining
    pthread_join(miner, NULL);
    pthread_join(merchant, NULL);

    printf("Gold: %d\n", Gold);
    return 0;
}