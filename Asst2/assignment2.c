#include "assignment2.h"
// llFix
////////////
int main(int argc, char * argv[])
{ 
	if(argc != 3)
	{
		printf("Error, incorrect number of arguments");
		return -1;

	}

	treeNode * head = NULL;
	head = fileIterator(argv[2], head);
	finalOutput(head, argv[1]);
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

// Looks to see if there is already a link with the same fileName
// if there is, it increments the counter var for that link.
// If there isn't it adds a new Link to the fileList struct.
////////////////////
fileList * addToFileList(fileList * fl, fileList * newLink)
{
	// Hit the end of the list, simply add the node
	/////////////////
	if(fl == NULL)
	{
		fl = newLink;
		return fl;
	}
	// Two files with the same name? Increment the counter var
	/////////////////////
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

// Adds a new node if one doesn't already exists or augments one that is
// already in there.
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
	// If this node is already in the tree
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
// I use this for testing primary
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

// Attempts to free all of the fileLists associated with each
// node in the BST
////////////////////
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

// Part of the assignment is to make sure each string and file is
// all lowercase.
///////////////////
void lowerCase(char * str, int size)
{	
	int i;
	for(i = 0; i < size; i++)
	{
		str[i] = tolower(str[i]);
	}
}

// This is one of the main functions of the program. This goes through
// a file's contents, pulls out each string, and puts it into the BST
/////////////////////
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
		// Check if current character isalpha / isdigit and then
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

// This function and the following function are ... inelegant at best.
// However, I wasn't able to think of a better way to make this output
// properly other than hard coding some char arrays and then using many,
// many while loops.
void finalOutput(treeNode * head, char * outputFileName)
{
	errno = 0;
	int fd = open(outputFileName, O_WRONLY | O_CREAT);
	int errsv;
	int status = 0;
	int amtToWrite;

	errsv = errno;
	// Error check for common file opening issues.
	///////////////
	if(errsv == 13)
	{
		printf("\n\nYou don't have access to this file\n\n");
		return;
	}
	if(fd == -1)
	{
		printf("\nError opening file to write\n");
		return;
	}
	if(head == NULL)
	{
		printf("\nNo output, empty tree");
		return;
	}

	// Write the opening xml tags
	////////////////////
	amtToWrite = strlen(opening);
	while(amtToWrite > 0)
	{
		status = write(fd, opening, amtToWrite);
		amtToWrite -= status;
	}

	// Go through the BST and write it's contents to the file
	//////////////////
	writeTree(head, fd);

	//Write the closing xml tags
	//////////////////
	amtToWrite = strlen(closing);
	while(amtToWrite > 0)
	{
		status = write(fd, closing, amtToWrite);
		amtToWrite -= status;
	}
	


	close(fd);
}

// Goes over the BST recursively and adds items to the file
////////////////
void writeTree(treeNode * head, int fd)
{

	fileList * ptr = head->files;
	int status = 0;
	int amtToWrite;
	char * digit;
	int digitLen;

	// Error check
	////////////////
	if(head == NULL)
	{
		return;
	}

	// Continue along the left tree.
	/////////////////
	if(head->left != NULL)
	{	
		writeTree(head->left, fd);
	}

	// This part is a hot mess. It adds the first part of the xml tag,
	// the word, the number of times it appears, then closes the tag. 
	// Again, I know it's really ugly, but when I tried to make it all one
	// string I was getting really weird outputs. So I did it this way. Ugh.
	/////////////////

	// Open xml word tags.
	////////////////
	amtToWrite = strlen(wordOpen);
	while(amtToWrite > 0)
	{
		status = write(fd, wordOpen, amtToWrite);
		amtToWrite -= status;
	}

	amtToWrite = strlen(head->str);
	while(amtToWrite > 0)
	{
		status = write(fd, head->str, amtToWrite);
		amtToWrite -= status;
	}

	amtToWrite = strlen(wordOpenMid);
	while(amtToWrite > 0)
	{
		status = write(fd, wordOpenMid, amtToWrite);
		amtToWrite -= status;
	}

	// Same as the hot mess above, except for each file. Once again, I tried
	// to make this all one big string and my output got all jacked up. So,
	// I did it this way and it worked like a charm. So ... here we are. At 
	// almost midnight and I just can't care anymore. It's fine ...it's fine.
	///////////////////
	llSort(ptr);
	while(ptr != NULL)
	{
		// Open xml file tags
		/////////////////
		amtToWrite = strlen(fileNameOpen);
		while(amtToWrite > 0)
		{
			status = write(fd, fileNameOpen , amtToWrite);
			amtToWrite -= status;
		}
		amtToWrite = strlen(ptr->fileName);
		while(amtToWrite > 0)
		{
			status = write(fd, ptr->fileName, amtToWrite);
			amtToWrite -= status;
		}
		amtToWrite = strlen(fileNameMid);
		while(amtToWrite > 0)
		{
			status = write(fd, fileNameMid, amtToWrite);
			amtToWrite -= status;
		}

		// Making an int a string was a bit more annoying that
		// I anticipated...
		////////////////
		digitLen = intLen(ptr->counter) + 1;
		digit = malloc( digitLen * sizeof(char));
		sprintf(digit, "%d", ptr->counter);
		amtToWrite = strlen(digit);
		while(amtToWrite > 0)
		{
			status = write(fd, digit, amtToWrite);
			amtToWrite -= status;
		}		
		free(digit);


		// Close xml file tags
		/////////////////
		amtToWrite = strlen(fileNameClose);
		while(amtToWrite > 0)
		{
			status = write(fd, fileNameClose, amtToWrite);
			amtToWrite -= status;
		}
		ptr = ptr->next;
	}

	// Close xml word tags
	//////////////////
	amtToWrite = strlen(wordClose);
	while(amtToWrite > 0)
	{
		status = write(fd, wordClose, amtToWrite);
		amtToWrite -= status;
	}

	// Continue along the tree.
	//////////////////
	if(head->right != NULL)
	{
		writeTree(head->right, fd);
	}
}

// Pulls out all data from a give file
///////////////
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

	char * fileContents = (char*)malloc((sizeof(char) * fileLength) + 1);
	while(amtToRead > 0)
	{
		status = read(fd, fileContents, amtToRead);
		amtToRead -= status;
	}

	fileContents[fileLength] = '\0';
	close(fd);
	return fileContents;
}

// Main loop of the program. Loops through each file in a given
// directory recursively, pulls all the contents from each of those
// files and tokenizes them. 
/////////////////
treeNode * fileIterator(char * name, treeNode * head)
{
	// Creates a directory pointer, an entry pointer and a char
	// pointer to hold what's pulled out of a file. 
	//////////////////
	DIR * dir;
	struct dirent * entry;
	char * fileContents;
	errno = 0;
	int errsv;
	if((dir = opendir(name)) == NULL)
	{
		// opendir returned null so we weren't given a directory, 
		// so we'll try to open a file.
		///////////////////
		errsv = errno;
		name = fileFixer(name);

		// Error checks for common file opening issues. Also makes sure the 
		// file we're given is a proper path... not just a name.
		///////////////////
		if(errsv == 2)
		{
			printf("\n\nNo such file or directory\n\n");
			free(name);
			return head;
		}
		if(errsv == 20)
		{
			fileContents = extract(name);
			
			// Error check for an empty file
			///////////////
			if(fileContents == NULL)
			{
				free(name);
				return head;
			}

			// All is good with our file, tokenize it and put it
			// in out BST
			///////////////
			head = tokenize(fileContents, head, name);
			free(fileContents);
			free(name);
			return head;
		}
		free(name);
		return NULL;
	}
	// We were given a directory, so we'll look until readdir hits the end of 
	// the directory.
	/////////////////
	while((entry = readdir(dir)))
	{
		// If it's a directory: if is a '.' directory, continue on with the loop,
		// we don't need to open them. If it's a regular directory, open it and 
		// continue down that path.
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

// Keeps track of the current path
//////////////
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


// Quick and dirty helper method
//////////////////
char * fileFixer(char * file)
{
	// If a file is passed with a just a name and no path at all
	// it add a './' to make it a relative path
	//////////////////
	if((file[0] != '.' || file[0] != '~') && file[1] != '/') 
	{
		int len = strlen(file) + 3;
		char * newFileName = malloc(len);
		snprintf(newFileName, len, "./%s", file);
		return newFileName;
	}
	else
	{
		char * newFileName = strdup(file);
		return newFileName;
	}
}


// Quick and dirty helper method to get the number of digits in an int
//////////////////
int intLen(int x)
{	
	int toReturn = 0;
	while(x > 0)
	{
		toReturn++;
		x /= 10;
	}

	return toReturn;
}

void llSort(fileList * fl)
{
	fileList * currentLink = fl;
	fileList * iterPtr;
	fileList * max;

	while(currentLink != NULL)
	{
		max = currentLink;
		iterPtr = currentLink->next;

		while(iterPtr != NULL)
		{
			if(max->counter < iterPtr->counter)
			{
				max = iterPtr;
			}
			else if(max->counter == iterPtr->counter)
			{
				if(strcmp(max->fileName, iterPtr->fileName) > 0)
				{
					max = iterPtr;
				}
			}

			iterPtr = iterPtr->next;
		}

		swap(currentLink, max);
		currentLink = currentLink->next;
	}
}

void swap(fileList * link1, fileList * link2)
{
	char * tempFileName = link1->fileName;
	int tempCounter = link1->counter;
	link1->fileName = link2->fileName;
	link1->counter = link2->counter;
	link2->fileName = tempFileName;
	link2->counter = tempCounter;
}