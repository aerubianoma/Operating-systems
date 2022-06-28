#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

// Menu of the app, insert correct data for a search!
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

	printf("Bienvenido! \n");

	// Menu variable
	int a=menu();
	// Variables for the input of the search
	int IDorig=0,IDFinal=0,Hora=24;
	// Variable to send the inputs of the search to the server
	int msg[3];
	// Variable that receive the output of the search
	char buffer[1024];
	
	// Run the menu
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
				printf("Datos enviados \n");
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

	// Variables necessary to initiate the client
	int clientSocket, ret;
	struct sockaddr_in serverAddr;

	// We create the socket for the client
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Check error in socket creation
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	// Struct necessary to connect the client with the server
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	// Connect the client with the server
	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	// Check error in connection
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	
	// We send the inputs of the search to the server	
	send(clientSocket, msg, sizeof(msg), 0);

	// Check error in the message that the server is sending to us (the output of the search)
	if(recv(clientSocket, buffer, 1024, 0) < 0){
		printf("[-]Error in receiving data.\n");
	}else{
		printf("Server: \t%s\n", buffer);
	}
	

	return 0;
}
