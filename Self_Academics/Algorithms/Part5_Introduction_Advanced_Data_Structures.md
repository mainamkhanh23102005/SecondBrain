# Part V Introduction: Advanced Data Structures

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #advanced

## Overview

Part V extends the data structures from Part III to more advanced settings: augmenting existing structures, disk-based storage, and disjoint-set operations.

---

## Chapters in This Part

| Chapter | Data Structure | Key Property |
|---|---|---|
| Ch 17 | Augmented Red-Black Trees | Add info to nodes; maintain $O(\log_2 n)$ operations |
| Ch 18 | B-Trees | Balanced trees minimizing disk I/O; $O(\log_2 n)$ operations |
| Ch 19 | Disjoint Sets (Union-Find) | UNION + FIND-SET in $O(m\alpha(n))$ for $m$ operations |

## Beyond Part V

Other advanced data structures not covered:
- **Fibonacci heaps:** INSERT/UNION/MINIMUM in $O(1)$; EXTRACT-MIN/DELETE in $O(\log_2 n)$ amortized; key for fast graph algorithms
- **Dynamic trees:** Maintain forest of disjoint trees with $O(\log_2 n)$ amortized operations
- **Splay trees:** BST with $O(\log_2 n)$ amortized for all operations
- **van Emde Boas trees:** All dictionary operations in $O(\log_2 \log_2 u)$ for integer keys in $\{0,\ldots,u-1\}$
- **Persistent data structures:** Allow queries on past versions

---

### Navigation
**Previous:** [[Ch16_Amortized_Analysis]]
**Next:** [[Ch17_Augmenting_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
