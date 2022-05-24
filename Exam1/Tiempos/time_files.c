#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>


int main(){

        // Array with the sizes in bits for the experiment
        int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
        // Size that we are going to use for the experiment
        int l = 6;
        // Pointer that reserves 104857600 bites of memory  
        int* data = malloc(sizes[l]);
        // Variables that we dont use (?)
    	int r;
        // Parent ID
    	pid_t pid;
        // Pointer to the file fp
        FILE *fp;
        
        // Here we initialize two structs
        struct timeval start, end;
        // Take actual time, necessary for the experiment (initial time)
        gettimeofday(&start, NULL); 

        // We create a child process
        pid = fork();

        // Check the error in fork
    	if (pid == -1 ){
            perror("error fork");
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

    	} 

        // Here we are in the parent process
        else {
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

            // Take actual time, necessary for the experiment (final time)
            gettimeofday(&end, NULL);

            printf("time: %f\n", (double) (end.tv_usec - start.tv_usec));
            
            // Close the file
            fclose(fp);
            exit(0);
    	}

        // Free the memory that malloc had 
        free(data);

    return 0;
}