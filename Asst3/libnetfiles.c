#include "libnetfiles.h"

static const int portNum = 42942;

int conn()
{
	// All connection and setup stuff
	/////////////////////////////////
	struct sockaddr_in serverAddressInfo;
	struct hostent *serverIPAddress = gethostbyname("grep.cs.rutgers.edu");

	int socketFD;

	if(serverIPAddress == NULL)
	{
		fprintf(stderr, "Can't find host\n");
		return -1;
	}
	
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

	return socketFD;

	// End of connection and setup stuff
	/////////////////////////////////////
	
}

int netopen(char * path, int mode)
{	
	char sendBuffer[256];
	int socketFD = conn();
	int n;
	int toReturn;

	bzero(sendBuffer, 256);
	sprintf(sendBuffer, "open,%s,%d,", path, mode);

	
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