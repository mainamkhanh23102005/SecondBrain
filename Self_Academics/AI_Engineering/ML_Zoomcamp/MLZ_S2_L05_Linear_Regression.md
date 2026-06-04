# ML Zoomcamp — Session 2, Lesson 5: Linear Regression

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 5 (video transcript). Introduces the linear regression model formula, intuition behind bias and weights, and a from-scratch Python implementation applied to the car price prediction dataset.

---

## 1. Executive Summary

Linear regression is the foundational regression model: it produces a **weighted sum** of input features plus a bias term. Given a feature vector $x_i$ representing one car, the model computes a predicted (log-)price $\hat{y}_i = w_0 + \sum_{j=1}^{n} w_j x_{ij}$. The weights $w_j$ encode how each feature pushes the price up or down. This lesson builds the model from scratch in Python, applies it to one concrete car (a 2015 Rolls-Royce Phantom), and shows how to interpret and invert the log-transformed prediction.

**The key question left open:** how do we *find* the right weights? — that is Lesson 2.7 (normal equation / gradient descent).

---

## 2. Zero-Loss Extraction

### 2.1 The Linear Regression Formula

For a single observation $x_i \in \mathbb{R}^n$:

$$g(x_i) = w_0 + \sum_{j=1}^{n} w_j \, x_{ij}$$

| Symbol | Meaning |
|---|---|
| $g(x_i)$ | Model's prediction for car $i$ (in log-price space) |
| $w_0$ | **Bias term** — base prediction when features give no information |
| $w_j$ | Weight for feature $j$ — how much one unit of $x_{ij}$ shifts the prediction |
| $x_{ij}$ | Value of feature $j$ for car $i$ |
| $n$ | Number of features |

### 2.2 Concrete Example — Row 10: Rolls-Royce Phantom Drophead Coupe (2015)

Using only three features for clarity:

| Feature | Value | Weight | Contribution |
|---|---|---|---|
| `engine_hp` | 453 | 0.01 | $453 \times 0.01 = 4.53$ |
| `city_mpg` | 11 | 0.04 | $11 \times 0.04 = 0.44$ |
| `popularity` | 86 | 0.002 | $86 \times 0.002 = 0.172$ |
| **Bias** $w_0$ | — | — | 7.17 |
| **Total** $\hat{y}_{\log}$ | — | — | **≈ 12.31** |

Inverting the log transform to get dollars:

$$\hat{\text{price}} = e^{\hat{y}_{\log}} - 1 = \texttt{np.expm1}(12.31) \approx \$222{,}000$$

### 2.3 From-Scratch Python Implementation

```python
import numpy as np

def linear_regression(xi, w0, w):
    """
    xi : list/array of feature values for one observation (length n)
    w0 : bias scalar
    w  : list/array of feature weights (length n)
    """
    n = len(xi)
    prediction = w0
    for j in range(n):
        prediction += w[j] * xi[j]
    return prediction


# --- Example usage (Row 10: Rolls-Royce Phantom) ---
xi = [453, 11, 86]        # engine_hp, city_mpg, popularity
w0 = 7.17
w  = [0.01, 0.04, 0.002]

log_pred   = linear_regression(xi, w0, w)   # ≈ 12.31
price_pred = np.expm1(log_pred)             # ≈ $222,000
print(f"Log-price prediction : {log_pred:.4f}")
print(f"Price prediction      : ${price_pred:,.0f}")
```

---

## 3. Deep-Dive Explanations

### 3.1 What Is the Bias Term $w_0$?

$w_0$ is the model's prediction for a **hypothetical average car** when every feature value is zero (or equivalently, before any feature adjustments are applied). Intuitively:

- Think of it as "what would we guess if we knew nothing specific about this car?"
- In our example, $w_0 = 7.17$ in log-price space, which corresponds to $e^{7.17} - 1 \approx \$1{,}300$ — a very cheap baseline that features then push upward.
- Without a bias term, the regression line is forced through the origin, severely limiting the model's expressive power.

### 3.2 Interpreting Individual Weights

Each weight $w_j$ measures **how much the log-price changes per unit increase in feature $j$**, holding all other features constant. This is the standard *ceteris paribus* interpretation of linear coefficients.

| Feature | Weight | Interpretation |
|---|---|---|
| `engine_hp` = 0.01 | Per extra horsepower, log-price rises by 0.01 → price multiplied by $e^{0.01} \approx 1.01$ (1% more expensive) |
| `city_mpg` = 0.04 | Higher city fuel efficiency → more expensive. Counterintuitive? High-performance luxury cars often have thirsty engines yet command premium prices, so mpg tracks engineering sophistication. |
| `popularity` = 0.002 | Twitter mentions have tiny weight — one mention barely moves the needle. You'd need thousands of extra mentions to see a meaningful price difference. |

> **Caution:** Weights in a naive linear model are **not causally interpretable** — they absorb correlated signals from omitted variables. Engine HP and `city_mpg` are negatively correlated in the raw data, so their weights compensate for each other.

### 3.3 Why Train on Log-Price, Not Raw Price?

As established in Lesson 2.3:
- Raw MSRP has a **long-tail distribution** — a few $1M+ exotic cars dominate the loss function.
- The log transform converts MSE on log-price into approximately **mean squared log error (MSLE)** on raw price, which treats proportional errors equally (a 10% error on a $10k car counts as much as on a $200k car).
- After prediction, invert with `np.expm1` to recover dollars.

$$\hat{\text{price}} = e^{\hat{y}} - 1 \quad \longleftrightarrow \quad \hat{y} = \ln(1 + \text{price})$$

### 3.4 The For-Loop Is Inefficient — Why Do We Write It?

The explicit `for j in range(n)` loop makes the formula concrete and debuggable. In practice, this is a **dot product** — covered in Lesson 2.6, where we rewrite this as:

$$g(x_i) = x_i^\top w$$

NumPy's vectorized dot product (`np.dot`) computes this orders of magnitude faster than a Python loop. The loop exists here only for pedagogical clarity.

### 3.5 Edge Case: What If $n = 0$?

If no features are provided (`xi = []`, `w = []`), the loop body never executes and the function returns `w0` — the pure bias prediction. This is mathematically correct: $g(x_i) = w_0 + \sum_{j=1}^{0} (\cdot) = w_0$.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Linear regression formula | $\hat{y}_i = w_0 + \sum_j w_j x_{ij}$ — a weighted sum plus bias |
| Bias term | Always needed; anchors the model's baseline prediction |
| Weight interpretation | "Per-unit effect on log-price, holding other features fixed" |
| Log-space predictions | Predict `log1p(price)`; invert at output with `expm1` |
| Efficiency | Replace the for-loop with `np.dot(xi, w)` (covered in L2.6) |

**Next step:** Lesson 2.6 — reformulate the for-loop as a dot product and generalize from one row to the full feature matrix (matrix-vector multiplication).

---

## Graph View Links

**Previous:** [[MLZ_S2_L04_Validation_Framework]]
**Next:** [[MLZ_S2_L06_Linear_Regression_Vector_Form]]
**Hub:** [[ML_Zoomcamp_Session2_Hub]]
