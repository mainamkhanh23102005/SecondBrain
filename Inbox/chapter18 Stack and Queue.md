CS256
|                                       | Chapter          | 17: Stacks and | Queues         |      |
| ------------------------------------- | ---------------- | -------------- | -------------- | ---- |
|                                       | Hanoi University | of Science     | and Technology |      |
| HanoiUniversityofScienceandTechnology |                  | CS256          |                | 1/21 |

| Slide contents | are mainly | based | on the following documents: |     |
| -------------- | ---------- | ----- | --------------------------- | --- |
Tony Gaddis, Starting out with C++, Eighth Edition, Pearson, 2015
| Tony | Gaddis, Power | Points | Slides: |     |
| ---- | ------------- | ------ | ------- | --- |
https://www.umsl.edu/~antognolij/gaddis.html
| HanoiUniversityofScienceandTechnology |     |     | CS256 | 2/21 |
| ------------------------------------- | --- | --- | ----- | ---- |

| Introduction | to Stack       |                 |           |     |
| ------------ | -------------- | --------------- | --------- | --- |
| Stack: a     | LIFO (last in, | first out) data | structure |     |
Implementation:
| – static:                             | fixed size, implemented | as          | array          |      |
| ------------------------------------- | ----------------------- | ----------- | -------------- | ---- |
| – dynamic:                            | variable size,          | implemented | as linked list |      |
| HanoiUniversityofScienceandTechnology |                         | CS256       |                | 3/21 |

| Stack Operations | and | Functions |     |     |
| ---------------- | --- | --------- | --- | --- |
Operations:
| – push:       | add a value onto | the top of   | the stack    |     |
| ------------- | ---------------- | ------------ | ------------ | --- |
| – pop: remove | a value          | from the top | of the stack |     |
Functions:
– isFull: true if the stack is currently full, i.e., has no more space to
| hold additional                       | elements    |                 |                      |      |
| ------------------------------------- | ----------- | --------------- | -------------------- | ---- |
| – isEmpty:                            | true if the | stack currently | contains no elements |      |
| HanoiUniversityofScienceandTechnology |             | CS256           |                      | 4/21 |

| Stack Operations | and Functions |     |     |     |     |
| ---------------- | ------------- | --- | --- | --- | --- |
#ifndef INTSTACK_H
#define INTSTACK_H
| class IntStack { |     |     |     |     |     |
| ---------------- | --- | --- | --- | --- | --- |
private:
| int *stackArray; | //  | Pointer   | to the | stack array      |     |
| ---------------- | --- | --------- | ------ | ---------------- | --- |
| int stackSize;   | //  | The stack | size   |                  |     |
| int top;         | //  | Indicates | the    | top of the stack |     |
public:
| IntStack(int);      | // Constructor |     |         |             |     |
| ------------------- | -------------- | --- | ------- | ----------- | --- |
| IntStack(const      | IntStack       | &); | // Copy | constructor |     |
| ~IntStack();        | // Destructor  |     |         |             |     |
| // Stack operations |                |     |         |             |     |
void push(int);
| void pop(int   | &);    |     |     |     |     |
| -------------- | ------ | --- | --- | --- | --- |
| bool isFull()  | const; |     |     |     |     |
| bool isEmpty() | const; |     |     |     |     |
};
#endif
| HanoiUniversityofScienceandTechnology |     | CS256 |     |     | 5/21 |
| ------------------------------------- | --- | ----- | --- | --- | ---- |

| Stack Operations and Functions        |       |      |
| ------------------------------------- | ----- | ---- |
| HanoiUniversityofScienceandTechnology | CS256 | 6/21 |

| Implementing          | Other Stack | Operations        |       |     |
| --------------------- | ----------- | ----------------- | ----- | --- |
| // Specification      | file        | for the MathStack | class |     |
| #ifndef MATHSTACK_H   |             |                   |       |     |
| #define MATHSTACK_H   |             |                   |       |     |
| #include "IntStack.h" |             |                   |       |     |
| class MathStack       | : public    | IntStack          |       |     |
{
public:
// Constructor
| MathStack(int | s) :       | IntStack(s) | {}  |     |
| ------------- | ---------- | ----------- | --- | --- |
| // MathStack  | operations |             |     |     |
| void add();   |            |             |     |     |
| void sub();   |            |             |     |     |
};
#endif
| HanoiUniversityofScienceandTechnology |     | CS256 |     | 7/21 |
| ------------------------------------- | --- | ----- | --- | ---- |

| Implementing |     |               | Other | Stack Operations |     |     |     |
| ------------ | --- | ------------- | ----- | ---------------- | --- | --- | --- |
| #include     |     | "MathStack.h" |       |                  |     |     |     |
//***********************************************
| //  | Member | function | add.       | add pops       |            | *   |     |
| --- | ------ | -------- | ---------- | -------------- | ---------- | --- | --- |
| //  | the    | first    | two values | off the stack  | and        | *   |     |
| //  | adds   | them.    | The sum    | is pushed onto | the stack. | *   |     |
//***********************************************
void MathStack::add()
{
|     | int | num,    | sum;  |                |            |     |     |
| --- | --- | ------- | ----- | -------------- | ---------- | --- | --- |
|     | //  | Pop the | first | two values off | the stack. |     |     |
pop(sum);
pop(num);
|     | sum        | += num; | // Add  | the two values, | store      | in sum. |     |
| --- | ---------- | ------- | ------- | --------------- | ---------- | ------- | --- |
|     | push(sum); |         | // Push | sum back onto   | the stack. |         |     |
}
| HanoiUniversityofScienceandTechnology |     |     |     | CS256 |     |     | 8/21 |
| ------------------------------------- | --- | --- | --- | ----- | --- | --- | ---- |

| Implementing |     |     | Other | Stack |     | Operations |     |     |     |
| ------------ | --- | --- | ----- | ----- | --- | ---------- | --- | --- | --- |
//***********************************************
| //  | Member | function |        | sub.           | sub | pops   | the    | *   |     |
| --- | ------ | -------- | ------ | -------------- | --- | ------ | ------ | --- | --- |
| //  | first  | two      | values | off            | the | stack. | The    | *   |     |
| //  | second | value    |        | is subtracted  |     | from   | the    | *   |     |
| //  | first  | value.   |        | The difference |     | is     | pushed | *   |     |
| //  | onto   | the      | stack. |                |     |        |        | *   |     |
//***********************************************
void MathStack::sub()
{
|     | int | num, | diff;     |     |        |     |                |     |     |
| --- | --- | ---- | --------- | --- | ------ | --- | -------------- | --- | --- |
|     | //  | Pop  | the first | two | values |     | off the stack. |     |     |
pop(diff);
pop(num);
|     | diff        | -=  | num; | // Subtract |      | num  | from diff.      |     |     |
| --- | ----------- | --- | ---- | ----------- | ---- | ---- | --------------- | --- | --- |
|     | push(diff); |     |      | // Push     | diff | back | onto the stack. |     |     |
}
| HanoiUniversityofScienceandTechnology |     |     |     |     |     | CS256 |     |     | 9/21 |
| ------------------------------------- | --- | --- | --- | --- | --- | ----- | --- | --- | ---- |

Stack Container in C++
| HanoiUniversityofScienceandTechnology | CS256 | 10/21 |
| ------------------------------------- | ----- | ----- |

| Stack Container     | in C++       |         |       |     |     |
| ------------------- | ------------ | ------- | ----- | --- | --- |
| // This program     | demonstrates | the STL | stack |     |     |
| // container        | adapter.     |         |       |     |     |
| #include <iostream> |              |         |       |     |     |
| #include <vector>   |              |         |       |     |     |
| #include <stack>    |              |         |       |     |     |
| using namespace     | std;         |         |       |     |     |
int main()
{
| const int                             | MAX = 8;         | // Max value    | to store | in the stack |       |
| ------------------------------------- | ---------------- | --------------- | -------- | ------------ | ----- |
| int count;                            |                  | // Loop counter |          |              |       |
| // Define                             | an STL           | stack           |          |              |       |
| stack<                                | int, vector<int> | > iStack;       |          |              |       |
| HanoiUniversityofScienceandTechnology |                  | CS256           |          |              | 11/21 |

| Stack | Container  | in C++      |     |        |          |     |     |
| ----- | ---------- | ----------- | --- | ------ | -------- | --- | --- |
|       | // Push    | values onto | the | stack. |          |     |     |
|       | for (count | = 2; count  |     | < MAX; | count += | 2)  |     |
{
|     | cout | << "Pushing | "   | << count | << endl; |     |     |
| --- | ---- | ----------- | --- | -------- | -------- | --- | --- |
iStack.push(count);
}
|     | // Display | the size      | of     | the stack. |          |     |     |
| --- | ---------- | ------------- | ------ | ---------- | -------- | --- | --- |
|     | cout <<    | "The size     | of the | stack      | is ";    |     |     |
|     | cout <<    | iStack.size() |        | << endl;   |          |     |     |
|     | // Pop the | values        | off    | the stack. |          |     |     |
|     | for (count | = 2; count    |        | < MAX;     | count += | 2)  |     |
{
|     | cout | << "Popping | "   | << iStack.top() |     | << endl; |     |
| --- | ---- | ----------- | --- | --------------- | --- | -------- | --- |
iStack.pop();
}
|     | return 0; |     |     |     |     |     |     |
| --- | --------- | --- | --- | --- | --- | --- | --- |
}
| HanoiUniversityofScienceandTechnology |     |     |     | CS256 |     |     | 12/21 |
| ------------------------------------- | --- | --- | --- | ----- | --- | --- | ----- |

| Introduction | to Queue      |                     |           |     |
| ------------ | ------------- | ------------------- | --------- | --- |
| Queue:       | a FIFO (first | in, first out) data | structure |     |
Implementation:
| – static:                             | fixed size, implemented | as          | array          |       |
| ------------------------------------- | ----------------------- | ----------- | -------------- | ----- |
| – dynamic:                            | variable size,          | implemented | as linked list |       |
| HanoiUniversityofScienceandTechnology |                         | CS256       |                | 13/21 |

| Queue Locations                       | and               | Operations  |                      |       |
| ------------------------------------- | ----------------- | ----------- | -------------------- | ----- |
| rear: position                        | where elements    | are         | added                |       |
| front: position                       | from which        | elements    | are removed          |       |
| enqueue:                              | add an element    | to the rear | of the queue         |       |
| dequeue:                              | remove an element | from        | the front of a queue |       |
| HanoiUniversityofScienceandTechnology |                   | CS256       |                      | 14/21 |

Enqueue
| HanoiUniversityofScienceandTechnology | CS256 | 15/21 |
| ------------------------------------- | ----- | ----- |

Dequeue
| HanoiUniversityofScienceandTechnology | CS256 | 16/21 |
| ------------------------------------- | ----- | ----- |

Queue with Circular Array
| HanoiUniversityofScienceandTechnology | CS256 | 17/21 |
| ------------------------------------- | ----- | ----- |

IntQueue class
#ifndef INTQUEUE_H
#define INTQUEUE_H
class IntQueue
{
private:
| int *queueArray; | //  | Points    | to the queue | array       |     |
| ---------------- | --- | --------- | ------------ | ----------- | --- |
| int queueSize;   | //  | The queue | size         |             |     |
| int front;       | //  | Subscript | of the       | queue front |     |
| int rear;        | //  | Subscript | of the       | queue rear  |     |
| int numItems;    | //  | Number    | of items in  | the queue   |     |
public:
// Constructor
IntQueue(int);
| // Copy constructor                   |          |       |     |     |       |
| ------------------------------------- | -------- | ----- | --- | --- | ----- |
| IntQueue(const                        | IntQueue | &);   |     |     |       |
| HanoiUniversityofScienceandTechnology |          | CS256 |     |     | 18/21 |

IntQueue class
// Destructor
~IntQueue();
// Queue operations
void enqueue(int);
void dequeue(int &);
bool isEmpty() const;
bool isFull() const;
void clear();
};
#endif
HanoiUniversityofScienceandTechnology CS256 19/21

deque and queue Containers
| HanoiUniversityofScienceandTechnology | CS256 | 20/21 |
| ------------------------------------- | ----- | ----- |

| deque and queue | Containers |     |     |     |
| --------------- | ---------- | --- | --- | --- |
Given a string containing just the characters (, ), {,}, [, and ],
determine if the input string is valid. Example: ”{[()]}” is valid, but
| ”{[(])}” is invalid. |                |            |                 |     |
| -------------------- | -------------- | ---------- | --------------- | --- |
| Given a positive     | integer, print | its binary | representation. |     |
Given a string. If two identical letters are adjacent, they cancel each
other out. Return the final string after all possible cancellations.
(Example: ”abbaca” → cancels bb to ”aaca” → cancels aa to ”ca”).
Given a string of characters. Check if the string is a Palindrome
| (reads the same                       | forwards and | backwards). | Example: ”RADAR” |       |
| ------------------------------------- | ------------ | ----------- | ---------------- | ----- |
| HanoiUniversityofScienceandTechnology |              | CS256       |                  | 21/21 |