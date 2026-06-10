#include <iostream>
#include "IntStack.h"
using namespace std;

IntStack::IntStack(int size)
{
    stackArray = new int[size];
    stackSize = size;
    top = -1;
}

IntStack::IntStack(const IntStack &obj)
{
    stackArray = (obj.stackSize > 0) ? new int[obj.stackSize] : nullptr;
    stackSize = obj.stackSize;
    for (int count = 0; count < stackSize; count++)
        stackArray[count] = obj.stackArray[count];
    top = obj.top;
}

IntStack::~IntStack() { delete [] stackArray; }

void IntStack::push(int num)
{
    if (isFull()) cout << "The stack is full.\n";
    else { top++; stackArray[top] = num; }
}

void IntStack::pop(int &num)
{
    if (isEmpty()) cout << "The stack is empty.\n";
    else { num = stackArray[top]; top--; }
}

bool IntStack::isFull()  const { return top == stackSize - 1; }
bool IntStack::isEmpty() const { return top == -1; }

// ===== Integrated mystery functions =====
int IntStack::countEven() const
{
    int count = 0;
    for (int i = 0; i <= top; i++)
        if (stackArray[i] % 2 == 0) count++;
    return count;
}

bool IntStack::removeBottom()
{
    if (isEmpty()) return false;
    for (int i = 0; i < top; i++)
        stackArray[i] = stackArray[i + 1];   // shift everything down
    top--;
    return true;
}

bool IntStack::removeKthFromTop(int k)
{
    if (k < 1 || k > top + 1) return false;
    int targetIndex = top - k + 1;           // "k from top" -> array index
    for (int i = targetIndex; i < top; i++)
        stackArray[i] = stackArray[i + 1];
    top--;
    return true;
}

void IntStack::displayStack() const
{
    cout << "bottom [ ";
    for (int i = 0; i <= top; i++)
        cout << stackArray[i] << " ";
    cout << "] top" << endl;
}
