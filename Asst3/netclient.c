#include "libnetfiles.h"

int main()
{
	char * fileContents = (char*)malloc((sizeof(char) * 3000) + 1);
	
	int amtToRead = 3000;
	int amtToWrite = 3000;
	int status;
	int fd;
	
	printf("%d\n", networkserverinit("grep.cs.rutgers.edu"));
	fd = netopen("./oz", O_RDONLY);
	printf("%d\n", fd);

	// while(amtToRead > 0)
// 	{
	status = netread(fd, fileContents, amtToRead);
	printf("status: %d\n", status);
	printf("amtToRead: %d\n", amtToRead);
	amtToRead = amtToRead - status;
	printf("amtToRead: %d\n", amtToRead);
	// }

	int fd2 = open("./test", O_WRONLY);
	printf("%s\n",fileContents);


	// while(amtToWrite > 0)
	// {
		status = write(fd2, fileContents, amtToWrite);
		printf("status: %d", status);
	// 	amtToWrite -= status;
	// }


	// printf("%s\n", fileContents);
	// printf("%d\n", status);
	printf("%d\n", netclose(fd));
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
