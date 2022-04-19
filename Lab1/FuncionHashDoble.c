#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<stdbool.h>

#define MAXCHAR 1000

int main(){

    	FILE *fp;
	FILE *funcionhash;
   	char row[MAXCHAR];
	char *token;
	long fila=2;
	bool Revisados[1345600];

    	fp = fopen("bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");
	funcionhash=fopen("FuncionHashDoble.csv","w+");
	for(int j=0;j<1345600;j++){
		Revisados[j]=false;
	}
	rewind(fp);
	fgets(row, MAXCHAR, fp);
	while (feof(fp)!=true)
	{
		fgets(row, MAXCHAR,fp);
		token=strtok(row, ",");
		int IDOrigen=atoi(token);
		token=strtok(NULL,",");
		int IDDestino=atoi(token);
		int Suma=(IDOrigen-1)*1160+IDDestino;
		if(!Revisados[Suma]){
			fprintf(funcionhash,"%i,%i,%li\n",IDOrigen,IDDestino,fila);
			Revisados[Suma]=true;
		}
		fila++;
  	}
	fclose(fp);
    return 0;
}

