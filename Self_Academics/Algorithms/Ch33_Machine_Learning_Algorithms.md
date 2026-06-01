# Chapter 33 — Machine Learning Algorithms

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #machine-learning #clustering #online-learning #gradient-descent

---

## Executive Summary

Chapter 33 brings a rigorous algorithmic lens to three core machine-learning problems. Unlike most of the textbook, these algorithms come with *expected* or *probabilistic* guarantees rather than worst-case deterministic bounds, and performance is measured against a *comparator* (optimal cluster assignment, best expert, global minimizer) rather than an adversarial input.

| Section | Problem | Algorithm | Guarantee |
|---------|---------|-----------|-----------|
| §33.1 | Clustering | Lloyd's (k-means) | Monotone decrease of objective; convergence to local minimum |
| §33.2 | Online prediction | WEIGHTED-MAJORITY | $m(T') \le (1+2\gamma)\,m_i(T') + \frac{2\ln n}{\gamma}$ |
| §33.3 | Convex optimization | Gradient Descent | $f(\bar{x}) - f(x^*) \le \frac{RL}{\sqrt{T}}$ |

**Overarching theme:** Each algorithm is iterative, each iteration is computationally cheap, and convergence is guaranteed by a *potential function* argument (Lloyd's) or a *Lyapunov / regret* bound (WEIGHTED-MAJORITY, gradient descent).

---

## Zero-Loss Extraction

### §33.1 — Clustering (k-Means / Lloyd's Algorithm)

**Problem:** Given $n$ points $x_1, \ldots, x_n \in \mathbb{R}^d$ and integer $k$, partition them into $k$ clusters $S_1, \ldots, S_k$ with centers $c_1, \ldots, c_k$ to minimize:
$$f(S, C) = \sum_{j=1}^k \sum_{x \in S_j} \Delta(x, c_j), \qquad \Delta(x, y) = \|x - y\|^2$$

**Theorem 33.1 (Centroid theorem):** The center minimizing $\sum_{x \in S} \Delta(x, c)$ over a fixed cluster $S$ is the centroid $\bar{x}_S = \frac{1}{|S|}\sum_{x \in S} x$.

**Theorem 33.2 (Nearest-center rule):** For fixed centers $C = \{c_1, \ldots, c_k\}$, the optimal assignment puts each $x_i$ in the cluster whose center is nearest: $S_j = \{x_i : j = \arg\min_\ell \Delta(x_i, c_\ell)\}$.

**Algorithm: LLOYD (k-means)**

```
LLOYD(x₁, …, xₙ, k)
1  choose initial centers c₁, …, cₖ arbitrarily
2  repeat
3      // Assignment step (Theorem 33.2)
4      for j = 1 to k
5          Sⱼ = {xᵢ : j = argminₗ Δ(xᵢ, cₗ)}
6      // Update step (Theorem 33.1)
7      for j = 1 to k
8          cⱼ = (1/|Sⱼ|) Σ_{x ∈ Sⱼ} x    // centroid
9  until assignments unchanged
10 return S₁, …, Sₖ, c₁, …, cₖ
```

- **Running time per iteration:** $O(Tdkn)$ where $T$ = number of iterations, $d$ = dimension, $k$ = clusters.
- **Termination:** $f(S, C)$ strictly decreases after every non-trivial iteration (since both steps can only decrease or maintain the objective, and the number of distinct assignments is finite: $k^n$). Hence Lloyd terminates.
- **Caveat:** Converges to a *local* minimum, not necessarily global. Performance depends on initialization; k-means++ initialization gives an $O(\log k)$-competitive expected solution.

---

### §33.2 — Online Learning: WEIGHTED-MAJORITY

**Setting:** At each round $t = 1, 2, \ldots$:
1. Algorithm predicts a binary label $\hat{y}_t \in \{0, 1\}$.
2. Environment reveals true label $y_t$.
3. Algorithm observes which of $n$ *experts* were correct.

**Algorithm: WEIGHTED-MAJORITY**

```
WEIGHTED-MAJORITY(γ)    // 0 < γ ≤ 1/2
1  wᵢ = 1 for i = 1 to n     // initial weights
2  for each round t
3      predict majority vote weighted by wᵢ
4      observe true label yₜ
5      for each expert i that was wrong
6          wᵢ = wᵢ · (1 − γ)
```

- **Prediction:** $\hat{y}_t = 1$ if $\sum_{i: \text{predicts 1}} w_i \ge \frac{1}{2}\sum_i w_i$, else 0.

**Lemma 33.3 (Warm-up — perfect expert exists):** If some expert $i^*$ makes no mistakes, WEIGHTED-MAJORITY makes at most $\lceil \log_2 n \rceil / \gamma$ mistakes... (More precisely: each algorithm mistake means the weighted majority was wrong, so at least half the total weight supported the wrong side, causing total weight to drop by factor $(1-\gamma/2)$... see Theorem 33.4.)

**Theorem 33.4 (Main bound):** Let $m(T')$ = algorithm's mistakes in $T'$ rounds, $m_i(T')$ = mistakes of expert $i$. For any expert $i$:
$$m(T') \le \frac{(1 + 2\gamma)\, m_i(T') + 2\ln n}{1}$$

More precisely:
$$m(T') \le (1 + 2\gamma)\, m_i(T') + \frac{2\ln n}{\gamma}$$

**Corollary 33.5 (Bound vs. best expert):** Let $m^*(T') = \min_i m_i(T')$ (best expert's mistake count):
$$m(T') \le (1 + 2\gamma)\, m^*(T') + \frac{2\ln n}{\gamma}$$

The $\frac{2\ln n}{\gamma}$ term is the *overhead* for not knowing which expert is best. As $T' \to \infty$, the per-round mistake rate converges to $(1+2\gamma)$ times the best expert's rate — near-optimal for small $\gamma$.

**Proof sketch:** Track total weight $W = \sum_i w_i$. Initially $W = n$. Each algorithm mistake means $\ge W/2$ weight is on wrong side, so $W$ decreases by factor $\ge (1-\gamma/2)$... The weight of any single expert $i$ after $m_i$ mistakes is $w_i = (1-\gamma)^{m_i}$. Since $W \ge w_i$:
$$n \cdot (1-\gamma/2)^{m(T')} \ge (1-\gamma)^{m_i(T')}$$
Taking logs and using $\ln(1-x) \ge -x - x^2$ gives the bound.

---

### §33.3 — Gradient Descent

**Problem:** Minimize a convex, differentiable function $f : \mathbb{R}^d \to \mathbb{R}$ over a convex set, or unconstrained.

**Parameters:**
- $R$: bound on distance from start to optimum, $\|x^{(0)} - x^*\| \le R$.
- $L$: Lipschitz constant for the gradient, $\|\nabla f(x)\| \le L$ for all $x$.
- $T$: number of iterations.
- $\gamma$: step size (learning rate).

**Algorithm: GRADIENT-DESCENT**

```
GRADIENT-DESCENT(f, x⁽⁰⁾, γ, T)
1  for t = 0 to T − 1
2      x⁽ᵗ⁺¹⁾ = x⁽ᵗ⁾ − γ · (∇f)(x⁽ᵗ⁾)
3  return x̄ = (1/T) Σₜ x⁽ᵗ⁾   // average iterate
```

**Lemma 33.6 (One-step progress):** For any $x^*$:
$$\|x^{(t+1)} - x^*\|^2 = \|x^{(t)} - x^*\|^2 - 2\gamma\langle\nabla f(x^{(t)}),\, x^{(t)} - x^*\rangle + \gamma^2\|\nabla f(x^{(t)})\|^2$$

**Lemma 33.7 (Convexity lower bound):** For convex $f$:
$$f(x^*) \ge f(x^{(t)}) + \langle\nabla f(x^{(t)}),\, x^* - x^{(t)}\rangle$$
i.e., $\langle\nabla f(x^{(t)}),\, x^{(t)} - x^*\rangle \ge f(x^{(t)}) - f(x^*)$.

**Theorem 33.8 (Convergence rate):** With step size $\gamma = R/(L\sqrt{T})$:
$$f(\bar{x}) - f(x^*) \le \frac{RL}{\sqrt{T}}$$

where $\bar{x} = \frac{1}{T}\sum_{t=0}^{T-1} x^{(t)}$.

*To achieve error $\le \varepsilon$: set $T = (RL/\varepsilon)^2$ iterations. Each iteration costs one gradient evaluation.*

**Lemma 33.9 (Telescoping sum):** Combining Lemmas 33.6 and 33.7 and summing over $t = 0, \ldots, T-1$:
$$\sum_{t=0}^{T-1} \bigl(f(x^{(t)}) - f(x^*)\bigr) \le \frac{\|x^{(0)}-x^*\|^2}{2\gamma} + \frac{\gamma L^2 T}{2} \le \frac{R^2}{2\gamma} + \frac{\gamma L^2 T}{2}$$

Dividing by $T$ and applying Jensen's inequality ($f(\bar{x}) \le \frac{1}{T}\sum f(x^{(t)})$ by convexity):
$$f(\bar{x}) - f(x^*) \le \frac{R^2}{2\gamma T} + \frac{\gamma L^2}{2}$$

Optimal $\gamma = R/(L\sqrt{T})$ balances the two terms, each equaling $\frac{RL}{2\sqrt{T}}$.

---

## Deep-Dive Explanations

### Why Lloyd's Algorithm Always Terminates

Each iteration strictly decreases $f(S, C)$ unless the assignment is already stable (no point changes cluster). The key is that the two steps — assignment and centroid update — *cannot increase* the objective:
- Assignment: assigning each point to its nearest center can only decrease or maintain total squared distance.
- Centroid update: replacing the center by the mean can only decrease the intra-cluster sum (Theorem 33.1).

Since the number of distinct assignment configurations is $k^n$ (finite) and $f$ strictly decreases at each non-trivial step, the algorithm terminates in at most $k^n$ iterations (in practice, far fewer).

### Regret vs. Absolute Mistake Bounds

WEIGHTED-MAJORITY gives a *relative* bound: algorithm mistakes $\le (1+2\gamma) \cdot \text{best expert's mistakes} + O(\log n / \gamma)$. This is a **regret** bound — performance relative to the best comparator in hindsight. The algorithm need not know which expert is best before seeing the data. For $\gamma = 1/2$ and $T$ rounds, the overhead is $O(\log n)$ mistakes total, regardless of $T$.

### Gradient Descent: The $1/\sqrt{T}$ Rate is Tight

For Lipschitz convex functions, the $O(1/\sqrt{T})$ convergence rate is *information-theoretically optimal*: no first-order method (using only gradient evaluations) can do better in the worst case. Faster rates require additional assumptions:
- **Strongly convex** $f$: rate improves to $O(1/T)$.
- **Smooth** $f$ (bounded Hessian): rate improves to $O(1/T^2)$ with Nesterov acceleration.

---

## Key Takeaways & Next Steps

| Algorithm | Problem | Convergence Guarantee | Per-Iteration Cost |
|-----------|---------|----------------------|-------------------|
| Lloyd's (k-means) | Clustering | Terminates (local min) | $O(dkn)$ |
| WEIGHTED-MAJORITY | Online prediction | $m \le (1+2\gamma)m^* + 2\ln n/\gamma$ | $O(n)$ |
| Gradient Descent | Convex minimization | $f(\bar{x})-f(x^*) \le RL/\sqrt{T}$ | $O(d)$ + 1 gradient eval |

**Key principles:**
1. **Potential functions** (Lloyd's) and **weight functions** (WEIGHTED-MAJORITY) track progress toward optimality.
2. **Averaging iterates** (gradient descent) stabilizes convergence when individual iterates oscillate.
3. **Regret bounds** (WEIGHTED-MAJORITY) are stronger than worst-case bounds — they adapt to the difficulty of the data stream.
4. **Convexity** is the key structural assumption enabling gradient descent's guarantees; without it, only local convergence can be shown.

**Next steps:**
- k-means++ initialization: $O(\log k)$ competitive ratio in expectation.
- Stochastic gradient descent (SGD): replace $\nabla f(x)$ with an unbiased estimate for large-scale problems.
- Online-to-batch conversion: run WEIGHTED-MAJORITY offline to get PAC-learning guarantees.
- Chapter 34 shifts to complexity theory — proving that many optimization problems cannot be solved efficiently.

---

### Navigation

**Previous:** [[Ch32_String_Matching]]  
**Next:** [[Ch34_NP_Completeness]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
