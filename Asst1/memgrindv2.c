#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "mymalloc.h"

int coinFlip();

int main(int argc, char * argv[])
{
	//Used for all parts
	int successCoutner = 0;
	int failCounter = 0;
	int totalCoutner = 0;
	int i = 0, j = 0;

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

	// //Part B
	char * partB;
	successCoutner = 0;
	failCounter = 0;

	for(i = 0; i < 1000; i++)
	{
		partB = (char*)malloc(sizeof(char));
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
	// i = 0;
	// successCoutner = 0;
	// failCounter = 0;

	// while(successCoutner < 1000)
	// {
	// 	if(i == 0)
	// 	{
	// 		partC[i] = (char*)malloc(sizeof(char));
	// 		i++;
	// 		successCoutner++;
	// 	}
	// 	else
	// 	{
	// 		if( coinFlip() )
	// 		{	
	// 			partC[i] = (char*)malloc(sizeof(char));
	// 			if(partC[i] == NULL)
	// 			{
	// 				i--;
	// 				free(partC[i]);
	// 			}
	// 			else
	// 			{
	// 				successCoutner++;
	// 				i++;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if(i >= 0)
	// 			{
	// 				free(partC[i]);
	// 				i--;
	// 			}
	// 		}
	// 	}
	// 	totalCoutner++;
	// 	printf("\n\n%d\n\n", successCoutner);
	// }

	// for(j = 0; j <= i; j++)
	// {
	// 	free(partC[j]);
	// }

	// printf("Total iterations: %d\n", totalCoutner);


	return 0;
}

int coinFlip()
{
	srand(time(NULL));
	int toReturn = rand();
	if(toReturn % 2 == 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
