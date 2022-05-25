#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>

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
        // Pointer that reserves sizes[l] bites of memory  
        int* data = malloc(sizes[l]);
        // Variable that saves what we are writing in the file
    	int r;
        // Parent ID
    	pid_t pid;
        // Pointer to the file fp
        FILE *fp;
        
        // Struct that contains the execution time
        struct timeval start, end;
        // Take actual time, necessary for the experiment (initial time)
        gettimeofday(&start, NULL); 

        // We create a child process
        pid = fork();

        // Check the error in fork
    	if (pid == -1 ){
            perror("Error fork");
            exit(EXIT_FAILURE);  
        }

        // Here we are in the child process 
        if(pid == 0){
            // Open the file data
            fp = fopen("data","w+");
            
            // Check error opening the file
            if(fp == NULL){
                perror("Error in child fopen() ");
            }
            
            // we set values to the data pointer
    		for(int i=0; i<sizes[l]/4; i++ ){
                *(data+i) = 420;
            }

            // Write in the file the data
    		r = fwrite(data,sizes[l],1,fp);
            // Check if there was a error in the write
            if(r==0){
                perror("Error in child fwrite()");
                exit(-1);
            }

            fclose(fp);
            exit(0);

    	} 

        // Here we are in the parent process
    
        // Will block parent process until any of its children has finished
        wait(NULL);
        // Open the data file    
        fp=fopen("data","r");

        // Check error opening the file
        if(fp==NULL){
            perror("Error in parent fopen()");
        }
        // Save the data that was read
        r = fread(data,sizes[l],1,fp);
        // Check error reading the file
        if(r==0){
            perror("Error in parent fread()");
            exit(-1);
        }

        // Close the file
        fclose(fp);

        // Take actual time, necessary for the experiment (final time)
        gettimeofday(&end, NULL);

        // Take time
        c += time_diff(&start,&end);
	    // Free the memory that malloc had 
        free(data);
    }
    printf("Average time: %f for size %d\n",c/5,sizes[i]);
}
    return 0;
}