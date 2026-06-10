# Exam Study — Topic 6: Stack (Array-Based)

**Source:** `CK-20252-Troy K69/6 - Stack/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #datastructures #stack #LIFO #exam

---

## 🎤 Professor's Opening (deliver this first)

> "A stack is a **LIFO** structure — *Last In, First Out* — like a stack of plates: you add and remove only from the **top**. It has exactly two main operations: **push** (add an item to the top) and **pop** (remove the top item). This implementation uses a dynamically allocated array plus a single integer index, `top`, that marks the current top element. Both push and pop are **O(1)** — they just touch the one slot at `top` and adjust the index. The convention here is `top = -1` for an empty stack; pushing **increments** `top` then writes, and popping reads then **decrements** `top`. Stacks are everywhere: function call frames, expression evaluation, undo features, and depth-first search."

---

## 1. Executive Summary

`IntStack` is a fixed-capacity **LIFO** stack on a dynamic array, tracked by a single `top` index (`-1` = empty). `push` increments `top` and stores; `pop` reads `stackArray[top]` and decrements. `isFull` checks `top == stackSize - 1`; `isEmpty` checks `top == -1`. The mystery functions add: **count even values**, **remove the bottom element**, and **remove the k-th element from the top**.

---

## 2. Zero-Loss Extraction

### 2.1 The class

```cpp
class IntStack {
private:
    int *stackArray;  // dynamic array storage
    int stackSize;    // capacity
    int top;          // index of the top element (-1 when empty)
public:
    IntStack(int);
    IntStack(const IntStack &);   // deep-copy copy constructor
    ~IntStack();
    void push(int);
    void pop(int &);
    bool isFull() const;
    bool isEmpty() const;
};
```

### 2.2 The four core operations (Question 1)

```cpp
IntStack::IntStack(int size) {
    stackArray = new int[size];
    stackSize = size;
    top = -1;                  // empty
}

void IntStack::push(int num) {
    if (isFull()) cout << "The stack is full.\n";
    else {
        top++;                 // make room at the new top
        stackArray[top] = num; // store
    }
}

void IntStack::pop(int &num) {
    if (isEmpty()) cout << "The stack is empty.\n";
    else {
        num = stackArray[top]; // read the top
        top--;                 // shrink
    }
}

bool IntStack::isFull()  const { return top == stackSize - 1; }
bool IntStack::isEmpty() const { return top == -1; }
```

> [!note] The order of operations matters
> **push** does `top++` *then* write (pre-increment placement). **pop** reads *then* `top--`. If you reversed either order you'd read/write the wrong slot or corrupt the top. State this clearly — it shows you understand the index discipline.

### 2.3 Decoding the mystery functions

| # | What it is | Purpose | Complexity |
|---|---|---|---|
| 1 | **`countEven()`** | Counts how many stored values are even, scanning indices `0..top` | $O(n)$, read-only |
| 2 | **`removeBottom()`** | Removes the **bottom** element by shifting everything down one and decrementing `top` | $O(n)$ |
| 3 | **`removeKthFromTop(k)`** | Removes the **k-th element counting from the top** (k=1 is the top) by shifting the elements above it down | $O(n)$ |

```cpp
// Function 1 — count even values
int IntStack::countEven() const {
    int count = 0;
    for (int i = 0; i <= top; i++)
        if (stackArray[i] % 2 == 0) count++;
    return count;
}

// Function 2 — remove the BOTTOM element
bool IntStack::removeBottom() {
    if (isEmpty()) return false;
    for (int i = 0; i < top; i++)
        stackArray[i] = stackArray[i + 1];  // shift everything down by one
    top--;
    return true;
}

// Function 3 — remove the k-th element from the TOP (k=1 => top)
bool IntStack::removeKthFromTop(int k) {
    if (k < 1 || k > top + 1) return false;     // validate: 1..size
    int targetIndex = top - k + 1;              // convert "k from top" to array index
    for (int i = targetIndex; i < top; i++)
        stackArray[i] = stackArray[i + 1];      // shift the elements above it down
    top--;
    return true;
}
```

### 2.4 Compiled demo + verified output

```
Initial stack: bottom [ 5 10 15 20 25 ] top
countEven() [Function 1] = 2
After removeBottom() [Function 2]: bottom [ 10 15 20 25 ] top
After removeKthFromTop(2) [Function 3]: bottom [ 10 15 25 ] top
```

(A non-destructive `displayStack()` helper was added for the demo, printing bottom → top.)

> [!note] Trace the output — be ready to justify each line
> - `countEven()` over `{5,10,15,20,25}`: even values are `10` and `20` → **2**. ✔
> - `removeBottom()` removes `5`, shifting the rest down → `{10,15,20,25}`. ✔
> - `removeKthFromTop(2)` on `{10,15,20,25}` (top=25): k=2 from the top means the **2nd from top = 20**. `targetIndex = top - k + 1 = 3 - 2 + 1 = 2`, i.e. `stackArray[2] = 20`. Shifting `25` down over it → `{10,15,25}`. ✔

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 Why a single `top` index gives O(1) push/pop

A stack only ever touches **one end**. The lone `top` index points at that end, so push/pop are pure index arithmetic plus one array access — no loops, no shifting. This is the defining efficiency of a stack and the reason it underpins function-call management (the program "call stack").

### 3.2 Why removing from the bottom/middle is "un-stack-like" and costs O(n)

Functions 2 and 3 deliberately break the LIFO contract by deleting from the **bottom** or **middle**. An array stack has no cheap way to do this: you must **shift** every element above the hole down by one to keep the storage contiguous (`0..top` with no gaps). That shifting is **O(n)** — the exact weakness a stack is *not* designed to have.

> [!important] The teaching point
> These functions illustrate a trade-off: arrays give O(1) access by index but O(n) interior deletion (shift). If interior removal were a common requirement, a **linked-list-based** stack would let you unlink a node in O(1) (once located) — but you'd lose the cache-friendliness and O(1) random index of the array. *Choose the structure to match the dominant operation.*

### 3.3 The index conversion in Function 3 — `top - k + 1`

Users think "k-th from the top"; the array thinks in indices `0..top`. The top element is at index `top` (that's "k=1"), so the k-th from the top is at `top - (k - 1) = top - k + 1`. Verifying this mapping is a favourite oral question.

> [!warning] Boundary checking
> The guard `k < 1 || k > top + 1` rejects invalid k. Note `top + 1` equals the **number of elements** (since `top` is 0-based and starts at −1). Off-by-one errors here (`>` vs `>=`, `top` vs `top+1`) are the most common bug — be precise.

### 3.4 The shift loops never touch `stackArray[top]` twice

In both shift loops the condition is `i < top` (not `<=`), because the last meaningful copy is `stackArray[top-1] = stackArray[top]`. After the loop, the old top slot is logically discarded by `top--`. Walk the examiner through this to prove you understand the loop bound.

### 3.5 Rule of Three (again)

`IntStack` owns `int* stackArray`, so it provides a **destructor** (`delete[]`) and a **deep-copy copy constructor**. The default shallow copy would make two stacks share one array → **double `delete[]`** on destruction (crash) and aliased mutations. This is the same ownership lesson as the Queue and Linked List.

---

## 4. Key Takeaways & Next Steps

1. **Stack = LIFO**, accessed only at the **top** via a single `top` index (`-1` = empty).
2. **push:** `top++` then write. **pop:** read then `top--`. **isFull:** `top == size-1`. **isEmpty:** `top == -1`.
3. push/pop are **O(1)**; deleting from the bottom/middle forces an **O(n) shift** — against the stack's nature.
4. **"k-th from top" → index `top - k + 1`**; mind the `k > top + 1` boundary check.
5. Owning a raw array ⇒ **Rule of Three** (destructor + deep copy constructor, both present).

> [!question] Stretch questions to rehearse
> 1. How would you implement a stack with a linked list, and what changes in the complexity of interior deletion?
> 2. Name three real-world uses of a stack and explain *why* a stack fits each (call frames, undo, balanced-parentheses / expression evaluation, DFS).

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. What does LIFO mean and how does this class enforce it?**
Last In, First Out — the most recently pushed element is the first popped. It's enforced by doing both push and pop only at the `top` index, never at the bottom.

**Q2. Walk through `push` and `pop`.**
`push`: if not full, increment `top` to open a new slot, then store the value there. `pop`: if not empty, copy `stackArray[top]` out to the caller, then decrement `top`. Both are O(1).

**Q3. How is an empty stack represented, and how does `isFull` work?**
`top == -1` means empty (no valid index yet). `isFull` is `top == stackSize - 1`, i.e. the top index has reached the last array slot.

**Q4. Why is `removeBottom` O(n) when push/pop are O(1)?**
Because removing the bottom leaves a gap at index 0, and to keep the array contiguous you must shift every remaining element down by one — n−1 moves. Stacks are optimised for the top, not the bottom.

**Q5. Explain the index math in `removeKthFromTop`.**
The top element is index `top` and counts as k=1. So the k-th from the top is at `top - k + 1`. After validating that k is between 1 and the element count (`top + 1`), it shifts the elements above the target down and decrements `top`.

**Q6. Why does the class need a custom copy constructor?**
It owns a heap array. The default copy would copy only the pointer (shallow), so two stacks would share one array — mutations would alias and both destructors would `delete[]` the same memory (double free). The deep-copy constructor allocates a new array and copies the contents.

---

## Graph View Links

**Previous**: [[Exam Study - Topic 5 (Queue)]]
**Next**: [[C++ OOP - Hub]]
**Hub**: [[C++ OOP - Hub]]
