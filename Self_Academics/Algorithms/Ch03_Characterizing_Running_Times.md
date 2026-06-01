# Chapter 3: Characterizing Running Times

## Executive Summary

Chapter 3 formalizes asymptotic analysis — the language of algorithm efficiency. It introduces five notations ($O$, $\Omega$, $\Theta$, $o$, $\omega$) with rigorous set-theoretic definitions, explains how to use them correctly to characterize algorithm running times (with care about which case — worst, best, or average — is being characterized), and provides an extensive reference on standard mathematical functions that appear throughout algorithm analysis: floors, ceilings, modular arithmetic, polynomials, exponentials, logarithms (including $\log_2 n$ written as $\lg n$), factorials (Stirling's approximation), the iterated logarithm $\lg^* n$, and Fibonacci numbers.

---

## Zero-Loss Extraction

### The Five Asymptotic Notations — Formal Definitions

**$O$-notation (asymptotic upper bound):**
$$O(g(n)) = \{ f(n) : \exists\, c > 0,\, n_0 > 0 \text{ s.t. } 0 \leq f(n) \leq c\,g(n) \text{ for all } n \geq n_0 \}$$
> $f(n) = O(g(n))$ means $f$ grows **no faster than** $g$.

**$\Omega$-notation (asymptotic lower bound):**
$$\Omega(g(n)) = \{ f(n) : \exists\, c > 0,\, n_0 > 0 \text{ s.t. } 0 \leq c\,g(n) \leq f(n) \text{ for all } n \geq n_0 \}$$
> $f(n) = \Omega(g(n))$ means $f$ grows **at least as fast as** $g$.

**$\Theta$-notation (asymptotically tight bound):**
$$\Theta(g(n)) = \{ f(n) : \exists\, c_1, c_2 > 0,\, n_0 > 0 \text{ s.t. } 0 \leq c_1\,g(n) \leq f(n) \leq c_2\,g(n) \text{ for all } n \geq n_0 \}$$
> $f(n) = \Theta(g(n))$ means $f$ grows **precisely at the same rate as** $g$ (to within constant factors).

**Theorem 3.1:** $f(n) = \Theta(g(n))$ if and only if $f(n) = O(g(n))$ **and** $f(n) = \Omega(g(n))$.

**$o$-notation (strict upper bound, not asymptotically tight):**
$$o(g(n)) = \{ f(n) : \forall\, c > 0,\, \exists\, n_0 > 0 \text{ s.t. } 0 \leq f(n) < c\,g(n) \text{ for all } n \geq n_0 \}$$
> Equivalently: $f(n) \in o(g(n)) \iff \lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.

**$\omega$-notation (strict lower bound, not asymptotically tight):**
$$\omega(g(n)) = \{ f(n) : \forall\, c > 0,\, \exists\, n_0 > 0 \text{ s.t. } 0 \leq c\,g(n) < f(n) \text{ for all } n \geq n_0 \}$$
> Equivalently: $f(n) \in \omega(g(n)) \iff \lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$.

### Relational Properties of Asymptotic Notations

| Analogy | Asymptotic | Real Numbers |
|---------|-----------|--------------|
| $f(n) = O(g(n))$ | $f \preceq g$ | $a \leq b$ |
| $f(n) = \Omega(g(n))$ | $f \succeq g$ | $a \geq b$ |
| $f(n) = \Theta(g(n))$ | $f \asymp g$ | $a = b$ |
| $f(n) = o(g(n))$ | $f \prec g$ | $a < b$ |
| $f(n) = \omega(g(n))$ | $f \succ g$ | $a > b$ |

- **Transitivity:** $f = \Theta(g)$ and $g = \Theta(h) \Rightarrow f = \Theta(h)$ (and analogously for all five notations).
- **Reflexivity:** $f(n) = \Theta(f(n))$, $f(n) = O(f(n))$, $f(n) = \Omega(f(n))$.
- **Symmetry:** $f(n) = \Theta(g(n)) \iff g(n) = \Theta(f(n))$.
- **Transpose symmetry:** $f(n) = O(g(n)) \iff g(n) = \Omega(f(n))$ and $f(n) = o(g(n)) \iff g(n) = \omega(f(n))$.
- **No trichotomy:** Unlike real numbers, not all functions are asymptotically comparable (e.g., $n$ and $n^{1+\sin n}$).

### Standard Notations and Common Functions

**Logarithms** (critical notation throughout CLRS):
$$\lg n = \log_2 n \quad \text{(binary logarithm)}$$
$$\ln n = \log_e n \quad \text{(natural logarithm)}$$
$$\lg^k n = (\lg n)^k \quad \text{(exponentiation)}$$
$$\lg \lg n = \lg(\lg n) \quad \text{(composition)}$$

Logarithm identity (change of base — changes value by only a constant factor):
$$\log_b n = \frac{\log_c n}{\log_c b}$$

For any positive polynomial $p(n)$ of degree $d$: $p(n) = \Theta(n^d)$.

**Stirling's approximation:**
$$n! = \sqrt{2\pi n} \left(\frac{n}{e}\right)^n \left(1 + \Theta\!\left(\frac{1}{n}\right)\right)$$

Consequences:
- $n! = o(n^n)$
- $n! = \omega(2^n)$  
- $\lg(n!) = \Theta(n \log_2 n)$

**Iterated logarithm $\lg^* n$:**
$$\lg^* n = \min\{i \geq 0 : \lg^{(i)} n \leq 1\}$$
where $\lg^{(i)} n$ is $\lg$ applied $i$ times. Values:

| $n$ | $\lg^* n$ |
|-----|----------|
| 2 | 1 |
| 4 | 2 |
| 16 | 3 |
| 65536 | 4 |
| $2^{65536}$ | 5 |

Since $10^{80}$ atoms exist in the observable universe and $2^{65536} \gg 10^{80}$, we effectively never encounter $\lg^* n > 5$ in practice.

**Fibonacci numbers** $F_i$: $F_0 = 0$, $F_1 = 1$, $F_i = F_{i-1} + F_{i-2}$ for $i \geq 2$.

Related to golden ratio $\phi = \frac{1 + \sqrt{5}}{2} \approx 1.618$:
$$F_i = \frac{\phi^i - \hat{\phi}^i}{\sqrt{5}} \approx \frac{\phi^i}{\sqrt{5}} \quad \text{(rounded to nearest integer for } i \geq 0\text{)}$$

where $\hat{\phi} = \frac{1-\sqrt{5}}{2} \approx -0.618$. Both satisfy $x^2 = x + 1$. Fibonacci numbers grow exponentially.

---

## Deep-Dive Explanations

### Using Asymptotic Notation Correctly

**Correct usage for Insertion Sort:**
- Worst-case running time: $\Theta(n^2)$ (most precise), also $O(n^2)$, $\Omega(n^2)$.
- Best-case running time: $\Theta(n)$.
- Blanket statement for all cases: $O(n^2)$ (correct — upper bound holds always), but **NOT** $\Theta(n^2)$ (incorrect — best case is only $\Theta(n)$).

**Key distinction:** "$O$" is a set; "$=$" means membership ($\in$). Writing $f(n) = O(g(n))$ is an intentional abuse of notation for readability.

**Asymptotic notation in equations:** In $2n^2 + \Theta(n) = \Theta(n^2)$, each $\Theta(n)$ represents an anonymous function. The equation means: for any $f(n) \in \Theta(n)$, there exists $h(n) \in \Theta(n^2)$ such that $2n^2 + f(n) = h(n)$.

### $\Omega(n^2)$ Lower Bound Proof for Insertion Sort (Worst Case)

Let $n$ be divisible by 3. Place the $n/3$ largest values in positions $A[1:n/3]$. After sorting, they must end up in $A[2n/3+1:n]$, passing through each of the $n/3$ middle positions $A[n/3+1:2n/3]$ one step at a time. At minimum: $(n/3)(n/3) = n^2/9$ shifts → $\Omega(n^2)$ worst case.

Combined with the $O(n^2)$ upper bound: worst-case time is $\Theta(n^2)$.

### Key Growth Rates

From slowest to fastest:
$$1 \prec \log_2 n \prec \sqrt{n} \prec n \prec n \log_2 n \prec n^2 \prec n^3 \prec 2^n \prec n!$$

Any exponential $a^n$ ($a > 1$) dominates any polynomial $n^b$:
$$\lim_{n \to \infty} \frac{n^b}{a^n} = 0 \quad \text{for all constants } a > 1,\, b > 0$$

Any positive polynomial dominates any polylogarithm:
$$\lim_{n \to \infty} \frac{\lg^k n}{n^\epsilon} = 0 \quad \text{for all constants } k,\, \epsilon > 0$$

### Formal Example: $4n^2 + 100n + 500 = O(n^2)$

Need constants $c, n_0 > 0$ such that $4n^2 + 100n + 500 \leq cn^2$ for all $n \geq n_0$.

Dividing by $n^2$: $4 + 100/n + 500/n^2 \leq c$.

Choose $n_0 = 100$: then $c = 5.05$ works. ✓

Equivalently: $4n^2 + 100n + 500 = \Omega(n^2)$ (choose $c = 4$, $n_0 = 1$). ✓

Therefore: $4n^2 + 100n + 500 = \Theta(n^2)$.

---

## Key Takeaways & Next Steps

1. **$O$-notation** gives upper bounds; **$\Omega$-notation** gives lower bounds; **$\Theta$-notation** (requiring both) is the most informative. Always specify which — avoid saying "running time is $\Theta(n^2)$" without specifying worst/best/average case.
2. **$\lg n$ always means $\log_2 n$** in CLRS notation — the natural choice for computer scientists since algorithms often split problems in two.
3. **Logarithms grow slower than any positive polynomial**; factorials grow faster than any exponential.
4. **$\lg^* n \leq 5$** for all practical input sizes — it appears in the analysis of union-find (Chapter 19).
5. The five notations form a precise mathematical vocabulary that Chapter 4 uses immediately to analyze recurrences.

---

### Navigation

**Previous:** [[Ch02_Getting_Started]]
**Next:** [[Ch04_Divide_and_Conquer]]
**Hub:** [[Index_Introduction_to_Algorithms]]
