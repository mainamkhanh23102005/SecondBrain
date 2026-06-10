// Topic 5 - Queue (circular array)
// Build & run:  g++ -std=c++11 main.cpp IntQueue.cpp -o demo && ./demo
#include <iostream>
#include "IntQueue.h"
using namespace std;

int main()
{
    IntQueue q(5);
    int dummy;

    q.enqueue(10); q.enqueue(20); q.enqueue(30); q.enqueue(20);
    cout << "After enqueue 10,20,30,20 (front->rear): "; q.displayQueue();

    q.dequeue(dummy);   // removes 10, so front becomes a valid index
    cout << "After dequeue (removed " << dummy << "): "; q.displayQueue();

    cout << "countOccurrences(20) [Function 1] = " << q.countOccurrences(20) << endl;

    q.enqueueFront(99); // Function 3
    cout << "After enqueueFront(99) [Function 3]: "; q.displayQueue();

    q.reverseQueue();   // Function 2
    cout << "After reverseQueue()  [Function 2]: "; q.displayQueue();
    return 0;
}
