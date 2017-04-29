#include "libnetfiles.h"

int main()
{
	char * fileContents = (char*)malloc((sizeof(char) * 5000) + 1);
	
	char * readTest = (char*)malloc(sizeof(char) * 50);
	
	int btr = 20;
	int amtToRead = 5000;
	int status;
	int fd;
	
	printf("%d\n", networkserverinit("grep.cs.rutgers.edu"));
	fd = netopen("./oz", O_RDONLY);
	printf("%d\n", fd);
	status = netread(fd, fileContents, btr);
	while(amtToRead > 0)
	{
		status = read(fd, fileContents, amtToRead);
		amtToRead -= status;
	}
	printf("%s\n", fileContents);
	printf("%d\n", status);
	printf("%d\n", netclose(fd));
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
