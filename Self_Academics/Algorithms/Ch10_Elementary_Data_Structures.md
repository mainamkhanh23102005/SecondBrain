# Chapter 10: Elementary Data Structures

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #arrays #stacks #queues #linked-lists #trees

## Overview

This chapter covers simple pointer-based data structures for implementing dynamic sets: arrays, matrices, stacks, queues, linked lists, and rooted trees.

---

## 10.1 Simple Array-Based Data Structures

### Arrays

Memory layout: if array starts at address $a$, element size $b$ bytes, 1-origin indexed, the $i$th element is at bytes $a + b(i-1)$ through $a + bi - 1$. Array access is $O(1)$ regardless of index (RAM model).

**Matrices:** Stored as one or more 1-D arrays in either **row-major** or **column-major** order.
- Row-major (1-origin): $M[i,j]$ at index $n(i-1) + j$
- Column-major (1-origin): $M[i,j]$ at index $i + m(j-1)$
- Single-array representations are more cache-efficient; multiple-array representations allow ragged arrays.

### Stacks (LIFO)

Array-based stack with attribute `S.top` (index of topmost element). Empty when `S.top = 0`.

```
STACK-EMPTY(S)
1  if S.top == 0
2      return TRUE
3  else return FALSE

PUSH(S, x)
1  if S.top == S.size
2      error "overflow"
3  else S.top = S.top + 1
4       S[S.top] = x

POP(S)
1  if STACK-EMPTY(S)
2      error "underflow"
3  else S.top = S.top - 1
4       return S[S.top + 1]
```

**All stack operations:** $O(1)$

### Queues (FIFO)

Circular array with attributes `Q.head` and `Q.tail`. Empty when `Q.head = Q.tail`.

```
ENQUEUE(Q, x)
1  Q[Q.tail] = x
2  if Q.tail == Q.size
3      Q.tail = 1
4  else Q.tail = Q.tail + 1

DEQUEUE(Q)
1  x = Q[Q.head]
2  if Q.head == Q.size
3      Q.head = 1
4  else Q.head = Q.head + 1
5  return x
```

**All queue operations:** $O(1)$

---

## 10.2 Linked Lists

Objects arranged in linear order via pointers rather than array indices.

**Doubly linked list:** Each element $x$ has `key`, `next` (successor), and `prev` (predecessor) attributes. `L.head` points to the first element; `L.head = NIL` means empty.

Variants: singly/doubly linked, sorted/unsorted, circular/non-circular.

### Key Operations

```
LIST-SEARCH(L, k)               // Θ(n) worst case
1  x = L.head
2  while x ≠ NIL and x.key ≠ k
3      x = x.next
4  return x

LIST-PREPEND(L, x)              // O(1)
1  x.next = L.head
2  x.prev = NIL
3  if L.head ≠ NIL
4      L.head.prev = x
5  L.head = x

LIST-INSERT(x, y)               // O(1) — inserts x after y
1  x.next = y.next
2  x.prev = y
3  if y.next ≠ NIL
4      y.next.prev = x
5  y.next = x

LIST-DELETE(L, x)               // O(1) with pointer; Θ(n) if searching by key
1  if x.prev ≠ NIL
2      x.prev.next = x.next
3  else L.head = x.next
4  if x.next ≠ NIL
5      x.next.prev = x.prev
```

### Sentinels

A **sentinel** `L.nil` is a dummy node that replaces NIL, turning the list into a **circular doubly linked list**. Simplifies boundary conditions:

```
LIST-DELETE′(x)       // no boundary checks needed
1  x.prev.next = x.next
2  x.next.prev = x.prev

LIST-INSERT′(x, y)    // inserts x after y
1  x.next = y.next
2  x.prev = y
3  y.next.prev = x
4  y.next = x
```

**Trade-off:** Sentinels reduce code complexity but consume extra memory — avoid when many small lists are used.

**Complexity comparison:**

| Operation | Array | Doubly Linked List |
|---|---|---|
| Insert at front | $\Theta(n)$ | $O(1)$ |
| Delete (with pointer) | $\Theta(n)$ | $O(1)$ |
| Access $k$th element | $O(1)$ | $\Theta(k)$ |
| Search | $\Theta(n)$ | $\Theta(n)$ |

---

## 10.3 Representing Rooted Trees

### Binary Trees

Each node $x$ has attributes `p` (parent), `left` (left child), `right` (right child). `T.root` points to root; `T.root = NIL` means empty tree.

### Left-Child, Right-Sibling Representation

For trees with **unbounded branching** (arbitrary number of children):
- `x.left-child` → leftmost child of $x$
- `x.right-sibling` → next sibling to the right

Uses only $O(n)$ space for any $n$-node rooted tree. The alternative of storing $k$ child pointers wastes memory when $k$ is large but most nodes have few children.

### Other Representations

- **Heap (Chapter 6):** Complete binary tree stored as a single array
- **Disjoint-set forests (Chapter 19):** Only parent pointers, no child pointers

---

## Complexity Summary

| Data Structure | Search | Insert | Delete |
|---|---|---|---|
| Unsorted array | $\Theta(n)$ | $O(1)$ | $O(1)$ |
| Sorted array | $O(\log_2 n)$ | $\Theta(n)$ | $\Theta(n)$ |
| Stack / Queue | $\Theta(n)$ | $O(1)$ | $O(1)$ |
| Doubly linked list | $\Theta(n)$ | $O(1)$ | $O(1)$* |

*$O(1)$ given a pointer to the element; $\Theta(n)$ if searching by key.

---

### Navigation
**Previous:** [[Part3_Introduction_Data_Structures]]
**Next:** [[Ch11_Hash_Tables]]
**Hub:** [[Index_Introduction_to_Algorithms]]
