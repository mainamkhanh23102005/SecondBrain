# Chapter 31 — Number-Theoretic Algorithms

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #number-theory #cryptography #RSA #primality

---

## Executive Summary

Chapter 31 develops the number-theoretic foundations underlying modern cryptography, particularly the RSA public-key cryptosystem. Starting from elementary divisibility and GCD theory, the chapter builds to Euler's and Fermat's theorems, Chinese Remainder Theorem, modular exponentiation, RSA key generation/encryption, and a randomized primality test (Miller-Rabin).

**Why it matters:** Finding large primes is feasible ($O(\beta)$ arithmetic operations per test); factoring their product is believed infeasible — this asymmetry is the entire basis of RSA security.

**Input-size convention:** All "polynomial-time" bounds here are in terms of the number of *bits* $\beta = \lceil \log_2 n \rceil$, not the magnitude of $n$.

---

## Zero-Loss Extraction

### §31.1 — Elementary Number-Theoretic Notions

**Divisibility:** $d \mid a$ iff $a = kd$ for some integer $k$. If $d \mid a$ and $d > 0$, $d$ is a *divisor* of $a$.

**Division theorem (Thm 31.1):** For any integer $a$ and positive $n$, there exist unique $q, r$ with $0 \le r < n$ and $a = qn + r$.

**GCD key facts:**
- $\gcd(a,b)$ = smallest positive element of $\{ax + by : x,y \in \mathbb{Z}\}$ (Thm 31.2).
- Corollary: $d \mid a$ and $d \mid b \Rightarrow d \mid \gcd(a,b)$.
- $\gcd(an, bn) = n\,\gcd(a,b)$ (Corollary 31.4).

**Relatively prime:** $\gcd(a,b) = 1$. Key theorem: $\gcd(ab, p) = 1 \iff \gcd(a,p)=1$ and $\gcd(b,p)=1$ (Thm 31.6).

**Unique prime factorization (Thm 31.8):** Every composite integer $a$ has a unique representation $a = p_1^{e_1} p_2^{e_2} \cdots p_r^{e_r}$.

---

### §31.2 — Greatest Common Divisor (Euclid's Algorithm)

**GCD recursion theorem (Thm 31.9):** $\gcd(a, b) = \gcd(b, a \bmod b)$.

**Algorithm: EUCLID**

```
EUCLID(a, b)
1  if b == 0
2      return a
3  else return EUCLID(b, a mod b)
```

**Running time:** $O(\log b)$ recursive calls; $O(\beta^3)$ bit operations total.

**Lamé's theorem (Thm 31.11):** If $a > b \ge 1$ and $b < F_{k+1}$ (Fibonacci), then EUCLID makes fewer than $k$ recursive calls. Worst case inputs: $(F_{k+1}, F_k)$.

**Extended Euclid — computes Bézout coefficients:**

```
EXTENDED-EUCLID(a, b)
1  if b == 0
2      return (a, 1, 0)
3  (d', x', y') = EXTENDED-EUCLID(b, a mod b)
4  (d, x, y) = (d', y', x' − ⌊a/b⌋ · y')
5  return (d, x, y)
```

Returns $(d, x, y)$ such that $d = \gcd(a,b) = ax + by$. Same running time as EUCLID.

---

### §31.3 — Modular Arithmetic

**Finite abelian group:** Set $S$ with binary operation $\oplus$ satisfying closure, identity $e$, associativity, inverses. If commutative: *abelian*.

**Additive group $(\mathbb{Z}_n, +_n)$:** Elements $\{0, 1, \ldots, n-1\}$, operation $+_n$, identity 0, size $n$. Always a finite abelian group.

**Multiplicative group $\mathbb{Z}_n^*$:** Elements of $\mathbb{Z}_n$ relatively prime to $n$. Size = $\phi(n)$ (Euler's phi function):
$$\phi(n) = n \prod_{p \mid n} \left(1 - \frac{1}{p}\right)$$
For prime $p$: $\phi(p) = p - 1$.

**Key group theory results:**
- **Lagrange's theorem (Thm 31.15):** If $S'$ is a subgroup of finite group $S$, then $|S'|$ divides $|S|$.
- **Corollary 31.16:** Any proper subgroup has size $\le |S|/2$.
- **Order of element $a$:** Smallest positive $t$ with $a^{(t)} = e$; equals $|\langle a \rangle|$ (Thm 31.17).
- **Corollary 31.19:** For any finite group $(S, \oplus)$ and $a \in S$: $a^{(|S|)} = e$.

A **primitive root** (generator) of $\mathbb{Z}_n^*$ generates the whole group; $\mathbb{Z}_n^*$ is cyclic (has a primitive root) iff $n \in \{2, 4, p^e, 2p^e\}$ for odd prime $p$ (Thm 31.32).

---

### §31.4 — Solving Modular Linear Equations

**Equation:** $ax \equiv b \pmod{n}$

- **Solvable iff** $d \mid b$ where $d = \gcd(a, n)$ (Corollary 31.21).
- **Number of solutions:** Either $d$ distinct solutions mod $n$ or none (Corollary 31.22).
- **Unique solution** when $\gcd(a, n) = 1$ (Corollary 31.25).

**Algorithm: MODULAR-LINEAR-EQUATION-SOLVER**

```
MODULAR-LINEAR-EQUATION-SOLVER(a, b, n)
1  (d, x', y') = EXTENDED-EUCLID(a, n)
2  if d | b
3      x₀ = x'(b/d) mod n
4      for i = 0 to d − 1
5          print (x₀ + i(n/d)) mod n
6  else print "no solutions"
```

Running time: $O(\log n + \gcd(a,n))$ arithmetic operations.

**Multiplicative inverse:** When $\gcd(a, n) = 1$, the unique solution to $ax \equiv 1 \pmod{n}$ is $a^{-1} \bmod n = x'$ returned by EXTENDED-EUCLID.

---

### §31.5 — Chinese Remainder Theorem (CRT)

**Setup:** $n = n_1 n_2 \cdots n_k$ with $n_i$ pairwise relatively prime.

**Theorem 31.27 (CRT):** The map $a \mapsto (a \bmod n_1, \ldots, a \bmod n_k)$ is a bijection between $\mathbb{Z}_n$ and $\mathbb{Z}_{n_1} \times \cdots \times \mathbb{Z}_{n_k}$, preserving addition and multiplication.

**Reconstruction:** Given $(a_1, \ldots, a_k)$:
$$a = \left(\sum_{i=1}^k a_i m_i (m_i^{-1} \bmod n_i)\right) \bmod n, \quad m_i = n/n_i$$

**Key corollary:** The system $x \equiv a_i \pmod{n_i}$ for $i=1,\ldots,k$ has a unique solution mod $n$.

**Application to RSA:** RSA correctness proof uses CRT — $M^{ed} \equiv M \pmod{p}$ and $M^{ed} \equiv M \pmod{q}$, and since $\gcd(p,q)=1$, $M^{ed} \equiv M \pmod{n}$.

---

### §31.6 — Powers of an Element

**Euler's theorem (Thm 31.30):** For $\gcd(a,n)=1$: $a^{\phi(n)} \equiv 1 \pmod{n}$.

**Fermat's theorem (Thm 31.31):** For prime $p$ and $\gcd(a,p)=1$: $a^{p-1} \equiv 1 \pmod{p}$.

**Discrete logarithm theorem (Thm 31.33):** If $g$ is a primitive root of $\mathbb{Z}_n^*$, then $g^x \equiv g^y \pmod{n} \iff x \equiv y \pmod{\phi(n)}$.

**Nontrivial square roots of 1:** $x^2 \equiv 1 \pmod{n}$ with $x \not\equiv \pm 1$ implies $n$ is composite (Corollary 31.35). Used in Miller-Rabin.

**Modular exponentiation by repeated squaring:**

```
MODULAR-EXPONENTIATION(a, b, n)
1  if b == 0
2      return 1
3  elif b mod 2 == 0          // b even
4      d = MODULAR-EXPONENTIATION(a, b/2, n)
5      return (d · d) mod n
6  else                        // b odd
7      d = MODULAR-EXPONENTIATION(a, b − 1, n)
8      return (a · d) mod n
```

Running time: $O(\beta)$ arithmetic operations, $O(\beta^3)$ bit operations (for $\beta$-bit inputs $a, b, n$).

---

### §31.7 — RSA Public-Key Cryptosystem

**Key generation:**
1. Pick random large primes $p \ne q$ (≥1024 bits each).
2. $n = pq$.
3. Choose small odd $e$ with $\gcd(e, \phi(n)) = 1$, where $\phi(n) = (p-1)(q-1)$.
4. $d = e^{-1} \bmod \phi(n)$ via EXTENDED-EUCLID.
5. Public key: $(e, n)$. Secret key: $(d, n)$.

**Encryption/Decryption:**
$$P(M) = M^e \bmod n, \qquad S(C) = C^d \bmod n$$

**Correctness (Thm 31.36):** $M^{ed} \equiv M \pmod{n}$ for all $M \in \mathbb{Z}_n$.

*Proof sketch:* $ed = 1 + k(p-1)(q-1)$. By Fermat's theorem, $M^{p-1} \equiv 1 \pmod{p}$, so $M^{ed} \equiv M \pmod{p}$. Similarly mod $q$. By CRT, $M^{ed} \equiv M \pmod{n}$.

**Running time:**
- Apply public key: $O(\beta^2)$ bit ops ($O(1)$ modular multiplications since $\log e = O(1)$).
- Apply secret key: $O(\beta^3)$ bit ops ($O(\beta)$ modular multiplications).

**Security:** Breaking RSA ≈ factoring $n = pq$. No polynomial-time factoring algorithm known.

**Hybrid use:** RSA encrypts a short symmetric key $K$; symmetric cipher encrypts the long message. Hash-then-sign: sign $h(M)$ instead of $M$ directly.

---

### §31.8 — Primality Testing

**Prime density:** $\pi(n) \approx n / \ln n$ (Prime Number Theorem). Expected trials to find a $\beta$-bit prime: $\approx \ln 2^\beta \approx 0.693\beta$.

**PSEUDOPRIME (base-2 Fermat test):**

```
PSEUDOPRIME(n)
1  if MODULAR-EXPONENTIATION(2, n-1, n) ≠ 1 (mod n)
2      return COMPOSITE   // definite
3  else return PRIME      // probably
```

Fails for *Carmichael numbers* (composites satisfying Fermat's condition for all bases), e.g., 561, 1105, 1729.

**Miller-Rabin test:** Write $n - 1 = 2^t u$ ($u$ odd). For witness $a$, compute $x_0 = a^u \bmod n$ then square $t$ times. Returns COMPOSITE if: (a) $x_t \ne 1$, or (b) some $x_i = 1$ with $x_{i-1} \ne \pm 1$ (nontrivial square root of 1 detected).

```
WITNESS(a, n)
1  write n − 1 = 2^t · u  (u odd, t ≥ 1)
2  x₀ = MODULAR-EXPONENTIATION(a, u, n)
3  for i = 1 to t
4      xᵢ = xᵢ₋₁² mod n
5      if xᵢ == 1 and xᵢ₋₁ ≠ 1 and xᵢ₋₁ ≠ n−1
6          return TRUE   // nontrivial sqrt of 1
7  if xₜ ≠ 1
8      return TRUE       // Fermat failure
9  return FALSE

MILLER-RABIN(n, s)
1  for j = 1 to s
2      a = RANDOM(2, n−2)
3      if WITNESS(a, n)
4          return COMPOSITE   // definite
5  return PRIME               // almost surely
```

**Error bound:** For any odd composite $n$, at most $1/4$ of bases $a \in \{2,\ldots,n-2\}$ are non-witnesses. After $s$ trials, error probability $\le (1/4)^s$.

**Running time per trial:** $O(\beta^3)$ bit ops. For $s$ trials: $O(s\beta^3)$.

---

## Deep-Dive Explanations

### Why Extended Euclid Enables Inverses

EXTENDED-EUCLID computes $d = \gcd(a,n) = ax + ny$, so $ax \equiv d \pmod{n}$. If $d = 1$, then $ax \equiv 1 \pmod{n}$, giving $a^{-1} \equiv x \pmod{n}$. This is the algebraic key to RSA key generation (computing $d = e^{-1} \bmod \phi(n)$).

### How RSA Correctness Follows from Number Theory

| Step | Theorem Used |
|------|-------------|
| $M^{ed} \equiv M \pmod{p}$ | Fermat's theorem + $ed \equiv 1 \pmod{p-1}$ |
| $M^{ed} \equiv M \pmod{q}$ | Fermat's theorem + $ed \equiv 1 \pmod{q-1}$ |
| Combine: $M^{ed} \equiv M \pmod{pq}$ | Chinese Remainder Theorem |

### Why Miller-Rabin Beats Pseudoprime Testing

Carmichael numbers fool any *fixed* base Fermat test. Miller-Rabin adds the nontrivial-square-root check: for composite $n$, there exist nontrivial square roots of 1 mod $n$ (Corollary 31.35). The key bound (not proved in text) is that at most $\phi(n)/4$ bases are non-witnesses for any composite $n$, giving the $(1/4)^s$ error rate.

---

## Key Takeaways & Next Steps

| Algorithm | Purpose | Running Time |
|-----------|---------|-------------|
| EUCLID | Compute $\gcd(a,b)$ | $O(\beta^3)$ bit ops |
| EXTENDED-EUCLID | Compute $\gcd$ + Bézout coefficients | $O(\beta^3)$ bit ops |
| MODULAR-LINEAR-EQUATION-SOLVER | Solve $ax \equiv b \pmod n$ | $O(\log n)$ arith ops |
| MODULAR-EXPONENTIATION | Compute $a^b \bmod n$ | $O(\beta^3)$ bit ops |
| MILLER-RABIN($n$, $s$) | Primality test, error $\le (1/4)^s$ | $O(s\beta^3)$ bit ops |

**Key invariants:**
- RSA security ≡ hardness of integer factorization (not proven equivalent, just assumed).
- $n$ is prime $\Rightarrow$ no nontrivial square root of 1 mod $n$ exists.
- CRT decomposes $\mathbb{Z}_n$ into independent components; simplifies proofs and computations.

**Next:** Chapter 32 (String Matching) — a completely different domain. For deeper cryptography: elliptic-curve cryptography, lattice-based post-quantum schemes.

---

### Navigation

**Previous:** [[Ch30_Polynomials_and_the_FFT]]  
**Next:** [[Ch32_String_Matching]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
