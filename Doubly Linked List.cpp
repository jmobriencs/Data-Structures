/*  John-Michael O'Brien  w1890922
    Doubly Linked List - Names
    Prof. Sabzevary
    CISP 430
    2/23/21
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// declare global variables
ifstream inFile("input.txt");
ofstream outFile("output.txt");

struct node
{
	string name; // string called name
	node* next; // node pointer called next
	node* prev; // node pointer called prev
};

node* findNode(node*& head, string name)
{
	node* current = head; // node pointer current set to head

	if (head) // if head points to something
	{
		while(current->next) // while current has a next
		{
			if (current->name == name) // if current's name is the same as name
			{
				break; // leave the loop
			}
			current = current->next; // iterator
		}
	}
	else // if head does not point to anything yet
	{
		current = NULL; // current will then point to NULL
		return current; // leave the function, returning NULL
	}

	// if the names aren't the same
	if (current->name != name)
	{
		current = NULL; // current will then point to null
	}
	return current; // will return NULL if name isn't found, will return address of name's node if name is found
}

void insertNode(node*& head, node*& tail, string name)
{
	if (findNode(head, name) == NULL) // if name isn't already in the list
	{
		node* newNode = new node; // set newNode pointer to new node on the heap
		newNode->name = name;
		// empty list, so newNode is the head and tail also points to the node
		if (head == NULL)
		{
			// cout << "nobody's on the list yet, so we're gonna put " << name << " at the head and tail" << endl;
			head = newNode; // head points to newNode
			tail = newNode; // tail points to newNode
			return; // leave the function
		}

		// check if newNode's name is smaller than head's name (earlier in alphabet, compares ASCII values)
		else if (newNode->name < head->name) // if newNode comes before head
		{
			newNode->next = head; // newNode's next points to the current head of the list
			head->prev = newNode; // current head of list's prev needs to point to newNode
			head = newNode; // the head is now pointing to the newNode
			return; // leave the function
		}

		// check if newNode's name is greater than tail's name (later in alphabet, compares ASCII values)
		else if (newNode->name > tail->name) // if newNode comes after tail
		{
			newNode->prev = tail; // newNode's prev points to the current tail of the list
			tail->next = newNode; // current tail of list's next needs to point to newNode
			tail = newNode; // the tail is now pointing to the newNode
			return; // leave the function
		}

		// if we're somewhere in middle
		else
		{
			node* current = head; // temp variable current for traversing
			while(current->name < name) // traversing so long as current name is less than name fed in
			{
				current = current->next; // iterator
			}
			// once current's name is greater than what we're fed in, break out of the loop
			current->prev->next = newNode; // current prev's next pointer now points to newNode
			newNode->prev = current->prev; // newNode's prev pointer now points to the node before current
			newNode->next = current; // newNode's next pointer now points to current
			current->prev = newNode; // current's prev pointer now points to newNode
		}
	}
}

void deleteNode(node*& head, node*& tail, string name)
{
	node* current = findNode(head, name); // if name *is* on the list, have location point to it
	if (current) // if current points to a place on the list
	{
		if (current->prev != NULL) // if there is something before current (current is not the head)
		{
			current->prev->next = current->next; // a node other than head is being deleted
		}
		else // if current is head
		{
			head = current->next; // the node being deleted is the head
		}

		if (current->next != NULL) //if there is something after current (current is not the tail)
		{
			current->next->prev = current->prev; // a node other than tail is being deleted
		}
		else // if current is tail
		{
			tail = current->prev;	// the node being deleted is the tail
		}
	}
}

void traverseBeginToEnd(node*& head) // only dealing with head
{
	node* current = head;
	while (current != NULL) // traversing forward
	{
		outFile << current->name << endl; // add name to output
		current = current->next; // iterator
	}
}

void traverseEndToBegin(node*& tail) // only dealing with tail
{
	node* current = tail;
	while (current != NULL)
	{
		outFile << current->name; // add name to output
		current = current->prev; // iterator
		if (current) // if we're not on the first name of the list
		{
			outFile << endl; // add a newline to the output
		}
	}
}

int main()
{
	node* head = NULL; // initialize node pointer head to point to null
	node* tail = NULL; // initialize node pointer tail to point to null

	string word; // local string variable called word

	while (inFile.good()) // so long as we have words in infile, no words, returns false
	{
		word = ""; // c
		inFile >> word;
		if (word == "delete") // when delete command is found
		{
			string name; // declare local variable string name
			inFile >> name; // read the name that is after delete in inFile
			deleteNode(head, tail, name); // call the deleteNode function
		}
		else
		{
			insertNode(head, tail, word); // will insert word into the list when delete isn't found
		}
	} // process the file word by word
	inFile.close(); // close the file

	// output to outFile
	traverseBeginToEnd(head); // function call
	outFile << "============" << endl; // output separator
	traverseEndToBegin(tail); // function call
	outFile.close(); //close the file

	// give the computer back the memory to prevent memory leaks
	node* current = head->next; // node pointer current points to head's next
	// while current has a next
	while(current->next)
	{
    	current = current->next; // current points to the node after itself
    	delete current->prev; // delete the node before current
	} // end while(current->next)
	delete head; // delete what head points to
	delete tail; // delete what tail points to
	return 0; // close program and report no errors
}
