#include <stdio.h>
#include <stdlib.h>


int menu() {
	int entrada=0;
	printf("______________________________________ \n");
	printf("1. Ingresar origen \n");
	printf("2. Ingresar destino \n");
	printf("3. Ingresar hora \n");
	printf("4. Buscar tiempo de viaje medio \n");
	printf("5. salir \n");
	printf("______________________________________ \n");
	scanf("%d", &entrada);
return entrada;
}

int main() {
	printf("Bienvenido! \n");
	int a=menu();
	int IDorig=0,IDFinal=0,Hora=24;
	FILE *fp=fopen("searchData.csv","w+");
	while(a!=5){
		switch(a){
			case 1:
				while(1>IDorig || IDorig>1160){
				printf("______________________________________ \n");
				printf("Ingrese el idOrigen:\n");
				scanf("%d",&IDorig);
				printf("______________________________________ \n");
				}
				a=menu();
			break;
			case 2:
				while(1>IDFinal || IDFinal>1160){
				printf("______________________________________ \n");
				printf("Ingrese el idDestino:\n");
				scanf("%d",&IDFinal);
				printf("______________________________________ \n");
				}
				a=menu();
			break;
			case 3:
				while(0>Hora || Hora>23){
				printf("______________________________________ \n");
				printf("Ingrese la hora:\n");
				scanf("%d",&Hora);
				printf("______________________________________ \n");
				}
				a=menu();
			break;
			case 4:
				printf("______________________________________ \n");
				printf("Archivo con datos generado! \n");
				fprintf(fp,"%d,%d,%d\n",IDorig,IDFinal,Hora);
				printf("______________________________________ \n");
				a=5;
			break;
			case 5:
				printf("______________________________________ \n");
				printf("Salio! \n");
				printf("______________________________________ \n");
			break;
			default:
				printf("______________________________________ \n");
				printf("Seleccione una opcion valida!\n");
				printf("______________________________________ \n");
				a=menu();
			break;
		}
	}
return 0;
}
