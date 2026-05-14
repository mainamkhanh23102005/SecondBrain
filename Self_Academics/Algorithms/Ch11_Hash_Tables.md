# Chapter 11: Hash Tables

## Executive Summary

Chapter 11 presents **hash tables** — the standard data structure for the dictionary problem (INSERT, DELETE, SEARCH). By mapping keys through a **hash function** $h: U \to \{0, 1, \ldots, m-1\}$, hash tables store $n$ keys in $\Theta(m)$ space. Under **independent uniform hashing**, all dictionary operations take $\Theta(1 + \alpha)$ expected time, where **load factor** $\alpha = n/m$. When $n = O(m)$, all operations are $O(1)$ expected. The chapter covers two collision resolution strategies (**chaining** and **open addressing**) and the critical design issue of hash functions — culminating in **universal hashing**, which provides worst-case guarantees regardless of adversarial key choices.

---

## Zero-Loss Extraction

### Core Algorithms & Pseudocode

**Direct-address table** (baseline — only feasible when universe $U$ is small):

```
DIRECT-ADDRESS-SEARCH(T, k)
1  return T[k]

DIRECT-ADDRESS-INSERT(T, x)
1  T[x.key] = x

DIRECT-ADDRESS-DELETE(T, x)
1  T[x.key] = NIL
```

**Chaining collision resolution**:

```
CHAINED-HASH-INSERT(T, x)
1  LIST-PREPEND(T[h(x.key)], x)        // O(1) worst case

CHAINED-HASH-SEARCH(T, k)
1  return LIST-SEARCH(T[h(k)], k)      // O(1 + α) expected

CHAINED-HASH-DELETE(T, x)
1  LIST-DELETE(T[h(x.key)], x)         // O(1) with doubly linked lists
```

**Hash function examples:**

```
// Division method:   h(k) = k mod m

// Multiplication method:   h(k) = ⌊m (kA mod 1)⌋
//   where 0 < A < 1 (e.g., A ≈ (√5 – 1)/2 ≈ 0.6180)

// Multiply-shift method (m = 2^ℓ, a is random odd w-bit integer):
//   ha(k) = (ka mod 2^w) ⋙ (w – ℓ)
//   (take top ℓ bits of the low-order w-bit product)
```

**Open addressing — probing sequences:**

```
// Linear probing:     h(k, i) = (h'(k) + i) mod m
// Quadratic probing:  h(k, i) = (h'(k) + c₁i + c₂i²) mod m
// Double hashing:     h(k, i) = (h₁(k) + i·h₂(k)) mod m
```

---

## Deep-Dive Explanations

### Direct Addressing vs. Hashing

**Direct-address table:** Array $T[0:m-1]$; slot $k$ stores element with key $k$. All operations $O(1)$. Requires $|U| = m$ to be small and affordable.

**Hash table:** Map key $k$ to slot $h(k)$. Reduces storage from $|U|$ to $m \ll |U|$. Trade-off: collisions must be handled.

**Key constraint:** Collisions are unavoidable when $|U| > m$ (pigeonhole principle). A good hash function minimizes collisions and makes their distribution uniform.

### Time and Space Complexity Analysis

#### Chaining

Load factor $\alpha = n/m$ = average chain length.

**Theorem 11.1:** Unsuccessful search = $\Theta(1 + \alpha)$ expected time.
*Proof:* Hashing to a slot takes $O(1)$; expected chain length at any slot is $\alpha$; must traverse entire chain.

**Theorem 11.2:** Successful search = $\Theta(1 + \alpha)$ expected time.
*Proof (via indicator variables):* Expected number of elements before the target in its chain = $\frac{\alpha}{2} - \frac{\alpha}{2n}$. Total: $\Theta(1 + \alpha)$.

**When $n = O(m)$:** $\alpha = O(1)$ → all operations $O(1)$ expected. INSERT and DELETE are $O(1)$ worst case.

**Worst case:** $\Theta(n)$ — if all $n$ keys hash to same slot.

#### Open Addressing

No external chains — all elements stored in the table itself. Each key $k$ defines a **probe sequence** $h(k, 0), h(k, 1), \ldots, h(k, m-1)$ — a permutation of $\{0, 1, \ldots, m-1\}$.

| Scheme | Probe sequence | Clustering |
|--------|---------------|------------|
| Linear probing | $h'(k) + i \pmod{m}$ | Primary clustering |
| Quadratic probing | $h'(k) + c_1 i + c_2 i^2 \pmod{m}$ | Secondary clustering |
| Double hashing | $h_1(k) + i \cdot h_2(k) \pmod{m}$ | Minimal clustering |

**Expected probes for open addressing:**
- Unsuccessful search: $\leq \frac{1}{1-\alpha}$ (for $\alpha < 1$)
- Successful search: $\leq \frac{1}{\alpha} \ln \frac{1}{1-\alpha}$

Open addressing requires $\alpha < 1$ (table must not be full) and cannot use doubly linked list deletion trick.

### Hash Function Design

**Goal:** Approximate **independent uniform hashing** — each key equally likely to hash to any slot, independently.

**Division method:** $h(k) = k \bmod m$
- Fast: one division operation
- Avoid $m$ as power of 2 (depends on only low bits) or power of 10 (decimal patterns)
- Best: $m$ = prime not close to power of 2 or 10

**Multiplication method:** $h(k) = \lfloor m(kA \bmod 1) \rfloor$
- $m$ need not be prime; typically $m = 2^\ell$
- Knuth suggests $A = (\sqrt{5}-1)/2 \approx 0.618$

**Multiply-shift method:** $h_a(k) = (ka \bmod 2^w) \gg (w - \ell)$
- $m = 2^\ell$, $a$ = random odd $w$-bit integer
- Implementable with 3 machine instructions

### Universal Hashing

**Motivation:** Any fixed hash function is vulnerable to adversarial inputs that all hash to the same slot. Solution: randomly choose from a hash family at runtime.

**Definition:** A family $\mathcal{H}$ of hash functions $U \to \{0, 1, \ldots, m-1\}$ is **universal** if for any two distinct keys $k_1, k_2 \in U$:
$$\Pr_{h \sim \mathcal{H}}\{h(k_1) = h(k_2)\} \leq \frac{1}{m}$$

**Corollary 11.3:** Using universal hashing with chaining, any sequence of $s$ INSERT/SEARCH/DELETE operations with $n = O(m)$ insertions takes $\Theta(s)$ expected time total.

**Construction (number-theoretic):** Let $p$ be prime with $p > |U|$. For $a \in \{1, \ldots, p-1\}$ and $b \in \{0, \ldots, p-1\}$:
$$h_{ab}(k) = ((ak + b) \bmod p) \bmod m$$
The family $\mathcal{H}_{pm} = \{h_{ab} : a \in \mathbb{Z}_p^*, b \in \mathbb{Z}_p\}$ is universal.

### Summary of Hash Table Performance

| Operation | Chaining (avg) | Open Addressing (avg) | Worst Case |
|-----------|---------------|----------------------|------------|
| SEARCH | $\Theta(1 + \alpha)$ | $O\!\left(\frac{1}{1-\alpha}\right)$ | $\Theta(n)$ |
| INSERT | $O(1)$ | $O\!\left(\frac{1}{1-\alpha}\right)$ | $\Theta(1)$ (chaining) |
| DELETE | $O(1)$ (doubly linked) | Complex | $O(1)$ (chaining) |

---

## Key Takeaways & Next Steps

1. **Hash tables** achieve $O(1)$ expected dictionary operations when the load factor $\alpha = n/m = O(1)$ — maintain this by resizing when $\alpha$ exceeds a threshold.
2. **Chaining** is simpler and more flexible; **open addressing** uses less memory (no pointer overhead) but requires $\alpha < 1$.
3. **Universal hashing** provides adversarial-input resistance — no input can force $\Theta(n)$ per operation when the hash function is chosen randomly from a universal family.
4. **Collision is unavoidable** ($|U| > m$) but can be made rare: $\binom{n}{2} / m$ expected collisions with uniform hashing.
5. The birthday paradox (Chapter 5) predicts that after $\Theta(\sqrt{m})$ insertions, a collision is expected — matches the chaining analysis.
6. Hash tables are used in compilers (symbol tables), databases (hash joins), Python's built-in `dict` type, and cryptographic applications.

---

### Navigation

**Previous:** [[Ch10_Elementary_Data_Structures]]
**Next:** [[Ch12_Binary_Search_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
