#include <stdio.h>
#include <stdlib.h>
#include "intnode.h"

int main(){

	/*
	typedef struct node{
		int key;
		struct node *next;
	}node;
	*/

	node a = {.key = 1, .next = -1};
	node b = {.key = 2, .next = -1};
	node d = {.key = 2, .next = -1};
	node e = {.key = 1, .next = -1};
	node f = {.key = 3, .next = -1};
	node g = {.key = 2, .next = -1};
	node h = {.key = 9, .next = -1};
	node i = {.key = 3, .next = -1};
	node j = {.key = 1, .next = -1};
	
	
	node list[9] = {a, b, d, e, f, g, h, i, j};

	

	FILE *fp = fopen("arreglo.bin","rb+");
	printf("open: %li\n", ftell(fp));
	
	fwrite(list, sizeof(node), 9, fp);
	printf("write: %li\n", ftell(fp));
	
	rewind(fp);
	printf("rewind: %li\n", ftell(fp));
	
	fclose(fp);

	FILE *fp2 = fopen("arreglo.bin", "rb+");
	node c;
	

	fread(&c, sizeof(node), 1, fp2);
	printf("read: %li\n", ftell(fp2));
	

	printf("%d\n", list[0].key);
	printf("%d, %li\n", c.key, c.next);
	
	
	//fread();//quiero probar si puedo leer el arreglo de nodos, sobretodo si puedo leer el puntero next para acceder al siguiente nodo (sin cargar el arreglo en memoria, leerlo desde el archivo)

	fclose(fp2);





/*
	int arr[5];
	int a = 0;
	int *ptr = &a;

	FILE *fp = fopen("arreglo.txt","rb");
	printf("antes: %li\n", ftell(fp));
	fread(arr, sizeof(int), 4, fp);
	printf("despues: %li\n", ftell(fp));
	rewind(fp);
	printf("rewind: %li\n", ftell(fp));
	fseek(fp, sizeof(int)*1, SEEK_SET);
	printf("seek: %li\n", ftell(fp));
	fread(ptr, sizeof(int), 1, fp);
	printf("El numero leido: %d", a);
/*
	for(int i = 0; i<5; i++){
		printf("%d", arr[i]);
	}

*/	
//	fclose(fp);

	

	return 0;
}
