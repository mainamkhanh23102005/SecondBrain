# Chapter 24: Maximum Flow

## Executive Summary

Chapter 24 solves the **maximum-flow problem**: given a directed flow network $G=(V,E)$ with source $s$, sink $t$, and edge capacities $c(u,v) \geq 0$, find a flow of maximum value from $s$ to $t$. The central result is the **max-flow min-cut theorem** (Theorem 24.6): a flow is maximum if and only if its residual network contains no augmenting path, and if and only if its value equals the capacity of some minimum cut. **Ford-Fulkerson** ($O(E|f^*|)$ for integer capacities) repeatedly augments flow along any $s$-$t$ path in the residual network. **Edmonds-Karp** ($O(VE^2)$) specializes Ford-Fulkerson by using BFS to find shortest augmenting paths, guaranteeing polynomial time. A key application is **maximum bipartite matching** ($O(VE)$), reducible to max-flow via unit-capacity networks.

---

## Zero-Loss Extraction

### Key Definitions

- **Flow network:** Directed graph $G=(V,E)$ with capacity $c(u,v) \geq 0$; source $s$, sink $t$; no antiparallel edges; no self-loops
- **Flow:** $f: V \times V \to \mathbb{R}$ satisfying:
  - *Capacity constraint:* $0 \leq f(u,v) \leq c(u,v)$ for all $u,v \in V$
  - *Flow conservation:* $\sum_{v \in V} f(u,v) = \sum_{v \in V} f(v,u)$ for all $u \neq s,t$
- **Flow value:** $|f| = \sum_{v \in V} f(s,v) - \sum_{v \in V} f(v,s)$
- **Residual capacity:** $c_f(u,v) = c(u,v) - f(u,v)$ if $(u,v) \in E$; $c_f(u,v) = f(v,u)$ if $(v,u) \in E$; 0 otherwise
- **Residual network:** $G_f = (V, E_f)$ where $E_f = \{(u,v) : c_f(u,v) > 0\}$; $|E_f| \leq 2|E|$
- **Augmenting path:** Simple path $s \rightsquigarrow t$ in $G_f$; residual capacity $c_f(p) = \min_{(u,v) \in p} c_f(u,v)$
- **Cut $(S,T)$:** Partition $V = S \cup T$ with $s \in S$, $t \in T$; capacity $c(S,T) = \sum_{u \in S, v \in T} c(u,v)$; minimum cut minimizes $c(S,T)$

### Core Algorithms & Pseudocode

**FORD-FULKERSON** — $O(E|f^*|)$ for integer capacities:

```
FORD-FULKERSON(G, s, t)
1  for each edge (u, v) ∈ G.E
2      (u, v).f = 0
3  while there exists a path p from s to t in the residual network Gf
4      cf(p) = min{cf(u, v) : (u, v) is in p}
5      for each edge (u, v) in p
6          if (u, v) ∈ G.E
7              (u, v).f = (u, v).f + cf(p)
8          else (v, u).f = (v, u).f − cf(p)
9  return f
```

**Edmonds-Karp:** FORD-FULKERSON with BFS in line 3 to find shortest augmenting path. Total time: $O(VE^2)$.

**Maximum Bipartite Matching via Ford-Fulkerson:**

```
Given bipartite graph G = (V, E), V = L ∪ R:
1  Construct flow network G′:
     V′ = V ∪ {s, t}
     E′ = {(s, u) : u ∈ L}
        ∪ {(u, v) : u ∈ L, v ∈ R, (u, v) ∈ E}   // directed L → R
        ∪ {(v, t) : v ∈ R}
     All capacities = 1
2  Run FORD-FULKERSON on G′
3  M = {(u, v) : u ∈ L, v ∈ R, f(u, v) = 1}
4  return M
```

---

## Deep-Dive Explanations

### Flow Networks and Formalism (Section 24.1)

**Antiparallel edges** (both $(u,v)$ and $(v,u)$): handle by splitting into two directed edges through a new intermediate vertex.

**Multiple sources/sinks:** add a supersource $s$ with $c(s, s_i) = \infty$ for each source $s_i$, and a supersink $t$ with $c(t_j, t) = \infty$ for each sink $t_j$.

### Residual Networks and Augmenting Paths (Section 24.2)

The residual capacity $c_f(u,v)$ captures how much additional flow can be pushed:
$$c_f(u,v) = \begin{cases} c(u,v) - f(u,v) & \text{if } (u,v) \in E \\ f(v,u) & \text{if } (v,u) \in E \\ 0 & \text{otherwise} \end{cases}$$

**Flow augmentation:** Given flow $f$ in $G$ and flow $f'$ in $G_f$, the augmented flow $f \uparrow f'$ has value $|f \uparrow f'| = |f| + |f'|$ (Lemma 24.1).

**Lemma 24.2:** For augmenting path $p$, define $f_p(u,v) = c_f(p)$ if $(u,v) \in p$, $f_p(v,u) = c_f(p)$ if $(v,u) \in p$, and 0 otherwise. Then $f_p$ is a valid flow in $G_f$ with $|f_p| = c_f(p) > 0$.

**Corollary 24.3:** Augmenting $f$ by $f_p$ yields a flow $f \uparrow f_p$ with value $|f| + |f_p| > |f|$.

### Cuts and the Max-Flow Min-Cut Theorem

**Net flow across a cut:** For any cut $(S,T)$, $f(S,T) = \sum_{u \in S, v \in T} f(u,v) - \sum_{u \in S, v \in T} f(v,u)$.

**Lemma 24.4:** For any flow $f$ and any cut $(S,T)$: $f(S,T) = |f|$.

**Corollary 24.5:** $|f| \leq c(S,T)$ for any flow $f$ and cut $(S,T)$.

**Theorem 24.6 (Max-flow min-cut theorem):** The following are equivalent:
1. $f$ is a maximum flow in $G$
2. $G_f$ contains no augmenting path
3. $|f| = c(S,T)$ for some cut $(S,T)$ of $G$

*Proof sketch:* (1)⇒(2): augmenting path would increase flow, contradiction. (2)⇒(3): define $S = \{v : \text{reachable from } s \text{ in } G_f\}$; edges from $S$ to $T$ must be saturated, so $|f| = c(S,T)$. (3)⇒(1): by Corollary 24.5.

### Analysis of Ford-Fulkerson

For integer capacities, each augmentation increases $|f|$ by at least 1, so the while loop runs at most $|f^*|$ times. Each iteration takes $O(E)$ (path search + update). **Total: $O(E|f^*|)$.**

Pathological case: if augmenting paths are chosen adversarially (alternating short paths with residual capacity 1), Ford-Fulkerson may perform $\Theta(|f^*|)$ iterations even when $|f^*|$ is huge.

### Edmonds-Karp Algorithm

Using BFS ensures shortest augmenting paths (fewest edges), giving the Edmonds-Karp algorithm.

**Lemma 24.7:** Under Edmonds-Karp, $\delta_f(s,v)$ (BFS distance in $G_f$) increases monotonically with each augmentation for all $v \neq s,t$.

**Theorem 24.8:** Total number of augmentations is $O(VE)$.
*Proof:* An edge $(u,v)$ is **critical** on an augmenting path when $c_f(p) = c_f(u,v)$; it disappears from $G_f$ after augmentation. Each time $(u,v)$ becomes critical, $\delta_f(s,u)$ increases by at least 2. Since distances are bounded by $|V|-2$, $(u,v)$ can become critical at most $|V|/2$ times. With $O(E)$ edges, total critical events $= O(VE)$, bounding augmentations.

Each augmentation takes $O(E)$ (BFS), so **total Edmonds-Karp time: $O(VE^2)$.**

### Maximum Bipartite Matching (Section 24.3)

**Bipartite matching reduction:** Build $G' = (V', E')$ with $V' = L \cup R \cup \{s,t\}$, unit-capacity edges from $s$ to each $u \in L$, from each $u \in L$ to adjacent $v \in R$, and from each $v \in R$ to $t$.

**Lemma 24.9:** Matching $M$ in $G$ ↔ integer-valued flow $f'$ in $G'$ with $|f'| = |M|$.

**Theorem 24.10 (Integrality theorem):** If all capacities are integers, Ford-Fulkerson produces an integer-valued maximum flow.

**Corollary 24.11:** $|$maximum matching$|$ in bipartite $G$ $=$ $|$maximum flow$|$ in $G'$.

**Running time:** Maximum matching cardinality $\leq \min(|L|,|R|) = O(V)$, so Ford-Fulkerson runs $O(V)$ augmentations on $G'$. Each takes $O(E')= O(E)$. **Total: $O(VE)$.**

### Time and Space Complexity

| Algorithm | Time | Notes |
|-----------|------|-------|
| Ford-Fulkerson | $O(E|f^*|)$ | Integer capacities only |
| Edmonds-Karp | $O(VE^2)$ | BFS augmenting; polynomial always |
| Max bipartite matching | $O(VE)$ | Via Ford-Fulkerson on unit-cap network |

---

## Key Takeaways & Next Steps

1. **Max-flow min-cut theorem** is the cornerstone: maximum flow equals minimum cut capacity; the cut is identified by reachability in $G_f$ when no augmenting path exists.
2. **Residual network** enables flow cancellation via reverse edges — pushing flow backward on an edge is equivalent to decreasing it.
3. **Edmonds-Karp** ($O(VE^2)$) guarantees polynomial time by using BFS; the key insight is that shortest-path distances in $G_f$ never decrease, bounding augmentations to $O(VE)$.
4. **Bipartite matching** reduces cleanly to max-flow: unit capacities force integer flows (Integrality Theorem), matching edges correspond exactly to flow-carrying $L$-to-$R$ edges.
5. **Reductions to max-flow:** multiple sources/sinks, vertex capacities (split vertex into $v_{in}$/$v_{out}$ with capacity edge), minimum path cover in DAGs.

---

### Navigation

**Previous:** [[Ch23_All-Pairs_Shortest_Paths]]
**Next:** [[Ch25_Bipartite_Matching_and_More]]
**Hub:** [[Index_Introduction_to_Algorithms]]
