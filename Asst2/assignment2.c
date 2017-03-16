#include "assignment2.h"

/*
Main():
	-Check user input to make sure that the user 
	provided the correct number of arguments and that it
	is a valid file or directory.

invertedIndex <inverted-index file name> <directory or file name>

*/

int main(int argc, char * argv[])
{ //open main
	// if(argc != 3)
	// {
	// 	printf("Error, incorrect number of arguments");
	// 	return -1;

	// }
	// char * indexFileName = argv[1];
	// char * directory = argv[2];

	treeNode * head = NULL;
	char * file = extract("./test.txt");
	head = tokenize(file, head);
	free(file);
	file = extract("./test2.txt");
	head = tokenize(file, head);
	free(file);
	// printf("\n\n%s\n\n", head->str);
	// printf("\n\n%s\n\n", file);
	printTree(head);
	destroyTree(head);

	return 0;
}



// int fileExists(char* filename){ // was gonna use stat() but files aren't gonna be >= 2gb?

    
// 	struct stat status;
// 	return (stat(filename, &filename) == 0);
// }
// if(fileExists(filename))  
// {
	//wait it says the 3rd argument is a directory or file name.
	// what do u think we should do to check which it is. 
	// we can use a method like this
	/*int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
   
   */// http://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
// }
	
//	file write will be like FILE ... = fopen(filename argument, "w")


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
		head->num++;
		free(newNode->str);
		free(newNode);
		return head;
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
		printf("null city\n");
		return;
	}

	if(head->left != NULL)
	{
		printTree(head->left);
	}

	printf("%s %d\n",head->str, head->num);

	if(head->right != NULL)
	{
		printTree(head->right);
	}
}

// Attempts free up all of the alloc'd memory in my BST
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
	free(head->str);
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
	char * toReturn = (char*)calloc(size + 1, sizeof(char));
	for(x = 0, y = start; y < end; x++, y++)
	{
		toReturn[x] = originalString[y];
	}

	lowerCase(toReturn, size);
	return toReturn;
}

void lowerCase(char * str, int size)
{	
	int i;
	for(i = 0; i < size; i++)
	{
		str[i] = tolower(str[i]);
	}
}

treeNode * tokenize(char * fileContents, treeNode * head)
{
	// Setting up some variables that will be used.
	// Most should be self explanatory.
	///////////////////
	char * inputString = fileContents;
	char * tempString;

	int startingPos = -1, endingPos = 0, sizeOfString = 0, len = 0, i = 0;
	len = strlen(inputString);

	treeNode * tempNode;

	// The logic will have to be changed a bit because
	// what is considered a token is a bit different
	// in this assignment.
	////////////////////
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

	return head;
}

char * extract(char * path)
{
	//setting up the vars we'll use to extract the 
	//contents of the file.
	int fd = open(path, O_RDONLY);
	int fileLength = lseek(fd, 0, SEEK_END);
	int status = 0;
	int offset = 0;
	int amtToRead = fileLength;
	lseek(fd, 0, SEEK_SET);

	//could quick file checks
	if(fd == -1)
	{
		printf("Error opening file.");
		return NULL;
	}
	if(fileLength == 0)
	{
		printf("Error, empty file.");
		return NULL;
	}

	char * fileContents = (char*)malloc((sizeof(char) * fileLength) + 1);
	while(amtToRead > 0)
	{
		status = read(fd, fileContents+offset, amtToRead);
		amtToRead -= status;
	}

	fileContents[fileLength] = '\0';
	close(fd);
	return fileContents;

}

int fileIterator()
{
	return 0;
}