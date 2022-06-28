#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>
#include "binGen/node.h"  

#define PORT 4444

// Search the time from idOrigen to idDestino at an specific hour
float search(int idO, int idD, int hora, FILE *times, FILE *hash){                
    
    // Struct that has variables named key and first
    node index;                                                                     

    // Set the pointer in the begining of the file hash (our hash table in binary)
    rewind(hash);
    // Set the pointer in the position on the row idOrigen of hash (remenber it is ordered)
    fseek(hash, sizeof(node)*(idO-1), SEEK_SET);
    // Save this data in index
    fread(&index, sizeof(node), 1, hash);
    
    // Set the pointer in the begining of the file times (the dataset in binary)
    rewind(times);
    // Set the pointer in the firts apareance of idOrigen on the dataset
    // Is index.firts - 2 because it is an array with header
    fseek(times, (index.first-2)*sizeof(row), SEEK_SET);

    // A struct that is going to have the data in
    row r;
    // variable that says if we are in the end of the dataset
    bool end_of_list = false;

    // Iterate meanwhile we aren't in the end of the list                              
    while(!end_of_list){
        // Read the times file and write the data in the array r with every row size of the struct row and 1 row
        fread(&r,sizeof(row), 1, times);
        // Check if we are in the correct row
        if(r.idDest == idD && r.hour == hora){  
            // Return the answer         
            return r.time;            
        }
        // Check if there is not more idOrigen equal to our input
        if (r.next == -1){
            // Ends the process
            end_of_list = true;
        }
        // If the other options didn't ocurre
        // Set the pointer in the next apareance of the idOrigen in the dataset 
        fseek(times, r.next, SEEK_SET);                      
    }
    return -1;
}

int main(){

    // Variable to take the date and time in the log file
	time_t T = time(NULL);

    // Variables neccesary to initiate the server
	int sockfd, ret;
	struct sockaddr_in serverAddr;

    // Variables to take the connection of the multiple clients
	int newSocket;
	struct sockaddr_in newAddr;
	socklen_t addr_size;

    // Variables for the inputs of the search received from the client and the output that we are going to send
	int buffer[3];
    char output[1024];

    // Parent id for the fork
	pid_t childpid;

    // Create the socket for the server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Check error in socket creation
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}


    // Struct necessary for the connection
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Initiate the server
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Check error in bind
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}


	if(listen(sockfd, 32) == 0){
		
	}else{
		printf("[-]Error in binding.\n");
	}

    // The server will be listening forever
	while(1){

        //Connect with the client
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);

        // Check error in the connection
		if(newSocket < 0){
			exit(1);
		}
		

        // We fork here and that allow us to receibe multiple clients
		if((childpid = fork()) == 0){
			
            // Here we close the socket of the server, that not permits more accept from it
            close(sockfd);

            // We receive the information from the client
			recv(newSocket, buffer, sizeof(buffer), 0);

		    // Open a binary file with the data from the dataset, in read and creation mode
            FILE *times = fopen("binGen/bogotaTimes.bin", "rb+");
            // Open a binary file with the hash table, in read and creation mode
            FILE *hash = fopen("binGen/hashTable.bin", "rb+");
   
            // IdOrigen that we want
            int idO = buffer[0];

            // IdDestino that we want
            int idD = buffer[1];

            // Hora that we want
            int hora = buffer[2];

            // Call the function search to look for the time that we want 
            float time = search(idO, idD, hora, times, hash);

            // Convert float to string
            gcvt(time,10,output);
            
            // We send the output to the client
            send(newSocket, output, strlen(output), 0);
            bzero(output, sizeof(output));

            // Here we save the important info in a log file
            struct tm tm = *localtime(&T);
            FILE *logs = fopen("logs.txt", "a");
            fprintf(logs, "[Fecha %04d/%02d/%02dT%02d:%02d:%02d]  Cliente [%s] [%f - %d - %d - %d]\n", tm.tm_year + 1900, tm.tm_mon +1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(newAddr.sin_addr),time, idO, idD, hora);

            // Close the file times
            fclose(times);
            // Close the file hash
            fclose(hash);			
		}

	}

    // Here we close the socket of the client
	close(newSocket);
    
	return 0;
}
