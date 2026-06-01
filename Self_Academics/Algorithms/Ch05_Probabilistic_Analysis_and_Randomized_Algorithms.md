# Chapter 5: Probabilistic Analysis and Randomized Algorithms

## Executive Summary

Chapter 5 introduces **probabilistic analysis** (analyzing performance under an assumed input distribution) and **randomized algorithms** (algorithms that make random choices to guarantee performance regardless of input). The central example is the **hiring problem**, analyzed via **indicator random variables** — a powerful technique that converts probability questions into expectation calculations using linearity of expectation. Key results: on average you hire $O(\ln n)$ times; randomly permuting the input converts this average-case guarantee into an **expected-case guarantee** independent of adversarial inputs. The chapter also covers the birthday paradox and on-line hiring.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Hiring problem (deterministic):**

```
HIRE-ASSISTANT(n)
1  best = 0          // candidate 0 is least-qualified dummy
2  for i = 1 to n
3      interview candidate i
4      if candidate i is better than candidate best
5          best = i
6          hire candidate i
```

Cost model: interview fee $c_i$ (cheap), hiring fee $c_h$ (expensive). Total cost = $O(c_i n + c_h m)$ where $m$ = number hired. Focus on hiring cost $c_h m$.

**Randomized hiring (impose random order):**

```
RANDOMIZED-HIRE-ASSISTANT(n)
1  randomly permute the list of candidates
2  HIRE-ASSISTANT(n)
```

**Uniform random permutation in-place ($\Theta(n)$ time):**

```
RANDOMLY-PERMUTE(A, n)
1  for i = 1 to n
2      swap A[i] with A[RANDOM(i, n)]
```

**Key definitions:**
- **RANDOM(a, b):** Returns a uniform random integer from $\{a, a+1, \ldots, b\}$.
- **Uniform random permutation:** Each of the $n!$ permutations equally likely (probability $1/n!$).
- **Indicator random variable:** $I\{A\} = \begin{cases}1 & \text{if event } A \text{ occurs} \\ 0 & \text{otherwise}\end{cases}$

---

## Deep-Dive Explanations

### Probabilistic Analysis vs. Randomized Algorithms

| Aspect | Probabilistic Analysis | Randomized Algorithm |
|--------|----------------------|----------------------|
| Source of randomness | Input distribution (assumed) | Algorithm's own random choices |
| Running time | Average-case (over input dist.) | Expected running time (over algorithm choices) |
| Guarantee | Valid only if distribution assumption holds | Holds for **any** input |
| Example | HIRE-ASSISTANT assuming random order | RANDOMIZED-HIRE-ASSISTANT |

### Indicator Random Variables — Lemma 5.1

**Lemma 5.1:** For event $A$, let $X_A = I\{A\}$. Then $E[X_A] = \Pr\{A\}$.

**Power:** Decompose complex quantities into sums of simple indicator variables, then apply linearity of expectation (which holds even for **dependent** variables):
$$E\left[\sum_i X_i\right] = \sum_i E[X_i]$$

### Analysis of Hiring Problem

Let $X_i = I\{\text{candidate } i \text{ is hired}\}$.

Candidate $i$ is hired iff $i$ is the best among the first $i$ candidates, which happens with probability $1/i$ (each of the first $i$ candidates is equally likely to be best).

$$E[X_i] = \Pr\{\text{candidate } i \text{ is hired}\} = \frac{1}{i}$$

Expected total number of hires:
$$E\left[\sum_{i=1}^n X_i\right] = \sum_{i=1}^n \frac{1}{i} = H_n = \ln n + O(1)$$

where $H_n = \sum_{i=1}^n \frac{1}{i}$ is the $n$-th harmonic number.

**Lemma 5.2:** Assuming candidates arrive in random order: expected hiring cost = $O(c_h \ln n)$.

**Lemma 5.3:** RANDOMIZED-HIRE-ASSISTANT: expected hiring cost = $O(c_h \ln n)$ for **any** input.

Improvement over worst case: $O(c_h n)$ → $O(c_h \ln n)$.

### Time and Space Complexity Analysis

| Algorithm | Time | Space |
|----------|------|-------|
| HIRE-ASSISTANT | $\Theta(n)$ (interviews) + $O(c_h \ln n)$ expected hiring cost | $O(1)$ |
| RANDOMLY-PERMUTE | $\Theta(n)$ | $O(1)$ in-place |
| RANDOMIZED-HIRE-ASSISTANT | $\Theta(n)$ | $O(1)$ |

### The Birthday Paradox (Section 5.4)

How many people must be in a room before two share a birthday? Let $n$ = number of people, $d = 365$ days.

Using indicator variables: Let $X_{ij}$ = indicator that persons $i$ and $j$ share a birthday. Then:
$$E[\text{# pairs sharing birthday}] = \binom{n}{2} \cdot \frac{1}{d} = \frac{n(n-1)}{2d}$$

This exceeds 1 when $n > \sqrt{2d} \approx 27$. A collision occurs with probability roughly $1 - e^{-n^2/(2d)}$; for 50% probability, $n \approx 23$.

**Implication for hashing:** In a hash table of size $m$, after inserting $\Theta(\sqrt{m})$ keys, expect a collision.

### On-line Hiring (Section 5.4.2)

Interview $n$ candidates one-by-one; hire exactly one person (the best observed in the first $k$ candidates, then hire the next better one). The optimal $k = \lfloor n/e \rfloor$. Success probability $\approx 1/e \approx 0.368$.

---

## Key Takeaways & Next Steps

1. **Indicator random variables** + **linearity of expectation** is the most powerful elementary technique for probabilistic analysis in algorithms.
2. **Randomization breaks adversarial inputs**: a randomized algorithm has no worst-case input — the randomness is internal.
3. The **harmonic series** $H_n = \ln n + O(1)$ appears repeatedly in probabilistic analyses (hiring, quicksort average case, hash tables).
4. The distinction between **average-case** (distributional assumption on input) and **expected** (algorithm's random choices) running time is subtle but important.
5. These techniques recur in Chapters 7 (randomized quicksort), 11 (hash tables), and Chapter 33 (machine learning).

---

### Navigation

**Previous:** [[Ch04_Divide_and_Conquer]]
**Next:** [[PartII_Introduction_Sorting_and_Order_Statistics]]
**Hub:** [[Index_Introduction_to_Algorithms]]
