# Exam Study — Cryptography and Applications

**Source PDF:** Cryptography_and_Applications.pdf — CS526 Lecture Slides  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #cryptography #symmetric #asymmetric #hash #JWT #PKI #TLS #OpenSSL

---

## Executive Summary

Cryptography is the science of transforming information so only authorized parties can read it. This document covers the **goals** of cryptography, the distinction between **steganography and cryptography**, classical and modern **cipher types**, the three algorithm families (**hash, symmetric, asymmetric**), real-world protocols (**MAC, HMAC, JWT, digital signatures, SSH, PKI, TLS/SSL, ACME**), and **attacks** on cryptographic systems. The key insight is that modern cryptography is a **hybrid system**: asymmetric cryptography solves the key exchange problem, while symmetric cryptography provides the speed for bulk data encryption.

---

## 1. Goals of Cryptography

Cryptography provides five fundamental security services:

| Goal | What It Provides |
|---|---|
| **Confidentiality** | Only authorized parties can read the data — eavesdroppers get unreadable ciphertext |
| **Integrity** | Data has not been altered — any modification is detectable |
| **Authentication** | Proof of the sender's identity — verify who you're communicating with |
| **Non-repudiation** | The sender cannot later deny having sent the message |
| **Availability** | (via access control mechanisms integrated with crypto) authorized users can access what they need |

---

## 2. Steganography vs. Cryptography

| Technique | Goal | Mechanism |
|---|---|---|
| **Steganography** | Hides the **existence** of data | Embeds data inside cover files (images, audio, video) — the message is invisible |
| **Cryptography** | Hides the **meaning** of data | Mathematically transforms plaintext into unreadable ciphertext — the message is visible but unreadable |

> Both can be combined for **double protection**: encrypt first, then hide steganographically. An attacker must both *find* the hidden data and then *decrypt* it.

---

## 3. Terminology

| Term | Definition |
|---|---|
| **Plaintext** | Unencrypted data — the original, readable message |
| **Ciphertext** | The scrambled, unreadable output of encryption |
| **Cleartext** | Unencrypted data not intended to be encrypted (transmitted "in the clear") |
| **Encryption** | Converting plaintext → ciphertext using an algorithm and key |
| **Decryption** | Converting ciphertext → plaintext using an algorithm and key |
| **Algorithm (Cipher)** | A set of procedures based on a mathematical formula for encryption/decryption |
| **Key** | The mathematical value input into the algorithm — must be kept secret |

> **Core principle**: security comes from the secrecy of the **key**, NOT the secrecy of the **algorithm**. Algorithms are public and standardized (Kerckhoffs's principle). Proprietary "secret" algorithms are suspect because they have not been publicly vetted.

---

## 4. Cipher Types

### By Operation on Data

| Type | How It Works | Security Level |
|---|---|---|
| **Stream cipher** | Processes one character/bit at a time | Less secure — only plaintext changes; generating engine repeats |
| **Block cipher** | Processes an entire block (8–16 bytes) at once; blocks can be randomized | More secure — cipher resets after each block; more random output |
| **Sponge function** | Absorbs input of any length; outputs a string of any requested length | Used in SHA-3; flexible in/out lengths |

### Classical Ciphers

| Cipher | Mechanism | Example |
|---|---|---|
| **Shift cipher (Caesar)** | Shifts each letter by a fixed number | A+3 = D, B+3 = E |
| **Substitution cipher** | Replaces each letter with a fixed different letter | A→M, B→N |
| **ROT13** | Shifts alphabet 13 positions — applying twice returns original | `security` → `frphevgl` |

### Adversarial Models

| Model | What the Attacker Can Do |
|---|---|
| **Ciphertext-only** | Can observe only ciphertext; uses statistical analysis |
| **Known-plaintext** | Has some plaintext–ciphertext pairs |
| **Chosen-plaintext** | Can get encryption of any message they choose |
| **Chosen-ciphertext** | Can get decryption of any ciphertext they choose |

> **Kerckhoffs's principle**: security of a cipher must depend ONLY on the secrecy of the key. Assume the attacker knows the algorithm.

> **Shannon's principle**: perfect secrecy is achievable only with a key at least as long as the message (One-Time Pad).

### XOR Cipher

XOR (eXclusive OR) is the fundamental operation in many modern ciphers:

| Bit A | Bit B | A XOR B |
|---|---|---|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

Rule: same bits → 0; different bits → 1.

**Self-inverting**: `(A XOR K) XOR K = A` — encrypting with K then encrypting again with K returns original.

**Example**: `s` (01110011) XOR `f` (01100110) = 00010101

### One-Time Pad (OTP)

The **only theoretically unbreakable cipher** — proven by Shannon (1949).

**Requirements for perfect secrecy:**
1. The key must be **truly random** (not PRNG).
2. The key must be **at least as long as the message**.
3. The key must be used **exactly once**.
4. The key must be **kept completely secret**.

| Plaintext | Position | Pad | Position | Calculation | Result |
|---|---|---|---|---|---|
| S | 19 | C | 3 | 19+3−1=21 | U |
| E | 5 | B | 2 | 5+2−1=6 | F |
| C | 3 | Y | 25 | 3+25−1=1 | A |

**Why OTP is impractical**: the key is as long as the message, and distributing it securely is as hard as distributing the message itself.

### Notation for Symmetric Cryptography

A symmetric encryption scheme = three algorithms:
- **Gen()** → outputs key $k$
- **Enc(k, m)** → outputs ciphertext $c$
- **Dec(k, c)** → outputs plaintext $m$

**Correctness requirement**: $\text{Dec}(k, \text{Enc}(k, m)) = m$ for all keys $k$ and messages $m$.

---

## 5. Stream Ciphers

A stream cipher generates a **keystream** (pseudo-random sequence of bits) and XORs it with the plaintext:

$$c_i = m_i \oplus k_i$$

| Cipher | Notes | Status |
|---|---|---|
| **RC4** | 40–128 bits; used in WEP (Wi-Fi) and SSL/TLS (deprecated); very fast | Broken — statistical biases in keystream; WEP cracked using RC4 weakness |
| **DVD Content Scrambling System (CSS)** | Used to protect DVD content; 40-bit key | Broken |

> **Critical weakness of stream ciphers**: if the same key is used twice with different messages, XORing the two ciphertexts reveals information about both plaintexts.

---

## 6. Block Ciphers

A block cipher divides the message into fixed-size blocks and encrypts each block using the key.

### Block Cipher Modes

**ECB (Electronic CodeBook) Mode:**
- Each block is encrypted independently with the same key.
- **Critical flaw**: identical plaintext blocks produce identical ciphertext blocks → patterns in the plaintext are visible in the ciphertext.
- **Not secure for most use cases**.

**CBC (Cipher Block Chaining) Mode:**
- Each plaintext block is XORed with the **previous ciphertext block** before encryption.
- The first block is XORed with an **Initialization Vector (IV)** — a random value.
- **Result**: identical plaintext blocks produce different ciphertext blocks.

$$C_i = E_K(P_i \oplus C_{i-1}) \quad \text{where } C_0 = IV$$

### Common Block Cipher Algorithms

| Algorithm | Key Size | Block Size | Status | Notes |
|---|---|---|---|---|
| **DES** (Data Encryption Standard) | 56 bits | 64 bits | **Deprecated** | First widely deployed; 56-bit key brute-forceable; broken 1999 |
| **3DES** (Triple DES) | 112 or 168 bits | 64 bits | **Deprecated** | 3 DES passes × 16 rounds each = 48 total iterations |
| **AES** (Advanced Encryption Standard) | 128, 192, 256 bits | 128 bits | **Current standard** | Replaced DES; rounds: 128-bit→9, 192-bit→11, 256-bit→13; no successful attacks |
| **Blowfish** | 32–448 bits | 64 bits | Strong | No significant weaknesses |
| **Twofish** | Up to 256 bits | 128 bits | Strong | Derived from Blowfish |

**How 3DES works:**
```
Plaintext → Encrypt(Key1) → Ciphertext1 → Encrypt(Key2) → Ciphertext2 → Encrypt(Key3) → Final
```
3 keys × 16 rounds = 48 total encryption iterations.

---

## 7. Hash Functions

A **hash function** (also: message digest function) takes an input of any length and produces a **fixed-length output** called a **digest** (or **hash value**).

**Formal notation**: $H(m) = h$ where $h$ is the digest.

### Properties of a Cryptographic Hash Function

| Property | Formal Name | Definition |
|---|---|---|
| **Fixed output size** | — | Any input length produces the same-length digest |
| **One-way (pre-image resistance)** | Pre-image resistance | Given $h$, it is computationally infeasible to find $m$ such that $H(m) = h$ |
| **Second pre-image resistance** | — | Given $m_1$, it is computationally infeasible to find $m_2 \neq m_1$ such that $H(m_1) = H(m_2)$ |
| **Collision resistance** | Collision resistance | It is computationally infeasible to find any two different inputs $m_1, m_2$ such that $H(m_1) = H(m_2)$ |
| **Avalanche effect** | — | A single bit change in input produces completely different digest |

> Hash functions are **one-way** — designed for verification, not encryption. You cannot derive the original message from a digest.

### Common Hash Algorithms

| Algorithm | Digest Size | Status | Notes |
|---|---|---|---|
| **MD5** | 128 bits | **Broken** | Collisions found; do not use for security |
| **SHA-1** | 160 bits | **Broken** | Google found collision in 2017; deprecated |
| **SHA-256** | 256 bits | Secure | SHA-2 family; current standard |
| **SHA-384** | 384 bits | Secure | SHA-2 family |
| **SHA-512** | 512 bits | Secure | SHA-2 family |
| **SHA-3** | Variable | Secure | Announced 2015; uses sponge function; designed dissimilar to SHA-2 |
| **RIPEMD-160** | 160 bits | Secure | Uses two parallel independent computation chains combined at end |

**Sample digests for "Cengage":**

| Algorithm | Digest |
|---|---|
| MD5 | 7e169c6f44088e315c7b1f6513c1b0f7 |
| SHA-256 | f6c8a86bf6a5128cbaf2ad251b0beaa3604c11c51587de518737537800098d76 |
| RIPEMD-160 | dd52a79bce64a1d145b51ce639e0dadda976516d |

---

## 8. Message Authentication Code (MAC)

A **MAC** provides both **integrity** and **authentication** for a message.

**How it works:**
- Sender computes: $MAC = \text{MAC\_Algorithm}(K, M)$
- Sender sends: $(M, MAC)$
- Receiver recomputes MAC using the same key and compares.
- If MAC matches → message is authentic and unmodified.

**Key property**: requires a **shared secret key** between sender and receiver. An attacker without the key cannot forge a valid MAC.

### HMAC (Hash-based Message Authentication Code)

**HMAC** is the most widely used MAC construction, using a cryptographic hash function internally.

**HMAC formula:**

$$\text{HMAC}(K, m) = H\big((K' \oplus opad) \| H((K' \oplus ipad) \| m)\big)$$

Where:
- $K'$ = key padded/truncated to the hash's block size
- $opad$ = outer padding: `0x5c5c5c...5c` (64 bytes)
- $ipad$ = inner padding: `0x363636...36` (64 bytes)
- $\|$ = concatenation

**Simplified description**: HMAC applies the hash function **twice** — once to the message with the inner pad, and once more to that result with the outer pad.

**Why double hashing?** Prevents **length extension attacks** that would be possible with a simple $H(K \| m)$ construction.

---

## 9. JWT (JSON Web Token)

A **JWT** is a compact, URL-safe token for transmitting claims between parties. Widely used for **authentication and authorization** in web applications.

### Structure

A JWT consists of three Base64URL-encoded parts separated by dots:

```
Header.Payload.Signature
```

**Example:**
```
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c
```

| Part | Content | Example (decoded) |
|---|---|---|
| **Header** | Algorithm and token type | `{"alg": "HS256", "typ": "JWT"}` |
| **Payload** | Claims (user data, permissions) | `{"sub": "1234567890", "name": "John Doe", "iat": 1516239022}` |
| **Signature** | HMAC of encoded header + payload | Computed and verified by server |

### JWT Claims

| Claim | Type | Description |
|---|---|---|
| `iss` | Registered | Issuer — who issued the token |
| `sub` | Registered | Subject — who the token is about |
| `aud` | Registered | Audience — who the token is intended for |
| `exp` | Registered | Expiration time |
| `iat` | Registered | Issued-at time |
| `name`, `role`, etc. | Custom | Application-specific claims |

### Signature Computation (HMAC-SHA256)

```
signature = HMACSHA256(
  base64UrlEncode(header) + "." + base64UrlEncode(payload),
  secret
)
```

**Verification flow:**
1. Server receives JWT.
2. Server recomputes the signature using the stored secret.
3. If the computed signature matches the token's signature → token is authentic and unmodified.
4. Server checks `exp` claim to ensure token has not expired.

**Security note**: JWTs are **not encrypted by default** — the payload is only Base64-encoded (not secret). Use JWE (JSON Web Encryption) if the payload must be confidential.

---

## 10. Asymmetric (Public Key) Cryptography

**Asymmetric cryptography** uses **two mathematically related keys**:
- **Public key**: freely distributed; anyone can have it.
- **Private key**: known only to the owner; never shared.

### Key Usage Reference

| Operation | Whose Key | Which Key | Purpose |
|---|---|---|---|
| **Encrypt for Alice** | Alice's | Public key | Only Alice can decrypt |
| **Alice decrypts** | Alice's | Private key | Reverses encryption |
| **Bob signs (digital signature)** | Bob's | **Private key** | Proves Bob authored it |
| **Alice verifies Bob's signature** | Bob's | **Public key** | Confirms authenticity |

**Memory rule:**
- **Encrypt** → use recipient's **public** key
- **Sign** → use sender's **private** key
- Verify → use sender's **public** key
- Decrypt → use your own **private** key

### Real-World Hybrid Approach

Asymmetric cryptography is **much slower** than symmetric. Modern systems use a **hybrid approach**:

```
Step 1: Use asymmetric crypto to securely exchange a symmetric session key.
Step 2: Use symmetric crypto (AES) for all actual data encryption.
```

**Why hybrid?**
- Asymmetric solves the **key distribution problem** (no secure channel needed to share the symmetric key).
- Symmetric provides **speed** for bulk data encryption.
- Best of both worlds.

### RSA Algorithm

RSA (1977) relies on the computational difficulty of **factoring the product of two large prime numbers**.

**Key generation (simplified with small numbers):**

1. Choose two primes: $p = 7,\ q = 19$
2. Compute: $n = p \times q = 133$
3. Compute: $m = (p-1)(q-1) = 6 \times 18 = 108$
4. Find $e$ coprime to $m$: $e = 5$ (since $\gcd(5, 108) = 1$)
5. Find $d$: $d = \frac{1 + n \cdot m}{e} = \frac{14364}{5} \approx 2873$

- **Public key**: $(n = 133,\ e = 5)$
- **Private key**: $(n = 133,\ d = 2873)$

In practice, $p$ and $q$ are **1,024-bit or larger primes** — factoring is computationally infeasible with classical computers.

### Elliptic Curve Cryptography (ECC)

ECC uses the mathematical difficulty of the **elliptic curve discrete logarithm problem** instead of integer factorization.

An elliptic curve: $y^2 = x^3 + ax + b$ — adding two points on the curve produces a third point.

**ECC vs RSA key equivalents:**

| RSA Key (bits) | ECC Key (bits) | Security Level |
|---|---|---|
| 1,024 | 160 | Low |
| 2,048 | 224 | Medium |
| 3,072 | 256 | High |
| 7,680 | 384 | Very High |
| 15,360 | 521 | Maximum |

> **ECC provides equivalent security with ~6× smaller keys** → faster computation + lower power consumption → ideal for mobile devices and IoT.

### HMAC vs. Digital Signature Comparison

| Feature | HMAC | Digital Signature |
|---|---|---|
| **Algorithm type** | Symmetric (shared secret key) | Asymmetric (public/private key pair) |
| **Authentication** | Requires shared secret | Anyone can verify using public key |
| **Non-repudiation** | No (both parties have the key) | **Yes** (only private key holder can sign) |
| **Speed** | Fast | Slower |
| **Use case** | Verifying data between trusted parties | Public verification, legal signing |

---

## 11. Digital Signatures

A **digital signature** is an electronic verification of the sender that provides:
1. **Sender verification** — confirms who sent the message.
2. **Non-repudiation** — sender cannot deny having signed.
3. **Integrity** — message has not been modified since signing.

### How Digital Signatures Work

**Signing process (Bob sends to Alice):**

```
Step 1: Bob creates a message.
Step 2: Bob hashes the message → produces digest D.
Step 3: Bob encrypts D with his PRIVATE KEY → this is the digital signature S.
Step 4: Bob sends (message + S) to Alice.
```

**Verification process (Alice receives):**

```
Step 5: Alice decrypts S using Bob's PUBLIC KEY → recovers digest D'.
         (If decryption fails → message did not come from Bob.)
Step 6: Alice hashes the received message with the same algorithm → produces D''.
Step 7: Compare D' with D''.
         If D' == D'' → message is authentic and unmodified ✓
         If D' ≠ D'' → message was tampered with ✗
```

**Critical note**: digital signatures do **NOT encrypt the message itself**. They only sign the hash. If confidentiality is also needed, Bob must additionally encrypt with Alice's public key.

---

## 12. Key Exchange Protocols

| Protocol | Description | Properties |
|---|---|---|
| **Diffie-Hellman (DH)** | Alice and Bob agree on public parameters; independently compute the same shared secret | Classic; same key for all sessions |
| **Diffie-Hellman Ephemeral (DHE)** | Same as DH but uses **different (ephemeral) keys per session**; keys discarded after use | Enables **Perfect Forward Secrecy** |
| **Elliptic Curve DH (ECDH)** | DH using elliptic curve math; smaller keys, same security | More efficient |
| **Perfect Forward Secrecy (PFS)** | A new random key generated per session; compromise of current key does not expose past sessions | Critical property for long-term security |

---

## 13. SSH Authentication

**SSH (Secure Shell)** provides encrypted remote access. SSH supports two authentication methods:

**Password-based:** username + password over encrypted channel.

**Public key-based (more secure):**

```
Client side: generate key pair (public + private)
Client: send public key to server (stored in ~/.ssh/authorized_keys)
Authentication:
  1. Server generates a random challenge.
  2. Client encrypts challenge with private key (signs it).
  3. Server decrypts with client's stored public key.
  4. If decryption succeeds → client is authenticated.
```

> Public key SSH authentication eliminates the risk of password sniffing or brute-forcing.

---

## 14. Public Key Infrastructure (PKI)

**PKI** is the system of hardware, software, policies, and standards that manages **digital certificates** and **public key encryption**.

### Digital Certificate

A **digital certificate** binds a **public key** to an **identity** (person, server, organization).

**Standard format: X.509**

A certificate contains:
- Subject's identity (Common Name, Organization, Country)
- Subject's public key
- **Issuer** (Certificate Authority — CA)
- Validity period (Not Before / Not After)
- Serial number
- CA's digital signature (what makes it trustworthy)

### Certificate Authority (CA)

A **CA** is a trusted third party that:
1. Verifies the identity of the certificate requester.
2. Issues a signed digital certificate binding the identity to the public key.
3. Maintains a **Certificate Revocation List (CRL)** of invalid/revoked certificates.

**Certificate chain of trust:**
- **Root CA** → signs **Intermediate CA** certificates → Intermediate CA signs **end-entity certificates**.
- Root CAs are self-signed and trusted by default in OS/browser trust stores.

### Certificate Operations (OpenSSL Commands)

```bash
# Generate RSA private key (2048-bit)
openssl genrsa -out private.key 2048

# Generate Certificate Signing Request (CSR)
openssl req -new -key private.key -out request.csr

# View CSR contents
openssl req -text -in request.csr

# Sign certificate with CA (CA signs the CSR)
openssl ca -in request.csr -out certificate.crt

# View certificate contents
openssl x509 -text -in certificate.crt

# Generate self-signed certificate (for testing)
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365
```

### Certificate Issuance Procedure

1. **Applicant** generates a key pair.
2. **Applicant** creates a **CSR (Certificate Signing Request)** containing: public key + identity information.
3. **CA** verifies the applicant's identity (DV: domain validation; OV: organization validation; EV: extended validation).
4. **CA** signs the CSR, producing a **digital certificate**.
5. **CA** returns the certificate to the applicant.
6. Applicant deploys the certificate on their server.
7. Clients verify the certificate by checking the CA's signature against the trusted root in their browser/OS.

### ACME Protocol

**ACME (Automatic Certificate Management Environment)** is a protocol for **automated certificate issuance and renewal** — used by **Let's Encrypt** (free CA).

**How ACME works:**
1. Client requests certificate from ACME server (CA).
2. ACME server issues a **challenge** (e.g., "place this token at `http://yourdomain.com/.well-known/acme-challenge/TOKEN`").
3. Client completes the challenge (proves domain control).
4. ACME server verifies the challenge.
5. CA issues the certificate to the client.
6. Certificate is automatically renewed before expiry.

> ACME enables **zero-cost, fully automated** HTTPS certificate management — eliminating the main friction of deploying TLS.

---

## 15. SSL/TLS and the Handshake

**TLS (Transport Layer Security)** provides encrypted communication between a client and server. It is the cryptographic backbone of HTTPS.

### TLS Handshake (simplified)

```
Client                              Server
  |                                   |
  |-- ClientHello (cipher suites) --> |
  |                                   |
  | <-- ServerHello (chosen cipher) --|
  | <-- Server Certificate ----------|
  | <-- ServerHelloDone -------------|
  |                                   |
  |-- ClientKeyExchange (pre-master secret, encrypted with server's public key) -->|
  |-- ChangeCipherSpec -------------> |
  |-- Finished (encrypted) ---------> |
  |                                   |
  | <-- ChangeCipherSpec ------------|
  | <-- Finished (encrypted) --------|
  |                                   |
  |===== Encrypted Application Data ==|
```

**What TLS provides:**
- **Confidentiality**: data encrypted with symmetric key (AES) negotiated during handshake.
- **Integrity**: MAC on every record.
- **Authentication**: server identity verified via certificate + CA trust chain.

---

## 16. Cryptographic Attacks

### Algorithm Attacks

| Attack | Description | Defense |
|---|---|---|
| **Ciphertext-only (known-ciphertext)** | Attacker observes only ciphertext; uses statistical analysis to find patterns | **Diffusion** (1 plaintext bit change → many ciphertext bit changes); **Confusion** (each ciphertext bit depends on many key bits) |
| **Downgrade attack** | Forces system to abandon its strong current protocol and fall back to an older, weaker one | Disable support for weak protocol versions; enforce TLS 1.2+ minimum |
| **Frequency analysis** | Exploits letter/word frequency patterns in substitution ciphers | Block ciphers with proper modes (CBC); modern ciphers resist this |

### Collision Attacks

A **collision** occurs when two different inputs produce the same hash digest.

**Birthday attack** exploits the **birthday paradox**:
- Finding any two inputs that collide is **much easier** than finding an input that collides with a *specific* target digest.
- The number of input pairs grows as $\binom{n}{2} = \frac{n(n-1)}{2}$.
- **For a 128-bit digest (MD5)**: only $2^{64}$ operations needed (vs. $2^{128}$ naively expected).
- **For a 256-bit digest (SHA-256)**: $2^{128}$ operations needed — computationally infeasible.

**Implication**: longer digests dramatically reduce collision probability. MD5 and SHA-1 are vulnerable to birthday attacks and **must not be used for security**.

### Quantum Computing Threat

- **Quantum computers** use **qubits** that can be both 0 and 1 simultaneously (superposition).
- This allows parallel computation on all possible values simultaneously.
- **Shor's algorithm** on a quantum computer can factor RSA primes efficiently → breaks RSA and DH.
- **Grover's algorithm** halves the effective key length of symmetric algorithms → AES-256 becomes effectively AES-128 strength against quantum.

**Post-quantum defenses:**
- **Post-quantum cryptography (PQC)**: algorithms based on problems quantum computers cannot efficiently solve (lattice-based, hash-based, code-based). NIST is standardizing these now.
- **Quantum Key Distribution (QKD)**: uses single photons — any eavesdropping physically disturbs the photons (Heisenberg uncertainty principle), making interception detectable.

---

## Deep Dive: Symmetric vs. Asymmetric — The Fundamental Trade-off

| Dimension | Symmetric | Asymmetric |
|---|---|---|
| Speed | **10–1000× faster** | Slow (computationally expensive) |
| Key management | Hard — requires secure key exchange | **Easy** — public key is freely distributable |
| Key count for $n$ users | $\frac{n(n-1)}{2}$ shared keys | $2n$ keys (each user has one key pair) |
| Security basis | Key secrecy | Mathematical hardness (factoring or discrete log) |
| Non-repudiation | No | **Yes** (only private key holder can sign) |

**For 10 users, symmetric requires $\frac{10 \times 9}{2} = 45$ secret keys** — each pair must share a unique key. Asymmetric requires only $10 \times 2 = 20$ keys total.

**Why hybrid encryption is universally used:**
1. **Problem with pure asymmetric**: too slow for bulk data.
2. **Problem with pure symmetric**: how do you securely exchange the initial key?
3. **Solution**: use asymmetric to securely exchange a symmetric key, then use symmetric for everything else.

---

## Key Takeaways for the Exam

1. **Cryptography hides meaning; steganography hides existence.**
2. **OTP** = theoretically unbreakable, but impractical (key = message length, used once only).
3. **ECB mode** is insecure (identical blocks → identical ciphertext). **CBC** is secure (IV + chaining).
4. **Hash functions** are one-way: MD5/SHA-1 are **broken**; use SHA-256 or SHA-3.
5. **HMAC**: $H((K \oplus opad) \| H((K \oplus ipad) \| m))$ — double hash for MAC authenticity.
6. **JWT**: Header.Payload.Signature — Base64URL-encoded; Signature = HMACSHA256(header + "." + payload, secret).
7. **Encrypt** with recipient's **public key**; **Sign** with sender's **private key**.
8. **RSA** = based on factoring; **ECC** = based on elliptic curve discrete log; ECC gives equivalent security with ~6× smaller keys.
9. **Digital signatures**: sign hash with private key; verify with public key; does NOT encrypt the message.
10. **PKI**: CA signs certificates binding public key to identity; ACME automates certificate issuance.
11. **Birthday attack**: collisions found in $O(2^{n/2})$ operations (not $O(2^n)$) — use long digests.
12. **Hybrid encryption**: asymmetric for key exchange + symmetric for bulk data.
13. **Downgrade attack**: force a weaker protocol version; mitigated by disabling old protocol versions.

---

## Knowledge Check Q&A

**Q1**: What is the difference between a stream cipher and a block cipher?  
**A**: Stream ciphers process one bit/character at a time; block ciphers process a fixed-size block (8–16 bytes) at once. Block ciphers are generally more secure because the cipher resets after each block and produces more random output.

**Q2**: Why is ECB mode insecure?  
**A**: Each block is encrypted independently with the same key, so identical plaintext blocks produce identical ciphertext blocks — patterns in the plaintext are visible in the ciphertext.

**Q3**: What is HMAC and why is the double-hash construction used?  
**A**: HMAC is a MAC using a cryptographic hash with a secret key: $H((K \oplus opad) \| H((K \oplus ipad) \| m))$. The double hash prevents length extension attacks that would be possible with a simple $H(K \| m)$.

**Q4**: What is the structure of a JWT?  
**A**: Header.Payload.Signature — all three parts are Base64URL-encoded and separated by dots. The signature is HMACSHA256 of the encoded header + "." + encoded payload using a secret key.

**Q5**: When do you encrypt with a public key vs. a private key?  
**A**: Use the **recipient's public key** to encrypt a message (only the recipient's private key can decrypt). Use your own **private key** to sign a message (anyone with your public key can verify the signature).

**Q6**: What is a birthday attack?  
**A**: An attack exploiting the birthday paradox — finding any collision between two inputs is much easier than finding an input that collides with a specific target. For an $n$-bit digest, only $O(2^{n/2})$ operations are needed.

---

## Graph View Links

**Previous**: [[Module 3 - Threats and Attacks on Endpoints]]  
**Next**: [[Module 8 - Network Security]]  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 6 - Basic Cryptography]]
