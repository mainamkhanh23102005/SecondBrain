# Chapter 12: Binary Search Trees

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #binary-search-tree #BST

## Overview

A **binary search tree (BST)** supports all dynamic-set operations in $O(h)$ time, where $h$ is the tree's height. For a balanced tree, $h = O(\log_2 n)$; in the worst case (degenerate tree), $h = \Theta(n)$.

---

## 12.1 BST Property

**Binary-search-tree property:** For any node $x$:
- All keys in the **left subtree** of $x$ are $\leq x.\text{key}$
- All keys in the **right subtree** of $x$ are $\geq x.\text{key}$

Each node stores: `key`, `left`, `right`, `p` (parent), and optional satellite data.

### Inorder Tree Walk

Visits nodes in sorted order — left subtree, then root, then right subtree.

```
INORDER-TREE-WALK(x)
1  if x ≠ NIL
2      INORDER-TREE-WALK(x.left)
3      print x.key
4      INORDER-TREE-WALK(x.right)
```

**Theorem 12.1:** Takes $\Theta(n)$ time on an $n$-node BST.

---

## 12.2 Querying a BST

All query operations run in $O(h)$ time.

### Search

```
TREE-SEARCH(x, k)           // recursive
1  if x == NIL or k == x.key
2      return x
3  if k < x.key
4      return TREE-SEARCH(x.left, k)
5  else return TREE-SEARCH(x.right, k)

ITERATIVE-TREE-SEARCH(x, k) // preferred (avoids call overhead)
1  while x ≠ NIL and k ≠ x.key
2      if k < x.key
3          x = x.left
4      else x = x.right
5  return x
```

### Minimum and Maximum

```
TREE-MINIMUM(x)    // follow left pointers
1  while x.left ≠ NIL
2      x = x.left
3  return x

TREE-MAXIMUM(x)    // follow right pointers
1  while x.right ≠ NIL
2      x = x.right
3  return x
```

### Successor

```
TREE-SUCCESSOR(x)
1  if x.right ≠ NIL
2      return TREE-MINIMUM(x.right)   // leftmost in right subtree
3  else
4      y = x.p
5      while y ≠ NIL and x == y.right
6          x = y
7          y = y.p
8      return y    // lowest ancestor whose left child is also an ancestor of x
```

**Theorem 12.2:** SEARCH, MINIMUM, MAXIMUM, SUCCESSOR, PREDECESSOR all run in $O(h)$ time.

---

## 12.3 Insertion and Deletion

### Insertion

```
TREE-INSERT(T, z)
1  x = T.root
2  y = NIL              // y trails x (will be z's parent)
3  while x ≠ NIL
4      y = x
5      if z.key < x.key
6          x = x.left
7      else x = x.right
8  z.p = y
9  if y == NIL
10     T.root = z       // tree was empty
11 elseif z.key < y.key
12     y.left = z
13 else y.right = z
```

Runs in $O(h)$ time.

### Deletion

Deleting node $z$ has three cases:
1. **$z$ has no left child:** Replace $z$ with its right child (possibly NIL)
2. **$z$ has no right child:** Replace $z$ with its left child
3. **$z$ has two children:** Find successor $y$ (leftmost in right subtree, so $y$ has no left child); splice $y$ out and put $y$ in $z$'s place

The **TRANSPLANT** subroutine replaces subtree rooted at $u$ with subtree rooted at $v$:

```
TRANSPLANT(T, u, v)
1  if u.p == NIL
2      T.root = v
3  elseif u == u.p.left
4      u.p.left = v
5  else u.p.right = v
6  if v ≠ NIL
7      v.p = u.p
```

```
TREE-DELETE(T, z)
1  if z.left == NIL
2      TRANSPLANT(T, z, z.right)
3  elseif z.right == NIL
4      TRANSPLANT(T, z, z.left)
5  else y = TREE-MINIMUM(z.right)   // z's successor
6      if y ≠ z.right
7          TRANSPLANT(T, y, y.right)
8          y.right = z.right
9          y.right.p = y
10     TRANSPLANT(T, z, y)
11     y.left = z.left
12     y.left.p = y
```

**Theorem 12.3:** INSERT and DELETE run in $O(h)$ time.

---

## Performance Summary

| Operation | Time |
|---|---|
| SEARCH / MINIMUM / MAXIMUM | $O(h)$ |
| SUCCESSOR / PREDECESSOR | $O(h)$ |
| INSERT | $O(h)$ |
| DELETE | $O(h)$ |
| INORDER-TREE-WALK | $\Theta(n)$ |

**Height analysis:**
- **Balanced (best/average):** $h = \Theta(\log_2 n)$ → all operations $O(\log_2 n)$
- **Degenerate (worst):** $h = \Theta(n)$ → all operations $\Theta(n)$
- **Random BST:** Expected height $O(\log_2 n)$ even without balancing

Red-black trees (Chapter 13) guarantee $O(\log_2 n)$ height.

---

### Navigation
**Previous:** [[Ch11_Hash_Tables]]
**Next:** [[Ch13_Red_Black_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
