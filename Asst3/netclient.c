#include "libnetfiles.h"

int main()
{	
	char * readIn = (char*)malloc(sizeof(char) * 210);
	int amtToRead = 200;
	int status = 0;

	networkserverinit("grep.cs.rutgers.edu");
	
	// int fd = open("./oz", atoi("O_RDONLY"));
	// printf("%d\n", fd);
	// printf("%d\n", close(fd));
	int fd = netopen("./oz", O_RDONLY);
	printf("%d\n", fd);

	status = netread(fd, readIn, amtToRead);
	printf("%d\n", status);
	printf("%d\n", amtToRead);
	printf("%s\n", readIn);

	printf("%d\n", netclose(fd));
	// printf("%d\n", netopen("./test", O_RDONLY));
	// printf("%d\n", netopen("./test2", O_RDONLY));
	// printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
