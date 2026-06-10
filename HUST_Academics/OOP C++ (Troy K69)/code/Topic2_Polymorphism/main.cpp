// Topic 2 - Inheritance & Polymorphism
// Build & run:
//   g++ -std=c++11 main.cpp GradedActivity.cpp PassFailActivity.cpp PassFailExam.cpp -o demo && ./demo
#include <iostream>
#include <iomanip>
#include "PassFailExam.h"
using namespace std;

// The "mystery function": an array of BASE pointers driving DERIVED objects.
void mysteryFunction()
{
    const int SIZE = 2;
    GradedActivity** ptrArray = new GradedActivity*[SIZE];

    ptrArray[0] = new PassFailExam(100, 25, 80.0);
    ptrArray[1] = new PassFailActivity(80.0);
    ptrArray[1]->setScore(75.0);

    cout << setprecision(1) << fixed;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "Activity " << (i + 1) << ":\n";
        cout << "The activity's numeric score is " << ptrArray[i]->getScore() << endl;
        cout << "The activity's letter grade is " << ptrArray[i]->getLetterGrade() << endl;
        cout << "---------------------------\n";
    }

    for (int i = 0; i < SIZE; i++)
        delete ptrArray[i];
    delete[] ptrArray;
}

int main()
{
    mysteryFunction();
    return 0;
}
