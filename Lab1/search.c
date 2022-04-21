#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binGen/node.h"                                                                

// Lenght of all the idOrigen in the dataset
#define HASH_SIZE 1160
// Lenght for the chars in a row
#define MAXCHAR 1000
                                                              

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

    	// Open a binary file with the data from the dataset, in read and creation mode
    	FILE *times = fopen("binGen/bogotaTimes.bin", "rb+");
    	// Open a binary file with the hash table, in read and creation mode
	FILE *hash = fopen("binGen/hashTable.bin", "rb+");
	// Open a csv file with the data for search, in read and creation mode
    	FILE *data = fopen("Busqueda.csv","r");
	// Variable for the rows in data
   	static char row[MAXCHAR];
   	// Variable for the items in the rows
	static char *token;
    
    
	// Obtain the first row of the file with a max size of 1000 characters
	fgets(row, MAXCHAR, data);
	token=strtok(row, ",");
    // IdOrigen that we want
    int idO = atoi(token);
    // IdDestino that we want
    token=strtok(NULL,",");
    int idD = atoi(token);
    // Hora that we want
    token=strtok(NULL,",");
    int hora = atoi(token);

    // Call the function search to look for the time that we want 
    float time = search(idO, idD, hora, times, hash);
    // There is no time for that configuration
    if(time == -1){
        printf("Data not found\n");
    // Return the answer
    }else{
        printf("%f\n", time);
    }

    // Close the file times
    fclose(times);
    // Close the file hash
    fclose(hash);
}
