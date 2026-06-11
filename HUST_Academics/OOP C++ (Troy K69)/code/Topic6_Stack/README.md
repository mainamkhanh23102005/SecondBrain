# Topic 6 — Stack / Array-Based (Code Walkthrough)

**Files:** `IntStack.{h,cpp}`, `main.cpp`
**Build & run:** `g++ -std=c++11 main.cpp IntStack.cpp -o demo && ./demo`

---

## File: `IntStack.{h,cpp}`

| Member | Meaning |
|---|---|
| `int *stackArray` | the storage array (heap) |
| `int stackSize` | capacity |
| `int top` | index of the current top element; **−1 means empty** |

### Functions

- **`IntStack(int size)`** — allocate the array; `top = -1`.
- **`IntStack(const IntStack& obj)`** — **deep-copy** copy constructor: new array + copy each element + copy `top` (avoids two stacks sharing one array → no double `delete[]`).
- **`~IntStack()`** — `delete [] stackArray`.
- **`push(int num)`** — if not full: `top++` **then** `stackArray[top] = num` (make room, then store).
- **`pop(int& num)`** — if not empty: read `num = stackArray[top]` **then** `top--` (read, then shrink).
- **`isFull()`** → `top == stackSize - 1`.  **`isEmpty()`** → `top == -1`.

### Integrated "mystery functions"

- **`countEven() const`** (Func 1) — scan indices `0..top`, count values where `value % 2 == 0`.
- **`removeBottom()`** (Func 2) — remove the bottom element by shifting everything down one (`stackArray[i] = stackArray[i+1]`), then `top--`. O(n).
- **`removeKthFromTop(int k)`** (Func 3) — remove the k-th element counting from the top (k=1 = top). Validate `1 ≤ k ≤ top+1`, compute `targetIndex = top - k + 1`, shift the elements above it down, `top--`.
- **`displayStack() const`** — helper for the demo; prints bottom→top.

## File: `main.cpp`

Pushes 5 values, then exercises each integrated function.

---

## Execution flow

```
1. IntStack s(10)
2. push 5,10,15,20,25        top walks 0→4   → bottom [ 5 10 15 20 25 ] top
3. countEven() [F1]          evens 10,20 → 2
4. removeBottom() [F2]       shift all down, top-- → [ 10 15 20 25 ]
5. removeKthFromTop(2) [F3]  k=2 → targetIndex = 3-2+1 = 2 (value 20),
                             shift above down, top-- → [ 10 15 25 ]
```

**Why push/pop are O(1) but Func 2 & 3 are O(n):** push/pop only touch the single `top` slot. Removing from the bottom/middle leaves a gap, so every element above must be **shifted down** to keep the array contiguous — that loop is what makes them O(n). A stack is optimised for the top only.

> **Index discipline to state aloud:** `push` is `top++` *then* write; `pop` is read *then* `top--`. In `removeKthFromTop`, the top is index `top` (k=1), so the k-th from the top is `top - k + 1`; the guard uses `top + 1` because that equals the number of elements.
