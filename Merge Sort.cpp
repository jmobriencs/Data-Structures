/*	John-Michael O'Brien  w1890922
	Merge Sort Lab
	Prof. Sabzevary
	CISP 430
	3/14/21
*/

#include<iostream>

using namespace std;

struct node
{
	int data;
	node* next;
};

// function to add a node to beginning of the linked list
void addNode(node*& head, int data)
{
	node* newnode = new node;
	newnode->data = data;
	newnode->next = head;
	head = newnode;
} // end void addNode(node*& head, int data)

// split function
void split(node* head, node*& a, node*& b)
{
	node* current = NULL;
    int listLength = 1; // start at 1 to get length rather than last index
    for(current = head; current->next; current = current->next)
		listLength++; // add 1 to length of list each iteration
    int splitLength = listLength / 2; // find the middle

    current = head;
    for(int i=0; i < splitLength; i++) // left partition
    {
        addNode(a, current->data);
        current = current->next;
    }
    for(int i=splitLength; i < listLength; i++) // right partition
    {
        addNode(b, current->data);
        current = current->next;
    }
} // end void split(node* head, node*& a, node*& b)

// merge function
node* merge(node* a, node* b)
{
	node* mergedList = NULL;
	// base cases if either list is empty, return the other one
	if(a == NULL)
		return(b);
	else if(b==NULL)
		return(a);

	if(a->data <= b->data) // also handles cases when data is the same
	{
		mergedList = a;
		mergedList->next = merge(a->next, b); // recursively add the rest of a with b to mergedList
	}
	else
	{
		mergedList = b;
		mergedList->next = merge(a, b->next); // recursively add the rest of b with a to mergedList
	}
	return mergedList; // return the merged list
} // end node* merge(node* a, node* b)

// mergeSort function
node* mergeSort(node* head)
{
	// base cases for if length is 0 or 1
	if(head == NULL)
		return NULL;
	if(head->next == NULL)
		return head;
	// local variables
	node* a = NULL; // node pointer a points to NULL
	node* b = NULL; // node pointer b points to NULL
	node* c = NULL; // node pointer c points to NULL

	// call to split function
	split(head, a, b);

	a = mergeSort(a); // recursive call to mergeSort to sort first half of the part of the list being fed in
	b = mergeSort(b); // recursive call to mergeSort to sort second half of the part of the list being fed in
	c = merge(a,b); // call to merge function to merge the two halves
	return c; // c is going to hold sorted version of the part of the list that we fed in
} // end node* mergeSort(node* head)

// prints the populated & sorted linked lists
void printLinkedList(node* head)
{
	while(head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
} // end void printLinkedList(node* head)

int main()
{
	node* head = NULL;
	node* sorted = NULL;
	int arr[] = {94, 2, 27, 1080, 109, 55, 11, 67, 18}; // explicitly defined array
	int arrSize = sizeof(arr) / sizeof(arr[0]);	// determine size of array
	// populate linked list from array
	for (int i = 0; i < arrSize; i++)
	{
		addNode(head, arr[i]); // traverse thru arr and add data as head of linked list (treating it like a stack)
	}
	cout << "Populated Unsorted Linked List:" << endl;
	printLinkedList(head); // print populated linked list
	sorted = mergeSort(head); // call to sort linked list
	cout << "\nLinked List after Merge Sort:" << endl;
	printLinkedList(sorted); // print linked list after merge sort
	return 0;
} // end int main()
