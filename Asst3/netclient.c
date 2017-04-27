#include "libnetfiles.h"

int main()
{
	networkserverinit("grep.cs.rutgers.edu");
	int testFD = netopen("./test", O_RDONLY);
	printf("%d\n", testFD);
	printf("%d\n", netclose(testFD));
	printf("%d\n", netopen("./test", O_RDONLY));
	printf("%d\n", netopen("./test2", O_RDONLY));
	printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
