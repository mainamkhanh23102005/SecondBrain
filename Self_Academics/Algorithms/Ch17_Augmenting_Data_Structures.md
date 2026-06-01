# Chapter 17: Augmenting Data Structures

## Executive Summary

Chapter 17 shows how to **augment** an existing data structure — adding extra information to each node — to support new operations efficiently. Two examples built on red-black trees are developed: **order-statistic trees** (adding $x.\text{size}$ to support OS-SELECT and OS-RANK in $O(\log_2 n)$) and **interval trees** (adding $x.\text{max}$ to support INTERVAL-SEARCH in $O(\log_2 n)$). The central result, **Theorem 17.1**, gives sufficient conditions under which augmentation of red-black trees does not degrade the $O(\log_2 n)$ insertion/deletion time: the extra attribute at node $x$ must depend only on $x$, $x.\text{left}$, and $x.\text{right}$.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**OS-SELECT** — returns the $i$-th smallest element in subtree rooted at $x$:

```
OS-SELECT(x, i)
1  r = x.left.size + 1     // rank of x within its subtree
2  if i == r
3      return x
4  elseif i < r
5      return OS-SELECT(x.left, i)
6  else return OS-SELECT(x.right, i − r)
```

**OS-RANK** — returns the rank of node $x$ in the full tree:

```
OS-RANK(T, x)
1  r = x.left.size + 1     // rank of x within its subtree
2  y = x
3  while y ≠ T.root
4      if y == y.p.right    // y is a right child
5          r = r + y.p.left.size + 1
6      y = y.p
7  return r
```

**INTERVAL-SEARCH** — finds any interval in the tree that overlaps $i$:

```
INTERVAL-SEARCH(T, i)
1  x = T.root
2  while x ≠ T.nil and i does not overlap x.int
3      if x.left ≠ T.nil and x.left.max ≥ i.low
4          x = x.left
5      else x = x.right
6  return x
```

---

## Deep-Dive Explanations

### Four-Step Augmentation Method

1. **Choose** an underlying data structure.
2. **Determine** additional information to maintain.
3. **Verify** the additional information can be maintained by basic modifying operations without asymptotic overhead.
4. **Develop** new operations.

### Order-Statistic Trees (Section 17.1)

**Augmentation:** Add attribute $x.\text{size}$ = number of internal nodes in subtree rooted at $x$.
$$x.\text{size} = x.\text{left.size} + x.\text{right.size} + 1$$
$T.\text{nil.size} = 0$.

**OS-SELECT($x$, $i$):** The rank of $x$ within its subtree is $r = x.\text{left.size} + 1$.
- If $i = r$: return $x$.
- If $i < r$: recurse into left subtree.
- If $i > r$: recurse into right subtree for element of rank $i - r$.

Running time: $O(\log_2 n)$ (follows one path down).

**OS-RANK($T$, $x$):** Start with $r = x.\text{left.size} + 1$. Walk up the tree: whenever $y$ is a right child, add $y.p.\text{left.size} + 1$ to $r$ (accounting for $y.p$ and its left subtree).

Running time: $O(\log_2 n)$ (path from $x$ to root).

**Maintaining sizes:** During insertion, increment $x.\text{size}$ for each node on the path from root down to new node: $O(\log_2 n)$ extra work. During rotation, update two nodes in $O(1)$:
```
// After LEFT-ROTATE(T, x), add:
y.size = x.size
x.size = x.left.size + x.right.size + 1
```
Total: INSERT and DELETE still $O(\log_2 n)$.

### Theorem 17.1 (Safe Augmentation of Red-Black Trees)

**Theorem:** Let $f$ be an attribute on each node $x$ where $x.f$ depends only on information in $x$, $x.\text{left}$, and $x.\text{right}$ (possibly including $x.\text{left}.f$ and $x.\text{right}.f$), and where $x.f$ can be computed in $O(1)$ time. Then INSERT and DELETE can maintain all $f$ values without asymptotically affecting their $O(\log_2 n)$ running times.

**Proof idea:** Changes to $f$ propagate only upward. After modifying a node, only ancestors need updating. Since height is $O(\log_2 n)$, updates take $O(\log_2 n)$ per insertion/deletion phase. Rotations ($\leq 2$ for insert, $\leq 3$ for delete) each take $O(\log_2 n)$ to propagate — but for locally-computed attributes (like $\text{size}$), updates are $O(1)$ per rotation.

### Interval Trees (Section 17.3)

**Augmentation:** Each node $x$ stores an interval $x.\text{int} = [x.\text{int.low}, x.\text{int.high}]$. The key is $x.\text{int.low}$. Add attribute:
$$x.\text{max} = \max\{x.\text{int.high},\; x.\text{left.max},\; x.\text{right.max}\}$$

By Theorem 17.1, this is maintainable in $O(\log_2 n)$.

**INTERVAL-SEARCH($T$, $i$):** Finds any node whose interval overlaps query interval $i = [i.\text{low}, i.\text{high}]$.
- Walk down from root.
- At each node: if left subtree's max $\geq i.\text{low}$, go left (might find overlap there); otherwise go right.

**Theorem 17.2 (Correctness):** INTERVAL-SEARCH either returns an overlapping interval or returns $T.\text{nil}$ (no overlap exists in the tree).

**Proof sketch:** If the search goes left, there is either an overlap in the left subtree, or no overlap exists in the right subtree — so going left is safe. Symmetric argument for going right.

Running time: $O(\log_2 n)$ (one path from root to leaf).

**Interval overlap test:** Intervals $i$ and $i'$ overlap iff $i.\text{low} \leq i'.\text{high}$ and $i'.\text{low} \leq i.\text{high}$.

### Time and Space Complexity

| Operation | Order-Statistic Tree | Interval Tree |
|-----------|---------------------|---------------|
| INSERT | $O(\log_2 n)$ | $O(\log_2 n)$ |
| DELETE | $O(\log_2 n)$ | $O(\log_2 n)$ |
| OS-SELECT | $O(\log_2 n)$ | N/A |
| OS-RANK | $O(\log_2 n)$ | N/A |
| INTERVAL-SEARCH | N/A | $O(\log_2 n)$ |
| Space | $O(n)$ + 1 int/node | $O(n)$ + 1 int/node |

---

## Key Takeaways & Next Steps

1. **Augmentation** extends red-black trees with extra node attributes at no asymptotic cost, as long as Theorem 17.1's conditions hold (attribute computable from node + children in $O(1)$).
2. **OS-SELECT and OS-RANK** in $O(\log_2 n)$ — the key is $x.\text{size}$ (subtree count), not rank (which changes with every insertion).
3. **INTERVAL-SEARCH** exploits $x.\text{max}$ to prune search directions: one root-to-leaf path suffices.
4. The four-step augmentation method is a reusable design pattern for many other data structures.
5. Augmentation underlies advanced structures like persistent trees, range trees, and segment trees.

---

### Navigation

**Previous:** [[PartV_Advanced_Data_Structures]]
**Next:** [[Ch18_B-Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
