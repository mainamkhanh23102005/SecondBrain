# Exam Study — Module 1: Introduction to Information Security

**Source PDF:** Week1.Secplus_8e_Mod01_PPT.pdf — CompTIA Security+ Guide to Network Security Fundamentals, 8th Edition, Module 1  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #security #CIA-triad #threat-actors #social-engineering

---

## Quick Lookup Index

**Sections:**
1. What Is Information Security?
2. The CIA Triad
3. AAA Framework
4. Types of Security Controls
5. Cybersecurity vs. Information Security
6. Threat Actors
7. Threat Vectors and Attack Surfaces
8. Vulnerability Categories
9. Impacts of Attacks
10. Information Security Resources
11. Social Engineering
- Deep Dive: Why Social Engineering Works — Cognitive Psychology
- Knowledge Check Q&A
- Graph View Links

**Key Terms:** CIA Triad, Confidentiality, Integrity, Availability, AAA, Authentication, Authorization, Accounting, security controls (Deterrent, Preventive, Detective, Compensating, Corrective, Directive), Cybersecurity, Information Security, threat actor, Black/White/Gray hat, Script Kiddies, Hacktivists, Nation-State, Insiders, Competitors, Criminal Syndicates, Shadow IT, Brokers, Cyberterrorists, APT, threat vector, attack surface, supply chain attack, vulnerability, zero-day, firmware, EOL, misconfiguration, Data Loss, Data Exfiltration, Data Breach, Identity Theft, NIST CSF, PCI DSS, HIPAA, GDPR, ISO 27001, CIS Controls, CVE, NVD, CVSS, TTPs, STIX, social engineering, Authority, Intimidation, Consensus, Scarcity, Urgency, Familiarity, Trust, prepending, Phishing, Spear Phishing, Whaling, Vishing, Smishing, Typosquatting, Pharming, Tailgating, Piggybacking, Shoulder Surfing, Dumpster Diving, System 1/System 2

---

## 1. What Is Information Security?

### The Dual Definition

| Dimension | Definition |
|---|---|
| **As a goal** | Ensuring that only authorized users can view, use, and change information |
| **As a process** | The cycle of protecting information and information systems from unauthorized access, use, modification, disruption, disclosure, or destruction |

> Security is **not a destination** — it is an **endless cycle** between attacker and defender. As defenders harden systems, attackers adapt. As attackers find new techniques, defenders respond.

### The Security–Convenience Inverse Relationship

$$\text{Security} \propto \frac{1}{\text{Convenience}}$$

The **more secure** a system becomes, the **less convenient** it is. This is not a flaw; it is fundamental. The goal is not to maximize security in isolation, but to find a *practical equilibrium* acceptable to users and the organization.

---

## 2. The CIA Triad

Every information security decision ultimately protects three core properties. Together these form the **CIA Triad**:

| Property | Definition | Example |
|---|---|---|
| **Confidentiality** | Only **authorized** individuals can view information | Encrypting customer credit card numbers on a payment server |
| **Integrity** | Information is **correct** and has not been altered by unauthorized parties | Preventing an attacker from changing a $10,000 purchase amount to $1 |
| **Availability** | Authorized users can **access** information when needed | Ensuring warehouse staff can see inventory data 24/7 |

> **Memory tip:** The CIA Triad is the measuring stick against which every security decision is evaluated.

---

## 3. AAA Framework

Beyond CIA, security requires the **AAA** model of access management:

| Component | What It Does | Example |
|---|---|---|
| **Authentication** | Verifies **who you are** | Password, biometric, token |
| **Authorization** | Determines **what you may do** after authentication | Role-based access control; only finance can view payroll |
| **Accounting** | **Records** what you do | Audit logs timestamping every action |

Without all three, a security system is incomplete: even if you verify identity and grant correct access, without accounting you cannot detect abuse or reconstruct incidents.

---

## 4. Types of Security Controls

Security controls are grouped by **what they do** when an attack occurs:

| Type | Action | Example |
|---|---|---|
| **Deterrent** | Discourages an attacker from attempting the attack | Warning sign: "Authorized personnel only — video surveillance in use" |
| **Preventive** | Stops an attack from succeeding | Firewall blocking unauthorized inbound traffic |
| **Detective** | Identifies that an attack has occurred | Intrusion Detection System (IDS) alerting on anomalous traffic |
| **Compensating** | Alternative control when the ideal control is not feasible | Manual review as a substitute when automated access control is unavailable |
| **Corrective** | Restores system to normal state after an attack | Reinstalling OS from clean backup after a rootkit infection |
| **Directive** | Informs users of what they must do | Acceptable Use Policy (AUP) specifying prohibited activities |

---

## 5. Cybersecurity vs. Information Security

| Concept | Scope | Focus |
|---|---|---|
| **Information Security** | Broad — covers all forms of information (physical, digital, spoken) | Protecting **information** regardless of format |
| **Cybersecurity** | Narrow subset — specifically digital/cyber systems | Protecting **systems, networks, and programs** from digital attacks |

> Cybersecurity is a *discipline within* information security. Information security includes securing paper documents, enforcing clean-desk policies, and managing physical access — none of which are "cyber."

**Layers of Information Security:**
- Physical security
- Network security
- Host/endpoint security
- Application security
- Data security
- Policy/Human layer (often the weakest)

---

## 6. Threat Actors

A **threat actor** (also: *malicious actor*, *attacker*) is an individual or group responsible for a cyber incident. Every threat actor has four defining attributes:

| Attribute | What It Describes |
|---|---|
| **Level of capability / sophistication** | Technical skill and tool development ability |
| **Resources and funding** | Financial backing; determines persistence and scale |
| **Internal vs. External** | Whether they have trusted access (inside the organization) or work from outside |
| **Intent / Motivation** | The *why* driving the attack |

### Historical Hacker Classification (Broad Labels)

| Label | Description |
|---|---|
| **Black hat** | Attacks for personal gain, malice, or destruction; illegal |
| **White hat** | Ethical attacker; probes systems **with permission**; reports findings privately |
| **Gray hat** | Attacks **without permission**; discloses publicly to shame organization into action |

> These three labels are insufficient for modern analysis. The taxonomy below provides precision.

### Modern Threat Actor Taxonomy

| Actor Type | Motivation | Key Characteristics |
|---|---|---|
| **Unskilled Attackers (Script Kiddies)** | Fame, curiosity, excitement | Low skill; uses pre-built automated tools downloaded from the Internet; damage can be unpredictable because they don't fully understand what they're running |
| **Hacktivists** | Ideology, politics, cause | Defacement, DDoS, data leaks; no financial motive; may use social media influence campaigns |
| **Nation-State Actors** | Espionage, sabotage, financial harm to rivals | Highest sophistication; government-funded; unlimited resources; mission-driven; deploy **APT** (Advanced Persistent Threat) |
| **Insiders** | Financial gain, revenge, blackmail, ideology | Hardest to detect — they have trusted access; sources: disgruntled employees, contractors; categories: IP theft (43%), sabotage (41%), espionage (32%) |
| **Competitors** | Financial gain, market advantage | Steal research data, customer lists, trade secrets; corporate espionage |
| **Criminal Syndicates** | Fortune, financial crime | Professional online criminal networks; outsource actual attack execution; operate like corporations with IT departments |
| **Shadow IT** | Frustration with IT department pace | Employees install unauthorized hardware/software; inadvertently create vulnerabilities; not malicious intent but dangerous effect |
| **Brokers** | Financial gain | Discover vulnerabilities and **sell to highest bidder** rather than reporting; supply a marketplace for exploits |
| **Cyberterrorists** | Disruption, panic, psychological damage | Target critical infrastructure (power grids, water systems, emergency services, financial systems) |

### Advanced Persistent Threat (APT)

**APT** is the signature attack technique of **nation-state actors**. The name encodes two defining properties:

- **Advanced**: uses innovative, custom-developed tools not publicly available; designed to defeat known defenses.
- **Persistent**: once inside, silently exfiltrates data over **months or years**; will not leave even if initially discovered partially.

> **Critical distinction**: financially motivated attackers move on when a target is hardened. Nation-state actors are **mission-driven** — they persist until they succeed, regardless of how difficult the target becomes.

---

## 7. Threat Vectors and Attack Surfaces

A **threat vector** is the means by which an attack reaches its target. An **attack surface** is the sum total of all points where an attacker could enter or extract data.

### Primary Attack Vectors

| Vector | Description | Key Risk |
|---|---|---|
| **Email / Mainstream communications** | ~94% of all malware arrives via email | Phishing, malicious attachments, embedded links |
| **Wireless** | Data floats through airwaves; unencrypted traffic can be captured | Eavesdropping on open Wi-Fi |
| **Removable media** | Infected USB drives deliberately left in public spaces | Users plug in found drives out of curiosity |
| **Direct access (physical)** | Physical access to the machine; attacker can boot alternate OS | Bypasses all software-level protections |
| **Social media** | Reconnaissance of employee schedules; impersonation | Information harvesting for targeted spear phishing |
| **Supply chain** | Malware injected during manufacturing, storage, or distribution | Users receive infected devices at point of purchase; near-impossible to detect |
| **Cloud** | Complexity creates security weaknesses | Misconfiguration; constant external probing |

### Supply Chain Attack — Why It Is Uniquely Dangerous

The supply chain attack vector is especially insidious:
1. The attacker compromises a device **before the target ever touches it**.
2. The compromised device is delivered through normal, trusted channels.
3. The victim has no reason to suspect the device is compromised.
4. It is virtually impossible to notify all affected users.

**Examples:**
- Open-source software: attackers add malicious code to widely-used open-source packages downloaded by developers. When developers run `npm install` or `pip install`, they unknowingly import the malicious package.
- Hardware supply chain: firmware or chips modified during manufacturing before delivery.

---

## 8. Vulnerability Categories

A **vulnerability** is an exposed weakness that can be exploited. Vulnerabilities fall into four major categories:

### A. Software Vulnerabilities

Software vulnerabilities stem from:
- **Bugs**: logical errors in code creating unexpected, exploitable behavior.
- **Unsecure coding practices**: input validation failures, buffer management errors.
- **Legacy/EOL software**: software that no longer receives security patches. Every day that passes, more attackers know about the unpatched vulnerabilities; no defense is possible beyond moving off the legacy software.

### B. Hardware Vulnerabilities

| Hardware Risk | Explanation |
|---|---|
| **Firmware attacks** | Firmware (code embedded in hardware) is hard to patch; some devices require specialized steps; some cannot be patched at all |
| **End-of-Life (EOL) hardware** | Vendor no longer issues patches; known vulnerabilities remain permanently unaddressed |
| **Legacy hardware** | Outdated designs with architectural weaknesses that cannot be fixed without replacement |

### C. Misconfiguration Vulnerabilities

| Misconfiguration | Description | Example |
|---|---|---|
| Default settings | Vendor defaults optimized for usability, not security | Router with published default password (admin/admin) |
| Open ports and services | Maximum access enabled by default | Firewall with FTP ports 20/21 unnecessarily open |
| Unsecured root accounts | Full administrative access given too broadly | Misconfigured cloud storage granting all users root access |
| Open permissions | Over-permissive file access | User with Read/Write/Execute when only Read is needed |
| Unsecure protocols | Protocols lacking encryption | Using Telnet instead of SSH; SNMPv1 instead of SNMPv3 |
| Weak encryption | Vulnerable cipher or short key | DES (56-bit) when AES-256 is available |

### D. Zero-Day Vulnerabilities

A **zero-day** vulnerability is one the software developer does **not yet know about**. The name reflects that the developer has had zero days to respond.

**Key characteristics:**
- No patch exists — cannot fix what you don't know is broken.
- Discovered by threat actors *before* the developer discovers it.
- Standard signature-based defenses are useless (no signatures for unknown attacks).
- **Primary defense**: behavioral analysis and machine learning (detect anomalous activity rather than known attack signatures).

---

## 9. Impacts of Attacks

### Data-Specific Impacts

| Impact | Definition | Example |
|---|---|---|
| **Data Loss** | Destroying data so it cannot be recovered | Attacker erases years of cancer research |
| **Data Exfiltration** | Stealing data and distributing to other parties | Selling customer list to a competitor |
| **Data Breach** | Stealing data and disclosing it without authorization | Selling stolen credit card numbers on dark web markets |
| **Identity Theft** | Using stolen PII to impersonate someone | Using a stolen Social Security Number to secure a bank loan |

### Enterprise-Level Impacts

- **Availability loss** → operations halt → **financial loss** (direct lost revenue + recovery costs).
- **Reputation damage**: the public blames the organization for the breach; customer trust erodes; users migrate to competitors. Long-term brand damage can outlast the technical breach by years.

---

## 10. Information Security Resources

Organizations use multiple categories of resources to build and maintain security programs:

| Resource Type | Examples | Purpose |
|---|---|---|
| **Frameworks** | NIST Cybersecurity Framework (CSF), ISO 27001 | Structured guidance for building a security program |
| **Regulations** | HIPAA (healthcare), PCI DSS (payment cards), GDPR (EU data) | Legal compliance requirements |
| **Standards** | IEEE 802.11 (Wi-Fi), ITU-T X.509 (certificates) | Technical interoperability standards |
| **Benchmarks/Best Practices** | CIS Controls, DISA STIGs | Specific configuration hardening guidance |
| **Information sources (feeds)** | Mitre CVE/NVD, vendor advisories, threat intelligence feeds | Vulnerability data and emerging threat data |

### NIST Cybersecurity Framework (CSF)

The **NIST CSF** is the most widely adopted security framework. It organizes security activities into **five core functions**:

| Function | What It Means | Example Activities |
|---|---|---|
| **Identify** | Know your assets and risks | Asset inventory, risk assessment, governance |
| **Protect** | Implement safeguards | Access control, awareness training, data security, firewall deployment |
| **Detect** | Identify incidents in real time | IDS/IPS, SIEM, continuous monitoring |
| **Respond** | Act on detected incidents | Incident response plan, communication, analysis, mitigation |
| **Recover** | Restore capabilities after an incident | Recovery planning, improvements, communications |

> **Memory aid:** ID-PR-DE-RE-RE → Identify, Protect, Detect, Respond, Recover.

### PCI DSS (Payment Card Industry Data Security Standard)

- Developed by the major credit card companies (Visa, Mastercard, Amex, Discover, JCB).
- Applies to **any organization** that stores, processes, or transmits cardholder data.
- Specifies 12 technical requirements (install firewall, change defaults, protect stored data, encrypt transmission, use/maintain AV, develop secure systems, restrict access, authenticate users, restrict physical access, monitor access, test systems, maintain an information security policy).
- Non-compliance can result in fines or loss of ability to accept credit card payments.

### Vulnerability Feeds and TTPs

- **CVE (Common Vulnerabilities and Exposures)**: Mitre-maintained list of disclosed security vulnerabilities, each with a unique CVE ID.
- **NVD (National Vulnerability Database)**: NIST database that enriches CVE data with CVSS scoring.
- **TTPs (Tactics, Techniques, and Procedures)**: describes how threat actors think (tactics), the specific technical methods they use (techniques), and their operational patterns (procedures). Used in threat intelligence to profile attackers.

---

## 11. Social Engineering

**Social engineering** exploits **human psychology** rather than technology. It is the most reliable attack surface because:
- Technology can be patched; human cognition cannot.
- Cognitive shortcuts (heuristics) that enable fast decision-making can be hijacked.

### Psychological Principles Exploited

| Principle | How Attacker Uses It | Example |
|---|---|---|
| **Authority** | Impersonates or invokes authority figure | "I'm the CEO, reset my password now." |
| **Intimidation** | Threatens negative consequences | "If you don't help me, I'll report you to HR." |
| **Consensus (Social Proof)** | Implies others have already done it | "Your colleague reset my password last week." |
| **Scarcity** | References time or resource constraints | "I can't wait — I have three minutes before my flight." |
| **Urgency** | Demands immediate action without reflection time | "The board meeting starts in two minutes!" |
| **Familiarity** | Gives impression of being well-known | "We met at the security conference last month." |
| **Trust** | Builds rapport before making the request | "You come highly recommended by [name of colleague]." |

**Prepending**: priming the target's mental state *before* the attack. Example: "Best customer support you'll ever get!" primes the customer to be cooperative before any request is made.

### Attack Techniques

#### Impersonation and Phishing Variants

| Type | Description |
|---|---|
| **Phishing** | Mass email falsely claiming to be from a legitimate entity (bank, IRS, vendor) |
| **Spear Phishing** | Highly targeted phishing customized with personal data from prior reconnaissance |
| **Whaling** | Spear phishing targeting executives or high-value individuals |
| **Vishing** | Voice phishing via phone; often automated recorded calls demanding account info |
| **Smishing** | SMS text message phishing; includes callback number |

#### Redirection Attacks

| Attack | Mechanism |
|---|---|
| **Typosquatting** | Register domains with common misspellings of legitimate sites (`goggle.com`, `faceboook.com`) |
| **Pharming** | DNS manipulation redirects users from the correct URL to a fraudulent site |

#### Physical Social Engineering

| Technique | Description |
|---|---|
| **Tailgating** | Following an authorized person through a secured door without their knowledge; social etiquette overrides security instinct |
| **Piggybacking** | Authorized employee deliberately allows an unauthorized person to enter with them |
| **Shoulder Surfing** | Watching someone enter a PIN, password, or code; can be extended with small cameras |
| **Dumpster Diving** | Searching trash for useful data (org charts, phone directories, printed emails, USB drives) |

---

## Deep Dive: Why Social Engineering Works — Cognitive Psychology

Social engineers exploit two categories of cognitive bias:

**1. System 1 vs. System 2 Thinking (Kahneman)**
- **System 1**: fast, intuitive, automatic — used when under urgency or stress.
- **System 2**: slow, analytical, deliberate — used when calm and reflective.
- Social engineers force **System 1** to dominate by injecting urgency ("board meeting in 2 minutes!"), authority ("I'm the CEO"), and time pressure. The target's brain bypasses the skeptical System 2 analysis.

**2. Heuristics as Attack Vectors**
- **Authority heuristic**: wired from childhood to obey authority figures → attacker claims authority → compliance before critical evaluation.
- **Social proof heuristic**: "others have done it" removes personal responsibility → makes the action feel safe.
- **Scarcity heuristic**: limited resources = heightened arousal = reduced reasoning quality.

**Defense implication**: training users to recognize the *pattern* (urgency + authority = red flag) is more effective than attempting to teach every possible social engineering scenario. The goal is to trigger a mental "pause" that re-engages System 2 thinking.

---

## Knowledge Check Q&A

**Q1**: What is the primary distinction between cybersecurity and information security?  
**A**: Information security covers ALL forms of information (physical, verbal, digital). Cybersecurity is a subset that focuses specifically on protecting digital systems and data from attacks.

**Q2**: An attacker uses a fake law enforcement badge to get past a guard. What attack is this?  
**A**: Social engineering — specifically impersonation using the Authority principle.

**Q3**: What makes a zero-day vulnerability especially dangerous?  
**A**: The developer does not know it exists, so no patch can be created. Standard signature-based defenses are useless because there are no known signatures.

**Q4**: Which threat actor type is most likely to target critical infrastructure like a power grid?  
**A**: Nation-state actors (using APT) or cyberterrorists.

**Q5**: A company accepts payment cards. Which framework must it comply with?  
**A**: PCI DSS (Payment Card Industry Data Security Standard).

---

## Textbook Knowledge Check Questions (Ciampa CompTIA Security+ 8e)

> These are the **official end-of-section Knowledge Check Activities** reproduced verbatim from the Module 1 lecture deck (8th Edition, © 2025 Cengage), with the textbook's own answers and explanations.

**KC 1-1.** Serafina is studying to take the Security+ certification exam. Which of the following of the CIA elements ensures that only authorized parties can view protected information?
- A. Confidentiality
- B. Integrity
- C. Availability
- D. Credentiality

**Answer: A. Confidentiality.** Confidentiality ensures that only authorized parties can view the information. Providing confidentiality can involve several different security tools, ranging from software to encrypt the credit card number stored on the web server to door locks to prevent access to those servers.

---

**KC 1-2.** What is considered the motivation of an employee who practices shadow IT?
- A. Deception
- B. Ignorance
- C. Ethical
- D. Malicious

**Answer: C. Ethical.** The process of bypassing corporate approval for technology purchases is known as shadow IT. The employee's motivation is often ethical (it has sound moral principles) but nevertheless weakens security.

---

**KC 1-3.** What is another name for "attack surface"?
- A. Vulnerability exposure
- B. Threat vector
- C. Legacy platform
- D. Attack floor

**Answer: B. Threat vector.** An attack surface, also called a threat vector, is a digital platform that threat actors target for their exploits.

---

## Graph View Links

**Previous**: —  
**Next**: [[Module 3 - Threats and Attacks on Endpoints]]  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 1 - Introduction to Information Security]]
