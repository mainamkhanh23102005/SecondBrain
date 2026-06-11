# Topic 4 — Linked List (Code Walkthrough)

**Files:** `NumberList.{h,cpp}`, `main.cpp`
**Build & run:** `g++ -std=c++11 main.cpp NumberList.cpp -o demo && ./demo`

---

## File: `NumberList.{h,cpp}`

The node and the list handle:

```cpp
struct ListNode { double value; ListNode *next; };   // a node = data + pointer to next
ListNode *head;                                       // entry point; nullptr = empty list
```

| Symbol | Meaning |
|---|---|
| `head` | points to the first node; `nullptr` means the list is empty |
| `node->next` | link to the next node; the last node's `next` is `nullptr` |

### Core operations

- **`appendNode(double num)`** — add to the **end**. Make a node; if `head` is null it becomes head; else walk `nodePtr` to the last node (`while (nodePtr->next)`) and link it on.
- **`insertNode(double num)`** — add in **sorted** order. Walk with `nodePtr` + trailing `previousNode`, skipping nodes `< num`. Insert before `nodePtr`: if `previousNode == nullptr` it goes at the front (update `head`), else splice between `previousNode` and `nodePtr`.
- **`deleteNode(double num)`** — remove first node equal to `num`. If it's the head, `head = head->next` then `delete`. Otherwise walk with `previousNode`, then `previousNode->next = nodePtr->next` and `delete nodePtr`.
- **`displayList() const`** — walk from head, print each `value`.
- **`~NumberList()`** — destructor: walk the list, saving `next` before each `delete`, freeing every node (prevents a leak).

### The three integrated "mystery functions"

- **`countNodes(ListNode* p) const`** (Function 1, recursive) — `return 0` if `p == nullptr` (base case), else `1 + countNodes(p->next)`. Public wrapper `countNodes()` starts it at `head`.
- **`showReverse(ListNode* p) const`** (Function 2, recursive) — recurse to the end **first** (`showReverse(p->next)`), then print `p->value` on the way back → prints in reverse **without changing the list**. Wrapper `showReverse()` starts at `head`. *(This is the lecturer's exact name from the Ch.19 slide.)*
- **`reverseList()`** (Function 3, iterative) — three pointers `prev/curr/next`: save `next`, flip `curr->next = prev`, advance both; finally `head = prev`. **Permanently** reverses the links.

## File: `main.cpp`

Builds a sorted list 1..5 with `insertNode`, then calls each function.

---

## Execution flow

```
1. for x=1..5: insertNode(x)   → sorted list  1 ▶ 2 ▶ 3 ▶ 4 ▶ 5
2. displayList()               → 1 2 3 4 5
3. countNodes()  [Func 1]      → recursion depth 5 → returns 5
4. showReverse() [Func 2]      → recurse to end, print on return → 5 4 3 2 1
                                 (list itself UNCHANGED)
5. reverseList() [Func 3]      → relinks pointers → head now at old tail
6. displayList()               → 5 4 3 2 1   (forward walk now prints reversed
                                 — proof the structure actually changed)
```

**Why Func 2 and Func 3 both print `5 4 3 2 1` but differ:** Func 2 only changes the *print order* using the call stack; Func 3 changes the *links*. Step 6's forward traversal is the proof — it only prints reversed because `reverseList` rewired the nodes.

> **The non-negotiable rule in `reverseList`:** save `next` *before* `curr->next = prev`. If you flip the link first you lose the pointer to the rest of the list.
