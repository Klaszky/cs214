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

	// char * file = extract("./test.txt");
	// head = tokenize(file, head, "test1.txt");
	// free(file);
	// file = extract("./test2.txt");
	// head = tokenize(file, head, "test2.txt");
	// free(file);
	treeNode * head = NULL;
	head = fileIterator("./", head);
	printTree(head);
	destroyTree(head);

	return 0;
}

// This makes and returns a Link with some
// default values and a supplied string
///////////////////
fileList * createLinkNode(char * fileName)
{
	lowerCase(fileName, strlen(fileName));
	fileList * temp = (fileList*)malloc(sizeof(fileList));
	temp->counter = 1;
	temp->fileName = strdup(fileName);
	temp->next = NULL;
	return temp;
}

fileList * addToFileList(fileList * fl, fileList * newLink)
{
	if(fl == NULL)
	{
		fl = newLink;
		return fl;
	}
	else if(strcmp(fl->fileName, newLink->fileName) == 0)
	{
		fl->counter++;
		free(newLink->fileName);
		free(newLink);
		return fl;
	}
	else
	{
		fl->next = addToFileList(fl->next, newLink);
		return fl;
	}
}

// This makes and returns a node with some
// default values and a supplied string
///////////////////
treeNode * createNode(char * newStr)
{
	treeNode * temp = (treeNode*)malloc(sizeof(treeNode));
	temp->left = NULL;
	temp->right = NULL;
	temp->files = NULL;
	temp->str = strdup(newStr);
	return temp;
}


treeNode * addToTree(treeNode * head, treeNode *newNode, fileList * newLink)
{
	// If tree is empty, just make head the tree
	///////////////////
	if(head == NULL)
	{
		head = newNode;
		head->files = addToFileList(head->files, newLink);
		return head;
	}
	// If this node is alread in the tree
	// it free the newNode that was passed and tries to 
	// add the current file to the node's linked list
	/////////////////////
	else if(strcasecmp(head->str, newNode->str) == 0)
	{
		head->files = addToFileList(head->files, newLink);
		free(newNode->str);
		free(newNode);
		return head;
	}
	// Recursive. If hits null, the makes that branch
	// the new node, if it hits nonNull, continue down
	// that branch
	///////////////////
	else if(strcasecmp(head->str, newNode->str) > 0)
	{
		if(head->left == NULL)
		{
			head->left = newNode;
			head->left->files = addToFileList(head->left->files, newLink);
		}
		else
		{
			head->left = addToTree(head->left, newNode, newLink);
		}

		return head;
	}
	else if(strcasecmp(head->str, newNode->str) < 0)
	{
		if(head->right == NULL)
		{
			head->right = newNode;	
			head->right->files = addToFileList(head->right->files, newLink);
		}
		else
		{
			head->right = addToTree(head->right, newNode, newLink);
		}

		return head;
	}

	return head;
}

// Recursive - This acts as my sort.
// I'm going to change this to be my output functions 
// sooner or later. 
///////////////////
void printTree(treeNode * head)
{
	fileList * ptr;
	if(head == NULL)
	{
		printf("Empty Tree\n");
		return;
	}

	if(head->left != NULL)
	{
		printTree(head->left);
	}

	printf("%s\n",head->str);
	ptr = head->files;
	while(ptr != NULL)
	{
		printf("%s %d\n", ptr->fileName, ptr->counter);
		ptr = ptr->next;
	}

	if(head->right != NULL)
	{
		printTree(head->right);
	}
}



// Attempts free up all of the alloc'd memory in my BST
// and each node's linked list.
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
	destroyList(head->files);
	free(head->str);
	free(head);
	return;
}

void destroyList(fileList * fl)
{
	if(fl->next != NULL)
	{
		destroyList(fl->next);
	}
	free(fl->fileName);
	free(fl);
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

treeNode * tokenize(char * fileContents, treeNode * head, char * currentFile)
{
	// Setting up some variables that will be used.
	// Most should be self explanatory.
	///////////////////
	if(fileContents == NULL)
	{
		return head;
	}
	char * inputString = fileContents;
	char * tempString;

	int startingPos = -1, endingPos = 0, sizeOfString = 0, len = 0, i = 0;
	len = strlen(inputString);

	treeNode * tempNode;
	fileList * tempLink;

	for(i = 0; i <= len; i++)
	{
		// Check if current character isalpha and then
		// makes some decisions based on that.
		///////////////////
		
		// This should cover the case where the string can't start
		// with a number.
		////////////////////
		if(sizeOfString == 0 && isdigit(inputString[i]) != 0)
		{
			continue;
		}
		else if(isalpha(inputString[i]) == 0 && isdigit(inputString[i]) == 0)
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

				tempLink = createLinkNode(currentFile);

				head = addToTree(head, tempNode, tempLink);
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
	// Setting up the vars we'll use to extract the 
	// contents of the file.
	////////////////////
	errno = 0;
	int fd = open(path, O_RDONLY);
	int errsv;
	errsv = errno;

	// Error check for file access
	////////////////
	if(errsv == 13)
	{
		printf("\n\nYou don't have access to this file\n\n");

		return NULL;
	}

	int fileLength = lseek(fd, 0, SEEK_END);
	int status = 0;
	int offset = 0;
	int amtToRead = fileLength;
	lseek(fd, 0, SEEK_SET);

	// File couldn't be opend
	////////////////////
	if(fd == -1)
	{
		printf("Error opening file.");
		return NULL;
	}

	// File is empty
	//////////////////
	if(fileLength == 0)
	{
		printf("Error, empty file.");
		return NULL;
	}

	//
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

treeNode * fileIterator(char * name, treeNode * head)
{
	DIR * dir;
	struct dirent * entry;
	char * fileContents;
	errno = 0;
	int errsv;
	if((dir = opendir(name)) == NULL)
	{
		errsv = errno;
		printf("\n\n%d\n\n", errsv);
		if(errsv == 2)
		{
			printf("\n\nNo such file or directory\n\n");
			return head;
		}
		if(errsv == 20)
		{
			fileContents = extract(name);
			
			// Error check
			///////////////
			if(fileContents == NULL)
			{
				return head;
			}

			head = tokenize(fileContents, head, name);
			free(fileContents);
			return head;
		}

		return NULL;
	}
	
	while((entry = readdir(dir)))
	{
		if(entry->d_type == DT_DIR)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
			    continue;
			}
			else
			{
				char * path = pathMake(name, entry->d_name);
				head = fileIterator(path, head);
				free(path);
			}
		}
		else if(entry->d_type == DT_REG)
		{
			char * path = pathMake(name, entry->d_name);
			fileContents = extract(path);
			head = tokenize(fileContents, head, entry->d_name);
			free(fileContents);
			free(path);
		}
	}
	closedir(dir);
	return head;
}

char * pathMake(char * currentPath, char * nextDir)
{
	// len1 and len2 are just to get the correct
	// size of the string we'll be making. The + 2
	// at the end if for the '/' and '\0'
	////////////////////////////
	int len = strlen(currentPath)+strlen(nextDir)+2;
	char * path = malloc(len);

	// If we get "./" it won't create the correct path
	// so we have this extra test in here.
	// snprintf writes 
	//////////////////////////
	if(strcmp(currentPath, "./") == 0)
	{
		snprintf(path, (len), "%s%s", currentPath, nextDir);
	}
	else
	{
		snprintf(path, (len), "%s/%s", currentPath, nextDir);
	}
	return path;	
}