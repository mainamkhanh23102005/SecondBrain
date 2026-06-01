# Chapter 25: Matchings in Bipartite Graphs

## Executive Summary

Chapter 25 covers three matching problems on bipartite graphs $G=(V,E)$ with $V = L \cup R$. **Hopcroft-Karp** ($O(\sqrt{V} \cdot E)$) finds a maximum matching by repeatedly augmenting a maximal set of vertex-disjoint shortest $M$-augmenting paths using BFS + DFS. **Gale-Shapley** ($O(n^2)$) solves the **stable-marriage problem** on a complete bipartite graph with ranked preferences, always terminating with the unique women-optimal stable matching. The **Hungarian algorithm** ($O(n^4)$, improvable to $O(n^3)$) solves the **assignment problem** (maximum-weight perfect matching) by maintaining a feasible vertex labeling and iteratively augmenting the matching in the equality subgraph.

---

## Zero-Loss Extraction

### Key Definitions

- **Matching:** $M \subseteq E$ where every vertex has at most one incident edge in $M$
- **Maximum matching:** matching of maximum cardinality
- **$M$-alternating path:** simple path alternating between $M$ and $E - M$
- **$M$-augmenting path:** $M$-alternating path from an unmatched vertex to an unmatched vertex (odd number of edges)
- **Symmetric difference:** $X \oplus Y = (X - Y) \cup (Y - X)$
- **Stable matching:** matching with no blocking pair (pair $(w, m)$ not matched, yet $w$ prefers $m$ to her partner and $m$ prefers $w$ to his partner)
- **Feasible vertex labeling:** $l.h + r.h \geq w(l,r)$ for all $l \in L$, $r \in R$
- **Equality subgraph:** $G_h = (V, E_h)$ where $E_h = \{(l,r) : l.h + r.h = w(l,r)\}$

### Core Algorithms & Pseudocode

**HOPCROFT-KARP** — $O(\sqrt{V} \cdot E)$:

```
HOPCROFT-KARP(G)
1  M = ∅
2  repeat
3      P = {P1, P2, …, Pk}: maximal set of vertex-disjoint shortest M-augmenting paths
4      M = M ⊕ (P1 ∪ P2 ∪ … ∪ Pk)
5  until P == ∅
6  return M
```

Each iteration of lines 2–5 uses three phases (all $O(E)$): (1) direct $G$ to form $G_M$; (2) BFS from all unmatched $L$-vertices to build layered DAG $H$; (3) DFS on $H^T$ to extract maximal vertex-disjoint shortest augmenting paths.

**GALE-SHAPLEY** — $O(n^2)$, women-oriented:

```
GALE-SHAPLEY(men, women, rankings)
1  assign each woman and man as free
2  while some woman w is free
3      m = first man on w's ranked list to whom she has not proposed
4      if m is free
5          w and m become engaged
6      elseif m ranks w higher than his current partner w′
7          m breaks engagement to w′ (w′ becomes free)
8          w and m become engaged
9      else m rejects w (w remains free)
10 return the stable matching of engaged pairs
```

**HUNGARIAN** — $O(n^4)$ ($O(n^3)$ with improvements); solves assignment problem:

```
HUNGARIAN(G)
1  for each l ∈ L: l.h = max{w(l, r) : r ∈ R}   // default labeling
2  for each r ∈ R: r.h = 0
3  M = greedy maximal matching in Gh
4  form equality subgraph Gh and directed equality subgraph GM,h
5  while M is not a perfect matching
6      P = FIND-AUGMENTING-PATH(GM,h)
7      M = M ⊕ P
8      update Gh and GM,h
9  return M

FIND-AUGMENTING-PATH(GM,h)
1  Initialize FL, FR = ∅; Q = all unmatched vertices in L
2  repeat
3      if Q is empty (no path found)
4          δ = min{l.h + r.h − w(l,r) : l ∈ FL, r ∈ R − FR}
5          for each l ∈ FL: l.h = l.h − δ
6          for each r ∈ FR: r.h = r.h + δ
7          rebuild GM,h; enqueue all new edges from FL into Q
8      u = DEQUEUE(Q)
9      for each new edge (l, r) or (r, l) in GM,h from u:
10         if r ∉ FR: add r to FR, set r.π = l; if r is unmatched, trace back and return path
11         if l ∉ FL: add l to FL, ENQUEUE(Q, l)
```

---

## Deep-Dive Explanations

### Augmenting Path Theory

**Lemma 25.1:** If $P$ is an $M$-augmenting path, then $M' = M \oplus P$ is a matching with $|M'| = |M| + 1$.

**Corollary 25.2:** $k$ vertex-disjoint $M$-augmenting paths increase matching size by $k$: $|M \oplus (P_1 \cup \cdots \cup P_k)| = |M| + k$.

**Lemma 25.3:** For matchings $M$ and $M^*$, the graph $(V, M \oplus M^*)$ is a disjoint union of paths, cycles, and isolated vertices with edges alternating between $M$ and $M^*$. If $|M^*| > |M|$, at least $|M^*| - |M|$ vertex-disjoint $M$-augmenting paths exist.

**Corollary 25.4:** $M$ is maximum $\iff$ $G$ contains no $M$-augmenting path.

### Hopcroft-Karp Algorithm

**Key idea:** Instead of augmenting one path per iteration (→ $O(VE)$ as in Ford-Fulkerson matching), augment a maximal set of shortest vertex-disjoint paths per iteration.

**Phase 1:** Direct edges of $G$: unmatched edges $L \to R$, matched edges $R \to L$, giving $G_M$.

**Phase 2:** Multi-source BFS from all unmatched $L$-vertices, stop at first unmatched $R$-vertex distance $q$. Build layered DAG $H$ up to layer $q$. Time: $O(E)$.

**Phase 3:** DFS on $H^T$ from unmatched $R$-vertices in layer $q$; each vertex visited at most once → finds maximal set of vertex-disjoint shortest $M$-augmenting paths. Time: $O(E)$.

**Lemma 25.5:** After augmenting by a maximal set of shortest paths of length $q$, the shortest $M'$-augmenting path has length $> q$.

**Lemma 25.6:** If shortest augmenting path has $q$ edges, then $|M^*| \leq |M| + |V|/(q+1)$.

**Lemma 25.7:** The repeat loop iterates $O(\sqrt{V})$ times.
*Proof:* After $\sqrt{V}$ iterations, shortest path length $\geq \sqrt{V}$; by Lemma 25.6, at most $|V|/(\sqrt{V}+1) = O(\sqrt{V})$ more iterations remain. Total: $O(\sqrt{V})$.

**Theorem 25.8:** HOPCROFT-KARP runs in $O(\sqrt{V} \cdot E)$ time ($O(\sqrt{V})$ iterations $\times$ $O(E)$ per iteration).

### Stable-Marriage Problem (Gale-Shapley)

**Theorem 25.9 (Correctness):** GALE-SHAPLEY terminates (at most $n^2$ proposals) and returns a stable matching. *Proof:* Men never become free after engagement; if $(w,m)$ were a blocking pair, $w$ proposed to $m$ before her partner, but $m$ eventually chose someone he prefers, so $m$ doesn't prefer $w$.

**Theorem 25.11 (Optimality):** Regardless of order in line 2, GALE-SHAPLEY always returns the same matching, and each woman receives the best partner possible across all stable matchings.

**Corollary 25.13:** Conversely, each man gets the worst partner possible in any stable matching.

**Corollary 25.10:** GALE-SHAPLEY runs in $O(n^2)$ time.

### Hungarian Algorithm (Assignment Problem)

**Setup:** Complete bipartite graph with $|L| = |R| = n$; edge weights $w(l,r)$; goal: maximum-weight perfect matching.

**Theorem 25.14:** If feasible vertex labeling $h$ and equality subgraph $G_h$ contains a perfect matching $M^*$, then $M^*$ is optimal.
*Proof:* $w(M^*) = \sum_{(l,r) \in M^*}(l.h + r.h) = \sum_{v \in V} v.h \geq w(M)$ for any matching $M$ (since $l.h + r.h \geq w(l,r)$ for all edges).

**Label update:** When BFS fails to find augmenting path, compute:
$$\delta = \min\{l.h + r.h - w(l,r) : l \in F_L,\; r \in R - F_R\}$$
Update: $l.h \leftarrow l.h - \delta$ for $l \in F_L$; $r.h \leftarrow r.h + \delta$ for $r \in F_R$.

**Lemma 25.15:** After label update: (1) all BFS-forest edges remain in $G_h$; (2) all matching edges remain; (3) at least one new edge enters $G_h$ from $F_L$ to $R - F_R$ → guarantees progress.

**Running time:** $O(n^4)$ straightforwardly ($n$ outer iterations × $O(n^3)$ per FIND-AUGMENTING-PATH). With $O(n)$ δ-computation, reduces to $O(n^3)$.

**Duality:** Max-weight matching = min sum of feasible vertex labels; mirrors max-flow min-cut duality.

### Time and Space Complexity

| Algorithm | Time | Space | Problem |
|-----------|------|-------|---------|
| HOPCROFT-KARP | $O(\sqrt{V} \cdot E)$ | $O(V+E)$ | Maximum bipartite matching |
| GALE-SHAPLEY | $O(n^2)$ | $O(n^2)$ | Stable marriage |
| HUNGARIAN | $O(n^4)$ ($O(n^3)$ improved) | $O(n^2)$ | Assignment (max-weight perfect matching) |
| Ford-Fulkerson matching | $O(VE)$ | $O(V+E)$ | Maximum bipartite matching |

---

## Key Takeaways & Next Steps

1. **Augmenting path theory** unifies all maximum-matching algorithms: $M$ is maximum iff no $M$-augmenting path exists (Corollary 25.4).
2. **Hopcroft-Karp** beats the simpler $O(VE)$ approach by augmenting many paths simultaneously, achieving $O(\sqrt{V} \cdot E)$ via phase-based BFS + DFS.
3. **Gale-Shapley** always produces the unique women-optimal stable matching in $O(n^2)$; men get their worst stable outcome.
4. **Hungarian algorithm** exploits the equality subgraph: any perfect matching in an equality subgraph is optimally weighted; label updates bring in new edges without losing previous progress.
5. **Duality pervades:** max matching ↔ min vertex cover (König's theorem); max-weight matching ↔ min-sum feasible labeling; max-flow ↔ min-cut (Chapter 24).

---

### Navigation

**Previous:** [[Ch24_Maximum_Flow]]
**Next:** [[Ch26_Parallel_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
