#include "libnetfiles.h"


int main()
{
	socklen_t client;
	int socketFD;
	int newSocketFD;
	int n;
	char buffer[256];
	int portNum = 42942;

	struct sockaddr_in serverAddressInfo;
	struct sockaddr_in clientAddressInfo;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
	{
	    printf("setsockopt(SO_REUSEADDR) failed");
	}

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

		nLink * head = NULL;
		head = argPull(buffer, head);
		nLink * temp = head;
		char * cmd = temp->arg;
		temp = temp->next;
		char * path = temp->arg;
		destroyList(head);
		if(strncmp("open", cmd, 4) == 0)
		{
			char * toWrite = nopen(path);
			n = write(newSocketFD, toWrite, strlen(toWrite) + 1);
			free(cmd);
			free(path);
			free(toWrite);
		}
		else if(strncmp("close", cmd, 5) == 0)
		{
			int result = nclose(path);
			char * toWrite = malloc(sizeof(char) * intLen(result) + 1);
			sprintf(toWrite, "%d", result);
			n = write(newSocketFD, toWrite, strlen(toWrite) + 1);
			free(cmd);
			free(path);
			free(toWrite);
		}

		n = write(newSocketFD, "Didn't get it", 14);
	}

	
	return 0;
}

char * nopen(char * path)
{
	int size;
	int err;
	int newFD = open(path, 0x0000);
	if(newFD != -1)
	{
		newFD *= -1;
	}
	err = errno;
	size = intLen(err) + intLen(newFD);
	char * returnStr = malloc(sizeof(char) * size + 1);
	sprintf(returnStr, "%d,%d,", err, newFD);
	return returnStr;
}

int nclose(char * fd)
{
	int returnVal;
	int intfd = atoi(fd);
	intfd *= -1;
	printf("%d\n", intfd);
	returnVal = close(intfd);
	return returnVal;
}

