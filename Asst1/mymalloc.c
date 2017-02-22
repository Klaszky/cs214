#include "mymalloc.h"

static char myblock[BLOCKSIZE];
metaData *head = (void*)myblock;

// Just makes the frist block and sets some values
////////////////////
void createFirstBlock()
{
	head->currentSize = BLOCKSIZE - sizeof(metaData);
	head->next = NULL;
	head->previous = NULL;
	head->isFree = 1;
}

void *mymalloc(size_t size, char * file, int line)
{

	// These two pointers are used to iterate over our linked list and 
	// to help make the next link.
	////////////////////
	metaData *iterationPointer = NULL;
	metaData *newBlock = NULL;

	// If the user enters malloc(0) it'll tell them that this doesn't
	// work
	////////////////////
	if(size == 0)
	{
		// I'll change the error messages sooner or later....
		printf("Fail - Requested 0 Memory\n");
		return 0;
	}

	// If head hasn't been used set up yet, create it/
	////////////////////
	if(head->currentSize == 0)
	{
		createFirstBlock();
	}

	// This is the pointer that will be used in the while loop
	////////////////////
	iterationPointer = (void*)head;

	while(iterationPointer != NULL)
	{
		// First check if this block is free
		////////////////////
		if(iterationPointer->isFree)
		{
			// If yes, check size of block vs size requested
			////////////////////
			if(iterationPointer->currentSize < size)
			{
				// If too small, move on
				////////////////////
				iterationPointer = iterationPointer->next;
			}
			else
			{
				// If large enough, see if there is enough space
				// for what is requested + another chunk of metaData
				////////////////////
				if(iterationPointer->currentSize < (size + sizeof(metaData) ))
				{
					// If there is room for whats requested, but not enough
					// for more metaData simply return this block of memory
					////////////////////
					iterationPointer->isFree = 0;
					iterationPointer->currentSize = size;
					printf("Success\n");
					return (void *)(iterationPointer + sizeof(metaData));
				}

				// It is large enough and we can make a new metaData
				// chunk.
				////////////////////
				else
				{

					// Create a new metaData block and put it right after current
					////////////////////
					newBlock = (void*)((void*)iterationPointer + sizeof(metaData) + size);
					newBlock->next = NULL;
					newBlock->previous = iterationPointer;
					newBlock->isFree = 1;
					newBlock->currentSize = iterationPointer->currentSize - sizeof(metaData) - size;

					// Updates to block of memory that will be returned
					////////////////////
					iterationPointer->currentSize = size;
					iterationPointer->next = newBlock;
					iterationPointer->isFree = 0;

					// Return where the pointer is + a bit so we don't
					// write over the metaData
					////////////////////
					printf("Success\n");
					return (void *)(iterationPointer + sizeof(metaData));

				}
			}
		}

		else
		{
			iterationPointer = iterationPointer->next;
		}
	}

	printf("Fail - Not enough Space\n");
	return 0;
}

void myfree(void *memoryPtr, char * file, int line)
{
	metaData * ptr = memoryPtr - sizeof(metaData);
	if(ptr->isFree)
	{
		printf("Already free");
		return;
	}

	else
	{
		ptr->isFree = 1;
		// while(ptr->previous != NULL && ptr->previous->isFree == 1 )
		// {
		// 	printf("4\n");
		// 	//merge
		// 	ptr->previous->currentSize += (ptr->currentSize + sizeof(metaData));
		// 	printf("5\n");
		// 	ptr->previous->next = ptr->next;
		// 	printf("6\n");
		// 	ptr = ptr->previous;
		// 	printf("7\n");
		// }
		// while(ptr->next != NULL && ptr->next->isFree == 1 )
		// {
		// 	printf("8\n");
		// 	//merge
		// 	ptr->next->currentSize += (ptr->currentSize + sizeof(metaData));
		// 	printf("9\n");
		// 	ptr->next->previous = ptr->previous;
		// 	printf("10\n");
		// 	ptr = ptr->next;
		// 	printf("11\n");
		// }
	}
}