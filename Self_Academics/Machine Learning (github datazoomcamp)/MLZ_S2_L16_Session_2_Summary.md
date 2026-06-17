# ML Zoomcamp — Session 2, Lesson 16: Car Price Prediction — Project Summary

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 16 (video transcript). A consolidated retrospective of the complete Session 2 project: the full ML lifecycle from raw data to a deployed linear regression model, key technical decisions, the RMSE progression across lessons, the assembled end-to-end pipeline, and a preview of Session 3.

---

## 1. Executive Summary

Session 2 of ML Zoomcamp is a complete, self-contained supervised learning project. Starting from a raw CSV of car listings, it walks through every step of a real ML workflow — data cleaning, exploratory analysis, feature engineering, model training, evaluation, regularization, hyperparameter tuning, and inference — implementing everything from scratch in NumPy and pandas (no scikit-learn).

The central model is **Ridge Linear Regression** trained via the **regularized Normal Equation**:

$$w^* = (X^\top X + rI)^{-1} X^\top y$$

The final model achieves validation and test RMSE of approximately **0.50** in log-price units, compared to a baseline of 0.76 — a 34% improvement driven primarily by feature engineering (age) and categorical variable encoding.

Session 3 will move to **classification**, using scikit-learn rather than hand-rolled NumPy — the "from scratch" exercise in Session 2 was intentional groundwork for understanding what libraries do under the hood.

---

## 2. The Complete ML Lifecycle — Session 2 in Order

### 2.1 Stage 1: Data Preparation (Lessons 2.1–2.3)

| Task | What Was Done | Why |
|---|---|---|
| Column name cleaning | Lowercased, spaces → underscores | Uniform access syntax; prevents `KeyError` on case mismatches |
| Long-tail detection | `sns.histplot` revealed extreme right skew in price | Linear models assume roughly symmetric, bounded targets |
| Log transformation | `y = log(price + 1)` | Compresses long tail; converts multiplicative price errors to additive |
| Missing value detection | `df.isnull().sum()` | Identified `engine_hp`, `engine_cylinders` as the main NaN sources |

### 2.2 Stage 2: Validation Framework (Lesson 2.4)

```python
# 60 / 20 / 20 stratified split
n          = len(df)
n_val      = int(n * 0.2)
n_test     = int(n * 0.2)
n_train    = n - n_val - n_test

idx        = np.arange(n)
np.random.shuffle(idx)

df_train   = df.iloc[idx[:n_train]].reset_index(drop=True)
df_val     = df.iloc[idx[n_train:n_train+n_val]].reset_index(drop=True)
df_test    = df.iloc[idx[n_train+n_val:]].reset_index(drop=True)

y_train    = np.log1p(df_train['msrp'].values)
y_val      = np.log1p(df_val['msrp'].values)
y_test     = np.log1p(df_test['msrp'].values)
```

**Why three splits?** Train: fit weights. Validation: tune features and hyperparameters. Test: single honest final evaluation.

### 2.3 Stage 3: Linear Regression Theory (Lessons 2.5–2.7)

The model predicts a scalar from a feature vector:

$$g(x_i) = w_0 + \sum_{j=1}^{n} x_{ij} w_j = w_0 + x_i^\top w$$

In matrix form for the full dataset:

$$\hat{y} = Xw \quad \text{where } X \in \mathbb{R}^{m \times (n+1)} \text{ (with bias column)}$$

The **Normal Equation** solves for optimal weights in closed form:

$$w^* = (X^\top X)^{-1} X^\top y$$

```python
def train_linear_regression(X, y):
    ones   = np.ones(X.shape[0])
    X_aug  = np.column_stack([ones, X])
    XtX    = X_aug.T.dot(X_aug)
    w_full = np.linalg.inv(XtX).dot(X_aug.T).dot(y)
    return w_full[0], w_full[1:]
```

### 2.4 Stage 4: Baseline Model (Lessons 2.8–2.10)

5 numerical features → RMSE **≈ 0.76** on validation set.

```python
base = ['engine_hp', 'engine_cylinders', 'highway_mpg', 'city_mpg', 'popularity']

def prepare_x(df):
    df_num = df[base]
    df_num = df_num.fillna(0)
    return df_num.values

def rmse(y, y_pred):
    return np.sqrt(((y - y_pred) ** 2).mean())
```

Key lesson: compute RMSE on the **validation set**, not the training set.

### 2.5 Stage 5: Feature Engineering (Lesson 2.11)

Age of car = 2017 − year → RMSE drops to **≈ 0.51** (33% improvement).

```python
def prepare_x(df):
    df = df.copy()                     # defensive copy
    df['age'] = 2017 - df['year']
    features = base + ['age']
    return df[features].fillna(0).values
```

**Key insight:** domain-informed features outperform algorithmic complexity.

### 2.6 Stage 6: Categorical Variables (Lesson 2.12)

One-hot encoding for `number_of_doors` + 7 categorical columns (top-5 values each):

```python
categories = {c: df_train[c].value_counts().head(5).index.tolist()
              for c in ['make', 'engine_fuel_type', 'transmission_type',
                        'driven_wheels', 'market_category',
                        'vehicle_size', 'vehicle_style']}

def prepare_x(df):
    df = df.copy()
    features = base.copy()
    df['age'] = 2017 - df['year']
    features.append('age')
    for v in [2, 3, 4]:
        col = f'num_doors_{v}'
        df[col] = (df['number_of_doors'] == v).astype(int)
        features.append(col)
    for c, vals in categories.items():
        for v in vals:
            col = f'{c}_{v}'
            df[col] = (df[c] == v).astype(int)
            features.append(col)
    return df[features].fillna(0).values
```

**Without regularization:** RMSE explodes to **~41** — near-singular Gram matrix from dummy variable collinearity.

### 2.7 Stage 7: Regularization (Lesson 2.13)

Add $rI$ to the Gram matrix before inversion:

$$w^* = (X^\top X + rI)^{-1} X^\top y$$

```python
def train_linear_regression_regularized(X, y, r=0.01):
    ones   = np.ones(X.shape[0])
    X_aug  = np.column_stack([ones, X])
    XtX    = X_aug.T.dot(X_aug)
    XtX    = XtX + r * np.eye(XtX.shape[0])   # regularization
    w_full = np.linalg.inv(XtX).dot(X_aug.T).dot(y)
    return w_full[0], w_full[1:]
```

With $r = 0.01$: RMSE recovers to **≈ 0.50**.

### 2.8 Stage 8: Hyperparameter Tuning (Lesson 2.14)

Grid search over $r \in \{0, 0.001, 0.01, 0.1, 1, 10\}$ on validation set → **best $r = 0.01$**.

### 2.9 Stage 9: Final Model and Deployment (Lesson 2.15)

```python
# Train on full data (train + val)
df_full_train = pd.concat([df_train, df_val]).reset_index(drop=True)
y_full_train  = np.concatenate([y_train, y_val])
X_full_train  = prepare_x(df_full_train)
w0, w = train_linear_regression_regularized(X_full_train, y_full_train, r=0.01)

# Evaluate on test set
X_test = prepare_x(df_test)
print(rmse(y_test, w0 + X_test.dot(w)))   # ≈ 0.50 — matches validation

# Inference for a single car
car     = {"make": "toyota", "year": 2015, "engine_hp": 185, ...}
X_car   = prepare_x(pd.DataFrame([car]))
price   = np.exp(w0 + X_car.dot(w)[0])
print(f"${price:,.0f}")
```

---

## 3. RMSE Progression Across the Session

```
0.76  ──  Baseline (5 numerical features, validation set)
0.51  ──  + age feature (Lesson 2.11)          ↓ 33%
41.0  ──  + OHE categoricals, no regularization (Lesson 2.12)  ↑ catastrophic
0.50  ──  + ridge regularization r=0.01 (Lesson 2.13)          ↓ recovered
0.50  ──  Final model on test set (Lesson 2.15)                 ✓ confirms generalization
```

---

## 4. Deep-Dive: Key Conceptual Lessons

### 4.1 The Normal Equation Is Not Magic — It Is Calculus

Finding $w$ that minimizes $\|Xw - y\|^2$ is a convex optimization problem. Setting the gradient to zero yields the Normal Equation in closed form. Machine learning training is not a mysterious search — for linear regression, it is a single algebraic formula.

### 4.2 The Three-Split Discipline Prevents Overfitting to Evaluation Data

Every time you look at a metric and make a model decision based on it, you "spend" some of that dataset's independence. The train/val/test split preserves one completely untouched dataset (test) for the final honest report. Collapsing to two splits (train/test) and using test RMSE to guide decisions leads to inflated reported scores.

### 4.3 Feature Engineering Beats Model Complexity

The biggest single RMSE improvement (0.76 → 0.51) came from one derived feature: `age = 2017 - year`. No change to the model architecture was needed. This is a recurring pattern in applied ML: **the right features matter more than a more sophisticated model**.

### 4.4 Regularization Is an Algebraic Necessity, Not Just a Modeling Choice

For the car dataset, regularization was required not to prevent classical overfitting but to ensure the Gram matrix $X^\top X$ was invertible. This distinction matters: even with infinite training data, the collinearity from OHE would still require regularization. It is a structural property of the feature matrix, not a symptom of insufficient data.

### 4.5 `prepare_x` as a Data Contract

Wrapping all feature construction in a single function and calling it identically on train, val, test, and inference data is the simplest form of a **data contract** — a guarantee that all datasets are processed identically. In production ML systems, this idea scales into feature stores and transformation pipelines.

---

## 5. Key Takeaways — Session 2 Complete Reference

| Concept | Summary |
|---|---|
| Log transform | Applied to price to remove long tail; predictions undone with `np.exp()` |
| Three-split strategy | Train (60%) → fit; Val (20%) → tune; Test (20%) → final honest report |
| Linear regression model | $g(x_i) = w_0 + x_i^\top w$ — weighted sum of features plus bias |
| Normal Equation | $w^* = (X^\top X)^{-1} X^\top y$ — closed-form optimal weights |
| Zero-fill missing values | Sets feature contribution to zero for that row — effectively ignores it |
| `prepare_x(df)` | Defensive copy + all feature engineering in one place → prevents skew |
| RMSE | $\sqrt{\frac{1}{m}\sum(\hat{y}_i - y_i)^2}$ — objective regression metric in target units |
| Feature engineering | `age = 2017 − year` gave the largest single improvement (33% RMSE reduction) |
| One-hot encoding | Binary indicator columns per categorical value — required for linear models |
| Dummy variable trap | Sum of all OHE columns = 1 = bias column → near-singular Gram matrix |
| Ridge regularization | $(X^\top X + rI)^{-1}$ stabilises near-singular matrices; penalises large weights |
| Grid search | Log-spaced $r$ candidates on validation set; pick lowest RMSE |
| Final model | Retrain on train+val with best $r$; evaluate once on test set |
| Inference | `dict → pd.DataFrame([dict]) → prepare_x → dot product → exp` |

---

## 6. What's Next: Session 3 — Classification with Scikit-Learn

Session 3 tackles **classification** (predicting a category rather than a continuous value). The key differences:

| Property | Session 2 (Regression) | Session 3 (Classification) |
|---|---|---|
| Target | Continuous (price) | Categorical (class label) |
| Output | Real number | Probability / class |
| Model | Linear Regression | Logistic Regression |
| Loss | MSE / RMSE | Log-loss / AUC |
| Implementation | Hand-rolled NumPy | scikit-learn |

Having implemented linear regression from scratch (Normal Equation in NumPy), Session 3 can now use `sklearn.linear_model.LogisticRegression` with full understanding of what the library is doing internally.

---

## Appendix: Full Session 2 Code — Assembled Pipeline

```python
import numpy as np
import pandas as pd

# ── Data prep ─────────────────────────────────────────────────────────────────
df = pd.read_csv('car_price.csv')
df.columns = df.columns.str.lower().str.replace(' ', '_')
df['msrp'] = df['msrp'].clip(upper=200_000)     # remove extreme outliers

# ── Train / val / test split ──────────────────────────────────────────────────
np.random.seed(42)
idx = np.arange(len(df))
np.random.shuffle(idx)
n = len(df)
df_train = df.iloc[idx[:int(n*0.6)]].reset_index(drop=True)
df_val   = df.iloc[idx[int(n*0.6):int(n*0.8)]].reset_index(drop=True)
df_test  = df.iloc[idx[int(n*0.8):]].reset_index(drop=True)
y_train, y_val, y_test = [np.log1p(d['msrp'].values) for d in (df_train, df_val, df_test)]

# ── Feature config ────────────────────────────────────────────────────────────
base = ['engine_hp', 'engine_cylinders', 'highway_mpg', 'city_mpg', 'popularity']
cat_cols = ['make', 'engine_fuel_type', 'transmission_type',
            'driven_wheels', 'market_category', 'vehicle_size', 'vehicle_style']
categories = {c: df_train[c].value_counts().head(5).index.tolist() for c in cat_cols}

def prepare_x(df):
    df = df.copy()
    features = base.copy()
    df['age'] = 2017 - df['year']
    features.append('age')
    for v in [2, 3, 4]:
        col = f'num_doors_{v}'
        df[col] = (df['number_of_doors'] == v).astype(int)
        features.append(col)
    for c, vals in categories.items():
        for v in vals:
            col = f'{c}_{v}'
            df[col] = (df[c] == v).astype(int)
            features.append(col)
    return df[features].fillna(0).values

# ── Model functions ───────────────────────────────────────────────────────────
def train_linear_regression_regularized(X, y, r=0.01):
    ones   = np.ones(X.shape[0])
    X_aug  = np.column_stack([ones, X])
    XtX    = X_aug.T.dot(X_aug) + r * np.eye(X_aug.shape[1])
    w_full = np.linalg.inv(XtX).dot(X_aug.T).dot(y)
    return w_full[0], w_full[1:]

def rmse(y, y_pred):
    return np.sqrt(((y - y_pred) ** 2).mean())

# ── Development loop (train → validate) ──────────────────────────────────────
X_train, X_val = prepare_x(df_train), prepare_x(df_val)
w0, w = train_linear_regression_regularized(X_train, y_train, r=0.01)
print(f"Val RMSE: {rmse(y_val, w0 + X_val.dot(w)):.4f}")

# ── Final model (train + val → test) ─────────────────────────────────────────
df_ft = pd.concat([df_train, df_val]).reset_index(drop=True)
y_ft  = np.concatenate([y_train, y_val])
w0, w = train_linear_regression_regularized(prepare_x(df_ft), y_ft, r=0.01)
print(f"Test RMSE: {rmse(y_test, w0 + prepare_x(df_test).dot(w)):.4f}")

# ── Single-car inference ──────────────────────────────────────────────────────
car = df_test.iloc[0].to_dict()
price = np.exp(w0 + prepare_x(pd.DataFrame([car])).dot(w)[0])
print(f"Predicted: ${price:,.0f}")
```

---

## Graph View Links

**Previous:** [[MLZ_S2_L15_Using_the_Model]]
**Next:** [[Machine Learning (github datazoomcamp)]]
**Hub:** [[Machine Learning (github datazoomcamp)]]
