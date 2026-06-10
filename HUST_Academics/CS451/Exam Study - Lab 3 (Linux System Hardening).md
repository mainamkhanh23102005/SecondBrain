# Exam Study — Lab 3: Linux System Hardening

**Source:** Practical Experience Report — Lab 3 (Ubuntu VM hardening, OpenSSH, Lynis)
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]
**Tags:** #CS451 #exam #lab #hardening #linux #ssh #lynis #ufw

---

## Quick Lookup Index

**Sections:**
1. System Hardening — Definition
2. OpenSSH Server (install / control / inspect)
3. Lynis — Auditing Tool
4. Running a Lynis Audit
5. Lynis Findings & Fixes (warnings + suggestions)
6. Readable HTML Report (lynis-report-converter)
7. Deep Dive: Why Each Hardening Step Reduces Risk

**Key Terms:** system hardening, attack surface, OpenSSH, `openssh-server`, `systemctl`, `ufw`, port 22, `ss -tuln`, Lynis, `lynis audit system`, Hardening Index, `lynis-report.dat`, CIS benchmark, `/etc/ssh/sshd_config`, `MaxAuthTries`, `/etc/login.defs`, `PASS_MAX_DAYS`, `/etc/issue` banner, BANN-7126, SSH-7408, AUTH-9286, FILE-6310, HRDN-7239, HRDN-7222, rkhunter, chkrootkit

---

## 1. System Hardening — Definition

**System hardening** — the **proactive** process of securing an IT system by **reducing its attack surface** and eliminating vulnerabilities. Done by:
- **Patching** software
- **Removing** unnecessary software/services
- **Enforcing strict access controls** to prevent unauthorized access / malware exploitation

> **Attack surface** = the sum of all points an attacker could use to enter or extract data. Hardening = shrink it.

---

## 2. OpenSSH Server

**OpenSSH** — secure remote-shell server; encrypted alternative to Telnet. Default port **TCP 22**.

**Install (chronological):**
| # | Command | Purpose |
|---|---|---|
| 1 | `sudo apt update` | Refresh package index (get latest version) |
| 2 | `sudo apt install openssh-server -y` | Install the SSH server (`-y` auto-confirms) |
| 3 | `sudo systemctl enable ssh` | Auto-start SSH on every boot |
| 4 | `sudo ufw allow ssh` | Open port 22 in UFW (Uncomplicated Firewall) |

**Control & inspect:**
| Task | Command |
|---|---|
| Start | `sudo systemctl start ssh` |
| Stop | `sudo systemctl stop ssh` |
| Restart | `sudo systemctl restart ssh` |
| Status (active/inactive/failed) | `sudo systemctl status ssh` |
| What port is SSH listening on | `ss -tuln | grep ssh` → default **TCP 22** |

**SSH client used:** built-in Windows OpenSSH client (via PowerShell): `ssh user@<vm-ip>`.

---

## 3. Lynis — Auditing Tool

**Lynis** — open-source **security auditing & hardening** tool for Unix-like OSes (Linux, macOS, BSD).

| Attribute | Detail |
|---|---|
| **Purpose** | Evaluate security posture: find vulnerabilities, misconfigurations, weak file permissions, compliance gaps (e.g. **CIS benchmarks**) |
| **Who** | Sysadmins, security pros, pentesters, IT auditors |
| **How it works** | Runs **locally on the host** (not a remote network scanner). Performs hundreds of tests: reads config files (e.g. `/etc/ssh/sshd_config`), checks package manager for outdated software, inspects kernel parameters |
| **Output** | Color-coded report of **Warnings** + **Suggestions**, plus a final **Hardening Index** score |

> **Key contrast:** traditional scanners probe from **outside** over the network; **Lynis runs from the inside** with full host access → deeper, configuration-level audit.

---

## 4. Running a Lynis Audit

```bash
sudo apt install lynis -y           # install
lynis audit system --quick          # run audit (prints report to console)
```
- Produces a console report **and** a data file `lynis-report.dat` (current dir, or `/var/log/lynis-report.dat`).
- Read the `.dat` file to enumerate all warnings/suggestions with their **codes**.

---

## 5. Lynis Findings & Fixes

| Type | Code | Finding | Note (why it matters) |
|---|---|---|---|
| Suggestion | **AUTH-9286** | Configure max password age in `/etc/login.defs` | Force password rotation → limits usefulness of a stolen credential |
| Suggestion | **SSH-7408** | Harden SSH config (`MaxAuthTries`, `AllowTcpForwarding`) | Prevents brute-force & unauthorized tunneling |
| Suggestion | **BANN-7126** | Add legal banner to `/etc/issue` | Warns unauthorized users; compliance requirement |
| Suggestion | **FILE-6310** | Place `/home` on a separate partition | Prevents one full partition from crashing the OS (DoS) |
| Suggestion | **HRDN-7239** | Install a malware scanner | e.g. `rkhunter`, `chkrootkit`, OSSEC for periodic rootkit scans |
| **Warning** | **HRDN-7222** | Restrict compiler access to root only | Stops a limited-access attacker from compiling exploit code on-box |

**Three fixes implemented in the lab:**

**Fix BANN-7126 — legal login banner:**
```bash
echo "WARNING: Authorized personnel only. All activity is monitored." | sudo tee /etc/issue
```

**Fix SSH-7408 — limit SSH auth tries (anti brute-force):**
```bash
sudo nano /etc/ssh/sshd_config
# find: #MaxAuthTries 6   → uncomment & change to:  MaxAuthTries 3
sudo systemctl restart ssh
```

**Fix AUTH-9286 — password expiration (90 days):**
```bash
sudo nano /etc/login.defs
# change: PASS_MAX_DAYS 99999   → PASS_MAX_DAYS 90
```

---

## 6. Readable HTML Report (optional)

The default `lynis-report.dat` is hard to read. Convert it to an HTML dashboard with the open-source **lynis-report-converter**:

```bash
sudo apt install git -y
git clone https://github.com/d4t4king/lynis-report-converter.git
cd lynis-report-converter
chmod +x lynis-report-converter.sh
sudo ./lynis-report-converter.sh -i /var/log/lynis-report.dat -o ~/lynis-readable-report.html
```
(Alternative: `ansi2html` to capture colored console output.)

---

## 7. Deep Dive: Why Each Step Reduces Risk

**`MaxAuthTries 3`** caps failed authentications per TCP connection. Brute-force tools rely on thousands of guesses per connection; forcing a reconnect after 3 failures multiplies attacker cost and floods logs (detectable). It doesn't stop brute force outright but raises the bar and improves detection.

**`PASS_MAX_DAYS 90`** bounds the *lifetime* of a compromised credential. If a password leaks, it becomes useless after at most 90 days — limiting the window for credential reuse/stuffing. Trade-off: too-short expiry encourages weak, incrementing passwords; 90 days is a common balance.

**Legal banner (`/etc/issue`)** is a *deterrent control* (recall the six control types from Module 1). It carries no technical barrier but establishes legal notice ("activity is monitored"), which matters for prosecution and many compliance regimes.

**Separate `/home` partition (FILE-6310)** isolates blast radius: a runaway log or malicious user filling `/home` can't exhaust the root filesystem and crash the OS — a local **availability** (DoS) protection.

**Restricting compilers to root (HRDN-7222)** denies a foothold attacker the ability to compile a privilege-escalation exploit locally ("living off the land"). Removing build tools from the attack surface is classic minimization.

**Installing a malware scanner (HRDN-7239)** adds a *detective* layer (`rkhunter`/`chkrootkit`) on top of the *preventive* hardening — defense in depth.

**Lynis as local auditor** complements external vuln scanners: external scans see open ports/services; Lynis sees *configuration* weaknesses (weak `sshd_config`, missing banner, password policy) that no network scan can detect.

---

## Lab Playbook (Copy-Paste)

```bash
# --- OpenSSH server ---
sudo apt update
sudo apt install openssh-server -y
sudo systemctl enable ssh           # start at boot
sudo systemctl start ssh
sudo systemctl status ssh           # active/inactive/failed?
sudo ufw allow ssh                  # open port 22 in firewall
ss -tuln | grep ssh                 # confirm listening on TCP 22
ssh user@<vm-ip>                    # connect from client

# --- UFW firewall basics ---
sudo ufw status
sudo ufw enable
sudo ufw allow 22/tcp
sudo ufw deny <port>

# --- Lynis audit ---
sudo apt install lynis -y
sudo lynis audit system --quick
cat /var/log/lynis-report.dat | grep -E 'warning|suggestion'

# --- Apply common hardening fixes ---
# Legal banner (BANN-7126)
echo "WARNING: Authorized personnel only. All activity is monitored." | sudo tee /etc/issue

# SSH brute-force limit (SSH-7408)
sudo nano /etc/ssh/sshd_config      # MaxAuthTries 3
sudo systemctl restart ssh

# Password expiry (AUTH-9286)
sudo nano /etc/login.defs           # PASS_MAX_DAYS 90

# Install malware scanner (HRDN-7239)
sudo apt install rkhunter chkrootkit -y
sudo rkhunter --check
```

---

## Knowledge Check Q&A

**Q1:** What is system hardening in one sentence?
**A:** Proactively securing a system by reducing its attack surface (patching, removing unneeded software, strict access controls).

**Q2:** How do you check which port SSH is listening on?
**A:** `ss -tuln | grep ssh` — default is **TCP 22**.

**Q3:** How does Lynis differ from a normal network vulnerability scanner?
**A:** Lynis runs **locally on the host** and inspects configuration files, packages, and kernel params; network scanners probe from outside. Lynis finds config-level weaknesses a remote scan can't.

**Q4:** Which `sshd_config` directive limits brute-force attempts, and to what value did the lab set it?
**A:** `MaxAuthTries`, set to `3` (from default 6).

**Q5:** What does setting `PASS_MAX_DAYS 90` achieve?
**A:** Forces password rotation every 90 days, limiting how long a stolen credential stays useful.

**Q6:** What kind of control (Module 1 taxonomy) is the `/etc/issue` legal banner?
**A:** A **deterrent** control — no technical barrier, but warns/discourages and satisfies compliance.

---

## Graph View Links

**Previous**: [[Exam Study - Lab 2 (Malware Analysis Tools)]]
**Next**: [[Exam Study - Lab 4.1 (Web Application Environment Setup)]]
**Hub**: [[CS451 - Hub]]
