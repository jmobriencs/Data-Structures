/*	John-Michael O'Brien  w1890922
	AVL Lab
	Prof. Sabzevary
	CISP 430
	4/12/21
*/

#include <iostream>
#include <algorithm> // max is part of this library
#include <fstream>

using namespace std;

// declare global variables
ifstream inFile("input.txt");
ofstream outFile("output.txt");

struct node // a node belonging to the avl tree
{
	int key;
	int height;
	node* left = NULL; // initialize all pointers to NULL asap (helps avoid segfaults/infinite loops)
	node* right = NULL;
};

struct queueNode // a node belonging to a queue
{
	node* node = NULL;
	queueNode* next = NULL;
};

struct queue // essentially a queue container
{
	queueNode* front = NULL;
	queueNode* rear = NULL;
};

// newNode function
node* newNode(int key)
{
	node* nn = new node;
	nn->key = key;
	nn->height = 0; // nn height always set 0
	nn->left = NULL;
	nn->right = NULL;
	return nn;
}

// height function
int height(node* node)
{
	if (node == NULL)
        return -1;
    return node->height;
}

// getBalance function
int getBalance(node* node) // calc each nodes balance from the childrens' height
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// enqueue function
void enqueue(node* nodeToEnqueue, queue* Queue)
{
	if(nodeToEnqueue != NULL) // so long as we have a node to add to the queue
	{
		queueNode* nqn = new queueNode;
		nqn->next = NULL;
		nqn->node = nodeToEnqueue;

		if(Queue->front == NULL) // inserting to an empty queue
      	{
			  Queue->front = nqn;
			  Queue->rear = nqn;
		}
		else
		{
			Queue->rear->next = nqn; // the current rear of the queue's next pointer now points to nqn
			Queue->rear = nqn; // the queue's rear pointer now points to nqn
		}
  	}
}

// dequeue function
node* dequeue(queue* Queue)
{
	node* avlNode = Queue->front->node; // get the (AVL) node from the queue's front pointer's node
	if(Queue->front != NULL)
  	{
		queueNode* temp = Queue->front->next;
		delete Queue->front; // give computer back (deallocate) the memory that the queueNode sitting at the front of the queue was using
		Queue->front = temp;
  	}
  	if(Queue->front == NULL) // if we removed the last node in the queue
		Queue->rear = NULL; // point the queue's rear pointer at NULL

	return avlNode;
}

// rightRotate function
node* rightRotate(node* x)
{
//	   x           y
// y        ->         x
//	  z             z
	node* y = x->left;
	node* z = y->right;

	// rotation
	x->left = z;
	y->right = x;

    // update heights for x and y
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // return the new root
    return y;
}

// leftRotate function
node* leftRotate(node* x)
{
//	   y           x
// x        <-         y
//	  z             z
	node* y = x->right;
	node* z = y->left;

	// rotation
    x->right = z;
	y->left = x;

    // update heights for x and y
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // return the new root
    return y;
}

// rebalance function
node* rebalance(node* node)
{
	node->height = max(height(node->left), height(node->right)) + 1;
	int balance = getBalance(node);  // node->left - node->right

	// do rotations as necessary

	// left heavy outside
	if (balance > 1 && getBalance(node->left) > 0)
		return rightRotate(node); // single rotation

	// left heavy inside
	else if (balance > 1 && getBalance(node->left) < 0)
	{
		// double rotation
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// right heavy outside
	if (balance < -1 && getBalance(node->right) < 0)
		return leftRotate(node); // single rotation

	// right heavy inside
	else if (balance < -1 && getBalance(node->right) > 0)
	{
		// double rotation
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	// no rotation
	return node;
}

// non-tail recursive algorithm because of rebalance
node* insert(node* node, int key)
{
	// recursive code for inserting a node
	// when insert happens set height to 0 for the node
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);

	else
		node->right = insert(node->right, key);

	node = rebalance(node);  // update heights and rebalance
	return node;
}

// print avl node formatted with key, height, and balance factor
void printNode(node* node)
{
	outFile << node->key;
	outFile << "("<<node->height << ",";
	outFile << getBalance(node)<<") ";
}

// print by level using two queues
void printTree(node* root)
{
	queue* currentLevel = new queue; // make a new queue on the heap, have currentLevel point to that
	queue* nextLevel = new queue; // make a new queue on the heap, have nextLevel point to that
  	queue* swap = NULL; // create a temp variable swap for the queue
  	node* tempNode = NULL; // create a temp variable tempNode for the avl node

	enqueue(root, currentLevel); // enqueue the root node onto the currentLevel queue
	while (currentLevel->front != NULL) // while there's still nodes in the currentLevel queue
	{
		tempNode = dequeue(currentLevel); // dequeue the front of currentLevel and store it in tempNode
    	printNode(tempNode); // call to print tempNode (avl node)
		enqueue(tempNode->left, nextLevel); // enqueue tempNode's left child onto nextLevel
    	enqueue(tempNode->right, nextLevel); // enqueue tempNode's right child onto nextLevel

		if (currentLevel->front == NULL) // if currentLevel is an empty queue
		{
			// swap the queues that currentLevel and nextLevel point to
			swap = currentLevel;
    		currentLevel = nextLevel;
			nextLevel = swap;
			outFile << endl;
		}
	}
	delete currentLevel; // give memory back to the computer
	delete nextLevel; // give memory back to the computer
}

// main function
int main()
{
	node* root = NULL;
	int temp;

	// take input from input.txt
	while (inFile >> temp)
		root = insert(root, temp);
	inFile.close(); // close input file

	// reroute display to output.txt
	outFile << "AVL Tree Generator" << endl;
	outFile << "Format: key(height,balance factor)" << endl;
	outFile << "-----------------------------------" << endl;
	printTree(root); // call to print AVL tree
	outFile.close();  // close output file
	return 0;
}
