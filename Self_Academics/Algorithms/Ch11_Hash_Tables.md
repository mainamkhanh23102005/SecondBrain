# Chapter 11: Hash Tables

**Source:** Introduction to Algorithms, 4th Ed. (CLRS)
**Tags:** #algorithms #clrs #data-structures #hash-tables #hashing #dictionaries

## Overview

A **hash table** is an effective data structure for implementing dictionaries (INSERT, SEARCH, DELETE). Under reasonable assumptions, each operation takes $O(1)$ time on average. The worst case is $\Theta(n)$.

---

## 11.1 Direct-Address Tables

When the universe $U = \{0, 1, \ldots, m-1\}$ of keys is small, use an array $T[0:m-1]$: slot $k$ holds a pointer to the element with key $k$, or NIL.

```
DIRECT-ADDRESS-SEARCH(T, k)  → T[k]          // O(1)
DIRECT-ADDRESS-INSERT(T, x)  → T[x.key] = x  // O(1)
DIRECT-ADDRESS-DELETE(T, x)  → T[x.key] = NIL // O(1)
```

**Limitation:** If $|U|$ is large or infinite, allocating $T[0:|U|-1]$ is impractical.

---

## 11.2 Hash Tables

When the set $K$ of keys actually stored is small relative to $U$, a hash function $h: U \to \{0, 1, \ldots, m-1\}$ maps keys to slots, reducing storage to $\Theta(|K|)$.

**Load factor:** $\alpha = n/m$ (average elements per slot), where $n = |K|$.

**Collision:** Two keys $k_1 \neq k_2$ with $h(k_1) = h(k_2)$. Unavoidable since $|U| > m$.

### Collision Resolution: Chaining

Each slot $T[j]$ points to a linked list of all elements hashing to $j$.

```
CHAINED-HASH-INSERT(T, x)    → LIST-PREPEND(T[h(x.key)], x)     // O(1)
CHAINED-HASH-SEARCH(T, k)    → LIST-SEARCH(T[h(k)], k)
CHAINED-HASH-DELETE(T, x)    → LIST-DELETE(T[h(x.key)], x)      // O(1)
```

**Analysis (independent uniform hashing):**

- **Theorem 11.1:** Unsuccessful search takes $\Theta(1 + \alpha)$ average time.
- **Theorem 11.2:** Successful search takes $\Theta(1 + \alpha)$ average time.

When $n = O(m)$, we have $\alpha = O(1)$, so all dictionary operations run in $O(1)$ average time.

---

## 11.3 Hash Functions

### Static Hashing

**Division method:** $h(k) = k \bmod m$
- Fast (one division), but choosing $m$ requires care (prime not close to a power of 2)

**Multiplication method:** $h(k) = \lfloor m (kA \bmod 1) \rfloor$ where $0 < A < 1$
- $m$ need not be prime; $A = (\sqrt{5}-1)/2$ (Knuth's suggestion) works well

**Multiply-shift method:** For $m = 2^\ell$ and $w$-bit words:
$$h_a(k) = (ka \bmod 2^w) \gg (w - \ell)$$
- Three machine instructions; fast in practice

**Limitation of static hashing:** A malicious adversary can force all $n$ keys to collide at one slot → $\Theta(n)$ searches.

### Random Hashing (Universal Hashing)

Choose a hash function **randomly** from a family $H$ at program startup. A family $H$ is **universal** if for any distinct $k_1, k_2 \in U$:
$$\Pr_{h \in H}\{h(k_1) = h(k_2)\} \leq \frac{1}{m}$$

**Number-theoretic construction:** For prime $p > m$, with $a \in \{1,\ldots,p-1\}$ and $b \in \{0,\ldots,p-1\}$:
$$h_{a,b}(k) = ((ak + b) \bmod p) \bmod m$$
The family $H_{pm} = \{h_{a,b}\}$ is universal (**Theorem 11.4**).

**Multiply-shift family (recommended):** The family of multiply-shift functions with odd constants $a$ is $2/m$-universal (**Theorem 11.5**). Fast and practical.

**Corollary 11.3:** With universal hashing and chaining, any sequence of $s$ INSERT/SEARCH/DELETE operations with $n = O(m)$ inserts takes $\Theta(s)$ expected time.

### Hashing Long Inputs

For variable-length strings/vectors: use cryptographic hash functions (e.g., SHA-256 with a random salt):
$$h_a(k) = \text{SHA-256}(a \mathbin{\|} k) \bmod m$$

---

## 11.4 Open Addressing

All elements stored **in the hash table itself** — no linked lists. When a slot is occupied, use a **probe sequence** to find the next slot.

For INSERT, SEARCH, DELETE: probe positions $h(k, 0), h(k, 1), \ldots, h(k, m-1)$ form a permutation of $\{0, 1, \ldots, m-1\}$.

**Common probe sequences:**

| Method | Formula | Property |
|---|---|---|
| **Linear probing** | $h(k, i) = (h'(k) + i) \bmod m$ | Primary clustering problem |
| **Quadratic probing** | $h(k, i) = (h'(k) + c_1 i + c_2 i^2) \bmod m$ | Secondary clustering |
| **Double hashing** | $h(k, i) = (h_1(k) + i \cdot h_2(k)) \bmod m$ | Best distribution |

**Load factor constraint:** $\alpha < 1$ required (table must have empty slots).

**Expected probes (unsuccessful search):**
$$\frac{1}{1 - \alpha} \quad \text{(uniform hashing assumption)}$$

**Expected probes (successful search):**
$$\frac{1}{\alpha} \ln \frac{1}{1-\alpha}$$

**Deletion** in open-addressing tables is tricky: must mark slots as DELETED (not NIL) to avoid breaking probe chains.

---

## 11.5 Practical Considerations (Hierarchical Memory)

Modern computers have multi-level cache hierarchies. Cache-friendly hash functions access memory in patterns that exploit spatial locality. The text discusses RC6-based hash function design for hierarchical memory systems.

---

## Performance Summary

| Operation | Worst Case | Average Case (uniform hashing) |
|---|---|---|
| INSERT (chaining) | $O(1)$ | $O(1)$ |
| DELETE (chaining, with pointer) | $O(1)$ | $O(1)$ |
| SEARCH (chaining) | $\Theta(n)$ | $\Theta(1 + \alpha)$ |
| SEARCH (open addressing) | $\Theta(n)$ | $O(1/(1-\alpha))$ |

When $\alpha = O(1)$: all dictionary operations take $O(1)$ expected time.

---

### Navigation
**Previous:** [[Ch10_Elementary_Data_Structures]]
**Next:** [[Ch12_Binary_Search_Trees]]
**Hub:** [[Index_Introduction_to_Algorithms]]
