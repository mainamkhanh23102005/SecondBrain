#include <iostream>
#include "IntQueue.h"
using namespace std;

IntQueue::IntQueue(int s)
{
    queueArray = new int[s];
    queueSize = s;
    front = -1; rear = -1; numItems = 0;
}

IntQueue::IntQueue(const IntQueue &obj)
{
    queueArray = new int[obj.queueSize];
    queueSize = obj.queueSize;
    front = obj.front; rear = obj.rear; numItems = obj.numItems;
    for (int count = 0; count < obj.queueSize; count++)
        queueArray[count] = obj.queueArray[count];
}

IntQueue::~IntQueue() { delete [] queueArray; }

void IntQueue::enqueue(int num)
{
    if (isFull()) cout << "The queue is full.\n";
    else {
        rear = (rear + 1) % queueSize;   // advance rear with wrap-around
        queueArray[rear] = num;
        numItems++;
    }
}

void IntQueue::dequeue(int &num)
{
    if (isEmpty()) cout << "The queue is empty.\n";
    else {
        front = (front + 1) % queueSize; // advance front with wrap-around
        num = queueArray[front];
        numItems--;
    }
}

bool IntQueue::isEmpty() const { return numItems == 0; }
bool IntQueue::isFull()  const { return numItems == queueSize; }

void IntQueue::clear()
{
    front = queueSize - 1;
    rear  = queueSize - 1;
    numItems = 0;
}

// ===== Integrated mystery functions =====
int IntQueue::countOccurrences(int target) const
{
    int count = 0;
    for (int i = 0; i < numItems; i++) {
        int index = (front + 1 + i) % queueSize;
        if (queueArray[index] == target) count++;
    }
    return count;
}

void IntQueue::reverseQueue()
{
    for (int i = 0; i < numItems / 2; i++) {
        int leftIndex  = (front + 1 + i) % queueSize;
        int rightIndex = (front + 1 + numItems - 1 - i) % queueSize;
        int temp = queueArray[leftIndex];
        queueArray[leftIndex]  = queueArray[rightIndex];
        queueArray[rightIndex] = temp;
    }
}

bool IntQueue::enqueueFront(int num)
{
    if (isFull()) return false;
    queueArray[front] = num;                       // write at current front slot
    front = (front - 1 + queueSize) % queueSize;   // move front BACKWARD safely
    numItems++;
    return true;
}

void IntQueue::displayQueue() const
{
    cout << "[ ";
    for (int i = 0; i < numItems; i++)
        cout << queueArray[(front + 1 + i) % queueSize] << " ";
    cout << "]" << endl;
}
