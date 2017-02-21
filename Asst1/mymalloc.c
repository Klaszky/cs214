#include "mymalloc.h"

static char myblock[BLOCKSIZE];

metaData *head = NULL;
metaData *iterationPointer = NULL;
metaData *nextBlock = NULL;


void *mymalloc(size_t size, char * file, int line)
{
	printf("1");

	if(size == 0)
	{
		printf("Fail");
		return 0;
	}

	printf("2");



	printf("3");
	if(head == NULL)
	{
		head = (metaData *) myblock;
		head->previous = NULL;
		head->next = NULL;
		head->currentSize = BLOCKSIZE - sizeof(metaData);
		head->isFree = 1;
		//put head into the array
		//set head->previous = null
		//set head size = to total size - sife of metaData
		//set isFree to true

	}

	printf("4");
	iterationPointer = head;



	printf("5");
	while(iterationPointer != NULL);
	{
		if(iterationPointer->isFree)
		{
			if(iterationPointer->currentSize < size)
			{
				iterationPointer = iterationPointer->next;
			}
			else
			{
				if(iterationPointer->currentSize < (size + sizeof(metaData) ))
				{
					iterationPointer->isFree = 0;
					return iterationPointer + sizeof(metaData);
				}
				else
				{
					iterationPointer->isFree = 0;

					if(iterationPointer->next == NULL)
					{
						nextBlock = (metaData*)(iterationPointer + sizeof(metaData) + size);
						nextBlock->next = NULL;
						nextBlock->previous = iterationPointer;
						nextBlock->isFree = 1;
					}

					printf("not Fail");
					return iterationPointer + sizeof(metaData);

				}
				//set isFree to false;
				//create a new link in the metaData list and put it right after the blocks to be returned to the user
				//return iteration pointer
			}
		}
		else
		{
			iterationPointer = iterationPointer->next;
		}
	}

	printf("Fail");
	return 0;
}

// void myfree(void *blockPtr)
// {
// 	if(blockPtr->isFree)
// 	{
// 		//print error saying its already free
// 	}

// 	else
// 	{
// 		blockPtr->isFree = 1;
// 		metaData * prevPtr = blockPtr;
// 		metaData * nextPtr = blockPtr;
// 		while(prevPtr->previous != NULL && prevPtr->previous->isFree == 1 )
// 		{
// 			//merge
// 			prevPtr->previous->currentSize += (prevPtr->currentSize + sizeof(metaData));
// 			prevPtr = prevPtr->previous;
// 		}
// 		while(nextPtr->previous != NULL && nextPtr->previous->isFree == 1 )
// 		{
// 			//merge
// 			nextPtr->next->currentSize += (nextPtr-> + sizeof(metaData));
// 			nextPtr = nextPtr->next;
// 		}
// 	}
// }