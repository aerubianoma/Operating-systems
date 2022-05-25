#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> 

float time_diff(struct timeval *start,struct timeval *end){
    return (end->tv_sec-start->tv_sec)+1e-6*(end->tv_usec-start->tv_usec);
}

float c=0;


int main(){
    
for(int i=0; i<6; i++){

    // Array with the sizes in bits for the experiment
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};

    for(int j=0; j<5; j++){
    // Position of the array
    int l = i;
    // Pointer that reserves sizes[l] bites of memory
    int* data = malloc(sizes[l]);

    // Here we initialize r and pipefd that has the information (read and write) of the pipe
	int r,pipefd[2];
    // Parent id
	pid_t pid;
    
    // Struct that contains the execution time
    struct timeval start, end;
    // Take actual time, necessary for the experiment (initial time)
    gettimeofday(&start, NULL); 

    // Create pipe
	r=pipe(pipefd);

    // Check error in pipe
	if(r<0){
		perror("Error pipe");
		exit(-1);
	}

    // We create a child process
    pid = fork();

    // Check error in fork
	if (pid == -1 ){
        perror("Error fork");
        exit(-1);
    } 

    // Here we are in the child process
    if(pid == 0){
        // We have the descriptor in the child process, thats why we already have it and we can close
		close(pipefd[1]);
        // Will block parent process until any of its children has finished
        wait(NULL);
        // read the data in the file data and save it into the descriptor of the pipe
        r = read(pipefd[0],data,sizes[l]);
        // We read so we close the pipe
		close(pipefd[0]);        
        exit(0);

	} 

    // Here we are in the parent process
    // We have the descriptor in the child process, thats why we already have it and we can close
	close(pipefd[0]);
    // we set values to the data pointer
	for( int i=0; i<sizes[l]/4; i++ ){
        *(data+i) = 420;
    }; 
    // We read the information that pass throught the pipe
	r = write(pipefd[1],data,sizes[l]);
    // We close the pipe
    close(pipefd[1]);

    // Take actual time, necessary for the experiment (final time)
    gettimeofday(&end, NULL);

    // Take time
    c += time_diff(&start,&end);
        
	

    free(data);
    }
    printf("Average time: %f for size %d\n",c/5,sizes[i]);
}
    return 0;
}