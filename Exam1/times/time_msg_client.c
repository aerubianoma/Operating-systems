#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 3535

float time_diff(struct timeval *start,struct timeval *end){
    
    return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);

}

float c = 0;


int main(int argc, char *argv[]){
for(int i=0; i<6; i++){

    // Array with the sizes in bits for the experiment
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    
    for(int j=0; j<5; j++){

        // 
        int clientfd, r;

        // Struct necessary to configure the socket
        struct sockaddr_in client;
        struct hostent *he;

        // Size that we are going to use for the experiment
        int l = i;
        
        // Pointer that reserves sizes[l] bites of memory 
        int* data = malloc(sizes[l]);

        // Struct that contains the execution time
    	struct timeval start, end;
        
        // Here we create the socket for the client
        clientfd = socket(AF_INET, SOCK_STREAM, 0);

        // Check error in client socket
        if(clientfd < 0){

            perror("Error in socket");
            exit(-1);
        
        }

        // Initialize values in the struct of the socket
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        inet_aton("127.0.0.1", &client.sin_addr);
        
        // Conect client to the server
        r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));

        // Take actual time, necessary for the experiment (initial time)
    	gettimeofday(&start, NULL); 

        // Check error in client connect
        if(r < 0){

            perror("Error in connect");
            exit(-1);
        
        }

        // Receive response from the server
        r = recv(clientfd, data, sizes[l], 0);

        // Check error in recv
    	if(r < 0){

            perror("Error in recv");
            exit(-1);
        
        }
    	
        // Take actual time, necessary for the experiment (final time)
        gettimeofday(&end, NULL);

        // Take time
        c += time_diff(&start,&end);

        }
    
        printf("Average time: %f for size %d\n",c/5,sizes[i]);
    
    }

}