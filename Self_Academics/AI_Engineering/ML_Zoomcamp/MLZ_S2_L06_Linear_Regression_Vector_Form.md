# ML Zoomcamp — Session 2, Lesson 6: Linear Regression — Vector Form

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 6 (video transcript). Covers the algebraic progression from a scalar loop → dot product → augmented vector notation → full matrix-vector formulation of linear regression. This is the mathematical backbone that enables efficient, vectorized training.

---

## 1. Executive Summary

Lesson 2.6 completes the algebraic picture of linear regression by showing three successive simplifications:

1. **Loop → Dot product:** the weighted sum $\sum_j w_j x_{ij}$ is exactly $x_i^\top w$ — a vector dot product.
2. **Bias absorption:** prepend a virtual feature $x_{i0} = 1$ to the feature vector and $w_0$ to the weight vector, eliminating the separate bias term.
3. **Single row → Full matrix:** stack all $m$ augmented feature vectors into matrix $X \in \mathbb{R}^{m \times (n+1)}$; then the predictions for all cars simultaneously are $\hat{y} = Xw$ — one matrix-vector multiplication.

This formulation is not just compact notation — it is how NumPy (and every ML library) executes linear regression on thousands of examples in microseconds via BLAS-optimized routines.

---

## 2. Zero-Loss Extraction

### 2.1 The Three Equivalent Formulations

#### Formulation 1 — Explicit Sum (Loop)

$$g(x_i) = w_0 + \sum_{j=1}^{n} w_j \, x_{ij}$$

#### Formulation 2 — Dot Product (Single Row)

$$g(x_i) = x_i^\top w \quad \text{where } x_i = \begin{bmatrix} x_{i1} \\ x_{i2} \\ \vdots \\ x_{in} \end{bmatrix}, \quad w = \begin{bmatrix} w_1 \\ w_2 \\ \vdots \\ w_n \end{bmatrix}$$

#### Formulation 3 — Augmented Dot Product (Bias Absorbed)

$$g(x_i) = \tilde{x}_i^\top \tilde{w} \quad \text{where } \tilde{x}_i = \begin{bmatrix} 1 \\ x_{i1} \\ \vdots \\ x_{in} \end{bmatrix}, \quad \tilde{w} = \begin{bmatrix} w_0 \\ w_1 \\ \vdots \\ w_n \end{bmatrix}$$

The prepended $1$ acts as a "dummy feature" that always multiplies $w_0$ — the bias — so the entire prediction collapses into a single dot product.

#### Formulation 4 — Matrix Form (All Rows at Once)

$$\hat{y} = X \tilde{w}$$

where

$$X = \begin{bmatrix} 1 & x_{11} & x_{12} & \cdots & x_{1n} \\ 1 & x_{21} & x_{22} & \cdots & x_{2n} \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ 1 & x_{m1} & x_{m2} & \cdots & x_{mn} \end{bmatrix} \in \mathbb{R}^{m \times (n+1)}, \quad \tilde{w} \in \mathbb{R}^{n+1}, \quad \hat{y} \in \mathbb{R}^m$$

Each row of $X\tilde{w}$ is the dot product of that row with $\tilde{w}$ — i.e., the prediction for one car. All $m$ predictions are computed in a single BLAS call.

### 2.2 Full Code Progression

```python
import numpy as np

# -------------------------------------------------------
# Step 1: Explicit for-loop (pedagogical baseline)
# -------------------------------------------------------
def dot_product_loop(xi, w):
    result = 0.0
    for j in range(len(xi)):
        result += xi[j] * w[j]
    return result

def linear_regression_loop(xi, w0, w):
    return w0 + dot_product_loop(xi, w)


# -------------------------------------------------------
# Step 2: NumPy dot product (no bias absorbed)
# -------------------------------------------------------
def linear_regression_dot(xi, w0, w):
    return w0 + np.dot(xi, w)


# -------------------------------------------------------
# Step 3: Augmented vector (bias absorbed into dot product)
# -------------------------------------------------------
xi = [453, 11, 86]          # engine_hp, city_mpg, popularity
w0 = 7.17
w  = [0.01, 0.04, 0.002]

w_aug  = [w0] + w           # [7.17, 0.01, 0.04, 0.002]
xi_aug = [1]  + xi          # [1, 453, 11, 86]

pred = np.dot(xi_aug, w_aug)   # scalar — same result as above


# -------------------------------------------------------
# Step 4: Full matrix form (multiple cars at once)
# -------------------------------------------------------
# Three example cars (already augmented with leading 1)
X = np.array([
    [1, 148, 24, 1385],   # car 1
    [1, 132, 25,  300],   # car 2
    [1, 453, 11,   86],   # Rolls-Royce (row 10)
])  # shape: (3, 4) — m=3 cars, n+1=4 columns

w_vec = np.array(w_aug)    # shape: (4,)

y_hat = X.dot(w_vec)       # shape: (3,) — one log-price per car
prices = np.expm1(y_hat)   # invert log transform → actual dollars
print(y_hat)
print(prices)
```

### 2.3 Dimensions Reference

| Symbol | Shape | Description |
|---|---|---|
| $x_i$ | $(n,)$ | Feature vector for one car (no bias column) |
| $\tilde{x}_i$ | $(n+1,)$ | Augmented feature vector (1 prepended) |
| $\tilde{w}$ | $(n+1,)$ | Weight vector including $w_0$ |
| $X$ | $(m, n+1)$ | Full feature matrix (all cars, bias column prepended) |
| $\hat{y}$ | $(m,)$ | Predictions for all $m$ cars |

---

## 3. Deep-Dive Explanations

### 3.1 Why Is $\sum_j w_j x_{ij}$ a Dot Product?

The dot product of two vectors $a, b \in \mathbb{R}^n$ is defined as:

$$a \cdot b = \sum_{j=1}^{n} a_j b_j$$

Setting $a = x_i$ (feature values) and $b = w$ (weights), we get exactly $\sum_{j=1}^{n} w_j x_{ij}$. This is not just a notational trick — it connects linear regression to the rich geometry of inner product spaces:
- $x_i^\top w$ measures the **projection** of $x_i$ onto the direction $w$.
- Maximizing/minimizing this over $x_i$ on the unit sphere gives the direction of $w$ itself — the eigenvector intuition behind PCA.

### 3.2 Why Absorb the Bias Into the Dot Product?

The separate bias term $w_0$ is algebraically annoying:
- It needs special handling in every formula.
- It breaks the clean $\hat{y} = Xw$ expression.
- Libraries like NumPy/sklearn expect a unified weight vector.

By prepending a column of ones to $X$ and a $w_0$ entry to $\tilde{w}$, the bias becomes just another weight multiplied by a constant feature $x_{i0} = 1$. This:
1. Reduces the entire model to a single matrix multiply.
2. Makes gradient computation uniform — $\frac{\partial}{\partial w_0}$ follows the same rule as $\frac{\partial}{\partial w_j}$.
3. Is how every major library handles intercepts internally.

### 3.3 From One Row to $m$ Rows — The Matrix Argument

For each car $i$, the prediction is:

$$\hat{y}_i = \tilde{x}_i^\top \tilde{w} = \sum_{k=0}^{n} \tilde{x}_{ik} \, \tilde{w}_k$$

Stack all $m$ predictions into a column vector $\hat{y}$:

$$\hat{y} = \begin{bmatrix} \tilde{x}_1^\top \tilde{w} \\ \tilde{x}_2^\top \tilde{w} \\ \vdots \\ \tilde{x}_m^\top \tilde{w} \end{bmatrix} = \underbrace{\begin{bmatrix} \tilde{x}_1^\top \\ \tilde{x}_2^\top \\ \vdots \\ \tilde{x}_m^\top \end{bmatrix}}_{X} \tilde{w} = X \tilde{w}$$

This is **matrix-vector multiplication** — the standard linear algebra operation. NumPy's `X.dot(w)` maps directly to a BLAS `dgemv` call, running in compiled C/Fortran and utilizing CPU SIMD instructions. For $m = 11{,}914$ rows and $n = 15$ features, this is ~$180{,}000$ multiply-adds completed in microseconds, versus milliseconds for a Python for-loop.

### 3.4 The Ones Column — A Common Source of Bugs

When constructing $X$ manually, forgetting to prepend the bias column is one of the most frequent linear regression bugs:

```python
# WRONG — no bias column
X_bad = df_train[features].values          # shape (7150, n)

# CORRECT — prepend ones
ones  = np.ones((len(df_train), 1))
X_ok  = np.column_stack([ones, df_train[features].values])  # (7150, n+1)
```

If you omit the ones column:
- The model is forced to predict $\hat{y} = 0$ when all features are zero.
- The bias must be implicitly absorbed into other weights, distorting all coefficients.
- Training error will be higher than necessary.

### 3.5 Why Not Just Use `sklearn.LinearRegression`?

`sklearn` handles bias (`fit_intercept=True`), feature matrix construction, and weight solving automatically. The manual implementation exists here to:
1. Build intuition for what the model *actually does* numerically.
2. Prepare for deriving the **Normal Equation** ($\tilde{w} = (X^\top X)^{-1} X^\top y$) in the next lesson — you can't understand the derivation without knowing the matrix form.
3. Enable implementing custom variants (regularization, weighted regression) without being a black-box user.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Loop → dot product | $\sum_j w_j x_{ij} = x_i^\top w$ — same computation, vector notation |
| Bias absorption | Prepend 1 to $\tilde{x}_i$ and $w_0$ to $\tilde{w}$; the formula becomes a pure dot product |
| Single row → matrix | Stack rows into $X \in \mathbb{R}^{m \times (n+1)}$; all predictions in one call: $\hat{y} = X\tilde{w}$ |
| Efficiency | `X.dot(w)` uses BLAS; avoid Python for-loops over rows in real code |
| Ones column | Always prepend a column of ones to $X$ when computing $X\tilde{w}$ manually |

**Next step:** Lesson 2.7 — derive the optimal weights $\tilde{w}^*$ via the **Normal Equation**, which minimizes mean squared error on the training set.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| $x_i$ | Raw feature vector for car $i$, shape $(n,)$ |
| $\tilde{x}_i = [1; x_i]$ | Augmented feature vector, shape $(n+1,)$ |
| $w$ | Weight vector (no bias), shape $(n,)$ |
| $\tilde{w} = [w_0; w]$ | Augmented weight vector (with bias), shape $(n+1,)$ |
| $X$ | Feature matrix, shape $(m, n+1)$, rows are $\tilde{x}_i^\top$ |
| $\hat{y} = X\tilde{w}$ | Prediction vector, shape $(m,)$ |
| $y$ | True target vector (log-prices), shape $(m,)$ |

---

## Graph View Links

**Previous:** [[MLZ_S2_L05_Linear_Regression]]
**Next:** [[MLZ_S2_L07_Training_Linear_Regression]]
**Hub:** [[ML_Zoomcamp_Session2_Hub]]
