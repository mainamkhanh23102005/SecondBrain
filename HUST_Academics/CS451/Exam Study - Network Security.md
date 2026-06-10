# Exam Study — Network Security

**Source PDF:** NetworkSecurity.pdf — CS526 Topic 18–19 Lecture Slides  
**Course:** [[CS451 - Hub|CS451 – Network Security Fundamentals]]  
**Tags:** #CS451 #exam #network-security #ARP #DNS #TCP #DDoS #firewall #iptables

---

## Executive Summary

Networks are the primary attack surface of modern computing. This document covers the **Internet address system** (MAC, IP, ports, domains), the **ARP and DNS protocols and their vulnerabilities**, **TCP connection security** (sequence numbers, session hijacking), **Denial-of-Service attacks** (SYN flood, Smurf, DDoS), **cryptographic network protection** (IPsec, SSL/SSH), and **firewall and network segregation** (packet filtering, application layer firewalls, iptables). The central insight is that most foundational Internet protocols (ARP, DNS, TCP sequence numbers) were designed without authentication — making them inherently vulnerable to spoofing attacks.

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

## Key Takeaways for the Exam

1. **Four address types**: MAC (Layer 2), IP (Layer 3), IP+Port (Layer 4), Domain name (Application).
2. **ARP has no authentication** → ARP spoofing redirects all traffic to attacker; defend with static ARP or DAI.
3. **TCP SYN flood**: spoofed SYN requests exhaust half-open connection state table.
4. **Smurf attack**: ping broadcast with victim as source → amplification attack.
5. **DNS has no authentication** → cache poisoning via forged responses; defend with DNSSEC.
6. **TCP sequence prediction**: old implementations used sequential ISNs; RFC 1948 mandates random ISNs.
7. **IPsec** operates at network layer — can protect against both session hijacking AND DoS via session reset.
8. **Stateless vs. stateful packet filtering**: stateful knows connection state; stateless treats each packet independently.
9. **iptables chains**: INPUT (inbound), OUTPUT (outbound), FORWARD (routing).
10. **Whitelist > blacklist**: default-deny is more secure than default-accept.
11. **DNSSEC** adds cryptographic signatures to DNS records — but does NOT encrypt DNS (confidentiality not provided).

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

## Graph View Links

**Previous**: [[Module 6 - Basic Cryptography]]  
**Next**: —  
**Hub**: [[CS451 - Hub]]  
**Source Notes**: [[Module 8 - Network Security]]
