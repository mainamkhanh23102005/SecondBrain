# Chapter 8: Sorting in Linear Time

## Executive Summary

Chapter 8 first proves that **any comparison sort requires $\Omega(n \log_2 n)$ comparisons** in the worst case (via the decision-tree model), establishing that heapsort and merge sort are asymptotically optimal. It then presents three **non-comparison sorts** that bypass this lower bound by exploiting structural knowledge about keys: **counting sort** ($\Theta(n+k)$, integers in $[0,k]$), **radix sort** ($\Theta(d(n+k))$, $d$-digit numbers), and **bucket sort** ($\Theta(n)$ average, uniform distribution). All three achieve linear time in the right domain, but trade generality for speed.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**COUNTING-SORT** — sorts integers in $[0,k]$:

```
COUNTING-SORT(A, n, k)
 1  let B[1 : n] and C[0 : k] be new arrays
 2  for i = 0 to k
 3      C[i] = 0                              // initialize counts
 4  for j = 1 to n
 5      C[A[j]] = C[A[j]] + 1                 // count occurrences
 6  // C[i] now contains number of elements equal to i
 7  for i = 1 to k
 8      C[i] = C[i] + C[i – 1]               // prefix sum: count ≤ i
 9  // C[i] now contains number of elements ≤ i
10  for j = n downto 1                        // reverse for stability
11      B[C[A[j]]] = A[j]
12      C[A[j]] = C[A[j]] – 1                 // decrement for duplicates
13  return B
```

**RADIX-SORT** — sorts $d$-digit numbers least-significant digit first:

```
RADIX-SORT(A, n, d)
1  for i = 1 to d
2      use a stable sort to sort array A[1 : n] on digit i
```

**BUCKET-SORT** — sorts $n$ reals uniform in $[0,1)$:

```
BUCKET-SORT(A, n)
1  let B[0 : n – 1] be a new array of empty lists
2  for i = 0 to n – 1
3      make B[i] an empty list
4  for i = 1 to n
5      insert A[i] into list B[⌊n · A[i]⌋]
6  for i = 0 to n – 1
7      sort list B[i] with insertion sort
8  concatenate lists B[0], B[1], … , B[n – 1] in order
9  return the concatenated lists
```

---

## Deep-Dive Explanations

### The Decision-Tree Lower Bound

**Model:** A **decision tree** is a full binary tree abstracting a comparison sort:
- Internal node $i:j$: compare $a_i$ vs $a_j$
- Left subtree: $a_i \leq a_j$; right subtree: $a_i > a_j$
- Each leaf: one possible sorted permutation

For a correct comparison sort on $n$ elements, every permutation must appear as a reachable leaf → at least $n!$ reachable leaves.

**Theorem 8.1:** Any comparison sort requires $\Omega(n \log_2 n)$ comparisons in the worst case.

*Proof:* A binary tree of height $h$ has at most $2^h$ leaves. Since the tree must have $\geq n!$ reachable leaves:
$$n! \leq 2^h \implies h \geq \log_2(n!) = \Omega(n \log_2 n)$$

using $\log_2(n!) = \Theta(n \log_2 n)$ from Stirling's approximation.

**Corollary 8.2:** Heapsort and merge sort are asymptotically optimal comparison sorts — their $O(n \log_2 n)$ upper bounds match the $\Omega(n \log_2 n)$ lower bound.

### Time and Space Complexity Analysis

#### Counting Sort: $\Theta(n + k)$

- Lines 2–3: $\Theta(k)$ — initialize count array
- Lines 4–5: $\Theta(n)$ — count occurrences
- Lines 7–8: $\Theta(k)$ — prefix sums
- Lines 10–12: $\Theta(n)$ — place elements in output
- **Total: $\Theta(n + k)$**. When $k = O(n)$: $\Theta(n)$.

**Stability:** The reverse loop (line 10: $j = n$ downto $1$) preserves relative order of equal elements → counting sort is **stable**. Critical for use as a subroutine in radix sort.

**Space:** $\Theta(n + k)$ — not in-place.

#### Radix Sort: $\Theta(d(n + k))$

**Key insight:** Sort on **least-significant digit first** (not most-significant), using a stable sort for each digit pass.

**Lemma 8.3:** Given $n$ $d$-digit numbers with digits in $[0, k-1]$, RADIX-SORT runs in $\Theta(d(n+k))$ time using counting sort as the stable subroutine.

**Optimizing digit size (Lemma 8.4):** For $n$ $b$-bit numbers, split into $d = \lceil b/r \rceil$ digits of $r$ bits each ($k = 2^r$). Running time: $\Theta((b/r)(n + 2^r))$.

Optimal $r = \lfloor \log_2 n \rfloor$ when $b \geq \lfloor \log_2 n \rfloor$, giving $\Theta(bn / \log_2 n)$.

When $b = O(\log_2 n)$ and $r = \log_2 n$: radix sort runs in $\Theta(n)$.

**Space:** Not in-place — requires auxiliary arrays.

#### Bucket Sort: $\Theta(n)$ Average Case

Assumption: input drawn from **uniform distribution** over $[0,1)$.

All lines except line 7 take $O(n)$ worst case. For the insertion sorts: let $n_i$ = number of elements in bucket $B[i]$.

$$T(n) = O(n) + \sum_{i=0}^{n-1} O(n_i^2)$$

Each element goes into bucket $B[i]$ with probability $1/n$ (uniform distribution). So $n_i \sim \text{Binomial}(n, 1/n)$.

$$E[n_i^2] = \text{Var}[n_i] + E^2[n_i] = \left(1 - \frac{1}{n}\right) + 1^2 = 2 - \frac{1}{n}$$

Therefore:
$$E[T(n)] = O(n) + n \cdot O\!\left(2 - \frac{1}{n}\right) = \Theta(n)$$

**Worst case:** $\Theta(n^2)$ (all elements in one bucket, insertion sort degrades).

### Algorithm Comparison

| Algorithm | Time | Space | In-place? | Stable? | Requirement |
|-----------|------|-------|-----------|---------|-------------|
| Counting sort | $\Theta(n+k)$ | $\Theta(n+k)$ | No | Yes | Integers in $[0,k]$ |
| Radix sort | $\Theta(d(n+k))$ | $\Theta(n+k)$ | No | Yes (if subroutine stable) | $d$-digit numbers, radix $k$ |
| Bucket sort | $\Theta(n)$ avg, $\Theta(n^2)$ worst | $\Theta(n)$ | No | No (depends on impl.) | Uniform distribution on $[0,1)$ |

---

## Key Takeaways & Next Steps

1. **$\Omega(n \log_2 n)$ is a hard lower bound** for comparison sorts — proven by counting leaves in a decision tree ($n!$ permutations require $\geq \log_2(n!) = \Omega(n \log_2 n)$ tree height).
2. **Non-comparison sorts break this bound** by using structural domain knowledge, not just pairwise comparisons.
3. **Counting sort's stability** is essential — radix sort correctness depends on it.
4. **Radix sort is counterintuitive** — sorting least-significant digit first works because stable sorting preserves prior-pass order.
5. **Bucket sort's linear time** assumes uniform distribution; with arbitrary distributions it can degrade to $\Theta(n^2)$.
6. These linear-time sorts are critical subroutines in many applications (e.g., suffix arrays, key sorting in graph algorithms).

---

### Navigation

**Previous:** [[Ch07_Quicksort]]
**Next:** [[Ch09_Medians_and_Order_Statistics]]
**Hub:** [[Index_Introduction_to_Algorithms]]
