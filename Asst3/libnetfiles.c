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

int netopen(char * path, int mode)
{	
	// Set up for our message to send to server
	/////////////////////////////////
	char sendBuffer[256];
	int socketFD = getSockFD();
	int n;
	
	nLink * head;
	int err;
	int fd;

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

	// head = argPull(sendBuffer, head);

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

int netclose(int fd)
{
	// Set up for our message to send to server
	/////////////////////////////////
	char sendBuffer[256];
	int socketFD = getSockFD();
	int n;
	int result;

	// Constuction of message to be sent. It'll need to be changed a bit
	///////////////////////////////////
	bzero(sendBuffer, 256);
	sprintf(sendBuffer, "close,%d,", fd);

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

	result = atoi(sendBuffer);
	return result;
}

ssize_t netread(int fd, void *buf, size_t nbyte)
{
	char sendBuffer[256];
	int socketFD = getSockFD();
	int n;
	int bytesRead;
	nLink * head;
	sprintf(sendBuffer, "read,%d,%d,", fd, nbyte);

	n = write(socketFD, sendBuffer, strlen(sendBuffer));

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

	return 1;
}
ssize_t netwrite(int fd, const void *buf, size_t nbyte)
{
	return 1;
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

nLink * createLink(char * arg)
{
	nLink * temp = (nLink*)malloc(sizeof(nLink));
	temp->arg = strdup(arg);
	temp->next = NULL;
	return temp;
}

nLink * addToLL(nLink * head, nLink * newnLink)
{
	// Hit the end of the list, simply add the node
	/////////////////
	if(head == NULL)
	{
		head = newnLink;
		return head;
	}

	else
	{
		head->next = addToLL(head->next, newnLink);
		return head;
	}
}

nLink * argPull(char * buffer, nLink * head)
{
	char * tempString;
	nLink * tempnLink;
	int startingPos = -1, endingPos = 0, sizeOfString = 0, len = 0, i = 0;
	len = strlen(buffer);

	for(i = 0; i <= len; i++)
	{
		// Check if current character isalpha and then
		// makes some decisions based on that.
		///////////////////
		if(buffer[i] == ',' || buffer[i] == '\0')
		{
			// Nothing to do if current string is empty 
			///////////////////
			if(sizeOfString == 0)
			{
				continue;
			}
			// Grabs the current string from input and puts it into the tree.
			///////////////////
			else
			{
				endingPos = i;
				tempString = pullString(startingPos, endingPos, sizeOfString, buffer);
				tempnLink = createLink(tempString);
				head = addToLL(head, tempnLink);
				free(tempString);
				startingPos = -1;
				sizeOfString = 0;	
			}
		}
		// Book keeping for current string.
		///////////////////
		else
		{
			if(startingPos == -1)
			{
				startingPos = i;
				sizeOfString++;
			}
			else
			{
				sizeOfString++;

			}
		}
	}

	return head;
}

char * pullString(int start, int end, int size, char * originalString)
{
	int x, y;
	char * temp = (char*)calloc(size + 1, sizeof(char));
	for(x = 0, y = start; y < end; x++, y++)
	{
		temp[x] = originalString[y];
	}

	return temp;
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

void destroyList(nLink * head)
{
	if(head == NULL)
	{
		return;
	}
	else
	{
		destroyList(head->next);
		free(head);
	}
}