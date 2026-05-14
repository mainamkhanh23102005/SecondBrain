# Part III Introduction: Data Structures

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #dynamic-sets

## Overview

Part III covers data structures for representing **dynamic sets** — sets that grow, shrink, or change over time. The right data structure depends on which operations are needed.

---

## Dynamic Set Operations

| Operation | Description |
|---|---|
| `SEARCH(S, k)` | Return pointer to element with key $k$, or NIL |
| `INSERT(S, x)` | Add element $x$ to set $S$ |
| `DELETE(S, x)` | Remove element $x$ from set $S$ |
| `MINIMUM(S)` | Return element with smallest key |
| `MAXIMUM(S)` | Return element with largest key |
| `SUCCESSOR(S, x)` | Return next larger element after $x$ |
| `PREDECESSOR(S, x)` | Return next smaller element before $x$ |

A **dictionary** supports INSERT, DELETE, and SEARCH. More advanced structures support all operations.

## Array Implementation Trade-offs

| Array Type | INSERT | DELETE | SEARCH | MIN/MAX | SUCC/PRED |
|---|---|---|---|---|---|
| Unsorted | $\Theta(1)$ | $\Theta(1)$ | $\Theta(n)$ | $\Theta(n)$ | $\Theta(n)$ |
| Sorted | $\Theta(n)$ | $\Theta(n)$ | $O(\log_2 n)$ | $\Theta(1)$ | $\Theta(1)$ |

Part III data structures improve on these bounds.

## Chapters in This Part

| Chapter | Data Structure | Key Property |
|---|---|---|
| Ch 10 | Elementary: arrays, stacks, queues, linked lists, trees | Basic pointer-based structures |
| Ch 11 | Hash Tables | Expected $O(1)$ for INSERT/DELETE/SEARCH |
| Ch 12 | Binary Search Trees | $O(h)$ all operations; $h = O(n)$ worst case |
| Ch 13 | Red-Black Trees | $O(\log_2 n)$ guaranteed all operations |

---

### Navigation
**Previous:** [[Ch9_Medians_and_Order_Statistics]]
**Next:** [[Ch10_Elementary_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
