---
title: "ML Zoomcamp 1.5 — Model Selection Process"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 1
lesson: 5
tags: [machine-learning, model-selection, train-validation-test-split, overfitting, multiple-comparisons, evaluation]
source: "YouTube — ML Zoomcamp Session 1"
date_processed: 2026-05-11
---

# ML Zoomcamp 1.5 — Model Selection Process

---

## Executive Summary

Training a model is only half the problem. The harder question is: **how do you know which model is actually the best one?** This lesson answers that with the **model selection process** — a rigorous, statistically grounded procedure for choosing among competing models without being deceived by random luck.

The core insight is that evaluating a model on the same data it was trained on is meaningless; a model must be evaluated on data it has never seen, mirroring how it will be used in production. However, even this has a subtle failure mode: when many models are compared against the same validation set, one of them can score well **purely by chance** (the multiple comparisons problem). The solution is a **three-way split** of your data into **train / validation / test** sets, where validation is used for model selection and test is a final, single-use sanity check to confirm the selected model didn't just get lucky. After selection, the validation data is recycled back into training for the final model.

---

## Zero-Loss Extraction

### The Fundamental Evaluation Principle

A model trained in July, deployed in August, will see **completely new data** in production that it never encountered during training. Evaluation must replicate this condition. You cannot evaluate a model on its own training data — it has already "seen the answers."

**Solution:** Hold out a subset of data before training, train on the rest, and evaluate the trained model on the withheld portion.

---

### Step 1 — The Train/Validation Split

| Split | Proportion | Purpose |
|---|---|---|
| **Training set** | 80% | Feed into the ML algorithm to produce model g |
| **Validation set** | 20% | Evaluate g after training; model never sees this during training |

**Data flow:**

```
Full dataset (100%)
        │
        ├── Training set (80%) ──→ X_train, y_train ──→ Train model g
        │
        └── Validation set (20%) ──→ X_val, y_val ──→ Apply g → ŷ_val
                                                              │
                                                Compare ŷ_val vs y_val
                                                              │
                                                    Compute accuracy (or other metric)
```

**Example evaluation on 6 emails:**

| Email | y (actual) | ŷ (predicted) | Correct? |
|---|---|---|---|
| 1 | 1 (spam) | 1 | ✓ |
| 2 | 0 (not spam) | 1 | ✗ |
| 3 | 1 (spam) | 1 | ✓ |
| 4 | 0 (not spam) | 0 | ✓ |
| 5 | 1 (spam) | 1 | ✓ |
| 6 | 0 (not spam) | 0 | ✓ |

Result: **4/6 correct → 66.7% accuracy**

---

### The Multiple Comparisons Problem

When you evaluate many models against the **same validation set**, statistical chance means at least one model will appear to perform well — not because it is actually better, but because it happened to predict this particular subset correctly.

**Illustration (coin-flipping analogy):**

Imagine your models are coins — each coin represents a different model family. For 5 emails, you flip each coin to generate predictions:

| "Model"           | Predictions                       | Accuracy |
| ----------------- | --------------------------------- | -------- |
| Euro              | [spam, spam, not spam, not spam, spam] | 20%      |
| US Dollar         | [spam, not spam, not spam, not spam, spam]       | 40%      |
| Polish Złoty      | [spam, spam, spam]                | 20%      |
| Ruble             | [not spam, not spam, not spam, not spam]              | 20%      |
| Ukrainian Hryvnia | [spam, not spam, spam, not spam, not spam]       | **100%** |

The Hryvnia achieves 100% accuracy — not because it's a better predictor, but because it happened to produce the exact same sequence as the ground truth by random chance. **This exact phenomenon occurs with real ML models.**

> In statistics, this is called the **multiple comparisons problem**: perform enough comparisons and you will find a spurious "winner" even when all competitors are equally bad.

---

### Step 2 — The Train/Validation/Test Split (The Proper Solution)

To guard against the multiple comparisons problem, hold out **two** separate datasets:

| Split | Proportion | Purpose |
|---|---|---|
| **Training set** | 60% | Train all candidate models |
| **Validation set** | 20% | Compare models; select the best |
| **Test set** | 20% | Final one-time check of the selected model |

> The 60/20/20 ratio is a common default but **not a rule**. It depends on total dataset size.

**Crucially: the test set is kept completely hidden throughout the model selection process.** It is only used once, after a winner has been selected, to verify the selection wasn't a lucky accident.

---

### The Six-Step Model Selection Process

```
1. Split data into Train / Validation / Test
         │
2. Train model g on Training set only
         │
3. Evaluate g on Validation set → record metric (e.g., accuracy)
         │
4. Repeat steps 2–3 for many different model families
         │
5. Select the best model based on validation performance
         │
6. Apply selected model to Test set → confirm it generalizes
```

**Worked example with model comparison table:**

| Model | Validation Accuracy |
|---|---|
| Logistic Regression | 66% |
| Decision Tree | 60% |
| Random Forest | 67% |
| Neural Network | **80%** ← selected |

After selection: apply Neural Network to test set → **79% accuracy**. This closely matches the validation score (80%), confirming the model did not simply get lucky on the validation set. ✓

---

### Final Step — Recycling the Validation Set for the Production Model

After the best model family is selected, the validation data has served its purpose. Rather than discarding it, **combine it with the training set** and retrain the final model on the full 80%:

```
After selection:
  Train set (60%) + Validation set (20%) = Combined set (80%)
           │
           ▼
  Retrain selected model (e.g., Neural Network) on 80% of data
           │
           ▼
  Verify final model on Test set (20%)
           │
           ▼
  Deploy to production
```

**Why this matters:** More training data almost always leads to a better model. By recycling validation data into the final training run, you extract more signal without compromising the integrity of the selection process.

---

## Deep-Dive Explanations

### Why Can't You Evaluate on Training Data?

Imagine a student who memorizes the exact answers to a practice exam, then takes the same exam again — they will score 100%, but this tells you nothing about whether they actually learned the material. The same applies to models: a model evaluated on its own training data will look artificially good because it has already "seen the answers." The only meaningful measure of a model's quality is its performance on **data it has never encountered**.

This principle — evaluation on held-out data — is the single most important rule in machine learning evaluation. Every evaluation methodology in the field (train/val/test splits, k-fold cross-validation, time-series walk-forward validation) is a variation of this fundamental idea.

---

### Why Does the Multiple Comparisons Problem Matter in Practice?

The coin-flip analogy seems absurd because no engineer would deploy a coin-flip model. But the same statistical phenomenon affects real models in subtle ways:

- You try 20 neural network architectures with different hyperparameters.
- By pure chance, one configuration happens to overfit your specific validation set's quirks — maybe the validation set has slightly more examples of a pattern that model over-weighted.
- It scores highest on validation, gets selected, and then **underperforms in production** because its apparent edge was noise, not signal.

The test set breaks this cycle. Even if a model got lucky on the validation set, it will fail to replicate that luck on a second, completely independent dataset (the test set). A large gap between validation performance and test performance is a red flag: the model may have "overfit the validation set" through the process of model selection itself.

> This is distinct from *overfitting to training data* — it's overfitting to the **evaluation procedure** itself, sometimes called "validation set leakage" or "selection bias."

---

### Interpreting the Train/Val/Test Split Ratio

The 60/20/20 split is intuitive but not optimal for all situations:

- **Small datasets (< 1,000 records):** 60/20/20 wastes too much data on evaluation. Consider k-fold cross-validation instead.
- **Large datasets (> 100,000 records):** 95/2.5/2.5 is often fine — even 2.5% of 100K is 2,500 evaluation examples, more than enough for statistical confidence.
- **Time-series data:** Splits must be **chronological** — always train on older data, validate and test on newer data. Random shuffling breaks temporal integrity.

The underlying principle is: each split needs to be large enough that the computed metric has low variance (is statistically stable), but not so large that it unnecessarily reduces the training set.

---

### The Production Analogy: July Training, August Deployment

The lecture introduces this metaphor to make evaluation philosophy intuitive:

| Time | What Happens |
|---|---|
| **July** | All available data → train model g |
| **August** | Model deployed; new emails arrive → model g has never seen any August data |

Evaluation must simulate this temporal separation. The validation set plays the role of "August data" — data the model never touched during July training. If you let the model peek at August data during training (data leakage), your evaluation is meaningless and the model will fail in real-world use.

---

## Key Takeaways & Next Steps

### Key Takeaways

1. **Never evaluate a model on its training data.** Evaluation must use held-out data the model has never seen. This simulates the real-world condition where a deployed model encounters new, unseen examples.

2. **A two-way split (train/val) is vulnerable to the multiple comparisons problem.** When comparing many models, one will appear to win by chance. The validation accuracy of the "winner" will be overly optimistic.

3. **A three-way split (train/val/test) is the standard solution.** The test set is a one-time insurance check: if the selected model performs similarly on test as on validation, the selection was real and not lucky.

4. **The six-step model selection process:**
   - Split data into 3 parts → Train → Evaluate on val → Repeat for many models → Select best → Verify on test.

5. **Validation data is not wasted.** After model selection, merge train + validation to retrain the final model before deployment. This gives the production model more data to learn from.

6. **The 60/20/20 split is a starting point, not a law.** Adjust ratios based on dataset size and statistical requirements.

### What's Coming Next

- **Lesson 1.6:** Introduction to **NumPy** — the foundational Python library for numerical computation, required for building ML pipelines in code.
- **Lesson 1.7:** Introduction to **Pandas** — the library for tabular data manipulation, feature engineering, and data preparation.
- **Future sessions:** All of the concepts from lesson 1.5 will be implemented in code: splitting data, training models, evaluating on validation and test sets.

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]]
