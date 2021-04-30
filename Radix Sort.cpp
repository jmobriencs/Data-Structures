/*	John-Michael O'Brien  w1890922
	Radix Sort Lab
	Prof. Sabzevary
	CISP 430
	3/3/21
*/

#include <iostream>
#include <math.h>

using namespace std;

struct node
{
	int value;
	node* next;
};

struct Queue
{
	node* front;
	node* rear;
};

// enqueue function
void enqueue(Queue& que, int num)
{
	node* newNode = new node;
	newNode->value = num;
	newNode->next = NULL;

	// add newNode to the queue
	if (que.rear) // use dot notation to deal with pointer rear itself
	{
		que.rear->next = newNode; // que.rear is the pointer, dereference that, and have its next pointer point to newNode
		que.rear = newNode; // que.rear is the pointer and it points to newNode
	}
	else
		que.front = que.rear = newNode; // have que's front & rear pointers point to newNode

} // end void enqueue(Queue& que, int num)

// dequeue function
int dequeue(Queue& que)
{
	node* temp; // create a node pointer temp variable
	int headValue = que.front->value; // create a copy of the value at the front of que and call it headValue
	if(que.front)// use dot notation to deal with pointer front itself
	{
		temp = que.front; // set temp to point to que's front pointer
		que.front = que.front->next; // set que's front pointer to point to the node after the current front
		delete temp; // prevent memory leaks by freeing up the old front

		if (!que.front) // if que's front points to nothing
			que.rear = NULL; // que's rear pointer points to nothing
	}
	return headValue;
} // end int dequeue(Queue& que)

// function that fills the buckets(bucketize me cap'n!)
void fillBuckets(int arr[], int size, Queue que[], int digit)
{
	int M=digit*10;
	int N=digit;

	// to process any of the digits
	for (int i = 0; i < size; i++)
	{
		int nothingToLeft = arr[i] % M; // to get rid of anything to left of what we're looking for
		int nothingToRight = nothingToLeft / N; // to get rid of anything to the right of what we're looking for
		enqueue(que[nothingToRight], arr[i]); // feeding in the ith element of arr and enqueing it into the corresponding que
	}
} // end void fillBuckets(int arr[], int size, Queue que[], int digit)

// function that flattens the array of queues and returns type int array (in ascending order)
int* flattenAscending(int size, Queue que[])
{
	int* arr = new int[size]; // a pointer that points to an array of ints on the heap of a certain size
	int index = 0;
	for (int i = 0; i < 10; i++) // for buckets 0 to 9
	{
		while(que[i].front != NULL && que[i].rear != NULL) // while que[i] (the current bucket) is not empty
		{
			arr[index] = dequeue(que[i]); // dequeue from the current bucket, place in proper location in the array
			index++;
		}
	}
	return arr;
} // end int* flattenAscending(int size, Queue que[])

// function that flattens the array of queues and returns type int array (in descending order)
int* flattenDescending(int size, Queue que[])
{
	int* arr = new int[size]; // a pointer that points to an array of ints on the heap of a certain size
	int index = 0;
	for (int i = 9; i > -1; i--) // buckets 9 to 0
	{
		while(que[i].front != NULL && que[i].rear != NULL) // while que[i] (the current bucket) is not empty
		{
			arr[index] = dequeue(que[i]); // dequeue from the current bucket, place in proper location in the array
			index++;
		}
	}
	return arr;
} // end int* flattenDescending(int size, Queue que[])

// function to find max value
int findMaxValue(int arr[], int arrSize)
{
	int maxValue = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] > maxValue)
		maxValue = arr[i];
	}
	return maxValue;
} // end int findMaxValue(int arr[], int arrSize)

// Returns the length, in number of digits, of value
int getLength(int value)
{
	if (value == 0)
   		return 1;

	int digits = 0;
	while (value != 0)
	{
    	digits = digits + 1;
    	value = value / 10;
	}
	return digits;
} // end int getLength(int value)

int main()
{
	struct Queue que[10]; // create a 10 element array of queues
	// create array of ints to sort
	int unsortedArray[] = {170, 45, 75, 90, 802, 2, 24, 66}; // array from the lecture notes
	int size = 8;

	for (int i = 0; i < 10; i++)
	{
		que[i].front = NULL; // initialize all que.front (buckets) to point nothing
		que[i].rear = NULL; // initialize all que.rear (buckets) to point nothing
	}

	// filling ascending array
	int* ascending = new int[size]; // make an ascending array on the heap
	for (int i = 0; i < size; i++)
	{
		ascending[i] = unsortedArray[i];
	}

	// filling descending array
	int* descending = new int[size]; // make a descending array on the heap
	for (int i = 0; i < size; i++)
	{
		descending[i] = unsortedArray[i];
	}

	// figure out how long our longest number is
	int maxNum = findMaxValue(unsortedArray, size);
	int maxNumLength = getLength(maxNum);

	// radix sort the array forwards
	for (int i = 0; i < maxNumLength; i++)
	{
		// put the numbers into their corresponding bucket (queue) based on the digit i many places from the least significant digit
		fillBuckets(ascending, size, que, pow (10, i)); // calling pow feeding in 10 to the power of i to fillBuckets
		// empty out the Qs in order using the dequeue function into a single data structure
		delete[] ascending; // prevent memory leaks
		ascending = flattenAscending(size, que); // ascending is going to point to a fresh new array on the heap

	}

	// radix sort the array backwards
	for (int i = 0; i < maxNumLength; i++)
	{
		// put the numbers into their corresponding queue based on the digit i many places from the least significant digit
		fillBuckets(descending, size, que, pow (10, i)); // calling pow feeding in 10 to the power of i to fillBuckets
		// empty out the Qs in order using the dequeue function into a single data structure
		delete[] descending; // prevent memory leaks
		descending = flattenDescending(size, que); // descending is going to point to a fresh new array on the heap
	}

	// display the ascending sorted array
	cout << "Ascending:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << ascending[i] << " ";
	}
	cout << endl << endl;

	// display the descending sorted array
	cout << "Descending:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << descending[i] << " ";
	}
	cout << endl;

	// cleanup all the memory reservations (nothing on the heap)
	delete[] ascending;
	delete[] descending;
} // end int main()
