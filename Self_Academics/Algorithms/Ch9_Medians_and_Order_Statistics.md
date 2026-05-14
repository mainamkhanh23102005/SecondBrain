# Chapter 9: Medians and Order Statistics

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #order-statistics #selection #median #randomized

## Overview

The **$i$th order statistic** of a set of $n$ elements is the $i$th smallest element. The **median** is the "middle" element (lower median for even $n$: $i = \lfloor (n+1)/2 \rfloor$). This chapter develops $O(n)$ algorithms for the selection problem.

---

## 9.1 Minimum and Maximum

### Finding the Minimum

```
MINIMUM(A, n)
1  min = A[1]
2  for i = 2 to n
3      if min > A[i]
4          min = A[i]
5  return min
```

**Comparisons:** $n - 1$ — provably optimal (each element except the winner must lose at least once).

### Simultaneous Min and Max

**Naive approach:** Find min ($n-1$ comparisons) then max ($n-1$ comparisons) = $2n-2$ total.

**Better approach:** Process elements in **pairs**:
1. Compare the two elements in the pair with each other
2. Compare the larger with the current max
3. Compare the smaller with the current min

**Cost per pair:** 3 comparisons for 2 elements = $3/2$ comparisons per element.

**Total:** $3\lfloor n/2 \rfloor$ comparisons — at most $3\lfloor n/2 \rfloor$ for even $n$.

---

## 9.2 Selection in Expected Linear Time

### RANDOMIZED-SELECT

Finds the $i$th smallest element using a modified quicksort partition.

```
RANDOMIZED-SELECT(A, p, r, i)
1  if p == r
2      return A[p]
3  q = RANDOMIZED-PARTITION(A, p, r)
4  k = q - p + 1          // k = rank of pivot in A[p:r]
5  if i == k
6      return A[q]         // pivot is the answer
7  elseif i < k
8      return RANDOMIZED-SELECT(A, p, q-1, i)
9  else
10     return RANDOMIZED-SELECT(A, q+1, r, i-k)
```

**Key difference from Quicksort:** Only recurses into **one** subarray (the one containing the $i$th order statistic).

**Worst-case complexity:** $\Theta(n^2)$ — same adversarial pivot sequence as quicksort.

### Expected Time Analysis

**Theorem 9.2:** RANDOMIZED-SELECT runs in expected $\Theta(n)$ time on any input of $n$ distinct elements.

**Proof sketch:**

Let $T(n)$ = expected running time on input of size $n$.

In the lucky case, PARTITION produces a split where neither side exceeds $3n/4$. This happens with probability $\geq 1/2$ (any pivot in the middle half gives a good split).

Using indicator variables: let $X_k = I\{\text{subarray sizes are } k \text{ and } n-k-1\}$:

$$E[T(n)] \leq E\!\left[\sum_{k=0}^{n-1} X_k (T(\max(k, n-k-1)) + O(n))\right]$$

This solves to $E[T(n)] = O(n)$.

**Intuition:** On average, we eliminate a constant fraction of elements at each step, giving a geometric series summing to $O(n)$.

---

## 9.3 Selection in Worst-Case Linear Time

### SELECT Algorithm (Median-of-Medians)

Deterministic $O(n)$ worst-case selection by choosing a **good pivot** guaranteed to produce a balanced split.

```
SELECT(A, p, r, i)
1  n = r - p + 1
2  if n <= 140
3      sort A[p:r] directly; return A[p+i-1]
4  divide A[p:r] into ceil(n/5) groups of 5 (last group may be smaller)
5  find the median of each group (by sorting)
6  copy medians into array M[1:ceil(n/5)]
7  median-of-medians = SELECT(M, 1, ceil(n/5), floor(ceil(n/5)/2))
8  partition A[p:r] around median-of-medians, let pivot rank = k
9  if i == k
10     return median-of-medians
11 elseif i < k
12     return SELECT(A, p, q-1, i)
13 else
14     return SELECT(A, q+1, r, i-k)
```

### Why the Pivot is Good

**Key bound:** At least $3n/10 - 6$ elements are $\leq$ the median-of-medians, and similarly at least $3n/10 - 6$ elements are $\geq$ it.

**Proof:**
- $\lceil n/5 \rceil$ groups → at least $\lceil \lceil n/5 \rceil / 2 \rceil \geq \lceil n/10 \rceil$ groups have their median $\leq$ the pivot
- Each such group contributes at least 3 elements $\leq$ pivot (in the group of 5, at least 3 are $\leq$ their median)
- Total: $\geq 3\lceil n/10 \rceil \geq 3n/10 - 6$ elements $\leq$ pivot

**Maximum subarray size:** $n - (3n/10 - 6) = 7n/10 + 6$

### Worst-Case Analysis

$$T(n) \leq T(\lceil n/5 \rceil) + T(7n/10 + 6) + O(n)$$

**Solution:** $T(n) = O(n)$ — verified by substitution with $T(n) \leq cn$ for large enough $c$.

The two recursive calls sum to: $cn/5 + c + 7cn/10 + 6c + an = 9cn/10 + 7c + an \leq cn$ when $c \geq 10a + 70c/10$, which holds for $c \geq 20a$.

---

## Comparison: Randomized vs. Deterministic Selection

| Property | RANDOMIZED-SELECT | SELECT (median-of-medians) |
|---|---|---|
| Expected time | $\Theta(n)$ | $\Theta(n)$ |
| Worst-case time | $\Theta(n^2)$ | $\Theta(n)$ |
| Practical speed | Faster | Slower (large constants) |
| Pivot choice | Random | Median-of-medians |

**Practical note:** RANDOMIZED-SELECT is preferred in practice due to smaller constants. SELECT is primarily of theoretical importance (proving $O(n)$ worst-case is achievable).

---

## Key Results Summary

| Problem | Algorithm | Comparisons |
|---|---|---|
| Find minimum | MINIMUM | $n-1$ (optimal) |
| Find maximum | MINIMUM variant | $n-1$ (optimal) |
| Find both min and max | Pair-comparison | $3\lfloor n/2 \rfloor$ |
| $i$th order statistic (expected) | RANDOMIZED-SELECT | $\Theta(n)$ |
| $i$th order statistic (worst case) | SELECT | $\Theta(n)$ |

---

### Navigation
**Previous:** [[Ch8_Sorting_in_Linear_Time]]
**Next:** [[Part3_Introduction_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
