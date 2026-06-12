# ML Zoomcamp — Session 2, Lesson 9: Root Mean Squared Error (RMSE)

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 9 (video transcript). Covers the motivation for an objective regression metric, the step-by-step derivation of RMSE from first principles with a worked numerical example, and the clean NumPy implementation — setting up the validation-set evaluation pipeline introduced in Lesson 2.10.

---

## 1. Executive Summary

Lesson 2.9 answers the question left open in Lesson 2.8: *how do we objectively measure how bad — or good — our model is?* Visual histogram comparison is subjective and non-comparable across model versions. We need a single scalar number.

**Root Mean Squared Error (RMSE)** is that scalar. It measures the average magnitude of prediction errors in the same units as the target variable:

$$\text{RMSE} = \sqrt{\frac{1}{m} \sum_{i=1}^{m} \left(g(x_i) - y_i\right)^2}$$

The formula is built up in four steps — difference → square → mean → square root — each with a clear mathematical purpose. The lesson walks through a concrete 4-observation numerical example and implements the function in three lines of NumPy.

RMSE is the primary evaluation metric for the entire Session 2 car price prediction project.

---

## 2. Zero-Loss Extraction

### 2.1 Formula Decomposition

$$\text{RMSE} = \underbrace{\sqrt{\vphantom{\sum}\quad}}_{\text{step 4: root}} \underbrace{\frac{1}{m}}_{\text{step 3: mean}} \underbrace{\sum_{i=1}^{m}}_{\text{step 3: sum}} \underbrace{\left(g(x_i) - y_i\right)^2}_{\text{steps 1–2: squared error}}$$

| Step | Operation | Symbol | Purpose |
|---|---|---|---|
| 1 | Difference | $g(x_i) - y_i$ | Residual — how far off the prediction is |
| 2 | Square | $(\cdot)^2$ | Make all errors positive; penalise large errors more |
| 3 | Mean | $\frac{1}{m}\sum$ | Aggregate into a single number independent of dataset size |
| 4 | Square root | $\sqrt{\cdot}$ | Restore units to the same scale as the target variable |

### 2.2 Worked Numerical Example

Four observations, four predictions:

| $i$ | Prediction $g(x_i)$ | Actual $y_i$ | Difference | Squared Error |
|---|---|---|---|---|
| 1 | 10 | 9 | $10 - 9 = 1$ | $1^2 = 1.00$ |
| 2 | 9 | 9 | $9 - 9 = 0$ | $0^2 = 0.00$ |
| 3 | 11 | 10.5 | $11 - 10.5 = 0.5$ | $0.5^2 = 0.25$ |
| 4 | 10 | 11.5 | $10 - 11.5 = -1.5$ | $(-1.5)^2 = 2.25$ |

**Step 3 — Mean Squared Error (MSE):**

$$\text{MSE} = \frac{1 + 0 + 0.25 + 2.25}{4} = \frac{3.5}{4} = 0.875$$

**Step 4 — RMSE:**

$$\text{RMSE} = \sqrt{0.875} \approx 0.935$$

For these four observations, the model's predictions are off by about 0.93 units on average (in log-price units for the car dataset).

### 2.3 Implementation

**Full step-by-step version (pedagogical):**

```python
import numpy as np

def rmse(y, y_pred):
    """
    Root Mean Squared Error.

    Parameters:
        y      : ndarray, shape (m,) — true target values
        y_pred : ndarray, shape (m,) — model predictions

    Returns:
        float — RMSE score (same units as y)
    """
    error  = y - y_pred          # step 1: residuals, shape (m,)
    se     = error ** 2          # step 2: squared errors
    mse    = se.mean()           # step 3: mean (numpy's .mean() = sum / m)
    return np.sqrt(mse)          # step 4: square root
```

**Simplified one-liner (equivalent):**

```python
def rmse(y, y_pred):
    return np.sqrt(((y - y_pred) ** 2).mean())
```

**Verification with the numerical example:**

```python
y_pred = np.array([10, 9, 11, 10], dtype=float)
y      = np.array([ 9, 9, 10.5, 11.5], dtype=float)

print(rmse(y, y_pred))   # → 0.9354  ≈ 0.93 ✓
```

### 2.4 Baseline RMSE in the Car Price Context

Because the target variable is $\log(\text{price} + 1)$, RMSE is in log-price units. To convert an RMSE of $\epsilon$ to a rough price percentage error:

$$\text{price error} \approx e^\epsilon - 1$$

| RMSE (log scale) | Approximate price error |
|---|---|
| 0.1 | ~10.5% |
| 0.5 | ~65% |
| 0.76 (baseline) | ~114% — predictions off by more than 2× |
| 0.50 (after L2.11) | ~65% |

---

## 3. Deep-Dive Explanations

### 3.1 Why Square the Errors?

Two reasons:

1. **Sign cancellation.** A prediction of +2 above the true value and one of −2 below would average to zero error — falsely suggesting perfect performance. Squaring makes all errors positive so they accumulate rather than cancel.

2. **Quadratic penalty for outliers.** Squaring means a prediction that is 2× off contributes 4× as much to the score as a prediction that is 1× off. RMSE is therefore more sensitive to large individual errors than the Mean Absolute Error (MAE). In car pricing, a $20K prediction error on a $100K car should hurt more than twenty $1K errors — RMSE captures this.

### 3.2 Why Take the Square Root?

After squaring, the units become squared units (e.g., $\log(\$)^2$). Taking the square root restores the metric to the original units ($\log(\$)$), making it directly comparable to the target values. An RMSE of 0.5 in log-price has the same scale as the log-prices themselves (which range from ~8 to ~15).

Without the square root, the metric would be **MSE** (Mean Squared Error). Both are valid; RMSE is preferred when interpretability in original units matters.

### 3.3 RMSE vs. MAE vs. MSE

| Metric | Formula | Units | Outlier sensitivity | Use case |
|---|---|---|---|---|
| MAE | $\frac{1}{m}\sum\|y_i - \hat{y}_i\|$ | Same as $y$ | Low — linear in error | When large errors are not catastrophic |
| MSE | $\frac{1}{m}\sum(y_i - \hat{y}_i)^2$ | Squared units | High | Gradient-based optimization (convex, smooth) |
| **RMSE** | $\sqrt{\text{MSE}}$ | **Same as $y$** | **High** | **General regression evaluation; interpretable** |

RMSE combines the interpretability of MAE (same units) with the outlier-sensitivity of MSE (squared errors). It is the standard metric for regression evaluation in most applied ML contexts.

### 3.4 Why `.mean()` Instead of Manual Sum-and-Divide

NumPy's `.mean()` method is:

```python
arr.mean()  # ≡  arr.sum() / len(arr)
```

Using `.mean()` directly is cleaner and numerically stable — it avoids materialising the sum variable and handles edge cases (e.g., very large arrays where the sum could overflow before dividing). It also works correctly for any shape of array due to NumPy broadcasting.

### 3.5 RMSE as the Basis for All Future Comparisons

Every model improvement in Lessons 2.11–2.14 is evaluated by whether it **decreases** validation RMSE. This creates a consistent, objective basis for comparing models:

| If this change reduces RMSE on the validation set | → Keep it |
|---|---|
| If this change increases RMSE | → Reject it |
| If this change has no effect on RMSE | → Consider complexity trade-off |

Without RMSE, "improvement" would be subjective. With it, every decision is data-driven.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| RMSE formula | $\sqrt{\frac{1}{m}\sum_{i=1}^m (g(x_i) - y_i)^2}$ — four steps: difference → square → mean → root |
| Why square | Prevents sign cancellation; penalises large errors quadratically |
| Why root | Restores original units (same scale as target) |
| NumPy implementation | `np.sqrt(((y - y_pred) ** 2).mean())` — three operations |
| Log-price RMSE → price error | $e^\text{RMSE} - 1$ gives approximate percentage error |
| Baseline RMSE ≈ 0.76 | On validation set after Lesson 2.10 correction |

**Next step:** Lesson 2.10 — correct the evaluation pipeline to use validation-set RMSE, introducing the `prepare_x` helper function.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| $g(x_i)$ | Model prediction for observation $i$ (also written $\hat{y}_i$) |
| $y_i$ | True target value for observation $i$ |
| $g(x_i) - y_i$ | Residual (prediction error) for observation $i$ |
| $m$ | Number of observations in the evaluation set |
| MSE | $\frac{1}{m}\sum(g(x_i) - y_i)^2$ — Mean Squared Error |
| RMSE | $\sqrt{\text{MSE}}$ — Root Mean Squared Error |
| `.mean()` | NumPy method: $\sum_i a_i / m$ — avoids manual sum-and-divide |

---

## Graph View Links

**Previous:** [[MLZ_S2_L08_Baseline_Model_For_Car_Price_Prediction]]
**Next:** [[MLZ_S2_L10_Computing_RMSE_on_Validation_Data]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
