#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int open(const char *pathname, int flags);
int nopen(char * buffer);
int intLen(int x);
char * pullString(int start, int end, int size, char * originalString);