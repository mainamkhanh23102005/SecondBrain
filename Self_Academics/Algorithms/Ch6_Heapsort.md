# Chapter 6: Heapsort

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #sorting #heap #priority-queue #data-structures

## Overview

Heapsort combines the best of insertion sort (in-place) and merge sort ($O(n \log_2 n)$ time). It introduces the **heap** data structure, which also underlies an efficient **priority queue** implementation.

---

## 6.1 Heaps

A **(binary) heap** is an array viewed as a nearly complete binary tree.

**Array representation:** For node at index $i$:
```
PARENT(i):  return floor(i/2)
LEFT(i):    return 2i
RIGHT(i):   return 2i + 1
```

**Two heap types:**

| Type | Property | Use |
|---|---|---|
| **Max-heap** | $A[\text{PARENT}(i)] \geq A[i]$ for all $i \neq 1$ | Heapsort, max-priority queues |
| **Min-heap** | $A[\text{PARENT}(i)] \leq A[i]$ for all $i \neq 1$ | Min-priority queues |

**Key property:** An $n$-element heap has height $\lfloor \log_2 n \rfloor$.

**Leaves:** Nodes at indices $\lfloor n/2 \rfloor + 1, \lfloor n/2 \rfloor + 2, \ldots, n$.

At most $\lceil n/2^{h+1} \rceil$ nodes of height $h$ in any $n$-element heap.

---

## 6.2 MAX-HEAPIFY — Restoring the Heap Property

Given that subtrees rooted at `LEFT(i)` and `RIGHT(i)` are valid max-heaps, but `A[i]` may be smaller than its children, "float" `A[i]` down to its correct position.

```
MAX-HEAPIFY(A, i)
 1  l = LEFT(i)
 2  r = RIGHT(i)
 3  if l <= A.heap-size and A[l] > A[i]
 4      largest = l
 5  else largest = i
 6  if r <= A.heap-size and A[r] > A[largest]
 7      largest = r
 8  if largest ≠ i
 9      exchange A[i] with A[largest]
10      MAX-HEAPIFY(A, largest)
```

**Complexity:** $O(\log_2 n)$ — follows a path from node to leaf of length at most $\lfloor \log_2 n \rfloor$.

**Recurrence:** $T(n) \leq T(2n/3) + \Theta(1)$, solved by Master Theorem Case 2: $T(n) = O(\log_2 n)$.

---

## 6.3 BUILD-MAX-HEAP — Building a Heap in Linear Time

Convert an unordered array into a max-heap by calling `MAX-HEAPIFY` bottom-up on all non-leaf nodes.

```
BUILD-MAX-HEAP(A, n)
1  A.heap-size = n
2  for i = floor(n/2) downto 1
3      MAX-HEAPIFY(A, i)
```

**Loop invariant:** At the start of iteration $i$, every node $i+1, i+2, \ldots, n$ is the root of a max-heap.

**Complexity:** $O(n)$ — tighter analysis using the bound on nodes at each height:

$$\sum_{h=0}^{\lfloor \log_2 n \rfloor} \left\lceil \frac{n}{2^{h+1}} \right\rceil O(h) = O\left(n \sum_{h=0}^{\infty} \frac{h}{2^h}\right) = O(n)$$

**Key insight:** Calling `MAX-HEAPIFY` $O(n)$ times is naively $O(n \log_2 n)$, but the tighter sum gives $O(n)$ because most nodes are near the leaves (at low height).

---

## 6.4 HEAPSORT

```
HEAPSORT(A, n)
1  BUILD-MAX-HEAP(A, n)
2  for i = n downto 2
3      exchange A[1] with A[i]      // move max to sorted position
4      A.heap-size = A.heap-size – 1
5      MAX-HEAPIFY(A, 1)            // restore heap property
```

**Invariant:** At the start of each iteration, `A[1:i]` is a max-heap containing the $i$ smallest elements, and `A[i+1:n]` contains the $n-i$ largest elements in sorted order.

**Complexity:**
- `BUILD-MAX-HEAP`: $O(n)$
- $n-1$ calls to `MAX-HEAPIFY`, each $O(\log_2 n)$
- **Total: $O(n \log_2 n)$**

Both best-case and worst-case are $\Theta(n \log_2 n)$ when all elements are distinct.

---

## 6.5 Priority Queues

A **max-priority queue** maintains a set $S$ with operations:

| Operation | Description | Time |
|---|---|---|
| `INSERT(S, x, k)` | Insert element $x$ with key $k$ | $O(\log_2 n)$ |
| `MAXIMUM(S)` | Return element with largest key | $\Theta(1)$ |
| `EXTRACT-MAX(S)` | Remove and return element with largest key | $O(\log_2 n)$ |
| `INCREASE-KEY(S, x, k)` | Increase key of element $x$ to $k$ | $O(\log_2 n)$ |

```
MAX-HEAP-MAXIMUM(A)
1  if A.heap-size < 1
2      error "heap underflow"
3  return A[1]

MAX-HEAP-EXTRACT-MAX(A)
1  max = MAX-HEAP-MAXIMUM(A)
2  A[1] = A[A.heap-size]
3  A.heap-size = A.heap-size – 1
4  MAX-HEAPIFY(A, 1)
5  return max
```

**INCREASE-KEY:** Set key, then bubble up toward root (compare with parent, swap if larger) — runs in $O(\log_2 n)$.

**INSERT:** Extend heap with key $-\infty$, then call INCREASE-KEY to set correct value — runs in $O(\log_2 n)$.

**Applications:**
- **Max-priority queue:** Job scheduling (always process highest-priority job)
- **Min-priority queue:** Event-driven simulation (process events in time order)

**Implementation note:** Heap elements are often pointers to objects. A mapping (e.g., hash table) or handles maintain the object-to-index correspondence.

---

## Complexity Summary

| Operation | Complexity |
|---|---|
| MAX-HEAPIFY | $O(\log_2 n)$ |
| BUILD-MAX-HEAP | $\Theta(n)$ |
| HEAPSORT | $\Theta(n \log_2 n)$ |
| INSERT / EXTRACT-MAX / INCREASE-KEY | $O(\log_2 n)$ |
| MAXIMUM | $\Theta(1)$ |

---

### Navigation
**Previous:** [[Part2_Introduction_Sorting]]
**Next:** [[Ch7_Quicksort]]
**Hub:** [[Index_Introduction_to_Algorithms]]
