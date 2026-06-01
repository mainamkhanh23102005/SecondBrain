# Chapter 15: Greedy Algorithms

## Executive Summary

Chapter 15 presents **greedy algorithms** — algorithms that make locally optimal (greedy) choices at each step in the hope of finding a globally optimal solution. Unlike dynamic programming, which solves subproblems before making a choice, greedy algorithms make a choice first and solve only one remaining subproblem. Two key ingredients justify correctness: the **greedy-choice property** (a global optimal can be assembled from locally optimal choices) and **optimal substructure** (same as DP). The chapter develops three canonical problems: activity selection ($\Theta(n)$ after sorting), Huffman codes ($O(n\log_2 n)$), and offline caching (the "furthest-in-future" strategy). Greedy algorithms are also the basis for MST (Kruskal, Prim) and Dijkstra's shortest-path algorithm.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Activity Selection — recursive greedy ($\Theta(n)$ after sorting):**

Activities sorted by finish time: $f_1 \leq f_2 \leq \cdots \leq f_n$.

```
RECURSIVE-ACTIVITY-SELECTOR(s, f, k, n)
1  m = k + 1
2  while m ≤ n and s[m] < f[k]    // find first activity in Sk to finish
3      m = m + 1
4  if m ≤ n
5      return {am} ∪ RECURSIVE-ACTIVITY-SELECTOR(s, f, m, n)
6  else return ∅
```

**Activity Selection — iterative greedy ($\Theta(n)$ after sorting):**

```
GREEDY-ACTIVITY-SELECTOR(s, f, n)
1  A = {a1}               // always pick the first to finish
2  k = 1
3  for m = 2 to n
4      if s[m] ≥ f[k]     // am is compatible with last selected?
5          A = A ∪ {am}
6          k = m
7  return A
```

**Huffman Codes ($O(n\log_2 n)$ — builds optimal prefix-free code tree):**

```
HUFFMAN(C)                // C = set of characters with .freq attribute
 1  n = |C|
 2  Q = C                 // min-priority queue keyed on freq
 3  for i = 1 to n − 1
 4      allocate new node z
 5      x = EXTRACT-MIN(Q)
 6      y = EXTRACT-MIN(Q)
 7      z.left = x
 8      z.right = y
 9      z.freq = x.freq + y.freq
10      INSERT(Q, z)
11  return EXTRACT-MIN(Q)  // root of optimal prefix-free code tree
```

---

## Deep-Dive Explanations

### Two Key Ingredients for Greedy Correctness

**1. Greedy-Choice Property:** A globally optimal solution can be assembled by making locally optimal choices. You need not consider what choices led to the current state, nor future choices. Proof typically: take any optimal solution, show you can substitute the greedy choice and get an equally good (or better) solution.

**2. Optimal Substructure:** (Same as DP) An optimal solution to the problem contains within it optimal solutions to subproblems. Once the greedy choice is made, you have exactly one remaining subproblem.

### Greedy Algorithm Development Process

1. Cast the problem as: make a choice → one subproblem remains.
2. **Prove the greedy-choice property**: there always exists an optimal solution that includes the greedy choice (exchange argument).
3. **Demonstrate optimal substructure**: greedy choice + optimal subproblem solution = optimal overall solution.

### Activity-Selection Problem

**Problem:** Given $n$ activities with start times $s_i$ and finish times $f_i$, find a maximum-size set of mutually compatible activities (no two overlap).

**Greedy choice:** Always select the activity with the **earliest finish time** among those compatible with previously selected activities. This leaves the maximum time available for remaining activities.

**Theorem 15.1 (Greedy-choice property):** For any subproblem $S_k$, the activity $a_m$ with earliest finish time in $S_k$ belongs to some maximum-size subset of mutually compatible activities of $S_k$.

*Proof:* Let $A_k$ be any max-size subset; let $a_j$ be its earliest-finishing activity. If $a_j = a_m$, done. Otherwise, substitute $a_m$ for $a_j$ — since $f_m \leq f_j$, all activities compatible with $a_j$ remain compatible with $a_m$. The new set has the same size and includes $a_m$.

**Complexity:** $\Theta(n)$ if pre-sorted; $O(n\log_2 n)$ including the sort.

### Huffman Codes

**Problem:** Given $n$ characters with known frequencies $c.\text{freq}$, find a prefix-free binary code minimizing total bits = $\sum_{c \in C} c.\text{freq} \cdot d_T(c)$ where $d_T(c)$ = depth of character $c$ in the code tree.

**Key insight:** Represent code as a full binary tree; leaves = characters; depth = codeword length. Optimal code trees are full binary trees.

**Greedy choice:** Always merge the two lowest-frequency nodes. This is the greedy-choice property: the two characters with lowest frequencies should be deepest in the tree (longest codewords).

**Lemma 15.2 (Greedy-choice property for Huffman):** If $x$ and $y$ are the two lowest-frequency characters, there exists an optimal prefix-free code in which $x$ and $y$ are sibling leaves at maximum depth.

**Correctness:** Huffman's algorithm satisfies both the greedy-choice property (Lemma 15.2) and optimal substructure — the tree for $C - \{x, y\} \cup \{z\}$ (where $z$ = merged node) is optimal, implying the full tree is optimal.

**Complexity:** $O(n\log_2 n)$ using a binary min-heap for the priority queue. ($n-1$ iterations, each taking $O(\log_2 n)$ for heap operations.)

### Greedy vs. Dynamic Programming: Knapsack Example

| Problem | Greedy Works? | Why |
|---------|--------------|-----|
| **Fractional knapsack** | Yes | Can take fractions; greedy by value/weight ratio is optimal |
| **0-1 knapsack** | No | Must take whole items; greedy leaves wasted capacity |

The 0-1 knapsack has overlapping subproblems and requires DP ($O(nW)$ time). The fractional knapsack can be solved greedily in $O(n\log_2 n)$ (sort by $v_i/w_i$, take greedily).

**Key distinction:** In DP, choices depend on subproblem solutions (bottom-up). In greedy, choices depend only on the current state (top-down, no reconsideration).

### Time and Space Complexity

| Algorithm | Time | Space | Condition |
|-----------|------|-------|-----------|
| GREEDY-ACTIVITY-SELECTOR | $\Theta(n)$ | $O(1)$ | Pre-sorted by finish time |
| Activity selection (including sort) | $O(n\log_2 n)$ | $O(1)$ | |
| HUFFMAN | $O(n\log_2 n)$ | $O(n)$ | Binary min-heap |
| Fractional knapsack | $O(n\log_2 n)$ | $O(1)$ | Sort by $v_i/w_i$ |

---

## Key Takeaways & Next Steps

1. **Greedy algorithms are correct when the greedy-choice property holds**: you can always make the locally optimal choice without worrying about future consequences.
2. **Proof strategy**: exchange argument — take any optimal solution, show substituting the greedy choice yields an equally good or better solution.
3. **Greedy vs. DP distinction**: DP solves subproblems before choosing; greedy chooses before solving. The greedy-choice property collapses the DP choice space to a single option.
4. **Huffman coding** is the canonical application: building optimal compression codes using a min-priority queue in $O(n\log_2 n)$.
5. Greedy algorithms underlie key graph algorithms: MST (Kruskal/Prim), single-source shortest paths (Dijkstra).

---

### Navigation

**Previous:** [[Ch14_Dynamic_Programming]]
**Next:** [[Ch16_Amortized_Analysis]]
**Hub:** [[Index_Introduction_to_Algorithms]]
