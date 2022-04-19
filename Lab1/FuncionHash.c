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
	int fila=2;
	bool Revisados[1160];

    	fp = fopen("bogota-cadastral-2020-1-All-HourlyAggregate.csv","r");
	funcionhash=fopen("FuncionHash.csv","w+");
	for(int j=0;j<1160;j++){
		Revisados[j]=false;
	}
	rewind(fp);
	fgets(row, MAXCHAR, fp);
	while (feof(fp)!=true)
	{
		fgets(row, MAXCHAR,fp);
		token=strtok(row, ",");
		int num=atoi(token);
		if(!Revisados[num]){
			fprintf(funcionhash,"%i,%i\n",num,fila);
			Revisados[num]=true;
		}
		fila++;
  	}
	fclose(fp);
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
    return 0;
}

