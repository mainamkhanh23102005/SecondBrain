---
tags: [software-engineering, testing, TDD, V&V, HUST, chapter8, exam-prep]
chapter: 8
source: Software Engineering 9th Edition – Sommerville
created: 2026-06-01
---
jkhli
# Chapter 8 – Software Testing: Zero-Loss Comprehensive Notes

> [!abstract] Executive Summary
> **Software testing** is the disciplined process of executing software with artificial data to expose defects and build confidence that the system meets its requirements. Testing serves two complementary goals:
> 1. **Validation testing** — demonstrate that the software does what it is supposed to do (correct inputs, expected behavior).
> 2. **Defect testing** — discover situations where the software behaves incorrectly or unexpectedly (often using atypical, boundary, or stress inputs).
>
> Testing is one pillar of the broader **Verification & Validation (V&V)** process alongside static techniques such as inspections and reviews. The three-stage testing pipeline — Development → Release → User — forms the backbone of professional software quality assurance. A critical meta-principle: **testing can only show the presence of errors, never their absence** (Dijkstra, 1972).

---

## 1. Executive Summary — The Testing Landscape

| Concept | Core Principle |
|---|---|
| **Testing Cannot Prove Correctness** | Even exhaustive testing cannot guarantee defect-free software. It demonstrates that known test cases pass, not that all possible inputs work. |
| **Two Goals, Two Test Designs** | Validation tests use correct inputs reflecting expected use; defect tests use obscure/boundary inputs to expose failures. |
| **V&V is Broader than Testing** | Static techniques (inspections, static analysis) and dynamic techniques (testing) are complementary — neither alone is sufficient. |
| **Automation is Essential** | Automated testing makes regression testing practical; manual testing remains necessary for usability and visual/interactive systems. |
| **Three-Stage Pipeline** | Development testing → Release testing → User testing. Each stage has different goals, teams, and methodologies. |

> [!quote] Dijkstra's Principle (1972)
> "Testing can only show the presence of errors, not their absence."

> [!quote] Boehm's V&V Distinction (1979)
> - **Validation:** "Are we building the right product?"
> - **Verification:** "Are we building the product right?"

---

## 2. Core Concepts — Technical Term Glossary

| Term | Definition |
|---|---|
| **Verification** | Checking that the software meets its *stated functional and non-functional requirements* — "building the product right." |
| **Validation** | Checking that the software meets the *customer's actual expectations* — "building the right product." More general than verification. |
| **V&V (Verification & Validation)** | The umbrella process covering all checking activities from requirements to delivery: both static (inspections) and dynamic (testing). |
| **Validation Testing** | Tests using expected, correct inputs to demonstrate the system performs as required. |
| **Defect Testing** | Tests designed to expose defects; may use obscure, atypical, or boundary inputs. |
| **Test Case** | A specification of an input to the test, the expected output (result), and a statement of what is being tested. |
| **Test Data** | The actual input values devised to test the system. |
| **Test Results** | The outputs produced by running test data against the system. |
| **Regression Testing** | Re-running previous tests after a system change to verify that the change has not introduced new bugs. |
| **Development Testing** | Testing during development by the development team to discover bugs; includes unit, component, and system testing. |
| **Release Testing** | Testing of a complete system version by a *separate* team before external release; focuses on validation. |
| **User Testing** | Testing by users or customers in their own environment; includes alpha, beta, and acceptance testing. |
| **Unit Testing** | Testing individual program components (methods, object classes) in isolation. |
| **Component Testing** | Testing composite components (multiple interacting objects) through their defined interface. |
| **System Testing** | Testing the integrated system as a whole, focusing on component interactions and emergent behavior. |
| **Mock Object** | An object with the same interface as a real dependency (e.g., database) that simulates its behavior for testing — faster, controllable, avoids heavy setup. |
| **Equivalence Partition** | A set of input values that are expected to produce equivalent system behavior; test cases drawn from each partition. |
| **Boundary Value Analysis** | Selecting test cases at the edges of equivalence partitions (and near midpoints) because failures often occur at boundaries. |
| **Black-Box Testing** | Test case design based solely on the specification, without knowledge of internal code. |
| **White-Box Testing** | Test case design using knowledge of the internal code structure (e.g., branch coverage, exception handling paths). |
| **Path Testing** | Testing every independent execution path through a component — all statements executed at least once, all conditionals tested both ways. |
| **TDD (Test-Driven Development)** | A development approach where tests are written *before* code; code is written to make the tests pass. |
| **Acceptance Testing** | Formal customer testing to decide whether a system should be accepted from the developer and deployed. |
| **Alpha Testing** | User testing at the developer's site; developers and users collaborate. |
| **Beta Testing** | Testing with an early release made available to selected users/public; interaction problems with varied environments discovered. |
| **Stress Testing** | Testing beyond the design load limits to discover failure behavior and defects exposed only under heavy load. |
| **Operational Profile** | A set of tests weighted to reflect the actual mix of transactions the system will handle in production. |
| **Inspection** | A static V&V technique in which a team reviews code or documents to find errors *without executing the software*. |
| **Software Inspection (Static Analysis)** | Review-based defect detection; can find 60–90% of defects in a program before testing begins. |

---

## 3. Verification & Validation — Full Framework

### 3.1 The V&V Goal

The ultimate goal of V&V is to establish **confidence that the software is "fit for purpose"** — good enough for its intended use. The required confidence level depends on three factors:

| Factor | Implication |
|---|---|
| **Software Purpose** | Safety-critical systems require much higher confidence than prototypes. |
| **User Expectations** | Users accustomed to buggy software tolerate failures in early versions; mature software must be more reliable. |
| **Marketing Environment** | Competitive pressure may push early releases before thorough testing is complete. |

### 3.2 Static vs. Dynamic V&V

| Technique | Type | Description |
|---|---|---|
| **Software Inspections** | Static | Review of code, requirements, design, and models without executing the software |
| **Static Analysis** | Static | Automated tool-based source text analysis to detect anomalies (Chapter 15) |
| **Testing (Dynamic V&V)** | Dynamic | Executing the software with artificial data and checking results |

**Three Advantages of Inspections Over Testing:**

1. **No error masking:** During testing, one error's output can hide other errors. Inspections examine each error independently — a single session can find many errors.
2. **Incomplete versions:** An incomplete program can be inspected without building test harnesses (which add cost). Testing requires harnesses for partial systems.
3. **Broader quality assessment:** Inspections can assess compliance with standards, portability, maintainability, and algorithmic efficiency — beyond just correctness.

> [!warning] Inspections Cannot Replace Testing
> Inspections miss: unexpected component *interactions*, *timing problems*, and *performance issues*. These are only discoverable through execution. Inspections and testing are complementary, not substitutable.
>
> Additional practical constraint: small companies may lack the staff to form a dedicated inspection team separate from the developers.

---

## 4. The Three-Stage Testing Pipeline

```
Development Testing → Release Testing → User Testing
   (Find bugs)          (Validate)       (Real environment)
```

| Stage | Who Tests | Goal | Test Type |
|---|---|---|---|
| **Development Testing** | Development team (programmers) | Find bugs and defects | Primarily defect testing |
| **Release Testing** | Separate testing team | Validate against requirements; good enough for external use | Primarily validation testing |
| **User Testing** | Users / customers | Discover real-environment interaction problems | Validation + usability |

---

## 5. Development Testing (Section 8.1)

Development testing covers three levels of granularity:

### 5.1 Unit Testing

Unit testing tests **individual program components** — methods, functions, or object classes — in isolation.

**For Object Classes, Ensure:**
- All *operations* are tested
- All *attributes* are set and checked
- The object is placed in *all possible states* (simulate all state-change events)

**State Sequence Testing (Weather Station Example):**
```
Shutdown → Running → Shutdown
Configuring → Running → Testing → Transmitting → Running
Running → Collecting → Running → Summarizing → Transmitting → Running
```
Each arrow represents a state transition that must be exercised by a test.

**Automated Unit Test Structure — Three Parts:**

| Part | Purpose |
|---|---|
| **Setup** | Initialize the system with test case inputs and expected outputs |
| **Call** | Invoke the object/method being tested |
| **Assertion** | Compare actual result to expected result; `true` = pass, `false` = fail |

**Mock Objects:**
When a unit depends on a slow or unavailable component (e.g., database), replace it with a **mock object** — same interface, simulated simplified behavior (e.g., in-memory array instead of disk). Mocks also simulate rare conditions (e.g., specific timestamps, failure states).

> [!warning] Inheritance and Unit Testing
> You cannot test an inherited operation in the superclass and assume it works in all subclasses. The operation may make assumptions that are invalid in some subclasses. **Test inherited operations in every subclass context.**

---

### 5.2 Choosing Unit Test Cases — Two Strategies

#### Strategy 1: Equivalence Partitioning (Partition Testing)

**Core Idea:** Identify groups of inputs (equivalence partitions) that the system processes in the same way. Design one test from each partition.

**How to Identify Partitions:**
- Read the specification to find distinct input ranges, types, and conditions
- Supplement with white-box analysis: exception handling paths create additional "exception partitions"

**Test Case Selection Rule:**
- Choose cases at **partition boundaries** (atypical values often overlooked by developers)
- Also choose cases **near the midpoint** of each partition (tests the typical case)

**Example — Input: 4–8 integers, each > 10,000:**

| Partition | Test Values (Boundary / Midpoint) |
|---|---|
| Number of inputs < 4 | 3 (boundary), 1 (single-value edge case) |
| Number of inputs 4–8 | 4 (lower boundary), 7 (midpoint), 8 (upper boundary) |
| Number of inputs > 8 | 9 (boundary), 11 |
| Input value < 10,000 | 9,999 (boundary), 1 |
| Input value 10,000–99,999 | 10,000 (lower boundary), 50,000 (midpoint), 99,999 (upper boundary) |
| Input value > 99,999 | 100,000 (boundary) |

> [!note] Black-Box vs. White-Box Testing
> Using the **specification** to identify partitions = **black-box testing** (no code knowledge needed). Supplementing with internal code knowledge (exception handlers, special cases) = **white-box testing**. Both together provide the most thorough coverage.

#### Strategy 2: Guideline-Based Testing

Experience-based rules that target known failure patterns. For sequences, arrays, or lists:

1. **Single-value sequences:** Test with a sequence of exactly one element — programmers often embed the assumption that sequences have multiple values.
2. **Varying sizes:** Use different sequence sizes across tests to avoid accidentally correct outputs.
3. **First, middle, last access:** Derive tests that access the first, middle, and last elements — catches boundary problems.

**General Guidelines (Whittaker, 2002):**
- Force the system to generate all error messages
- Design inputs that overflow input buffers
- Repeat the same input/sequence numerous times
- Force invalid outputs to be generated
- Force computation results to be too large or too small

---

### 5.3 Component Testing

Component testing tests **composite components** — multiple interacting objects — through their **defined interface** (not the internal objects individually).

**Why Component Testing Is Needed:**
Interface errors between objects are only detectable when objects interact; unit tests on individual objects cannot reveal them.

**Four Interface Types:**

| Interface Type | Description | Example |
|---|---|---|
| **Parameter Interface** | Data or function references passed between components | Method calls with parameters |
| **Shared Memory Interface** | A block of memory shared between components; one writes, others read | Embedded sensor data in memory |
| **Procedural Interface** | A component encapsulates procedures that other components call | Objects and reusable components |
| **Message Passing Interface** | Components request services by passing messages; results returned via message | Client–server systems, microservices |

**Three Classes of Interface Errors:**

| Error Class | Description |
|---|---|
| **Interface Misuse** | Calling component passes wrong type, wrong order, or wrong number of parameters |
| **Interface Misunderstanding** | Calling component misunderstands the called component's behavior (e.g., calling binary search on an unsorted array) |
| **Timing Errors** | In real-time shared-memory or message-passing systems, producer and consumer operate at different speeds; consumer reads stale data |

**Interface Testing Guidelines:**

1. List every external component call and test each with **extreme parameter values** — most likely to reveal interface inconsistencies.
2. Pass **null pointers** to interfaces that accept pointer parameters.
3. Design tests that **deliberately cause component failure** — differing failure assumptions are a common misunderstanding.
4. Use **stress testing** in message-passing systems — many more messages than expected in practice.
5. **Vary activation order** of components sharing memory — reveals implicit ordering assumptions.

---

### 5.4 System Testing

System testing tests the **integrated system as a whole**, focusing on component interactions and **emergent behavior** — system properties that only appear when components are combined.

**Two Differences from Component Testing:**

| Aspect | Component Testing | System Testing |
|---|---|---|
| Scope | Individual interface | Full integrated system |
| What's included | New components only | New + reusable + COTS components |
| Team | Usually individual developer | Often a collective, separate team |

**Use Case–Based System Testing:**
Each use case exercises a specific thread of component interactions. Use sequence diagrams to identify the thread and design test cases:

**Example — Weather Station Collect Data Use Case:**
```
SatComms:request → WeatherStation:reportWeather → Commslink:get(summary) → WeatherData:summarize
```
Test inputs: a request for a report. Expected output: correct summarized report. Also test exceptions (malformed request, unavailable sensor).

**System Testing Policies (typical rules):**
1. All functions accessed through menus must be tested.
2. Combinations of functions accessed through the same menu must be tested.
3. All functions must be tested with both correct AND incorrect input.

> [!warning] Automated System Testing Challenges
> Automated *unit* tests can predict outputs easily. For system-level outputs (complex reports, graphical displays), outputs may be large or hard to predict in advance. Human evaluation may be required to check *credibility* of outputs even if exact expected values cannot be pre-specified.

---

## 6. Test-Driven Development (Section 8.2)

### 6.1 TDD Process

TDD interleaves test writing with code development. You never write code without first writing a failing test.

**The TDD Cycle (Figure 8.9):**

```
1. Identify small increment of functionality to implement
2. Write an automated test for it (test will initially fail — by design)
3. Run test (+ all existing tests) → it FAILS (expected — proves test adds value)
4. Implement the functionality + refactor existing code if needed
5. Run all tests → ALL PASS
6. Move to next increment (go to step 1)
```

> [!info] Why Failing First Matters
> Running the test before implementing the code and watching it fail **proves that the test is actually testing something**. A test that passes before the code exists is not testing anything meaningful.

### 6.2 TDD Benefits

| Benefit | Explanation |
|---|---|
| **Code Coverage** | Every code segment has at least one associated test — all code is executed during testing. Defects are discovered when written, not later. |
| **Regression Testing** | The full test suite grows incrementally. Regression tests can always be re-run cheaply to verify changes haven't broken anything. |
| **Simplified Debugging** | When a new test fails, the bug is in the newly written code — no need for a debugger. Reports confirm debuggers are rarely needed in TDD practice. |
| **System Documentation** | Tests describe what the code is *supposed to do* — reading tests aids comprehension of unfamiliar code. |

### 6.3 TDD Limitations

| Limitation | Explanation |
|---|---|
| **Reused/Legacy Components** | Must write tests for the whole component, not incrementally |
| **Multi-threaded Systems** | Different thread interleavings in different test runs may produce inconsistent results |
| **System-level Validation** | TDD does not replace system testing — it doesn't validate performance, reliability, or emergent behavior |
| **Incomplete Knowledge** | If you don't know enough to write a test (e.g., forgetting to test divide-by-zero), the corresponding code protection will never be written |

> [!quote] TDD Cost-Benefit Insight
> The most important benefit of TDD is **reducing regression testing costs**. In manual testing, regression tests are prohibitively expensive in time and effort. Automated TDD tests re-run in seconds, making regression testing practical after *every* change.

---

## 7. Release Testing (Section 8.3)

Release testing validates a complete system version before external release, performed by a **separate team** not involved in development.

**Two Critical Distinctions from Development System Testing:**

| Aspect | Development System Testing | Release Testing |
|---|---|---|
| **Team** | Development team | Separate, independent team |
| **Goal** | Find bugs (defect testing) | Validate against requirements (validation testing) |

Release testing is **black-box testing** — also called **functional testing** — because testers know only the specification, not the code.

### 7.1 Requirements-Based Testing

A systematic approach: for **each requirement**, derive a set of tests that demonstrate it has been satisfied.

**Example — MHC-PMS Drug Allergy Requirements:**

| Test # | Test Description |
|---|---|
| 1 | Patient with NO allergies: prescribe known allergen medication → verify NO warning issued |
| 2 | Patient with ONE known allergy: prescribe that drug → verify warning IS issued |
| 3 | Patient with TWO+ allergies: prescribe each drug separately → verify correct warning for each |
| 4 | Prescribe TWO allergenic drugs simultaneously → verify TWO warnings issued |
| 5 | Prescribe allergenic drug, override warning → verify system requires reason for override |

> [!tip] One Requirement → Multiple Tests
> A single requirement almost always requires multiple tests for full coverage: normal case, boundary cases, error cases, and combinations. Maintain traceability records linking each test to its requirement.

### 7.2 Scenario Testing

Scenario testing tests **multiple requirements simultaneously** through a realistic narrative story of system use.

**Scenario Design Criteria (Kaner, 2003):**
- Credible and realistic (stakeholders relate to it)
- Fairly complex (exercises multiple system features)
- Motivates stakeholders (they believe it's important)
- Easy to evaluate (problems are recognizable when they occur)

**MHC-PMS Home Visit Scenario (Figure 8.10) — Features Tested:**

| # | Feature Tested |
|---|---|
| 1 | Authentication (nurse login) |
| 2 | Download / upload of specific patient records to laptop |
| 3 | Home visit scheduling |
| 4 | Encryption and decryption of records on mobile device |
| 5 | Record retrieval and modification |
| 6 | Links with drugs database (side-effect information) |
| 7 | Call prompting system |

> [!note] Scenario Testing vs. Requirements Testing
> Requirements-based testing checks *individual* requirements in isolation. Scenario testing checks that **combinations of requirements** do not cause problems when exercised together — a complementary strength.

### 7.3 Performance Testing

Performance testing validates **emergent properties** — system characteristics that only appear when the system is fully integrated (performance, reliability).

**Two Purposes of Stress Testing:**

1. **Test failure behavior:** Verify that overloaded systems fail softly (no data corruption, no abrupt service loss). Circumstances may cause load to exceed maximum anticipated levels.
2. **Surface hidden defects:** Unusual combinations of normal circumstances that only appear under load; stress testing replicates these.

**Operational Profile:**
To validate performance requirements, construct an operational profile — a set of tests weighted to match the *actual production mix*. If 90% of transactions are type A, 90% of performance tests should also be type A.

> [!warning] Operational Profile vs. Defect Discovery
> An operational profile is ideal for **validation** but NOT for **defect discovery**. Defects often lurk at the limits of the system, not in the most common transaction paths. Use *both*: operational profiles for validation, stress tests for defect discovery.

**Stress Testing in Distributed Systems:**
Network-based systems often exhibit severe degradation under load — the network becomes swamped with coordination messages; processes wait longer and longer. Stress testing identifies the degradation threshold so the system can be designed to reject transactions beyond that point.

---

## 8. User Testing (Section 8.4)

User testing is essential because the **user's working environment** — clinical noise, parallel conversations, emergencies — has major effects on reliability, performance, and usability. No developer can replicate this environment in a lab.

### 8.1 Three Types of User Testing

| Type | Who | Where | Purpose |
|---|---|---|---|
| **Alpha Testing** | Selected users + development team | Developer's site | Collaborative; users identify non-obvious problems; developers can ask clarifying questions |
| **Beta Testing** | Early adopters or general public | User's own environment | Discover interaction problems with varied real environments; also serves as marketing |
| **Acceptance Testing** | Customers | Customer's site (ideally) | Formal customer decision: accept or reject the system |

**Alpha testing** is common for shrink-wrapped software products where users want early access to new features and can help design more realistic tests.

**Beta testing** is essential for products used in many different environments — the developer cannot replicate all deployment environments.

### 8.2 The 6-Stage Acceptance Testing Process

```
Define Criteria → Plan Testing → Derive Tests → Run Tests → Negotiate Results → Accept/Reject
```

| Stage | Description |
|---|---|
| **1. Define Acceptance Criteria** | Ideally done *before* contract signing. Criteria must be agreed between customer and developer and form part of the contract. (In practice, often delayed due to incomplete requirements.) |
| **2. Plan Acceptance Testing** | Define resources, time, budget, coverage requirements, test order, and risk mitigation (system crashes, inadequate performance). |
| **3. Derive Acceptance Tests** | Design tests covering both *functional* and *non-functional* (performance) requirements. Aim for complete requirements coverage. (Establishing completely objective criteria is difficult in practice.) |
| **4. Run Acceptance Tests** | Execute tests, ideally in the real deployment environment (may require a user testing environment). Manual end-user interaction is often required; full automation is rarely possible. |
| **5. Negotiate Test Results** | It is almost never the case that all tests pass perfectly. Developer and customer negotiate: which failures are acceptable? What is the remediation plan? |
| **6. Reject or Accept System** | Formal decision meeting. If rejected: further development + repeat acceptance testing. If conditionally accepted: deploy with agreed remediation timeline. |

> [!warning] The Acceptance Testing Reality
> Customers rarely reject a system even with failures because the cost of *not using* the software (new hardware purchased, staff trained, processes changed) often exceeds the cost of working around its problems. **Conditional acceptance** is common: deploy now, developer commits to fixing urgent issues quickly.

### 8.3 Agile Acceptance Testing

In XP and agile methods:
- The user is **embedded in the development team** (alpha tester from day one)
- Requirements are expressed as **user stories**
- The user defines **acceptance tests per story** — automated
- Development does not proceed until the story's acceptance tests pass
- There is **no separate acceptance testing activity** — it is continuous

> [!warning] Agile Acceptance Testing Limitation
> The embedded user may not be a "typical" user — their preferences may not represent the broader user base. The requirement for automated acceptance tests severely limits testing of interactive systems (usability, visual layout) that require groups of end-users to evaluate. For such systems, additional manual acceptance testing is still needed.

---

## 9. Deep-Dive: Why Testing Philosophy Matters

> [!question] The Fundamental Testing Tension
> You can never test enough. Exhaustive testing (all possible inputs, all execution sequences) is computationally impossible for any non-trivial program. Therefore, testing is *always* a sampling problem: you choose a subset of possible test cases and bet that they are representative.
>
> The key insight: **the choice of what not to test is as important as what to test**. Equivalence partitioning and guideline-based testing are engineering frameworks for making this sampling decision rationally rather than arbitrarily.

**Common Pitfalls and Mitigations:**

| Pitfall | Why It Happens | Mitigation |
|---|---|---|
| Testing only typical inputs | Programmers design for typical cases | Equivalence partitioning forces boundary testing |
| Stopping when a test passes | Confirmation bias | Design tests that are expected to *fail* — defect tests, not validation tests |
| Not re-running after changes | Regression bugs are common | Automate the test suite; run on every commit |
| Unit tests passing but system failing | Interface misunderstandings between units | Separate component and system testing phases |
| Accepting because cost of rejection is high | Business pressure | Define acceptance criteria contractually before development begins |
| Mock objects hiding real failures | Mocks simulate simplified behavior | Use real components in system and integration testing |

**The Inspections vs. Testing Trade-off:**

| Factor | Inspections Win | Testing Wins |
|---|---|---|
| **Finding many errors fast** | ✓ No error masking; one session finds many | — Errors mask each other |
| **Incomplete systems** | ✓ No test harness needed | — Requires harnesses |
| **Interaction/Timing bugs** | — Cannot detect | ✓ Only detectable via execution |
| **Performance issues** | — Cannot detect | ✓ Only measurable via execution |
| **Small teams** | — Hard to staff separately | ✓ Developers can test their own code |

---

## 10. Exam Prep — Discussion Questions

> [!question] Discussion Question 1 — Validation vs. Defect Testing
> A tester is building tests for the MHC-PMS drug allergy module. Describe how their test design would differ if they were doing (a) validation testing vs. (b) defect testing. Give two specific test cases for each type and explain why the distinction matters.
>
> **Guidance:** (a) Validation: prescribe a drug the patient IS allergic to → verify warning appears (expected use, correct input); verify that overriding the warning prompts for a reason. (b) Defect: prescribe a drug with a name that differs by one character from an allergen (fuzzy-match boundary); prescribe 50+ drugs simultaneously to test for race conditions in the allergy-check module. Distinction matters because validation confirms known requirements; defect testing probes the unknown failure space using experience and adversarial thinking.

> [!question] Discussion Question 2 — Equivalence Partitioning Applied
> The `catWhiteSpace` method in a `Paragraph` object replaces sequences of blank characters with a single blank character. Identify the testing partitions for this method and derive at least five test cases, including boundary cases.
>
> **Guidance:** Partitions: (1) no blanks — no change expected; (2) single blank — no change expected; (3) two consecutive blanks — reduce to one; (4) multiple consecutive blanks (n > 2) — reduce to one; (5) blanks at start of string; (6) blanks at end of string; (7) blanks at start AND end; (8) only blanks (entire string is blank spaces). Test cases: empty string; "hello" (no blanks); "hello world" (one blank); "hello  world" (two blanks); "  hello  world  " (leading, internal, and trailing blanks).

> [!question] Discussion Question 3 — TDD vs. Traditional Development
> A team manager argues: "TDD doubles the workload because you write tests first AND then code." Counter this argument by explaining (a) the economic case for TDD and (b) two specific scenarios where TDD would be less suitable.
>
> **Guidance:** (a) TDD reduces regression testing costs dramatically. Without TDD, regression testing is run manually (expensive, error-prone, often skipped). With TDD, the entire test suite runs in seconds after every change — catching bugs immediately when they are cheapest to fix (in the new code). The "double workload" is partially offset by: simplified debugging (bug location obvious from failing test), better code design (writing tests forces clear interfaces), and reduced integration problems. (b) Less suitable: (1) multi-threaded systems where test runs produce non-deterministic results; (2) systems integrating large reusable or legacy components where writing incremental tests is impractical.

> [!question] Discussion Question 4 — Interface Error Detection
> A system has a binary search component called with an unordered array (interface misunderstanding). Describe: (a) why unit testing of the binary search component would NOT catch this bug, (b) what type of test would catch it, and (c) what general interface testing guideline applies.
>
> **Guidance:** (a) Unit testing the binary search component in isolation would always pass a correctly sorted array — the component itself works correctly. The bug lies in the *calling* component's misunderstanding of the precondition. (b) Component/interface testing of the combined system — testing the *calling* component's interaction with binary search using the actual data the calling component provides. (c) Guideline: "Examine the code to be tested and explicitly list each call to an external component. Design a set of tests where parameter values are at extreme ends of their valid ranges." Also: deliberately cause the called component to fail — this surfaces assumption mismatches.

> [!question] Discussion Question 5 — Acceptance Testing Reality
> The MHC-PMS is delivered to a hospital. Acceptance testing reveals: (a) the drug-allergy warning sometimes takes 8 seconds to appear (requirement: < 2 seconds) and (b) the encryption key phrase input occasionally accepts incorrect phrases (security requirement violation). How should the 6-stage acceptance testing process handle each finding? Under what conditions might the hospital accept the system despite these failures?
>
> **Guidance:** (a) Performance failure (8s vs. 2s): significant but not safety-critical. Negotiate: conditional acceptance with developer committed to a performance fix within 30 days. Hospital may accept because missing the system has operational costs (nurses without patient records during home visits). (b) Security violation: a safety/regulatory issue — accepting patient records that can be decrypted without the correct key is a data protection failure. This is much harder to conditionally accept — it could violate GDPR/HIPAA. Likely requires rejection until fixed. However, if the system has already been deployed and staff trained, the hospital may seek a contractual commitment for an emergency patch within 72 hours. General point: acceptance is not purely technical — it is a negotiation shaped by operational dependency on the system.

---

## 11. Key Points Summary (from Textbook)

> [!summary] Textbook Key Points — Chapter 8

- **Testing can only show the presence of errors** in a program. It cannot demonstrate that there are no remaining faults.
- **Development testing** is the responsibility of the software development team. A separate team should be responsible for release testing. In the user testing process, customers or system users provide test data and check test success.
- Development testing includes **unit testing** (individual objects and methods), **component testing** (related groups of objects), and **system testing** (partial or complete systems).
- When testing, try to **"break" the software** using experience and guidelines to choose test cases effective in discovering defects.
- Wherever possible, **write automated tests** — embedded in a program that can be run every time a change is made.
- **Test-first development** writes tests before code; small code changes are made and code is refactored until all tests pass.
- **Scenario testing** replicates practical system use — devise typical usage scenarios to derive test cases.
- **Acceptance testing** is a user testing process where the aim is to decide if the software is good enough to be deployed in its operational environment.

---

## 12. Further Reading

| Resource | Authors | Notes |
|---|---|---|
| "How to design practical test cases" | Yamaura (IEEE Software, Nov 1998) | Practical test case design from a company with very low defect rates |
| *How to Break Software: A Practical Guide to Testing* | Whittaker (2002) | Experience-based guidelines for designing tests likely to find real faults |
| "Software Testing and Verification" | IBM Systems Journal, 41(1), 2002 | Papers on testing, test metrics, and test automation |
| "Test-driven development" | IEEE Software 24(3), May/June 2007 | Overview of TDD and experience papers across different software types |
| *Test Driven Development: By Example* | Beck (2002) | Foundational TDD textbook |

---

[[Chapter7_Comprehensive|← Previous: Chapter 7 – Design and Implementation]] | [[Software Engineering Hub|Hub]]
