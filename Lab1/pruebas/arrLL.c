#include <stdio.h>
#include <stdlib.h>
#include "intnode.h"

int main(){
    
    FILE *fp = fopen("arreglo.bin","rb+");
    printf("Open: %li\n", ftell(fp));
	
    node c;

	fread(&c, sizeof(node), 1, fp);

    printf("Despues del read: %li\n", ftell(fp));

    int *next_key = &(c.next->key);
	printf("Key del nodo: %d\n", c.key);
    printf("Key del next nodo: %d\n", *next_key);
	
	
	//fread();//quiero probar si puedo leer el arreglo de nodos, sobretodo si puedo leer el puntero next para acceder al siguiente nodo (sin cargar el arreglo en memoria, leerlo desde el archivo)

	fclose(fp);

    /*

    printf("----------\n");

    FILE *fp2 = fopen("arreglo.bin", "rb+");

	fread(ptr2, sizeof(node), 1, fp2);
	printf("read: %li\n", ftell(fp2));
	

	
	printf("%d\n", (ptr2->next)->key);
	
	
	//fread();//quiero probar si puedo leer el arreglo de nodos, sobretodo si puedo leer el puntero next para acceder al siguiente nodo (sin cargar el arreglo en memoria, leerlo desde el archivo)

	fclose(fp2);

*/
    return 0;
}    