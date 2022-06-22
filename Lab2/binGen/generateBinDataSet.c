// Necessary libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// Lenght of the csv from dropbox with all the data
#define TABLE_SIZE 5904703 
// Lenght for the chars in a row
#define MAXCHAR 1000

// Struct that has variables named in the same way that they are in our data set
// Here is an aditional value for the next idOrgn in the datasaet to do the search faster
typedef struct row{
    // IdOrigen
    int idOrgn;
    // IdDestino
    int idDest;
    // Hour
    int hour;
    // Time (value that we are looking for in the search)
    float time;
    // Next idOrigen that is equal to the current idOrigen
    long next;
} row;

// Generate a empty array of structs of type row with size TABLE_SIZE
row * init_hash_table(int table_size){
    // Instantiate a struct of type row
    row *hash_table;
    // Assign memory to hash_tabletable with size bytes of row multiplied by the size of the entire dataset
    hash_table = malloc(table_size*sizeof(row));
    // Iterate over this array
    for(int i= 0; i< table_size; i++){
        // Initiate the next value with -1
        hash_table[i].next = -1;
    }
    // Return the array
    return hash_table;
}

// Iterate over the table to link the rows with the same idOrigen
void parenting(FILE *fp){
    // A struct that is going to have the data in
    row *tmp;
    // Assign memory to hash_tabletable with size bytes of row multiplied by the size of the entire dataset
    tmp = malloc(TABLE_SIZE*sizeof(row));
    // Array to know if a idOrigen was check
    bool vis[1160];                                                 

    // Set the pointer in the begining of the file fp
    rewind(fp);
    // Read the fp file and write the data in the array tmp with every row size of the struct row and TABLE_SIZE rows
    fread(tmp, sizeof(row), TABLE_SIZE, fp);                        

    // Iterate over all the rows in the dataset-1 because it has header from the bottom of the dataset
    for(int i = TABLE_SIZE-1; i >= 0; i--){
        // Save the ith row of the the dataset binary file in cmp
        row cmp = tmp[i];
        // Check if an idOrigen was visited
        if(vis[cmp.idOrgn-1] != true){
            // Save the value of the current position in next
            int next = i;
            // Iterate from the current position i to the top of the dataset
            for (int j = i-1; j >= 0; j--){
                // check if the idOrigen of cmp is equal to a upper row idOrigen in the dataset 
                if (tmp[j].idOrgn == cmp.idOrgn && tmp[j].next != next){
                    // Save the next atributte of th upper value of cmp
                    tmp[j].next = sizeof(row)*next;
                    // Set next to continue to the top of the file
                    next = j;
                }      
            }
            // Check the idOrigen as visited
            vis[cmp.idOrgn-1] = true;
        }  
    }

    // Set the pointer in the begining of the file fp
    rewind(fp);
    // Write in the fp file the data in the array tmp with every row size of the struct row and TABLE_SIZE rows
    fwrite(tmp, sizeof(row),TABLE_SIZE, fp);
    // Free the memory that tmp was using
    free(tmp);
}

int main(){
    // Variable for the rows in fp_raw (the dataset from dropbox) 
    char row_s[MAXCHAR];
    // Get the values in the columns
	char *token;

    // Open the csv of our the dataset from dropbox in lecture mode
    FILE *fp_raw = fopen("bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");
    // Open a binary file with the data from the dataset with a new column, in write and creation mode
    FILE *fp = fopen("bogotaTimes.bin", "wb+");

    // Struct that has variables equal to the wors in the dataset and a new one for the next values
    row *table; 
    // Initiate an array of struct with next values -1
    table = init_hash_table(TABLE_SIZE);

    // Set the pointer in the begining of the file fp_raw
    rewind(fp_raw);

    // Obtain the first row of the file with a max size of 1000 characters  
    fgets(row_s, MAXCHAR,fp_raw);
    // Iterate over the size of the dataset
    for(int i = 0; i< TABLE_SIZE; i++){
        // fgets after read go to the next position in the file
        // Here we check all the rows of fp_raw
        fgets(row_s, MAXCHAR,fp_raw);
        // Get the data that is before the first , and save it in token (idOrigen)
	    token = strtok(row_s, ",");
        // Convert the idOrigen from char to int      
	    table[i].idOrgn = atoi(token);
        // Get the data that is after the first , and before the next ,  and save it in token (idDestino) 
	    token = strtok(NULL,",");
        // Convert the idDestino from char to int
	    table[i].idDest = atoi(token);
        // Get the data that is after the second , and before the next ,  and save it in token (hour) 
        token = strtok(NULL, ",");
        // Convert the hour from char to int
        table[i].hour = atoi(token);
        // Get the data that is after the third , and before the next ,  and save it in token (time) 
        token = strtok(NULL, ",");
        // Convert the time from char to float
        table[i].time = atof(token); 
    }
    // Close the file fp_raw
    fclose(fp_raw);

    // Write in the fp file the data in the array table with every row size of the struct node and TABLE_SIZE rows
    fwrite(table, sizeof(row), TABLE_SIZE, fp);
    // Set the pointer in the begining of the file fp_raw
    rewind(fp);
    // Set the values in column next
    parenting(fp);                                                  //aplica el emparentado
    // Close the file fp_raw
    fclose(fp);
    // Free the memory that table was using
    free(table);
    
    return 0;
}