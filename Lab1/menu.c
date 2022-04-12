#include <stdio.h>
#include <stdlib.h>


int menu() {
	int entrada;
	printf("1. Ingresar Origen \n");
	printf("2. Ingresar destino \n");
	printf("3. Ingresar hora \n");
	printf("4. Buscar tiempo de viaje medio \n");
	printf("5. salir \n");
	scanf("%d", &entrada);
return entrada;
}

int main() {
	printf("Bienvenido \n");
	int a=menu();
	int IDorig=0,IDFinal=0,Hora=24;
	while(a!=5){
		switch(a){
			case 1:
				while(1>IDorig || IDorig>1160){
				printf("Ingrese el origen\n");
				scanf("%d",&IDorig);
				}
				a=menu();
			break;
			case 2:
				while(1>IDFinal || IDFinal>1160){
				printf("Ingrese el final\n");
				scanf("%d",&IDFinal);
				}
				a=menu();
			break;
			case 3:
				while(0>Hora || Hora>23){
				printf("Ingrese la hora\n");
				scanf("%d",&Hora);
				}
				a=menu();
			break;
			case 4:
				printf("Buscará el tiempo \n");
				a=menu();
			break;
			case 5:
				printf("Salió \n");
			break;
			default:
				printf("Seleccione una opciòn vàlida\n");
				a=menu();
			break;
		}
	}
return 0;
}
