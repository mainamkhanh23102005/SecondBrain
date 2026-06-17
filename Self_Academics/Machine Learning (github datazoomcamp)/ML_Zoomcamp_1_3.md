# ML Zoomcamp 1.3 — Supervised Machine Learning

**Source:** ML Zoomcamp by DataTalksClub — Session 1, Lesson 3
**Tags:** #machine-learning #supervised-learning #classification #regression #ranking
**Date Processed:** 2026-05-11

---

## Executive Summary

Supervised machine learning is the process of training an algorithm by providing it labeled examples — a **feature matrix X** paired with a **target vector y** — so it can learn a function **g(X) ≈ y** that generalizes to unseen data. Based on the nature of the target variable, supervised ML problems fall into three types: **regression** (numeric output), **classification** (categorical output, with binary and multi-class subtypes), and **ranking** (ordered scoring of items).

---

## Zero-Loss Extraction

### Core Definitions

| Concept | Formal Definition |
|---|---|
| **Feature Matrix X** | A 2D array where each **row** is an observation/object and each **column** is a feature (characteristic) of that object |
| **Target Vector y** | A 1D array where each element is the known label/value for the corresponding row in X |
| **Model g** | A function trained such that g(X) ≈ y — it extracts patterns from X to predict y |
| **Training** | The process of finding g by optimizing it against known (X, y) pairs |
| **Prediction** | Applying the trained g to new, unseen X to produce ŷ (predictions) |

### The Three Types of Supervised ML

| Type | Output of g | Target Variable | Example |
|---|---|---|---|
| **Regression** | Continuous number (−∞ to +∞) | Numerical value | Car price, house price |
| **Classification** | Category (discrete label) | Class label | Spam/not-spam, image category |
| **Ranking** | Score per item → ordered list | Relevance/preference score | Search results, recommender systems |

### Classification Subtypes

| Subtype | # of Classes | Target Values | Example |
|---|---|---|---|
| **Binary Classification** | 2 | {0, 1} | Spam detection (spam=1, not-spam=0) |
| **Multi-class Classification** | ≥ 3 | {0, 1, 2, …, k} | Image recognition (car, cat, dog) |

---

## Deep-Dive Explanations

### 1. The Supervised Learning Paradigm

The word "supervised" is deliberate: humans act as teachers. We show the algorithm many labeled examples — for each input X (a car's make, mileage, model year), we provide the correct output y (its price). The algorithm then learns the statistical patterns that map X → y, so it can generalize: given a **new** car it has never seen, it can predict a price.

**Key insight:** The model doesn't memorize — it generalizes. If the actual price was $11,000 and the model predicts $15,000, that imperfect prediction is acceptable as long as it's useful.

---

### 2. The Mathematical Formalization

$$g: X \rightarrow \hat{y} \approx y$$

- **X** (capital) → feature matrix, shape `[n_observations × n_features]`
- **y** (lowercase) → target vector, shape `[n_observations]`
- **g** → the learned model function

The goal: find g such that applying it to X produces predictions $\hat{y}$ as close as possible to the true labels y.

**Intuition for non-math readers:**
- X is a spreadsheet: rows = items (emails, cars), columns = properties (word counts, mileage)
- y is a single column saying "the correct answer" for each row
- g is the formula that takes any row of X and outputs a predicted answer

---

### 3. Regression

Regression problems output a **real number**. The output range can be:
- Strictly non-negative (e.g., price: $0 to +∞)
- Any real number (e.g., temperature change: −∞ to +∞)

**Examples:**
- **Car price prediction:** X = {make, model, year, mileage, condition} → y = price in USD
- **House price prediction:** X = {area in m², rooms, distance from city center, proximity to subway} → y = price

The critical distinguishing factor: the target y is **continuous** — there is no fixed set of possible values.

---

### 4. Classification

Classification problems output a **discrete category** rather than a number. The model assigns each input to one class from a predefined set.

**Binary Classification** (2 classes):
- The most common and practically important subtype
- Target y ∈ {0, 1}
- Model g typically outputs a **probability** between 0 and 1 (e.g., P(spam) = 0.87), which is then thresholded
- Example: Spam detection — features extracted from email text → P(spam)

**Multi-class Classification** (≥ 3 classes):
- Target y ∈ {class_1, class_2, …, class_k}
- Example: Image recognition — input image → one of {car, cat, dog}
- The number of classes can be arbitrarily large (thousands of ImageNet categories, for instance)

**Why binary gets special treatment:** It has its own set of algorithms, evaluation metrics (precision, recall, ROC-AUC), and output interpretation (probability vs. hard label).

---

### 5. Ranking

Ranking is a supervised ML problem type where the goal is to **order a set of items** by predicted relevance or preference for a given user/query. It is less often formally taught in intro courses but is extremely common in production systems.

**How it works:**
1. For each candidate item, g assigns a score s ∈ [0, 1]
2. All items are sorted by their scores in descending order
3. Top-k items are returned

**Real-world examples:**
- **E-commerce recommender systems** (e.g., OLX, Amazon): Given user profile + item catalog → score each item → show top 6 most likely purchases
- **Web search** (e.g., Google): Given query "machine learning zoomcamp" + document corpus → score each document by predicted relevance → return ranked list
- **Marketplace search**: Given search term "iPhone" + all listings → rank by relevance to this specific user

**Distinction from classification:** Ranking doesn't just say "relevant or not" — it produces an **ordering** where relative differences matter. A document at rank 1 must be more relevant than rank 2, not just "relevant."

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **Supervised ML = learning from labeled examples.** You provide (X, y) pairs; the algorithm learns g such that g(X) ≈ y.
2. **X is always a 2D feature matrix** (rows = observations, columns = features). y is always a 1D target vector.
3. **The type of problem is determined by the type of y:**
   - Continuous number → Regression
   - Discrete category → Classification (binary or multi-class)
   - Ordered relevance → Ranking
4. **Binary classification is the most practically prevalent type** — most real-world ML problems can be framed as "will event X happen? (yes/no)"
5. **The model g learns patterns statistically** — it will not always predict the exact value, but it aims to be close enough to be useful.

### What's Coming Next

- **Lesson 1.4:** The bigger picture — how to organize ML projects end-to-end using the **CRISP-DM** methodology (Cross-Industry Standard Process for Data Mining)
- **Later in the course:** Deep dives into regression (next lesson) and binary classification (primary focus of the course)

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]] | [[ML_Zoomcamp_1_7]]
