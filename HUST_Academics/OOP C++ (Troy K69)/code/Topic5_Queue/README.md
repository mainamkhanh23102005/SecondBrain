# Topic 5 — Queue / Circular Array (Code Walkthrough)

**Files:** `IntQueue.{h,cpp}`, `main.cpp`
**Build & run:** `g++ -std=c++11 main.cpp IntQueue.cpp -o demo && ./demo`

---

## File: `IntQueue.{h,cpp}`

| Member | Meaning |
|---|---|
| `int *queueArray` | the ring buffer (heap array) |
| `int queueSize` | capacity |
| `int front` | index **one before** the first element (starts at −1) |
| `int rear` | index of the **last** element |
| `int numItems` | how many elements are currently stored |

The first real element always lives at `(front + 1) % queueSize`.

### Functions

- **`IntQueue(int s)`** — allocate the array; `front = rear = -1`, `numItems = 0`.
- **`IntQueue(const IntQueue& obj)`** — **deep-copy** copy constructor: allocate a *new* array and copy each element (so two queues never share one array → no double `delete[]`).
- **`~IntQueue()`** — `delete [] queueArray`.
- **`enqueue(int num)`** — add at the rear: if not full, `rear = (rear+1) % queueSize` (wrap), store, `numItems++`.
- **`dequeue(int& num)`** — remove at the front: if not empty, `front = (front+1) % queueSize` (wrap), read into `num`, `numItems--`.
- **`isEmpty()`** → `numItems == 0`.  **`isFull()`** → `numItems == queueSize`. (Counting items removes the classic front==rear "full or empty?" ambiguity.)
- **`clear()`** — reset indices and `numItems` to empty.

### Integrated "mystery functions"

- **`countOccurrences(int target) const`** (Func 1) — walk all `numItems` logical slots via `(front+1+i) % queueSize`, count matches.
- **`reverseQueue()`** (Func 2) — swap the i-th from the front with the i-th from the rear, looping `numItems/2` times (each swap fixes two elements).
- **`enqueueFront(int num)`** (Func 3) — insert at the **front**: write `queueArray[front] = num`, then move `front` **backward** with `(front - 1 + queueSize) % queueSize` (the `+ queueSize` avoids a negative index).
- **`displayQueue() const`** — helper for the demo; prints the logical order front→rear.

## File: `main.cpp`

Drives the queue and prints the state after each step.

---

## Execution flow

```
1. IntQueue q(5)
2. enqueue 10,20,30,20        rear walks 0→1→2→3   → [ 10 20 30 20 ]
3. dequeue(dummy)             front -1→0, removes 10 → [ 20 30 20 ]
                             (front now a valid index, needed for step 5)
4. countOccurrences(20) [F1]  scans 3 items → 2
5. enqueueFront(99) [F3]      write at front(0)=99, front→4 → [ 99 20 30 20 ]
6. reverseQueue() [F2]        swap ends inward → [ 20 30 20 99 ]
```

**Why step 3 matters:** `enqueueFront` writes `queueArray[front]` *before* moving `front`. On a brand-new queue `front == -1`, so we first enqueue+dequeue to make `front` a valid index (0) before calling it — otherwise it would touch `queueArray[-1]`.

> **The core trick:** `(i + 1) % queueSize` makes the array behave like a ring, reusing slots freed by `dequeue`. Moving backward needs `(i - 1 + queueSize) % queueSize` so the index never goes negative.
