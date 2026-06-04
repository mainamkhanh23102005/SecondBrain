---
title: "ML Zoomcamp 2.2 — Data Preparation"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 2
lesson: 2
tags: [machine-learning, pandas, data-preparation, data-cleaning, dtype, string-normalization, column-normalization, data-science, csv, car-price-dataset]
source: "YouTube — ML Zoomcamp Session 2"
date_processed: 2026-05-27
---

# ML Zoomcamp 2.2 — Data Preparation

---

## Executive Summary

Before any machine learning model can be trained, raw data must be made **machine-readable and internally consistent**. This lesson focuses on the very first step of that pipeline: **schema normalization** — a two-layer cleaning process applied to the car price dataset that will be used for linear regression throughout Session 2.

Layer 1 targets the **column names**: they arrive with mixed capitalization and spaces (e.g., `'Engine HP'`, `'MSRP'`), which break dot-notation access and create inconsistency in any programmatic pipeline. Layer 2 targets the **string values inside object-type columns**: inconsistent casing (e.g., `'Sedan'` vs `'sedan'`) creates silent duplicate categories that corrupt one-hot encoding and groupby aggregations downstream.

The deeper insight is that data preparation is not cosmetic. Inconsistent schemas cause real bugs: a column name with a space cannot be accessed via dot notation; a categorical value with wrong case becomes a separate category in every downstream encoding step. Normalization must happen before any EDA, feature engineering, or model training.

---

## Zero-Loss Extraction

### 1. Loading the Dataset

```python
import pandas as pd

df = pd.read_csv('data.csv')
df.head()   # always inspect first 5 rows after loading
```

The car price dataset contains one row per car model with these columns (before cleaning):

| Raw Column Name | Type | Notes |
|---|---|---|
| `Make` | object | Car manufacturer (e.g., BMW) |
| `Model` | object | Model name |
| `Year` | int64 | Model year |
| `Engine HP` | float64 | Horsepower (space in name — dot notation fails) |
| `Engine Cylinders` | float64 | Cylinder count |
| `Transmission Type` | object | MANUAL / AUTOMATIC |
| `Driven_Wheels` | object | all_wheel_drive, front_wheel_drive, etc. |
| `Number of Doors` | float64 | Door count (float because NaN forces float) |
| `Market Category` | object | Luxury, Performance, etc. |
| `Vehicle Size` | object | Compact, Midsize, Large |
| `Vehicle Style` | object | Sedan, Coupe, SUV, etc. |
| `highway MPG` | int64 | Highway fuel economy |
| `city mpg` | int64 | City fuel economy |
| `Popularity` | int64 | Social media popularity score |
| `MSRP` | int64 | **Target variable** — Manufacturer Suggested Retail Price |

**The problems visible immediately:**
- Mixed case: `'Make'` (title), `'MSRP'` (upper), `'highway MPG'` (lower + upper)
- Spaces in names: `'Engine HP'`, `'Transmission Type'`, `'Number of Doors'`
- Spaces inside values: e.g., vehicle styles like `'4dr SUV'`

---

### 2. Column Name Normalization

**Goal:** Make every column name lowercase with underscores instead of spaces.

```python
# Before
df.columns
# Index(['Make', 'Model', 'Year', 'Engine HP', 'Engine Cylinders',
#        'Transmission Type', 'Driven_Wheels', 'Number of Doors',
#        'Market Category', 'Vehicle Size', 'Vehicle Style',
#        'highway MPG', 'city mpg', 'Popularity', 'MSRP'], dtype='object')

# Normalize: lowercase + replace spaces with underscores
df.columns = df.columns.str.lower().str.replace(' ', '_')

# After
df.head()
# make | model | year | engine_hp | engine_cylinders | transmission_type | ...
```

**How it works — step by step:**

| Step | Code | What it does |
|---|---|---|
| 1 | `df.columns` | Returns the `Index` of column names |
| 2 | `.str.lower()` | Applies `.lower()` to every column name via `.str` accessor — returns a new `Index` |
| 3 | `.str.replace(' ', '_')` | Chains another string operation — replaces spaces with underscores |
| 4 | `df.columns = ...` | Writes the cleaned `Index` back to the DataFrame |

---

### 3. Identifying String (Object-Type) Columns

**Why this step is necessary:** Applying `.str.lower()` to a numeric column (e.g., `engine_hp`) would fail or produce meaningless results. We need to find only the object-dtype columns.

```python
# View all column types
df.dtypes
# make                  object
# model                 object
# year                   int64
# engine_hp            float64
# engine_cylinders     float64
# transmission_type     object
# driven_wheels         object
# number_of_doors      float64
# market_category       object
# vehicle_size          object
# vehicle_style         object
# highway_mpg            int64
# city_mpg               int64
# popularity             int64
# msrp                   int64

# Boolean mask: True where dtype is object
df.dtypes == 'object'
# make                  True
# model                 True
# year                 False
# engine_hp            False
# ...

# Extract the names of object columns
strings = list(df.dtypes[df.dtypes == 'object'].index)
# → ['make', 'model', 'transmission_type', 'driven_wheels',
#    'market_category', 'vehicle_size', 'vehicle_style']
```

**Pattern breakdown — `df.dtypes[df.dtypes == 'object'].index`:**

```
df.dtypes                    → Series (index = col names, values = dtypes)
df.dtypes == 'object'        → boolean Series (True for object cols)
df.dtypes[boolean_mask]      → filtered Series (only object-type rows)
.index                       → the labels of that filtered Series = column names
list(...)                    → convert Index to Python list (cleaner display)
```

---

### 4. String Value Normalization

**Goal:** Apply the same lowercase + underscore normalization to the *values* inside every string column.

```python
for col in strings:
    df[col] = df[col].str.lower().str.replace(' ', '_')

# Verify
df.head()
# All string values are now lowercase with underscores:
# 'bmw' not 'BMW', 'rear_wheel_drive' not 'Rear Wheel Drive', etc.
```

**Why reassign back to `df[col]`:** `.str.lower()` returns a **new Series** — it does not modify the column in place. Without the reassignment `df[col] = ...`, the original DataFrame is unchanged.

---

### Full Workflow — The Complete Data Preparation Pipeline

```python
import pandas as pd

# Step 1: Load
df = pd.read_csv('data.csv')

# Step 2: Normalize column names
df.columns = df.columns.str.lower().str.replace(' ', '_')

# Step 3: Identify string columns
strings = list(df.dtypes[df.dtypes == 'object'].index)

# Step 4: Normalize string values
for col in strings:
    df[col] = df[col].str.lower().str.replace(' ', '_')
```

---

### Quick Reference: Operations Used

| Operation | Code | Returns |
|---|---|---|
| Load CSV | `pd.read_csv('file.csv')` | DataFrame |
| All column names | `df.columns` | Index |
| Column types | `df.dtypes` | Series |
| Boolean mask by dtype | `df.dtypes == 'object'` | boolean Series |
| Filter by mask | `df.dtypes[mask]` | filtered Series |
| Column names from Series | `series.index` | Index |
| Apply string op to Index | `df.columns.str.lower()` | Index |
| Apply string op to column | `df['col'].str.lower()` | Series |
| Chain string ops | `.str.lower().str.replace(' ', '_')` | Series / Index |
| Reassign column | `df['col'] = new_series` | (in-place modification) |

---

## Deep-Dive Explanations

### Why Column Name Normalization Is Not Optional

Pandas provides two syntaxes to access a column:

```python
df.make          # dot notation — concise, but requires valid Python identifier
df['make']       # bracket notation — always works
```

A "valid Python identifier" means: no spaces, does not start with a digit, is not a reserved keyword. The raw column `'Engine HP'` violates the first rule — dot notation silently fails or raises a `SyntaxError`:

```python
df.Engine HP     # SyntaxError: invalid syntax
df['Engine HP']  # works, but awkward in loops and pipelines
```

In real ML pipelines, column names are often used programmatically (e.g., `df[col]` in a loop, or passed as strings to functions). A column name with a space introduces fragility: the programmer must always remember to quote it and handle the space. After normalization, every column is accessible both ways, and the mental overhead disappears.

---

### `df.dtypes` — Why Object Means String (in Practice)

NumPy, the array library underpinning Pandas, does not have a native string dtype. Strings are stored as Python `object` references inside an array — hence the dtype name `object`. When Pandas reads a CSV:

- Numeric-looking columns → inferred as `int64` or `float64` (stored as typed C arrays)
- Text-looking columns → stored as `object` (an array of Python string pointers)

**Why `number_of_doors` is `float64` despite being a count:** A column inferred as integer cannot hold `NaN` in older Pandas/NumPy (`int64` has no NaN concept — NaN is a float IEEE value). If any cell is missing, Pandas upgrades the column to `float64`. This is a common source of surprise — an integer column becomes float because of one missing value.

The practical rule: when you load a CSV and see `object` dtype, it is a string column. When you see a numeric type where you expected integers but get floats, there are missing values.

---

### The `df.dtypes[mask].index` Pattern in Depth

This is an idiomatic Pandas pattern for selecting columns by attribute. It exploits the dual nature of `df.dtypes` as a Series: it has both an *index* (column names) and *values* (dtype objects).

```python
# Full expansion of the pattern:
dtype_series = df.dtypes                        # index=col_names, values=dtypes
boolean_mask = dtype_series == 'object'         # True where dtype is 'object'
filtered     = dtype_series[boolean_mask]       # keep only True entries
col_names    = filtered.index                   # the index = the column names
strings      = list(col_names)                  # to plain Python list
```

This is more concise than an explicit loop:

```python
# Equivalent but verbose alternative (avoid this):
strings = [col for col in df.columns if df[col].dtype == object]
```

Both produce the same result. The mask-then-index pattern is preferred in professional Pandas code because it is fully vectorized and reads as a single pipeline.

---

### Why String Value Normalization Prevents Downstream Bugs

Consider what happens in Session 2 when we one-hot encode `vehicle_style`. If the raw data contains both `'Sedan'` and `'sedan'`, Pandas treats them as two distinct categories and creates **two separate binary columns** in the encoded matrix. The model then sees cars of the same type as different, corrupting the feature space.

Similarly, a `groupby('vehicle_style').mean()` would produce two rows for what is logically one group:

```python
# Without normalization:
df.groupby('vehicle_style')['msrp'].mean()
# Sedan    35000.0   ← some rows
# sedan    32000.0   ← other rows (same type, wrong grouping)

# After normalization:
# sedan    33500.0   ← correctly combined
```

The normalization step is cheap (a single loop) and prevents silent correctness bugs that are extremely difficult to debug later in the pipeline.

---

### The `.str` Accessor — Bridging Python Strings to Pandas

Python's built-in string methods (`.lower()`, `.replace()`, `.strip()`) work on individual `str` objects. A Pandas `Series` is an array — applying `.lower()` directly would raise `AttributeError` because `Series` doesn't have that method.

The `.str` accessor is a **namespace** that exposes string methods vectorized over the entire Series:

```python
single_string.lower()          # built-in Python string method
series.str.lower()             # Pandas: applies .lower() to every element
```

The same accessor works on `Index` objects (including `df.columns`), which is why the column name normalization syntax works identically to the value normalization syntax. The accessor handles `NaN` gracefully: `.str.lower()` on a `NaN` value returns `NaN` instead of raising an exception.

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **Data preparation is step 0, not step 2.** Raw CSVs have inconsistent schemas. Normalize before any analysis begins — inconsistency poisons EDA, encoding, and model training.

2. **Column name normalization pattern:**
   ```python
   df.columns = df.columns.str.lower().str.replace(' ', '_')
   ```
   The `.str` accessor works on `Index` objects the same way it works on `Series`.

3. **Identifying object columns:**
   ```python
   strings = list(df.dtypes[df.dtypes == 'object'].index)
   ```
   In CSV-loaded DataFrames, `object` dtype always means string. This pattern is the idiomatic way to extract column names that satisfy a type condition.

4. **String value normalization loop:**
   ```python
   for col in strings:
       df[col] = df[col].str.lower().str.replace(' ', '_')
   ```
   Always reassign — `.str` methods return new Series, they do not modify in place.

5. **Two levels of normalization:** (a) column *names* and (b) string *values*. Both are necessary. Normalizing names fixes programmatic access; normalizing values fixes downstream encoding and grouping correctness.

6. **Why `float64` on integer-looking columns:** A missing value (`NaN`) forces integer columns to `float64`. Always check `dtypes` after loading — a float column where you expect int signals missing data.

### What's Coming Next

- **Lesson 2.3 — Exploratory Data Analysis (EDA):** With a clean schema, the next step is understanding the data — distributions, missing value counts, correlation with the target (`msrp`), and identifying which features are informative for price prediction.
- **Lesson 2.4 — Setting Up the Validation Framework:** Train/validation/test split strategy to avoid data leakage in the car price model.

---

### Related Notes

[[ML_Zoomcamp_1_9]] | [[ML_Zoomcamp_1_8]] | [[ML_Zoomcamp_1_7]] | [[ML_Zoomcamp_1_5]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_1]]

---

## Graph View Links

**Previous:** [[ML_Zoomcamp_1_9]]
**Next:** [[MLZ_S2_L03_Exploratory_Data_Analysis]]
**Hub:** [[Machine Learning (github DataTalksClub)]]
