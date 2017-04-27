#include "libnetfiles.h"

static const int portNum = 42942;

struct sockaddr_in serverAddressInfo;
struct hostent *serverIPAddress;

int networkserverinit(char * hostname)
{
	serverIPAddress = gethostbyname(hostname);
	
	if(serverIPAddress == NULL)
	{
		fprintf(stderr, "Can't find host\n");
		return -1;
	}

	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_port = htons(portNum);

	bcopy((char *) serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);

	return 0;

}

int getSockFD()
{
	// All connection and setup stuff
	/////////////////////////////////

	int socketFD;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socketFD < 0)
	{
		fprintf(stderr, "Couldn't make a socket.\n");
		return -1;
	}

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
	int socketFD = getSockFD();
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