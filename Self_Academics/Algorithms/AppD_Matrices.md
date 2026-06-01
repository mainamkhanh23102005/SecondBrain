# Appendix D — Matrices

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #mathematics #linear-algebra #matrices

---

## Executive Summary

Appendix D provides the linear algebra foundation for Chapter 28 (Matrix Operations), Chapter 29 (Linear Programming), and Chapter 33 (Machine Learning Algorithms). Two sections cover the essential toolkit:

| Section | Topic | Key Results |
|---------|-------|------------|
| D.1 | Matrices and Operations | Matrix types, addition, multiplication $\Theta(pqr)$, transpose, inner/outer product, Euclidean norm |
| D.2 | Basic Properties | Inverse, rank, null vectors, determinant, positive-definite matrices; Theorems D.1–D.6 |

---

## Zero-Loss Extraction

### §D.1 — Matrices and Matrix Operations

#### Notation

A **matrix** $A = (a_{ij})$ is an $m \times n$ rectangular array of numbers; $a_{ij}$ denotes the element in row $i$, column $j$. The set of all $m \times n$ real matrices is $\mathbb{R}^{m \times n}$; over a set $S$: $S^{m \times n}$.

The **transpose** $A^T$ is obtained by exchanging rows and columns: $(A^T)_{ij} = a_{ji}$.

A **vector** (default: column vector) is an $n \times 1$ matrix; its transpose $x^T$ is a $1 \times n$ row vector. The **unit vector** $e_i$ has a 1 in position $i$ and 0s elsewhere.

A **zero matrix** (all entries 0) is the identity for matrix addition: $A + 0 = A$.

#### Special Square Matrices

| Type | Defining Condition | Notable Property |
|------|--------------------|-----------------|
| Diagonal | $a_{ij} = 0$ for $i \ne j$ | Multiplication scales rows/columns |
| Identity $I_n$ | Diagonal with 1s on diagonal; $i$th col $= e_i$ | $I_m A = A I_n = A$ for any $m \times n$ matrix $A$ |
| Tridiagonal | $t_{ij} = 0$ if $|i - j| > 1$ | Arises in finite-difference methods |
| Upper-triangular $U$ | $u_{ij} = 0$ if $i > j$ | Solved by back substitution |
| Lower-triangular $L$ | $l_{ij} = 0$ if $i < j$ | Solved by forward substitution |
| Unit upper/lower triangular | Triangular with 1s on diagonal | Used in LUP decomposition (§28.1) |
| Permutation $P$ | Exactly one 1 per row and column | $PA$ permutes rows of $A$; $AP$ permutes columns |
| Symmetric | $A = A^T$ | $A^T A$ is always symmetric (Exercise D.1-2) |

#### Matrix Operations

**Addition:** $C = A + B$ where $c_{ij} = a_{ij} + b_{ij}$ (componentwise; requires same dimensions).

**Scalar multiplication:** $(\lambda A)_{ij} = \lambda a_{ij}$; negative: $-A = (-1)A$.

**Matrix multiplication:** For $A$ ($p \times q$) and $B$ ($q \times r$), $C = AB$ is $p \times r$:

$$c_{ij} = \sum_{k=1}^{q} a_{ik}\, b_{kj} \tag{D.2}$$

Running time: $\Theta(pqr)$ multiplications and additions. For $n \times n$ matrices: $\Theta(n^3)$ (MATRIX-MULTIPLY, §4.2). Strassen achieves $\Theta(n^{\log_2 7}) \approx \Theta(n^{2.807})$.

**Algebraic laws:**
- Associative: $A(BC) = (AB)C$
- Distributive: $A(B + C) = AB + AC$; $(B + C)D = BD + CD$
- **Not commutative** for $n > 1$: $AB \ne BA$ in general
- $I_m A = A I_n = A$ for any $m \times n$ matrix $A$
- $A \cdot 0 = 0$

**Transpose rules:** $(AB)^T = B^T A^T$ (Exercise D.1-2).

#### Inner Product, Outer Product, and Norm

For $n$-vectors $x$ and $y$:

- **Inner product:** $\langle x, y \rangle = x^T y = \sum_{i=1}^n x_i y_i \quad$ (scalar; commutative: $\langle x, y \rangle = \langle y, x \rangle$)
- **Outer product:** $xy^T$ is an $n \times n$ matrix with $(xy^T)_{ij} = x_i y_j$
- **Euclidean norm:** $\|x\| = \sqrt{x^T x} = \sqrt{\sum_{i=1}^n x_i^2}$; property: $\|\lambda x\| = |\lambda|\,\|x\|$

---

### §D.2 — Basic Matrix Properties

#### Matrix Inverse

The **inverse** of an $n \times n$ matrix $A$ is the matrix $A^{-1}$ (if it exists) satisfying $AA^{-1} = I_n = A^{-1}A$. Inverses are **unique** when they exist.

- **Singular (noninvertible):** inverse does not exist.
- **Nonsingular (invertible):** inverse exists; satisfies $(BA)^{-1} = A^{-1}B^{-1}$ and $(A^{-1})^T = (A^T)^{-1}$.

#### Rank

Vectors $x_1, \ldots, x_n$ are **linearly dependent** if there exist coefficients $c_1, \ldots, c_n$ (not all zero) with $\sum_{i} c_i x_i = 0$; otherwise **linearly independent** (e.g., columns of an identity matrix).

The **rank** of a matrix equals its column rank = row rank (fundamental theorem; the proof uses the Rank-Nullity theorem). For an $m \times n$ matrix: $0 \le \text{rank}(A) \le \min\{m,n\}$. A square $n \times n$ matrix has **full rank** if $\text{rank}(A) = n$; an $m \times n$ matrix has **full column rank** if $\text{rank}(A) = n$.

**Theorem D.1:** A square matrix has full rank $\iff$ it is nonsingular.

A **null vector** for $A$ is a nonzero vector $x$ such that $Ax = 0$.

**Theorem D.2:** $A$ has full column rank $\iff$ $A$ has no null vector.

**Corollary D.3:** A square matrix is singular $\iff$ it has a null vector.

#### Determinant

The **$(ij)$-th minor** $A[ij]$ of an $n \times n$ matrix $A$ (for $n > 1$) is the $(n-1) \times (n-1)$ matrix obtained by deleting row $i$ and column $j$ from $A$.

The **determinant** is defined recursively by cofactor expansion along the first row:

$$\det(A) = \sum_{j=1}^{n} (-1)^{1+j}\, a_{1j}\, \det(A[1j])$$

The term $(-1)^{i+j}\det(A[ij])$ is the **cofactor** of element $a_{ij}$.

**Theorem D.4 (Determinant properties):**
1. A zero row or column $\Rightarrow \det(A) = 0$.
2. Multiplying any one row (or column) by $\lambda$ multiplies $\det(A)$ by $\lambda$.
3. Adding entries of one row (column) to another row (column) leaves $\det(A)$ unchanged.
4. $\det(A^T) = \det(A)$.
5. Swapping any two rows (or columns) multiplies $\det(A)$ by $-1$.
6. $\det(AB) = \det(A)\det(B)$ for any square $A, B$.

**Theorem D.5:** $A$ is singular $\iff$ $\det(A) = 0$.

#### Positive-Definite and Positive-Semidefinite Matrices

An $n \times n$ matrix $A$ is **positive-definite** if $x^T A x > 0$ for all nonzero $n$-vectors $x$ (e.g., $I_n$ is positive-definite).

**Theorem D.6:** If $A$ has full column rank, then $A^T A$ is positive-definite.

*Proof:* $x^T(A^T A)x = (Ax)^T(Ax) = \|Ax\|^2 \ge 0$. If $x \ne 0$, Theorem D.2 guarantees $Ax \ne 0$, so $\|Ax\|^2 > 0$.

An $n \times n$ matrix $A$ is **positive-semidefinite** if $x^T A x \ge 0$ for all nonzero $x$. This arises in §33.3 (kernel methods and regression).

---

## Deep-Dive Explanations

### Why Rank = Column Rank = Row Rank

This is the pivotal structural theorem of linear algebra. The Rank-Nullity theorem states: for an $m \times n$ matrix $A$, column rank $+$ nullity $= n$ (where nullity $= \dim(\ker A)$). Since nullity depends only on $A$ and row rank similarly, the two ranks coincide. This equality justifies speaking of "the rank" without specifying row or column; it also means rank is preserved under transposition.

### Determinant as Signed Volume

Geometrically, $|\det(A)|$ is the volume of the parallelepiped spanned by the columns (or rows) of $A$. The sign encodes orientation. Properties 2–5 of Theorem D.4 correspond precisely to the three elementary row operations used in Gaussian elimination, which is why computing the determinant reduces to tracking these operations. Property 6 ($\det(AB) = \det(A)\det(B)$) makes the determinant a group homomorphism from invertible matrices to non-zero reals.

### Four Equivalent Characterizations of Invertibility

Theorems D.1–D.5 give four equivalent conditions for an $n \times n$ matrix $A$:

| Condition | Theorem |
|-----------|---------|
| Full rank | D.1 |
| Nonsingular (inverse exists) | D.1 |
| No null vector | D.2 / D.3 |
| $\det(A) \ne 0$ | D.5 |

These equivalences are exploited throughout Chapters 28–29: for instance, LUP decomposition (§28.1) can solve $Ax = b$ if and only if $A$ is nonsingular.

### Positive-Definiteness and Chapter 28

Positive-definite matrices arise in LUP decomposition without pivoting: a symmetric positive-definite matrix admits a **Cholesky decomposition** $A = LL^T$ (§28.3). Theorem D.6 shows that the Gram matrix $A^T A$ is always positive-definite when $A$ has full column rank — the fundamental fact behind least-squares and §33.3 normal equations.

### Matrix Multiplication Complexity

The $\Theta(n^3)$ bound from the standard triple-loop algorithm (MATRIX-MULTIPLY, p. 81) follows directly from equation (D.2): $n$ multiplications and $n-1$ additions per entry, $n^2$ entries. Strassen's algorithm (§4.2) achieves $\Theta(n^{\log_2 7})$ by reducing 8 recursive $n/2$-subproblems to 7, changing the recurrence from $T(n) = 8T(n/2) + \Theta(n^2)$ to $T(n) = 7T(n/2) + \Theta(n^2)$.

---

## Key Takeaways & Next Steps

| Concept | One-Line Definition | Appears In |
|---------|-------------------|-----------|
| Matrix multiplication | $c_{ij} = \sum_k a_{ik}b_{kj}$; time $\Theta(pqr)$ | Ch. 4 (Strassen), Ch. 28 |
| Transpose | $(A^T)_{ij} = a_{ji}$; $(AB)^T = B^T A^T$ | Ch. 28, 29, 33 |
| Inner product | $\langle x,y\rangle = x^T y$; commutative scalar | Geometric algorithms, Ch. 33 |
| Euclidean norm | $\|x\| = \sqrt{x^T x}$; $\|\lambda x\| = |\lambda|\|x\|$ | Ch. 33 (regression, SVM) |
| Inverse | $AA^{-1} = I$; unique; $(BA)^{-1} = A^{-1}B^{-1}$ | LUP decomposition (Ch. 28) |
| Rank | Column rank = row rank; $\le \min\{m,n\}$ | Solvability of linear systems |
| Full rank $\iff$ nonsingular | Theorem D.1 | LUP, LP (Ch. 29) |
| Null vector | Nonzero $x$ with $Ax = 0$ | Singularity detection |
| Determinant | Signed volume; $\det(AB) = \det A \cdot \det B$ | Invertibility check (Ch. 28) |
| Singular $\iff$ $\det = 0$ | Theorem D.5 | LUP, Cramer's rule |
| Positive-definite | $x^T Ax > 0$ for all $x \ne 0$; $A^T A$ is PD if full col rank | Cholesky (Ch. 28), least squares (Ch. 33) |
| Positive-semidefinite | $x^T Ax \ge 0$ for all $x \ne 0$ | Kernel methods (Ch. 33) |

**Key principles:**
1. **Rank = column rank = row rank** — justifies treating rank as a single matrix invariant.
2. **Full rank $\iff$ nonsingular $\iff$ no null vector $\iff$ $\det \ne 0$** — four equivalent characterizations of invertibility (Theorems D.1–D.5).
3. **$A^T A$ is positive-definite when $A$ has full column rank** — the key fact behind Cholesky decomposition and least-squares normal equations.
4. **Determinant encodes invertibility** — $\det(A) = 0$ is the exact criterion for singularity; elementary row operations multiply $\det$ by known constants, enabling Gaussian elimination.
5. **Matrix multiplication is not commutative** — order of operands always matters; $(AB)^T = B^T A^T$ reverses order in transposes and inverses.

---

### Navigation

**Previous:** [[AppC_Counting_and_Probability]]  
**Next:** *(Appendix D is the final appendix of CLRS 4th Edition)*  
**Hub:** [[Index_Introduction_to_Algorithms]]
