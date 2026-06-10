# Topic 4 — Linked List

**Questions source:** `4 - Linked List/Questions.txt`
**Runnable code:** `code/Topic4_LinkedList/` (NumberList.{h,cpp} + main.cpp)
**Textbook:** *Starting Out with C++* (Gaddis, 8th ed.), Ch. 17 — Linked Lists
**Hub:** [[C++ OOP - Hub]]

---

## Q1. Explain the algorithm ideas behind insertNode, deleteNode, and appendNode

**Background (Gaddis §17.1):** *"A linked list is a series of connected nodes, where each node is a data structure."* Each node holds a `value` and a `next` pointer; the list is reached through a single `head` pointer, and `nullptr` marks the end (and the empty list). Because nodes are dynamically allocated, the list can **grow or shrink at runtime** — its advantage over a fixed array. The three operations are all variations of one idea: **walk the list with a `nodePtr`, keep a trailing `previousNode`, then rewire pointers.**

**`appendNode(num)` — add to the END.**
1. Allocate a new node, store `num`, set its `next = nullptr`.
2. If the list is empty (`head == nullptr`), the new node becomes `head`.
3. Otherwise walk `nodePtr` until `nodePtr->next == nullptr` (the last node), then link `nodePtr->next = newNode`.

**`insertNode(num)` — insert in SORTED position.**
1. Allocate the new node.
2. Walk with `nodePtr` **and** a trailing `previousNode`, skipping every node whose `value < num`. This stops at the first node ≥ `num` — the insertion point.
3. If `previousNode == nullptr`, the new value is the smallest → insert at the **front** (`head = newNode; newNode->next = nodePtr;`).
4. Otherwise splice it in the middle/end: `previousNode->next = newNode; newNode->next = nodePtr;`.

**`deleteNode(num)` — remove the first node equal to `num`.**
1. If the list is empty, do nothing.
2. If the **head** is the target, bypass it: `head = head->next;` then `delete` the old head (the head has no predecessor, so it is a special case).
3. Otherwise walk with `nodePtr` + `previousNode` until `nodePtr->value == num`. If found, unlink it (`previousNode->next = nodePtr->next;`) and `delete nodePtr;`.

> **The core idea in one sentence:** in a singly linked list you can only move forward, so to insert or delete you must hold a pointer to the node *before* the operation point (`previousNode`) in order to re-link the gap. The **head is always a special case** because it has no predecessor.

---

## Q2. Explain the primary purpose of the following functions

| # | What it really is | Purpose | Note |
|---|---|---|---|
| 1 | **Recursive node count** | Returns the number of nodes: `1 + count(next)`, base case `nullptr → 0` | $O(n)$ time, uses $O(n)$ call-stack |
| 2 | **Recursive reverse-print** | Recurses to the end **first**, then prints while returning → prints values in **reverse order**. Does **not** modify the list | Uses the call stack to remember order |
| 3 | **Iterative in-place reversal** | Reverses the actual links with three pointers (`prev`, `curr`, `next`), then `head = prev`. The list itself is permanently reversed | $O(n)$ time, $O(1)$ space |

```cpp
// Function 1 — recursive count
if (nodePtr != nullptr) return 1 + countNodes(nodePtr->next);
else                    return 0;                 // base case

// Function 2 — recursive reverse PRINT (recurse first, then print)
if (nodePtr != nullptr) { printReverse(nodePtr->next); cout << nodePtr->value << " "; }

// Function 3 — iterative in-place REVERSE of the links
while (curr != nullptr) {
    next = curr->next;   // 1. save the rest of the list
    curr->next = prev;   // 2. flip the current link backwards
    prev = curr;         // 3. advance prev
    curr = next;         // 4. advance curr
}
head = prev;             // prev is the old tail = new head
```

> **The distinction to stress:** Functions 2 and 3 *both* yield `5 4 3 2 1`, but Function 2 only **prints** in reverse (the list is unchanged — it just exploits the call stack), while Function 3 **physically re-links** the nodes so the list is reversed for good. In Function 3 the order of the four lines is non-negotiable: **save `next` first**, or you overwrite the only pointer to the rest of the list and lose it.

---

## Q3. Integrate these functions into the project and run a demo

**Full runnable files:** `code/Topic4_LinkedList/` — `NumberList.{h,cpp}` (the three functions are integrated as `countNodes`, `printReverse`, `reverseList`), `main.cpp`.
**Build & run:**
```bash
g++ -std=c++11 main.cpp NumberList.cpp -o demo && ./demo
```

```cpp
NumberList list;
for (int x = 1; x <= 5; x++) list.insertNode(x);  // -> 1 2 3 4 5
list.displayList();
cout << list.countNodes() << endl;                 // Function 1
list.printReverse();                               // Function 2
list.reverseList();                                // Function 3
list.displayList();
```

**✅ Verified output:**
```
Original list (head -> tail): 1 2 3 4 5
countNodes()  [Function 1] = 5
printReverse()[Function 2] = 5 4 3 2 1
After reverseList() [Function 3]: 5 4 3 2 1
```

The last line is the proof Function 3 mutated the structure: a normal **forward** traversal (`displayList`) now prints in reverse.

---

**Previous**: [[Topic 3 - Exception Handling]] · **Next**: [[Topic 5 - Queue]] · **Hub**: [[C++ OOP - Hub]]
