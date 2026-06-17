# ML Zoomcamp — Session 2, Lesson 14: Tuning the Model

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 14 (video transcript). Covers hyperparameter search for the regularization parameter $r$: iterating over candidate values, reading the bias term and RMSE as diagnostic signals, selecting the optimal $r = 0.01$, retraining the final model, and setting up the test-set evaluation in Lesson 2.15.

---

## 1. Executive Summary

Lesson 2.14 closes the model-development loop by finding the best value of the regularization parameter $r$ introduced in Lesson 2.13. The approach is straightforward: **grid search** — iterate over a hand-picked list of candidate values, train a model for each, measure validation RMSE, and pick the winner.

Two diagnostic signals are monitored simultaneously:

1. **Validation RMSE** — the primary metric: lower is better.
2. **Bias term $w_0$** — a secondary signal: an exploding $w_0$ (e.g., $10^6$) indicates the model is still numerically unstable despite regularization.

The search confirms $r = 0.01$ as the optimal value: RMSE is near its minimum, the bias is well-behaved, and the model has not yet started to degrade from over-regularization. The final model is retrained with $r = 0.01$ and is ready for test-set evaluation.

This lesson demonstrates a general ML workflow pattern: **hyperparameter search on the validation set → select best → retrain final model → evaluate once on test set**. The test set is never touched until the final evaluation to preserve its role as an unbiased holdout.

---

## 2. Zero-Loss Extraction

### 2.1 Grid Search Setup

Candidate values for $r$ span several orders of magnitude — from 0 (unregularized) to large values that force heavy shrinkage:

```python
# Candidates: log-spaced to probe a wide range efficiently
r_candidates = [0, 0.001, 0.01, 0.1, 1, 10]
```

The list is intentionally coarse; the goal is to identify the right order of magnitude, not to over-engineer precision.

### 2.2 Grid Search Loop

```python
X_train = prepare_x(df_train)
X_val   = prepare_x(df_val)

print(f"{'r':>8}  {'w0':>12}  {'RMSE':>8}")
print("-" * 36)

for r in r_candidates:
    w0, w  = train_linear_regression_regularized(X_train, y_train, r=r)
    y_pred = w0 + X_val.dot(w)
    score  = rmse(y_val, y_pred)
    print(f"{r:8.4f}  {w0:12.4f}  {score:8.4f}")
```

### 2.3 Results Table

| $r$ | Bias $w_0$ | Validation RMSE | Interpretation |
|---|---|---|---|
| 0 | ~$10^{6}$ (huge) | ~41 | Unregularized — singular Gram, exploded |
| 0.001 | Large | High | Still nearly singular |
| **0.01** | **Reasonable** | **~0.50** | **Sweet spot — stable and accurate** |
| 0.1 | Smaller | Slightly worse | Mild over-regularization begins |
| 1 | Small | Noticeably worse | Significant shrinkage — underfitting |
| 10 | Very small | Much worse | Heavy underfitting — weights near zero |

> **Key pattern:** RMSE is high at both extremes and minimized at $r = 0.01$. This U-shaped behaviour is the signature of the bias-variance trade-off.

### 2.4 Selecting the Best $r$

```python
best_r = 0.01
```

The selection criterion is the lowest validation RMSE among values where the bias $w_0$ is also within a reasonable numerical range (not exploded). Both conditions are met at $r = 0.01$.

### 2.5 Retraining the Final Model

After selecting $r$, retrain on the full training set with the chosen hyperparameter:

```python
# Final model — trained with the selected regularization strength
w0_final, w_final = train_linear_regression_regularized(X_train, y_train, r=best_r)

# Confirm performance on validation set
y_pred_val = w0_final + X_val.dot(w_final)
print(f"Final Validation RMSE: {rmse(y_val, y_pred_val):.4f}")
# Output: ≈ 0.50
```

This final model is NOT re-evaluated on the test set yet — that happens in Lesson 2.15.

### 2.6 Model Development RMSE Progression Summary

| Lesson | Change Made | Validation RMSE |
|---|---|---|
| 2.8 (baseline) | 5 numerical features, train-set RMSE | ~0.76 (train-set — biased) |
| 2.10 | Correct validation-set RMSE | ~0.76 |
| 2.11 | + age feature | ~0.51 |
| 2.12 | + OHE categoricals (no regularization) | ~41 (exploded) |
| 2.13 | + regularization ($r=0.01$) | ~0.50 |
| **2.14** | **Tuned $r=0.01$ confirmed** | **~0.50** |

---

## 3. Deep-Dive Explanations

### 3.1 Why Grid Search on the Validation Set (Not the Test Set)

The validation set is used to make decisions — in this case, which $r$ to choose. Every time we pick $r$ based on validation RMSE, we are implicitly fitting to the validation set. This is acceptable: the validation set is designed for this purpose.

The test set is held out precisely because we cannot use it for decision-making. If we optimized $r$ using test RMSE and then reported that test RMSE as our final score, we would be reporting an optimistically biased number — the model was "tuned" to perform well on it.

**The rule:** Test set touched exactly **once**, after all hyperparameter decisions are finalized. Its RMSE is the published, honest performance estimate.

### 3.2 Interpreting the Bias Term as a Diagnostic

The bias $w_0$ is the model's prediction when all features are zero. In the log-price domain:

- A well-trained model should have $w_0$ in roughly the same range as the target values (8–12).
- $w_0 \approx 10^6$ signals that the weights are numerically unstable — the model is trying to compensate for enormous feature weights by setting an enormous baseline.
- $w_0 \approx 0$ with $r$ very large signals the model has been over-regularized: all weights, including the bias, are driven toward zero.

Monitoring $w_0$ alongside RMSE provides an early warning: if RMSE looks acceptable but $w_0$ is still large, the model may be numerically unstable in ways that don't immediately manifest in the RMSE.

### 3.3 Why Log-Spacing the $r$ Candidates

The candidates $\{0, 0.001, 0.01, 0.1, 1, 10\}$ are logarithmically spaced (factors of 10 apart). This is standard practice for regularization hyperparameters because:

- The effect of regularization scales multiplicatively, not additively. Going from $r=0.001$ to $r=0.01$ has a much larger effect than going from $r=9$ to $r=10$.
- Log-spacing probes the full range of behavior (from near-singular to heavily regularized) with a small number of evaluations.
- Once the optimal order of magnitude is identified (here: $10^{-2}$), a finer search within $[0.001, 0.1]$ could be conducted if needed.

### 3.4 Could We Add More Training Data Instead of Regularizing?

Regularization is needed because **near-collinear features destabilize the Gram matrix inversion**, not because the dataset is too small. Adding more training data rows would not fix the collinearity — two perfectly duplicate OHE columns remain perfectly collinear regardless of how many rows you have. Only adding $rI$ to the Gram matrix addresses the algebraic root cause.

More data does reduce variance in a different sense — reducing overfitting to noise — but regularization is the correct tool for the matrix singularity problem.

### 3.5 The Role of This Lesson in the Full ML Workflow

This lesson completes the **inner loop** of the ML development cycle:

```
Build features (L2.11–L2.12)
    → Evaluate on validation set (L2.10)
        → Identify failure mode (L2.12: RMSE explosion)
            → Fix with regularization (L2.13)
                → Tune hyperparameter on validation (L2.14) ← HERE
                    → Retrain final model
                        → Evaluate once on test set (L2.15)
```

Every iteration of this loop produces a concrete RMSE improvement. The validation set is the compass; the test set is the finish line.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Grid search | Try a log-spaced set of $r$ values; pick the one with lowest validation RMSE |
| Bias $w_0$ as diagnostic | Exploded $w_0$ → still numerically unstable; near-zero $w_0$ → over-regularized |
| Best $r = 0.01$ | Lowest validation RMSE; bias is well-behaved; no degradation yet |
| Test set discipline | Never use test RMSE to select hyperparameters — touch it only once |
| Log-spacing $r$ | Multiplicative effect of regularization demands log-spaced candidates |
| Retrain before evaluating | Always retrain with best $r$ before final test-set evaluation |

**Next step:** Lesson 2.15 — evaluate the final model on the test set, interpret the result, and conclude the Session 2 project.

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| $r$ | Regularization hyperparameter — strength of L2 penalty |
| `r_candidates` | `[0, 0.001, 0.01, 0.1, 1, 10]` — log-spaced candidate values |
| Grid search | Exhaustive evaluation of all candidate $r$ values on validation set |
| $w_0$ | Bias term — diagnostic: should be within plausible target range |
| Best $r$ | $r = 0.01$ — minimizes validation RMSE with stable bias |
| Final model | `train_linear_regression_regularized(X_train, y_train, r=0.01)` |
| Test set | Evaluated exactly once after all hyperparameter decisions are final |

---

## Graph View Links

**Previous:** [[MLZ_S2_L13_Regularization]]
**Next:** [[MLZ_S2_L15_Using_the_Model]]
**Hub:** [[Machine Learning (github datazoomcamp)]]
