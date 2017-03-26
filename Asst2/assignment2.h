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

// Prototypes
//////////////////

void destroyList(fileList * fl);
void destroyTree(treeNode * head);
void finalOutput(treeNode * head, char * outputFileName);
void free(void * ptr);
void lowerCase(char * string, int size);
void printTree(treeNode * head);
void writeTree(treeNode * head, int fd);
void llSort(fileList * fl);
void swap(fileList * link1, fileList * link2);
void * calloc(size_t nmemb, size_t size);
void * malloc(size_t size);
int intLen(int x);
int strcasecmp(const char * s1, const char * s2);
int tolower(int c);
int fprintf(FILE * stream, const char * format, ...);
size_t strlen(const char *s);
off_t lseek(int fd, off_t offset, int whence);
char * extract(char * path);
char * fileFixer(char * file);
char * pathMake(char * currentPath, char * nextDir);
treeNode * fileIterator(char * name, treeNode * head);
treeNode * tokenize(char * fileContents, treeNode * head, char * currentFile);

char * opening = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<fileIndex>\n";
char * closing = "</fileIndex>";
char * wordOpen = "\t<word text=\"";
char * wordOpenMid = "\">\n";
char * wordClose = "\t</word>\n";
char * fileNameOpen = "\t\t<file name=\"";
char * fileNameMid = "\">";
char * fileNameClose = "</file>\n";