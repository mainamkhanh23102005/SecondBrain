# ML Zoomcamp 1.1 — Introduction to Machine Learning

> [!info] Document Type
> **Type A — Theoretical/Conceptual.** This lecture introduces foundational Machine Learning concepts through a practical, real-world motivating example.

---

## 1. Tổng quan Tài liệu (Executive Summary)

This lecture opens ML Zoomcamp by defining Machine Learning through a concrete use case: **predicting the price of a used car on a classifieds website**. The core argument is that just as a human expert can assess a car's value from its characteristics (by learning patterns from historical data), an ML model can do the same — automatically and at scale. The lecture establishes the three foundational pillars of supervised ML: **features**, **target**, and **model**.

---

## 2. Trích xuất Trọng tâm (Zero-Loss Extraction)

### The Motivating Problem

| Scenario | Detail |
|---|---|
| Platform | Used car classifieds website (e.g., OLX/Avito equivalent) |
| User pain point | Sellers don't know how to price their car correctly |
| Risk of pricing too HIGH | No buyers — car doesn't sell |
| Risk of pricing too LOW | Seller loses potential profit ("leaving money on the table") |
| Current manual approach | Sellers browse similar ads and estimate manually |
| ML solution | Automatically suggest a price based on car characteristics |

---

### Core ML Terminology

| Term | Definition | Example in the Car Use Case |
|---|---|---|
| **Features** | All known information/characteristics about an object | Year, manufacturer, mileage, model, number of doors |
| **Target** | The variable we want to predict | Price |
| **Model** | The artifact that encapsulates learned patterns | A trained regression model that outputs a predicted price |
| **Training data** | Dataset of objects with known features AND target | Historical car listings with prices |
| **Prediction** | The model's output for new, unseen data | Estimated price for a car being listed now |

---

### The ML Workflow (Supervised Learning Pipeline)

```
[Raw Data: Cars with known prices]
         |
         v
[Features Matrix]  +  [Target Vector (Price)]
         |
         v
[Machine Learning Algorithm]  → TRAIN →  [Model]
         |
         v
[New Car (features only, no price known)]
         |
         v
[Model]  → PREDICT →  [Price Prediction]
```

**Step-by-step:**
1. Collect data about cars (features) and their known prices (target).
2. Feed features and target into an ML algorithm.
3. The algorithm trains a model by extracting statistical patterns.
4. For a new listing (no price known), input its features into the trained model.
5. The model outputs a predicted price.

---

### Application in Production (User-Facing Flow)

```
User fills out listing form
   → App extracts features (year, make, mileage, model, doors, etc.)
   → Features passed to trained ML Model
   → Model returns a predicted price
   → Price auto-filled into the form
   → User can adjust up or down as desired
```

---

## 3. Giải thích Cặn kẽ (Deep-Dive Explanations)

### Why use ML instead of just asking an expert?

An expert *can* price a car correctly — but only because they have already processed hundreds or thousands of data points throughout their career. They have, in essence, manually trained their own internal model. The key insight from this lecture is:

> **"If an expert can do this, so can a model."**

The difference is **scale and automation**. An expert is constrained by time and availability. An ML model, once trained, delivers instant predictions for millions of listings simultaneously. ML **replicates expert knowledge** and makes it available on demand — without requiring the expert to be present.

---

### Why is the prediction "correct on average" but not always exact?

> [!warning] Important Concept — Statistical vs. Exact Accuracy
> The model does **not** guarantee a perfectly accurate price for every individual car. It learns **statistical patterns** — the average relationship between features and price across all training examples.

- A 2010 Toyota Corolla with 120,000 km will have a range of real-world prices depending on condition, location, color, service history, and negotiation.
- The model captures the **average** price for that configuration of features, not every idiosyncratic case.
- This is acceptable for the use case: the goal is a *reasonable starting point*, not an infallible price.

This reflects a core property of supervised learning — models minimize **average** error (e.g., Mean Squared Error) across all training samples, not error on any single example.

---

### Why is the feature/target split so critical?

> [!info] Supervised Learning Logic
> During **training**, the model sees both features AND the target (price). This is what makes it **supervised** learning.
> During **inference** (prediction), the model only receives features — it must produce the target itself.

The split enforces the model to learn a mapping function `f(features) → target`. If the target is accidentally included as a feature during training, the model "cheats" — a failure known as **data leakage** — and will be useless in production where no target value exists.

---

### Analogy: The Human Expert vs. The ML Model

| Dimension | Human Expert | ML Model |
|---|---|---|
| Learning source | Years of market experience | Historical labeled dataset |
| Speed | Slow (manual analysis per car) | Instant (milliseconds per prediction) |
| Scale | One car at a time | Millions simultaneously |
| Consistency | Variable (fatigue, bias, mood) | Consistent given the same input |
| Explainability | High (can articulate reasoning) | Depends on model type (linear vs. deep) |
| Update mechanism | Continuous via lived experience | Periodic retraining on new data |

---

## 4. Tổng hợp & Mở rộng (Key Takeaways & Next Steps)

### Core Takeaways

1. **Machine Learning = Pattern Extraction from Data.** It is the process of automatically learning the mapping `f(features) → target` from a labeled dataset.
2. **Features are the inputs; target is the output.** This distinction is fundamental to every supervised learning problem.
3. **The trained model encapsulates learned patterns** and applies them to new, unseen data at a speed and scale no human expert can match.
4. **Predictions are statistically correct on average**, not guaranteed to be exact for every individual instance — this is an inherent property of statistical learning, not a flaw.
5. **ML solves the scaling problem of expert knowledge** — it replicates what an expert learns over years of experience, then makes that knowledge available instantly and at unlimited scale.

---

### Extended Thinking Questions

> [!info] Go Deeper
> 1. **What if features are incomplete or noisy?** If a seller forgets to enter mileage, or enters an incorrect manufacture year, how should the system handle missing or erroneous feature values before passing them to the model? This is the problem of **feature validation and imputation** — a critical data engineering concern in any real ML pipeline.
> 2. **How do we know when to retrain the model?** Car prices change over time due to inflation, market trends, and new model releases. A model trained on 2020 data may produce stale predictions by 2024. This leads to the concepts of **model drift monitoring** and **continuous training pipelines** — essential in production ML systems.

---

*Source: ML Zoomcamp — Session 1, Lesson 1.1 — Introduction to Machine Learning*
*Next: 1.2 — ML vs. Rule-Based Systems (Spam Detection example)*

---

### Related Notes

[[ML_Zoomcamp_1_2]] | [[ML_Zoomcamp_1_3]] | [[ML_Zoomcamp_1_4]] | [[ML_Zoomcamp_1_5]]
