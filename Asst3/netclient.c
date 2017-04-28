#include "libnetfiles.h"

int main()
{
	networkserverinit("grep.cs.rutgers.edu");
	printf("%d\n", netopen("./test", O_RDONLY));
	// printf("%d\n", netclose(-5));
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
