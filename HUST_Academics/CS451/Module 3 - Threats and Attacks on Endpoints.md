# Module 3 – Threats and Attacks on Endpoints

**Source:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage, 2022) | Module 3  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #security #malware #application-attacks #endpoints #CS451

---

## Executive Summary

The word *endpoint* has replaced *host* and *client* because today's network-connected devices extend far beyond keyboards and monitors — encompassing smartphones, wearables, industrial sensors, automotive systems, and drones. Every endpoint is both a potential target and a potential entry point to the entire network. This module classifies the full spectrum of malware by its **primary action** (imprison, launch, snoop, deceive, evade) and examines **application-layer attacks** (XSS, SQL injection) that exploit web server logic. The ransomware economics section reveals why the threat is self-sustaining.

---

## 1. Malware Overview

**Malware** (malicious software) is software that enters a computer system without the user's knowledge or consent and performs an unwanted, harmful action. The legal definition is any instruction set "designed to modify, damage, destroy, record, or transmit information within a computer system or network without the intent or permission of the owner."

> There is no industry standard taxonomy for malware. The classification used here is by **primary action**: Imprison, Launch, Snoop, Deceive, Evade.

---

## 2. Imprison — Ransomware and Cryptomalware

### Ransomware

**Ransomware** prevents a user's endpoint from properly functioning until a fee is paid. The device is essentially held hostage — rebooting causes the ransomware to re-launch.

**Evolution of ransomware:**

1. **Blocker ransomware** (early form): displays a screen pretending to be law enforcement or a software vendor, blocks access, and demands a "fine" via online payment. Uses official-looking imagery.

2. **Modern ransomware**: drops the pretense entirely; blocks computer and demands a fee for release. Attackers have deliberately set ransoms to a "sweet spot":
   - Low enough that individuals pay rather than fight (~$500 for individuals).
   - High enough that the aggregate is profitable (average ransom >$1.3 million per enterprise; increased by one-third in recent years).

3. **Government targeting**: two-thirds of 2019 ransomware attacks targeted state and local governments with weaker security; >350 governments successfully attacked.

**Why cyber insurance fuels ransomware:**
Cyber insurance (an $8 billion industry) instructs insurers to pay ransoms because it holds down their overall costs compared to lost revenue from downtime and third-party recovery consultants. However, this reward mechanism incentivizes more attacks. The cyber insurance loss ratio is only **35 cents per dollar of premiums** (vs. ~62 cents for property/casualty), making cyber insurance extremely lucrative and arguably subsidizing ransomware growth.

> The first ransomware attack occurred in **1989**, when an AIDS researcher distributed 20,000 floppy disks to other researchers in 90+ countries. After 90 boot cycles, it demanded $189.

### Cryptomalware

A **more malicious variant** of ransomware: rather than just blocking the screen, cryptomalware **encrypts all files** on the device (and any connected network drives, USB drives, NAS, servers, and cloud repositories). The user must pay to receive the decryption key.

**Urgency mechanisms:**
- Ransom price escalates every few hours/days.
- Threat actors claim an increasing number of files will be permanently deleted until payment.
- If the deadline passes, the decryption key is claimed to be destroyed.

**Modern delivery behavior:**
- Decryption key is delivered ~99% of the time after payment.
- Key works ~96% of the time (some variants corrupt data during encryption).
- Threat actors maintain this reliability because it sustains victim willingness to pay.

---

## 3. Launch — Viruses, Worms, and Bots

This category of malware uses the infected computer to **launch attacks** on other computers.

### Virus

A computer virus requires **two carriers**: a file (to which it attaches) and a human (to transport it to other computers).

#### File-Based Virus

A file-based virus is malicious code **attached to a file**. It replicates on the host computer without human intervention (strictly speaking), but spreads to other computers only when a user transfers the infected file (email attachment, USB drive).

**Key properties:**
- Infects 50+ Windows file types (`.exe`, `.docx`, `.xlsx`, `.msi`, `.ps1`, `.wsf`, etc.)
- **Lifecycle**: infects → unloads payload (corrupt/delete files, steal data, disable security) → replicates into another file on the same host.
- **Appender infection**: virus attaches to the end of the file and inserts a jump instruction at the beginning redirecting execution to the virus code.

**Armored viruses (evasion techniques):**
- **Split infection**: splits malicious code into fragments placed at random positions throughout the program.
- **Mutation**: changes internal code to one of a set of predefined mutations on each execution.
- Some armored viruses detect security researcher tool files and self-destruct.

#### Fileless Virus

A fileless virus does **not** attach to a file. Instead, it uses **Living-off-the-Land Binaries (LOLBins)** — native OS services and processes — to load malicious code directly into RAM.

**Common Windows LOLBins exploited:**

| LOLBin | Description |
|---|---|
| PowerShell | Cross-platform task automation with full access to Windows OS core |
| Windows Management Instrumentation (WMI) | Standard for accessing device management information |
| .NET Framework | Developer platform for building applications |
| Macro (VBA) | Automation scripts stored within Office documents |

**Advantages of fileless viruses over file-based:**

| Property | Explanation |
|---|---|
| Easy to infect | Delivered via malicious webpages; browser executes JavaScript → invokes LOLBin |
| Extensive control | PowerShell has full OS access; can manipulate accounts and password protection |
| Persistent | Writes script to Windows Registry; re-launches on every reboot |
| Difficult to detect | No file to scan; LOLBins appear as trusted applications; PowerShell memory section is unsearchable |
| Difficult to defend | Disabling all LOLBins would cripple the OS; they are loaded at boot before any defense can act |

### Worm

A **worm** is a malicious program that spreads **autonomously across networks** by exploiting vulnerabilities in applications or OSs — without any human transport action.

| Feature | Virus | Worm |
|---|---|---|
| Self-replication scope | On the same host only | Across computers via network |
| Human transport needed | Yes (user transfers infected file) | No (autonomous network propagation) |
| Nickname | — | "Network virus" |

**Payload**: modern worms leave behind malware payloads (delete files, grant remote control) — not merely slow networks through replication.

> **First major worm (1988)**: exploited a misconfiguration in a remote command execution program. Affected ~6,000 computers (10% of the Internet at the time).

### Bot / Botnet

A **bot** (zombie) is an infected computer placed under remote attacker control. A **botnet** aggregates hundreds, thousands, or millions of bots under a **bot herder**.

**Botnet command structures:**
- Bot-herding website where commands are posted for bots to fetch.
- Third-party website sign-in (no direct affiliation needed).
- Commands encoded in blog posts, Twitter posts, or Facebook notes.
- **Dead drop C&C**: bot herder creates a draft email in Gmail (never sent); bot logs in and reads the draft. No sent-message record; all traffic encrypted.

| Botnet Use | Description |
|---|---|
| **Spam** | Send massive volumes of spam from thousands of IPs |
| **Spread malware** | Download and execute files, create new bots |
| **Ad fraud** | Simulate mouse clicks on ads to generate fraudulent revenue |
| **Cryptomining** | Combine millions of bots to verify cryptocurrency transactions |

---

## 4. Snoop — Spyware and Keyloggers

### Spyware

**Spyware** is tracking software deployed **without user consent**. It secretly monitors users by collecting personal or sensitive information.

| Technology | Description | Impact |
|---|---|---|
| Automatic download | Installs software without user interaction | Could install unauthorized applications |
| Passive tracking | Gathers information without installing software | Collects browsing history, private data |
| System-modifying software | Alters configurations (browser home page, search engine, media player) | Changes not approved by user |
| Tracking software | Monitors behavior; collects PII | Can lead to fraud or identity theft |

> Not all spyware is inherently malicious — parental monitoring tools use the same mechanisms.

### Keylogger

A **keylogger** silently captures and stores every keystroke typed on the keyboard. Threat actors later search the captured text for passwords, credit card numbers, and personal information.

| Type | Mechanism | Advantage | Disadvantage |
|---|---|---|---|
| **Software keylogger** | Program installed on the computer; captures keystrokes, screenshots, and webcam images | Remote installation; no physical access needed; sends data over victim's Internet connection | Can be detected by antimalware |
| **Hardware keylogger** | Physical device inserted between keyboard and USB port | Undetectable by antimalware; looks like a normal keyboard plug | Requires physical installation and retrieval; attacker must return to collect the device |

---

## 5. Deceive — PUPs, Trojans, and RATs

### Potentially Unwanted Programs (PUPs)

**PUPs** are software the user does not want, often installed alongside other programs when users overlook default installation options. Examples:
- Pre-installed bloatware on new devices that cannot be easily removed.
- Advertising, pop-ups, browser toolbar injections.
- Home page hijacking, search result alteration, settings that redirect to competitors' sites.

### Trojan

A **Trojan** masquerades as a benign application while performing malicious actions. Named for the Trojan Horse of Greek legend — a gift concealing an attack force.

Example: a user downloads a "calendar program" that also scans for credit card numbers and transmits them to an attacker's server.

### Remote Access Trojan (RAT)

A **RAT** extends the Trojan's capabilities by providing **unauthorized remote access** to the victim's computer via specially configured communication protocols. The attacker can:
- Monitor user activity in real time.
- Change system settings.
- Browse and copy files.
- Use the victim's computer to access other network-connected devices.

---

## 6. Evade — Backdoors, Logic Bombs, and Rootkits

### Backdoor

A **backdoor** bypasses normal security protections to provide access to a computer, program, or service. Backdoors are legitimately used by developers for ongoing access — but are supposed to be removed before production release. When they are not (or when attackers install their own), they create permanent, stealthy re-entry points.

### Logic Bomb

A **logic bomb** is code embedded in a legitimate program that lies dormant until a specific logical event triggers it. Once triggered, it executes malicious actions (data deletion, sabotage).

**Why logic bombs are hard to detect:**
- Embedded in large codebases (hundreds of thousands of lines) — a few malicious lines are invisible.
- Programs are not routinely scanned for malicious logic.
- Trusted employees can plant them undetected.

> Example: a Maryland government employee planted a logic bomb script scheduled to destroy 4,000 servers 90 days after his termination.

### Rootkit

A **rootkit** hides its own presence and the presence of other malware by accessing **lower layers of the OS** or using **undocumented system functions**. This makes it and any accompanying software invisible to the OS and standard antimalware scanners.

**Modern OS mitigations** (significantly diminish rootkit risk):
- Preventing unauthorized kernel drivers from loading.
- Blocking modifications to kernel areas used by rootkits to hide.
- Preventing rootkits from modifying the bootloader.

---

## 7. Application Attacks

Application attacks target **software already running on devices** rather than adding new malware. The most common targets are **Internet web servers**, because a single web server vulnerability can expose thousands of users.

### Web Application Infrastructure

```
Client Browser
    ↓ HTTP
Web Server
    ↓
Application Server(s)
    ↓
Database Server(s) (internal network)
```

Each layer is a potential attack surface. A vulnerability anywhere can cascade to compromise backend databases and network infrastructure.

### Cross-Site Scripting (XSS)

**XSS** exploits websites that accept user input without sanitizing (validating) it and include that input in their response.

**Attack mechanism:**
1. A website has a form that echoes user input (e.g., a bookmark sharing site that greets users by name).
2. The site does not validate the `Name` field before including it in the "Thank You" response page.
3. An attacker submits malicious JavaScript as the name field value.
4. The server embeds the script in the response and sends it to another user's browser.
5. That browser executes the script — giving the attacker control of that user's session.

> The name "cross-site scripting" reflects that the attack *originates* on the web server but *executes* on the victim's computer.

### SQL Injection

**SQL injection** inserts malicious SQL statements into a database query by exploiting unsanitized user input.

**Attack example** (password reset form):

```sql
-- Legitimate query when user enters: braden.thomas@fakemail.com
SELECT fieldlist FROM table WHERE field = 'braden.thomas@fakemail.com'

-- Attacker's injection: whatever' or 'a'='a
SELECT fieldlist FROM table WHERE field = 'whatever' or 'a'='a'
```

**Why this works:**
- `'whatever'` matches nothing in the database.
- `or` means: if *either* condition is true, the entire WHERE clause is true.
- `'a'='a'` is **always** true.
- Therefore the WHERE clause is always true → all records in the table are returned.

**Detection method:** enter a single quotation mark as input.
- `Email Address Unknown` → input is properly sanitized. No vulnerability.
- `Server Failure` → input is **not** sanitized; SQL syntax error from the extra quote. Vulnerability confirmed.

By submitting crafted SQL statements, attackers can extract all data from the database or manipulate existing records (delete, modify, insert).

---

## Deep Dive: The Ransomware Economics Loop

Ransomware is not merely a technical problem — it is a **self-sustaining economic ecosystem** with multiple aligned incentives:

1. **Attackers** earn guaranteed payment (ransoms are paid 99% of the time and work 96% of the time).
2. **Cyber insurers** prefer paying ransoms (holds down their overall costs; loss ratio only 35%).
3. **Victims** prefer paying (faster recovery than rebuilding from scratch; insurers encourage it).
4. **The ecosystem grows**: ransomware payment reliability attracts more criminals; increasing attacks drive more businesses to buy cyber insurance; higher premiums increase insurer profits.

The cycle is broken only when victims *cannot* or *choose not* to pay — which requires either resilient backup strategies (making recovery cheap) or government policy preventing ransom payments to designated criminal groups.

**Defensive implication**: the best defense against ransomware is **not** better detection of the ransomware itself — it is **resilient, tested, and air-gapped backups** that make paying the ransom unnecessary.

---

## Key Takeaways & Next Steps

1. **Fileless viruses** are the current frontier of malware evasion: they leave no file to scan, use trusted OS components, and persist across reboots through the Registry.
2. **Cryptomalware** makes backup integrity the primary defense — any backup reachable from the infected network can itself be encrypted.
3. **RATs** represent a total loss of endpoint control; assume compromise of all credentials and data accessible from the affected device.
4. **SQL injection** is still the #1 web application vulnerability class (OWASP Top 10); input validation and parameterized queries are the mitigation.
5. **Botnets** aggregate ordinary computers into weapons — users are entirely unaware their machine is attacking others.

---

## Graph View Links

**Previous**: [[Module 2 - Threat Management and Cybersecurity Resources]]  
**Next**: [[Module 6 - Basic Cryptography]]  
**Hub**: [[CS451 - Hub]]
