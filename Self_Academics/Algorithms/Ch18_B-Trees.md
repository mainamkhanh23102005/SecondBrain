# Chapter 18: B-Trees

## Executive Summary

Chapter 18 presents **B-trees** — balanced search trees designed to minimize **disk accesses** rather than just CPU operations. Since disk I/O is orders of magnitude slower than RAM access, B-trees use a high branching factor $t$ (minimum degree $\geq 2$) so that the tree height $h \leq \log_t\lceil(n+1)/2\rceil$ — far shallower than a binary BST. With branching factor $t = 1000$, a B-tree of height 2 can store over one billion keys, requiring at most 2 disk accesses per search. All operations (SEARCH, INSERT, DELETE) take $O(h) = O(\log_t n)$ disk accesses and $O(th) = O(t\log_t n)$ CPU time. B-trees are the foundation of most database systems and file systems.

---

## Zero-Loss Extraction

### B-Tree Properties (Minimum Degree $t \geq 2$)

Every B-tree node $x$ satisfies:
1. $x.n$ keys stored in monotonically increasing order: $x.\text{key}_1 \leq x.\text{key}_2 \leq \cdots \leq x.\text{key}_{x.n}$
2. $x.\text{leaf}$: TRUE if $x$ is a leaf
3. Internal nodes have $x.n + 1$ children $x.c_1, x.c_2, \ldots, x.c_{x.n+1}$
4. Keys separate child subtree ranges: $k_1 \leq x.\text{key}_1 \leq k_2 \leq \cdots \leq x.\text{key}_{x.n} \leq k_{x.n+1}$
5. **All leaves at the same depth** (height $h$)
6. **Key count bounds:** every non-root node has $t-1$ to $2t-1$ keys; root has $1$ to $2t-1$ keys. A **full node** has exactly $2t-1$ keys.

### Core Algorithms & Pseudocode

**B-TREE-SEARCH** ($O(t\log_t n)$ CPU, $O(\log_t n)$ disk accesses):

```
B-TREE-SEARCH(x, k)
1  i = 1
2  while i ≤ x.n and k > x.key_i
3      i = i + 1
4  if i ≤ x.n and k == x.key_i
5      return (x, i)          // found
6  elseif x.leaf
7      return NIL              // not found
8  else DISK-READ(x.c_i)
9       return B-TREE-SEARCH(x.c_i, k)
```

**B-TREE-CREATE** ($O(1)$ disk ops):

```
B-TREE-CREATE(T)
1  x = ALLOCATE-NODE()
2  x.leaf = TRUE;  x.n = 0
3  DISK-WRITE(x)
4  T.root = x
```

**B-TREE-SPLIT-CHILD** — splits full child $x.c_i$ around its median key:

```
B-TREE-SPLIT-CHILD(x, i)
 1  y = x.c_i                          // full node to split
 2  z = ALLOCATE-NODE()                // z takes upper half of y
 3  z.leaf = y.leaf;  z.n = t − 1
 4  for j = 1 to t − 1
 5      z.key_j = y.key_{j+t}          // z gets y's greatest keys
 6  if not y.leaf
 7      for j = 1 to t
 8          z.c_j = y.c_{j+t}          // z gets corresponding children
 9  y.n = t − 1                        // y keeps t − 1 keys
10  for j = x.n + 1 downto i + 1
11      x.c_{j+1} = x.c_j             // shift parent's children right
12  x.c_{i+1} = z
13  for j = x.n downto i
14      x.key_{j+1} = x.key_j         // shift parent's keys right
15  x.key_i = y.key_t                  // insert y's median into parent
16  x.n = x.n + 1
17  DISK-WRITE(y);  DISK-WRITE(z);  DISK-WRITE(x)
```

**B-TREE-INSERT** — single downward pass, splits full nodes proactively:

```
B-TREE-INSERT(T, k)
1  r = T.root
2  if r.n == 2t − 1               // root is full → grow tree height
3      s = ALLOCATE-NODE()
4      T.root = s
5      s.leaf = FALSE;  s.n = 0
6      s.c_1 = r
7      B-TREE-SPLIT-CHILD(s, 1)
8      B-TREE-INSERT-NONFULL(s, k)
9  else B-TREE-INSERT-NONFULL(r, k)

B-TREE-INSERT-NONFULL(x, k)
1  i = x.n
2  if x.leaf
3      while i ≥ 1 and k < x.key_i
4          x.key_{i+1} = x.key_i;  i = i − 1
5      x.key_{i+1} = k;  x.n = x.n + 1
6      DISK-WRITE(x)
7  else while i ≥ 1 and k < x.key_i
8           i = i − 1
9       i = i + 1
10      DISK-READ(x.c_i)
11      if x.c_i.n == 2t − 1        // child is full → split first
12          B-TREE-SPLIT-CHILD(x, i)
13          if k > x.key_i
14              i = i + 1
15      B-TREE-INSERT-NONFULL(x.c_i, k)
```

---

## Deep-Dive Explanations

### Why B-Trees: The Disk Access Problem

Disk access time (~4 ms) is $\sim 100{,}000\times$ slower than RAM access (~50 ns). The key metric for disk-based algorithms is **number of disk blocks read/written**, not CPU operations. 

B-tree nodes are sized to equal one disk block ($\sim 4$KB). With keys of a few bytes, this gives $t \approx 500\text{–}2000$. Result: a tree of height 2 stores $\sim (2t-1)(2t) \geq 10^6$ to $4\times10^9$ keys, requiring at most 2 disk reads per search (root stays in RAM).

### Height Bound (Theorem 18.1)

For an $n$-key B-tree with minimum degree $t \geq 2$:
$$h \leq \log_t \frac{n+1}{2}$$

**Proof:** At depth $d$, the tree has $\geq 2t^{d-1}$ nodes (root has $\geq 1$ key; others have $\geq t-1$ keys, so $\geq t$ children).

Minimum keys: $n \geq 1 + (t-1)\sum_{d=1}^{h} 2t^{d-1} = 1 + 2(t-1)\cdot\frac{t^h-1}{t-1} = 2t^h - 1$.

So $t^h \leq (n+1)/2$, giving $h \leq \log_t\frac{n+1}{2}$. $\square$

**Comparison:** Red-black trees: $h = O(\log_2 n)$. B-trees: $h = O(\log_t n)$. Factor of $\log_2 t$ fewer disk accesses.

### Insertion: One-Pass with Proactive Splitting

B-tree insertion proceeds in a **single downward pass** (no backtracking):
1. While descending, split any full node ($2t-1$ keys) before entering it.
2. This guarantees the current node's parent is never full when we need to push up a median.
3. At the leaf, insert the key directly (leaf is guaranteed non-full).

If the root is full, create a new empty root and split the old root — this is the only way the tree height increases.

### Disk I/O Analysis

| Operation | Disk accesses | CPU time |
|-----------|--------------|----------|
| B-TREE-SEARCH | $O(h) = O(\log_t n)$ | $O(t \log_t n)$ |
| B-TREE-INSERT | $O(h) = O(\log_t n)$ | $O(t \log_t n)$ |
| B-TREE-DELETE | $O(h) = O(\log_t n)$ | $O(t \log_t n)$ |
| B-TREE-CREATE | $O(1)$ | $O(1)$ |

Where $h \leq \log_t\frac{n+1}{2}$.

### B-Tree Variants

- **B+-trees:** Store all satellite data in leaves; internal nodes contain only keys and child pointers. Maximizes internal node branching factor. Most database systems (MySQL InnoDB, PostgreSQL) use B+-trees.
- **2-3-4 trees:** B-tree with $t = 2$ (nodes have 2, 3, or 4 children). Equivalent to red-black trees.

---

## Key Takeaways & Next Steps

1. **B-trees optimize disk I/O** by packing many keys per node: height $h = O(\log_t n)$ replaces $O(\log_2 n)$, saving a factor of $\log_2 t$ disk accesses.
2. **Branching factor $t$** is chosen so one B-tree node = one disk block; typically $t \in [500, 2000]$.
3. **Insertion uses proactive splitting**: descend once, splitting full nodes, so no backtracking is needed.
4. **Deletion** (not shown in pseudocode here) is more complex: may need to merge nodes or redistribute keys, but still $O(\log_t n)$ disk accesses.
5. B-trees (especially B+-trees) are the backbone of every production relational database and file system.

---

### Navigation

**Previous:** [[Ch17_Augmenting_Data_Structures]]
**Next:** [[Ch19_Data_Structures_for_Disjoint_Sets]]
**Hub:** [[Index_Introduction_to_Algorithms]]
