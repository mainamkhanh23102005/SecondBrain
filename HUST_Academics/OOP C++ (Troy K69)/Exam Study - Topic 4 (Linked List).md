# Exam Study — Topic 4: Linked List

**Source:** `CK-20252-Troy K69/4 - Linked List/`
**Course:** [[C++ OOP - Hub|C++ OOP & Data Structures — Final Exam Hub]]
**Tags:** #cpp #datastructures #linkedlist #pointers #recursion #exam

---

## 🎤 Professor's Opening (deliver this first)

> "A linked list is a **dynamic, node-based data structure**. Unlike an array, its elements are not stored contiguously in memory; instead each **node** holds a value plus a **pointer to the next node**, and the list is accessed through a single `head` pointer. The big trade-off is this: a linked list gives **O(1) insertion and deletion** once you have a pointer to the spot — you just rewire a couple of pointers — but it pays for that with **O(n) access** because there is no indexing; you must walk from the head. Arrays are the opposite: O(1) access but O(n) insertion in the middle. Everything in a linked list comes down to careful **pointer surgery**: never lose the rest of the list while you re-link."

---

## 1. Executive Summary

The `NumberList` class is a **singly linked list** of `double`s, sorted in ascending order by `insertNode`. The three core operations — `appendNode`, `insertNode`, `deleteNode` — are all variations on "walk the list with a `nodePtr`, remember the `previousNode`, then rewire pointers." The mystery functions add: a **recursive node count**, a **recursive reverse-print**, and an **iterative in-place reversal** of the whole list.

---

## 2. Zero-Loss Extraction

### 2.1 The node structure

```cpp
class NumberList {
private:
    struct ListNode {
        double value;
        struct ListNode *next;   // self-referential pointer = the "link"
    };
    ListNode *head;              // entry point; nullptr means empty list
public:
    NumberList() { head = nullptr; }
    ~NumberList();
    void appendNode(double);
    void insertNode(double);
    void deleteNode(double);
    void displayList() const;
};
```

### 2.2 The three core algorithms (the heart of Question 1)

**`appendNode` — add to the END.** Allocate a node; if the list is empty, it becomes `head`; otherwise walk to the last node (the one whose `next` is `nullptr`) and link it on.

```cpp
void NumberList::appendNode(double num) {
    ListNode *newNode = new ListNode;
    newNode->value = num;
    newNode->next  = nullptr;
    if (!head) head = newNode;                 // empty list
    else {
        ListNode *nodePtr = head;
        while (nodePtr->next) nodePtr = nodePtr->next;  // find last node
        nodePtr->next = newNode;               // link at the end
    }
}
```

**`insertNode` — insert in SORTED position.** Walk with a `nodePtr` and trailing `previousNode`, skipping all nodes whose value `< num`. Then splice the new node in between `previousNode` and `nodePtr`.

```cpp
void NumberList::insertNode(double num) {
    ListNode *newNode = new ListNode;
    newNode->value = num;
    if (!head) { head = newNode; newNode->next = nullptr; }
    else {
        ListNode *nodePtr = head;
        ListNode *previousNode = nullptr;
        while (nodePtr != nullptr && nodePtr->value < num) {  // find insertion point
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        if (previousNode == nullptr) {     // insert at the front
            head = newNode;
            newNode->next = nodePtr;
        } else {                            // insert in the middle/end
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}
```

**`deleteNode` — remove the first node equal to `num`.** Special-case the head; otherwise walk with a trailing `previousNode`, then bypass the target and `delete` it.

```cpp
void NumberList::deleteNode(double num) {
    if (!head) return;
    ListNode *nodePtr, *previousNode;
    if (head->value == num) {              // deleting the head
        nodePtr = head->next;
        delete head;
        head = nodePtr;
    } else {
        nodePtr = head;
        while (nodePtr != nullptr && nodePtr->value != num) {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }
        if (nodePtr != nullptr) {          // found it
            previousNode->next = nodePtr->next;  // unlink
            delete nodePtr;                       // free
        }
    }
}
```

### 2.3 Decoding the mystery functions

| # | What it is | Purpose | Complexity |
|---|---|---|---|
| 1 | **Recursive node count** | Returns the number of nodes: `1 + count(next)`, base case `nullptr → 0` | $O(n)$ time, $O(n)$ call-stack space |
| 2 | **Recursive reverse-print** | Recurse to the end *first*, then print on the way back → prints values in **reverse order** (does NOT modify the list) | $O(n)$ |
| 3 | **Iterative in-place reversal** | Reverses the actual links using three pointers (`prev`, `curr`, `next`), then sets `head = prev` | $O(n)$ time, $O(1)$ space |

```cpp
// Function 1 — recursive count
int NumberList::countNodes(ListNode *nodePtr) const {
    if (nodePtr != nullptr) return 1 + countNodes(nodePtr->next);
    else                    return 0;            // base case
}

// Function 2 — recursive reverse PRINT (recurse first, print after)
void NumberList::printReverse(ListNode *nodePtr) const {
    if (nodePtr != nullptr) {
        printReverse(nodePtr->next);   // go all the way to the end first...
        cout << nodePtr->value << " "; // ...then print while returning
    }
}

// Function 3 — iterative in-place REVERSAL of the links
void NumberList::reverseList() {
    ListNode *curr = head, *prev = nullptr, *next = nullptr;
    while (curr != nullptr) {
        next = curr->next;   // 1. remember the rest of the list
        curr->next = prev;   // 2. flip the current link backwards
        prev = curr;         // 3. advance prev
        curr = next;         // 4. advance curr
    }
    head = prev;             // prev is the new head (old tail)
}
```

### 2.4 Compiled demo + verified output

Built a sorted list `1 2 3 4 5` via `insertNode`, then exercised all three:

```
Original list (head -> tail):
1
2
3
4
5
Node count (Function 1): 5
Print reverse (Function 2): 5 4 3 2 1
After reverseList() (Function 3), displayList:
5
4
3
2
1
```

> [!note] Function 2 vs Function 3 — the distinction examiners probe
> Both produce `5 4 3 2 1`, but they are **fundamentally different**: Function 2 only *prints* in reverse and leaves the list untouched (it uses the **call stack** to remember order); Function 3 actually **mutates the links** so the list itself is reversed permanently. After Function 3, `displayList()` (forward traversal) prints reversed — that's the proof the structure changed.

---

## 3. Deep-Dive Explanations (the *why*)

### 3.1 The universal linked-list idiom: `previousNode` / `nodePtr`

Because a singly linked list can only move *forward*, to delete or insert at a position you must keep a **trailing pointer** to the node *before* the current one — otherwise you can't re-link the gap. This "two-pointer walk" appears in `insertNode` and `deleteNode` and is the single most important pattern to internalise.

### 3.2 Why the head is always a special case

The head has **no predecessor**, so inserting before it or deleting it cannot use the `previousNode->next = ...` trick — you must update `head` directly. Notice both `insertNode` (`if (previousNode == nullptr)`) and `deleteNode` (`if (head->value == num)`) special-case the head. (A *dummy head node* is a classic technique to eliminate this special case.)

### 3.3 The reversal algorithm, pointer by pointer

The order of the four lines in Function 3 is **non-negotiable**:

1. `next = curr->next;` — **save** the rest of the list *before* we destroy the link.
2. `curr->next = prev;` — **reverse** the current node's pointer.
3. `prev = curr;` — slide `prev` forward.
4. `curr = next;` — slide `curr` forward using the saved pointer.

> [!warning] The #1 bug: losing the list
> If you write `curr->next = prev;` *before* saving `next`, you overwrite the only pointer to the remainder of the list and **lose everything after `curr`** — a memory leak and a broken list. Always **save `next` first**. This is the classic interview/exam trap.

### 3.4 Recursion and the call stack (Function 2)

Function 2 prints in reverse *without reversing the list* by exploiting the call stack: it dives to the last node before printing anything, so the **deepest call prints first**. Elegant, but the trade-off is **$O(n)$ stack space** and the risk of **stack overflow** on a very long list — whereas the iterative reversal (Function 3) uses only $O(1)$ extra space.

### 3.5 Memory management & the destructor

The destructor walks the list and `delete`s every node (saving `next` before each `delete`, same idiom). Without it, destroying a `NumberList` would **leak every node**. This is the Rule-of-Three motivation: a class owning heap nodes needs a destructor (and really a deep copy constructor + assignment too, otherwise two lists could share nodes and double-free).

---

## 4. Key Takeaways & Next Steps

1. **Node = value + `next` pointer; the list = a `head` pointer.** `nullptr` marks empty / end-of-list.
2. **Insert/delete = pointer surgery with a trailing `previousNode`.** The head is always a special case.
3. **Reversal:** save `next` → flip link → advance both. Order matters or you lose the list. $O(n)$ time, $O(1)$ space.
4. **Recursive reverse-print uses the call stack** ($O(n)$ space) and does *not* change the list; in-place reversal does.
5. **Trade-off vs arrays:** O(1) insert/delete given the position, but O(n) access (no indexing).

> [!question] Stretch questions to rehearse
> 1. How would a **doubly linked list** simplify deletion? (Each node has a `prev` pointer, so no trailing pointer needed.)
> 2. How do you detect a cycle in a linked list? (Floyd's slow/fast pointers.)

---

## Likely Follow-up Oral Questions (with model answers)

**Q1. Explain the idea behind `insertNode`.**
It keeps the list sorted. It walks from the head with a `nodePtr` and a trailing `previousNode`, skipping every node whose value is less than the new value. When it stops, the new node belongs *between* `previousNode` and `nodePtr`, so it links it there. If `previousNode` is still `nullptr`, the new value is the smallest and becomes the new head.

**Q2. Why do you need a `previousNode` pointer?**
In a singly linked list you can only move forward, so to splice a node in or out you need a handle on the node *before* the operation point to fix its `next` pointer. Without it you can't bridge the gap.

**Q3. Walk me through reversing the list.**
Use three pointers. Save `curr->next` into `next`, point `curr->next` back to `prev`, then move `prev` and `curr` forward. Repeat until `curr` is null; finally set `head` to `prev`, which is the old last node. It's O(n) time and O(1) space.

**Q4. What's the difference between the recursive reverse-print and the in-place reversal?**
The recursive print outputs the values in reverse by using the call stack but leaves the list unchanged. The in-place reversal physically re-links the nodes so the list itself is reversed. Proof: after the in-place reversal, a normal forward traversal prints in reverse.

**Q5. What is the time complexity of the recursive count, and what's the risk?**
O(n) time and O(n) call-stack space — one stack frame per node — so a very long list could overflow the stack. An iterative count would be O(1) space.

**Q6. Why does the class need a destructor?**
Each node is heap-allocated with `new`. The destructor traverses and `delete`s every node; otherwise the whole list leaks when the object dies.

---

## Graph View Links

**Previous**: [[Exam Study - Topic 3 (Exception Handling)]]
**Next**: [[Exam Study - Topic 5 (Queue)]]
**Hub**: [[C++ OOP - Hub]]
