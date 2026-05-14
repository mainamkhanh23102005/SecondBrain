# Part IV: Advanced Design and Analysis Techniques — Introduction

## Executive Summary

Part IV covers three important algorithm design and analysis techniques: **dynamic programming** (Chapter 14), **greedy algorithms** (Chapter 15), and **amortized analysis** (Chapter 16). These techniques are more sophisticated than divide-and-conquer and randomization (covered earlier), but apply to a broad class of problems encountered throughout algorithm design.

---

## Zero-Loss Extraction

### The Three Techniques

| Technique | Core Idea | When to Apply |
|-----------|-----------|---------------|
| **Dynamic Programming** | Break problem into overlapping subproblems; store solutions in a table to avoid recomputation | Optimization problems with optimal substructure and overlapping subproblems |
| **Greedy Algorithms** | Make locally optimal choices at each step; never revise a choice | Problems where the greedy-choice property holds (greedy local choice is part of global optimum) |
| **Amortized Analysis** | Bound the average cost per operation over a sequence, not just the worst per individual operation | Sequences of operations on a data structure where some are expensive but infrequent |

---

## Deep-Dive Explanations

### Dynamic Programming (Chapter 14)

Applies to optimization problems where subproblems overlap. Key insight: instead of solving the same subproblem many times (exponential time), solve each subproblem once and store its answer — reducing to polynomial time. Two approaches: **bottom-up** (fill table from small to large subproblems) and **top-down with memoization** (recursive + cache). Both achieve the same asymptotic time.

### Greedy Algorithms (Chapter 15)

Like dynamic programming, greedy algorithms apply to optimization problems. The difference: greedy makes the locally best choice at each step without revisiting. This only works if the greedy-choice property holds. When it does, greedy algorithms are faster and simpler than DP. Determining when greedy works requires proving the greedy-choice property and optimal substructure.

### Amortized Analysis (Chapter 16)

Some algorithms perform operations where most are cheap but occasional ones are expensive. Amortized analysis provides a tighter bound than multiplying worst-case-per-operation by the number of operations. Three methods: **aggregate analysis**, **accounting method**, and **potential method**. Amortized analysis is useful both for analyzing existing algorithms and for designing new ones.

---

## Key Takeaways & Next Steps

1. These three techniques transform otherwise intractable problems into efficient algorithms.
2. **DP vs. greedy**: DP is more powerful (handles any problem with optimal substructure) but greedy is faster when applicable.
3. **Amortized analysis** avoids overly pessimistic bounds by analyzing sequences rather than individual operations.
4. These techniques recur throughout later parts: DP in graph algorithms (Dijkstra, Floyd-Warshall), greedy in MST algorithms (Kruskal, Prim).

---

### Navigation

**Previous:** [[Ch13_Red-Black_Trees]]
**Next:** [[Ch14_Dynamic_Programming]]
**Hub:** [[Index_Introduction_to_Algorithms]]
