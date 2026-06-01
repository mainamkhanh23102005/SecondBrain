# Chapter 29: Linear Programming

**Source:** Introduction to Algorithms (CLRS), Chapter 29  
**Tags:** #algorithms #linear-programming #optimization #simplex #duality

---

## Executive Summary

**Linear programming (LP)** optimizes a linear objective function over a convex feasible region defined by linear constraints. This chapter covers LP formulation, the geometry of optimal solutions (always at vertices of the feasible region), the **simplex algorithm** (vertex-traversal), polynomial-time algorithms (ellipsoid, interior-point), and **duality** (every LP has a dual whose optimal value equals the primal's). Key applications: modeling shortest paths, max-flow, min-cost flow, and multicommodity flow as LPs.

---

## Zero-Loss Extraction

### 1. Standard Form

A **maximization LP in standard form** has $n$ decision variables $x_1, \ldots, x_n$ and $m$ inequality constraints:

$$\text{maximize} \quad c^T x$$
$$\text{subject to} \quad Ax \leq b, \quad x \geq 0$$

where $A$ is $m \times n$, $b$ is an $m$-vector, $c$ is an $n$-vector.

- **Objective function:** $c^T x = \sum_{j=1}^n c_j x_j$.
- **Constraints:** $m$ constraints (each $\sum_j a_{ij} x_j \leq b_i$) plus $n$ **nonnegativity constraints** ($x_j \geq 0$).
- **Feasible solution:** any $x$ satisfying all constraints.
- **Infeasible LP:** no feasible solution exists.
- **Unbounded LP:** feasible, but objective can grow without bound.
- **Optimal solution $\bar{x}$:** feasible $x$ maximizing $c^T x$; **optimal objective value** $= c^T \bar{x}$.

**Converting to standard form:**
- Equality $a^T x = b$ → two inequalities: $a^T x \leq b$ and $-a^T x \leq -b$.
- $\leq$ constraint → introduce **slack variable** $s \geq 0$: $a^T x + s = b$.
- Minimization: negate the objective ($\min c^T x \equiv \max (-c)^T x$).
- Unconstrained variable $x_j$ → introduce $x_j = x_j^+ - x_j^-$ with $x_j^+, x_j^- \geq 0$.

---

### 2. Geometric Intuition

**Feasible region** = intersection of $m + n$ half-spaces → a **convex polytope** (called a **simplex** in $n$ dimensions).

**Optimal solution geometry:** for a bounded LP, an optimal solution always exists at a **vertex** of the feasible region. Proof: the objective hyperplane slides in the direction of $c$; the last feasible intersection is at a vertex or on an edge (in which case both endpoints — both vertices — are optimal).

**Two-variable LP example:**
$$\text{maximize} \quad x_1 + x_2$$
subject to $x_1 \leq 4$, $2x_2 \leq 12$, $3x_1 + 2x_2 \leq 18$, $x_1, x_2 \geq 0$.

Graphically: plot constraints, identify feasible region (convex polygon), slide objective line $x_1 + x_2 = z$ upward until last intersection. Optimal: $x_1 = 2$, $x_2 = 6$, objective value $= 8$.

---

### 3. Algorithms for LP

| Algorithm | Time | In Practice |
|-----------|------|-------------|
| **Simplex** | Exponential worst-case | Fast in practice |
| **Ellipsoid** | $O(\text{poly}(n, m))$ | Slow in practice |
| **Interior-point** | $O(\text{poly}(n, m))$ | Often as fast as simplex; faster on large inputs |

**Simplex algorithm:** start at a vertex; repeatedly move to an adjacent vertex with at least as large an objective value; stop at a local maximum (which is globally optimal by convexity).

**Integer linear programming (ILP):** add constraint that all variables are integers → NP-hard (Exercise 34.5-3). No known polynomial-time algorithm.

---

### 4. Duality (§29.3)

Every LP (the **primal**) has a corresponding **dual LP**. For the standard-form primal:

$$\text{Primal: maximize } c^T x, \quad Ax \leq b, \quad x \geq 0$$
$$\text{Dual: minimize } b^T y, \quad A^T y \geq c, \quad y \geq 0$$

**Weak duality:** if $\bar{x}$ is a feasible primal solution and $\bar{y}$ is a feasible dual solution, then
$$c^T \bar{x} \leq b^T \bar{y}$$

**Strong duality:** if the primal has an optimal solution $\bar{x}$, then the dual has an optimal solution $\bar{y}$ with
$$c^T \bar{x} = b^T \bar{y}$$

**Interpretation:** the dual objective value bounds the primal from above; at optimality they coincide. The dual variables are **shadow prices** — marginal value of relaxing each primal constraint by one unit.

---

### 5. Formulating Graph Problems as LPs

#### 5.1 Single-Pair Shortest Path

Variables: $d_v$ = estimated shortest-path weight from source $s$ to $v$.

$$\text{maximize} \quad d_t$$
$$\text{subject to} \quad d_v \leq d_u + w(u,v) \quad \forall (u,v) \in E$$
$$d_s = 0$$

Maximizing $d_t$ forces it to equal the true shortest-path weight (minimizing would trivially set all $d_v = 0$). This LP has $|V|$ variables and $|E| + 1$ constraints.

#### 5.2 Maximum Flow

Variables: $f_{uv}$ = flow on edge $(u,v)$.

$$\text{maximize} \quad \sum_{v \in V} f_{sv} - \sum_{v \in V} f_{vs}$$
$$\text{subject to}$$
$$f_{uv} \leq c(u,v) \quad \forall u,v \in V \quad \text{(capacity)}$$
$$\sum_{v} f_{vu} = \sum_{v} f_{uv} \quad \forall u \neq s,t \quad \text{(flow conservation)}$$
$$f_{uv} \geq 0 \quad \forall u,v \in V$$

This has $|V|^2$ variables and $2|V|^2 + |V| - 2$ constraints (reducible to $O(V+E)$).

#### 5.3 Minimum-Cost Flow

Send exactly $d$ units from $s$ to $t$ while minimizing $\sum_{(u,v) \in E} a(u,v) \cdot f_{uv}$:

$$\text{minimize} \quad \sum_{(u,v) \in E} a(u,v) \cdot f_{uv}$$
subject to capacity, flow conservation (same as max-flow), and total flow $= d$.

#### 5.4 Multicommodity Flow

$k$ commodities $K_i = (s_i, t_i, d_i)$; flow $f^i_{uv}$ for commodity $i$ on edge $(u,v)$. Aggregate flow $f_{uv} = \sum_i f^i_{uv}$ must respect capacity $c(u,v)$.

**No polynomial-time algorithm exists for this problem other than via LP.** The LP has a "null" objective (find any feasible flow):

$$\text{find} \quad f^i_{uv} \geq 0 \quad \forall i, u, v$$
subject to capacity, flow conservation per commodity, and demand satisfaction.

---

### 6. Political Advertising Example

Motivating example: minimize advertising spend $x_1 + x_2 + x_3 + x_4$ (thousands of dollars across 4 issues) to win required urban, suburban, and rural votes:

$$-2x_1 + 8x_2 + 0x_3 + 10x_4 \geq 50 \quad \text{(urban)}$$
$$5x_1 + 2x_2 + 0x_3 + 0x_4 \geq 100 \quad \text{(suburban)}$$
$$3x_1 - 5x_2 + 10x_3 - 2x_4 \geq 25 \quad \text{(rural)}$$
$$x_1, x_2, x_3, x_4 \geq 0$$

---

## Deep-Dive Explanations

### Why the Optimal Is Always at a Vertex

The feasible region is a **convex set**: any convex combination of feasible points is also feasible. The objective function is linear, so it is also convex (and concave). For a bounded LP, the objective achieves its maximum on the boundary. By induction on dimension, the maximum on any convex face is achieved at a vertex of that face. The simplex algorithm exploits this by only ever examining vertices.

### Duality and the Simplex Algorithm's Termination

The simplex algorithm terminates when no adjacent vertex improves the objective. By **strong duality**, this local optimum equals the global optimum: if the simplex solution $\bar{x}$ has the same value as the feasible dual solution $\bar{y}$, then $c^T \bar{x} = b^T \bar{y}$, and by weak duality, $\bar{x}$ must be optimal.

### Integer Programming is Hard

Relaxing integrality constraints gives a polynomial-time solvable LP. The LP relaxation's optimal value is an upper bound on the ILP optimum. Finding the ILP optimum requires exponential time in the worst case (it's NP-hard), unlike LP which admits polynomial-time algorithms.

---

## Key Takeaways & Next Steps

1. **Model clearly:** identify decision variables, constraints (linear), and objective (linear). All three must be linear for LP to apply.
2. **Geometry:** feasible region is a convex polytope; an optimal solution always exists at a vertex.
3. **Three algorithm families:** simplex (practical, exponential worst-case), ellipsoid (polynomial, slow in practice), interior-point (polynomial, practical).
4. **Duality is powerful:** the dual provides an upper bound on the primal; strong duality certifies optimality.
5. **LP can model many graph problems** (shortest paths, max-flow, min-cost flow, multicommodity flow). Some of these have faster specialized algorithms; LP is indispensable for multicommodity flow.
6. **ILP is NP-hard** — adding integrality constraints destroys polynomial-time solvability.
7. **Next:** Chapter 30 (Polynomials and the FFT) — fast polynomial multiplication via the Discrete Fourier Transform.

---

### Navigation

- **Previous:** [[Ch28_Matrix_Operations|Ch28 — Matrix Operations]]
- **Next:** [[Ch30_Polynomials_and_the_FFT|Ch30 — Polynomials and the FFT]]
- **Hub:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms Index]]
