# Topic 1 — Operator Overloading & Object Conversion

**Questions source:** `1 - Operator Overloading, Object Conversion/Questions.txt`
**Runnable code:** `code/Topic1_OperatorOverloading/main.cpp`
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), §14.5 Operator Overloading, §14.6 Object Conversion
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the ideas of Operator Overloading and Object Conversion in OOP C++

**Operator overloading** — *"C++ allows you to redefine how standard operators work when used with class objects"* (Gaddis §14.5). C++ already knows how to apply operators like `+`, `==`, or `<<` to **primitive types**, but it does **not** know what they mean for a class you define. Operator overloading lets you supply that meaning by writing a special member (or friend) function whose name is the keyword `operator` followed by the symbol — e.g. `operator+`. That function then runs automatically every time the operator is used with an object of the class, so your class behaves as naturally as a built-in type (`p3 = p1 + p2;` instead of `p3 = p1.add(p2);`).

**What "the operator runs a function" really means** — the compiler rewrites the operator into a function call:

```
   You write:            Compiler calls:                Who is the left operand?
 ─────────────────   ────────────────────────────   ───────────────────────────
   p1 + p2           p1.operator+(p2)                p1  (a Point2D)  → MEMBER ok
   10 + p1           operator+(10, p1)               10  (an int)     → must be FRIEND
   cout << p1        operator<<(cout, p1)            cout (an ostream)→ must be FRIEND
   p1 == p2          p1.operator==(p2)               p1  (a Point2D)  → MEMBER ok
```

Key rules from the textbook:
- You **cannot create new operators** and you **cannot change the number of operands** an operator takes (its arity), nor its precedence/associativity.
- At least one operand must be a **class object** (you cannot redefine `int + int`).
- Whether you write it as a **member** or a **friend** depends on the *left operand* (see the table above, and Q2, Functions 2 and 4).

**Object conversion** — *"Special operator functions may be written to convert a class object to any other type"* (Gaddis §14.6). With built-in types, conversions happen automatically (e.g. assigning an `int` to a `double`). For your own class you teach the compiler how to convert your object into another type by writing a **conversion operator** of the form `operator TargetType() const`. After that, the compiler can implicitly (or explicitly) turn your object into that type — e.g. turning a `Point2D` into a `double`.

**Rules from the lecturer's "Notes on Overloaded Operators" slide (Ch.14):**
- *"Can change the meaning of an operator, but cannot change the number of operands."*
- *"Only certain operators can be overloaded — cannot overload `?:`, `.`, `.*`, `::`, `sizeof`."*
- *"`++`/`--` are overloaded differently for prefix vs. postfix."*
- *"Overloaded **relational** operators should return a `bool`"* → that is why Function 1 (`operator==`) returns `bool`.
- *"Overloaded **stream** operators `>>`, `<<` must return a reference to the istream/ostream object"* → that is why Function 4 returns `ostream&`.

**Object Conversion — the lecturer's form (Ch.14 slide):** write a conversion operator named `operator TargetType()`. The slide's example converts a `FeetInches` object to an `int`:
```cpp
FeetInches::operator int() { return feet; }   // then:  int d = distance;  // distance is a FeetInches
```
Our Function 3, `operator double()`, is the same pattern converting a `Point2D` to a `double`.

> **Why it matters:** both features make user-defined types *first-class citizens* — they read and behave like the language's own types, which makes code more intuitive and less error-prone.

---

## Q2. Explain the primary purpose of the following functions

| # | Given code | What it really is | Purpose |
|---|---|---|---|
| 1 | `bool f(const Point2D& other)` → `x==other.x && y==other.y` | **`operator==`** | Tests two points for **value equality** (same x AND same y) |
| 2 | `friend Point2D f(int val, const Point2D& p)` | **friend `operator+(int, Point2D)`** | Adds a scalar `val` to **both** coordinates. It must be a **friend** because the **left operand is an `int`**, not a `Point2D`, so it cannot be a member |
| 3 | `operator double() const` → `x*x + y*y` | **Conversion operator** (`Point2D` → `double`) | Converts the point to a `double` equal to its **squared magnitude** $x^2+y^2$ (squared distance from origin; squared to avoid a `sqrt`) |
| 4 | `friend ostream& f(ostream& os, const Point2D& p)` | **`operator<<`** (stream insertion) | Lets you write `cout << p;`. Returns `ostream&` so calls can be **chained** (`cout << a << b`). Must be a friend because the left operand is `ostream` |
| 5 | `int& f(int index)` returning a **reference** | **Indexed accessor** (like `operator[]`) | Returns a **modifiable reference** to `x` (index 0) or `y` (index 1) so the caller can both read *and write* (`p.at(0) = 100;`); throws `out_of_range` for any other index |

**Why Function 5 returns a *reference* (`int&`) — it becomes an lvalue you can assign to:**

```
   p1.at(0) = 100;

   ┌─ p1 ──────────┐
   │  x:  3  ◀──────┼─────  at(0) returns a REFERENCE to x (not a copy),
   │  y:  3        │        so "= 100" writes straight into p1.x
   └───────────────┘

   returns int  (a copy)   → p1.at(0) = 100;  ✗ assigns to a temporary, error
   returns int& (an alias) → p1.at(0) = 100;  ✓ modifies the real member
```

> **The single most important idea here:** a member operator's left operand is always the object (`*this`). When the left operand is *not* your class — an `int` (Function 2) or an `ostream` (Function 4) — the operator **must be a non-member**, declared `friend` so it can still reach the private `x`/`y`.

---

## Q3. Integrate these functions into the project and run a demo

**Full runnable file:** `code/Topic1_OperatorOverloading/main.cpp`
**Build & run:**
```bash
g++ -std=c++11 main.cpp -o demo && ./demo
```

The five functions are integrated as their real operators: Function 1 → `operator==`, Function 2 → `friend operator+(int, Point2D)`, Function 3 → `operator double()`, Function 4 → `operator<<`, Function 5 → `at(int)`.

```cpp
int main() {
    Point2D p1(2, 3), p2(4, 5);

    Point2D p3 = p1 + p2;                                   // original operator+
    cout << "p1 + p2 = " << p3 << endl;                     // Function 4

    Point2D p4(2, 3);
    cout << "p1 == p2 ? " << (p1 == p2 ? "true":"false") << endl;  // Function 1
    cout << "p1 == p4 ? " << (p1 == p4 ? "true":"false") << endl;

    Point2D p5 = 10 + p1;                                   // Function 2 (int on the left)
    cout << "10 + p1 = " << p5 << endl;

    double mag = p1;                                        // Function 3 (implicit conversion)
    cout << "Squared magnitude of p1 = " << mag << endl;

    p1.at(0) = 100;                                         // Function 5 (write via reference)
    cout << "After p1.at(0) = 100: " << p1 << endl;

    try { p1.at(5) = 7; }
    catch (const out_of_range& e) { cout << "Caught exception: " << e.what() << endl; }
    return 0;
}
```

**✅ Verified output:**
```
p1 + p2 = Point(6, 8)
p1 == p2 ? false
p1 == p4 ? true
10 + p1 = Point(12, 13)
Squared magnitude of p1 = 13
After p1.at(0) = 100: Point(100, 3)
Caught exception: Invalid index! Use 0 for X, 1 for Y.
```

Check for Function 3: `p1 = (2,3)` → $2^2 + 3^2 = 4 + 9 = 13$. ✔

---

**Previous**: [[C++ OOP - Hub]] · **Next**: [[Topic 2 - Inheritance, Polymorphism]] · **Hub**: [[C++ OOP - Hub]]
