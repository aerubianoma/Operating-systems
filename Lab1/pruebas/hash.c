#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define TABLE_SIZE 5904703
#define MAXCHAR 1000

typedef struct row{
    int idOrgn;
    int idDest;
    int hour;
    float time;
    long next;

} row;


//Funcion hash: mapea el id de origen a una posicion en la tabla
unsigned int hashFunct(int origin){
    return origin*origin % TABLE_SIZE;  
}


//Inicializa una tabla vacia //next values en -1
row * init_hash_table(int table_size){
    row *hash_table;
    hash_table = malloc(table_size*sizeof(row));
    for(int i= 0; i< table_size; i++){
        hash_table[i].next = -1;
    }
    return hash_table;
}

/*


void print_table(){
    for(int i = 0; i< TABLE_SIZE ; i++){
        if(hash_table[i] == NULL){
            printf("\t%i\t----\n", i);
        }else{
            printf("\t%i\t", i);
            row *tmp = hash_table[i];
            while (tmp != NULL)
            {
                printf("%d, %d, %d - ", tmp->idOrgn, tmp->idDest, tmp->time);
                tmp = tmp->next;
            }
            printf("\n");
        } 
    }
}

//ultiliza la funcion hash para insertar un elemento en la tabla, las colisiones se resuelven por chaining
bool hash_insert(row *r){
    if(r == NULL) return false;
    int index = hashFunct(r->idOrgn);
    r->next = hash_table[index];
    hash_table[index] = r;
    return true;    
}

//busca uun elemento en la posicion que le da la funcion hash, si no lo encuentra ahi, recorre la lista
row *hash_search(int origen){
    int index = hashFunct(origen);
    row *tmp = hash_table[index];
    while (tmp != NULL && tmp->idOrgn != origen){ //itera en la lista enlazada, si no encuentra el elemento, retorna un puntero null
        tmp = tmp->next; 
    }
    return tmp;
    
}

*/

void parenting(FILE *fp){
    row *tmp; 
    tmp = malloc(TABLE_SIZE*sizeof(row));
    bool vis[1160];

    rewind(fp);
    fread(tmp, sizeof(row), TABLE_SIZE, fp);

    for(int i = TABLE_SIZE-1; i >= 0; i--){
        row cmp = tmp[i];
        if(vis[cmp.idOrgn-1] != true){
            int next = i;
            for (int j = i-1; j >= 0; j--){
            
                if (tmp[j].idOrgn == cmp.idOrgn && tmp[j].next != next){
                    tmp[j].next = sizeof(row)*next;
                    next = j;
                }      
            }
            vis[cmp.idOrgn-1] = true;
        }
        
        printf("%d\n", i);  
    }
    rewind(fp);
    fwrite(tmp, sizeof(row),TABLE_SIZE, fp);
    free(tmp);
}

int main(){

    char row_s[MAXCHAR];
	char *token;
    long fila = 2;
    FILE *fp_raw = fopen("bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");
    FILE *fp = fopen("bogotaTimes.bin", "wb+");

    
    row *table; 
    table = init_hash_table(TABLE_SIZE); //no olvidar el free() al final

    rewind(fp_raw);
    fgets(row_s, MAXCHAR,fp_raw);
    for(int i = 0; i< TABLE_SIZE; i++){
        fgets(row_s, MAXCHAR,fp_raw);
	    token = strtok(row_s, ",");
	    table[i].idOrgn = atoi(token);
	    token = strtok(NULL,",");
	    table[i].idDest = atoi(token);
        token = strtok(NULL, ",");
        table[i].hour = atoi(token);
        token = strtok(NULL, ",");
        table[i].time = atof(token); 
    }

    fclose(fp_raw);

    
    fwrite(table, sizeof(row), TABLE_SIZE, fp);
    rewind(fp);
    parenting(fp);

    fseek(fp, sizeof(row), SEEK_SET);
    row r2;
    fread(&r2, sizeof(row), 1, fp);

    row r = table[1];
    printf("row: 0 orgn: %d, dest: %d, hora: %d, time: %f, next: %li\n", r.idOrgn, r.idDest, r.hour, r.time, r.next);
    printf("row2: 0 orgn: %d, dest: %d, hora: %d, time: %f, next: %li\n", r2.idOrgn, r2.idDest, r2.hour, r2.time, r2.next);

    fclose(fp);

    
    	
    /*--------quitar

    row ggg = {.idOrgn= 23, .idDest = 32, .hour = 5, .time = 22.3, .next = NULL};
    row ggg2 = {.idOrgn= 7, .idDest = 32, .hour = 5, .time = 22.3, .next = NULL};

    row ggg3 = {.idOrgn= 78, .idDest = 32, .hour = 5, .time = 22.3, .next = NULL};
    hash_insert(&ggg);
    hash_insert(&ggg2);
    hash_insert(&ggg3);
    print_table();

    row *pr = hash_search(78);
    if (pr == NULL){
        printf("Not found");
    }else{
        printf("found!!! %d\n", 78);
    }

*/
    free(table);
    return 0;
}