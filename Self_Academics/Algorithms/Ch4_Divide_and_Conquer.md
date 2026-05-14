# Chapter 4: Divide-and-Conquer

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #divide-and-conquer #recurrences #matrix-multiplication

## Overview

The divide-and-conquer paradigm breaks problems into smaller subproblems, solves them recursively, and combines results. This chapter develops the mathematical tools — recurrences and methods for solving them — needed to analyze such algorithms. It uses matrix multiplication as the running example.

---

## The Divide-and-Conquer Paradigm

Three steps for the recursive (non-base) case:
1. **Divide** — break problem into smaller instances of the same problem
2. **Conquer** — solve recursively
3. **Combine** — merge subproblem solutions

**Base case:** problem small enough to solve directly without recursing.

**Recurrences** describe running time $T(n)$ in terms of $T$ on smaller inputs. An **algorithmic recurrence** satisfies:
- $T(n) = \Theta(1)$ for $n < n_0$ (some threshold constant $n_0 > 0$)
- Every recursion path reaches a defined base case in finite steps

**Convention:** When no base case is stated, assume the recurrence is algorithmic.

---

## 4.1 Matrix Multiplication

**Naive approach** (`MATRIX-MULTIPLY`):

```
MATRIX-MULTIPLY(A, B, C, n)     // computes C = C + A·B
1  for i = 1 to n
2      for j = 1 to n
3          for k = 1 to n
4              c[i][j] = c[i][j] + a[i][k] * b[k][j]
```

**Complexity:** $\Theta(n^3)$

### Divide-and-Conquer Matrix Multiply

Partition $n \times n$ matrices into four $n/2 \times n/2$ submatrices:
$$C = A \cdot B \implies \begin{pmatrix} C_{11} & C_{12} \\ C_{21} & C_{22} \end{pmatrix} = \begin{pmatrix} A_{11} & A_{12} \\ A_{21} & A_{22} \end{pmatrix} \begin{pmatrix} B_{11} & B_{12} \\ B_{21} & B_{22} \end{pmatrix}$$

Eight recursive multiplications of $n/2 \times n/2$ matrices.

**Recurrence:** $T(n) = 8T(n/2) + \Theta(1)$

**Solution (Master Theorem, Case 1):** $T(n) = \Theta(n^3)$ — no improvement!

---

## 4.2 Strassen's Algorithm

Reduces 8 recursive multiplications to **7** by computing auxiliary matrices $S_1, \ldots, S_{10}$ and $P_1, \ldots, P_7$:

**Auxiliary sums (10 additions/subtractions of $n/2 \times n/2$ matrices):**
$$S_1 = B_{12} - B_{22}, \quad S_2 = A_{11} + A_{12}, \quad S_3 = A_{21} + A_{22}, \quad S_4 = B_{21} - B_{11}$$
$$S_5 = A_{11} + A_{22}, \quad S_6 = B_{11} + B_{22}, \quad S_7 = A_{12} - A_{22}, \quad S_8 = B_{21} + B_{22}$$
$$S_9 = A_{11} - A_{21}, \quad S_{10} = B_{11} + B_{12}$$

**Seven recursive products:**
$$P_1 = A_{11} \cdot S_1, \quad P_2 = S_2 \cdot B_{22}, \quad P_3 = S_3 \cdot B_{11}, \quad P_4 = A_{22} \cdot S_4$$
$$P_5 = S_5 \cdot S_6, \quad P_6 = S_7 \cdot S_8, \quad P_7 = S_9 \cdot S_{10}$$

**Combine:**
$$C_{11} = P_5 + P_4 - P_2 + P_6, \quad C_{12} = P_1 + P_2$$
$$C_{21} = P_3 + P_4, \quad C_{22} = P_5 + P_1 - P_3 - P_7$$

**Recurrence:** $T(n) = 7T(n/2) + \Theta(n^2)$

**Solution (Master Theorem, Case 1):** $T(n) = \Theta(n^{\log_2 7}) = O(n^{2.81})$

**Key insight:** Trading one multiplication for several additions is profitable when multiplications dominate (i.e., for large matrices).

| Algorithm | Time |
|---|---|
| Naive MATRIX-MULTIPLY | $\Theta(n^3)$ |
| D&C MATRIX-MULTIPLY-RECURSIVE | $\Theta(n^3)$ |
| Strassen | $\Theta(n^{\log_2 7}) \approx \Theta(n^{2.807})$ |

---

## 4.3 Substitution Method

**Steps:**
1. **Guess** the form of the solution (with symbolic constants)
2. **Prove** by mathematical induction, solving for the constants

**Example:** For $T(n) = 2T(\lfloor n/2 \rfloor) + \Theta(n)$, guess $T(n) = O(n \log_2 n)$:
- Inductive hypothesis: $T(n) \leq c\,n\log_2 n$
- Substituting: $T(n) \leq 2(c\lfloor n/2 \rfloor \log_2(\lfloor n/2 \rfloor)) + \Theta(n) \leq cn\log_2 n - cn + \Theta(n) \leq cn\log_2 n$ ✓

### Common Pitfalls

- **Never use asymptotic notation in the inductive hypothesis** — constants must be explicit
- If the math doesn't close, try **subtracting a lower-order term** from the guess (e.g., guess $T(n) \leq cn - d$ instead of $T(n) \leq cn$)

---

## 4.4 Recursion-Tree Method

Model the recurrence as a tree where each node represents the cost at one level of recursion.

**Technique:**
1. Draw the recursion tree
2. Sum costs across each level
3. Sum all per-level costs

**Example:** $T(n) = T(n/3) + T(2n/3) + cn$
- Tree height: $\Theta(\log_2 n)$ (along the longer $2/3$ branch)
- Cost per level: $\leq cn$
- Total: $O(n \log_2 n)$ (confirmed by substitution: $T(n) = \Theta(n \log_2 n)$)

**Key insight:** In this asymmetric split, the total leaves cost $O(n)$ (dominated by internal node cost $O(n \log_2 n)$).

**Use:** Best for generating good guesses to verify with substitution method. Can serve as a direct proof if done carefully.

---

## 4.5 The Master Method (Master Theorem)

Applies to recurrences of the form:
$$T(n) = aT(n/b) + f(n), \quad a > 0,\; b > 1$$

**Watershed function:** $n^{\log_b a}$

### Three Cases

| Case | Condition | Solution |
|---|---|---|
| **Case 1** | $f(n) = O(n^{\log_b a - \epsilon})$ for some $\epsilon > 0$ (watershed dominates polynomially) | $T(n) = \Theta(n^{\log_b a})$ |
| **Case 2** | $f(n) = \Theta(n^{\log_b a} \log_2^k n)$ for some $k \geq 0$ (tied within log factors) | $T(n) = \Theta(n^{\log_b a} \log_2^{k+1} n)$ |
| **Case 3** | $f(n) = \Omega(n^{\log_b a + \epsilon})$ for some $\epsilon > 0$, AND $af(n/b) \leq cf(n)$ for some $c < 1$ (driving function dominates polynomially) | $T(n) = \Theta(f(n))$ |

**Intuition:**
- **Case 1:** Leaves dominate — tree fans out fast
- **Case 2:** Each level costs similarly — multiply by $\log_2 n$ levels
- **Case 3:** Root dominates — costs decrease geometrically top to bottom

### Examples

| Recurrence | $a$, $b$, $f(n)$ | Case | Solution |
|---|---|---|---|
| $T(n) = 9T(n/3) + n$ | $a=9$, $b=3$, $f(n)=n$, watershed $n^2$ | Case 1 ($n = O(n^{2-1})$) | $\Theta(n^2)$ |
| $T(n) = T(2n/3) + 1$ | $a=1$, $b=3/2$, $f(n)=1$, watershed $n^0=1$ | Case 2 ($k=0$) | $\Theta(\log_2 n)$ |
| $T(n) = 3T(n/4) + n\log_2 n$ | $a=3$, $b=4$, $f(n)=n\log_2 n$, watershed $n^{0.79}$ | Case 3 | $\Theta(n\log_2 n)$ |
| $T(n) = 2T(n/2) + \Theta(n)$ | $a=2$, $b=2$, $f(n)=\Theta(n)$, watershed $n$ | Case 2 ($k=0$) | $\Theta(n\log_2 n)$ |
| $T(n) = 7T(n/2) + \Theta(n^2)$ | Strassen, watershed $n^{\log_2 7} \approx n^{2.807}$ | Case 1 | $\Theta(n^{\log_2 7})$ |
| $T(n) = 8T(n/2) + \Theta(1)$ | Naive D&C, watershed $n^3$ | Case 1 | $\Theta(n^3)$ |

> **Note:** The master theorem does NOT apply to all recurrences (e.g., $T(n) = T(n/3) + T(2n/3) + \Theta(n)$ — non-uniform subproblem sizes).

---

## 4.6–4.7 Proof of Master Theorem and Akra-Bazzi Method

- **Section 4.6:** Formal proof of the master theorem (works by analyzing the recursion tree rigorously)
- **Section 4.7 (Akra-Bazzi Method):** Handles recurrences of the form $T(n) = \sum_{i=1}^{k} a_i T(n/b_i) + f(n)$ with different subproblem sizes. Requires calculus (integrals). More general than the master theorem.

---

## Key Recurrence Solutions Summary

| Recurrence | Solution |
|---|---|
| $T(n) = T(n-1) + \Theta(1)$ | $\Theta(n)$ |
| $T(n) = T(n/2) + \Theta(1)$ | $\Theta(\log_2 n)$ |
| $T(n) = 2T(n/2) + \Theta(n)$ | $\Theta(n \log_2 n)$ |
| $T(n) = T(n/3) + T(2n/3) + \Theta(n)$ | $\Theta(n \log_2 n)$ |
| $T(n) = 4T(n/2) + \Theta(n)$ | $\Theta(n^2)$ |
| $T(n) = 8T(n/2) + \Theta(1)$ | $\Theta(n^3)$ |
| $T(n) = 7T(n/2) + \Theta(n^2)$ | $\Theta(n^{\log_2 7})$ |
| $T(n) = 2T(n-1) + 1$ | $\Theta(2^n)$ |

---

### Navigation
**Previous:** [[Ch3_Characterizing_Running_Times]]
**Next:** [[Ch5_Probabilistic_Analysis_and_Randomized_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
