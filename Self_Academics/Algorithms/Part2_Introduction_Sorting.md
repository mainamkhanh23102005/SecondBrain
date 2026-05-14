# Part II Introduction: Sorting and Order Statistics

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #sorting

## Overview

Part II covers algorithms for the sorting problem — producing a permutation of $n$ numbers in non-decreasing order. It also addresses order statistics (finding the $i$th smallest element).

---

## The Sorting Problem

**Input:** A sequence $\langle a_1, a_2, \ldots, a_n \rangle$

**Output:** A permutation $\langle a_1', a_2', \ldots, a_n' \rangle$ such that $a_1' \leq a_2' \leq \cdots \leq a_n'$

Each item being sorted typically has a **key** (sort criterion) and **satellite data** (carried with the key during moves).

## Why Sorting is Fundamental

- Many applications directly need sorted output
- Sorting is a key subroutine in many other algorithms
- Rich variety of techniques used across sorting algorithms
- Provable lower bound: $\Omega(n \log_2 n)$ for comparison-based sorting
- Best algorithms achieve this asymptotically — making them optimal

## Chapters in This Part

| Chapter | Algorithm | Key Property |
|---|---|---|
| Ch 6 | Heapsort | $O(n \log_2 n)$, in-place, uses heap data structure |
| Ch 7 | Quicksort | $\Theta(n^2)$ worst, $\Theta(n \log_2 n)$ expected, in-place, practical fastest |
| Ch 8 | Linear-Time Sorting | $\Theta(n)$ time possible with non-comparison assumptions |
| Ch 9 | Medians & Order Statistics | $O(n)$ time to find $i$th smallest element |

## Comparison-Based Lower Bound

Any comparison-based sorting algorithm requires $\Omega(n \log_2 n)$ comparisons in the worst case (proved in Chapter 8 via decision trees).

---

### Navigation
**Previous:** [[Ch5_Probabilistic_Analysis_and_Randomized_Algorithms]]
**Next:** [[Ch6_Heapsort]]
**Hub:** [[Index_Introduction_to_Algorithms]]
