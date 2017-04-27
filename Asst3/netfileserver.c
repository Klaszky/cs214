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