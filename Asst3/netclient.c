#include "libnetfiles.h"

int main()
{	
	char * readIn = (char*)malloc(sizeof(char) * 5000);
	size_t amtToRead = 5000;
	size_t status = 0;
	char * buf = "grep.cs.rutgers.edu\n";


	networkserverinit("grep.cs.rutgers.edu");
	
	// int fd = open("./oz", atoi("O_RDONLY"));
	// printf("%d\n", fd);
	// printf("%d\n", close(fd));
	int fd = netopen("./oz.txt", O_RDONLY);
	printf("%d\n", fd);

	status = netread(fd, readIn, (int)amtToRead);
	amtToRead -= status;
	printf("status: %d\n", status);
	printf("amtToRead: %d\n", (int)amtToRead);
	printf("\n\n\n\n\n\n");
	printf("%s\n", readIn);

	printf("%d\n", netclose(fd));
	int fd2 = netopen("./test", O_WRONLY);
	printf("fd2 %d\n", fd2);
	status = netwrite(fd2, buf, strlen(buf));
	printf("status 2: %d\n", status);
	printf("%d\n", netclose(fd2));
	// printf("%d\n", netopen("./test2", O_RDONLY));
	// printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
