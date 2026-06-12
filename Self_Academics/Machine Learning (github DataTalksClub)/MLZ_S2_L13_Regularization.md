# ML Zoomcamp — Session 2, Lesson 13: Regularization

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 13 (video transcript). Covers the root cause of RMSE explosion from Lesson 2.12 — linear dependence making the Gram matrix singular — and the fix: **ridge regularization**, which adds a small multiple $r$ of the identity matrix to $X^\top X$ before inversion. Derives the regularized Normal Equation, implements `train_linear_regression_regularized`, and demonstrates recovery to RMSE ≈ 0.50.

---

## 1. Executive Summary

When the feature matrix $X$ contains nearly duplicate or linearly dependent columns (as it does after full one-hot encoding), the Gram matrix $G = X^\top X$ becomes nearly singular: its determinant approaches zero, and its inverse contains astronomically large values. The Normal Equation then multiplies these huge inverse entries by $X^\top y$, producing enormous weights — and correspondingly enormous RMSE.

The fix is **ridge regularization** (also called L2 regularization): before inverting the Gram matrix, add a small positive multiple of the identity matrix:

$$G_r = X^\top X + r I$$

$$\boxed{w^* = (X^\top X + rI)^{-1} X^\top y}$$

Adding $r > 0$ to every diagonal entry of $G$ guarantees that $G_r$ is **strictly positive definite** — and therefore invertible — regardless of the linear dependencies in $X$. The parameter $r$ is a hyperparameter controlling how strongly the weights are penalized: small $r$ is close to unregularized regression; large $r$ forces all weights toward zero (underfitting).

With $r = 0.01$, RMSE recovers from ~41 to ~0.50 — better than the pre-categorical baseline.

---

## 2. Zero-Loss Extraction

### 2.1 Root Cause: Linear Dependence and Singular Matrices

A matrix is **singular** (non-invertible) when its columns are linearly dependent — meaning at least one column can be expressed as a linear combination of the others.

**Constructed example with a duplicate column:**

```python
import numpy as np

# Column 2 and column 3 are identical — linear dependence
X = np.array([
    [1, 2, 2],
    [4, 5, 5],
    [7, 8, 8],
], dtype=float)

G = X.T.dot(X)
np.linalg.inv(G)
# LinAlgError: Singular matrix — inverse does not exist
```

**Near-duplicate column (adding tiny noise):**

```python
# Tiny perturbation — matrix is no longer exactly singular
X_noisy = np.array([
    [1, 2, 2.0001],
    [4, 5, 5.0001],
    [7, 8, 8.0001],
], dtype=float)

G_noisy = X_noisy.T.dot(X_noisy)
np.linalg.inv(G_noisy)
# Returns an "inverse" — but entries are ENORMOUS (e.g., 1e12)
```

NumPy does not raise an error for near-singular matrices, but the computed inverse is numerically useless — its entries are many orders of magnitude too large. When multiplied by $X^\top y$, the resulting weights inherit those enormous values.

This is exactly the situation in Lesson 2.12: one-hot encoding all categories of a variable creates columns that sum to the bias column (all-ones), producing near-perfect linear dependence.

### 2.2 The Fix: Adding to the Diagonal

Observation: if we add a positive constant to every diagonal entry of a matrix, we make all its eigenvalues strictly positive — which is the condition for invertibility.

```python
# Tiny diagonal addition stabilizes the inverse
r = 0.01
n = G_noisy.shape[0]
G_reg = G_noisy + r * np.eye(n)    # adds r to each diagonal entry

np.linalg.inv(G_reg)
# Now returns a well-conditioned inverse with reasonable-sized entries
```

As $r$ increases:
- Diagonal entries of $G_r$ increase → minimum eigenvalue increases → condition number improves.
- The resulting weights are **shrunk toward zero** — the model is prevented from assigning extremely large weights to collinear features.

### 2.3 The Regularized Normal Equation

The regularized version adds $rI$ to the Gram matrix before inversion:

$$\tilde{G} = X^\top X + rI \in \mathbb{R}^{(n+1) \times (n+1)}$$

$$w^* = \tilde{G}^{-1} X^\top y = (X^\top X + rI)^{-1} X^\top y$$

This is the **Ridge Regression** (L2-regularized linear regression) closed-form solution. It is guaranteed to be unique and numerically stable for any $r > 0$, regardless of the rank of $X$.

**Why this is equivalent to constrained optimization:**
Ridge regression can also be derived as the solution to:

$$w^* = \arg\min_w \left[\|Xw - y\|^2 + r\|w\|^2\right]$$

The $r\|w\|^2$ term penalizes large weights, creating a trade-off between fitting the data and keeping weights small. The closed-form solution to this constrained problem is exactly $(X^\top X + rI)^{-1} X^\top y$.

### 2.4 Implementation: `train_linear_regression_regularized`

```python
def train_linear_regression_regularized(X, y, r=0.01):
    """
    Ridge regression via the regularized Normal Equation.
    Solves: w* = (X^T X + r*I)^{-1} X^T y

    Parameters:
        X : ndarray, shape (m, n)  — feature matrix (NO bias column)
        y : ndarray, shape (m,)    — target vector
        r : float                  — regularization strength (default 0.01)

    Returns:
        w0 : float   — bias term
        w  : ndarray — feature weights, shape (n,)
    """
    ones = np.ones(X.shape[0])
    X_aug = np.column_stack([ones, X])        # shape: (m, n+1)

    XtX = X_aug.T.dot(X_aug)                 # Gram matrix: (n+1, n+1)
    XtX_reg = XtX + r * np.eye(XtX.shape[0]) # add r to diagonal
    XtX_inv = np.linalg.inv(XtX_reg)         # now well-conditioned

    w_full = XtX_inv.dot(X_aug.T).dot(y)     # shape: (n+1,)
    return w_full[0], w_full[1:]              # (bias, feature weights)
```

The only change from `train_linear_regression` is the single line `XtX_reg = XtX + r * np.eye(XtX.shape[0])`.

### 2.5 Effect on RMSE

```python
# Replacing unregularized function with regularized version
X_train = prepare_x(df_train)
w0, w   = train_linear_regression_regularized(X_train, y_train, r=0.01)

X_val  = prepare_x(df_val)
y_pred = w0 + X_val.dot(w)

print(rmse(y_val, y_pred))
# Output: ≈ 0.50  ← recovered from the ~41 explosion
```

### 2.6 Effect of `r` on Model Behavior

| $r$ value | Behavior | RMSE |
|---|---|---|
| 0 | Identical to unregularized — huge weights | ~41 (catastrophic) |
| 0.001 | Near-unregularized — still somewhat unstable | High |
| **0.01** | **Sweet spot — stable weights, good fit** | **~0.50** |
| 0.1 | Moderate regularization — weights shrinking | Slightly worse |
| 1 | Heavy regularization — weights heavily penalized | Noticeably worse |
| 10 | Extreme regularization — weights forced near zero | Much worse (underfitting) |

### 2.7 Dimensions Reference

| Symbol | Shape | Description |
|---|---|---|
| $X$ | $(m,\; 44)$ | Feature matrix (44 features after OHE) |
| $X^\top X$ | $(45,\; 45)$ | Gram matrix (44 features + bias column) |
| $rI$ | $(45,\; 45)$ | Regularization term: $r$ on diagonal, 0 elsewhere |
| $(X^\top X + rI)^{-1}$ | $(45,\; 45)$ | Regularized inverse — well-conditioned for any $r > 0$ |
| $w^*$ | $(45,)$ | Regularized optimal weights |

---

## 3. Deep-Dive Explanations

### 3.1 Linear Dependence in the OHE Context

In Lesson 2.12, one-hot encoding `number_of_doors` creates three columns:

$$\text{num\_doors\_2} + \text{num\_doors\_3} + \text{num\_doors\_4} = \mathbf{1}$$

where $\mathbf{1}$ is the all-ones vector — which is exactly the bias column added inside `train_linear_regression`. The augmented feature matrix $X_\text{aug}$ therefore has a column that is a perfect linear combination of three other columns. $X_\text{aug}^\top X_\text{aug}$ is exactly singular: $\det(X_\text{aug}^\top X_\text{aug}) = 0$.

With 7 categorical columns plus `number_of_doors`, there are 8 such perfect dependencies. In practice, due to rows having `NaN` values (filled with 0) and rows belonging to the "other" category (all five OHE columns = 0), the dependencies are usually near-perfect but not exact — hence near-singular rather than exactly singular, and NumPy "succeeds" at finding a pseudo-inverse with enormous entries.

### 3.2 Why Adding to the Diagonal Restores Invertibility

The eigendecomposition of a symmetric positive semi-definite matrix $G = Q \Lambda Q^\top$ gives eigenvalues $\lambda_1, \ldots, \lambda_{n+1} \geq 0$. Adding $rI$ shifts every eigenvalue by $r$:

$$G + rI = Q (\Lambda + rI) Q^\top$$

with eigenvalues $\lambda_1 + r, \ldots, \lambda_{n+1} + r > 0$ for any $r > 0$.

A matrix is invertible iff all its eigenvalues are strictly positive. Since $G$ is positive semi-definite (some eigenvalues may be 0), $G$ alone may not be invertible. But $G + rI$ has all eigenvalues $\geq r > 0$, so it is **strictly positive definite** and always invertible.

The inverse eigenvalues are $(\lambda_i + r)^{-1} \leq 1/r$, which is bounded — no more astronomically large entries.

### 3.3 Bias-Variance Trade-off via $r$

Ridge regularization introduces a classic **bias-variance trade-off**:

- **$r = 0$ (unregularized):** Minimum bias — the model can fit any linear relationship in the data, including spurious ones from collinear features. High variance — weights are sensitive to small perturbations in the data. In the collinear case, variance is infinite (singular matrix).
- **$r \to \infty$ (heavy regularization):** Maximum bias — all weights shrink toward zero, making the model predict the mean $w_0$ for everything. Zero variance — weights are fully determined by the prior ($w = 0$), ignoring the data.
- **Optimal $r$:** Balances fit quality (low bias) with weight stability (low variance). Found via hyperparameter search on the validation set (Lesson 2.14).

### 3.4 Ridge vs. Lasso Regularization

The lesson implements **ridge (L2) regularization**. A related alternative is **lasso (L1)**:

| Property | Ridge (L2): $r\|w\|_2^2$ | Lasso (L1): $r\|w\|_1$ |
|---|---|---|
| Closed-form solution | Yes — $(X^\top X + rI)^{-1} X^\top y$ | No — requires iterative solvers |
| Effect on weights | Shrinks all weights smoothly toward zero | Can set weights to *exactly* zero (sparse) |
| Feature selection | No — all features retained | Yes — irrelevant features zeroed out |
| Best for | Correlated features, stable shrinkage | Sparse signal, automatic feature selection |

For the car price dataset with many correlated OHE columns, ridge is the natural choice and has a clean closed-form solution consistent with the Normal Equation approach.

### 3.5 What the Regularization Term Does to Individual Weights

Without regularization, two perfectly collinear features $x_j$ and $x_k$ can have weights $w_j = +10^{12}$ and $w_k = -10^{12}$ — they cancel each other out in predictions, but their values are meaningless. With ridge regularization, the $r\|w\|^2$ penalty discourages both $w_j$ and $w_k$ from growing large. The model instead finds smaller, shared weights that are more numerically stable and more interpretable.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Singular Gram matrix | Caused by linearly dependent columns in $X$ (OHE dummy trap, duplicate features) |
| Near-singular | NumPy "inverts" it but with enormous entries → huge weights → RMSE explodes |
| Ridge regularization | Add $rI$ to Gram matrix before inversion: $w^* = (X^\top X + rI)^{-1} X^\top y$ |
| $r > 0$ guarantees | $X^\top X + rI$ is strictly positive definite → always invertible |
| Effect of increasing $r$ | Weights shrink toward zero; bias increases; variance decreases |
| RMSE recovery | From ~41 (no regularization) to ~0.50 (r=0.01) |
| L2 closed form | Unique advantage over L1: direct matrix formula, no iterative optimization |

**Next step:** Lesson 2.14 — tune $r$ by grid-searching values $\{0, 0.001, 0.01, 0.1, 1, 10\}$ on the validation set to confirm $r = 0.01$ as the optimal regularization strength.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| $G = X^\top X$ | Gram matrix — square, symmetric, positive semi-definite |
| $G_r = X^\top X + rI$ | Regularized Gram matrix — strictly positive definite for $r > 0$ |
| $r$ | Regularization hyperparameter — controls weight shrinkage strength |
| $I$ | Identity matrix — same size as $G$ |
| $w^* = G_r^{-1} X^\top y$ | Ridge regression closed-form solution |
| $r\|w\|^2$ | L2 penalty term — penalizes large weights in the loss function |
| Singular matrix | $\det(G) = 0$ — no inverse exists (linearly dependent columns) |
| Near-singular | $\det(G) \approx 0$ — inverse exists but with enormous entries |

---

## Graph View Links

**Previous:** [[MLZ_S2_L12_Categorical_Variables]]
**Next:** [[MLZ_S2_L14_Tuning_the_Model]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
