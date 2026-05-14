# Part III: Data Structures — Introduction

## Executive Summary

Part III introduces **dynamic sets** — sets that can grow, shrink, and change over time — and the data structures used to implement them. The four chapters (10–13) cover elementary structures (arrays, linked lists, stacks, queues, trees), hash tables, binary search trees, and red-black trees. The goal is to support the standard dynamic-set operations efficiently. Each chapter builds on the previous, culminating in red-black trees that guarantee $O(\log_2 n)$ worst-case time for all operations.

---

## Zero-Loss Extraction

### Standard Dynamic-Set Operations

| Operation | Description |
|-----------|-------------|
| `SEARCH(S, k)` | Return pointer to element with key $k$, or NIL |
| `INSERT(S, x)` | Add element $x$ to set $S$ |
| `DELETE(S, x)` | Remove element $x$ from set $S$ (pointer, not key) |
| `MINIMUM(S)` | Return pointer to element with smallest key |
| `MAXIMUM(S)` | Return pointer to element with largest key |
| `SUCCESSOR(S, x)` | Return pointer to next larger element |
| `PREDECESSOR(S, x)` | Return pointer to next smaller element |

A **dictionary** supports INSERT, DELETE, and SEARCH. A **priority queue** supports INSERT and EXTRACT-MIN/MAX.

### Array Implementation Costs (for reference)

| Operation | Unsorted Array | Sorted Array |
|-----------|---------------|--------------|
| INSERT | $\Theta(1)$ | $\Theta(n)$ |
| DELETE | $\Theta(1)$ | $\Theta(n)$ |
| SEARCH | $\Theta(n)$ | $O(\log_2 n)$ (binary search) |
| MIN/MAX | $\Theta(n)$ | $\Theta(1)$ |
| SUCCESSOR/PREDECESSOR | $\Theta(n)$ | $\Theta(1)$ |

---

## Deep-Dive Explanations

### Part III Contents

- **Chapter 10:** Elementary data structures — arrays, matrices, stacks, queues, linked lists, and rooted trees. Foundation for everything that follows.

- **Chapter 11:** Hash tables — support INSERT, DELETE, SEARCH with $O(1)$ expected time (using probability). Worst case $\Theta(n)$ but rare with good hash functions and universal hashing.

- **Chapter 12:** Binary search trees (BSTs) — support all operations above. Worst case $\Theta(n)$ per operation (unbalanced tree), but serve as the conceptual foundation for balanced BSTs.

- **Chapter 13:** Red-black trees — balanced BSTs guaranteeing $O(\log_2 n)$ worst case for all operations. The standard data structure for ordered dynamic sets in practice (used in most language standard libraries).

### The Design Goal

For $n$-element dynamic sets, the target is:
- Dictionary operations: $O(\log_2 n)$ worst case (Chapter 13's red-black trees achieve this)
- Hash table operations: $O(1)$ expected (Chapter 11)

Array implementations are inadequate: any operation that is $\Theta(1)$ in one arrangement is $\Theta(n)$ in another.

---

## Key Takeaways & Next Steps

1. **Dynamic sets** are the core abstraction for representing data that changes over time; algorithms need efficient implementations.
2. **The key tension**: sorted arrays give fast queries but slow updates; unsorted arrays give fast updates but slow queries. Trees and hash tables break this trade-off.
3. **Red-black trees** achieve the theoretically optimal $O(\log_2 n)$ worst case for comparison-based dynamic sets — the culmination of Part III.
4. These data structures recur throughout later parts: BSTs and heaps in graph algorithms (Parts VI–VII), hash tables in string algorithms.

---

### Navigation

**Previous:** [[Ch09_Medians_and_Order_Statistics]]
**Next:** [[Ch10_Elementary_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
