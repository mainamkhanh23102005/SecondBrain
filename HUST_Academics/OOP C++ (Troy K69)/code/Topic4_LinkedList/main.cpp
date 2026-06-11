// Topic 4 - Linked List
// Build & run:  g++ -std=c++11 main.cpp NumberList.cpp -o demo && ./demo
#include <iostream>
#include "NumberList.h"
using namespace std;

int main()
{
    NumberList list;
    for (int x = 1; x <= 5; x++)
        list.insertNode(x);                 // sorted insert -> 1 2 3 4 5

    cout << "Original list (head -> tail): ";
    list.displayList();

    cout << "countNodes()  [Function 1] = " << list.countNodes() << endl;

    cout << "showReverse()[Function 2] = ";
    list.showReverse();
    cout << endl;

    list.reverseList();                      // Function 3
    cout << "After reverseList() [Function 3]: ";
    list.displayList();
    return 0;
}
