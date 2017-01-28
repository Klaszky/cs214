// Includes and prototypes
///////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isalpha(int c);

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
// default values and a user supplied string
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
// Change to make: does a case insensitive search then a sensitive one
// to make things appear where they should
///////////////////
treeNode * addToTree(treeNode * head, treeNode *newNode)
{
	if(head == NULL)
	{
		head = newNode;
		return head;
	}
	else if(strcmp(head->str, newNode->str) == 0)
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
	else
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

// Recursive - This acts as my sort as well. 
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

// At temps free up all of the alloc'd memory in my BST
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

// Takes an input string, a size and some indices, grabs the portion of the string
// contained in said indices and returns a new, null terminated string.
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
	// if(argc != 2)
	// {
	// 	printf("Insufficient number of command line arguments."):
	// 	return 0;
	// }

	
	treeNode * head = NULL;

	// some test code
	///////////////////

	// treeNode * test = createNode("Joseph");
	// treeNode * test2 = createNode("Joseph");
	// head = addToTree(head, test);
	// head = addToTree(head, test2);
	// printf("\n%s\n\n", head->str);
	// printf("%d\n", head->num);
	// printf("\n%s\n\n", head->left->str);
	// printf("%d\n", head->left->num);
	
	
	int startingPos = -1, endingPos = 0, counter = 0, len = 0, i = 0;
	char * test1 = "i am joe and i know what i know so, just you lame Lame lAme laMe lamE";
	len = strlen(test1);
	char * tempString;
	treeNode * tempNode;

	for(i = 0; i <= len; i++)
	{
		if(isalpha(test1[i]) == 0)
		{
			if(counter == 0)
			{
				continue;
			}
			else
			{
				endingPos = i;
				tempString = pullString(startingPos, endingPos, counter, test1);
				tempNode = createNode(tempString);
				head = addToTree(head, tempNode);
				free(tempString);
				// free(tempNode);
				startingPos = -1;
				counter = 0;	
			}
		}
		else
		{
			if(startingPos == -1)
			{
				startingPos = i;
				counter++;
			}
			else
			{
				counter++;

			}
		}
	}

	printTree(head);
	destroyTree(head);
	
	return 0;
}