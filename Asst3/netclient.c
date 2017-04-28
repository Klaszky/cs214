#include "libnetfiles.h"

int main()
{
	int fd;
	printf("%d\n", networkserverinit("grep.cs.rutgers.edu"));
	fd = netopen("./test", O_RDONLY)
	printf("%d\n", fd);
	printf("%d\n", netclose(fd);
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
