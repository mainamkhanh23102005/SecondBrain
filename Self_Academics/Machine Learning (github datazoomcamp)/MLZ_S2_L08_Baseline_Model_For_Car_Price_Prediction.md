# ML Zoomcamp — Session 2, Lesson 8: Baseline Model for Car Price Prediction

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 8 (video transcript). Covers building the first end-to-end baseline: selecting numerical features, handling missing values by zero-filling, training the linear regression model from Lesson 2.7, generating predictions via matrix multiplication, and visually diagnosing model quality — motivating the need for RMSE introduced in Lesson 2.9.

---

## 1. Executive Summary

Lesson 2.8 is the first time every component from the prior lessons converges into a **runnable, end-to-end pipeline**. The goal is deliberately modest: establish a *baseline* — the simplest possible model — so that future improvements can be measured against a known reference point.

The lesson makes three key decisions:

1. **Use only the five numerical columns** of the car dataset: `engine_hp`, `engine_cylinders`, `highway_mpg`, `city_mpg`, and `popularity`. Categorical features (make, model, transmission type, etc.) are deferred to later lessons once encoding strategies are introduced.

2. **Fill all missing values with zero.** Two of the five features (`engine_hp`, `engine_cylinders`) contain `NaN` entries. Zero-filling is the simplest remedy: it is mathematically equivalent to telling the model "ignore this feature for this row," which is acceptable for a baseline even though it is not the most statistically rigorous approach.

3. **Evaluate quality visually first.** By overlaying histograms of predicted values versus actual values, we immediately see that the model's predictions skew lower than the true prices. This motivates a formal, numerical evaluation metric — **RMSE** — to replace subjective visual inspection.

The pipeline built here is the scaffold every subsequent Session 2 lesson will extend.

---

## 2. Zero-Loss Extraction

### 2.1 The Five Numerical Features

The dataset's `dtypes` reveal five numerical (non-object) columns suitable for direct model input without any encoding:

| Feature | Dtype | Meaning | Missing Values? |
|---|---|---|---|
| `engine_hp` | float64 | Engine horsepower | **Yes** |
| `engine_cylinders` | float64 | Number of cylinders | **Yes** |
| `highway_mpg` | int64 | Highway fuel efficiency (MPG) | No |
| `city_mpg` | int64 | City fuel efficiency (MPG) | No |
| `popularity` | int64 | Popularity score / social media mentions | No |

All other columns (`make`, `model`, `year`, `transmission_type`, `vehicle_style`, etc.) are strings or categoricals — they require one-hot encoding or embedding before they can be fed to a linear model.

### 2.2 Building the Feature Matrix

```python
# Define the five baseline numerical features
base = ['engine_hp', 'engine_cylinders', 'highway_mpg', 'city_mpg', 'popularity']

# Extract just these columns from the training split
df_train_base = df_train[base]

# Confirm missing values exist (should show NaN counts for the first two)
df_train_base.isnull().sum()
# engine_hp          69
# engine_cylinders    30
# highway_mpg          0
# city_mpg             0
# popularity           0

# Fill ALL missing values with 0
df_train_base = df_train_base.fillna(0)

# Confirm no remaining NaNs
assert df_train_base.isnull().sum().sum() == 0

# Extract as NumPy array — shape: (m, 5)
X_train = df_train_base.values
```

### 2.3 Training the Model

We reuse `train_linear_regression` from Lesson 2.7. The function internally prepends a ones column for the bias term, computes the Normal Equation, and returns the bias and weight vector separately.

```python
# Reuse the function built in Lesson 2.7
def train_linear_regression(X, y):
    """
    Solves w* = (X^T X)^{-1} X^T y via the Normal Equation.
    Internally augments X with a ones column for the bias term.

    Returns:
        w0 : float   — bias / intercept
        w  : ndarray — feature weights, shape (n,)
    """
    import numpy as np
    ones = np.ones(X.shape[0])
    X_aug = np.column_stack([ones, X])   # shape: (m, n+1)

    XtX     = X_aug.T.dot(X_aug)         # Gram matrix: (n+1, n+1)
    XtX_inv = np.linalg.inv(XtX)
    w_full  = XtX_inv.dot(X_aug.T).dot(y)

    return w_full[0], w_full[1:]         # (bias, feature weights)


# Train on the zero-filled feature matrix
w0, w = train_linear_regression(X_train, y_train)

print(f"Bias  w0 = {w0:.4f}")
print(f"Weights w = {w}")
```

### 2.4 Generating Predictions

After training, we apply the model to the **same training data** to produce in-sample predictions. This is not how we evaluate generalization (that requires the validation set), but it gives an immediate visual sanity check.

```python
# Apply the model: y_hat = w0 + X * w  (matrix form: y_hat = X_aug @ w_full)
y_pred = w0 + X_train.dot(w)   # shape: (m,)
```

The prediction formula expands as:

$$\hat{y}_i = w_0 + w_1 \cdot \text{engine\_hp}_i + w_2 \cdot \text{engine\_cylinders}_i + w_3 \cdot \text{highway\_mpg}_i + w_4 \cdot \text{city\_mpg}_i + w_5 \cdot \text{popularity}_i$$

### 2.5 Visual Evaluation: Distribution Comparison

```python
import seaborn as sns
import matplotlib.pyplot as plt

fig, ax = plt.subplots(figsize=(8, 4))

# Predictions in red (semi-transparent)
sns.histplot(y_pred,   color='red',  alpha=0.5, bins=50, ax=ax, label='Predictions')

# Ground truth in blue (semi-transparent)
sns.histplot(y_train,  color='blue', alpha=0.5, bins=50, ax=ax, label='Actual (y_train)')

ax.set_xlabel('log(price + 1)')
ax.set_ylabel('Count')
ax.legend()
plt.tight_layout()
plt.show()
```

**Result:**

![[MLZ_S2_L08_distribution_comparison.png]]

> **Reading the chart:** The red bars (PRED) cluster around $\log(\text{price}) \approx 9.8$ and spike sharply on the left at $\approx 8$ — an artifact of zero-filled rows whose missing `engine_hp`/`engine_cylinders` pull predictions toward the baseline $w_0$. The blue bars (TARGET) are centred further right at $\approx 10.5$–$11$, matching the actual price distribution. The two peaks do **not** align: the model systematically *underestimates* car prices. This gap is visible but not precisely quantified by a chart alone, which is why **RMSE** is introduced in Lesson 2.9.

### 2.6 Dimensions Reference

| Symbol | Shape | Description |
|---|---|---|
| `df_train_base` | $(m,\; 5)$ | DataFrame with 5 numerical columns |
| $X_\text{train}$ | $(m,\; 5)$ | NumPy feature matrix (zero-filled, no ones column) |
| $y_\text{train}$ | $(m,)$ | Log-transformed prices (from Lesson 2.4 validation framework) |
| $w_0$ | scalar | Bias / intercept returned by `train_linear_regression` |
| $w$ | $(5,)$ | Feature weight vector $[w_1, \ldots, w_5]$ |
| $\hat{y}$ | $(m,)$ | In-sample predictions |

---

## 3. Deep-Dive Explanations

### 3.1 The Mathematics of Zero-Filling: Why It "Ignores" the Feature

When a value is missing, we replace it with $x_{ij} = 0$. Substituting into the linear model:

$$g(x_i) = w_0 + x_{i1} w_1 + \underbrace{0}_{x_{ij}=0} \cdot w_j + \cdots + x_{in} w_n$$

The missing feature's term vanishes:

$$g(x_i) = w_0 + x_{i1} w_1 + \cdots + x_{i,j-1} w_{j-1} + x_{i,j+1} w_{j+1} + \cdots + x_{in} w_n$$

The model behaves as if feature $j$ does not exist for row $i$. The learned weight $w_j$ still contributes to predictions for rows where the feature *is* present — it is only zeroed out on the missing rows. This is the core insight: **zero-filling is not "pretending the feature has value zero"; it is "excluding this feature from this row's prediction."**

### 3.2 Zero-Fill vs. Mean-Fill: Trade-offs

| Property | Fill with $0$ | Fill with $\mu_j$ (column mean) |
|---|---|---|
| Simplicity | Trivial — one line | Requires computing and storing mean |
| Domain validity | Often unrealistic (e.g., zero horsepower) | More realistic — imputes a plausible value |
| Model behaviour | Ignores the feature for missing rows | Contributes a neutral "average" signal |
| Bias introduced | Pulls predictions toward $w_0$ for missing rows | Pulls predictions toward the mean trend |
| When to prefer | Baselines, rapid prototyping | Production models, better calibration |
| Complication | None | Must compute mean on train split only, then apply to val/test to avoid data leakage |

The lesson deliberately chooses zero-filling because it keeps the pipeline simple. The commentary is honest: from domain knowledge, zero cylinders is physically meaningless. But in practice, for this baseline, it works well enough — and "well enough for a baseline" is the explicit goal.

### 3.3 Why We Train on Training Data and Predict on Training Data (for Now)

Applying the model to the same data used to train it gives **in-sample predictions**. This deliberately violates good evaluation practice (you should always evaluate on held-out data) but serves a diagnostic purpose here: if the in-sample distribution doesn't even match the target, the model is clearly underfit and needs improvement *before* worrying about train/val gaps.

The proper evaluation — using the validation set established in Lesson 2.4 — is deferred until after RMSE is introduced, because RMSE gives a single scalar to compare, not just a visual chart.

### 3.4 Interpreting the Distribution Mismatch

When the histogram of predictions peaks to the *left* of the histogram of actuals, it means the model systematically predicts **lower prices** than the true prices. Several causes are possible:

- **Missing features:** The five numerical columns alone are insufficient. Important price signals live in categorical features (make, model, body style) that are not yet included.
- **Zero-filling distortion:** For rows where `engine_hp` or `engine_cylinders` is zero-filled, the prediction is pulled toward $w_0$, potentially underestimating high-powered cars whose horsepower was missing.
- **Log-scale effects:** Since `y_train` is $\log(\text{price} + 1)$, small errors in log-space correspond to large multiplicative errors in actual price. The model may be calibrated on the log scale but visually look worse than it is.

All of these are expected at the baseline stage. The lesson frames this correctly: the chart is not a verdict, it is a *hypothesis* — we need RMSE to confirm it.

### 3.5 The Alpha Parameter: Why Transparency Matters

Using `alpha=0.5` (50% transparency) in `sns.histplot` is not just aesthetic. When two overlapping distributions are plotted opaquely:

- The front distribution completely obscures the back distribution wherever they overlap.
- You cannot see the overlap region, which is exactly the part that tells you how well the distributions match.

With transparency, overlap appears as a **blend of the two colors** (red + blue → purple in RGB space). The size of the purple region is a rough visual proxy for model quality: more purple = better overlap = better model.

### 3.6 Why Visual Inspection Is Insufficient: Motivating RMSE

Visual distribution comparison has several limitations as an evaluation method:

1. **Subjective:** Two engineers looking at the same chart may disagree whether the overlap is "good enough."
2. **Non-comparable across iterations:** If you make 10 changes to the model, you cannot rank them by chart inspection alone.
3. **Insensitive to tail behavior:** Both distributions may have the same peak location but very different tails — the chart may look fine while the model fails badly on expensive/cheap outliers.
4. **Cannot aggregate across cross-validation folds:** You need a scalar metric to average across folds.

**Root Mean Square Error (RMSE)** resolves all four issues:

$$\text{RMSE} = \sqrt{\frac{1}{m} \sum_{i=1}^{m} (\hat{y}_i - y_i)^2}$$

It is a single number, computed identically on any dataset, sensitive to large errors (via squaring), and directly comparable across model versions. Lesson 2.9 derives and implements it.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Baseline features | Use only the 5 dtype-numerical columns as a starting point; add categoricals later |
| Missing values (quick fix) | `.fillna(0)` — makes the model ignore that feature for that row |
| Missing values (better fix) | `.fillna(df_train[col].mean())` — compute mean on train only to avoid leakage |
| Zero-fill math | $x_{ij} = 0 \Rightarrow w_j \cdot x_{ij} = 0$ — feature drops out of that prediction |
| In-sample prediction | Valid for sanity checking; not for evaluation — use the validation set |
| Histogram overlap | Use `alpha < 1.0` so both distributions are visible through each other |
| Distribution mismatch | Predictions peaking left of actuals → model systematically underestimates |
| Limitation of charts | Cannot rank models numerically or aggregate across folds — need RMSE |

**Next step:** Lesson 2.9 — derive and implement RMSE as an objective scalar metric for evaluating linear regression on the car price dataset.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| `base` | Python list of the 5 selected feature column names |
| `df_train_base` | Pandas DataFrame: training rows, 5 numerical columns only |
| $X_\text{train} \in \mathbb{R}^{m \times 5}$ | Feature matrix (zero-filled, no bias column) |
| $y_\text{train} \in \mathbb{R}^m$ | Log-transformed car prices for training rows |
| $w_0 \in \mathbb{R}$ | Bias term (intercept) returned by `train_linear_regression` |
| $w \in \mathbb{R}^5$ | Feature weights $[w_1, w_2, w_3, w_4, w_5]$ |
| $\hat{y} = w_0 + X_\text{train} \cdot w$ | In-sample predictions, shape $(m,)$ |
| `alpha` | Seaborn transparency parameter: $0$ = invisible, $1$ = fully opaque |
| RMSE | $\sqrt{\frac{1}{m}\sum_{i=1}^{m}(\hat{y}_i - y_i)^2}$ — objective regression metric (Lesson 2.9) |

---

## Graph View Links

**Previous:** [[MLZ_S2_L07_Training_Linear_Regression]]
**Next:** [[MLZ_S2_L09_RMSE]]
**Hub:** [[Machine Learning (github datazoomcamp)]]
