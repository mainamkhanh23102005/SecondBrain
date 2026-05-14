# Chapter 16: Amortized Analysis

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #amortized-analysis #data-structures #dynamic-tables

## Overview

**Amortized analysis** bounds the average cost per operation in a **worst-case** sequence of operations. Unlike average-case analysis, no probability is involved — it gives a deterministic worst-case bound. When some operations are expensive but rare, the expensive operations can be "amortized" over many cheap ones.

**Key property:** Total amortized cost $\geq$ Total actual cost (amortized costs are an upper bound).

---

## 16.1 Aggregate Analysis

Sum the total cost $T(n)$ over all $n$ operations; amortized cost per operation = $T(n)/n$.

### Example 1: Stack with MULTIPOP

Operations: PUSH ($O(1)$), POP ($O(1)$), MULTIPOP (pops $k$ items, costs $O(\min(s,k))$).

Naive bound: $n$ operations × $O(n)$ per MULTIPOP = $O(n^2)$ — **not tight**.

**Aggregate analysis:** Each object is pushed at most once and popped at most once. Total pops $\leq$ total pushes $\leq n$. Total cost: $O(n)$. **Amortized cost per operation: $O(1)$.**

### Example 2: Binary Counter INCREMENT

A $k$-bit counter stores binary numbers. INCREMENT flips bits from the least-significant position carrying.

Naive bound: $O(k)$ per INCREMENT × $n$ operations = $O(nk)$ — **not tight**.

Aggregate analysis: Bit $A[i]$ flips at most $\lfloor n/2^i \rfloor$ times in $n$ increments.

$$\text{Total flips} = \sum_{i=0}^{k-1} \left\lfloor \frac{n}{2^i} \right\rfloor < n \sum_{i=0}^{\infty} \frac{1}{2^i} = 2n = O(n)$$

**Amortized cost per INCREMENT: $O(1)$.**

---

## 16.2 The Accounting Method

Assign **amortized costs** $\hat{c}_i$ to operations. When $\hat{c}_i > c_i$ (actual cost), store the excess as **credit** on data structure objects. Credit can later pay for operations where $\hat{c}_i < c_i$.

**Requirement:** Total credit $= \sum \hat{c}_i - \sum c_i \geq 0$ at all times.

### Stack Example

| Operation | Actual Cost | Amortized Cost | Credit |
|---|---|---|---|
| PUSH | 1 | 2 | +1 stored on pushed object |
| POP | 1 | 0 | uses $1 credit from popped object |
| MULTIPOP | $\min(s,k)$ | 0 | uses credit from popped objects |

Each object on the stack carries $1 of credit. Total amortized cost = $O(n)$ → total actual cost = $O(n)$.

### Binary Counter Example

Amortized cost to set bit 0→1: $2 (pays for setting + stores $1 for future reset).  
Amortized cost to reset bit 1→0: $0 (paid by stored credit).

Each INCREMENT sets at most one bit to 1 → amortized cost $\leq 2 = O(1)$.

---

## 16.3 The Potential Method

Define a **potential function** $\Phi: D_i \to \mathbb{R}$ mapping data structure states to real numbers.

**Amortized cost of $i$th operation:**
$$\hat{c}_i = c_i + \Phi(D_i) - \Phi(D_{i-1})$$

**Total amortized cost:**
$$\sum_{i=1}^n \hat{c}_i = \sum_{i=1}^n c_i + \Phi(D_n) - \Phi(D_0)$$

If $\Phi(D_n) \geq \Phi(D_0)$ for all $n$, then $\sum \hat{c}_i \geq \sum c_i$ → amortized costs upper-bound actual costs.

**Convention:** Define $\Phi(D_0) = 0$ and prove $\Phi(D_i) \geq 0$ for all $i$.

### Stack: $\Phi(D) = $ number of objects in stack

- PUSH: $\hat{c} = 1 + 1 = 2$
- POP: $\hat{c} = 1 + (-1) = 0$
- MULTIPOP($k'$): $\hat{c} = k' + (-k') = 0$

All operations $O(1)$ amortized → total $O(n)$.

### Binary Counter: $\Phi(D) = $ number of 1-bits

If INCREMENT resets $t_i$ bits and sets 1 bit:
$$\hat{c}_i \leq (t_i + 1) + (1 - t_i) = 2$$

Amortized cost $O(1)$ → total $O(n)$.

---

## 16.4 Dynamic Tables

A **dynamic table** doubles when full and (optionally) halves when $\frac{1}{4}$ full.

**Potential function for expansion:**
$$\Phi(T) = 2 \cdot T.\text{num} - T.\text{size}$$

Where `num` = number of items, `size` = allocated size.

**Amortized cost of INSERT:** $O(1)$ always.
- Normal insert (no expansion): $\hat{c} = 1 + 2 = 3$
- Expansion (doubles, costs `num`): amortized $= 3$ (potential drops to offset)

**Amortized cost of DELETE with contraction:** $O(1)$ — maintaining invariant `num` $\geq$ `size`/4 prevents too-frequent resizing.

**Overall:** Any sequence of $n$ INSERT/DELETE operations on a dynamic table costs $O(n)$ total — $O(1)$ amortized per operation.

---

## Summary of Three Methods

| Method | How it works | Best used when |
|---|---|---|
| **Aggregate** | $T(n)/n$ per operation | All operations have same amortized cost |
| **Accounting** | Assign credits to objects; credit must stay $\geq 0$ | Different operations have different amortized costs |
| **Potential** | $\hat{c}_i = c_i + \Delta\Phi$; find $\Phi$ with $\Phi(D_n) \geq \Phi(D_0)$ | More mathematical; useful for design insights |

All three methods yield the same asymptotic bounds for the same problem.

---

### Navigation
**Previous:** [[Ch15_Greedy_Algorithms]]
**Next:** [[Part5_Introduction_Advanced_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
