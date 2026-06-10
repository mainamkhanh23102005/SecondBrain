# Topic 5 — Queue (Circular Array)

**Questions source:** `5 - Queue/Questions.txt`
**Runnable code:** `code/Topic5_Queue/` (IntQueue.{h,cpp} + main.cpp)
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), Ch. 18 §18.4–18.5 — Queues
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the algorithm ideas behind enqueue, dequeue, isFull, isEmpty

**Background (Gaddis §18.4):** *"A queue is a data structure that stores and retrieves items in a first-in-first-out manner."* A queue gives access to its elements in **FIFO** order, *"like customers standing in a grocery checkout line: the first customer in line is the first one served."* You **enqueue** (add) at the **rear** and **dequeue** (remove) from the **front**.

This implementation uses a **circular array** with three trackers: `front` (index *one before* the first element, starts at −1), `rear` (index of the last element), and `numItems` (current count).

**`enqueue(num)` — add at the rear.**
1. If `isFull()`, report the queue is full.
2. Otherwise advance the rear **with wrap-around**: `rear = (rear + 1) % queueSize;`
3. Store `queueArray[rear] = num;` and increment `numItems`.

**`dequeue(num)` — remove from the front.**
1. If `isEmpty()`, report the queue is empty.
2. Otherwise advance the front **with wrap-around**: `front = (front + 1) % queueSize;`
3. Read `num = queueArray[front];` and decrement `numItems`.

**`isEmpty()`** → returns `numItems == 0`.
**`isFull()`** → returns `numItems == queueSize`.

> **The central idea — the circular (ring) buffer.** The expression `(index + 1) % queueSize` is what makes the array *circular*: when an index reaches the last slot, the modulo wraps it back to `0`, so slots freed by earlier dequeues are reused. Without this, a linear array would falsely report "full" once `rear` hits the end even though there is free space at the front (or you'd have to shift every element, which is O(n)). With wrap-around, **enqueue and dequeue are O(1)**.
>
> **Why a separate `numItems`?** In a bare ring buffer, `front == rear` could mean *either* empty *or* full. Tracking the count removes that ambiguity, lets the queue use **every** slot, and makes `isFull`/`isEmpty` trivial O(1) checks.

---

## Q2. Explain the primary purpose of the following functions

| # | What it really is | Purpose |
|---|---|---|
| 1 | **`countOccurrences(target)`** | Counts how many items equal `target`, visiting each logical element via `(front+1+i) % queueSize`. Read-only, $O(n)$ |
| 2 | **`reverseQueue()`** | Reverses the queue **in place** by swapping the i-th element from the front with the i-th from the rear, using modular indices. Loops `numItems/2` times |
| 3 | **`enqueueFront(num)`** | Inserts a new element at the **front** (front insertion): writes `queueArray[front] = num`, then moves `front` **backward** with `(front - 1 + queueSize) % queueSize`. $O(1)$ |

```cpp
// Function 1
int index = (front + 1 + i) % queueSize;          // i-th logical element
if (queueArray[index] == target) count++;

// Function 2
int leftIndex  = (front + 1 + i) % queueSize;
int rightIndex = (front + 1 + numItems - 1 - i) % queueSize;
swap(queueArray[leftIndex], queueArray[rightIndex]);

// Function 3
queueArray[front] = num;
front = (front - 1 + queueSize) % queueSize;       // note the "+ queueSize"
```

> **The trap in Function 3:** moving an index *backward* can go negative (`front - 1` when `front == 0` gives −1), and C++'s `%` does not map that to `queueSize - 1`. Adding `queueSize` first keeps the operand non-negative: `(0 - 1 + 5) % 5 = 4`. Always write `(i - 1 + n) % n` for backward wrap.
>
> **Honest caveat:** `enqueueFront` writes `queueArray[front]` *before* moving `front`, so calling it on a brand-new queue (where `front == -1`) would touch `queueArray[-1]`. The demo first enqueues and dequeues so `front` holds a valid index before calling it.

---

## Q3. Integrate these functions into the project and run a demo

**Full runnable files:** `code/Topic5_Queue/` — `IntQueue.{h,cpp}` (functions integrated as `countOccurrences`, `reverseQueue`, `enqueueFront`; a non-destructive `displayQueue` helper is added for the demo), `main.cpp`.
**Build & run:**
```bash
g++ -std=c++11 main.cpp IntQueue.cpp -o demo && ./demo
```

```cpp
IntQueue q(5); int dummy;
q.enqueue(10); q.enqueue(20); q.enqueue(30); q.enqueue(20);
q.displayQueue();
q.dequeue(dummy);                 // removes 10 -> front becomes valid
q.displayQueue();
q.countOccurrences(20);           // Function 1
q.enqueueFront(99);               // Function 3
q.displayQueue();
q.reverseQueue();                 // Function 2
q.displayQueue();
```

**✅ Verified output:**
```
After enqueue 10,20,30,20 (front->rear): [ 10 20 30 20 ]
After dequeue (removed 10): [ 20 30 20 ]
countOccurrences(20) [Function 1] = 2
After enqueueFront(99) [Function 3]: [ 99 20 30 20 ]
After reverseQueue()  [Function 2]: [ 20 30 20 99 ]
```

---

**Previous**: [[Topic 4 - Linked List]] · **Next**: [[Topic 6 - Stack]] · **Hub**: [[C++ OOP - Hub]]
