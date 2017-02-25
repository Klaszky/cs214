#include "mymalloc.h"

static char myblock[BLOCKSIZE];
metaData *head = (void*)myblock;

// Just makes the frist block and sets some values
////////////////////
void createFirstBlock()
{
	head->currentSize = BLOCKSIZE - sizeof(metaData);
	head->next = NULL;
	head->isFree = 1;
}


void *mymalloc(size_t size, char * file, int line)
{

	// These two pointers are used to iterate over our linked list
	// of metaData and to help make the next link respectively.
	////////////////////
	metaData *iterationPointer = NULL;
	metaData *newBlock = NULL;

	// If the user enters malloc(0) it'll tell them that this doesn't
	// work
	////////////////////
	if(size == 0)
	{
		// I'll change the error messages sooner or later....
		fprintf(stderr, "User requested 0 bytes.\nFile: %s, Line %d\n", file, line);
		return NULL;
	}

	// If head hasn't been used set up yet, create it.
	////////////////////
	if(head->currentSize == 0)
	{
		createFirstBlock();
	}

	// This is the pointer that will be used in the while loop
	////////////////////
	iterationPointer = head;

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
					//for testing ...
					display();
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
					newBlock->isFree = 1;
					newBlock->currentSize = iterationPointer->currentSize - sizeof(metaData) - size;

					if(iterationPointer->next == NULL)
					{
						newBlock->next = NULL;
					}
					else
					{
						newBlock->next = iterationPointer->next;
					}
					// Updates to block of memory that will be returned
					////////////////////
					iterationPointer->currentSize = size;
					iterationPointer->next = newBlock;
					iterationPointer->isFree = 0;

					// Return where the pointer is + a bit so we don't
					// write over the metaData
					////////////////////
					//for testing
					//display();
					return (void *)((void*)iterationPointer + sizeof(metaData));

				}
			}
		}

		else
		{
			iterationPointer = iterationPointer->next;
		}
	}
	
	fprintf(stderr, "Not enough memory to allocate %d bytes.\nFile: %s, Line %d\n", size, file, line);
	return NULL;
}

void myfree(void *memoryPtr, char * file, int line)
{
	if(memoryPtr == NULL)
	{
		fprintf(stderr, "Tried to free 'NULL.'\nFile: %s, Line %d\n", file, line);
		return;
	}
	// Takes the pointer you were given and attempts to make it point to the
	// metaData
	////////////////////
	metaData * ptr = memoryPtr - sizeof(metaData);

	//  Part of a check to see if the pointer that was given, is something 
	// that our malloc program had alloc'd. Work in progress at the moment.
	////////////////////
	if(!withinBounds(ptr))
	{
		fprintf(stderr, "Not a pointer allocted by a malloc call.\nFile: %s, Line %d\n", file, line);
		return;
	}
	if(ptr->isFree)
	{
		fprintf(stderr, "Already Free.\nFile: %s, Line %d\n", file, line);
		return;
	}


	// If the pointer is pointing to metaData and it isn't already free
	// set the variable to free then attempts to clean up memory next to it.
	////////////////////
	else
	{
		ptr->isFree = 1;
		merge();
	}
	//for testing...
	display();
}

//for testing....
void display()
{
	metaData * iterptr = head;
	while(iterptr != NULL)
	{
		printf("size: %d\n", iterptr->currentSize);
		printf("isFree: %d\n", iterptr->isFree);
		if(iterptr->next == NULL)
		{
			printf("end of memory\n\n");
		}

		iterptr = iterptr->next;

	}
}

//FIX ~ maybe compare addresses
//////////////////

// int valid(metaData * ptr)
// {
// 	metaData * iterptr = head;
// 	while(iterptr != NULL)
// 	{
// 		if(iterptr == ptr)
// 		{
// 			return 1;
// 		}

// 		iterptr = iterptr->next;	
// 	}

// 	return 0;
// }

int withinBounds(void * ptr)
{
	return (void*)ptr >= (void*)myblock && (void*)ptr < (void*)myblock + BLOCKSIZE;
}

void merge()
{
	metaData * ptr = head;
	while(ptr != NULL)
	{
		while(ptr->isFree && ptr->next != NULL && ptr->next->isFree)
		{
			ptr->currentSize += ptr->next->currentSize + sizeof(metaData);
			ptr->next = ptr->next->next;
		}
		ptr = ptr->next;
	}
}
