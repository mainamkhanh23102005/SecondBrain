CS256
|                                       | Chapter          | 14: More About | Classes        |      |
| ------------------------------------- | ---------------- | -------------- | -------------- | ---- |
|                                       | Hanoi University | of Science     | and Technology |      |
| HanoiUniversityofScienceandTechnology |                  | CS256          |                | 1/22 |

| Slide contents | are mainly | based | on the following documents: |     |
| -------------- | ---------- | ----- | --------------------------- | --- |
Tony Gaddis, Starting out with C++, Eighth Edition, Pearson, 2015
| Tony | Gaddis, Power | Points | Slides: |     |
| ---- | ------------- | ------ | ------- | --- |
https://www.umsl.edu/~antognolij/gaddis.html
| HanoiUniversityofScienceandTechnology |     |     | CS256 | 2/22 |
| ------------------------------------- | --- | --- | ----- | ---- |

| Instance  | and Static  | Members        |       |     |
| --------- | ----------- | -------------- | ----- | --- |
| Rectangle | box1, box2; |                |       |     |
| // Set    | the width   | and length for | box1. |     |
box1.setWidth(5);
box1.setLength(10);
| // Set | the width | and length for | box2. |     |
| ------ | --------- | -------------- | ----- | --- |
box2.setWidth(500);
box2.setLength(1000);
| HanoiUniversityofScienceandTechnology |     |     | CS256 | 3/22 |
| ------------------------------------- | --- | --- | ----- | ---- |

| Instance                              | and Static | Members |      |
| ------------------------------------- | ---------- | ------- | ---- |
| HanoiUniversityofScienceandTechnology |            | CS256   | 4/22 |

| Instance | and Static | Members |     |     |     |     |
| -------- | ---------- | ------- | --- | --- | --- | --- |
Instance variable: a member variable in a class. Each object has its
| own | copy. |     |     |     |     |     |
| --- | ----- | --- | --- | --- | --- | --- |
Static variable: one variable shared among all objects of a class.
| Static                                | member | function:        | can be used | to access static | member |      |
| ------------------------------------- | ------ | ---------------- | ----------- | ---------------- | ------ | ---- |
| variables;                            | can    | be called before | any objects | are defined.     |        |      |
| HanoiUniversityofScienceandTechnology |        |                  | CS256       |                  |        | 5/22 |

| Static Member | Variable: | Tree.h |     |     |
| ------------- | --------- | ------ | --- | --- |
| // Tree class |           |        |     |     |
| class Tree    | {         |        |     |     |
private:
| static | int objectCount; | // Static | member variable. |     |
| ------ | ---------------- | --------- | ---------------- | --- |
public:
| // Constructor       |                  |                 |              |     |
| -------------------- | ---------------- | --------------- | ------------ | --- |
| Tree()               | { objectCount++; | }               |              |     |
| // Accessor          | function         | for objectCount |              |     |
| int getObjectCount() |                  | const { return  | objectCount; | }   |
};
| // Definition                         | of the static | member | variable, written |      |
| ------------------------------------- | ------------- | ------ | ----------------- | ---- |
| // outside                            | the class.    |        |                   |      |
| int Tree::objectCount                 |               | = 0;   |                   |      |
| HanoiUniversityofScienceandTechnology |               | CS256  |                   | 6/22 |

| Static Member                         | Variable: | Tree.h |      |
| ------------------------------------- | --------- | ------ | ---- |
| HanoiUniversityofScienceandTechnology |           | CS256  | 7/22 |

| Static Member | Variable: | Tree.h |     |
| ------------- | --------- | ------ | --- |
Three Instances of the Tree Class, But Only One objectCount Variable
| HanoiUniversityofScienceandTechnology |     | CS256 | 8/22 |
| ------------------------------------- | --- | ----- | ---- |

| Static Member | Function |        |              |     |     |     |
| ------------- | -------- | ------ | ------------ | --- | --- | --- |
| Declared with |          | before | return type: |     |     |     |
static
| static int | getObjectCount() |     | const |     |     |     |
| ---------- | ---------------- | --- | ----- | --- | --- | --- |
{
return objectCount;
}
| Static member                         | functions                 | can | only access | static member | data. |      |
| ------------------------------------- | ------------------------- | --- | ----------- | ------------- | ----- | ---- |
| Can be called                         | independent               |     | of objects: |               |       |      |
| int num                               | = Tree::getObjectCount(); |     |             |               |       |      |
| HanoiUniversityofScienceandTechnology |                           |     | CS256       |               |       | 9/22 |

| Memberwise | Assignment |     |     |     |     |
| ---------- | ---------- | --- | --- | --- | --- |
Can use = to assign one object to another, or to initialize an object
| with an object’s       | data             |              |            |        |     |
| ---------------------- | ---------------- | ------------ | ---------- | ------ | --- |
| Copies member          | to member.       | e.g.,        |            |        |     |
| instance2              | = instance1;     | means:       |            |        |     |
| copy all member        | values from      | instance1    | and assign | to the |     |
| corresponding          | member variables | of instance2 |            |        |     |
| Use at initialization: |                  |              |            |        |     |
Rectangle r2 = r1;
| HanoiUniversityofScienceandTechnology |     | CS256 |     |     | 10/22 |
| ------------------------------------- | --- | ----- | --- | --- | ----- |

Memberwise Assignment
| HanoiUniversityofScienceandTechnology | CS256 | 11/22 |
| ------------------------------------- | ----- | ----- |

Memberwise Assignment
| HanoiUniversityofScienceandTechnology | CS256 | 12/22 |
| ------------------------------------- | ----- | ----- |

| Operator Overloading |     |     |     |
| -------------------- | --- | --- | --- |
Operators such as =, +, and others can be redefined when used with
| objects | of a class. |     |     |
| ------- | ----------- | --- | --- |
The name of the function for the overloaded operator is operator
| followed   | by the operator | symbol, e.g.:  |     |
| ---------- | --------------- | -------------- | --- |
| operator+: | to overload     | the + operator |     |
| operator=: | to overload     | the = operator |     |
Prototype goes in the declaration of the class that is overloading it.
| HanoiUniversityofScienceandTechnology |     | CS256 | 13/22 |
| ------------------------------------- | --- | ----- | ----- |

| Operator Overloading |     |     |     |     |
| -------------------- | --- | --- | --- | --- |
Prototype:
|                                       | void operator=(const | SomeClass | &rval) |       |
| ------------------------------------- | -------------------- | --------- | ------ | ----- |
| HanoiUniversityofScienceandTechnology |                      | CS256     |        | 14/22 |

| Invoking                              | an Overloaded      | Operator                    |       |
| ------------------------------------- | ------------------ | --------------------------- | ----- |
| As                                    | a member function: | object1.operator=(object2); |       |
| Conventional                          | manner:            | object1 = object2;          |       |
| HanoiUniversityofScienceandTechnology |                    | CS256                       | 15/22 |

The this Pointer
this: predefined pointer available to a class’s member functions
Always points to the instance (object) of the class whose function is
being called
Is passed as a hidden argument to all non-static member functions
Can be used to access members that may be hidden by parameters
with same name
class SomeClass {
private:
int num;
public:
void setNum(int num) {
this->num = num;
}
};
HanoiUniversityofScienceandTechnology CS256 16/22

| Notes |        | on Overloaded |           |            | Operators |                |     |               |     |     |
| ----- | ------ | ------------- | --------- | ---------- | --------- | -------------- | --- | ------------- | --- | --- |
|       | Can    | change        | meaning   |            | of an     | operator.      |     |               |     |     |
|       | Cannot | change        |           | the number |           | of operands    | of  | the operator. |     |     |
|       | Only   | certain       | operators |            | can       | be overloaded. |     |               |     |     |
|       | Cannot |               | overload: | ?:,        | ., .*,    | ::, sizeof.    |     |               |     |     |
++, -- operators overloaded differently for prefix vs. postfix notation.
|                                       | Overloaded      |     | relational |           | operators | should | return | a bool value.    |     |       |
| ------------------------------------- | --------------- | --- | ---------- | --------- | --------- | ------ | ------ | ---------------- | --- | ----- |
|                                       | Overloaded      |     | stream     | operators |           | >>, << | must   | return reference | to  |       |
|                                       | istream/ostream |     |            | objects.  |           |        |        |                  |     |       |
| HanoiUniversityofScienceandTechnology |                 |     |            |           |           | CS256  |        |                  |     | 17/22 |

| Object | Conversion           |               |                  |               |              |     |
| ------ | -------------------- | ------------- | ---------------- | ------------- | ------------ | --- |
|        | Type of              | an object     | can be converted | to            | another type |     |
|        | Automatically        | done          | for built-in     | data          | types        |     |
|        | Must write           | an operator   | function         | to perform    | conversion   |     |
|        | To convert           | an FeetInches |                  | object to     | an int:      |     |
|        | FeetInches::operator |               |                  | int() {return | feet;}       |     |
Assuming distance is a FeetInches object, allows statements like:
|                                       | int | d = distance; |     |       |     |       |
| ------------------------------------- | --- | ------------- | --- | ----- | --- | ----- |
| HanoiUniversityofScienceandTechnology |     |               |     | CS256 |     | 18/22 |

Aggregation
| class StudentInfo | {   |     |     |
| ----------------- | --- | --- | --- |
private:
| string firstName, | LastName;    |      |     |
| ----------------- | ------------ | ---- | --- |
| string address,   | city, state, | zip; |     |
};
| class Student { |     |     |     |
| --------------- | --- | --- | --- |
private:
| StudentInfo personalData; |     |     |     |
| ------------------------- | --- | --- | --- |
};
| HanoiUniversityofScienceandTechnology | CS256 |     | 19/22 |
| ------------------------------------- | ----- | --- | ----- |

Aggregation
| HanoiUniversityofScienceandTechnology | CS256 | 20/22 |
| ------------------------------------- | ----- | ----- |

Friends of Classes
Friend: a function or class that is not a member of a class, but has
| access to private | members | of the class. |     |
| ----------------- | ------- | ------------- | --- |
A friend function can be a stand-alone function or a member function
| of another class. |     |     |     |
| ----------------- | --- | --- | --- |
It is declared a friend of a class with the friend keyword in the
| function prototype.                   |     |       |       |
| ------------------------------------- | --- | ----- | ----- |
| HanoiUniversityofScienceandTechnology |     | CS256 | 21/22 |

| Friends of                            | Classes                    |                       |       |       |
| ------------------------------------- | -------------------------- | --------------------- | ----- | ----- |
| Stand-alone                           | function: friend           | void setAVal(intVal&, |       | int); |
| Member                                | function of another        | class:                |       |       |
| friend                                | void SomeClass::setNum(int |                       | num); |       |
| HanoiUniversityofScienceandTechnology |                            | CS256                 |       | 22/22 |