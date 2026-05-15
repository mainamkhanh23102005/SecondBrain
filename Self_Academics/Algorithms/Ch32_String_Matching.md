# Chapter 32 — String Matching

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #string-matching #KMP #Rabin-Karp #automata

---

## Executive Summary

String matching finds all occurrences of a *pattern* $P[1..m]$ in a *text* $T[1..n]$. The chapter develops four algorithms of increasing sophistication, all exploiting *preprocessing* to avoid redundant character comparisons:

| Algorithm | Preprocessing | Matching | Total |
|-----------|-------------|---------|-------|
| Naive | 0 | $O((n-m+1)m)$ | $O((n-m+1)m)$ |
| Rabin-Karp | $\Theta(m)$ | $O((n-m+1)m)$ worst / $O(n+m)$ expected | $O(n+m)$ expected |
| Finite Automaton | $O(m^3 |\Sigma|)$ | $\Theta(n)$ | $O(m^3|\Sigma|+n)$ |
| KMP | $\Theta(m)$ | $\Theta(n)$ | $\Theta(n+m)$ |

A fifth approach — **suffix arrays** — achieves $O(n \log_2 n)$ preprocessing and $O(m \log_2 n + k m)$ matching for $k$ occurrences.

**Core vocabulary:**
- Valid shift $s$: $P$ occurs at position $s+1$ in $T$ ($T[s+1..s+m] = P[1..m]$).
- $\Sigma$: finite alphabet. $|\Sigma|$ matters for FA preprocessing.

---

## Zero-Loss Extraction

### §32.1 — Naive String Matcher

```
NAIVE-STRING-MATCHER(T, P)
1  n = T.length
2  m = P.length
3  for s = 0 to n − m
4      if P[1..m] == T[s+1..s+m]
5          print "Pattern occurs with shift" s
```

- **Running time:** $O((n-m+1)m)$ — worst case on "aaaa…a" pattern against "aaaa…ab" text.
- No preprocessing; each potential shift is checked from scratch.

---

### §32.2 — Rabin-Karp Algorithm

**Key idea:** Hash each length-$m$ window of $T$ and compare with $h(P)$; only do character-by-character check on *hash matches* (spurious hits are rare).

**Rolling hash:** Treat characters as digits in base $d = |\Sigma|$:
$$t_s = T[s+1] \cdot d^{m-1} + T[s+2] \cdot d^{m-2} + \cdots + T[s+m]$$

Compute $t_{s+1}$ from $t_s$ in $O(1)$:
$$t_{s+1} = \bigl(d \cdot (t_s - T[s+1] \cdot h) + T[s+m+1]\bigr) \bmod q$$

where $h = d^{m-1} \bmod q$ and $q$ is a suitable prime.

```
RABIN-KARP-MATCHER(T, P, d, q)
1  n = T.length;  m = P.length
2  h = d^(m-1) mod q
3  p = 0;  t₀ = 0
4  for i = 1 to m           // preprocessing
5      p = (d·p + P[i]) mod q
6      t₀ = (d·t₀ + T[i]) mod q
7  for s = 0 to n − m       // matching
8      if p == tₛ
9          if P[1..m] == T[s+1..s+m]
10             print "Pattern occurs with shift" s
11     if s < n − m
12         tₛ₊₁ = (d(tₛ − T[s+1]·h) + T[s+m+1]) mod q
```

- **Preprocessing:** $\Theta(m)$.
- **Matching:** $O((n-m+1)m)$ worst case (all hashes match). Expected $O(n+m)$ when spurious hits are rare ($O(1)$ expected per window, since probability of a spurious hit $\approx 1/q$).

---

### §32.3 — String Matching with Finite Automata

**Suffix function $\sigma$:** For string $x$, $\sigma(x) =$ length of the longest prefix of $P$ that is also a suffix of $x$.

**Transition function $\delta$:** 
$$\delta(q, a) = \sigma(P[1..q]\, a)$$

The FA maintains state $q$ = length of the longest prefix of $P$ matched so far. State $m$ is the accepting state.

```
FINITE-AUTOMATON-MATCHER(T, δ, m)
1  n = T.length
2  q = 0
3  for i = 1 to n
4      q = δ(q, T[i])
5      if q == m
6          print "Pattern occurs with shift" i − m
```

**Matching time:** $\Theta(n)$.

```
COMPUTE-TRANSITION-FUNCTION(P, Σ)
1  m = P.length
2  for q = 0 to m
3      for each a ∈ Σ
4          k = min(m+1, q+2)
5          repeat k = k − 1
6          until P[1..k] ⊐ P[1..q]a
7          δ(q, a) = k
8  return δ
```

**Preprocessing time:** $O(m^3 |\Sigma|)$ (inner loop repeats at most $m+1$ times; suffix check is $O(m)$).

**Key lemma (Lemma 32.4):** $\sigma(xa) = \sigma(P[1..\sigma(x)]\, a)$ — the suffix function depends only on the current state, not the full history.

---

### §32.4 — Knuth-Morris-Pratt (KMP) Algorithm

**Prefix function $\pi$:** Encodes the degeneracy of the pattern.
$$\pi[q] = \max\{k : k < q \text{ and } P[1..k] \sqsupset P[1..q]\}$$

(Longest proper prefix of $P[1..q]$ that is also a suffix.)

```
COMPUTE-PREFIX-FUNCTION(P)
1  m = P.length
2  π = new array[1..m]
3  π[1] = 0
4  k = 0
5  for q = 2 to m
6      while k > 0 and P[k+1] ≠ P[q]
7          k = π[k]
8      if P[k+1] == P[q]
9          k = k + 1
10     π[q] = k
11 return π
```

**Running time:** $\Theta(m)$ — amortized: $k$ can increase at most $m$ times total (once per iteration), and each `while` iteration decreases $k$, so the total number of decreases is $\le m$.

```
KMP-MATCHER(T, P)
1  n = T.length;  m = P.length
2  π = COMPUTE-PREFIX-FUNCTION(P)
3  q = 0
4  for i = 1 to n
5      while q > 0 and P[q+1] ≠ T[i]
6          q = π[q]
7      if P[q+1] == T[i]
8          q = q + 1
9      if q == m
10         print "Pattern occurs with shift" i − m
11         q = π[q]
```

**Matching time:** $\Theta(n)$ — same amortized argument: $q$ increases at most $n$ times, decreases are bounded by total increases.

**Key lemmas:**
- **Lemma 32.5 (Iteration lemma):** $\pi^*[q] = \{k : k < q \text{ and } P[1..k] \sqsupset P[1..q]\}$ (the set of all valid prefix-suffix lengths).
- **Lemma 32.6:** For $q \ge 2$: $\pi[q-1] \in \pi^*[q-1]$, characterizing the second-longest proper prefix-suffix.
- **Corollary 32.7:** $\pi[q] > 0 \Rightarrow \pi[\pi[q]] \le \pi[q]-1$ (used to bound the while loop).

---

### §32.5 — Suffix Arrays

**Definition:** The *suffix array* $SA$ of text $T$ is an array of indices into $T$ sorted by the lexicographic order of the corresponding suffixes.

- **Construction:** $O(n \log_2 n)$ using doubling; $O(n)$ with more sophisticated methods.
- **Search:** For pattern $P$ of length $m$, binary search on $SA$ in $O(m \log_2 n)$; once the range is found, each of $k$ occurrences is reported in $O(m)$ (or $O(1)$ with LCP arrays): total $O(m \log_2 n + km)$.

Suffix arrays are often preferred in practice over suffix trees due to lower memory constants, while achieving the same asymptotic bounds.

---

## Deep-Dive Explanations

### Why KMP Runs in $\Theta(n+m)$

The crucial observation is that $q$ (the match length) is bounded between 0 and $m$. Over the entire matching phase:
- Each iteration of the outer `for` loop either increases $q$ by 1 (when $P[q+1] = T[i]$) or leaves it unchanged.
- The `while` loop decreases $q$ each iteration but can only run as many times as $q$ has been increased.
- Total increases over $n$ iterations $\le n$, so total `while` iterations $\le n$.

Combined: $O(n)$ for matching, $O(m)$ for preprocessing → $\Theta(n+m)$.

### Suffix Function vs. Prefix Function: Two Views of the Same Idea

The FA and KMP algorithms solve the same problem via different representations:

| Concept | FA Approach | KMP Approach |
|---------|------------|-------------|
| State | $q$ = longest matched prefix length | $q$ = same |
| "Fallback" on mismatch | $\delta(q, a) = \sigma(P[1..q]a)$ | $\pi[q]$ (then retry) |
| Preprocessing cost | $O(m^3|\Sigma|)$ | $\Theta(m)$ |
| Matching cost | $\Theta(n)$ | $\Theta(n)$ |

KMP avoids storing the full $\delta$ table by lazily computing fallbacks via $\pi$, reducing space and preprocessing time.

### Rabin-Karp: When Hashing Shines

Rabin-Karp is particularly useful for **multi-pattern search**: precompute hashes of $k$ patterns in $O(km)$, then scan the text once, checking each window hash against all $k$ pattern hashes in $O(k)$ per step — $O(n \cdot k + km)$ total, vs. $O(nkm)$ for $k$ independent naive searches. For two-dimensional pattern matching, RK extends naturally via row-then-column hashing.

---

## Key Takeaways & Next Steps

| Algorithm | Preprocessing | Matching | Best Use |
|-----------|-------------|---------|---------|
| Naive | — | $O((n-m+1)m)$ | Baseline; simple implementation |
| Rabin-Karp | $\Theta(m)$ | $O(n+m)$ expected | Multi-pattern, 2D matching |
| Finite Automaton | $O(m^3|\Sigma|)$ | $\Theta(n)$ | Fixed $\Sigma$, repeated queries on same $P$ |
| KMP | $\Theta(m)$ | $\Theta(n)$ | General optimal single-pattern search |
| Suffix Array | $O(n\log_2 n)$ | $O(m\log_2 n+km)$ | Many patterns against same text |

**Key invariants:**
- All efficient algorithms use preprocessing to encode pattern self-similarity (prefix-suffix structure).
- KMP's $\pi$ function and the FA's $\delta$ function carry the same information; KMP computes it implicitly.
- Rabin-Karp is the only randomized algorithm here; hash collisions cause spurious hits but not missed matches.

**Next steps:**
- Suffix trees: $O(n)$ construction (Ukkonen's algorithm), $O(m)$ search — theoretically optimal for repeated text queries.
- Aho-Corasick automaton: multi-pattern matching in $O(n + m_{\text{total}} + k)$.
- Chapter 33 applies ML methods to clustering and online learning — a completely different paradigm.

---

### Navigation

**Previous:** [[Ch31_Number_Theoretic_Algorithms]]  
**Next:** [[Ch33_Machine_Learning_Algorithms]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
