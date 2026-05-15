# Appendix C — Counting and Probability

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #mathematics #counting #probability #combinatorics #random-variables

---

## Executive Summary

Appendix C is the combinatorics and probability toolkit for algorithm analysis. Nearly every randomized algorithm (quicksort, hashing, skip lists, randomized data structures) requires at least §C.2–C.3; probabilistic analyses of deterministic algorithms (e.g., birthday paradox, balls-into-bins) rely on §C.1. Four sections (plus §C.5 Tails in the next batch — file 1525) build the toolkit:

| Section | Topic | Key Results |
|---------|-------|------------|
| C.1 | Counting | $n!$ permutations, $\binom{n}{k}$ combinations, binomial theorem, entropy bound |
| C.2 | Probability | Axioms, conditional probability, independence, Bayes's theorem |
| C.3 | Random Variables | Expectation, linearity, Jensen's inequality, variance |
| C.4 | Geo & Binomial | Geometric $E[X]=1/p$, Binomial $E[X]=np$, $\text{Var}[X]=npq$ |
| C.5 | Tails | *(next batch — file 1525)* |

---

## Zero-Loss Extraction

### §C.1 — Counting

#### Rules of Sum and Product

**Rule of sum:** $|A \cup B| = |A| + |B|$ when $A \cap B = \emptyset$ (disjoint union).  
**Rule of product:** $|A \times B| = |A| \cdot |B|$ (ordered pairs from independent choices).

#### Strings

A **$k$-string** over an $n$-set $S$ is a sequence of $k$ elements (with repetition); there are $n^k$ such strings ($= |S^k|$). A **$k$-substring** of a string $s$ is a contiguous subsequence of length $k$.

#### Permutations

A **permutation** of an $n$-set is an ordered sequence of all $n$ elements; there are $n!$ permutations.

A **$k$-permutation** of an $n$-set is an ordered sequence of $k$ distinct elements:

$$P(n,k) = \frac{n!}{(n-k)!} = n(n-1)\cdots(n-k+1) \tag{C.1}$$

#### Combinations

A **$k$-combination** of an $n$-set is an unordered $k$-element subset. The count:

$$\binom{n}{k} = \frac{n!}{k!\,(n-k)!} = \frac{P(n,k)}{k!} \tag{C.2}$$

Symmetry: $\binom{n}{k} = \binom{n}{n-k}$.

#### Binomial Coefficients and Theorem

$$\binom{n}{k} \text{ (read "$n$ choose $k$")} \quad \Rightarrow \quad (x+y)^n = \sum_{k=0}^{n}\binom{n}{k}x^k y^{n-k} \tag{C.4}$$

Special case ($x=y=1$): $2^n = \sum_{k=0}^{n}\binom{n}{k}$ — counts all binary $n$-strings by number of 1s.

#### Binomial Bounds

For $1 \le k \le n$:

$$\left(\frac{n}{k}\right)^k \le \binom{n}{k} \le \frac{n^k}{k!} \le \left(\frac{en}{k}\right)^k \tag{C.5–C.6}$$

For $0 \le k \le n$, using the **binary entropy function** $H(\lambda) = -\lambda \log_2 \lambda - (1-\lambda)\log_2(1-\lambda)$:

$$\binom{n}{k} \le 2^{n H(k/n)} \tag{C.7}$$

where $H(0) = H(1) = 0$ (by convention $0 \log_2 0 = 0$), and $H(1/2) = 1$.

---

### §C.2 — Probability

#### Probability Space

- **Sample space $S$:** set of all outcomes (elementary events).
- **Event $A$:** a subset $A \subseteq S$.
- **Probability distribution $\Pr\{\cdot\}$:** mapping from events to $[0,1]$.

**Axioms:**
1. $\Pr\{A\} \ge 0$ for all $A$.
2. $\Pr\{S\} = 1$.
3. $\Pr\{A \cup B\} = \Pr\{A\} + \Pr\{B\}$ when $A \cap B = \emptyset$ (countably additive).

Consequences: $\Pr\{\emptyset\} = 0$; $\Pr\{\bar{A}\} = 1 - \Pr\{A\}$; $A \subseteq B \Rightarrow \Pr\{A\} \le \Pr\{B\}$.

**Union bound (Boole's inequality):** $\Pr\{A \cup B\} \le \Pr\{A\} + \Pr\{B\}$ for any events.

#### Discrete and Uniform Distributions

**Discrete:** $S$ finite or countably infinite; $\Pr\{A\} = \sum_{s \in A}\Pr\{s\}$.  
**Uniform:** $\Pr\{s\} = 1/|S|$ for all $s$; then $\Pr\{A\} = |A|/|S|$ — reduces probability to counting.

**Continuous uniform distribution** on $[a,b]$: $\Pr\{[c,d]\} = (d-c)/(b-a)$; single points have probability 0.

#### Conditional Probability

$$\Pr\{A \mid B\} = \frac{\Pr\{A \cap B\}}{\Pr\{B\}}, \quad \Pr\{B\} \ne 0 \tag{C.16}$$

#### Independence

Events $A$ and $B$ are **independent** if $\Pr\{A \cap B\} = \Pr\{A\}\Pr\{B\}$, equivalently $\Pr\{A \mid B\} = \Pr\{A\}$.

A collection $A_1, \ldots, A_n$ is **pairwise independent** if $\Pr\{A_i \cap A_j\} = \Pr\{A_i\}\Pr\{A_j\}$ for all $i < j$.  
It is **(mutually) independent** if every subset satisfies the product rule — a strictly stronger condition.

#### Bayes's Theorem

$$\Pr\{A \mid B\} = \frac{\Pr\{A\}\,\Pr\{B \mid A\}}{\Pr\{B\}} \tag{C.19}$$

Expanded denominator: $\Pr\{B\} = \Pr\{A\}\Pr\{B \mid A\} + \Pr\{\bar{A}\}\Pr\{B \mid \bar{A}\}$ (law of total probability).

---

### §C.3 — Discrete Random Variables

A **discrete random variable** $X$ is a function $X : S \to \mathbb{R}$ from a countable sample space.  
**Probability density function (pdf):** $f(x) = \Pr\{X = x\}$; satisfies $\sum_x f(x) = 1$.  
**Joint pdf of $X, Y$:** $f(x,y) = \Pr\{X=x \text{ and } Y=y\}$; summing over one variable gives the marginal.  
**Independence of $X, Y$:** $\Pr\{X=x \text{ and } Y=y\} = \Pr\{X=x\}\Pr\{Y=y\}$ for all $x, y$.

#### Expected Value

$$E[X] = \sum_x x \cdot \Pr\{X = x\} \tag{C.9}$$

(well-defined if the sum converges absolutely).

**Linearity of expectation** (holds even without independence):

$$E[X + Y] = E[X] + E[Y], \qquad E[aX] = a\,E[X] \tag{C.24–C.25}$$

**For natural-valued $X \ge 0$:**

$$E[X] = \sum_{i=1}^{\infty} \Pr\{X \ge i\} \tag{C.28}$$

**Jensen's inequality:** If $f$ is convex, $E[f(X)] \ge f(E[X])$.

**Independence and expectation:** $X \perp Y \Rightarrow E[XY] = E[X]\,E[Y]$.

#### Variance and Standard Deviation

$$\text{Var}[X] = E\!\left[(X - E[X])^2\right] = E[X^2] - E^2[X] \tag{C.31}$$

$$\text{Var}[aX] = a^2\,\text{Var}[X]$$

**Pairwise independence:** $\text{Var}[X_1 + \cdots + X_n] = \sum_{i=1}^n \text{Var}[X_i]$.  
**Markov's inequality:** $\Pr\{X \ge t\} \le E[X]/t$ for $X \ge 0$, $t > 0$.  
**Standard deviation:** $\sigma_X = \sqrt{\text{Var}[X]}$.

---

### §C.4 — Geometric and Binomial Distributions

#### Bernoulli Trials

A **Bernoulli trial** has two outcomes: success with probability $p$, failure with $q = 1-p$. Trials are mutually independent with the same $p$.

#### Geometric Distribution

Let $X$ = number of trials until the first success. For $k \ge 1$:

$$\Pr\{X = k\} = q^{k-1}p \tag{C.35}$$

$$E[X] = \frac{1}{p}, \qquad \text{Var}[X] = \frac{q}{p^2} \tag{C.36–C.37}$$

Intuition: on average $1/p$ trials are needed before a success.

#### Binomial Distribution

Let $X$ = number of successes in $n$ Bernoulli trials. For $k = 0, 1, \ldots, n$:

$$b(k;\, n,\, p) = \binom{n}{k} p^k q^{n-k} \tag{C.38}$$

Note $\sum_{k=0}^n b(k;n,p) = (p+q)^n = 1$ (from binomial theorem).

$$E[X] = np, \qquad \text{Var}[X] = npq \tag{C.40–C.41}$$

**Mode:** $b(k;n,p) > b(k-1;n,p)$ iff $k < (n+1)p$; distribution increases up to the mode then decreases.

**Lemma C.1 (upper bound):** For $0 < p < 1$, $q = 1-p$, $0 \le k \le n$:

$$b(k;\, n,\, p) \le \left(\frac{np}{k}\right)^k \left(\frac{nq}{n-k}\right)^{n-k} \frac{1}{\sqrt{2\pi k(1-k/n)/n}}$$

---

## Deep-Dive Explanations

### Counting as the Bridge Between Combinatorics and Probability

Under the uniform distribution, $\Pr\{A\} = |A|/|S|$, so probability reduces to counting. The counting toolkit built in §C.1 directly feeds §C.2–C.4:

| Counting result | Probabilistic application |
|----------------|--------------------------|
| $n^k$ strings | $\Pr\{\text{specific bit string}\} = 1/2^n$ |
| $n!$ permutations | $\Pr\{\text{random permutation has property}\}$ (Ch. 5 analysis) |
| $\binom{n}{k}$ | Binomial distribution (C.38) — exactly $k$ successes |
| Entropy $H(\lambda)$ | Binomial tail bound (C.7); information-theoretic lower bounds |

### Linearity of Expectation — The Master Tool

The most-used probability fact in CLRS is linearity of expectation, because it holds **regardless of dependence**. The pattern is:

1. Define indicator $X_i = \mathbf{1}[\text{event } i \text{ occurs}]$ so $E[X_i] = \Pr\{\text{event } i\}$.
2. Express the quantity of interest as $X = \sum_i X_i$.
3. Apply linearity: $E[X] = \sum_i E[X_i] = \sum_i \Pr\{\text{event } i\}$.

Examples: expected number of inversions (Ch. 2), expected comparisons in quicksort (Ch. 7), expected chain length in hashing (Ch. 11).

### Geometric Distribution — "Waiting Time" Intuition

The geometric distribution models *waiting time*: how many independent trials until the first success? The key identity $E[X] = 1/p$ follows from the geometric series:

$$E[X] = \sum_{k=1}^\infty k\,q^{k-1}p = p \cdot \frac{d}{dq}\sum_{k=1}^\infty q^k = p \cdot \frac{d}{dq}\frac{q}{1-q} = \frac{1}{p}$$

This is used in: birthday-paradox analysis (how many people before a shared birthday, $p \approx k/365$), balls-into-bins (how many tosses to fill a bin), and hashing load analysis.

### Binomial via Indicator Variables — Variance Calculation

Computing $\text{Var}[X]$ for a binomial directly is tedious. The elegant approach: let $X_i = \mathbf{1}[\text{trial } i \text{ succeeds}]$; then $X = \sum_{i=1}^n X_i$ with $X_i$ *mutually independent*. Since $X_i \in \{0,1\}$, $\text{Var}[X_i] = E[X_i^2] - E[X_i]^2 = p - p^2 = pq$. Independence gives $\text{Var}[X] = \sum \text{Var}[X_i] = npq$.

---

## Key Takeaways & Next Steps

| Concept | One-Line Definition | Appears In |
|---------|-------------------|-----------|
| Rule of product | $|A \times B| = |A| \cdot |B|$ | Counting strings, sample spaces |
| $k$-permutation | Ordered $k$-subset; $P(n,k) = n!/(n-k)!$ | Arrangement problems |
| $\binom{n}{k}$ | Unordered $k$-subset of $n$-set | Binomial distribution, bounds |
| Entropy $H(\lambda)$ | $-\lambda\log_2\lambda - (1-\lambda)\log_2(1-\lambda)$; max at $\lambda=1/2$ | Binomial tail bound, info theory |
| Probability axioms | Non-negativity, normalization, countable additivity | Foundation of all probabilistic analysis |
| Conditional probability | $\Pr\{A\mid B\} = \Pr\{A\cap B\}/\Pr\{B\}$ | Bayes's theorem, algorithm analysis |
| Independence | $\Pr\{A\cap B\} = \Pr\{A\}\Pr\{B\}$ | Simplifies expectations/variances |
| Bayes's theorem | $\Pr\{A\mid B\} = \Pr\{A\}\Pr\{B\mid A\}/\Pr\{B\}$ | Inference, Monte Carlo methods |
| Linearity of expectation | $E[X+Y]=E[X]+E[Y]$ regardless of dependence | Quicksort, hashing, Ch. 5 analysis |
| Jensen's inequality | Convex $f \Rightarrow E[f(X)] \ge f(E[X])$ | Lower bound proofs |
| Markov's inequality | $\Pr\{X\ge t\} \le E[X]/t$ | Simple tail bound |
| Geometric distribution | Waiting time; $E[X]=1/p$, $\text{Var}=q/p^2$ | Birthday paradox, balls-into-bins |
| Binomial distribution | $k$ successes in $n$ trials; $E=np$, $\text{Var}=npq$ | Hashing, randomized algorithms |

**Key principles:**
1. **Under uniform distribution, probability = counting / $|S|$** — master §C.1 first.
2. **Linearity of expectation is the primary tool** — avoid computing full distributions when possible.
3. **Indicator random variables** decompose complex expectations into sums of probabilities.
4. **Independence matters for variance but not expectation** — variance of sums requires pairwise independence; expectation requires nothing.
5. **Geometric ↔ Binomial duality:** geometric counts trials until first success; binomial counts successes in fixed trials.

**Next:** §C.5 (Tails of the binomial distribution — Chernoff bounds and related tail inequalities) in file 1525.

---

### Navigation

**Previous:** [[AppB_Sets_Etc]]  
**Next:** [[AppD_Matrices]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
