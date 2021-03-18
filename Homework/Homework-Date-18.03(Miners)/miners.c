//--------------------------------------------
// NAME: Petur Damianov
// CLASS: XI b
// NUMBER: 21
// PROBLEM: Miners
//---------------------------------------------

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
void* get_gold(void *id){
    int miner_id = *(int*) id;
    for (int i = 0; i < 20; i++){

    	if (pthread_mutex_lock(&lock)) { 
			printf("\n ERROR: mutex_lock() has failed!\n"); 
			exit(-1); 
		}
    	
        Gold += 10;
	    printf("Miner %d gathered 10 gold\n", miner_id);

	   	if (pthread_mutex_unlock(&lock)) { 
			printf("\n ERROR: mutex_unlock() has failed!\n"); 
			exit(-1); 
		}
	    sleep(2);
    }
    return NULL;
}

/* THREAD 2 - merchant*/
void* sell_gold(void *id){
	int seller_id = *(int*) id;
	for (int i = 0; i < 20; i++){

		if (pthread_mutex_lock(&lock)) { 
			printf("\n ERROR: mutex_lock() has failed!\n"); 
			exit(-1);  
		}

	    if (Gold >= 10) {
	    	Gold -= 10;
	    	printf("Trader %d sold 10 gold\n", seller_id);
	    }else {
	    	printf("The warehouse is empty, cannot sell!\n");
	    }

	   	if (pthread_mutex_unlock(&lock)) { 
			printf("\n ERROR: mutex_unlock() has failed!\n"); 
			exit(-1); 
		}
	    sleep(2);
	}
    return NULL;
}


int main(int argc, char *argv[])
{

	int miners_count;
	int merchants_count;

	// Mutex creation
	if (pthread_mutex_init(&lock, NULL)) { 
		printf("\n ERROR: mutex_init() has failed!\n"); 
		exit(-1); 
	}

	// Find miners and merchants count
	if (argc == 3){
		miners_count = atoi(argv[1]);
		merchants_count = atoi(argv[2]);
	}else if (argc == 1){
		miners_count = 1;
		merchants_count = 1;
	}else{
		printf("\nError: Invalid number of arguments!\n");
		return -1;
	}

	pthread_t miner[miners_count], merchant[merchants_count];

	// Creating threads
	for (int m = 0; m < miners_count; m++){
		int miner_id = m + 1;
		if(pthread_create(&(miner[m]), NULL, &get_gold, &miner_id)){
	        printf("\n ERROR: miner pthread_create() has failed!\n");
	       	return 1;
	    }
	}


    for (int t = 0; t < merchants_count; t++){
    	int merchant_id = t + 1;
		if(pthread_create(&(merchant[t]), NULL, &sell_gold, &merchant_id)){
		   	printf("\n ERROR: merchant pthread_create() has failed!\n");
		    return 1;
		}
    }

    // Joining threads
	for (int i = 0; i < miners_count; i++){
		if (pthread_join(miner[i], NULL)) { 
			printf("\n ERROR: miner pthread_join() has failed!\n"); 
			exit(-1); 
		}	
	}
	for (int i = 0; i < merchants_count; i++){
		if (pthread_join(merchant[i], NULL)) { 
			printf("\n ERROR: merchant pthread_join() has failed!\n"); 
			exit(-1); 
		}	
	}


	// Mutex destroing
	if (pthread_mutex_destroy(&lock)) { 
		printf("\n ERROR: mutex_destroy() has failed!\n"); 
		exit(-1); 
	}

    printf("Gold: %d\n", Gold);
    return 0;
}
