# ML Zoomcamp — Session 2, Lesson 12: Categorical Variables

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 12 (video transcript). Covers one-hot encoding (OHE) of categorical variables — the mechanics of binary column creation, the `number_of_doors` case study (a pseudo-numerical categorical), building a `categories` dictionary with top-5 values per column, and integrating all categoricals into `prepare_x` via nested loops — concluding with an RMSE explosion that motivates regularization in Lesson 2.13.

---

## 1. Executive Summary

Up to Lesson 2.11, the model only sees numerical features. Categorical features — `make`, `model`, `engine_fuel_type`, `transmission_type`, `driven_wheels`, `market_category`, `vehicle_size`, `vehicle_style` — carry rich price signals (a BMW costs more than a Kia of similar age and specs) but cannot be fed directly to a linear model as strings.

The standard solution is **one-hot encoding (OHE)**: for each unique value of a categorical column, create a new binary column that is 1 when the row has that value and 0 otherwise. This transforms a single string column with $k$ unique values into $k$ binary columns, all of which are valid numerical inputs.

The lesson also exposes a subtle trap: `number_of_doors` *looks* numerical (it holds values 2, 3, 4) but is actually categorical — the difference between 2-door and 4-door is not an additive quantity, it is a category membership. It is therefore one-hot encoded, not used as a raw integer.

Adding all categorical features without regularization causes a catastrophic RMSE spike (from ~0.51 to ~41), because near-duplicate encoded columns make the Gram matrix nearly singular. This sets up the regularization solution in Lesson 2.13.

---

## 2. Zero-Loss Extraction

### 2.1 Categorical vs. Numerical Features

| Feature Type | Examples | Pandas dtype | Can feed to linear model directly? |
|---|---|---|---|
| Numerical | `engine_hp`, `highway_mpg`, `age` | `int64`, `float64` | Yes |
| Categorical (string) | `make`, `engine_fuel_type`, `transmission_type` | `object` | No — must encode |
| Pseudo-numerical categorical | `number_of_doors` (values: 2, 3, 4) | `int64` or `float64` | **No** — should encode |

**Why is `number_of_doors` categorical despite being a number?**
Cars come in distinct door configurations: 2-door coupes, 3-door hatchbacks, 4-door sedans. These are discrete categories, not points on a continuous scale. Treating `number_of_doors` as numerical would tell the model that a 4-door car is "twice as door-ful" as a 2-door car — a meaningless arithmetic statement. The correct interpretation is: a 4-door car belongs to the "4-door" category, which is orthogonal to the others.

### 2.2 One-Hot Encoding: Mechanics

For a column with values $\{v_1, v_2, v_3\}$, OHE creates three binary columns:

| `number_of_doors` | `num_doors_2` | `num_doors_3` | `num_doors_4` |
|---|---|---|---|
| 2 | 1 | 0 | 0 |
| 4 | 0 | 0 | 1 |
| 3 | 0 | 1 | 0 |
| 2 | 1 | 0 | 0 |

Each row has exactly one 1 and all others 0. The linear model then learns a separate weight for each category, effectively computing a per-category baseline offset.

**Pandas implementation for a single value:**

```python
# Boolean mask → integer (True → 1, False → 0)
df_train['num_doors_4'] = (df_train['number_of_doors'] == 4).astype(int)
```

**Loop for all values:**

```python
for v in [2, 3, 4]:
    df_train[f'num_doors_{v}'] = (df_train['number_of_doors'] == v).astype(int)
```

### 2.3 Selecting Top-5 Categories per Column

For high-cardinality columns like `make` (50+ unique values), encoding every value would create too many features. A practical heuristic is to encode only the **top-5 most frequent values** — covering the majority of rows while keeping the feature count manageable.

```python
# Inspect top values for 'make'
df_train['make'].value_counts().head(5)
# Chevrolet    1120
# Ford          900
# Volkswagen    700
# Toyota        650
# Dodge         580
# Name: make, dtype: int64

# Extract the index (the make names) as a Python list
top_makes = df_train['make'].value_counts().head(5).index.tolist()
# ['Chevrolet', 'Ford', 'Volkswagen', 'Toyota', 'Dodge']
```

Rows whose `make` does not appear in the top 5 will have all 5 make-indicator columns set to 0 — the model treats them as "other."

### 2.4 Building the `categories` Dictionary

All categorical columns are processed uniformly. We define a dict mapping column name → list of top-5 values:

```python
cat_cols = [
    'make', 'engine_fuel_type', 'transmission_type',
    'driven_wheels', 'market_category', 'vehicle_size', 'vehicle_style'
]

# Compute once on train set only (no leakage)
categories = {}
for c in cat_cols:
    categories[c] = df_train[c].value_counts().head(5).index.tolist()

# categories = {
#   'make':              ['Chevrolet', 'Ford', 'Volkswagen', 'Toyota', 'Dodge'],
#   'engine_fuel_type':  ['regular unleaded', 'premium unleaded (required)', ...],
#   'transmission_type': ['AUTOMATIC', 'MANUAL', ...],
#   ...
# }
```

> **Data leakage warning:** `categories` is computed on `df_train` only. When calling `prepare_x(df_val)` or `prepare_x(df_test)`, the same `categories` dict is used — we do **not** recompute it on val/test data.

### 2.5 Updated `prepare_x` with Full Categorical Encoding

```python
base = ['engine_hp', 'engine_cylinders', 'highway_mpg', 'city_mpg', 'popularity']

def prepare_x(df):
    """
    Builds feature matrix including:
      - 5 base numerical features
      - age (engineered from year)
      - number_of_doors OHE (3 binary columns)
      - 7 categorical columns × 5 top values = 35 binary columns
    Total: 5 + 1 + 3 + 35 = 44 features
    """
    df = df.copy()                        # defensive copy
    features = base.copy()               # start with baseline features (new list)

    # ── Age feature ────────────────────────────────────────────────────────────
    df['age'] = 2017 - df['year']
    features.append('age')

    # ── number_of_doors OHE ────────────────────────────────────────────────────
    for v in [2, 3, 4]:
        col = f'num_doors_{v}'
        df[col] = (df['number_of_doors'] == v).astype(int)
        features.append(col)

    # ── Categorical variable OHE ───────────────────────────────────────────────
    for c, values in categories.items():
        for v in values:
            col = f'{c}_{v}'
            df[col] = (df[c] == v).astype(int)
            features.append(col)

    # ── Extract feature matrix ─────────────────────────────────────────────────
    df_num = df[features].fillna(0)
    X = df_num.values                    # shape: (m, 44)
    return X
```

### 2.6 Training and Evaluation

```python
X_train = prepare_x(df_train)
w0, w   = train_linear_regression(X_train, y_train)

X_val  = prepare_x(df_val)
y_pred = w0 + X_val.dot(w)

print(rmse(y_val, y_pred))
# Output: ~41  ← catastrophic failure — something went wrong
```

Examining the weights reveals the problem:

```python
print(w)
# [ 2.3e+12  -4.1e+13   8.7e+11  ...  -9.2e+14 ]  ← enormous values
```

The model has learned astronomically large weights. RMSE is ~41 (recall the target is log-price with values 8–15; an RMSE of 41 means predictions are completely wrong).

### 2.7 Feature Count Reference

| Feature Group | Count | Notes |
|---|---|---|
| Base numerical | 5 | engine_hp, engine_cylinders, highway_mpg, city_mpg, popularity |
| Age | 1 | 2017 − year |
| number_of_doors OHE | 3 | 2-door, 3-door, 4-door |
| make OHE | 5 | Top-5 makes |
| engine_fuel_type OHE | 5 | Top-5 fuel types |
| transmission_type OHE | 5 | Top-5 transmission types |
| driven_wheels OHE | 5 | Top-5 drive configs |
| market_category OHE | 5 | Top-5 market categories |
| vehicle_size OHE | 5 | Top-5 sizes |
| vehicle_style OHE | 5 | Top-5 styles |
| **Total** | **44** | |

---

## 3. Deep-Dive Explanations

### 3.1 Why OHE and Not Ordinal Encoding?

An alternative to OHE is **ordinal encoding**: assign integers to categories (Chevrolet=0, Ford=1, Volkswagen=2, ...). This is wrong for nominal categories because it imposes a false ordering and magnitude:

- The model would infer Ford (1) is "halfway between" Chevrolet (0) and Volkswagen (2).
- It would infer a Dodge (4) costs "4 times as much per unit of make-ness" as a Chevrolet (0).

OHE makes no such assumptions — each category gets its own independent binary feature and weight.

### 3.2 The Dummy Variable Trap: Why RMSE Explodes

When you OHE all three door values (2, 3, 4), you create three binary columns. For every row, exactly one of these is 1 — so their sum is always 1:

$$\text{num\_doors\_2}_i + \text{num\_doors\_3}_i + \text{num\_doors\_4}_i = 1 \quad \forall i$$

The sum of these three columns equals the **bias column** (the column of all ones added inside `train_linear_regression`). This is **perfect multicollinearity**: one column is an exact linear combination of the others. The Gram matrix $X^\top X$ becomes singular (not invertible), and NumPy returns a "pseudo-inverse" with astronomically large values.

With 7 categorical columns each fully one-hot encoded plus `number_of_doors`, and the interaction between all those binary columns and the bias term, the feature matrix is riddled with near-linear-dependence. The result is:

$$\text{weights} \to \text{enormous values} \quad \Rightarrow \quad \text{RMSE} \to 41$$

### 3.3 The Standard Remedy: Drop One Category (and Why We Don't)

The classical fix for the dummy variable trap is to drop one OHE column per categorical variable (e.g., use only 2-door and 3-door — 4-door is implied when both are 0). This is called using **$k-1$ dummies** for a $k$-category variable.

This lesson takes the alternative approach: keep all $k$ columns but add **regularization** (Lesson 2.13). Regularization prevents the Gram matrix from exploding even when near-singular, and it works automatically without needing to manually track which category to drop.

### 3.4 Why Top-5 and Not All Values?

For `make` with 50+ unique values, encoding all of them would add 50+ sparse binary columns. Most categories appear in very few rows, so the model can't reliably learn their coefficients — these rare categories contribute noise, not signal.

Top-5 by frequency covers the majority of the dataset while keeping the feature space manageable. Rare makes get the "other" treatment (all zeros), which is a reasonable default.

### 3.5 Why the `categories` Dict Must Be Built on Train Data

The categories dict tells `prepare_x` which values to one-hot encode. If it were recomputed on the validation set, it might include different top-5 values — making the feature matrix for val and train structurally inconsistent. Worse, it would mean the validation set influenced feature engineering decisions, introducing leakage.

**Rule:** Compute all data-dependent parameters (top values, means, standard deviations) on the **training set only**, then apply those same parameters to val and test sets.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Categorical ≠ object dtype | `number_of_doors` is categorical despite having numeric values |
| OHE mechanics | `(df[col] == val).astype(int)` creates a binary indicator column |
| Top-5 heuristic | Encode only the most frequent values; rare values become "other" (all zeros) |
| `categories` dict | Built on train set once; reused for val/test — prevents leakage |
| Defensive copy + `features.copy()` | Both the DataFrame and the features list must be local copies |
| RMSE explosion (~41) | Caused by near-perfect multicollinearity from full OHE + bias column |
| Fix | Regularization (Lesson 2.13) — add $rI$ to the Gram matrix |

**Next step:** Lesson 2.13 — Regularization: add $r \cdot I$ to the Gram matrix to stabilize the Normal Equation in the presence of near-singular feature matrices.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| OHE | One-Hot Encoding — $k$ categories → $k$ binary columns |
| `categories` | Dict: `{col_name: [top_5_values]}` — computed on train set only |
| `(df[c] == v).astype(int)` | Creates binary indicator: 1 if row has value $v$, else 0 |
| $X \in \mathbb{R}^{m \times 44}$ | Feature matrix after full OHE (5 base + 1 age + 3 doors + 35 cat) |
| Dummy variable trap | Sum of all OHE columns for one variable = 1 = bias column → singular Gram matrix |
| RMSE ≈ 41 | Catastrophic failure from near-singular Gram matrix without regularization |

---

## Graph View Links

**Previous:** [[MLZ_S2_L11_Feature_Engineering]]
**Next:** [[MLZ_S2_L13_Regularization]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
