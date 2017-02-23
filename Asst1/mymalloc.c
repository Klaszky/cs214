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
		return 0;
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
					//display();
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
					newBlock->previous = iterationPointer;
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
					return (void *)(iterationPointer + sizeof(metaData));

				}
			}
		}

		else
		{
			iterationPointer = iterationPointer->next;
		}
	}
	
	fprintf(stderr, "Not enough memory to allocate %d bytes.\nFile: %s, Line %d\n", size, file, line);
	return 0;
}

void myfree(void *memoryPtr, char * file, int line)
{
	if(memoryPtr == NULL)
	{
		fprintf(stderr, "Tried to free 'NULL.'\nFile: %s, Line %d\n", file, line);
	}
	// Takes the pointer you were given and attempts to make it point to the
	// metaData
	////////////////////
	metaData * ptr = memoryPtr - 16*sizeof(metaData);

	if(ptr->isFree)
	{
		fprintf(stderr, "Already Free.\nFile: %s, Line %d\n", file, line);
		return;
	}

	//  Part of a check to see if the pointer that was given, is something 
	// that our malloc program had alloc'd. Work in progress at the moment.
	////////////////////
	// if(valid(ptr))
	// {
	// 	printf("It is valid\n");
	// }
	// else
	// {
	// 	printf("not valid\n");
	// 	return;
	// }

	// If the pointer is pointing to metaData and it isn't already free
	// set the variable to free then attempts to clean up memory next to it.
	////////////////////
	else
	{
		ptr->isFree = 1;

		// Keeps looking at memory after the current pointer until it hits
		// a block of memory that isn't free. Merges all the free ones together
		////////////////////
		while(ptr->next != NULL && ptr->next->isFree == 1 )
		{
			ptr->currentSize += (ptr->next->currentSize + sizeof(metaData));
			ptr->next = ptr->next->next;
			if(ptr->next != NULL)
			{
				ptr->next->previous = ptr;
			}
		}
		// Keeps looking at memory before the current pointer until it hits
		// a block of memory that isn't free. Merges all the free ones together
		////////////////////
		while(ptr->previous != NULL && ptr->previous->isFree == 1 )
		{
			ptr->previous->currentSize += (ptr->currentSize + sizeof(metaData));
			ptr->previous->next = ptr->next;
			ptr = ptr->previous;
		}
	}
	//for testing...
	//display();
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

int valid(metaData * ptr)
{
	metaData * iterptr = head;
	while(iterptr != NULL)
	{
		if(iterptr == ptr)
		{
			return 1;
		}

		iterptr = iterptr->next;	
	}

	return 0;
}