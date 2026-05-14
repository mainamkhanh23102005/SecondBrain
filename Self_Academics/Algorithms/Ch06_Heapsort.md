# Chapter 6: Heapsort

## Executive Summary

Chapter 6 introduces **heapsort** — a sorting algorithm that combines the best properties of insertion sort (in-place, $O(1)$ extra space) and merge sort ($O(n \log_2 n)$ running time). The foundation is the **heap** data structure: a nearly complete binary tree stored as an array, where the **max-heap property** ($A[\text{PARENT}(i)] \geq A[i]$) ensures the root holds the maximum. Three key procedures build up to heapsort: **MAX-HEAPIFY** restores the heap property in $O(\log_2 n)$; **BUILD-MAX-HEAP** constructs a heap in $O(n)$ (not $O(n \log_2 n)$ — a tight analysis via height-weighted sums); **HEAPSORT** sorts in-place in $O(n \log_2 n)$. The heap also serves as an efficient **priority queue** with all operations in $O(\log_2 n)$.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Index navigation procedures** (can be implemented as bit shifts in practice):

```
PARENT(i)
1  return ⌊i/2⌋

LEFT(i)
1  return 2i

RIGHT(i)
1  return 2i + 1
```

**MAX-HEAPIFY** — restores max-heap property at index $i$ assuming children subtrees are valid max-heaps:

```
MAX-HEAPIFY(A, i)
 1  l = LEFT(i)
 2  r = RIGHT(i)
 3  if l ≤ A.heap-size and A[l] > A[i]
 4      largest = l
 5  else largest = i
 6  if r ≤ A.heap-size and A[r] > A[largest]
 7      largest = r
 8  if largest ≠ i
 9      exchange A[i] with A[largest]
10      MAX-HEAPIFY(A, largest)
```

**BUILD-MAX-HEAP** — constructs max-heap from unordered array in bottom-up order:

```
BUILD-MAX-HEAP(A, n)
1  A.heap-size = n
2  for i = ⌊n/2⌋ downto 1
3      MAX-HEAPIFY(A, i)
```

*Loop invariant:* At the start of each iteration, nodes $i+1, i+2, \ldots, n$ are each roots of max-heaps.

**HEAPSORT** — sorts array in place:

```
HEAPSORT(A, n)
1  BUILD-MAX-HEAP(A, n)
2  for i = n downto 2
3      exchange A[1] with A[i]
4      A.heap-size = A.heap-size – 1
5      MAX-HEAPIFY(A, 1)
```

**Priority queue operations:**

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

MAX-HEAP-INCREASE-KEY(A, x, k)
1  if k < x.key
2      error "new key is smaller than current key"
3  x.key = k
4  find the index i in array A where object x occurs
5  while i > 1 and A[PARENT(i)].key < A[i].key
6      exchange A[i] with A[PARENT(i)], updating object-to-index mapping
7      i = PARENT(i)

MAX-HEAP-INSERT(A, x, n)
1  if A.heap-size == n
2      error "heap overflow"
3  A.heap-size = A.heap-size + 1
4  k = x.key
5  x.key = –∞
6  A[A.heap-size] = x
7  map x to index heap-size in the array
8  MAX-HEAP-INCREASE-KEY(A, x, k)
```

---

## Deep-Dive Explanations

### Heap Representation

A **binary heap** on array $A[1:n]$ is a nearly complete binary tree:
- **Root** = $A[1]$
- **Parent** of $A[i]$ = $A[\lfloor i/2 \rfloor]$
- **Left child** of $A[i]$ = $A[2i]$
- **Right child** of $A[i]$ = $A[2i+1]$
- **Height** of an $n$-node heap = $\lfloor \log_2 n \rfloor$

**Max-heap property:** $A[\text{PARENT}(i)] \geq A[i]$ for all $i > 1$ (root holds maximum).

**Min-heap property:** $A[\text{PARENT}(i)] \leq A[i]$ (root holds minimum; used for priority queues).

Leaves are exactly the nodes indexed $\lfloor n/2 \rfloor + 1, \ldots, n$ — they have no children and trivially satisfy the heap property.

### Time and Space Complexity Analysis

#### MAX-HEAPIFY: $O(\log_2 n)$

Recurrence: each child subtree has size at most $2n/3$ (worst case: bottom level half-full), so:
$$T(n) \leq T(2n/3) + \Theta(1)$$

By **Master Theorem Case 2** with $a=1$, $b=3/2$, $n^{\log_{3/2} 1} = n^0 = 1$, and $f(n) = \Theta(1)$:
$$T(n) = O(\log_2 n)$$

Equivalently: running time on a node of height $h$ is $O(h)$.

#### BUILD-MAX-HEAP: $O(n)$

**Naive bound** (too loose): $O(n)$ calls × $O(\log_2 n)$ each = $O(n \log_2 n)$.

**Tight analysis:** At most $\lceil n/2^{h+1} \rceil$ nodes exist at height $h$ in an $n$-node heap. Each costs $O(h)$. Total cost:
$$\sum_{h=0}^{\lfloor \log_2 n \rfloor} \left\lceil \frac{n}{2^{h+1}} \right\rceil O(h) \leq cn \sum_{h=0}^{\lfloor \log_2 n \rfloor} \frac{h}{2^h} \leq cn \sum_{h=0}^{\infty} \frac{h}{2^h} = cn \cdot 2 = O(n)$$

using the identity $\sum_{h=0}^{\infty} h x^h = x/(1-x)^2$ evaluated at $x = 1/2$, giving 2.

**Result:** BUILD-MAX-HEAP runs in $\Theta(n)$ time — building a heap from scratch is linear.

#### HEAPSORT: $O(n \log_2 n)$

- Line 1 (BUILD-MAX-HEAP): $O(n)$
- Lines 2–5: $n-1$ iterations, each calling MAX-HEAPIFY in $O(\log_2 n)$
- Total: $O(n) + (n-1) \cdot O(\log_2 n) = O(n \log_2 n)$

Worst-case is also $\Omega(n \log_2 n)$ (Exercise 6.4-4), so $\Theta(n \log_2 n)$ worst case.
Best-case is also $\Omega(n \log_2 n)$ when all elements are distinct (Exercise 6.4-5).

#### Priority Queue Operations

| Operation | Time | Notes |
|-----------|------|-------|
| MAX-HEAP-MAXIMUM | $\Theta(1)$ | Just return $A[1]$ |
| MAX-HEAP-EXTRACT-MAX | $O(\log_2 n)$ | Constant work + MAX-HEAPIFY |
| MAX-HEAP-INCREASE-KEY | $O(\log_2 n)$ | Bubbles up a path of length $O(\log_2 n)$ |
| MAX-HEAP-INSERT | $O(\log_2 n)$ | Insert $-\infty$ then INCREASE-KEY |

All operations: $O(\log_2 n)$ time plus $O(1)$ overhead for object-to-index mapping (via handles or hash table).

### Algorithm Summary

| Algorithm | Time | Space | In-place? |
|-----------|------|-------|-----------|
| MAX-HEAPIFY | $O(\log_2 n)$ | $O(\log_2 n)$ recursion stack | N/A |
| BUILD-MAX-HEAP | $\Theta(n)$ | $O(1)$ extra | Yes |
| HEAPSORT | $O(n \log_2 n)$ worst | $O(1)$ extra | Yes |

### Heapsort vs. Other Sorts

Heapsort is asymptotically optimal as a comparison sort (matches the $\Omega(n \log_2 n)$ lower bound proven in Chapter 8), and sorts in-place unlike merge sort. However, quicksort (Chapter 7) typically outperforms heapsort in practice due to better cache behavior and smaller constant factors.

---

## Key Takeaways & Next Steps

1. **The heap** is a powerful data structure: $O(n)$ to build, $O(\log_2 n)$ per update, and it directly implements priority queues.
2. **BUILD-MAX-HEAP runs in $\Theta(n)$**, not $O(n \log_2 n)$ — the tight analysis via height-weighted sums is a recurring proof technique.
3. **Heapsort** achieves $O(n \log_2 n)$ and $O(1)$ extra space — optimal on both measures among comparison sorts.
4. The MAX-HEAPIFY recurrence $T(n) \leq T(2n/3) + \Theta(1)$ is a canonical Master Theorem Case 2 application.
5. Priority queues with $O(\log_2 n)$ operations appear in Dijkstra's algorithm (Chapter 22) and Prim's algorithm (Chapter 21).
6. The heap structure reappears in Chapter 21 (Fibonacci heaps, for even faster priority queues).

---

### Navigation

**Previous:** [[PartII_Introduction_Sorting_and_Order_Statistics]]
**Next:** [[Ch07_Quicksort]]
**Hub:** [[Index_Introduction_to_Algorithms]]
