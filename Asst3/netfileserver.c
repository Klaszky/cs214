#include "libnetfiles.h"

pthread_mutex_t writeMutex;
pthread_mutex_t readMutex;

int main()
{
	// Set up vars to use in our program
	//////////////////////////////////
	socklen_t client;
	int socketFD;
	int * newSocketFD = malloc(sizeof(int));
	int portNum = 42942;
	pthread_t netpthread;

	// Setting up our connection
	////////////////////////////////
	struct sockaddr_in serverAddressInfo;
	struct sockaddr_in clientAddressInfo;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
	{
	    fprintf(stderr, "setsockopt(SO_REUSEADDR) failed");
	}

	if(socketFD < 0)
	{
		fprintf(stderr, "Can't open FD\n");
		return -1;
	}

	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
	serverAddressInfo.sin_port = htons(portNum);
	serverAddressInfo.sin_family = AF_INET;
	serverAddressInfo.sin_addr.s_addr = INADDR_ANY;

	if(bind(socketFD, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		fprintf(stderr, "Can't bind socket\n");
		return -1;
	}

	// End of connection set up
	////////////////////////////////

	while(1)
	{
		listen(socketFD, 5);

		client = sizeof(clientAddressInfo);
		*newSocketFD = accept(socketFD, (struct sockaddr *) &clientAddressInfo, &client);

		if(*newSocketFD < 0)
		{
			fprintf(stderr, "Coudln't accept connection\n");
		}

		pthread_create(&netpthread, NULL, (void*)threadMain, newSocketFD);
		pthread_detach(netpthread);


	}
	
	return 0;
}

void * threadMain(int * args)
{
	int n;
	int newSocketFD = (int)*args;
	char buffer[256];
	bzero(buffer, 256);
	n = read(newSocketFD, buffer, 255);

	if(n < 0)
	{
		fprintf(stderr, "Couldn't read from socket\n");
		pthread_exit(NULL);
	}

	nLink * head = NULL;
	head = argPull(buffer, head);

	nLink * temp = head;
	char * cmd = temp->arg;

	if(strncmp("open", cmd, 4) == 0)
	{
		nopen(head, newSocketFD);
	}
	else if(strncmp("read", cmd, 4) == 0)
	{
		nread(head, newSocketFD);
	}
	else if(strncmp("close", cmd, 5) == 0)
	{
		nclose(head, newSocketFD);
	}
	else if(strncmp("write", cmd, 5) == 0)
	{
		destroyList(head);
		nwrite(buffer, newSocketFD);
	}

	n = write(newSocketFD, "Didn't get it", 14);

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);
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
	err = errno;
	errno = 0;
	if(newFD != -1)
	{
		newFD *= -1;
	}
	
	// Setting errno and getting my message ready to send
	////////////////
	msgSize = intLen(err) + intLen(newFD);

	char * message = (char*)malloc(sizeof(char) * msgSize + 1);
	sprintf(message, "%d,%d,", err, newFD);
	
	// Writing new socket and error check
	////////////////
	n = write(socketFD, message, strlen(message));

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	destroyList(head);
	return 0;
}


int nclose(nLink * head, int socketFD)
{
	// Var set up
	//////////////
	int n;
	int err;
	int result;
	int intFD = atoi(head->next->arg);
	
	// Change to local FD
	//////////////
	if(intFD != -1)
	{
		intFD *= -1;
	}
	
	// Actually closing and checking errno
	//////////////
	result = close(intFD);
	err = errno;
	errno = 0;
	
	char * message = (char*)malloc(sizeof(char) * (intLen(result) + intLen(err) + 1));
	sprintf(message, "%d,%d,", err, result);
	
	n = write(socketFD, message, strlen(message) + 1);

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	destroyList(head);
	return result;
}

int nread(nLink * head, int socketFD)
{
	// Var set up
	////////////////
	int n;
	int err;
	// Gettting proper FD
	////////////////	
	int intFD = atoi(head->next->arg);
	if(intFD != -1)
	{
		intFD *= -1;
	}

	// I know this is lazy, but it's getting late.
	/////////////////
	int intSize = atoi(head->next->next->arg);
	int status;
	// Reading the file
	/////////////////
	char * buffer = (char*)malloc( sizeof(char) * intSize + 1);
	pthread_mutex_lock(&readMutex);
	status = read(intFD, buffer, intSize);
	printf("%d\n", status);
	printf("%s\n", buffer);
	pthread_mutex_unlock(&readMutex);

	err = errno;
	errno = 0;
	if(status < 0)
	{
		fprintf(stderr, "Error reading from file\n");
		return -1;
	}

	char * message = (char*)malloc(sizeof(char) * (strlen(buffer) + intLen(status) + intLen(err) + 1) );
	sprintf(message, "%d,%d,%s,", err, status, buffer);
	

	n = write(socketFD, message, strlen(message) + 1);

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	destroyList(head);

	return 0;
}

int nwrite(char * buffer, int socketFD)
{
	// Var set up
	////////////////
	nLink * head = NULL;
	head = writePull(buffer, head);
	nLink * temp = head;
	temp = temp->next;
	int n;
	int err;
	int status;
	int intFD;
	int intSize;
	char * backupbuffer;



	// Gettting proper FD
	////////////////	
	intFD = atoi(temp->arg);
	if(intFD != -1)
	{
		intFD *= -1;
	}

	temp = temp->next;

	// I know this is lazy, but it's getting late.
	/////////////////
	intSize = atoi(temp->arg);
	temp = temp->next;
	buffer = temp->arg;
	
	if(intSize > 200)
	{
		backupbuffer = (char*)malloc(sizeof(char) * intSize + 1);
	}

	sprintf(backupbuffer, "%s", buffer);
	while(n > 0)
	{
		n = read(socketFD, backupbuffer, 255);
	}

	buffer = backupbuffer;
	// Reading the file
	/////////////////	
	pthread_mutex_lock(&writeMutex);
	status = write(intFD, buffer, intSize);
	pthread_mutex_unlock(&writeMutex);

	err = errno;
	errno = 0;

	if(status < 0)
	{
		fprintf(stderr, "Error writing to file\n");
		return -1;
	}

	char * message = (char*)malloc(sizeof(char) * intLen(status) + 1);
	sprintf(message, "%d,%d,%s,", err, status, buffer);
	

	n = write(socketFD, message, strlen(message) + 1);

	if(n < 0)
	{
		fprintf(stderr, "Couldn't write to socket.\n");
		return -1;
	}

	destroyList(head);

	return 0;
}