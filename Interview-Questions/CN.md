# 🌐 40 Most Important Computer Networks Interview Questions

> **Target Audience:** Freshers to Experienced Engineers  
> **Topics Covered:** OSI Model, TCP/IP, Protocols, Routing, DNS, HTTP, Security, Subnetting & More  
> **Interview Level:** SDE / Network Engineer / Backend Developer

---

## Table of Contents

| # | Question |
|---|----------|
| 1 | [What is a Computer Network?](#q1) |
| 2 | [What is the OSI Model?](#q2) |
| 3 | [What is the TCP/IP Model?](#q3) |
| 4 | [OSI vs TCP/IP Model](#q4) |
| 5 | [What is an IP Address? IPv4 vs IPv6](#q5) |
| 6 | [What is Subnetting and CIDR?](#q6) |
| 7 | [What is a MAC Address?](#q7) |
| 8 | [What is the difference between Hub, Switch, and Router?](#q8) |
| 9 | [What is TCP vs UDP?](#q9) |
| 10 | [What is the TCP Three-Way Handshake?](#q10) |
| 11 | [What is TCP Four-Way Termination?](#q11) |
| 12 | [What is DNS and how does it work?](#q12) |
| 13 | [What is DHCP?](#q13) |
| 14 | [What is ARP (Address Resolution Protocol)?](#q14) |
| 15 | [What is NAT (Network Address Translation)?](#q15) |
| 16 | [What is HTTP vs HTTPS?](#q16) |
| 17 | [What is HTTP/1.1 vs HTTP/2 vs HTTP/3?](#q17) |
| 18 | [What are HTTP Methods?](#q18) |
| 19 | [What are HTTP Status Codes?](#q19) |
| 20 | [What is a Cookie vs Session vs Token?](#q20) |
| 21 | [What is a Firewall?](#q21) |
| 22 | [What is a VPN?](#q22) |
| 23 | [What is a Proxy Server vs Reverse Proxy?](#q23) |
| 24 | [What is Load Balancing?](#q24) |
| 25 | [What is Routing? Static vs Dynamic Routing](#q25) |
| 26 | [What is BGP (Border Gateway Protocol)?](#q26) |
| 27 | [What is OSPF?](#q27) |
| 28 | [What is a VLAN?](#q28) |
| 29 | [What is the difference between TCP Congestion Control algorithms?](#q29) |
| 30 | [What is a Socket?](#q30) |
| 31 | [What is SSL/TLS and how does the TLS Handshake work?](#q31) |
| 32 | [What is a CDN (Content Delivery Network)?](#q32) |
| 33 | [What is ICMP and how does `ping` work?](#q33) |
| 34 | [What is the difference between unicast, broadcast, and multicast?](#q34) |
| 35 | [What is Flow Control vs Congestion Control?](#q35) |
| 36 | [What is a Sliding Window Protocol?](#q36) |
| 37 | [What is Network Topology?](#q37) |
| 38 | [What is SMTP, POP3, and IMAP?](#q38) |
| 39 | [What is a WebSocket?](#q39) |
| 40 | [What is Network Security — Common Attacks & Defenses?](#q40) |

---

<a name="q1"></a>
## Q1. What is a Computer Network?

**Answer:**

A **computer network** is a collection of interconnected devices (computers, servers, routers, switches, etc.) that communicate with each other to share resources, data, and services.

### Key Components

```
┌──────────────────────────────────────────────────────────┐
│                   Computer Network                       │
│                                                          │
│  [PC] ──── [Switch] ──── [Router] ──── [Internet]        │
│  [PC] ────┘             │                                │
│  [Server] ──────────────┘                                │
└──────────────────────────────────────────────────────────┘
```

### Types of Networks

| Type | Full Form | Range | Example |
|------|-----------|-------|---------|
| PAN | Personal Area Network | ~10 m | Bluetooth devices |
| LAN | Local Area Network | Building / Campus | Office network |
| MAN | Metropolitan Area Network | City | City-wide ISP |
| WAN | Wide Area Network | Country / Globe | The Internet |

### Network Classification by Topology
- **Bus, Star, Ring, Mesh, Hybrid** (covered in Q37)

### Goals of Networking
- **Resource sharing** — printers, storage, databases
- **Communication** — email, messaging, VoIP
- **Reliability** — data redundancy across nodes
- **Scalability** — add nodes without redesign

---

<a name="q2"></a>
## Q2. What is the OSI Model?

**Answer:**

The **OSI (Open Systems Interconnection)** model is a conceptual framework that standardizes network communication into **7 layers**. Each layer serves the layer above it and is served by the layer below it.

```
┌─────┬───────────────────┬────────────────────────────────────┬──────────────────────┐
│ No. │ Layer             │ Function                           │ Protocols/Examples   │
├─────┼───────────────────┼────────────────────────────────────┼──────────────────────┤
│  7  │ Application       │ User interface, network services   │ HTTP, FTP, SMTP, DNS │
│  6  │ Presentation      │ Data format, encryption, compress  │ SSL/TLS, JPEG, ASCII │
│  5  │ Session           │ Establish/manage/terminate sessions│ NetBIOS, RPC         │
│  4  │ Transport         │ End-to-end delivery, reliability   │ TCP, UDP             │
│  3  │ Network           │ Logical addressing, routing        │ IP, ICMP, OSPF, BGP  │
│  2  │ Data Link         │ Physical addressing, framing       │ Ethernet, MAC, ARP   │
│  1  │ Physical          │ Bits over medium                   │ Cables, Wi-Fi, Hubs  │
└─────┴───────────────────┴────────────────────────────────────┴──────────────────────┘
```

### Mnemonic
> **A**ll **P**eople **S**eem **T**o **N**eed **D**ata **P**rocessing  
> (Application → Physical, top to bottom)

### Data Unit at Each Layer

```
Application  →  Data
Transport    →  Segment
Network      →  Packet
Data Link    →  Frame
Physical     →  Bits
```

### How a Packet Travels (Sender Side)
```
App Layer data
    ↓ + Transport header = Segment
    ↓ + Network header   = Packet
    ↓ + Data Link header = Frame
    ↓ + Physical bits    → transmitted
```
Receiver side performs the reverse — **de-encapsulation** at each layer.

---

<a name="q3"></a>
## Q3. What is the TCP/IP Model?

**Answer:**

The **TCP/IP model** (also called the Internet Model) is the practical protocol suite used by the modern Internet. It has **4 layers** and was developed before OSI.

```
┌────────────────────┬──────────────────────────────────┬──────────────────────┐
│ TCP/IP Layer       │ Maps to OSI Layers               │ Protocols            │
├────────────────────┼──────────────────────────────────┼──────────────────────┤
│ Application        │ OSI 5 + 6 + 7                    │ HTTP, FTP, DNS, SMTP │
│ Transport          │ OSI 4                            │ TCP, UDP             │
│ Internet           │ OSI 3                            │ IP, ICMP, ARP        │
│ Network Access     │ OSI 1 + 2                        │ Ethernet, Wi-Fi      │
└────────────────────┴──────────────────────────────────┴──────────────────────┘
```

### Data Flow in TCP/IP
```
[Browser] → HTTP Request
              ↓ TCP adds port numbers (Segment)
              ↓ IP adds source/dest IP (Packet)
              ↓ Ethernet adds MAC addresses (Frame)
              ↓ Physical bits sent over wire/air
```

---

<a name="q4"></a>
## Q4. OSI vs TCP/IP Model

**Answer:**

```
OSI Model (7 Layers)        TCP/IP Model (4 Layers)
─────────────────────       ─────────────────────────
7. Application  ┐
6. Presentation ├──────────► Application
5. Session      ┘
4. Transport    ───────────► Transport
3. Network      ───────────► Internet
2. Data Link    ┐
1. Physical     ├──────────► Network Access
                ┘
```

| Feature | OSI Model | TCP/IP Model |
|---------|-----------|--------------|
| Layers | 7 | 4 |
| Developed by | ISO (1984) | DARPA (1970s) |
| Usage | Conceptual / reference | Practical / deployed |
| Protocol independence | Yes | No (tied to TCP/IP) |
| Transport layer | TCP, UDP, SCTP | TCP, UDP |
| Reliability | Layer 4 (Transport) | Layer 4 (Transport) |

> **Interview Tip:** OSI is the **reference model** used for teaching and troubleshooting. TCP/IP is what **actually runs the Internet**.

---

<a name="q5"></a>
## Q5. What is an IP Address? IPv4 vs IPv6

**Answer:**

An **IP (Internet Protocol) address** is a unique numerical label assigned to every device on a network, used for identification and routing.

### IPv4

- **32-bit** address → 2³² ≈ 4.3 billion addresses
- Written as 4 octets in dotted-decimal: `192.168.1.1`
- Divided into **Network** + **Host** portions

```
IP: 192  .  168  .   1  .   1
     ↑         ↑              ↑
  Network    Network        Host
```

### IPv6

- **128-bit** address → 2¹²⁸ ≈ 3.4 × 10³⁸ addresses
- Written as 8 groups of 4 hex digits: `2001:0db8:85a3:0000:0000:8a2e:0370:7334`
- Leading zeros and consecutive zero groups (`::`) can be compressed: `2001:db8:85a3::8a2e:370:7334`

### IPv4 vs IPv6

| Feature | IPv4 | IPv6 |
|---------|------|------|
| Size | 32-bit | 128-bit |
| Format | Dotted decimal | Colon-hex |
| Addresses | ~4.3 billion | ~340 undecillion |
| Header size | 20–60 bytes | Fixed 40 bytes |
| NAT needed? | Yes (address shortage) | No |
| Security | Optional (IPSec) | Built-in IPSec |
| Broadcast | Yes | No (uses multicast) |

### Special IPv4 Ranges

```
127.0.0.1          → Loopback (localhost)
192.168.x.x        → Private (Home/LAN)
10.x.x.x           → Private (Enterprise)
172.16–31.x.x      → Private (Cloud)
0.0.0.0            → Any local address
255.255.255.255    → Broadcast
```

---

<a name="q6"></a>
## Q6. What is Subnetting and CIDR?

**Answer:**

**Subnetting** is the practice of dividing a large IP network into smaller, manageable sub-networks (subnets). It improves security, performance, and address utilization.

**CIDR (Classless Inter-Domain Routing)** uses a prefix notation `IP/prefix_length` to define the subnet mask.

### Subnet Mask

The subnet mask separates the **network** portion from the **host** portion:

```
IP:          192.168.1.100  →  11000000.10101000.00000001.01100100
Subnet Mask: 255.255.255.0  →  11111111.11111111.11111111.00000000
                                └────── Network ──────────┘└─Host─┘
CIDR:        192.168.1.0/24
```

### CIDR Quick Reference

| CIDR | Subnet Mask | Hosts | Usage |
|------|-------------|-------|-------|
| /8 | 255.0.0.0 | 16,777,214 | Class A |
| /16 | 255.255.0.0 | 65,534 | Class B |
| /24 | 255.255.255.0 | 254 | Class C / Home |
| /25 | 255.255.255.128 | 126 | Half subnet |
| /30 | 255.255.255.252 | 2 | Point-to-point |
| /32 | 255.255.255.255 | 1 | Single host |

### Subnetting Example

Divide `192.168.1.0/24` into 4 equal subnets:

```
/24 split into /26 (borrow 2 bits → 2² = 4 subnets):

Subnet 0: 192.168.1.0/26    → hosts: .1 – .62,   broadcast: .63
Subnet 1: 192.168.1.64/26   → hosts: .65 – .126,  broadcast: .127
Subnet 2: 192.168.1.128/26  → hosts: .129 – .190, broadcast: .191
Subnet 3: 192.168.1.192/26  → hosts: .193 – .254, broadcast: .255
```

> **Formula:** Usable hosts per subnet = 2^(host bits) − 2  
> (subtract network address and broadcast address)

---

<a name="q7"></a>
## Q7. What is a MAC Address?

**Answer:**

A **MAC (Media Access Control) address** is a **hardware address** permanently assigned to a Network Interface Card (NIC) by its manufacturer. It operates at the **Data Link Layer (OSI Layer 2)**.

```
Format: 48-bit address, written as 6 pairs of hex digits
Example: AA:BB:CC:DD:EE:FF
         └──OUI──┘└─Device─┘

OUI (Organizationally Unique Identifier) = first 3 bytes → identifies manufacturer
Device ID = last 3 bytes → unique per device
```

### MAC vs IP Address

| Feature | MAC Address | IP Address |
|---------|------------|------------|
| Layer | Data Link (Layer 2) | Network (Layer 3) |
| Assignment | Hardware (permanent) | Software (configurable) |
| Scope | Local network only | Global routing |
| Format | 48-bit hex | 32-bit (IPv4) / 128-bit (IPv6) |
| Changes? | Generally fixed | Can change (DHCP) |
| Used by | Switches | Routers |

### How MAC is Used

```
When PC-A sends data to PC-B on same LAN:
  1. PC-A knows PC-B's IP
  2. PC-A uses ARP to find PC-B's MAC address
  3. Switch uses MAC table to forward frame to PC-B's port
  4. IP is used only if traffic leaves the LAN (via router)
```

---

<a name="q8"></a>
## Q8. What is the difference between Hub, Switch, and Router?

**Answer:**

```
┌─────────────┬───────────┬────────────────────────────────┬────────────────┐
│ Device      │ OSI Layer │ Function                       │ Addressing     │
├─────────────┼───────────┼────────────────────────────────┼────────────────┤
│ Hub         │ Layer 1   │ Broadcasts to ALL ports        │ None           │
│ Switch      │ Layer 2   │ Forwards to SPECIFIC port      │ MAC Address    │
│ Router      │ Layer 3   │ Routes between networks        │ IP Address     │
└─────────────┴───────────┴────────────────────────────────┴────────────────┘
```

### Hub
- Dumb device — receives on one port, **floods** all other ports
- Creates a **collision domain** — only one device can talk at a time
- Largely obsolete

### Switch
- Smart device — maintains a **MAC Address Table**
- Learns which device is on which port
- Sends frame **only** to the destination port
- Each port is its own **collision domain**

### Router
- Connects **different networks** (e.g., LAN to Internet)
- Maintains a **routing table** (IP → next hop)
- Performs **NAT**, **firewall**, **DHCP** in home routers
- Each interface is its own **broadcast domain**

```
LAN A: 192.168.1.0/24                LAN B: 10.0.0.0/8
[PC1]─┐                               ┌─[Server]
[PC2]─┤─[Switch]──[Router]──[Switch]─┤
[PC3]─┘                               └─[DB]
          Layer 2          Layer 3
        (MAC-based)      (IP-based)
```

---

<a name="q9"></a>
## Q9. What is TCP vs UDP?

**Answer:**

**TCP (Transmission Control Protocol)** and **UDP (User Datagram Protocol)** are the two main Transport Layer protocols.

```
┌─────────────────────┬─────────────────────────┬─────────────────────────┐
│ Feature             │ TCP                     │ UDP                     │
├─────────────────────┼─────────────────────────┼─────────────────────────┤
│ Connection          │ Connection-oriented      │ Connectionless          │
│ Reliability         │ Guaranteed delivery      │ No guarantee            │
│ Ordering            │ In-order delivery        │ No ordering             │
│ Error checking      │ Yes (+ retransmission)   │ Checksum only           │
│ Flow control        │ Yes (sliding window)     │ No                      │
│ Congestion control  │ Yes                     │ No                      │
│ Speed               │ Slower (overhead)        │ Faster (low overhead)   │
│ Header size         │ 20–60 bytes              │ 8 bytes                 │
│ Use cases           │ HTTP, FTP, SSH, Email    │ DNS, Video, Gaming, VoIP│
└─────────────────────┴─────────────────────────┴─────────────────────────┘
```

### TCP Header (key fields)
```
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
┌─────────────────────────┬─────────────────────────────────────┐
│      Source Port        │       Destination Port              │
├─────────────────────────┴─────────────────────────────────────┤
│                     Sequence Number                           │
├───────────────────────────────────────────────────────────────┤
│                  Acknowledgment Number                        │
├──────┬──────────┬──────────────────────────────────────────── │
│Offset│ Reserved │ Flags (SYN, ACK, FIN, RST, PSH, URG)       │
├──────┴──────────┴──────────────────────────────────────────── │
│       Window Size       │           Checksum                  │
└─────────────────────────┴─────────────────────────────────────┘
```

### UDP Header (just 8 bytes)
```
┌─────────────────────────┬─────────────────────────────────────┐
│      Source Port        │       Destination Port              │
├─────────────────────────┼─────────────────────────────────────┤
│         Length          │           Checksum                  │
└─────────────────────────┴─────────────────────────────────────┘
```

---

<a name="q10"></a>
## Q10. What is the TCP Three-Way Handshake?

**Answer:**

The **Three-Way Handshake** is the process TCP uses to establish a reliable connection between client and server **before** data transfer begins.

```
Client                                Server
  │                                     │
  │──────── SYN (seq=x) ───────────────►│  Step 1: Client initiates
  │                                     │
  │◄─── SYN-ACK (seq=y, ack=x+1) ──────│  Step 2: Server acknowledges + sync
  │                                     │
  │──────── ACK (ack=y+1) ─────────────►│  Step 3: Client acknowledges
  │                                     │
  │════════ Data Transfer ══════════════│  Connection Established ✅
```

### Step-by-step

| Step | Segment | Flags | Meaning |
|------|---------|-------|---------|
| 1 | Client → Server | **SYN** | "I want to connect, my seq# is x" |
| 2 | Server → Client | **SYN + ACK** | "OK, my seq# is y, I got your x" |
| 3 | Client → Server | **ACK** | "Got it, let's talk" |

### Why Three Steps?
- Two-way isn't enough — both sides must synchronize their **sequence numbers** independently
- Each SYN consumes one sequence number and requires acknowledgment

> **SYN Flood Attack:** Attackers send many SYN packets without completing the handshake, exhausting server resources. Mitigated with **SYN cookies**.

---

<a name="q11"></a>
## Q11. What is TCP Four-Way Termination?

**Answer:**

TCP uses a **Four-Way Handshake** (also called Four-Way FIN) to gracefully close a connection, because both sides must independently close their half of the connection.

```
Client                                Server
  │                                     │
  │──────── FIN (seq=u) ───────────────►│  Step 1: Client done sending
  │                                     │
  │◄─────── ACK (ack=u+1) ─────────────│  Step 2: Server acknowledges
  │                                     │
  │         [Server finishes sending]   │
  │                                     │
  │◄─────── FIN (seq=v) ───────────────│  Step 3: Server done sending
  │                                     │
  │──────── ACK (ack=v+1) ─────────────►│  Step 4: Client acknowledges
  │                                     │
  │     [TIME_WAIT: 2×MSL]              │  Connection Closed ✅
```

### TIME_WAIT State
After sending the final ACK, the client waits for **2 × MSL (Maximum Segment Lifetime)** — typically 60–120 seconds — to:
- Ensure the last ACK reached the server
- Allow delayed segments to expire

### TCP States Summary
```
CLOSED → SYN_SENT → ESTABLISHED → FIN_WAIT_1 → FIN_WAIT_2
       → TIME_WAIT → CLOSED
```

---

<a name="q12"></a>
## Q12. What is DNS and how does it work?

**Answer:**

**DNS (Domain Name System)** is the Internet's distributed **phone book** — it translates human-readable domain names (`www.google.com`) into IP addresses (`142.250.182.46`) that computers use to communicate.

### DNS Resolution Process (Recursive)

```
Browser: "What is the IP of www.example.com?"

[Browser]
    │
    ▼
[Recursive Resolver]  ← Usually provided by ISP or 8.8.8.8
    │  Cache miss?
    ▼
[Root Name Server]    ← "I don't know, ask .com TLD server"
    │
    ▼
[TLD Name Server]     ← "I don't know, ask example.com's NS"
    │
    ▼
[Authoritative NS]    ← "93.184.216.34" ✅
    │
    ▼
[Recursive Resolver]  ← Caches the result (TTL)
    │
    ▼
[Browser]             ← Gets IP, connects
```

### DNS Record Types

| Record | Purpose | Example |
|--------|---------|---------|
| **A** | Domain → IPv4 | `example.com → 93.184.216.34` |
| **AAAA** | Domain → IPv6 | `example.com → 2606:2800::1` |
| **CNAME** | Alias to another domain | `www → example.com` |
| **MX** | Mail server | `example.com → mail.example.com` |
| **NS** | Authoritative nameserver | `example.com → ns1.example.com` |
| **TXT** | Arbitrary text (SPF, DKIM) | Spam protection |
| **PTR** | Reverse DNS (IP → domain) | `34.216.184.93 → example.com` |
| **SOA** | Start of Authority | Zone metadata |

### DNS uses UDP port 53 (TCP for large responses > 512 bytes)

---

<a name="q13"></a>
## Q13. What is DHCP?

**Answer:**

**DHCP (Dynamic Host Configuration Protocol)** automatically assigns IP addresses and network configuration to devices on a network, eliminating the need for manual IP configuration.

### DHCP DORA Process

```
Client                              DHCP Server
  │                                     │
  │──── DISCOVER (broadcast) ──────────►│  "I need an IP address!"
  │                                     │
  │◄─── OFFER (IP: 192.168.1.10) ──────│  "Here, take this IP"
  │                                     │
  │──── REQUEST (I'll take .10) ───────►│  "OK I accept that IP"
  │                                     │
  │◄─── ACK (confirmed) ───────────────│  "It's yours for the lease" ✅
```

### Information DHCP Provides
- IP address (e.g., `192.168.1.100`)
- Subnet mask (e.g., `255.255.255.0`)
- Default gateway (e.g., `192.168.1.1`)
- DNS servers (e.g., `8.8.8.8`)
- Lease duration (e.g., 24 hours)

### DHCP Lease Renewal
```
t = 0        → Lease granted
t = T/2      → Client sends DHCP Request to renew
t = 7T/8     → Client broadcasts if renewal failed
t = T        → Lease expires, client must get new IP
```

> **Port:** DHCP uses **UDP 67** (server) and **UDP 68** (client).

---

<a name="q14"></a>
## Q14. What is ARP (Address Resolution Protocol)?

**Answer:**

**ARP** maps a known **IP address** to an unknown **MAC address** within a local network. It operates at the boundary of Layer 2 and Layer 3.

### ARP Process

```
PC-A wants to send to 192.168.1.20 (PC-B), but doesn't know PC-B's MAC.

1. PC-A broadcasts ARP Request:
   "Who has 192.168.1.20? Tell 192.168.1.10"
   [src MAC: AA:AA] [dst MAC: FF:FF:FF:FF:FF:FF (broadcast)]

2. PC-B (192.168.1.20) replies with ARP Reply (unicast):
   "I am 192.168.1.20, my MAC is BB:BB"

3. PC-A stores in ARP cache:
   192.168.1.20 → BB:BB:BB:BB:BB:BB (TTL: ~20 minutes)
```

### ARP Table (Cache)
```bash
# Linux / Mac
$ arp -a
? (192.168.1.1) at aa:bb:cc:dd:ee:ff [ether] on eth0
? (192.168.1.5) at 11:22:33:44:55:66 [ether] on eth0
```

### Gratuitous ARP
A device sends an ARP reply without a request — used to:
- Announce its IP/MAC to update neighbors' caches
- Detect IP conflicts

### ARP Spoofing (Attack)
Attacker sends fake ARP replies to poison the ARP cache, redirecting traffic through the attacker (Man-in-the-Middle).

> **RARP (Reverse ARP):** Maps MAC → IP. Largely replaced by DHCP.

---

<a name="q15"></a>
## Q15. What is NAT (Network Address Translation)?

**Answer:**

**NAT** allows multiple devices on a private network to share a **single public IP address** when accessing the Internet. It's the primary mechanism that extended the life of IPv4.

### How NAT Works

```
Private Network                 NAT Router              Internet
192.168.1.10:5000 ─────────────► 203.0.113.5:8001 ──────────► Web Server
192.168.1.11:5000 ─────────────► 203.0.113.5:8002 ──────────► Web Server
192.168.1.12:5001 ─────────────► 203.0.113.5:8003 ──────────► Web Server

NAT Table:
┌──────────────────┬──────────────────┐
│ Private          │ Public           │
├──────────────────┼──────────────────┤
│ 192.168.1.10:5000│ 203.0.113.5:8001 │
│ 192.168.1.11:5000│ 203.0.113.5:8002 │
│ 192.168.1.12:5001│ 203.0.113.5:8003 │
└──────────────────┴──────────────────┘
```

### Types of NAT

| Type | Description |
|------|-------------|
| **Static NAT** | 1-to-1 mapping (private ↔ public) |
| **Dynamic NAT** | Pool of public IPs, assigned as needed |
| **PAT / NAPT** | Many-to-1 using port numbers (most common, home routers) |

> **PAT = Port Address Translation** — the type used in virtually all home and office routers.

---

<a name="q16"></a>
## Q16. What is HTTP vs HTTPS?

**Answer:**

**HTTP (HyperText Transfer Protocol)** is the foundation of data communication on the Web. **HTTPS** is HTTP secured with **TLS (Transport Layer Security)**.

```
HTTP:   Client ──── plaintext ────► Server      ← Anyone can read!
HTTPS:  Client ══ encrypted TLS ══► Server      ← Only endpoints can read ✅
```

| Feature | HTTP | HTTPS |
|---------|------|-------|
| Port | 80 | 443 |
| Encryption | None | TLS/SSL |
| Authentication | None | Certificate validates server |
| Data Integrity | None | Guaranteed (MAC) |
| Performance | Slightly faster | Minimal overhead (TLS 1.3) |
| SEO Impact | Penalized | Preferred by Google |

### What HTTPS Provides (CIA for security)
- **Confidentiality** — data is encrypted
- **Integrity** — data cannot be tampered in transit
- **Authentication** — server identity verified via SSL certificate

### HTTPS Request Flow
```
1. DNS resolves domain to IP
2. TCP 3-way handshake (port 443)
3. TLS handshake (negotiate cipher, exchange keys)
4. HTTP request/response over encrypted channel
5. TCP teardown
```

---

<a name="q17"></a>
## Q17. What is HTTP/1.1 vs HTTP/2 vs HTTP/3?

**Answer:**

Each HTTP version improved performance and efficiency:

```
┌──────────┬────────────┬───────────────────────────────────────────────┐
│ Version  │ Year       │ Key Features                                  │
├──────────┼────────────┼───────────────────────────────────────────────┤
│ HTTP/1.0 │ 1996       │ One request per connection                    │
│ HTTP/1.1 │ 1997       │ Persistent connections, pipelining            │
│ HTTP/2   │ 2015       │ Multiplexing, header compression, server push │
│ HTTP/3   │ 2022       │ QUIC (UDP-based), 0-RTT, no HOL blocking      │
└──────────┴────────────┴───────────────────────────────────────────────┘
```

### HTTP/1.1 Problems
```
Request 1 ──────────────────────────────────────►
                       Response 1 ◄──────────────
Request 2 ──────────────────────────────────────►  (Head-of-Line blocking)
                       Response 2 ◄──────────────
```
- **Head-of-Line (HOL) Blocking** — later requests wait for earlier ones
- 6 parallel TCP connections per origin (browser workaround)

### HTTP/2 Solution: Multiplexing
```
TCP Connection
├── Stream 1: GET /index.html   ──► Response chunks interleaved
├── Stream 2: GET /style.css    ──► Response chunks interleaved
└── Stream 3: GET /script.js    ──► Response chunks interleaved
```
- **Binary framing** (not text)
- **Header compression** (HPACK)
- **Server Push** — send resources before client requests

### HTTP/3: QUIC over UDP
- Built on **QUIC** protocol (Google) — runs over **UDP**
- **0-RTT handshake** for returning clients
- Independent streams — loss in one stream doesn't block others
- TLS 1.3 is **mandatory and built-in**

---

<a name="q18"></a>
## Q18. What are HTTP Methods?

**Answer:**

HTTP methods (also called **verbs**) define the **intended action** for a request on a resource.

| Method | Action | Idempotent | Safe | Body? |
|--------|--------|:----------:|:----:|:-----:|
| **GET** | Retrieve a resource | ✅ | ✅ | No |
| **POST** | Create a new resource | ❌ | ❌ | Yes |
| **PUT** | Replace entire resource | ✅ | ❌ | Yes |
| **PATCH** | Partial update | ❌ | ❌ | Yes |
| **DELETE** | Remove a resource | ✅ | ❌ | Optional |
| **HEAD** | Like GET, but no body | ✅ | ✅ | No |
| **OPTIONS** | Returns allowed methods | ✅ | ✅ | No |
| **CONNECT** | Tunnel (used for HTTPS proxy) | ❌ | ❌ | No |
| **TRACE** | Loop-back test (debug) | ✅ | ✅ | No |

> **Idempotent:** Calling the method multiple times produces the same result.  
> **Safe:** Does not modify server state.

### REST API Mapping
```
GET    /users          → List all users
POST   /users          → Create new user
GET    /users/42       → Get user 42
PUT    /users/42       → Replace user 42 entirely
PATCH  /users/42       → Update user 42 partially
DELETE /users/42       → Delete user 42
```

---

<a name="q19"></a>
## Q19. What are HTTP Status Codes?

**Answer:**

HTTP status codes are 3-digit numbers indicating the result of an HTTP request. They are grouped into 5 classes:

```
1xx → Informational   (request received, processing)
2xx → Success         (request completed successfully)
3xx → Redirection     (further action needed)
4xx → Client Error    (bad request from client)
5xx → Server Error    (server failed to process)
```

### Most Important Codes

| Code | Name | Meaning |
|------|------|---------|
| **200** | OK | Standard success |
| **201** | Created | Resource created (POST/PUT) |
| **204** | No Content | Success, no response body |
| **301** | Moved Permanently | URL changed forever, update bookmarks |
| **302** | Found | Temporary redirect |
| **304** | Not Modified | Use cached version |
| **400** | Bad Request | Malformed request syntax |
| **401** | Unauthorized | Authentication required |
| **403** | Forbidden | Authenticated but no permission |
| **404** | Not Found | Resource doesn't exist |
| **405** | Method Not Allowed | HTTP method not supported |
| **408** | Request Timeout | Client too slow |
| **409** | Conflict | State conflict (duplicate entry) |
| **422** | Unprocessable Entity | Validation error |
| **429** | Too Many Requests | Rate limit exceeded |
| **500** | Internal Server Error | Generic server error |
| **502** | Bad Gateway | Upstream server error |
| **503** | Service Unavailable | Server overloaded/down |
| **504** | Gateway Timeout | Upstream server timeout |

---

<a name="q20"></a>
## Q20. What is a Cookie vs Session vs Token?

**Answer:**

HTTP is **stateless** — each request is independent. Cookies, sessions, and tokens are mechanisms to maintain **state** across requests.

### Cookie
- Small key-value data stored in the **browser**
- Sent automatically with every HTTP request to the domain
- Set by server via `Set-Cookie` header

```
Server → Set-Cookie: user_id=42; HttpOnly; Secure; SameSite=Strict; Max-Age=3600
Browser → stores cookie
Browser → next request includes: Cookie: user_id=42
```

### Session
- Server stores the **session data** (user state)
- Browser stores only a **session ID** (cookie)
- More secure — sensitive data stays on server

```
Login:
  Browser → POST /login (credentials)
  Server  → creates session, stores in DB/memory
  Server  → Set-Cookie: session_id=abc123
  Browser → stores session_id cookie

Next Request:
  Browser → GET /dashboard (Cookie: session_id=abc123)
  Server  → looks up session_id → retrieves user state
```

### JWT Token (JSON Web Token)
- **Stateless** — all data encoded in the token itself
- Signed (HMAC/RSA) — server doesn't need to store anything
- Structure: `header.payload.signature`

```
eyJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoiYWxpY2UifQ.SIGNATURE
└──── Header ───────┘└────── Payload ─────────┘└── Sig ─┘
```

### Comparison

| Feature | Cookie | Session | JWT |
|---------|--------|---------|-----|
| Storage | Browser | Server + Browser ID | Browser (header/localStorage) |
| Stateless | No | No | ✅ Yes |
| Scalability | Medium | Hard (sticky sessions) | High |
| Revocation | Easy | Easy | Hard (need blacklist) |

---

<a name="q21"></a>
## Q21. What is a Firewall?

**Answer:**

A **firewall** is a network security device (hardware or software) that monitors and controls incoming/outgoing network traffic based on predetermined **security rules**.

```
Internet ──── [Firewall] ──── Internal Network
               Rules:
               ALLOW TCP 443 inbound
               ALLOW TCP 80  inbound
               DENY  all     inbound (default)
               ALLOW all     outbound
```

### Types of Firewalls

| Type | How It Works | Inspection Level |
|------|-------------|-----------------|
| **Packet Filter** | Checks IP/port headers | Layer 3/4 |
| **Stateful** | Tracks connection state | Layer 3/4 + state |
| **Application (Layer 7)** | Inspects payload/content | Layer 7 |
| **Next-Gen (NGFW)** | Deep packet inspection + IPS + App ID | All layers |

### Firewall Rules (ACL Example)
```
Rule 1: ALLOW  src=any      dst=10.0.0.5  port=443 proto=TCP
Rule 2: ALLOW  src=any      dst=10.0.0.5  port=80  proto=TCP
Rule 3: DENY   src=any      dst=any       port=any proto=any  ← Default deny
```

### DMZ (Demilitarized Zone)
```
Internet → [Outer Firewall] → [DMZ: Web/Mail Servers] → [Inner Firewall] → [Internal DB/Apps]
```
Servers in the DMZ are exposed to Internet but isolated from internal networks.

---

<a name="q22"></a>
## Q22. What is a VPN?

**Answer:**

A **VPN (Virtual Private Network)** creates an **encrypted tunnel** over the public Internet, allowing secure communication as if devices were on the same private network.

```
[Home PC] ══════ Encrypted Tunnel ════════ [VPN Server] ──── [Company Network]
            (over untrusted Internet)
```

### How VPN Works
1. Client authenticates to VPN server
2. An **encrypted tunnel** is established (IPSec, OpenVPN, WireGuard)
3. All traffic is routed through the tunnel
4. VPN server forwards traffic to the destination

### VPN Protocols

| Protocol | Security | Speed | Port |
|----------|----------|-------|------|
| **IPSec** | High | Medium | UDP 500/4500 |
| **OpenVPN** | High | Medium | UDP/TCP 1194 |
| **WireGuard** | Very High | Fast | UDP 51820 |
| **L2TP/IPSec** | Medium | Medium | UDP 1701 |
| **PPTP** | Weak (deprecated) | Fast | TCP 1723 |

### Types of VPN

| Type | Use Case |
|------|----------|
| **Remote Access VPN** | Employee connects to company from home |
| **Site-to-Site VPN** | Connect two offices over Internet |
| **Split Tunneling** | Only corporate traffic through VPN |

---

<a name="q23"></a>
## Q23. What is a Proxy Server vs Reverse Proxy?

**Answer:**

Both proxies sit between clients and servers, but they serve different purposes:

### Forward Proxy (Proxy Server)
- Sits between **client and Internet**
- Hides client's identity from servers
- Use case: Corporate filtering, caching, anonymity

```
[Client] ──► [Forward Proxy] ──► [Internet/Server]
              (hides client IP)
```

### Reverse Proxy
- Sits between **Internet and backend servers**
- Hides backend server infrastructure from clients
- Use case: Load balancing, SSL termination, caching, security

```
[Client] ──► [Reverse Proxy] ──► [Server 1]
              (hides servers)  ├─► [Server 2]
                               └─► [Server 3]
```

### Comparison

| Feature | Forward Proxy | Reverse Proxy |
|---------|--------------|---------------|
| Protects | Client | Server |
| Placed at | Client side | Server side |
| Client awareness | Client configures it | Client unaware |
| Examples | Squid, corporate proxy | Nginx, HAProxy, Cloudflare |
| Use cases | Privacy, caching, filtering | Load balancing, SSL termination |

### Popular Reverse Proxy Uses
- **Nginx** — SSL termination, static file serving, load balancing
- **Cloudflare** — DDoS protection, CDN, WAF
- **API Gateway** — rate limiting, auth, routing

---

<a name="q24"></a>
## Q24. What is Load Balancing?

**Answer:**

**Load Balancing** distributes incoming network traffic across multiple backend servers to ensure no single server becomes a bottleneck, improving availability and scalability.

```
                    ┌──► Server 1 (load: 30%)
Client ──► [LB] ───┤──► Server 2 (load: 35%)
                    └──► Server 3 (load: 35%)
```

### Load Balancing Algorithms

| Algorithm | How It Works | Best For |
|-----------|-------------|----------|
| **Round Robin** | Rotate through servers sequentially | Uniform servers |
| **Weighted Round Robin** | More requests to powerful servers | Heterogeneous servers |
| **Least Connections** | Send to server with fewest active connections | Long-lived sessions |
| **IP Hash** | Hash client IP → same server | Session persistence |
| **Random** | Pick a random server | Simple, stateless apps |
| **Resource Based** | Based on CPU/memory metrics | Dynamic workloads |

### Layer 4 vs Layer 7 Load Balancing

| Feature | Layer 4 (Transport) | Layer 7 (Application) |
|---------|--------------------|-----------------------|
| Operates on | TCP/UDP headers | HTTP headers, URL, cookies |
| Speed | Faster | Slower (deeper inspection) |
| Routing | IP:port based | Content-based |
| Use case | General TCP | HTTP, microservices |

### Health Checks
Load balancers regularly poll servers:
```
LB → GET /health HTTP/1.1
Server → 200 OK  ← Healthy, keep sending traffic
Server → timeout ← Unhealthy, remove from pool
```

---

<a name="q25"></a>
## Q25. What is Routing? Static vs Dynamic Routing

**Answer:**

**Routing** is the process of selecting the best path for network packets to travel from source to destination across interconnected networks.

### Routing Table
Every router maintains a routing table:
```
Destination      Mask              Gateway         Interface  Metric
0.0.0.0          0.0.0.0           192.168.1.1     eth0       10    ← Default route
192.168.1.0      255.255.255.0     0.0.0.0         eth0       0     ← Directly connected
10.0.0.0         255.0.0.0         192.168.1.254   eth0       20
```

### Static Routing

- Routes **manually configured** by an administrator
- Does not adapt to network changes automatically
- Suitable for small, stable networks

```
# Add a static route (Linux)
ip route add 10.0.0.0/8 via 192.168.1.1 dev eth0
```

| Pros | Cons |
|------|------|
| Simple, predictable | Manual — doesn't scale |
| Low overhead | No fault tolerance |
| No convergence time | Admin must update on changes |

### Dynamic Routing

- Routers automatically **discover and update** routes using routing protocols
- Adapts to topology changes (link failures, new links)

| Protocol | Type | Algorithm | Metric | Scale |
|----------|------|-----------|--------|-------|
| **RIP** | Distance Vector | Bellman-Ford | Hop count | Small |
| **OSPF** | Link State | Dijkstra (SPF) | Cost (bandwidth) | Large enterprise |
| **EIGRP** | Hybrid | DUAL | Bandwidth + delay | Cisco only |
| **BGP** | Path Vector | Best Path | AS path, policy | Internet |

---

<a name="q26"></a>
## Q26. What is BGP (Border Gateway Protocol)?

**Answer:**

**BGP (Border Gateway Protocol)** is the routing protocol that powers the **global Internet**. It manages how packets are routed between **Autonomous Systems (AS)** — large networks operated by ISPs, cloud providers, and large enterprises.

```
AS 64512 (ISP A)          AS 64513 (ISP B)          AS 64514 (Google)
[Router] ──── eBGP ────── [Router] ──── eBGP ────── [Router]
  │                          │
  │← iBGP →[Router] →[Router] (within same AS)
```

### Key Concepts

| Concept | Meaning |
|---------|---------|
| **AS (Autonomous System)** | A network under a single administrative policy |
| **ASN** | Unique 16 or 32-bit number identifying an AS |
| **eBGP** | BGP between different ASes |
| **iBGP** | BGP within the same AS |
| **BGP Table** | List of all known network prefixes and their paths |

### BGP Path Selection (simplified)
BGP selects the "best" path based on multiple attributes in order:
```
1. Highest LOCAL_PREF      (prefer internal policy)
2. Shortest AS_PATH        (fewest AS hops)
3. Lowest ORIGIN           (IGP > EGP > Incomplete)
4. Lowest MED              (prefer lower metric from same AS)
5. eBGP over iBGP
6. Lowest IGP metric to next hop
```

> **Fun Fact:** BGP route leaks and misconfigurations are responsible for major Internet outages. In 2019, a BGP misconfiguration at a small ISP re-routed significant portions of Internet traffic through Nigeria.

---

<a name="q27"></a>
## Q27. What is OSPF?

**Answer:**

**OSPF (Open Shortest Path First)** is a **link-state** interior gateway routing protocol used within a single Autonomous System. It uses **Dijkstra's SPF algorithm** to compute the shortest path tree.

### How OSPF Works

```
1. HELLO packets → discover neighbors
2. Exchange LSAs (Link State Advertisements) → build LSDB
3. LSDB = complete map of the network topology
4. Run Dijkstra's SPF → compute shortest paths
5. Install best routes in routing table
```

### OSPF Areas
OSPF uses a hierarchical **area** design to scale:
```
        Area 0 (Backbone)
       ┌──────────────────┐
       │  [ABR]──[ABR]    │
       └────┬──────┬──────┘
            │      │
         Area 1  Area 2
```
- **Area 0** — Backbone area, all areas must connect to it
- **ABR (Area Border Router)** — connects areas to backbone
- **ASBR** — connects OSPF domain to external routing

### OSPF Metric: Cost
```
Cost = Reference Bandwidth / Interface Bandwidth
Default Reference = 100 Mbps

FastEthernet (100 Mbps) → Cost = 1
GigabitEthernet (1 Gbps) → Cost = 1 (same! — tune reference BW)
Serial (1.544 Mbps T1)   → Cost = 64
```

---

<a name="q28"></a>
## Q28. What is a VLAN?

**Answer:**

A **VLAN (Virtual Local Area Network)** is a logical segmentation of a physical network switch into multiple isolated broadcast domains — without needing separate physical hardware.

```
Physical Switch (24 ports)
├── Ports 1–8   → VLAN 10 (HR Department)
├── Ports 9–16  → VLAN 20 (Engineering)
└── Ports 17–24 → VLAN 30 (Finance)

Traffic isolation: HR cannot directly communicate with Finance ✅
```

### Why VLANs?

| Benefit | Description |
|---------|-------------|
| **Security** | Departments isolated even on same switch |
| **Reduced broadcast** | Broadcasts contained within VLAN |
| **Flexibility** | Move users logically without rewiring |
| **Performance** | Smaller broadcast domains = less noise |

### VLAN Tagging — IEEE 802.1Q

```
Normal Ethernet Frame:   [Dst MAC][Src MAC][Type][Data]
802.1Q Tagged Frame:     [Dst MAC][Src MAC][802.1Q Tag][Type][Data]
                                            └── VLAN ID (12 bits, 1–4094)
```

### Trunk vs Access Ports

| Port Type | Carries | Used Between |
|-----------|---------|-------------|
| **Access** | Single VLAN (untagged) | Switch ↔ End device |
| **Trunk** | Multiple VLANs (tagged) | Switch ↔ Switch, Switch ↔ Router |

### Inter-VLAN Routing
VLANs are isolated — to communicate between VLANs, a **Layer 3 device** (router or Layer 3 switch) is required:
```
[VLAN 10 PC] → Switch (trunk) → Router (sub-interfaces) → Switch (trunk) → [VLAN 20 PC]
```

---

<a name="q29"></a>
## Q29. What is TCP Congestion Control?

**Answer:**

**TCP Congestion Control** prevents the network from being overwhelmed by controlling the **rate** at which a TCP sender injects data into the network.

### Key Variable: Congestion Window (cwnd)
```
Effective sending rate = min(cwnd, rwnd) / RTT
cwnd  = congestion window (sender-side limit)
rwnd  = receiver window (receiver-side limit)
```

### Phases of TCP Congestion Control

```
cwnd
 ^
 │        /
 │       /      Congestion Avoidance (+1 per RTT)
 │  ssth/
 │    /    Slow Start (doubles each RTT)
 │   /
 │  /
 └──────────────────────────► time
```

#### 1. Slow Start
- Start with `cwnd = 1 MSS`
- Double cwnd every RTT (exponential growth)
- Until cwnd reaches `ssthresh`

#### 2. Congestion Avoidance
- Increase cwnd by `1 MSS per RTT` (linear growth)
- Much more conservative than slow start

#### 3. On Loss Detection

| Event | Action |
|-------|--------|
| **Triple Duplicate ACK** | ssthresh = cwnd/2, cwnd = ssthresh (TCP Reno) |
| **Timeout** | ssthresh = cwnd/2, cwnd = 1 (restart slow start) |

### TCP Variants

| Variant | Key Behavior |
|---------|-------------|
| **TCP Tahoe** | On any loss: cwnd = 1 |
| **TCP Reno** | 3 dup ACKs: fast recovery; timeout: cwnd = 1 |
| **TCP CUBIC** | Cubic function for cwnd growth (default Linux) |
| **BBR** | Bottleneck Bandwidth and RTT (Google, latency-based) |

---

<a name="q30"></a>
## Q30. What is a Socket?

**Answer:**

A **socket** is a software endpoint for sending and receiving data across a network. It is the combination of an **IP address + port number**, uniquely identifying a communication endpoint.

```
Socket = IP Address : Port
Example: 192.168.1.10:5000

A connection is uniquely identified by a 5-tuple:
  (Protocol, Src IP, Src Port, Dst IP, Dst Port)
  e.g. (TCP, 192.168.1.10, 54321, 93.184.216.34, 443)
```

### Socket Types

| Type | Protocol | Description |
|------|----------|-------------|
| **Stream Socket** | TCP | Reliable, connection-oriented |
| **Datagram Socket** | UDP | Unreliable, connectionless |
| **Raw Socket** | IP | Direct IP access, custom protocols |

### Socket Lifecycle (TCP Server/Client)

```
SERVER                          CLIENT
socket()                        socket()
bind()                          
listen()                        connect() ──────────────────────────────►
accept() ◄──────────────────────────────────────── (3-way handshake)
                                
recv()/send() ◄────────────────────────────────────► send()/recv()

close()                         close()
```

### Well-Known Port Numbers

| Port | Protocol | Service |
|------|----------|---------|
| 20/21 | TCP | FTP (data/control) |
| 22 | TCP | SSH |
| 23 | TCP | Telnet |
| 25 | TCP | SMTP |
| 53 | UDP/TCP | DNS |
| 67/68 | UDP | DHCP |
| 80 | TCP | HTTP |
| 110 | TCP | POP3 |
| 143 | TCP | IMAP |
| 443 | TCP | HTTPS |
| 3306 | TCP | MySQL |
| 5432 | TCP | PostgreSQL |
| 6379 | TCP | Redis |
| 27017 | TCP | MongoDB |

---

<a name="q31"></a>
## Q31. What is SSL/TLS and how does the TLS Handshake work?

**Answer:**

**SSL (Secure Sockets Layer)** is the predecessor to **TLS (Transport Layer Security)**. TLS is the modern standard for encrypting data in transit. SSL is deprecated; when people say "SSL certificate," they mean TLS.

### TLS 1.2 Handshake

```
Client                                         Server
  │                                               │
  │──── ClientHello (TLS version, ciphers, random)►│
  │                                               │
  │◄─── ServerHello (chosen cipher, random) ──────│
  │◄─── Certificate (server's public key + cert) ─│
  │◄─── ServerHelloDone ──────────────────────────│
  │                                               │
  │ [Verify cert against trusted CA]              │
  │                                               │
  │──── ClientKeyExchange (pre-master secret) ────►│
  │──── ChangeCipherSpec ─────────────────────────►│
  │──── Finished (encrypted) ─────────────────────►│
  │                                               │
  │◄─── ChangeCipherSpec ──────────────────────────│
  │◄─── Finished (encrypted) ──────────────────────│
  │                                               │
  │═══════════ Encrypted Application Data ════════│
```

### TLS 1.3 Improvements
- **1-RTT handshake** (vs 2-RTT in TLS 1.2)
- **0-RTT** for session resumption
- Removed weak cipher suites (RC4, DES, 3DES)
- **Forward Secrecy** mandatory (ephemeral key exchange)

### Certificate Chain of Trust
```
Root CA (self-signed, trusted by OS/browser)
    └── Intermediate CA
            └── Server Certificate (example.com)
```

### Key Concepts

| Term | Meaning |
|------|---------|
| **Symmetric Encryption** | Same key for encrypt/decrypt (fast) — used for data |
| **Asymmetric Encryption** | Public/private key pair — used for key exchange |
| **Certificate Authority (CA)** | Trusted entity that signs certificates |
| **Forward Secrecy** | Past sessions safe even if private key is compromised |

---

<a name="q32"></a>
## Q32. What is a CDN (Content Delivery Network)?

**Answer:**

A **CDN** is a geographically distributed network of servers (called **Points of Presence / PoPs**) that cache and deliver content to users from the **nearest location**, reducing latency and load on origin servers.

```
Without CDN:
[User in Mumbai] ─────────────────────────────────► [Origin Server in US]
                           High latency ❌

With CDN:
[User in Mumbai] ──────► [CDN PoP in Mumbai] ──────► Content served fast ✅
                          (cached content)
[User in London] ──────► [CDN PoP in London] ──────► Content served fast ✅
```

### How CDN Caching Works

```
1. User requests: GET /image.jpg
2. CDN checks cache:
   ├── Cache HIT  → serve directly (fast)
   └── Cache MISS → fetch from origin, cache it, serve user
3. Cache-Control header determines TTL:
   Cache-Control: max-age=86400 (cache for 1 day)
```

### CDN Benefits

| Benefit | How |
|---------|-----|
| **Reduced latency** | Serve from nearby PoP |
| **Reduced origin load** | Most requests served from cache |
| **DDoS protection** | Absorb traffic at edge |
| **SSL termination** | TLS at edge, plain HTTP to origin |
| **Global availability** | Redundancy across regions |

### Popular CDNs
- **Cloudflare** — free tier, security focus
- **AWS CloudFront** — deep AWS integration
- **Akamai** — enterprise, oldest CDN
- **Fastly** — real-time purging, used by GitHub

---

<a name="q33"></a>
## Q33. What is ICMP and how does `ping` work?

**Answer:**

**ICMP (Internet Control Message Protocol)** is a network layer protocol used for **diagnostic and error-reporting** purposes. It is not used to transfer application data.

### How `ping` Works

```
Host A: ping 8.8.8.8

1. Host A sends: ICMP Echo Request → 8.8.8.8
   (Type=8, Code=0, Seq=1, TTL=64)

2. 8.8.8.8 replies: ICMP Echo Reply → Host A
   (Type=0, Code=0, Seq=1)

3. Host A displays round-trip time (RTT)

Output:
64 bytes from 8.8.8.8: icmp_seq=1 ttl=118 time=12.4 ms
```

### Common ICMP Message Types

| Type | Code | Meaning |
|------|------|---------|
| 0 | 0 | Echo Reply (ping response) |
| 3 | 0 | Destination Network Unreachable |
| 3 | 1 | Destination Host Unreachable |
| 3 | 3 | Destination Port Unreachable |
| 5 | 0 | Redirect (routing) |
| 8 | 0 | Echo Request (ping) |
| 11 | 0 | TTL Exceeded (used by traceroute) |

### How `traceroute` Works
```
traceroute exploits TTL:

Packet 1: TTL=1 → Router 1 decrements to 0 → sends ICMP TTL Exceeded → reveals Router 1
Packet 2: TTL=2 → Router 1 decrements to 1 → Router 2 decrements to 0 → reveals Router 2
...and so on until destination reached
```

---

<a name="q34"></a>
## Q34. What is the difference between Unicast, Broadcast, and Multicast?

**Answer:**

These describe how a packet is delivered to one or more destinations:

```
Unicast:    [Sender] ──────────────────────────────► [One Recipient]

Broadcast:  [Sender] ──────────────────────────────► [All on network]
                      ├──────────────────────────────► [Recipient A]
                      ├──────────────────────────────► [Recipient B]
                      └──────────────────────────────► [Recipient C]

Multicast:  [Sender] ──────────────────────────────► [Group Members]
                      ├──────────────────────────────► [Member A]
                      └──────────────────────────────► [Member B]
                      (C is not a member, doesn't receive)

Anycast:    [Sender] ──────────────────────────────► [Nearest of group]
```

### Comparison

| Feature | Unicast | Broadcast | Multicast | Anycast |
|---------|---------|-----------|-----------|---------|
| Recipients | One | All on subnet | Group members | Nearest one |
| Efficiency | Medium | Low (wasteful) | High | High |
| IP Range | Any | x.x.x.255 / 255.255.255.255 | 224.0.0.0/4 | Shared IP |
| Crosses routers | Yes | No | Yes (with IGMP) | Yes |
| Protocol examples | HTTP, SSH | DHCP Discover | IPTV, video conf | DNS (IPv6) |

### Multicast Group Management — IGMP
- Hosts use **IGMP (Internet Group Management Protocol)** to join/leave multicast groups
- Routers use **PIM (Protocol-Independent Multicast)** to route multicast traffic

---

<a name="q35"></a>
## Q35. What is Flow Control vs Congestion Control?

**Answer:**

Both limit the rate of data transmission, but for different reasons:

```
┌─────────────────────┬──────────────────────────┬────────────────────────────┐
│ Feature             │ Flow Control              │ Congestion Control         │
├─────────────────────┼──────────────────────────┼────────────────────────────┤
│ Purpose             │ Protect the RECEIVER      │ Protect the NETWORK        │
│ Problem solved      │ Receiver buffer overflow  │ Router/link overload       │
│ Feedback from       │ Receiver (rwnd)           │ Network (packet loss, RTT) │
│ Mechanism           │ Sliding window            │ cwnd + slow start + AIMD   │
│ Layer               │ Transport (end-to-end)    │ Transport (end-to-end)     │
└─────────────────────┴──────────────────────────┴────────────────────────────┘
```

### Flow Control — Receive Window (rwnd)
```
Receiver: "I can only handle X bytes right now"
Sender:   "OK, I'll only send X bytes before waiting for ACK"

TCP Header: Window Size field = current rwnd
If rwnd = 0 → sender stops, waits for window update
```

### Congestion Control — Combined
```
Actual send rate = min(cwnd, rwnd) / RTT
```
- **cwnd** = congestion window (network capacity estimate)
- **rwnd** = receive window (receiver buffer capacity)

---

<a name="q36"></a>
## Q36. What is a Sliding Window Protocol?

**Answer:**

The **Sliding Window Protocol** allows multiple packets to be **in-flight** (sent but unacknowledged) simultaneously, improving link utilization over simple stop-and-wait.

### Stop-and-Wait (No sliding window)
```
Sender: [Pkt 1] ──►
                    ACK ◄── (wait...)
Sender: [Pkt 2] ──►
                    ACK ◄── (wait...)
Utilization = RTT wasted waiting
```

### Sliding Window
```
Window size = 4

Sender:  [1][2][3][4] ──────────────────────────────►
                       ACK 1 ◄──
         [2][3][4][5] (window slides)
                       ACK 2 ◄──
         [3][4][5][6] (window slides again)
```

### Sender Window
```
│ Sent & ACK'd │ Sent, not ACK'd │ Can send │ Cannot send yet │
│──────────────│─────────────────│──────────│─────────────────│
              ▲                  ▲          ▲
           Last ACK        Last sent    Window end
```

### Go-Back-N vs Selective Repeat

| Feature | Go-Back-N (GBN) | Selective Repeat (SR) |
|---------|----------------|-----------------------|
| On error | Re-send from error packet | Re-send only lost packet |
| Receiver buffer | Not needed | Needs buffer (window size) |
| Efficiency | Lower (re-sends good pkts) | Higher |
| Complexity | Simple | More complex |

---

<a name="q37"></a>
## Q37. What is Network Topology?

**Answer:**

**Network topology** describes the **physical or logical arrangement** of nodes and connections in a network.

### Physical Topologies

```
BUS:     [PC]──[PC]──[PC]──[PC]──[PC]
              (shared single cable)

RING:    [PC]──[PC]
          │         │
         [PC]──[PC]

STAR:         [Switch]
            /    |    \
         [PC]   [PC]  [PC]
         (most common in LANs)

MESH:    [A]──[B]
          │ ╲╱  │
          │ ╱╲  │
         [C]──[D]
         (full mesh: every node connects to every other)

TREE:         [Core Switch]
            /              \
    [Dist Switch]      [Dist Switch]
    /     \              /     \
[Access] [Access]  [Access] [Access]
(hierarchical — enterprise standard)
```

### Comparison

| Topology | Pros | Cons | Failure Impact |
|----------|------|------|----------------|
| Bus | Simple, cheap | Collision, single point of failure | Whole network |
| Ring | Equal access | One break = network down | Whole network |
| Star | Easy to manage, isolate faults | Central switch = SPOF | One device |
| Mesh | Highly fault tolerant | Expensive, complex | Minimal |
| Tree | Scalable | Root = SPOF | Sub-tree affected |

---

<a name="q38"></a>
## Q38. What is SMTP, POP3, and IMAP?

**Answer:**

These are email protocols operating at the **Application Layer**:

```
┌──────────────────────┬──────────────────────────────────────────────────────┐
│ Protocol             │ Purpose                                              │
├──────────────────────┼──────────────────────────────────────────────────────┤
│ SMTP (Port 25/587)   │ Sending email (client → server, server → server)    │
│ POP3 (Port 110/995)  │ Retrieving email — downloads and often deletes       │
│ IMAP (Port 143/993)  │ Retrieving email — keeps on server, multi-device     │
└──────────────────────┴──────────────────────────────────────────────────────┘
```

### Email Flow

```
[Alice's Mail Client]
         │ SMTP (port 587)
         ▼
[Alice's Mail Server — smtp.alice.com]
         │ SMTP (port 25) — server to server
         ▼
[Bob's Mail Server — smtp.bob.com]
         │
[Bob's Mail Client]
         │ IMAP (port 993) or POP3 (port 995)
         ▼
    [Retrieves email]
```

### POP3 vs IMAP

| Feature | POP3 | IMAP |
|---------|------|------|
| Storage | Downloads to device, deletes from server | Stays on server |
| Multi-device | Poor (email only on one device) | Excellent (sync across devices) |
| Offline access | Yes | Limited |
| Folder sync | No | Yes |
| Port (secure) | 995 (SSL) | 993 (SSL) |
| Best for | Single device, save bandwidth | Multiple devices, modern usage |

### SMTP Security
- **STARTTLS** — upgrades plain SMTP connection to encrypted
- **SMTPS (port 465)** — SMTP over SSL/TLS
- **SPF, DKIM, DMARC** — anti-spam email authentication

---

<a name="q39"></a>
## Q39. What is a WebSocket?

**Answer:**

**WebSocket** is a communication protocol that provides **full-duplex, persistent bidirectional** communication between client and server over a **single TCP connection** — unlike HTTP, which is request-response only.

### HTTP vs WebSocket

```
HTTP (Request-Response):
Client ──── GET /data ────────────────────────────────────────────────────────► Server
Client ◄─── Response ────────────────────────────────────────────────────────── Server
            (connection closed)
Client ──── GET /data (again, poll) ─────────────────────────────────────────► Server

WebSocket (Full-Duplex):
Client ◄══════════════════════════════════════════════════════════════════════► Server
            (persistent, both sides can send anytime)
```

### WebSocket Handshake (HTTP Upgrade)

```
Client → HTTP Request:
  GET /chat HTTP/1.1
  Upgrade: websocket
  Connection: Upgrade
  Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
  Sec-WebSocket-Version: 13

Server → HTTP Response:
  HTTP/1.1 101 Switching Protocols
  Upgrade: websocket
  Connection: Upgrade
  Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=

[Now in WebSocket mode — full duplex] ✅
```

### Use Cases

| Use Case | Why WebSocket? |
|----------|---------------|
| Real-time chat | Instant message delivery both ways |
| Live sports scores | Server pushes updates |
| Online gaming | Low-latency bidirectional |
| Stock/crypto tickers | Server pushes price updates |
| Collaborative editing | All users see changes instantly |
| IoT device control | Commands + telemetry bidirectional |

### WebSocket vs SSE vs Long Polling

| Feature | Long Polling | SSE | WebSocket |
|---------|-------------|-----|-----------|
| Direction | Half (server push via repeated requests) | Server → Client only | Full duplex |
| Protocol | HTTP | HTTP | WS |
| Overhead | High | Low | Low |
| Auto-reconnect | Manual | Built-in | Manual |
| Use case | Legacy | Notifications, feeds | Real-time bidirectional |

---

<a name="q40"></a>
## Q40. What is Network Security — Common Attacks & Defenses?

**Answer:**

Network security protects the integrity, confidentiality, and availability of data and resources. Here are the most critical attacks and their defenses:

### Common Network Attacks

#### 1. Man-in-the-Middle (MitM)
```
Normal:   Client ─────────────────────────────────────── Server
MitM:     Client ─── Attacker ──── Server
                  (reads/modifies all traffic)
```
**Defense:** TLS/HTTPS, certificate pinning, HSTS

#### 2. DDoS (Distributed Denial of Service)
```
Botnet [1000s of bots] ──► Flood target with requests ──► Server overwhelmed
```
**Defense:** CDN (Cloudflare), rate limiting, IP blacklisting, anycast

#### 3. SQL Injection (via HTTP)
```
Malicious URL: GET /user?id=1 OR 1=1--
```
**Defense:** Parameterized queries, WAF, input validation

#### 4. DNS Spoofing / Cache Poisoning
```
Attacker injects fake DNS response:
  "www.bank.com → 1.2.3.4 (attacker's server)"
```
**Defense:** DNSSEC, encrypted DNS (DoH/DoT), short TTLs

#### 5. ARP Spoofing
```
Attacker sends fake ARP: "I am the gateway (00:00:00:00:00:00)"
All traffic flows through attacker
```
**Defense:** Dynamic ARP Inspection (DAI), static ARP entries

#### 6. SYN Flood
```
Attacker: SYN, SYN, SYN, SYN... (never completes handshake)
Server:   Allocates resources for each → exhausted
```
**Defense:** SYN cookies, rate limiting, firewall rules

#### 7. Packet Sniffing
```
On shared networks: attacker captures unencrypted packets
```
**Defense:** TLS everywhere, VPN, WPA3 for Wi-Fi

### Summary Defense Table

| Attack | Layer | Defense |
|--------|-------|---------|
| SYN Flood | Layer 4 | SYN cookies, rate limiting |
| DDoS | Layer 3/4/7 | CDN, WAF, rate limiting |
| MitM | Layer 6/7 | TLS, HSTS, cert pinning |
| ARP Spoofing | Layer 2 | DAI, static ARP, 802.1X |
| DNS Poisoning | Layer 7 | DNSSEC, DoH, DoT |
| Port Scanning | Layer 4 | Firewall, IDS/IPS |
| Packet Sniffing | Layer 2/3 | Encryption (TLS, VPN) |

### Key Security Protocols

| Protocol | Purpose | Port |
|----------|---------|------|
| TLS 1.3 | Encrypt data in transit | 443 |
| IPSec | Network-layer encryption | — |
| SSH | Secure remote access | 22 |
| DNSSEC | Authenticate DNS responses | 53 |
| DoH | DNS over HTTPS | 443 |
| 802.1X | Port-based network access control | — |

---

## 📌 Quick Revision Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────────┐
│                  Computer Networks — At a Glance                         │
├────────────────────────┬─────────────────────────────────────────────────┤
│ OSI Layers (7)         │ App, Presentation, Session, Transport,          │
│                        │ Network, Data Link, Physical                    │
│ TCP/IP Layers (4)      │ Application, Transport, Internet, Network Access│
│ IP addressing          │ IPv4 (32-bit), IPv6 (128-bit), CIDR notation   │
│ TCP vs UDP             │ Reliable+slow vs Fast+unreliable                │
│ 3-Way Handshake        │ SYN → SYN-ACK → ACK                            │
│ 4-Way Termination      │ FIN → ACK → FIN → ACK                          │
│ DNS                    │ Domain → IP, uses UDP 53, A/AAAA/MX/CNAME      │
│ DHCP                   │ DORA (Discover, Offer, Request, Ack)            │
│ ARP                    │ IP → MAC mapping, broadcasts on LAN             │
│ NAT / PAT              │ Private IPs share one public IP via ports       │
│ HTTP Methods           │ GET/POST/PUT/PATCH/DELETE                       │
│ HTTP Status            │ 2xx=OK, 3xx=Redirect, 4xx=Client, 5xx=Server   │
│ TLS Handshake          │ ClientHello→ServerHello→Cert→Keys→Finished      │
│ Routing                │ Static (manual) vs Dynamic (OSPF, BGP, RIP)    │
│ Congestion Control     │ Slow Start → Congestion Avoidance → AIMD       │
│ Sliding Window         │ Multiple in-flight packets, efficiency          │
│ WebSocket              │ Full-duplex, HTTP upgrade, port 80/443          │
│ VLAN                   │ Logical network segmentation on switch          │
│ CDN                    │ Geo-distributed caching, reduce latency         │
│ VPN                    │ Encrypted tunnel over public Internet           │
│ Firewall               │ Packet filter / stateful / NGFW                │
│ DDoS Defense           │ CDN, rate limiting, anycast, WAF                │
│ Common ports           │ 22=SSH, 53=DNS, 80=HTTP, 443=HTTPS, 25=SMTP   │
└────────────────────────┴─────────────────────────────────────────────────┘
```

---

> 💡 **Pro Interview Tips:**
> - For protocol questions, always mention the **port number** and **layer** it operates at
> - Explain **TCP vs UDP** tradeoff clearly — interviewers love this question
> - For system design, know when to use **WebSocket vs HTTP polling vs SSE**
> - Subnetting questions — practice calculating CIDR ranges mentally
> - Know the **OSI layer** of each attack for security questions

---

*Happy Networking & Good Luck with your Interview! 🚀*
