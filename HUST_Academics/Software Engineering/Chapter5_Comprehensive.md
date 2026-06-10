---
tags: [software-engineering, UML, system-modeling, HUST, chapter5, exam-prep]
chapter: 5
source: Software Engineering 9th Edition – Sommerville
created: 2026-06-01
---

# Chapter 5 – System Modeling: Zero-Loss Comprehensive Notes

> [!abstract] Executive Summary
> **System modeling** is the process of building abstract models of a system, each representing a different perspective (context, interaction, structure, behavior). These models serve three purposes across the engineering lifecycle:
> 1. **Facilitate discussion** — informal, incomplete models stimulate design conversations among developers.
> 2. **Document existing systems** — partial but correct representations of what a system currently does.
> 3. **Drive implementation** — complete, formal models used as the basis for generating source code (MDE/MDA).
>
> The unifying language is the **Unified Modeling Language (UML)**, and experience shows that five diagram types cover the essentials of any system: Activity, Use Case, Sequence, Class, and State diagrams.

---

## 1. Executive Summary — Why System Models Matter

| Concern | Core Principle |
|---|---|
| **Abstraction, Not Representation** | A model deliberately simplifies a system; it picks out salient characteristics, unlike a translation (which preserves everything). |
| **Multiple Perspectives Needed** | No single diagram type captures all system properties. Context, interaction, structure, and behavior each reveal different things. |
| **Use in RE and Design** | Models of the *existing* system ground requirements elicitation; models of the *new* system communicate proposed requirements and drive design. |
| **MDE Potential** | When models are complete and formal, tools can automatically generate implementation code — raising the level of abstraction in engineering. |
| **Flexibility in Notation** | The required rigor of a UML model depends on how it will be used. Agile modeling uses informal, sketch-level notation; code-generation requires full precision. |

> [!quote] Abstraction vs. Representation
> A *model* deliberately simplifies — it is an abstraction. A *representation* (e.g., a translation) maintains all information. Engineers build models, not representations.

---

## 2. Core Concepts — Technical Term Glossary

| Term | Definition |
|---|---|
| **System Model** | An abstract description of a system from one or more perspectives, expressed in a graphical notation (typically UML). |
| **UML (Unified Modeling Language)** | A set of 13 diagram types, standardized since the 1990s, that is the universal language for software system modeling. |
| **Context Model** | A model showing the system's external environment and the other systems it interacts with; used to establish system boundaries. |
| **Interaction Model** | A model showing how a system interacts with its environment (use cases) or how internal components communicate (sequence diagrams). |
| **Structural Model** | A model showing the static organization of system components — their classes, attributes, operations, and associations. |
| **Behavioral Model** | A model showing the dynamic behavior of a system: how it responds to data inputs (data-driven) or external/internal events (event-driven). |
| **Use Case** | A simple scenario describing what a user expects from a system; models discrete tasks involving external interaction. |
| **Actor** | An external entity (human or other system) that interacts with the system being modeled. |
| **Sequence Diagram** | A UML diagram showing the chronological sequence of interactions between actors/objects during a specific use case. |
| **Lifeline** | A dotted vertical line in a sequence diagram representing the time an object instance is involved in a computation. |
| **Class Diagram** | A UML diagram showing object classes and the associations (relationships) between them. |
| **Association** | A structural link between two classes indicating a relationship; can be annotated with multiplicities and role names. |
| **Multiplicity** | Annotation on an association end indicating how many objects participate (e.g., `1`, `1..*`, `*`). |
| **Generalization** | An association type (arrow pointing to superclass) that indicates inheritance; sub-classes inherit attributes and operations. |
| **Aggregation** | A special association (diamond on the "whole" class) indicating a whole-part composition relationship. |
| **Activity Diagram** | A UML diagram showing activities in a process and the flow of control between them; used for context models and data-driven behavioral models. |
| **State Diagram** | A UML diagram showing system states and the stimuli that cause transitions between them; used for event-driven behavioral models. |
| **Superstate** | A composite state in a state diagram that encapsulates multiple sub-states; enables hierarchical modeling to manage complexity. |
| **Data-Flow Diagram (DFD)** | A pre-UML notation showing how data moves through processing steps; UML 2.0 activity diagrams are its modern equivalent. |
| **Model-Driven Engineering (MDE)** | An approach where models (not programs) are the primary development artifact; code is automatically generated from formal models. |
| **Model-Driven Architecture (MDA)** | The OMG's specific MDE approach, defining three model levels: CIM, PIM, and PSM. |
| **CIM (Computation Independent Model)** | Describes domain abstractions without reference to implementation; also called a domain model. |
| **PIM (Platform Independent Model)** | Describes system operation without reference to an execution platform; typically expressed using UML structural and behavioral diagrams. |
| **PSM (Platform Specific Model)** | A PIM transformed for a specific platform (e.g., J2EE, .NET); may be automatically generated by tools. |
| **Executable UML (xUML)** | A reduced, formally-defined subset of UML 2 suitable for automated code generation; uses domain models, class models, and state models. |
| **OCL (Object Constraint Language)** | A declarative language for specifying constraints on UML models; used in xUML to define dynamic behavior. |
| **Stereotype** | A UML extension mechanism (e.g., `«system»`) used to classify elements with domain-specific meaning. |

---

## 3. Four System Modeling Perspectives

> [!info] The Four Perspectives
> Every system can be modeled from four complementary perspectives — no single one is sufficient.

| Perspective | Question Answered | Primary UML Diagram Types |
|---|---|---|
| **External (Context)** | What is the system's environment? What other systems does it interact with? | Architecture (box-and-arrow), UML Activity Diagram |
| **Interaction** | How does the system interact with its environment or how do its components communicate? | Use Case Diagrams, Sequence Diagrams |
| **Structural** | How is the system organized statically? What are its data structures? | Class Diagrams, Component Diagrams |
| **Behavioral** | How does the system behave dynamically when processing data or responding to events? | State Diagrams, Activity Diagrams |

> [!note] Relation to Krutchen's 4+1 View
> These four perspectives closely align with Krutchen's 4+1 architectural view model (Chapter 6), which adds a unifying use-case scenario layer to four views (logical, process, development, physical).

---

## 4. The Five Essential UML Diagram Types

A 2007 survey (Erickson and Siau) found that practitioners considered five UML diagrams sufficient to represent system essentials:

| # | Diagram Type | Purpose | Perspective |
|---|---|---|---|
| 1 | **Activity Diagram** | Shows activities in a process and flow of control between them | Context / Behavioral |
| 2 | **Use Case Diagram** | Shows interactions between a system and external actors | Interaction |
| 3 | **Sequence Diagram** | Shows chronological interactions between actors and system components | Interaction |
| 4 | **Class Diagram** | Shows object classes and associations in the system | Structural |
| 5 | **State Diagram** | Shows how the system reacts to internal and external events | Behavioral |

---

## 5. Context Models (Section 5.1)

### 5.1 System Boundaries

Before modeling a system's internals, architects must decide **where the system ends and its environment begins**. This is a non-trivial decision influenced by:
- Technical factors: data duplication vs. access speed trade-offs
- Social/organizational factors: political boundaries, cost allocation, team territories

> [!warning] System Boundary is Not Neutral
> Boundary decisions are often politically motivated. A boundary may be chosen to keep analysis on one site, to avoid a difficult manager, or to artificially increase project scope and budget. Be critical when evaluating boundary justifications.

### 5.2 Context Model Structure

A context model is typically represented as a **simple box-and-arrow architectural diagram** showing:
- The system under development (a box)
- Other systems in its environment (boxes, annotated with `«system»` stereotype)
- Connections between them (lines, possibly annotated with relationship type)

**MHC-PMS Context Example:**
The Mental Health Care Patient Management System is connected to: Patient Record System, Appointments System, Management Reporting System, HC Statistics System, Prescription System.

> [!note] Limitation of Context Models
> Context models show *what* other systems exist in the environment but NOT:
> - The *type* of relationship (does system A produce data for B, or share it bidirectionally?)
> - Physical proximity
> - Network topology
> Context models are always supplemented by process models (activity diagrams).

### 5.3 Process Models Using Activity Diagrams

UML **Activity diagrams** model the *business processes* in which the system participates, adding dynamism to the static context model.

**Activity Diagram Key Notation:**

| Symbol | Meaning |
|---|---|
| Filled circle | Start of process |
| Filled circle inside larger circle | End of process |
| Rectangle with round corners | Activity (a specific sub-process) |
| Solid horizontal bar (synchronization) | All incoming activities must complete before progress; outgoing activities may proceed in parallel |
| Arrow | Flow of work from one activity to another |
| `[guard]` annotation on arrow | Condition that must be true for this flow to be taken |

**MHC-PMS Involuntary Detention Example:**
The process shows that when a patient is detained, multiple activities occur concurrently (inform social care, inform next of kin, update detention register) because all three outgoing arrows emerge from the same synchronization bar.

---

## 6. Interaction Models (Section 5.2)

### 6.1 Use Case Modeling

**Use cases** model discrete tasks that involve external interaction with a system. Each use case:
- Shows *what* the user wants the system to do (not *how*)
- Is represented as an ellipse
- Has actors (human or other systems) shown as stick figures

**Levels of Detail for Use Cases:**

| Format | When to Use |
|---|---|
| Ellipse-only diagram | High-level overview of all system interactions |
| Simple textual description | When the interaction is straightforward |
| **Structured tabular description** | Most useful in practice (actors, description, data, stimulus, response, comments) |
| Sequence diagram | When precise, step-by-step interaction must be documented |

**MHC-PMS Transfer Data Use Case (Tabular):**

| Field | Value |
|---|---|
| Actors | Medical receptionist, Patient Record System (PRS) |
| Description | Receptionist may transfer updated personal info or treatment summary from MHC-PMS to general patient record database |
| Data | Patient's personal information, treatment summary |
| Stimulus | User command issued by medical receptionist |
| Response | Confirmation that PRS has been updated |
| Comments | Receptionist must have appropriate security permissions |

> [!info] Arrow Direction Convention
> Formally, use case diagram lines should have no arrows (messages flow in both directions). Informal arrows are used to show *who initiates* the transaction — a common but technically imprecise shorthand.

### 6.2 Sequence Diagrams

Sequence diagrams show the **sequence of interactions** during a particular use case instance. They reveal:
- Which objects are involved
- The order of method calls
- Return values
- Alternative flows (conditional branches)

**Key Notation Elements:**

| Element | Notation | Meaning |
|---|---|---|
| Object/Actor | Name at top, vertical dotted line | Participant in interaction |
| Lifeline rectangle | Solid rectangle on dotted line | Duration of object involvement |
| Annotated arrow | → with label | Method call (label: `methodName(params)`) |
| Return arrow | ← dashed | Return value |
| `alt` box | Rectangle labeled `alt` with `[condition]` sections | Alternative execution paths (if/else) |
| Object creation | Arrow to new box mid-diagram | Object instantiated during interaction |

**MHC-PMS View Patient Info Sequence (Figure 5.6):**
```
Medical Receptionist → P:PatientInfo: ViewInfo(PID)
P:PatientInfo → D:MHCPMS-DB: Report(Info, PID, UID)
D:MHCPMS-DB → AS:Authorization: Authorize(Info, UID)
alt [Authorization OK]: → Medical Receptionist: Patient Info (form filled)
alt [Authorization Fail]: → Medical Receptionist: Error(No Access)
```

> [!tip] When to Include All Interactions
> Early in development (RE, high-level design): omit implementation-specific interactions (e.g., how UID is retrieved). Only include interactions critical to understanding the use case. If used for code generation, every interaction must be specified.

---

## 7. Structural Models (Section 5.3)

### 7.1 Class Diagrams

Class diagrams show the **static organization** of object classes and the associations between them. Three levels of detail:

**Level 1: Classes and Associations**
- Class shown as a box with the class name
- Association shown as a line between boxes
- Multiplicity annotation at each end: `1` (exactly one), `1..*` (one or more), `*` (zero or more), `1..4` (one to four)

**Level 2: Named Associations and Roles**
- Associations can have names (e.g., "Diagnosed-with", "Referred-by")
- Objects can have roles in the association

**Level 3: Attributes and Operations**

| Section of Class Box | Contents |
|---|---|
| Top | Class name |
| Middle | Attributes (name, optional type) |
| Bottom | Operations/methods |

**MHC-PMS Consultation Class Example:**
```
Consultation
─────────────────────────
Doctors
Date
Time
Clinic
Reason
Medication Prescribed
Treatment Prescribed
Voice Notes / Transcript
─────────────────────────
New()
Prescribe()
RecordNotes()
Transcribe()
```

> [!note] UML Class Diagrams vs. Database Semantic Data Models
> At Levels 1–2, UML class diagrams closely resemble Entity-Relationship (ER) diagrams from database modeling. The key difference: UML classes include *operations* whereas ER entities do not (they focus purely on data structure).

### 7.2 Generalization (Inheritance)

Generalization allows **common attributes and operations to be factored into a superclass** so they are defined once and inherited by subclasses.

**UML Notation:** Arrow with open arrowhead pointing *up* toward the more general class.

**MHC-PMS Doctor Hierarchy:**
```
Doctor
├── Hospital Doctor
│   ├── Trainee Doctor
│   ├── Registered Doctor (Qualified)
│   └── Consultant
└── General Practitioner
```

| Class | Unique Attributes |
|---|---|
| Doctor (base) | Name, Phone#, Email; Register(), De-Register() |
| Hospital Doctor | Staff#, Pager# |
| General Practitioner | Practice, Address |

> [!warning] Inheritance Testing Pitfall
> You cannot test an inherited operation in the superclass and assume it works correctly in all subclasses. The operation may make assumptions about other attributes or operations that are valid in the superclass but violated in a subclass. **Each subclass context must be tested independently** (discussed again in Chapter 8).

### 7.3 Aggregation

Aggregation represents **whole-part** (compositional) relationships.

**UML Notation:** Diamond shape at the *whole* class end of the association.

**Example:** A `PatientRecord` (whole) is composed of one `Patient` object and one or more `Consultation` objects.

```
PatientRecord ◆──── Patient     (1:1)
PatientRecord ◆──── Consultation (1:1..*)
```

---

## 8. Behavioral Models (Section 5.4)

### 8.1 Data-Driven Modeling

Data-driven models show the **sequence of processing steps** that transform input data into output. They answer: *what happens to the data from end to end?*

**Historical Context:** DFDs (Data-Flow Diagrams) were the original notation (DeMarco, 1978). UML 2.0 introduced Activity Diagrams as a modern equivalent.

**UML Activity Diagram for Data-Driven Systems:**
- Activities (rounded rectangles) = processing steps
- Objects (rectangles with underline) = data items flowing between steps
- Data flowing between activities is shown as object tokens on arrows

**Alternative: Sequence Diagrams as Data-Flow Models**
If messages only flow from left to right in a sequence diagram, it documents sequential data processing. Sequence diagrams highlight *objects*; activity diagrams highlight *functions*. Use together for complementary views.

> [!tip] Choice Between Activity and Sequence Diagrams
> Use **Activity diagrams** when you want to emphasize the *flow of data and processing steps*. Use **Sequence diagrams** when you want to emphasize *which objects are responsible* for each step. For a complete behavioral model, develop both.

### 8.2 Event-Driven Modeling

Event-driven models show **how a system responds to stimuli** by transitioning between finite states. Key assumption: the system is always in exactly one state; events trigger state transitions.

**UML State Diagram Key Notation:**

| Symbol | Meaning |
|---|---|
| Rounded rectangle | A system state; can include `Do: action` description |
| Labeled arrow | A stimulus causing a state transition |
| `Exit: action` in state | Action performed when leaving the state |
| Filled circle | Start state |
| Filled circle in larger circle | End state |

**Microwave Oven States and Stimuli (Illustrative Example):**

| State | Description |
|---|---|
| Waiting | Idle; display shows current time |
| Half Power | Power set to 300W; display shows "Half power" |
| Full Power | Power set to 600W; display shows "Full power" |
| Set Time | Cooking time being entered; display shows time |
| Disabled | Door open; oven locked for safety; interior light on |
| Enabled | Door closed; oven ready; display shows "Ready to cook" |
| Operation | Oven cooking; display shows countdown timer |

| Stimulus | Source |
|---|---|
| Half power / Full power | User button press |
| Number | Numeric keypad |
| Timer | Timer button |
| Door open / Door closed | Door switch sensor |
| Start / Cancel | Control buttons |

### 8.3 Managing State Complexity — Superstates

For large systems, the number of states grows rapidly. **Superstates** provide a hierarchical solution:
- A superstate appears as a **single state** on the high-level diagram
- It is **expanded** into a sub-state diagram on a separate, lower-level diagram

**Example:** The `Operation` superstate in the microwave contains sub-states: `Time Checking → Cook → Alarm / Done`. This keeps the top-level diagram readable while preserving completeness.

---

## 9. Model-Driven Engineering (Section 5.5)

### 9.1 MDE Philosophy

MDE raises the level of abstraction: **models, not programs, are the principal development artifact**. Code is automatically generated. Engineers focus on system behavior, not platform details.

**Arguments For and Against MDE:**

| For MDE | Against MDE |
|---|---|
| Engineers think at high abstraction level | Model abstractions may not match implementation abstractions |
| Reduces implementation errors | Platform independence only matters for large, long-lifetime systems |
| Faster design & implementation via tools | Code generation support rarely covers full execution environment (UI, legacy systems) |
| Reusable, platform-independent models | Agile methods conflict with extensive upfront modeling |
| One PIM → multiple PSMs for different platforms | Most significant problems (security, integration, testing) aren't solved by MDE |

### 9.2 Model-Driven Architecture (MDA) — Three Model Levels

> [!info] MDA Transformation Chain
> CIM → (human-guided translation) → PIM → (tool-generated) → PSM → (tool-generated) → Executable Code

| Level | Name | Description | Status |
|---|---|---|---|
| **CIM** | Computation Independent Model | Domain abstractions; no implementation concern. Also called domain model. | Human-authored; CIM→PIM translation still research-prototype |
| **PIM** | Platform Independent Model | System operation modeled in UML; no target platform reference | Human-authored; basis for all downstream transformation |
| **PSM** | Platform Specific Model | PIM transformed for a specific platform (J2EE, .NET, etc.) | Tool-generated; multiple PSMs from one PIM |
| **Code** | Executable Code | Actual program running on the hardware/software platform | Tool-generated from PSM |

**Multiple Platforms from One PIM:**
```
PIM ──→ J2EE Translator ──→ J2EE PSM ──→ Java Code Generator ──→ Java Program
    └──→ .NET Translator  ──→ .NET PSM  ──→ C# Code Generator  ──→ C# Program
```

> [!warning] Practical Limitation of MDA Tools
> Commercial MDA tools only support translation to *standard* platforms (J2EE, .NET). They cannot account for company-specific libraries, legacy system integration, or custom UI frameworks. Special-purpose translators must be written — adding significant cost. Full automation of PIM→PSM is rarely achievable in practice.

### 9.3 Executable UML (xUML)

xUML dramatically reduces UML to **three key model types** that have formally defined semantics (suitable for code generation):

| Model Type | Purpose |
|---|---|
| **Domain models** | Principal domain concerns using class diagrams (objects, attributes, associations) |
| **Class models** | Classes with attributes and operations |
| **State models** | A state diagram per class describing the class's lifecycle |

**Dynamic behavior specification options:**
- **OCL (Object Constraint Language):** Declarative constraints
- **UML Action Language:** High-level imperative language referencing objects and attributes

> [!note] MDA vs. MDE Scope
> MDA covers only **design and implementation** stages. MDE is broader — it encompasses model-based requirements engineering, model-based testing, software process, and any context where models drive the lifecycle.

---

## 10. Deep-Dive: Why Multiple Model Types Are Necessary

> [!question] The Core Insight: No Model Is Complete
> Consider the MHC-PMS. A class diagram shows that `Patient` is associated with `Consultation`, but tells you nothing about:
> - The sequence of steps when a patient is referred (interaction model needed)
> - What happens when a detained patient's door-open sensor triggers during an emergency (state diagram needed)
> - Which external systems receive data after an update (context model needed)
>
> Each perspective reveals something the others hide. The four perspectives are not redundant — they are **orthogonal views** of the same system.

**Common Pitfalls in Modeling:**

| Pitfall | Consequence | Prevention |
|---|---|---|
| Over-specifying interactions too early | Locks in implementation decisions before they are known | Omit implementation-dependent interactions; add detail only when needed |
| Ignoring system boundary decisions | System scope creep; duplicated data between systems | Explicitly negotiate and document system boundaries with stakeholders early |
| Treating a model as an alternative representation | Over-precision; too much detail crowds out key abstractions | Always ask: "what detail can I safely omit?" |
| Using a single diagram type | Missing behavioral or structural properties | Develop complementary models from at least two perspectives |
| Using MDA without custom translator support | Only 80% of code generated; manual patches break on tool upgrades | Assess full execution environment before committing to MDA |

---

## 11. Exam Prep — Discussion Questions

> [!question] Discussion Question 1 — Why Context Models Are Insufficient Alone
> Explain why a simple context model of the MHC-PMS is insufficient for specifying system requirements. What information is missing from Figure 5.1, and what type of model should be added to supply it? Give two concrete examples of requirements that the context model cannot capture.
>
> **Guidance:** The context model shows which external systems exist but not (a) the direction of data flow, (b) what data is transferred, (c) the sequence of interactions, or (d) the conditions under which interactions occur. Missing: whether the MHC-PMS *pushes* data to the Appointments System or *pulls* it; whether the PRS integration is synchronous or asynchronous. Add activity diagrams (process models) to show business processes, and use cases to document specific interactions.

> [!question] Discussion Question 2 — Use Case vs. Sequence Diagram: What Each Captures
> For the "Transfer Data" use case in the MHC-PMS: (a) What does the use case diagram convey that the sequence diagram does not? (b) What does the sequence diagram convey that the use case diagram does not? (c) In a resource-constrained project, which would you prioritize and why?
>
> **Guidance:** (a) Use case: the actors involved (receptionist, PRS), the name of the use case, and its relationship to other use cases for the same actor — gives a system-level interaction map. (b) Sequence diagram: the specific objects called, the order of operations, return values, and alternative flows (authorization success/failure) — gives implementation-level detail. (c) Prioritize use cases for RE (stakeholder sign-off); prioritize sequence diagrams if the team is about to implement the feature.

> [!question] Discussion Question 3 — Class Diagram Multiplicity and Design Decisions
> In Figure 5.9, the association between `Patient` and `Consultation` has multiplicity `1..*` on the Consultation end. (a) What does this mean? (b) What design decision does this encode? (c) What would change in the class diagram if the system needed to support patients who have never had a consultation (e.g., recently registered)?
>
> **Guidance:** (a) Each Patient is associated with one or more Consultations — every patient must have had at least one. (b) This encodes the assumption that a patient is only registered in the system after their first consultation. (c) Change multiplicity to `0..*` (zero or more) — a patient can exist in the system with no consultations yet recorded.

> [!question] Discussion Question 4 — State Diagrams and Complexity Management
> The microwave oven state diagram uses a superstate to manage complexity. (a) Explain what the `Operation` superstate abstracts away on the high-level diagram. (b) Describe a scenario where a developer would need to look at the expanded sub-state diagram rather than the top-level diagram. (c) What is the general principle behind superstates?
>
> **Guidance:** (a) The `Operation` superstate hides internal states (Time Checking, Cook, Alarm, Done) and the fault/door-open logic. The top-level diagram only needs to know: enter `Operation` when Start is pressed, exit to `Waiting` when done or `Disabled` when door opens. (b) A developer implementing the microwave controller firmware needs the sub-state details to know: what triggers the generator, when to activate the buzzer, and how to handle a turntable fault. (c) General principle: hide detail at a higher level of abstraction; expose it only when necessary. This mirrors the principle of information hiding in software design.

> [!question] Discussion Question 5 — Arguments Against MDE in Practice
> A software architect argues: "For our system — a 3-year hospital information system with custom legacy integration — MDE is not worth the investment." Evaluate this argument using the textbook's analysis of MDE trade-offs. Under what conditions would you change your recommendation?
>
> **Guidance:** The argument is well-supported by the textbook. MDE's platform-independence argument only holds for systems where platforms become obsolete during the system's lifetime (3 years is borderline). The dominant challenges for a hospital IS (security, legacy integration, testing) are NOT solved by MDE. MDA tools will not cover the custom legacy integration, requiring special-purpose translators — potentially exceeding the cost of just coding it. Recommendation change: if the system is planned for a 10+ year lifespan and must run on future unknown platforms, the investment in PIMs becomes justified. Also if the team has existing xUML tooling and expertise.

---

## 12. Key Points Summary (from Textbook)

> [!summary] Textbook Key Points — Chapter 5

- A model is an **abstract view** of a system that ignores some system details. Complementary system models can be developed to show the system's context, interactions, structure, and behavior.
- **Context models** show how a system being modeled is positioned in an environment with other systems and processes; they help define the boundaries of the system to be developed.
- **Use case diagrams and sequence diagrams** are used to describe the interactions between users, the system being designed, and other systems. Use cases describe interactions between a system and external actors; sequence diagrams add more information by showing interactions between system objects.
- **Structural models** show the organization and architecture of a system. **Class diagrams** define the static structure of classes and their associations.
- **Behavioral models** describe the dynamic behavior of an executing system from the perspective of the **data processed** (activity diagrams) or **events that stimulate responses** (state diagrams).
- **Activity diagrams** may be used to model data processing, where each activity represents one process step.
- **State diagrams** model a system's behavior in response to internal or external events.
- **Model-driven engineering** is an approach to software development in which a system is represented as a set of models that can be automatically transformed to executable code.

---

## 13. Further Reading

| Resource | Authors | Notes |
|---|---|---|
| *Requirements Analysis and System Design* | Maciaszek (2001) | Focuses on information systems analysis; discusses how different UML models are used in analysis |
| *MDA Distilled: Principles of Model-Driven Architecture* | Mellor, Scott, Weise (2004) | Concise, accessible intro to MDA; written by enthusiasts — read critically for limitations |
| *Using UML: Software Engineering with Objects and Components* (2nd ed.) | Stevens with Pooley (2006) | Short, readable introduction to UML in specification and design |

---

[[Chapter6_Comprehensive|→ Next: Chapter 6 – Architectural Design]] | [[Software Engineering Hub|Hub]]
