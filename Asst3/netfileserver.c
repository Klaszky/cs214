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
	int socketFD = -1;
	int newSocketFD = -1;
	int client = -1;
	int n = -1;
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
///////////////////////////////////////////////////////////////
		// printf("%d\n", strlen(buffer));
		if(strlen(buffer) > 4 && strncmp("open", buffer, 4) == 0)
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
	nLink * head = NULL;
	head = argPull(buffer, head);
	printf("%s\n", head->arg);
	head = head->next;
	printf("%s\n", head->arg);
	int returnFD = open(head->arg, O_RDONLY);
	printf("%d\n", errno);
	return returnFD;
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
	nLink * temp;
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

				// endingPos = i;

				// tempString = pullString(startingPos, endingPos, sizeOfString, inputString);
				// tempNode = createNode(tempString);

				// tempLink = createLinkNode(currentFile);

				// head = addToTree(head, tempNode, tempLink);
				// free(tempString);
				// startingPos = -1;
				// sizeOfString = 0;
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