// Necesarry libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// archivo with the struct
#include "node.h"

// Lenght of all the idOrigen in the dataset
#define HASH_SIZE 1160
// Lenght of the idOrigen that are really in that column in the dataset                                       
#define CVS_SIZE 1014
// Lenght for the chars in a row
#define MAXCHAR 1000

int main(){
	
	// Instantiate the necessary variables

    // Variable for the rows in fp_raw (our hash table) 
    char row_s[MAXCHAR];
    // Get the firts column in the row 
	char *token;
	// Get the second column in the row
    char *token2;

    // Open the csv of our hash table in lecture mode
    FILE *fp_raw = fopen("hashTable.csv","r");
    // Open a binary file with a new hash table that has the id Origen in order, in write and creation mode
    FILE *fp = fopen("hashTable.bin", "wb+");

    // Struct that has variables named key and first
    node *table; 
    // Assign memory to table with size bytes of node multiplied by the size of all the idOrigen
    table = malloc(sizeof(node)*HASH_SIZE);

    // Set the pointer in the begining of the file fp_raw
    rewind(fp_raw);

    // Iterate over all the idOrigen that are reachable
    for(int i = 0; i < CVS_SIZE; i++){
    	// fgets after read go to the next position in the file
		// Here we check all the rows of fp_raw
        fgets(row_s, MAXCHAR,fp_raw); 
        // Get the data that is before the first , and save it in token (idOrigen)
	    token = strtok(row_s, ",");    
	    // Convert the idOrigen from char to int                     
	    int key = atoi(token);
	    // Save the idOrigen in the key value of the position key-1
	    // Because we want an ordered hash table
	    // Is key-1 because table is an array
        table[key-1].key = key;
        // Get the data that is after the first , and before the next ,  and save it in token2 (position of the first idOrigen)     
	    token2 = strtok(NULL,",");
	    // Convert the position from char to int
        int first = atoi(token2);
        // Save the first position of the idOrigen in the first value of the position key-1
	    // Because we want an ordered hash table
	    // Is key-1 because table is an array                           
	    table[key-1].first = first; 
    }
    // Close the file fp_raw
    fclose(fp_raw);

    // Set the pointer in the begining of the file fp
    rewind(fp);
    // Write in the fp file the data in the array table with every row size of the node struct and HASH_SIZE rows 
    fwrite(table, sizeof(node), HASH_SIZE, fp);
    // close the file fp
    fclose(fp);
    // Free the memory that table was using
    free(table);

    return 0;
}
