# Chapter 14: Dynamic Programming

## Executive Summary

Chapter 14 presents **dynamic programming (DP)** — a technique that transforms exponential-time problems into polynomial-time algorithms by solving each subproblem exactly once and storing its answer. DP applies to optimization problems with two key properties: **optimal substructure** (an optimal solution contains optimal solutions to subproblems) and **overlapping subproblems** (the same subproblems recur many times). The chapter develops four canonical problems: rod cutting ($\Theta(n^2)$), matrix-chain multiplication ($\Theta(n^3)$), longest common subsequence ($\Theta(mn)$), and optimal binary search trees ($\Theta(n^3)$). Two implementation styles — bottom-up and top-down with memoization — achieve the same asymptotic time.

---

## Zero-Loss Extraction

### The Four-Step DP Method

1. **Characterize** the structure of an optimal solution.
2. **Recursively define** the value of an optimal solution.
3. **Compute** the value (bottom-up or memoized top-down).
4. **Construct** an optimal solution from computed information.

### Core Algorithms & Pseudocode

**Rod Cutting — naive recursive (exponential $\Theta(2^n)$):**

```
CUT-ROD(p, n)
1  if n == 0
2      return 0
3  q = −∞
4  for i = 1 to n
5      q = max{q, p[i] + CUT-ROD(p, n − i)}
6  return q
```

**Rod Cutting — top-down with memoization ($\Theta(n^2)$):**

```
MEMOIZED-CUT-ROD(p, n)
1  let r[0:n] = all −∞
2  return MEMOIZED-CUT-ROD-AUX(p, n, r)

MEMOIZED-CUT-ROD-AUX(p, n, r)
1  if r[n] ≥ 0
2      return r[n]
3  if n == 0 then q = 0
4  else q = −∞
5       for i = 1 to n
6           q = max{q, p[i] + MEMOIZED-CUT-ROD-AUX(p, n − i, r)}
7  r[n] = q
8  return q
```

**Rod Cutting — bottom-up ($\Theta(n^2)$):**

```
BOTTOM-UP-CUT-ROD(p, n)
1  let r[0:n] be a new array
2  r[0] = 0
3  for j = 1 to n
4      q = −∞
5      for i = 1 to j
6          q = max{q, p[i] + r[j − i]}
7      r[j] = q
8  return r[n]
```

**Rod Cutting — extended (returns both value and cut locations):**

```
EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
1  let r[0:n] and s[1:n] be new arrays
2  r[0] = 0
3  for j = 1 to n
4      q = −∞
5      for i = 1 to j
6          if q < p[i] + r[j − i]
7              q = p[i] + r[j − i];  s[j] = i
8      r[j] = q
9  return r and s

PRINT-CUT-ROD-SOLUTION(p, n)
1  (r, s) = EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
2  while n > 0
3      print s[n]
4      n = n − s[n]
```

**Matrix-Chain Multiplication ($\Theta(n^3)$ time, $\Theta(n^2)$ space):**

Recurrence: $m[i, j] = \min_{i \leq k < j} \{ m[i,k] + m[k+1,j] + p_{i-1} p_k p_j \}$, with $m[i,i] = 0$.

```
MATRIX-CHAIN-ORDER(p, n)
 1  let m[1:n, 1:n] and s[1:n−1, 2:n] be new tables
 2  for i = 1 to n
 3      m[i, i] = 0
 4  for l = 2 to n                   // l = chain length
 5      for i = 1 to n − l + 1
 6          j = i + l − 1
 7          m[i, j] = ∞
 8          for k = i to j − 1
 9              q = m[i, k] + m[k+1, j] + p_{i−1} p_k p_j
10              if q < m[i, j]
11                  m[i, j] = q;  s[i, j] = k
12  return m and s

PRINT-OPTIMAL-PARENS(s, i, j)
1  if i == j then print "A"_i
2  else print "("
3       PRINT-OPTIMAL-PARENS(s, i, s[i,j])
4       PRINT-OPTIMAL-PARENS(s, s[i,j]+1, j)
5       print ")"
```

**Longest Common Subsequence ($\Theta(mn)$ time and space):**

Recurrence:
$$c[i,j] = \begin{cases} 0 & \text{if } i=0 \text{ or } j=0 \\ c[i-1,j-1]+1 & \text{if } x_i = y_j \\ \max(c[i-1,j],\; c[i,j-1]) & \text{if } x_i \neq y_j \end{cases}$$

```
LCS-LENGTH(X, Y, m, n)
 1  let b[1:m, 1:n] and c[0:m, 0:n] be new tables
 2  for i = 1 to m then c[i, 0] = 0
 3  for j = 0 to n then c[0, j] = 0
 4  for i = 1 to m
 5      for j = 1 to n
 6          if x_i == y_j
 7              c[i, j] = c[i−1, j−1] + 1;  b[i, j] = "↖"
 8          elseif c[i−1, j] ≥ c[i, j−1]
 9              c[i, j] = c[i−1, j];  b[i, j] = "↑"
10          else c[i, j] = c[i, j−1];  b[i, j] = "←"
11  return c and b

PRINT-LCS(b, X, i, j)
1  if i == 0 or j == 0 then return
2  if b[i, j] == "↖"
3      PRINT-LCS(b, X, i−1, j−1);  print x_i
4  elseif b[i, j] == "↑"
5      PRINT-LCS(b, X, i−1, j)
6  else PRINT-LCS(b, X, i, j−1)
```

---

## Deep-Dive Explanations

### Two Key Properties for DP Applicability

**1. Optimal Substructure:** An optimal solution incorporates optimal solutions to subproblems. Verified via "cut-and-paste": if a subproblem solution within an optimal solution were not optimal, replace it with the optimal subproblem solution to get a better overall solution — contradiction.

**Contrast with longest simple path:** Shortest paths have optimal substructure (subproblems are independent). Longest simple paths do NOT — subproblems share vertices, making them non-independent. This problem is NP-complete.

**2. Overlapping Subproblems:** The recursive algorithm solves the same subproblems repeatedly. DP exploits this: solve each subproblem once, store in a table. Divide-and-conquer, by contrast, generates brand-new subproblems at each step (no benefit from memoization).

### Top-Down vs. Bottom-Up

| Approach | Mechanism | Advantage |
|----------|-----------|-----------|
| Top-down + memoization | Recursive; cache results | Solves only needed subproblems; natural structure |
| Bottom-up | Fill table in order of subproblem size | No recursion overhead; better cache behavior; sometimes enables space optimization |

Same asymptotic running time. Bottom-up usually has better constants.

### Subproblem Graph

Directed graph $G = (V, E)$ where each vertex = one subproblem, edge $(x, y)$ = solving $x$ requires $y$. The running time = sum of time to solve each subproblem = proportional to $|V| + |E|$ (for constant work per edge).

- Rod cutting: $|V| = n$, max $n$ edges/vertex → $O(n^2)$
- Matrix-chain: $|V| = \Theta(n^2)$, max $n-1$ edges/vertex → $O(n^3) = \Theta(n^3)$
- LCS: $|V| = \Theta(mn)$, constant edges/vertex → $\Theta(mn)$

### Time and Space Complexity Analysis

| Problem | Time | Space | Subproblems |
|---------|------|-------|-------------|
| Rod cutting | $\Theta(n^2)$ | $\Theta(n)$ | $n$ subproblems, $n$ choices each |
| Matrix-chain multiplication | $\Theta(n^3)$ | $\Theta(n^2)$ | $\Theta(n^2)$ subproblems, $n-1$ choices each |
| Longest common subsequence | $\Theta(mn)$ | $\Theta(mn)$ | $\Theta(mn)$ subproblems, 1–2 choices |
| Optimal BSTs | $\Theta(n^3)$ | $\Theta(n^2)$ | $\Theta(n^2)$ subproblems, $n$ choices |

### LCS Optimal Substructure (Theorem 14.1)

For sequences $X = \langle x_1,\ldots,x_m \rangle$, $Y = \langle y_1,\ldots,y_n \rangle$, and LCS $Z = \langle z_1,\ldots,z_k \rangle$:
1. If $x_m = y_n$: then $z_k = x_m = y_n$ and $Z_{k-1}$ is an LCS of $X_{m-1}$ and $Y_{n-1}$.
2. If $x_m \neq y_n$ and $z_k \neq x_m$: then $Z$ is an LCS of $X_{m-1}$ and $Y$.
3. If $x_m \neq y_n$ and $z_k \neq y_n$: then $Z$ is an LCS of $X$ and $Y_{n-1}$.

This gives a recurrence with $\Theta(mn)$ distinct subproblems.

### Space Optimization Possibilities

LCS-LENGTH can be reduced to $\Theta(\min(m,n))$ space for computing only the length (need only two rows at a time). Full reconstruction still requires the $b$ table or recomputing values.

---

## Key Takeaways & Next Steps

1. **DP transforms exponential algorithms to polynomial** by recognizing and exploiting overlapping subproblems — the same insight that separates $\Theta(n^2)$ rod cutting from the naive $\Theta(2^n)$.
2. **Optimal substructure is the foundation**: without it, DP cannot be applied (longest simple path example).
3. **Bottom-up DP** (filling a table in subproblem-size order) is usually preferable to top-down memoization for constant-factor reasons.
4. **The subproblem graph** provides a systematic way to count subproblems and determine running time: $T = O(|V| + |E|)$.
5. DP is used in: bioinformatics (sequence alignment, edit distance), compilers (parsing), route optimization, and as a subroutine in many graph algorithms (Bellman-Ford, Floyd-Warshall).

---

### Navigation

**Previous:** [[PartIV_Advanced_Design_and_Analysis_Techniques]]
**Next:** [[Ch15_Greedy_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
