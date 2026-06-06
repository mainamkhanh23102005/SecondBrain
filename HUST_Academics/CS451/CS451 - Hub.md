# CS451 – Network Security Fundamentals

**Textbook:** CompTIA Security+ Guide to Network Security Fundamentals (Cengage Learning, 2022)  
**Tags:** #CS451 #security #cybersecurity

---

## Course Overview

CS451 covers the foundational principles and practical techniques of network security, aligned with the **CompTIA Security+ SY0-601** certification framework. The course moves from conceptual definitions and threat actor taxonomy through malware classification, cryptographic systems, and network-level attack vectors.

---

## Module Index

| Module | Topic | Key Concepts |
|---|---|---|
| [[Module 1 - Introduction to Information Security\|Module 1]] | Introduction to Information Security | CIA Triad, Threat Actors, Vulnerabilities, Social Engineering |
| [[Module 2 - Threat Management and Cybersecurity Resources\|Module 2]] | Threat Management & Cybersecurity Resources | Penetration Testing, Vulnerability Scanning, SIEM, SOAR |
| [[Module 3 - Threats and Attacks on Endpoints\|Module 3]] | Threats and Attacks on Endpoints | Malware taxonomy, Ransomware, Fileless viruses, XSS, SQL Injection |
| [[Module 6 - Basic Cryptography\|Module 6]] | Basic Cryptography | Hash algorithms, Symmetric, Asymmetric, Digital Signatures, Quantum |
| [[Module 8 - Network Security\|Module 8]] | Networking Threats, Assessments & Defenses | MITM, ARP Poisoning, DNS Attacks, DDoS, PowerShell/Macro attacks |
| [[Supplementary - Web Application Development\|Supp. WAD]] | Web Application Development | nginx, PHP-FPM, MySQL, HTTP mechanics, cookies, sessions, SocialNet app |
| [[Supplementary - Web Application Security\|Supp. WAS]] | Web Application Security (SocialNet Case Study) | CSRF, SQL Injection (UNION), Stored XSS, Session Hijacking, Session Fixation |

---

## Key Themes Across Modules

- **Security ∝ 1/Convenience** — every security decision has a usability cost.
- **Defense-in-depth**: no single control is sufficient; layer physical, logical, and procedural defenses.
- **Human is the weakest link**: social engineering and phishing succeed because psychology, not technology, is the attack surface.
- **Attackers are patient**: APT actors and professional criminals invest months or years in a single target.
- **Every endpoint is an entry point**: IoT, OT, and endpoint security must extend to the entire connected surface.

---

## Related Areas

- [[Module 1 - Introduction to Information Security|Threat Actor Taxonomy]] connects to [[Module 2 - Threat Management and Cybersecurity Resources|Pen Testing]] (understanding attacker mindset).
- [[Module 3 - Threats and Attacks on Endpoints|Malware]] connects to [[Module 6 - Basic Cryptography|Cryptography]] (ransomware is cryptomalware; cryptographic tools used by attackers).
- [[Module 6 - Basic Cryptography|Asymmetric cryptography]] connects to [[Module 8 - Network Security|MITM attacks]] (fake certificates used in MITM to intercept TLS).
- [[Supplementary - Web Application Development|Web app sessions/cookies]] are the exact mechanism exploited in [[Supplementary - Web Application Security|ATT-6 and ATT-7]] (session hijacking, session fixation).
- [[Module 3 - Threats and Attacks on Endpoints|XSS and SQL Injection]] theory from Module 3 is applied hands-on with concrete attack steps in the supplementary WAS module.
