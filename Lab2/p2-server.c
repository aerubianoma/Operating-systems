#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "binGen/node.h"  
#define SIZE 1024
#define MAXCHAR 1000    
 
void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];
 
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}

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
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0){
  printf("[+]Listening....\n");
  }else{
  perror("[-]Error in listening");
    exit(1);
  }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("[+]Data written in the file successfully.\n");
      // Open a binary file with the data from the dataset, in read and creation mode
    FILE *times = fopen("binGen/bogotaTimes.bin", "rb+");
    // Open a binary file with the hash table, in read and creation mode
    FILE *hash = fopen("binGen/hashTable.bin", "rb+");
    // Open the csv with the input data
    FILE *fp_raw = fopen("recv.txt","r");

    // Variable for the rows in fp_raw (the dataset from dropbox) 
    char row_s[MAXCHAR];
    // Get the values in the columns
    char *token1;
    char *token2;
    char *token3;

    // Set the pointer in the begining of the file fp_raw
    rewind(fp_raw);
    fgets(row_s, MAXCHAR,fp_raw); 
    // Get the data that is before the first , and save it in token (idOrigen)
    token1 = strtok(row_s, ",");    
    // IdOrigen that we want
    int idO = atoi(token1);
    // Get the data that is after the first , and before the next ,    
    token2 = strtok(NULL,",");
    // IdDestino that we want
    int idD = atoi(token2);
    // Get the data that is after the second , and before the next ,
    token3 = strtok(NULL,",");
    // Hora that we want
    int hora = atof(token3);

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

    // Close the file times
    fclose(times);
    // Close the file hash
    fclose(hash);

  return 0;
}