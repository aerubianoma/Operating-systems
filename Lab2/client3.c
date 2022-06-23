#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

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

int main(){
	float *time;
	printf("Bienvenido! \n");
	int a=menu();
	int IDorig=0,IDFinal=0,Hora=24;
	int msg[3];
	
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
				msg[0] = IDorig;
				msg[1] = IDFinal;
				msg[2] = Hora;
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

	int clientSocket, ret;
	struct sockaddr_in serverAddr;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	
		
		send(clientSocket, msg, sizeof(msg), 0);


		if(recv(clientSocket, time, sizeof(time), 0) < -1){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: %f\n", *time);
		}
	

	return 0;
}
