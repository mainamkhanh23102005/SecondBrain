# Chapter 9: Medians and Order Statistics

## Executive Summary

Chapter 9 solves the **selection problem**: finding the $i$-th smallest element from $n$ elements without sorting. Section 9.1 shows minimum/maximum take exactly $n-1$ comparisons (optimal), and simultaneous min+max only needs $3\lfloor n/2 \rfloor$ comparisons. Section 9.2 presents **RANDOMIZED-SELECT**, a quicksort-style algorithm with $\Theta(n)$ expected time (but $\Theta(n^2)$ worst case). Section 9.3 presents **SELECT** (median-of-medians), a deterministic algorithm achieving $\Theta(n)$ worst-case time via a cleverly chosen pivot that guarantees at least $3n/10$ elements on each side of the partition.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**MINIMUM** — finds minimum with $n-1$ comparisons (optimal):

```
MINIMUM(A, n)
1  min = A[1]
2  for i = 2 to n
3      if min > A[i]
4          min = A[i]
5  return min
```

**RANDOMIZED-SELECT** — returns the $i$-th smallest of $A[p:r]$:

```
RANDOMIZED-SELECT(A, p, r, i)
1  if p == r
2      return A[p]
3  q = RANDOMIZED-PARTITION(A, p, r)
4  k = q – p + 1                        // rank of pivot A[q] within A[p:r]
5  if i == k
6      return A[q]                       // pivot is the answer
7  elseif i < k
8      return RANDOMIZED-SELECT(A, p, q – 1, i)
9  else return RANDOMIZED-SELECT(A, q + 1, r, i – k)
```

**SELECT** (median-of-medians, worst-case linear):

```
SELECT(A, p, r, i)
 1  while (r – p + 1) mod 5 ≠ 0
 2      for j = p + 1 to r
 3          if A[p] > A[j]
 4              exchange A[p] with A[j]  // put minimum at A[p]
 5      if i == 1
 6          return A[p]
 7      p = p + 1;  i = i – 1           // remove minimum, adjust rank
 8  g = (r – p + 1) / 5                 // number of 5-element groups
 9  for j = p to p + g – 1
10      sort ⟨A[j], A[j+g], A[j+2g], A[j+3g], A[j+4g]⟩ in place
11  // group medians now in A[p+2g : p+3g–1]
12  x = SELECT(A, p + 2g, p + 3g – 1, ⌈g/2⌉)  // pivot = median of medians
13  q = PARTITION-AROUND(A, p, r, x)
14  k = q – p + 1
15  if i == k
16      return A[q]
17  elseif i < k
18      return SELECT(A, p, q – 1, i)
19  else return SELECT(A, q + 1, r, i – k)
```

---

## Deep-Dive Explanations

### Minimum and Maximum

**Minimum:** MINIMUM uses exactly $n-1$ comparisons — optimal because every element except the minimum must "lose" at least one comparison (tournament argument).

**Simultaneous min and max:** Naïve: $(n-1) + (n-1) = 2n-2$ comparisons. Better: process elements in pairs:
1. Compare each pair against each other: 1 comparison
2. Compare smaller of pair with current minimum: 1 comparison
3. Compare larger of pair with current maximum: 1 comparison
4. Total: 3 comparisons per 2 elements → at most $3\lfloor n/2 \rfloor$ total.

### Time and Space Complexity Analysis

#### RANDOMIZED-SELECT: $\Theta(n)$ Expected, $\Theta(n^2)$ Worst

**Worst case:** $\Theta(n^2)$ — same as quicksort worst case. Occurs if pivot always chosen at extreme rank, giving $T(n) = T(n-1) + \Theta(n) = \Theta(n^2)$.

**Expected time (Theorem 9.2):** Key lemma: a partitioning is **helpful** if it reduces the remaining set to $\leq 3/4$ of its current size.

**Lemma 9.1:** A partitioning is helpful with probability $\geq 1/2$ (pivot falls in middle half with probability $\geq 1/2$).

Since each helpful partitioning shrinks size by factor $3/4$, at most $\lceil \log_{4/3} n \rceil$ helpful partitionings occur. Expected number of unhelpful partitionings between two consecutive helpful ones $= E[X_k] \leq 2$ (geometric distribution with $p \geq 1/2$).

Total expected comparisons $< \sum_{k=0}^{m} 2 \cdot n_k$ where $n_k \leq (3/4)^k n$:
$$E[\text{comparisons}] < 2n \sum_{k=0}^{\infty} \left(\frac{3}{4}\right)^k = 2n \cdot 4 = 8n = O(n)$$

**Lower bound:** First call examines all $n$ elements → $\Omega(n)$. Therefore: **expected running time = $\Theta(n)$**.

#### SELECT (Median-of-Medians): $\Theta(n)$ Worst Case

**Algorithm steps:**
1. Pad to multiple of 5 (while loop, O(n) total)
2. Divide into $g = \lfloor n/5 \rfloor$ groups of 5; sort each group in $\Theta(1)$ → $\Theta(n)$ total
3. All group medians lie in $A[p+2g : p+3g-1]$
4. Recursively call SELECT to find median of group medians: $T(n/5)$
5. Partition around this pivot $x$: $\Theta(n)$
6. Recurse on one side

**Pivot quality guarantee:** Of the $g$ group medians, at least $\lceil g/2 \rceil$ are $\geq x$ (the median of medians). For each of these medians, 3 elements in its group are $\geq$ that median $\geq x$. So at least $3\lceil g/2 \rceil \geq 3n/10$ elements are $\geq x$. Symmetrically, $\geq 3n/10$ elements are $\leq x$.

**Bound on recursive subproblem:** At most $n - 3\lceil g/2 \rceil \leq n - 3n/10 = 7n/10$ elements (roughly) remain in either recursive call.

**Recurrence (Theorem 9.3):**
$$T(n) \leq T\!\left(\frac{n}{5}\right) + T\!\left(\frac{7n}{10}\right) + \Theta(n)$$

Solved by substitution: guess $T(n) \leq cn$. Then:
$$T(n) \leq c\frac{n}{5} + c\frac{7n}{10} + an = c\frac{9n}{10} + an \leq cn$$

when $c \geq 10a$. Note $\frac{1}{5} + \frac{7}{10} = \frac{9}{10} < 1$, ensuring the geometric series converges.

**Result: $T(n) = \Theta(n)$ worst case.**

### Algorithm Comparison

| Algorithm | Time | Space | Notes |
|-----------|------|-------|-------|
| Naive (sort then index) | $O(n \log_2 n)$ | $O(1)$ | |
| RANDOMIZED-SELECT | $\Theta(n)$ expected, $\Theta(n^2)$ worst | $O(\log_2 n)$ recursion | Practical |
| SELECT (median-of-medians) | $\Theta(n)$ worst | $O(\log_2 n)$ recursion | Mostly theoretical |

**Why groups of 5?** Groups of 3 give only $\frac{1}{3} + \frac{2}{3} \cdot \frac{2}{3} = 1$ → doesn't converge. Groups of 7 also work but with larger constants. 5 is the minimum odd number that guarantees a better-than-$9/10$ sum.

---

## Key Takeaways & Next Steps

1. **Selection is easier than sorting**: $O(n)$ vs $\Omega(n \log_2 n)$ — you don't need to fully sort to find the $i$-th element.
2. **RANDOMIZED-SELECT** is the practical choice: simpler, faster constants than SELECT despite worse worst case.
3. **SELECT's pivot trick** (median of medians) is a landmark theoretical result — it guarantees $\geq 3n/10$ elements on each partition side deterministically.
4. The recurrence $T(n) \leq T(n/5) + T(7n/10) + \Theta(n)$ is solvable because $1/5 + 7/10 = 9/10 < 1$.
5. Simultaneous min/max in $3\lfloor n/2 \rfloor$ comparisons is a practical optimization worth knowing.
6. Selection algorithms are used in statistical analysis, data streaming, and as subroutines in computational geometry.

---

### Navigation

**Previous:** [[Ch08_Sorting_in_Linear_Time]]
**Next:** [[PartIII_Introduction_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
