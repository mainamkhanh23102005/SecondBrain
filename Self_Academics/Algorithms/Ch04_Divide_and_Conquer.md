# Chapter 4: Divide-and-Conquer

## Executive Summary

Chapter 4 deepens the divide-and-conquer paradigm with a focus on **matrix multiplication** as a running example, then develops four systematic methods for solving the **recurrences** that arise from recursive algorithms. Key results include Strassen's surprising $\Theta(n^{\log_2 7}) \approx O(n^{2.81})$ matrix multiplication algorithm, which beats the naive $\Theta(n^3)$ by exploiting algebraic structure. The **Master Theorem** provides a "cookbook" for solving the recurrence $T(n) = aT(n/b) + f(n)$ by comparing $f(n)$ against the **watershed function** $n^{\log_b a}$ in three cases. The **Akra-Bazzi method** extends this to unbalanced recurrences.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Naive iterative matrix multiplication** ($C = C + A \cdot B$, $n \times n$ matrices):

```
MATRIX-MULTIPLY(A, B, C, n)
1  for i = 1 to n              // each of n rows
2      for j = 1 to n          // each of n columns
3          for k = 1 to n
4              c[i][j] = c[i][j] + a[i][k] * b[k][j]
```

**Divide-and-conquer matrix multiplication:**

```
MATRIX-MULTIPLY-RECURSIVE(A, B, C, n)
 1  if n == 1
 3      c11 = c11 + a11 · b11;  return
 5  // Divide: partition A, B, C into four n/2 × n/2 submatrices (Θ(1) by index calculation)
 6  partition A, B, C into A11, A12, A21, A22; B11, B12, B21, B22; C11, C12, C21, C22
 7  // Conquer: 8 recursive calls
 8  MATRIX-MULTIPLY-RECURSIVE(A11, B11, C11, n/2)
 9  MATRIX-MULTIPLY-RECURSIVE(A11, B12, C12, n/2)
10  MATRIX-MULTIPLY-RECURSIVE(A21, B11, C21, n/2)
11  MATRIX-MULTIPLY-RECURSIVE(A21, B12, C22, n/2)
12  MATRIX-MULTIPLY-RECURSIVE(A12, B21, C11, n/2)
13  MATRIX-MULTIPLY-RECURSIVE(A12, B22, C12, n/2)
14  MATRIX-MULTIPLY-RECURSIVE(A22, B21, C21, n/2)
15  MATRIX-MULTIPLY-RECURSIVE(A22, B22, C22, n/2)
```

**Strassen's algorithm (high-level):**

```
STRASSEN(A, B, C, n)
1  if n == 1: c11 = c11 + a11·b11; return
2  // Divide
   Partition A, B, C into n/2 × n/2 submatrices
3  // Step 2: Compute 10 auxiliary matrices (Θ(n²) time)
   S1 = B12 – B22;   S2  = A11 + A12;   S3 = A21 + A22;   S4 = B21 – B11
   S5 = A11 + A22;   S6  = B11 + B22;   S7 = A12 – A22;   S8 = B21 + B22
   S9 = A11 – A21;   S10 = B11 + B12
4  // Step 3: 7 recursive multiplications (7T(n/2) time)
   P1 = STRASSEN(A11, S1,  n/2)    // A11·B12 – A11·B22
   P2 = STRASSEN(S2,  B22, n/2)    // A11·B22 + A12·B22
   P3 = STRASSEN(S3,  B11, n/2)    // A21·B11 + A22·B11
   P4 = STRASSEN(A22, S4,  n/2)    // A22·B21 – A22·B11
   P5 = STRASSEN(S5,  S6,  n/2)    // A11·B11 + A11·B22 + A22·B11 + A22·B22
   P6 = STRASSEN(S7,  S8,  n/2)    // A12·B21 + A12·B22 – A22·B21 – A22·B22
   P7 = STRASSEN(S9,  S10, n/2)    // A11·B11 + A11·B12 – A21·B11 – A21·B12
5  // Step 4: Combine into C (Θ(n²) time)
   C11 += P5 + P4 – P2 + P6
   C12 += P1 + P2
   C21 += P3 + P4
   C22 += P5 + P1 – P3 – P7
```

### Master Theorem (Theorem 4.1)

For recurrences of the form $T(n) = aT(n/b) + f(n)$ where $a > 0$, $b > 1$, and $f(n)$ is defined and nonneg for all sufficiently large $n$, define the **watershed function** $n^{\log_b a}$:

| Case | Condition | Solution |
|------|-----------|----------|
| **Case 1** | $f(n) = O(n^{\log_b a - \epsilon})$ for some $\epsilon > 0$ | $T(n) = \Theta(n^{\log_b a})$ |
| **Case 2** | $f(n) = \Theta(n^{\log_b a} \cdot \log_2^k n)$ for some $k \geq 0$ | $T(n) = \Theta(n^{\log_b a} \cdot \log_2^{k+1} n)$ |
| **Case 3** | $f(n) = \Omega(n^{\log_b a + \epsilon})$ for some $\epsilon > 0$, AND $af(n/b) \leq cf(n)$ for some $c < 1$ | $T(n) = \Theta(f(n))$ |

**Intuition:**
- Case 1: Leaves dominate (watershed grows faster → cost accumulates at leaves).
- Case 2: All levels contribute equally (watershed ≈ driving function → factor of $\log_2 n$ levels).
- Case 3: Root dominates (driving function dominates → top-level cost is largest).

---

## Deep-Dive Explanations

### Recurrences

A **recurrence** describes a function in terms of its value on smaller inputs. For divide-and-conquer with $a$ subproblems of size $n/b$:
$$T(n) = aT(n/b) + D(n) + C(n)$$

An **algorithmic recurrence** satisfies: (1) $T(n) = \Theta(1)$ for $n < n_0$; (2) every recursion terminates. Convention: **omit the base case** when the recurrence is algorithmic — the solution's asymptotics don't change with a sufficiently large threshold constant $n_0$.

Floors/ceilings in recurrences generally do not affect asymptotic solutions — the Master Theorem implicitly handles them.

### Matrix Multiplication: Complexity Analysis

**MATRIX-MULTIPLY** (naive): $\Theta(n^3)$ — three nested loops, each $n$ iterations.

**MATRIX-MULTIPLY-RECURSIVE** recurrence:
$$T(n) = 8T(n/2) + \Theta(1)$$

Watershed function: $n^{\log_2 8} = n^3$. Driving function $\Theta(1) = O(n^{3-\epsilon})$ → **Case 1** → $T(n) = \Theta(n^3)$.

Same asymptotic complexity as naive! The bushier recursion tree (8 children vs. merge sort's 2) cancels the smaller per-node work.

**Strassen's algorithm** recurrence:
$$T(n) = 7T(n/2) + \Theta(n^2)$$

Watershed function: $n^{\log_2 7} \approx n^{2.807}$. Driving function $\Theta(n^2) = O(n^{\log_2 7 - \epsilon})$ with $\epsilon \approx 0.807$ → **Case 1** → $T(n) = \Theta(n^{\log_2 7}) = O(n^{2.81})$.

**Strassen's insight:** Trade 1 matrix multiplication for ~5 extra matrix additions (cheaper operations) to reduce 8-way recursion to 7-way. The extra $\Theta(n^2)$ overhead is dominated by the recursive cost.

### Four Methods for Solving Recurrences

#### 1. Substitution Method
1. **Guess** the form (e.g., $T(n) = O(n \log_2 n)$).
2. **Prove by mathematical induction** with explicit constants.

Example: $T(n) \leq 2T(\lfloor n/2 \rfloor) + \Theta(n)$.  
Guess: $T(n) \leq cn \log_2 n$. Substitute: $T(n) \leq 2c\lfloor n/2\rfloor \log_2(\lfloor n/2 \rfloor) + \Theta(n) \leq cn \log_2 n - cn + \Theta(n) \leq cn \log_2 n$ for large enough $c$. ✓

**Trick:** If math fails, subtract a lower-order term from the guess (e.g., try $T(n) \leq cn - d$ instead of $T(n) \leq cn$).

**Pitfall:** Never use asymptotic notation inside the inductive hypothesis — constants must remain explicit.

#### 2. Recursion Tree Method
- Draw the recursion tree: nodes represent costs at each recursive call level.
- Sum costs **per level** (often geometric series), then sum across levels.
- Example: $T(n) = 3T(n/4) + cn^2$.  
  Tree height: $\log_4 n$. Per-level costs form geometric series with ratio $3/16 < 1$. Total cost $= \sum_{i=0}^{\log_4 n} (3/16)^i cn^2 \leq \frac{16}{13}cn^2 = O(n^2)$. Verified → $\Theta(n^2)$.

- Use for **intuition** about the guess; verify with substitution.

#### 3. Master Method (Theorem 4.1)
See the three-case table above. Common examples:

| Recurrence | $a$ | $b$ | $n^{\log_b a}$ | Case | Solution |
|-----------|-----|-----|----------------|------|---------|
| $T(n) = 2T(n/2) + \Theta(n)$ | 2 | 2 | $n$ | 2 ($k=0$) | $\Theta(n \log_2 n)$ |
| $T(n) = 9T(n/3) + n$ | 9 | 3 | $n^2$ | 1 | $\Theta(n^2)$ |
| $T(n) = 3T(n/4) + n \log_2 n$ | 3 | 4 | $n^{\log_4 3} \approx n^{0.79}$ | 3 | $\Theta(n \log_2 n)$ |
| $T(n) = 8T(n/2) + \Theta(1)$ | 8 | 2 | $n^3$ | 1 | $\Theta(n^3)$ |
| $T(n) = 7T(n/2) + \Theta(n^2)$ | 7 | 2 | $n^{\log_2 7}$ | 1 | $\Theta(n^{\log_2 7})$ |
| $T(n) = T(n/2) + \Theta(1)$ | 1 | 2 | $n^0 = 1$ | 2 | $\Theta(\log_2 n)$ |

**Gaps in the Master Theorem:** No case applies when the polynomial separation doesn't exist (e.g., $T(n) = 2T(n/2) + n/\log_2 n$ — answer is $\Theta(n \log_2 \log_2 n)$, requires other methods).

#### 4. Akra-Bazzi Method (Section 4.7)
For recurrences $T(n) = \sum_{i=1}^{k} a_i T(b_i n) + f(n)$ with potentially different $b_i$ values. Find $p$ such that $\sum_{i=1}^{k} a_i b_i^p = 1$, then:
$$T(n) = \Theta\!\left(n^p\!\left(1 + \int_1^n \frac{f(u)}{u^{p+1}}\, du\right)\right)$$

Handles unbalanced recurrences like $T(n) = T(n/3) + T(2n/3) + \Theta(n) = \Theta(n \log_2 n)$.

### Why Strassen Beats $\Theta(n^3)$ (Conceptual)

The recursion tree for $T(n) = 8T(n/2)$ has $8^{\log_2 n} = n^3$ leaves. Strassen's tree has $7^{\log_2 n} = n^{\log_2 7}$ leaves. Reducing branching from 8 to 7 changes the leaf count polynomially: $n^3 \to n^{2.807}$. This is achieved by expressing 8 submatrix multiplications using only 7 multiplications plus 18 additions (additions are cheaper for large matrices).

---

## Key Takeaways & Next Steps

1. **Divide-and-conquer** works best when combining solutions is cheap relative to the savings from recursive decomposition.
2. **Strassen's algorithm** ($\Theta(n^{\log_2 7})$) shows that algebraic tricks can break the "natural" complexity barrier. Current best is $O(n^{2.371552})$ (Williams et al., 2024).
3. **Master Theorem** handles the vast majority of practical recurrences — memorize the three cases. For gaps, use substitution or Akra-Bazzi.
4. **Recursion trees** build intuition; the substitution method provides rigorous proof.
5. Floors and ceilings generally do not affect asymptotic solutions for algorithmic recurrences.
6. The techniques here apply directly to quicksort (Chapter 7), binary search, merge sort analysis extensions, and dynamic programming (Chapter 14).

---

### Navigation

**Previous:** [[Ch03_Characterizing_Running_Times]]
**Next:** [[Ch05_Probabilistic_Analysis_and_Randomized_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
