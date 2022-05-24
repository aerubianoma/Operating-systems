#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>


int main(){
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    int l = 5;
    int* data = malloc(sizes[l]);
	int r,pipefd[2];
	pid_t pid;
    
    struct timeval start, end;
    gettimeofday(&start, NULL); 

	r=pipe(pipefd);
	if(r<0){
		perror("Error in pipe()");
		exit(-1);
	}

    pid = fork();

	if (pid == -1 ){
        perror("error fork");
        exit(EXIT_FAILURE);
    } if(pid == 0){ //hijo
		close(pipefd[1]);
        wait(NULL);
        r = read(pipefd[0],data,sizes[l]);
        if(r<sizes[l]){
            perror("Fallo read() hijo");
            exit(-1);
        }
		close(pipefd[0]);

        gettimeofday(&end, NULL);

        printf("time: %f\n", (double) ((end.tv_sec - start.tv_sec)*1000000L
           + end.tv_usec - start.tv_usec));
        
        exit(0);
	} else { //padre
		close(pipefd[0]);
		for( int i=0; i<sizes[l]/4; i++ ){
            *(data+i) = 420;
        }; 

		r = write(pipefd[1],data,sizes[l]);
        if(r<sizes[l]){
            perror("Fallo write() padre");
            exit(-1);
        }

        close(pipefd[1]);    
        
	}

    return 0;
}