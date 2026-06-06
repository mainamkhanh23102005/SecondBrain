# Module 1 – Introduction to Information Security

**Source:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage, 2022) | Module 1  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #security #cybersecurity #CS451

---

## Executive Summary

This module establishes the conceptual bedrock of cybersecurity. It defines information security through the lens of the **CIA Triad**, catalogues the full taxonomy of **threat actors** and their motivations, maps **vulnerability categories** and **attack vectors**, and dissects the psychology and mechanics of **social engineering**. The central tension in security is the inverse relationship between security and convenience — increasing one always diminishes the other — and the field's goal is not perfect security but *equilibrium*.

---

## 1. What Is Information Security?

### The Security–Convenience Trade-off

Security and convenience are **inversely proportional**:

$$\text{Security} \propto \frac{1}{\text{Convenience}}$$

The more secure a system becomes, the less convenient it is to use. This is not a flaw — it is an inherent property. The goal of information security is therefore not elimination of all risk (impossible) but the maintenance of a *practical equilibrium*: as attackers adapt, defenders must adapt.

> "Information security is an endless cycle between attacker and defender."

### The CIA Triad

All information security policy ultimately protects three properties:

| Property | Definition | Example |
|---|---|---|
| **Confidentiality** | Only authorized individuals can view information | Encrypting credit card numbers on a web server |
| **Integrity** | Information is correct and has not been altered by unauthorized parties | Preventing an attacker from changing a purchase amount from $10,000 to $1 |
| **Availability** | Authorized users can access information when needed | Ensuring warehouse employees can view order data |

### Security Workforce Roles

| Role | Reports To | Key Responsibility |
|---|---|---|
| **CISO** (Chief Information Security Officer) | CIO | Assessing, managing, and implementing all security |
| **Security Manager** | CISO | Supervises technicians; resolves issues; works on CISO-identified tasks |
| **Security Administrator** | Security Manager | Manages daily operations; analyzes and designs solutions |
| **Security Technician** | Security Administrator | Entry-level; configures hardware, implements software, diagnoses problems |

The information security workforce can be divided into two broad categories:
- **Managerial personnel**: administer plans, policies, and people.
- **Technical personnel**: design, configure, install, and maintain security systems.

### CompTIA Security+ Certification

The **SY0-601** exam is the standard benchmark for entry-level security skills. It is vendor-neutral, DoD 8140-approved, and ISO 17024-compliant. Holders command salaries 5–15× higher than non-certified peers with similar qualifications.

---

## 2. Threat Actors

A **threat actor** (also called a *malicious actor* or *attacker*) is an individual or entity responsible for cyber incidents. Threat actors are characterized by four attributes:

- **Level of capability/sophistication**: technical skill and resource access
- **Resources and funding**: financial backing available
- **Internal vs. External**: position relative to the organization
- **Intent/Motivation**: the *why* behind the attack

### Types of Hackers (Historical Classification)

| Type | Description |
|---|---|
| **Black hat** | Attacks for personal gain or malicious damage; illegal |
| **White hat** | Ethical attackers; probe systems *with permission* and report findings privately |
| **Gray hat** | Break in *without permission* but disclose publicly to shame the organization into action |

> These broad labels are insufficient today. Modern categorization is more precise.

### Modern Threat Actor Taxonomy

| Actor Type | Motivation | Key Characteristics |
|---|---|---|
| **Script Kiddies** | Fame, curiosity | Low skill; uses pre-built automated attack tools; unpredictable damage |
| **Hacktivists** | Ideology/politics | Deface websites, DDoS, disinformation campaigns; no financial motive |
| **State Actors** | Espionage, sabotage, financial harm | Highest sophistication; unlimited government resources; persistent; use **APT** |
| **Insiders** | Financial gain, revenge, espionage | Hardest to detect; trusted access; IP theft (43%), sabotage (41%), espionage (32%) |
| **Competitors** | Financial gain | Steal research, customer lists |
| **Criminal Syndicates** | Fortune | Professional online criminal networks; outsource actual crimes |
| **Shadow IT** | Frustration with IT pace | Employees install unauthorized hardware/software; inadvertently create vulnerabilities |
| **Brokers** | Financial gain | Discover vulnerabilities and sell to highest bidder instead of reporting |
| **Cyberterrorists** | Disruption, panic | Target critical infrastructure (power grids, emergency services) |

### Advanced Persistent Threat (APT)

APT is the signature tool of **state actors**. The name describes its two defining features:

- **Advanced**: uses innovative, custom tools.
- **Persistent**: silently extracts data over months or years after initial compromise.

APT represents the highest tier of threat sophistication. Unlike financially motivated attackers who move on when a target is too hardened, state actors are mission-driven and will persist until success.

---

## 3. Vulnerabilities

A **vulnerability** is the state of being exposed to the possibility of being attacked or harmed.

### Vulnerability Categories

#### A. Platform Vulnerabilities

| Platform Type | Why Vulnerable |
|---|---|
| **Legacy Platforms** | Outdated OS/software no longer receives security patches; known vulnerabilities are unpatched |
| **On-Premises Platforms** | Rapid provisioning without adequate security configuration; multiple network entry points (USB, wireless, email) |
| **Cloud Platforms** | Misconfiguration by company personnel; accessible from anywhere, constantly probed |

#### B. Weak Configurations

| Configuration Issue | Explanation | Example |
|---|---|---|
| Default settings | Set for usability, not security | Router with default password widely known |
| Open ports and services | Maximum access by default | Firewall with FTP ports 20/21 open |
| Unsecured root accounts | Unfettered access to all resources | Misconfigured cloud storage giving all users root |
| Open permissions | Over-permissive file access | User with Read/Write/Execute when only Read is needed |
| Unsecure protocols | Lacks adequate protection | Telnet, SNMPv1 instead of SSH/SNMPv3 |
| Weak encryption | Vulnerable cipher or short key | Using DES or a 56-bit key where AES-256 is available |
| Errors | Human mistakes in configuration | Using deprecated settings instead of current ones |

#### C. Third-Party Vulnerabilities

**Vendor management** is the process of monitoring and managing interactions with external third parties. Third-party risks include:

- **System integration gaps**: workarounds create vulnerabilities when systems are incompatible.
- **Weakest link principle**: the Target breach (2013) occurred because attackers breached an HVAC contractor with network access, then pivoted into Target's payment systems, stealing 40 million credit card numbers.

#### D. Patch Vulnerabilities

Patches are security updates that fix uncovered vulnerabilities. However, patching itself introduces risks:

- **Firmware is hard to patch**: specialized steps required; some firmware cannot be patched at all.
- **Few patches for apps**: no automated distribution for most application software.
- **Patch delays**: organizations test patches before deployment to prevent breaking custom applications, leaving a window of exposure.

#### E. Zero-Day Vulnerabilities

A **zero-day** vulnerability is one that the software developer does not yet know about. Because no patch exists:
- Systems are open to attack with no specific mitigation.
- Discovered by threat actors *before* developers; zero days of warning.
- Defenses rely on behavioral analysis and machine learning rather than signature-based detection.

---

## 4. Attack Vectors

An **attack vector** is a pathway used by a threat actor to penetrate a system.

| Vector | Description | Key Risk |
|---|---|---|
| **Email** | ~94% of all malware delivered via email; tricks users into opening attachments or clicking links | Most common delivery mechanism |
| **Wireless** | Data "floats" through airwaves; unprotected transmissions can be intercepted | Eavesdropping on unencrypted Wi-Fi |
| **Removable media** | Infected USB drives left in public spaces | Users plug in found drives out of curiosity |
| **Direct access** | Physical access to the machine; attacker can boot alternate OS to bypass security | Bypasses all software-level protections |
| **Social media** | Reconnaissance of employee schedules; impersonation to help desk | Information harvesting for targeted attacks |
| **Supply chain** | Malware injected during manufacturing or storage of devices | Users receive infected devices at point of purchase; virtually impossible to detect |
| **Cloud** | Complexity of cloud systems creates security weaknesses | Misconfigurations; constant external probing |

> **Supply chain infections** are especially dangerous: users receive compromised devices out-of-box and there is no practical way to notify all affected users.

---

## 5. Social Engineering

**Social engineering** elicits information or triggers actions by exploiting human psychology rather than technology. It can also be used in **influence campaigns** (social media or hybrid warfare) to sway public opinion.

### Psychological Principles

| Principle | Description | Example |
|---|---|---|
| **Authority** | Impersonate or invoke an authority figure | "I'm the CEO calling." |
| **Intimidation** | Coerce through threat | "If you don't reset my password, I'll call your supervisor." |
| **Consensus** | Use social proof — others have done it | "I called last week and your colleague reset my password." |
| **Scarcity** | Reference something in short supply | "I can't waste time here." |
| **Urgency** | Demand immediate action | "My meeting with the board starts in five minutes." |
| **Familiarity** | Give impression of being well-known | "I remember reading a good evaluation on you." |
| **Trust** | Inspire confidence | "You know who I am." |

**Prepending**: influencing the subject *before* the event occurs to prime their response in a desired direction (e.g., "The best film you'll see this year!" primes you to enjoy the movie).

### Techniques for Gaining Trust

- **Provide a reason**: using "because" dramatically increases compliance.
- **Project confidence**: moving through restricted areas calmly, greeting people, avoids suspicion.
- **Evasion and diversion**: giving vague answers, feigning confusion, or resorting to anger to deflect challenges.
- **Humor**: puts people at ease and builds a sense of trust.

### Attack Types: Psychological

#### Impersonation (Identity Fraud)
Masquerade as a real or fictitious character. Goal: obtain private information (**pretexting**). Requires **credential harvesting** (reconnaissance via Internet and social media) to build a convincing persona.

#### Phishing Variants

| Type | Description |
|---|---|
| **Phishing** | Generic mass-email falsely claiming to be from a legitimate entity |
| **Spear Phishing** | Targeted phishing customized to specific individuals using their personal data |
| **Whaling** | Spear phishing targeting wealthy individuals or senior executives |
| **Vishing** | Voice phishing via recorded phone calls demanding account info |
| **Smishing** | SMS text message phishing; includes callback number played by recording |

#### Redirection Attacks

| Attack | Mechanism |
|---|---|
| **Typosquatting** | Registering domains that are common misspellings of legitimate sites (e.g., `goggle.com`) |
| **Bitsquatting** | Registering domains that differ by a single bit flip in a character (e.g., `aeazon.com`) |
| **Pharming** | Malware or DNS infection redirects users from intended sites to fraudulent ones |

#### Spam and Spim
- **Spam**: unsolicited bulk email; ~99% sent from botnets; even 0.001% response rate is profitable at scale.
- **Image spam**: uses graphical text to defeat text-based spam filters.
- **Spim**: spam via instant messaging; more dangerous because immediacy triggers reflexive clicks.

#### Hoaxes
False warnings from "IT department" instructing users to erase files or change configurations — actions that actually create vulnerabilities or install attacker tools.

#### Watering Hole Attack
Identify a website commonly visited by a target group; infect that site with malware. Victims are compromised simply by visiting a trusted, familiar site.

### Attack Types: Physical

| Attack | Description |
|---|---|
| **Dumpster Diving** | Searching trash for useful information (memos, org charts, phone directories, manuals, USB drives) |
| **Google Dorking** | Advanced Google searches to find sensitive data carelessly posted online (`intext:"SSN" filetype:xlsx`) |
| **Tailgating** | Following an authorized user through a secured door without credentials; relies on social etiquette overriding security |
| **Piggybacking** | Authorized employee deliberately allows an unauthorized person to enter with them |
| **Shoulder Surfing** | Watching someone enter codes or passwords; extended by cameras and smartphones |

---

## 6. Impact of Attacks

### Data Impacts

| Impact | Description | Example |
|---|---|---|
| **Data Loss** | Destroying data so it cannot be recovered | Erasing patient data used for cancer research |
| **Data Exfiltration** | Stealing data to distribute to other parties | Selling a customer list to a competitor |
| **Data Breach** | Stealing data to disclose it in an unauthorized fashion | Selling credit card numbers to other threat actors |
| **Identity Theft** | Using PII to impersonate someone | Using a stolen SSN to secure a bank loan |

### Enterprise Impacts

- **Availability loss** → lost productivity → **financial loss**.
- **Reputation damage**: public blames the organization for its own breach; customers migrate to competitors.

---

## Deep Dive: Why Social Engineering Is So Effective

The reason social engineering succeeds is rooted in cognitive psychology. Humans have **cognitive shortcuts** (heuristics) that allow quick decision-making. Social engineers hijack these shortcuts:

- **Authority heuristic**: we are wired from childhood to obey authority figures. A caller claiming to be the CEO triggers automatic deference before critical evaluation occurs.
- **Urgency/Scarcity heuristic**: when time is short or resources are scarce, the brain shifts from System 2 (slow, analytical) to System 1 (fast, intuitive) thinking — bypassing security skepticism.
- **Social proof heuristic**: "others have done it" removes the feeling of personal responsibility for the decision.

The attacker's goal is to trigger these heuristics and act *before* the target has time to engage analytical thinking. This is why defenses focus on training users to recognize the trigger patterns (urgency + authority = red flag) rather than relying on technology alone.

---

## Key Takeaways & Next Steps

1. The **CIA Triad** is the foundation — every security decision is ultimately measured against Confidentiality, Integrity, and Availability.
2. **State actors** are the most dangerous threat actors: unlimited resources, specific targets, and near-infinite persistence.
3. **Zero-day vulnerabilities** are the hardest to defend; behavioral detection and least-privilege architecture are the primary mitigations.
4. **Social engineering** bypasses technology entirely; human psychology is the most reliable attack surface.
5. **Supply chain attacks** are uniquely dangerous because the compromise occurs before the victim ever touches the device.

**Next Topics**: [[Module 2 - Threat Management and Cybersecurity Resources|Penetration Testing & Vulnerability Scanning]]

---

## Graph View Links

**Previous**: —  
**Next**: [[Module 2 - Threat Management and Cybersecurity Resources]]  
**Hub**: [[CS451 - Hub]]
