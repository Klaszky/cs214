#include "libnetfiles.h"

int main()
{	
	char * readIn = (char*)malloc(sizeof(char) * 2000);
	int amtToRead = 2000;
	int status = 0;

	networkserverinit("grep.cs.rutgers.edu");
	
	// int fd = open("./oz", atoi("O_RDONLY"));
	// printf("%d\n", fd);
	// printf("%d\n", close(fd));
	int fd = netopen("./oz", O_RDONLY);
	printf("%d\n", fd);

	while(amtToRead > 0)
	{
		status = netread(fd, readIn, amtToRead);
		amtToRead -= status;
		printf("status: %d\n", status);
		printf("amtToRead: %d\n", amtToRead);
	}

	printf("%s\n", readIn);

	printf("%d\n", netclose(fd));
	// printf("%d\n", netopen("./test", O_RDONLY));
	// printf("%d\n", netopen("./test2", O_RDONLY));
	// printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
