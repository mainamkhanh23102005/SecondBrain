# Exam Study — Topic 3: Exception Handling (try / catch / throw)

**Source:** `CK-20252-Troy K69/3 - Exception/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #oop #exceptions #error-handling #exam

---

## 🎤 Professor's Opening (deliver this first)

> "Exception handling is C++'s structured mechanism for **separating the code that *detects* an error from the code that *handles* it**. Instead of returning error codes that callers might ignore, a function `throw`s an exception object when something goes wrong. The runtime then **unwinds the stack** — destroying local objects properly along the way — until it finds a `catch` block whose type matches. This keeps the *normal* logic clean and readable in the `try` block, while error recovery lives in `catch` blocks. The three keywords are: `try` (wrap risky code), `throw` (signal the error), and `catch` (handle a specific type of error)."

---

## 1. Executive Summary

The `Rectangle` class refuses negative dimensions: instead of silently accepting bad input, its setters **`throw`** custom exception classes (`NegativeWidth`, `NegativeLength`). Calling code wraps the setters in a **`try`** block and **`catch`**es those exceptions to react. The mystery function shows two patterns: catching a *specific* exception to **auto-recover**, plus a **catch-all** `catch(...)` as a safety net.

---

## 2. Zero-Loss Extraction

### 2.1 The class with exception types

```cpp
class Rectangle {
private:
    double width;
    double length;
public:
    // Exception classes — empty "tag" types used purely for identification
    class NegativeWidth  { };
    class NegativeLength { };

    Rectangle() { width = 0.0; length = 0.0; }

    void   setWidth(double);
    void   setLength(double);
    double getWidth()  const { return width; }
    double getLength() const { return length; }
    double getArea()   const { return width * length; }
};

void Rectangle::setWidth(double w) {
    if (w >= 0) width = w;
    else        throw NegativeWidth();   // signal the error
}

void Rectangle::setLength(double len) {
    if (len >= 0) length = len;
    else          throw NegativeLength();
}
```

### 2.2 The mystery function (decoded)

```cpp
void mysteryFunction(Rectangle& rect, double val) {
    try {
        rect.setWidth(val);      // (A) may throw NegativeWidth
        rect.setLength(val);     // (B) may throw NegativeLength
    }
    catch (Rectangle::NegativeWidth) {        // specific handler
        cout << "Fixing width automatically..." << endl;
        rect.setWidth(0);        // auto-recovery: clamp to 0
        // throw;                // (commented out) would re-throw to caller
    }
    catch (...) {                             // catch-all safety net
        cout << "An unknown error occurred!" << endl;
    }
}
```

**Purpose:** It tries to set both width and length to `val`. If `val` is negative, `setWidth` throws `NegativeWidth`; the first `catch` **recovers automatically** by setting the width to 0. Any *other* exception type (e.g. `NegativeLength`, which can only happen if the design changed) is caught by the catch-all `catch(...)`.

### 2.3 Compiled demo + verified output

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
    return 0;
}
```

**✅ Verified actual output:**

```
=== Case 1: valid value (5.0) ===
Width=5 Length=5 Area=25

=== Case 2: negative value (-3.0) ===
Fixing width automatically...
Width=0 Length=5 Area=0
```

> [!warning] The subtle, exam-winning detail in Case 2
> When `val = -3`, `setWidth(-3)` throws **immediately**, so **`setLength` on line (B) never executes**. Control jumps straight to the `catch`, which sets width to 0. Result: `Width=0`, and `Length=5` (the *leftover* value from Case 1, because the same `r` object was reused and `setLength` was skipped). `Area = 0 × 5 = 0`. Being able to explain *why length is still 5* — "because the throw aborted the try block before setLength ran" — demonstrates real understanding of control flow.

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 Why exceptions instead of error codes?

The traditional C approach returns a special value (`-1`, `nullptr`) to signal failure. Problems: callers **forget to check**, error-handling code is **tangled** with normal logic, and constructors/operators **cannot return** an error code at all. Exceptions fix all three: they **cannot be silently ignored** (an uncaught exception calls `std::terminate`), they **separate** normal and error paths, and they work in constructors.

### 3.2 What happens at a `throw` — stack unwinding

When `throw` executes:
1. A copy of the exception object is created.
2. The runtime **unwinds the stack**: it exits the current scope, **calling destructors** for all fully-constructed local objects (this is why RAII matters — resources get released).
3. It keeps unwinding outward through function calls until it finds a `catch` whose type matches.
4. If no handler is found anywhere, `std::terminate()` aborts the program.

### 3.3 Catch ordering and the catch-all `catch(...)`

> [!important] Order matters: most-specific first.
> Handlers are tried **top to bottom**. A `catch(...)` must come **last**, because it matches *everything* — anything after it is unreachable (and the compiler warns). `catch(...)` is a safety net for unknown/unexpected exceptions but is "blunt": it gives you **no information** about what was thrown, so use specific catches whenever you can.

### 3.4 Why empty exception classes (`class NegativeWidth { };`)?

The exception type itself is the message — its *type* identifies the error. Matching is done **by type**, not by value, so even an empty class is enough to route `setWidth`'s failure to the right `catch`. A richer design would store data (e.g. the offending value) inside the exception so the handler can report it. Best practice is to derive from `std::exception` and override `what()`.

### 3.5 The commented-out `throw;` (re-throwing)

A bare `throw;` inside a `catch` **re-throws the current exception** to the *next* handler up the call stack. This implements the pattern: *"handle part of it here (log it / partially recover), then let an outer layer deal with the rest."* Here it's commented out, so the exception is fully handled locally and the program continues.

### 3.6 Catch by value vs. by reference

These catches use **catch-by-value** (`catch (Rectangle::NegativeWidth)`). For exceptions in a class hierarchy you should **catch by reference** (`catch (const std::exception& e)`) to avoid **slicing** (Topic 2's pitfall again!) and to access polymorphic `what()`. Mention this for bonus depth.

---

## 4. Key Takeaways & Next Steps

1. **Three keywords:** `try` (wrap), `throw` (signal), `catch` (handle). They separate error *detection* from error *handling*.
2. A `throw` **aborts the rest of the `try` block** and unwinds the stack, calling destructors — that's why `setLength` was skipped in Case 2.
3. **Catch specific types first, `catch(...)` last.** Specific catches give information; the catch-all is a blunt safety net.
4. A bare **`throw;`** re-throws to an outer handler — "partial handling".
5. **Best practice:** derive exceptions from `std::exception`, override `what()`, and **catch by `const` reference**.

> [!question] Stretch questions to rehearse
> 1. What is RAII, and why does it make exception-safe code easier? (Destructors run during unwinding, so resources release automatically.)
> 2. What happens if an exception is thrown but never caught?

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. Explain `try`, `throw`, and `catch`.**
`try` encloses code that might fail. `throw` raises an exception object when an error is detected, immediately abandoning the rest of the `try`. `catch` blocks, placed right after the `try`, handle exceptions whose type matches; the runtime picks the first matching handler.

**Q2. In Case 2, why is the length still 5 after passing −3?**
Because `setWidth(-3)` threw before `setLength` could run, so length kept its previous value (5 from Case 1). The catch then forced width to 0. This shows that a throw aborts the remaining statements in the try block.

**Q3. What does `catch(...)` mean and where must it go?**
It catches **any** exception regardless of type. It must be the **last** handler because it matches everything; anything placed after it would be unreachable.

**Q4. What would the commented `throw;` have done?**
A bare `throw;` re-throws the currently-handled exception to the next outer `try/catch`, letting a higher layer also respond after this one partially handled it.

**Q5. Why use custom exception classes instead of, say, throwing an int?**
The *type* carries meaning and lets you write targeted catches (`catch (NegativeWidth)` vs `catch (NegativeLength)`). Throwing an `int` loses that semantic distinction. Best practice is to inherit from `std::exception`.

**Q6. What is stack unwinding?**
The process, during a throw, of exiting nested scopes and calling destructors for all local objects constructed so far, until a matching handler is found — ensuring resources are released even on the error path.

---

## Graph View Links

**Previous**: [[Exam Study - Topic 2 (Inheritance, Polymorphism)]]
**Next**: [[Exam Study - Topic 4 (Linked List)]]
**Hub**: [[C++ OOP - Hub]]
