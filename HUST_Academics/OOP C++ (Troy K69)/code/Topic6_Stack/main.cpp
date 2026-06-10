// Topic 6 - Stack (array-based)
// Build & run:  g++ -std=c++11 main.cpp IntStack.cpp -o demo && ./demo
#include <iostream>
#include "IntStack.h"
using namespace std;

int main()
{
    IntStack s(10);
    s.push(5); s.push(10); s.push(15); s.push(20); s.push(25);
    cout << "Initial stack: "; s.displayStack();

    cout << "countEven() [Function 1] = " << s.countEven() << endl;

    s.removeBottom();        // Function 2 -> removes 5
    cout << "After removeBottom() [Function 2]: "; s.displayStack();

    s.removeKthFromTop(2);   // Function 3 -> removes 2nd from top (20)
    cout << "After removeKthFromTop(2) [Function 3]: "; s.displayStack();
    return 0;
}
