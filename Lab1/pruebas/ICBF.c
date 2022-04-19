#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intnode.h"

#define LIST_SIZE 9


void parenting(FILE *fp){
    node *tmp; 
    tmp = malloc(LIST_SIZE*sizeof(node));
    bool vis[9];
    for(int i= 0; i<9 ; i++){
        vis[i] = false;
    }

    rewind(fp);
    fread(tmp, sizeof(node), LIST_SIZE, fp);

    for(int i = LIST_SIZE-1; i >= 0; i--){
        node cmp = tmp[i];
        if(vis[cmp.key-1] != true){
             int next = i;
            for (int j = i-1; j >= 0; j--){
               //
                if (tmp[j].key == cmp.key && tmp[j].next != next){
                    tmp[j].next = sizeof(node)*next;
                    next = j;
                    printf("i: %d, j: %d, next: %d\n", i, j, next);
                }   
            }
            vis[cmp.key-1] = true;
        }  
    }
    rewind(fp);
    fwrite(tmp, sizeof(node), LIST_SIZE, fp);
    for(int i = 0; i< LIST_SIZE; i++){
        printf("%li: _______\n", (long)i*sizeof(node));
        printf("Key: %d, next: %li\n", tmp[i].key, tmp[i].next);
    }
    free(tmp);
    for(int i = 0; i< 9; i++){
        printf("%d\n", vis[i]);
    }
}

void print_same_key(node n, FILE *fp){
    node tmp = n;
    bool flag = true;
    while(flag){
        printf("%d\n", tmp.key);
        if(tmp.next == -1){
            flag = false;
            break;
        }
        fseek(fp, tmp.next, SEEK_SET);
        fread(&tmp, sizeof(node), 1, fp);
    }
    
}


int main(){

    FILE *fp = fopen("arreglo.bin","rb+");
    printf("Open: %li\n", ftell(fp));
	
    /*
    node c;
    int list_size = 0;

    for(int i = 0; i< list_size; i++){
        fread(&c, sizeof(node), 1, fp);

    }
	*/ 

    parenting(fp);
    fseek(fp, 32, SEEK_SET);
    node ggg;
    fread(&ggg, sizeof(node), 1, fp);
    printf("Despues del parenting: %li\n", ftell(fp));
    printf("%d\n", ggg.key);
    printf("Lista de list[0]: ");
    print_same_key(ggg, fp);
/*
    printf("Despues del read: %li\n", ftell(fp));
	printf("Key del nodo: %d\n", c.key);
    printf("Key del next nodo: %d\n", *next_key);
*/	
	
	//fread();//quiero probar si puedo leer el arreglo de nodos, sobretodo si puedo leer el puntero next para acceder al siguiente nodo (sin cargar el arreglo en memoria, leerlo desde el archivo)

	fclose(fp);
}