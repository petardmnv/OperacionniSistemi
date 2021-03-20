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


pthread_mutex_t lock; 

struct workerPack{
	int id;
	int mineral_blocks;
	int *resourses;
};

/* THREAD 1 - worker*/
void* work(void *pack){
    struct workerPack* p = (struct workerPack*)pack;

    sleep(3);
    for (int i = 0; i < p->mineral_blocks; ++i){
    	if (p->resourses[i] < 8){
    		sleep(3);
    	}else{
    		while(p->resourses[i] >= 8){
		 		if (pthread_mutex_lock(&lock)) { 
					printf("\n ERROR: mutex_lock() has failed!\n"); 
					exit(-1);  
				} 

	    		printf("SCV %d is mining from mineral block %d\n", p->id, i + 1);
	    		p->resourses[i] -= 8;

	    		printf("SCV %d is transporting minerals\n", p->id);
	    		if (pthread_mutex_unlock(&lock)) { 
					printf("\n ERROR: mutex_unlock() has failed!\n"); 
					exit(-1); 
				}	

				sleep(2);

		 		if (pthread_mutex_lock(&lock)) { 
					printf("\n ERROR: mutex_lock() has failed!\n"); 
					exit(-1);  
				} 

				printf("SCV %d delivered minerals to the Command center\n", p->id);

				if (pthread_mutex_unlock(&lock)) { 
					printf("\n ERROR: mutex_unlock() has failed!\n"); 
					exit(-1); 
				}
			}	
    	}
    }
    free(p);
    return NULL;
}

/* THREAD 2 - merchant*/
/*void* sell_gold(void *id){
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
}*/


int main(int argc, char *argv[])
{

	int workers_count = 5;
	int mineral_blocks;

	// Mutex creation
	if (pthread_mutex_init(&lock, NULL)) { 
		printf("\n ERROR: mutex_init() has failed!\n"); 
		exit(-1); 
	}

	// Get mineral_blocks count
	if (argc == 2){
		mineral_blocks = atoi(argv[1]);
	}else if (argc == 1){
		mineral_blocks = 2;
	}else{
		printf("\nError: Invalid number of arguments!\n");
		return -1;
	}


	int mineral_blocks_resourses[mineral_blocks];
	for (int i = 0; i < mineral_blocks; ++i){
		//#TODO
		//Change to 1000 now is 50
		mineral_blocks_resourses[i] = 50;
	}
	/*
		Game starts:
			- 2 mineral blocks 
			- you could change mineral blocks
			- Workers:
				- 5 workers
				- Worker can't mine from empty material block
				- mining materials - before that print - "SCV N is mining from mineral block M" 3s for finding mine
				- transport minerals to command center - 2s - "SCV N is transporting minerals"
				- delivering materials - print - "SCV N delivered minerals to the Command center"
				- On every mining miner mines 8 materials

			- 20 Marines needed to finsh the game
			- Comand Center:
				- all workers deliver materials to command center(workers couldn't deliver materials at the same time)	
				- player is typing commands while the program is runnung
				- player can type - m for marine creation 
				- marine creation costs - 50 minerals and 1s time for creation
				- player can type - s for worker creation 
				- worker creation costs 50 minerals and 4s for creation
				- after marine is created console prints - "You wanna piece of me, boy?"

		Game ends:
			- console prints - "Map minerals N, player minerals M, SCVs X, Marines Y"

	*/

	pthread_t workers[workers_count];

	// Creating threads
	for (int i = 0; i < workers_count; i++){
		int worker_id = i + 1;

		struct workerPack *pack = malloc(sizeof(struct workerPack));
		pack->id = worker_id;
		pack->resourses = malloc(sizeof(int) * mineral_blocks);
		for (int j = 0; j < mineral_blocks; ++j){
			pack->resourses[j] = mineral_blocks_resourses[j];
		}
		pack->mineral_blocks = mineral_blocks;

		if(pthread_create(&(workers[i]), NULL, &work, (void*)pack)){
	        printf("\n ERROR: worker pthread_create() has failed!\n");
	       	return 1;
	    }
	}

	for (int i = 0; i < workers_count; i++){
		if (pthread_join(workers[i], NULL)) { 
			printf("\n ERROR: worker pthread_join() has failed!\n"); 
			exit(-1); 
		}	
	}


	// Mutex destroing
	if (pthread_mutex_destroy(&lock)) { 
		printf("\n ERROR: mutex_destroy() has failed!\n"); 
		exit(-1); 
	}

    return 0;
}