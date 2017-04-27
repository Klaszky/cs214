#include "libnetfiles.h"

static const int portNum = 42942;

int netopen(char * path)
{
	struct sockaddr_in serverAddressInfo;
	struct hostent *serverIPAddress = gethostbyname("grep.cs.rutgers.edu");

	char sendBuffer[256];
	
	if(serverIPAddress == NULL)
	{
		fprintf(stderr, "Can't find host\n");
		return -1;
	}
	
	int socketFD;
	int n;
	int toReturn;
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socketFD < 0)
	{
		fprintf(stderr, "Couldn't make a socket.\n");
		return -1;
	}

	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_port = htons(portNum);

	bcopy((char *) serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);

	if(connect(socketFD, (struct sockaddr *)&serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		fprintf(stderr, "Couldn't connect to socket.\n");
		return -1;
	}

	bzero(sendBuffer, 256);
	// fgets(sendBuffer, 255, stdin);
	///////////////////////////////////////////////////////////
	sprintf(sendBuffer, "open,%s,", path);
	//////////////////////////////////////////////////////////
	
	n = write(socketFD, sendBuffer, strlen(sendBuffer));

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	bzero(sendBuffer,256);

	n = read(socketFD, sendBuffer, 255);


	if(n < 0)
	{
		fprintf(stderr, "Couldn't read from socket.\n");
		return -1;
	}

	printf("%s\n", sendBuffer);
	// toReturn = atoi(sendBuffer);
	return 1;
}