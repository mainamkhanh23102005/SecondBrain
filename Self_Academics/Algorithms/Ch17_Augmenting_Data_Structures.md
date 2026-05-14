# Chapter 17: Augmenting Data Structures

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #red-black-trees #augmentation #interval-trees #order-statistics

## Overview

**Augmenting** a data structure means adding extra information to existing nodes so that new operations can be supported efficiently. This chapter augments red-black trees in two ways: order-statistic trees (supporting rank queries) and interval trees (supporting interval overlap queries). The key insight: as long as the extra attribute at each node can be computed from the node and its children in $O(1)$, INSERT and DELETE remain $O(\log_2 n)$.

---

## 17.1 Dynamic Order Statistics

An **order-statistic tree** is a red-black tree where each node $x$ stores an additional field:

$$x.\text{size} = \text{number of nodes in the subtree rooted at } x$$

**Identity:**
$$x.\text{size} = x.\text{left.size} + x.\text{right.size} + 1$$

Sentinel nil nodes have `nil.size = 0`.

### OS-SELECT: Find the $i$th Smallest

```
OS-SELECT(x, i)
1  r = x.left.size + 1          // rank of x within its subtree
2  if i == r
3      return x
4  elseif i < r
5      return OS-SELECT(x.left, i)
6  else
7      return OS-SELECT(x.right, i - r)
```

**Complexity:** $O(\log_2 n)$ — descends one level at each step.

**Logic:** $r$ is the rank of $x$ within its own subtree. If $i = r$, $x$ is the answer. If $i < r$, recurse into the left subtree. If $i > r$, recurse into the right subtree looking for rank $i - r$.

### OS-RANK: Find the Rank of a Node

```
OS-RANK(T, x)
1  r = x.left.size + 1
2  y = x
3  while y ≠ T.root
4      if y == y.p.right
5          r = r + y.p.left.size + 1
6      y = y.p
7  return r
```

**Complexity:** $O(\log_2 n)$ — walks up to the root.

**Logic:** Start with rank = size of $x$'s left subtree + 1. As we climb upward, whenever $x$ is a right child, add the left subtree size of the parent plus 1 (the parent itself).

---

## 17.2 Maintaining Subtree Sizes

### During INSERT

**Phase 1 (BST insert):** Walking down from root to insertion point, increment `x.size` for each node on the path. Since path length is $O(\log_2 n)$, this costs $O(\log_2 n)$.

**Phase 2 (fixup via rotations):** Each rotation modifies `size` for only 2 nodes in $O(1)$.

Add to LEFT-ROTATE after adjusting $x$ and $y$'s parent pointers:
```
y.size = x.size
x.size = x.left.size + x.right.size + 1
```

### During DELETE

Symmetric to insert: decrement sizes along the path walked during delete's BST phase; update during rotations.

---

## 17.3 Augmenting Red-Black Trees (General Theorem)

**Theorem 17.1:** Let $f$ be an attribute for each node in a red-black tree augmented beyond the usual `color`, `key`, `left`, `right`, `p` fields. Suppose $f(x)$ can be computed from only $x$, $x.\text{left}$, and $x.\text{right}$, including $f(x.\text{left})$ and $f(x.\text{right})$, in $O(1)$ time. Then INSERT and DELETE can maintain $f$ for all nodes in $O(\log_2 n)$ time without asymptotically affecting their performance.

**Proof sketch:**
- INSERT and DELETE change only $O(\log_2 n)$ nodes (along the root-to-leaf path + rotations).
- Each rotation involves $O(1)$ nodes and updates propagate upward at most $O(\log_2 n)$ levels.
- Since $f(x)$ is computable in $O(1)$ from children's $f$ values, each node update costs $O(1)$.

**Design recipe for augmentation:**
1. Choose an underlying data structure (e.g., red-black tree)
2. Determine what additional information to store at each node
3. Verify that this information can be maintained during INSERT and DELETE in $O(\log_2 n)$
4. Develop new operations using the stored information

---

## 17.4 Interval Trees

**Problem:** Maintain a dynamic set of intervals $[l_i, r_i]$ and support:
- **INSERT(T, x):** Insert interval $x.\text{int} = [x.\text{int.low}, x.\text{int.high}]$
- **DELETE(T, x):** Delete interval
- **INTERVAL-SEARCH(T, i):** Find any interval in $T$ that overlaps with $i = [i.\text{low}, i.\text{high}]$

Two intervals $[a, b]$ and $[c, d]$ overlap iff $a \leq d$ and $c \leq b$ (i.e., neither is entirely to the left of the other).

### Augmentation

**Key:** $x.\text{int.low}$ (BST key) + $x.\text{max}$ = maximum high endpoint in subtree rooted at $x$.

$$x.\text{max} = \max(x.\text{int.high},\ x.\text{left.max},\ x.\text{right.max})$$

This satisfies Theorem 17.1: $x.\text{max}$ depends only on $x$ and its children.

### INTERVAL-SEARCH

```
INTERVAL-SEARCH(T, i)
1  x = T.root
2  while x ≠ T.nil and i does not overlap x.int
3      if x.left ≠ T.nil and x.left.max ≥ i.low
4          x = x.left
5      else
6          x = x.right
7  return x
```

**Complexity:** $O(\log_2 n)$.

**Correctness:** The algorithm either finds an overlapping interval or correctly determines none exists.
- If we go left: there exists an overlapping interval in the left subtree (or nowhere). Because `x.left.max ≥ i.low`, some interval in the left subtree has its high endpoint ≥ `i.low`. If none overlaps, every interval in the left subtree has high < `i.low`... but then `x.left.max < i.low` — contradiction. So the left subtree must contain an overlap.
- If we go right: no overlap exists in the left subtree (since `x.left.max < i.low`).

---

## Summary

| Structure | Augmentation | New Operations | Complexity |
|---|---|---|---|
| Order-statistic tree | `x.size` = subtree size | OS-SELECT, OS-RANK | $O(\log_2 n)$ |
| Interval tree | `x.max` = max high endpoint | INTERVAL-SEARCH | $O(\log_2 n)$ |

**Key principle (Theorem 17.1):** If the extra attribute at each node is computable in $O(1)$ from the node and its children, augmented INSERT/DELETE remain $O(\log_2 n)$.

---

### Navigation
**Previous:** [[Part5_Introduction_Advanced_Data_Structures]]
**Next:** [[Ch18_B_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
