/* John-Michael O'Brien  w1890922
   Postfix Assignment
   Prof. Sabzevary
   CISP 430
   2/10/21
*/

#include <iostream>
#include <fstream>
using namespace std;

// place at the global level
ifstream inFile("input.txt");

struct Node
{
    float value; // float called value
    Node* next; // node pointer called next
};

// feeding in a node alias called topAlias
Node* pop(Node*& topAlias) // pop returns a node pointer and takes in a node alias
{
    Node* temp = topAlias; // this is a node pointer named temp assigned to topAlias
    topAlias = topAlias->next; // assigning topAlias' next TO topAlias
    return temp;
}

// push function that returns nothing
void push(float item, Node*& topAlias) // takes in a float called item and a Node alias called topAlias
{
    Node* nn = new Node; // assigned a Node pointer nn to a new node's address, and that new Node is in the heap
    nn->value = item; // nn value assigned to item
    nn->next = topAlias; // assigning the top of the stack to nn's next
    topAlias = nn; // assign nn to top of stack
}

int main()
{
    // make the stack
    Node* stack = new Node; // we make a new Node in the heap and have stack point to that

    // to check all operators/operands in the file
    while(inFile.good())
    {
        char curr = 0; // assign 0 to the char curr
        inFile >> curr; // taking the next thing in inFile and storing it in curr (can be any kind of ASCII character)
        switch(curr)
        {
            case '+':
            {
                Node* x = pop(stack); // take item of top of stack, return the address, and store it in node pointer x
                Node* y = pop(stack); // take the now new top of stack, return the address, and store it in node pointer y
                float value = y->value + x->value; // created variable value to store addition of the values at nodes y and x
                push(value, stack); // push value onto the stack
                delete x; // give memory back to computer
                delete y; // give memory back to computer
                break;
            }
            case '-':
            {
                Node* x = pop(stack); // take item of top of stack, return the address, and store it in node pointer x
                Node* y = pop(stack); // take the now new top of stack, return the address, and store it in node pointer y
                float value = y->value - x->value; // created variable value to store subtraction of the values at nodes y and x
                push(value, stack); // push value onto the stack
                delete x; // give memory back to computer
                delete y; // give memory back to computer
                break;
            }
            case '*':
            {
                Node* x = pop(stack); // take item of top of stack, return the address, and store it in node pointer x
                Node* y = pop(stack); // take the now new top of stack, return the address, and store it in node pointer y
                float value = y->value * x->value; // created variable value to store multiplication of the values at nodes y and x
                push(value, stack); // push value onto the stack
                delete x; // give memory back to computer
                delete y; // give memory back to computer
                break;
            }
            case '/':
            {
                Node* x = pop(stack); // take item of top of stack, return the address, and store it in node pointer x
                Node* y = pop(stack); // take the now new top of stack, return the address, and store it in node pointer y
                float value = y->value / x->value; // created variable value to store division of the values at nodes y and x
                push(value, stack); // push value onto the stack
                delete x; // give memory back to computer
                delete y; // give memory back to computer
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                push(curr - '0', stack); // convert from a char to an int and push on to the stack as node, ASCII value of 0 is 48
                break;
            }
            case 0: // value of null character is 0
            {
                break;
            }
            default:
            {
                cout << "Encountered a char that is not an operator or a non-zero number.";
                cout << "It has a value of " << (int) curr << "." << endl;
            }
        }
    }
    inFile.close(); // close the file
    Node* endResult = pop(stack); // created a node pointer endResult and set it equal to what we pop off the stack
    cout << endResult->value << endl; // display endResult's value
    delete endResult; // give memory back to computer
}
