# Exam Study — Topic 5: Queue (Circular Array)

**Source:** `CK-20252-Troy K69/5 - Queue/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #datastructures #queue #circular-buffer #FIFO #exam

---

## 🎤 Professor's Opening (deliver this first)

> "A queue is a **FIFO** structure — *First In, First Out* — exactly like people lining up: the first person to arrive is the first served. It has two ends: we **enqueue** (add) at the **rear** and **dequeue** (remove) from the **front**. This implementation uses a **circular array**: rather than shifting all elements forward on every dequeue, which would be O(n), we keep two indices — `front` and `rear` — and let them **wrap around** the array using modular arithmetic, `index = (index + 1) % queueSize`. That wrap-around is the whole trick: it lets a fixed-size array be reused indefinitely as a ring, giving **O(1) enqueue and dequeue**."

---

## 1. Executive Summary

`IntQueue` is a fixed-capacity FIFO queue built on a **circular (ring) buffer**. It tracks `front`, `rear`, and `numItems`. `enqueue` advances `rear` with wrap-around and stores; `dequeue` advances `front` with wrap-around and reads. `numItems` makes `isEmpty`/`isFull` trivial and removes the classic "full vs empty ambiguity" of circular buffers. The mystery functions add: **count occurrences**, **in-place reverse**, and **enqueue-at-front**.

---

## 2. Zero-Loss Extraction

### 2.1 The class

```cpp
class IntQueue {
private:
    int *queueArray;  // the ring buffer
    int queueSize;    // capacity
    int front;        // index ONE BEFORE the first element (sentinel start = -1)
    int rear;         // index of the last element
    int numItems;     // current count — the key to unambiguous full/empty
public:
    IntQueue(int);
    IntQueue(const IntQueue &);   // deep-copy copy constructor
    ~IntQueue();
    void enqueue(int);
    void dequeue(int &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();
};
```

### 2.2 The four core operations (Question 1)

```cpp
IntQueue::IntQueue(int s) {
    queueArray = new int[s];
    queueSize = s;
    front = -1; rear = -1; numItems = 0;
}

void IntQueue::enqueue(int num) {
    if (isFull()) cout << "The queue is full.\n";
    else {
        rear = (rear + 1) % queueSize;   // advance rear WITH WRAP-AROUND
        queueArray[rear] = num;          // store new item
        numItems++;
    }
}

void IntQueue::dequeue(int &num) {
    if (isEmpty()) cout << "The queue is empty.\n";
    else {
        front = (front + 1) % queueSize; // advance front WITH WRAP-AROUND
        num = queueArray[front];         // retrieve the front item
        numItems--;
    }
}

bool IntQueue::isEmpty() const { return numItems == 0; }   // (written as if(numItems)...)
bool IntQueue::isFull()  const { return numItems == queueSize; }
```

> [!note] Why `numItems` is brilliant
> In a bare circular buffer, "front == rear" could mean *either* empty *or* full — an ambiguity usually solved by wasting one slot. Tracking `numItems` separately removes the ambiguity entirely, lets the queue use **all** slots, and makes `isFull`/`isEmpty` O(1) one-liners.

### 2.3 Decoding the mystery functions

| # | What it is | Purpose | Note |
|---|---|---|---|
| 1 | **`countOccurrences(target)`** | Counts how many items equal `target` by walking all `numItems` *logically* via `(front+1+i) % queueSize` | $O(n)$, read-only |
| 2 | **`reverseQueue()`** | Reverses the queue **in place** by swapping the i-th from front with the i-th from rear, using modular indices | $O(n)$, swaps `numItems/2` pairs |
| 3 | **`enqueueFront(num)`** | Inserts a new element at the **front** (turns the queue into a deque-like front-insert): writes at `front`, then moves `front` back one with wrap-around | $O(1)$ |

```cpp
// Function 1 — count occurrences of target
int IntQueue::countOccurrences(int target) const {
    int count = 0;
    for (int i = 0; i < numItems; i++) {
        int index = (front + 1 + i) % queueSize;  // logical i-th element
        if (queueArray[index] == target) count++;
    }
    return count;
}

// Function 2 — reverse in place
void IntQueue::reverseQueue() {
    for (int i = 0; i < numItems / 2; i++) {
        int leftIndex  = (front + 1 + i) % queueSize;
        int rightIndex = (front + 1 + numItems - 1 - i) % queueSize;
        int temp = queueArray[leftIndex];
        queueArray[leftIndex]  = queueArray[rightIndex];
        queueArray[rightIndex] = temp;
    }
}

// Function 3 — enqueue at the FRONT
bool IntQueue::enqueueFront(int num) {
    if (isFull()) return false;
    queueArray[front] = num;                  // write at the current front sentinel slot
    front = (front - 1 + queueSize) % queueSize;  // move front BACKWARD (note the + queueSize!)
    numItems++;
    return true;
}
```

### 2.4 Compiled demo + verified output

```
After enqueue 10,20,30,20 (front->rear): [ 10 20 30 20 ]
After dequeue (removed 10): [ 20 30 20 ]
countOccurrences(20) [Function 1] = 2
After enqueueFront(99) [Function 3]: [ 99 20 30 20 ]
After reverseQueue() [Function 2]: [ 20 30 20 99 ]
```

(A non-destructive `displayQueue()` helper was added for the demo; it prints the logical order using `(front+1+i) % queueSize`.)

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 The wrap-around: `(index + 1) % queueSize`

The modulo is what makes the array *circular*. When `rear` reaches the last slot (`queueSize - 1`), `(rear + 1) % queueSize` becomes `0` — it **wraps to the beginning** and reuses slots freed by earlier dequeues. Without modulo, you'd hit the end of the array and falsely report "full" even with empty slots at the front (the **false-overflow** problem of a linear queue), or you'd be forced to shift all elements (O(n)).

### 3.2 Why `enqueueFront` needs `(front - 1 + queueSize) % queueSize`

Moving an index **backwards** can go negative: if `front` is `0`, `front - 1` is `-1`, and in C++ `-1 % queueSize` is **not** `queueSize - 1` (it's implementation-defined / negative). Adding `queueSize` first guarantees a non-negative operand: `(0 - 1 + 5) % 5 = 4`. 

> [!warning] The classic modular-arithmetic bug
> `(i - 1) % n` is **wrong** for wrapping backwards; it can produce a negative index → out-of-bounds access. Always write `(i - 1 + n) % n`. This appears in Function 3 and is a favourite exam "spot the bug" question.

### 3.3 The `front = -1` sentinel — and a hidden edge case

This design starts `front = -1`, meaning *"one before the first element."* The first real element always lives at `(front + 1) % queueSize`. That's why every traversal uses `front + 1 + i`, and why `dequeue` advances `front` **before** reading.

> [!note] Honest caveat about Function 3 on a fresh queue
> Because `enqueueFront` writes to `queueArray[front]` *before* moving `front`, calling it on a brand-new queue (where `front == -1`) would access `queueArray[-1]` — out of bounds. In the demo we first enqueue and dequeue so `front` holds a valid index (0). This is a real fragility of the function worth pointing out: it assumes `front` is already a valid slot.

### 3.4 Reversal via two-ended swap

Function 2 is the array two-pointer reversal adapted for a ring: pair up the 1st-from-front with the 1st-from-rear, 2nd with 2nd-from-rear, etc., swapping each pair. It only needs `numItems / 2` iterations because each swap fixes **two** elements; the middle element (if `numItems` is odd) stays put. The only twist vs. a plain array is computing the logical indices with modulo.

### 3.5 The Rule of Three appears again

`IntQueue` owns a raw `int*`. It correctly provides a **destructor** (`delete[] queueArray`) and a **deep-copy copy constructor** (allocates a new array and copies elements). Be ready to explain that the *default* shallow copy would make two queues share one array → double `delete[]` (a crash) when both are destroyed.

---

## 4. Key Takeaways & Next Steps

1. **Queue = FIFO**: enqueue at rear, dequeue at front.
2. **Circular buffer + modulo** gives O(1) enqueue/dequeue without shifting; `(i+1) % size` wraps forward.
3. **Backward wrap needs `(i - 1 + size) % size`** to avoid negative indices — the key trap.
4. **`numItems` removes the full-vs-empty ambiguity** and makes `isFull`/`isEmpty` trivial.
5. Owning a raw array ⇒ **Rule of Three** (destructor + deep copy constructor, both present here).

> [!question] Stretch questions to rehearse
> 1. How could you implement a queue with two stacks? What's the amortised cost?
> 2. What is a *deque*, and how does `enqueueFront` move this class toward one?

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. What does FIFO mean and how is it enforced here?**
First In, First Out — the earliest enqueued element is dequeued first. It's enforced by always adding at `rear` and always removing at `front`, with both indices only ever moving forward (with wrap-around).

**Q2. Why a circular array instead of a normal one?**
A linear array would either need to shift every element on each dequeue (O(n)) or would falsely report "full" once `rear` hits the end despite free slots at the front. Wrapping the indices with modulo reuses those freed slots and keeps every operation O(1).

**Q3. Explain `(rear + 1) % queueSize`.**
It advances `rear` to the next slot, and when `rear` is at the last index it wraps back to 0, so the array behaves like a ring.

**Q4. There's a `+ queueSize` in `enqueueFront`. Why?**
Because moving the index backward (`front - 1`) can be negative, and the C++ `%` operator doesn't map negatives to the range we want. Adding `queueSize` first keeps the operand non-negative so the modulo gives the correct wrapped index.

**Q5. How do `isFull` and `isEmpty` work, and why is `numItems` used?**
`isEmpty` is `numItems == 0` and `isFull` is `numItems == queueSize`. Tracking the count avoids the classic ambiguity where `front == rear` could mean either full or empty, and it lets us use the entire array.

**Q6. What does `reverseQueue` do and why only `numItems/2` iterations?**
It swaps the i-th element from the front with the i-th from the rear, reversing the logical order in place. Each swap places two elements correctly, so half the iterations cover the whole queue; an odd middle element needs no swap.

---

## Graph View Links

**Previous**: [[Exam Study - Topic 4 (Linked List)]]
**Next**: [[Exam Study - Topic 6 (Stack)]]
**Hub**: [[C++ OOP - Hub]]
