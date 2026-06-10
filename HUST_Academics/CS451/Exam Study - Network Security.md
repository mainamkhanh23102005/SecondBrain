# Exam Study — Network Security

**Source PDF:** NetworkSecurity.pdf — CS526 Topic 18–19 Lecture Slides  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #network-security #ARP #DNS #TCP #DDoS #firewall #iptables

---

## Quick Lookup Index

**Sections:**
1. Types of Addresses in the Internet (MAC, IP, Port, Domain)
2. Routing and Address Translation (ARP, DNS, Reverse DNS, BGP)
3. Threats in Networking (CIA threats, root causes)
4. Address Resolution Protocol (ARP) (How it works, ARP spoofing, defenses)
5. Packet Sniffing (promiscuous mode)
6. TCP Protocol and Session Hijacking (sequence numbers, 3-way handshake, prediction, blind hijacking, RST DoS)
7. Denial-of-Service (DoS) Attacks (SYN flood, Smurf, DDoS, reflection)
8. DNS Security (hierarchy, resolution, cache poisoning, pharming)
9. Cryptographic Network Protection (SSL/TLS, SSH, ISN, IPsec)
10. Firewall and Network Segregation (firewall types, packet filtering, iptables, whitelist/blacklist)
- Deep Dive: Why Unauthenticated Protocols Are the Core Problem
- Knowledge Check Q&A
- Lab Playbook (Copy-Paste)

**Key Terms:** MAC address, IP address, port, domain name, ARP, NDP, DNS, reverse DNS, BGP, promiscuous mode, packet sniffing, ngrep, telnet, ftp, cleartext, ARP spoofing, ARP poisoning, ARP cache, static ARP, DHCP certification, arpwatch, Dynamic ARP Inspection, DAI, DHCP snooping, TCP, sequence number, ISN, acknowledgment number, SYN, ACK, SYN-ACK, three-way handshake, sequence prediction, RFC 1948, blind session hijacking, session hijacking, RST, MITM, replay, DoS, DDoS, SYN flood, half-open connection, Smurf, ICMP Echo, broadcast address, botnet, reflection, pulsing zombie, amplification, DNS hierarchy, root server, TLD server, authoritative server, recursive resolver, iterative, recursive, TTL, DNS cache poisoning, transaction ID, BIND, pharming, phishing, DNSSEC, IPsec, SSL, TLS, SSH, SFTP, FTPS, firewall, personal firewall, network firewall, packet filtering, stateless, stateful, application layer firewall, proxy server, interceptor, Deep Packet Inspection, DPI, WAF, ModSecurity, iptables, ufw, firewalld, awall, INPUT, OUTPUT, FORWARD, DROP, ACCEPT, REJECT, LOG, default policy, blacklist, whitelist, default-deny, default-accept, netcat, nc, tcpdump

---

## 1. Types of Addresses in the Internet

The Internet uses **four distinct address types** at different layers of the network stack:

| Layer | Address Type | Size | Example | Purpose |
|---|---|---|---|---|
| **Network Access (Layer 2)** | MAC address | 48 or 64 bits | `00:1A:2B:3C:4D:5E` | Identifies NIC hardware; used for local delivery |
| **Network (Layer 3)** | IP address | 32 bits (IPv4) / 128 bits (IPv6) | `128.3.23.3` | Routes packets across networks |
| **Transport (Layer 4)** | IP + Port | IP + 16-bit port | `128.3.23.3:80` | Identifies specific application process on a host |
| **Application/Human** | Domain name | Variable | `www.purdue.edu` | Human-readable host identifier |

---

## 2. Routing and Address Translation

| Translation | Protocol | Direction |
|---|---|---|
| **IP address → MAC address** | ARP (IPv4) / NDP (IPv6) | Used for local delivery on same subnet |
| **IP address routing** | TCP/IP, UDP, BGP | Routes packets: Destination IP → Next Hop IP |
| **Domain name → IP address** | DNS | Translates `google.com` → `142.250.190.46` |
| **IP address → Domain name** | Reverse DNS | Translates IP → hostname (for logging/analysis) |

---

## 3. Threats in Networking

| CIA Property | Threat | Example |
|---|---|---|
| **Confidentiality** | Packet sniffing | NIC in promiscuous mode reads all packets on the segment |
| **Integrity** | Session hijacking, MITM, Replay attack | Attacker intercepts and modifies packets |
| **Availability** | Denial of Service (DoS) attacks | Flood of packets overwhelms target |
| **All** | Address translation poisoning | ARP spoofing, DNS poisoning |
| **All** | Routing attacks | Manipulation of BGP routing tables |

**Root causes (concrete security problems):**
- **ARP is not authenticated** → ARP spoofing (poisoning)
- **Network packets pass by untrusted hosts** → Packet sniffing
- **TCP state can be easy to guess** → TCP sequence prediction / hijacking
- **Open access** → Vulnerable to DoS attacks
- **DNS is not authenticated** → DNS poisoning attacks

---

## 4. Address Resolution Protocol (ARP)

### How ARP Works

ARP translates **IP addresses → Ethernet MAC addresses** (used by network drivers to send frames).

**Message types:**
- **ARP request**: "Who has IP X? Tell me your MAC."
- **ARP reply**: "I have IP X; my MAC is Y."
- **ARP announcement**: unsolicited announcement of an IP-MAC mapping.

Each host maintains an **ARP cache** (table of IP → MAC mappings). When a device needs to send a packet to a known IP:
1. Check ARP cache — if mapping exists, use it.
2. If not, broadcast ARP request.
3. Target replies; all devices on the segment cache the mapping.

### ARP Spoofing (ARP Poisoning)

**Problem**: ARP has **no authentication** — any device can claim any IP-to-MAC mapping.

**Attack:**
- Attacker sends **fake ARP replies** to victims, mapping the attacker's MAC to the victim's IP.
- Victims update their ARP caches with the fraudulent mapping.
- All traffic destined for the victim is now redirected to the attacker.

**Legitimate uses of ARP spoofing:**
- Redirecting users to a registration/captive portal before network access.
- Implementing redundancy and fault tolerance (failover).

**Defenses:**

| Defense | Description |
|---|---|
| **Static ARP tables** | Manually configure IP→MAC mappings; cannot be overwritten by ARP replies |
| **DHCP Certification** | Access control ensuring hosts only use IP addresses assigned to them; only authorized DHCP servers accessible |
| **Arpwatch** | Detection tool that sends email alerts when ARP table entries are updated |
| **Dynamic ARP Inspection (DAI)** | Switch feature that validates ARP packets against a DHCP snooping database |

---

## 5. Packet Sniffing

When a network interface card (NIC) is set to **promiscuous mode**, it reads **all packets** on the network segment — not just those addressed to it.

**Attack:**
- Eve places her NIC in promiscuous mode.
- Eve reads all unencrypted data (e.g., using `ngrep`).
- `ftp` and `telnet` transmit passwords in **cleartext** — Eve captures credentials.

**Prevention:**
- **Encryption**: IPsec (network layer), TLS (transport/application layer).
- Use SSH instead of Telnet, SFTP/FTPS instead of FTP.

---

## 6. TCP Protocol and Session Hijacking

### TCP Overview

TCP (Transmission Control Protocol) is **connection-oriented** and **preserves order**:
- **Sender**: breaks data into packets; attaches sequence numbers.
- **Receiver**: acknowledges receipt; requests retransmission of lost packets; reassembles in correct order.

### TCP Sequence Numbers

Every TCP segment carries:
- **Sequence number (32 bits)**: 
  - If SYN flag set: this is the **initial sequence number (ISN)**. Actual data starts at ISN+1.
  - If SYN clear: the accumulated sequence number of the first data byte in this segment.
- **Acknowledgment number (32 bits)**: 
  - If ACK flag set: the next sequence number the receiver expects (acknowledges all prior bytes).

### TCP Three-Way Handshake

```
Client (C)                              Server (S)
     |                                       |
     |---- SYN (seq=x) -------------------->| (Listening)
     |                                       | (Store data)
     |<--- SYN-ACK (ack=x+1, seq=y) --------| 
     |                                       |
     |---- ACK (ack=y+1, seq=x+1) --------->| (Connected)
```

After the handshake, both sides have established sequence numbers and can exchange data.

### TCP Sequence Prediction Attack

**Attack:**
1. Attacker does **not** have full control of the network (cannot intercept packets).
2. Attacker CAN inject packets with fake source IP addresses.
3. TCP sequence numbers are used to authenticate packets.
4. If attacker can **predict the ISN**, they can forge packets that appear legitimate.

**Why it works:**
- Old implementations used predictable or sequential ISNs.
- If attacker knows the initial sequence number and can estimate traffic volume, they can predict likely current sequence numbers.
- Fix: **use cryptographically random ISNs** (RFC 1948).

### Blind TCP Session Hijacking

**Scenario**: A and B have a trusted connection. Attacker E wants to impersonate B to A.

**Attack steps:**
1. E opens a connection to A → gets initial sequence number.
2. E launches **DoS attack on B** to fill B's connection queue (prevent B from responding).
3. E sends packets to A spoofed as if from B (using predicted sequence numbers).
4. A accepts E's packets as legitimate communications from B.
5. E cannot receive replies (B's IP, not E's), but can **execute commands on A**.

**Defense**: if E is outside the firewall, the attack can be blocked by the firewall.

### Risks from Session Hijacking

| Risk | Description |
|---|---|
| Inject data into unencrypted server-to-server traffic | Email exchanges, DNS zone transfers |
| Inject data into client-to-server traffic | FTP downloads, HTTP responses |
| Spoof IP addresses for preliminary firewall checks | Bypass IP-based ACLs |
| Carry out MITM attacks on weak crypto protocols | Often results in user warnings (that get ignored) |
| Denial of service | Send RST (reset) packet to close connection |

**DoS via session hijacking:**
- Attacker guesses sequence number for an existing connection.
- Sends RST packet → closes connection → results in DoS.
- Naive success probability: $\frac{1}{2^{32}}$ (for random 32-bit sequence numbers).
- **Most systems allow a large window of acceptable sequence numbers** → much higher success probability.
- Most effective against long-lived connections (e.g., **BGP** peering sessions).

---

## 7. Denial-of-Service (DoS) Attacks

### Categories of DoS Attacks

| Category | Method |
|---|---|
| **Stopping services locally** | Process killing; process crashing; filling file system; system reconfiguration |
| **Exhausting resources locally** | Spawning processes to fill process table |
| **Exhausting resources remotely** | Packet floods (Smurf, SYN flood, DDoS) |
| **Crashing services remotely** | Sending malformed packets to crash buggy services |

### SYN Flooding

**Attack:**
1. Attacker sends many TCP SYN requests with **spoofed source IP addresses**.
2. Victim server allocates resources (half-open connection state) for each request and sends SYN-ACK.
3. Spoofed source IPs never complete the handshake (no ACK comes back).
4. Half-open connections persist until timeout.
5. Old servers had **small fixed limits** on half-open connections → limit reached → legitimate requests rejected.
6. Resources exhausted → server stops accepting new connections → DoS.

**Current effectiveness**: no more effective than other channel-capacity-based attacks today (modern systems have mitigations).

### Smurf DoS Attack

**Attack mechanism:**
1. Attacker sends an **ICMP Echo Request** (ping) to the **broadcast address** of a network.
2. Source IP is **spoofed as the DoS target** (victim's IP).
3. Every host on the network generates an ICMP Echo Reply to the **victim** (spoofed source).
4. Victim is flooded by responses from the entire network.

```
Attacker --[ICMP Echo Req: Src=DoS Target, Dest=Broadcast]--> Network Gateway
                                                                      ↓
                    All hosts on network send ICMP Echo Reply to DoS Target
```

**Prevention**: Configure routers to **reject external packets destined for broadcast addresses**.

### Distributed DoS (DDoS)

A **DDoS** uses **hundreds, thousands, or millions of compromised devices** (botnet) to simultaneously flood a target.

**Categories of DDoS bots by device type:**

| Device Type | Layer Targeted | Primary Attack Target |
|---|---|---|
| Network computers (PC, laptop) | Layer 3 | Web servers and networks |
| Application IoT (cameras, garage openers) | Layer 7 | Cloud-based resources |
| Operational Technology (autos, drones, robots) | Layer 7 | Critical infrastructure |

**DDoS attack scale milestones:**

| Year | Attack Size | Source |
|---|---|---|
| 2016 | 1.1 Tbps | 145,607 compromised IoT cameras/DVRs |
| 2018 | 1.7 Tbps | Largest at the time |
| 2020 | 2.3 Tbps | Largest recorded at publication |

### Hiding DDoS Attacks

| Technique | Description |
|---|---|
| **Reflection** | Send packets with spoofed source IP (victim's IP) to large servers; responses go to victim (PING → PING response; SYN → SYN-ACK) |
| **Pulsing zombie floods** | Each zombie is active briefly, then dormant; zombies take turns attacking; makes tracing difficult |

---

## 8. DNS Security

### How DNS Works

DNS is a **distributed, hierarchical database** that translates domain names → IP addresses.

**DNS hierarchy:**
```
Root (.)
├── .com, .org, .net, .edu
│   ├── google.com
│   │   └── www.google.com
│   └── purdue.edu
│       └── cs.purdue.edu
```

**Server types:**
| Type | Description |
|---|---|
| **Root servers** | Top of the hierarchy; 13 logical root servers worldwide |
| **TLD servers** | Top-Level Domain servers; responsible for .com, .org, .net, .edu, country codes (.uk, .fr) |
| **Authoritative DNS servers** | Organization's DNS servers; authoritative source for their domain's hostname→IP mappings |
| **Local (recursive) resolver** | ISP/enterprise resolver; acts as proxy, forwards queries into hierarchy; caches results |

### DNS Resolution

**Two resolution schemes:**
- **Iterative**: resolver queries each server level separately, gets referrals.
- **Recursive**: resolver asks a server to fully resolve the name on its behalf.

**DNS Caching:**
- Responses are cached for fast repeated lookups.
- Negative results also cached (prevents flooding for misspellings).
- Each record has a **TTL (Time to Live)** field — cached records expire and are re-fetched.

### Inherent DNS Vulnerabilities

1. Users/hosts **trust the host-address mapping** provided by DNS.
2. DNS resolvers **trust responses received** after sending queries.
3. **No authentication** for DNS responses.

### DNS Cache Poisoning

**Attacker's goal**: have the resolver cache the attacker's IP address for a target domain.

**Attack:**
1. Attacker sends a query for `www.google.com` to a recursive resolver.
2. The resolver queries the authoritative server.
3. Before the real server responds, the attacker sends a **forged response** with the attacker's IP.
4. The forged response is accepted IF the **16-bit transaction ID** matches.
5. If the forged response is accepted first → cached → all subsequent users are redirected.

**Transaction ID defense:**
- The query includes a random 16-bit transaction ID.
- Attacker must guess the ID (or wait for it to be predictable).
- Early BIND DNS used **sequential IDs** — trivially predicted (CERT 1997 report).
- Fix: use **random transaction IDs**.

**Race to respond first:**
- The attacker can guess when a DNS cache entry is about to expire.
- Send many forged responses in the window between the resolver sending the query and receiving the legitimate reply.
- If the attacker's response arrives before the real server's → poisoning succeeds.

### User-Side Attack: Pharming

**Pharming** exploits DNS poisoning to redirect users from legitimate URLs to fraudulent sites:
- More dangerous than phishing: users do not need to click a suspicious link — they type the correct URL and are redirected transparently.

**Real-world examples:**
- January 2005: Panix (large New York ISP) domain hijacked to a site in Australia.
- November 2004: Google and Amazon users redirected to Med Network Inc.

---

## 9. Cryptographic Network Protection

### Solutions Above the Transport Layer

| Protocol | Protection Provided | Limitation |
|---|---|---|
| **SSL/TLS** | Protects against session hijacking and injected data | Does NOT protect against DoS via spoofed packets |
| **SSH** | Encrypted remote access | Application-specific; same DoS limitation |

### Solutions at the Network Layer

| Solution | Description | Protects Against |
|---|---|---|
| **Cryptographically random ISNs** (RFC 1948) | Makes TCP sequence numbers unpredictable | TCP sequence prediction attacks |
| **IPsec** | Cryptographic authentication and encryption at the IP layer | Session hijacking, data injection, AND DoS via session reset attacks |

> **IPsec advantage**: because it operates at the network layer, it can authenticate every IP packet — making IP spoofing and sequence prediction attacks infeasible.

---

## 10. Firewall and Network Segregation

### Types of Firewalls

**Classification by deployment form:**
| Type | Description |
|---|---|
| **Personal Firewall (Desktop)** | Software solution; installed on individual host |
| **Network Firewall (Hardware)** | Dedicated hardware device; sits between network segments |

**Classification by feature:**
| Type | Mechanism |
|---|---|
| **Packet filtering (stateless)** | Checks each packet independently; inspects IP addresses, ports, and protocol |
| **Packet filtering (stateful)** | Tracks connection state; knows whether a packet is part of an established connection |
| **Application Layer Firewall** | Inspects application-layer content; understands HTTP, FTP, DNS, etc. |

### Packet Filtering Firewall

**Characteristics:**
- Checks IP addresses and ports of incoming and outgoing packets.
- Defines rules for incoming, outgoing, and forwarded packets.
- Rule chains (lists of rules) with policies.
- Commonly implemented in routing devices (e.g., home routers).

**Famous implementation**: `iptables` (Linux)
- Many software firewalls built atop iptables: `ufw`, `firewalld`, `awall`.

### Application Layer Firewall

Can be implemented as:
- **Proxy Server**: all traffic flows through the proxy; proxy makes decisions.
- **Interceptor**: sits inline and inspects traffic.
- **Deep Packet Inspection (DPI)**: examines packet payload, not just headers.

**Web Application Firewall (WAF)**: specialized application layer firewall for HTTP/HTTPS traffic.
- Example: **Nginx/Apache with OWASP ModSecurity** — protects against XSS, SQL injection, CSRF.

### iptables Deep Dive

**Three chains:**
| Chain | Controls | Direction |
|---|---|---|
| **INPUT** | Inbound packets to the local host | → Host |
| **OUTPUT** | Outbound packets from the local host | Host → |
| **FORWARD** | Packets passing through the host (routing) | → Host → |

**Rule structure:**
```
Rule = Matching condition (selectors) + Target policy
```

**Four target policies:**
| Policy | Action |
|---|---|
| **DROP** | Silently discard the packet |
| **ACCEPT** | Allow the packet through |
| **REJECT** | Discard and send ICMP error back to sender |
| **LOG** | Log the packet (then continue to next rule) |

**Default policy**: the action taken when NO rule matches.

**Common iptables commands:**
```bash
# List all rules
iptables -nL

# List rules for INPUT chain with line numbers
iptables -nL INPUT --line-numbers

# Set default policy for INPUT chain to ACCEPT
iptables -P INPUT ACCEPT

# Append a rule: drop TCP traffic from specific IP/prefix
iptables -A INPUT -s <ip/prefix> -p tcp -j DROP

# Append a rule: allow SSH (port 22) from anywhere
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
```

**Testing with netcat:**
```bash
# Server side (listen on port)
nc -l <port>

# Client side (connect to server)
nc <ip> <port>
```

### Firewall Configuration Approaches

| Approach | Default Policy | Method |
|---|---|---|
| **Blacklist (default-accept)** | ACCEPT everything | Selectively block known bad traffic |
| **Whitelist (default-deny)** | DROP everything | Selectively allow known good traffic |

> **Whitelist is more secure** because unknown/new traffic is blocked by default. Blacklist allows new/unknown traffic by default — attackers can use novel methods to bypass.

**Blacklist example:**
```bash
iptables -P INPUT ACCEPT                        # Default: accept
iptables -A INPUT -s 192.168.1.100 -j DROP      # Block specific IP
```

**Whitelist example:**
```bash
iptables -P INPUT DROP                          # Default: drop all
iptables -A INPUT -p tcp --dport 80 -j ACCEPT   # Allow HTTP
iptables -A INPUT -p tcp --dport 443 -j ACCEPT  # Allow HTTPS
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT  # Allow responses
```

---

## Deep Dive: Why Unauthenticated Protocols Are the Core Problem

The root cause of most network attacks is that foundational Internet protocols were designed in an era when **trust was assumed** between network participants:

| Protocol | Authentication | Consequence |
|---|---|---|
| **ARP** | None | Any device can claim any IP-MAC mapping → ARP poisoning |
| **DNS** | None (in base protocol) | Any response can be injected → DNS cache poisoning |
| **TCP** | Sequence numbers only (guessable) | Sequence prediction → session hijacking |
| **ICMP** | None | Source IP easily spoofed → Smurf attacks |

**Solutions (adding authentication retroactively):**
- **DNSSEC**: cryptographically signs DNS records — validates responses come from authoritative source.
- **IPsec**: authenticates every IP packet at the network layer.
- **RFC 1948**: specifies cryptographically random TCP ISNs.
- **TLS/SSL**: adds authentication and encryption above TCP.
- **Dynamic ARP Inspection (DAI)**: validates ARP packets against DHCP binding table.

---

## Knowledge Check Q&A

**Q1**: What is ARP spoofing and why is it possible?  
**A**: ARP spoofing sends fake ARP replies mapping an attacker's MAC to a victim's IP. It is possible because ARP has no authentication — any device can claim any IP-MAC mapping, and devices will update their caches.

**Q2**: Explain how a SYN flood attack works.  
**A**: Attacker sends many SYN requests with spoofed source IPs. Server allocates half-open connection state for each but never receives the completing ACK. When the half-open connection table fills, no new legitimate connections can be established.

**Q3**: What is DNS cache poisoning and what defends against it?  
**A**: An attacker sends a forged DNS response before the legitimate server responds, causing the resolver to cache a false IP for a domain. Defense: DNSSEC (cryptographic signatures on DNS records), randomized transaction IDs, and source port randomization.

**Q4**: What is the difference between DROP and REJECT in iptables?  
**A**: DROP silently discards the packet — the sender gets no response. REJECT discards the packet AND sends an ICMP error back to the sender, informing them the connection was refused.

**Q5**: Why is a whitelist firewall policy more secure than a blacklist?  
**A**: Whitelist (default-deny) blocks all traffic unless explicitly permitted — unknown/new attack types are blocked automatically. Blacklist (default-accept) allows everything except known bad traffic — novel attacks pass through because they haven't been added to the blacklist yet.

**Q6**: How does IPsec provide stronger protection than SSL/TLS for preventing session hijacking?  
**A**: IPsec operates at the network (IP) layer and authenticates every packet — including the IP header. This prevents IP spoofing and TCP sequence prediction attacks. SSL/TLS operates above TCP and cannot protect against spoofed packets at the network layer.

---

## Lab Playbook (Copy-Paste)

> Placeholders: `<ip>` = target/source IP, `<ip/prefix>` = CIDR (e.g. `192.168.1.0/24`), `<port>` = TCP/UDP port, `<iface>` = interface (e.g. `eth0`), `<domain>` = hostname. Most commands need `sudo`/root.

### iptables — Inspect

```bash
# List all rules (numeric, no DNS lookups)
iptables -nL

# List INPUT chain rules with line numbers
iptables -nL INPUT --line-numbers

# List with packet/byte counters and verbose detail
iptables -nvL

# Flush (delete) all rules in all chains
iptables -F
```

### iptables — Default Policies

```bash
# Set default policy for a chain (applies when no rule matches)
iptables -P INPUT ACCEPT
iptables -P INPUT DROP
iptables -P OUTPUT ACCEPT
iptables -P FORWARD DROP
```

### iptables — Add / Delete Rules (INPUT / OUTPUT / FORWARD)

```bash
# Append (-A) rule: DROP all TCP from a specific IP/prefix
iptables -A INPUT -s <ip/prefix> -p tcp -j DROP

# Append: ACCEPT SSH (port 22) from anywhere
iptables -A INPUT -p tcp --dport 22 -j ACCEPT

# Append: ACCEPT HTTP/HTTPS
iptables -A INPUT -p tcp --dport 80 -j ACCEPT
iptables -A INPUT -p tcp --dport 443 -j ACCEPT

# Insert (-I) rule at top of chain (position 1)
iptables -I INPUT 1 -s <ip> -j DROP

# REJECT (send ICMP error back) instead of silent DROP
iptables -A INPUT -p tcp --dport <port> -j REJECT

# LOG matching packets (continues to next rule afterward)
iptables -A INPUT -s <ip> -j LOG --log-prefix "BLOCKED: "

# Allow already-established / related connections (stateful)
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

# Allow loopback
iptables -A INPUT -i lo -j ACCEPT

# OUTPUT chain: block outbound to an IP
iptables -A OUTPUT -d <ip> -j DROP

# FORWARD chain: allow routed traffic between subnets
iptables -A FORWARD -s <ip/prefix> -d <ip/prefix> -j ACCEPT

# Delete a rule by spec (same as -A but with -D), or by line number
iptables -D INPUT -s <ip> -j DROP
iptables -D INPUT 2
```

### iptables — Blacklist vs Whitelist

```bash
# Blacklist (default-accept): block known-bad
iptables -P INPUT ACCEPT
iptables -A INPUT -s 192.168.1.100 -j DROP

# Whitelist (default-deny, more secure): allow only known-good
iptables -P INPUT DROP
iptables -A INPUT -i lo -j ACCEPT
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT
iptables -A INPUT -p tcp --dport 80 -j ACCEPT
iptables -A INPUT -p tcp --dport 443 -j ACCEPT
```

### Testing Connectivity (netcat)

```bash
# Server side: listen on a port
nc -l <port>
nc -lvp <port>          # verbose, persistent listen

# Client side: connect to a server
nc <ip> <port>

# Quick port-open check
nc -zv <ip> <port>
```

### Packet Sniffing (tcpdump / ngrep)

```bash
# Capture on an interface (no name resolution)
tcpdump -i <iface> -n

# Capture only a specific host / port
tcpdump -i <iface> -n host <ip>
tcpdump -i <iface> -n port <port>

# Print packet payload in ASCII / hex
tcpdump -i <iface> -nA port <port>      # ASCII
tcpdump -i <iface> -nX port <port>      # hex + ASCII

# Write / read a capture file
tcpdump -i <iface> -w capture.pcap
tcpdump -r capture.pcap

# Capture cleartext creds (ftp/telnet) with ngrep
ngrep -d <iface> -q -W byline "USER|PASS" port 21
```

### ARP / DNS Tools

```bash
# View / inspect the ARP cache
arp -a
ip neigh show

# Add a STATIC ARP entry (defense against spoofing)
arp -s <ip> <mac>
ip neigh add <ip> lladdr <mac> dev <iface>

# ARP spoofing with arpspoof (dsniff) — MITM between target and gateway
echo 1 > /proc/sys/net/ipv4/ip_forward
arpspoof -i <iface> -t <target_ip> <gateway_ip>

# DNS lookups
dig <domain>
dig <domain> +short
dig @<dns_server> <domain>
nslookup <domain>

# Reverse DNS
dig -x <ip>

# Inspect a domain's records / TTL
dig <domain> ANY
host <domain>
```

---

## Textbook Review Questions (Ciampa CompTIA Security+ 7e — Module 8)

> Official end-of-module review questions, reconstructed from the textbook chapter. Answers are derived (the chapter prints no key); *(verify)* marks any less-certain answer.

**1.** Which attack intercepts communications between a web browser and the underlying OS?
- a. Interception
- b. Man-in-the-browser (MITB)
- c. DIG
- d. ARP poisoning

**Answer: b.** A man-in-the-browser attack sits between the browser and the OS/libraries to intercept and manipulate calls.

**2.** Calix was asked to protect a system from a potential attack on DNS. What are the locations he would need to protect?
- a. Web server buffer and host DNS server
- b. Reply referrer and domain buffer
- c. Web browser and browser add-on
- d. Host table and external DNS server

**Answer: d.** DNS resolution can be subverted at the local host table or at the external DNS server, so both must be protected.

**3.** What is the result of an ARP poisoning attack?
- a. The ARP cache is compromised.
- b. Users cannot reach a DNS server.
- c. MAC addresses are altered.
- d. An internal DNS must be used instead of an external DNS.

**Answer: a.** ARP poisoning injects forged IP-to-MAC mappings, corrupting (compromising) the victim's ARP cache.

**4.** Deacon has observed that the switch is broadcasting all packets to all devices. He suspects it is the result of an attack that has overflowed the switch MAC address table. Which type of attack is this?
- a. MAC spoofing attack
- b. MAC cloning attack
- c. MAC flooding attack
- d. MAC overflow attack

**Answer: c.** MAC flooding overruns the switch's MAC (CAM) table, forcing it into fail-open/broadcast (hub-like) behavior.

**5.** Tomaso is explaining to a colleague the different types of DNS attacks. Which DNS attack would only impact a single user?
- a. DNS hijack attack
- b. DNS poisoning attack
- c. DNS overflow attack
- d. DNS resource attack

**Answer: b.** Poisoning the local host table/resolver cache affects only that one machine, whereas a hijack at the DNS server affects all users. *(verify)*

**6.** Proteus has been asked to secure endpoints that can be programmed and have an IP address so that they cannot be used in a DDoS attack. What is the name for this source of DDoS attack?
- a. Network
- b. Application
- c. IoT
- d. Operational Technology

**Answer: c.** Programmable, IP-addressable endpoints are IoT devices, frequently hijacked into DDoS botnets.

**7.** Which of the following is NOT a reason that threat actors use PowerShell for attacks?
- a. It cannot be detected by antimalware running on the computer.
- b. It leaves behind no evidence on a hard drive.
- c. It can be invoked prior to system boot.
- d. Most applications flag it as a trusted application.

**Answer: a.** PowerShell activity can be detected/logged by antimalware; the false claim that it "cannot be detected" is the NOT reason.

**8.** What is the difference between a DoS and a DDoS attack?
- a. DoS attacks are faster than DDoS attacks.
- b. DoS attacks use fewer computers than DDoS attacks.
- c. DoS attacks do not use DNS servers as DDoS attacks do.
- d. DoS attacks use more memory than DDoS attacks.

**Answer: b.** A DoS originates from one (or few) machines; a DDoS is distributed across many compromised computers.

**9.** Which of the following is NOT true about VBA?
- a. It is commonly used to create macros.
- b. It is built into most Microsoft Office applications.
- c. It is included in select non-Microsoft products.
- d. It is being phased out and replaced by PowerShell.

**Answer: d.** VBA is not being replaced by PowerShell; the other three statements are true.

**10.** Which of the following is NOT a Microsoft defense against macros?
- a. Protected View
- b. Trusted documents
- c. Trusted domain
- d. Trusted location

**Answer: c.** Microsoft's macro defenses include Protected View, Trusted Documents, and Trusted Locations; "Trusted domain" is not one of them.

**11.** Theo uses the Python programming language and does not want his code to contain vulnerabilities. Which of the following best practices would Theo NOT use?
- a. Only use compiled and not interpreted Python code.
- b. Use the latest version of Python.
- c. Use caution when formatting strings.
- d. Download only vetted libraries.

**Answer: a.** "Only use compiled and not interpreted Python code" is not a real practice (Python is interpreted), so it is the one Theo would NOT use.

**12.** What is Bash?
- a. The command-language interpreter for Linux/UNIX OSs
- b. The open source scripting language that contains many vulnerabilities
- c. A substitute for SSH
- d. The underlying platform on which macOS is built

**Answer: a.** Bash (Bourne-again shell) is the command-language interpreter/shell for Linux and UNIX systems.

**13.** Gregory wants to look at the details about the path a packet takes from his Linux computer to another device. Which Linux command-line utility will he use?
- a. tracepacket
- b. trace
- c. tracert
- d. traceroute

**Answer: d.** On Linux the path-tracing utility is `traceroute` (`tracert` is the Windows equivalent).

**14.** Which utility sends custom TCP/IP packets?
- a. curl
- b. hping
- c. shape
- d. pingpacket

**Answer: b.** `hping` crafts and sends custom TCP/IP packets for testing and probing.

**15.** Which of the following is a third-party OS penetration testing tool?
- a. theHarvester
- b. scanless
- c. Nessus
- d. sn1per

**Answer: d.** sn1per is a third-party penetration-testing/automation framework. *(verify)*

**16.** Eros wants to change a configuration file on his Linux computer. He first wants to display the entire file contents. Which tool would he use?
- a. head
- b. show
- c. display
- d. cat

**Answer: d.** `cat` prints a file's entire contents (`head` shows only the top lines).

**17.** Which of the following is a tool for editing packets and then putting the packets back onto the network to observe their behavior?
- a. Tcpreplay
- b. Tcpdump
- c. Wireshark
- d. Packetdump

**Answer: a.** Tcpreplay edits captured packets and replays them onto the network for observation.

**18.** Estevan has recommended that the organization hire and deploy two security guards in the control room to limit the effect if one of the guards has been compromised. What is Estevan proposing?
- a. Dual observation protocol (DOP)
- b. Compromise mitigation assessment (CMA)
- c. Two-person integrity/control
- d. Multiplayer recognition

**Answer: c.** Requiring two people so neither can act alone is two-person integrity/control.

**19.** Which of the following sensors can detect an object that enters the sensor's field?
- a. Proximity
- b. Field detection
- c. IR verification
- d. Object recognition

**Answer: a.** A proximity sensor detects an object entering its sensing field.

**20.** Which of the following does NOT describe an area that separates threat actors from defenders?
- a. DMZ
- b. Air gap
- c. Secure area
- d. Containment space

**Answer: d.** DMZ, air gap, and secure area are real separation concepts; "containment space" is not a recognized term.

---

## Graph View Links

**Previous**: [[Module 6 - Basic Cryptography]]  
**Next**: —  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 8 - Network Security]]
