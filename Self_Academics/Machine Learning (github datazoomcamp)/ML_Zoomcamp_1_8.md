---
title: "ML Zoomcamp 1.8 — Linear Algebra Refresher"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 1
lesson: 8
tags: [machine-learning, linear-algebra, numpy, vectors, matrices, dot-product, matrix-inverse, python, data-science]
source: "YouTube — ML Zoomcamp Session 1"
date_processed: 2026-05-22
---

# ML Zoomcamp 1.8 — Linear Algebra Refresher

---

## Executive Summary

Linear algebra is the **mathematical backbone of machine learning**. Every model — from simple linear regression to deep neural networks — is ultimately a sequence of vector and matrix operations. This lesson provides the minimal, practical subset of linear algebra that ML practitioners use daily: scalar-vector multiplication, vector addition, the dot product, matrix-vector multiplication, matrix-matrix multiplication, the identity matrix, and the matrix inverse.

The central pedagogical move of this lesson is to build each operation from the one before it: the dot product is implemented from scalar operations, matrix-vector multiplication is implemented from dot products, and matrix-matrix multiplication is implemented as a column-by-column sequence of matrix-vector multiplications. This layered construction makes the relationships between operations explicit and provides the intuition needed to understand why linear regression has the closed-form solution it does — which is introduced in the next session.

---

## Zero-Loss Extraction

### 1. Conventions: Column Vectors and Notation

In linear algebra, **vectors are written as column vectors** by convention — a vertical arrangement of numbers:

$$\mathbf{u} = \begin{bmatrix} 2 \\ 4 \\ 5 \\ 6 \end{bmatrix}$$

This is purely a notational convention. NumPy's default 1D array is conceptually a row vector, but the mathematical notation assumes columns. When translating between the two representations, the key operator is the **transpose** ($^T$), which flips a column vector into a row vector (and vice versa).

> Why columns? Because matrix-vector multiplication requires multiplying a row of the matrix by a column vector. The column convention makes the shape-compatibility rules visually consistent: a $(k \times n)$ matrix times an $(n \times 1)$ column vector produces a $(k \times 1)$ column vector.

---

### 2. Scalar-Vector Multiplication

Multiplying a vector by a scalar **scales every element** by that scalar:

$$2 \cdot \begin{bmatrix} 2 \\ 4 \\ 5 \\ 6 \end{bmatrix} = \begin{bmatrix} 4 \\ 8 \\ 10 \\ 12 \end{bmatrix}$$

In NumPy, this is a direct vectorized operation (no loop needed):

```python
u = np.array([2, 4, 5, 6])
2 * u   # → [4, 8, 10, 12]
```

---

### 3. Vector Addition

Adding two vectors combines them **element-wise**. Given vectors $\mathbf{u}$ and $\mathbf{v}$ of the same length $n$:

$$\mathbf{u} + \mathbf{v} = \begin{bmatrix} u_1 + v_1 \\ u_2 + v_2 \\ \vdots \\ u_n + v_n \end{bmatrix}$$

In NumPy:

```python
u = np.array([1, 2, 3])
v = np.array([2, 2, 2])
u + v   # → [3, 4, 5]
```

Both scalar multiplication and vector addition behave exactly as NumPy's element-wise operations — the NumPy behavior directly mirrors the mathematical definitions.

---

### 4. Dot Product (Vector-Vector Multiplication)

The **dot product** (also called the *inner product*) is the first non-trivial operation. Unlike element-wise multiplication (which produces a vector), the dot product **collapses two vectors into a single scalar**:

$$\mathbf{u}^T \mathbf{v} = \sum_{i=1}^{n} u_i \cdot v_i$$

**Worked example** — $\mathbf{u} = [2, 4, 5, 6]^T$, $\mathbf{v} = [1, 0, 0, 2]^T$:

$$\mathbf{u}^T \mathbf{v} = (2)(1) + (4)(0) + (5)(0) + (6)(2) = 2 + 0 + 0 + 12 = 14$$

**Notation note:** Writing $\mathbf{u}^T \mathbf{v}$ makes the shape rules explicit — $\mathbf{u}^T$ is a $(1 \times n)$ row vector, $\mathbf{v}$ is an $(n \times 1)$ column vector, and their product is a $(1 \times 1)$ scalar.

**Python implementation (from scratch):**

```python
def vector_vector_multiplication(u, v):
    assert u.shape[0] == v.shape[0]   # dimensionality must match
    n = u.shape[0]
    result = 0.0
    for i in range(n):
        result += u[i] * v[i]         # accumulate element-wise products
    return result

# Test: should return 14
vector_vector_multiplication(u, v)    # → 14.0
```

**NumPy shortcut:**

```python
np.dot(u, v)   # → 14
```

---

### 5. Matrix-Vector Multiplication

Given matrix $U$ of shape $(k \times n)$ and vector $\mathbf{v}$ of shape $(n \times 1)$, the product $U\mathbf{v}$ is a vector of shape $(k \times 1)$. Each element of the result is the **dot product of one row of $U$ with $\mathbf{v}$**:

$$\mathbf{w} = U\mathbf{v}, \quad w_i = \mathbf{u}_i^T \mathbf{v} = \sum_{j=1}^{n} U_{ij} \, v_j \quad \text{for } i = 0, 1, \ldots, k-1$$

**Dimension rule:** The number of **columns** of $U$ must equal the number of **elements** of $\mathbf{v}$ (both equal $n$). The result has as many elements as $U$ has rows ($k$).

**Python implementation (from scratch):**

```python
def matrix_vector_multiplication(U, v):
    assert U.shape[1] == v.shape[0]   # columns of U = length of v
    num_rows = U.shape[0]
    result = np.zeros(num_rows)
    for i in range(num_rows):
        result[i] = vector_vector_multiplication(U[i], v)   # dot product of row i with v
    return result

# Test
matrix_vector_multiplication(U, v)   # → 1D array of length k
```

**NumPy shortcut:**

```python
U.dot(v)   # identical result
```

---

### 6. Matrix-Matrix Multiplication

Given matrices $U$ of shape $(m \times n)$ and $V$ of shape $(n \times p)$, the product $W = UV$ has shape $(m \times p)$. The key insight is to **decompose $V$ into its columns**:

$$V = \begin{bmatrix} \mathbf{v}_0 & \mathbf{v}_1 & \cdots & \mathbf{v}_{p-1} \end{bmatrix}$$

Then each column of the result is a **matrix-vector product**:

$$W = UV, \quad W_{:,\, j} = U \mathbf{v}_j \quad \text{for } j = 0, 1, \ldots, p-1$$

**Dimension rule:** The number of columns of $U$ must equal the number of rows of $V$ (both equal $n$).

**Python implementation (from scratch):**

```python
def matrix_matrix_multiplication(U, V):
    assert U.shape[1] == V.shape[0]   # inner dimensions must match
    num_rows = U.shape[0]
    num_cols = V.shape[1]
    result = np.zeros((num_rows, num_cols))
    for i in range(num_cols):
        vi = V[:, i]                                          # extract i-th column of V
        Uvi = matrix_vector_multiplication(U, vi)             # U times that column
        result[:, i] = Uvi                                    # store as i-th column of result
    return result

# Test
matrix_matrix_multiplication(U, V)   # → (m × p) matrix
```

**NumPy shortcut:**

```python
U.dot(V)   # identical result
```

---

### 7. Identity Matrix

The **identity matrix** $I$ is the matrix equivalent of the number 1. It is a square matrix with **1s on the main diagonal and 0s everywhere else**:

$$I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$$

Formally, its entries are given by the Kronecker delta: $I_{ij} = \delta_{ij}$, where $\delta_{ij} = 1$ if $i = j$ and $0$ otherwise.

The defining property: multiplying any matrix by $I$ (from either side) returns the matrix unchanged:

$$U \cdot I = I \cdot U = U$$

**NumPy:**

```python
I = np.eye(3)     # 3×3 identity matrix
# array([[1., 0., 0.],
#        [0., 1., 0.],
#        [0., 0., 1.]])

V.dot(I)          # → V (identity property verified)
```

The `eye` function name comes from the mathematical symbol $I$ (read "eye") for identity.

---

### 8. Matrix Inverse

For a **square matrix** $A$ of shape $(n \times n)$, its inverse $A^{-1}$ is the unique matrix such that:

$$A^{-1} \cdot A = A \cdot A^{-1} = I$$

The inverse is the matrix analogue of the reciprocal: just as $x \cdot x^{-1} = 1$ for numbers, $A \cdot A^{-1} = I$ for matrices.

**Important constraints:**
- Only **square matrices** can have inverses (number of rows = number of columns).
- Not all square matrices are invertible — a matrix is invertible if and only if its determinant is non-zero (i.e., it is *non-singular*).

**NumPy** (lives in the `linalg` — linear algebra — subpackage):

```python
V_square = V[:3, :3]           # take a 3×3 sub-matrix
V_inv = np.linalg.inv(V_square)

# Verification: should give the identity matrix (up to floating-point precision)
V_inv.dot(V_square)            # → I (approximately)
```

---

### Summary Reference Table

| Operation | Math Notation | Shape Rule | NumPy |
|---|---|---|---|
| Scalar × vector | $c\,\mathbf{u}$ | $(n,) \to (n,)$ | `c * u` |
| Vector + vector | $\mathbf{u} + \mathbf{v}$ | $(n,) + (n,) \to (n,)$ | `u + v` |
| Dot product | $\mathbf{u}^T\mathbf{v}$ | $(n,) \cdot (n,) \to$ scalar | `np.dot(u, v)` |
| Matrix × vector | $U\mathbf{v}$ | $(k \times n) \cdot (n,) \to (k,)$ | `U.dot(v)` |
| Matrix × matrix | $UV$ | $(m \times n) \cdot (n \times p) \to (m \times p)$ | `U.dot(V)` |
| Identity matrix | $I$ | $(n \times n)$ | `np.eye(n)` |
| Matrix inverse | $A^{-1}$ | $(n \times n) \to (n \times n)$ | `np.linalg.inv(A)` |

---

## Deep-Dive Explanations

### Why Does the Dot Product Produce a Scalar?

The dot product can be understood in two complementary ways:

**Algebraically:** It is the sum of element-wise products — a natural measure of how much two vectors "agree." If $u_i$ and $v_i$ have the same sign for every $i$, the sum is large and positive. If they have opposite signs, terms cancel and the result approaches zero.

**Geometrically:** $\mathbf{u}^T\mathbf{v} = \|\mathbf{u}\| \|\mathbf{v}\| \cos\theta$, where $\theta$ is the angle between the vectors. This means:
- Two **perpendicular vectors** have dot product 0 (orthogonality).
- Two **parallel vectors** have maximum dot product $\|\mathbf{u}\|\|\mathbf{v}\|$.

In ML, the dot product is used as a **similarity measure**: a prediction in linear regression is $\hat{y} = \mathbf{w}^T\mathbf{x}$, the dot product between the weight vector $\mathbf{w}$ and the feature vector $\mathbf{x}$. A large positive dot product means the features align strongly with the learned weights.

---

### Why NumPy's `*` Is NOT the Dot Product

This is one of the most common sources of confusion for beginners:

```python
u = np.array([2, 4, 5, 6])
v = np.array([1, 0, 0, 2])

u * v        # → [2, 0, 0, 12]   element-wise product (NOT dot product)
np.dot(u, v) # → 14              dot product (sum of element-wise products)
```

NumPy's `*` operator applies the linear algebra definition of **scalar multiplication extended to arrays**, not the dot product. To get the dot product you must use `np.dot(u, v)` or equivalently `u @ v` (the `@` operator, introduced in Python 3.5+, is the matrix multiplication operator).

---

### The Layered Construction of Matrix Multiplication

The transcript makes an important pedagogical point: matrix-matrix multiplication is not defined independently — it is built from simpler operations:

```
Scalar operations
    └──► Dot product (vector-vector)
              └──► Matrix-vector multiplication
                        └──► Matrix-matrix multiplication
```

Each layer is reducible to the one below. This hierarchy matters because:
1. It shows that matrix multiplication is just **organized dot products** — no magic.
2. NumPy's `dot` function resolves which computation to perform based on input shapes, using the same conceptual hierarchy.
3. When implementing these from scratch (as the lesson does), you can test each layer independently before composing them.

---

### Shape Rules — The Single Most Important Debugging Skill

Almost every NumPy error in ML practice traces back to a shape mismatch. The rules are:

| Operation | Requirement | Output Shape |
|---|---|---|
| $\mathbf{u}^T\mathbf{v}$ | `len(u) == len(v)` | scalar |
| $U\mathbf{v}$ | `U.shape[1] == v.shape[0]` | `(U.shape[0],)` |
| $UV$ | `U.shape[1] == V.shape[0]` | `(U.shape[0], V.shape[1])` |

The **inner dimensions** must match; the **outer dimensions** define the result shape. This is why assertions appear first in all three implementations — they enforce the mathematical preconditions explicitly.

---

### Identity Matrix as the "Multiplicative One" for Matrices

The analogy in the transcript — "identity matrix is like the number 1" — is mathematically precise. In the real numbers, 1 is the **multiplicative identity**: $x \cdot 1 = 1 \cdot x = x$ for all $x$. The identity matrix $I$ is the multiplicative identity for the ring of square matrices: $AI = IA = A$ for any compatible square matrix $A$.

This is why $I$ appears in the definition of the inverse. Just as $x \cdot x^{-1} = 1$ (the number returns to the identity), $A \cdot A^{-1} = I$ (the matrix returns to the matrix identity).

---

### Why the Matrix Inverse Matters for ML

The matrix inverse will be directly used in the **closed-form solution for linear regression** (covered in the next session). Linear regression seeks weights $\mathbf{w}$ minimizing squared error, and the exact solution is:

$$\mathbf{w} = (X^T X)^{-1} X^T \mathbf{y}$$

Here $X$ is the feature matrix, $\mathbf{y}$ is the target vector, and $(X^T X)^{-1}$ is the matrix inverse of the **Gram matrix** $X^T X$. Every linear algebra concept from this lesson — dot products, matrix multiplication, transposition, the inverse — appears in this single formula. This is why the lesson exists: the payoff comes immediately in Session 2.

---

### Numerical Precision and Floating-Point Inverses

When verifying that $A^{-1} A = I$ using `np.linalg.inv`, the result is rarely *exactly* the identity matrix — it will have very small floating-point errors (on the order of $10^{-15}$):

```python
V_inv.dot(V_square)
# array([[ 1.00000000e+00,  2.22044605e-16, -1.11022302e-16],
#        [ 0.00000000e+00,  1.00000000e+00,  0.00000000e+00],
#        [ 0.00000000e+00,  0.00000000e+00,  1.00000000e+00]])
```

These tiny off-diagonal values are **rounding errors from floating-point arithmetic**, not errors in the algorithm. Use `np.allclose(result, np.eye(n))` to check approximate equality in practice.

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **Vectors in linear algebra are column vectors.** The $(1 \times n)$ row-vector notation $\mathbf{u}^T$ (transpose) is used when writing the dot product as a matrix product: $\mathbf{u}^T\mathbf{v}$.

2. **The dot product is the workhorse of ML.** It collapses two vectors of the same length into a scalar via $\sum_{i=1}^{n} u_i v_i$. NumPy: `np.dot(u, v)`.

3. **`u * v` in NumPy is element-wise, NOT the dot product.** This distinction is critical.

4. **Matrix-vector multiplication is a stack of dot products** — one per row of the matrix. Shape rule: `U.shape[1] == v.shape[0]`. NumPy: `U.dot(v)`.

5. **Matrix-matrix multiplication is column-by-column matrix-vector multiplication.** Shape rule: inner dimensions must match (`U.shape[1] == V.shape[0]`). NumPy: `U.dot(V)`.

6. **The identity matrix $I$ behaves like the number 1.** Create with `np.eye(n)`.

7. **The matrix inverse $A^{-1}$** satisfies $A^{-1}A = I$. Only square, non-singular matrices have inverses. Compute with `np.linalg.inv(A)`.

8. **These operations combine directly in the linear regression formula** $\mathbf{w} = (X^TX)^{-1}X^T\mathbf{y}$ — the closed-form solution introduced in Session 2.

### What's Coming Next

- **Lesson 1.9:** Introduction to **Pandas** — the library for tabular data manipulation built on top of NumPy. DataFrames are the primary data structure for loading, exploring, and preparing ML datasets.
- **Session 2:** The linear algebra from this lesson is applied directly to derive and implement **linear regression** using the normal equation $(X^TX)^{-1}X^T\mathbf{y}$.

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]] | [[ML_Zoomcamp_1_7]]
