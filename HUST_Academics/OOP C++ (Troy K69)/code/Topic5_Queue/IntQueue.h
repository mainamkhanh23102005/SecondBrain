#ifndef INTQUEUE_H
#define INTQUEUE_H

class IntQueue
{
private:
    int *queueArray;
    int queueSize;
    int front;        // index ONE BEFORE the first element (starts at -1)
    int rear;         // index of the last element
    int numItems;     // current count (removes full/empty ambiguity)
public:
    IntQueue(int);
    IntQueue(const IntQueue &);   // deep-copy copy constructor
    ~IntQueue();

    void enqueue(int);
    void dequeue(int &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();

    // --- Integrated mystery functions ---
    int  countOccurrences(int target) const;  // Function 1
    void reverseQueue();                        // Function 2
    bool enqueueFront(int num);                 // Function 3

    void displayQueue() const;                  // helper for the demo (non-destructive)
};
#endif
