#include <stdio.h>
#include <stdlib.h>


int menu() {
	int entrada;
	printf("Bienvenido \n");
	printf("1. Ingresar Origen \n");
	printf("2. Ingresar destino \n");
	printf("3. Ingresar hora \n");
	printf("4. Buscar tiempo de viaje medio \n");
	printf("5. salir \n");
	scanf("%d", &entrada);
return entrada;
}

int main() {
	int a=menu();
	switch(a){
		case 1:
			printf("Ingresará el origen \n");
		break;
		case 2:
			printf("Ingresará el destino \n");
		break;
		case 3:
			printf("Ingresará la hora \n");
		break;
		case 4:
			printf("Buscará el tiempo \n");
		break;
		case 5:
			printf("Salió \n");
		break;
	}
return 0;
}
