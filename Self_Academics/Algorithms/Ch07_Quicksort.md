# Chapter 7: Quicksort

## Executive Summary

Chapter 7 presents **quicksort** — the most widely used sorting algorithm in practice. It sorts in-place via the divide-and-conquer paradigm using **partitioning**: choose a pivot, rearrange so all elements $\leq$ pivot come before it and all elements $>$ pivot come after, then recurse on both sides. Worst-case running time is $\Theta(n^2)$ (maximally unbalanced partitions), but the **expected running time** of the randomized version is $\Theta(n \log_2 n)$ for any input. The analysis uses indicator random variables to count comparisons: $E[\text{comparisons}] = O(n \log_2 n)$ because any pair $z_i, z_j$ is compared with probability exactly $\frac{2}{j - i + 1}$.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**QUICKSORT** — divide-and-conquer sort on $A[p:r]$:

```
QUICKSORT(A, p, r)
1  if p < r
2      q = PARTITION(A, p, r)     // partition around pivot, pivot ends at A[q]
3      QUICKSORT(A, p, q – 1)     // recursively sort low side
4      QUICKSORT(A, q + 1, r)     // recursively sort high side
```

**PARTITION** — rearranges $A[p:r]$ in place, returns pivot index (Lomuto partition scheme, pivot = $A[r]$):

```
PARTITION(A, p, r)
1  x = A[r]                       // pivot
2  i = p – 1                      // highest index into low side
3  for j = p to r – 1             // process each element other than pivot
4      if A[j] ≤ x
5          i = i + 1
6          exchange A[i] with A[j]
7  exchange A[i + 1] with A[r]    // put pivot in correct place
8  return i + 1                   // new index of pivot
```

*Loop invariant:* At the start of each iteration: (1) $A[p:i] \leq x$; (2) $A[i+1:j-1] > x$; (3) $A[r] = x$.

**RANDOMIZED-PARTITION** — randomly select pivot before partitioning:

```
RANDOMIZED-PARTITION(A, p, r)
1  i = RANDOM(p, r)
2  exchange A[r] with A[i]
3  return PARTITION(A, p, r)
```

**RANDOMIZED-QUICKSORT** — randomized version for guaranteed expected performance:

```
RANDOMIZED-QUICKSORT(A, p, r)
1  if p < r
2      q = RANDOMIZED-PARTITION(A, p, r)
3      RANDOMIZED-QUICKSORT(A, p, q – 1)
4      RANDOMIZED-QUICKSORT(A, q + 1, r)
```

---

## Deep-Dive Explanations

### The Partition Procedure

PARTITION runs in $\Theta(n)$ on a subarray of size $n = r - p + 1$: the for loop makes exactly $r - p$ iterations, each doing $O(1)$ work.

After PARTITION, the pivot $A[q]$ is in its final sorted position: every element in $A[p:q-1] \leq A[q]$ and every element in $A[q+1:r] \geq A[q]$. The two subarrays can be sorted independently.

### Time and Space Complexity Analysis

#### Worst Case: $\Theta(n^2)$

Worst case = maximally unbalanced partition every time: one side has $n-1$ elements, the other has $0$. Occurs when input is already sorted (ascending or descending) with deterministic pivot $= A[r]$.

Recurrence: $T(n) = T(n-1) + T(0) + \Theta(n) = T(n-1) + \Theta(n)$

Proof by substitution: guess $T(n) \leq cn^2$:
$$T(n) \leq c(n-1)^2 + \Theta(n) \leq cn^2 - c(2n-1) + \Theta(n) \leq cn^2$$

for $c$ large enough. Combined with $\Omega(n^2)$ lower bound (unbalanced case): $T(n) = \Theta(n^2)$ worst case.

#### Best Case: $\Theta(n \log_2 n)$

Best case = perfectly balanced partition every time: both halves $\leq n/2$.

Recurrence: $T(n) = 2T(n/2) + \Theta(n)$

By Master Theorem Case 2: $T(n) = \Theta(n \log_2 n)$.

#### Balanced Partitioning Insight

Any constant-proportion split (e.g., 9-to-1) yields $O(n \log_2 n)$:
$$T(n) = T(9n/10) + T(n/10) + \Theta(n)$$

Tree height = $\log_{10/9} n = \Theta(\log_2 n)$; each level costs $O(n)$ → total $O(n \log_2 n)$.

**Key insight:** Only splits that shrink one side by a constant factor matter — the exact ratio affects only the hidden constant. A 99-to-1 split still gives $O(n \log_2 n)$.

#### Expected Running Time: $\Theta(n \log_2 n)$ — Indicator Variable Analysis

**Lemma 7.1:** Running time of QUICKSORT = $O(n + X)$ where $X$ = total element comparisons.

**Lemma 7.2:** Elements $z_i$ and $z_j$ (with $z_i < z_j$) are compared if and only if one of $\{z_i, z_j\}$ is the first element chosen as pivot from the set $Z_{ij} = \{z_i, z_{i+1}, \ldots, z_j\}$.

**Lemma 7.3:** $\Pr\{z_i \text{ compared with } z_j\} = \dfrac{2}{j - i + 1}$

*Proof:* $|Z_{ij}| = j - i + 1$; each element equally likely to be chosen first; $z_i$ and $z_j$ are compared iff one of them is first → probability $= \frac{1}{j-i+1} + \frac{1}{j-i+1} = \frac{2}{j-i+1}$.

**Theorem 7.4 (Expected running time):**

Let $X_{ij} = I\{z_i \text{ compared with } z_j\}$. Then:

$$E[X] = \sum_{i=1}^{n-1} \sum_{j=i+1}^{n} \frac{2}{j-i+1}$$

Substituting $k = j - i$:

$$E[X] = \sum_{i=1}^{n-1} \sum_{k=1}^{n-i} \frac{2}{k+1} < \sum_{i=1}^{n-1} \sum_{k=1}^{n} \frac{2}{k} = \sum_{i=1}^{n-1} O(\log_2 n) = O(n \log_2 n)$$

Combined with Lemma 7.1: **Expected running time of RANDOMIZED-QUICKSORT = $O(n \log_2 n)$**.

Since best-case is $\Theta(n \log_2 n)$: **expected running time = $\Theta(n \log_2 n)$**.

#### Space Complexity

Quicksort is **in-place** (only $O(1)$ extra array elements outside input). However, the recursion stack depth is $O(\log_2 n)$ expected, $\Theta(n)$ worst case.

### Algorithm Summary

| Version | Worst Case | Expected/Average | Space (stack) | In-place? |
|---------|-----------|-----------------|---------------|-----------|
| QUICKSORT | $\Theta(n^2)$ | $\Theta(n \log_2 n)$ (avg) | $\Theta(n)$ worst | Yes |
| RANDOMIZED-QUICKSORT | $\Theta(n^2)$ | $\Theta(n \log_2 n)$ (expected) | $O(\log_2 n)$ expected | Yes |

### Quicksort vs. Other Sorts

Quicksort outperforms heapsort and merge sort in practice due to:
- Tight inner loop (fewer cache misses)
- Small constant factors hidden in $O$-notation
- Good average-case behavior on random inputs

Downsides: $\Theta(n^2)$ worst case (requires randomization to avoid), not stable, $O(\log_2 n)$ stack overhead.

---

## Key Takeaways & Next Steps

1. **Partitioning** is the core operation: PARTITION places the pivot at its final position in $\Theta(n)$ time.
2. **Balanced splits** → $O(n \log_2 n)$; **unbalanced splits** → $O(n^2)$. Any constant-proportion split is balanced enough.
3. **Randomization removes adversarial inputs**: RANDOMIZED-QUICKSORT has no worst-case input for its expected-time guarantee.
4. The indicator variable proof $\Pr\{z_i \text{ vs.} z_j\} = \frac{2}{j-i+1}$ is a canonical application of Chapter 5's techniques.
5. Quicksort analysis connects to harmonic series: $\sum_{k=1}^{n} 2/k = O(\log_2 n)$ per $i$.
6. Chapter 8 proves $\Omega(n \log_2 n)$ is optimal for comparison-based sorting, confirming quicksort's average-case optimality.

---

### Navigation

**Previous:** [[Ch06_Heapsort]]
**Next:** [[Ch08_Sorting_in_Linear_Time]]
**Hub:** [[Index_Introduction_to_Algorithms]]
