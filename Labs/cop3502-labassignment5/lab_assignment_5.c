#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

int length(node *head);
char* toCString(node* head);
void insertChar(node** pHead, char c);
void deleteList(node** pHead);
void printList(node *head);

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int count = 0;
	node *counter = head;

	while (counter != NULL) {
		count++;
		counter = counter->next;
	}
	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{

	int i = 0;
	char c;
	int stringLength = length(head);
	
	char *string = malloc(sizeof(char) * (stringLength + 1));
	while (head != NULL) {
		c = head->letter;
		string[i] = head->letter;
		head = head->next;
		i++;
	}
	string[stringLength] = '\0';
	return string;

}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node *newNode = malloc(sizeof(node));
	
	if (*pHead == NULL) {
		newNode->letter = c;
		newNode->next = NULL;
		*pHead = newNode;
	}
	else {
		node *temp = *pHead;
		while (temp->next != NULL)
			temp = temp->next;

		newNode->letter = c;
		newNode->next = NULL;

		temp->next = newNode;

		//printf("DONE INSERTING... PRINT: \n");
		//printList(*pHead);
	}

}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node *temp = *pHead;
	//int stringLength = length(*pHead);
	while (temp != NULL) {
		*pHead = temp->next;
		free(temp);
		temp = *pHead;
	}

	*pHead = NULL;
}

void printList(node *head) {
	printf("\n-----------------\n");
	while (head != NULL) {
		printf("head 			= %p\n", head);
		printf("head->letter		= %c\n", head->letter);
		printf("head->next 		= %p\n\n", head->next);
		head = head->next;
	}
	printf("-----------------\n\n");
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}
