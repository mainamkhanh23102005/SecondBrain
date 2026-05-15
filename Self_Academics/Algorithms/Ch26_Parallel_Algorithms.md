# Chapter 26: Parallel Algorithms

## Executive Summary

Chapter 26 introduces **fork-join parallelism** for multicore computers. The model adds three keywords — `spawn`, `sync`, `parallel` — to ordinary pseudocode; deleting them yields the **serial projection**. Performance is analyzed via **work** $T_1$ (total computation) and **span** $T_\infty$ (critical-path length), giving **parallelism** $T_1/T_\infty$. A **greedy scheduler** achieves $T_P \leq T_1/P + T_\infty$ (Theorem 26.1), within factor 2 of optimal. Three parallel algorithms are developed: **P-MATRIX-MULTIPLY-RECURSIVE** (work $\Theta(n^3)$, span $\Theta(\log_2^2 n)$, parallelism $\Theta(n^3/\log_2^2 n)$), parallel **Strassen** (work $\Theta(n^{\log_2 7})$, same span), and **P-MERGE-SORT** (work $\Theta(n\log_2 n)$, span $\Theta(\log_2^3 n)$, parallelism $\Theta(n/\log_2^2 n)$) using a divide-and-conquer parallel merge.

---

## Zero-Loss Extraction

### Key Definitions

- **Strand:** maximal chain of sequential instructions with no parallel control
- **Trace:** DAG of strands representing execution dependencies
- **Work** $T_1$: running time on 1 processor = total time of all strands
- **Span** $T_\infty$: running time with unlimited processors = longest critical path in trace
- **Parallelism:** $T_1/T_\infty$ = average work per critical-path step = max achievable speedup
- **Slackness:** $(T_1/T_\infty)/P$ = factor by which parallelism exceeds processor count
- **Speedup on $P$ processors:** $T_1/T_P$; **linear speedup:** $T_1/T_P = \Theta(P)$
- **Determinacy race:** two parallel strands access same memory location, at least one writes

### Core Algorithms & Pseudocode

**P-FIB (Parallel Fibonacci — illustrative):**

```
P-FIB(n)
1  if n ≤ 1: return n
2  else x = spawn P-FIB(n − 1)   // fork: run in parallel
3       y = P-FIB(n − 2)          // continue while child runs
4       sync                       // join: wait for spawn
5       return x + y
```

**P-MATRIX-MULTIPLY (parallel loops):**

```
P-MATRIX-MULTIPLY(A, B, C, n)
1  parallel for i = 1 to n
2      parallel for j = 1 to n
3          for k = 1 to n
4              cij = cij + aik · bkj
```

**P-MATRIX-MULTIPLY-RECURSIVE (spawn-based divide-and-conquer):**

```
P-MATRIX-MULTIPLY-RECURSIVE(A, B, C, n)
1  if n == 1: c11 = c11 + a11 · b11; return
2  let D be new n × n matrix; parallel zero D
3  partition A, B, C, D into n/2 × n/2 submatrices
4  spawn P-M-M-R(A11, B11, C11, n/2)  // 4 spawns for C submatrices
5  spawn P-M-M-R(A11, B12, C12, n/2)
6  spawn P-M-M-R(A21, B11, C21, n/2)
7  spawn P-M-M-R(A21, B12, C22, n/2)
8  spawn P-M-M-R(A12, B21, D11, n/2)  // 4 spawns for D submatrices
9  spawn P-M-M-R(A12, B22, D12, n/2)
10 spawn P-M-M-R(A22, B21, D21, n/2)
11 spawn P-M-M-R(A22, B22, D22, n/2)
12 sync
13 parallel for i,j: cij = cij + dij    // C = C + D
```

**P-MERGE-SORT:**

```
P-MERGE-SORT(A, p, r)
1  if p ≥ r: return
2  q = ⌊(p + r)/2⌋
3  spawn P-MERGE-SORT(A, p, q)
4  spawn P-MERGE-SORT(A, q + 1, r)   // both halves in parallel
5  sync
6  P-MERGE(A, p, q, r)               // parallel merge
```

**P-MERGE-AUX (parallel divide-and-conquer merge):**

```
P-MERGE-AUX(A, p1, r1, p2, r2, B, p3)
1  if p1 > r1 and p2 > r2: return
2  if r1 − p1 < r2 − p2: swap subarrays  // ensure A[p1:r1] is larger
3  q1 = ⌊(p1 + r1)/2⌋; x = A[q1]         // x = median of larger subarray
4  q2 = FIND-SPLIT-POINT(A, p2, r2, x)   // binary search O(lg n)
5  q3 = p3 + (q1 − p1) + (q2 − p2); B[q3] = x
6  spawn P-MERGE-AUX(A, p1, q1−1, p2, q2−1, B, p3)   // merge lower halves
7  spawn P-MERGE-AUX(A, q1+1, r1, q2, r2, B, q3+1)   // merge upper halves
8  sync
```

---

## Deep-Dive Explanations

### The Work/Span Model

A **parallel trace** is a DAG of strands. Two strands are **in series** if one path connects them; **in parallel** if no path connects them in either direction.

**Series composition:** spans add; works add.
**Parallel composition:** work adds, span = max of spans.

**Analyzing P-FIB(n):**
$$T_1(n) = \Theta(\phi^n), \quad T_\infty(n) = \Theta(n), \quad \text{Parallelism} = \Theta(\phi^n/n)$$

**Parallel loop span** (via recursive spawning): for $n$ iterations each with span $\text{iter}_\infty$:
$$T_\infty = \Theta(\log_2 n) + \max_i\{\text{iter}_\infty(i)\}$$

### Scheduling Theory

**Work law:** $T_P \geq T_1/P$ (can't do more than $P$ work per step).

**Span law:** $T_P \geq T_\infty$ (can't beat the critical path).

**Theorem 26.1 (Greedy scheduler bound):** A greedy scheduler satisfies:
$$T_P \leq T_1/P + T_\infty$$
*Proof:* Complete steps (at least $P$ strands ready): at most $T_1/P$ such steps. Incomplete steps (fewer than $P$ ready): each reduces span by 1, so at most $T_\infty$ such steps.

**Corollary 26.2:** Greedy scheduler is within factor 2 of optimal ($T_P \leq 2T_P^*$).

**Corollary 26.3:** If $P \ll T_1/T_\infty$ (slackness $\gg 1$), then $T_P \approx T_1/P$ (near-perfect linear speedup).

### Parallel Matrix Algorithms

**P-MATRIX-MULTIPLY** (parallelizing outer two loops):
- Work: $T_1 = \Theta(n^3)$; Span: $T_\infty = \Theta(n)$; Parallelism: $\Theta(n^2)$

**P-MATRIX-MULTIPLY-RECURSIVE** (eight parallel spawns, temp matrix $D$ avoids races):
- Work: $M_1(n) = 8M_1(n/2) + \Theta(n^2) = \Theta(n^3)$
- Span recurrence: $M_\infty(n) = M_\infty(n/2) + \Theta(\log_2^2 n) = \Theta(\log_2^2 n)$ (master theorem case 2, $k=1$)
- Parallelism: $\Theta(n^3/\log_2^2 n)$

**Parallel Strassen (7 spawns):**
- Work: $\Theta(n^{\log_2 7})$; Span: $\Theta(\log_2^2 n)$; Parallelism: $\Theta(n^{\log_2 7}/\log_2^2 n)$

### Parallel Merge Sort

**P-NAIVE-MERGE-SORT** (parallel recursion, serial MERGE):
- Work: $\Theta(n\log_2 n)$; Span: $T_\infty(n) = T_\infty(n/2) + \Theta(n) = \Theta(n)$; Parallelism: **only $\Theta(\log_2 n)$** — bottlenecked by serial merge.

**P-MERGE (parallel merge via P-MERGE-AUX):**
- Key: split larger subarray at median, binary search for split in smaller, recurse in parallel
- Each recursive spawn handles $\leq 3n/4$ elements (since median of larger splits fairly)
- Span: $T_\infty(n) = T_\infty(3n/4) + \Theta(\log_2 n) = \Theta(\log_2^2 n)$ (master theorem case 2, $k=1$)
- Work: $T_1(n) = \Theta(n)$ (proved by substitution; matches serial merge)

**P-MERGE-SORT (with P-MERGE):**
- Work: $T_1(n) = 2T_1(n/2) + \Theta(n) = \Theta(n\log_2 n)$
- Span: $T_\infty(n) = T_\infty(n/2) + \Theta(\log_2^2 n) = \Theta(\log_2^3 n)$ (master case 2, $k=2$)
- Parallelism: $\Theta(n\log_2 n)/\Theta(\log_2^3 n) = \Theta(n/\log_2^2 n)$ — much better than $\Theta(\log_2 n)$

### Determinacy Races

A **determinacy race** occurs when two parallel strands access the same memory location and at least one modifies it. Example: `parallel for i = 1 to 2: x = x + 1` may print 1 instead of 2 due to interleaved load/increment/store instructions.

Prevention: parallel strands must be **mutually noninterfering** (only read, never write, shared variables). The faulty `P-MAT-VEC-WRONG` parallelizes the inner loop of matrix-vector multiply but races on `yi`.

### Time and Space Complexity

| Algorithm | Work $T_1$ | Span $T_\infty$ | Parallelism $T_1/T_\infty$ |
|-----------|-----------|----------------|---------------------------|
| P-FIB(n) | $\Theta(\phi^n)$ | $\Theta(n)$ | $\Theta(\phi^n/n)$ |
| P-MAT-VEC | $\Theta(n^2)$ | $\Theta(n)$ | $\Theta(n)$ |
| P-MATRIX-MULTIPLY | $\Theta(n^3)$ | $\Theta(n)$ | $\Theta(n^2)$ |
| P-MATRIX-MULTIPLY-RECURSIVE | $\Theta(n^3)$ | $\Theta(\log_2^2 n)$ | $\Theta(n^3/\log_2^2 n)$ |
| Parallel Strassen | $\Theta(n^{\log_2 7})$ | $\Theta(\log_2^2 n)$ | $\Theta(n^{\log_2 7}/\log_2^2 n)$ |
| P-NAIVE-MERGE-SORT | $\Theta(n\log_2 n)$ | $\Theta(n)$ | $\Theta(\log_2 n)$ |
| P-MERGE | $\Theta(n)$ | $\Theta(\log_2^2 n)$ | $\Theta(n/\log_2^2 n)$ |
| P-MERGE-SORT | $\Theta(n\log_2 n)$ | $\Theta(\log_2^3 n)$ | $\Theta(n/\log_2^2 n)$ |

---

## Key Takeaways & Next Steps

1. **Work/Span analysis** separates total computation ($T_1$) from critical-path depth ($T_\infty$); parallelism $T_1/T_\infty$ is the most important single metric.
2. **Greedy scheduling** achieves $T_P \leq T_1/P + T_\infty$; near-perfect linear speedup when slackness $\gg 1$.
3. **Recursive spawning** is the key technique: 8 parallel spawns in matrix multiply give $\Theta(\log_2^2 n)$ span with $\Theta(n^3)$ work.
4. **P-MERGE** illustrates that seemingly serial algorithms (merging) can be parallelized via divide-and-conquer, improving parallelism from $\Theta(\log_2 n)$ to $\Theta(n/\log_2^2 n)$.
5. **Determinacy races** are subtle bugs; parallel strands must not write to shared variables without synchronization.

---

### Navigation

**Previous:** [[PartVII_Selected_Topics]]
**Next:** [[Ch27_Online_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
