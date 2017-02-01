// Includes and prototypes
///////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isalpha(int c);
int strcmp(const char * s1, const char * s2);
int strcasecmp(const char * s1, const char * s2);
void * malloc(size_t size);
void * calloc(size_t nmemb, size_t size);
void free(void * ptr);
char * strdup(const char * s);
size_t strlen(const char *s);



// Main struct for my Binary search tree
///////////////////
typedef struct treeNode
{
	struct treeNode * left;
	struct treeNode * right;
	int num;
	char * str;
}treeNode;

// This makes and returns a node with some
// default values and a supplied string
///////////////////
treeNode * createNode(char * newStr)
{
	treeNode * temp = (treeNode*)malloc(sizeof(treeNode));
	temp->left = NULL;
	temp->right = NULL;
	temp->num = 1;
	temp->str = strdup(newStr);
	return temp;
}

// Recursive - it's basically doing a search of the tree
// looking at each string and comparing then inserting
// if it doesn't find a copy of the string in new node
///////////////////
treeNode * addToTree(treeNode * head, treeNode *newNode)
{
	if(head == NULL)
	{
		head = newNode;
		return head;
	}
	// Okay, so this part is a bit redundant....
	// Because strcmp compares based on
	// ascii values I was having a tough time
	// getting it to sort properly. So now there
	// are two compares. One case sensitive, one not.
	////////////////////
	else if(strcasecmp(head->str, newNode->str) == 0)
	{
		if(strcmp(head->str, newNode->str) == 0)
		{
			head->num++;
			free(newNode);
			return head;
		}
		else if(strcmp(head->str, newNode->str) > 0)
		{
			if(head->left == NULL)
			{
				head->left = newNode;
			}
			else
			{
				head->left = addToTree(head->left, newNode);
			}

			return head;
		}
		else if(strcmp(head->str, newNode->str) < 0)
		{
			if(head->right == NULL)
			{
				head->right = newNode;	
			}
			else
			{
				head->right = addToTree(head->right, newNode);
			}

			return head;
		}

	}
	else if(strcasecmp(head->str, newNode->str) > 0)
	{
		if(head->left == NULL)
		{
			head->left = newNode;
		}
		else
		{
			head->left = addToTree(head->left, newNode);
		}

		return head;
	}
	else if(strcasecmp(head->str, newNode->str) < 0)
	{
		if(head->right == NULL)
		{
			head->right = newNode;	
		}
		else
		{
			head->right = addToTree(head->right, newNode);
		}

		return head;
	}
	return head;
}

// Recursive - This acts as my sort. 
///////////////////
void printTree(treeNode * head)
{
	if(head == NULL)
	{
		return;
	}
	int i;

	if(head->left != NULL)
	{
		printTree(head->left);
	}
	for(i = 0; i < head->num; i++)
	{
		printf("%s\n",head->str);
	}
	if(head->right != NULL)
	{
		printTree(head->right);
	}
}

// Attemps free up all of the alloc'd memory in my BST
///////////////////
void destroyTree(treeNode * head)
{
	if(head == NULL)
	{
		return;
	}

	if(head->left != NULL)
	{
		destroyTree(head->left);
	}
	if(head->right != NULL)
	{
		destroyTree(head->right);
	}

	free(head);
	return;
}

// Takes an input string, a size and some indices, 
// grabs the portion of the string contained in said 
// indices and returns a new, null terminated string.
///////////////////
char * pullString(int start, int end, int size, char * originalString)
{
	int x, y;
	char * temp = (char*)calloc(size + 1, sizeof(char));
	for(x = 0, y = start; y < end; x++, y++)
	{
		temp[x] = originalString[y];
	}

	return temp;
}

int main(int argc, char * argv[])
{

	// performing a test and grabbing the cmd line string
	///////////////////
	if(argc != 2)
	{
		printf("Insufficient number of command line arguments.\n");
		return 0;
	}

	// Setting up some variables that will be used.
	// Most should be self explanatory.
	///////////////////
	char * inputString = argv[1];
	char * tempString;

	int startingPos = -1, endingPos = 0, sizeOfString = 0, len = 0, i = 0;
	len = strlen(inputString);

	treeNode * head = NULL;
	treeNode * tempNode;

	// Main loop of the program, goes over every
	// character of the input.
	///////////////////
	for(i = 0; i <= len; i++)
	{
		// Check if current character isalpha and then
		// makes some decisions based on that.
		///////////////////
		if(isalpha(inputString[i]) == 0)
		{
			// Nothing to do if current string is empty 
			///////////////////
			if(sizeOfString == 0)
			{
				continue;
			}
			// Grabs the current string from input and puts it into the tree.
			///////////////////
			else
			{
				endingPos = i;
				tempString = pullString(startingPos, endingPos, sizeOfString, inputString);
				tempNode = createNode(tempString);
				head = addToTree(head, tempNode);
				free(tempString);
				startingPos = -1;
				sizeOfString = 0;	
			}
		}
		// Book keeping for current string.
		///////////////////
		else
		{
			if(startingPos == -1)
			{
				startingPos = i;
				sizeOfString++;
			}
			else
			{
				sizeOfString++;

			}
		}
	}

	printTree(head);
	destroyTree(head);
	
	return 0;
}
