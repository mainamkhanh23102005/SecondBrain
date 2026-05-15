# Chapter 26: Parallel Algorithms

**Source:** Introduction to Algorithms (CLRS), Chapter 26  
**Tags:** #algorithms #parallel #fork-join #multicore #work-span

---

## Executive Summary

This chapter extends the serial algorithm model to **fork-join parallel algorithms** for shared-memory multicore machines. Three new pseudocode keywords — `spawn`, `sync`, and `parallel` — express logical parallelism without binding it to specific processors. A DAG-based **trace** model captures execution dependencies, while **work/span analysis** provides tight bounds on running time across any number of processors. Core results: the greedy scheduler theorem ($T_P \leq T_1/P + T_\infty$), parallel matrix multiplication achieving $\Theta(n^2)$ parallelism, and parallel merge sort achieving $\Theta(n/\log_2^2 n)$ parallelism.

---

## Zero-Loss Extraction

### 1. Fork-Join Model

**Three keywords added to pseudocode:**

| Keyword | Meaning |
|---------|---------|
| `spawn f(...)` | Call $f$ in parallel; caller continues without waiting |
| `sync` | Wait for all outstanding spawned children to return |
| `parallel for` | Loop iterations may execute simultaneously |

**Serial projection:** delete all three keywords → ordinary correct serial pseudocode for the same problem. This property ensures correctness.

**Task-parallel platforms** (e.g., Cilk, OpenMP, Java Fork-Join, TBB) sit above raw threads, handling load balancing automatically.

---

### 2. The Trace (DAG) Model

Execution is modeled as a directed acyclic graph $G = (V, E)$:
- **Strand:** maximal chain of sequential instructions with no spawn/sync/call/return. Vertices of $G$.
- **Edge $(u,v)$:** strand $u$ must finish before strand $v$ starts.
- **In series:** $G$ has a directed path $u \to v$ or $v \to u$.
- **In parallel:** no directed path in either direction.

**Spawn** adds two outgoing edges from the parent strand: one to the child's first strand, one to the parent's continuation. **Sync** adds incoming edges from each outstanding spawned child's last strand to the post-sync strand. **Ideal parallel computer** assumes sequentially consistent shared memory and equal-power processors.

---

### 3. Work and Span

$$T_1 = \text{work} = \text{total time on 1 processor (sum of strand times)}$$
$$T_\infty = \text{span} = \text{length of critical path (longest weighted path in trace)}$$
$$\text{Parallelism} = \frac{T_1}{T_\infty} = \text{max possible speedup on any \# processors}$$
$$\text{Slackness} = \frac{T_1}{P \cdot T_\infty}$$

**Work Law:**
$$T_P \geq \frac{T_1}{P}$$

**Span Law:**
$$T_P \geq T_\infty$$

**Speedup:** $T_1/T_P \leq P$ (at most linear).

---

### 4. Greedy Scheduling Theorems

**Greedy scheduler:** never leaves a processor idle when there is ready work.

- **Complete step:** $\geq P$ ready strands → assign any $P$.
- **Incomplete step:** $< P$ ready strands → assign all, leave some processors idle.

**Theorem 26.1:** On a $P$-processor ideal parallel computer, a greedy scheduler runs any computation with work $T_1$ and span $T_\infty$ in time
$$T_P \leq \frac{T_1}{P} + T_\infty$$

**Corollary 26.2:** $T_P \leq 2\,T_P^*$ (greedy is within factor 2 of optimal).

**Corollary 26.3:** If $P \ll T_1/T_\infty$ (slackness $\gg 1$), then $T_P \approx T_1/P$ — near-perfect linear speedup. Rule of thumb: slackness $\geq 10$ suffices in practice.

---

### 5. P-FIB Example

```
P-FIB(n)
1  if n ≤ 1
2      return n
3  else x = spawn P-FIB(n − 1)   // fork: run in parallel
4       y = P-FIB(n − 2)
5       sync                       // join: wait for spawned child
6       return x + y
```

- **Work:** $T_1(n) = \Theta(\phi^n)$ where $\phi = (1+\sqrt5)/2$ (golden ratio).
- **Span recurrence:** $T_\infty(n) = \max\{T_\infty(n-1),\, T_\infty(n-2)\} + \Theta(1) = T_\infty(n-1) + \Theta(1)$, so $T_\infty(n) = \Theta(n)$.
- **Parallelism:** $T_1/T_\infty = \Theta(\phi^n / n)$ — grows explosively with $n$.

---

### 6. Parallel Loops via Recursive Spawning

A compiler implements `parallel for i = 1 to n { body }` by spawning a binary tree of procedure instances:

```
P-LOOP-HELPER(lo, hi)
1  if lo == hi
2      execute body(lo)         // base case: single iteration
3  else mid = ⌊(lo + hi) / 2⌋
4       spawn P-LOOP-HELPER(lo, mid)
5       P-LOOP-HELPER(mid+1, hi)
6       sync
```

**Overhead:** tree has $n-1$ internal nodes → constant-factor overhead on work (absorbed asymptotically). Span gains $\Theta(\log_2 n)$ for the tree depth.

**Span formula for parallel loop with iterations of individual span $\text{iter}_\infty(i)$:**
$$T_\infty = \Theta(\log_2 n) + \max_{1 \leq i \leq n} \text{iter}_\infty(i)$$

**Example — P-MAT-VEC** ($n \times n$ matrix × vector):

```
P-MAT-VEC(A, x, y, n)
1  parallel for i = 1 to n
2      for j = 1 to n
3          y_i = y_i + a_{ij} * x_j
```

- $T_1 = \Theta(n^2)$, $T_\infty = \Theta(n)$, Parallelism $= \Theta(n)$.

---

### 7. Race Conditions

A **determinacy race** occurs when two logically parallel strands access the same memory location and at least one modifies it. Race bugs are non-deterministic and notoriously hard to reproduce.

```
RACE-EXAMPLE()
1  x = 0
2  parallel for i = 1 to 2
3      x = x + 1              // ← determinacy race!
4  print x                    // may print 1 (wrong) or 2 (correct)
```

The increment `x = x + 1` is a load-increment-store sequence. If both processors load $x = 0$ before either stores, both compute $1$ and the final value is $1$, not $2$.

**Solution:** redesign to avoid shared mutable state in parallel strands, or use synchronization primitives (locks, atomics).

---

### 8. Parallel Matrix Multiplication (§26.2)

**P-SQUARE-MATRIX-MULTIPLY** (parallel outer loops):

```
P-SQUARE-MATRIX-MULTIPLY(A, B, C, n)
1  parallel for i = 1 to n
2      parallel for j = 1 to n
3          for k = 1 to n
4              c_{ij} = c_{ij} + a_{ik} * b_{kj}
```

- $T_1 = \Theta(n^3)$, $T_\infty = \Theta(n)$, Parallelism $= \Theta(n^2)$.

**Recursive parallel** (spawn 8 sub-multiplications):
- $T_1(n) = 8\,T_1(n/2) + \Theta(n^2) = \Theta(n^3)$
- $T_\infty(n) = T_\infty(n/2) + \Theta(n) = \Theta(n)$ (addition step dominates)
- Parallelism $= \Theta(n^2)$.

---

### 9. Parallel Merge Sort (§26.3)

**P-MERGE** (parallel merge using binary search):
- Find the median of the larger input array in the smaller via binary search.
- Recursively merge each half in parallel.
- Work: $\Theta(n \log_2 n)$, Span: $\Theta(\log_2^2 n)$.

**P-MERGE-SORT** overall:
- Work: $T_1(n) = \Theta(n \log_2 n)$
- Span: $T_\infty(n) = \Theta(\log_2^3 n)$
- Parallelism: $\Theta(n / \log_2^2 n)$

---

## Deep-Dive Explanations

### Why Series-Parallel Composition Works for Span Analysis

Any fork-join trace decomposes into series and parallel compositions of sub-traces:
- **Series:** spans add — $T_\infty(A ; B) = T_\infty(A) + T_\infty(B)$.
- **Parallel:** spans take max — $T_\infty(A \| B) = \max(T_\infty(A), T_\infty(B))$.

This is why the spawned call to P-FIB$(n-1)$ and the continuation P-FIB$(n-2)$ contribute a max: they run in parallel. The Θ(1) for the sync/return/call overhead is added in series.

### Greedy Scheduler Proof Sketch

Complete steps: if there are $k$ complete steps, total work $\geq kP$, so $k \leq T_1/P$.  
Incomplete steps: in each incomplete step, every ready strand executes, so the remaining critical-path length strictly decreases by $\geq 1$. Hence at most $T_\infty$ incomplete steps.  
Total: $T_P \leq T_1/P + T_\infty$.

---

## Key Takeaways & Next Steps

1. **Express *what* can run in parallel, not *how*:** spawn/sync specify logical parallelism; the scheduler handles assignment.
2. **Work $=$ serial cost; span $=$ parallelism bottleneck.** Minimizing both is the design goal.
3. **Greedy schedulers are within 2× of optimal** and achieve near-linear speedup when slackness $\gg 1$.
4. **Parallel loops add only $\Theta(\log_2 n)$ to span** via recursive spawning — cheap parallelism.
5. **Race conditions break determinism silently** — eliminate shared writes in parallel strands.

---

### Navigation

- **Previous:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms — Index Hub]]
- **Next:** [[Ch27_Online_Algorithms|Ch27 — Online Algorithms]]
- **Hub:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms Index]]
