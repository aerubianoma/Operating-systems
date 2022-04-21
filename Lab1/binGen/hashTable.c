// Necessary libraries
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<stdbool.h>


// Lenght for the chars in a row
#define MAXCHAR 1000

int main(){

    // Instantiate the necessary variables
    // The big csv from dropbox with all the data
    static FILE *fp;
    // The new csv with our hash table
	static FILE *hashTable;
	// Variable for the rows in fp
   	static char row[MAXCHAR];
   	// Variable for the items in the rows
	static char *token;
	// To know in what row we are 
	int fila = 2;
	// Array to know if a idOrigen was check
	static bool Revisados[1160];

	// Open the csv from dropbox in lecture mode
    fp = fopen("../bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");
	// Open our csv with oun hash table in write and creation mode
	hashTable = fopen("hashTable.csv","w+");

	// Iterate over al the idOrigen
	for(int j = 0;j < 1160;j++){
		// Put all the idOrigen in a not checked mode
		Revisados[j] = false;
	}

	// Set the pointer in the begining of the file fp
	rewind(fp);
	// Obtain the first row of the file with a max size of 1000 characters
	fgets(row, MAXCHAR, fp);

	// Iterate meanwhile we are not in the end of the file fp
	while (feof(fp) != true){
		// fgets after read go to the next position in the file
		// Here we check all the rows of fp
		fgets(row,MAXCHAR,fp);
		// Get the data that is before the first , and save it in token (idOrigen)
		token = strtok(row, ",");
		// Convert the idOrigen from char to int
		int num = atoi(token);
		// Check if that idOrigen was already checked
		if(!Revisados[num]){
			// Write in our hash table the position of the first idOrigen that we found in fp 
			fprintf(hashTable,"%i,%i\n",num,fila);
			// Mark that idOrigen as check
			Revisados[num]=true;
		}
		// Increment the number of files
		fila++;
  	}
  	// Close the fp file
	fclose(fp);

/*
If you want to know what idOrigen are not in fp use this
int a=1;
for(int i=1;i<1161;i++){
bool esta=false;
	rewind(funcionhash);
	while (feof(funcionhash)!=true)
	{
		fgets(row, MAXCHAR,funcionhash);
		token=strtok(row, ",");
		int num=atoi(token);
		if(num==i){
			esta=true;
		}
	}
if(!esta){
	printf("el numero %d en no estar es %i\n",a,i);
	a++;
}

}
*/
    return 0;
}


