#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

typedef struct nLink
{
	char * arg;
	struct nLink * next;
}nLink;

// int open(const char *pathname, int flags);
int nopen(char * buffer);
int intLen(int x);
char * pullString(int start, int end, int size, char * originalString);
nLink * createLink(char * arg);
nLink * addToLL(nLink * head, nLink * newnLink);
nLink * argPull(char * buffer, nLink * head);