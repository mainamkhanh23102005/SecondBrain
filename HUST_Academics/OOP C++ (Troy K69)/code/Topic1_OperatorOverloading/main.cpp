// Topic 1 - Operator Overloading & Object Conversion
// All five "mystery functions" integrated into Point2D as their real operators.
// Build & run:  g++ -std=c++11 main.cpp -o demo && ./demo
#include <iostream>
#include <stdexcept>
using namespace std;

class Point2D {
private:
    int x;
    int y;
public:
    // Default + parametrised constructor
    Point2D(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    // Original: overloaded binary +  (member function)
    Point2D operator+(const Point2D& other) const {
        Point2D result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

    // Function 1 -> operator== (value equality)
    bool operator==(const Point2D& other) const {
        return (this->x == other.x && this->y == other.y);
    }

    // Function 2 -> friend operator with an int as the LEFT operand
    friend Point2D operator+(int val, const Point2D& p) {
        return Point2D(p.x + val, p.y + val);
    }

    // Function 3 -> conversion operator: Point2D -> double (squared magnitude)
    operator double() const {
        return x * x + y * y;
    }

    // Function 4 -> operator<< (stream insertion), must be a friend
    friend ostream& operator<<(ostream& os, const Point2D& p) {
        os << "Point(" << p.x << ", " << p.y << ")";
        return os;
    }

    // Function 5 -> indexed accessor returning a modifiable reference
    int& at(int index) {
        if (index == 0)      return x;
        else if (index == 1) return y;
        else throw out_of_range("Invalid index! Use 0 for X, 1 for Y.");
    }
};

int main() {
    Point2D p1(2, 3);
    Point2D p2(4, 5);

    // Original operator+
    Point2D p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;                 // uses Function 4 too

    // Function 1: operator==
    Point2D p4(2, 3);
    cout << "p1 == p2 ? " << (p1 == p2 ? "true" : "false") << endl;
    cout << "p1 == p4 ? " << (p1 == p4 ? "true" : "false") << endl;

    // Function 2: int + Point2D
    Point2D p5 = 10 + p1;
    cout << "10 + p1 = " << p5 << endl;

    // Function 3: implicit conversion to double
    double mag = p1;
    cout << "Squared magnitude of p1 = " << mag << endl;

    // Function 5: write through the returned reference
    p1.at(0) = 100;
    cout << "After p1.at(0) = 100: " << p1 << endl;

    try {
        p1.at(5) = 7;
    } catch (const out_of_range& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}
