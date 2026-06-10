# Module 2 – Threat Management and Cybersecurity Resources

**Source:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage, 2022) | Module 2  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #security #pentesting #vulnerability-scanning #SIEM #CS451

---

## Executive Summary

Threat management is the systematic process of minimizing the damage hostile cyber actions can inflict on an organization. This module covers two core offensive-defensive tools: **penetration testing** (simulating an attacker to find deep vulnerabilities) and **vulnerability scanning** (continuous automated monitoring of the attack surface). It also covers the data management tools (**SIEM** and **SOAR**) that consolidate and act on the flood of security events every enterprise faces. The key insight is that penetration testing and vulnerability scanning are *complementary*, not interchangeable.

---

## 1. Penetration Testing

### Why Perform a Penetration Test?

A **penetration test** ("pen test") attempts to exploit vulnerabilities exactly as a threat actor would, using both the same techniques and the same mindset. The distinction from a simple scan is critical:

| Dimension | Vulnerability Scan | Penetration Test |
|---|---|---|
| **Purpose** | Reduces the attack surface | Identifies *deep* vulnerabilities |
| **Procedure** | Finds weaknesses and mitigates them | Acts like a threat agent to *exploit* vulnerabilities |
| **Frequency** | Ongoing / continuous monitoring | Periodically or on regulatory schedule |
| **Personnel** | Internal security personnel | External third parties or internal teams |
| **Process** | Mostly automated | Entirely manual |
| **Goal** | Identify risks via scanning | Gain unauthorized access and demonstrate real-world exploitability |

> A scan reveals *surface* problems. A pen test exposes *deep* vulnerabilities that only appear when someone actively tries to break in. The most dangerous result of a poorly planned pen test is creating unnecessary legal issues — breaking into a network without proper authorization is a crime regardless of intent.

### Who Should Perform the Test?

#### Internal Security Personnel

**Advantages:**
- No additional cost
- Faster to deploy
- Enhances employee training and security awareness

**Disadvantages:**
- **Inside knowledge**: employees already know the network; a real attacker would not — so the simulation is inherently unrealistic.
- **Lack of expertise**: may lack credentials for a comprehensive test.
- **Reluctance to reveal**: employees may be unwilling to expose vulnerabilities in systems they personally manage.

#### Internal War Game Teams

| Team | Role | Duties | Note |
|---|---|---|---|
| **Red Team** | Attackers | Scans for and exploits vulnerabilities | May have unfair inside knowledge advantage |
| **Blue Team** | Defenders | Monitors for Red Team attacks; hardens defenses | Analyzes logs, traffic, signs of attack |
| **White Team** | Referees | Enforces rules; documents responses and attacks | Neutral observers |
| **Purple Team** | Bridge | Provides real-time feedback between Red and Blue | Blue learns to detect; Red learns about defensive technologies |

> **Capture the Flag (CTF)**: an optional incentive where challenges of varying difficulty are pre-defined; solvers earn "flags" worth points.

#### External Pen Tester Consultants

**Advantages:** expertise, credentials, experience, focus.  
**Disadvantage:** the consultant learns sensitive information about the network. Mitigated by a **Non-Disclosure Agreement (NDA)** requiring all data be destroyed or returned at test completion.

#### Penetration Testing Levels

| Level | Knowledge Given | Main Task | Advantage | Disadvantage |
|---|---|---|---|---|
| **Black Box** | None; no special privileges | Attempt to penetrate from scratch | Perfectly emulates an external threat actor | If network cannot be penetrated, no test can occur |
| **Gray Box** | Limited knowledge; some elevated privileges | Focus on highest-risk systems | More efficient; skips discovery phase | Head start prevents true external threat emulation |
| **White Box** | Full knowledge; source code access | Identify potential points of weakness directly | Focused, deep analysis | Does not reveal the full vulnerability picture |

#### Crowdsourced Pen Testing

A large pool of handpicked independent security researchers test the organization simultaneously. Advantages:
- Faster testing → quicker remediation
- Different individuals rotating through test cycles
- Multiple simultaneous tests

---

## 2. Rules of Engagement

The **rules of engagement** define the parameters of the pen test, preventing scope creep, legal issues, and wasted effort.

| Category | Key Consideration |
|---|---|
| **Timing** | Start/stop dates (allow 20% buffer); whether to test during business hours or off-hours |
| **Scope** | Live vs. simulated environment; internal targets (IP ranges, domains); external targets (cloud, ISPs); physical boundaries; social engineering targets |
| **Authorization** | Formal written approval from all parties *before* testing; cloud providers and ISPs require separate authorization |
| **Exploitation** | Define which vulnerabilities may be exploited; define "off-limits" data |
| **Communication** | Notify at initiation; report incidents immediately; provide periodic status; immediately escalate critical findings |
| **Cleanup** | Remove all agents, scripts, binaries, temporary files, backdoors; restore changed credentials; remove added accounts |
| **Reporting** | Two-part report: **executive summary** (strategic audience, risk overview) + **technical report** (security professionals, detailed vulnerabilities and remediation) |

> **Real-world cautionary tale (2019)**: Two Coalfire security contractors were arrested breaking into the Dallas County Courthouse during an Iowa state court pen test. Scope confusion meant county officials were never notified. Both parties later attributed it to "different interpretations of scope." Always obtain authorization at *every* level.

---

## 3. Performing a Penetration Test

A pen test is structured in two phases: **reconnaissance** and **penetration**.

### Phase 1: Reconnaissance (Footprinting)

#### Active Reconnaissance
Directly probing for vulnerabilities and information. Includes:
- **War driving**: searching for wireless signals from a vehicle or on foot using a portable device.

| War Driving Tool | Purpose |
|---|---|
| Mobile computing device | Primary detection device with wireless NIC |
| External wireless NIC adapter | Better sensitivity with external antenna jack |
| Antenna(s) | Extends detection range significantly |
| Specialized software | Provides more detail than built-in OS utilities |
| GPS receiver | Pinpoints locations precisely |

- **War flying**: using drones (UAVs) for faster, wider coverage — can fly over perimeters.

> **Disadvantage of active recon**: likely to alert in-house security who may lock down the network.

#### Passive Reconnaissance
Uses public information without sending probes to the target:
- **OSINT (Open Source Intelligence)**: publicly accessible information — social media, DNS records, job postings, company websites.
- Raises no alarms; testers "make do" with whatever public information is available.

### Phase 2: Penetration

Threat actors — and pen testers — follow this systematic process:

1. **Reconnaissance**: identify systems, look for vulnerabilities.
2. **Gain access**: exploit discovered vulnerabilities to enter the system.
3. **Privilege escalation**: escalate from user-level to admin/root access.
4. **Lateral movement**: move through the network from the initial compromise point.
5. **Install tools**: plant additional access mechanisms to extend reach.
6. **Install backdoor**: create persistent access that survives fixing the original vulnerability.
7. **Execute objective**: reach the ultimate target and perform the malicious action (steal data, disrupt operations).

> **Critical insight**: the initially compromised system is rarely the *target*. It is only a **gateway**. The pen tester must **pivot** from it to other systems. No vulnerability is insignificant — any vulnerability can serve as a stepping stone to the ultimate target.

> Unlike automated vulnerability scanning, penetration testing is entirely **manual**. Patience and persistence are essential — a good pen test takes time.

---

## 4. Vulnerability Scanning

### Defining a Vulnerability Scan

A **vulnerability scan** is a continuous, usually automated process that:
- Identifies current vulnerabilities
- Monitors cybersecurity progress
- Reduces the overall attack surface

It is cyclical and ongoing — not a one-time event.

### When and What to Scan

Not everything can be scanned all the time. Two constraints limit comprehensive scanning:

1. **Workflow interruptions**: continuous scanning degrades system response times; off-hours scanning is preferred.
2. **Technical constraints**: large networks with many devices may not fit within a single scanning window; bandwidth and license limitations apply.

**Best practice**: create an **asset inventory** listing all significant assets. Scan high-value assets more frequently. Use an *inventory scan* if no asset inventory exists.

### Types of Scans

#### Credentialed vs. Non-Credentialed

| Type | Description | Speed | Depth |
|---|---|---|---|
| **Non-credentialed** | No authentication; checks open ports and responding services | Faster | Surface-level |
| **Credentialed** | Provides valid credentials (username + password) to mimic a compromised insider | Slower | Deep; checks software configuration and security posture |

#### Intrusive vs. Nonintrusive

| Type | Description | Risk |
|---|---|---|
| **Intrusive** | Attempts to exploit found vulnerabilities; more accurate | Can impair or destabilize the target system |
| **Nonintrusive** | Records vulnerabilities without exploiting them | Cannot confirm true exploitability |

### Vulnerability Information Sources

- **Mitre CVE (Common Vulnerabilities and Exposures)**: the most popular vulnerability feed; assigns CVE IDs, brief descriptions, and references for OS and application vulnerabilities.
- **NVD (National Vulnerability Database)**: NIST database tracking CVE entries with scoring data.
- **CVSS (Common Vulnerability Scoring System)**: numeric scoring formula considering: access vector, attack complexity, authentication, confidentiality impact, integrity impact, and availability impact.

### Examining and Prioritizing Results

Vulnerability scan output requires careful interpretation:

#### Prioritization Questions
1. Can the vulnerability be addressed in a reasonable timeframe?
2. Can an *external* threat actor exploit it, or does it require physical/privileged access?
3. Would exploitation allow lateral movement to more critical systems?
4. Is the data on the affected device sensitive or public?
5. Is the vulnerable system critical to core operations?

> **Key principle**: vulnerabilities with the highest CVSS scores do not always deserve the earliest attention. Context — the organization's environment, risk tolerance, and remediation cost — determines actual priority.

#### False Positives and False Negatives
- **False positive**: alarm raised when no real problem exists. Common when scan options are misconfigured or when the scanner fails to recognize a compensating control already in place.
- **False negative**: failure to raise an alarm when a real vulnerability exists. More dangerous.

**Correlation with logs**: cross-referencing scan findings against system event logs (which record unsuccessful events, significant successful events, dates, times, error codes, user/system responsible) can identify false positives.

---

## 5. Data Management Tools

### SIEM — Security Information and Event Management

A **SIEM** (pronounced "seem") consolidates real-time security monitoring with analysis and reporting of security events. Data inputs include network packet captures and log collections from all devices.

| SIEM Feature | Description |
|---|---|
| **Aggregation** | Combines data from network devices, servers, and applications into a unified picture |
| **Correlation** | Searches aggregated data for common characteristics (e.g., multiple attacks from one IP) |
| **Automated alerting and triggers** | Informs security personnel of critical issues (e.g., "Alert when ≥40 packet drops from the same IP within 60 seconds") |
| **Time synchronization** | Orders events across a wide time spectrum to trace attack timelines |
| **Event duplication** | Filters multiple alerts from different devices detecting the same event into a single alarm |
| **Logs** | Retains event records for compliance and future forensic analysis |

**Advanced SIEM capabilities:**
- **User behavior analysis**: establishes a baseline of normal activity; lateral movement or unusual access generates an alert.
- **Sentiment analysis**: computationally categorizes emotions (positive/negative/neutral) in text to track threat actor discussions in forums and predict future attacks.

### SOAR — Security Orchestration, Automation and Response

**SOAR** extends SIEM by combining comprehensive data gathering and analytics to **automate incident response**. Where a SIEM generates alerts for humans to investigate, a SOAR can automatically execute predefined response playbooks.

| Dimension | SIEM | SOAR |
|---|---|---|
| Primary function | Collect, correlate, and alert | Collect, correlate, alert, *and* automate response |
| Human involvement | Required for investigation | Reduced — automates response workflows |

---

## Deep Dive: The Attacker's Mindset and Why It Matters

The most important insight in penetration testing is that **real attackers are not defeated by strong perimeter defenses**. They pivot. If the front door is locked, they look for a window. If that window is locked, they look for a basement entry. No single vulnerability is irrelevant because any foothold inside the perimeter becomes the launch point for reaching the true target.

This is why purely automated scanning (which only finds surface vulnerabilities) is insufficient for a mature security program. Only a human — simulating the creativity, persistence, and lateral thinking of a real threat actor — can reveal the full chain of exploitation that leads from an inconsequential configuration error to a full system compromise.

Pen testing, then, is not just a technical exercise. It is an **epistemological challenge**: can we discover what we don't know we don't know about our own defenses?

---

## Key Takeaways & Next Steps

1. **Pen testing and vulnerability scanning are complementary**: scans reduce the attack surface continuously; pen tests expose deep exploitation paths periodically.
2. **Authorization is non-negotiable**: always obtain written permission from *all* relevant parties, including cloud providers and ISPs.
3. **Scope and cleanup are as important as the test itself**: a pen test that does not clean up is itself a security incident.
4. **SIEM is the nervous system of a security operations center (SOC)**: without correlation and alerting, individual logs are noise; SIEM transforms them into intelligence.
5. **CVSS scores are a starting point, not a decision**: organizational context determines actual remediation priority.

---

## Graph View Links

**Previous**: [[Module 1 - Introduction to Information Security]]  
**Next**: [[Module 3 - Threats and Attacks on Endpoints]]  
**Hub**: [[CS451 - Hub]]
