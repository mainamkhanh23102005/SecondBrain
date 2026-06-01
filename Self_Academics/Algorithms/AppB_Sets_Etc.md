# Appendix B — Sets, Relations, Functions, and Graphs

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #mathematics #sets #relations #functions #graphs #discrete-math

---

## Executive Summary

Appendix B is the discrete-mathematics vocabulary layer for the entire book. Before analyzing any graph algorithm or reasoning about data structures, you need a shared language for sets, relations, functions, graphs, and trees. Five sections build this foundation:

| Section | Topic | Key Objects |
|---------|-------|-------------|
| B.1 | Sets | Membership, operations, cardinality, Cartesian product |
| B.2 | Relations | Equivalence relations, partial orders, total orders |
| B.3 | Functions | Injection, surjection, bijection, inverse |
| B.4 | Graphs | Directed/undirected, paths, connectivity, SCC |
| B.5 | Trees | Free trees, rooted trees, binary trees, complete $k$-ary trees |

---

## Zero-Loss Extraction

### §B.1 — Sets

**Membership and equality.**  
$x \in S$ means $x$ belongs to $S$; $x \notin S$ means it does not. Two sets are equal iff they contain the same elements (order and repetition irrelevant: $\{1,2,3,1\} = \{3,2,1\}$).

**Special sets:**  
$\emptyset$ (empty), $\mathbb{Z}$ (integers), $\mathbb{R}$ (reals), $\mathbb{N}$ (naturals $= \{0,1,2,\ldots\}$).

**Subset relations:**  
- $A \subseteq B$: every element of $A$ is in $B$ (subset).  
- $A \subset B$: $A \subseteq B$ and $A \ne B$ (proper subset).  
- $\emptyset \subseteq A$ for every set $A$; $A \subseteq A$ always.  
- $A = B \iff A \subseteq B \text{ and } B \subseteq A$.

**Set operations:**

| Operation | Notation | Definition |
|-----------|----------|-----------|
| Intersection | $A \cap B$ | $\{x : x \in A \text{ and } x \in B\}$ |
| Union | $A \cup B$ | $\{x : x \in A \text{ or } x \in B\}$ |
| Difference | $A - B$ | $\{x : x \in A \text{ and } x \notin B\}$ |
| Complement | $\bar{A}$ | $U - A$ (universe $U$ assumed) |

**Algebraic laws** (all are equalities):

| Law | Instance |
|-----|---------|
| Empty | $A \cap \emptyset = \emptyset$; $A \cup \emptyset = A$ |
| Idempotency | $A \cap A = A$; $A \cup A = A$ |
| Commutative | $A \cap B = B \cap A$ |
| Associative | $A \cap (B \cap C) = (A \cap B) \cap C$ |
| Distributive | $A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$ |
| Absorption | $A \cap (A \cup B) = A$ |
| DeMorgan | $\overline{A \cap B} = \bar{A} \cup \bar{B}$; $\overline{A \cup B} = \bar{A} \cap \bar{B}$ |

**Cardinality and countability.**  
- $|S|$: number of elements; $|\emptyset| = 0$.  
- Two sets have the same cardinality iff a bijection exists between them.  
- *Finite* if $|S| \in \mathbb{N}$; *countably infinite* if bijects with $\mathbb{N}$; *uncountable* otherwise.  
  - $\mathbb{Z}$ is countable; $\mathbb{R}$ is uncountable.  
- **Inclusion-exclusion (2 sets):** $|A \cup B| = |A| + |B| - |A \cap B|$, so $|A \cup B| \le |A| + |B|$.  
- If $A \subseteq B$ then $|A| \le |B|$.

**Power set.** $2^S$ = set of all subsets of $S$; $|2^S| = 2^{|S|}$.

**Ordered structures.**  
- **Ordered pair**: $(a,b) \ne (b,a)$ (formally $\{a,\{a,b\}\}$).  
- **Cartesian product**: $A \times B = \{(a,b) : a \in A,\ b \in B\}$; $|A \times B| = |A| \cdot |B|$.  
- $n$-fold product $A^n = A \times \cdots \times A$; $|A^n| = |A|^n$.  
- **Intervals** over $\mathbb{R}$ (or $\mathbb{Z}$): $[a,b]$ closed, $(a,b)$ open, $[a,b)$ and $(a,b]$ half-open.

---

### §B.2 — Relations

A **binary relation** $R$ on sets $A$ and $B$ is a subset of $A \times B$; we write $a\,R\,b$ when $(a,b) \in R$. An *$n$-ary relation* on $A_1,\ldots,A_n$ is a subset of $A_1 \times \cdots \times A_n$.

**Properties of $R \subseteq A \times A$:**

| Property | Condition |
|----------|-----------|
| Reflexive | $a\,R\,a$ for all $a \in A$ |
| Symmetric | $a\,R\,b \Rightarrow b\,R\,a$ |
| Transitive | $a\,R\,b \wedge b\,R\,c \Rightarrow a\,R\,c$ |
| Antisymmetric | $a\,R\,b \wedge b\,R\,a \Rightarrow a = b$ |

**Equivalence relation** = reflexive + symmetric + transitive.  
- **Equivalence class** of $a$: $[a] = \{b \in A : a\,R\,b\}$.

**Theorem B.1 (Equivalence Relation $\Leftrightarrow$ Partition).**  
The equivalence classes of any equivalence relation $R$ on $A$ form a *partition* of $A$ (nonempty, pairwise-disjoint, union = $A$), and any partition of $A$ determines a unique equivalence relation whose classes are the partition sets.

*Proof sketch.*  
- Classes are nonempty (reflexivity: $a \in [a]$); cover $A$ (same reason); pairwise disjoint: if $c \in [a] \cap [b]$, then $a\,R\,c$ and $b\,R\,c$, so by symmetry $c\,R\,b$ and by transitivity $a\,R\,b$, giving $[a] = [b]$.  
- Converse: define $(a,b) \in R$ iff $a,b$ in the same part; reflexivity, symmetry, transitivity all follow from the partition property. $\blacksquare$

**Partial order** = reflexive + antisymmetric + transitive → defines a **poset** (partially ordered set).  
- *Maximal element*: no other element is strictly above it (may not be unique).  
- **Total (linear) order**: partial order where every pair is comparable.  
- **Total preorder**: total relation that is transitive (without requiring antisymmetry).

---

### §B.3 — Functions

A **function** $f : A \to B$ is a binary relation such that for every $a \in A$ there is *exactly one* $b \in B$ with $(a,b) \in f$, written $b = f(a)$.  
- $A$ = domain; $B$ = codomain.  
- **Image of $A' \subseteq A$**: $f(A') = \{b \in B : b = f(a) \text{ for some } a \in A'\}$.  
- **Range** = $f(A)$ (image of entire domain; may be a proper subset of codomain).

**Classification:**

| Type | Definition | Finite-set implication |
|------|-----------|----------------------|
| **Surjection** (onto) | Range = Codomain | $\|A\| \ge \|B\|$ |
| **Injection** (one-to-one) | $a \ne a' \Rightarrow f(a) \ne f(a')$ | $\|A\| \le \|B\|$ |
| **Bijection** | Injective and surjective | $\|A\| = \|B\|$ |
| **Permutation** | Bijection from a set to itself | |

**Inverse.** For bijective $f$: $f^{-1}(b) = a \iff f(a) = b$.

**Sequences.** A finite sequence of length $n$ is $f : \{0,\ldots,n-1\} \to V$, written $\langle f(0), \ldots, f(n-1) \rangle$. An infinite sequence has domain $\mathbb{N}$.

---

### §B.4 — Graphs

**Directed graph** (digraph) $G = (V, E)$: $V$ is the finite vertex set; $E \subseteq V \times V$ is the edge set. Self-loops (edges $(v,v)$) are allowed.

**Undirected graph** $G = (V, E)$: $E$ is a set of unordered pairs $\{u,v\}$ with $u \ne v$. Convention: write $(u,v)$ and note $(u,v) = (v,u)$. No self-loops.

**Degree.**  
- *Undirected*: $\deg(v)$ = number of edges incident on $v$. Isolated vertex: $\deg = 0$.  
- *Directed*: $\text{in-deg}(v)$ = edges entering; $\text{out-deg}(v)$ = edges leaving; $\deg = \text{in-deg} + \text{out-deg}$.

**Paths and reachability.**  
A **path** of length $k$ from $u$ to $u'$: sequence $\langle v_0, v_1, \ldots, v_k \rangle$ with $v_0 = u$, $v_k = u'$, and each $(v_{i-1}, v_i) \in E$.  
- **Simple path**: all vertices distinct.  
- $u'$ is **reachable** from $u$ (written $u \overset{*}{\leadsto} u'$) if a path exists.  
- **Subpath**: contiguous subsequence $\langle v_i, v_{i+1}, \ldots, v_j \rangle$ of a path.

**Cycles.**  
- *Directed*: path $\langle v_0, \ldots, v_k \rangle$ with $v_0 = v_k$ and $\ge 1$ edge; *simple* if $v_1, \ldots, v_k$ are distinct. A self-loop is a cycle of length 1.  
- *Undirected*: path with $v_0 = v_k$, $k > 0$, all edges distinct; *simple* if $v_1, \ldots, v_k$ distinct.  
- **Acyclic graph**: contains no simple cycles.

**Connectivity.**  
- *Undirected*: **connected** if every vertex is reachable from every other; **connected components** = equivalence classes of "is reachable from."  
- *Directed*: **strongly connected** if every pair of vertices is mutually reachable; **strongly connected components (SCCs)** = equivalence classes of "mutually reachable." $G$ is strongly connected iff it has exactly one SCC.

**Graph isomorphism.** $G = (V,E)$ and $G' = (V',E')$ are **isomorphic** if there exists a bijection $f : V \to V'$ such that $(u,v) \in E \iff (f(u), f(v)) \in E'$.

**Subgraphs and induced subgraphs.**  
$G' = (V',E')$ is a **subgraph** of $G$ if $V' \subseteq V$ and $E' \subseteq E$.  
The **induced subgraph** on $V' \subseteq V$: $E' = \{(u,v) \in E : u,v \in V'\}$.

**Directed / undirected versions.**  
- *Directed version* of undirected $G$: replace each edge $(u,v)$ with $(u,v)$ and $(v,u)$.  
- *Undirected version* of directed $G$: include $(u,v)$ iff $u \ne v$ and $E$ contains $(u,v)$ or $(v,u)$ (or both); each pair appears once.  
- *Neighbor* in a directed graph: $v$ is a neighbor of $u$ if $(u,v) \in E$ or $(v,u) \in E$.

**Special graph types:**

| Type | Definition |
|------|-----------|
| **Complete** | Every pair of vertices adjacent (undirected) |
| **Bipartite** | $V$ partitions into $V_1, V_2$; all edges go between $V_1$ and $V_2$ |
| **Forest** | Acyclic undirected graph |
| **Free tree** | Connected acyclic undirected graph |
| **DAG** | Directed acyclic graph |
| **Multigraph** | Undirected; allows multiple edges between the same pair and self-loops |
| **Hypergraph** | Each "hyperedge" connects an arbitrary subset of vertices |

**Edge contraction.** Contracting edge $(u,v)$: merge $u$ and $v$ into a new vertex $x$, removing $(u,v)$ and replacing every edge to $u$ or $v$ with an edge to $x$.

---

### §B.5 — Trees

**Free tree:** A connected, acyclic, undirected graph. A *forest* is acyclic but possibly disconnected.

**Theorem B.2 — Six equivalent characterizations of a free tree.** For undirected $G = (V,E)$, the following are equivalent:

1. $G$ is a free tree.
2. Any two vertices in $G$ are connected by a unique simple path.
3. $G$ is connected, but removing any single edge disconnects it.
4. $G$ is connected and $|E| = |V| - 1$.
5. $G$ is acyclic and $|E| = |V| - 1$.
6. $G$ is acyclic, but adding any edge creates a cycle.

**Rooted tree:** A free tree with one distinguished vertex (the *root*). Vocabulary:

| Term | Definition |
|------|-----------|
| Parent of $x$ | Unique vertex immediately above $x$ on the root-to-$x$ path |
| Child of $x$ | Any vertex $y$ whose parent is $x$ |
| Ancestor of $x$ | Any vertex on the root-to-$x$ path (including $x$ itself) |
| Leaf (external node) | A node with no children |
| Internal node | A nonleaf |
| Degree of $x$ | Number of children of $x$ (in rooted tree; excludes parent) |
| Depth of $x$ | Length of path from root to $x$ |
| Height of $x$ | Edges on longest downward path from $x$ to a leaf |
| Height of tree | Height of root = maximum depth of any node |

**Ordered tree:** A rooted tree in which the children of each node are linearly ordered (first child, second child, …). Two rooted trees may be identical as rooted trees but different as ordered trees.

**Binary tree:** Defined recursively — either the empty tree (NIL) or a root with a *left subtree* and a *right subtree* (each also a binary tree). Key distinction from ordered trees: a single child is explicitly a *left* child or a *right* child — position matters.

**Full binary tree:** Every node is either a leaf or has exactly 2 children. Represents a binary tree by replacing missing children with external (square-leaf) nodes.

**Positional tree / $k$-ary tree:** Children labeled with distinct positive integers $1, \ldots, k$; child $i$ is absent if unlabeled. Binary tree = $k$-ary with $k = 2$.

**Complete $k$-ary tree of height $h$:**
- All leaves at depth $h$; all internal nodes have degree $k$.
- Leaves: $k^h$. Height given $n$ leaves: $\log_k n$.
- Internal nodes: $\displaystyle\frac{k^h - 1}{k - 1}$.
- Binary ($k=2$): $2^h - 1$ internal nodes, $2^h$ leaves.

---

## Deep-Dive Explanations

### Theorem B.1: Why Equivalence Relations and Partitions Are the Same Thing

The proof has two directions:

**Relation → partition.** Reflexivity guarantees each class $[a]$ is nonempty and that $A = \bigcup_a [a]$. Disjointness: if $c \in [a] \cap [b]$, then $a\,R\,c$ and $b\,R\,c$; by symmetry $c\,R\,b$; by transitivity $a\,R\,b$; hence $[a] = [b]$.

**Partition → relation.** Define $(a,b) \in R$ iff $a,b$ share a part. This is trivially reflexive (each element is in its own part), symmetric (membership is mutual), and transitive (if $a,b$ share part $A_i$ and $b,c$ share part $A_j$, then $A_i = A_j$ since $b$ belongs to exactly one part, so $a,c$ share a part).

**Algorithmic relevance:** Union-Find (Chapter 19) is the concrete data structure for maintaining equivalence classes under a dynamic equivalence relation. `Union(x,y)` merges the classes containing $x$ and $y$; `Find(x)` returns the representative of $x$'s class.

### Bijection, Pigeonhole, and Counting Arguments

The size inequalities for injections and surjections give "pigeonhole" reasoning:
- **Injection $f: A \to B$** implies $|A| \le |B|$: distinct elements of $A$ map to distinct elements of $B$.
- **Surjection $f: A \to B$** implies $|A| \ge |B|$: every element of $B$ has at least one preimage.
- **Pigeonhole principle** (contrapositive): if $|A| > |B|$ then no injection $A \to B$ exists — two elements of $A$ must collide.

In hashing (Chapter 11): any hash function $h : U \to \{0,\ldots,m-1\}$ with $|U| > m$ *must* have collisions. Universal hashing randomizes which elements collide, making collisions unlikely in expectation.

### Theorem B.2: Why All Six Tree Characterizations Are Equivalent

The proof is a ring of implications $(1)\Rightarrow(2)\Rightarrow(3)\Rightarrow(4)\Rightarrow(5)\Rightarrow(6)\Rightarrow(1)$:

- **(1)→(2):** Connectivity gives a path. Uniqueness by contradiction: if two distinct simple paths exist from $u$ to $v$, find divergence point $w$ and reconvergence point $z$; the path $w \to \cdots \to z$ via $p_1$ plus the reverse via $p_2$ forms a cycle, contradicting acyclicity.
- **(3)→(4):** Lower bound $|E| \ge |V|-1$ from Exercise B.4-3. Inductive proof of $|E| \le |V|-1$: removing any edge yields 2 components satisfying (3), so by induction each has $\le |V_i|-1$ edges; together $\le |V|-2$; adding the removed edge gives $|E| \le |V|-1$.
- **(4)→(5):** A cycle of $k$ vertices can be extended to all $|V|$ vertices while keeping edges $= $ vertices, yielding $|E| \ge |V|$, contradicting $|E| = |V|-1$.
- **(5)→(6):** With $k$ components, $|E| = |V|-k$, so $k=1$ (single tree). Any added edge connects two already-connected vertices, creating a second path and hence a cycle.

**Algorithmic use:** Conditions (4) and (5) are the operational tests in spanning tree algorithms (Kruskal: grow forest with $|E|=|V|-1$; Prim: no cycle = acyclicity). Condition (2) underlies unique tree paths used in LCA and heavy-path decomposition.

### Graphs as Binary Relations

A directed graph $G = (V, E)$ is literally the pair of a set $V$ and a binary relation $E$ on $V$. Graph vocabulary is relational vocabulary:

| Graph term | Relational reading |
|-----------|-------------------|
| Self-loop at every vertex | $E$ is reflexive |
| Undirected graph | $E$ is symmetric |
| Transitive closure of $E$ | Reachability relation on $V$ |
| SCC | Equivalence class under "mutually reachable" (an equivalence relation on $V$) |

Chapter 20 algorithms (BFS, DFS, SCC decomposition) all compute properties of this relation.

---

## Key Takeaways & Next Steps

| Concept | One-Line Definition | Appears In |
|---------|-------------------|-----------|
| Partition / Equivalence class | Pairwise-disjoint covering subsets; $[a] = \{b : a\,R\,b\}$ | Union-Find (Ch. 19), SCCs (Ch. 20) |
| Partial order / Total order | Reflexive + antisymmetric + transitive; total if all pairs comparable | Priority queues, topological sort (Ch. 20) |
| Bijection | One-to-one correspondence; $\|A\| = \|B\|$ | Counting arguments, algorithm proofs |
| Pigeonhole | $\|A\| > \|B\| \Rightarrow$ no injection exists | Hashing lower bounds (Ch. 11) |
| Reachability | $u' $ reachable from $u$ via a path | BFS/DFS (Ch. 20), shortest paths (Ch. 22) |
| SCC | Maximal mutually-reachable vertex set | Kosaraju / Tarjan (Ch. 20) |
| DAG | Directed acyclic graph | Topological sort (Ch. 20), DP (Ch. 14) |
| Bipartite | $V$ splits into two sides; all edges cross | Bipartite matching (Ch. 25) |
| Free tree | Connected acyclic undirected graph; $|E| = |V|-1$ | Spanning trees (Ch. 21), MST (Kruskal/Prim) |
| Rooted tree | Free tree with distinguished root; depth / height defined | BSTs (Ch. 12), heaps (Ch. 6), all tree DS |
| Binary tree | Left/right child distinction; defined recursively | Red-Black trees (Ch. 13), BSTs (Ch. 12) |
| Complete $k$-ary tree | All leaves at depth $h$; $k^h$ leaves; height $= \log_k n$ | Heap structure (Ch. 6), merge trees |

**Key principles:**
1. **Set equality via double-containment:** to prove $A = B$, show $A \subseteq B$ and $B \subseteq A$.
2. **Equivalence class disjointness** is proved by a two-step transitivity chain — memorize that argument.
3. **Injection/surjection size lemmas** are the tools for counting arguments throughout the book.
4. **Graph = relation:** whenever you encounter a graph algorithm, translate its concepts back to the relational definitions here.

---

### Navigation

**Previous:** [[AppA_Summations]]  
**Next:** [[AppC_Counting_and_Probability]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
