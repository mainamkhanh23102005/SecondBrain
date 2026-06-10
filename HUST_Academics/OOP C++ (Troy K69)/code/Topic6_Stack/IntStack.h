#ifndef INTSTACK_H
#define INTSTACK_H

class IntStack
{
private:
    int *stackArray;
    int stackSize;
    int top;          // index of the top element (-1 when empty)
public:
    IntStack(int);
    IntStack(const IntStack &);   // deep-copy copy constructor
    ~IntStack();

    void push(int);
    void pop(int &);
    bool isFull() const;
    bool isEmpty() const;

    // --- Integrated mystery functions ---
    int  countEven() const;         // Function 1
    bool removeBottom();            // Function 2
    bool removeKthFromTop(int k);   // Function 3

    void displayStack() const;      // helper for the demo (non-destructive)
};
#endif
