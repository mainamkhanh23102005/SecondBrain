// Topic 3 - Exception Handling
// Build & run:  g++ -std=c++11 main.cpp Rectangle.cpp -o demo && ./demo
#include <iostream>
#include "Rectangle.h"
using namespace std;

// The "mystery function": specific catch with auto-recovery + catch-all safety net.
void mysteryFunction(Rectangle& rect, double val) {
    try {
        rect.setWidth(val);      // may throw NegativeWidth
        rect.setLength(val);     // skipped if the line above throws
    }
    catch (Rectangle::NegativeWidth) {
        cout << "Fixing width automatically..." << endl;
        rect.setWidth(0);
        // throw;   // (would re-throw to the caller)
    }
    catch (...) {
        cout << "An unknown error occurred!" << endl;
    }
}

int main() {
    Rectangle r;

    cout << "=== Case 1: valid value (5.0) ===" << endl;
    mysteryFunction(r, 5.0);
    cout << "Width=" << r.getWidth() << " Length=" << r.getLength()
         << " Area=" << r.getArea() << endl << endl;

    cout << "=== Case 2: negative value (-3.0) ===" << endl;
    mysteryFunction(r, -3.0);
    cout << "Width=" << r.getWidth() << " Length=" << r.getLength()
         << " Area=" << r.getArea() << endl;
    return 0;
}
