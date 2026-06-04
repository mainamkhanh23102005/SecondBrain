# ML Zoomcamp — Session 2, Lesson 3: Exploratory Data Analysis

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 3 (video transcript). Covers EDA methodology on the car price prediction dataset, with emphasis on distribution analysis and log transformation of the target variable.

---

## 1. Executive Summary

Before training any model, you must **understand your data**. This lesson establishes a systematic EDA workflow for the car price prediction problem: column-by-column inspection, distribution visualization, long-tail diagnosis, and missing value auditing. The single most important insight is that **long-tail target distributions actively harm model performance** — the fix is a logarithmic transformation that reshapes MSRP into an approximately normal distribution, which is far friendlier to regression models.

---

## 2. Zero-Loss Extraction

### 2.1 Dataset Column Overview

| Column | Type | Semantics | # Unique Values (approx.) |
|---|---|---|---|
| `make` | Categorical | Car manufacturer (BMW, Audi, Mercedes…) | 48 |
| `model` | Categorical | Specific model name | Many (more granular than make) |
| `year` | Numerical | Model year | 28 |
| `engine_fuel_type` | Categorical | Fuel type (diesel, gas, electric…) | 10 |
| `engine_hp` | Numerical | Engine horsepower | — |
| `engine_cylinders` | Numerical | Number of cylinders | — |
| `transmission_type` | Categorical | Automatic, manual, etc. | — |
| `driven_wheels` | Categorical | FWD, RWD, AWD, 4WD | — |
| `number_of_doors` | Numerical | 2 or 4 (has missing values) | — |
| `market_category` | Categorical | Luxury, performance, etc. (many missing) | — |
| `vehicle_size` | Categorical | Compact, midsize, large | — |
| `vehicle_style` | Categorical | Sedan, SUV, coupe… | — |
| `highway_mpg` | Numerical | Miles per gallon on highway | — |
| `city_mpg` | Numerical | Miles per gallon in city | — |
| `popularity` | Numerical | Twitter mention count (proxy for demand) | — |
| `msrp` | Numerical | **Target variable** — manufacturer's suggested retail price | — |

### 2.2 EDA Code Skeleton

```python
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Display plots inline in Jupyter
%matplotlib inline

df = pd.read_csv('data.csv')

# --- Column inspection loop ---
for col in df.columns:
    print(col)
    print(df[col].unique()[:5])   # First 5 unique values
    print(f"nunique: {df[col].nunique()}")
    print()

# --- Target variable distribution ---
sns.histplot(df['msrp'], bins=50)
plt.show()

# Zoom in to prices ≤ 100,000
sns.histplot(df[df['msrp'] < 100_000]['msrp'], bins=50)
plt.show()

# --- Log transformation ---
log_price = np.log1p(df['msrp'])
sns.histplot(log_price, bins=50)
plt.show()

# --- Missing values audit ---
df.isnull().sum()
```

### 2.3 Missing Values Summary (known)

| Column | Has Missing Values |
|---|---|
| `engine_fuel_type` | Yes |
| `market_category` | Yes |
| `engine_hp` | Yes |
| `engine_cylinders` | Yes |
| `number_of_doors` | Yes |

---

## 3. Deep-Dive Explanations

### 3.1 Why Inspect Unique Values Instead of `.head()`?

`.head()` shows only the first five rows. If the data is sorted (e.g., all BMWs first), `.head()` gives a misleading picture. `.unique()[:5]` combined with `.nunique()` immediately answers:
- **Is this categorical or continuous?** (e.g., `nunique=48` → categorical; `nunique=11,914` → effectively continuous)
- **What's the cardinality?** High-cardinality categoricals (like `model`) need different encoding strategies than low-cardinality ones (like `transmission_type`).

### 3.2 Long-Tail Distribution — Why It Hurts Models

The raw MSRP distribution is **right-skewed (long-tail)**:

```
Frequency
  ▓▓▓▓▓▓▓▓
  ▓▓▓▓▓▓▓▓▓▓
  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓
  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░.......
  $0       $50k     $500k   $2M
```

- The vast majority of cars are in the $10k–$50k range.
- A tiny number of ultra-luxury/exotic cars cost $500k–$2M.
- These outlier values **dominate the loss function** (MSE is quadratic — a $1M error has $10^6$ times more weight than a $1k error).
- The model wastes capacity trying to fit these rare, extreme values instead of learning the common pattern.

### 3.3 Log Transformation — The Mechanism

The fix is to model $\log(1 + \text{price})$ instead of raw price. Why does this work?

$$y_{\text{log}} = \ln(1 + \text{price})$$

The logarithm has **diminishing returns**: the gap between $\ln(10{,}000)$ and $\ln(100{,}000)$ is far smaller than the gap between those raw values. Concretely:

| Price | $\ln(1 + \text{price})$ |
|---|---|
| \$1,000 | 6.91 |
| \$25,000 | 10.13 |
| \$100,000 | 11.51 |
| \$2,000,000 | 14.51 |

The $2M car is now only ~2.1x the log-value of a $25k car, not 80x. The tail **collapses** into the distribution's right edge.

**Why `np.log1p` instead of `np.log`?**

$\log(0)$ is undefined (negative infinity). Adding 1 shifts the domain: $\log_1\!p(x) = \ln(1 + x)$. This means:
- If price = 0 → $\ln(1) = 0$ ✓ (safe)
- In this dataset, minimum price is ~$1000, so the `+1` is numerically negligible, but it's a **defensive programming habit** — always use `log1p` on non-negative targets.

### 3.4 The Resulting Distribution

After transformation, the MSRP histogram approximates a **normal (Gaussian) distribution**:

$$f(x) = \frac{1}{\sigma\sqrt{2\pi}} e^{-\frac{1}{2}\left(\frac{x-\mu}{\sigma}\right)^2}$$

This is ideal for regression because:
1. **Linear regression** assumes Gaussian-distributed residuals (not the target directly, but approximately related).
2. **MSE loss** is well-behaved: no single outlier can dominate training.
3. The **variance** is now more homogeneous across the value range (homoscedasticity).

There remains a spike at $\ln(1001) \approx 6.91$, corresponding to the platform's minimum listing price of $1000. This is a data artifact, not a real distribution feature — it should be noted but doesn't require removal at this stage.

### 3.5 Missing Values — Why Note Them Now?

Missing values don't block EDA, but they **will** block model training. Algorithms like linear regression cannot accept `NaN` inputs. By cataloguing missing values during EDA, you know which imputation strategy to apply later:
- **Numerical columns** (`engine_hp`, `engine_cylinders`): fill with 0, mean, or median.
- **Categorical columns** (`engine_fuel_type`, `market_category`): fill with `"unknown"` or drop.

---

## 4. Key Takeaways & Next Steps

| Insight | Action |
|---|---|
| Long-tail MSRP distribution | Apply `np.log1p` to target before training; invert with `np.expm1` at prediction time |
| Data has sorting bias (all BMWs first) | **Shuffle** before splitting (covered in Lesson 2.4) |
| Multiple columns have missing values | Plan imputation strategy before model training |
| `popularity` = Twitter mentions | Treat as proxy feature — may or may not be predictive |

**Next step:** Set up the train/validation/test split framework (Lesson 2.4) so models can be properly evaluated.

---

## Graph View Links

**Previous:** [[ML_Zoomcamp_2_2]]
**Next:** [[MLZ_S2_L04_Validation_Framework]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
