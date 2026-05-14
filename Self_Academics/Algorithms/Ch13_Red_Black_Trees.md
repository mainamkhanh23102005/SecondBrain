# Chapter 13: Red-Black Trees

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #red-black-tree #balanced-BST

## Overview

A **red-black tree** is a balanced binary search tree that guarantees all dynamic-set operations in $O(\log_2 n)$ worst-case time. It achieves balance by maintaining five structural properties via node coloring and rotations.

---

## 13.1 Red-Black Properties

Each node has an extra attribute: `color` (RED or BLACK). NIL pointers are replaced by a sentinel `T.nil` (always BLACK).

**Five red-black properties:**
1. Every node is either RED or BLACK
2. The **root** is BLACK
3. Every **leaf** (T.nil) is BLACK
4. If a node is RED, then both its children are BLACK (no two consecutive reds)
5. For each node, all simple paths to descendant leaves contain the **same number of black nodes** (equal **black-height**)

**Black-height** $\text{bh}(x)$: number of black nodes on any path from $x$ (not including $x$) to a leaf.

**Lemma 13.1:** A red-black tree with $n$ internal nodes has height at most $2\log_2(n+1)$.

**Proof sketch:**
- Subtree rooted at $x$ contains $\geq 2^{\text{bh}(x)} - 1$ internal nodes (induction)
- By property 4, at least half the nodes on any root-to-leaf path are black, so $\text{bh}(\text{root}) \geq h/2$
- Therefore $n \geq 2^{h/2} - 1 \implies h \leq 2\log_2(n+1)$

**Consequence:** SEARCH, MINIMUM, MAXIMUM, SUCCESSOR, PREDECESSOR all run in $O(\log_2 n)$ time (they work on BST of height $O(\log_2 n)$).

---

## 13.2 Rotations

Rotations preserve the BST property and run in $O(1)$ time (only pointer changes).

```
LEFT-ROTATE(T, x)           // requires x.right ≠ T.nil
1   y = x.right
2   x.right = y.left         // turn y's left subtree into x's right subtree
3   if y.left ≠ T.nil
4       y.left.p = x
5   y.p = x.p
6   if x.p == T.nil
7       T.root = y
8   elseif x == x.p.left
9       x.p.left = y
10  else x.p.right = y
11  y.left = x               // put x on y's left
12  x.p = y
```

RIGHT-ROTATE is symmetric. After rotation:
- $x$ becomes $y$'s left child ($\alpha, x, \beta$ → $y$'s left; $\gamma$ → $y$'s right)
- $y$ becomes the new root of the subtree

---

## 13.3 Insertion

RB-INSERT inserts node $z$ as in a regular BST, colors it RED, then calls RB-INSERT-FIXUP to restore red-black properties.

```
RB-INSERT(T, z)
1   [standard BST insert with T.nil instead of NIL]
16  z.color = RED
17  RB-INSERT-FIXUP(T, z)
```

**Which properties can be violated?**
- Property 2: violated if $z$ is the root (easy fix: color root black)
- Property 4: violated if $z$'s parent is also RED

### RB-INSERT-FIXUP: Three Cases

The loop maintains: $z$ is RED, at most one property is violated (either 2 or 4).

(Shown for case where $z$'s parent is a **left child** of grandparent; symmetric for right child)

**Case 1 — Uncle $y$ is RED:**
- Recolor: $z$'s parent → BLACK, uncle → BLACK, grandparent → RED
- Move $z$ up to grandparent; violation may propagate up but tree height is $O(\log_2 n)$
- $z$ moves up 2 levels per iteration → $O(\log_2 n)$ iterations

**Case 2 — Uncle is BLACK, $z$ is right child:**
- Left-rotate on $z$'s parent → transforms into Case 3

**Case 3 — Uncle is BLACK, $z$ is left child:**
- Recolor $z$'s parent → BLACK, grandparent → RED
- Right-rotate on grandparent → loop terminates

After the loop: set `T.root.color = BLACK` to handle property 2.

**Total time:** $O(\log_2 n)$ — at most $O(\log_2 n)$ loop iterations, each $O(1)$.

---

## 13.4 Deletion

RB-DELETE removes a node and calls RB-DELETE-FIXUP to restore properties.

**Key difference from BST deletion:** Track which node $y$ was removed/moved and its original color. If $y$'s original color was BLACK, black-height may be violated.

**RB-DELETE-FIXUP: Four cases** (symmetric set for left/right):
- Each case involves the "extra black" that must be pushed up or absorbed
- **Case 1:** Sibling $w$ is RED → rotate to convert to Cases 2/3/4
- **Case 2:** Sibling $w$ is BLACK, both children of $w$ are BLACK → move extra black up
- **Case 3:** Sibling $w$ is BLACK, $w$'s left child is RED → rotate/recolor to get Case 4
- **Case 4:** Sibling $w$ is BLACK, $w$'s right child is RED → rotate/recolor, loop terminates

**Total time:** $O(\log_2 n)$.

---

## Performance Summary

| Operation | Time |
|---|---|
| SEARCH / MINIMUM / MAXIMUM | $O(\log_2 n)$ |
| SUCCESSOR / PREDECESSOR | $O(\log_2 n)$ |
| INSERT (RB-INSERT) | $O(\log_2 n)$ |
| DELETE (RB-DELETE) | $O(\log_2 n)$ |
| LEFT-ROTATE / RIGHT-ROTATE | $O(1)$ |

**Rotations per insert:** at most 2.
**Rotations per delete:** at most 3.

**Space:** $O(n)$ plus one sentinel node.

---

### Navigation
**Previous:** [[Ch12_Binary_Search_Trees]]
**Next:** [[Part4_Introduction_Advanced_Design]]
**Hub:** [[Index_Introduction_to_Algorithms]]
