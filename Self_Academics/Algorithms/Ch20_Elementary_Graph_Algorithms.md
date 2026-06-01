# Chapter 20: Elementary Graph Algorithms

## Executive Summary

Chapter 20 presents four fundamental graph algorithms built on graph search. **Graph representations** — adjacency lists ($\Theta(V+E)$ space) and adjacency matrices ($\Theta(V^2)$ space) — are compared. **Breadth-first search (BFS)** discovers all vertices reachable from a source $s$ in $O(V+E)$, computing shortest-path distances $\delta(s,v)$ (Theorem 20.5). **Depth-first search (DFS)** runs in $\Theta(V+E)$, assigns discovery/finish timestamps, classifies edges via the Parenthesis Theorem (Theorem 20.7), and underlies the remaining algorithms. **Topological sort** processes a DAG in $\Theta(V+E)$ by outputting vertices in reverse DFS finish-time order. **Strongly connected components (SCCs)** are found by two DFS passes — on $G$ then $G^T$ — in $\Theta(V+E)$ (Theorem 20.16).

---

## Zero-Loss Extraction

### Graph Representations

**Adjacency list** $G.\text{Adj}$: array of $|V|$ linked lists; $\Theta(V+E)$ space; preferred for sparse graphs. Edge weight $w(u,v)$ stored alongside $v$ in $u$'s list. Edge lookup: $O(\deg(u))$.

**Adjacency matrix** $A = (a_{ij})$: $a_{ij} = 1$ if $(i,j) \in E$, else $0$; $\Theta(V^2)$ space; $O(1)$ edge lookup; symmetric for undirected graphs.

### Core Algorithms & Pseudocode

**BFS (Breadth-First Search)** — $O(V+E)$, computes shortest-path distances:

```
BFS(G, s)
 1  for each vertex u ∈ G.V – {s}
 2      u.color = WHITE;  u.d = ∞;  u.π = NIL
 3  s.color = GRAY;  s.d = 0;  s.π = NIL
 4  Q = {s}
 5  while Q ≠ ∅
 6      u = DEQUEUE(Q)
 7      for each vertex v in G.Adj[u]
 8          if v.color == WHITE
 9              v.color = GRAY;  v.d = u.d + 1;  v.π = u
10              ENQUEUE(Q, v)
11      u.color = BLACK

PRINT-PATH(G, s, v)
1  if v == s:  print s
2  elseif v.π == NIL:  print "no path from s to v"
3  else:  PRINT-PATH(G, s, v.π);  print v
```

**DFS (Depth-First Search)** — $\Theta(V+E)$, timestamps all vertices:

```
DFS(G)
1  for each vertex u ∈ G.V
2      u.color = WHITE;  u.π = NIL
3  time = 0
4  for each vertex u ∈ G.V
5      if u.color == WHITE
6          DFS-VISIT(G, u)

DFS-VISIT(G, u)
1  time = time + 1;  u.d = time;  u.color = GRAY
2  for each vertex v in G.Adj[u]
3      if v.color == WHITE
4          v.π = u;  DFS-VISIT(G, v)
5  time = time + 1;  u.f = time;  u.color = BLACK
```

**TOPOLOGICAL-SORT** — $\Theta(V+E)$, valid only on DAGs:

```
TOPOLOGICAL-SORT(G)
1  call DFS(G) to compute finish times v.f for each vertex v
2  as each vertex is finished, insert it onto the front of a linked list
3  return the linked list of vertices
```

**STRONGLY-CONNECTED-COMPONENTS** — $\Theta(V+E)$:

```
STRONGLY-CONNECTED-COMPONENTS(G)
1  call DFS(G) to compute finish times u.f for each vertex u
2  create G^T (transpose: reverse all edges)
3  call DFS(G^T) in decreasing order of u.f from step 1
4  output each DFS tree from step 3 as a separate SCC
```

---

## Deep-Dive Explanations

### BFS Analysis and Correctness

BFS uses a FIFO queue of GRAY vertices (the frontier). Each vertex is enqueued and dequeued at most once → $O(V)$ for queue operations. Each adjacency list is scanned once → $O(E)$ total. Running time: $O(V+E)$.

**Theorem 20.5 (Correctness):** At termination, $v.d = \delta(s,v)$ for all $v \in V$. The predecessor subgraph $G_\pi$ is a breadth-first tree in which every root-to-leaf path is a shortest path in $G$.

Key lemmas: $\delta(s,v) \leq \delta(s,u)+1$ for $(u,v) \in E$ (Lemma 20.1); queue $d$-values form a non-decreasing sequence with at most two consecutive values (Lemma 20.3).

### DFS Properties

DFS timestamps each vertex $u$ with discovery time $u.d$ and finish time $u.f$, satisfying $u.d < u.f$ and $1 \leq u.d, u.f \leq 2|V|$.

**Theorem 20.7 (Parenthesis Theorem):** For any two vertices $u, v$: the intervals $[u.d, u.f]$ and $[v.d, v.f]$ are either disjoint (neither is an ancestor of the other) or one is entirely contained in the other ($u$ is an ancestor of $v$ or vice versa).

**Corollary 20.8:** $v$ is a proper descendant of $u$ iff $u.d < v.d < v.f < u.f$.

**Theorem 20.9 (White-Path Theorem):** $v$ is a descendant of $u$ in the DFS forest iff at time $u.d$ there is a path from $u$ to $v$ consisting entirely of WHITE vertices.

### Edge Classification

During DFS, edges are classified by the color of the adjacent vertex when first explored:

| Color of $v$ when $(u,v)$ explored | Edge type |
|-------------------------------------|-----------|
| WHITE | Tree edge |
| GRAY | Back edge |
| BLACK | Forward or cross edge |

**Theorem 20.10:** In DFS of an **undirected** graph, every edge is either a tree edge or a back edge (no forward or cross edges).

### Topological Sort

**Lemma 20.11:** A directed graph $G$ is acyclic iff DFS yields no back edges.

**Theorem 20.12:** TOPOLOGICAL-SORT correctly topologically sorts any DAG $G$: for any edge $(u,v) \in E$, $v.f < u.f$, so $u$ appears before $v$ in the output.

Running time: $\Theta(V+E)$ (DFS + $O(1)$ per vertex to prepend to list).

### Strongly Connected Components

**Key insight:** $G$ and $G^T$ have the same SCCs. The component graph $G^{SCC}$ is a DAG.

**Lemma 20.14:** If $(u,v) \in E$ with $u \in C'$ and $v \in C$, then $f(C') > f(C)$ (the SCC with an outgoing edge to $C$ finishes later in the first DFS).

**Corollary 20.15:** If $f(C) > f(C')$, then $G^T$ contains no edge from $C$ to $C'$.

**Theorem 20.16 (Correctness):** STRONGLY-CONNECTED-COMPONENTS correctly identifies all SCCs. The second DFS on $G^T$, starting from the highest-finish-time vertex, visits exactly one SCC per DFS tree — because edges in $G^T$ only go from already-visited components to the current one.

### Time and Space Complexity

| Algorithm | Time | Space |
|-----------|------|-------|
| BFS | $O(V+E)$ | $O(V)$ |
| DFS | $\Theta(V+E)$ | $O(V)$ (recursion stack) |
| TOPOLOGICAL-SORT | $\Theta(V+E)$ | $O(V)$ |
| STRONGLY-CONNECTED-COMPONENTS | $\Theta(V+E)$ | $O(V+E)$ for $G^T$ |
| Adjacency list | — | $\Theta(V+E)$ |
| Adjacency matrix | — | $\Theta(V^2)$ |

---

## Key Takeaways & Next Steps

1. **BFS** computes shortest paths in unweighted graphs in $O(V+E)$; key invariant: queue contains only GRAY (frontier) vertices.
2. **DFS** discovers structure via timestamps: the Parenthesis Theorem characterizes ancestor-descendant relationships, and edge classification reveals cycles.
3. **DAG iff no back edges:** Lemma 20.11 is the standard cycle detection criterion.
4. **Topological sort** = DFS + reverse finish-time order; runs in $\Theta(V+E)$.
5. **SCCs** in $\Theta(V+E)$: two DFS passes exploit the fact that the component graph is a DAG, visiting SCCs in reverse topological order on $G^T$.

---

### Navigation

**Previous:** [[PartVI_Graph_Algorithms]]
**Next:** [[Ch21_Minimum_Spanning_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
