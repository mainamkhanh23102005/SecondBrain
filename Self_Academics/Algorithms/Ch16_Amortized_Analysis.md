# Chapter 16: Amortized Analysis

## Executive Summary

Chapter 16 presents **amortized analysis** — a technique for bounding the average cost per operation in a sequence of data-structure operations, even when individual operations vary wildly in cost. Unlike average-case analysis, amortized analysis gives **worst-case guarantees** without probability. Three methods are covered: **aggregate analysis** (total cost / $n$), **accounting method** (assign amortized costs; store excess as credit on objects), and **potential method** (store excess as a potential function $\Phi$ on the data structure). All three are illustrated on stacks with MULTIPOP and binary counters with INCREMENT. Section 16.4 applies potential analysis to **dynamic tables**, proving $O(1)$ amortized cost per insertion even with table doubling.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Stack with MULTIPOP:**

```
MULTIPOP(S, k)
1  while not STACK-EMPTY(S) and k > 0
2      POP(S)
3      k = k − 1
```

**Binary counter INCREMENT:**

```
INCREMENT(A, k)
1  i = 0
2  while i < k and A[i] == 1
3      A[i] = 0
4      i = i + 1
5  if i < k
6      A[i] = 1
```

**Dynamic table TABLE-INSERT (with doubling):**

```
TABLE-INSERT(T, x)
1  if T.size == 0
2      allocate T.table with 1 slot;  T.size = 1
3  if T.num == T.size           // table is full → expand
4      allocate new-table with 2·T.size slots
5      insert all items in T.table into new-table
6      free T.table
7      T.table = new-table;  T.size = 2·T.size
8  insert x into T.table
9  T.num = T.num + 1
```

---

## Deep-Dive Explanations

### Method 1: Aggregate Analysis

**Idea:** Show that $n$ operations take $T(n)$ total time. Assign amortized cost $T(n)/n$ to each operation (same for all types).

**Stack + MULTIPOP example:**
- Worst-case single MULTIPOP: $O(n)$, giving naïve bound $O(n^2)$ for $n$ operations.
- **Key observation:** Every object can be popped at most once per push. Total pops ≤ total pushes ≤ $n$.
- Total cost of any $n$ operations: $O(n)$. Amortized cost per operation: $O(1)$.

**Binary counter example:**
- Worst-case single INCREMENT: $\Theta(k)$. Naïve bound: $O(nk)$ for $n$ operations.
- **Key observation:** Bit $A[i]$ flips at most $\lfloor n/2^i \rfloor$ times in $n$ INCREMENTs.
$$\text{Total flips} = \sum_{i=0}^{k-1} \left\lfloor \frac{n}{2^i} \right\rfloor < n \sum_{i=0}^{\infty} \frac{1}{2^i} = 2n$$
- Total cost: $O(n)$. Amortized cost per INCREMENT: $O(1)$.

### Method 2: Accounting Method

**Idea:** Assign amortized costs $\hat{c}_i$ (possibly $\neq$ actual cost $c_i$). Excess charge = **credit** stored on specific objects. **Invariant:** total credit $\geq 0$ always (otherwise amortized cost is not a valid upper bound on actual cost).

$$\sum_{i=1}^n \hat{c}_i \geq \sum_{i=1}^n c_i \quad \Longleftrightarrow \quad \text{total credit} \geq 0$$

**Stack + MULTIPOP:**

| Operation | Actual cost | Amortized cost | Credit |
|-----------|-------------|----------------|--------|
| PUSH | 1 | 2 | +1 stored on top object |
| POP | 1 | 0 | −1 taken from popped object |
| MULTIPOP($k'$) | $k'$ | 0 | −$k'$ from $k'$ objects |

Each object always has $\$1$ credit when on the stack → total credit ≥ 0 always. Total amortized cost = $O(n)$ → total actual cost = $O(n)$.

**Binary counter:**
- Setting a bit to 1: amortized cost = 2 ($\$1$ actual + $\$1$ credit stored on the bit).
- Resetting a bit to 0: amortized cost = 0 ($\$1$ credit pays the actual cost).
- Each INCREMENT sets at most one bit to 1 → amortized cost ≤ 2 per INCREMENT → total $O(n)$.

### Method 3: Potential Method

**Idea:** Define potential function $\Phi: D \to \mathbb{R}$ on the data structure state. Define amortized cost:
$$\hat{c}_i = c_i + \Phi(D_i) - \Phi(D_{i-1})$$

Telescoping: $\sum_{i=1}^n \hat{c}_i = \sum_{i=1}^n c_i + \Phi(D_n) - \Phi(D_0)$

If $\Phi(D_n) \geq \Phi(D_0)$ for all $n$, then $\sum \hat{c}_i \geq \sum c_i$ (amortized costs bound actual costs).

**Stack + MULTIPOP:** Define $\Phi$ = number of objects on the stack.
- $\Phi(D_0) = 0$; $\Phi(D_i) \geq 0$ always.
- PUSH: $\hat{c} = 1 + ((s+1) - s) = 2$
- MULTIPOP($k'$): $\hat{c} = k' + (-k') = 0$
- POP: $\hat{c} = 1 + (-1) = 0$
- All three operations have amortized cost $O(1)$ → total actual cost $O(n)$.

**Binary counter:** Define $\Phi$ = number of 1-bits in the counter.
- If INCREMENT resets $t_i$ bits to 0 and sets at most 1 bit to 1:
  - Actual cost: $c_i \leq t_i + 1$
  - Potential difference: $\Phi(D_i) - \Phi(D_{i-1}) \leq 1 - t_i$
  - Amortized cost: $\hat{c}_i = c_i + \Delta\Phi \leq (t_i + 1) + (1 - t_i) = 2$
- Total actual cost of $n$ INCREMENTs: $O(n)$.

### Dynamic Tables (Section 16.4)

**TABLE-INSERT with doubling:** When the table is full, allocate a new table with **twice** as many slots and copy all items. Actual cost of $i$-th operation: $c_i = i$ if expansion occurs, $c_i = 1$ otherwise.

**Aggregate analysis:** Expansions occur at sizes 1, 2, 4, 8, ... Total cost of $n$ insertions:
$$\sum c_i \leq n + \sum_{j=0}^{\lfloor \log_2 n \rfloor} 2^j < n + 2n = 3n = O(n)$$

**Amortized cost per TABLE-INSERT: $O(1)$.**

**Potential method:** $\Phi(T) = 2 \cdot T.\text{num} - T.\text{size}$
- After expansion: load factor $= 1/2$, so $\Phi = 0$.
- $\Phi \geq 0$ always (since load factor $\geq 1/2$ by invariant).
- Standard insertion (no expansion): $\hat{c} = 1 + (2(n+1) - m) - (2n - m) = 3$
- Expansion (table was full): $\hat{c} = n+1 + (2(n+1) - 2n) - (2n - n) = 3$
- Amortized cost: $O(1)$ in all cases.

**Load factor invariant:** After any sequence of TABLE-INSERT operations (with doubling), load factor $\alpha(T) \geq 1/2$ always. So unused space $\leq$ used space — never more than a constant fraction wasted.

### Summary of Three Methods

| Method | Amortized cost for | Key invariant |
|--------|-------------------|---------------|
| Aggregate | All operations (same) | Total cost / $n$ |
| Accounting | Per-operation type | Total credit $\geq 0$ |
| Potential | Per-operation | $\Phi(D_i) \geq \Phi(D_0)$ for all $i$ |

All three yield the same amortized bounds when applied correctly. Choice of method depends on which is most natural for the data structure.

---

## Key Takeaways & Next Steps

1. **Amortized $\neq$ average-case**: amortized gives worst-case guarantees about sequences; average-case uses probability over inputs.
2. **Aggregate**: simplest; assign same amortized cost to all operations.
3. **Accounting**: most flexible; different amortized costs per operation type; credit must stay non-negative.
4. **Potential**: most powerful; generalizes accounting; $\Phi$ captures "stored work" in the data structure state.
5. **Dynamic table doubling** achieves $O(1)$ amortized insert by spreading expansion costs over many cheap operations — the canonical practical application of amortized analysis.

---

### Navigation

**Previous:** [[Ch15_Greedy_Algorithms]]
**Next:** [[PartV_Advanced_Data_Structures]]
**Hub:** [[Index_Introduction_to_Algorithms]]
