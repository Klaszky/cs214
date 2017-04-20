#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int socketFD;
	int portNum;
	int n;
	char buffer[256];

	struct sockaddr_in serverAddressInfo;
	struct hostent *serverIPAddress;

	if(argc < 3)
	{
		printf("wrong number of args\n");
		return -1;
	}

	portNum = atoi(argv[2]);
	serverIPAddress = gethostbyname(argv[1]);
	if(serverIPAddress == NULL)
	{
		printf("can't find host\n");
		return -1;
	}

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD < 0)
	{
		printf("couldn't make a socket\n");
		return -1;
	}

	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_port = htons(portNum);

	bcopy((char *) serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);

	if(connect(socketFD, (struct sockaddr *)&serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		printf("couldn't connect \n");
		return -1;
	}

	printf("Eneter a msg: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);

	n = write(socketFD,buffer,strlen(buffer));

	if(n < 0)
	{
		printf("couldn't write to socket\n");
		return -1;
	}

	bzero(buffer,256);

	n = read(socketFD, buffer, 255);

	if(n < 0)
	{
		printf("Couldn't read from socket\n");
		return -1;
	}


	printf("%s\n",buffer);
}