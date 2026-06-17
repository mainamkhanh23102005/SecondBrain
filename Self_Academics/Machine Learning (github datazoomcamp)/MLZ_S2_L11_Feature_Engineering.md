# ML Zoomcamp — Session 2, Lesson 11: Feature Engineering

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 11 (video transcript). Covers the most impactful single-feature addition in the project: deriving `age` from `year`, the defensive-copy pattern for safe dataframe mutation inside `prepare_x`, and the large RMSE improvement (0.76 → 0.51) that results — demonstrating that domain-informed feature engineering often outperforms algorithmic changes.

---

## 1. Executive Summary

Lesson 2.11 introduces the first act of **feature engineering**: transforming raw data into a more informative representation before it enters the model. The target feature is `year` — the model year of the car — which is one of the most powerful predictors of price. However, using the raw year is suboptimal for a linear model because the year number itself is arbitrary (a car from 2015 is not "2015 units" of anything meaningful). What matters is how **old** the car is relative to when the data was collected.

The transformation is:

$$\text{age}_i = 2017 - \text{year}_i$$

where 2017 is the year the dataset was compiled. This single change drops validation RMSE from **0.76 to 0.51** — a 33% improvement, larger than anything adding more numerical columns could achieve with the baseline set alone.

The lesson also introduces a critical software engineering pattern for data pipelines: **making a defensive copy** of the input DataFrame inside `prepare_x` before adding new columns. This prevents the function from silently mutating the caller's data — a subtle but dangerous bug.

---

## 2. Zero-Loss Extraction

### 2.1 Why `year` Alone Is a Poor Feature

The `year` column contains values like 1990, 2005, 2017. For a linear model, this feature contributes the term $w_\text{year} \cdot \text{year}_i$. The issue is interpretability and scale:

- A car from 2015 vs. 2016 differs by 1 year; a 1990 car vs. 1991 car also differs by 1 year. The model correctly treats these as equal annual differences.
- However, the **magnitude** of the coefficient $w_\text{year}$ is hard to interpret ("price increases by $w_\text{year}$ per year-number unit").
- More importantly: the relationship between `year` and price is that **newer cars are more expensive** — a negative relationship with age. Expressing this as `age` makes the domain logic explicit and can help the model converge better.

$$\text{age}_i = 2017 - \text{year}_i \quad \Longrightarrow \quad \text{price} \downarrow \text{ as age} \uparrow$$

A car with `age = 0` is brand new (2017); `age = 9` was manufactured in 2008.

### 2.2 The Defensive Copy Pattern

Without a copy, `prepare_x` silently modifies the caller's DataFrame:

```python
# BUG — mutates df_train in-place, caller loses original 'age' column state
def prepare_x(df):
    df['age'] = 2017 - df['year']   # adds column to the CALLER'S df
    ...
```

After calling `prepare_x(df_train)`, `df_train` now permanently contains an `age` column. This causes subtle bugs: re-running the cell accumulates columns, downstream code sees an unexpected schema, and the function is no longer a pure transformation (same input → same output).

The fix is to **take a copy at the start of the function**:

```python
def prepare_x(df):
    df = df.copy()   # work on a local copy; original is unchanged
    df['age'] = 2017 - df['year']
    ...
```

After `prepare_x(df_train)` returns, `df_train` is exactly as it was before the call. The `age` column exists only inside the returned `X` matrix.

### 2.3 Updated `prepare_x` Function

```python
base = ['engine_hp', 'engine_cylinders', 'highway_mpg', 'city_mpg', 'popularity']

def prepare_x(df):
    """
    Builds the feature matrix from a raw DataFrame.
    Safely adds derived features without mutating the input.

    Returns:
        X : ndarray, shape (m, 6)  — 5 base features + age
    """
    df = df.copy()                        # defensive copy — original unchanged

    # Derived feature: age of car (data collected in 2017)
    df['age'] = 2017 - df['year']

    # Full feature list: base + engineered
    features = base + ['age']

    df_num = df[features]
    df_num = df_num.fillna(0)
    X = df_num.values                     # shape: (m, 6)
    return X
```

### 2.4 Full Pipeline with Age Feature

```python
# ── TRAINING ───────────────────────────────────────────────────────────────────
X_train = prepare_x(df_train)                       # shape: (m_train, 6)
w0, w   = train_linear_regression(X_train, y_train)

# ── VALIDATION ─────────────────────────────────────────────────────────────────
X_val  = prepare_x(df_val)                          # shape: (m_val, 6)
y_pred = w0 + X_val.dot(w)

score  = rmse(y_val, y_pred)
print(f"Validation RMSE (with age): {score:.4f}")
# Output: ≈ 0.51  (down from 0.76 baseline)
```

### 2.5 RMSE Progression

| Model | Features | Validation RMSE |
|---|---|---|
| Baseline (L08/L10) | 5 numerical columns | ~0.76 |
| + Age (L11) | 5 numerical + `age` | **~0.51** |
| Improvement | — | −0.25 (−33%) |

### 2.6 Visual Improvement

With the `age` feature, the predicted distribution aligns more closely with the target:

```python
import seaborn as sns

y_pred_train = w0 + prepare_x(df_train).dot(w)

sns.histplot(y_pred_train, color='red',  alpha=0.5, bins=50, label='Predictions')
sns.histplot(y_train,      color='blue', alpha=0.5, bins=50, label='Target')
```

The peaks now roughly coincide, though the tails are still imperfect — especially the right tail (very expensive cars), and the left spike from zero-filled rows persists. Categorical features (introduced in Lesson 2.12) will address these gaps.

---

## 3. Deep-Dive Explanations

### 3.1 Stationarity: Why Age Beats Year as a Raw Feature

A model trained on `year` would assign coefficient $w_\text{year}$. If you deploy this model next year (2018), a car manufactured in 2018 would have `year = 2018` — a value the model never saw during training (max was 2017). The year feature is **non-stationary**: its distribution shifts over time.

In contrast, `age = current_year − year` is **relative**. A brand-new car always has `age = 0`, regardless of the calendar year. If you retrain with fresh data and the current year is 2026, new cars still have `age = 0`. The feature's meaning stays fixed.

> **General principle:** Transform absolute timestamps into relative time-since-event features whenever possible. This improves generalization and makes coefficients interpretable.

### 3.2 Linear Model Perspective: What the Age Coefficient Captures

After training, the weight $w_\text{age}$ captures the average **log-price decrease per additional year of age**. If $w_\text{age} = -0.1$, then:

$$\log(\text{price of a 5-year-old car}) = \log(\text{price of new car}) + 5 \times (-0.1) = \log(\text{price of new car}) - 0.5$$

In raw price: a 5-year-old car costs $e^{-0.5} \approx 60\%$ of a new car of the same make and features. This is a directly interpretable business insight extracted automatically by the model.

### 3.3 Why Defensive Copying Is a Hard Requirement in Notebook Workflows

In a Jupyter notebook, cells are not executed in a fixed order. A user might:

1. Run `prepare_x(df_train)` once — `df_train` gains an `age` column.
2. Re-run `prepare_x(df_train)` — the function tries to compute `2017 - df['year']` on the `age` column that now exists (or throws a `KeyError` / produces wrong results).

This class of bug is **non-reproducible** without re-running the entire notebook from scratch. The defensive copy eliminates it entirely: the function is a pure transformation that has no side effects on its inputs.

```python
# Pattern: always copy, then operate on the copy
def prepare_x(df):
    df = df.copy()   # O(m × n) — minor cost; prevents O(debugging_hours) bugs
    ...
```

### 3.4 The `features` List vs. Mutating `base`

The function builds `features = base + ['age']` (creating a new list) rather than `base.append('age')` (mutating the global `base` list). This is for the same reason as the DataFrame copy:

```python
# WRONG — mutates the module-level 'base' list every time prepare_x is called
def prepare_x(df):
    base.append('age')    # after 3 calls, base has 3 'age' entries
    ...

# CORRECT — base stays unchanged; features is a local variable
def prepare_x(df):
    features = base + ['age']   # new list; base unmodified
    ...
```

Mutating shared state inside a function is a common source of hard-to-find bugs in Python ML code.

### 3.5 Why 33% RMSE Improvement From a Single Feature?

The baseline used only five features, all of which capture the car's **physical specifications** (engine, fuel efficiency). These say nothing about how worn out or outdated the car is. `age` directly captures **depreciation** — the single largest driver of car resale value after make/model. Adding it gives the model a fundamentally new signal rather than a marginal refinement of an existing one.

This illustrates a key ML principle: **a domain-informed feature beats raw algorithmic power**. No amount of model complexity on the baseline 5 features would capture depreciation as cleanly as a single well-engineered column.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| `age = 2017 − year` | Transform absolute year into relative age for stationarity and interpretability |
| Defensive copy | Always `df = df.copy()` at the top of feature-engineering functions |
| `features = base + [new]` | Create a new list; never mutate the global `base` list |
| Validation RMSE | Dropped from 0.76 → 0.51 — a 33% improvement from one feature |
| Feature engineering priority | Domain knowledge features often beat model complexity upgrades |
| $w_\text{age}$ interpretation | Log-price decrease per additional year of age — directly interpretable depreciation rate |

**Next step:** Lesson 2.12 — one-hot encode categorical variables (make, engine_fuel_type, transmission_type, driven_wheels, vehicle_style, etc.) to give the model brand-level and spec-level price signals.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| `age` | $2017 - \text{year}$ — years since manufacture |
| `base` | Global list of 5 baseline numerical feature names (never mutated) |
| `features` | Local list inside `prepare_x`: `base + ['age']` — 6 total |
| `df = df.copy()` | Defensive copy — prevents in-place mutation of caller's DataFrame |
| $X \in \mathbb{R}^{m \times 6}$ | Feature matrix after adding age |
| $w_\text{age} < 0$ | Negative weight — older cars are cheaper, captured as log-price decrease per year |
| RMSE $0.76 \to 0.51$ | Validation error after adding age feature |

---

## Graph View Links

**Previous:** [[MLZ_S2_L10_Computing_RMSE_on_Validation_Data]]
**Next:** [[MLZ_S2_L12_Categorical_Variables]]
**Hub:** [[Machine Learning (github datazoomcamp)]]
