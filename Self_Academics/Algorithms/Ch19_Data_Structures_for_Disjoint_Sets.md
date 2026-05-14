# Chapter 19: Data Structures for Disjoint Sets

## Executive Summary

Chapter 19 presents **disjoint-set (union-find) data structures** — structures that maintain a collection of disjoint sets under three operations: MAKE-SET, UNION, and FIND-SET. Two implementations are analyzed: a **linked-list representation** with a weighted-union heuristic achieves $O(m + n\log_2 n)$ for $m$ total operations; a **disjoint-set forest** with union by rank and path compression achieves $O(m\,\alpha(n))$, where $\alpha(n)$ is the inverse Ackermann function satisfying $\alpha(n) \leq 4$ for any practical $n$. The final section proves this near-linear bound via a potential-function amortized analysis involving the rapidly growing Ackermann function $A_k(j)$.

---

## Zero-Loss Extraction

### Operations

- **MAKE-SET($x$):** creates a new set $\{x\}$ with representative $x$
- **UNION($x$, $y$):** merges the sets containing $x$ and $y$; destroys both originals
- **FIND-SET($x$):** returns the representative of the set containing $x$

Parameters for analysis: $n$ = number of MAKE-SET operations; $m$ = total operations ($m \geq n$); at most $n-1$ UNION operations can occur.

### Core Algorithms & Pseudocode

**Connected components (application):**

```
CONNECTED-COMPONENTS(G)
1  for each vertex v ∈ G.V
2      MAKE-SET(v)
3  for each edge (u, v) ∈ G.E
4      if FIND-SET(u) ≠ FIND-SET(v)
5          UNION(u, v)

SAME-COMPONENT(u, v)
1  if FIND-SET(u) == FIND-SET(v)
2      return TRUE
3  else return FALSE
```

**Disjoint-set forest — union by rank + path compression:**

```
MAKE-SET(x)
1  x.p = x
2  x.rank = 0

UNION(x, y)
1  LINK(FIND-SET(x), FIND-SET(y))

LINK(x, y)
1  if x.rank > y.rank
2      y.p = x
3  else x.p = y
4      if x.rank == y.rank
5          y.rank = y.rank + 1

FIND-SET(x)           // two-pass path compression
1  if x ≠ x.p
2      x.p = FIND-SET(x.p)   // compress: point directly to root
3  return x.p
```

---

## Deep-Dive Explanations

### Linked-List Representation

Each set is a linked list with `head` and `tail` pointers. Each element has a back-pointer to the set object (its representative).

- MAKE-SET: $O(1)$ — create singleton list
- FIND-SET: $O(1)$ — follow back-pointer to head
- UNION (simple): $\Theta(n)$ amortized — appending longer list onto shorter requires updating all back-pointers

**Weighted-union heuristic:** always append the shorter list onto the longer. Each element's back-pointer is updated at most $\lceil \log_2 n \rceil$ times (each update at least doubles the set size), so total pointer updates over all UNIONs is $O(n\log_2 n)$.

**Theorem 19.1:** With the linked-list representation and weighted-union heuristic, $m$ operations ($n$ of which are MAKE-SET) take $O(m + n\log_2 n)$ total time.

### Disjoint-Set Forest

Represent each set as a rooted tree (not necessarily binary). Each node points to its parent; roots point to themselves and serve as representatives.

**Without heuristics:** a sequence of $n-1$ UNIONs can create a linear chain → $\Theta(n)$ per FIND-SET.

**Union by rank:** make the root with smaller rank point to the root with larger rank. When ranks tie, increment the new root's rank. Rank is an upper bound on height. Alone: $O(m\log_2 n)$.

**Path compression:** FIND-SET is a two-pass recursive method — first pass finds the root; on unwind, every node on the find path is updated to point directly to the root. Does not change ranks. Alone: $\Theta(n + f \cdot (1 + \log_{2+f/n} n))$ for $f$ FIND-SET operations.

**Combined:** $O(m\,\alpha(n))$.

### The Ackermann Function and $\alpha(n)$

Define $A_k(j)$ for integers $k, j \geq 0$:
$$A_0(j) = j + 1, \qquad A_k(j) = A_{k-1}^{(j)}(j) \text{ for } k \geq 1$$
where $f^{(i)}$ denotes $i$-fold functional iteration.

**Lemma 19.2:** $A_1(j) = 2j + 1$

**Lemma 19.3:** $A_2(j) = 2^{j+1}(j+1) - 1$

Growth: $A_0(1) = 2$, $A_1(1) = 3$, $A_2(1) = 7$, $A_3(1) = 2047$, $A_4(1) > 10^{80}$ (more than atoms in the observable universe).

**Inverse Ackermann:** $\alpha(n) = \min\{k : A_k(1) \geq n\}$. For all $n \leq A_4(1) \gg 10^{80}$, $\alpha(n) \leq 4$.

### Amortized Analysis: $O(m\,\alpha(n))$ Bound (Section 19.4)

**Key lemmas:**
- **Lemma 19.4:** $x.\text{rank} \leq x.p.\text{rank}$ (strict if $x$ is not a root); ranks of non-roots never change; ranks of roots are monotonically non-decreasing.
- **Corollary 19.5:** Ranks strictly increase along any path toward the root.
- **Lemma 19.6:** Every node has rank at most $n-1$ (tight bound: $\lfloor \log_2 n \rfloor$).

**Potential function:** For each node $x$ after $q$ operations:
$$\phi_q(x) = \begin{cases} \alpha(n) \cdot x.\text{rank} & \text{if } x \text{ is a root or } x.\text{rank} = 0 \\ (\alpha(n) - \text{level}(x)) \cdot x.\text{rank} - \text{iter}(x) & \text{otherwise} \end{cases}$$
where $\text{level}(x) = \max\{k : A_k(x.\text{rank}) \leq x.p.\text{rank}\}$ and $\text{iter}(x)$ = maximum iterations of $A_{\text{level}(x)}$ starting at $x.\text{rank}$ without exceeding $x.p.\text{rank}$.

**Lemma 19.8:** $0 \leq \phi_q(x) \leq \alpha(n) \cdot x.\text{rank}$ for all $x$, $q$.

**Lemma 19.10:** Potential of non-root nodes never increases during LINK or FIND-SET; drops by $\geq 1$ if rank $\geq 1$ and level or iter changes.

**Amortized costs:**
- **Lemma 19.11:** MAKE-SET: $O(1)$ amortized
- **Lemma 19.12:** LINK: $O(\alpha(n))$ amortized
- **Lemma 19.13:** FIND-SET with $s$-node find path: at least $\max\{0, s - (\alpha(n)+2)\}$ nodes have potential drop $\geq 1$; amortized cost $= O(s) - (s - (\alpha(n)+2)) = O(\alpha(n))$

**Theorem 19.14:** A sequence of $m$ MAKE-SET, UNION, FIND-SET operations ($n$ of which are MAKE-SET) on a disjoint-set forest with union by rank and path compression runs in $O(m\,\alpha(n))$ total time.

### Time and Space Complexity

| Implementation | MAKE-SET | FIND-SET | UNION | Total ($m$ ops) |
|----------------|----------|----------|-------|-----------------|
| Linked list (simple) | $O(1)$ | $O(1)$ | $\Theta(n)$ amort. | $\Theta(n^2)$ worst |
| Linked list + weighted-union | $O(1)$ | $O(1)$ | $O(\log_2 n)$ amort. | $O(m + n\log_2 n)$ |
| Forest, union by rank only | $O(1)$ | $O(\log_2 n)$ | $O(\log_2 n)$ | $O(m\log_2 n)$ |
| Forest, path compression only | $O(1)$ | $O(\log_2 n)$ amort. | — | $\Theta(n + f \cdot (1 + \log_{2+f/n} n))$ |
| Forest, union by rank + path comp. | $O(1)$ | $O(\alpha(n))$ amort. | $O(\alpha(n))$ amort. | $O(m\,\alpha(n))$ |

Space: $O(n)$ for $n$ elements.

---

## Key Takeaways & Next Steps

1. **$O(m\,\alpha(n))$ is essentially linear:** $\alpha(n) \leq 4$ for any $n$ up to $A_4(1) \gg 10^{80}$, making the disjoint-set forest with both heuristics practically $O(m)$.
2. **Union by rank** prevents tall trees; **path compression** flattens trees on FIND-SET — neither alone achieves the same bound as both together.
3. **The proof technique** uses a potential function encoding how much a node can benefit from future path compressions; Ackermann's function is the key to making the analysis tight.
4. **Applications:** Kruskal's MST algorithm (Chapter 21) uses MAKE-SET, FIND-SET, and UNION directly; connected components (this chapter); offline LCA (Problem 19-3).
5. Disjoint-set forests are the **most practically efficient union-find structure**: simple to implement, near-linear in any realistic scenario.

---

### Navigation

**Previous:** [[Ch18_B-Trees]]
**Next:** [[PartVI_Graph_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
