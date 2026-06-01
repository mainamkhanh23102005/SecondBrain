# Chapter 13: Red-Black Trees

## Executive Summary

Chapter 13 presents **red-black trees** — balanced BSTs that guarantee $O(\log_2 n)$ worst-case time for all dynamic-set operations. A red-black tree is a BST where every node is colored RED or BLACK, governed by five structural properties that collectively bound the height to $h \leq 2\log_2(n+1)$ (Lemma 13.1). The two main operations that can disturb this balance — INSERT and DELETE — restore the red-black properties using **rotations** ($O(1)$) and **recoloring** after the standard BST operation. RB-INSERT performs at most 2 rotations; RB-DELETE at most 3. Both run in $O(\log_2 n)$. Red-black trees are the standard ordered dynamic-set data structure used in most language standard libraries (C++ `std::map`, Java `TreeMap`).

---

## Zero-Loss Extraction

### The Five Red-Black Properties

For every node $x$ in a red-black tree:

1. Every node is either RED or BLACK.
2. The root is BLACK.
3. Every leaf ($T.\text{nil}$) is BLACK.
4. If a node is RED, then both its children are BLACK. (No two adjacent red nodes.)
5. For each node, all simple paths from that node to descendant leaves contain the same number of BLACK nodes (**black-height**).

**Sentinel $T.\text{nil}$:** A single black sentinel node replaces all NIL pointers (both leaf pointers and the root's parent pointer). All leaf nodes and the root's `.p` attribute point to $T.\text{nil}$. This simplifies boundary conditions.

**Black-height $\text{bh}(x)$:** Number of BLACK nodes on any simple path from $x$ (exclusive) to a descendant leaf.

### Core Algorithms & Pseudocode

**Rotations** (both $O(1)$ — change only a constant number of pointers):

```
LEFT-ROTATE(T, x)
 1  y = x.right          // y is x's right child
 2  x.right = y.left     // y's left subtree becomes x's right subtree
 3  if y.left ≠ T.nil
 4      y.left.p = x
 5  y.p = x.p            // link x's parent to y
 6  if x.p == T.nil
 7      T.root = y
 8  elseif x == x.p.left
 9      x.p.left = y
10  else x.p.right = y
11  y.left = x            // put x on y's left
12  x.p = y

RIGHT-ROTATE(T, y)       // symmetric: swap left ↔ right
```

**RB-INSERT** (inserts node $z$ with key already set):

```
RB-INSERT(T, z)
 1  RB-TRANSPLANT helper: y = T.nil, x = T.root
 2  while x ≠ T.nil         // find insertion position
 3      y = x
 4      if z.key < x.key
 5          x = x.left
 6      else x = x.right
 7  z.p = y
 8  if y == T.nil
 9      T.root = z
10  elseif z.key < y.key
11      y.left = z
12  else y.right = z
13  z.left = T.nil; z.right = T.nil
14  z.color = RED
15  RB-INSERT-FIXUP(T, z)
```

**RB-INSERT-FIXUP** (restores red-black properties after insert):

```
RB-INSERT-FIXUP(T, z)
 1  while z.p.color == RED
 2      if z.p == z.p.p.left      // z's parent is a left child
 3          y = z.p.p.right        // y = uncle of z
 4          if y.color == RED                   // Case 1
 5              z.p.color = BLACK
 6              y.color = BLACK
 7              z.p.p.color = RED
 8              z = z.p.p          // move z up two levels
 9          else
10              if z == z.p.right              // Case 2
11                  z = z.p
12                  LEFT-ROTATE(T, z)
13              z.p.color = BLACK              // Case 3
14              z.p.p.color = RED
15              RIGHT-ROTATE(T, z.p.p)
16      else // same with "left" and "right" exchanged
17          y = z.p.p.left
18          if y.color == RED                   // Case 1′
19              z.p.color = BLACK
20              y.color = BLACK
21              z.p.p.color = RED
22              z = z.p.p
23          else
24              if z == z.p.left               // Case 2′
25                  z = z.p
26                  RIGHT-ROTATE(T, z)
27              z.p.color = BLACK              // Case 3′
28              z.p.p.color = RED
29              LEFT-ROTATE(T, z.p.p)
30  T.root.color = BLACK
```

**RB-TRANSPLANT** (helper — like TRANSPLANT but uses $T.\text{nil}$ and always assigns $v.p$):

```
RB-TRANSPLANT(T, u, v)
1  if u.p == T.nil
2      T.root = v
3  elseif u == u.p.left
4      u.p.left = v
5  else u.p.right = v
6  v.p = u.p          // unconditional assignment — works even if v = T.nil
```

**RB-DELETE**:

```
RB-DELETE(T, z)
 1  y = z
 2  y-original-color = y.color
 3  if z.left == T.nil
 4      x = z.right
 5      RB-TRANSPLANT(T, z, z.right)    // replace z by its right child
 6  elseif z.right == T.nil
 7      x = z.left
 8      RB-TRANSPLANT(T, z, z.left)     // replace z by its left child
 9  else y = TREE-MINIMUM(z.right)      // y is z's successor
10      y-original-color = y.color
11      x = y.right
12      if y ≠ z.right                  // y is further down
13          RB-TRANSPLANT(T, y, y.right)
14          y.right = z.right
15          y.right.p = y
16      else x.p = y                    // in case x is T.nil
17      RB-TRANSPLANT(T, z, y)
18      y.left = z.left
19      y.left.p = y
20      y.color = z.color
21  if y-original-color == BLACK
22      RB-DELETE-FIXUP(T, x)           // fix violations if y was black
```

**RB-DELETE-FIXUP** (4 cases when $x$ is a left child; symmetric for right child):

```
RB-DELETE-FIXUP(T, x)
 1  while x ≠ T.root and x.color == BLACK
 2      if x == x.p.left                // x is a left child
 3          w = x.p.right               // w is x's sibling
 4          if w.color == RED                          // Case 1
 5              w.color = BLACK
 6              x.p.color = RED
 7              LEFT-ROTATE(T, x.p)
 8              w = x.p.right           // new sibling after rotation
 9          if w.left.color == BLACK and w.right.color == BLACK  // Case 2
10              w.color = RED
11              x = x.p                 // move extra black up
12          else
13              if w.right.color == BLACK               // Case 3
14                  w.left.color = BLACK
15                  w.color = RED
16                  RIGHT-ROTATE(T, w)
17                  w = x.p.right
18              w.color = x.p.color                     // Case 4
19              x.p.color = BLACK
20              w.right.color = BLACK
21              LEFT-ROTATE(T, x.p)
22              x = T.root              // loop will terminate
23      else // same as lines 3–22 with "right" and "left" exchanged
24          ...
25  x.color = BLACK
```

---

## Deep-Dive Explanations

### Why Red-Black Trees Work: Lemma 13.1

**Lemma 13.1:** A red-black tree with $n$ internal nodes has height $h \leq 2\log_2(n+1)$.

**Proof sketch:**
1. **Claim A:** Subtree rooted at $x$ contains $\geq 2^{\text{bh}(x)} - 1$ internal nodes.
   - *Base:* leaf ($T.\text{nil}$) has $\text{bh} = 0$ and $2^0 - 1 = 0$ internal nodes. ✓
   - *Inductive step:* children of $x$ have black-height $\geq \text{bh}(x) - 1$, so each contributes $\geq 2^{\text{bh}(x)-1} - 1$ internal nodes. Together with $x$ itself: $\geq 2 \cdot (2^{\text{bh}(x)-1} - 1) + 1 = 2^{\text{bh}(x)} - 1$.
2. By Property 4, on any path from root to leaf, at least half the nodes are BLACK. Thus $\text{bh}(\text{root}) \geq h/2$.
3. Combining: $n \geq 2^{h/2} - 1$, so $h \leq 2\log_2(n+1)$. $\square$

**Corollary:** All BST operations take $O(\log_2 n)$ worst case on a red-black tree.

### Rotations

Rotations are the key structural operations that rebalance the tree:
- **LEFT-ROTATE(T, x):** Node $x$'s right child $y$ becomes the new root; $x$ becomes $y$'s left child; $y$'s original left subtree becomes $x$'s right subtree.
- **RIGHT-ROTATE** is symmetric (swap left ↔ right).
- Both take $O(1)$ time — only pointer changes, no key comparisons.

### RB-INSERT-FIXUP: Three Cases

New node $z$ is colored RED. The only potential violation is **Property 4** (two adjacent red nodes: $z$ and its parent $z.p$). The loop invariant: $z$ is red and $z.p.p$ exists (grandparent).

| Case | Condition | Action | Effect |
|------|-----------|--------|--------|
| 1 | Uncle $y$ is RED | Recolor $z.p$ and $y$ BLACK; recolor grandparent RED; move $z$ up two levels | Pushes violation up tree |
| 2 | Uncle $y$ is BLACK; $z$ is right child | Left-rotate on $z.p$; fall through to Case 3 | Converts to Case 3 |
| 3 | Uncle $y$ is BLACK; $z$ is left child | Recolor $z.p$ BLACK; recolor grandparent RED; right-rotate on grandparent | Terminates loop |

**Analysis:** Case 1 can repeat $O(\log_2 n)$ times. Cases 2 and 3 each terminate after a constant number of steps and at most 2 total rotations. Total: $O(\log_2 n)$.

### RB-DELETE-FIXUP: Four Cases

When the deleted node $y$ was BLACK, node $x$ (which takes $y$'s place) is "doubly black" — it needs to shed its extra black. The four cases for $x$ as a left child:

| Case | Condition | Action | Effect |
|------|-----------|--------|--------|
| 1 | Sibling $w$ is RED | Recolor $w$ black, $x.p$ red; left-rotate on $x.p$; update $w$ | Converts to Case 2/3/4 |
| 2 | $w$ BLACK; both $w$'s children BLACK | Color $w$ RED; move extra black up: $x = x.p$ | May loop; terminates if $x$ becomes red-and-black |
| 3 | $w$ BLACK; $w$.left RED, $w$.right BLACK | Swap $w$ and $w$.left colors; right-rotate on $w$; update $w$ | Converts to Case 4 |
| 4 | $w$ BLACK; $w$.right RED | Set $w$'s color to $x.p$'s; color $x.p$ and $w$.right BLACK; left-rotate on $x.p$; $x = T.\text{root}$ | Terminates immediately |

**Key insight:** The "extra black" is a bookkeeping device — $x.p$ literally has one fewer black on the paths through $x$. Cases 1/3/4 terminate after at most 3 rotations total. Only Case 2 loops, moving $x$ upward at most $O(\log_2 n)$ times.

### Time and Space Complexity Analysis

| Operation | Time | Notes |
|-----------|------|-------|
| RB-INSERT | $O(\log_2 n)$ | At most 2 rotations |
| RB-DELETE | $O(\log_2 n)$ | At most 3 rotations |
| SEARCH, MIN, MAX, SUCCESSOR, PREDECESSOR | $O(\log_2 n)$ | Standard BST operations; height bounded |
| LEFT-ROTATE / RIGHT-ROTATE | $O(1)$ | Pointer manipulation only |

**Space:** $O(n)$ — one sentinel $T.\text{nil}$ node shared by all leaves.

### Comparison: BST vs. Red-Black Tree

| Property | BST | Red-Black Tree |
|----------|-----|---------------|
| Height | $O(n)$ worst case | $O(\log_2 n)$ guaranteed |
| All operations | $O(h)$ | $O(\log_2 n)$ |
| INSERT | $O(h)$; simple | $O(\log_2 n)$; ≤ 2 rotations |
| DELETE | $O(h)$; 4 cases | $O(\log_2 n)$; ≤ 3 rotations |
| Overhead | Minimal | Color bit per node |

---

## Key Takeaways & Next Steps

1. **Red-black trees guarantee $O(\log_2 n)$ worst case** for all operations by maintaining height $\leq 2\log_2(n+1)$ via 5 structural properties.
2. **Rotations** are the key primitive: $O(1)$ structural changes that maintain the BST property while fixing red-black properties.
3. **INSERT is simpler than DELETE**: at most 2 rotations; fixes only Property 4 violations. DELETE may violate Property 5 ("doubly black") requiring up to 3 rotations.
4. **The sentinel $T.\text{nil}$** eliminates boundary conditions throughout — all NIL checks become uniform checks against this single sentinel.
5. Red-black trees are used in: C++ `std::map`/`std::set`, Java `TreeMap`/`TreeSet`, Linux kernel (CFS scheduler), and as the foundation for augmented data structures (Chapter 14).

---

### Navigation

**Previous:** [[Ch12_Binary_Search_Trees]]
**Next:** [[PartIV_Advanced_Design_and_Analysis_Techniques]]
**Hub:** [[Index_Introduction_to_Algorithms]]
