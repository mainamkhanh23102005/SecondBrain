# Chapter 22: Single-Source Shortest Paths

## Executive Summary

Chapter 22 solves the **single-source shortest-paths** problem on weighted directed graphs: find minimum-weight paths from source $s$ to all reachable vertices. Shortest-path weights $\delta(s,v)$ are undefined when negative-weight cycles are reachable. The **relaxation** framework (INITIALIZE-SINGLE-SOURCE + RELAX) underlies all three algorithms: **Bellman-Ford** ($O(VE)$, handles negative weights, detects negative cycles), **DAG-SHORTEST-PATHS** ($\Theta(V+E)$, requires acyclic graph), and **Dijkstra's algorithm** ($O(V\log_2 V + E)$ with Fibonacci heap, requires nonnegative weights). Section 22.4 shows how systems of difference constraints reduce to single-source shortest paths.

---

## Zero-Loss Extraction

### Key Definitions

- **Shortest-path weight:** $\delta(u,v) = \min\{w(p) : u \overset{p}{\rightsquigarrow} v\}$; $\infty$ if no path; $-\infty$ if negative-weight cycle on path
- **Relaxation:** for edge $(u,v)$, if $v.d > u.d + w(u,v)$, update $v.d = u.d + w(u,v)$ and $v.\pi = u$
- **Shortest-paths tree:** rooted directed subgraph containing unique shortest path from $s$ to each reachable vertex

### Core Algorithms & Pseudocode

**INITIALIZE-SINGLE-SOURCE** — $\Theta(V)$:

```
INITIALIZE-SINGLE-SOURCE(G, s)
1  for each vertex v ∈ G.V
2      v.d = ∞;  v.π = NIL
3  s.d = 0

RELAX(u, v, w)
1  if v.d > u.d + w(u, v)
2      v.d = u.d + w(u, v)
3      v.π = u
```

**BELLMAN-FORD** — $O(VE)$, handles negative weights:

```
BELLMAN-FORD(G, w, s)
1  INITIALIZE-SINGLE-SOURCE(G, s)
2  for i = 1 to |G.V| − 1
3      for each edge (u, v) ∈ G.E
4          RELAX(u, v, w)
5  for each edge (u, v) ∈ G.E    // check for negative cycle
6      if v.d > u.d + w(u, v)
7          return FALSE            // negative cycle reachable
8  return TRUE
```

**DAG-SHORTEST-PATHS** — $\Theta(V+E)$, DAGs only:

```
DAG-SHORTEST-PATHS(G, w, s)
1  topologically sort G.V
2  INITIALIZE-SINGLE-SOURCE(G, s)
3  for each vertex u in topological order
4      for each vertex v in G.Adj[u]
5          RELAX(u, v, w)
```

**DIJKSTRA** — nonneg weights only; $O(V^2)$ array, $O(E\log_2 V)$ binary heap, $O(V\log_2 V + E)$ Fibonacci heap:

```
DIJKSTRA(G, w, s)
1  INITIALIZE-SINGLE-SOURCE(G, s)
2  S = ∅;  Q = min-priority queue of all V keyed by .d
3  while Q ≠ ∅
4      u = EXTRACT-MIN(Q)
5      S = S ∪ {u}
6      for each vertex v in G.Adj[u]
7          RELAX(u, v, w)
8          if v.d changed: DECREASE-KEY(Q, v, v.d)
```

---

## Deep-Dive Explanations

### Properties of Relaxation

These properties hold after INITIALIZE-SINGLE-SOURCE and any sequence of relaxation steps:

- **Triangle inequality (Lemma 22.10):** $\delta(s,v) \leq \delta(s,u) + w(u,v)$ for any $(u,v) \in E$
- **Upper-bound property (Lemma 22.11):** $v.d \geq \delta(s,v)$ always; once $v.d = \delta(s,v)$, it never changes
- **No-path property (Cor. 22.12):** if no path $s \rightsquigarrow v$, then $v.d = \infty$ always
- **Convergence property (Lemma 22.14):** if $u.d = \delta(s,u)$ and $(u,v)$ is relaxed, then $v.d = \delta(s,v)$ thereafter
- **Path-relaxation property (Lemma 22.15):** if edges of shortest path $p = \langle v_0, v_1, \ldots, v_k\rangle$ are relaxed in order, then $v_k.d = \delta(s, v_k)$
- **Predecessor-subgraph property (Lemma 22.17):** when $v.d = \delta(s,v)$ for all $v$, $G_\pi$ is a shortest-paths tree

### Bellman-Ford Algorithm

Makes $|V|-1$ passes over all edges. Correctness: any simple shortest path has at most $|V|-1$ edges; by path-relaxation property, $|V|-1$ passes suffice.

Negative-cycle detection: if any edge can still be relaxed after $|V|-1$ passes, a negative-weight cycle is reachable.

**Theorem 22.4:** Bellman-Ford returns TRUE iff no negative-weight cycle is reachable from $s$; when TRUE, $v.d = \delta(s,v)$ for all $v$.

**Running time:** $O(VE)$ ($\Theta(V)$ init + $|V|-1$ passes each relaxing all $|E|$ edges + $O(E)$ check).

### DAG Shortest Paths

Process vertices in topological order; relax each edge exactly once. Since the graph is a DAG, negative weights are allowed (no negative cycles possible).

**Theorem 22.5:** Correct, $v.d = \delta(s,v)$ at termination. Running time: $\Theta(V+E)$.

**Application:** PERT critical-path analysis — negate edge weights to find longest path (critical path = minimum time to complete all tasks).

### Dijkstra's Algorithm

Greedy: repeatedly extracts vertex $u$ with minimum $u.d$ from $V - S$; adds to $S$; relaxes outgoing edges. Requires nonneg weights so that $u.d = \delta(s,u)$ when $u$ is extracted.

**Theorem 22.6:** At termination, $u.d = \delta(s,u)$ for all $u \in V$.
*Proof key:* When $u$ is extracted, any vertex $y \notin S$ on a shortest path $s \rightsquigarrow u$ satisfies $y.d \geq u.d$ (since $u$ was chosen as minimum); combining with $\delta(s,y) \leq \delta(s,u) \leq u.d \leq y.d$ gives equality.

**Running time comparison:**

| Priority Queue | EXTRACT-MIN | DECREASE-KEY | Total |
|----------------|-------------|--------------|-------|
| Array | $O(V)$ × $V$ | $O(1)$ × $E$ | $O(V^2)$ |
| Binary heap | $O(\log_2 V)$ × $V$ | $O(\log_2 V)$ × $E$ | $O(E\log_2 V)$ |
| Fibonacci heap | $O(\log_2 V)$ amort × $V$ | $O(1)$ amort × $E$ | $O(V\log_2 V + E)$ |

### Difference Constraints (Section 22.4)

A **system of difference constraints** has the form $x_j - x_i \leq b_k$ for each constraint. Construct a **constraint graph** $G = (V, E)$: vertex $v_i$ per variable $x_i$, edge $(v_i, v_j)$ with weight $b_k$ per constraint $x_j - x_i \leq b_k$, plus extra source vertex $v_0$ with zero-weight edges to all $v_i$.

**Theorem:** The system is feasible iff $G$ has no negative-weight cycles. If feasible, the solution $x_i = \delta(v_0, v_i)$ satisfies all constraints. Solve with Bellman-Ford: $O(VE)$.

**Lemma 22.8:** If $x$ is a solution, so is $x + d$ (shifting all values by a constant $d$).

### Time and Space Complexity

| Algorithm | Time | Constraint | Space |
|-----------|------|------------|-------|
| BELLMAN-FORD | $O(VE)$ | Any weights | $O(V)$ |
| DAG-SHORTEST-PATHS | $\Theta(V+E)$ | Acyclic graph | $O(V)$ |
| DIJKSTRA (array) | $O(V^2)$ | Nonneg weights | $O(V)$ |
| DIJKSTRA (binary heap) | $O(E\log_2 V)$ | Nonneg weights | $O(V)$ |
| DIJKSTRA (Fibonacci heap) | $O(V\log_2 V + E)$ | Nonneg weights | $O(V)$ |

---

## Key Takeaways & Next Steps

1. **Relaxation is the universal primitive:** all three algorithms differ only in which edges they relax and in what order.
2. **Bellman-Ford** handles the most general case (negative weights, negative-cycle detection) at cost $O(VE)$.
3. **DAG-SHORTEST-PATHS** is optimal for acyclic graphs: $\Theta(V+E)$, no restrictions on weights.
4. **Dijkstra** is fastest when weights are nonneg: $O(V\log_2 V + E)$ with Fibonacci heap, mirroring Prim's MST algorithm.
5. **Negative weights** require Bellman-Ford or the DAG algorithm; Dijkstra fails because it assumes $u.d = \delta(s,u)$ at extraction time.

---

### Navigation

**Previous:** [[Ch21_Minimum_Spanning_Trees]]
**Next:** [[Ch23_All-Pairs_Shortest_Paths]]
**Hub:** [[Index_Introduction_to_Algorithms]]
