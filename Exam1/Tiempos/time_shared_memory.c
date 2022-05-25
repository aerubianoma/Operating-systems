//Ejemplo de comunicación de dos procesos mediante memoria compartida
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

float time_diff(struct timeval *start,struct timeval *end){
    return (end->tv_sec-start->tv_sec)+1e-6*(end->tv_usec-start->tv_usec);
}

float c=0;

int main(){

for(int i=0; i<6; i++){

    // Array with the sizes in bits for the experiment
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};

    for(int j=0; j<5; j++){
    // Size that we are going to use for the experiment
    int l = i;
    // Variable to check error in shmdt
    int r = 0;
    // Variable to read the data
    char out;
    // Pointer that reserves sizes[l] bites of memory  
    int* data = malloc(sizes[l]);

    // Struct that contains the execution time
	struct timeval start, end;
    // Take actual time, necessary for the experiment (initial time)
    gettimeofday(&start, NULL); 

    // Parent id
    pid_t pid;

    // Key for the shared memory
    key_t key = 1000+l;
    // Id for the shared memory
    int shmId;
    // Create the space for shared memory
    shmId = shmget(key, sizes[l], IPC_CREAT);
    // Check error in shmget
    if(shmId < 0){
        perror("Error in first shmget");
        exit(-1);
    }

    // Associate the shared memory to this process
    data = (int *)shmat(shmId, 0, 0);

    // We create a child process
    pid = fork();
    // Check error in fork
	if (pid == -1 ){
        perror("Error in fork");
        exit(EXIT_FAILURE);
    } 
    // Here we are in the child process
    if(pid == 0){
		for( int i=0; i<sizes[l]/4; i++ ){
            *(data+i) = 420;
        }
        exit(0);
	} 

    // Here we are in the parent process
    // Will block parent process until any of its children has finished
    wait(NULL);
    // Take actual time, necessary for the experiment (final time)
    gettimeofday(&end, NULL);

    // Take time
    c += time_diff(&start,&end);
    
	
    // Disassociate the space for shared memory
    r = shmdt(&data);
    // Check error in shmdt
    if(r < 0){
      perror("Error in last shmdt ");
      exit(-1);
    }
    free(data);
    }
    printf("Average time: %f for size %d\n",c/5,sizes[i]);
}
return 0;
}