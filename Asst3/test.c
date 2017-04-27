#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("./test", O_RDONLY);
	int idk = close(fd);
	printf("%d\n", idk);
}
