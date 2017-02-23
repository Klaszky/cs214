#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
	// test2 = (int*)malloc(400);
	// test3 = (int*)malloc(50);
	// test2 = (int*)malloc(400);
	// free(test);
	// free(test2);
	// int *test, *test2, *test3;
	// test = (int*)malloc(4500);
	// free(test);
	// test = (int*)malloc(100);
	// test2 = (int*)malloc(400);
	// free(test);
	// free(test2);
	int i;
	int counter = 0;
	int * test;
	int * test2;
	int * test3;
	int x;

	//free(test);
	// free(&x);

	test = (int*)malloc(sizeof(int));
	test2 = (int*)malloc(sizeof(int));
	test3 = (int*)malloc(8*sizeof(int));

	free(test2);
	free(test);

	test = (int*)malloc(sizeof(int));
	//free(test+30);
	test2 = (int*)malloc(20*sizeof(int));

	free(test);
	free(test2);
	free(test3);

	test = (int*)malloc(sizeof(int));
	test2 = (int*)malloc(sizeof(int));
	test3 = (int*)malloc(8*sizeof(int));

	free(test2);
	free(test3);

	test2 = (int*)malloc(45*sizeof(int));
	test3 = (int*)malloc(8*sizeof(int));

	free(test2);
	free(test);
	free(test3);

	// test = (int*)malloc(4500);
	// test2 = (int*)malloc(400);
	// test3 = (int*)malloc(50);
	// free(test);
	// free(test2);
	// for(i = 0; i < 5000; i++)
	// {
	// 	test = (int*)malloc(sizeof(int));
	// 	test2 = (int*)malloc(sizeof(int));
	// 	test3 = (int*)malloc(8*sizeof(int));
	// 	if(test != 0)
	// 	{
	// 		counter++;
	// 		// free(test);
	// 	}
	// 	if(test2 != 0)
	// 	{
	// 		counter++;
	// 	}
	// 	if(test3 != 0)
	// 	{
	// 		counter++;
	// 		free(test3);
	// 	}
	// 		free(test);
	// 		free(test2);

	// }
	// printf("%d\n", counter);

	// return 0;
}
