# Chapter 3: Characterizing Running Times

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #asymptotic-notation #complexity

## Overview

This chapter formalizes asymptotic notation for characterizing algorithm efficiency. It introduces $O$, $\Omega$, $\Theta$, $o$, and $\omega$ notations, their formal definitions, and reviews standard mathematical functions (polynomials, exponentials, logarithms, factorials, Fibonacci numbers) that commonly arise in algorithm analysis.

---

## 3.1 Intuitive Asymptotic Notation

### O-notation (Upper Bound)
$f(n) = O(g(n))$: $f$ grows **no faster** than $g$.

- $7n^3 + 100n^2 - 20n + 6 = O(n^3)$ — also $O(n^4)$, $O(n^5)$, etc.
- Useful for blanket worst-case statements

### $\Omega$-notation (Lower Bound)
$f(n) = \Omega(g(n))$: $f$ grows **at least as fast** as $g$.

- $7n^3 + 100n^2 - 20n + 6 = \Omega(n^3)$ — also $\Omega(n^2)$, $\Omega(n)$

### $\Theta$-notation (Tight Bound)
$f(n) = \Theta(g(n))$: $f$ grows **at precisely the rate** of $g$ (within constant factors).

- If $f(n) = O(g(n))$ and $f(n) = \Omega(g(n))$, then $f(n) = \Theta(g(n))$

### Example: Insertion Sort
- Worst-case: $O(n^2)$, $\Omega(n^2)$, $\Theta(n^2)$ — all correct; $\Theta(n^2)$ most precise
- Best-case: $\Theta(n)$
- All-cases bound: $O(n^2)$ (correct, but only say $\Theta(n^2)$ for "worst-case")

**Common mistake:** Using $O$ where $\Theta$ is intended (implying tightness not guaranteed by $O$).

---

## 3.2 Formal Definitions

### $O$-notation

$$O(g(n)) = \{f(n) : \exists c > 0,\, n_0 > 0 \text{ s.t. } 0 \leq f(n) \leq c\,g(n)\ \forall n \geq n_0\}$$

We write $f(n) = O(g(n))$ (set membership, abusing "=").

**Example:** $4n^2 + 100n + 500 = O(n^2)$
- Need: $4n^2 + 100n + 500 \leq cn^2$
- Divide by $n^2$: $4 + 100/n + 500/n^2 \leq c$ — satisfied for $n_0 = 1$, $c = 604$

### $\Omega$-notation

$$\Omega(g(n)) = \{f(n) : \exists c > 0,\, n_0 > 0 \text{ s.t. } 0 \leq c\,g(n) \leq f(n)\ \forall n \geq n_0\}$$

**Example:** $4n^2 + 100n + 500 = \Omega(n^2)$ — choose $n_0 = 1$, $c = 4$

### $\Theta$-notation

$$\Theta(g(n)) = \{f(n) : \exists c_1, c_2 > 0,\, n_0 > 0 \text{ s.t. } 0 \leq c_1\,g(n) \leq f(n) \leq c_2\,g(n)\ \forall n \geq n_0\}$$

**Theorem 3.1:** $f(n) = \Theta(g(n))$ if and only if $f(n) = O(g(n))$ and $f(n) = \Omega(g(n))$.

### $o$-notation (Strict Upper Bound)

$$o(g(n)) = \{f(n) : \forall c > 0,\, \exists n_0 > 0 \text{ s.t. } 0 \leq f(n) < c\,g(n)\ \forall n \geq n_0\}$$

Equivalently: $\lim_{n \to \infty} f(n)/g(n) = 0$.

- $2n = o(n^2)$ but $2n^2 \neq o(n^2)$

### $\omega$-notation (Strict Lower Bound)

$$\omega(g(n)) = \{f(n) : \forall c > 0,\, \exists n_0 > 0 \text{ s.t. } 0 \leq c\,g(n) < f(n)\ \forall n \geq n_0\}$$

Equivalently: $\lim_{n \to \infty} g(n)/f(n) = 0$.

- $n^2/2 = \omega(n)$ but $n^2/2 \neq \omega(n^2)$

### Asymptotic Notation Analogy

| Asymptotic | Numeric analogy |
|---|---|
| $f = O(g)$ | $a \leq b$ |
| $f = \Omega(g)$ | $a \geq b$ |
| $f = \Theta(g)$ | $a = b$ |
| $f = o(g)$ | $a < b$ |
| $f = \omega(g)$ | $a > b$ |

**Note:** Trichotomy does NOT hold for asymptotic notation — some pairs of functions are incomparable (e.g., $n$ vs. $n^{1+\sin n}$).

### Properties

- **Transitivity** holds for all five notations
- **Reflexivity:** $f = \Theta(f)$, $f = O(f)$, $f = \Omega(f)$
- **Symmetry:** $f = \Theta(g) \Leftrightarrow g = \Theta(f)$
- **Transpose symmetry:** $f = O(g) \Leftrightarrow g = \Omega(f)$; $f = o(g) \Leftrightarrow g = \omega(f)$

---

## 3.3 Standard Notations and Common Functions

### Logarithms

$$\lg n = \log_2 n \quad \ln n = \log_e n \quad \lg^k n = (\log_2 n)^k \quad \lg \lg n = \log_2(\log_2 n)$$

**Key properties (for $a, b, c > 0$):**
$$\log_b(ac) = \log_b a + \log_b c \qquad \log_b(a^n) = n\log_b a \qquad \log_b a = \frac{\log_c a}{\log_c b}$$

Changing base only introduces a constant factor, so $O(\log_b n) = O(\log_2 n)$ for any constant $b > 1$.

**Polylogarithmic vs polynomial:** For any $a > 0$ and $b$:
$$\lim_{n\to\infty} \frac{(\log_2 n)^b}{n^a} = 0 \implies (\log_2 n)^b = o(n^a)$$
Any polynomial grows faster than any polylogarithm.

### Exponentials

For constants $a > 1$: $a^n$ grows faster than any polynomial.

$$e^x = \sum_{i=0}^{\infty} \frac{x^i}{i!} \geq 1 + x \quad (\text{equality only at } x = 0)$$

For small $x$: $e^x \approx 1 + x + \Theta(x^2)$

### Factorials

$$n! = \prod_{k=1}^{n} k \qquad n! \leq n^n$$

**Stirling's approximation:**
$$n! = \sqrt{2\pi n}\left(\frac{n}{e}\right)^n\left(1 + \Theta\left(\frac{1}{n}\right)\right)$$

Key results:
- $n! = o(n^n)$ — factorial is sub-exponential in $n^n$
- $n! = \omega(2^n)$ — factorial grows faster than $2^n$
- $\log_2(n!) = \Theta(n \log_2 n)$

### Iterated Logarithm $\lg^* n$

$$\lg^* n = \min\{i \geq 0 : \lg^{(i)} n \leq 1\}$$

where $\lg^{(i)} n$ applies $\log_2$ exactly $i$ times.

| $n$ | $\lg^* n$ |
|---|---|
| $2$ | $1$ |
| $4$ | $2$ |
| $16$ | $3$ |
| $65536$ | $4$ |
| $2^{65536}$ | $5$ |

$\lg^* n$ is extremely slowly growing — never exceeds 5 for practical input sizes.

### Fibonacci Numbers

$$F_0 = 0,\quad F_1 = 1,\quad F_i = F_{i-1} + F_{i-2} \quad (i \geq 2)$$

**Closed form:** $F_i = \phi^i / \sqrt{5}$ rounded to the nearest integer, where $\phi = (1+\sqrt{5})/2 \approx 1.618$ (golden ratio).

Fibonacci numbers grow **exponentially**.

### Function Growth Rate Summary

$$1 \prec \log_2 \log_2 n \prec \log_2 n \prec n^{\epsilon} \prec n \prec n\log_2 n \prec n^2 \prec n^3 \prec 2^n \prec n!$$

(where $\epsilon > 0$ is any positive constant)

---

## Key Results

| Notation | Meaning | Example |
|---|---|---|
| $O(n^2)$ | Grows at most as fast as $n^2$ | Insertion sort worst-case bound |
| $\Omega(n^2)$ | Grows at least as fast as $n^2$ | Insertion sort worst-case lower bound |
| $\Theta(n \log_2 n)$ | Grows at exactly $n \log_2 n$ rate | Merge sort all cases |
| $o(n^2)$ | Grows strictly slower than $n^2$ | $n \log_2 n = o(n^2)$ |
| $\omega(n)$ | Grows strictly faster than $n$ | $n^2/2 = \omega(n)$ |

---

### Navigation
**Previous:** [[Ch2_Getting_Started]]
**Next:** [[Ch4_Divide_and_Conquer]]
**Hub:** [[Index_Introduction_to_Algorithms]]
