# Topic 1 — Operator Overloading & Object Conversion (Code Walkthrough)

**File:** `main.cpp` (single file — the whole demo is self-contained)
**Build & run:** `g++ -std=c++11 main.cpp -o demo && ./demo`

---

## The class: `Point2D`

A 2-D point with two private members:

| Member | Meaning |
|---|---|
| `int x` | the x-coordinate |
| `int y` | the y-coordinate |

Both are **private**, so the only way to touch them from outside is through the public functions below. The whole point of this topic is making the operators feel built-in.

---

## Function-by-function

### `Point2D(int x = 0, int y = 0)` — constructor
Default + parametrised in one. The `= 0` defaults mean `Point2D()`, `Point2D(2)`, and `Point2D(2,3)` all work. Uses `this->x = x;` because the parameter name `x` shadows the member `x` (the `this->` disambiguates — straight from the lecturer's "this pointer" slide).

### `Point2D operator+(const Point2D& other) const` — member `+`
Adds two points componentwise and returns a **new** `Point2D`. Left operand is `*this`, right operand is `other`. `const` because it doesn't modify either operand. Called when you write `p1 + p2` → `p1.operator+(p2)`.

### `bool operator==(const Point2D& other) const` — Function 1
Returns `true` only if **both** coordinates match. Returns `bool` (the lecturer's rule for relational operators).

### `friend Point2D operator+(int val, const Point2D& p)` — Function 2
Adds a scalar to **both** coordinates. It is a **friend (non-member)** because the **left operand is an `int`**, not a `Point2D` — a member function can't have a non-object on its left. `friend` lets it still read `p.x`/`p.y`. Called by `10 + p1` → `operator+(10, p1)`.

### `operator double() const` — Function 3 (conversion operator)
Converts a `Point2D` to a `double` equal to `x*x + y*y` (squared magnitude). Triggered implicitly by `double mag = p1;`.

### `friend ostream& operator<<(ostream& os, const Point2D& p)` — Function 4
Lets `cout << p` print `Point(x, y)`. **Friend** because the left operand is `ostream`. Returns `ostream&` so calls **chain** (`cout << a << b`).

### `int& at(int index)` — Function 5
Returns a **reference** to `x` (index 0) or `y` (index 1), so `p.at(0) = 100;` writes into the real member. Any other index `throw`s `std::out_of_range` (links to Topic 3).

---

## Execution flow of `main()`

```
1. Point2D p1(2,3), p2(4,5)          → constructor runs twice
2. p3 = p1 + p2                      → operator+(member)      → Point(6,8)
   cout << p3                        → operator<< (Function 4)
3. p1 == p2 / p1 == p4               → operator== (Function 1) → false / true
4. p5 = 10 + p1                      → friend operator+ (Function 2) → Point(12,13)
5. double mag = p1                   → operator double (Function 3) → 13
6. p1.at(0) = 100                    → at() returns int& (Function 5), writes x
7. p1.at(5) = 7  inside try{}        → at() throws out_of_range → caught, message printed
```

Every line of `main` exercises exactly one of the integrated functions, in order — so you can read the output top-to-bottom against this list.
