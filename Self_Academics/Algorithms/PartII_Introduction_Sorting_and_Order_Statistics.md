# Part II: Sorting and Order Statistics — Introduction

## Executive Summary

Part II presents the core algorithms for the **sorting problem**: rearranging $n$ numbers into non-decreasing order. The part covers six sorting algorithms across four chapters (6–9), ranging from comparison-based sorts ($\Omega(n \log_2 n)$ lower bound proven in Chapter 8) to non-comparison sorts that achieve linear time under restricted input assumptions. Chapter 9 extends the framework to **order statistics** — finding the $i$-th smallest element in $O(n)$ time.

---

## Zero-Loss Extraction

### The Sorting Problem

**Input:** A sequence of $n$ numbers $\langle a_1, a_2, \ldots, a_n \rangle$.

**Output:** A permutation $\langle a_1', a_2', \ldots, a_n' \rangle$ such that $a_1' \leq a_2' \leq \cdots \leq a_n'$.

**Key structure note:** In practice, numbers being sorted are part of **records** with a **key** (the sorted value) and **satellite data** (carried along). When satellite data is large, sort an array of pointers to records rather than the records themselves to minimize data movement.

### Sorting Algorithms — Running Time Summary

| Algorithm | Worst-case | Average-case/Expected | In-place? |
|-----------|-----------|----------------------|-----------|
| Insertion sort | $\Theta(n^2)$ | $\Theta(n^2)$ | Yes |
| Merge sort | $\Theta(n \log_2 n)$ | $\Theta(n \log_2 n)$ | No |
| Heapsort | $O(n \log_2 n)$ | — | Yes |
| Quicksort | $\Theta(n^2)$ | $\Theta(n \log_2 n)$ (expected) | Yes |
| Counting sort | $\Theta(k + n)$ | $\Theta(k + n)$ | No |
| Radix sort | $\Theta(d(n + k))$ | $\Theta(d(n + k))$ | No |
| Bucket sort | $\Theta(n^2)$ | $\Theta(n)$ (average) | No |

---

## Deep-Dive Explanations

### Why Sorting Matters

1. **Inherent need:** Many applications require sorted output (e.g., bank statements sorted by check number).
2. **Subroutine:** Sorting underlies algorithms throughout computer science (e.g., rendering ordered graphical objects).
3. **Rich techniques:** Sorting algorithms collectively demonstrate the widest range of algorithm design techniques.
4. **Provable optimality:** A $\Omega(n \log_2 n)$ lower bound (Chapter 8, decision-tree model) means comparison-based algorithms that match this bound are **asymptotically optimal**.
5. **Engineering depth:** Cache behavior, memory hierarchy, and satellite data all affect real-world sorting performance.

### Comparison Sorts vs. Non-Comparison Sorts

**Comparison sorts** (Insertion, Merge, Heap, Quick): determine order only by comparing pairs of elements. The decision-tree model proves their worst-case lower bound is $\Omega(n \log_2 n)$.

**Non-comparison sorts** can beat $\Omega(n \log_2 n)$ by exploiting structural knowledge of keys:

- **Counting sort:** Keys are integers in $\{0, 1, \ldots, k\}$ → $\Theta(k + n)$. Linear when $k = O(n)$.
- **Radix sort:** $d$-digit numbers with $k$ values per digit → $\Theta(d(n + k))$. Linear when $d$ and $k$ are constants.
- **Bucket sort:** Keys uniformly distributed in $[0, 1)$ → $\Theta(n)$ average-case.

### Order Statistics (Chapter 9)

The **$i$-th order statistic** of a set of $n$ numbers = the $i$-th smallest element.

Naïve approach: sort first → $\Omega(n \log_2 n)$. Chapter 9 achieves:
- **Randomized algorithm:** $\Theta(n^2)$ worst case, $O(n)$ expected (uses Chapter 5 probability tools).
- **Deterministic algorithm:** $O(n)$ worst case (more complex, uses median-of-medians).

---

## Key Takeaways & Next Steps

1. **Comparison sorts** cannot do better than $\Omega(n \log_2 n)$ in the worst case — proven rigorously in Chapter 8.
2. **Heapsort** and **merge sort** are asymptotically optimal comparison sorts; quicksort is preferred in practice despite worse worst-case due to small constants and cache behavior.
3. **Non-comparison sorts** achieve linear time at the cost of domain restrictions on keys.
4. **Order statistics** can be solved in $O(n)$ — no need to sort everything to find one element.
5. Understanding the trade-offs between these algorithms (in-place, stability, cache behavior, constant factors) is essential for choosing the right sort in practice.

---

### Navigation

**Previous:** [[Ch05_Probabilistic_Analysis_and_Randomized_Algorithms]]
**Next:** [[Ch06_Heapsort]]
**Hub:** [[Index_Introduction_to_Algorithms]]
