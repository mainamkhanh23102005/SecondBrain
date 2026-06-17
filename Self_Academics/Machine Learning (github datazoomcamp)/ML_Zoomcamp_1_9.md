---
title: "ML Zoomcamp 1.9 — Introduction to Pandas"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 1
lesson: 9
tags: [machine-learning, pandas, python, dataframe, series, tabular-data, data-wrangling, data-science, groupby, filtering, string-operations]
source: "YouTube — ML Zoomcamp Session 1"
date_processed: 2026-05-22
---

# ML Zoomcamp 1.9 — Introduction to Pandas

---

## Executive Summary

Pandas is the **primary library for tabular data manipulation in Python** and the gateway between raw data files and the NumPy arrays that ML models consume. Its central abstraction is the **DataFrame** — a table with named columns and a labeled row index — where every column is a **Series**: a one-dimensional array augmented with an index and a name.

This lesson covers the full practical workflow: creating DataFrames from different Python structures, accessing and modifying columns and rows, applying element-wise and string operations to entire Series, filtering rows with boolean conditions, summarizing data with statistics and group aggregations, and converting back to Python-native formats. The deeper insight is that Pandas is a **thin, labeled layer on top of NumPy**: all the element-wise vectorization from lesson 1.7 applies here, but now each array carries column names, row indices, and missing-value awareness — the metadata that makes working with real-world data tractable. This dataset (car prices) is the one used for linear regression starting in Session 2.

---

## Zero-Loss Extraction

### 1. Importing Pandas

```python
import pandas as pd   # 'pd' is the universal convention, just as 'np' is for NumPy
```

---

### 2. Creating a DataFrame

A **DataFrame** is a table. There are two primary construction patterns:

**Pattern A — List of lists + explicit column names:**

```python
data = [
    ['Nissan',   'Stanza',  1991, 138,  4, 'MANUAL',    'sedan',   2000],
    ['Hyundai',  'Sonata',  2017, None, 4, 'AUTOMATIC', 'Sedan',   27150],
    ['Lotus',    'Elise',   2010, 218,  4, 'MANUAL',    'Coupe',   54990],
    ['GMC',      'Acadia',  2017, 194,  4, 'AUTOMATIC', '4dr SUV', 34450],
    ['Nissan',   'Frontier',2017, 261,  6, 'MANUAL',    'Pickup',  32340],
]

columns = [
    'make', 'model', 'year', 'engine_hp', 'engine_cylinders',
    'transmission_type', 'vehicle_style', 'msrp'
]

df = pd.DataFrame(data, columns=columns)
```

Without `columns=`, Pandas labels columns `0, 1, 2, ...` — it has no way to infer meaning.

**Pattern B — List of dictionaries (keys become column names automatically):**

```python
data = [
    {'make': 'Nissan',  'model': 'Stanza',   'year': 1991, 'msrp': 2000},
    {'make': 'Hyundai', 'model': 'Sonata',   'year': 2017, 'msrp': 27150},
    # ...
]

df = pd.DataFrame(data)   # column names inferred from dictionary keys
```

| Construction | When to use |
|---|---|
| List of lists + `columns=` | Data in a flat table format (e.g., loaded from CSV rows) |
| List of dicts | Data already keyed by field name (e.g., JSON/API responses) |

---

### 3. Exploring a DataFrame

```python
df.head()      # first 5 rows (default)
df.head(2)     # first n rows — first thing to call after loading data
```

`head()` is the standard "sanity check" after loading: it confirms the schema, column types, and sample values before any processing.

---

### 4. Accessing Columns (Series)

Every column in a DataFrame is a **pandas Series** — a 1D labeled array.

```python
# Dot notation — concise, but only works when name is a valid Python identifier
df.make                         # → Series of make values

# Bracket notation — always works, required when name has spaces or special chars
df['make']                      # → same Series
df['engine hp']                 # → bracket notation required (space in name)

# Select multiple columns → returns a new DataFrame (double brackets)
df[['make', 'model', 'msrp']]   # → 3-column DataFrame
```

> The double-bracket pattern `df[[list]]` is often confused with single-bracket `df[col]`. Remember: single bracket → Series; double brackets (list inside) → DataFrame.

---

### 5. Adding, Replacing, and Deleting Columns

```python
# Add a new column
df['id'] = [1, 2, 3, 4, 5]

# Replace an existing column (same syntax as adding)
df['id'] = [10, 20, 30, 40, 50]

# Delete a column
del df['id']
```

The bracket-assignment and `del` patterns mirror Python dictionary semantics — DataFrames behave like ordered dictionaries of Series, keyed by column name.

---

### 6. The Index: `.loc` vs `.iloc`

Every DataFrame has a **row index** — a label for each row. By default it is a `RangeIndex` (0, 1, 2, ..., n-1).

```python
df.index   # → RangeIndex(start=0, stop=5, step=1)
```

**Label-based access — `.loc`:** Uses the index *label*:

```python
df.loc[1]          # → row with index label 1 (a Series of that row)
df.loc[[1, 3]]     # → rows with labels 1 and 3 (a DataFrame)
```

**Positional access — `.iloc`:** Uses the integer *position*, regardless of index:

```python
df.iloc[1]         # → second row (position 1), even if label is different
df.iloc[[1, 3]]    # → rows at positions 1 and 3
```

**When the index is non-default** (e.g., set to `['a', 'b', 'c', 'd', 'e']`):

```python
df.index = ['a', 'b', 'c', 'd', 'e']

df.loc[1]          # ❌ KeyError — label 1 no longer exists
df.loc['b']        # ✓ row with label 'b'
df.iloc[1]         # ✓ still works — position 1 is always the second row
```

**Resetting the index:**

```python
df = df.reset_index(drop=True)   # drop=True discards old index; reassign to apply in-place
```

> `reset_index()` returns a **new** DataFrame — it does not modify `df` in place. Without reassigning (`df = df.reset_index(...)`), the original DataFrame is unchanged.

---

### 7. Element-wise Operations on Series

Pandas Series support all NumPy-style vectorized operations:

```python
df['engine_hp'] / 100        # divide every element by 100; NaN stays NaN
df['engine_hp'] * 2          # multiply every element by 2
df['year'] > 2015            # → boolean Series: [False, True, True, True, True]
df['make'] == 'Nissan'       # → boolean Series: [True, False, False, False, True]
```

This works because Pandas uses NumPy arrays under the hood. Operations broadcast to every element without a loop.

---

### 8. Filtering Rows

The standard filter pattern mirrors NumPy boolean indexing:

```python
# Filter: single condition
df[df['year'] > 2015]                        # rows where year > 2015

# Filter: string match
df[df['make'] == 'Nissan']                   # rows where make is Nissan

# Filter: combined conditions — use & (bitwise AND), not Python's 'and'
df[(df['make'] == 'Nissan') & (df['year'] > 2015)]
```

The result is a **new DataFrame** containing only the matching rows. The original `df` is unchanged.

> **Critical pitfall:** Use `&` (bitwise AND) and `|` (bitwise OR) for combining Pandas boolean arrays, **never** Python's `and` / `or`. Python's logical operators evaluate whole Series as a single boolean, raising a `ValueError`. The `&` operator applies element-wise.

---

### 9. String Operations via `.str`

Pandas cannot directly apply Python string methods (`.lower()`, `.replace()`, etc.) to an entire Series — those methods live on individual `str` objects. The `.str` accessor bridges the gap:

```python
# Lowercase all values in a column
df['vehicle_style'].str.lower()

# Replace spaces with underscores
df['vehicle_style'].str.replace(' ', '_')

# Chain operations: first lowercase, then replace spaces
df['vehicle_style'].str.lower().str.replace(' ', '_')
```

Each call returns a **new Series** — it does not modify the column in place. To apply the transformation permanently:

```python
df['vehicle_style'] = df['vehicle_style'].str.lower().str.replace(' ', '_')
```

This pattern — transform → reassign — is the standard string-cleaning workflow for text columns.

---

### 10. Summarizing Operations

**Numeric aggregations (on a Series):**

```python
df['msrp'].min()     # minimum value
df['msrp'].max()     # maximum value
df['msrp'].mean()    # arithmetic mean
```

**`describe()` — full summary statistics:**

```python
df['msrp'].describe()
# count      5.000000
# mean   24186.000000
# std    19768.XXX
# min     2000.000000
# 25%    27150.000000
# 50%    32340.000000
# 75%    34450.000000
# max    54990.000000

df.describe()          # applies describe() to ALL numeric columns simultaneously
df.describe().round(2) # round to 2 decimal places for readability
```

`describe()` computes: **count, mean, std, min, 25th percentile, 50th percentile (median), 75th percentile, max** — the seven-number summary standard for any numeric column.

**Unique value counts (for categorical columns):**

```python
df['make'].nunique()    # → 4 (number of distinct makes)
df.nunique()            # → for every column: {make: 4, model: 5, transmission_type: 2, ...}
```

**Missing value detection:**

```python
df.isnull()              # → boolean DataFrame: True where value is NaN
df.isnull().sum()        # → count of nulls per column: {engine_hp: 1, rest: 0}
```

The pattern `df.isnull().sum()` is the standard first step in data quality assessment — it reveals which columns need imputation or filtering before model training.

---

### 11. GroupBy (Aggregation by Category)

GroupBy splits the DataFrame into groups by a column's values, then applies an aggregation to each group — exactly like SQL's `GROUP BY`:

```sql
-- SQL equivalent
SELECT transmission_type, AVG(msrp), MIN(msrp), MAX(msrp)
FROM cars
GROUP BY transmission_type;
```

```python
# Pandas equivalents
df.groupby('transmission_type')['msrp'].mean()   # avg price per transmission type
df.groupby('transmission_type')['msrp'].min()    # min price per transmission type
df.groupby('transmission_type')['msrp'].max()    # max price per transmission type
```

The result is a **Series** indexed by the group keys (e.g., `'AUTOMATIC'`, `'MANUAL'`).

---

### 12. Accessing the Underlying NumPy Array

Since Pandas is built on NumPy, any Series can expose its raw NumPy array via `.values`:

```python
df['msrp'].values    # → np.array([2000, 27150, 54990, 34450, 32340])
```

This is useful when passing data to functions that expect plain NumPy arrays (e.g., custom implementations, scikit-learn internals, or the manual matrix operations from lesson 1.8).

---

### 13. Converting DataFrame back to Python Structures

```python
df.to_dict(orient='records')
# → [{'make': 'Nissan', 'model': 'Stanza', 'year': 1991, ...},
#    {'make': 'Hyundai', 'model': 'Sonata', 'year': 2017, ...},
#    ...]
```

`orient='records'` produces a list where each element is a dictionary representing one row — the inverse of Pattern B construction. Useful for serialization (saving to JSON, passing to APIs, etc.).

---

### Quick Reference: Core Pandas Operations

| Task | Syntax | Returns |
|---|---|---|
| First n rows | `df.head(n)` | DataFrame |
| Column (dot) | `df.col_name` | Series |
| Column (bracket) | `df['col_name']` | Series |
| Multiple columns | `df[['a', 'b']]` | DataFrame |
| Row by label | `df.loc[label]` | Series (row) |
| Row by position | `df.iloc[pos]` | Series (row) |
| Add/replace column | `df['new'] = values` | (in-place) |
| Delete column | `del df['col']` | (in-place) |
| Filter rows | `df[condition]` | DataFrame |
| Combine filters | `df[(c1) & (c2)]` | DataFrame |
| String method | `df['col'].str.lower()` | Series |
| Summary stats | `df.describe()` | DataFrame |
| Count nulls | `df.isnull().sum()` | Series |
| Count unique | `df.nunique()` | Series |
| Group aggregate | `df.groupby('col')['val'].mean()` | Series |
| NumPy array | `df['col'].values` | ndarray |
| To list of dicts | `df.to_dict(orient='records')` | list |

---

## Deep-Dive Explanations

### DataFrame = Labeled NumPy Arrays

A Pandas DataFrame is best understood as a **dictionary of NumPy arrays that share a common index**. When you write `df['msrp']`, Pandas returns the `msrp` column's underlying NumPy array wrapped in a Series object that adds the index labels.

This is why `.values` "unwraps" to a raw NumPy array — you are stripping off the labels and getting back to the contiguous memory block. The practical consequence is that all NumPy vectorization applies to Pandas Series with identical syntax, because the execution happens in the same C code. The label layer is metadata — lightweight, but critical for alignment and readability.

---

### Why the Index Matters: Automatic Alignment

The index is not just cosmetic. When you perform operations between two Series, Pandas **aligns by index label**, not by position:

```python
s1 = pd.Series([10, 20, 30], index=['a', 'b', 'c'])
s2 = pd.Series([1, 2, 3],   index=['b', 'c', 'd'])

s1 + s2
# a    NaN   ← 'a' has no match in s2
# b    21.0  ← matched by label 'b'
# c    32.0  ← matched by label 'c'
# d    NaN   ← 'd' has no match in s1
```

This alignment-by-label is the key difference from NumPy (which aligns by position). In ML data preparation, it prevents silent errors when rows get reordered or filtered — the index ensures the target `y` always matches its corresponding feature row `X` even after complex transformations.

---

### `.loc` vs `.iloc` — When Each Breaks

| Scenario | Use `.loc` | Use `.iloc` |
|---|---|---|
| Default `RangeIndex` (0, 1, 2, ...) | Both work (label = position) | Both work |
| Custom string index (`'a', 'b', ...`) | `.loc['b']` ✓ | `.iloc[1]` ✓ |
| After filtering rows | `.loc` by original label ✓ | `.iloc` by new position ✓ |
| After `reset_index()` | Both work again | Both work again |

The confusion arises when the index is a RangeIndex — `.loc[1]` and `.iloc[1]` return the same row, so the distinction is invisible. It becomes critical after a filter: filtering produces a DataFrame where the index labels are preserved from the original but positions restart at 0.

```python
filtered = df[df['year'] > 2015]   # e.g., keeps rows 1, 2, 3, 4
filtered.iloc[0]   # → row at position 0 = the row with original index label 1
filtered.loc[1]    # → row with label 1 (same result here, but for different reasons)
filtered.loc[0]    # ❌ KeyError — label 0 was filtered out
```

This is a frequent bug source. **`reset_index(drop=True)` after filtering** is the clean solution when you need contiguous positional access.

---

### `&` vs `and` in Boolean Filters — A Critical Pitfall

Python's `and` operator is designed for single boolean values. When applied to a Pandas Series (which is array-valued), it tries to evaluate the entire Series as `True` or `False`, which is ambiguous and raises a `ValueError`.

Pandas (and NumPy) use **bitwise operators** for element-wise logical operations:

| Python | Pandas/NumPy | Meaning |
|---|---|---|
| `and` | `&` | Element-wise AND |
| `or` | `\|` | Element-wise OR |
| `not` | `~` | Element-wise NOT |

```python
# ❌ Wrong — raises ValueError
df[df['year'] > 2015 and df['make'] == 'Nissan']

# ✓ Correct — parentheses required because & has higher precedence than >
df[(df['year'] > 2015) & (df['make'] == 'Nissan')]
```

The parentheses around each condition are **not optional** — without them, Python evaluates `2015 & df['make']` first (due to operator precedence), producing nonsense.

---

### `NaN` — Missing Values and Their Propagation

`NaN` (Not a Number) is a special IEEE 754 floating-point value from NumPy (`np.nan`) that Pandas uses to represent any missing data, regardless of the column's logical type. Key behaviors:

1. **Arithmetic propagates NaN:** `NaN / 100 = NaN`. Operations on missing values produce missing results — they don't silently become 0.
2. **`isnull()` detects them:** Regular `==` comparison fails (`NaN != NaN` by IEEE definition); always use `df.isnull()` or `pd.isna()`.
3. **Aggregations skip NaN by default:** `df['engine_hp'].mean()` computes the mean of the 4 non-null values, ignoring the 1 null.
4. **ML models cannot handle NaN:** Before feeding data to any model, all missing values must be imputed (filled with mean/median/mode) or the rows must be dropped. The `isnull().sum()` pattern is the first step of this analysis.

---

### `describe()` — What the Percentiles Tell You

The five-number summary returned by `describe()` reveals the **distribution shape** of a numeric column without plotting:

- `25%` (Q1) and `75%` (Q3): The **interquartile range** (IQR = Q3 - Q1) contains the middle 50% of data. A very large IQR relative to the mean suggests high variance or outliers.
- Large gap between `75%` and `max`: likely an **upper outlier** or skewed distribution.
- Large gap between `min` and `25%`: likely a **lower outlier**.
- `mean` significantly greater than `50%` (median): **right-skewed** distribution (a few very large values pull the mean up — common in price data).

In the car price dataset, this pattern will be visible: a few luxury/sports cars have prices far above the median, which motivates log-transforming the target variable before linear regression.

---

### GroupBy — The Split-Apply-Combine Pattern

Pandas `groupby` implements the **split-apply-combine** paradigm:

1. **Split:** Divide the DataFrame into sub-groups by the values of the grouping column.
2. **Apply:** Execute an aggregation function (`mean`, `min`, `max`, `count`, etc.) on a target column within each group.
3. **Combine:** Reassemble the results into a new Series indexed by the group keys.

```python
df.groupby('transmission_type')['msrp'].mean()
# transmission_type
# AUTOMATIC    30533.33
# MANUAL       18113.33
# Name: msrp, dtype: float64
```

This is computationally equivalent to looping over unique `transmission_type` values, filtering, and computing the mean — but implemented in optimized C code under the hood. In Session 2, groupby will be used to compute feature statistics for normalization and baseline comparisons.

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **Pandas is labeled NumPy.** A DataFrame is a dictionary of NumPy arrays with shared row index. All NumPy element-wise operations work on Series.

2. **Two ways to create a DataFrame:** list-of-lists + `columns=`, or list-of-dicts (keys auto-become column names). Both appear in real workflows.

3. **Column access:** dot notation for simple names; bracket notation always works; double brackets return a DataFrame (not a Series).

4. **`.loc` = label-based; `.iloc` = position-based.** They diverge after filtering or custom indexing. Always call `reset_index(drop=True)` after filtering if you need sequential positional access.

5. **Filtering uses `&` and `|`, not `and` and `or`.** Parentheses around each condition are required.

6. **`.str` accessor applies string methods element-wise.** Chain `.str.lower().str.replace()` for cleaning text columns. Operations return new Series — reassign to apply.

7. **`describe()` is the fastest distribution summary.** Check mean vs. median for skewness; check IQR for spread and outliers.

8. **`isnull().sum()` is the standard first step in missing-value analysis.** Every column with non-zero nulls needs a handling strategy before model training.

9. **`groupby` = SQL `GROUP BY`.** Split-apply-combine pattern; returns a Series indexed by group keys.

10. **`.values` extracts the underlying NumPy array.** Use it to bridge Pandas Series into functions that require plain `ndarray` input.

### What's Coming Next

- **Lesson 1 Summary:** A recap video covering all nine lessons of Session 1 — the ML framework, Python setup, NumPy, linear algebra, and Pandas.
- **Session 2 — Linear Regression:** The car price DataFrame from this lesson becomes the training dataset. Feature selection, the design matrix $X$, the target vector $\mathbf{y}$, and the normal equation $\mathbf{w} = (X^TX)^{-1}X^T\mathbf{y}$ (using `np.linalg.inv` from lesson 1.8) are applied to predict `msrp`.

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]] | [[ML_Zoomcamp_1_7]] | [[ML_Zoomcamp_1_8]]
