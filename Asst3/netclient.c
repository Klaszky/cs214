#include "libnetfiles.h"

int main()
{	
	int fd = open("./oz", atoi("O_RDONLY"));
	printf("%d\n", fd);
	// printf("%d\n", netclose(fd));
	// printf("%d\n", netopen("./test", O_RDONLY));
	// printf("%d\n", netopen("./test2", O_RDONLY));
	// printf("%d\n", netopen("./testing", O_RDONLY));

	return 0;
}
