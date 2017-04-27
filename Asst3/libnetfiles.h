#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct nLink
{
	char * arg;
	struct nLink * next;
}nLink;

int intLen(int x);
char * pullString(int start, int end, int size, char * originalString);
nLink * createLink(char * arg);
nLink * addToLL(nLink * head, nLink * newnLink);
nLink * argPull(char * buffer, nLink * head);
void destroyList(nLink * head);
int networkserverinit(char * hostname);
char * nopen(char * buffer);
int netopen(char * path, int mode);
int nclose(char * fd);
int netclose(int fd);