//Ejemplo de comunicación de dos procesos mediante memoria compartida
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>


int main()
{
	int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    int r, l = 5;
    int* data = malloc(sizes[l]);

	struct timeval start, end;
    gettimeofday(&start, NULL); 

    pid_t pid;
    key_t key=6677;
    int shmId;
    //crear espacio de memoria compartida
    shmId = shmget(key, sizes[l], 0666|IPC_CREAT);
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }
    //asociar espacio de memoria creada a este proceso
    data = (int *)shmat(shmId, 0, 0);
    pid = fork();
	if (pid == -1 ){
        perror("error fork");
        exit(EXIT_FAILURE);
    } if(pid == 0){ //hijo
		for( int i=0; i<sizes[l]/4; i++ ){
            *(data+i) = 420;
        }
	} else { //padre
        wait(NULL);

        gettimeofday(&end, NULL);

        printf("time: %f\n", (double) ((end.tv_sec - start.tv_sec)*1000000L
           + end.tv_usec - start.tv_usec));
        
        exit(0);
	}
    r = shmdt(data);  //desasociar espacio de memoria compartida
    if(r < 0){
      perror("error shmdt ");
      exit(-1);
    }
}