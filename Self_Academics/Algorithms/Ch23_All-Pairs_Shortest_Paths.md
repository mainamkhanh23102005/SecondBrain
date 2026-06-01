# Chapter 23: All-Pairs Shortest Paths

## Executive Summary

Chapter 23 finds shortest paths between **all pairs** of vertices in a weighted directed graph. Three algorithms are presented: a **matrix-multiplication-based DP** ($\Theta(n^3 \log_2 n)$ with repeated squaring), **Floyd-Warshall** ($\Theta(n^3)$, DP on intermediate vertices), and **Johnson's algorithm** ($O(V^2\log_2 V + VE)$, optimal for sparse graphs). Floyd-Warshall is the classic choice for dense graphs with possibly negative weights. Johnson's algorithm uses **reweighting** (Bellman-Ford to compute $h$, then Dijkstra from each vertex) to handle negative weights on sparse graphs efficiently.

---

## Zero-Loss Extraction

### Representations

Input: $n \times n$ weight matrix $W = (w_{ij})$ where $w_{ij} = 0$ if $i=j$, $w_{ij} = w(i,j)$ if $(i,j)\in E$, $w_{ij} = \infty$ otherwise. Output: $n \times n$ matrix $D$ where $d_{ij} = \delta(i,j)$, and predecessor matrix $\Pi$.

### Core Algorithms & Pseudocode

**EXTEND-SHORTEST-PATHS** — one-step "matrix multiplication" ($\Theta(n^3)$):

```
EXTEND-SHORTEST-PATHS(L^(r-1), W, L^(r), n)
1  // L^(r) initialized to ∞
2  for i = 1 to n
3      for j = 1 to n
4          for k = 1 to n
5              l^(r)_ij = min(l^(r)_ij, l^(r-1)_ik + w_kj)
```

**FASTER-APSP** — $\Theta(n^3\log_2 n)$ via repeated squaring:

```
FASTER-APSP(W, n)
1  L = W;  r = 1
2  while r < n − 1
3      M = ∞
4      EXTEND-SHORTEST-PATHS(L, L, M, n)   // M = L^2
5      r = 2r;  L = M
6  return L
```

**FLOYD-WARSHALL** — $\Theta(n^3)$, handles negative weights:

```
FLOYD-WARSHALL(W, n)
1  D^(0) = W
2  for k = 1 to n
3      let D^(k) be a new n × n matrix
4      for i = 1 to n
5          for j = 1 to n
6              d^(k)_ij = min(d^(k-1)_ij, d^(k-1)_ik + d^(k-1)_kj)
7  return D^(n)
```

Space-efficient variant (FLOYD-WARSHALL′): drop superscripts, use single matrix $D$, still correct. Space: $\Theta(n^2)$.

**JOHNSON** — $O(V^2\log_2 V + VE)$:

```
JOHNSON(G, w)
1  Create G′ = G + new vertex s with zero-weight edges (s, v) for all v ∈ G.V
2  if BELLMAN-FORD(G′, w, s) == FALSE
3      report "input graph contains a negative-weight cycle"
4  else
5      for each vertex v ∈ G′.V
6          h(v) = δ(s, v) computed by Bellman-Ford
7      for each edge (u, v) ∈ G.E
8          ŵ(u, v) = w(u, v) + h(u) − h(v)    // reweight
9      for each vertex u ∈ G.V
10         run DIJKSTRA(G, ŵ, u) to compute δ̂(u, v) for all v ∈ G.V
11         for each vertex v ∈ G.V
12             d_uv = δ̂(u, v) − h(u) + h(v)    // restore original weights
13 return D
```

---

## Deep-Dive Explanations

### Shortest Paths and Matrix Multiplication (Section 23.1)

Define $l_{ij}^{(r)}$ = min weight of any path from $i$ to $j$ with at most $r$ edges.

**Recurrence:**
$$l_{ij}^{(0)} = \begin{cases} 0 & i = j \\ \infty & i \neq j \end{cases}, \qquad l_{ij}^{(r)} = \min_{1 \leq k \leq n} \{l_{ik}^{(r-1)} + w_{kj}\}$$

This is isomorphic to matrix multiplication with $(\min, +)$ instead of $(+, \times)$.

EXTEND-SHORTEST-PATHS computes $L^{(r)} = L^{(r-1)} \cdot W$ in $\Theta(n^3)$. SLOW-APSP (not shown) applies this $n-1$ times → $\Theta(n^4)$. FASTER-APSP uses repeated squaring: $\lceil\log_2(n-1)\rceil$ squarings → $\Theta(n^3\log_2 n)$.

### Floyd-Warshall Algorithm (Section 23.2)

**DP formulation:** $d_{ij}^{(k)}$ = min weight path from $i$ to $j$ with all intermediate vertices in $\{1, \ldots, k\}$.

$$d_{ij}^{(0)} = w_{ij}, \qquad d_{ij}^{(k)} = \min\!\left(d_{ij}^{(k-1)},\; d_{ik}^{(k-1)} + d_{kj}^{(k-1)}\right)$$

At $k = n$: $d_{ij}^{(n)} = \delta(i,j)$. Negative-cycle detection: if $d_{ii}^{(n)} < 0$ for any $i$.

**Transitive closure:** Replace $(\min, +)$ with $(\vee, \wedge)$ (logical OR, AND):
$$t_{ij}^{(0)} = [i=j \text{ or } (i,j)\in E], \qquad t_{ij}^{(k)} = t_{ij}^{(k-1)} \vee (t_{ik}^{(k-1)} \wedge t_{kj}^{(k-1)})$$

TRANSITIVE-CLOSURE runs in $\Theta(n^3)$, uses booleans (space and speed advantage on bit-level hardware).

### Johnson's Algorithm (Section 23.3)

**Reweighting:** Define $\hat{w}(u,v) = w(u,v) + h(u) - h(v)$. For any path $p = \langle v_0, v_1, \ldots, v_k\rangle$:
$$\hat{w}(p) = w(p) + h(v_0) - h(v_k)$$

**Lemma 23.1:** $p$ is a shortest path under $w$ iff it is under $\hat{w}$. Negative-weight cycles are preserved.

**Key:** Choose $h(v) = \delta(s,v)$ where $s$ is a new source with zero-weight edges to all vertices. Then $h(v) \leq h(u) + w(u,v)$ (triangle inequality), so $\hat{w}(u,v) \geq 0$ for all edges.

After running Dijkstra with $\hat{w}$: restore original distances via $\delta(u,v) = \hat{\delta}(u,v) - h(u) + h(v)$.

**Running time:** $O(VE)$ for Bellman-Ford + $O(E)$ reweighting + $V \times O(V\log_2 V + E)$ Dijkstra = $O(V^2\log_2 V + VE)$.

### Time and Space Complexity

| Algorithm | Time | Space | Handles Neg. Weights |
|-----------|------|-------|----------------------|
| Repeated Dijkstra (array) | $O(V^3)$ | $O(V^2)$ | No |
| Repeated Dijkstra (Fibonacci) | $O(V^2\log_2 V + VE)$ | $O(V^2)$ | No |
| Repeated Bellman-Ford | $O(V^2 E)$ | $O(V^2)$ | Yes |
| FASTER-APSP (matrix) | $\Theta(n^3\log_2 n)$ | $O(n^2)$ | Yes |
| Floyd-Warshall | $\Theta(n^3)$ | $O(n^2)$ | Yes |
| Johnson | $O(V^2\log_2 V + VE)$ | $O(V^2)$ | Yes |

---

## Key Takeaways & Next Steps

1. **Floyd-Warshall** is the standard choice for dense graphs: $\Theta(n^3)$, simple code, handles negative weights; detect negative cycles via diagonal.
2. **Johnson's algorithm** beats Floyd-Warshall on sparse graphs ($|E| = o(n^2/\log_2 n)$) by combining reweighting + Dijkstra; uses $O(V^2\log_2 V + VE)$ time.
3. **Reweighting insight:** Adding vertex potentials $h(v)$ preserves relative path costs (telescoping), making all edges nonneg without changing which path is shortest.
4. **Matrix multiplication analogy:** $(\min, +)$ plays the role of $(+, \times)$; repeated squaring reduces matrix-based APSP from $\Theta(n^4)$ to $\Theta(n^3\log_2 n)$.
5. All DP formulations exploit **optimal substructure of shortest paths** (Lemma 22.1).

---

### Navigation

**Previous:** [[Ch22_Single-Source_Shortest_Paths]]
**Next:** [[Ch24_Maximum_Flow]]
**Hub:** [[Index_Introduction_to_Algorithms]]
