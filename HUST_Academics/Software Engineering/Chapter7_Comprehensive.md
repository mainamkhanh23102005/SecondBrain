---
tags: [software-engineering, design, implementation, UML, design-patterns, HUST, chapter7, exam-prep]
chapter: 7
source: Software Engineering 9th Edition – Sommerville
created: 2026-05-19
---

# Chapter 7 – Design and Implementation: Zero-Loss Comprehensive Notes

> [!abstract] Executive Summary
> **Design and implementation** are the stage where abstract requirements become a concrete, executable system. This chapter has two tightly coupled goals:
> 1. **Show how** system modeling and architectural design (Chapters 5–6) are translated into a working object-oriented design using the UML.
> 2. **Introduce implementation concerns** — reuse, configuration management, host-target development, and open-source development — that are critical in professional practice but rarely covered in programming textbooks.
>
> The key insight: design and implementation are **not sequential** — they are deeply interleaved, iterative activities. Design decisions influence what is implementable; implementation realities feed back and refine the design. Getting this interplay right is the hallmark of experienced software engineering.

---

## 1. Executive Summary — Why Design & Implementation Matter Together

<<<<<<< HEAD
| Concern | Core Principle |
|---|---|
| **Design–Implementation Coupling** | Design decisions must consider implementation feasibility; implementation choices may force design revision. They are inherently interleaved. |
| **Language Choice Affects Design Method** | UML is valuable for OO languages (Java, C#); less useful for dynamic languages (Python); irrelevant for COTS configuration. |
| **Buy vs. Build Decision** | Early in any project, assess whether COTS systems can meet requirements. Adapting existing software is almost always cheaper and faster than building from scratch. |
| **Object-Oriented Advantages** | OO systems are easier to change because objects encapsulate both data and operations — modifying one object should not affect others. |
| **Reuse First Mindset** | Before designing anything, search for reusable components, patterns, and systems. Reuse should be the default, not the exception. |
=======
| Concern                                   | Core Principle                                                                                                                                                      |
| ----------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Design–Implementation Coupling**        | Design decisions must consider implementation feasibility; implementation choices may force design revision. They are inherently interleaved.                       |
| **Language Choice Affects Design Method** | UML is valuable for OO languages (Java, C#); less useful for dynamic languages (Python); irrelevant for COTS configuration.                                         |
| **Buy vs. Build Decision**                | Early in any project, assess whether COTS systems can meet requirements. Adapting existing software is almost always cheaper and faster than building from scratch. |
| **Object-Oriented Advantages**            | OO systems are easier to change because objects encapsulate both data and operations — modifying one object should not affect others.                               |
| **Reuse First Mindset**                   | Before designing anything, search for reusable components, patterns, and systems. Reuse should be the default, not the exception.                                   |
>>>>>>> 4e0b62081cbb4de5280aecd60424a255a9cd6ec1

---

## 2. Core Concepts — Technical Term Glossary

| Term | Definition |
|---|---|
| **Object-Oriented Design (OOD)** | A design process that identifies the object classes in a system and the relationships between them, based on system requirements. |
| **Object Class** | A template defining the attributes (data) and operations (behavior) shared by all objects of that type. |
| **System Context Model** | A structural model showing the other systems in the environment of the system being developed. |
| **Interaction Model** | A dynamic model showing how the system interacts with its environment as it is used. |
| **Use Case** | A named interaction between the system and an external actor (user or other system); the unit of interaction description. |
| **Subsystem Model** | A static (structural) model showing logical groupings of objects into coherent subsystems (represented as UML packages). |
| **Sequence Diagram** | A dynamic (behavioral) UML model showing the time-ordered sequence of messages exchanged between objects for a specific scenario. |
| **State Machine / State Diagram** | A dynamic model describing how an individual object or subsystem changes state in response to events (Harel, 1987). |
| **Structural Model** | Describes the static structure of a system: classes, attributes, operations, and their relationships (generalization, association, composition). |
| **Dynamic Model** | Describes the behavioral structure: interactions, state changes, and sequences of service requests between objects. |
| **Interface Specification** | A precise definition of the signatures and semantics of services provided by an object or group of objects. |
| **UML Interface Stereotype** | In UML, an interface is represented as a class diagram with the `«interface»` label and no attribute section. |
| **Design Pattern** | A named, well-documented description of a proven solution to a recurring design problem, capturing both the solution template and its trade-offs. |
| **Gang of Four (GoF)** | Gamma, Helm, Johnson, Vlissides — authors of the canonical patterns book (1995) defining 23 general-purpose OO design patterns. |
| **Observer Pattern** | A GoF pattern that separates the display of object state from the object itself; all displays are notified and updated automatically when state changes. |
| **Façade Pattern** | A GoF pattern that provides a simplified unified interface to a set of interfaces in a subsystem. |
| **Iterator Pattern** | A GoF pattern providing a standard way to traverse a collection's elements without exposing the internal representation. |
| **Decorator Pattern** | A GoF pattern allowing functionality to be added to an object dynamically at run-time. |
| **Software Reuse** | Using existing software artefacts — at abstraction, object, component, or system level — to construct new systems. |
| **COTS (Commercial Off-The-Shelf)** | Ready-made software products that can be bought and configured to meet user requirements. |
| **Configuration Management** | The general process of managing change in an evolving software system: version management, system integration, and problem tracking. |
| **Version Management** | Tracking the different versions of software components and coordinating multi-developer work. |
| **System Integration** | Defining which component versions compose each system build, then compiling and linking them automatically. |
| **Problem Tracking** | Allowing users to report bugs and enabling developers to track fix progress. |
| **Host-Target Development** | A development model where software is developed on one machine (host) but executed on another (target). |
| **Development Platform** | The hardware + OS + IDE + tools used to write and build the software. |
| **Execution Platform** | The hardware + OS + middleware on which the final software runs. |
| **Simulator** | A software tool that mimics the target hardware environment on a development machine; speeds up embedded systems development but is expensive to build. |
| **IDE (Integrated Development Environment)** | A set of integrated software tools supporting editing, compiling, debugging, and testing within a common framework. |
| **UML Deployment Diagram** | A UML diagram showing how software components are physically deployed on hardware processors. |
| **Open Source Development** | An approach where source code is published and volunteer developers are invited to participate in development. |
| **Free Software Foundation (FSF)** | The organization (founded by Stallman) advocating that source code should always be freely available for users to examine and modify. |
| **GPL (GNU General Public License)** | A "reciprocal" open source license: using GPL-licensed code in your system obligates you to also release your system as open source. |
| **LGPL (GNU Lesser General Public License)** | A GPL variant allowing linking to open source components without requiring your own code to be open source; modifications to the licensed component must be published. |
| **BSD License** | A non-reciprocal license: you may use and modify open source code in proprietary systems without obligation to republish; you must acknowledge the original creator. |

---

## 3. Object-Oriented Design Using the UML — The Five-Stage Process

The OOD process is **not sequential** — all stages interleave and influence each other. Sommerville deliberately does not show it as a flowchart because that would misrepresent its iterative, creative nature.

```
Stage 1: Understand system context & external interactions
Stage 2: Design the system architecture
Stage 3: Identify the principal object classes
Stage 4: Develop design models
Stage 5: Specify component interfaces
```

### 3.1 Stage 1 — System Context and Interactions

**Why this stage is essential:** Before designing anything, you must understand what is *outside* the system. The system boundary determines:
- Which functionality is implemented inside the new system vs. delegated to adjacent systems.
- What data flows across the boundary and who initiates interactions.

Two complementary model types:

| Model Type | Kind | What It Shows |
|---|---|---|
| **System context model** | Structural (static) | Other systems in the environment and their associations with the target system. Uses association notation; cardinality shows multiplicity (e.g., 1 Control System → 1..n Weather Stations). |
| **Interaction model** | Dynamic | How the system interacts with the environment in use. Best represented as a **use case model** — abstract enough to avoid over-specification. |

**Wilderness Weather Station Example — System Context:**

```
Control System (1) ────── (1..n) Weather Station
Weather Information System (1) ────── (1..n) Weather Station
Satellite (1) ────── (1) Weather Station
```

**Weather Station Use Cases (Interaction Model):**

<<<<<<< HEAD
| Use Case | Description |
|---|---|
| Report Weather | Send summarized weather data to the weather information system |
| Report Status | Send hardware status information to the weather information system |
| Restart | If shut down, restart the system |
| Shutdown | Shut down the weather station |
| Reconfigure | Reconfigure the weather station software |
| Powersave | Enter power-saving mode |
| Remote Control | Send control commands to any weather station subsystem |
=======
| Use Case       | Description                                                        |
| -------------- | ------------------------------------------------------------------ |
| Report Weather | Send summarized weather data to the weather information system     |
| Report Status  | Send hardware status information to the weather information system |
| Restart        | If shut down, restart the system                                   |
| Shutdown       | Shut down the weather station                                      |
| Reconfigure    | Reconfigure the weather station software                           |
| Powersave      | Enter power-saving mode                                            |
| Remote Control | Send control commands to any weather station subsystem             |
>>>>>>> 4e0b62081cbb4de5280aecd60424a255a9cd6ec1

**Use Case Description — Structured Natural Language (Figure 7.3):**

| Field | Content |
|---|---|
| **System** | Weather station |
| **Use case** | Report weather |
| **Actors** | Weather information system, Weather station |
| **Data** | Summary: max/min/avg ground & air temperatures; max/min/avg air pressures; max/min/avg wind speeds; total rainfall; wind direction at 5-minute intervals. |
| **Stimulus** | Weather information system establishes a satellite link and requests transmission. |
| **Response** | Summarized data are sent to the weather information system. |
| **Comments** | Usually hourly reporting, but frequency is configurable and may vary per station. |

> [!important] Why Use Case Descriptions Matter
> Structured natural language descriptions force clarity about what data flows, who initiates the interaction, and what the system must do. This directly feeds Stage 3 (object identification): nouns in the description → candidate objects/attributes; verbs → candidate operations.

### 3.2 Stage 2 — Architectural Design

Using context and interaction models, identify the major subsystems and their communication infrastructure.

**Weather Station High-Level Architecture (Figure 7.4):**

```
Fault Manager      Configuration Manager      Power Manager
         \                 |                  /
          ──────── Communication Link ────────
         /                 |                  \
    Communications     Data Collection       Instruments
```

Key design decision: **broadcast messaging over a common communication link**.
- Each subsystem *listens* for messages on the shared link and picks up only those addressed to it.
- The sender does **not** need to know the identity of the target subsystem.
- **Benefit:** Easy to add or reconfigure subsystems — no sender changes required.
- This is distinct from the patterns in Chapter 6; it is a **message-bus / broadcast** style.

**Data Collection Subsystem Architecture (Figure 7.5):**
```
Data Collection
  ├── Transmitter
  ├── Receiver
  └── WeatherData    (producer–consumer pattern; see Chapter 20)
```

### 3.3 Stage 3 — Object Class Identification

This is the most difficult and creative stage. No single technique is sufficient; you must use multiple knowledge sources together.

**Three Approaches to Object Class Identification:**

| Approach | Technique | Originator |
|---|---|---|
| **1. Grammatical analysis** | Analyze natural language descriptions: nouns → objects/attributes; verbs → operations | Abbott (1983) |
| **2. Tangible entities** | Use real-world things (roles, events, interactions, locations, org units) | Coad & Yourdon (1990); Shlaer & Mellor (1988); Wirfs-Brock et al. (1990) |
| **3. Scenario-based** | Analyze use case scenarios; team identifies objects, attributes, operations per scenario | Beck & Cunningham (1989) |

> [!warning] No Single Approach Suffices
> In practice, you start with grammatical analysis of the informal description, then refine using domain knowledge, then validate through scenario analysis. Requirements documents, user interviews, and existing systems are all inputs.

**Weather Station Object Classes (Figure 7.6):**

| Class | Attributes | Operations |
|---|---|---|
| `WeatherStation` | `identifier` | `reportWeather()`, `reportStatus()`, `powerSave(instruments)`, `remoteControl(commands)`, `reconfigure(commands)`, `restart(instruments)`, `shutdown(instruments)` |
| `WeatherData` | `airTemperatures`, `groundTemperatures`, `windSpeeds`, `windDirections`, `pressures`, `rainfall` | `collect()`, `summarize()` |
| `GroundThermometer` | `gt_Ident`, `temperature` | `get()`, `test()` |
| `Anemometer` | `an_Ident`, `windSpeed`, `windDirection` | `get()`, `test()` |
| `Barometer` | `bar_Ident`, `pressure`, `height` | `get()`, `test()` |

**Why these objects?**
- `WeatherStation`: Encapsulates all external interactions (maps to use cases). A single interface class.
- `WeatherData`: Handles the "Report Weather" logic — collects and summarizes instrument data.
- Hardware instrument classes (`GroundThermometer`, `Anemometer`, `Barometer`): Directly represent tangible entities. They operate **autonomously** — collect data at a set frequency and store locally; deliver to `WeatherData` on request.

**Domain-knowledge refinement:** Weather stations are remote and instruments fail. Therefore:
- Add `test()` operations to detect instrument malfunction (automatic fault reporting).
- Add `identifier` attributes (many stations, each needs a unique ID).
- Next step: identify common features → design an `Instrument` superclass with shared attributes (`identifier`, collection frequency) and shared operations (`get()`, `test()`).

### 3.4 Stage 4 — Design Models

Design models are the **bridge between requirements and implementation**. They must balance two competing demands:
- **Abstract enough** to not obscure relationships with implementation noise.
- **Detailed enough** for programmers to make implementation decisions.

Solution: produce models at **multiple levels of detail**.

| Model Type | Kind | Description | Example |
|---|---|---|---|
| **Subsystem model** | Static | Logical groupings of objects into coherent subsystems (UML packages). | Figure 7.4 — weather station subsystems. |
| **Sequence model** | Dynamic | Time-ordered sequence of messages for a specific use case scenario. Read top-to-bottom. | Figure 7.7 — data collection sequence. |
| **State machine model** | Dynamic | How an object/subsystem changes state in response to events/messages. | Figure 7.8 — weather station state diagram. |

> [!warning] The Over-Modeling Danger
> "There is a danger in doing too much modeling. You should not make detailed decisions about the implementation that really should be left to the system programmers." — Sommerville.
> The UML supports 13 diagram types; rarely use all of them. **Minimize models to reduce cost and time.**

**Sequence Diagram — Report Weather Use Case (Figure 7.7):**

Read top-to-bottom. Two arrowhead styles:
- **Stick arrowhead (→):** Asynchronous — sender does **not** wait for a reply; continues processing.
- **Squared arrowhead (▬→):** Synchronous — sender suspends and waits for a reply.

```
WeatherInfoSystem → SatComms: request(report)          [async]
SatComms → WeatherInfoSystem: acknowledge              [async]
SatComms → WeatherStation: reportWeather()             [async]
WeatherStation → Commslink: get(summary)               [sync — waits]
Commslink → WeatherData: summarize()                   [sync — waits]
WeatherData → Commslink: weather summary               [reply]
Commslink → WeatherStation: reply                      [reply]
WeatherStation → SatComms: send(report)                [reply]
SatComms → WeatherInfoSystem: reply(report)            [reply]
```

> [!tip] Practical Rule
> Produce one sequence diagram per significant use case. If you have a use case model, you need a matching sequence model for each major use case.

**State Diagram — Weather Station (Figure 7.8):**

States and transitions:

| From State | Event/Message | To State |
|---|---|---|
| *(Initial)* | — | **Shutdown** |
| Shutdown | `restart()` | Running |
| Shutdown | `reconfigure()` or `powerSave()` | Configuring |
| Configuring | configuration done | Shutdown |
| Running | `shutdown()` | Shutdown |
| Running | `reportWeather()` | Summarizing |
| Summarizing | weather summary complete | Transmitting |
| Transmitting | transmission done | Running |
| Running | `reportStatus()` | Testing |
| Testing | test complete | Transmitting |
| Running | clock signal | Collecting |
| Collecting | collection done | Running |
| Running | `remoteControl()` | Controlled |

> [!important] When to Use State Diagrams
> State diagrams add value for objects/subsystems with complex, event-driven behavior. Many objects in a system are simple and do not need state models — use them selectively for the most behavior-rich components.

### 3.5 Stage 5 — Interface Specification

**Why interface specification matters:** Interfaces allow subsystems and objects to be developed **in parallel** by different teams. Once an interface is defined, other developers can code against it without waiting for implementation.

**Rules for interface design:**
1. Do **not** include data representation details (no attributes in the interface class).
2. Do include **accessor and mutator operations** for all needed data.
3. Data representation is hidden → it can change without affecting clients (maintainability).

**UML Interface Notation:**
```
«interface»
InterfaceName
──────────────
operationA(param): ReturnType
operationB(param): ReturnType
```

**Weather Station Interfaces (Figure 7.9):**

```
«interface»                          «interface»
Reporting                            RemoteControl
──────────────────────────           ──────────────────────────────────
weatherReport(WS-Ident): Wreport     startInstrument(instrument): iStatus
statusReport(WS-Ident): Sreport      stopInstrument(instrument): iStatus
                                     collectData(instrument): iStatus
                                     provideData(instrument): string
```

**Key insight — N:M relationship between objects and interfaces:**
- One object can implement **multiple interfaces** (different viewpoints on its methods).
- Multiple objects can be accessed through a **single interface**.
- In Java: interfaces are declared separately; classes `implement` them.
- Example: The `remoteControl()` method in `WeatherStation` maps to all four operations in the `RemoteControl` interface — the individual operations are encoded in the command string parameter.

---

## 4. Design Patterns — Reusing Design Knowledge

### 4.1 What Is a Design Pattern?

Originated from Christopher Alexander's architectural work (1977): patterns of building design that are "inherently pleasing and effective." Transferred to software by the Gang of Four (Gamma et al., 1995).

> A pattern is a **description of accumulated wisdom and experience** — a well-tried solution to a common problem that can be reused in different settings. It is NOT a detailed specification; it is a **template** for a solution.

**The Four Essential Elements (GoF definition):**

| Element | Description |
|---|---|
| **Name** | A meaningful, vocabulary-building reference. Speaking in pattern names communicates design intent precisely. |
| **Problem description** | Explains when the pattern applies: motivation (why it's useful) and applicability (conditions for use). |
| **Solution description** | A template (not a concrete design) for solving the problem — the structure, participants, collaborations, and implementation. Often expressed graphically (UML class diagram). |
| **Consequences** | Results and trade-offs of applying the pattern. Helps the designer judge applicability for their situation. |

### 4.2 The Observer Pattern — Deep Dive

**Problem:** You need multiple, independent displays of the same object's state. The displays may not be known when the state object is designed. When state changes, ALL displays must update automatically, with minimal coupling between the state object and the displays.

**Solution:**

```
Subject ────────────────────────── Observer
──────────────────────             ──────────────
Attach(Observer)                   Update()
Detach(Observer)
Notify()
  for all o in observers:
    o -> Update()
          │
          ↓ inherits          ↓ inherits
ConcreteSubject            ConcreteObserver
──────────────             ──────────────────────────
GetState()                 Update()
subjectState                 observerState = subject->GetState()
  return subjectState        observerState
```

**Participants:**
- `Subject` (abstract): Maintains list of observers; provides `Attach()`, `Detach()`, `Notify()`.
- `Observer` (abstract): Defines the `Update()` interface.
- `ConcreteSubject`: Holds the actual state; calls `Notify()` when state changes; `GetState()` lets observers pull updated state.
- `ConcreteObserver`: Maintains a local copy of the subject state; implements `Update()` to synchronize its copy via `GetState()`, then refreshes its display.

**Consequences (Trade-offs):**

| Benefit | Cost |
|---|---|
| Minimal coupling: Subject knows only the abstract `Observer` interface, not concrete observers. | Display performance optimizations are impractical because Subject cannot know what observers are doing. |
| Open/closed: New observer types (displays) can be added without changing Subject. | A single state change may trigger a cascade of linked updates to all observers, some potentially unnecessary. |

**Real-world applications:**
- MVC: Model is the Subject; Views are Observers.
- Event systems, pub-sub messaging, reactive UI frameworks.

### 4.3 Four Key GoF Patterns — Summary Table

| Pattern | Problem | Solution | Example Use |
|---|---|---|---|
| **Observer** | Notify multiple objects when another object's state changes | Subject maintains a list of Observers; calls `Update()` on all when state changes | MVC Views, event listeners, dashboards |
| **Façade** | Tidy up interfaces to a subsystem developed incrementally | Provide a single simplified interface to a complex subsystem | Database access layers, API wrappers |
| **Iterator** | Access elements of a collection without exposing internal representation | Define a standard traversal interface | Java `Iterator`, Python `__iter__` |
| **Decorator** | Add functionality to an existing class at run-time | Wrap the object in a Decorator that adds behavior while delegating to the original | Java I/O streams, middleware pipelines |

### 4.4 Why Patterns Are Powerful — And Why They Are Hard

**Patterns support high-level, conceptual reuse** — fundamentally different from component reuse:
- Component reuse: constrained by specific algorithms, interfaces, types. Conflicts with your design mean you can't reuse or introduce inefficiencies.
- Pattern reuse: you reuse the **idea**; you adapt the **implementation** to your system. Full freedom.

**Why patterns are hard for beginners:**
1. You must **recognize** a problem situation as matching a known pattern. This requires design experience.
2. The 23 GoF patterns cover general-purpose problems. Domain-specific problems may need domain-specific patterns from specialist pattern catalogs (Buschmann et al., 1996–2007; Schmidt et al., 2000).
3. In practice, patterns are discovered during design by experience: "develop a design, experience a problem, then recognize a pattern can be used."

> [!tip] How to Build Pattern Intuition
> Study the 23 GoF patterns deeply. For each: know the problem, the structure, the consequences. Then read real code that uses them. Pattern recognition is a skill built by exposure — not by reading pattern books once.

---

## 5. Implementation Issues

### 5.1 Reuse — The Default Strategy

**Historical shift:** Before the 1990s, all software was built from scratch (only language library reuse). Cost and schedule pressure made this unviable for commercial/Internet systems. Today, **reuse is the primary development strategy**.

**Four Levels of Software Reuse:**

| Level | What Is Reused | How |
|---|---|---|
| **Abstraction level** | Design knowledge (patterns, architectural patterns) | Apply the pattern structure; no direct code reuse |
| **Object level** | Objects and methods from a library | Use library classes directly (e.g., JavaMail for email processing) |
| **Component level** | Collections of objects operating together | Adapt and extend a component/framework (e.g., UI framework for display management, adding your own layout and data connections) |
| **System level** | Entire application systems | Configure, adapt, or integrate COTS systems (e.g., SAP ERP; most commercial systems built this way) |

**Benefits of reuse:**
- Faster development
- Lower development risk (reused code is already tested)
- Higher reliability (tested in other applications)
- Reduced cost

**Costs of reuse (often underestimated):**

| Cost | Explanation |
|---|---|
| **Search and assessment** | Finding suitable software, evaluating fit, testing compatibility with your environment takes time. |
| **Purchase cost** | Large COTS systems can be very expensive. |
| **Adaptation and configuration** | Reusable components rarely fit perfectly; customization has a cost. |
| **Integration cost** | Components from different providers may make conflicting assumptions, making integration difficult and expensive. |

> [!important] Strategic Principle
> Consider reuse **before** detailed design begins. You may need to modify your requirements or design to make best use of available reusable assets. In many domains, software engineering **is** software reuse engineering.

### 5.2 Configuration Management — Managing Change

**Why it is essential:** Change is constant in software development. Without CM, developers overwrite each other's work, use wrong component versions, and cannot recover from failures.

**Three Core CM Activities:**

| Activity | Purpose | Example Tools |
|---|---|---|
| **Version management** | Track all versions of all components; prevent one developer's changes from overwriting another's. | Git, Subversion (SVN) |
| **System integration** | Define which component versions constitute each system build; compile and link automatically. | GNU make, build systems, CI/CD pipelines |
| **Problem tracking** | Allow users to report bugs; allow developers to track, assign, and resolve issues. | Bugzilla, GitHub Issues, Jira |

**Tool categories:**
- **Comprehensive CM systems** (e.g., IBM ClearCase): All three activities in one integrated system with a unified user interface and shared code repository.
- **Separate tools** in an IDE: Version control (Git), build system (make/Maven/Gradle), issue tracker (Bugzilla). More flexible, widely used in open-source and agile teams.

> [!note] See Chapter 25
> Configuration management is critical enough to warrant its own full chapter (Chapter 25). The treatment here is introductory.

### 5.3 Host-Target Development

**The model:** Software is written and compiled on the **host** (development platform) but runs on the **target** (execution platform).

**Why they differ:** Target systems may be embedded hardware, different OS, or production servers with restricted software licenses. You cannot always install the production runtime on your development machine.

**Deployment decisions for distributed systems:**

| Decision Factor | Explanation |
|---|---|
| **Hardware/software requirements** | A component designed for a specific architecture or OS must be deployed on a compatible platform. |
| **Availability requirements** | High-availability: deploy components on multiple platforms so that a platform failure doesn't bring down the whole system. |
| **Component communication** | High inter-component traffic → co-locate components on the same platform or nearby platforms to minimize latency. |

**Development platform tools:**

| Tool Category | Examples |
|---|---|
| Compiler + syntax editor | GCC, LLVM, IntelliJ |
| Debugger | GDB, IDE-integrated debuggers |
| Graphical editing tools | PlantUML, Rational Rose, draw.io |
| Test automation | JUnit, pytest, NUnit |
| Project management | Version control integration, task management |
| Static analyzers | SonarQube, Coverity (see Chapter 15) |
| Change/configuration management server | GitHub, GitLab, Bitbucket |

**Integrated Development Environment (IDE):**
- A unified framework hosting multiple tools.
- Language-specific IDEs (IntelliJ for Java) or general-purpose extensible IDEs (Eclipse with plugins).
- Eclipse is based on a **plug-in architecture** — specializable for any language or application domain.

**UML Deployment Diagrams:** Show software components deployed on hardware nodes; used to document and communicate target platform decisions. Especially important for distributed systems where component placement affects performance, availability, and cost.

---

## 6. Open Source Development

### 6.1 What Is Open Source Development?

Open source development publishes the system's **source code** and invites volunteers to contribute. Roots in the Free Software Foundation's philosophy that code should be freely available to examine and modify.

**Open source extended FSF by:**
- Using the Internet to recruit a **much larger** population of volunteer developers (many of whom are also users).
- In principle: anyone can report bugs, propose features, submit fixes.
- In practice: successful open source projects still have a **core control group** who govern changes.

**Key examples:** Linux, Java, Apache, MySQL. Major companies (IBM, Sun/Oracle) actively support and build on open source.

**Two strategic questions for companies:**

| Question | Depends On |
|---|---|
| Should our product **use** open source components? | Domain (are high-quality open source alternatives available?), existing system compatibility, timeline and cost constraints. |
| Should our product be developed **as** open source? | Business model (support/consulting vs. product licensing), confidentiality concerns, community potential. |

**Open source development is most successful for platform products**, not specialized application systems — fewer developers are interested in narrow-domain applications.

### 6.2 Open Source Licensing — Critical Legal Framework

**The key principle:** Even though source code is freely available, the original developer still **owns the code legally**. The license governs what others may do with it. Using the wrong license can obligate you to open-source your proprietary product.

**Three Primary License Models:**

| License | Type | Key Rule | Use in Proprietary Systems? |
|---|---|---|---|
| **GPL (GNU General Public License)** | Reciprocal ("copyleft") | If you use GPL code in your system, your **entire system** must be open-sourced. | No — will "infect" your code. |
| **LGPL (GNU Lesser General Public License)** | Weak reciprocal | You may link to LGPL components without open-sourcing your own code. BUT: if you *modify* the LGPL component, you must publish those modifications as open source. | Yes (linking), No (modifying). |
| **BSD License** | Non-reciprocal (permissive) | You may use, modify, and include BSD code in proprietary systems without obligation to republish. You **must** acknowledge the original creator. | Yes, freely. |

> [!warning] License Compliance Is a Legal Obligation
> Using GPL-licensed code in a product you intend to sell without open-sourcing it is a **copyright violation**. Many companies have been sued over this.

**Bayersdorfer's (2007) Six Practices for Open Source License Management:**

| # | Practice |
|---|---|
| 1 | Maintain a database of all open source components used, with a copy of each component's license **as it was at the time of use** (licenses can change). |
| 2 | Understand each component's license type before use; one component's license may allow proprietary use while another's does not. |
| 3 | Track evolution pathways of open source projects — understand how components might change and how that could affect your license obligations. |
| 4 | Educate developers about open source licensing — having procedures isn't enough if developers don't understand them. |
| 5 | Implement auditing systems — developers under deadline pressure may inadvertently violate license terms. |
| 6 | Participate in open source communities you rely on — contribute back to sustain the projects. |

**Business model shift:** The traditional model of selling specialized software is eroding. More companies are **open-sourcing their software** and selling support, maintenance, and consultancy. This trend accelerates as open source matures.

---

## 7. Deep-Dive Analysis — Trade-offs and Why Things Are Designed This Way

### 7.1 Why OO Design Interleaves Rather Than Sequences

Traditional structured design methods proposed a sequential cascade: requirements → architectural design → detailed design → implementation. The UML-based methods (arising from the merger of OO methods in the 1990s) **rejected this linearity** because:

1. **Objects are found incrementally**: The first pass at object identification is always incomplete. Implementation reveals missing objects, incorrect relationships, and design flaws that require revision.
2. **Interface decisions feed back**: Defining a clean interface for an object often reveals that the initial decomposition was wrong.
3. **Domain knowledge arrives late**: Users and domain experts clarify requirements during design and even during implementation.

The correct mental model: **concurrent spiral activities**, not a waterfall.

### 7.2 Why the Broadcast Architecture for the Weather Station?

The weather station uses a broadcast/message-bus architecture (subsystems listen on a shared communication link) instead of direct subsystem-to-subsystem messaging. Why?

**Direct messaging problem:** If the Communications subsystem sends a `shutdown()` message directly to each other subsystem, it must know the identity and interface of every other subsystem. Adding a new subsystem requires modifying Communications.

**Broadcast advantage:** Communications broadcasts `shutdown()` on the common link. Every subsystem independently listens and responds appropriately. Adding a new subsystem requires **zero changes** to existing subsystems.

**Trade-off:** Broadcast reduces coupling but may reduce message delivery guarantees (you must ensure all subsystems are listening). For a weather station, this is acceptable.

### 7.3 Why Interfaces Should Hide Data Representation

If you expose the internal data structure (e.g., weather data stored as an array), then every client that accesses the data is **coupled** to that representation. If you later change to a linked list (for performance), every client breaks.

By defining an interface that exposes only operations (not attributes), the representation becomes a private implementation detail. It can change freely without affecting clients. This is the **information hiding / encapsulation principle** applied at the interface level.

Exception noted by Sommerville: in **static structural models (class diagrams)**, it often makes sense to expose attributes because they convey essential characteristics of the object in the most compact way — this is for documentation purposes, not for client code coupling.

### 7.4 The Pattern Recognition Challenge

The 23 GoF patterns cover only "general-purpose" problems. For domain-specific problems:
- Pattern-Oriented Software Architecture series (Buschmann et al., 1996, 2007a, 2007b; Schmidt et al., 2000; Kircher & Jain, 2004) provides domain patterns.
- Hundreds of patterns exist across domains.

The critical skill is **pattern recognition in the problem space**, not pattern memorization. This is why Sommerville notes that inexperienced programmers find patterns hard to use — not because they don't know the patterns, but because they cannot recognize the problem shape that a pattern solves.

### 7.5 The Reuse Paradox

Reuse always has **hidden adaptation costs** that are easily underestimated:
- COTS systems rarely fit perfectly; the gap between what the COTS does and what you need must be bridged by configuration or extension code.
- Integration between components from different providers is particularly expensive because each provider made different, possibly incompatible, design assumptions.
- Testing reused components in your environment is mandatory — "it worked elsewhere" is not sufficient assurance.

This is why reuse must be considered **before** detailed design: if you discover mid-design that a COTS system almost-but-not-quite fits your requirements, it may be cheaper to adjust your requirements to fit the COTS than to build a custom solution.

---

## 8. Exam Prep — Top 10 High-Yield Facts for HUST

> [!example] Top 10 High-Yield Facts

**1.** Design and implementation are **interleaved, not sequential** activities. Design decisions must consider implementation feasibility; implementation realities feed back into design revision.

**2.** OOD has **five stages**: (1) system context/interactions, (2) architectural design, (3) object class identification, (4) design models, (5) interface specification — but they are concurrent and iterative, not a waterfall.

**3.** A **system context model** is structural (static); an **interaction model** is dynamic. Use cases are the recommended form for interaction models — abstract enough to avoid over-specification.

**4.** The **three approaches to object class identification** are: grammatical analysis (nouns → objects, verbs → operations), tangible entities in the application domain, and scenario-based analysis of use cases.

**5.** The **four GoF design pattern elements** are: name, problem description, solution description (a template, not a concrete design), and consequences (trade-offs). Knowing all four elements is what separates a pattern from a mere technique.

**6.** The **Observer pattern** separates state from display: `Subject` maintains observers and calls `Update()` on all of them when state changes; `ConcreteObserver` maintains a copy of the state and refreshes its display. Minimal coupling is the key benefit.

**7.** **Software reuse levels**: abstraction (patterns), object (libraries), component (frameworks), system (COTS). Reuse must be considered *before* detailed design, not after.

**8.** The **three CM activities**: version management (track/coordinate versions), system integration (define builds), problem tracking (bug reporting and resolution).

**9.** The **three open source license models**: GPL (reciprocal — "copyleft," use = must open-source your system), LGPL (weak reciprocal — linking OK but modifications must be published), BSD (non-reciprocal — use freely in proprietary systems, must acknowledge creator).

**10.** **Host-target development**: software is *developed* on the host platform and *executed* on the target platform. For embedded systems, **simulators** mimic target hardware on the host — expensive to build but speed up development by avoiding constant hardware deployment.

---

## 9. Discussion Questions — Exam Practice

> [!question] Discussion Question 1 — Design vs. Implementation Interleaving
> Sommerville states that design and implementation are "invariably interleaved." Give two concrete examples from the weather station case study where an implementation decision would feed back and require a revision to the design. Why does this make a purely sequential design-then-implement methodology unsuitable for most real-world projects?
>
> **Guidance:** Example 1 — discovering that `WeatherStation.remoteControl(commands)` needs separate encoding of four operations reveals an interface design need for the `RemoteControl` interface. Example 2 — choosing a broadcast communication link at implementation time reveals that the architectural model must be updated to show the shared link explicitly. Waterfall methodology is unsuitable because it locks in designs before implementation reveals constraints.

> [!question] Discussion Question 2 — When to Use Which Design Model
> Given that the UML supports 13 diagram types, Sommerville recommends minimizing the number of models produced. For the weather station, which three model types are most valuable, and why? Under what conditions would a state diagram be unnecessary for a particular object?
>
> **Guidance:** The three most valuable are subsystem models (for architectural overview), sequence diagrams (for each significant use case), and state machine models (for behaviorally complex objects/subsystems). A state diagram is unnecessary for objects with simple or purely reactive behavior — e.g., a `Barometer` whose only behavior is `get()` and `test()` does not need one.

> [!question] Discussion Question 3 — GPL Compliance Scenario
> A startup builds a commercial web application. They use an open source library licensed under the GPL for PDF generation. The startup's lawyers discover this after launch. What are the implications? What should the company do now, and what should they do in future projects to prevent this?
>
> **Guidance:** Implications: the GPL obligates them to release their entire application as open source (or negotiate a commercial license with the copyright holder if one exists). Remediation: either replace the GPL library with an LGPL/BSD alternative, purchase a commercial license from the library author, or open-source the product. Prevention: implement Bayersdorfer's six practices — especially maintaining a component license database and educating developers before use.

> [!question] Discussion Question 4 — Object Class Identification Methods
> Compare the three approaches to object class identification: grammatical analysis, tangible entities, and scenario-based analysis. Why does Sommerville advocate using all three rather than one? Illustrate using an example beyond the weather station.
>
> **Guidance:** Grammatical analysis is fast but language-dependent (ambiguity in natural language leads to missing objects). Tangible entities grounds design in the real world but misses abstract system objects (like `WeatherData`). Scenario-based (use case) analysis is most thorough but expensive. Example: for a library system — grammatical analysis gives `Book`, `Member`, `Loan`; tangible entities give `Shelf`, `LibraryCard`; scenario analysis of "overdue fine notification" reveals `FineCalculator` and `NotificationService` that neither of the other approaches surfaces.

> [!question] Discussion Question 5 — The Reuse Trade-off
> A development team is building an HR system. They found an open source HR COTS package that covers 80% of their requirements. The remaining 20% involves a custom appraisal workflow unique to their organization. Analyze the reuse decision: what are the key factors, what should they investigate, and what risks should they flag?
>
> **Guidance:** Factors: license type (GPL would force open-sourcing their customizations), extensibility API of the COTS (can the appraisal workflow be added without modifying the core?), integration with existing payroll systems. Investigation: check COTS license; prototype the customization to assess cost; assess integration complexity. Risks: adaptation cost may exceed build cost; future COTS upgrades may break customizations; vendor lock-in; the "80/20" gap may be the hardest 20% technically.

---

## 10. Key Points Summary (from Textbook)

> [!summary] Textbook Key Points — Chapter 7

- Software design and implementation are **interleaved** activities. The level of detail in the design depends on the type of system and whether a plan-driven or agile approach is used.
- The OOD process includes: designing the system architecture, identifying objects in the system, describing the design using object models, and documenting component interfaces.
- A range of models may be produced: **static models** (class, generalization, association) and **dynamic models** (sequence, state machine).
- **Component interfaces** must be defined precisely so that other objects can use them. A UML interface stereotype may be used.
- When developing software, always consider the possibility of **reusing** existing software: as components, services, or complete systems.
- **Configuration management** is the process of managing changes to an evolving software system. It is essential when a team is developing software cooperatively.
- Most software development is **host-target**: develop on the host IDE; execute on the target machine.
- **Open source development** involves making source code publicly available, allowing many people to propose changes and improvements.

---

## 11. Further Reading

| Resource | Authors | Notes |
|---|---|---|
| *Design Patterns: Elements of Reusable Object-oriented Software* | Gamma, Helm, Johnson, Vlissides (1995) | The original GoF patterns handbook. 23 foundational patterns. |
| *Applying UML and Patterns* (3rd ed.) | Larman (2004) | Clear introduction to OO design with UML; excellent coverage of patterns in practice. |
| *Producing Open Source Software* | Fogel (2008) | Comprehensive guide to open source background, licensing, and running open source projects. |
| *Pattern-Oriented Software Architecture* Vol. 1–5 | Buschmann et al. (1996–2007); Schmidt et al. (2000); Kircher & Jain (2004) | Domain-specific pattern catalogs: distributed computing, concurrent & networked objects, resource management, pattern languages. |

---

<<<<<<< HEAD
[[Chapter6_Comprehensive|← Previous: Chapter 6 – Architectural Design]] | [[Software Engineering Hub|Hub]]
=======
[[Chapter6_Comprehensive|← Previous: Chapter 6 – Architectural Design]] | [[Chapter8_Comprehensive|→ Next: Chapter 8 – Software Testing]] | [[Software Engineering Hub|Hub]]
>>>>>>> 4e0b62081cbb4de5280aecd60424a255a9cd6ec1
