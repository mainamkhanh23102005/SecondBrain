# Chapter 34 — NP-Completeness

**Source:** Introduction to Algorithms, 4th Edition (CLRS)  
**Tags:** #algorithms #CLRS #NP-completeness #complexity #reductions #P-vs-NP

---

## Executive Summary

Chapter 34 develops the theory of NP-completeness — the formal framework for identifying problems that are *likely* intractable. The central apparatus: define complexity classes P (polynomial-time decidable) and NP (polynomial-time verifiable), establish polynomial-time reductions as the tool for comparing problem hardness, and prove a cascade of NP-completeness results anchored by CIRCUIT-SAT.

**The reduction chain:**
$$\text{CIRCUIT-SAT} \le_P \text{SAT} \le_P \text{3-CNF-SAT} \le_P \text{CLIQUE} \le_P \text{VERTEX-COVER} \le_P \text{HAM-CYCLE} \le_P \text{TSP}$$
$$\text{3-CNF-SAT} \le_P \text{SUBSET-SUM}$$

**Key insight:** P ≠ NP is widely believed but unproven. A proof that any NP-complete problem is in P would show P = NP, resolving the most important open question in computer science.

**Three iconic contrasting pairs:**
| Easy (P) | Hard (NP-complete) |
|----------|--------------------|
| Shortest path | Longest simple path |
| Euler tour | Hamiltonian cycle |
| 2-CNF satisfiability | 3-CNF satisfiability |

---

## Zero-Loss Extraction

### §34.1 — The Class P

**Abstract problem:** A binary relation $Q \subseteq I \times \{0,1\}^*$ on instances $I$. An algorithm *solves* $Q$ if it produces $Q(i)$ for every $i \in I$.

**Encoding:** A function $e : I \to \{0,1\}^*$. Two encodings are *polynomially related* if one can be converted to the other in polynomial time.

**Lemma 34.1:** Whether an abstract problem is polynomial-time solvable is independent of which polynomially related encoding is used.

**Language framework:** A *decision problem* is a language $L \subseteq \{0,1\}^*$. Algorithm $A$ *accepts* $x$ if $A(x) = 1$; *decides* $L$ if $A$ accepts exactly strings in $L$.

$$P = \{L \subseteq \{0,1\}^* : \exists \text{ polynomial-time algorithm deciding } L\}$$

---

### §34.2 — The Class NP

**Verification algorithm:** $A(x, y) = 1$ certifies that $x \in L$, where $y$ is a *certificate* (witness) of polynomial length in $|x|$.

$$NP = \{L : \exists \text{ polynomial-time verification algorithm for } L\}$$

**HAM-CYCLE $\in$ NP:** Certificate = the Hamiltonian cycle (sequence of $|V|$ vertices). Verification checks each vertex appears once and edges exist — $O(V)$.

**Inclusions:** $P \subseteq NP$ (a decider serves as verifier with empty certificate). Whether $P = NP$ is open.

**co-NP:** Languages $L$ such that $\bar{L} \in NP$. Whether $NP = $ co-NP is also open.

---

### §34.3 — NP-Completeness and Reducibility

**Polynomial-time reducibility ($\le_P$):** $L_1 \le_P L_2$ if there exists a polynomial-time computable function $f$ such that $x \in L_1 \iff f(x) \in L_2$.

**Lemma 34.3:** If $L_1 \le_P L_2$ and $L_2 \in P$, then $L_1 \in P$.

**NP-completeness (NPC):** $L$ is NP-complete if (1) $L \in NP$ and (2) $L' \le_P L$ for every $L' \in NP$.

**NP-hard:** Satisfies condition (2) but not necessarily (1).

**Theorem 34.4:** If any NP-complete problem is polynomial-time solvable, then $P = NP$. Equivalently, if any problem in NP is not poly-time solvable, then no NPC problem is.

#### CIRCUIT-SAT is NP-complete

**CIRCUIT-SAT:** $\{\langle C \rangle : C$ is a satisfiable boolean combinational circuit$\}$.

**Lemma 34.5 (CIRCUIT-SAT $\in$ NP):** Certificate = truth assignment to all wires. Verifier checks each gate's output matches its truth table and the circuit output is 1. Linear time.

**Lemma 34.6 (CIRCUIT-SAT is NP-hard):** For any $L \in NP$ with polynomial-time verifier $A$ running in time $T(n) = O(n^k)$:
- Represent $A$'s computation as a sequence of *configurations* (program, PC, input $x$, certificate $y$, working storage).
- A boolean circuit $M$ (implementing the computer hardware) maps each configuration $c_i$ to $c_{i+1}$.
- Construct a circuit $C$ from $T(n)$ copies of $M$ chained together; wire in the known parts of $c_0$ (program, input $x$); leave $y$ as free inputs.
- $C(y) = A(x, y)$, so $C$ is satisfiable $\iff$ $\exists y: A(x,y) = 1$ $\iff$ $x \in L$.
- Circuit size is polynomial in $n$; $F$ runs in polynomial time.

**Theorem 34.7:** CIRCUIT-SAT is NP-complete (by Lemmas 34.5 and 34.6).

---

### §34.4 — NP-Completeness Proofs

**Lemma 34.8 (Reduction methodology):** If $L' \le_P L$ for some $L' \in NPC$, then $L$ is NP-hard. If additionally $L \in NP$, then $L \in NPC$.

**Standard NPC proof recipe:**
1. Show $L \in NP$ (exhibit a polynomial-time verifier and its certificate).
2. Select a known NPC language $L'$.
3. Construct a polynomial-time reduction $f: x \mapsto f(x)$ such that $x \in L' \iff f(x) \in L$.

#### SAT is NP-complete (Theorem 34.9)

**SAT** = $\{\langle \varphi \rangle : \varphi$ is a satisfiable boolean formula$\}$.

- **SAT $\in$ NP:** Certificate = satisfying assignment; verifier evaluates the formula in polynomial time.
- **CIRCUIT-SAT $\le_P$ SAT:** For each wire $x_i$ in circuit $C$, introduce a variable $x_i$. For each gate, add a clause of the form $x_{\text{out}} \leftrightarrow (\text{function of inputs})$. The formula is the AND of the circuit-output variable with all gate clauses. Avoid exponential blowup from fan-out $\ge 2$ by using variables rather than substitution.

#### 3-CNF-SAT is NP-complete (Theorem 34.10)

**3-CNF-SAT** = satisfiable formulas in *conjunctive normal form* with exactly 3 distinct literals per clause.

**SAT $\le_P$ 3-CNF-SAT** (three-step reduction):
1. **Parse tree:** Build a binary parse tree for $\varphi$; introduce auxiliary variable $y_i$ for each internal node's output. Rewrite as $\varphi' = y_{\text{root}} \wedge \bigwedge_i (y_i \leftrightarrow \text{subtree}_i)$. Each clause has $\le 3$ variables.
2. **CNF conversion:** For each clause $C_i$ of $\varphi'$, build its truth table; form a DNF for $\lnot C_i$; negate and apply De Morgan's laws to get a CNF equivalent to $C_i$. Each truth table has $\le 2^3 = 8$ rows, so $\le 8$ CNF clauses per original clause.
3. **Padding to 3 literals:** Introduce auxiliary variables $p, q$. A 2-literal clause $(l_1 \vee l_2)$ becomes $(l_1 \vee l_2 \vee p) \wedge (l_1 \vee l_2 \vee \lnot p)$. A 1-literal clause $l$ becomes 4 clauses using all combinations of $p, q$.

Total size is polynomial in $|\varphi|$; satisfiability is preserved throughout.

---

### §34.5 — NP-Complete Problems

#### §34.5.1 CLIQUE is NP-complete (Theorem 34.11)

**CLIQUE** = $\{\langle G, k\rangle : G$ has a clique of size $k\}$.

- **CLIQUE $\in$ NP:** Certificate = the $k$-vertex subset; verify all $\binom{k}{2}$ pairs have edges.
- **3-CNF-SAT $\le_P$ CLIQUE:** Given $\varphi = C_1 \wedge \cdots \wedge C_k$ with 3 literals per clause:
  - Create a *triple* of vertices $\{v_1^r, v_2^r, v_3^r\}$ for each clause $C_r$.
  - Add edge $(v_i^r, v_j^s)$ iff $r \ne s$ and literals $l_i^r, l_j^s$ are *consistent* (not complementary).
  - $\varphi$ satisfiable $\iff$ $G$ has a clique of size $k$: each satisfying assignment picks one true literal per clause, giving $k$ mutually-consistent vertices forming a clique.

#### §34.5.2 VERTEX-COVER is NP-complete (Theorem 34.12)

**VERTEX-COVER** = $\{\langle G, k\rangle : G$ has a vertex cover of size $k\}$.

- **CLIQUE $\le_P$ VERTEX-COVER:** Given $\langle G, k\rangle$, output $\langle \bar{G}, |V|-k\rangle$ where $\bar{G}$ is the complement graph (edges not in $G$).
- **Key lemma:** $V' \subseteq V$ is a $k$-clique in $G$ $\iff$ $V \setminus V'$ is a vertex cover of size $|V|-k$ in $\bar{G}$.
  - Forward: if $(u,v) \in \bar{E}$, then $(u,v) \notin E$, so at least one of $u,v \notin V'$, hence it's in $V \setminus V'$.
  - Reverse: if $u,v \notin V \setminus V'$ (i.e., $u,v \in V'$), then $(u,v) \notin \bar{E}$, i.e., $(u,v) \in E$ — so $V'$ is a clique.

#### §34.5.3 HAM-CYCLE is NP-complete (Theorem 34.13)

**HAM-CYCLE** = $\{\langle G\rangle : G$ has a Hamiltonian cycle$\}$.

- **VERTEX-COVER $\le_P$ HAM-CYCLE** via a *gadget construction*:
  - For each edge $(u,v) \in E$, introduce a 12-vertex gadget $\Gamma_{uv}$ with exactly 3 possible traversal patterns through the gadget (covering one or both endpoints).
  - Link gadgets for edges incident to the same vertex $u$ into a chain via edges $([u,u^{(i)},6], [u,u^{(i+1)},1])$.
  - Add $k$ selector vertices $s_1,\ldots,s_k$; connect each to the endpoints of each vertex's gadget chain.
  - $G$ has a vertex cover of size $k$ $\iff$ $G'$ has a Hamiltonian cycle: the cycle routes through selector vertices to cover all gadgets corresponding to covered edges.

#### §34.5.4 TSP is NP-complete (Theorem 34.14)

**TSP** = $\{\langle G, c, k\rangle : G$ has a TSP tour with cost $\le k\}$.

- **HAM-CYCLE $\le_P$ TSP:** Given graph $G = (V,E)$, construct complete graph $G' = (V, V \times V)$ with costs:
  $$c(i,j) = \begin{cases} 0 & \text{if } (i,j) \in E \\ 1 & \text{otherwise} \end{cases}$$
  Query instance: $\langle G', c, 0\rangle$. Then $G$ has a Hamiltonian cycle $\iff$ $G'$ has a TSP tour of cost 0 (a cost-0 tour uses only edges in $E$, forming a HC).

#### §34.5.5 SUBSET-SUM is NP-complete (Theorem 34.15)

**SUBSET-SUM** = $\{\langle S, t\rangle : \exists S' \subseteq S$ with $\sum_{s \in S'} s = t\}$.

- **3-CNF-SAT $\le_P$ SUBSET-SUM:** Given $\varphi$ with $n$ variables $x_1,\ldots,x_n$ and $k$ clauses $C_1,\ldots,C_k$:
  - Each number in $S$ has $n+k$ digits (base 10). The $n$ most-significant digit positions correspond to variables; the $k$ least-significant correspond to clauses.
  - For each variable $x_i$: add $v_i$ (with 1 in position $i$, and 1 in clause positions where $x_i$ appears) and $\bar{v}_i$ (with 1 in position $i$, and 1 in clause positions where $\lnot x_i$ appears).
  - For each clause $C_j$: add slack variables $s_j$ (1 in clause position $j$) and $\bar{s}_j$ (2 in clause position $j$).
  - Target $t$: 1 in each variable digit, 4 in each clause digit.
  - Base 10 prevents carries (max digit sum per position = 6). A subset sums to $t$ $\iff$ $\varphi$ is satisfiable: choosing $v_i$ or $\bar{v}_i$ per variable sets each variable position to 1, and satisfying each clause gives 1–3 contribution to its digit (padded to 4 using $s_j, \bar{s}_j$).

---

## Deep-Dive Explanations

### The Computational-History Reduction (NP-Hardness of CIRCUIT-SAT)

The proof of Lemma 34.6 is the conceptual core of complexity theory. The key move: a computation is *physical* — it runs on hardware, and hardware is a circuit. An algorithm $A$ running for $T(n)$ steps produces a sequence of configurations $c_0, c_1, \ldots, c_{T(n)}$. Each transition $c_i \to c_{i+1}$ is computed by a fixed circuit $M$. Chaining $T(n)$ copies of $M$ gives a circuit $C$ computing the entire run. The certificate $y$ is the only free input; wiring in all known values reduces ACCEPTANCE to CIRCUIT-SATISFIABILITY.

### Why Reduction Direction Matters

When proving $L \in NPC$, reduce *from* a known NPC problem *to* $L$ (i.e., $L' \le_P L$). This shows $L$ is at least as hard as $L'$. The common mistake is reducing in the wrong direction — showing $L \le_P L'$ only proves $L$ is easier than $L'$, not harder.

### The Complement Trick (CLIQUE $\to$ VERTEX-COVER)

The complement graph transformation is elegant: edges present in $G$ become absent in $\bar{G}$ and vice versa. A clique (all pairs connected) in $G$ becomes an independent set (no pairs connected) in $\bar{G}$. The complement of an independent set is a vertex cover. This one algebraic duality connects two seemingly unrelated optimization problems.

---

## Key Takeaways & Next Steps

| Problem | NPC via reduction from | Key structural insight |
|---------|----------------------|----------------------|
| CIRCUIT-SAT | (direct, from all of NP) | Computation = circuit; NP verifier → polynomial-size circuit |
| SAT | CIRCUIT-SAT | Variable per wire; gate = biconditional clause |
| 3-CNF-SAT | SAT | Parse tree → clause form → pad to 3 literals |
| CLIQUE | 3-CNF-SAT | Clause → vertex triple; consistency → edges |
| VERTEX-COVER | CLIQUE | Complement graph; clique complement = vertex cover |
| HAM-CYCLE | VERTEX-COVER | Gadget construction enforcing cover-path structure |
| TSP | HAM-CYCLE | Cost 0/1 on edges; HC ↔ cost-0 tour |
| SUBSET-SUM | 3-CNF-SAT | Base-10 encoding; variables → digits; clauses → slack |

**Key principles:**
1. Proving $L \in NPC$ requires both $L \in NP$ (certificate + verifier) and NP-hardness ($L' \le_P L$ from known NPC $L'$).
2. Reductions preserve satisfiability/feasibility, not structure — the transformed instance looks completely different.
3. No polynomial-time algorithm for any NP-complete problem is known. NPC status is the standard evidence for intractability.
4. When you cannot solve a problem optimally, consider: approximation algorithms (Chapter 35), parameterized complexity, or special-case restrictions.

**Next steps:**
- Chapter 35: Approximation algorithms — how to get near-optimal solutions for NP-hard problems in polynomial time.
- PCP theorem: inapproximability results (some NP-hard problems cannot be approximated within any constant factor unless P = NP).
- Fixed-parameter tractability: algorithms running in $O(f(k) \cdot n^c)$ for parameter $k$.

---

### Navigation

**Previous:** [[Ch33_Machine_Learning_Algorithms]]  
**Next:** [[Ch35_Approximation_Algorithms]]  
**Hub:** [[Index_Introduction_to_Algorithms]]
