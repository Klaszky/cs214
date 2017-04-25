#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libnetfiles.h"

int main(int argc, char *argv[])
{
	int socketFD;
	int newSocketFD;
	int portNum;
	int client;
	int n;
	char buffer[256];

	struct sockaddr_in serverAddressInfo;
	struct sockaddr_in clientAddressInfo;

	if(argc < 2)
	{
		printf("won't number of cmd line args\n");
		return -1;
	}

	portNum = atoi(argv[1]);
	socketFD = socket(AF_INET, SOCK_STREAM, 0);

	if(socketFD < 0)
	{
		printf("Can't open FD\n");
		return -1;
	}

	// clean out buffer
	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	//what the hell is htons? is it changing the int to a network int?
	serverAddressInfo.sin_port = htons(portNum);

	// not sure what this does.
	serverAddressInfo.sin_family = AF_INET;

	// not sure what this does.
	serverAddressInfo.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketFD, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		printf("can't bind socket\n");
		return -1;
	}


	while(1)
	{
		listen(socketFD, 5);

		client = sizeof(clientAddressInfo);
		newSocketFD = accept(socketFD, (struct sockaddr *) &clientAddressInfo, &client);

		if(newSocketFD < 0)
		{
			printf("coudln't accept connection\n");
		}

		bzero(buffer, 256);
		n = read(newSocketFD, buffer, 255);

		if(n < 0)
		{
			printf("couldn't read from socket\n");
			return -1;
		}
///////////////////////////////////////////////////////////////
		// printf("%d\n", strlen(buffer));
		if(strlen(buffer) > 4 && strncmp("open", buffer, 4) == 1)
		{
			int FD = nopen(buffer);
			int fdLen = intLen(FD);
			char * writeString = (char*)malloc(fdLen+1);
			sprintf(writeString,"%d",FD);
			n = write(newSocketFD, writeString, strlen(writeString));
		}

///////////////////////////////////////////////////////////////

		else
		{
			printf("Message: %s\n", buffer);

			n = write(newSocketFD, "Message recieved", 18);

			if(n < 0)
			{
				printf("couldn't write out to new socket\n");
				return -1;
			}
		}
	}


	return 0;
}

int nopen(char * buffer)
{
	char * path = pullString(4, strlen(buffer), strlen(buffer)-4, buffer);
	int returnFD = open(path, O_RDONLY);
	return returnFD;
}

char * pullString(int start, int end, int size, char * originalString)
{
	int x, y;
	char * toReturn = (char*)calloc(size + 1, sizeof(char));
	for(x = 0, y = start; y < end; x++, y++)
	{
		toReturn[x] = originalString[y];
	}

	return toReturn;
}

int intLen(int x)
{	
	int toReturn = 0;
	while(x > 0)
	{
		toReturn++;
		x /= 10;
	}

	return toReturn;
}