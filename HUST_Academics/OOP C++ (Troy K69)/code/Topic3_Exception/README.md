# Topic 3 — Exception Handling (Code Walkthrough)

**Files:** `Rectangle.{h,cpp}`, `main.cpp`
**Build & run:** `g++ -std=c++11 main.cpp Rectangle.cpp -o demo && ./demo`

---

## File: `Rectangle.{h,cpp}`

| Member | Meaning |
|---|---|
| `double width`, `double length` (private) | the rectangle's dimensions |

**Nested exception classes** (empty "tag" types — their *type* is the signal):
- `class NegativeWidth { };`
- `class NegativeLength { };`

A single class is allowed more than one exception class — that is why both exist.

Functions:
- `Rectangle()` — sets width and length to 0.
- `setWidth(double w)` (`.cpp`) — if `w >= 0` store it; **else `throw NegativeWidth();`**.
- `setLength(double len)` (`.cpp`) — if `len >= 0` store it; **else `throw NegativeLength();`**.
- `getWidth()/getLength()/getArea()` — accessors; `getArea()` returns `width * length`.

The setters are the **detectors** — they decide something is wrong and `throw`. They do **not** handle the error; that is the caller's job.

## File: `main.cpp` — `mysteryFunction(Rectangle& rect, double val)`

The **handler**. Wraps the two setters in a `try`, with a specific `catch` that auto-recovers and a `catch(...)` safety net.

```cpp
try {
    rect.setWidth(val);    // (A)
    rect.setLength(val);   // (B) — runs only if (A) didn't throw
}
catch (Rectangle::NegativeWidth) { rect.setWidth(0); }   // recover
catch (...) { /* any other exception */ }
```

---

## Execution flow

```
Case 1: mysteryFunction(r, 5.0)        (valid)
   try: setWidth(5)  ✓   setLength(5) ✓   → no throw, catches skipped
   result: Width=5  Length=5  Area=25

Case 2: mysteryFunction(r, -3.0)       (invalid)
   try: setWidth(-3) → THROW NegativeWidth
        └─ function setWidth aborts, try block immediately exited
           → setLength(-3) is NEVER reached
   catch (NegativeWidth): print "Fixing width...", setWidth(0)
   result: Width=0  Length=5(leftover from Case 1)  Area=0
```

**The detail to explain in the exam:** in Case 2 the `throw` on line (A) skips line (B), so `setLength` never runs — that is why `length` keeps its old value (5) while `width` becomes 0. Detection (`throw` in the setter) and handling (`catch` in `mysteryFunction`) are cleanly separated.

> A richer design (lecturer slides 11 & 14): give the exception class a `value` member + `getValue()` so the `catch` can report the offending number, e.g. `catch (Rectangle::NegativeWidth e) { cout << e.getValue(); }`.
