# Module 8 – Network Security: Threats, Assessments, and Defenses

**Source:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage, 2022) | Module 8  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #security #networking #MITM #DDoS #DNS #ARP #CS451

---

## Executive Summary

Networks are the circulatory system of modern computing — and the primary attack surface. A single network vulnerability can expose hundreds or thousands of devices simultaneously. This module categorizes **network-specific attacks** (interception, Layer 2, DNS, DDoS, and malicious scripting), then covers **assessment and defense tools** (network reconnaissance utilities, packet capture tools). The IoT case study that opens the module illustrates a critical modern principle: **every Internet-connected device is an attack surface**, even "uninteresting" ones like smart windows.

---

## 1. The IoT Attack Surface

The module opens with the case of **View** smart windows — Internet-connected, IP-addressed, smartphone-controlled windows. The CEO claimed: "The good news is the window's not that interesting to hack."

Security professionals would strongly disagree. IoT devices like these are targets for **three reasons**:

1. **Network entry point**: IoT devices typically lack robust security, making them easy pivot points into corporate networks. In one cited attack, Russian state actors used printers and video decoders as entry points, then ran tcpdump to sniff internal subnets and installed shell scripts for persistent access.

2. **Attack point against other networks**: Compromised IoT devices are harvested into botnets and used to launch DDoS attacks against third parties.

3. **Backflow into the vendor's own network**: View windows require remote connectivity to View's headquarters for "commissioning, configuring, monitoring, and maintaining." An attacker who compromises a window installed at *another company* can potentially backflow into View's own network.

> **Lesson**: in an IoT world, "not interesting to hack" is never a valid security posture. Every network-connected endpoint, regardless of function, must be hardened.

---

## 2. Interception Attacks

### Man-in-the-Middle (MITM)

In an **MITM attack**, a threat actor positions themselves between two communicating parties — neither party is aware of the interception.

**Two phases:**
1. **Interception**: alter packet headers in an IP address so users attempting to reach a legitimate URL are redirected to the attacker's site.
2. **Decryption**: send a fake digital certificate associated with a compromised application to trick the victim's computer into accepting the attacker's session.

```
Bob ←→ [Threat Actor] ←→ Alice
         (invisible, intercepting and possibly modifying all traffic)
```

### Session Replay Attack

A **replay attack** is a variation of MITM where the attacker copies a legitimate transmission *before* forwarding it to the recipient. The copy is used later when the attacker "replays" the captured transmission to impersonate the legitimate user.

**Session replay** specifically targets **session IDs** — unique numbers assigned by web servers for the duration of a user's visit.

Session IDs are typically:
- At least **128 bits** in length.
- Generated using date, time, IP address, email, username, user ID, role, privilege level, access rights, etc.
- Hashed using a secure hash function like SHA-256.

A sample session ID: `fa2e76d49a0475910504cb3ab7a1f626d174d2d`

**How session IDs are stolen:**
- Network attacks: hijacking communication, altering traffic between two users.
- Endpoint attacks: cross-site scripting, Trojans, malicious JavaScript.

Once stolen, the threat actor can impersonate the victim for the session.

### Man-in-the-Browser (MITB)

**MITB** is more targeted than MITM. Rather than intercepting between two network endpoints, it intercepts between the **web browser and the underlying computer's security mechanisms**.

**Attack flow:**
1. Trojan infects the computer and installs a malicious **browser extension**.
2. Opening the browser activates the extension.
3. When the user navigates to a targeted site (e.g., an online bank), the extension activates.
4. User signs in → extension waits for the financial transaction page.
5. User clicks Submit → extension **captures all form data and may modify fields**.
6. Browser sends (modified) data to server → server executes transaction and sends receipt.
7. Extension **intercepts the receipt and modifies it** to show the original values — user sees a normal receipt.

**Why MITB is dangerous:**
- Distributed via Trojan browser extensions (appear legitimate).
- The extension can remain dormant for months until the user visits a targeted site.
- Resides within the browser — standard antimalware typically cannot detect it.

---

## 3. Layer 2 Attacks

### OSI Model Context

The **OSI reference model** (1978, revised 1983) describes network communication as 7 layers:

| Layer | Name | Responsibility | Key Identifier |
|---|---|---|---|
| 7 | Application | End-user applications | Application stream (POP3, IMAP, SSL, SSH) |
| 6 | Presentation | Data format translation | — |
| 5 | Session | Managing sessions between applications | — |
| 4 | Transport | End-to-end communication, error recovery | Protocols/ports |
| 3 | Network | Routing between networks | IP addresses |
| 2 | Data Link | Physical addressing, framing, error detection | MAC addresses |
| 1 | Physical | Physical transmission of raw bits | Physical links |

**Layer 2 is a prime attack target** because it is **compartmentalized**: if Layer 2 is compromised, all higher layers continue operating — unaware that all their communication is now flowing through an attacker.

### ARP Poisoning

**Address Resolution Protocol (ARP)** maps IP addresses (logical, changeable) to MAC addresses (physical, burned-in to NICs). When a device needs a MAC address for a known IP, it broadcasts an ARP request; the target responds with its MAC address, and all devices cache the result.

**ARP poisoning exploit:**
- ARP has **no authentication** — any device can claim any IP-to-MAC mapping.
- Threat actor sends **spoofed ARP replies** to victims, mapping their MAC address to a victim's IP.
- Victims update their ARP caches with the fraudulent mapping.
- All traffic intended for the victim is now redirected to the threat actor.

**ARP cache before/after an MITM poisoning:**

| Device | IP | MAC | Victim 1's ARP Cache Before | After |
|---|---|---|---|---|
| Threat Actor | 192.146.118.2 | 00-aa-BB-cc-dd-02 | — | Victims now cache 192.146.118.3 and .4 as the threat actor's MAC |
| Victim 1 | 192.146.118.3 | 00-aa-BB-cc-dd-03 | Correct mappings | Threat actor's MAC mapped to Victim 2's IP |
| Victim 2 | 192.146.118.4 | 00-aa-BB-cc-dd-04 | Correct mappings | Threat actor's MAC mapped to Victim 1's IP |

### MAC Address Attacks on Switches

A **switch** learns which device is on each port by recording the source MAC address of packets it receives, building a **MAC address table** (stored in Content Addressable Memory, CAM).

#### MAC Cloning

1. Attacker discovers the MAC address of a legitimate device on the switch.
2. Attacker **spoofs that MAC** on their own device.
3. Attacker sends a packet onto the network with the spoofed MAC as source.
4. Switch **updates its MAC address table**: the legitimate MAC is now associated with the attacker's port.
5. All future packets intended for the legitimate device are forwarded to the attacker.

#### MAC Flooding

1. Attacker floods the switch with packets — **each from a different spoofed MAC address**.
2. The switch's CAM fills up with thousands of fake MAC-to-port entries.
3. CAM capacity exhausted → switch enters **fail-open mode** → broadcasts all frames to all ports.
4. Attacker can now capture all traffic on any port (equivalent to being on a hub, not a switch).

> **A MAC flooding attack on one switch fills adjacent switches' CAM tables as well**, cascading through the network.

---

## 4. DNS Attacks

The **Domain Name System (DNS)** translates human-readable hostnames (e.g., `google.com`) into IP addresses. DNS is critical infrastructure — attacking it enables **URL redirection** (send users to fraudulent sites) and **domain reputation damage** (earned by a competitor using DNS attacks to associate the target domain with spam or malware).

### DNS Poisoning (Local)

Targets the local **HOSTS file** on the victim's device.

TCP/IP checks the local HOSTS file before querying external DNS:
```
127.0.0.1    localhost
74.125.47.99 www.google.com
216.77.188.41 www.att.net
```

An attacker modifies the HOSTS file to redirect specific domain names to malicious IP addresses. Since most users are unaware the HOSTS file exists, infections can persist undetected.

**HOSTS file locations:**
- UNIX/Linux/macOS: `/etc/hosts`
- Windows: `C:\Windows\System32\drivers\etc\hosts`

### DNS Hijacking (External)

Targets external DNS servers by exploiting **zone transfer vulnerabilities** — DNS servers exchange data between themselves to stay synchronized.

**Attack flow:**

```
1. Attacker requests: "What is the IP for www.evil.net?"
2. Legitimate DNS server asks the authoritative server: ns.evil.net
3. ns.evil.net sends back ALL its zone records (zone transfer):
   www.good.net → 192.168.1.1 (attacker's address)
   www.better.net → 192.168.1.1
   www.best.net → 192.168.1.1
4. Legitimate DNS server accepts and caches the fraudulent records.
5. All users querying this DNS server are redirected to 192.168.1.1.
```

If the DNS server does not validate that responses come from authoritative sources, it accepts and propagates fraudulent entries.

**Comparison:**

| Attack | Scope | Longevity |
|---|---|---|
| DNS Poisoning (local) | Affects one device; controls all domains the user visits | Can remain undetected indefinitely |
| DNS Hijacking (external) | Affects all users of that DNS server; fewer domains controlled | Harder to execute; broader impact |

---

## 5. Distributed Denial of Service (DDoS)

A **Denial of Service (DoS) attack** bombards a target with "bogus" requests, overwhelming it so it cannot respond to legitimate users.

A **DDoS** multiplies this by using **hundreds, thousands, or millions of sources** simultaneously. The participating devices are compromised (part of a botnet) — their owners are completely unaware.

### DDoS Sources

| Source Type | Devices | Layer Targeted | Primary Target |
|---|---|---|---|
| **Network computers** | Desktop, laptop, tablet | Layer 3 | Web servers and networks |
| **Application IoT** | Baby cameras, garage door openers | Layer 7 | Cloud-based resources |
| **Operational Technology (OT)** | Automobiles, drones, robots | Layer 7 | Infrastructure (power grids) |

**Scale of modern DDoS attacks:**

| Year | Attack Size | Source |
|---|---|---|
| 2016 | 1.1 Tbps | 145,607 compromised IoT cameras and DVRs against a French web host |
| 2018 | 1.7 Tbps | Largest at that time |
| 2020 | 2.3 Tbps | Largest recorded at time of publication |
| (Theoretical) | 4 Tbps | 1 million compromised IoT devices = streaming 800,000 HD movies simultaneously |

---

## 6. Malicious Coding and Scripting Attacks

### PowerShell

PowerShell is a Microsoft task automation and configuration management framework available on Windows, macOS, and Linux (since 2016).

**Why it is a threat actor target:**
- **Full OS access**: on Windows, PowerShell accesses the OS core, kernel, user accounts, password protection, and all APIs.
- **No disk writes needed**: code can be injected from the PowerShell environment into other processes without storing anything on disk.
- **Trusted application**: most security tools flag PowerShell as trusted; its actions are rarely scrutinized.
- **Bypasses security**: commands can be configured to bypass antimalware detection.

**Dangerous PowerShell parameters used in attacks:**
- `ExecutionPolicyBypass`: runs scripts despite system restrictions.
- `WindowStyleHidden`: runs without notification to the user.
- `NoProfile`: does not load the system's custom PowerShell environment.

**Attack example**: phishing email with "URGENT!" subject and malicious Excel attachment. User opens → approves script → decrypts and executes a PowerShell script with the above parameters.

> These are not vulnerabilities — they are legitimate features of PowerShell used by administrators. The dual-use nature of PowerShell is precisely what makes it valuable to attackers.

### Visual Basic for Applications (VBA) / Macros

**VBA** automates complex, multi-step tasks in Microsoft Office applications (Word, Excel, PowerPoint) and is stored within documents (`.docx`, `.xlsx`).

**Macro malware risk**: 98% of all Office-targeted threats involve macro-based malware.

**Microsoft's macro security layers:**
- **Protected View**: read-only mode for files from Internet/unsafe locations/email attachments; macros cannot run.
- **Trusted Documents**: files the user has designated as safe; can open active content without warning.
- **Trusted Location**: files from user-designated trusted folders open in standard mode.

> **Best practice**: disable all macro support unless a documented business requirement exists. If macros are required, allow only **digitally signed macros from trusted publishers**. Disable Trusted Documents and Trusted Locations to prevent bypass.

### Python

Python is a widely used programming language (multi-platform, object-oriented, concise syntax).

**Security best practices for Python code:**
- Use the latest Python version.
- Stay current on known Python vulnerabilities.
- Be careful with string formatting (format string vulnerabilities).
- Download only vetted/official Python libraries.

### Bash

**Bash** is the command language interpreter ("shell") for Linux/UNIX. Bash scripting runs interpreted scripts without pre-compilation.

**Historical vulnerability**: a Bash vulnerability allowed attackers to remotely attach a malicious executable file to a variable that was executed when Bash was invoked — simply by sending a crafted environment variable.

---

## 7. Network Assessment and Defense Tools

### Network Reconnaissance and Discovery Tools

| Tool (Windows/Linux) | Description | Key Parameters |
|---|---|---|
| `tracert` / `traceroute` | Shows the path a packet takes from source to destination | `-d`: display numeric addresses only; `-h hops`: max hop count |
| `nslookup` / `dig` | DNS diagnostic utility for looking up hostnames and IP addresses | `host`: look up using default server; `host [server]`: use specified server |
| `ipconfig` / `ifconfig` | Displays IP address, network mask, and gateway for all adapters | `-all`: detailed info; `-release`: terminates DHCP lease; `-displaydns`: shows DNS resolver cache |

> These tools are standard OS utilities — available on every Windows and Linux system. Pen testers and attackers alike use them during reconnaissance.

---

## Deep Dive: Why Layer 2 Is the Most Dangerous Attack Surface

The OSI model's **compartmentalization** — each layer functioning independently — is both its greatest engineering strength and its critical security weakness.

When a security system is designed, it typically focuses on **higher layers**: firewalls at Layer 3-4, TLS at Layer 5-7, application-level authentication at Layer 7. But Layer 2 attacks **undercut all of these defenses at once**.

Consider ARP poisoning: once the threat actor has redirected ARP traffic, they sit between two endpoints. TLS does not help if the attacker has also sent a fake certificate (which they can do in the same attack). Firewall rules are irrelevant because the traffic is arriving from an apparently legitimate MAC address. Application-level logging sees only "legitimate" users.

This is the **depth-first vs. breadth-first** principle of attack: rather than attacking each defense layer individually (breadth-first), Layer 2 attacks descend *below* all the defenses and undermine them simultaneously (depth-first).

**Defense implication**: Network segmentation (VLANs), **Dynamic ARP Inspection (DAI)**, **Port Security** (limiting MAC addresses per switch port), **DHCP Snooping** (preventing fake DHCP responses), and **802.1X network access control** are the primary Layer 2 defenses.

---

## Key Takeaways & Next Steps

1. **Every IoT device is a potential network entry point** — "not interesting to hack" is never a valid security assumption.
2. **ARP has no authentication** — it is inherently vulnerable; Dynamic ARP Inspection is the primary mitigation.
3. **DNS is critical infrastructure** — poisoning it affects all users; DNSSEC (DNS Security Extensions) is the mitigation.
4. **DDoS attacks grow exponentially** — the scale of attack far exceeds what any single organization can absorb without upstream filtering (ISP-level scrubbing, CDN protection).
5. **PowerShell and VBA macros** are legitimate tools weaponized by attackers; disable what is not needed and enforce signing for what remains.
6. **Layer 2 attacks undermine all higher-layer security** — network segmentation and Dynamic ARP Inspection are essential baseline controls.

---

## Graph View Links

**Previous**: [[Module 6 - Basic Cryptography]]  
**Next**: —  
**Hub**: [[CS451 - Hub]]
