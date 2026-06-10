# Exam Study — Topic 1: Operator Overloading & Object Conversion

**Source:** `CK-20252-Troy K69/1 - Operator Overloading, Object Conversion/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #oop #operator-overloading #conversion #exam

---

## 🎤 Professor's Opening (deliver this first)

> "Operator overloading is a form of **compile-time polymorphism** that lets me redefine what built-in operators like `+`, `==`, or `<<` mean when their operands are objects of my own class. The compiler already knows `2 + 3`; it does *not* know `point1 + point2`. By writing a function named `operator+`, I teach the compiler how to add two `Point2D` objects, so my class behaves as naturally as a built-in type. **Object conversion** is the closely related idea of teaching the compiler how to turn my object into another type — for example, turning a `Point2D` into a `double` — using a conversion operator. Together they make user-defined types *first-class citizens* of the language."

---

## 1. Executive Summary

This topic is about making a custom class (`Point2D`) feel like a native type. We do this with two mechanisms:

- **Operator overloading:** defining functions named `operator<symbol>` so that operators (`+`, `==`, `<<`, `[]`, etc.) work on our objects.
- **Object (type) conversion:** defining a **conversion operator** `operator T()` so the compiler can implicitly or explicitly convert our object into another type `T`.

The exam gives five "mystery functions" — the task is to recognise each as a standard operator/idiom and explain its purpose.

---

## 2. Zero-Loss Extraction

### 2.1 The original class (as given)

```cpp
class Point2D {
private:
    int x;
    int y;
public:
    Point2D(int x = 0, int y = 0) {   // default + parametrised constructor in one
        this->x = x;
        this->y = y;
    }

    // Overloaded binary +  : member function
    Point2D operator+(const Point2D& other) {
        Point2D result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

    void print() {
        cout << "Coordinates: (" << x << ", " << y << ")" << endl;
    }
};
```

### 2.2 Decoding the five mystery functions

| # | Code role | What it really is | Purpose |
|---|---|---|---|
| 1 | `bool mysteryFunction1(const Point2D& other)` returning `x==other.x && y==other.y` | **`operator==`** (equality comparison) | Compares two points for *value equality* (same x AND same y) |
| 2 | `friend Point2D mysteryFunction2(int val, const Point2D& p)` | **Friend binary operator with a non-object left operand** (e.g. `operator+(int, Point2D)`) | Adds a scalar `val` to *both* coordinates; being a `friend` lets the **left** operand be an `int` |
| 3 | `operator double() const` | **Conversion operator** (object → `double`) | Converts the point to a `double` equal to $x^2 + y^2$ (its squared magnitude / distance² from origin) |
| 4 | `friend ostream& mysteryFunction4(ostream&, const Point2D&)` | **`operator<<`** (stream insertion) | Lets you write `cout << p;` to print `Point(x, y)` |
| 5 | `int& mysteryFunction5(int index)` returning a **reference** | **`operator[]`-style indexed accessor** | Returns a *modifiable reference* to `x` (index 0) or `y` (index 1); throws `out_of_range` otherwise |

> [!note] The mathematical meaning of Function 3
> `operator double()` returns $x^2 + y^2$. This is the **squared Euclidean distance** from the origin, $\lVert p \rVert^2$. They return the *square* (not $\sqrt{x^2+y^2}$) to avoid the cost and floating-point error of `sqrt` — a common optimisation when you only need to *compare* magnitudes.

### 2.3 Integrated, compiled demo

All five functions were integrated as their real operators and compiled with `g++ -std=c++11`. Function 1 → `operator==`, Function 2 → `friend addScalar`, Function 3 → `operator double()`, Function 4 → `operator<<`, Function 5 → `at(int)` (reference accessor).

```cpp
int main() {
    Point2D p1(2, 3);
    Point2D p2(4, 5);

    Point2D p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;

    cout << "p1 == p2 ? " << (p1 == p2 ? "true" : "false") << endl;
    Point2D p4(2, 3);
    cout << "p1 == p4 ? " << (p1 == p4 ? "true" : "false") << endl;

    Point2D p5 = addScalar(10, p1);          // friend, int on the left
    cout << "addScalar(10, p1) = " << p5 << endl;

    double mag = p1;                          // implicit conversion via operator double()
    cout << "Squared magnitude of p1 = " << mag << endl;

    p1.at(0) = 100;                           // modify x through a returned reference
    cout << "After p1.at(0) = 100: " << p1 << endl;

    try {
        p1.at(5) = 7;
    } catch (const out_of_range& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}
```

**✅ Verified actual output:**

```
p1 + p2 = Point(6, 8)
p1 == p2 ? false
p1 == p4 ? true
addScalar(10, p1) = Point(12, 13)
Squared magnitude of p1 = 13
After p1.at(0) = 100: Point(100, 3)
Caught exception: Invalid index! Use 0 for X, 1 for Y.
```

(Check: `p1=(2,3)` → squared magnitude $= 2^2 + 3^2 = 4 + 9 = 13$. ✔)

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 Member function vs. friend function — the key design decision

The single most-tested idea here is **when an operator should be a member and when it should be a `friend` (non-member)**.

- A **member** operator's *left operand is always `*this`* (the object). So `p1 + p2` calls `p1.operator+(p2)`. This works when the left operand is your class.
- But what about `10 + p1` or `cout << p1`? Here the **left operand is not a `Point2D`** — it is an `int` or an `ostream`. You cannot add a member function to `int` or to `ostream`. The solution is a **non-member function**, declared `friend` so it can still touch the private members.

> [!important] This is the reason Function 2 and Function 4 are `friend`s.
> `operator<<` *must* be a non-member because the left operand is `std::ostream` (owned by the standard library), and `operator+(int, Point2D)` *must* be a non-member because the left operand is an `int`. Being a `friend` is just an access shortcut so it can read `p.x` and `p.y` directly.

### 3.2 Why `operator<<` returns `ostream&`

It returns the stream **by reference** so that calls can be **chained**: `cout << p1 << p2 << endl;`. Each `<<` returns the same `cout`, which becomes the left operand of the next `<<`. Returning by value would copy the stream (illegal) and break chaining.

### 3.3 Why Function 5 returns `int&` (a reference) — and why it is dangerous

Returning `int&` makes the call an **lvalue** — something you can assign *to*. That is exactly how `vector::operator[]` works: `v[0] = 5;`. Our demo does `p1.at(0) = 100;` and it modifies the real `x`.

> [!warning] Pitfall: returning a reference to a local would be a disaster
> Returning a reference is only safe because `x` and `y` are **member variables** that outlive the function call. If you ever return a reference to a **local variable**, that variable is destroyed when the function returns, leaving a **dangling reference** — undefined behaviour. Examiners love this trap.

### 3.4 Implicit conversion: power and danger

`double mag = p1;` silently invoked `operator double()`. This is convenient but can cause **surprising silent conversions** (e.g. `if (p1) ...` might compile by accident). Modern C++ lets you mark conversions `explicit` to require an explicit cast `static_cast<double>(p1)`. Mention this to show depth.

### 3.5 Operators you should *not* overload, and rules you cannot break

- You **cannot** invent new operators (e.g. `**`) or change **arity/precedence/associativity**.
- At least one operand must be a **user-defined type** — you cannot redefine `int + int`.
- `::`, `.`, `.*`, `?:`, and `sizeof` **cannot** be overloaded.

---

## 4. Key Takeaways & Next Steps

1. **Operator overloading = teaching the compiler what an operator means for your type.** It is syntactic sugar over an ordinary function named `operator<symbol>`.
2. **Member vs friend** is decided by the *left operand*: if it isn't your class, the operator must be a non-member (often a `friend`).
3. **Conversion operator `operator T()`** turns your object into another type; consider `explicit` to avoid silent surprises.
4. **Return `ostream&` for chaining** and **return references only to long-lived members**.
5. The squared-magnitude trick ($x^2+y^2$ without `sqrt`) is a real-world efficiency choice.

> [!question] Stretch questions to rehearse
> 1. Why is it better to overload `operator==` *and* derive `operator!=` from it, rather than writing both independently? (Answer: single source of truth → `return !(a==b);` avoids inconsistency.)
> 2. Should `operator+` be `const`? (Yes — it shouldn't modify its operands; mark it `Point2D operator+(const Point2D& other) const`.)

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. What is the difference between overloading an operator as a member vs. a friend?**
A member function takes the left operand implicitly as `*this`, so it only works when the left operand is an object of the class. A friend (non-member) function takes *both* operands explicitly, which is required when the left operand is a different type such as `int` or `ostream`. Friendship just grants access to private members.

**Q2. What does `operator double() const` do, and why is it `const`?**
It is a user-defined conversion operator that lets the compiler convert a `Point2D` into a `double` (here, $x^2+y^2$). It is `const` because computing the conversion doesn't change the object, so it should be callable on `const` objects too.

**Q3. Why does the indexed accessor return `int&` instead of `int`?**
Returning a reference makes the expression an lvalue, so the caller can both read *and write* the coordinate: `p.at(0) = 100;`. Returning by value would only allow reading.

**Q4. What happens with an invalid index?**
It `throw`s `std::out_of_range`, which links this topic to exception handling (Topic 3). The caller must wrap the access in a `try/catch`.

**Q5. Can you overload `operator=` and why might you need to?**
Yes — the copy-assignment operator. You need a custom one whenever the class manages a resource (like a raw pointer) to perform a *deep* copy and avoid two objects sharing/double-freeing the same memory (the Rule of Three).

---

## Graph View Links

**Previous**: [[C++ OOP - Hub]]
**Next**: [[Exam Study - Topic 2 (Inheritance, Polymorphism)]]
**Hub**: [[C++ OOP - Hub]]
