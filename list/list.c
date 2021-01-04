// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
  Creating a new Node with integer item that is assigned by the user 
*/
struct nodeStruct* List_createNode(int item)
{
	//Creating Node by initializing it to NULL
	struct nodeStruct *head = NULL;
	//allocating size for head pointer
	head = malloc(sizeof(struct nodeStruct));
	//Meanwhile head is not pointing to NULL, create a head pointer pointing to a specific item
	head -> item = item;
	//Set the head pointer points toward 'next' pointer to NULL
	head -> next = NULL;
	//Returning a pointer to the new node
	return head;
}
/*
 * Insert node at the head of the list.
 */
/*Reference to: https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node*/
/*Example: 5->4->3->2->1, adding 6 into the linked list to the head
  After adding 6 into the linked list to produce a linked list of 6->5->4->3->2->2->1*/
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node)
{
	//Execute the headinsert only if it is not NULL
	if ( node != NULL )
	{
		//Storing the address of headRef pointer to the node pointer to next	
		node->next = *headRef;
		//Storing the node to the pointer of headRef
		*headRef = node;
	}
}
/*
 * Insert node after the tail of the list.
 */
/*Ex: the linked lists has the following content: 3->2->1
	adding 0 to the end of the linked list to have 3->2->1->0*/

void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node)
{
   //Creating a  pointer tail variable for storing the address of the pointer headRef
   	struct nodeStruct *tail = *headRef;
	//Execute this if statement if the linked list is not empty
	if ( tail != NULL) 
	{
		//Check if the tail pointer to next is NULL or not, if it is,
		//It implies that it has reached the end of the linked list
		while ( tail -> next != NULL) 
		{
			//While it is not the last node, iterating through each node
			tail = tail -> next;
		}
		//Node pointer is stored into the tail pointer that points toward next
		tail -> next = node;
	}
	//If it is at the NULL, meaning at the end of the node, store the tail
	//to the content of node
	else if ( tail == NULL) 
	{
		tail = node;
	}
}
/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
/*Reference to given materials on assignment 1 specification*/
int List_countNodes (struct nodeStruct *head)
{
	//Variable for storing the number of nodes
	int numberOfNodes = 0;
	struct nodeStruct *curr = head;

	//Incrementing the number of nodes until it reaches NULL
	while ( curr != NULL )
	{
		//Iterating through each node
		curr = curr ->next;
		//for every successfully transversed node, increment the number of nodes by one
		numberOfNodes++;
	}
	//Returning the number of nodes counted
	return numberOfNodes;
}
/*
 * Return the first node holding the value item, return NULL if none found
 */
/*EX: the linked list contains: 5->4->3->2->1 and searching for specific item within the linked list*/
/*Algorithm: Iterating through the element one by one until the desired item is found else return none*/
struct nodeStruct* List_findNode(struct nodeStruct *head, int item)
{
	//Meanwhile the head pointer does not point to NULL, meaning that it is not empty

	while ( (head) != NULL )
	{
		//If the item found then return the found item
		if ( (head)-> item == item )
		{
			return head;
		}
		//If not found yet, continue onto the next pointer element by
		//transversing to the next pointer on the linked list
		(head) = (head) -> next;
	}
	//If desired item is not found,then return NULL
		return NULL;
}
/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only one node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node)
{
	
	//Allocating spaces for temproary variables 
	struct nodeStruct *temp1 = malloc(sizeof(struct nodeStruct));
	struct nodeStruct *temp2 = malloc(sizeof(struct nodeStruct));
	//If there is only one node, then set the head of the list to NULL
	if ( (*headRef) == node  )
	{
		(*headRef) = node -> next;
		//freeing the allocated space for temp1
		free(node);
	}
	//Meanwhile it is not the only node
	else
	{
		//Storing the address pointer of headRef into temp1
		temp1 = (*headRef);
		//Iterating through each temp1 meanwhile temp1 points next does not
		//point to node and it does not point to NULL
		while ( (temp1->next != node) && (temp1 ->next != NULL) )
		{
			//Replacing temp1 pointer with the next following temp1 
			temp1 = temp1 -> next;
		}
		//If temp1 pointer points next equal to the node
		if (temp1->next == node)
		{
			//storing temp2 with the pointer of 'next' pointed by temp1
			temp2 = temp1 ->next;
			//Replacing temp1 pointer to next with the next two pointers,
			//replacing the following two pointers
			temp1 -> next = temp1 -> next -> next;
			//freeing the allocated space for temp2
			free(temp2);
		}
	}
}
/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
//Swapping function: Bubble sort
//Reference from: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/ for 
//sorting algorithm
void List_sort (struct nodeStruct **headRef)
{
	//Variables initialization
		//Flag is used to indicate if any swap between two nodes are required
	int flag = 0;
	struct nodeStruct *node;
	struct nodeStruct *nodeptr = NULL;

	//If the head is empty then return
	if( (*headRef) == NULL )
	{
		return;
	}
	else
	//Swapping and comparison begins
	{
		//Execute the first comparison first then if flag is still true, implying that
		//swapping is still required and it is not fully sorted yet
		do
		{
			//No swapping required
			flag = 0;
			//Storing the address pointer of headRef to struct node
			node = (*headRef);
			while ( node -> next != nodeptr )
			{
				//If the node that points to is greater than the item connecting after that pointer,
				//then swap
				if (node -> item > node->next-> item )
				{
					//swapping the node with the node after
					swapNode(node, node->next);
					//Swapping required
					flag = 1;
				}
				//Iterate to the next node
				node =  node -> next;
			}
			nodeptr = node; 
		}
		//run only when flag = 1
		while (flag);
	}
}
/*
  Allocate memory for a node of type struct nodeStruct and initialize
  it with the value item. Return a pointer to the new node.
  Simple Swapping function for changing the position of node 1 and node 2*/
void swapNode(struct nodeStruct *node1, struct nodeStruct *node2)
{	
	int tmp;
	//Interchanging contents of node1 and node2
	//For instance node1 initially has the value of 1 and node 2 has the value of 2
	//After swapping, node1 and node 2 will have the value of 2 and 1, respectively.
	tmp = node1->item;
	node1 -> item = node2 -> item;
	node2 -> item = tmp;	
}


int main()
{
	printf("\n----------Testing Linked List----------\n");
	struct nodeStruct *head = NULL;

	// Starting count:
	assert(List_countNodes(head) == 0);
	printf("Test 1:Passed Count Node\n");
	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
		printf("Test 2:Passed Counting the Node\n");
	assert(List_findNode(head, 0) == firstNode);
	printf("Test 3:Passed Finding Node with item = 0\n");
	assert(List_findNode(head, 1) == NULL);
	printf("Test 4:Passed Finding Node with item = 1\n");

	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	printf("Test 5:Passed Counting the Node\n");
	assert(List_findNode(head, 0) == firstNode);
	printf("Test 6:Passed Finding the Node 3 after tail insert\n");

	assert(List_findNode(head, -5) == lastNode);
		printf("Test 7:Passed Finding the Node 4 after tail insert\n");

	assert(List_findNode(head, 1) == NULL);
			printf("Test 8:Passed Finding the Node 5 after tail insert\n");


	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);
	printf ("Test 9:Passed Verifying List\n");
	// Sort and verify:
	List_sort(&head);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);
	printf ("Test 10:Passed Verifying and Sorting List\n");

	// Delete
	assert(List_countNodes(head) == 2);
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == -5);
	assert(current->next == NULL);


	printf("\n----------End of Testing----------\n");
	return 0;
}


