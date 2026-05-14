# Chapter 15: Greedy Algorithms

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #greedy #activity-selection #huffman #optimization

## Overview

A **greedy algorithm** makes the locally optimal choice at each step, hoping it leads to a globally optimal solution. Unlike dynamic programming (which solves subproblems before making choices), greedy algorithms make a choice first, then solve the remaining subproblem. Greedy works when the problem has the **greedy-choice property** and **optimal substructure**.

---

## 15.1 Activity-Selection Problem

**Problem:** Given $n$ activities with start/finish times, find the maximum-size set of mutually compatible (non-overlapping) activities.

**Greedy choice:** Always select the activity with the **earliest finish time** — leaves maximum room for remaining activities.

**Theorem 15.1:** The activity with earliest finish time is always included in some optimal solution (proof by exchange argument).

```
GREEDY-ACTIVITY-SELECTOR(s, f, n)
1  A = {a1}               // select the first to finish
2  k = 1
3  for m = 2 to n
4      if s[m] >= f[k]    // am is compatible with ak?
5          A = A ∪ {am}
6          k = m
7  return A
```

**Complexity:** $\Theta(n)$ (assuming pre-sorted by finish time; $O(n \log_2 n)$ including sort).

---

## 15.2 Elements of the Greedy Strategy

### Two Key Properties

**1. Greedy-choice property:** A globally optimal solution can be assembled by making locally optimal (greedy) choices. The greedy choice does not depend on subproblem solutions — it's made before solving any subproblems.

**2. Optimal substructure:** An optimal solution contains optimal solutions to subproblems (same as for DP).

### Greedy vs. Dynamic Programming

| Aspect | Dynamic Programming | Greedy |
|---|---|---|
| Choice timing | After solving subproblems | Before solving subproblems |
| Direction | Bottom-up (typically) | Top-down |
| Choices considered | All (exhaustive) | One (locally optimal) |
| Correctness | Always (if OS + OVS) | Only when greedy-choice property holds |

### Knapsack Example: Greedy vs. DP

- **Fractional knapsack:** Greedy works — sort by value/weight, take greedily. $O(n \log_2 n)$.
- **0-1 knapsack:** Greedy fails — must consider all item combinations. Requires DP: $O(nW)$.

**Insight:** Greedy fails for 0-1 knapsack because taking an item leaves a "hole" in the knapsack that can't always be optimally filled.

---

## 15.3 Huffman Codes

**Problem:** Given character frequencies, find a **prefix-free binary code** (no codeword is a prefix of another) that minimizes the total encoding length.

**Key insight:** Represent the code as a full binary tree where leaves are characters. The cost of the tree is:
$$B(T) = \sum_{c \in C} c.freq \cdot d_T(c)$$
where $d_T(c)$ = depth (= codeword length) of character $c$.

**Optimal substructure:** In an optimal tree, the two least-frequent characters have the longest codewords and are siblings at the deepest level.

**Greedy approach:** Build tree bottom-up — always merge the two least-frequent nodes.

```
HUFFMAN(C)
1  n = |C|
2  Q = C                              // min-priority queue by frequency
3  for i = 1 to n-1
4      allocate a new node z
5      z.left = x = EXTRACT-MIN(Q)
6      z.right = y = EXTRACT-MIN(Q)
7      z.freq = x.freq + y.freq
8      INSERT(Q, z)
9  return EXTRACT-MIN(Q)              // return the root of the tree
```

**Complexity:** $O(n \log_2 n)$ using a min-heap.

**Correctness:** The greedy-choice property holds because the two lowest-frequency characters must be at the deepest level in any optimal tree (by an exchange argument). Optimal substructure follows because the merged subtree is itself an optimal code for the combined character.

---

## 15.4 Offline Caching (Furthest-in-Future)

**Problem:** Given a cache of size $k$ and a sequence of block requests, minimize cache misses when block evictions must be chosen.

**Greedy strategy (FURTHEST-IN-FUTURE / OPT):** On a miss, evict the block whose next use is **furthest in the future** (or never used again).

**Theorem 15.3 (Sleator & Tarjan):** FURTHEST-IN-FUTURE is an optimal offline caching algorithm.

**Proof:** By an exchange argument — any eviction choice that differs from FURTHEST-IN-FUTURE can be modified to agree with it without increasing total misses.

**Note:** This requires knowing the future access sequence (offline algorithm). Online algorithms (like LRU, FIFO) cannot achieve this optimality in general.

---

## Greedy Algorithm Design Recipe

1. Cast the problem as making one choice and being left with one subproblem
2. Prove a greedy choice is always safe (greedy-choice property)
3. Show optimal substructure: greedy choice + optimal subproblem solution = optimal overall solution
4. Implement, usually iteratively

---

## Summary of Key Results

| Problem | Greedy Strategy | Complexity |
|---|---|---|
| Activity selection | Earliest finish time | $\Theta(n)$ after sorting |
| Fractional knapsack | Highest value/weight first | $O(n \log_2 n)$ |
| Huffman coding | Merge two lowest-frequency nodes | $O(n \log_2 n)$ |
| Offline caching | Evict furthest-in-future | $O(nk)$ |

---

### Navigation
**Previous:** [[Ch14_Dynamic_Programming]]
**Next:** [[Ch16_Amortized_Analysis]]
**Hub:** [[Index_Introduction_to_Algorithms]]
