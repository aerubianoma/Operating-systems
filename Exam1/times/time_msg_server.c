#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


#define PORT 3535
#define BACKLOG 2

float time_diff(struct timeval *start,struct timeval *end){
    
    return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);

}

float c = 0;

/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
*/

int serverfd;

int main(){
for(int i=0; i<6; i++){
    
    // Array with the sizes in bits for the experiment
    int sizes[] = {1024,10240,102400,1048576,10485760,104857600};
    
    for(int j=0; j<5; j++){
        
        // Size that we are going to use for the experiment and check error when server is listen
        int r, l = i;
        
        // Pointer that reserves sizes[l] bites of memory 
        int* data = malloc(sizes[l]);

        // Struct that contains the execution time
    	struct timeval start, end;

        // 
        int clientfd, opt = 1;
        
        // Struct necessary to configure the socket
        struct sockaddr_in server, client;
        
        // Size of the socket
        socklen_t tamano;

        // Here we create the socket for the server
        serverfd = socket(AF_INET, SOCK_STREAM, 0);
        
        // Check error in socket
        if(serverfd < 0){
           
            perror("Error in server socket");
            exit(-1);
        
        }

        // Initialize values in the struct of the socket
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = INADDR_ANY;
        bzero(server.sin_zero, 8); 


        // Set position in memory of the socket
        setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

        // Initiate the server
        r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));

        // Check error in server bind
        if(r < 0){

            perror("Error in server bind");
            exit(-1);
        
        }

        // Our socket here is a server
        r = listen(serverfd, BACKLOG);

        // Check errir in server liste
        if(r < 0){

            perror("Error in server listen");
            exit(-1);
        
        }

        // Accept client
        clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
    	
        // Take actual time, necessary for the experiment (initial time)
        gettimeofday(&start, NULL); 

        // Check error in server accept
        if(clientfd < 0)
        {
            perror("Error in server accept");
            exit(-1);
        }

    	for( int i=0; i<sizes[l]/4; i++ ){
        
            *(data+i) = 420;
        
        }

        // Send response from server to client
        r = send(clientfd, data, sizes[l], 0);

        // Check error in server send
        if(r < 0){

            perror("Error in server send");
            exit(-1);
        
        }

        // Take actual time, necessary for the experiment (final time)
    	gettimeofday(&end, NULL);
        
        // Take time
        c += time_diff(&start,&end);

        // Close the server
        close(serverfd);
        
        }
    
        printf("Average time: %f for size %d\n",c/5,sizes[i]);
    
    }

}