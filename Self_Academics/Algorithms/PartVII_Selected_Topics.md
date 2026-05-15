# Part VII: Selected Topics — Introduction

## Executive Summary

Part VII contains a selection of advanced algorithmic topics that extend earlier material. Ten chapters cover new computation models (parallel algorithms, online algorithms), specialized domains (matrices, polynomials, number theory, string matching, machine learning), and limitations of efficient algorithms (NP-completeness, approximation algorithms).

---

## Zero-Loss Extraction

### Part VII Contents

| Chapter | Topic | Key Result |
|---------|-------|-----------|
| Ch26 | Parallel Algorithms | Fork-join parallelism; work and span; parallel matrix multiply and merge sort |
| Ch27 | Online Algorithms | Competitive analysis; move-to-front heuristic; online caching |
| Ch28 | Matrix Operations | LU/LUP decomposition; Gaussian elimination $O(n^3)$; least-squares |
| Ch29 | Linear Programming | Simplex method; duality; max-flow as LP |
| Ch30 | Polynomials and FFT | DFT; FFT $O(n\log_2 n)$; polynomial multiplication |
| Ch31 | Number-Theoretic Algorithms | GCD; modular arithmetic; RSA; Miller-Rabin primality |
| Ch32 | String Matching | Rabin-Karp; KMP; finite automata; suffix arrays |
| Ch33 | Machine Learning Algorithms | $k$-means clustering; multiplicative weights; gradient descent |
| Ch34 | NP-Completeness | P vs NP; polynomial reductions; NP-complete problems |
| Ch35 | Approximation Algorithms | Vertex cover; TSP; set cover; subset sum approximations |

---

## Deep-Dive Explanations

### Overview of Advanced Topics

**Parallel algorithms (Ch26):** Fork-join model with two complexity measures — **work** $T_1$ (total operations) and **span** $T_\infty$ (critical-path length). **Parallelism** $= T_1 / T_\infty$. Parallel matrix multiplication and merge sort illustrate the model.

**Online algorithms (Ch27):** No advance knowledge of future input. **Competitive ratio** measures performance relative to the optimal offline algorithm (that knows all inputs). Move-to-front for list maintenance and online caching achieve constant competitive ratios.

**NP-completeness (Ch34):** Class P (decidable in polynomial time); class NP (verifiable in polynomial time); NP-hard (at least as hard as any NP problem); NP-complete = NP ∩ NP-hard. If any NP-complete problem is in P, then P = NP. Classic NP-complete problems: SAT (Cook-Levin theorem), 3-CNF-SAT, CLIQUE, VERTEX-COVER, HAMILTONIAN-CYCLE, TSP, SUBSET-SUM.

**Approximation algorithms (Ch35):** For NP-complete optimization problems, find approximate solutions with guaranteed quality. The **approximation ratio** $\rho(n)$ bounds how far from optimal: $\max(C/C^*, C^*/C) \leq \rho(n)$. APPROX-VERTEX-COVER gives a 2-approximation; greedy set cover gives $H(d)$-approximation where $H(d) = O(\log n)$.

---

## Key Takeaways & Next Steps

1. Part VII covers advanced specialized topics; each chapter is largely self-contained.
2. NP-completeness (Ch34) and approximation (Ch35) are foundational for understanding the limits of efficient computation.
3. FFT (Ch30) and RSA (Ch31) have direct practical applications in signal processing and cryptography.
4. The parallel model (Ch26) is increasingly important with modern multi-core hardware.

---

### Navigation

**Previous:** [[Ch25_Bipartite_Matching]]
**Next:** [[Ch26_Parallel_Algorithms]]
**Hub:** [[Index_Introduction_to_Algorithms]]
