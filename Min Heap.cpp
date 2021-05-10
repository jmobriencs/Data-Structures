/*	John-Michael O'Brien  w1890922
	Min Heap
	Prof. Sabzevary
	CISP 430
	5/3/21
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

// global variables
int heapArr[10];
int heapSize = 0;

// swap function
void swap(int x, int y)
{
	int temp = heapArr[x];
	heapArr[x] = heapArr[y];
	heapArr[y] = temp;
}

// finds proper location for insertion for min heap
void siftUp(int index)
{
	if (index != 0)  // so long as we haven't reached the root yet
	{
		int parent = (index - 1) / 2;  // get the parent index
		// if parent is bigger, we need to swap
		if (heapArr[parent] > heapArr[index])
		{
			swap(parent, index);
			siftUp(parent);
		}
	}
}

// sifting down with the tail, which is now at the root
void siftDown(int index)
{
	int leftChild = 2 * index + 1;  // left child index
	int rightChild = 2 * index + 2;  // right child index
	int minimum = index;

	if (leftChild <= heapSize && rightChild <= heapSize)  // checking to see if left and right child are out of bounds for the tree (right child is usually the problem)
	{
		if (rightChild == heapSize)
			minimum = leftChild;

		// find out which one of those children is smaller
		else
		{
			if (heapArr[leftChild] < heapArr[rightChild])
				minimum = leftChild;

			else
				minimum = rightChild;
		}
	}

	// if parent value is bigger than what we have in minimum
	if (heapArr[index] > heapArr[minimum])
	{
		swap(minimum, index);  // swap minimum w/ current parent
 		siftDown(minimum);  // call sift down with whatever index of minimum is
	}
}

// insert to end of heapArr
void insert(int num)
{
	heapArr[heapSize] = num;  // insert num as last element of array
	siftUp(heapSize);  // reconstruct the min heap
	heapSize++;  // increase the size of the heapSize var
}

// delete the root (smallest) value
void deleteRoot()
{
	if (heapSize < 0)
		return;
	heapSize--;  // decrement heapSize
	swap(0, heapSize);  // swap the items at the first and last indexes
	siftDown(0);  // sift down with swapped item which is now at index 0
}

// prints the min heap level-by-level
void printLevels()
{
    for (int i = 0, level = 0; i < heapSize; level++)
    {
        cout << "Lvl " << level << ": ";
        int numNodesOnLevel = pow(2, level);  // determines num of possible nodes on ea. level (i.e. 2^0, 2^1, 2^2...)
        while (numNodesOnLevel > 0 && i < heapSize)
		{
			cout << heapArr[i++] << " ";
            numNodesOnLevel--;
		}
        cout << endl;
    }
}

// prints the initial min heap and the heap after 5 deletes
void printResults()
{
    // print initial min heap
	cout << "~~~~~~~~ Initial Min Heap ~~~~~~~~" << endl;
	printLevels();

	// implementing 5 deletes of the root (smallest number)
	for(int i = 0; i < 5; i++)
	{
		cout << "\n~~~~~~~~ Min Heap after delete #" << i+1 << " ~~~~~~~~~" << endl;
		deleteRoot();
		printLevels();
	}
}

int main()
{
	ifstream inFile("input.txt");
	for (int i = 0; i < 10 && inFile.good(); i++)  // only up to 10 items will be inserted into heapArr
    {
        int num;
		inFile >> num;  // get num input from input.txt
		insert(num);  // insert number into heapArr
    }
    inFile.close();  // close input file
	printResults();  // print initial min heap and the min heap after 5 deletes
	return 0;
}
