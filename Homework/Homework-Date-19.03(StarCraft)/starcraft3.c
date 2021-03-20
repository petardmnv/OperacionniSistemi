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

int remaining_minerals;
int mined_materials = 0;

/* THREAD 1 - worker*/
void* work(void *pack){

    struct workerPack* p = (struct workerPack*)pack;

    while (remaining_minerals > 0){

	    for (int i = 0; i < p->mineral_blocks; i++){

	    	if (p->resourses[i] > 0){
	    		sleep(3);

	    		while(p->resourses[i] > 0){

	    			int tmp_mined_materials = 0;

			 		if (pthread_mutex_lock(&lock)) { 
						printf("\n ERROR: mutex_lock() has failed!\n"); 
						exit(-1);  
					} 


					//Mining minerals
					printf("SCV %d is mining from mineral block %d\n", p->id, i + 1);

		    		if (p->resourses[i] >= 8){

			    		p->resourses[i] -= 8;
		    			remaining_minerals -= 8;
		    			tmp_mined_materials = 8;

		    		}else{

		    			remaining_minerals -= p->resourses[i];
		    			tmp_mined_materials = p->resourses[i];
		    			p->resourses[i] = 0;
		    		}


		    		//Transporting minerals
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

					// Delivering minerals
					printf("SCV %d delivered minerals to the Command center\n", p->id);
					mined_materials += tmp_mined_materials;


					if (pthread_mutex_unlock(&lock)) { 
						printf("\n ERROR: mutex_unlock() has failed!\n"); 
						exit(-1); 
					}
				}	
	    	}
	    }
	}
    free(p);
    return NULL;
}

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


	int *mineral_blocks_resourses = malloc(sizeof(int) * mineral_blocks);
	for (int i = 0; i < mineral_blocks; ++i){
		mineral_blocks_resourses[i] = 500;
	}

	remaining_minerals = mineral_blocks * 500;

	pthread_t *workers = malloc(sizeof(pthread_t) * 5);

	// Creating threads
	for (int i = 0; i < workers_count; i++){
		int worker_id = i + 1;

		struct workerPack *pack = malloc(sizeof(struct workerPack));
		pack->id = worker_id;
		pack->resourses = mineral_blocks_resourses;
		pack->mineral_blocks = mineral_blocks;

		if(pthread_create(&(workers[i]), NULL, &work, (void*)pack)){
	        printf("\n ERROR: worker pthread_create() has failed!\n");
	       	return 1;
	    }
	}


	int marines_count = 0;

	while (remaining_minerals > 0 || marines_count < 20){
		char input;
		scanf("%c", &input);

		if (input == 'm'){
			if (mined_materials < 50){
				printf("Not enough minerals\n");
			}else{

				mined_materials -= 50;
				sleep(1);
				printf("You wanna piece of me, boy?\n");
				marines_count += 1;
			}
		}

		if (input == 's'){

			if (mined_materials < 50){
				printf("Not enough minerals\n");
			}else{

				mined_materials -= 50;
				sleep(4);
				printf("SCV good to go, sir.\n");
				workers_count += 1;
			}
			workers = realloc(workers, sizeof(pthread_t) * workers_count);

			struct workerPack *pack = malloc(sizeof(struct workerPack));
			pack->id = workers_count;
			pack->resourses = mineral_blocks_resourses;
			pack->mineral_blocks = mineral_blocks;

			if(pthread_create(&(workers[workers_count - 1]), NULL, &work, (void*)pack)){
		        printf("\n ERROR: worker pthread_create() has failed!\n");
		       	return 1;
		    }

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


	printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", mineral_blocks * 500, mined_materials, workers_count, marines_count);

	free(mineral_blocks_resourses);
    return 0;
}