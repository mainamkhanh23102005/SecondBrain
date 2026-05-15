# Appendix A — Summations

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #mathematics #summations #series

---

## Executive Summary

Appendix A compiles the summation techniques used throughout CLRS algorithm analyses. Running times of iterative algorithms reduce to sums; recurrence solutions involve series. Two sections build the toolkit: **A.1** gives closed-form formulas for standard series; **A.2** gives bounding techniques when closed forms are unavailable. Mastery of these formulas eliminates the need to re-derive results and directly enables reading every later-chapter proof.

| Formula Family | Representative Result | Appears In |
|---------------|----------------------|-----------|
| Arithmetic | $\sum_{k=1}^n k = \frac{n(n+1)}{2} = \Theta(n^2)$ | Insertion sort analysis (Ch. 2) |
| Geometric | $\sum_{k=0}^n x^k = \frac{x^{n+1}-1}{x-1}$ | Merge sort, tree analysis |
| Harmonic | $H_n = \sum_{k=1}^n \frac{1}{k} = \ln n + O(1)$ | Quicksort, hash tables (Ch. 11) |
| Telescoping | $\sum_{k=1}^n (a_k - a_{k-1}) = a_n - a_0$ | Amortized analysis (Ch. 16) |
| Geometric (diff.) | $\sum_{k=0}^\infty kx^k = \frac{x}{(1-x)^2}$ | Expected depth calculations |

---

## Zero-Loss Extraction

### §A.1 — Summation Formulas and Properties

**Notation.** The finite sum $a_1 + a_2 + \cdots + a_n$ is written $\sum_{k=1}^n a_k$; the value is 0 when $n = 0$. An infinite sum $\sum_{k=1}^\infty a_k$ converges if the limit of partial sums exists; otherwise it diverges. An *absolutely convergent* series $\sum |a_k| < \infty$ may be rearranged freely.

---

#### Linearity

For any real constant $c$ and sequences $\{a_k\}$, $\{b_k\}$:
$$\sum_{k=1}^n (c\,a_k + b_k) = c\sum_{k=1}^n a_k + \sum_{k=1}^n b_k$$

Linearity extends to asymptotic notation inside summations:
$$\sum_{k=1}^n \Theta(f(k)) = \Theta\!\left(\sum_{k=1}^n f(k)\right)$$

---

#### Arithmetic Series

$$\sum_{k=1}^n k = \frac{n(n+1)}{2} = \Theta(n^2)$$

**General arithmetic series** (constants $a \ge 0$, $b > 0$):
$$\sum_{k=1}^n (a + bk) = an + b\cdot\frac{n(n+1)}{2} = \Theta(n^2)$$

---

#### Sums of Squares and Cubes

$$\sum_{k=0}^n k^2 = \frac{n(n+1)(2n+1)}{6}$$

$$\sum_{k=0}^n k^3 = \left(\frac{n(n+1)}{2}\right)^2$$

---

#### Geometric Series

For real $x \ne 1$:
$$\sum_{k=0}^n x^k = \frac{x^{n+1} - 1}{x - 1}$$

**Infinite decreasing geometric series** ($|x| < 1$):
$$\sum_{k=0}^\infty x^k = \frac{1}{1 - x}$$

(Convention: $0^0 = 1$, so the formula holds even when $x = 0$.)

---

#### Harmonic Series

The $n$-th harmonic number:
$$H_n = \sum_{k=1}^n \frac{1}{k} = \ln n + O(1)$$

Tighter bounds (equations A.20–A.21 in CLRS):
$$\ln(n+1) \le H_n \le \ln n + 1$$

*Note:* $\ln$ denotes the natural logarithm; the $O(1)$ term is Euler's constant $\gamma \approx 0.5772$.

---

#### Integrating and Differentiating Series

Differentiating the infinite geometric series $\sum_{k=0}^\infty x^k = \frac{1}{1-x}$ with respect to $x$ and multiplying by $x$:
$$\sum_{k=0}^\infty kx^k = \frac{x}{(1-x)^2} \qquad (|x| < 1)$$

This identity appears whenever computing expected values of geometrically distributed quantities (e.g., expected number of probes in hashing).

---

#### Telescoping Series

For any sequence $a_0, a_1, \ldots, a_n$:
$$\sum_{k=1}^n (a_k - a_{k-1}) = a_n - a_0$$

Because each interior term $a_1, a_2, \ldots, a_{n-1}$ is added once and subtracted once. Equivalently:
$$\sum_{k=0}^{n-1}(a_k - a_{k+1}) = a_0 - a_n$$

**Example.** Recognising the partial-fraction telescoping structure:
$$\sum_{k=1}^{n-1} \frac{1}{k(k+1)} = \sum_{k=1}^{n-1}\!\left(\frac{1}{k} - \frac{1}{k+1}\right) = 1 - \frac{1}{n}$$

---

#### Reindexing Summations

Reversing the order of a summation (substituting $j = n - k$):
$$\sum_{k=0}^n a_{n-k} = \sum_{j=0}^n a_j$$

**General rule:** when the summation index appears in the body with a *minus sign*, try reindexing. Example — recognising a hidden harmonic series:
$$\sum_{k=1}^n \frac{1}{n - k + 1} \;\overset{j = n-k+1}{=}\; \sum_{j=1}^n \frac{1}{j} = H_n$$

---

#### Products

The finite product $a_1 a_2 \cdots a_n$ is written $\prod_{k=1}^n a_k$ (empty product = 1). Convert to a summation via logarithms:
$$\log\!\prod_{k=1}^n a_k = \sum_{k=1}^n \log a_k$$

---

### §A.2 — Bounding Summations

When no closed form exists, four techniques bound summations arising in algorithm analyses.

---

#### Technique 1 — Mathematical Induction

**Proving exact values.** Show $\sum_{k=1}^n k = n(n+1)/2$: base $n=1$ gives $1=1$ ✓; inductive step:
$$\sum_{k=1}^{n+1} k = \frac{n(n+1)}{2} + (n+1) = \frac{(n+1)(n+2)}{2} \checkmark$$

**Proving asymptotic bounds.** To show $\sum_{k=0}^n k^3 = O(n^4)$, prove $\sum_{k=0}^n k^3 \le cn^4$ for some constant $c \ge 3/2$ by induction.

**Critical pitfall.** Do *not* carry a big-$O$ with a growing hidden constant through induction. The argument "$\sum_{k=1}^n k = O(n^2)$, therefore $\sum_{k=1}^{n+1} k = O(n^2) + (n+1) = O(n^2)$" is fallacious: the constant absorbing $n+1$ must grow with $n$, so it is never truly constant.

---

#### Technique 2 — Bounding the Terms

**Max-term domination:**
$$\sum_{k=1}^n a_k \le n \cdot a_{\max}, \quad a_{\max} = \max_{1 \le k \le n} a_k$$

**Geometric ratio test:** If $a_{k+1}/a_k \le r$ for all $k \ge 0$ where $r < 1$ is a *constant*, then:
$$\sum_{k=0}^\infty a_k \le \frac{a_0}{1 - r}$$

**Pitfall.** The harmonic series $\sum 1/k$ has ratio $k/(k+1) < 1$, yet it diverges. The test requires a *fixed* constant $r$; here no such $r < 1$ works because the ratio approaches 1.

---

#### Technique 3 — Splitting Summations

Partition the index range into tractable pieces.

**Arithmetic series lower bound** (even $n$):
$$\sum_{k=1}^n k \ge \sum_{k=\lceil n/2 \rceil}^n k \ge \frac{n}{2} \cdot \frac{n}{2} = \frac{n^2}{4} = \Omega(n^2)$$

**Dropping initial constant terms.** When $a_k$ is independent of $n$, any fixed prefix contributes a constant so asymptotically it can be ignored:
$$\sum_{k=k_0}^n a_k = \Theta\!\left(\sum_{k=k_0+c}^n a_k\right) \text{ for any constant } c$$

**Harmonic series $O(\log_2 n)$ via splitting.** Divide $[1,n]$ into $\lfloor \log_2 n \rfloor + 1$ pieces where piece $i$ covers $[2^i, 2^{i+1})$. Each piece sums to at most 1:
$$H_n \le \sum_{i=0}^{\lfloor \log_2 n \rfloor} \underbrace{\sum_{k=2^i}^{\min(2^{i+1}-1,\,n)} \frac{1}{k}}_{\le 1} \le \lfloor \log_2 n \rfloor + 1 = O(\log_2 n)$$

---

#### Technique 4 — Approximation by Integrals

For **monotonically increasing** $f$, rectangles lie below the curve on the left:
$$\int_{m-1}^{n} f(x)\,dx \;\le\; \sum_{k=m}^{n} f(k) \;\le\; \int_{m}^{n+1} f(x)\,dx$$

For **monotonically decreasing** $f$ the inequalities reverse.

**Application — tight harmonic bounds.** Since $1/x$ is monotone decreasing:

*Lower bound:*
$$H_n = \sum_{k=1}^n \frac{1}{k} \ge \int_1^{n+1} \frac{1}{x}\,dx = \ln(n+1)$$

*Upper bound:*
$$H_n = \sum_{k=1}^n \frac{1}{k} \le 1 + \int_1^n \frac{1}{x}\,dx = 1 + \ln n$$

Together these prove the tight bounds (A.20)–(A.21): $\;\ln(n+1) \le H_n \le 1 + \ln n$.

---

## Deep-Dive Explanations

### Why Geometric Series Appear Everywhere in Algorithms

Divide-and-conquer algorithms create subproblem trees where the work at depth $d$ is $a^d \cdot T(n/b^d)$. When $a < b^c$ (for problem of size $n^c$), the total work is dominated by the root; when $a > b^c$, it is dominated by leaves. Formally, both cases reduce to bounding $\sum_{d=0}^{\log_2 n} r^d$ for ratio $r = a/b^c$, which is a geometric series. This is exactly the core of the Master Theorem derivation (Ch. 4).

### Harmonic Series and Quicksort

The expected number of comparisons in randomized quicksort is $2n H_n \approx 2n \ln n$, the harmonic-series estimate. The sum arises because element ranked $k$ is compared to a random pivot: summing $2/(k+1)$ over all elements gives the harmonic series. The $\Theta(n \log n)$ bound on quicksort's expected cost is inseparable from $H_n = \Theta(\log n)$.

### Telescoping as a Proof Technique

The amortized analysis in Chapter 16 often defines a *potential function* $\Phi$ and bounds the total actual cost as the sum of amortized costs plus the net change in potential: $\sum \text{actual} = \sum \text{amortized} - (\Phi_n - \Phi_0)$. This is exactly a telescoping sum — the intermediate potentials cancel. Recognising the telescoping structure turns a difficult multi-step bound into a one-line calculation.

---

## Key Takeaways & Next Steps

| Formula | Closed Form | $\Theta$-Bound | Typical Context |
|---------|-------------|----------------|----------------|
| $\sum_{k=1}^n k$ | $\frac{n(n+1)}{2}$ | $\Theta(n^2)$ | Insertion sort worst case |
| $\sum_{k=0}^n x^k$ ($x>1$) | $\frac{x^{n+1}-1}{x-1}$ | $\Theta(x^n)$ | Geometric branching |
| $\sum_{k=0}^\infty x^k$ ($|x|<1$) | $\frac{1}{1-x}$ | $\Theta(1)$ | Convergent subproblems |
| $\sum_{k=1}^n 1/k$ | $H_n$ | $\Theta(\log n)$ | Quicksort, hashing |
| $\sum_{k=0}^\infty kx^k$ ($|x|<1$) | $\frac{x}{(1-x)^2}$ | $\Theta(1)$ | Expected geometric r.v. |

**Key principles:**
1. **Linearity first:** simplify by separating constants and sums before applying any formula.
2. **Recognise the family:** arithmetic ($k$), geometric ($x^k$), harmonic ($1/k$), or can it telescope?
3. **Reindex when the index appears with a minus sign:** a hidden simpler sum often lurks beneath.
4. **Section A.2** (bounding techniques) is needed when no closed form exists — crucial for analysis of algorithms with non-standard recurrences.

---

### Navigation

**Previous:** [[AppIntro_Mathematical_Background]]  
**Next:** [[AppB_Sets_Etc]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
