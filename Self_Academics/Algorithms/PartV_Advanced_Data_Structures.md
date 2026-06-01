# Part V: Advanced Data Structures — Introduction

## Executive Summary

Part V returns to data structures for dynamic sets at an advanced level, building on Part III (Chapters 10–13). Three chapters cover: **augmenting data structures** (Chapter 17, adding extra information to red-black trees), **B-trees** (Chapter 18, disk-optimized balanced trees), and **disjoint sets** (Chapter 19, near-linear union-find with inverse Ackermann $\alpha(n)$ amortized time).

---

## Zero-Loss Extraction

### Part V Contents

| Chapter | Topic | Key Result |
|---------|-------|-----------|
| Ch17 | Augmenting Data Structures | Order-statistic trees + interval trees; Theorem 17.1 for safe augmentation |
| Ch18 | B-Trees | Disk-based balanced BSTs; $O(\log_t n)$ operations with $O(t)$ disk reads per level |
| Ch19 | Disjoint Sets (Union-Find) | $O(m \alpha(n))$ for $m$ operations; $\alpha(n) \leq 4$ in practice |

---

## Deep-Dive Explanations

### Augmenting Data Structures (Ch17)

Red-black trees can be augmented with extra node attributes to support new operations. The key theorem (Theorem 17.1) shows that if an attribute $f$ at node $x$ depends only on $x$, $x.\text{left}$, and $x.\text{right}$, then INSERT/DELETE maintain $f$ without asymptotic overhead.

**Examples:**
- **Order-statistic trees:** Add $x.\text{size}$ (subtree size) → OS-SELECT and OS-RANK in $O(\log_2 n)$
- **Interval trees:** Add $x.\text{max}$ (max endpoint in subtree) → INTERVAL-SEARCH in $O(\log_2 n)$

### B-Trees (Ch18)

Balanced $t$-way search trees designed to minimize disk accesses. Each node holds 1 to $2t-1$ keys and $2$ to $2t$ children. Height $h \leq \log_t\lceil n/2 \rceil$. Every operation reads $O(h)$ disk pages. When $t = \Theta(B)$ (block size), B-trees are optimal for disk I/O.

### Disjoint Sets (Ch19)

Maintains a collection of disjoint sets under UNION and FIND-SET. Using union-by-rank and path compression, $m$ operations on $n$ elements take $O(m\alpha(n))$ total time, where $\alpha(n)$ is the inverse Ackermann function ($\alpha(n) \leq 4$ for any realistic $n$). Used in Kruskal's MST algorithm.

---

## Key Takeaways & Next Steps

1. Augmentation lets red-black trees support new queries while maintaining $O(\log_2 n)$ all operations.
2. B-trees dominate disk-based algorithms — their design is driven by I/O cost, not just computation.
3. Disjoint-set union is practically $O(1)$ per operation — the $\alpha(n)$ factor is essentially constant.

---

### Navigation

**Previous:** [[Ch16_Amortized_Analysis]]
**Next:** [[Ch17_Augmenting_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
