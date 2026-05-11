---
title: "ML Zoomcamp 1.2 — ML vs Rule-Based Systems"
course: "Machine Learning Zoomcamp (DataTalksClub)"
session: 1
lesson: 2
tags: [machine-learning, rule-based-systems, spam-detection, classification, feature-engineering, supervised-learning]
source: "YouTube — ML Zoomcamp Session 1"
date_processed: 2026-05-10
---
 
# ML Zoomcamp 1.2 — ML vs Rule-Based Systems

---

## Executive Summary

This lesson draws a precise architectural distinction between **rule-based systems** and **machine learning systems** using spam detection as a running example. In a rule-based system, a human analyst examines data, manually identifies patterns, and encodes those patterns as hard-coded `if-else` logic. This approach is brittle: as the problem evolves, the rule set grows without bound and becomes impossible to maintain.

Machine learning inverts the paradigm. Instead of a human writing the rules, the algorithm *learns* the rules from labeled examples. The human's job shifts from *writing rules* to *labeling data* and *engineering features*. Crucially, the rules discovered during the rule-based phase are not wasted — they become the first features fed into the ML model. The output of ML training is a **model** (a reusable artifact) that can assign a probability score to any new unseen example.

---

## Zero-Loss Extraction

### 1. The Problem: Spam Detection

- An email system serves users who begin receiving unsolicited or fraudulent emails.
- Goal: build a **binary classifier** that routes emails to either `INBOX` or `SPAM`.

---

### 2. Rule-Based Approach

#### 2a. How Rules Are Derived
1. Analyst manually inspects spam emails.
2. Identifies discriminating patterns (e.g., specific sender address, keywords in subject/body).
3. Encodes each pattern as an explicit `if-else` condition in code (e.g., Python).

#### 2b. Example Rules Discovered

| Rule | Condition | Label |
|------|-----------|-------|
| R1 | `sender == "promotions@online.com"` | SPAM |
| R2 | `"tax review" in subject AND sender_domain == "online.com"` | SPAM |
| R3 | `"deposit" in body` | SPAM |
| Default | none of the above | INBOX (ham) |

#### 2c. Why Rule-Based Systems Fail

- **Rules decay**: Spammers adapt. New spam patterns constantly emerge, requiring new rules.
- **False positives**: A legitimate email from Pedro saying *"I paid the deposit"* triggers Rule R3. The word `"deposit"` alone is not a reliable signal.
- **Unmaintainable code**: As rules accumulate, interactions between rules cause unexpected breakage. Every change risks regressing previously working cases.
- **Never-ending cycle**: Analyze → write rules → deploy → new complaint → analyze again → repeat forever.

---

### 3. Machine Learning Approach

The ML approach solves the maintainability problem by replacing hand-written rules with a **learned model** trained from labeled data.

#### 3a. Step 1 — Collect Labeled Data
- Email providers expose a **"Mark as Spam"** button. User interactions generate labels.
- Dataset: each email paired with a label: `spam = 1`, `not spam (ham) = 0`.
- This label is called the **target variable** (what we want the model to predict).

#### 3b. Step 2 — Extract Features
Features are quantitative representations of each email. They describe *characteristics* of the data that are potentially predictive.

**Example binary features** (1 = True, 0 = False):

| Feature # | Description |
|-----------|-------------|
| F1 | `len(title) > 10` |
| F2 | `len(body) > 100` |
| F3 | `sender == "promotions@online.com"` |
| F4 | Sender name matches a known suspicious pattern |
| F5 | `sender_domain == "online.com"` |
| F6 | `"deposit" in body` |

**Binary features**: Features restricted to exactly two values — `True/False` encoded as `1/0`.

> **Key insight**: These features directly mirror the rules from the rule-based phase. This is intentional and good practice: **start with a rule-based system first**, then convert those rules into features for an ML model. The rule-based phase is analytical groundwork, not wasted effort.

**Feature vector for a single email** (example):

```
Email: "Congratulations! You've won a prize. Pay $10 deposit to account XYZ."
Labels: spam = 1

F1 (title long)          → 1   (title > 10 chars)
F2 (body long)           → 1   (body is lengthy)
F3 (known spam sender)   → 0   (sender is different)
F4 (suspicious name)     → 0   (name looks normal)
F5 (domain = online.com) → 1   (domain matches)
F6 (contains "deposit")  → 1   (word present)

Feature vector: [1, 1, 0, 0, 1, 1]   Target: 1
```

The full dataset is a matrix of such feature vectors, one row per email.

#### 3c. Step 3 — Train the Model
- The feature matrix + target variable column are fed into an **ML algorithm**.
- The algorithm learns the relationship between feature patterns and labels.
- This process is called **training** or **fitting** the model.
- Output: a **model** — a mathematical function that can score new emails.

#### 3d. Step 4 — Generate Predictions (Inference)
- The trained model takes a feature vector as input and outputs a **probability**: the model's confidence that the email is spam.
- Example outputs: `[0.80, 0.60, 0.10, 0.01, 0.70, 0.40]` for six emails.

#### 3e. Step 5 — Apply a Decision Threshold
- A **threshold** converts the continuous probability into a discrete class label.
- Default threshold: **0.5** (50%).
  - `P(spam) >= 0.5` → classify as **SPAM** → route to spam folder.
  - `P(spam) < 0.5` → classify as **HAM** → route to inbox.

| Email | P(spam) | Decision |
|-------|---------|----------|
| 1 | 0.80 | SPAM |
| 2 | 0.60 | SPAM |
| 3 | 0.10 | HAM |
| 4 | 0.01 | HAM |
| 5 | 0.70 | SPAM |
| 6 | 0.40 | HAM |

> The threshold is a tunable hyperparameter. Lowering it catches more spam (higher recall) but increases false positives. Raising it reduces false positives but misses more spam (lower recall).

---

### 4. Architectural Comparison: Rule-Based vs ML

```
RULE-BASED SYSTEM
─────────────────
  Code (hard-coded rules)
       +
  Data (emails to classify)
       │
       ▼
  Outcome (spam / not spam)

Human writes the logic. Logic is static until a human changes it.


MACHINE LEARNING — TRAINING PHASE
───────────────────────────────────
  Data (emails)
       +
  Outcome (labels: spam / not spam)   ← outcome is INPUT, not output
       │
       ▼
  ML Algorithm
       │
       ▼
  Model (learned artifact)

MACHINE LEARNING — INFERENCE PHASE
────────────────────────────────────
  Data (new emails, unknown label)
       +
  Model
       │
       ▼
  Outcome (predicted: spam / not spam)
```

**The fundamental flip**: In rule-based systems, the *outcome* is embedded in the code. In ML, the *outcome* (label) is fed *into* the system as training signal to produce the model. The model then generates outcomes for unseen data.

---

## Deep-Dive Explanations

### Why Does the Rule-Based Approach Break?

The core failure mode is **concept drift** combined with **rule interaction complexity**.

- **Concept drift**: The definition of "spam" changes over time as spammers adapt to detection. A rule that works today (block "deposit") creates false positives tomorrow when legitimate users happen to use the same word.
- **Combinatorial complexity**: Rules don't exist in isolation. Adding Rule R3 may interfere with R1 in unexpected ways. Testing every combination is infeasible as the rule count grows.
- **Maintenance cost scales superlinearly**: Each new rule requires re-analysis of all existing emails to ensure it doesn't create regressions, re-deployment, and monitoring. This is human labor that never stops.

### Why Features Often Mirror Rules

When transitioning from rule-based to ML, the rules you've already written encode *domain knowledge* — signals that a human expert identified as discriminating. Rather than discarding this knowledge, you preserve it by converting each rule into a binary feature:

- Rule: `if sender == "promotions@online.com" → SPAM`
- Feature: `F3 = 1 if sender == "promotions@online.com" else 0`

The ML algorithm then determines *how much weight* to assign to each feature. A feature derived from a weak rule may get low weight. A feature derived from a strong rule gets high weight. The algorithm adjudicates between competing signals in a principled way — something a human maintaining `if-else` chains cannot easily do.

### What the Model Actually Does

The model is a mathematical function `f(x) → p` where:
- `x` is a feature vector (e.g., `[1, 1, 0, 0, 1, 1]`)
- `p ∈ [0, 1]` is the predicted probability of spam

The model's internal parameters (weights) were optimized during training to minimize the difference between its probability outputs and the true labels across all training examples. After training, these weights are *frozen* and the model can be applied to any new email without retraining.

### Binary Features and Feature Types

This lesson uses exclusively **binary (boolean) features** for simplicity. In practice, features can be:
- **Continuous**: e.g., `len(body)` as a raw number (not just `> threshold`)
- **Categorical**: e.g., one-hot encoding of `sender_domain`
- **Count-based**: e.g., number of exclamation marks in subject
- **TF-IDF**: term frequency representations of the full email body

Binary features are a valid starting point and are often surprisingly competitive because many important signals in classification problems are essentially presence/absence of a pattern.

### The Threshold Is a Policy Decision, Not a Model Parameter

The model outputs probabilities. The threshold that converts probabilities to labels is set *by the system designer*, not learned. This is deliberate:
- In spam detection, you might prefer `threshold = 0.7` to minimize false positives (legitimate emails wrongly flagged as spam are highly disruptive).
- In fraud detection, you might prefer `threshold = 0.3` to catch as many fraudulent transactions as possible, accepting some false positives.

The optimal threshold depends on the **cost asymmetry** between false positives and false negatives in the specific application.

---

## Key Takeaways

1. **Rule-based systems are a dead end at scale**: they require constant human intervention as the problem evolves and become unmanageable as the rule set grows.

2. **Machine learning inverts the abstraction**: instead of writing rules, you provide labeled examples and let an algorithm learn the rules. This generalizes to new patterns automatically when the model is retrained on new data.

3. **Don't skip the rule-based phase**: building a rule-based system first is not a detour — it produces domain knowledge and validated patterns that become your first feature set. The ML model inherits and extends this knowledge.

4. **The ML pipeline has fixed stages**: Data → Feature Engineering → Training → Inference. Each stage is a distinct engineering concern.

5. **Binary features are the simplest feature type**: True/False signals encoded as 1/0. They are a natural encoding for the kinds of conditions that appear in rule-based systems.

6. **The model output is a probability, not a label**: the conversion from probability to label requires a threshold, which is a policy parameter tunable for the specific cost tradeoffs of your application.

---

## Next Steps

- **Lesson 1.3**: Supervised Learning — formalizes the framework used in both price prediction (regression) and spam detection (classification). Introduces the taxonomy: **regression**, **classification**, and **ranking**.
- **To deepen understanding**:
  - Implement the rule-based spam filter in Python, then convert each rule to a binary feature.
  - Train a `LogisticRegression` or `DecisionTreeClassifier` (scikit-learn) on the feature matrix and observe which features receive the highest weights/importance scores.
  - Experiment with different classification thresholds and plot the precision-recall tradeoff (PR curve).

---

### Related Notes

[[ML_Zoomcamp_1_1]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]]
