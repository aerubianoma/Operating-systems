#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "intnode.h"


#define HASH_SIZE 1160
#define CVS_SIZE 1014
#define MAXCHAR 1000

int main(){
    char row_s[MAXCHAR];
	char *token;
    char *token2;
    long fila = 2;
    FILE *fp_raw = fopen("FuncionHash.csv","r");
    FILE *fp = fopen("tablaHash.bin", "wb+");

    
    node *table; //no olvidar el free() al final
    table = malloc(sizeof(node)*HASH_SIZE);

    rewind(fp_raw);

    for(int i = 0; i < CVS_SIZE; i++){
        fgets(row_s, MAXCHAR,fp_raw);
	    token = strtok(row_s, ",");
	    int key = atoi(token);
        table[key-1].key = key;
	    token2 = strtok(NULL,",");
        int first = atoi(token2);
	    table[key-1].first = first; 
    }

    for (int i = 0; i < HASH_SIZE ; i++)
    {
        printf("i: %d ,id: %d, first: %d\n", i, table[i].key, table[i].first);
    }
    //printf();
    
    fclose(fp_raw);

    rewind(fp);
    fwrite(table, sizeof(node), HASH_SIZE, fp);

    fclose(fp);

    free(table);
}
