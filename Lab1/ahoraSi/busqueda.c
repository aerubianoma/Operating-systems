#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include "intnode.h"

#define HASH_SIZE 1160

int id_first(int key, FILE *fp){  //devuelve la posicion del primer elemento con id = key
    rewind(fp);
    node n;
    fseek(fp, sizeof(node)*key, SEEK_SET);
    fread(&n, sizeof(node), 1, fp);
    if(n.key == 0){
        return -1;
    }
    return n.first;  

}

float busqueda(int idO, int idD, int hora, FILE *times, FILE *hash){
    rewind(hash);
    fseek(hash, sizeof(node)*(idO-1), SEEK_SET);
    node index;
    fread(&index, sizeof(node), 1, hash);
    row r;
    printf("key: %d, first: %d\n", index.key, index.first);
    rewind(times);
    fseek(times, (index.first-2)*sizeof(row), SEEK_SET);
    bool end_of_list = false;
    while(!end_of_list){
        fread(&r,sizeof(row), 1, times);
       // printf("orgn: %d, dest: %d, hora: %d\n", r.idOrgn, r.idDest, r.hour);
        if(r.idDest == idD && r.hour == hora){
           
           //printf("idO: %d, idD %d, time: %f", r.idOrgn, r.idDest, r.time);
            //printf("dest: %d, hora: %d, time: %f\n", r.idDest, r.hour, r.time);
            return r.time;
            
        }
        if (r.next == -1){
            end_of_list = true;
        }
        fseek(times, r.next, SEEK_SET);
    }
    //printf("origen: %d, destino: %d, hora: %d\n", r.idDest, r.hour);
    return -1;
}


int main(){

    FILE *times = fopen("bogotaTimes.bin", "rb+");
    FILE *hash = fopen("tablaHash.bin", "rb+");

    int idO = 731;
    int idD = 229;
    int hora = 18;

    node r;

    fseek(hash, sizeof(node)*(idO-1), SEEK_SET);
    fread(&r, sizeof(node), 1, hash);

    printf("pos %d\n", r.first);

    float time = busqueda(idO, idD, hora, times, hash);
    if(time == -1){
        printf("NA\n");
    }else{
        printf("%f\n", time);
    }
    int n;
    scanf("%d: ", &n);

    fclose(times);
    fclose(hash);
}
