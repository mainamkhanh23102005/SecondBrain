# Topic 3 — Exception Handling

**Questions source:** `3 - Exception/Questions.txt`
**Runnable code:** `code/Topic3_Exception/` (Rectangle.{h,cpp} + main.cpp)
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), §16.1 Exceptions
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the ideas of try, catch in Exception C++

**Exceptions** — *"Exceptions are used to signal errors or unexpected events that occur while a program is running"* (Gaddis §16.1). Instead of returning special error codes that a caller might ignore, a function that detects a problem **throws** an exception, and a separate handler **catches** it. This cleanly **separates the code that detects an error from the code that handles it**. The three keywords:

- **`throw`** — signals an error. *"The throw keyword is followed by an argument, which can be any value … The line containing a throw statement is known as the throw point. When a throw statement is executed, control is passed to … an exception handler. When an exception is thrown by a function, the function aborts"* (§16.1). So a `throw` **immediately abandons** the current function/block.

- **`try`** — *"the try block … is followed by a block of code executing any statements that might directly or indirectly cause an exception to be thrown"* (§16.1). You wrap the risky calls in `try { ... }`.

- **`catch`** — *"The try block is immediately followed by one or more catch blocks, which are the exception handlers. A catch block starts with the keyword catch, followed by a set of parentheses containing the definition of an exception parameter"* (§16.1). The runtime picks the **first catch whose type matches** the thrown object.

How they work together: code in the `try` runs normally; if a called function `throw`s, the rest of the `try` is skipped and control jumps to the matching `catch`. Matching is **by type**, which is why custom exception classes (even empty ones) are useful — their *type* identifies the error. A `catch(...)` matches **any** exception and must be placed **last** (anything after it is unreachable).

**The control flow — two paths through a try/catch:**

```
  ┌─────────── NORMAL PATH (no error) ───────────┐
  │  try {                                        │
  │      setWidth(val);   ✓                       │
  │      setLength(val);  ✓                       │
  │  }                                            │
  │  catch(NegativeWidth) { ... }  ── skipped     │
  │  catch(...)           { ... }  ── skipped     │
  └──────────────────────┬───────────────────────┘
                         ▼  continue after the try


  ┌─────────── ERROR PATH (setWidth throws) ──────┐
  │  try {                                         │
  │      setWidth(val);   ✗ THROW NegativeWidth ──┼──┐  rest of try abandoned
  │      setLength(val);   ··· never runs          │  │  (setLength skipped!)
  │  }                                             │  │
  │  catch(NegativeWidth) { setWidth(0); } ◀───────┼──┘  jump to matching catch
  │  catch(...)           { ... }  ── not reached  │
  └──────────────────────┬────────────────────────┘
                         ▼  continue after the try
```

---

## Q2. Explain the primary purpose of the following function

```cpp
void mysteryFunction(Rectangle& rect, double val) {
    try {
        rect.setWidth(val);      // (A) throws Rectangle::NegativeWidth if val < 0
        rect.setLength(val);     // (B) only runs if (A) did NOT throw
    }
    catch (Rectangle::NegativeWidth) {   // specific handler -> auto-recovery
        cout << "Fixing width automatically..." << endl;
        rect.setWidth(0);
        // throw;                         // (commented) would re-throw to the caller
    }
    catch (...) {                         // catch-all safety net
        cout << "An unknown error occurred!" << endl;
    }
}
```

**Primary purpose:** it tries to set both the width and length of `rect` to `val`, with **error recovery**:
- If `val` is negative, `setWidth(val)` throws `NegativeWidth`. The **specific** `catch (Rectangle::NegativeWidth)` handles it by **automatically clamping the width to 0** and printing a message — the program keeps running instead of crashing.
- The **`catch (...)`** is a generic safety net for any *other* exception type.
- The commented `// throw;` is a **re-throw**: if enabled, after partially handling the error here, it would pass the same exception up to an outer handler.

> **Key control-flow point:** because `setWidth` throws on line (A), line (B) `setLength(val)` **never executes** — the throw aborts the rest of the `try` block.

---

## Q3. Integrate this function into the project and run a demo

**Full runnable files:** `code/Topic3_Exception/` — `Rectangle.{h,cpp}`, `main.cpp`.
**Build & run:**
```bash
g++ -std=c++11 main.cpp Rectangle.cpp -o demo && ./demo
```

```cpp
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
}
```

**✅ Verified output:**
```
=== Case 1: valid value (5.0) ===
Width=5 Length=5 Area=25

=== Case 2: negative value (-3.0) ===
Fixing width automatically...
Width=0 Length=5 Area=0
```

**How to read it (the detail to explain):** In **Case 2**, `setWidth(-3)` throws immediately, so `setLength(-3)` is **skipped**. The `catch` sets width to 0. The length is still **5** — the leftover value from Case 1, because the same object `r` is reused and `setLength` never ran. Therefore `Area = 0 × 5 = 0`.

---

**Previous**: [[Topic 2 - Inheritance, Polymorphism]] · **Next**: [[Topic 4 - Linked List]] · **Hub**: [[C++ OOP - Hub]]
