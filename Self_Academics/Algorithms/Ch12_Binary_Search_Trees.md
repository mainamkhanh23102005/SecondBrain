# Chapter 12: Binary Search Trees

## Executive Summary

Chapter 12 presents the **binary search tree (BST)** — a linked binary tree satisfying the **BST property** (left subtree keys $\leq$ node key $\leq$ right subtree keys), enabling $O(h)$ dynamic-set operations where $h$ is tree height. All seven operations (SEARCH, MINIMUM, MAXIMUM, SUCCESSOR, PREDECESSOR, INSERT, DELETE) run in $O(h)$. For a balanced tree $h = \Theta(\log_2 n)$; for a degenerate (chain) tree $h = \Theta(n)$. The DELETE operation is the most complex, using a TRANSPLANT helper to handle four cases. BSTs underlie red-black trees (Chapter 13) and many other data structures.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Inorder tree walk** — prints keys in sorted order in $\Theta(n)$:

```
INORDER-TREE-WALK(x)
1  if x ≠ NIL
2      INORDER-TREE-WALK(x.left)
3      print x.key
4      INORDER-TREE-WALK(x.right)
```

**Tree search** (recursive and iterative):

```
TREE-SEARCH(x, k)
1  if x == NIL or k == x.key
2      return x
3  if k < x.key
4      return TREE-SEARCH(x.left, k)
5  else return TREE-SEARCH(x.right, k)

ITERATIVE-TREE-SEARCH(x, k)
1  while x ≠ NIL and k ≠ x.key
2      if k < x.key
3          x = x.left
4      else x = x.right
5  return x
```

**Min/Max/Successor/Predecessor**:

```
TREE-MINIMUM(x)
1  while x.left ≠ NIL
2      x = x.left
3  return x

TREE-MAXIMUM(x)
1  while x.right ≠ NIL
2      x = x.right
3  return x

TREE-SUCCESSOR(x)
1  if x.right ≠ NIL
2      return TREE-MINIMUM(x.right)   // leftmost in right subtree
3  else  // go up until we're a left child
4      y = x.p
5      while y ≠ NIL and x == y.right
6          x = y;  y = y.p
7      return y
```

**Insertion**:

```
TREE-INSERT(T, z)
1  x = T.root;  y = NIL
2  while x ≠ NIL
3      y = x                           // y tracks parent
4      if z.key < x.key
5          x = x.left
6      else x = x.right
7  z.p = y
8  if y == NIL
9      T.root = z                      // tree was empty
10 elseif z.key < y.key
11     y.left = z
12 else y.right = z
```

**TRANSPLANT helper** (replaces subtree rooted at $u$ with subtree rooted at $v$):

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

**Deletion** (four cases):

```
TREE-DELETE(T, z)
1  if z.left == NIL
2      TRANSPLANT(T, z, z.right)      // case (a): no left child
3  elseif z.right == NIL
4      TRANSPLANT(T, z, z.left)       // case (b): left child only
5  else y = TREE-MINIMUM(z.right)     // y = z's successor
6      if y ≠ z.right                 // y is further down
7          TRANSPLANT(T, y, y.right)  // replace y by y's right child
8          y.right = z.right
9          y.right.p = y
10     TRANSPLANT(T, z, y)            // replace z by its successor y
11     y.left = z.left
12     y.left.p = y
```

---

## Deep-Dive Explanations

### BST Property

For every node $x$: all keys in left subtree $\leq x.key$; all keys in right subtree $\geq x.key$.

This property ensures inorder traversal visits keys in sorted order (Theorem 12.1: $\Theta(n)$ time).

### Time and Space Complexity Analysis

All basic operations follow a simple path from root to leaf (or root to node). Running time = $O(h)$ where $h$ = height of tree.

| Operation | Time | Notes |
|-----------|------|-------|
| INORDER-TREE-WALK | $\Theta(n)$ | Visits every node exactly once |
| TREE-SEARCH | $O(h)$ | Follows path down |
| TREE-MINIMUM/MAXIMUM | $O(h)$ | Follows left/right spine |
| TREE-SUCCESSOR/PREDECESSOR | $O(h)$ | At most two path segments |
| TREE-INSERT | $O(h)$ | Finds insertion position like search |
| TREE-DELETE | $O(h)$ | Constant work + TREE-MINIMUM call |

**Space:** $O(n)$ — each node stores key, satellite data, and 3 pointers (left, right, parent).

### Height Analysis

- **Best case** (complete binary tree): $h = \lfloor \log_2 n \rfloor = \Theta(\log_2 n)$
- **Worst case** (chain — sorted insertions): $h = n - 1 = \Theta(n)$
- **Expected case** (random insertions): $E[h] = O(\log_2 n)$ — proven in Section 12.4

For guaranteed $O(\log_2 n)$: use red-black trees (Chapter 13).

### Deletion: Four Cases

**Case (a):** $z$ has no left child → replace $z$ with its right child (may be NIL).

**Case (b):** $z$ has left child but no right child → replace $z$ with its left child.

**Case (c):** $z$ has two children and successor $y = z.right$ (no left child since it's in-tree) → replace $z$ with $y$, set $y.left = z.left$.

**Case (d):** $z$ has two children, successor $y \neq z.right$ (deeper in right subtree) → first splice $y$ out (replacing it with $y.right$), then substitute $y$ for $z$.

Key insight: **successor $y$ of a node with two children has no left child** (Exercise 12.2-5). This allows clean splicing.

### Successor/Predecessor Logic

**Successor of $x$:**
- If $x$ has a right subtree: return minimum of right subtree
- Otherwise: go up until we move from a right child to its parent → that parent is the successor

**Predecessor of $x$** (symmetric):
- If $x$ has a left subtree: return maximum of left subtree
- Otherwise: go up until we move from a left child to its parent

---

## Key Takeaways & Next Steps

1. The **BST property** enables $O(h)$ operations; inorder traversal produces sorted output in $\Theta(n)$.
2. All operations run in $O(h)$ — height is the critical parameter. Random BSTs have $E[h] = O(\log_2 n)$ but worst case is $\Theta(n)$.
3. **DELETE is the most complex operation**: the two-children case requires finding the successor and transplanting it; TRANSPLANT is the key helper.
4. BSTs build intuition for Chapter 13's red-black trees, which add coloring and rotation rules to guarantee $h = O(\log_2 n)$.
5. BSTs also underlie treaps (random BSTs with heap priorities), splay trees (amortized $O(\log_2 n)$), and skip lists.

---

### Navigation

**Previous:** [[Ch11_Hash_Tables]]
**Next:** [[Ch13_Red-Black_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
