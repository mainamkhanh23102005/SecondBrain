# Exam Study — Module 4: Endpoint and Application Development Security

**Source PDF:** CompTIASec_7e_Mod04.pdf — CompTIA Security+ Guide to Network Security Fundamentals, 7th Edition, Module 4  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #threat-intelligence #endpoint-security #SecDevOps #UEFI #EDR

---

## Quick Lookup Index

**Sections:**
1. Threat Intelligence Sources
2. Securing Endpoint Computers (Confirm / Protect / Harden)
3. Creating and Deploying SecDevOps
- Deep Dive: SecDevOps vs. Traditional Development
- Deep Dive: The Chain of Trust — Why Boot Security Starts at Hardware
- Knowledge Check Q&A
- Graph View Links

**Key Terms:** KRI, IOC, predictive analysis, OSINT, CISCP, AIS, STIX, TAXII, closed source, vetting, vulnerability database, NVD, threat maps, file/code repositories, dark web, clear web, deep web, boot integrity, BIOS, UEFI, Secure Boot, BIOS attack, boot security, chain of trust, hardware root of trust, TPM, HSM, AV, static analysis, dynamic analysis, antimalware, Bayesian filtering, antispyware, secure cookies, SSL/TLS, HTTP Response Headers, HIDS, HIPS, EDR, patch management, forced updates, OS security, least functionality, security template, Tamper Protection, Group Policy, confinement tools, whitelisting, blacklisting, sandbox, quarantine, directory traversal, command injection, software diversity, provisioning, deprovisioning, integrity measurement, waterfall model, agile model, DevOps, SecDevOps, SDLC, 5 Cs, continuous monitoring/validation/integration/delivery/deployment, secure coding, static code analysis, dynamic code analysis, fuzzing

---

## 1. Threat Intelligence Sources

Organizations increasingly pool and share knowledge about attacks with the broader security community. Shared threat intelligence accelerates detection, prediction, and response.

### Key Risk Indicators (KRIs) and Indicators of Compromise (IOC)

| Concept | Definition |
|---|---|
| **Key Risk Indicator (KRI)** | A metric tracking the upper and lower bounds of specific indicators of normal network activity (network logs/sec, failed remote logins, network bandwidth, outbound email traffic) |
| **Indicator of Compromise (IOC)** | Evidence that a malicious activity is occurring; shows an attack is in the early stages but has not yet been fully detected |

**How they relate:**
- When a **KRI** exceeds its normal bounds → it becomes an **IOC** showing that malicious activity may be occurring.
- IOC information helps organizations with **predictive analysis** — identifying attacks before they fully execute.

### Categories of Threat Intelligence Sources

#### Open Source Information (OSINT)

| Source | Description |
|---|---|
| **OSINT (Open Source Intelligence)** | Any threat intelligence that is freely available without restrictions |
| **CISCP (Cyber Information Sharing and Collaboration Program)** | Enables actionable, relevant, and timely unclassified information exchange through partnerships |

**CISCP Services:**
- Analyst-to-analyst technical exchanges
- CISCP analytical products
- Cross-industry orchestration
- Digital malware analysis

**Two concerns around public information-sharing centers:**
1. **Privacy**: victim organizations must avoid sharing proprietary or sensitive information when providing IOCs and attack details.
2. **Speed**: How quickly can threat indicators be exchanged?

**Automated Indicator Sharing (AIS)** enables exchange of cyberthreat indicators between parties through computer-to-computer communication. Two tools facilitate AIS:

| Tool | Full Name | Description |
|---|---|---|
| **STIX** | Structured Threat Information Expression | A language and format for describing and exchanging cyber threat intelligence |
| **TAXII** | Trusted Automated Exchange of Intelligence Information | An application protocol and data exchange format for sharing cyberthreat information securely |

#### Closed Source Information

- **Closed source** is **proprietary** threat intelligence.
- Organizations participating in closed source information-sharing are part of **private information sharing centers** that restrict both access and participation.
- All candidates must go through a **vetting process** and meet specific criteria before gaining access.

### Useful Sources of Threat Intelligence

| Source | Description |
|---|---|
| **Vulnerability database** | Repository of known vulnerabilities and information on how they have been exploited (e.g., National Vulnerability Database — NVD) |
| **Threat maps** | Illustrate cyberthreats overlaid on a geographic representation of the world in real time |
| **File and code repositories** | Where victims can upload malicious files and software code to be examined by others — helps craft defenses |
| **Dark web** | Security professionals use the dark web on a limited basis to look for signs that their enterprise's information is being sought out or sold |

**Three layers of the web:**
| Layer | Contents |
|---|---|
| **Clear web** | Publicly indexed sites (Google, Yahoo, Bing) |
| **Deep web** | Academic/subscription content, records, databases, organization-specific information — not indexed |
| **Dark web** | Illegal activities, black markets, threat actor communications — requires special software to access |

---

## 2. Securing Endpoint Computers

Securing endpoint computers involves **three major tasks**:

1. **Confirming** that the computer has started securely
2. **Protecting** the computer from attacks
3. **Hardening** it for even greater protection

### Task 1: Confirm Boot Integrity

Ensuring secure startup involves the **Unified Extensible Firmware Interface (UEFI)** and its boot security features.

#### BIOS vs. UEFI

| Feature | BIOS | UEFI |
|---|---|---|
| Role | First firmware loaded at startup; initializes hardware | Improved replacement for BIOS |
| Hard drive support | Limited | Supports drives larger than 2TB |
| Partitions | Limited to 4 primary partitions | Unlimited number of primary partitions |
| Boot speed | Slower | Faster booting |
| Networking | Limited | Supports networking functionality within the firmware itself (aids troubleshooting) |

#### Boot Security (Chain of Trust)

The ability to update BIOS firmware opened a vector for **BIOS attacks** (malware that infects the BIOS itself — extremely dangerous as it persists through OS reinstallation).

**Boot security** validates that each element used in each step of the boot process has **not been modified**:

1. Validation begins with the **boot software** (bootloader).
2. Then validates **software drivers**.
3. Then hands control to the **OS**.

This sequential validation is called the **chain of trust**:
- Each element relies on the previous element confirming it is secure.
- If any element in the chain is modified, the chain fails.
- **Hardware root of trust**: the chain starts at hardware (which cannot be modified like software) — this is the strongest possible starting point.

> **Why hardware is the best root of trust**: software can be modified by an attacker with sufficient privileges. Hardware security modules (HSMs, TPM chips) cannot be altered by software attacks.

### Task 2: Protect Endpoints

Protection is accomplished through software installed on the endpoint:

#### Antivirus (AV)

- Examines a computer for **file-based virus infections** and monitors computer activity (e.g., scanning new documents that might contain a virus).
- Log files created by AV products provide beneficial information about attacks.
- **Static analysis** (signature-based): compares file signatures against a database of known malware — fast but cannot detect new/unknown malware.
- **Dynamic analysis** (heuristic): monitors behavior patterns; detects new/unknown malware based on suspicious behavior.

#### Antimalware

- A suite of software providing protections against **multiple types of malware** (not just viruses).
- **Bayesian filtering**: spam protection technique that analyzes every word in each email and determines how frequently the word occurs in spam vs. non-spam — probabilistic classification.
- **Antispyware**: component that helps prevent computers from becoming infected with spyware; uses pop-up blockers to control blocking levels.

#### Web Browser Protections

- **Secure cookies (SSL/TLS)**: sent to web server with an encrypted request over HTTPS — prevents unauthorized person from intercepting cookies being transmitted between browser and web server.
- **HTTP Response Headers**: tell the browser how to behave while communicating with the website (e.g., enforcing HTTPS, blocking cross-origin requests, preventing clickjacking).

#### Monitoring and Response Systems

| System | Description |
|---|---|
| **HIDS** (Host Intrusion Detection System) | Software-based application running on the endpoint; detects that an attack **has occurred** and can report it |
| **HIPS** (Host Intrusion Prevention System) | Monitors endpoint activity and **immediately blocks** a malicious attack by following specific rules |
| **EDR** (Endpoint Detection and Response) | More robust than both HIDS and HIPS combined; aggregates data from multiple endpoints to a centralized database; performs sophisticated analytics to identify patterns and detect anomalies |

**EDR advantages:**
- Combines features of HIDS (detect) and HIPS (prevent) in a more comprehensive solution.
- Aggregates data from multiple endpoint computers to a centralized database.
- Can perform more sophisticated analytics that identify patterns and detect anomalies that single-endpoint systems would miss.

### Task 3: Harden Endpoints

Hardening involves **patch management** and **OS security configurations**.

#### Patch Management

**Effective patch management** uses two types of tools:

| Tool Type | Description |
|---|---|
| **Automated patch update service** | Automates patch distribution across the organization |
| **Patch reception service** | Manages how endpoints receive and apply patches |

**Windows 10 patch options:**
- **Forced updates**: mandatory patches pushed automatically.
- **No selective updates**: all updates must be accepted (cannot cherry-pick).
- **More efficient distribution**: updates delivered in chunks to minimize network impact.

#### Operating System Security

Securing an OS involves proper security configurations and **confinement tools**.

**A typical OS security configuration should include:**
- **Disabling unnecessary ports and services** — reduce the attack surface.
- **Disabling default accounts/passwords** — default credentials are publicly known.
- **Employing least functionality** — only what is necessary for the role.

**Windows-specific hardening:**
- **Security template**: a collection of security configuration settings that can be deployed to multiple computers.
- **Windows 10 Tamper Protection**: prevents Windows security settings from being changed or disabled by threat actors modifying the Registry.
- **Group Policy**: can prevent access to Registry editing tools, preventing malware from modifying security configurations.

#### Confinement Tools

Three tools restrict what malware can do even if it gets onto the system:

| Tool | Description |
|---|---|
| **Application whitelisting/blacklisting** | Whitelist: only approved applications can run. Blacklist: specified applications are blocked. Whitelist is more secure. |
| **Sandbox** | Isolated environment where an application can run without affecting the rest of the OS or files. Application 1 runs inside the sandbox — its files and settings cannot reach other applications or the OS. |
| **Quarantine** | Isolates a suspected malicious file so it cannot execute or interact with the system until analyzed. |

---

## 3. Creating and Deploying SecDevOps

### Why Application Security Matters

An unsecure application can open the door for attackers to exploit:
- The application itself.
- The data it accesses.
- The **underlying OS**.

Key vulnerabilities in applications:

| Vulnerability Class | Description |
|---|---|
| **Directory traversal attack** | Exploits vulnerability in web application or web server software allowing a user to move from the root directory to other restricted directories; can view confidential files or enter commands as **command injection** |
| **Poor memory management** | Results in buffer overflow, integer overflow, pointer/object dereference, and DLL injection attacks |

### Application Development Concepts

#### General Concepts

**Application development stages:**

| Stage | Description |
|---|---|
| **Development** | Writing and building the application code |
| **Testing** | Verifying functionality and security |
| **Staging** | Final validation in a production-like environment |
| **Production** | Live deployment to end users |

**Key concepts:**

| Concept | Definition |
|---|---|
| **Software diversity** | Two or more functionally identical variants of a program are developed from the same specification but by different programmers/teams — provides error detection, increased reliability, and additional documentation |
| **Provisioning** | Enterprise-wide configuration, deployment, and management of multiple types of IT system resources |
| **Deprovisioning** | Removing a resource that is no longer needed in application development |
| **Integrity measurement** | An "attestation mechanism" designed to convince a remote party that an application is running only a set of known and approved executables |

### Application Development Lifecycle Model

Two primary lifecycle models:

| Model | Approach | Characteristics |
|---|---|---|
| **Waterfall model** | Sequential design process | Phase 1 must complete before Phase 2 begins; documentation-heavy; changes are costly |
| **Agile model** | Incremental, iterative approach | Work in short sprints; adapt to changing requirements; faster delivery of working software |

### SecDevOps

**DevOps** = Development + Operations — integrating software development and IT operations.

**SecDevOps** = Security-focused DevOps — integrates security into the **entire software development life cycle (SDLC)**, making it a core component of both development and operations teams' work.

**Two definitions of SecDevOps:**
1. A **security-focused approach** to software development and operations that integrates security into the entire SDLC.
2. The process of integrating **secure development best practices and methodologies** into application software development and deployment using the agile model.

**How SecDevOps works:**
- Applies **automated courses of action** to develop code as quickly and securely as possible.
- This automation enables the **5 Cs of SecDevOps**:

| C | Meaning |
|---|---|
| **Continuous monitoring** | Ongoing real-time visibility into system state and security posture |
| **Continuous validation** | Automated security checks at every stage of development |
| **Continuous integration** | Code changes are automatically built and tested |
| **Continuous delivery** | Code is always in a deployable state |
| **Continuous deployment** | Automatically deploy code to production after successful tests |

> **Memory tip:** The 5 Cs of SecDevOps: Monitor → Validate → Integrate → Deliver → Deploy.

### Secure Coding Techniques

Several coding techniques limit data exposure and prevent introducing vulnerabilities:

| Technique | Why It Matters |
|---|---|
| **Determine how encryption will be implemented** | Encryption must be built in from the design phase; retrofitting is difficult and error-prone |
| **Ensure memory management is handled correctly** | Prevents buffer overflows, integer overflows, and pointer dereferences from creating exploitable vulnerabilities |

**Key principle**: secure coding is not a review step done after coding — it is a **mindset applied throughout development**.

### Code Testing

Testing is one of the most important steps in SecDevOps. It should be performed during **implementation** and **verification** phases.

| Testing Type | When | Description |
|---|---|---|
| **Static code analysis** | Before compilation | Tests run on source code before it is compiled; may be accompanied by manual peer reviews; detects vulnerabilities in code logic |
| **Dynamic code analysis** | After compilation | Security testing performed on compiled, running code; tests behavior during execution |
| **Fuzzing** | During dynamic analysis | Provides random, unexpected, or invalid input to a program in an attempt to trigger exceptions, crashes, or unexpected behavior — reveals input handling vulnerabilities |

**Why both static and dynamic testing are necessary:**
- Static analysis finds **code logic errors** and vulnerabilities that can be spotted without execution.
- Dynamic analysis finds **runtime behavior** vulnerabilities that only appear when the code is actually executing.
- Neither alone is sufficient.

---

## Deep Dive: SecDevOps vs. Traditional Development

In **traditional waterfall development**, security was added at the end:
```
Design → Code → Test → Security Review → Deploy
```
Problems with this approach:
- Security issues found late are expensive to fix.
- Security requirements may conflict with design decisions already made.
- Developers do not think about security as they write code.

In **SecDevOps**:
```
Every sprint: Design (with security) → Code (with secure practices) → 
              Test (static + dynamic + fuzz) → Validate → Deploy → Monitor
```
Security is not a gate to pass — it is **woven into every activity**. The result:
- Vulnerabilities found and fixed cheaply during development.
- Security is part of team culture, not an external audit function.
- Automated security checks prevent regressions.

---

## Deep Dive: The Chain of Trust — Why Boot Security Starts at Hardware

The chain of trust concept addresses a fundamental problem: **how do you trust a system that may have been compromised before you even start using it?**

The answer is to start with something that **cannot be tampered with** — hardware:
1. The **hardware root of trust** (TPM chip or UEFI firmware) verifies the bootloader.
2. The verified bootloader verifies the kernel.
3. The verified kernel verifies OS components.
4. The verified OS verifies applications.

If any link in this chain cannot be verified, the system halts. This is why:
- **Secure Boot** (UEFI feature) prevents unsigned boot software from running.
- **TPM (Trusted Platform Module)** stores cryptographic measurements of the boot process — any tampering changes these measurements, triggering a boot failure.
- **HSM (Hardware Security Module)** provides hardware-based key storage that malware cannot access.

---

## Knowledge Check Q&A

**Q1**: What is the difference between a KRI and an IOC?  
**A**: A KRI is a metric tracking bounds of normal network activity. When a KRI exceeds its normal bounds, it becomes an IOC — evidence that malicious activity is occurring.

**Q2**: What is STIX and what is TAXII?  
**A**: STIX is a language/format for expressing and exchanging cyber threat intelligence. TAXII is the application protocol and data exchange format for sharing it securely between parties.

**Q3**: What are the three major tasks for securing an endpoint computer?  
**A**: (1) Confirming it started securely (boot integrity), (2) Protecting it from attacks (AV, antimalware, EDR), (3) Hardening it (patch management, OS configuration, confinement tools).

**Q4**: What is the hardware root of trust and why does it matter?  
**A**: Starting the chain of trust at hardware means the verification process begins with something that cannot be modified by software attacks (unlike the bootloader or OS). This prevents malware from compromising the system before the OS loads.

**Q5**: What is the difference between HIDS, HIPS, and EDR?  
**A**: HIDS detects attacks after they occur; HIPS blocks attacks immediately based on rules; EDR is the most comprehensive — it aggregates data from multiple endpoints, performs sophisticated analytics, and provides both detection and response capabilities.

**Q6**: What are the 5 Cs of SecDevOps?  
**A**: Continuous Monitoring, Continuous Validation, Continuous Integration, Continuous Delivery, Continuous Deployment.

**Q7**: What is fuzzing?  
**A**: A dynamic code analysis technique that provides random, unexpected, or invalid input to a program in an attempt to trigger exceptions — revealing input handling vulnerabilities.

---

## Textbook Review Questions (Ciampa CompTIA Security+ 7e — Module 4)

> Official end-of-module review questions, reconstructed from the textbook chapter. Answers are derived (the chapter prints no key); *(verify)* marks any less-certain answer.

**1.** An IOC occurs when what metric exceeds its normal bounds?
- a. IRR
- b. LRG
- c. EXR
- d. KRI

**Answer: d.** A Key Risk Indicator (KRI) exceeding its normal bounds signals an Indicator of Compromise (IOC); the other options are not real metrics.

**2.** What are the two concerns about using public information sharing centers?
- a. Cost and availability
- b. Privacy and speed
- c. Security and privacy
- d. Regulatory approval and sharing

**Answer: c.** The two concerns Ciampa lists for public sharing centers are security (trusting shared data) and privacy (protecting organizational data).

**3.** Which privacy protection uses four colors to indicate the expected sharing limitations that are to be applied by recipients of the information?
- a. CISA
- b. FOIA
- c. TLP
- d. PCII

**Answer: c.** The Traffic Light Protocol (TLP) uses four colors (Red, Amber, Green, White) to mark sharing limitations.

**4.** Oskar has been receiving emails about critical threat intelligence information from a public information sharing center. His team leader has asked him to look into how the process can be automated so that the information can feed directly into the team's technology security. What technology will Oskar recommend?
- a. Automated Indicator Sharing (AIS)
- b. Bidirectional Security Protocol (BSP)
- c. Linefeed Access
- d. Lightwire JSON Control

**Answer: a.** Automated Indicator Sharing (AIS) enables automated, machine-speed exchange of threat indicators; the other options are fabricated.

**5.** Which of the following is an application protocol for exchanging cyberthreat intelligence over HTTPS?
- a. STIX
- b. AIP-TAR
- c. TAXII
- d. TCP-Over-Secure (ToP)

**Answer: c.** TAXII (Trusted Automated Exchange of Intelligence Information) is the application protocol that transports threat intelligence over HTTPS; STIX is the data format, not the transport protocol.

**6.** What are the two limitations of private information sharing centers?
- a. Access to data and participation
- b. Government approval and cost
- c. Timing of reports and remote access
- d. Bandwidth and CPU

**Answer: a.** Ciampa cites access to the data and the willingness of organizations to participate as the two limitations of private sharing centers.

**7.** Which of the following is NOT a limitation of a threat map?
- a. Many maps claim that they show data in real time, but most are simply a playback of previous attacks.
- b. Because threat maps show anonymized data, it is impossible to know the identity of the attackers or the victims.
- c. They can be difficult to visualize.
- d. Threat actors usually mask their real locations, so what is displayed on a threat map is incorrect.

**Answer: c.** Difficulty visualizing is not a stated limitation — threat maps are highly visual; the other three are genuine limitations Ciampa lists.

**8.** Luka has been asked by his supervisor to monitor the dark web for any IOCs concerning their organization. The next week, Luca reports that he was unable to find anything because looking for information on the dark web is different from using the regular web. Which of the following is FALSE about looking for information on the dark web?
- a. It is necessary to use Tor or IP2.
- b. Dark web search engines are identical to regular search engines.
- c. Dark web merchants open and close their sites without warning.
- d. The naming structure is different on the dark web.

**Answer: b.** Dark web search engines are not identical to regular ones; they behave differently, so this statement is FALSE.

**9.** Which of the following is NOT an improvement of UEFI over BIOS?
- a. Stronger boot security
- b. Networking functionality in UEFI
- c. Access larger hard drives
- d. Support of USB 3.0

**Answer: d.** USB 3.0 support is a hardware/OS feature, not a UEFI-over-BIOS improvement; the other three are genuine UEFI advantages.

**10.** Which boot security mode sends information on the boot process to a remote server?
- a. UEFI Native Mode
- b. Secure Boot
- c. Trusted Boot
- d. Measured Boot

**Answer: d.** Measured Boot sends boot-process measurements to a remote attestation server for verification.

**11.** Which of the following is NOT an important OS security configuration?
- a. Employing least functionality
- b. Disabling default accounts
- c. Disabling unnecessary services
- d. Restricting patch management

**Answer: d.** Patch management should be enabled/streamlined, not restricted; restricting it would weaken security, so it is NOT a recommended configuration.

**12.** Which stage conducts a test that will verify the code functions as intended?
- a. Production stage
- b. Testing stage
- c. Staging stage
- d. Development stage

**Answer: b.** The Testing stage verifies the code functions as intended before release.

**13.** Which model uses a sequential design process?
- a. Secure model
- b. Agile model
- c. Rigid model
- d. Waterfall model

**Answer: d.** The Waterfall model uses a strict sequential (phase-by-phase) design process.

**14.** Which of the following is NOT an advantage of an automated patch update service?
- a. Downloading patches from a local server instead of using the vendor's online update service can save bandwidth and time because each computer does not have to connect to an external server.
- b. Administrators can approve updates for "detection" only; this allows them to see which computers require the update without installing it.
- c. Users can disable or circumvent updates just as they can if their computer is configured to use the vendor's online update service.
- d. Administrators can approve or decline updates for client systems, force updates to install by a specific date, and obtain reports on what updates each computer needs.

**Answer: c.** With an automated patch service, administrators control updates so users CANNOT disable or circumvent them; this is a drawback of the vendor service, not an advantage of the automated one.

**15.** What type of analysis is heuristic monitoring based on?
- a. Dynamic analysis
- b. Static analysis
- c. Code analysis
- d. Input analysis

**Answer: a.** Heuristic monitoring observes behavior at runtime, which is dynamic analysis.

**16.** Which of these is a list of preapproved applications?
- a. Greenlist
- b. Redlist
- c. Blacklist
- d. Whitelist

**Answer: d.** A whitelist (allow list) is the list of preapproved applications; a blacklist is the list of blocked ones.

**17.** What is the advantage of a secure cookie?
- a. It cannot be stored on the local computer without the user's express permission.
- b. It is sent to the server over HTTPS.
- c. It is analyzed by AV before it is transmitted.
- d. It only exists in RAM and is deleted once the web browser is closed.

**Answer: b.** A secure cookie has the Secure attribute set, so the browser transmits it only over encrypted HTTPS connections.

**18.** Which of the following tries to detect and stop an attack?
- a. HIDS
- b. HIPS
- c. RDE
- d. SOMA

**Answer: b.** A Host Intrusion Prevention System (HIPS) detects AND stops attacks, whereas a HIDS only detects them.

**19.** What does Windows 10 Tamper Protection do?
- a. Limits access to the registry.
- b. Prevents any updates to the registry until the user approves the update.
- c. Compresses and locks the registry.
- d. Creates a secure backup copy of the registry.

**Answer: a.** Tamper Protection limits access to the registry keys (and security settings) so malware cannot change them.

**20.** Which of the following is FALSE about a quarantine process?
- a. It holds a suspicious application until the user gives approval.
- b. It can send a sanitized version of the attachment.
- c. It can send a URL to the document that is on a restricted computer.
- d. It is most often used with email attachments.

**Answer: a.** Quarantine isolates suspicious content automatically rather than holding it pending user approval, making this statement FALSE. *(verify)*

---

## Graph View Links

**Previous**: [[Module 3 - Threats and Attacks on Endpoints]]  
**Next**: [[Module 6 - Basic Cryptography]]  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 2 - Threat Management and Cybersecurity Resources]]
