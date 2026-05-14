# Chapter 14: Dynamic Programming

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #dynamic-programming #optimization #memoization

## Overview

Dynamic programming (DP) solves problems by combining solutions to **overlapping subproblems**, storing each subproblem's solution to avoid recomputation. It applies to **optimization problems** and requires two key properties: **optimal substructure** and **overlapping subproblems**.

**Four-step DP design process:**
1. Characterize the structure of an optimal solution
2. Recursively define the value of an optimal solution
3. Compute the value bottom-up (or top-down with memoization)
4. Construct an optimal solution from computed information

---

## 14.1 Rod Cutting

**Problem:** Given a rod of length $n$ and prices $p_i$ for rods of length $i$, find the maximum revenue $r_n$ from cutting.

**Optimal substructure:** $r_n = \max_{1 \leq i \leq n} (p_i + r_{n-i})$

**Naive recursive solution:** $T(n) = 2^n$ — exponential (solves same subproblems repeatedly)

**Bottom-up DP:**

```
BOTTOM-UP-CUT-ROD(p, n)
1  let r[0:n] be a new array
2  r[0] = 0
3  for j = 1 to n
4      q = -∞
5      for i = 1 to j
6          q = max{q, p[i] + r[j-i]}
7      r[j] = q
8  return r[n]
```

**Complexity:** $\Theta(n^2)$ time, $\Theta(n)$ space.

**Memoized top-down:** Same $\Theta(n^2)$ asymptotic time, slightly higher overhead.

**Reconstruction:** Maintain array $s[j]$ = optimal first cut for length $j$; trace back with PRINT-CUT-ROD-SOLUTION.

---

## 14.2 Matrix-Chain Multiplication

**Problem:** Given chain $\langle A_1, A_2, \ldots, A_n \rangle$ with $A_i$ of dimension $p_{i-1} \times p_i$, find the parenthesization minimizing total scalar multiplications.

**Number of parenthesizations:** $\Omega(2^n)$ — brute force infeasible.

**Optimal substructure:** For any split at position $k$ (where $i \leq k < j$):
$$m[i,j] = m[i,k] + m[k+1,j] + p_{i-1} p_k p_j$$

**Recurrence:**
$$m[i,j] = \begin{cases} 0 & \text{if } i = j \\ \min_{i \leq k < j}\{m[i,k] + m[k+1,j] + p_{i-1} p_k p_j\} & \text{if } i < j \end{cases}$$

```
MATRIX-CHAIN-ORDER(p, n)
1  let m[1:n, 1:n] and s[1:n-1, 2:n] be new tables
2  for i = 1 to n: m[i,i] = 0
4  for l = 2 to n                  // l = chain length
5      for i = 1 to n-l+1
6          j = i + l - 1
7          m[i,j] = ∞
8          for k = i to j-1
9              q = m[i,k] + m[k+1,j] + p[i-1]*p[k]*p[j]
10             if q < m[i,j]
11                 m[i,j] = q; s[i,j] = k
13 return m and s
```

**Complexity:** $O(n^3)$ time, $\Theta(n^2)$ space.

---

## 14.3 Elements of Dynamic Programming

### Two Key Properties

**1. Optimal Substructure:** An optimal solution to a problem contains optimal solutions to subproblems.
- How to find it: make a choice → identify which subproblems remain → show subproblems' solutions must be optimal
- Varies by: number of subproblems × choices per subproblem

**2. Overlapping Subproblems:** The same subproblems recur — DP stores and reuses them.
- Contrast with divide-and-conquer: generates **new** subproblems at each step

### Memoization vs. Bottom-Up

| Approach | Method | When to prefer |
|---|---|---|
| **Top-down with memoization** | Recursive + cache | When not all subproblems need solving |
| **Bottom-up** | Iterative table-fill | Lower constant factor (no call overhead) |

**Caution — unrelated greedy-style traps:**
- Longest path ≠ shortest path (only the latter has optimal substructure for unweighted graphs)
- Cannot reuse independent subproblems when the same nodes appear in both

### Subproblem Graphs

A directed graph capturing subproblem dependencies. Bottom-up DP processes vertices in **reverse topological order**. Total running time = $O(V + E)$ of the subproblem graph.

---

## 14.4 Longest Common Subsequence (LCS)

**Problem:** Given sequences $X = \langle x_1, \ldots, x_m \rangle$ and $Y = \langle y_1, \ldots, y_n \rangle$, find the longest common subsequence.

**Optimal substructure:** Let $c[i,j]$ = length of LCS of $X[1:i]$ and $Y[1:j]$:

$$c[i,j] = \begin{cases} 0 & \text{if } i=0 \text{ or } j=0 \\ c[i-1,j-1] + 1 & \text{if } x_i = y_j \\ \max(c[i-1,j], c[i,j-1]) & \text{if } x_i \neq y_j \end{cases}$$

**Complexity:** $\Theta(mn)$ time and space.

---

## 14.5 Optimal Binary Search Trees

**Problem:** Given keys $k_1 < k_2 < \cdots < k_n$ with search probabilities $p_i$ and dummy-key probabilities $q_i$ (for unsuccessful searches), build a BST minimizing expected search cost.

**Expected cost:** $E[\text{search}] = \sum_{i=1}^n (d[k_i]+1) p_i + \sum_{j=0}^n (d[d_j]+1) q_j$

**Recurrence:** Let $e[i,j]$ = expected cost of optimal BST on $k_i, \ldots, k_j$, and $w[i,j] = \sum_{l=i}^{j} p_l + \sum_{l=i-1}^{j} q_l$:
$$e[i,j] = \min_{i \leq r \leq j}\{e[i,r-1] + e[r+1,j] + w[i,j]\}$$

**Complexity:** $O(n^3)$ time, $\Theta(n^2)$ space.

---

## DP Problem Summary

| Problem | Subproblems | Time | Space |
|---|---|---|---|
| Rod cutting | $O(n)$ | $\Theta(n^2)$ | $\Theta(n)$ |
| Matrix-chain | $O(n^2)$ | $\Theta(n^3)$ | $\Theta(n^2)$ |
| LCS | $O(mn)$ | $\Theta(mn)$ | $\Theta(mn)$ |
| Optimal BST | $O(n^2)$ | $\Theta(n^3)$ | $\Theta(n^2)$ |

---

### Navigation
**Previous:** [[Part4_Introduction_Advanced_Design]]
**Next:** [[Ch15_Greedy_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
