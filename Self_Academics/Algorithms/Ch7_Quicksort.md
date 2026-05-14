# Chapter 7: Quicksort

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #sorting #quicksort #divide-and-conquer #randomized

## Overview

Quicksort is a divide-and-conquer sorting algorithm with $\Theta(n^2)$ worst-case but $\Theta(n \log_2 n)$ expected (and typical) performance. It sorts **in-place** and is often the fastest sorting algorithm in practice due to small constant factors.

---

## 7.1 Description of Quicksort

**Divide-and-conquer structure:**
1. **Divide:** Partition $A[p:r]$ around a pivot element $A[r]$ into two (possibly empty) subarrays:
   - $A[p:q-1]$: elements $\leq$ pivot
   - $A[q+1:r]$: elements $\geq$ pivot
2. **Conquer:** Recursively sort both subarrays
3. **Combine:** Nothing — subarrays are already sorted in-place

```
QUICKSORT(A, p, r)
1  if p < r
2      q = PARTITION(A, p, r)
3      QUICKSORT(A, p, q-1)
4      QUICKSORT(A, q+1, r)
```

### PARTITION (Lomuto scheme)

```
PARTITION(A, p, r)
1  x = A[r]           // pivot
2  i = p - 1
3  for j = p to r - 1
4      if A[j] <= x
5          i = i + 1
6          exchange A[i] with A[j]
7  exchange A[i+1] with A[r]
8  return i + 1
```

**Loop invariant:** At the start of each iteration of the `for` loop:
- $A[p:i] \leq x$
- $A[i+1:j-1] > x$
- $A[r] = x$ (pivot is untouched)

**Complexity of PARTITION:** $\Theta(n)$ where $n = r - p + 1$.

---

## 7.2 Performance of Quicksort

### Worst Case: $\Theta(n^2)$

Occurs when PARTITION produces one subproblem of size $n-1$ and one of size $0$ at every level (e.g., already-sorted input with pivot always being the largest element).

**Recurrence:** $T(n) = T(n-1) + T(0) + \Theta(n) = T(n-1) + \Theta(n)$

**Solution:** $T(n) = \Theta(n^2)$

**Proof by substitution:** Guess $T(n) \leq cn^2$ for some constant $c$:
$$T(n) \leq c(n-1)^2 + \Theta(n) = cn^2 - (2cn - c - \Theta(n)) \leq cn^2$$

### Best Case: $\Theta(n \log_2 n)$

Occurs when PARTITION always produces two subarrays of size $\lfloor n/2 \rfloor$ and $\lceil n/2 \rceil - 1$.

**Recurrence:** $T(n) = 2T(n/2) + \Theta(n)$

**Solution (Master Theorem Case 2):** $T(n) = \Theta(n \log_2 n)$

### Balanced vs. Unbalanced Splits

Even a constant-proportion split (e.g., 9-to-1) gives $O(n \log_2 n)$:
$$T(n) \leq T(9n/10) + T(n/10) + \Theta(n) = O(n \log_2 n)$$

The recursion tree has depth $\log_{10/9} n = O(\log_2 n)$, with $O(n)$ cost per level.

**Key insight:** Any split that keeps both sides a constant fraction of $n$ yields $O(n \log_2 n)$ — only extreme imbalance (e.g., 0-to-$n$) causes $\Theta(n^2)$.

---

## 7.3 Randomized Quicksort

Replace the fixed pivot (last element) with a random element to avoid worst-case behavior on any specific input.

```
RANDOMIZED-PARTITION(A, p, r)
1  i = RANDOM(p, r)
2  exchange A[i] with A[r]
3  return PARTITION(A, p, r)

RANDOMIZED-QUICKSORT(A, p, r)
1  if p < r
2      q = RANDOMIZED-PARTITION(A, p, r)
3      RANDOMIZED-QUICKSORT(A, p, q-1)
4      RANDOMIZED-QUICKSORT(A, q+1, r)
```

**Expected running time:** $\Theta(n \log_2 n)$ for any input.

---

## 7.4 Analysis of Randomized Quicksort

**Total comparisons:** Let $X$ = total number of comparisons across all PARTITION calls.

**Key observation:** Elements $z_i$ and $z_j$ (the $i$th and $j$th smallest elements) are compared **at most once** — only when one is chosen as pivot.

Let $X_{ij} = I\{z_i \text{ is compared to } z_j\}$.

$$E[X] = \sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \Pr\{z_i \text{ compared to } z_j\}$$

$z_i$ and $z_j$ are compared if and only if one of them is the first element chosen as pivot from $\{z_i, z_{i+1}, \ldots, z_j\}$.

$$\Pr\{z_i \text{ compared to } z_j\} = \frac{2}{j - i + 1}$$

$$E[X] = \sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \frac{2}{j-i+1} = \sum_{i=1}^{n-1} \sum_{k=2}^{n-i+1} \frac{2}{k} \leq \sum_{i=1}^{n-1} O(\log_2 n) = O(n \log_2 n)$$

**Theorem 7.4:** RANDOMIZED-QUICKSORT runs in expected time $\Theta(n \log_2 n)$ on any input of $n$ distinct elements.

---

## Complexity Summary

| Scenario | Running Time |
|---|---|
| Worst case | $\Theta(n^2)$ |
| Best case | $\Theta(n \log_2 n)$ |
| Expected (randomized) | $\Theta(n \log_2 n)$ |

**Space:** In-place, but $O(\log_2 n)$ expected stack depth for RANDOMIZED-QUICKSORT (worst case $O(n)$).

---

### Navigation
**Previous:** [[Part2_Introduction_Sorting]]
**Next:** [[Ch8_Sorting_in_Linear_Time]]
**Hub:** [[Index_Introduction_to_Algorithms]]
