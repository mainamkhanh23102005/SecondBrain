# Chapter 35 — Approximation Algorithms

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #approximation #NP-completeness #optimization

---

## Executive Summary

Many practically important problems are NP-complete, yet they cannot be abandoned. Chapter 35 presents **polynomial-time approximation algorithms** — algorithms that return *near-optimal* solutions with a provable *approximation ratio* $\rho(n)$, meaning the returned cost $C$ and optimal cost $C^*$ satisfy:
$$\max\!\left(\frac{C}{C^*},\frac{C^*}{C}\right) \le \rho(n)$$

Five problems are covered: **vertex cover** (2-approximation), **TSP with triangle inequality** (2-approximation), **set covering** ($O(\log|X|)$-approximation), **MAX-3-CNF satisfiability** (randomized 8/7-approximation), **weighted vertex cover via LP** (2-approximation), and **subset sum** (FPTAS).

Key vocabulary:
- **$\rho(n)$-approximation algorithm**: always within factor $\rho(n)$ of optimal.
- **PTAS** (polynomial-time approximation scheme): for any fixed $\varepsilon > 0$, runs in time polynomial in $n$ and returns a $(1+\varepsilon)$-approximation.
- **FPTAS** (fully polynomial-time approximation scheme): running time polynomial in *both* $n$ and $1/\varepsilon$.

---

## Zero-Loss Extraction

### §35.1 — Vertex-Cover Problem

**Problem:** Given undirected graph $G=(V,E)$, find a minimum vertex cover $V' \subseteq V$ (every edge has at least one endpoint in $V'$).

**Algorithm: APPROX-VERTEX-COVER**

```
APPROX-VERTEX-COVER(G)
1  C = ∅
2  E' = G.E
3  while E' ≠ ∅
4      let (u,v) be an arbitrary edge of E'
5      C = C ∪ {u, v}
6      remove from E' every edge incident on u or v
7  return C
```

- **Running time:** $O(V + E)$
- **Theorem 35.1:** APPROX-VERTEX-COVER is a polynomial-time **2-approximation** algorithm.
- **Proof sketch:** Let $A$ = set of edges chosen in line 4. $A$ is a *maximal matching* (no two edges in $A$ share an endpoint). Any vertex cover $C^*$ needs $\ge |A|$ vertices, so $|C^*| \ge |A|$. The algorithm adds exactly $2|A|$ vertices, giving $|C| = 2|A| \le 2|C^*|$.

**Exercises highlight:** The greedy "highest-degree vertex" heuristic does *not* achieve ratio 2 (Exercise 35.1-3 asks for a counterexample using bipartite graphs with variable right-side degree).

---

### §35.2 — Traveling-Salesperson Problem

**Input:** Complete undirected graph $G=(V,E)$ with nonneg. integer costs $c(u,v)$. Find minimum-cost Hamiltonian cycle (tour).

#### With Triangle Inequality

The cost function satisfies $c(u,w) \le c(u,v) + c(v,w)$ for all $u,v,w \in V$.

**Algorithm: APPROX-TSP-TOUR**

```
APPROX-TSP-TOUR(G, c)
1  select a root vertex r ∈ G.V
2  compute minimum spanning tree T for G from r using MST-PRIM(G, c, r)
3  let H = list of vertices in preorder tree walk of T
4  return the Hamiltonian cycle H
```

- **Running time:** $\Theta(V^2)$ (with simple MST-PRIM).
- **Theorem 35.2:** When triangle inequality holds, APPROX-TSP-TOUR is a polynomial-time **2-approximation** algorithm.
- **Proof sketch:**
  1. Deleting any edge from optimal tour $H^*$ gives a spanning tree, so $w(T) \le c(H^*)$.
  2. Full walk $W$ traverses every edge of $T$ twice: $c(W) = 2w(T) \le 2c(H^*)$.
  3. Triangle inequality allows "shortcutting" repeated vertices without increasing cost: $c(H) \le c(W) \le 2c(H^*)$.

#### Without Triangle Inequality

**Theorem 35.3:** If $P \ne NP$, then for any constant $\rho \ge 1$, no polynomial-time $\rho$-approximation algorithm exists for the general TSP.

**Proof technique (key idea):** Reduction from Hamiltonian-cycle problem. Construct TSP instance where edges in $G$ cost 1 and edges *not* in $G$ cost $\rho|V|+1$. A Hamiltonian cycle exists iff optimal tour costs $|V|$; otherwise it costs $> \rho|V|$. A $\rho$-approximation algorithm would solve HC in polynomial time, contradicting $P \ne NP$.

---

### §35.3 — Set-Covering Problem

**Input:** Finite set $X$, family $\mathcal{F}$ of subsets covering $X$. Find minimum-cardinality subfamily $C \subseteq \mathcal{F}$ that covers all of $X$.

**Algorithm: GREEDY-SET-COVER**

```
GREEDY-SET-COVER(X, F)
1  U₀ = X
2  C = ∅
3  i = 0
4  while Uᵢ ≠ ∅
5      select S ∈ F maximizing |S ∩ Uᵢ|
6      Uᵢ₊₁ = Uᵢ − S
7      C = C ∪ {S}
8      i = i + 1
9  return C
```

- **Running time:** $O(|X| \cdot |\mathcal{F}| \cdot (|X| + |\mathcal{F}|))$; a linear-time implementation exists (Exercise 35.3-3).
- **Theorem 35.4:** GREEDY-SET-COVER is a polynomial-time $O(\log|X|)$-approximation algorithm.
- **Proof sketch:** Let $k = |C^*|$. After $i$ iterations, $|U_i| \le |X|(1 - 1/k)^i \le |X| \cdot e^{-i/k}$. Setting $|U_i| < 1$ requires $i > k \ln|X|$, so the algorithm runs at most $k\lceil \ln|X| \rceil$ iterations: $|C| \le |C^*| \lceil \ln|X| \rceil$.

---

### §35.4 — Randomization and Linear Programming

#### Randomized Approximation: MAX-3-CNF Satisfiability

**Problem:** Given $m$ clauses, each with exactly 3 distinct literals (no variable appears with its negation in the same clause), maximize satisfied clauses.

**Algorithm:** Set each variable independently to 1 w.p. $\frac{1}{2}$ and 0 w.p. $\frac{1}{2}$.

- **Theorem 35.5:** This randomized algorithm is a **randomized 8/7-approximation**.
- **Proof:** $\Pr[\text{clause } i \text{ not satisfied}] = (1/2)^3 = 1/8$, so $\Pr[\text{clause } i \text{ satisfied}] = 7/8$. $E[\text{satisfied clauses}] = 7m/8$. Ratio: $m / (7m/8) = 8/7$.

#### LP-Based Approximation: Weighted Vertex Cover

**Problem:** Find minimum-weight vertex cover in $G=(V,E)$ where vertex $v$ has weight $w(v)$.

**LP relaxation** (of the 0-1 integer program):

$$\text{minimize } \sum_{v \in V} w(v)\, x(v)$$
$$\text{subject to: } x(u) + x(v) \ge 1 \quad \forall (u,v) \in E$$
$$0 \le x(v) \le 1 \quad \forall v \in V$$

**Algorithm: APPROX-MIN-WEIGHT-VC**

```
APPROX-MIN-WEIGHT-VC(G, w)
1  C = ∅
2  compute x, optimal solution to LP relaxation
3  for each vertex v ∈ V
4      if x(v) ≥ 1/2
5          C = C ∪ {v}
6  return C
```

- **Theorem 35.6:** APPROX-MIN-WEIGHT-VC is a polynomial-time **2-approximation** for the minimum-weight vertex-cover problem.
- **Proof sketch:** For any edge $(u,v)$: $x(u)+x(v) \ge 1 \Rightarrow$ at least one rounded to $\ge 1/2$, so every edge is covered. Weight: $w(C) = \sum_{x(v)\ge 1/2} w(v) \le 2\sum_v w(v)x(v) = 2z^* \le 2w(C^*)$.

---

### §35.5 — Subset-Sum Problem (FPTAS)

**Problem:** Given set $S = \{x_1,\ldots,x_n\}$ of positive integers and target $t$, find a subset whose sum is as large as possible but $\le t$.

#### Exact Algorithm: EXACT-SUBSET-SUM

```
EXACT-SUBSET-SUM(S, n, t)
1  L₀ = ⟨0⟩
2  for i = 1 to n
3      Lᵢ = MERGE-LISTS(Lᵢ₋₁, Lᵢ₋₁ + xᵢ)
4      remove from Lᵢ every element > t
5  return max element of Lₙ
```

- $L_i$ = sorted list of all sums of subsets of $\{x_1,\ldots,x_i\}$ that do not exceed $t$.
- Exponential in general ($|L_i|$ can reach $2^i$); polynomial if $t$ is polynomial in $|S|$.

#### Approximation Scheme: APPROX-SUBSET-SUM

**Key idea — trimming:** Remove elements from list $L$ by $\delta$ such that for every removed $y$, some remaining $z$ satisfies $y/(1+\delta) \le z \le y$.

```
TRIM(L, δ)
1  let m = length of L
2  L' = ⟨y₁⟩
3  last = y₁
4  for i = 2 to m
5      if yᵢ > last · (1 + δ)   // yᵢ ≥ last since L is sorted
6          append yᵢ to L'
7          last = yᵢ
8  return L'
```

```
APPROX-SUBSET-SUM(S, n, t, ε)
1  L₀ = ⟨0⟩
2  for i = 1 to n
3      Lᵢ = MERGE-LISTS(Lᵢ₋₁, Lᵢ₋₁ + xᵢ)
4      Lᵢ = TRIM(Lᵢ, ε/2n)
5      remove from Lᵢ every element > t
6  let z* = max value in Lₙ
7  return z*
```

- **Trimming parameter:** $\delta = \varepsilon / 2n$.
- **Theorem 35.7:** APPROX-SUBSET-SUM is a **FPTAS** for the subset-sum problem.
- **Approximation bound:** $y^*/z^* \le (1 + \varepsilon/2n)^n \le e^{\varepsilon/2} \le 1 + \varepsilon$ (using the fact that $e^{\varepsilon/2} \le 1+\varepsilon$ for $0 < \varepsilon < 1$ which follows from $e^x \le 1+2x$ for $0 < x < 1$... more precisely by the series expansion combined with $\varepsilon < 1$).
- **List size after trimming:** At most $\lfloor \log_{1+\delta} t \rfloor + 2 = O\!\left(\frac{2n}{\varepsilon} \log t\right)$ — polynomial in $n$ and $1/\varepsilon$.

**Worked example:** $S = \langle 104, 102, 201, 101\rangle$, $t=308$, $\varepsilon=0.40$, $\delta=0.05$. After 4 iterations and trimming, $z^* = 302$ vs. optimal $307$ (error $< 2\% \ll 40\%$).

---

## Deep-Dive Explanations

### The Lower-Bound Proof Technique

A recurring theme: to prove approximation ratio $\rho$, you do **not** need to know $|C^*|$ exactly. Instead, you find a **lower bound $LB \le |C^*|$** and an **upper bound $UB \ge |C|$**, then show $UB \le \rho \cdot LB$:

| Problem | Lower bound $LB$ | Upper bound $UB$ |
|---------|-----------------|-----------------|
| Vertex Cover | $\|A\|$ (maximal matching) | $2\|A\|$ |
| TSP (triangle ineq.) | $w(T)$ (MST weight) | $2w(T)$ (full walk cost) |
| Weighted VC | $z^*$ (LP relaxation) | $2z^*$ (rounded solution) |

### Why FPTAS Trimming Works

After $n$ rounds of trimming with $\delta = \varepsilon/2n$, the total error compounds multiplicatively. An optimal value $y^*$ is approximated by some $z \in L_n$ satisfying:
$$\frac{y^*}{z} \le (1 + \delta)^n = \left(1 + \frac{\varepsilon}{2n}\right)^n \xrightarrow{n\to\infty} e^{\varepsilon/2} \le 1 + \varepsilon$$

The last inequality uses $0 < \varepsilon < 1$ and the bound $e^x \le 1+2x$ for $x \in (0,\frac{1}{2})$.

### Impossibility Without Triangle Inequality (TSP)

The proof of Theorem 35.3 is a *gap-amplification* argument. Any gap (ratio $> 1$) between the "yes" cost and the "no" cost can be amplified to exceed $\rho$. This construction *creates* a gap of exactly $\rho+1$, which means any $\rho$-approximation algorithm would distinguish between "yes" and "no" instances — solving an NP-complete problem in polynomial time.

---

## Key Takeaways & Next Steps

| Algorithm | Problem | Running Time | Ratio |
|-----------|---------|-------------|-------|
| APPROX-VERTEX-COVER | Vertex Cover | $O(V+E)$ | 2 |
| APPROX-TSP-TOUR | TSP (triangle ineq.) | $\Theta(V^2)$ | 2 |
| GREEDY-SET-COVER | Set Covering | $O(\|X\| \cdot \|\mathcal{F}\| \cdot (\|X\|+\|\mathcal{F}\|))$ | $O(\log\|X\|)$ |
| Random assignment | MAX-3-CNF | $O(n+m)$ | 8/7 |
| APPROX-MIN-WEIGHT-VC | Weighted VC | Poly (LP) | 2 |
| APPROX-SUBSET-SUM | Subset Sum | $O(n^2/\varepsilon \cdot \log(n/\varepsilon))$ | $1+\varepsilon$ (FPTAS) |

**Key principles:**
1. Approximation ratio comes from relating solution size to a computable lower bound.
2. LP relaxation provides a lower bound for integer programs; rounding doubles the bound.
3. Randomization can achieve good expected approximation ratios.
4. FPTAS = best possible for NP-hard problems (unless P=NP): polynomial in *both* $n$ and $1/\varepsilon$.

**Next steps:**
- Christofides' $\frac{3}{2}$-approximation for metric TSP (uses minimum-weight matching).
- Inapproximability results via PCP theorem (see CLRS Chapter 34 notes).
- Study the primal-dual method and randomized rounding for advanced approximation design.

---

### Navigation

**Previous:** [[Ch34_NP_Completeness]]  
**Next:** *(end of Part VII — Selected Topics)*  
**Hub:** [[Index_Introduction_to_Algorithms]]
