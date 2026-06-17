# ML Zoomcamp — Session 2, Lesson 15: Using the Model

> [!info] Document Type
> **Type A — Applied ML / Data Engineering.** Synthesized from ML Zoomcamp Session 2 Lesson 15 (video transcript). Covers the final training protocol — merging train + validation into a full dataset and retraining — the test-set evaluation that confirms generalization, and the end-to-end single-car inference pipeline (dict → DataFrame → prepare_x → predict → exp).

---

## 1. Executive Summary

Lesson 2.15 completes the car price prediction project with two deliverables:

1. **Final model training.** The train and validation splits are merged into a single `df_full_train` dataset, and the model is retrained on this larger set with the confirmed best regularization parameter $r = 0.01$. This gives the final weights maximum signal — all non-test data is used.

2. **Deployment-style inference.** The trained model is applied to a single car represented as a Python dictionary (mimicking a real API request), demonstrating the complete prediction pipeline: `dict → pd.DataFrame → prepare_x → linear model → exp`. The test set RMSE matches the validation RMSE to three decimal places — confirming the model generalises rather than having overfit to the validation set.

The lesson closes the full ML lifecycle: data preparation → feature engineering → training → validation → tuning → final training → test evaluation → inference.

---

## 2. Zero-Loss Extraction

### 2.1 Why Retrain on Train + Validation Combined?

During development, the model was trained only on `df_train` to ensure that `df_val` remained an unbiased evaluation set. Now that all hyperparameter decisions are finalized, the validation set can be "spent" — merged with the training set to give the final model more data to learn from.

```
Development:   [df_train → fit model] [df_val → evaluate]  [df_test → held out]
Final model:   [df_full_train = df_train + df_val → fit]   [df_test → evaluate once]
```

More training data → better-estimated weights → better generalization (all else equal).

### 2.2 Merging DataFrames and Target Arrays

**DataFrames (pandas):**

```python
import pandas as pd

# Concatenate row-wise; reset_index avoids duplicate index values
df_full_train = pd.concat([df_train, df_val]).reset_index(drop=True)

print(len(df_full_train))   # ≈ 9500 rows (train + val combined)
```

> **Why `reset_index(drop=True)`?** After concatenation, the index inherits from both source DataFrames — so `df_val`'s rows still have their original (0, 1, 2, ...) indices, creating duplicates. `reset_index` assigns a clean sequential index (0, 1, ..., 9499). `drop=True` discards the old index rather than appending it as a column.

**Target arrays (NumPy):**

```python
import numpy as np

# np.concatenate works on 1-D arrays directly; no index issue
y_full_train = np.concatenate([y_train, y_val])

print(y_full_train.shape)   # (9500,)
```

### 2.3 Training the Final Model

```python
# Prepare full feature matrix
X_full_train = prepare_x(df_full_train)                          # shape: (9500, 44)

# Train with best regularization parameter
w0_final, w_final = train_linear_regression_regularized(
    X_full_train, y_full_train, r=0.01
)

print(f"Bias: {w0_final:.4f}")
print(f"Weights shape: {w_final.shape}")    # (44,)
```

### 2.4 Test-Set Evaluation

```python
# Prepare test features — same prepare_x function, same categories dict
X_test  = prepare_x(df_test)                                     # shape: (m_test, 44)
y_pred_test = w0_final + X_test.dot(w_final)

test_rmse = rmse(y_test, y_pred_test)
print(f"Test RMSE: {test_rmse:.4f}")
# Output: ≈ same as validation RMSE to 3 decimal places
```

**Interpretation:** Test RMSE ≈ Validation RMSE → the model **generalises well**. The performance seen during development was not a fluke or an artefact of overfitting to the validation set.

### 2.5 Single-Car Inference Pipeline

The real-world use case: a user submits a car's features (via an app or API), and the model returns a price estimate.

```python
# Step 1 — Simulate an incoming request as a Python dict
# (In production: parsed from JSON request body)
car = df_test.iloc[20].to_dict()   # pick car #20 from test set (unseen during training)

# Step 2 — Wrap in a single-row DataFrame (prepare_x expects a DataFrame)
df_car = pd.DataFrame([car])       # shape: (1, n_cols)

# Step 3 — Build the feature vector
X_car = prepare_x(df_car)          # shape: (1, 44)

# Step 4 — Predict log-price
log_price_pred = w0_final + X_car.dot(w_final)   # shape: (1,)
log_price_pred = log_price_pred[0]               # extract scalar

# Step 5 — Undo the log transformation to recover actual price
price_pred = np.exp(log_price_pred)
print(f"Predicted price: ${price_pred:,.0f}")

# Step 6 — Compare to the actual price (for evaluation only)
price_actual = np.exp(y_test[20])
print(f"Actual price:    ${price_actual:,.0f}")
# Output example: Predicted ~$37,000 vs Actual ~$32,000 — off by ~$5,000 (~16%)
```

### 2.6 Complete Final Pipeline Summary

```python
# ── 1. Merge data ──────────────────────────────────────────────────────────────
df_full_train = pd.concat([df_train, df_val]).reset_index(drop=True)
y_full_train  = np.concatenate([y_train, y_val])

# ── 2. Train final model ───────────────────────────────────────────────────────
X_full_train = prepare_x(df_full_train)
w0, w = train_linear_regression_regularized(X_full_train, y_full_train, r=0.01)

# ── 3. Evaluate on test set ────────────────────────────────────────────────────
X_test = prepare_x(df_test)
print(f"Test RMSE: {rmse(y_test, w0 + X_test.dot(w)):.4f}")

# ── 4. Predict for a single car ────────────────────────────────────────────────
car     = df_test.iloc[20].to_dict()
X_car   = prepare_x(pd.DataFrame([car]))
price   = np.exp(w0 + X_car.dot(w)[0])
print(f"Predicted: ${price:,.0f}")
```

### 2.7 RMSE Across All Splits

| Split | RMSE | Notes |
|---|---|---|
| Training (in-sample, L08) | ~0.76 | Biased — model was trained on this data |
| Validation (after L10 correction) | ~0.76 | Unbiased baseline |
| Validation (after age, L11) | ~0.51 | Feature engineering gain |
| Validation (after OHE + reg, L13/14) | ~0.50 | Categorical + regularization |
| **Test (final model, L15)** | **~0.50** | **Confirms generalization** |

---

## 3. Deep-Dive Explanations

### 3.1 Why Not Train on All Three Splits (Including Test)?

The test set must remain unseen during training to serve as an honest, unbiased estimate of the model's performance on future, truly new data. If test data were included in training:

- The model would have "seen" some of the data it is being evaluated on.
- Test RMSE would be optimistically biased.
- We would have no reliable estimate of real-world performance.

The test set is the **deployment proxy** — it simulates data that does not yet exist when the model is trained.

### 3.2 Why Test RMSE ≈ Validation RMSE Is a Good Sign

If test RMSE were significantly worse than validation RMSE, it would suggest:

- **Validation set leakage:** hyperparameter choices were implicitly over-fitted to the validation distribution.
- **Distribution shift:** validation and test sets do not represent the same data distribution.
- **Too many hyperparameter iterations:** the more often you evaluate on the validation set and change hyperparameters, the more you inadvertently fit to it.

Agreement between validation and test RMSE indicates the validation set was used responsibly — decisions were made based on general principles (regularization magnitude, feature engineering) rather than overfitting to specific validation artefacts.

### 3.3 The `pd.DataFrame([dict])` Pattern for Inference

The `prepare_x` function expects a pandas DataFrame. In production, incoming data typically arrives as a JSON object (parsed into a Python dict). The bridge is:

```python
# Request arrives as:
request = {"make": "toyota", "year": 2015, "engine_hp": 185, ...}

# Convert to single-row DataFrame for prepare_x:
df_request = pd.DataFrame([request])   # note: list of one dict
X_request  = prepare_x(df_request)    # shape: (1, 44)
```

Wrapping the dict in a list `[request]` is required because `pd.DataFrame` interprets a dict as `{column: [values]}`, but a *list of dicts* as `[{row1_col: val, ...}, ...]`. A list of one dict produces a single-row DataFrame.

### 3.4 Undoing the Log Transformation

The model predicts $\hat{y} = \log(\text{price} + 1)$. To recover the actual price:

$$\text{price} = e^{\hat{y}} - 1 \approx e^{\hat{y}} \quad (\text{since } +1 \text{ is negligible at car price scale})$$

In code: `np.exp(log_price_pred)`. This reverses the log transform applied during data preparation in Lesson 2.3. For a prediction of $\hat{y} = 10.6$:

$$\text{price} = e^{10.6} \approx \$40{,}000$$

The $-1$ correction (for the `log(price + 1)` transform) is negligible at these price scales and is often omitted in practice.

### 3.5 Why the Final Model Uses Train + Val but the Same $r$

One might ask: with more data, should $r$ be re-tuned? In principle yes — with more data, the model is less prone to overfitting and can tolerate a lower $r$. In practice:

- The change from `m_train` to `m_train + m_val` is modest (~15–20% more rows).
- The selected $r = 0.01$ was chosen primarily to stabilize the near-singular Gram matrix, not to prevent classical overfitting. This need does not change with slightly more data.
- Re-running the grid search would require holding out another validation set — unnecessary complexity at this stage.

For production systems, a proper cross-validation procedure would re-tune $r$ on the full pre-test dataset.

---

## 4. Key Takeaways & Next Steps

| Concept | Rule |
|---|---|
| Full train | `pd.concat([df_train, df_val]).reset_index(drop=True)` — merge after all decisions are final |
| `reset_index(drop=True)` | Prevents duplicate index values after concatenation |
| `np.concatenate` | Merges 1-D NumPy target arrays (no index issue) |
| Test set touched once | Only after all hyperparameter decisions; result is the honest final score |
| Test RMSE ≈ Val RMSE | Confirms generalization — model did not overfit to validation distribution |
| Single-car inference | `dict → pd.DataFrame([dict]) → prepare_x → dot → exp` |
| Undo log transform | `np.exp(log_price_pred)` recovers actual price from log-price prediction |

**Next step:** Lesson 2.16 — Session 2 project summary, key concepts recap, and preview of Session 3 (classification with scikit-learn).

---

## Appendix: Notation Summary

| Notation | Meaning |
|---|---|
| `df_full_train` | Combined train + validation DataFrame |
| `y_full_train` | Combined train + validation target array |
| `pd.concat([a, b]).reset_index(drop=True)` | Row-wise merge with clean sequential index |
| `np.concatenate([a, b])` | 1-D array merge (equivalent to pandas concat for arrays) |
| `w0_final`, `w_final` | Weights of the final model trained on full training data |
| `y_pred = w0 + X.dot(w)` | Linear model inference formula |
| `np.exp(log_pred)` | Inverse of log transform — recovers raw price |
| Test RMSE | Single honest evaluation of the deployed model's expected real-world performance |

---

## Graph View Links

**Previous:** [[MLZ_S2_L14_Tuning_the_Model]]
**Next:** [[MLZ_S2_L16_Session_2_Summary]]
**Hub:** [[Machine Learning (github datazoomcamp)]]
