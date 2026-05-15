# Chapter 27: Online Algorithms

**Source:** Introduction to Algorithms (CLRS), Chapter 27  
**Tags:** #algorithms #online #competitive-analysis #caching #LRU

---

## Executive Summary

**Online algorithms** receive input progressively and must act without knowledge of future inputs. This chapter analyzes them via **competitive analysis**: comparing an online algorithm's cost against the optimal offline (all-knowing) algorithm on the same input, taking the worst-case ratio. Three problems are studied: the stairs-vs-elevator toy problem (introducing competitive ratio), the **list-maintenance problem** (MOVE-TO-FRONT is 4-competitive), and **online caching** (LIFO has $\Theta(n/k)$ competitive ratio; LRU has $\Theta(k)$; RANDOMIZED-MARKING has $O(\log_2 k)$ expected ratio against an oblivious adversary).

---

## Zero-Loss Extraction

### 1. Online vs. Offline

| | **Online** | **Offline** |
|---|---|---|
| Input | Arrives progressively | Known in advance |
| Decisions | Irrevocable, made without future knowledge | Can be globally optimal |
| Analysis | Competitive ratio vs. optimal offline | Worst-case or average-case |

**Offline algorithm** (sometimes called "seer" or FORESEE): knows the entire future. Used as a benchmark.

---

### 2. Competitive Ratio

For a **minimization** problem, if online algorithm $A$ has cost $A(I)$ on input $I$ and the optimal offline algorithm has cost $F(I)$:

$$\text{competitive ratio of } A = \max_{I \in U} \frac{A(I)}{F(I)}$$

If this ratio is $c$, algorithm $A$ is **$c$-competitive**. The ratio is always $\geq 1$; smaller is better. For **randomized** algorithms, the expected competitive ratio replaces $A(I)$ with $\mathbb{E}[A(I)]$.

---

### 3. Stairs-vs-Elevator (§27.1)

**Setup:** $k$ floors up, elevator arrives in $[0, B-1]$ minutes. Staircase always takes $k$ minutes.

| Algorithm | Cost | Competitive Ratio |
|-----------|------|-------------------|
| Always stairs | $k$ | $k$ |
| Always elevator | $m+1$ | $B/k$ |
| **Hedging** (wait $k$ min, then take stairs) | $\leq 2k$ | **2** |

**Hedging strategy cost $h(m)$:**
$$h(m) = \begin{cases} m+1 & \text{if elevator arrives within } k \text{ min} \\ 2k & \text{if elevator arrives after } k \text{ min} \end{cases}$$

Competitive ratio of hedging = $2$, independent of $k$ and $B$.

**Key insight:** initially waiting guards against fast elevators; switching to stairs guards against slow elevators.

---

### 4. List Maintenance: MOVE-TO-FRONT (§27.2)

**Problem:** maintain a linked list of $n$ elements $\{x_1,\ldots,x_n\}$. Searching for $x$ at position $r$ costs $r$; moving adjacent elements costs $1$ per swap. Goal: minimize total search + swap cost.

**MOVE-TO-FRONT(L, x):** search for $x$ (cost $r_L(x)$), then swap it to the front (cost $r_L(x)-1$). Total cost: $2r_L(x)-1$.

**FORESEE:** optimal offline algorithm that knows future requests; rearranges list optimally after each search.

**Inversion count** $I(L, L')$: number of pairs whose relative order differs between two lists $L$ and $L'$.

**Theorem 27.1:** MOVE-TO-FRONT has competitive ratio **4**.

**Proof sketch (potential method):**  
Define $\Phi_i = 2\,I(L^M_i, L^F_i)$ (twice the inversion count between the two lists after step $i$, $\Phi_0 = 0$, $\Phi_i \geq 0$). Analysis using amortized cost shows:
$$\sum_{i=1}^m c^M_i \leq 4 \sum_{i=1}^m c^F_i$$

where $c^M_i, c^F_i$ are MOVE-TO-FRONT's and FORESEE's costs on call $i$.

**Swap impact on inversion count:** swapping adjacent $x,y$ in one list changes $I(L, L')$ by exactly $\pm 1$.

---

### 5. Online Caching (§27.3)

**Setup:** $n$ memory requests for blocks $b_1, b_2, \ldots, b_n$. Cache holds $\leq k$ blocks. On a **cache miss** with a full cache, one block must be **evicted**. Goal: minimize total cache misses.

#### 5.1 Eviction Policies

| Policy | Evict | Competitive Ratio |
|--------|-------|-------------------|
| **LIFO** | Most recently added | $\Theta(n/k)$ — **unbounded** |
| **LFU** | Least frequently used | $\Theta(n/k)$ — **unbounded** |
| **FIFO** | Oldest in cache | $O(k)$ |
| **LRU** | Least recently used | $\Theta(k)$ |
| **RANDOMIZED-MARKING** | Random unmarked block | $O(\log_2 k)$ expected |

#### 5.2 LIFO is Terrible: $\Theta(n/k)$ (Theorem 27.2)

**Lower bound construction:** request sequence $1,2,\ldots,k, k{+}1, k, k{+}1, k, k{+}1, \ldots$ LIFO evicts block $k$ for $k+1$ then block $k+1$ for $k$ on every alternation — every request is a miss. The optimal offline algorithm (furthest-in-future) evicts only once after the initial $k$ compulsory misses.

#### 5.3 LRU is $\Theta(k)$ (Theorem 27.3)

**Epoch partitioning:** Epoch $i$ begins upon the $(k+1)$-st distinct request since epoch $i-1$ began.

- **LRU:** each epoch has $\leq k$ misses (first-request-in-epoch is the only possible miss for each block, and there are $\leq k$ distinct blocks per epoch).
- **Optimal offline:** must incur $\geq 1$ miss per epoch (the first request of each epoch was last seen $\geq k$ requests ago).
- Ratio $\leq k/1 = O(k)$.

FIFO also achieves $O(k)$ (Exercise 27.3-3).

#### 5.4 Lower Bound $\Omega(k)$ for Any Deterministic Algorithm (Theorem 27.4)

**Adversary argument:** with $k+1$ possible blocks, an adversary always requests the block just evicted by the deterministic algorithm, forcing a miss every request. The optimal offline (furthest-in-future) incurs $\leq k + n/k$ misses. For $n \geq k^2$:

$$\text{competitive ratio} \geq \frac{n}{k + n/k} \geq \frac{k}{2} = \Omega(k)$$

Every deterministic online caching algorithm has competitive ratio $\Omega(k)$.

#### 5.5 RANDOMIZED-MARKING is $O(\log_2 k)$ (Theorem 27.5)

**Algorithm:** maintain a `mark` bit per cached block (initially 0). On request for block $b$:
- Cache hit: mark $b$.
- Cache miss + not all marked: evict a uniformly random **unmarked** block; bring in $b$, mark it.
- Cache miss + all marked: reset all marks to 0, then proceed as above.

```
RANDOMIZED-MARKING(b)
1  if b is in cache
2      b.mark = 1
3  else
4      if all cached blocks are marked
5          set all b'.mark = 0 for every cached b'
6      select an unmarked block u uniformly at random
7      evict u
8      place b in cache
9      b.mark = 1
```

**Epochs** (same as LRU proof): an epoch spans $k$ distinct block requests. $r_i$ = number of **new** requests (not seen in epoch $i-1$) in epoch $i$.

**Lemma 27.6 (Ball Drawing):** A bag has $x-1$ blue balls, $y$ white balls, 1 red ball. Draw until $m$ non-white balls chosen ($m \leq x$). Probability the red ball is chosen $= m/x$.

**Expected misses in epoch $i$:**
- New requests: always miss → $r_i$ misses.
- Old requests: $j$-th old request misses with probability $\leq r_i/(k-j+1)$.

$$\mathbb{E}[X_i] \leq r_i + r_i \sum_{j=1}^{k-r_i} \frac{1}{k-j+1} \leq r_i (1 + H_k) = O(r_i \log_2 k)$$

where $H_k$ is the $k$-th harmonic number ($H_k = \Theta(\log_2 k)$).

**Optimal offline lower bound:** over two consecutive epochs $i-1$ and $i$, at least $r_i$ cache misses must occur regardless of algorithm.

**Expected competitive ratio:**
$$\frac{\mathbb{E}[X]}{\text{OPT}} \leq \frac{\sum_i O(r_i \log_2 k)}{\sum_i r_i} = O(\log_2 k)$$

**Oblivious adversary:** does not know the random choices; knows only the algorithm. This assumption is necessary — a nonoblivious adversary can exploit randomness as if the algorithm were deterministic.

---

## Deep-Dive Explanations

### The Potential Method for MOVE-TO-FRONT

The proof uses $\Phi_i = 2\,I(L^M_i, L^F_i)$. When MOVE-TO-FRONT moves $x$ to the front:
- Elements in $BB$ (before $x$ in both lists): each swap with one creates a new inversion → inversion count $+|BB|$.
- Elements in $BA$ (before $x$ in MTF's list but after in FORESEE's): each swap removes an inversion → inversion count $-|BA|$.

FORESEE's $t_i$ swaps change potential by at most $2t_i$ (each swap changes inversion count by $\pm 1$).

Amortized cost of MTF's $i$-th call:
$$\hat{c}^M_i = c^M_i + \Delta\Phi_i \leq (1 + 2r^M(x)) + 2(|BB|-|BA|) + 2t_i \leq 4c^F_i$$

Summing over all $m$ calls: $\sum c^M_i \leq \sum \hat{c}^M_i \leq 4\sum c^F_i$.

### Why RANDOMIZED-MARKING Beats the $\Omega(k)$ Deterministic Lower Bound

The adversary argument for the $\Omega(k)$ lower bound assumed the adversary knows which block was evicted. Against a **randomized** algorithm with an **oblivious** adversary, the adversary must commit to the entire request sequence before seeing the algorithm's random choices. The adversary cannot guarantee that every request is a cache miss, because it doesn't know which blocks are marked.

---

## Key Takeaways & Next Steps

1. **Competitive ratio** measures worst-case performance relative to an omniscient algorithm — it's the online analog of approximation ratio.
2. **Hedging beats extremes:** waiting then switching (stairs-elevator) achieves competitive ratio 2, whereas always-stairs has ratio $k$ and always-elevator has ratio $B/k$.
3. **MOVE-TO-FRONT is 4-competitive** — the potential-function proof shows that inversions between the two lists are a reliable proxy for cost differences.
4. **All deterministic caching algorithms have ratio $\Omega(k)$** — randomization is the only escape.
5. **RANDOMIZED-MARKING achieves $O(\log_2 k)$** expected ratio against an oblivious adversary — exponentially better than deterministic algorithms.
6. **Next:** Chapter 28 (Matrix Operations) — LUP decomposition and matrix inversion.

---

### Navigation

- **Previous:** [[Ch26_Parallel_Algorithms|Ch26 — Parallel Algorithms]]
- **Next:** [[Ch28_Matrix_Operations|Ch28 — Matrix Operations]]
- **Hub:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms Index]]
