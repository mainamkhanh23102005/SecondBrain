# Chapter 2: Getting Started

## Executive Summary

Chapter 2 introduces the foundational framework for algorithm design and analysis through two sorting algorithms: **Insertion Sort** (incremental method) and **Merge Sort** (divide-and-conquer). It establishes the concept of **loop invariants** for correctness proofs, develops the **RAM model** for analysis, and derives the first complexity results: Insertion Sort runs in $\Theta(n^2)$ worst-case time, while Merge Sort achieves $\Theta(n \log_2 n)$ — a fundamentally better asymptotic rate. The chapter introduces $\Theta$-notation informally and demonstrates **recursion trees** as an intuition-building tool.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Insertion Sort** — builds sorted subarray left-to-right by inserting each new element into its correct position:

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

**MERGE** — merges two sorted subarrays A[p:q] and A[q+1:r] into sorted A[p:r]:

```
MERGE(A, p, q, r)
 1  nL = q – p + 1          // length of A[p : q]
 2  nR = r – q               // length of A[q + 1 : r]
 3  let L[0 : nL – 1] and R[0 : nR – 1] be new arrays
 4  for i = 0 to nL – 1      // copy A[p : q] into L[0 : nL – 1]
 5      L[i] = A[p + i]
 6  for j = 0 to nR – 1      // copy A[q + 1 : r] into R[0 : nR – 1]
 7      R[j] = A[q + j + 1]
 8  i = 0                    // i indexes smallest remaining element in L
 9  j = 0                    // j indexes smallest remaining element in R
10  k = p                    // k indexes the location in A to fill
11  // As long as each of L and R contains an unmerged element,
12  // copy the smallest unmerged element back into A[p : r].
13  while i < nL and j < nR
14      if L[i] ≤ R[j]
15          A[k] = L[i]
16          i = i + 1
17      else A[k] = R[j]
18          j = j + 1
19      k = k + 1
20  // Having gone through one of L and R entirely, copy the
21  // remainder of the other to the end of A[p : r].
22  while i < nL
23      A[k] = L[i];  i = i + 1;  k = k + 1
24  while j < nR
25      A[k] = R[j];  j = j + 1;  k = k + 1
```

**MERGE-SORT** — recursively sorts A[p:r] using divide-and-conquer:

```
MERGE-SORT(A, p, r)
1  if p ≥ r
2      return              // zero or one element — already sorted
3  q = ⌊(p + r) / 2⌋      // midpoint of A[p : r]
4  MERGE-SORT(A, p, q)     // recursively sort A[p : q]
5  MERGE-SORT(A, q + 1, r) // recursively sort A[q + 1 : r]
6  MERGE(A, p, q, r)       // merge A[p : q] and A[q + 1 : r] into A[p : r]
```

### Key Definitions

- **Sorting problem:** Input sequence $\langle a_1, a_2, \ldots, a_n \rangle$ → Output permutation $\langle a_1', a_2', \ldots, a_n' \rangle$ such that $a_1' \leq a_2' \leq \cdots \leq a_n'$.
- **Loop invariant:** A property that is true before each iteration of a loop. Requires three proofs: **Initialization** (holds before first iteration), **Maintenance** (holds from iteration to iteration), **Termination** (useful at loop exit).
- **RAM model:** Single-processor, random-access machine where each instruction and data access takes constant time. No memory hierarchy, no concurrent operations.
- **Input size:** For sorting, the number $n$ of items. For integer multiplication, the total number of bits.
- **Running time $T(n)$:** Number of instructions and data accesses executed on input of size $n$.

### Pseudocode Conventions

- Indentation marks block structure (no `begin`/`end`).
- Loop counter retains its value after loop exit (value that first exceeded the bound).
- `A[i : j]` denotes the subarray $A[i], A[i+1], \ldots, A[j]$ (inclusive on both ends).
- Objects composed of attributes accessed with dot notation: `x.f`.
- Arrays and objects passed by pointer (not by value). Scalar parameters passed by value.
- `NIL` denotes a null pointer.
- Boolean operators `and`, `or` are short-circuiting.

---

## Deep-Dive Explanations

### Loop Invariant Proof for Insertion Sort

The loop invariant: *At the start of each iteration with index $i$, the subarray $A[1 : i-1]$ consists of the elements originally in $A[1 : i-1]$, but in sorted order.*

- **Initialization ($i = 2$):** $A[1:1]$ is a single element — trivially sorted. ✓
- **Maintenance:** The body of the for loop shifts elements right until it finds the insertion point for `key = A[i]`. After insertion, $A[1:i]$ is sorted. ✓
- **Termination ($i = n+1$):** $A[1:n]$ is the full array in sorted order. ✓

### Time and Space Complexity Analysis

#### Insertion Sort

| Case | Running Time | Explanation |
|------|-------------|-------------|
| Best case (already sorted) | $\Theta(n)$ | While loop executes 0 times; $t_i = 1$ for all $i$ |
| Worst case (reverse sorted) | $\Theta(n^2)$ | While loop executes $i$ times; $t_i = i$ for all $i$ |
| Average case | $\Theta(n^2)$ | On average, $t_i \approx i/2$; still quadratic |

Formal worst-case derivation:
$$T(n) = \sum_{i=2}^{n} \left( c_1 + c_2 + c_4 + c_5 t_i + c_6(t_i - 1) + c_7(t_i - 1) + c_8 \right)$$

With $t_i = i$ (worst case) and $\sum_{i=2}^{n} i = \frac{n(n+1)}{2} - 1$:

$$T(n) = \frac{c_5 + c_6 + c_7}{2} n^2 + \left(c_1 + c_2 + c_4 + \frac{c_5 - c_6 - c_7}{2} + c_8\right) n - (c_2 + c_4 + c_5 + c_8) = \Theta(n^2)$$

Space complexity: $O(1)$ extra space (sorts in place).

#### MERGE Procedure

MERGE runs in $\Theta(n)$ time where $n = r - p + 1$ (the size of the merged subarray):
- Lines 1–3 and 8–10 take $\Theta(1)$.
- For loops (lines 4–7) take $\Theta(n_L + n_R) = \Theta(n)$.
- The three while loops together copy each of the $n$ elements back exactly once → $\Theta(n)$ total.

Space complexity: $\Theta(n)$ auxiliary (arrays L and R).

#### Merge Sort

The recurrence for worst-case running time $T(n)$:
$$T(n) = \begin{cases} \Theta(1) & \text{if } n = 1 \\ 2T(n/2) + \Theta(n) & \text{if } n > 1 \end{cases}$$

**Recursion tree analysis:** The tree has $\log_2 n + 1$ levels. Each level above the leaves contributes $c_2 n$ total cost; the leaf level contributes $c_1 n$. Total:
$$T(n) = c_2 n \log_2 n + c_1 n = \Theta(n \log_2 n)$$

This is confirmed by the **Master Theorem** (Chapter 4), which gives $T(n) = \Theta(n \log_2 n)$.

Comparison: Merge Sort ($\Theta(n \log_2 n)$ worst case) beats Insertion Sort ($\Theta(n^2)$) for large $n$. The trade-off: $n$ replaces a factor of $n$ with $\log_2 n$.

Space complexity: $\Theta(n)$ (requires $O(n)$ auxiliary storage; does **not** sort in place).

### Order of Growth and $\Theta$-Notation

We simplify running-time formulas by keeping only the **leading term** and **discarding its constant coefficient**. This yields the **order of growth**:
- $an^2 + bn + c \to n^2 \to \Theta(n^2)$
- $an + b \to n \to \Theta(n)$

Informally: $\Theta(f(n))$ means "proportional to $f(n)$ for large $n$."

### Divide-and-Conquer Design Method

Three steps in the recursive case:
1. **Divide:** Break problem into subproblems smaller than the original.
2. **Conquer:** Solve subproblems recursively (base case: solve directly).
3. **Combine:** Merge subproblem solutions into the solution for the original problem.

For merge sort: Divide = compute midpoint $q$ ($\Theta(1)$); Conquer = two recursive calls; Combine = MERGE ($\Theta(n)$).

General recurrence for divide-and-conquer with $a$ subproblems of size $n/b$:
$$T(n) = aT(n/b) + D(n) + C(n)$$

---

## Key Takeaways & Next Steps

1. **Insertion Sort** is simple and efficient for small inputs ($\Theta(n)$ best case) but impractical for large inputs ($\Theta(n^2)$ worst case).
2. **Merge Sort** is the first example of $\Theta(n \log_2 n)$ sorting — the asymptotic optimum for comparison-based sorting (proven in Chapter 8).
3. **Loop invariants** are the primary correctness proof tool throughout CLRS; they mirror mathematical induction.
4. The **RAM model** provides a machine-independent cost model for algorithm analysis.
5. **Order of growth** (via $\Theta$-notation) strips away constant factors and lower-order terms to reveal the algorithm's true scalability.
6. **Recurrences** naturally describe the running time of recursive algorithms; solving them is the subject of Chapter 4.

---

### Navigation

**Previous:** [[Index_Introduction_to_Algorithms]]
**Next:** [[Ch03_Characterizing_Running_Times]]
**Hub:** [[Index_Introduction_to_Algorithms]]
