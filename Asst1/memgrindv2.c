#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "mymalloc.h"

int main(int argc, char * argv[])
{
	//Used for all parts
	int successCoutner = 0;
	int failCounter = 0;
	int i = 0;

	//Part A
	char * partA[1000];

	for(i = 0; i < 1000; i++)
	{
		partA[i] = (char*)malloc(sizeof(char));
		if(partA[i] != NULL)
		{
			successCoutner++;
		}
		else
		{
			failCounter++;
		}
	}

	for(i = 0; i < successCoutner; i++)
	{
		free(partA[i]);
	}

	printf("\n\nPart A:\n");
	printf("Successes: %d\nFailures: %d\n", successCoutner, failCounter);

	//Part B
	char * partB;
	successCoutner = 0;
	failCounter = 0;

	for(i = 0; i < 1000; i++)
	{
		partB = (char*)malloc(sizeof(char*));
		if(partB != NULL)
		{
			successCoutner++;
		}
		else
		{
			failCounter++;
		}

		free(partB);
	}

	printf("\n\nPart B:\n");
	printf("Successes: %d\nFailures: %d\n", successCoutner, failCounter);

	//Part C

	// char * partC[1000];
	i = 0;
	successCoutner = 0;
	failCounter = 0;
	return 0;
}
