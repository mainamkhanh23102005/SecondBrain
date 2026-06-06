# Module 6 – Basic Cryptography

**Source:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage, 2022) | Module 6  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #cryptography #encryption #hashing #asymmetric #symmetric #CS451

---

## Executive Summary

Cryptography is the discipline of transforming information so that only authorized parties can understand it. Unlike steganography (which hides the *existence* of data), cryptography masks the *content* so that even if the data is intercepted, it is unreadable. This module covers the three algorithm families (**hash**, **symmetric**, **asymmetric**), their use cases and constraints, how they are attacked, and how they are implemented in software and hardware. The closing blockchain section shows how cryptographic hash chaining produces tamper-evident distributed ledgers.

---

## 1. Foundations of Cryptography

### Steganography vs. Cryptography

| Technique | Goal | Mechanism | Example |
|---|---|---|---|
| **Steganography** | Hide the *existence* of data | Embeds data in cover files (image, audio, video headers) | Greek tablets with wax covering secret messages |
| **Cryptography** | Hide the *meaning* of data | Mathematically transforms plaintext into ciphertext | Modern TLS, AES encryption |

> Both can be combined for double protection: first encrypt, then steganographically hide. An attacker must first *find* the hidden data and then *decrypt* it.

### Core Terminology

| Term | Definition |
|---|---|
| **Plaintext** | Unencrypted data that is input for encryption or output of decryption |
| **Ciphertext** | The scrambled, unreadable output of encryption |
| **Cleartext** | Unencrypted data that is *not* intended to be encrypted (transmitted "in the clear") |
| **Encryption** | The process of changing plaintext to ciphertext |
| **Decryption** | The process of changing ciphertext back to plaintext |
| **Algorithm (Cipher)** | A set of procedures based on a mathematical formula that performs encryption/decryption |
| **Key** | A mathematical value input into the algorithm to produce ciphertext; must be kept secret |

> At its essence, cryptography **replaces trust with mathematics**. The security is based on the secrecy of the *key*, not the secrecy of the *algorithm*. Algorithms are public and standardized; keys are private.

### Cipher Types

#### By Operation on Data

| Type | Description | Security |
|---|---|---|
| **Stream cipher** | Processes one character at a time, replacing it with one character | Less secure — the generating engine does not vary; only the plaintext changes |
| **Block cipher** | Manipulates an entire block of plaintext (8–16 bytes) at once; blocks can be randomized | More secure — cipher resets to original state after each block; more random output |
| **Sponge function** | Takes input of any length, applies a repeated absorption process, outputs string of any requested length | Used in SHA-3 family |

#### Early Cipher Examples

- **Substitution cipher**: replaces each character with another (A→M, B→N, etc.).
- **ROT13**: rotates the alphabet 13 steps (A→N, B→O); applying twice returns original. `security` → `frphevgl`.
- **XOR cipher**: uses eXclusive OR on binary values.  
  - If bits are the same → output `0`.  
  - If bits differ → output `1`.  
  - `s` (01110011) XOR `f` (01100110) = 00010101.
- **One-Time Pad (OTP)**: combines plaintext with a random key of equal length. Theoretically unbreakable if used exactly once and key is truly random. Used by WWII intelligence services.

**OTP Example:**

| Plaintext | Position | Pad | Position | Calculation | Result |
|---|---|---|---|---|---|
| S | 19 | C | 3 | 19+3−1=21 | U |
| E | 5 | B | 2 | 5+2−1=6 | F |
| C | 3 | Y | 25 | 3+25−1=1 | A |
| R | 18 | F | 6 | 18+6−1=23 | W |
| E | 5 | E | 5 | 5+5−1=9 | I |
| T | 20 | A | 1 | 20+1−1=20 | T |

### Cryptographic Use Cases

Cryptography provides five core security protections:

| Use Case | Protection Provided | Mechanism |
|---|---|---|
| **Confidentiality** | Only authorized parties can view data | Encryption ensures only key holders can read ciphertext |
| **Integrity** | Data has not been altered | Changing ciphertext without the key is computationally infeasible |
| **Authentication** | Proof of the sender's identity | Specific cryptographic techniques verify origin |
| **Nonrepudiation** | Prevents denial of an action | Sender cannot claim they never sent a signed message |
| **Obfuscation** | Makes something obscure | Encryption obscures the original content |

> **Security through obscurity is a fallacy**: hiding an algorithm (proprietary "military-grade" cryptography) does not make it secure. What makes cryptography secure is the secrecy of the **key**, not the algorithm. Proprietary algorithms have not been vetted by the cryptographic community and will likely contain flaws.

### Data States

Cryptography protects data in any of three states:

| State | Description | Example |
|---|---|---|
| **Data in processing** (data in use) | Actions being performed by a device | Printing a report |
| **Data in transit** (data in motion) | Data being transmitted across a network | Sending an email over the Internet |
| **Data at rest** | Data stored on electronic media | Files on a hard drive or NAS |

### Cryptographic Constraints

| Constraint | Explanation |
|---|---|
| **Speed** | Hardware/software factors limit encryption/decryption throughput |
| **Size** | Encrypted files can be up to one-third larger than plaintext |
| **Weak keys** | Some ciphers can generate keys that cause unpredictable behavior or weaken security |
| **Key length** | Short key lengths result in weaker security; brute-force becomes feasible |
| **Longevity** | As computers become more powerful, older ciphers become crackable faster |
| **Predictability** | Weak PRNGs create predictable output |
| **Reuse** | Reusing the same key for multiple encryptions creates a larger footprint for analysis |
| **Entropy** | Low entropy in the data-generating function allows prediction of future values |
| **Computational overhead** | IoT/sensor devices often lack capacity for standard cryptographic computations |

**Resource vs. Security Constraint:** Strong security requires high energy and low latency — directly conflicting goals for low-power IoT devices. **Lightweight cryptography** is an emerging subfield specifically targeting this constraint — it does not weaken security but reduces features and computational overhead.

---

## 2. Hash Algorithms

A **hash algorithm** creates a unique digital fingerprint (called a **digest** or **message digest**) of any set of data. Hashing is **one-way**: the original data cannot be derived from the digest.

> Hash algorithms are **not** for encryption (not designed to be reversed). They are for **comparison and verification**.

### Properties of a Secure Hash

| Property | Definition | Example |
|---|---|---|
| **Fixed size** | Any input length produces the same-length digest | `a` → 32-char hex; 1 million `a`s → 32-char hex (MD5) |
| **Unique** | Different inputs produce different digests; a 1-character change produces a completely different digest | `Sunday` ≠ `sunday` in digest |
| **Original** | Cannot produce an input that generates a predefined/desired hash | Infeasible to engineer collisions |
| **Secure** | The hash cannot be reversed to determine original plaintext | One-way function |

### Common Hash Algorithms

| Algorithm | Notes | Status |
|---|---|---|
| **MD2** (1989) | First in the Message Digest family | Deprecated |
| **MD4** | Second generation | Deprecated |
| **MD5** | Most widely used of the MD family; 128-bit digest | **No longer suitable for use** — serious weaknesses identified |
| **SHA-1** | 1993; US government standard | **No longer suitable** |
| **SHA-256** | SHA-2 family; 256-bit digest | Currently secure |
| **SHA-384** | SHA-2 family; 384-bit digest | Currently secure |
| **SHA-512** | SHA-2 family; 512-bit digest | Currently secure |
| **SHA-3** | Announced 2015; deliberately designed dissimilar to SHA-2 to prevent attackers building on prior work; uses a sponge function | Currently secure; recommended |
| **RIPEMD-128/256/320** | RACE Integrity Primitives Evaluation MD; uses two parallel independent computation chains combined at the end | Currently used |

**Sample Digests for the word "Cengage":**

| Algorithm | Digest |
|---|---|
| MD2 | b365b3f6ca8b35460782a658f2e82009 |
| MD5 | 7e169c6f44088e315c7b1f6513c1b0f7 |
| RIPEMD-160 | dd52a79bce64a1d145b51ce639e0dadda976516d |
| SHA-1 | 963ea98f0af1927e02ed0f13786162a5b8e713c0 |
| SHA-256 | f6c8a86bf6a5128cbaf2ad251b0beaa3604c11c51587de518737537800098d76 |
| SHA3-512 | 3a82d58e17f3991413c5f4e9811930b69513bba02a860eed82070f892ab381f9... |

---

## 3. Symmetric Cryptographic Algorithms

**Symmetric cryptography** uses the **same key** to encrypt and decrypt. Also called **private key cryptography**. Bob encrypts with key K → only Alice (who also has key K) can decrypt.

**Challenge**: distributing the shared key securely is the fundamental weakness. If the key is intercepted during distribution, all encrypted communication is compromised.

### Common Symmetric Algorithms

| Algorithm | Key Size | Block Size | Status | Notes |
|---|---|---|---|---|
| **DES** (Data Encryption Standard) | 56 bits | 64 bits | **Deprecated** | First widely used symmetric algorithm; no longer secure |
| **3DES** (Triple DES) | 112 or 168 bits | 64 bits | **Deprecated** | 3 rounds of DES (48 total iterations); three different keys for max security |
| **AES** (Advanced Encryption Standard) | 128, 192, or 256 bits | 128 bits | **Current standard** | Performs 3 steps on every block; rounds by key: 128-bit→9, 192-bit→11, 256-bit→13; no successful attacks to date |
| **RC4** (Rivest Cipher 4) | Up to 128 bits | Stream cipher | Weakened | Most common of the RC family; stream-based |
| **Blowfish** | 32–448 bits | 64 bits | Strong | No significant weaknesses found |
| **Twofish** | Up to 256 bits | 128 bits | Strong | Derived from Blowfish; considered strong but less widely used |

**How 3DES works:**

```
Plaintext → [Encrypt with Key 1] → Ciphertext 1
Ciphertext 1 → [Encrypt with Key 2] → Ciphertext 2
Ciphertext 2 → [Encrypt with Key 3] → Ciphertext 3 (final)
```

Total: 3 encryption passes × 16 rounds each = **48 iterations**.

---

## 4. Asymmetric Cryptographic Algorithms

**Asymmetric cryptography** (public key cryptography) solves the key distribution problem by using **two mathematically related keys**: a **public key** (freely distributed) and a **private key** (known only to the owner).

**Encryption flow:**
- Bob wants to send a secure message to Alice → Bob encrypts with **Alice's public key**.
- Only Alice can decrypt → Alice uses **her private key**.

**Core principles:**
- Keys work in **both directions**: what is encrypted with the public key can be decrypted with the private key, and vice versa.
- The **public key never needs to be protected** — anyone can have it.
- The **private key must never be shared with anyone**.

### Asymmetric Key Usage Reference

| Scenario | Whose Key | Which Key |
|---|---|---|
| Bob wants to send Alice a secure message | Alice's | Public key |
| Alice reads the encrypted message from Bob | Alice's | Private key |
| Bob wants to keep an encrypted copy for himself | Bob's | Public key (encrypt) → Private key (decrypt) |
| Bob receives Alice's reply | Bob's | Private key |
| Bob sends Alice a digital signature | Bob's | **Private key** (signs the hash) |
| Alice verifies Bob's digital signature | Bob's | **Public key** (decrypts the hash) |

### RSA Algorithm

The **RSA** asymmetric algorithm (1977) is based on the computational difficulty of **factoring** the product of two large prime numbers.

**RSA key generation (simplified with small numbers):**

1. Select two prime numbers: $p = 7,\ q = 19$
2. Compute: $n = p \times q = 133$
3. Compute: $m = (p-1)(q-1) = 6 \times 18 = 108$
4. Find $e$ such that $\gcd(e, m) = 1$: $e = 5$
5. Find $d$ such that $d = \frac{1 + n \cdot m}{e} = \frac{14364}{5} = 2872.8 \approx 2873$

- **Public key**: $(n = 133,\ e = 5)$
- **Private key**: $(n = 133,\ d = 2873)$

In practice, $p$ and $q$ are 1,024-bit or larger primes, making factoring computationally infeasible with classical computers.

**RSA's weakness**: as computers become faster, factoring becomes more feasible. Quantum computers threaten to break RSA entirely.

### Elliptic Curve Cryptography (ECC)

**ECC** replaces RSA's factoring problem with the mathematical difficulty of **elliptic curve discrete logarithm** computation. An elliptic curve is a function $y^2 = x^3 + ax + b$ drawn on an X-Y axis. Adding two points on the curve gives a third point on the curve (from which the inverse is used).

**ECC vs. RSA key length for equivalent security:**

| RSA Key (bits) | ECC Key (bits) |
|---|---|
| 1,024 | 160 |
| 2,048 | 224 |
| 3,072 | 256 |
| 7,680 | 384 |
| 15,360 | 521 |

> ECC provides equivalent security with dramatically smaller key sizes → faster computation + lower power consumption. This makes ECC ideal for mobile devices and IoT.

Uses: US government internal communications, Tor anonymity network, Bitcoin proof-of-ownership.

### Digital Signatures

A **digital signature** is an electronic verification of the sender. It provides:
1. **Sender verification**: confirms the identity of the message originator.
2. **Nonrepudiation**: the signer cannot later claim the signature was forged.
3. **Integrity proof**: the message has not been altered since signing.

**How digital signatures work (Bob to Alice):**

```
Step 1: Bob creates a memo.
Step 2: Bob hashes the memo → produces a digest.
Step 3: Bob encrypts the digest with his PRIVATE key → this encrypted digest is the digital signature.
Step 4: Bob sends the memo + digital signature to Alice.
Step 5: Alice decrypts the digital signature using Bob's PUBLIC key → reveals the digest.
         (If decryption fails → message did not come from Bob.)
Step 6: Alice hashes the received memo with the same algorithm.
Step 7: Alice compares her hash with the decrypted digest.
         If equal → message is authentic and unmodified.
         If not equal → message was tampered with.
```

> **Important**: digital signatures do not encrypt the message itself. Bob must additionally encrypt with Alice's public key if confidentiality is also required.

The **Digital Signature Algorithm (DSA)** is the US federal government standard (NIST, 1991; published in Digital Signature Standard, DSS). Patent is available worldwide royalty-free.

### Key Exchange Protocols

| Protocol | Description |
|---|---|
| **Diffie-Hellman (DH)** | Alice and Bob agree on a large prime and integer (public); through mathematical exchange, they independently compute the same shared secret key |
| **Diffie-Hellman Ephemeral (DHE)** | Same as DH but uses different (ephemeral/temporary) keys for each session; keys are discarded after use |
| **Elliptic Curve Diffie-Hellman (ECDH)** | Uses elliptic curve mathematics instead of prime numbers; smaller keys, same security |
| **Perfect Forward Secrecy (PFS)** | Generates a new random public key for each session; if the current key is compromised, past sessions remain secure |

---

## 5. Cryptographic Attacks

### Algorithm Attacks

#### Known Ciphertext Attack (Ciphertext-Only Attack)
The attacker can observe only the ciphertext. They use **statistical analysis** to find patterns that reveal clues about the plaintext or key. Wireless networks are particularly vulnerable (attacker can capture large ciphertext volumes and inject frames).

**Counter-measures:**
- **Diffusion**: a single plaintext character change propagates into multiple ciphertext character changes.
- **Confusion**: each ciphertext character depends on multiple parts of the key.

#### Downgrade Attack
The attacker forces the system to **abandon its current higher-security protocol** and fall back to an older, weaker one. The attacker then attacks the weaker mode.

Example: forcing TLS 1.3 → TLS 1.0 (known vulnerabilities).

#### Misconfiguration / Implementation Attacks
The most common breach vector: not breaking the algorithm, but exploiting **incorrect configuration**:
- Selecting deprecated algorithms (DES, SHA-1) when stronger options are available.
- Not selecting the strongest available option (choosing SHA-256 when SHA3-512 is one menu item away).

### Collision Attacks

A **collision** occurs when two different inputs produce the same hash digest. Since hash algorithms are used to verify integrity, a collision allows an attacker to substitute a malicious file while the digest matches the legitimate one.

A **collision attack** attempts to find two different inputs that produce the same digest.

#### Birthday Attack

Based on the **birthday paradox**:
- For someone to share *your* birthday (a specific match), ~253 people are needed in a room for 50% probability.
- For *any two people* to share a birthday (any match), only **23 people** are needed.

In hashing: finding *any* two inputs that collide is much easier than finding an input that collides with a *specific* digest. This is because pairs multiply $\binom{n}{2} = \frac{n(n-1)}{2}$ when cross-matched.

**Implication**: longer digests (SHA3-512) dramatically reduce collision probability. Short digests (MD5) are vulnerable to birthday attacks.

### Quantum Cryptographic Defenses

**Quantum computing** uses **qubits** (quantum bits) that can be both 0 and 1 simultaneously (superposition). This allows:
- Parallel computation: one qubit can run two separate calculation streams simultaneously.
- A quantum computer could factor RSA primes using hundreds of atoms in parallel — breaking all current asymmetric cryptography.

**Post-quantum cryptography**: algorithms designed to be secure against quantum computer attacks. Currently being standardized by NIST.

**Quantum Key Distribution (QKD)**:
- Uses single photons (randomly polarized) transmitted over a quantum channel.
- Eavesdropping *physically changes* the photons (Heisenberg uncertainty principle).
- Alice and Bob can detect any interception attempt by comparing their received bit strings.
- If strings are perfectly correlated → no eavesdropper; if imperfect → an eavesdropper is present.

---

## 6. Implementing Cryptography

### Software Encryption

#### File and File System Cryptography

- **Third-party tools**: GNU Privacy Guard (GnuPG), AxCrypt, Folder Lock, VeraCrypt.
- **OS-native**:
  - **Microsoft EFS** (Encrypting File System): integrated with NTFS; files in an encrypted folder are automatically encrypted on write and decrypted on read — transparent to authorized users.
  - **Apple FileVault**: similar function for macOS.

#### Full Disk Encryption (FDE)

Encrypts the entire disk volume — not just individual files.

- **BitLocker** (Windows): encrypts the entire system volume including Windows Registry and temp files. Prevents access by booting an alternate OS or moving the drive to another computer.

### Hardware Encryption

Hardware encryption cannot be exploited like software encryption — it is not subject to software vulnerabilities.

#### Encrypted Hardware USB Drives

- Will not connect to a computer without the correct password.
- All data is automatically encrypted on copy.
- Tamper-resistant external casing.
- Administrators can remotely control, track, disable, or self-destruct the drive.

#### Self-Encrypting Drives (SED)

- Authentication on power-up between drive and host device.
- If authentication fails: deny access or perform **cryptographic erase** (delete decryption keys so data cannot be recovered).
- **Opal**: a Trusted Computing Group (TCG) specification for SEDs ensuring hardware encryption interoperability across vendors.

#### Hardware Security Module (HSM)

An **HSM** is a removable external cryptographic device (USB, expansion card, network server).

Features:
- Onboard true random number generator and key storage.
- Accelerated symmetric and asymmetric encryption.
- Encrypted backup of sensitive material.
- Cannot be compromised by malware (security is hardware-based).

#### Trusted Platform Module (TPM)

A **TPM** is a chip on the computer **motherboard** providing cryptographic services.

Features:
- True random number generator (not PRNG).
- Full asymmetric encryption support (can generate public/private key pairs).
- Boot-time integrity measurement: if system files or data have been altered, the computer will not boot.
- If the hard drive is moved to another computer, the user must enter a recovery password before accessing the volume.

> **HSM vs. TPM**: HSM is **external** (removable); TPM is **internal** (soldered on motherboard).

### Blockchain

A **blockchain** is a shared, immutable (tamper-evident) ledger maintained across multiple computers in a peer-to-peer network.

**Core properties:**
- All parties must give **consensus** before a new transaction is added.
- Once added, transactions cannot be altered without the knowledge of all participants.
- Relies on **SHA-256** hash chaining: each block contains the hash of the previous block, so altering any block invalidates all subsequent blocks.

**Why blockchain matters for cryptography:** Blockchain makes it computationally infeasible to insert or replace a block without the approval of the entire network — demonstrating hash algorithms as a practical tool for distributed trust without a central authority.

> Walmart tracks produce using blockchain. Before: 6 days, 18 hours, 26 minutes to trace a bag of sliced mangoes. After: **2.2 seconds**.

---

## Deep Dive: Symmetric vs. Asymmetric — When to Use Which

The fundamental trade-off is this:

| Dimension | Symmetric | Asymmetric |
|---|---|---|
| Speed | **Much faster** (10–1000× faster) | Slow (computationally expensive) |
| Key management | **Harder**: requires secure out-of-band key exchange | **Easier**: public key is freely distributable |
| Key count | $\frac{n(n-1)}{2}$ keys for $n$ users | $2n$ keys for $n$ users (each user has a key pair) |
| Security basis | Key secrecy | Mathematical hardness (factoring or discrete log) |

**Hybrid cryptography** (used in TLS/HTTPS) combines both:
1. Use **asymmetric cryptography** to securely exchange a symmetric key.
2. Use **symmetric cryptography** for the bulk of the encrypted communication.

This gives you the key distribution security of asymmetric cryptography with the speed of symmetric cryptography.

---

## Key Takeaways & Next Steps

1. **SHA-3 and AES-256** are the current gold standards for hashing and symmetric encryption, respectively.
2. **ECC** is preferred over RSA for mobile and IoT — same security, smaller keys.
3. **Digital signatures** use the private key to sign, public key to verify — the *reverse* of encryption (which uses the public key to encrypt and private key to decrypt).
4. **Downgrade attacks** and **misconfiguration** are far more common than actually breaking an algorithm. Keep algorithms current; configure them correctly.
5. **Post-quantum cryptography** is coming: RSA and DH are vulnerable to quantum factoring. Begin monitoring NIST PQC standards.

---

## Graph View Links

**Previous**: [[Module 3 - Threats and Attacks on Endpoints]]  
**Next**: [[Module 8 - Network Security]]  
**Hub**: [[CS451 - Hub]]
