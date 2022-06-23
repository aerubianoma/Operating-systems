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
	time_t T = time(NULL);
	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	int buffer[3];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			
				recv(newSocket, buffer, sizeof(buffer), 0);
// Set the pointer in the begining of the file fp_raw

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
            // There is no time for that configuration
            if(time == -1){
                printf("______________________________________ \n");
                printf("Data not found\n");
                printf("______________________________________ \n");
            // Return the answer
            }else{
                printf("______________________________________ \n");
                printf("Su tiempo promedio es:\n");
                printf("%f\n", time);
                printf("______________________________________ \n");
            }

            struct tm tm = *localtime(&T);
            FILE *logs = fopen("logs.txt", "a");
            fprintf(logs, "Fecha: %04d/%02d/%02d %02d:%02d:%02d  Cliente: %s [%f - %d - %d - %d]\n", tm.tm_year + 1900, tm.tm_mon +1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(newAddr.sin_addr),time, idO, idD, hora);

            // Close the file times
            fclose(times);
            // Close the file hash
            fclose(hash);
            
				printf("Client: %d\n", buffer[0]);
				send(newSocket, &time, sizeof(time), 0);
				//bzero(time, sizeof(time));
				
			
		}

	}

	close(newSocket);


	return 0;
}
