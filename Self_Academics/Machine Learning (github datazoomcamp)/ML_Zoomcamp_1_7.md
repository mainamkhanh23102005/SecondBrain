---
title: "ML Zoomcamp 1.7 — Introduction to NumPy"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 1
lesson: 7
tags: [machine-learning, numpy, python, arrays, vectorization, numerical-computation, data-science, linear-algebra]
source: "YouTube — ML Zoomcamp Session 1"
date_processed: 2026-05-14
---

# ML Zoomcamp 1.7 — Introduction to NumPy

---

## Executive Summary

NumPy (Numerical Python) is the **foundational library for numerical computation in Python** and the backbone of the entire scientific Python ecosystem. At its core, NumPy provides the **n-dimensional array** (`ndarray`) — a data structure that is fundamentally different from a Python list in two key ways: it is stored in contiguous memory (making it much faster), and it supports **vectorized operations**, meaning mathematical functions can be applied to entire arrays at once without writing explicit loops.

This lesson covers the practical toolkit that appears in nearly every ML workflow: creating arrays (1D and 2D), indexing and slicing, generating random data, performing element-wise arithmetic and comparison operations, and computing summary statistics. The central insight is that NumPy lets you write code that **reads like mathematics** — concise, expressive, and dramatically faster than equivalent Python loop code.

---

## Zero-Loss Extraction

### 1. Importing NumPy

```python
import numpy as np   # 'np' is the universal convention across all data science
```

The alias `np` is not enforced by Python — it is a community convention so universal that code using `numpy.zeros(...)` instead of `np.zeros(...)` will confuse other practitioners.

---

### 2. Creating 1D Arrays

| Function | Example | Output |
|---|---|---|
| `np.zeros(n)` | `np.zeros(10)` | Array of `n` zeros |
| `np.ones(n)` | `np.ones(10)` | Array of `n` ones |
| `np.full(n, val)` | `np.full(10, 2.5)` | Array of `n` elements all equal to `val` |
| `np.array(list)` | `np.array([1, 2, 3, 5, 7, 12])` | Array from Python list |
| `np.arange(stop)` | `np.arange(10)` | Integers `[0, 1, ..., 9]` |
| `np.arange(start, stop)` | `np.arange(3, 10)` | Integers `[3, 4, ..., 9]` |
| `np.linspace(start, stop, n)` | `np.linspace(0, 1, 11)` | `n` evenly spaced values from `start` to `stop` (inclusive) |

```python
a = np.zeros(10)            # [0. 0. 0. 0. 0. 0. 0. 0. 0. 0.]
b = np.ones(10)             # [1. 1. 1. 1. 1. 1. 1. 1. 1. 1.]
c = np.full(10, 2.5)        # [2.5 2.5 ... 2.5]
a = np.array([1, 2, 3, 5, 7, 12])
r = np.arange(10)           # [0 1 2 3 4 5 6 7 8 9]
r = np.arange(3, 10)        # [3 4 5 6 7 8 9]
l = np.linspace(0, 1, 11)   # [0.  0.1 0.2 0.3 ... 1.0]
```

> `np.arange` is analogous to Python's built-in `range`, but returns a NumPy array instead of an iterator. `np.linspace` is distinct: it takes the **number of points** rather than a step size, and always includes both endpoints.

---

### 3. Indexing and Element Assignment (1D)

Python's **zero-based indexing** applies directly to NumPy arrays:

```python
a = np.array([1, 2, 3, 5, 7, 12])

a[2]      # → 3   (3rd element; index 2 = position 3)
a[2] = 10 # Mutate: replace 3 with 10 → [1, 2, 10, 5, 7, 12]
```

---

### 4. Creating 2D Arrays (Matrices)

NumPy arrays can have any number of dimensions. For ML, **2D arrays (matrices)** are the most common, representing datasets (rows = samples, columns = features).

```python
# Zeros matrix: pass shape as a tuple (rows, columns)
m = np.zeros((5, 2))       # 5 rows, 2 columns, all zeros

# From a list of lists
n = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
])
# Shape: 3 rows × 3 columns
```

---

### 5. Indexing and Slicing (2D)

2D arrays are indexed with **two indices**: `[row, column]`. The colon `:` is the **"all"** operator — it means "every element along this axis."

```python
# Element access: [row, column]
n[0, 1]       # → 2   (row 0, column 1)
n[0, 1] = 20  # Replace that element with 20

# Access an entire row (returns a 1D array)
n[0]          # → [1, 2, 3]   (first row)
n[1]          # → [4, 5, 6]   (second row)
n[2]          # → [7, 8, 9]   (third row)

# Assign to an entire row
n[2] = [1, 1, 1]   # Replace last row with ones

# Access an entire column: n[:, col_index]
# The : means "all rows"
n[:, 1]       # → [2, 5, 8]   (second column)
n[:, 2]       # → [3, 6, 9]   (third column)

# Assign to an entire column
n[:, 2] = [0, 1, 2]   # Replace last column
```

---

### 6. Random Array Generation

NumPy's `random` subpackage provides several distributions for generating synthetic data and initializing ML experiments.

```python
# Uniform distribution U(0, 1) — values between 0 and 1
np.random.rand(5, 2)           # 5×2 matrix, random floats in [0, 1)

# Fix the random seed for reproducibility
np.random.seed(2)
np.random.rand(5, 2)           # Same result every time seed is set first

# Standard normal distribution N(0, 1)
np.random.randn(5, 2)          # Values centered around 0, spread by std dev 1

# Random integers: low (inclusive) to high (exclusive)
np.random.randint(0, 100, (5, 2))   # Integers in [0, 99], shape 5×2

# Scale uniform to any range via multiplication
np.random.rand(5, 2) * 100     # Floats in [0, 100)
```

---

### 7. Element-wise Operations (Vectorization)

This is NumPy's most important feature. **Scalar operations** are broadcast across every element; **array operations** are applied element-by-element. No loops required.

```python
a = np.arange(5)    # [0, 1, 2, 3, 4]

# Scalar operations (broadcast to every element)
a + 1               # [1, 2, 3, 4, 5]
a * 2               # [0, 2, 4, 6, 8]
a - 1               # [-1, 0, 1, 2, 3]
a / 2               # [0.0, 0.5, 1.0, 1.5, 2.0]
a ** 2              # [0, 1, 4, 9, 16]

# Chained operations (evaluated left-to-right like normal math)
a * 2 + 10          # [10, 12, 14, 16, 18]
(a + 1) ** 2        # [1, 4, 9, 16, 25]

# Element-wise array operations (arrays must have compatible shapes)
b = np.array([1, 2, 3, 4, 5])
a + b               # [1, 3, 5, 7, 9]   (element-by-element sum)
a * b               # [0, 2, 6, 12, 20]  (element-by-element product)
a / b               # [0.0, 0.5, 0.67, 0.75, 0.8]
```

> This is the same mechanism used when scaling random numbers: `np.random.rand(5, 2) * 100` multiplies every element by 100 — no loop, one expression.

---

### 8. Boolean (Comparison) Operations and Boolean Indexing

Comparison operators on NumPy arrays return **boolean arrays** — arrays of `True`/`False` values — which can then be used to **filter** elements without a loop.

```python
a = np.arange(5)    # [0, 1, 2, 3, 4]
b = np.array([2, 0, 1, 5, 3])

# Comparison with scalar → boolean array
a >= 2              # [False, False, True, True, True]
a == 3              # [False, False, False, True, False]

# Comparison between arrays → element-wise boolean array
a > b               # [False, True, True, False, True]

# Boolean indexing: use a boolean array to select elements
a[a >= 2]           # → [2, 3, 4]   (only elements where condition is True)
a[a > b]            # → elements of a where a is greater than corresponding b
```

This pattern — `array[boolean_condition]` — is one of the most-used idioms in data science for filtering rows, selecting features, and masking outliers.

---

### 9. Summarizing Operations

Summarizing operations **collapse** an array into a single scalar. Unlike element-wise operations, they aggregate across elements.

```python
a = np.arange(5)    # [0, 1, 2, 3, 4]

a.min()     # → 0    (smallest element)
a.max()     # → 4    (largest element)
a.sum()     # → 10   (sum of all elements: 0+1+2+3+4)
a.mean()    # → 2.0  (arithmetic mean)
a.std()     # → standard deviation (spread of values around the mean)

# Also works on 2D arrays — aggregates over ALL elements by default
n = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
n.sum()     # → 45
n.min()     # → 1
n.mean()    # → 5.0
```

> Per-axis aggregations (e.g., sum of each row, min of each column) are possible with the `axis` parameter — covered in the NumPy documentation linked from the course.

---

## Deep-Dive Explanations

### Why NumPy Arrays Instead of Python Lists?

Python lists are general-purpose containers: each element is a full Python object with its own type, reference count, and memory header. This flexibility comes at a steep cost in memory and CPU time.

NumPy arrays store data in **contiguous blocks of memory**, all elements of the same data type (e.g., 64-bit floats). The computation happens in **compiled C code**, not interpreted Python. The practical result:

- A NumPy operation on an array of 1 million elements runs **10–100× faster** than an equivalent Python `for` loop.
- Memory usage is typically **5–10× lower** than an equivalent Python list.

In ML, where datasets routinely have millions of samples and hundreds of features, this difference is the boundary between code that runs in seconds and code that runs in hours.

---

### What Is Vectorization and Why Does It Matter?

**Vectorization** means expressing operations on entire collections of data as single statements, rather than looping over individual elements.

Conceptually, the shift is from:

```python
# Non-vectorized (Python loop)
result = []
for x in a:
    result.append(x * 2 + 1)
```

to:

```python
# Vectorized (NumPy)
result = a * 2 + 1
```

These two snippets produce identical output, but the NumPy version:
1. Is faster by an order of magnitude (C loop vs. Python loop)
2. Reads like a mathematical expression, directly mirroring the formula
3. Composes with other NumPy operations without intermediate loops

In ML, virtually every algorithm — gradient descent, matrix multiplication, feature normalization — is expressed as vectorized operations. NumPy makes this natural.

---

### Understanding the Colon `:` in 2D Indexing

The colon `:` is a **slice that means "all indices along this axis."** In a 2D array:

```
n[row_index, column_index]
```

If either index is `:`, it selects everything along that dimension:

```python
n[0, :]    # Row 0, all columns  → same as n[0]
n[:, 1]    # All rows, column 1  → second column as 1D array
n[:, :]    # All rows, all columns → entire matrix (copy)
```

This notation is borrowed from mathematical **matrix slicing** and is consistent throughout the entire NumPy/Pandas ecosystem. Mastering it is essential for data manipulation in later lessons.

---

### Pseudorandom Numbers and the Importance of Seeding

Computers cannot generate truly random numbers — they use **pseudorandom number generators (PRNGs)**, deterministic algorithms that produce sequences of numbers with statistical properties indistinguishable from true randomness. Given the same starting value (the **seed**), a PRNG always produces the same sequence.

```python
np.random.seed(42)
np.random.rand(3)   # Always produces the same 3 numbers on any machine
```

In ML, seeding is critical for **reproducibility**:
- Two researchers seeding with the same value will get identical random train/validation splits, identical random weight initializations, and identical stochastic gradient descent trajectories.
- Without seeding, experimental results cannot be verified or replicated.

> Small caveat: the exact output can differ across NumPy versions or operating systems due to changes in the PRNG algorithm, but within a consistent environment, the seed guarantees reproducibility.

---

### Boolean Indexing — The Filter Pattern

The pattern `array[condition]` is so common it deserves its own mental model:

```
Step 1: Evaluate condition → boolean array of same shape
Step 2: Use boolean array as a mask → select only True positions
```

```python
a = np.array([10, 5, 8, 2, 9])

mask = a > 6          # [True, False, True, False, True]
a[mask]               # → [10, 8, 9]

# More commonly written inline:
a[a > 6]              # → [10, 8, 9]
```

This is the NumPy equivalent of SQL's `WHERE` clause, and it generalizes to filtering rows of a feature matrix (2D array) by some condition on a target column — a pattern that appears constantly in data preparation.

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **NumPy arrays are not Python lists.** They store homogeneous data in contiguous memory and execute operations in compiled C — enabling 10–100× speedups for numerical work.

2. **`import numpy as np` is a universal convention.** Always use `np` as the alias.

3. **Creating arrays:** `np.zeros`, `np.ones`, `np.full`, `np.array`, `np.arange`, `np.linspace` cover all common initialization patterns.

4. **2D arrays use tuple shapes and `[row, col]` indexing.** The colon `:` selects all elements along an axis: `n[:, 1]` retrieves the second column.

5. **Seeding with `np.random.seed(n)` is mandatory for reproducible experiments.** Apply it before any random array generation.

6. **Vectorization replaces loops.** Scalar and array operations apply element-wise with no explicit iteration. Chain operations freely: `a * 2 + 10`.

7. **Boolean indexing is the vectorized filter.** `a[a > 5]` selects all elements of `a` greater than 5 — no loop, one expression.

8. **Summarizing operations collapse arrays to scalars:** `.min()`, `.max()`, `.sum()`, `.mean()`, `.std()`.

### What's Coming Next

- **Lesson 1.8:** Introduction to **Pandas** — the library for tabular data manipulation built on top of NumPy. DataFrames are the primary data structure for loading, cleaning, and preparing datasets for ML.
- **Future sessions:** NumPy will be used directly for matrix operations in linear algebra (dot products, matrix multiplication) — the mathematical foundation of linear regression and other models.

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]]
