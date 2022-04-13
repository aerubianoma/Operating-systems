#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAXCHAR 1000

int main(){

    FILE *fp;
    char row[MAXCHAR];

    fp = fopen("bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");

    ;

    while (feof(fp) != true)
    {
        fgets(row, MAXCHAR, fp);
        printf("Row: %s", row);
    }

    return 0;
}
