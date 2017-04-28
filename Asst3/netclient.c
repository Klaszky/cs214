#include "libnetfiles.h"

int main()
{
	char * readTest = malloc(sizeof(char) * 50);
	int btr = 20;
	int status;
	int fd;
	printf("%d\n", networkserverinit("grep.cs.rutgers.edu"));
	fd = netopen("./test", O_RDONLY);
	printf("%d\n", fd);
	status = netread(fd, readTest, btr);
	printf("%s\n", readTest);
	printf("%d\n", status);
	printf("%d\n", netclose(fd));
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
