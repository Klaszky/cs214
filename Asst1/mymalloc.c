#include "mymalloc.c"

typedef struct metaData
{
	struct metaData *next, *previous;
	int isFree;
	int size;
}metaData;

void *mymalloc(size_t size)
{
	metaData *head;
	metaData *pToHead;
	metaData *next;

	if(head = NULL)
	{
		//put head into the array
		//set head->previous = null
		//set head size = to total size - sife of metadata
		//set isFree to true
	}

	iterationPointer = head;

	while(/*have no fallen off the end of the array*/)
	{
		if(/*iterationPointer->isFree*/)
		{
			if(/*iterationPointer->size < size*/)
			{
				iterationPointer = iterationPointer->next;
			}
			else
			{
				//set isFree to false;
				//create a new link in the metaData list and put it right after the blocks to be returned to the user
				//return iteration pointer
			}
		}
	}
}

void myfree(~~~)
{
	
}