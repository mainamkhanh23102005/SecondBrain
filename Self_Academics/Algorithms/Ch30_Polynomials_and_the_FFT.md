# Chapter 30: Polynomials and the FFT

**Source:** Introduction to Algorithms (CLRS), Chapter 30  
**Tags:** #algorithms #FFT #polynomials #DFT #divide-and-conquer #signal-processing

---

## Executive Summary

The **Fast Fourier Transform (FFT)** reduces polynomial multiplication from $\Theta(n^2)$ (naïve coefficient-form) to $\Theta(n \log_2 n)$ by converting between two polynomial representations: **coefficient form** and **point-value form**. The key insight is that evaluating a polynomial at the $n$-th roots of unity admits a divide-and-conquer recursion (splitting even/odd coefficients) that halves the problem each time. The same trick inverts the DFT matrix to interpolate. This gives the **convolution theorem**: $c = a \otimes b$ iff $\text{DFT}(c) = \text{DFT}(a) \cdot \text{DFT}(b)$ (pointwise), computable in $\Theta(n \log_2 n)$.

---

## Zero-Loss Extraction

### 1. Polynomial Representations

A polynomial $A(x) = \sum_{j=0}^{n-1} a_j x^j$ of **degree-bound $n$** has:

#### Coefficient Representation
- Vector $a = (a_0, a_1, \ldots, a_{n-1})$.
- **Evaluation at $x_0$:** $\Theta(n)$ via Horner's rule: $A(x_0) = a_0 + x_0(a_1 + x_0(a_2 + \cdots))$.
- **Addition of two degree-$n$ polys:** $\Theta(n)$.
- **Multiplication of two degree-$n$ polys:** $\Theta(n^2)$ naïvely; $c_k = \sum_{j=0}^k a_j b_{k-j}$.

The product vector $c = a \otimes b$ is called the **convolution** of $a$ and $b$.

#### Point-Value Representation
- Set of $n$ pairs $\{(x_0, y_0), \ldots, (x_{n-1}, y_{n-1})\}$ with $y_k = A(x_k)$, all $x_k$ distinct.
- **Uniqueness:** Theorem 30.1 — there is exactly one polynomial of degree-bound $n$ passing through $n$ distinct point-value pairs (Vandermonde matrix is invertible when points are distinct).
- **Evaluation → Addition:** $\Theta(n)$ (pointwise sum).
- **Evaluation → Multiplication:** $\Theta(n)$ (pointwise product), **but** degree-$n$ × degree-$n$ product has degree-bound $2n$, requiring $2n$ evaluation points.

#### Fast Polynomial Multiplication via FFT

$$\text{Coeff}(A) \xrightarrow{\text{FFT at } 2n\text{th roots}} \text{PV}(A) \xrightarrow{\times} \text{PV}(C) \xrightarrow{\text{Inverse FFT}} \text{Coeff}(C)$$

**Steps (for degree-bound $n$ inputs, assuming $n$ is a power of 2):**
1. **Extend:** pad $A$ and $B$ with $n$ zero high-order coefficients → degree-bound $2n$.
2. **Evaluate (FFT):** compute $2n$ point-value pairs for each at the complex $2n$-th roots of unity → $\Theta(n \log_2 n)$.
3. **Pointwise multiply:** $c_k = a_k \cdot b_k$ for $k = 0, \ldots, 2n-1$ → $\Theta(n)$.
4. **Interpolate (inverse FFT):** recover coefficients of $C$ → $\Theta(n \log_2 n)$.

**Theorem 30.2:** Two degree-bound-$n$ polynomials can be multiplied in $\Theta(n \log_2 n)$ time.

---

### 2. Complex Roots of Unity

A **complex $n$-th root of unity** is a complex number $\omega$ with $\omega^n = 1$.

The $n$ roots are $e^{2\pi i k/n}$ for $k = 0, 1, \ldots, n-1$, where $e^{iu} = \cos u + i \sin u$.

**Principal $n$-th root of unity:** $\omega_n = e^{2\pi i/n}$.

All other $n$-th roots of unity are $\omega_n^0, \omega_n^1, \ldots, \omega_n^{n-1}$.

These $n$ values are equally spaced around the unit circle in the complex plane.

**Key Lemmas:**

| Lemma | Statement |
|-------|-----------|
| **Cancellation (30.3)** | $\omega_{dn}^{dk} = \omega_n^k$ for $d > 0$ |
| **Corollary 30.4** | $\omega_n^{n/2} = -1$ for even $n$ |
| **Halving (30.5)** | The squares of the $n$ complex $n$-th roots of unity are the $n/2$ complex $(n/2)$-th roots of unity, each appearing twice |
| **Summation (30.6)** | $\sum_{j=0}^{n-1} (\omega_n^k)^j = 0$ for integer $k$ not divisible by $n$ |

The **halving lemma** is the crucial enabler of divide-and-conquer.

---

### 3. The Discrete Fourier Transform (DFT)

For input vector $a = (a_0, \ldots, a_{n-1})$, the **DFT** is the vector $y = \text{DFT}_n(a)$ where:

$$y_k = A(\omega_n^k) = \sum_{j=0}^{n-1} a_j \omega_n^{kj}, \quad k = 0, 1, \ldots, n-1$$

In matrix form: $y = V_n a$, where $V_n$ is the **Vandermonde matrix** with $(k,j)$ entry $= \omega_n^{kj}$.

---

### 4. The FFT Algorithm

**Divide-and-conquer:** split $A(x)$ into even and odd indexed coefficients:
$$A_{\text{even}}(x) = a_0 + a_2 x + a_4 x^2 + \cdots + a_{n-2} x^{n/2-1}$$
$$A_{\text{odd}}(x) = a_1 + a_3 x + a_5 x^2 + \cdots + a_{n-1} x^{n/2-1}$$

$$A(x) = A_{\text{even}}(x^2) + x \cdot A_{\text{odd}}(x^2)$$

By the **halving lemma**, evaluating at $\omega_n^0, \ldots, \omega_n^{n-1}$ reduces to evaluating $A_{\text{even}}$ and $A_{\text{odd}}$ at the $n/2$ complex $(n/2)$-th roots of unity.

```
FFT(a, n)
 1  if n == 1
 2      return a                               // base case: DFT_1(a_0) = a_0
 3  ω_n = e^{2πi/n}
 4  ω = 1
 5  a_even = (a_0, a_2, ..., a_{n−2})
 6  a_odd  = (a_1, a_3, ..., a_{n−1})
 7  y_even = FFT(a_even, n/2)                // recursive DFT_{n/2}
 8  y_odd  = FFT(a_odd,  n/2)                // recursive DFT_{n/2}
 9  for k = 0 to n/2 − 1
10      y_k         = y_even[k] + ω · y_odd[k]    // "butterfly"
11      y_{k+n/2}   = y_even[k] − ω · y_odd[k]    // "butterfly"
12      ω = ω · ω_n                               // twiddle factor update
13  return y
```

**Lines 10–11** are called **butterfly operations**; the twiddle factor $\omega \cdot y_{\text{odd}}[k]$ appears once but is added and subtracted.

**Running time recurrence:**
$$T(n) = 2T(n/2) + \Theta(n) \implies T(n) = \Theta(n \log_2 n)$$

(Case 2 of the master theorem.)

---

### 5. Inverse DFT (Interpolation)

**Theorem 30.7:** The inverse of the DFT matrix $V_n$ has $(j,k)$ entry $= \omega_n^{-jk}/n$.

The **inverse DFT** is:
$$a_j = \frac{1}{n} \sum_{k=0}^{n-1} y_k \omega_n^{-jk}, \quad j = 0, \ldots, n-1$$

**Implementation:** run FFT with $\omega_n$ replaced by $\omega_n^{-1}$, then divide each output by $n$.

$$\text{Inverse FFT runs in } \Theta(n \log_2 n) \text{ as well.}$$

---

### 6. The Convolution Theorem

**Theorem 30.8 (Convolution Theorem):** For vectors $a$ and $b$ of length $n$ (power of 2), padded to length $2n$:
$$a \otimes b = \text{DFT}_{2n}^{-1}(\text{DFT}_{2n}(a) \cdot \text{DFT}_{2n}(b))$$

where $\cdot$ denotes componentwise multiplication.

This says: **convolution in the time domain = pointwise multiplication in the frequency domain.** The FFT makes both directions fast ($\Theta(n \log_2 n)$).

---

### 7. FFT Circuit (§30.3)

The FFT structure naturally maps to a **hardware circuit** (butterfly network):
- $n$ inputs fan into $\log_2 n$ stages of $n/2$ butterfly operations each.
- Total: $\frac{n}{2} \log_2 n$ butterfly operations.
- Used in signal processors, MP3 encoders, video codecs, etc.

The bit-reversal permutation of input indices explains the input ordering: coefficient $a_j$ is placed at index given by bit-reversing the binary representation of $j$.

---

## Deep-Dive Explanations

### Why Roots of Unity Enable $\Theta(n \log_2 n)$

At arbitrary evaluation points, computing all $n$ values of $A$ requires $\Omega(n^2)$ multiplications. The roots of unity satisfy the **halving lemma**: the squares of the $n$ $n$-th roots are exactly the $n/2$ $(n/2)$-th roots of unity, each with multiplicity 2. This means evaluating the two sub-polynomials at $n/2$ points each exactly covers all the work needed for the full $n$-point evaluation — a perfect halving that yields the $T(n) = 2T(n/2) + \Theta(n)$ recurrence.

### Butterfly Computation

For each $k = 0, \ldots, n/2 - 1$, the butterfly operation computes:
$$y_k = y_{\text{even},k} + \omega_n^k \cdot y_{\text{odd},k}$$
$$y_{k+n/2} = y_{\text{even},k} - \omega_n^k \cdot y_{\text{odd},k}$$

This exploits $\omega_n^{k+n/2} = -\omega_n^k$ (from the Corollary 30.4: $\omega_n^{n/2} = -1$), allowing one twiddle-factor multiplication to compute two outputs.

### DFT as a Change of Basis

The DFT is just a matrix multiplication $y = V_n a$ with a special Vandermonde matrix whose columns are geometric progressions of roots of unity. The inverse DFT is $a = V_n^{-1} y = \bar{V}_n y / n$ (conjugate divided by $n$). The FFT exploits the structure of $V_n$ to factor it into sparse matrices, reducing $\Theta(n^2)$ to $\Theta(n \log_2 n)$ operations.

---

## Key Takeaways & Next Steps

1. **Two representations, one algorithm:** coefficient form is good for evaluation and addition; point-value form is good for multiplication. FFT converts in $\Theta(n \log_2 n)$.
2. **Polynomial multiplication in $\Theta(n \log_2 n)$** via: extend → FFT → pointwise multiply → inverse FFT.
3. **Halving lemma is the engine:** squaring the $n$-th roots gives the $(n/2)$-th roots → perfect recursive halving.
4. **Convolution theorem:** time-domain convolution = frequency-domain pointwise product. Fundamental in signal processing, compression, and scientific computing.
5. **Inverse FFT:** same algorithm with $\omega_n \to \omega_n^{-1}$ and a final division by $n$.
6. **Practical note:** $n$ must be a power of 2; otherwise, pad with zeros. Hardware FFT circuits implement the butterfly network directly.
7. **Next:** Chapter 31 (Number-Theoretic Algorithms) — GCDs, modular arithmetic, primality, RSA.

---

### Navigation

- **Previous:** [[Ch29_Linear_Programming|Ch29 — Linear Programming]]
- **Next:** [[Ch31_Number_Theoretic_Algorithms|Ch31 — Number-Theoretic Algorithms]]
- **Hub:** [[Index_Introduction_to_Algorithms|Introduction to Algorithms Index]]
