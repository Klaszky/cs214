#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h> // open man page
#include <dirent.h> // open man page
#include <sys/stat.h> // https://linux.die.net/man/3/stat get file status
#include <limits.h> // http://pubs.opengroup.org/onlinepubs/009695399/basedefs/limits.h.html
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Main struct for my Binary search tree
///////////////////
typedef struct treeNode
{
	struct treeNode * left;
	struct treeNode * right;
	struct fileList * files;
	char * str;
}treeNode;

typedef struct fileList
{
	int counter;
	char * fileName;
	struct fileList * next;
}fileList;

int strcasecmp(const char * s1, const char * s2);
void free(void * ptr);
void * malloc(size_t size);
void * calloc(size_t nmemb, size_t size);
size_t strlen(const char *s);
int tolower(int c);
void lowerCase(char * string, int size);
off_t lseek(int fd, off_t offset, int whence);
char * extract(char * path);
void printTree(treeNode * head);
treeNode * tokenize(char * fileContents, treeNode * head, char * currentFile);
void destroyTree(treeNode * head);
treeNode * fileIterator(char * name, treeNode * head);
char * pathMake(char * currentPath, char * nextDir);
void destroyList(fileList * fl);
char * fileFixer(char * file);