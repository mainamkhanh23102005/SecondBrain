# Chapter 5: Probabilistic Analysis and Randomized Algorithms

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #probability #randomized-algorithms #expected-value

## Overview

This chapter introduces **probabilistic analysis** — computing expected behavior by averaging over input distributions — and **randomized algorithms** — algorithms that make random choices to achieve good expected performance for any input. The hiring problem serves as the central motivating example.

---

## 5.1 The Hiring Problem

**Setting:** Interview $n$ candidates one-by-one. Always keep the best seen so far. Interviewing costs $c_i$; hiring (firing old, paying agency) costs $c_h \gg c_i$.

```
HIRE-ASSISTANT(n)
1  best = 0       // candidate 0 is a dummy least-qualified candidate
2  for i = 1 to n
3      interview candidate i
4      if candidate i is better than candidate best
5          best = i
6          hire candidate i
```

**Total cost:** $O(c_i n + c_h m)$ where $m$ = number hired.

- Worst case: candidates arrive in increasing order → hire all $n$ → $O(c_h n)$
- Average case requires probabilistic analysis

**Key distinction:**
- **Probabilistic analysis:** assumes inputs come from a distribution; computes *average-case* running time
- **Randomized algorithm:** algorithm itself makes random choices; guarantees good *expected* running time for any input

---

## 5.2 Indicator Random Variables

**Definition:** For sample space $S$ and event $A$:
$$I\{A\} = \begin{cases} 1 & \text{if } A \text{ occurs} \\ 0 & \text{if } A \text{ does not occur} \end{cases}$$

**Lemma 5.1:** $E[I\{A\}] = \Pr\{A\}$

**Power:** Combined with **linearity of expectation**, indicator random variables decompose complex counting problems into sums of simple probabilities — even when random variables are dependent.

$$E\left[\sum_i X_i\right] = \sum_i E[X_i]$$

### Analysis of Hiring Problem

Assume candidates arrive in uniformly random order.

Let $X_i = I\{\text{candidate } i \text{ is hired}\}$

Candidate $i$ is hired $\iff$ candidate $i$ is the best among the first $i$ candidates $\iff$ probability $1/i$.

$$E[X] = \sum_{i=1}^{n} E[X_i] = \sum_{i=1}^{n} \frac{1}{i} = H_n \approx \ln n$$

**Lemma 5.2:** Average-case total hiring cost is $O(c_h \ln n)$ — much better than worst-case $O(c_h n)$.

**Classic applications of indicator variables:**
- Expected inversions in a random permutation: $\binom{n}{2}/2$
- Hat-check problem: expected number of customers who get own hat = 1 (regardless of $n$!)

---

## 5.3 Randomized Algorithms

**Key idea:** Instead of hoping inputs come in random order, the algorithm enforces a random order itself.

### RANDOMIZED-HIRE-ASSISTANT

```
RANDOMIZED-HIRE-ASSISTANT(n)
1  randomly permute the list of candidates
2  HIRE-ASSISTANT(n)
```

**Lemma 5.3:** Expected hiring cost is $O(c_h \ln n)$ — for **any** input, not just random inputs.

**Difference from probabilistic analysis:**
- Probabilistic analysis: statement holds on average over random inputs
- Randomized algorithm: statement holds in expectation over algorithm's random choices

### RANDOMLY-PERMUTE — Uniform Random Permutation

```
RANDOMLY-PERMUTE(A, n)
1  for i = 1 to n
2      swap A[i] with A[RANDOM(i, n)]
```

**Lemma 5.4:** `RANDOMLY-PERMUTE` produces a uniform random permutation (every permutation equally likely, with probability $1/n!$).

**Proof sketch:** Loop invariant — before iteration $i$, every $(i-1)$-permutation of $n$ elements appears in $A[1:i-1]$ with probability $(n-i+1)!/n!$.

**Correctness of `PERMUTE-WITH-ALL` (swap with any position):** Does NOT produce a uniform permutation — only $n^n$ vs $n!$ possible sequences.

---

## 5.4 Further Probabilistic Analysis (Selected)

### Birthday Paradox

In a room of $k$ people, the probability that two share a birthday exceeds $\tfrac{1}{2}$ when $k \geq 23$ (with 365 days in a year).

Using indicator variables: let $X_{ij} = I\{\text{persons } i \text{ and } j \text{ share a birthday}\}$.

$$E[X] = \binom{k}{2} \cdot \frac{1}{365} \geq 1 \implies k \approx \sqrt{2 \cdot 365} \approx 27$$

### Balls into Bins

Toss $n$ balls independently into $n$ bins, each equally likely. Expected number of balls in any given bin = 1. The maximum load (balls in the fullest bin) is $\Theta(\log_2 n / \log_2 \log_2 n)$ with high probability.

### Streaks of Coin Flips

In $n$ flips of a fair coin, the expected length of the longest streak of heads is $\Theta(\log_2 n)$.

---

## Key Concepts Summary

| Concept | Definition |
|---|---|
| Indicator random variable | $I\{A\} \in \{0,1\}$; $E[I\{A\}] = \Pr\{A\}$ |
| Linearity of expectation | $E[\sum X_i] = \sum E[X_i]$ — works even with dependence |
| Average-case running time | Expected over distribution of inputs |
| Expected running time | Expected over algorithm's random choices |
| Uniform random permutation | Each of $n!$ permutations equally likely |

---

### Navigation
**Previous:** [[Ch4_Divide_and_Conquer]]
**Next:** [[Part2_Introduction_Sorting]]
**Hub:** [[Index_Introduction_to_Algorithms]]
