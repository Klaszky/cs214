#include "libnetfiles.h"

static const int portNum = 42942;

struct sockaddr_in serverAddressInfo;
const struct hostent *serverIPAddress;

int networkserverinit(char * hostname)
{
	// All connection and setup stuff
	/////////////////////////////////
	serverIPAddress = gethostbyname(hostname);
	
	// Error check to see if the host exsists. I'll have to set h_errno at some point
	/////////////////////////////////
	if(serverIPAddress == NULL)
	{
		fprintf(stderr, "Can't find host\n");
		return -1;
	}


	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_port = htons(portNum);

	bcopy((char *) serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);

	// All good return 0 to say it worked.
	///////////////////////////////////
	return 0;

	// End of connection and setup stuff
	/////////////////////////////////////
	
}

int getSockFD()
{
	// Socket set up
	///////////////////////////////////
	int socketFD;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	// Error check for creating socket
	///////////////////////////////////
	if(socketFD < 0)
	{
		fprintf(stderr, "Couldn't make a socket.\n");
		return -1;
	}

	// Error check for connection
	//////////////////////////////////
	if(connect(socketFD, (struct sockaddr *)&serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		fprintf(stderr, "Couldn't connect to socket.\n");
		return -1;
	}

	return socketFD;
}

int netopen(char * path, int mode)
{	
	// Set up for our message to send to server
	/////////////////////////////////
	char sendBuffer[256];
	int socketFD = getSockFD();
	int n;
	// int toReturn;

	// Constuction of message to be sent. It'll need to be changed a bit
	///////////////////////////////////
	bzero(sendBuffer, 256);
	sprintf(sendBuffer, "open,%s,%d,", path, mode);

	// Send message
	///////////////////////////////////
	n = write(socketFD, sendBuffer, strlen(sendBuffer));

	// Error check
	//////////////////////////////////
	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	// Read from return socket
	////////////////////////////////
	bzero(sendBuffer,256);
	n = read(socketFD, sendBuffer, 255);

	// Error check of return socket
	////////////////////////////////
	if(n < 0)
	{
		fprintf(stderr, "Couldn't read from socket.\n");
		return -1;
	}

	// At this point we'll need to do another arg pull. Once args are pulled
	// we'll need to set errno and out return value. Current print statement and
	// return value is just for testing.
	////////////////////////////////
	printf("%s\n", sendBuffer);
	// toReturn = atoi(sendBuffer);
	return 1;
}