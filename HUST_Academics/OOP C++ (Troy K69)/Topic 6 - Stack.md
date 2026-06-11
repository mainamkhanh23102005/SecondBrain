# Topic 6 — Stack (Array-Based)

**Questions source:** `6 - Stack/Questions.txt`
**Runnable code:** `code/Topic6_Stack/` (IntStack.{h,cpp} + main.cpp)
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), Ch. 18 §18.1–18.2 — Stacks
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the algorithm ideas behind push, pop, isFull, isEmpty

**Background (Gaddis §18.1):** *"A stack is a data structure that stores and retrieves items in a last-in-first-out manner."* A stack is **LIFO**: *"the last element inserted into the stack is the first one retrieved."* The textbook's image is a stack of cafeteria plates — *"the first one he or she puts on the stack is the last one taken off."* All access happens at one end, the **top**.

This implementation stores the elements in a dynamic array with a single index `top` (= the index of the current top element; **−1 means empty**).

**The array + `top` index:**

```
index:    0     1     2     3     4
        ┌────┬────┬────┬────┬────┐
        │ 5  │ 10 │ 15 │    │    │   stackSize = 5
        └────┴────┴────┴────┴────┘
          ▲           ▲
        bottom       top = 2   (the element you can pop)

  empty stack:  top = -1     full stack:  top = stackSize - 1 (= 4)
```

**`push(num)` — add to the top.**
1. If `isFull()`, report the stack is full.
2. Otherwise increment first, then store: `top++; stackArray[top] = num;`.

```
push(20)         top++  →  3, then write at index 3
        ┌────┬────┬────┬────┬────┐
        │ 5  │ 10 │ 15 │ 20 │    │
        └────┴────┴────┴────┴────┘
                            ▲
                          top = 3
```

**`pop(num)` — remove from the top.**
1. If `isEmpty()`, report the stack is empty.
2. Otherwise read first, then shrink: `num = stackArray[top]; top--;`.

```
pop()    read stackArray[3]=20, then top--  →  2
        ┌────┬────┬────┬────┬────┐
        │ 5  │ 10 │ 15 │(20)│    │   (20) still in memory but
        └────┴────┴────┴────┴────┘    logically gone (top moved back)
                       ▲
                     top = 2
```

**`isFull()`** → returns `top == stackSize - 1` (the top index reached the last slot).
**`isEmpty()`** → returns `top == -1` (no valid element yet).

> **The central idea:** because a stack only ever touches **one end**, a single `top` index is enough, and both push and pop are just index arithmetic plus one array access → **O(1)**. The order of operations matters: `push` does `top++` *then* write; `pop` reads *then* `top--`. Reversing either order would read/write the wrong slot. (This array-based stack has a fixed capacity; the textbook notes a stack can also be built on a linked list to grow/shrink dynamically — §18.2.)

---

## Q2. Explain the primary purpose of the following functions

| # | What it really is | Purpose |
|---|---|---|
| 1 | **`countEven()`** | Counts how many stored values are even, scanning indices `0..top`. Read-only, $O(n)$ |
| 2 | **`removeBottom()`** | Removes the **bottom** element by shifting every element down one (`stackArray[i]=stackArray[i+1]`) and decrementing `top`. $O(n)$ |
| 3 | **`removeKthFromTop(k)`** | Removes the **k-th element counting from the top** (k=1 is the top). Converts "k from top" to the array index `top - k + 1`, shifts the elements above it down, decrements `top` |

```cpp
// Function 1
for (int i = 0; i <= top; i++) if (stackArray[i] % 2 == 0) count++;

// Function 2 — remove the BOTTOM
for (int i = 0; i < top; i++) stackArray[i] = stackArray[i + 1];
top--;

// Function 3 — remove the k-th from the TOP
if (k < 1 || k > top + 1) return false;     // validate: k in 1..(#elements)
int targetIndex = top - k + 1;              // "k from top" -> array index
for (int i = targetIndex; i < top; i++) stackArray[i] = stackArray[i + 1];
top--;
```

**Function 2 — `removeBottom()` shifts everything down by one:**

```
start:  ┌────┬────┬────┬────┐          top = 3
        │ 5  │ 10 │ 15 │ 20 │
        └────┴────┴────┴────┘
          ▲ remove the bottom (index 0)

shift:  stackArray[0]=stackArray[1], [1]=[2], [2]=[3]   (each slides left)
        ┌────┬────┬────┬────┐
        │ 10 │ 15 │ 20 │(20)│   then top--  → 2
        └────┴────┴────┴────┘
                       ▲ top = 2   result: 10 15 20
```

**Function 3 — `removeKthFromTop(k)` maps "k from top" to an index, then shifts:**

```
stack:  index   0    1    2    3
              ┌────┬────┬────┬────┐     top = 3
              │ 10 │ 15 │ 20 │ 25 │
              └────┴────┴────┴────┘
   k from top:  4    3    2    1
                          ▲
   removeKthFromTop(2):  targetIndex = top - k + 1 = 3 - 2 + 1 = 2  → value 20

shift the elements ABOVE index 2 down:  stackArray[2] = stackArray[3]
              ┌────┬────┬────┬────┐
              │ 10 │ 15 │ 25 │(25)│   then top--  → 2
              └────┴────┴────┴────┘
                            ▲ top = 2   result: 10 15 25
```

> **The teaching point:** push/pop are O(1) because they touch only the top, but Functions 2 and 3 deliberately remove from the **bottom/middle**, which an array stack cannot do cheaply — every element above the hole must be **shifted down** to keep storage contiguous, making them **O(n)**. The index math in Function 3 is the favourite oral question: the top element is at index `top` and counts as k=1, so the k-th from the top is at `top - k + 1`; the guard `k > top + 1` works because `top + 1` is the number of elements (top is 0-based, starting at −1).

---

## Q3. Integrate these functions into the project and run a demo

**Full runnable files:** `code/Topic6_Stack/` — `IntStack.{h,cpp}` (functions integrated as `countEven`, `removeBottom`, `removeKthFromTop`; a non-destructive `displayStack` helper is added for the demo), `main.cpp`.
**Build & run:**
```bash
g++ -std=c++11 main.cpp IntStack.cpp -o demo && ./demo
```

```cpp
IntStack s(10);
s.push(5); s.push(10); s.push(15); s.push(20); s.push(25);
s.displayStack();
s.countEven();            // Function 1
s.removeBottom();         // Function 2 -> removes 5
s.displayStack();
s.removeKthFromTop(2);    // Function 3 -> removes 2nd from top (20)
s.displayStack();
```

**✅ Verified output:**
```
Initial stack: bottom [ 5 10 15 20 25 ] top
countEven() [Function 1] = 2
After removeBottom() [Function 2]: bottom [ 10 15 20 25 ] top
After removeKthFromTop(2) [Function 3]: bottom [ 10 15 25 ] top
```

**How to read it:** evens in `{5,10,15,20,25}` are `10` and `20` → **2**. `removeBottom` drops `5`. Then `removeKthFromTop(2)` on `{10,15,20,25}` (top=25): `targetIndex = 3 − 2 + 1 = 2` → `stackArray[2] = 20` is removed, leaving `{10,15,25}`.

---

**Previous**: [[Topic 5 - Queue]] · **Next**: [[C++ OOP - Hub]] · **Hub**: [[C++ OOP - Hub]]
