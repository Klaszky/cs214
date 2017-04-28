#include "libnetfiles.h"


int main()
{
	// Set up vars to use in our program
	//////////////////////////////////
	socklen_t client;
	int socketFD;
	int newSocketFD;
	int n;
	char buffer[256];
	int portNum = 42942;

	// Setting up our connection
	////////////////////////////////
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

	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
	serverAddressInfo.sin_port = htons(portNum);
	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketFD, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		printf("can't bind socket\n");
		return -1;
	}

	// End of connection set up
	////////////////////////////////

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
		// temp = temp->next;
		// char * path = temp->arg;
		// destroyList(head);
		if(strncmp("open", cmd, 4) == 0)
		{
			nopen(head, newSocketFD);
		}
		// else if(strncmp("read", cmd, 4) == 0)
		// {
		// 	return 0;
		// }
		// else if(strncmp("close", cmd, 5) == 0)
		// {
		// 	int result = nclose(path);
		// 	char * toWrite = malloc(sizeof(char) * intLen(result) + 1);
		// 	sprintf(toWrite, "%d", result);
		// 	n = write(newSocketFD, toWrite, strlen(toWrite) + 1);
		// 	free(cmd);
		// 	free(path);
		// 	free(toWrite);
		// }

		n = write(newSocketFD, "Didn't get it", 14);
	}

	
	return 0;
}

int nopen(nLink * head, int socketFD)
{
	// Var set up 
	//////////////////
	int msgSize;
	int err;
	int n;

	// Pulling out of arguments from linked list
	/////////////////
	nLink * tmp = head;
	tmp = tmp->next;

	char * path = tmp->arg;
	tmp = tmp->next;

	int mode = atoi(tmp->arg);
	
	// Actually opening the file and error check
	/////////////////
	int newFD = open(path, mode);
	if(newFD != -1)
	{
		newFD *= -1;
	}
	
	// Setting errno and getting my message ready to send
	////////////////
	err = errno;
	errno = 0;
	msgSize = intLen(err) + intLen(newFD);

	char * message = malloc(sizeof(char) * msgSize + 1);
	sprintf(message, "%d,%d,", err, newFD);
	
	// Writing new socket and error check
	////////////////
	n = write(socketFD, message, strlen(message));
	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	free(message);
	destroyList(head);
	return 0;
}

int nclose(nLink * head)
{
	destroyList(head);
	// int returnVal;
	// int intFD = atoi(fd);
	// intFD *= -1;
	// returnVal = close(intFD);
	// return returnVal;
	return -1;
}

char * nread(char * fd, char * size)
{
	int intFD = atoi(fd);
	int intSize = atoi(size);
	int status;
	char * buffer = malloc(sizeof(char) * intSize + 1);
	status = read(intFD, buffer, intSize);
	char * message = malloc(sizeof(char) * (strlen(buffer) + intLen(status)) );
	sprintf(message, "%d,%s,", status, buffer);
	free(buffer);
	return message;

}