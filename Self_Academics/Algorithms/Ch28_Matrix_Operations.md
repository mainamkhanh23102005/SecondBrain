# Chapter 28: Matrix Operations

**Source:** Introduction to Algorithms (CLRS), Chapter 28  
**Tags:** #algorithms #linear-algebra #LUP #matrix #gaussian-elimination

---

## Executive Summary

This chapter focuses on two foundational matrix problems: **solving systems of linear equations** and **inverting matrices**. The central tool is **LUP decomposition** — factoring a nonsingular matrix $A$ into a permutation matrix $P$, unit lower-triangular $L$, and upper-triangular $U$ such that $PA = LU$. Once factored, a system $Ax = b$ is solved in $\Theta(n^2)$ via forward and back substitution; computing the decomposition itself takes $\Theta(n^3)$. The chapter also proves that **matrix multiplication and matrix inversion are equivalently hard** (each is reducible to the other in the same asymptotic time), and treats symmetric positive-definite matrices and least-squares.

---

## Zero-Loss Extraction

### 1. Setting Up $Ax = b$

Given an $n \times n$ non-singular matrix $A$ and vector $b$, solve $Ax = b$.

- If $A$ is non-singular, the unique solution is $x = A^{-1}b$.
- Computing $A^{-1}$ directly is numerically unstable; LUP decomposition is preferred.

---

### 2. LUP Decomposition

**Goal:** find matrices $L$, $U$, $P$ satisfying
$$PA = LU$$

where:
- $P$ = $n \times n$ permutation matrix (encoded as array $\pi[1:n]$, where $\pi[i] = j$ means $P_{i,j} = 1$).
- $L$ = unit lower-triangular ($l_{ii} = 1$, $l_{ij} = 0$ for $j > i$).
- $U$ = upper-triangular ($u_{ij} = 0$ for $i > j$).

**Every nonsingular matrix has an LUP decomposition.**

**Solving $Ax = b$ via LUP:**
1. Multiply both sides by $P$: $PAx = Pb$, i.e., $LUx = Pb$.
2. Let $y = Ux$. Solve $Ly = Pb$ by **forward substitution** (top to bottom): $y_i = b_{\pi[i]} - \sum_{j=1}^{i-1} l_{ij} y_j$.
3. Solve $Ux = y$ by **back substitution** (bottom to top): $x_i = (y_i - \sum_{j=i+1}^n u_{ij} x_j)/u_{ii}$.
4. Both substitution steps run in $\Theta(n^2)$.

```
LUP-SOLVE(L, U, π, b, n)
1  let x, y be new vectors of length n
2  for i = 1 to n
3      y_i = b_{π[i]} − Σ_{j=1}^{i−1} l_{ij} · y_j   // forward substitution
4  for i = n downto 1
5      x_i = (y_i − Σ_{j=i+1}^{n} u_{ij} · x_j) / u_{ii}  // back substitution
6  return x
```

---

### 3. LU Decomposition (No Pivoting)

For a nonsingular $A$ where pivoting is not needed ($a_{11} \neq 0$ and all sub-pivots $\neq 0$, e.g., symmetric positive-definite matrices):

**Recursive factoring:** partition
$$A = \begin{pmatrix} a_{11} & w^T \\ v & A' \end{pmatrix} = \begin{pmatrix} 1 & 0 \\ v/a_{11} & I \end{pmatrix} \begin{pmatrix} a_{11} & w^T \\ 0 & A' - vw^T/a_{11} \end{pmatrix}$$

**Schur complement:** $S = A' - vw^T/a_{11}$ (an $(n-1)\times(n-1)$ matrix). If $A$ is nonsingular, $S$ is nonsingular.

```
LU-DECOMPOSITION(A, n)
 1  let L, U be new n × n matrices
 2  initialize U with 0s below diagonal; L with 1s on diagonal, 0s above
 4  for k = 1 to n
 5      u_{kk} = a_{kk}                     // pivot
 6      for i = k+1 to n
 7          l_{ik} = a_{ik} / a_{kk}        // column of L
 8          u_{ki} = a_{ki}                  // row of U
 9      for i = k+1 to n
10          for j = k+1 to n
11              a_{ij} = a_{ij} − l_{ik} · u_{kj}  // Schur complement
12  return L and U
```

**Running time:** $\Theta(n^3)$ (triply nested loop).

**Pivots:** the diagonal elements $u_{kk}$ are the pivots. If any pivot is $0$ (or very small), the method fails or becomes numerically unstable.

---

### 4. LUP Decomposition (With Pivoting)

Pivot on the element with **largest absolute value** in the current first column to avoid division by zero and improve numerical stability.

```
LUP-DECOMPOSITION(A, n)
 1  let π[1:n] be new array; for i = 1 to n: π[i] = i   // identity permutation
 4  for k = 1 to n
 5      p = 0
 6      for i = k to n                            // find pivot row
 7          if |a_{ik}| > p: p = |a_{ik}|; k' = i
10      if p == 0: error "singular matrix"
12      exchange π[k] ↔ π[k']
13      for i = 1 to n: exchange a_{ki} ↔ a_{k'i}  // swap rows k and k'
15      for i = k+1 to n
16          a_{ik} = a_{ik} / a_{kk}              // L below diagonal (in place)
17      for j = k+1 to n
18          a_{ij} = a_{ij} − a_{ik} · a_{kj}    // Schur complement (in place)
```

- Runs in $\Theta(n^3)$ (same as LU).
- Stores $L$ and $U$ in place in $A$: $a_{ij} = l_{ij}$ if $i > j$, $a_{ij} = u_{ij}$ if $i \leq j$.
- **Pivoting costs at most a constant factor** in time.

---

### 5. Matrix Inversion from LUP (§28.2)

Given LUP decomposition of $A$, compute $A^{-1}$ by solving $AX_i = e_i$ for each column $X_i$ of $A^{-1}$:
- Each column solve: $\Theta(n^2)$ (one LUP-SOLVE call).
- $n$ columns total: $\Theta(n^3)$.
- Plus LUP decomposition: $\Theta(n^3)$.
- **Total: $A^{-1}$ computable in $\Theta(n^3)$.**

---

### 6. Equivalence of Matrix Multiplication and Inversion

Let $M(n)$ = time to multiply two $n \times n$ matrices, $I(n)$ = time to invert an $n \times n$ matrix.

**Theorem 28.1 (Multiplication $\leq$ Inversion):** If $I(n) = \Omega(n^2)$ and $I(3n) = O(I(n))$, then $M(n) = O(I(n))$.

**Proof sketch:** To compute $C = AB$, construct:
$$D = \begin{pmatrix} I & A & 0 \\ 0 & I & B \\ 0 & 0 & I \end{pmatrix}, \quad D^{-1} = \begin{pmatrix} I & -A & AB \\ 0 & I & -B \\ 0 & 0 & I \end{pmatrix}$$

$AB$ appears as the upper-right $n \times n$ block of $D^{-1}$. Constructing $D$ takes $\Theta(n^2)$; inverting $D$ takes $O(I(3n)) = O(I(n))$.

**Theorem 28.2 (Inversion $\leq$ Multiplication):** If $M(n) = \Omega(n^2)$, $M(n)$ is "smooth" (regularity condition), then $I(n) = O(M(n))$.

**Proof sketch:** invert by LUP decomposition with Strassen-like multiplication for the Schur complement computation, yielding an $O(M(n))$ inversion algorithm.

**Corollary:** Using Strassen's $\Theta(n^{\log_2 7})$ matrix multiplication also gives $\Theta(n^{\log_2 7})$ matrix inversion.

---

### 7. Symmetric Positive-Definite Matrices (§28.3)

A matrix $A$ is **symmetric positive-definite (SPD)** if $A = A^T$ and $x^T A x > 0$ for all nonzero $x$.

**Key property:** LU decomposition of an SPD matrix requires **no pivoting** (all pivots are positive).

**Cholesky decomposition:** for SPD $A$, factor $A = LL^T$ where $L$ is lower-triangular. This is twice as fast as LU in practice.

**Application — Least-Squares:** Given overdetermined system $Ax \approx b$ ($A$ is $m \times n$, $m > n$, full column rank), the least-squares solution minimizes $\|Ax - b\|_2^2$:
$$x^* = (A^T A)^{-1} A^T b$$

$A^T A$ is SPD (when $A$ has full column rank), so Cholesky decomposition applies.

---

## Deep-Dive Explanations

### Why Pivoting is Necessary

Even if $A$ is nonsingular, the upper-left element $a_{kk}$ (the pivot) can be zero mid-way through Gaussian elimination, causing division by zero. Small but nonzero pivots amplify floating-point errors. **LUP decomposition** avoids this by permuting rows so that the largest absolute value in the current column becomes the pivot — a strategy called **partial pivoting**.

### Forward and Back Substitution Intuition

$Ly = Pb$ can be solved top to bottom because $L$ is lower-triangular: $y_1 = b_{\pi[1]}$ directly, then $y_2 = b_{\pi[2]} - l_{21}y_1$, etc. Each $y_i$ depends only on already-computed $y_1, \ldots, y_{i-1}$. Back substitution works bottom to top for the same reason applied to $U$.

### Schur Complement and Recursive Structure

The matrix identity
$$A = \begin{pmatrix} 1 & 0 \\ v/a_{11} & I \end{pmatrix} \begin{pmatrix} a_{11} & w^T \\ 0 & S \end{pmatrix}$$
shows that $A$'s LU decomposition is built from that of its Schur complement $S = A' - vw^T/a_{11}$. Nonsingularity of $A$ implies nonsingularity of $S$, justifying the recursion.

---

## Key Takeaways & Next Steps

1. **LUP decomposition** ($\Theta(n^3)$) + **forward/back substitution** ($\Theta(n^2)$) = efficient, numerically stable solution to $Ax = b$.
2. **Pivoting is essential** for numerical stability: always choose the largest-magnitude pivot in the current column.
3. **Matrix inversion is $\Theta(n^3)$** via LUP; computing $A^{-1}$ explicitly is usually unnecessary (solve $Ax = b$ instead).
4. **Matrix multiplication $\equiv$ matrix inversion** in asymptotic complexity — Strassen-style speedups apply to both.
5. **SPD matrices** enable Cholesky decomposition (faster, no pivoting needed) and arise naturally in least-squares problems.
6. **Next:** Chapter 29 (Linear Programming) — optimization with linear objectives and constraints.

---

### Navigation

- **Previous:** [[Ch27_Online_Algorithms|Ch27 — Online Algorithms]]
- **Next:** [[Ch29_Linear_Programming|Ch29 — Linear Programming]]
- **Hub:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms Index]]
