#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
	// test2 = (char*)malloc(400);
	// test3 = (char*)malloc(50);
	// test2 = (char*)malloc(400);
	// free(test);
	// free(test2);
	// int *test, *test2, *test3;
	// test = (char*)malloc(4500);
	// free(test);
	// test = (char*)malloc(100);
	// test2 = (char*)malloc(400);
	// free(test);
	// free(test2);
	int i;


	// int x;
	int counter = 0;
	char * test;
	char * test2;
	char * test3;
	// int * test4[1000];

	// for(i = 0; i < 1000; i++)
	// {
	// 	test4[i] = (int*)malloc(sizeof(int));
	// 	counter++;
	// }
	// for(i = 0; i < counter; i++)
	// {
	// 	free(test4[i]);
	// }

	//free(test);
	// free(&x);

	// test = (char*)malloc(sizeof(char));
	// test2 = (char*)malloc(sizeof(int));
	// test3 = (char*)malloc(8*sizeof(int));

	// free(test);

	// free(test2);
	// free(test);

	// test = (char*)malloc(sizeof(int));
	// //free(test+30);
	// test2 = (char*)malloc(20*sizeof(int));

	// free(test);
	// free(test2);
	// free(test3);

	// test = (char*)malloc(sizeof(int));
	// test2 = (char*)malloc(sizeof(int));
	// test3 = (char*)malloc(8*sizeof(int));

	// free(test2);
	// free(test3);

	// test2 = (char*)malloc(45*sizeof(int));
	// test3 = (char*)malloc(8*sizeof(int));

	// free(test2);
	// free(test);
	// free(test3);

	test = (char*)malloc(4500);
	test2 = (char*)malloc(400);
	test3 = (char*)malloc(50);
	free(test);
	free(test2);
	for(i = 0; i < 5000; i++)
	{
		test = (char*)malloc(sizeof(char));
		test2 = (char*)malloc(sizeof(int));
		test3 = (char*)malloc(8*sizeof(int));
		if(test != 0)
		{
			counter++;
			free(test);
		}
		if(test2 != 0)
		{
			counter++;
		}
		if(test3 != 0)
		{
			counter++;
			// free(test3);
		}
			free(test);
			free(test2);

	}
	printf("%d\n", counter);

	return 0;
}
