# C++ OOP & Data Structures — Final Exam Hub (Troy K69, CK-20252)

**Textbook:** *Starting Out with C++: From Control Structures through Objects* — Tony Gaddis
**Course:** OOP & Data Structures in C++ (Troy program, K69)
**Exam format:** Oral exam (vấn đáp). Each student draws **1 of 6 topics**, gets **5 minutes to prepare**, then **4–5 minutes to answer in English**. You must explain like a professor: clear, confident, and able to defend the design choices.
**Tags:** #cpp #oop #datastructures #exam #oral #TroyK69

---

## How to Use These Notes

Each of the 6 topic notes is a self-contained "exam package" built to the `Master_Synthesizer` framework:

1. **🎤 Professor's Opening** — a ~30-second spoken script you can deliver verbatim the moment you draw the topic.
2. **Executive Summary** — the one-paragraph core idea.
3. **Zero-Loss Extraction** — the exact source code, the decoded "mystery functions", and verified program output.
4. **Deep-Dive Explanations** — the *why*: design trade-offs, complexity, and the pitfalls examiners probe.
5. **Likely Follow-up Questions** — the oral questions the examiner is most likely to ask, with model answers.

> [!tip] Exam strategy
> In an oral exam, **structure beats volume**. Always answer in three beats: **(1) define the concept**, **(2) explain *why* it exists / what problem it solves**, **(3) give a concrete example from the code**. The examiner is testing whether you *understand*, not whether you memorised.

---

## The 6 Topics

| # | Topic | Core Concept | What the "mystery functions" really are |
|---|---|---|---|
| 1 | [[Exam Study - Topic 1 (Operator Overloading, Object Conversion)\|Operator Overloading & Object Conversion]] | Giving operators new meaning for user-defined types | `operator==`, friend scalar-add, `operator double()` conversion, `operator<<`, reference-returning accessor |
| 2 | [[Exam Study - Topic 2 (Inheritance, Polymorphism)\|Inheritance & Polymorphism]] | One interface, many forms via `virtual` + base pointers | Array of base pointers (`GradedActivity**`) with dynamic dispatch |
| 3 | [[Exam Study - Topic 3 (Exception Handling)\|Exception Handling]] | Separating error detection from error handling via `try`/`catch`/`throw` | Specific-catch with auto-recovery + catch-all `catch(...)` |
| 4 | [[Exam Study - Topic 4 (Linked List)\|Linked List]] | Dynamic node-based sequence with pointer surgery | Recursive count, recursive reverse-print, iterative in-place reverse |
| 5 | [[Exam Study - Topic 5 (Queue)\|Queue (Circular Array)]] | FIFO with wrap-around modular indexing | Count occurrences, in-place reverse, enqueue-at-front |
| 6 | [[Exam Study - Topic 6 (Stack)\|Stack (Array)]] | LIFO with a single `top` index | Count evens, remove-from-bottom, remove k-th from top |

---

## Cross-Cutting Themes (the examiner's favourite traps)

These ideas appear across multiple topics — knowing them lets you sound like a professor no matter which topic you draw.

- **The Rule of Three.** Any class managing a raw pointer (`Stack`, `Queue`) needs a **destructor**, **copy constructor**, and **copy assignment operator**. The textbook classes provide the first two — be ready to explain *why* the default shallow copy would be catastrophic (two objects sharing one array → double `delete`).
- **`virtual` and dynamic dispatch.** A call through a base pointer/reference only picks the derived version *if the function is `virtual`*. This single keyword is the entire mechanism behind polymorphism (Topic 2) and is the reason a base class should have a **virtual destructor**.
- **Ownership & memory.** `new` must be balanced by `delete`; `new[]` by `delete[]`. Mismatching them, or forgetting them, is undefined behaviour or a leak. Linked lists, stacks, and queues all hinge on this.
- **Modular arithmetic for circular buffers.** `index = (index + 1) % size` is the trick that turns a fixed array into a ring (Topic 5). Understand *why* the `+ size` is needed when moving backwards.
- **Complexity vocabulary.** Be able to state $O(1)$ vs $O(n)$ for every operation. Stack push/pop and queue enqueue/dequeue are $O(1)$; searching or reversing is $O(n)$.

---

## Graph View Links

**Start here**: [[Exam Study - Topic 1 (Operator Overloading, Object Conversion)|Topic 1]]
**Hub**: (this note)
