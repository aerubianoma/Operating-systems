#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
 
#define PORT 8080

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE];
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

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

int main(int argc, char *argv[]){
	

	printf("Bienvenido! \n");
	int a=menu();
	int IDorig=0,IDFinal=0,Hora=24;
	FILE *fp=fopen("searchData.txt","w+");
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
  fclose(fp);
  int clientSocket, ret;
	struct sockaddr_in serverAddr;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	printf("%d\n",clientSocket);
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
	printf("%d\n",clientSocket);
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		fp = fopen("searchData.txt", "r"); 
  	if (fp == NULL) {
    	perror("[-]Error in reading file.");
    	exit(1);
  	}
 
  	send_file(fp, clientSocket);
  	printf("[+]File data sent successfully.\n");
  	printf("[+]Closing the connection.\n");
  	close(clientSocket);
  	fclose(fp);
}
	return 0;
}