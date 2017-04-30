#include "libnetfiles.h"

int main()
{	
	char * readIn = (char*)malloc(sizeof(char) * 3500);
	int amtToRead = 3500;
	int status = 0;
	char * buf = "I don't know what to type blah, blah blah";


	networkserverinit("grep.cs.rutgers.edu");
	
	// int fd = open("./oz", atoi("O_RDONLY"));
	// printf("%d\n", fd);
	// printf("%d\n", close(fd));
	int fd = netopen("./oz.txt", O_RDONLY);
	printf("%d\n", fd);

	status = netread(fd, readIn, amtToRead);
	amtToRead -= status;
	printf("status: %d\n", status);
	printf("amtToRead: %d\n", amtToRead);
	// printf("%s\n", readIn);

	printf("%d\n", netclose(fd));
	// int fd2 = netopen("./test", O_WRONLY);
	// status = netwrite(fd2, buf, strlen(buf));
	// printf("status 2: %d\n", status);
	// printf("%d\n", netopen("./test2", O_RDONLY));
	// printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
