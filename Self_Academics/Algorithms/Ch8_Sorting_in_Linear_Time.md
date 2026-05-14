# Chapter 8: Sorting in Linear Time

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #sorting #counting-sort #radix-sort #bucket-sort #linear-time

## Overview

Comparison-based sorting algorithms require $\Omega(n \log_2 n)$ comparisons in the worst case. By making assumptions about the input (integer keys, bounded range, uniform distribution), we can break this barrier and achieve $O(n)$ time.

---

## 8.1 Lower Bounds for Sorting

### Decision-Tree Model

A **decision tree** is a full binary tree representing all possible comparisons in a sorting algorithm. Each:
- **Internal node** $i:j$ represents a comparison of $A[i]$ with $A[j]$
- **Leaf** represents a specific permutation (the sorted order)

A correct comparison sort must produce a leaf for every permutation → at least $n!$ leaves.

### Lower Bound Proof

**Lemma:** A binary tree of height $h$ has at most $2^h$ leaves.

**Theorem 8.1:** Any comparison-based sorting algorithm requires $\Omega(n \log_2 n)$ comparisons in the worst case.

**Proof:**
- Need at least $n!$ leaves: $n! \leq 2^h$
- Taking logs: $h \geq \log_2(n!)$
- By Stirling's approximation: $\log_2(n!) = \Omega(n \log_2 n)$

**Corollary:** Heapsort and merge sort are asymptotically optimal comparison sorts.

---

## 8.2 Counting Sort

**Assumptions:** Input integers in range $[0, k]$ for some constant $k$.

**Idea:** Count occurrences of each value; use cumulative counts to place elements directly into output positions.

```
COUNTING-SORT(A, n, k)
1  let B[1:n] and C[0:k] be new arrays
2  for i = 0 to k
3      C[i] = 0
4  for j = 1 to n
5      C[A[j]] = C[A[j]] + 1       // C[i] = count of elements equal to i
6  for i = 1 to k
7      C[i] = C[i] + C[i-1]        // C[i] = count of elements ≤ i
8  for j = n downto 1
9      B[C[A[j]]] = A[j]
10     C[A[j]] = C[A[j]] - 1
11 return B
```

**Complexity:** $\Theta(n + k)$ time and space.

**Stability:** Elements with the same value appear in the same order in the output as in the input (critical for RADIX-SORT correctness). The loop at line 8 iterates in reverse to preserve stability.

**When to use:** Practical when $k = O(n)$, giving $\Theta(n)$.

---

## 8.3 Radix Sort

**Idea:** Sort by each digit, from **least significant to most significant**, using a stable sort (e.g., COUNTING-SORT) on each digit.

```
RADIX-SORT(A, n, d)
1  for i = 1 to d
2      use a stable sort to sort A on digit i
```

**Why least-significant-digit first?** Preserves order established by previous passes for digits already sorted. Most-significant-digit-first requires additional work (partitioning).

**Theorem 8.3:** Given $n$ $d$-digit numbers where each digit takes $k$ possible values, RADIX-SORT correctly sorts in $\Theta(d(n+k))$ time.

### Choosing the Digit Size

For $b$-bit numbers (range $[0, 2^b - 1]$), choose $r$-bit digits (so $d = \lceil b/r \rceil$ passes, $k = 2^r$):

$$T(n, b) = \Theta\!\left(\frac{b}{r}(n + 2^r)\right)$$

**Optimal choice:** $r = \log_2 n$ (balances $n$ and $2^r$):
$$T(n, b) = \Theta\!\left(\frac{b}{\log_2 n} \cdot n\right) = \Theta\!\left(\frac{bn}{\log_2 n}\right)$$

For $b = O(\log_2 n)$: RADIX-SORT runs in $\Theta(n)$.

---

## 8.4 Bucket Sort

**Assumption:** Input is $n$ values drawn uniformly from $[0, 1)$.

**Idea:** Divide $[0, 1)$ into $n$ equal-sized **buckets**; put each element into its bucket; sort each bucket (e.g., with insertion sort); concatenate.

```
BUCKET-SORT(A, n)
1  let B[0:n-1] be a new array of empty lists
2  for i = 1 to n
3      insert A[i] into list B[floor(n * A[i])]
4  for i = 0 to n-1
5      sort list B[i] with insertion sort
6  concatenate lists B[0], B[1], ..., B[n-1] in order
```

**Expected complexity:** $O(n)$ — with uniform distribution, expected number of elements per bucket is 1, and insertion sort on a constant-length list takes $O(1)$.

**Formal analysis:**
Let $n_i$ = number of elements in bucket $B[i]$.
$$E[T(n)] = \Theta(n) + \sum_{i=0}^{n-1} E[O(n_i^2)] = \Theta(n) + n \cdot O\!\left(\frac{2 - 1/n}{n}\right) = O(n)$$

---

## Comparison of Sorting Algorithms

| Algorithm | Worst Case | Average Case | Space | Stable? | Notes |
|---|---|---|---|---|---|
| Insertion Sort | $\Theta(n^2)$ | $\Theta(n^2)$ | $O(1)$ | Yes | Fast for small/nearly sorted |
| Merge Sort | $\Theta(n \log_2 n)$ | $\Theta(n \log_2 n)$ | $O(n)$ | Yes | Optimal comparison sort |
| Heapsort | $\Theta(n \log_2 n)$ | $\Theta(n \log_2 n)$ | $O(1)$ | No | In-place |
| Quicksort | $\Theta(n^2)$ | $\Theta(n \log_2 n)$ | $O(\log_2 n)$ | No | Fast in practice |
| Counting Sort | $\Theta(n+k)$ | $\Theta(n+k)$ | $O(n+k)$ | Yes | Integers in $[0,k]$ |
| Radix Sort | $\Theta(d(n+k))$ | $\Theta(d(n+k))$ | $O(n+k)$ | Yes | Fixed-digit integers |
| Bucket Sort | $\Theta(n^2)$ | $O(n)$ | $O(n)$ | Yes | Uniform $[0,1)$ input |

---

### Navigation
**Previous:** [[Ch7_Quicksort]]
**Next:** [[Ch9_Medians_and_Order_Statistics]]
**Hub:** [[Index_Introduction_to_Algorithms]]
