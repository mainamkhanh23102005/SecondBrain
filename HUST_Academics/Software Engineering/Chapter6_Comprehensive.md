---
tags: [software-engineering, architecture, HUST, chapter6, exam-prep]
chapter: 6
source: Software Engineering 9th Edition – Sommerville
created: 2026-05-09
---

# Chapter 6 – Architectural Design: Zero-Loss Comprehensive Notes

> [!abstract] Executive Summary
> **Architectural design** is the critical bridge between requirements engineering and detailed design. It defines the **overall structure** of a system — its major components, their responsibilities, and how they interact. Getting the architecture right early is decisive because:
> - **Non-functional requirements** (performance, security, availability, maintainability) are primarily determined by architecture, not by individual component implementations.
> - **Refactoring architecture is expensive**; refactoring individual components is cheap. Invest in architecture upfront.
> - Architecture serves as the **shared language** across stakeholders (clients, managers, developers, testers) and enables large-scale reuse across product lines.

---

## 1. Executive Summary – Why Architectural Design Matters

| Benefit                         | Explanation                                                                                                                                                |
| ------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Stakeholder Communication**   | High-level architectural models give non-technical stakeholders a comprehensible view for discussion and sign-off.                                         |
| **System Analysis**             | Making architecture explicit forces early analysis of whether critical non-functional requirements (performance, reliability, maintainability) can be met. |
| **Large-Scale Reuse**           | A documented architecture is a compact, reusable blueprint; systems in the same domain share similar architectures (product lines).                        |
| **Complexity Management**       | Architecture hides implementation detail and lets designers focus on key system abstractions.                                                              |
| **Design Plan for Negotiation** | Architecture acts as a vehicle for negotiating system requirements between clients, developers, and managers (Hofmeister et al., 2000).                    |

> [!quote] Key Principle (Bosch, 2000)
> Individual components implement **functional requirements**. The system architecture governs **non-functional requirements**.

---

## 2. Core Concepts — Technical Term Glossary

| Term | Definition |
|---|---|
| **Architectural Design** | The process of identifying and defining the major structural components of a system and their relationships; the first stage of software design. |
| **Architecture in the Small** | Architecture of an individual program — how it decomposes into components. |
| **Architecture in the Large** | Architecture of complex enterprise/distributed systems spanning multiple computers, organizations, and programs (covered in Chapters 18–19). |
| **Architectural Model** | A description of how a system is organized as a set of communicating components. |
| **Architectural Pattern (Style)** | A stylized, abstract description of a proven system organization that captures design knowledge reusable across multiple systems. |
| **Architectural View** | A perspective on the architecture that exposes a particular subset of architectural properties (e.g., logical, physical). |
| **4+1 View Model** | Krutchen's (1995) framework of four fundamental architectural views unified by use-case scenarios. |
| **Non-Functional Requirements (NFRs)** | System qualities such as performance, security, safety, availability, and maintainability — primarily shaped by architecture. |
| **Block Diagram** | An informal, box-and-arrow diagram commonly used to represent architectural components and their connections. |
| **Architectural Description Language (ADL)** | A specialized formal notation for describing system architectures; elements are components and connectors. |
| **UML (Unified Modeling Language)** | General-purpose modeling language; useful for detailed architectural documentation but too implementation-close for early design. |
| **Separation and Independence** | A core design principle that localizes change; the MVC and Layered patterns directly implement this principle. |
| **Repository (Blackboard)** | A central shared data store; the passive variant is a repository, the active (AI-derived) variant is a blackboard that triggers components when data becomes available. |
| **Transaction** | An atomic unit of database work; all operations must complete before changes are made permanent. |
| **Transaction Processing (TP) System** | A database-centered, interactive system handling concurrent user requests to query or update a database. |
| **Language Processing System** | A system that translates a formal/natural language into another representation and optionally executes it (e.g., compilers). |
| **Reference Architecture** | A domain-specific, comprehensive architectural template used to evaluate designs and educate practitioners; no single application implements all features. |
| **Product Line Architecture** | A core architecture reused — with variants — across a family of related systems. |
| **COTS (Commercial Off-The-Shelf)** | Vertical software packages configured and adapted for specific business applications (e.g., SAP ERP). |
| **ERP (Enterprise Resource Planning)** | Generic configurable business systems (SAP, Oracle) representing reuse of application architectures without re-implementation. |
| **Lexical Analyzer (Lexer)** | Compiler component that tokenizes raw source text into an internal form. |
| **Symbol Table** | Compiler repository holding names and properties of entities (variables, classes, objects). |
| **Syntax Analyzer (Parser)** | Compiler component that checks grammar and builds a syntax tree. |
| **Syntax Tree (AST)** | Internal tree structure representing the grammatical structure of the compiled program. |
| **Semantic Analyzer** | Compiler component that checks type correctness and meaning using the syntax tree and symbol table. |
| **Code Generator** | Compiler component that traverses the syntax tree to produce abstract machine code. |
| **Pipe** | A conduit passing a data stream between two processes (originates in Unix shells). |
| **Filter** | A processing component that transforms an input data stream and produces an output data stream. |
| **Remote Procedure Call (RPC)** | Mechanism by which a client invokes a procedure on a server across a network (e.g., HTTP request-reply). |
| **Multi-tier Architecture** | A client–server variant with distinct tiers: web server, application server, database server. |

---

## 3. Architectural Design Decisions

Architectural design is **creative, not procedural**. Architects answer these nine fundamental questions:

1. Is there a **generic application architecture** that can serve as a template?
2. How will the system be **distributed** across cores or processors?
3. What **architectural patterns or styles** apply?
4. What is the **fundamental approach** for structuring the system?
5. How will structural components be **decomposed into sub-components**?
6. What **control strategy** governs component operation?
7. What architectural organization best delivers the **non-functional requirements**?
8. How will the **architectural design be evaluated**?
9. How should the architecture be **documented**?

> [!note] Non-Functional Requirement → Architectural Strategy

| NFR | Recommended Architectural Strategy |
|---|---|
| **Performance** | Localize critical operations in **few large components** on the **same machine**; minimize inter-component communication; support replication across processors. |
| **Security** | Use a **layered architecture** with most critical assets in **innermost layers**; apply high-level security validation at each inner layer. |
| **Safety** | Concentrate safety-related operations in **one or a few components** to minimize validation scope; enable safe shutdown subsystems. |
| **Availability** | Build in **redundant components**; design for hot-swappable replacement/update without stopping the system. |
| **Maintainability** | Use **fine-grain, self-contained components**; separate data producers from consumers; avoid shared mutable data structures. |

> [!warning] Conflict & Trade-off
> **Performance vs. Maintainability** is the canonical tension: large components improve performance; small fine-grain components improve maintainability. Resolution may require applying different patterns to different subsystems.

---

## 4. Architectural Views — The 4+1 View Model (Krutchen, 1995)

> [!info] Why Multiple Views?
> No single model can represent all relevant architectural information. Each view exposes a different perspective; together they give a complete architectural picture.

### 4.1 The Five Views

```
          ┌─────────────────────────────────────────────────┐
          │                  USE CASES / SCENARIOS           │
          │                    (+1 unifying view)            │
          └──────────────────────┬──────────────────────────┘
                                 │
         ┌───────────┬───────────┼───────────┬───────────┐
         ▼           ▼           ▼           ▼           ▼
      LOGICAL     PROCESS   DEVELOPMENT   PHYSICAL   CONCEPTUAL
```

---

### 4.2 Logical View

- **What it shows:** Key **abstractions** in the system — object classes, entities, and their relationships.
- **Purpose:** Maps system **requirements** to logical entities; supports understanding of what the system does conceptually.
- **Primary audience:** Requirements analysts, domain experts.
- **UML notation:** Class diagrams, object diagrams.

---

### 4.3 Process View

- **What it shows:** Run-time behavior — how the system is composed of **interacting processes** and threads.
- **Purpose:** Enables reasoning about **non-functional qualities** — performance, throughput, concurrency, availability.
- **Primary audience:** Performance engineers, system architects.
- **UML notation:** Activity diagrams, sequence diagrams, communication diagrams.

---

### 4.4 Development View

- **What it shows:** Software **decomposition for development** — how the codebase is broken into modules, packages, subsystems, and libraries that individual developers or teams implement.
- **Purpose:** Supports **project planning** and work assignment; useful for build/dependency management.
- **Primary audience:** Software managers, programmers, build engineers.
- **UML notation:** Component diagrams, package diagrams.

---

### 4.5 Physical View

- **What it shows:** System **hardware topology** and the mapping of software components onto processors, nodes, and network links.
- **Purpose:** Supports **deployment planning**; identifies distribution and infrastructure needs.
- **Primary audience:** Systems engineers, infrastructure/DevOps teams.
- **UML notation:** Deployment diagrams.

---

### 4.6 Conceptual View (Hofmeister et al., 2000 — extension)

- **What it shows:** Abstract, high-level view independent of implementation technology; groups of functions or features mapped to large-scale components.
- **Purpose:** Decomposes high-level requirements; supports reuse decisions; can represent a **product line** rather than a single system.
- **Example:** Figure 6.1 (packing robot) is a conceptual view.
- Used almost always during the **design process** to support architectural decision-making and stakeholder communication.

---

### 4.7 Notation Choices

| Notation | Pros | Cons |
|---|---|---|
| **Informal block diagrams** | Fast, intuitive, whiteboard-friendly, accessible to all stakeholders | No defined semantics; hides relationship types and component properties |
| **UML** | Widely understood; rigorous when used formally | Designed for OO systems; too implementation-close for early architectural work |
| **ADL** | Formally rigorous; captures components and connectors precisely | Difficult for domain specialists to understand; limited practical uptake |

> [!tip] Sommerville's Recommendation
> Prefer **informal notations** during design for speed and communication; use UML (or ADL) only when producing detailed documentation or for model-driven development, and for critical systems requiring regulatory compliance.

---

## 5. Architectural Patterns

> [!quote] Definition
> An **architectural pattern** is a stylized, abstract description of good practice, tried and tested in different systems and environments. It includes: **name, description, example, when to use, advantages, disadvantages**.

---

### 5.1 Model-View-Controller (MVC)

**Separates** presentation and interaction from system data via three interacting components.

| Component | Responsibility |
|---|---|
| **Model** | Manages system data and associated operations; encapsulates application state; notifies View of state changes. |
| **View** | Defines and manages how data is presented to the user; renders Model; requests Model updates. |
| **Controller** | Manages user interaction (key presses, mouse clicks); maps user actions to Model updates; selects the View. |

**Data flow:**
```
User Events → Controller → Model (state change) → View (change notification) → rendered output
```

| | |
|---|---|
| **When used** | Multiple ways to view/interact with the same data; future UI requirements unknown. |
| **Advantages** | Data changes independently of representation; same data can be displayed in multiple simultaneous views; all views update on one data change. |
| **Disadvantages** | Added code complexity when data model and interactions are simple. |

---

### 5.2 Layered Architecture

**Organizes** the system into ordered layers where each layer provides services **only to the layer immediately above** it.

**Generic 4-layer model:**
```
┌──────────────────────────────────────────────┐
│  Layer 4: User Interface                      │
├──────────────────────────────────────────────┤
│  Layer 3: UI Management, Auth & Authorization │
├──────────────────────────────────────────────┤
│  Layer 2: Core Business Logic / App Function  │  ← System Utilities
├──────────────────────────────────────────────┤
│  Layer 1: System Support (OS, Database, etc.) │
└──────────────────────────────────────────────┘
```

**LIBSYS 5-layer example:** Web Browser Interface → LIBSYS Login/Query/Print → Distributed Search → Document Retrieval/Rights → Individual Library Databases (DB1…DBn).

|                   |                                                                                                                                                                                                                                                                                                          |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **When used**     | Building new facilities on top of existing systems; multi-team development (one team per layer); multi-level security requirements.                                                                                                                                                                      |
| **Advantages**    | Entire layers can be replaced without affecting others (so long as the interface is stable); redundant facilities (e.g., authentication) can be inserted at multiple layers to increase dependability; supports multi-platform portability (only machine-dependent inner layers need re-implementation). |
| **Disadvantages** | Clean layer separation is hard in practice — high-level layers sometimes bypass intermediate layers and call lower layers directly; performance overhead from multiple levels of service-request interpretation.                                                                                         |

---

### 5.3 Repository Architecture

**Centralizes** all shared data in a single repository; components interact **only through the repository**, not directly with each other.

```
       ┌────────────┐  ┌────────────┐  ┌────────────┐
       │ UML Editor │  │Code Gen.   │  │Design Anal.│
       └────┬───────┘  └─────┬──────┘  └─────┬──────┘
            │                │               │
       ┌────▼────────────────▼───────────────▼──────┐
       │              Project Repository             │
       └────┬────────────────┬───────────────┬──────┘
            │                │               │
       ┌────▼───────┐  ┌─────▼──────┐  ┌────▼──────┐
       │ Java Editor│  │Python Edit.│  │Report Gen.│
       └────────────┘  └────────────┘  └───────────┘
```

**Blackboard variant:** Active repository that **triggers** components when particular data becomes available (used in AI/data-driven systems where which tool to activate can only be determined after data analysis — Nii, 1986).

| | |
|---|---|
| **When used** | Large volumes of data generated and stored long-term; data-driven systems where data inclusion triggers a tool; IDEs (version-controlled design repositories). |
| **Advantages** | Components are independent — they need not know of each other; changes by one component propagate to all via the repository; consistent data management (e.g., unified backup). |
| **Disadvantages** | Repository is a **single point of failure**; communication bottleneck if all interaction goes through it; difficult to distribute across multiple machines (risk of data redundancy and inconsistency). |

---

### 5.4 Client–Server Architecture

**Organizes** functionality into **services** delivered by dedicated servers; clients access servers via a network using a request-reply protocol.

**Three major components:**
1. **Servers** — offer specific services (print server, file server, compile server).
2. **Clients** — call on server services; multiple concurrent client instances.
3. **Network** — interconnects clients and servers (typically Internet protocols / HTTP).

```
Client 1 ─┐
Client 2 ─┤                    ┌─ Catalogue Server ── Library Catalogue
Client 3 ─┼─── Internet ───────┼─ Video Server ────── Film Store
Client 4 ─┘                    ├─ Picture Server ───── Photo Store
                                └─ Web Server ───────── Film & Photo Info
```

> [!note] Key Asymmetry
> Clients must know server names and service APIs. **Servers do not need to know client identities** or how many clients exist.

| | |
|---|---|
| **When used** | Shared database accessed from multiple locations; variable load requiring server replication. |
| **Advantages** | Distributed architecture with effective use of networked processors; easy to add new servers; servers can be upgraded transparently; general services (e.g., printing) available to all clients without per-client implementation. |
| **Disadvantages** | Each service is a **single point of failure** (vulnerable to denial-of-service attacks or server crash); performance depends on network conditions (unpredictable); management complexity when servers are owned by different organizations. |

---

### 5.5 Pipe and Filter Architecture

**Organizes** processing as a sequence of **discrete functional transformations (filters)** connected by **data conduits (pipes)**; data flows through the pipeline and is transformed at each stage.

**Invoice processing example:**
```
Read Issued Invoices → Identify Payments → Find Payments Due → Issue Receipts
                                        ↘
                                    Issue Payment Reminder
```

| | |
|---|---|
| **When used** | Data processing applications (batch or transaction-based) with inputs processed in discrete sequential stages; batch sequential processing; embedded system process pipelines. |
| **Advantages** | Easy to understand; transformation reuse; workflow matches many business processes naturally; straightforward evolution (add new transforms); can be implemented sequentially **or** concurrently. |
| **Disadvantages** | **Data format must be agreed** between transformations (each filter parses input, unparsing output adds overhead); incompatible data structures prevent functional reuse; **not suitable for interactive systems** (complex I/O formats and event-driven control are incompatible with pipelining). |

---

### 5.6 Comprehensive Pattern Comparison Table

| Pattern | Primary View | Key Structural Feature | Best For | Main Weakness |
|---|---|---|---|---|
| **MVC** | Conceptual / Run-time | Three interacting components (Model, View, Controller) | Multi-view interactive UIs, web apps | Extra complexity for simple data/interactions |
| **Layered** | Conceptual | Hierarchical layers; each serves only the layer above | Multi-team builds, security-critical systems, portability | Hard to maintain clean separation; performance overhead |
| **Repository** | Static structural | Central shared data store; passive or active (blackboard) | IDEs, CAD systems, MIS, data-driven AI systems | Single point of failure; distribution difficult |
| **Client–Server** | Run-time | Services on servers; clients access via network | Distributed systems, shared databases, scalable web apps | Service single point of failure; network-dependent performance |
| **Pipe and Filter** | Run-time | Linear data flow through discrete transformation stages | Batch processing, compilers, data pipelines | Inflexible data format contract; poor fit for interactive UIs |

---

## 6. Application Architectures

> [!info] Definition
> **Application architectures** encapsulate the principal structural characteristics of a **class** of systems. They enable design reuse without necessarily requiring code reuse.

### Uses of Application Architecture Models

1. **Starting point** for architectural design when unfamiliar with the application domain.
2. **Design checklist** — compare your design against the generic architecture for consistency.
3. **Work organization** — stable structural components can be developed in parallel by different teams.
4. **Component reuse assessment** — compare existing components against the generic structure.
5. **Vocabulary** — shared language for discussing and comparing applications of the same type.

---

### 6.1 Transaction Processing Systems

**Definition:** Database-centered interactive systems that process user requests to query or update a database; operations are **atomic** — all steps must complete or none take effect.

**Conceptual structure:**
```
User ──→ I/O Processing ──→ Application Logic ──→ Transaction Manager ──→ Database
```

**Properties:**
- User actions **cannot interfere** with each other (isolation).
- Database **integrity is maintained** at all times.
- Examples: ATM banking, e-commerce, booking systems, information systems.

**ATM example (pipe-and-filter instantiation):**
```
Input:  Get Customer Account ID → Validate Card → Select Service
Process: Query Account → Update Account
Output: Print Details → Return Card → Dispense Cash
```

**Multi-tier web information system:**
| Tier | Component | Responsibility |
|---|---|---|
| **Presentation** | Web Browser | User interface |
| **Middle (App)** | Application Server | UI functionality (login, role checking, form/menu management, data validation), application logic (security, patient info, data import/export, reporting) |
| **Data** | Database Server | Transaction management, persistent data storage |

---

### 6.2 Language Processing Systems

**Definition:** Systems that translate a formal/natural language into another representation and optionally execute the result.

**Generic architecture:**
```
Source Language Instructions → Translator (Check Syntax, Check Semantics, Generate) → Abstract Machine Instructions → Interpreter (Fetch, Execute) → Results
```

**Compiler components (pipe-and-filter model):**
1. **Lexical Analyzer** — tokenizes source text into internal form.
2. **Symbol Table** — repository of entity names (variables, classes, objects).
3. **Syntax Analyzer** — checks grammar; builds syntax tree.
4. **Syntax Tree (AST)** — internal structural representation of the program.
5. **Semantic Analyzer** — checks type/semantic correctness using syntax tree + symbol table.
6. **Code Generator** — walks the syntax tree; emits abstract machine code.

**Two architectural implementations:**

| Model                        | Pattern Used                                    | Best When                                                                                                           |
| ---------------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **Pipe and filter compiler** | Pipe and Filter                                 | Batch compilation without user interaction (e.g., XML-to-XML translation)                                           |
| **Repository-based IDE**     | Repository (symbol table + AST as central repo) | Integrated tools needing immediate cross-component updates (structured editor, interactive debugger, prettyprinter) |

---

## 7. Design Decisions — Trade-off Analysis

> [!warning] Performance vs. Maintainability
> **Performance** demands few, large, co-located components (fewer communication hops). **Maintainability** demands many, small, independent, decoupled components. These are directly opposing forces — no architecture satisfies both maximally.

### Resolution Strategies

| Strategy | Description |
|---|---|
| **Subsystem-level pattern mixing** | Apply performance-optimized patterns (e.g., coarse-grained components) to hot paths; apply fine-grain patterns to less critical subsystems. |
| **Layered + localization** | Use a layered architecture to isolate security concerns in inner layers while keeping outer layers maintainable. |
| **Replication** | For availability and performance, replicate servers/components so load can be distributed and failures tolerated. |
| **Interface stability contracts** | In layered architectures, define and freeze layer interfaces so layers can be replaced (performance improvements) without breaking adjacent layers (maintainability). |

### Full NFR Trade-off Matrix

| NFR | Architectural Implication | Conflicts With |
|---|---|---|
| **Performance** | Few, large components; same machine; replication | Maintainability (small components) |
| **Security** | Layered; innermost layers most protected | Performance (multiple validation layers add latency) |
| **Safety** | Safety logic concentrated in one component | Maintainability (concentration reduces modularity) |
| **Availability** | Redundant, hot-swappable components | Cost, performance (replication overhead) |
| **Maintainability** | Fine-grain, self-contained, decoupled components | Performance (more inter-component communication) |

### Architectural Evaluation

- True test is **runtime system behavior** — hard to assess pre-deployment.
- Evaluate by **comparing against reference architectures** and established patterns.
- Use Bosch's (2000) non-functional characteristic descriptions of patterns as an evaluation guide.

---

## 8. Exam Prep — Top 10 High-Yield Facts for HUST

> [!example] Top 10 High-Yield Facts

**1.** Architectural design is the **critical link between requirements engineering and detailed design**; it is the **first stage of software design**.

**2.** **Non-functional requirements** (performance, security, availability, maintainability) are primarily determined by **system architecture**, not individual component implementations.

**3.** Krutchen's **4+1 view model** consists of: Logical (key abstractions), Process (run-time interactions), Development (decomposition for teams), Physical (hardware mapping), unified by Use Cases (+1).

**4.** The **Layered pattern** supports: incremental development, replaceability (stable interfaces), portability (only inner machine-dependent layers need porting), and multi-level security. Its weakness: clean separation is hard; performance suffers from multiple interpretation levels.

**5.** The **Repository pattern** uses a central data store so components are decoupled from each other; its active variant (the **Blackboard**) triggers components when relevant data arrives — suitable for AI/data-driven systems.

**6.** In **Client–Server**, clients know server identities; **servers do not need to know client identities**. Clients use a request-reply protocol (e.g., HTTP).

**7.** The **Pipe and Filter** pattern is **unsuitable for interactive systems** with graphical UIs because event-driven I/O (mouse clicks, menus) cannot be modeled as a simple stream.

**8.** **Performance vs. Maintainability** is the canonical architectural trade-off: large components = better performance; small fine-grain components = better maintainability.

**9.** A **transaction** is an **atomic unit of database work** — all operations must complete or none take effect, ensuring database consistency even on partial failure.

**10.** A compiler can use either a **pipe-and-filter** model (for batch compilation) or a **repository** model (for integrated IDEs where changes in one tool must immediately reflect in others).

---

## 9. Exam Prep — 5 Complex Discussion Questions

> [!question] Discussion Question 1 — Pattern Selection Justification
> A hospital is building a system to manage patient records, accessible from many workstations across multiple wards, with strict access control, the ability to add new reporting tools without disrupting operations, and a requirement for 99.9% uptime. Identify and justify **two or more architectural patterns** that should be combined, explaining how each addresses a specific system requirement.
>
> **Guidance:** Discuss Layered (security, multi-level access), Repository (shared data, new tool integration), and Client–Server (distributed access, server replication for availability). Address how the patterns interact and what trade-offs remain.

---

> [!question] Discussion Question 2 — 4+1 View Model Application
> For the MHC-PMS (Mental Health Care Patient Management System), describe what each of the four Krutchen views would contain and which stakeholder would primarily use each view. Explain why no single view is sufficient to fully specify the system architecture.
>
> **Guidance:** Logical → domain classes (patient, appointment, prescription); Process → login/session management, concurrent access; Development → component breakdown for dev teams; Physical → web server, app server, DB server nodes. Explain that each view answers different questions and audiences.

---

> [!question] Discussion Question 3 — Architectural Conflict Resolution
> A financial trading platform requires: (a) sub-millisecond transaction response times, (b) a secure audit trail, (c) the ability to add new trading algorithms without system downtime. Identify the architectural conflicts between these three requirements and propose a coherent architecture that achieves an acceptable compromise.
>
> **Guidance:** (a) demands few, large, co-located components — conflicts with (c) fine-grain, modular components. (b) demands layered security with validation overhead — conflicts with (a). Propose a core high-performance subsystem (large components, in-memory data) isolated from a modular algorithm plugin subsystem (repository or microkernel), with a security layer at the system boundary.

---

> [!question] Discussion Question 4 — Repository vs. Pipe-and-Filter for Compilers
> Garlan and Shaw (1993) note that compilers can be implemented as either a pipe-and-filter architecture or as a repository architecture. Compare both in terms of (a) structure, (b) suitability for batch vs. interactive environments, and (c) the trade-offs a team building an IDE should consider when choosing between them.
>
> **Guidance:** Pipe-and-filter: sequential phases, simple data flow, good for batch but requires one phase to complete before the next; changes not immediately visible to other tools. Repository: shared symbol table and AST; tools can react immediately to updates (syntax-directed editor, debugger); better for interactive IDEs but adds shared schema dependency.

---

> [!question] Discussion Question 5 — When NOT to Use an Architectural Pattern
> Sommerville notes that the **pipe-and-filter pattern is unsuitable for interactive systems** and that the **layered architecture is hard to implement cleanly in practice**. Using these observations, articulate a general principle for when an architectural pattern is inappropriate, and describe how an architect should respond when a chosen pattern proves to be a poor fit mid-project.
>
> **Guidance:** Patterns are inappropriate when their structural assumptions conflict with fundamental system characteristics (e.g., event-driven I/O vs. stream processing). Mid-project: use different patterns for different subsystems (pattern mixing), isolate the ill-fitting area behind an abstraction layer, and avoid full architectural refactoring (expensive). Reference the cost of architectural vs. component refactoring.

---

## 10. Key Points Summary (from Textbook)

> [!summary] Textbook Key Points — Chapter 6

- A software architecture is a description of how a software system is organized. Properties such as **performance, security, and availability** are influenced by the architecture used.
- Architectural design decisions include: type of application, distribution, architectural styles, and documentation/evaluation approach.
- Architectures may be documented from several views: **conceptual, logical, process, development, physical**.
- **Architectural patterns** reuse knowledge about generic system organizations; they describe the architecture, when to use it, and its advantages and disadvantages.
- Commonly used patterns: **MVC, Layered, Repository, Client–Server, Pipe and Filter**.
- Generic application architecture models help understand, compare, validate, and assess component reuse for systems of the same type.
- **Transaction processing systems** allow remote access and modification of database information by multiple users; examples include information systems and resource management systems.
- **Language processing systems** translate texts between languages and execute instructions; they include a **translator** and an **abstract machine** (interpreter or hardware processor).
<<<<<<< HEAD
=======

---

[[Chapter5_Comprehensive|← Previous: Chapter 5 – System Modeling]] | [[Chapter7_Comprehensive|→ Next: Chapter 7 – Design and Implementation]] | [[Software Engineering Hub|Hub]]
>>>>>>> 4e0b62081cbb4de5280aecd60424a255a9cd6ec1
