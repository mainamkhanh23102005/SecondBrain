# Chapter 21: Minimum Spanning Trees

## Executive Summary

Chapter 21 presents the **minimum spanning tree (MST)** problem: find an acyclic subset $T \subseteq E$ that connects all vertices of a connected, undirected, weighted graph $G=(V,E,w)$ with minimum total weight. A generic greedy method (GENERIC-MST) builds the MST by adding **safe edges** — characterized by **Theorem 21.1** (cut theorem: a light edge crossing a cut that respects $A$ is safe). Two concrete algorithms both achieve $O(E\log_2 V)$: **Kruskal's algorithm** sorts edges and uses union-find; **Prim's algorithm** grows a single tree using a min-priority queue. With a Fibonacci heap, Prim's algorithm runs in $O(E + V\log_2 V)$.

---

## Zero-Loss Extraction

### Key Definitions

- **Spanning tree:** acyclic connected subgraph spanning all $|V|$ vertices ($|V|-1$ edges)
- **Cut $(S, V-S)$:** partition of $V$; an edge **crosses** the cut if its endpoints lie on opposite sides
- **Cut respects $A$:** no edge in $A$ crosses the cut
- **Light edge:** minimum-weight edge crossing a cut
- **Safe edge for $A$:** adding it preserves $A \subseteq$ some MST

### Core Algorithms & Pseudocode

**GENERIC-MST** (greedy framework):

```
GENERIC-MST(G, w)
1  A = ∅
2  while A does not form a spanning tree
3      find an edge (u, v) that is safe for A
4      A = A ∪ {(u, v)}
5  return A
```

**MST-KRUSKAL** — $O(E\log_2 V)$:

```
MST-KRUSKAL(G, w)
1  A = ∅
2  for each vertex v ∈ G.V
3      MAKE-SET(v)
4  sort edges of G.E into non-decreasing order by weight w
5  for each edge (u, v) from sorted list
6      if FIND-SET(u) ≠ FIND-SET(v)
7          A = A ∪ {(u, v)}
8          UNION(u, v)
9  return A
```

**MST-PRIM** — $O(E\log_2 V)$ with binary heap; $O(E + V\log_2 V)$ with Fibonacci heap:

```
MST-PRIM(G, w, r)
1  for each vertex u ∈ G.V
2      u.key = ∞;  u.π = NIL
3  r.key = 0
4  Q = min-priority queue of all vertices keyed on .key
5  while Q ≠ ∅
6      u = EXTRACT-MIN(Q)            // add u to MST
7      for each vertex v in G.Adj[u]
8          if v ∈ Q and w(u, v) < v.key
9              v.π = u
10             v.key = w(u, v)
11             DECREASE-KEY(Q, v, w(u, v))
```

At termination: $A = \{(v, v.\pi) : v \in V - \{r\}\}$ is the MST.

---

## Deep-Dive Explanations

### The Cut Theorem (Safe Edge Recognition)

**Theorem 21.1:** Let $A \subseteq$ some MST, $(S, V-S)$ be any cut respecting $A$, and $(u,v)$ be a light edge crossing $(S, V-S)$. Then $(u,v)$ is safe for $A$.

*Proof sketch:* If $(u,v) \notin T$ (the MST containing $A$), there exists another edge $(x,y)$ on the path from $u$ to $v$ in $T$ that crosses the cut. Since $(u,v)$ is light, $w(u,v) \leq w(x,y)$. Constructing $T' = (T - \{(x,y)\}) \cup \{(u,v)\}$ gives $w(T') \leq w(T)$, so $T'$ is an MST containing $A \cup \{(u,v)\}$.

**Corollary 21.2:** A light edge connecting two distinct components of the MST forest $G_A = (V, A)$ is safe for $A$.

### Kruskal's Algorithm

Processes edges in non-decreasing weight order. For each edge $(u,v)$: if $u$ and $v$ are in different components (FIND-SET returns different representatives), add it and merge components (UNION). Uses disjoint-set forest from Ch19.

**Running time:** Sorting $O(E\log_2 E) = O(E\log_2 V)$ (since $|E| < |V|^2$). Disjoint-set operations: $O(E\,\alpha(V)) = O(E\log_2 V)$. Total: $O(E\log_2 V)$.

### Prim's Algorithm

Maintains a single growing tree. Invariant: for all $v \in Q$ (not yet in tree), $v.\text{key}$ = minimum weight of any edge connecting $v$ to the current tree. EXTRACT-MIN gives the next safe edge.

**Running time with binary min-heap:**
- $|V|$ EXTRACT-MIN operations: $O(V\log_2 V)$
- $O(E)$ DECREASE-KEY operations: $O(E\log_2 V)$
- Total: $O(E\log_2 V)$

**Running time with Fibonacci heap:**
- EXTRACT-MIN: $O(\log_2 V)$ amortized × $V$ = $O(V\log_2 V)$
- DECREASE-KEY: $O(1)$ amortized × $O(E)$ = $O(E)$
- Total: $O(E + V\log_2 V)$ — better when $|E| = \omega(V)$

### Time and Space Complexity

| Algorithm | Time (binary heap) | Time (Fibonacci heap) | Space |
|-----------|-------------------|----------------------|-------|
| MST-KRUSKAL | $O(E\log_2 V)$ | N/A (uses union-find) | $O(V+E)$ |
| MST-PRIM | $O(E\log_2 V)$ | $O(E + V\log_2 V)$ | $O(V)$ |

---

## Key Takeaways & Next Steps

1. **Both algorithms are correct** by the cut theorem: they always add a light edge crossing a cut that respects the current $A$.
2. **Kruskal's** is better for sparse graphs in practice; it uses union-find and processes edges globally in sorted order.
3. **Prim's** is better for dense graphs; with a Fibonacci heap it achieves $O(E + V\log_2 V)$, optimal when $|E| = \omega(V)$.
4. **The generic method** unifies both: any strategy that adds safe edges produces an MST. Correctness reduces to verifying the cut theorem applies.
5. MST is used in: network design, clustering (single-linkage), Kruskal's as a subroutine in other graph algorithms.

---

### Navigation

**Previous:** [[Ch20_Elementary_Graph_Algorithms]]
**Next:** [[Ch22_Single-Source_Shortest_Paths]]
**Hub:** [[Index_Introduction_to_Algorithms]]
