# Chapter 2: Getting Started

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #sorting #analysis #divide-and-conquer

## Overview

This chapter introduces the framework for designing and analyzing algorithms. It covers insertion sort as a first algorithm, establishes loop invariants for correctness proofs, introduces the RAM model and running-time analysis, and develops merge sort via the divide-and-conquer paradigm.

---

## 2.1 Insertion Sort

**Problem:** Sort a sequence $\langle a_1, a_2, \ldots, a_n \rangle$ into non-decreasing order.

**Intuition:** Like sorting a hand of playing cards — pick up one card at a time and insert it into its correct position among the already-sorted cards in the left hand.

```
INSERTION-SORT(A, n)
1  for i = 2 to n
2      key = A[i]
3      // Insert A[i] into the sorted subarray A[1 : i – 1].
4      j = i – 1
5      while j > 0 and A[j] > key
6          A[j + 1] = A[j]
7          j = j – 1
8      A[j + 1] = key
```

### Loop Invariant

**Invariant:** At the start of each iteration of the `for` loop, the subarray `A[1 : i – 1]` consists of the elements originally in `A[1 : i – 1]`, but in sorted order.

To prove correctness using a loop invariant, show three properties:

| Property | Meaning |
|---|---|
| **Initialization** | True before the first iteration (i = 2: subarray A[1:1] is trivially sorted) |
| **Maintenance** | If true before iteration, remains true after |
| **Termination** | When loop ends (i = n+1), invariant gives correctness: A[1:n] is sorted |

### Pseudocode Conventions

- **Indentation** denotes block structure (no `begin`/`end`)
- Array notation: `A[i : j]` denotes the subarray $A[i], A[i+1], \ldots, A[j]$
- Object attributes accessed as `x.f`
- Arrays/objects passed by pointer; scalars passed by value
- `NIL` for null pointers; `//` for comments
- `error` indicates an unrecoverable precondition failure

---

## 2.2 Analyzing Algorithms

### RAM Model

Algorithms are analyzed against a **Random-Access Machine (RAM)** model:
- One processor executes instructions sequentially
- Each instruction (arithmetic, data movement, control) takes **constant time**
- Word size: $c \log_2 n$ bits (sufficient to index $n$ elements)
- No memory hierarchy (no cache effects modeled)

### Running Time of Insertion Sort

Let $t_i$ = number of times the `while` loop test executes for a given $i$.

| Case | Condition | $t_i$ | $T(n)$ |
|---|---|---|---|
| **Best case** | Already sorted | $t_i = 1$ | $\Theta(n)$ — linear |
| **Worst case** | Reverse sorted | $t_i = i$ | $\Theta(n^2)$ — quadratic |

**Worst-case running time:** $T(n) = an^2 + bn + c = \Theta(n^2)$

### Analysis Concepts

- **Input size:** Number of items (for sorting), total bits (for integer problems), or multiple parameters (for graphs: $|V|$ and $|E|$)
- **Worst-case analysis:** Guarantees an upper bound; most relevant for real-time systems
- **Average-case:** Often as bad as worst-case (insertion sort average is still $\Theta(n^2)$)
- **Order of growth:** Focus only on the leading term, ignoring constants and lower-order terms

---

## 2.3 Designing Algorithms: Divide-and-Conquer

### The Method

1. **Divide** the problem into smaller subproblems of the same type
2. **Conquer** by solving them recursively
3. **Combine** the solutions into a solution for the original problem

**Base case:** If the problem is small enough, solve directly.

### Merge Sort

Sorts subarray `A[p : r]` by dividing, recursively sorting, then merging.

```
MERGE-SORT(A, p, r)
1  if p >= r          // zero or one element?
2      return
3  q = floor((p + r) / 2)   // midpoint of A[p : r]
4  MERGE-SORT(A, p, q)       // recursively sort left half
5  MERGE-SORT(A, q + 1, r)   // recursively sort right half
6  MERGE(A, p, q, r)          // merge the two sorted halves
```

**MERGE Procedure:** Copies subarrays `A[p : q]` → `L` and `A[q+1 : r]` → `R`, then merges back into `A[p : r]`.

```
MERGE(A, p, q, r)
 1  nL = q – p + 1          // length of A[p : q]
 2  nR = r – q               // length of A[q + 1 : r]
 3  let L[0 : nL – 1] and R[0 : nR – 1] be new arrays
 4  for i = 0 to nL – 1     // copy A[p : q] into L
 5      L[i] = A[p + i]
 6  for j = 0 to nR – 1     // copy A[q + 1 : r] into R
 7      R[j] = A[q + j + 1]
 8  i = 0  // index into L
 9  j = 0  // index into R
10  k = p  // index into A
11  while i < nL and j < nR
12      if L[i] <= R[j]
13          A[k] = L[i]
14          i = i + 1
15      else A[k] = R[j]
16          j = j + 1
17      k = k + 1
18  while i < nL           // copy remaining L
19      A[k] = L[i]
20      i = i + 1
21      k = k + 1
22  while j < nR           // copy remaining R
23      A[k] = R[j]
24      j = j + 1
25      k = k + 1
```

**Correctness:** Each of the `n` elements is copied back into `A` exactly once → $\Theta(n)$ time.

### Analyzing Merge Sort

**Recurrence:**

$$T(n) = \begin{cases} \Theta(1) & \text{if } n < n_0 \\ 2T(n/2) + \Theta(n) & \text{if } n \geq n_0 \end{cases}$$

**Solution:** $T(n) = \Theta(n \log_2 n)$

**Intuition via recursion tree:**
- Tree has $\log_2 n + 1$ levels
- Each level costs $c_2 n$ (except leaves which cost $c_1 n$)
- Total: $c_2 n \log_2 n + c_1 n = \Theta(n \log_2 n)$

### Comparison

| Algorithm | Worst-case | Best-case | In-place? |
|---|---|---|---|
| Insertion Sort | $\Theta(n^2)$ | $\Theta(n)$ | Yes |
| Merge Sort | $\Theta(n \log_2 n)$ | $\Theta(n \log_2 n)$ | No |

For large inputs, merge sort's $\Theta(n \log_2 n)$ dominates over insertion sort's $\Theta(n^2)$.

---

## Key Complexity Results

| Algorithm / Operation | Complexity |
|---|---|
| INSERTION-SORT (worst) | $\Theta(n^2)$ |
| INSERTION-SORT (best) | $\Theta(n)$ |
| MERGE | $\Theta(n)$ |
| MERGE-SORT | $\Theta(n \log_2 n)$ |

> **Note:** In CLRS, `lg n` always denotes $\log_2 n$.

---

### Navigation
**Previous:** [[Index_Introduction_to_Algorithms]]
**Next:** [[Ch3_Characterizing_Running_Times]]
**Hub:** [[Index_Introduction_to_Algorithms]]
