# ML Zoomcamp — Session 2, Lesson 7: Training Linear Regression — The Normal Equation

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 7 (video transcript). Covers the derivation of the Normal Equation from first principles — why $X$ is not directly invertible, how the Gram matrix restores invertibility, and how to implement the closed-form solution in NumPy, including the bias-absorption trick inside the training function.

---

## 1. Executive Summary

Lesson 2.7 answers the question left open in Lesson 2.6: *given* the matrix form $\hat{y} = Xw$, how do we actually **find** $w$? The approach is the **Normal Equation**:

$$\tilde{w}^* = (X^\top X)^{-1} X^\top y$$

This is a **closed-form, non-iterative** solution that directly computes the globally optimal weights (in the least-squares sense) in a single pass. It works because:

1. $X \in \mathbb{R}^{m \times (n+1)}$ is rectangular and cannot be directly inverted.
2. Multiplying through by $X^\top$ yields the square **Gram matrix** $X^\top X \in \mathbb{R}^{(n+1) \times (n+1)}$, which is generally invertible.
3. Left-multiplying by $(X^\top X)^{-1}$ isolates $w$ — the weights that minimize mean squared error.

The result is packaged into a clean `train_linear_regression(X, y)` function that handles bias absorption internally.

---

## 2. Zero-Loss Extraction

### 2.1 The Problem: Why Can't We Just Invert $X$?

We want to solve the linear system:

$$Xw = y$$

Algebraically, if $X$ were square and invertible, we could left-multiply both sides by $X^{-1}$:

$$X^{-1} X w = X^{-1} y \implies Iw = X^{-1} y \implies w = X^{-1} y$$

However, $X$ is **rectangular**: it has shape $m \times (n+1)$ where typically $m \gg n$ (many more training examples than features). Only square matrices can have inverses, so $X^{-1}$ does not exist. Furthermore, with $m > n+1$ equations and only $n+1$ unknowns, the system is **overdetermined** — no $w$ satisfies all equations exactly. We seek the *best approximate solution*.

### 2.2 The Normal Equation Derivation

**Step 1 — Multiply both sides by $X^\top$:**

$$X^\top X w = X^\top y$$

This transforms the rectangular system into a square system. The matrix $X^\top X$ is called the **Gram matrix**.

**Step 2 — Analyze the Gram matrix:**

$$G = X^\top X \in \mathbb{R}^{(n+1) \times (n+1)}$$

It is square, symmetric, and positive semi-definite. When features are not linearly dependent, it is positive definite and therefore **invertible**.

**Step 3 — Left-multiply both sides by $(X^\top X)^{-1}$:**

$$(X^\top X)^{-1} X^\top X w = (X^\top X)^{-1} X^\top y$$

$$I \cdot w = (X^\top X)^{-1} X^\top y$$

$$\boxed{w^* = (X^\top X)^{-1} X^\top y}$$

This is the **Normal Equation**. The resulting $w^*$ is not an exact solution to $Xw = y$ (which generally has none), but it is the **least-squares optimal** $w$ — the one that minimizes $\|Xw - y\|^2$.

### 2.3 Full Implementation

```python
import numpy as np

# -------------------------------------------------------
# Step 1: Build a test matrix and target vector
# -------------------------------------------------------
# Must have more rows than columns for the inverse to exist
X = np.array([
    [2, 4, 5, 6],
    [1, 4, 5, 6],
    [2, 5, 2, 2],
    [2, 5, 2, 5],
    [1, 2, 5, 2],
], dtype=float)

y = np.array([95, 87, 110, 102, 78], dtype=float)


# -------------------------------------------------------
# Step 2: Prepend ones column (add bias feature)
# -------------------------------------------------------
ones = np.ones(X.shape[0])         # shape: (m,)
X_aug = np.column_stack([ones, X]) # shape: (m, n+1)


# -------------------------------------------------------
# Step 3: Compute the Gram matrix
# -------------------------------------------------------
XtX = X_aug.T.dot(X_aug)           # shape: (n+1, n+1)


# -------------------------------------------------------
# Step 4: Invert the Gram matrix
# -------------------------------------------------------
XtX_inv = np.linalg.inv(XtX)       # shape: (n+1, n+1)

# Sanity check — should be very close to identity matrix
# (small floating-point residuals are expected and harmless)
identity_approx = XtX_inv.dot(XtX)


# -------------------------------------------------------
# Step 5: Apply the Normal Equation
# -------------------------------------------------------
w_full = XtX_inv.dot(X_aug.T).dot(y)  # shape: (n+1,)

w0 = w_full[0]    # bias term (intercept)
w  = w_full[1:]   # feature coefficients [w1, w2, ..., wn]


# -------------------------------------------------------
# Complete reusable function
# -------------------------------------------------------
def train_linear_regression(X, y):
    """
    Trains linear regression via the Normal Equation.
    Bias absorption (ones column) is handled internally.

    Returns:
        w0 : float  — bias / intercept
        w  : ndarray — feature weights, shape (n,)
    """
    ones = np.ones(X.shape[0])
    X = np.column_stack([ones, X])   # augment with bias column

    XtX     = X.T.dot(X)
    XtX_inv = np.linalg.inv(XtX)
    w_full  = XtX_inv.dot(X.T).dot(y)

    return w_full[0], w_full[1:]     # (bias, feature weights)


# Usage — callers do NOT need to add the ones column themselves
w0, w = train_linear_regression(X, y)
print(f"Bias w0 = {w0:.4f}")
print(f"Weights = {w}")
```

### 2.4 Dimensions Reference

| Symbol | Shape | Description |
|---|---|---|
| $X$ | $(m,\; n+1)$ | Augmented feature matrix (ones column prepended) |
| $y$ | $(m,)$ | Target vector (e.g., log-prices) |
| $X^\top X$ | $(n+1,\; n+1)$ | Gram matrix — square, symmetric |
| $(X^\top X)^{-1}$ | $(n+1,\; n+1)$ | Inverse of Gram matrix |
| $w^*$ | $(n+1,)$ | Optimal weight vector: $[w_0,\, w_1,\, \ldots,\, w_n]$ |

### 2.5 Key Formula Reference

| Formula | Role |
|---|---|
| $Xw = y$ | The ideal (generally unsolvable) linear system |
| $X^\top X w = X^\top y$ | The normal equations — always solvable when $X^\top X$ is invertible |
| $w^* = (X^\top X)^{-1} X^\top y$ | Closed-form optimal weights (Normal Equation) |
| $X^\top X \in \mathbb{R}^{(n+1) \times (n+1)}$ | Gram matrix — square, invertible when features are not collinear |

---

## 3. Deep-Dive Explanations

### 3.1 Why Multiplying by $X^\top$ Is the "Magic Step"

The key geometric insight: the system $Xw = y$ asks for a vector $y$ to lie exactly in the column space of $X$. With $m > n+1$, a generic $y$ does **not** lie in this subspace — hence no exact solution exists.

Multiplying through by $X^\top$ projects everything onto the column space of $X$. The vector $X^\top y$ is the projection of $y$ into that space, and the equation $X^\top X w = X^\top y$ always has a solution. That solution $w^*$ produces the prediction $X w^*$ that is the **orthogonal projection** of $y$ onto the column space of $X$ — the closest any prediction can get to $y$ under Euclidean distance. This is equivalent to minimizing:

$$\text{MSE}(w) = \frac{1}{m} \|Xw - y\|^2$$

A full proof appears in *The Elements of Statistical Learning* (Hastie, Tibshirani, Friedman), Chapter 3.

### 3.2 Why the Gram Matrix Is (Usually) Invertible

$X^\top X$ is positive semi-definite by construction: for any vector $v$,

$$v^\top (X^\top X) v = \|Xv\|^2 \geq 0$$

It becomes **positive definite** (and therefore invertible) when the columns of $X$ are linearly independent — i.e., no feature is an exact linear combination of other features. In practice this means:

- No duplicate columns
- No feature that is a constant multiple of another
- No column of all-zeros (after the ones column is added)

When features *are* collinear, $X^\top X$ is singular. The standard remedy is **ridge regularization**: replace $X^\top X$ with $X^\top X + \lambda I$, which always has an inverse for any $\lambda > 0$.

### 3.3 Floating-Point Identity Matrix — Why the Residuals Are Normal

When verifying `XtX_inv.dot(XtX) ≈ I`, off-diagonal entries will be tiny (e.g., $10^{-15}$) instead of exact zeros. This is **not a bug**. Floating-point arithmetic operates at ~15–16 significant decimal digits of precision (IEEE 754 double), so:

- Matrix multiplication accumulates rounding errors at each multiply-add step.
- An $(n+1) \times (n+1)$ matrix multiply performs $O((n+1)^2)$ such operations.
- The accumulated error is on the order of $\epsilon_\text{machine} \approx 2.2 \times 10^{-16}$ per operation.

The residuals can be safely treated as zero. They do not affect the quality of the computed weights.

### 3.4 Interpreting the Bias Term $w_0$

The bias is the **baseline prediction**: the value $g(x)$ would take if every feature were zero. In the car price problem:

- A positive $w_0$ means even a car with zero horsepower, zero age, etc., has a nonzero base price — the model starts from a non-zero reference.
- Without the bias, the hyperplane is forced through the origin, distorting all weights to compensate.

Bias absorption (prepending a column of 1s to $X$) is done **inside** `train_linear_regression`, so callers pass their raw feature matrix $X$ and receive a separate `w0` they can use to reconstruct predictions:

```python
# Applying the model after training
def apply_model(X, w0, w):
    return w0 + X.dot(w)   # equivalent to X_aug.dot([w0, *w])
```

### 3.5 Interpreting Negative Weights

If a trained weight $w_j < 0$, feature $j$ **decreases** the prediction as it increases. In the car example, age likely has a negative weight: each additional year reduces the predicted price. This is meaningful domain knowledge extracted automatically by the Normal Equation from the training data.

### 3.6 Why the Normal Equation vs. Gradient Descent?

| Property | Normal Equation | Gradient Descent |
|---|---|---|
| Iterative? | No — single closed-form step | Yes — many iterations needed |
| Complexity | $O(m(n+1)^2 + (n+1)^3)$ | $O(k \cdot m \cdot (n+1))$ for $k$ iterations |
| Scales to large $n$? | Poor — matrix inversion is $O((n+1)^3)$ | Good — avoids large matrix inversion |
| Scales to large $m$? | Acceptable — $X^\top X$ accumulation is $O(m(n+1)^2)$ | Good — mini-batch variants exist |
| Hyperparameters | None | Learning rate, batch size, stopping criterion |
| Best use case | Small to medium $n$ (up to ~10,000 features) | Large-scale / high-dimensional problems |

For the ML Zoomcamp car dataset ($m \approx 11{,}914$ rows, $n \approx 15$ features), the Normal Equation is instant. It becomes impractical when $n$ is in the hundreds of thousands (e.g., NLP bag-of-words), where gradient descent is preferred.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| $X$ is rectangular | Cannot invert directly; the linear system $Xw = y$ is overdetermined |
| Multiply by $X^\top$ | Converts to a square system via the Gram matrix $X^\top X$ |
| Normal Equation | $w^* = (X^\top X)^{-1} X^\top y$ — closed-form, globally optimal in least-squares sense |
| Invertibility condition | $X^\top X$ is invertible iff columns of $X$ are linearly independent (no multicollinearity) |
| Floating-point check | `XtX_inv.dot(XtX) ≈ I` with tiny off-diagonals is normal — not a bug |
| Bias is internal | `train_linear_regression` adds the ones column inside; callers pass raw $X$ |
| Negative weights | Valid — they encode a decrease in prediction per unit increase in that feature |

**Next step:** Lesson 2.8 — use `train_linear_regression` on the actual car dataset to predict prices and evaluate the model with RMSE.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| $X \in \mathbb{R}^{m \times (n+1)}$ | Augmented feature matrix (ones column prepended) |
| $y \in \mathbb{R}^m$ | Target vector (e.g., log-prices) |
| $G = X^\top X$ | Gram matrix — $(n+1) \times (n+1)$, square, symmetric |
| $G^{-1} = (X^\top X)^{-1}$ | Inverse of Gram matrix |
| $w^* = G^{-1} X^\top y$ | Optimal weights via Normal Equation |
| $w_0$ | Bias / intercept — first element of $w^*$ |
| $w_1, \ldots, w_n$ | Feature coefficients — remaining elements of $w^*$ |

---

## Graph View Links

**Previous:** [[MLZ_S2_L06_Linear_Regression_Vector_Form]]
**Next:** [[MLZ_S2_L08_Baseline_Model_For_Car_Price_Prediction]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
