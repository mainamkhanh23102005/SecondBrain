# Part VI: Graph Algorithms — Introduction

## Executive Summary

Part VI covers fundamental graph algorithms. Six chapters address the most important graph problems: **elementary graph algorithms** (Chapter 20, BFS + DFS + topological sort + SCCs), **minimum spanning trees** (Chapter 21, Kruskal and Prim), **single-source shortest paths** (Chapter 22, Bellman-Ford, Dijkstra, DAG shortest paths), **all-pairs shortest paths** (Chapter 23, Floyd-Warshall, Johnson), **maximum flow** (Chapter 24, Ford-Fulkerson, push-relabel), and **bipartite matching** (Chapter 25, stable marriage, assignment problems).

---

## Zero-Loss Extraction

### Part VI Contents

| Chapter | Topic | Key Result |
|---------|-------|-----------|
| Ch20 | Elementary Graph Algorithms | BFS $O(V+E)$; DFS $\Theta(V+E)$; topological sort; SCCs |
| Ch21 | Minimum Spanning Trees | Kruskal $O(E\log_2 V)$; Prim $O(E + V\log_2 V)$ with Fibonacci heap |
| Ch22 | Single-Source Shortest Paths | Bellman-Ford $O(VE)$; Dijkstra $O(E + V\log_2 V)$; DAG $\Theta(V+E)$ |
| Ch23 | All-Pairs Shortest Paths | Floyd-Warshall $\Theta(V^3)$; Johnson $O(V^2\log_2 V + VE)$ |
| Ch24 | Maximum Flow | Ford-Fulkerson, Edmonds-Karp $O(VE^2)$; push-relabel |
| Ch25 | Bipartite Matching | Hopcroft-Karp; stable marriage; min-cost assignment |

**Notation convention:** Inside asymptotic notation, $V$ denotes $|V|$ and $E$ denotes $|E|$. Graph $G = (V, E)$ is represented using adjacency lists (default) or adjacency matrices (all-pairs algorithms).

---

## Deep-Dive Explanations

### Graph Representations

- **Adjacency list:** Array of $|V|$ lists; $\Theta(V+E)$ space; preferred for sparse graphs ($|E| \ll |V|^2$)
- **Adjacency matrix:** $|V| \times |V|$ matrix; $\Theta(V^2)$ space; preferred for dense graphs; $O(1)$ edge lookup

### Elementary Graph Search

**BFS** computes shortest-path distances (unweighted) from a source $s$ in $O(V+E)$; produces a breadth-first tree where the path from $s$ to $v$ is a shortest path.

**DFS** runs in $\Theta(V+E)$, assigns discovery/finish timestamps, classifies edges (tree, back, forward, cross), and forms the basis for topological sort and SCC decomposition.

**Topological sort** on a DAG takes $\Theta(V+E)$: run DFS, output vertices in decreasing finish time order.

**Strongly connected components:** Two DFS runs — one on $G$, one on $G^T$ in reverse finish-time order — identify all SCCs in $\Theta(V+E)$.

---

## Key Takeaways & Next Steps

1. Graph algorithm running times are measured in two parameters: $|V|$ and $|E|$.
2. Adjacency lists are asymptotically space-efficient for sparse graphs and are the default representation.
3. BFS and DFS are the core primitives; most graph algorithms build on them.

---

### Navigation

**Previous:** [[Ch19_Data_Structures_for_Disjoint_Sets]]
**Next:** [[Ch20_Elementary_Graph_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
