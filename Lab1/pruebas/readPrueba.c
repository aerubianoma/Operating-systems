#include <stdio.h>
#include <stdlib.h>
#include "intnode.h"

int main(){

    FILE *fp = fopen("tablaHash.bin", "rb+");

    rewind(fp);
    node n;
    fseek(fp, sizeof(node) * 0, SEEK_SET);
    fread(&n, sizeof(node), 1, fp);
    printf("key: %d, first: %d\n", n.key, n.first);
    
    fclose(fp);
/*
    FILE *fp2 = fopen("arreglo.bin", "rb+");
    node n;
    fread(&n, sizeof(node), 1, fp2);
    printf("key: %d, next: %li\n", n.key, n.next);
    fclose(fp2);
*/
}
