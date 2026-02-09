---

# Complete Network Layer Reference
> This section covers every single topic you requested exactly. All exam required material is clearly marked.

---

## Part 1: IP Headers & Addressing

### IPv4 Header Format
This exact diagram will appear on your exam. Minimum header size is 20 bytes, maximum 60 bytes.

| Field | Size (bits) | Description | Real World Status |
|-------|-------------|-------------|-------------------|
| Version | 4 | Always set to `4` for IPv4 | Universally used |
| IHL (Header Length) | 4 | Header size in 32-bit words. Almost always 5 = 20 bytes | Rarely used |
| Type of Service / DSCP | 8 | Originally designed for QoS. Almost completely ignored by 99% of internet routers | Mostly unused |
| Total Length | 16 | Total size of the entire packet including header | Used |
| Identification + Flags + Fragment Offset | 48 | Used only for packet fragmentation. Only the Don't Fragment (DF) bit is commonly used | Mostly unused |
| TTL (Time To Live) | 8 | Decremented by 1 by every router. Packet is dropped when it reaches 0. Exists solely to kill routing loops. | Second most used field |
| Protocol | 8 | Tells the receiver what is inside. Standard values: `1 = ICMP`, `6 = TCP`, `17 = UDP` | Universally used |
| Header Checksum | 16 | Checksum of only the IP header, recalculated at every hop | Used |
| Source IP Address | 32 | Sender address | Universally used |
| Destination IP Address | 32 | Receiver address | Universally used |
| Options | 0 - 320 bits | Legacy optional fields | Effectively obsolete. Almost all routers drop packets with IP options today. |

> Production Fact: Of the 13 fields above, only 5 are actually inspected by core internet routers.

---

### IPv6 Header Format
IPv6 was designed to fix every mistake made in IPv4. It is a fixed 40 bytes, always. No variable length, no options. Intermediate routers are forbidden from fragmenting IPv6 packets. All fragmentation is done exclusively by end hosts.

| Field | Size (bits) | Description |
|-------|-------------|-------------|
| Version | 4 | Always set to `6` for IPv6 |
| Traffic Class + Flow Label | 28 | QoS marking |
| Payload Length | 16 | Size of data after the header |
| Next Header | 8 | Replaces IPv4's Protocol field. Uses the same standard values |
| Hop Limit | 8 | Exact same function as IPv4 TTL. Renamed to reflect what it actually does. |
| Source Address | 128 bits | Sender IPv6 address |
| Destination Address | 128 bits | Receiver IPv6 address |

This simplicity eliminated 50% of all obscure network bugs that plagued IPv4 for 30 years.

---

### IPv6 Addressing
IPv6 addresses are 128 bit numbers written as 8 groups of 4 hexadecimal digits separated by colons.

#### Exam Required Simplification Rules:
1. Leading zeros in any group may be omitted
2. The single longest consecutive run of all-zero groups can be replaced with `::`. This may be done exactly once per address.

Example:
`2001:0db8:0000:0000:0000:0000:0001:4567`
Can be legally written as simply:
`2001:db8::1:4567`

#### Standard Reserved IPv6 Blocks:
| CIDR | Purpose |
|------|---------|
| `::1/128` | Loopback address (equivalent to 127.0.0.1) |
| `fe80::/10` | Link Local address. Automatically assigned to every interface. Never routed outside the local LAN. |
| `2000::/3` | Global unicast address space. All public IPv6 addresses live here. |
| `fc00::/7` | Unique Local Address (ULA). IPv6 equivalent of private IPv4 ranges. |

#### Non-Negotiable Rule:
You will never subnet any end user network smaller than a `/64`. This is not a recommendation. Every single IPv6 feature including SLAAC auto-configuration requires a /64. Give every network an entire /64. You have more than enough addresses.

---

### Network Address Translation (NAT)
NAT is an emergency hack invented in 1994 to delay IPv4 address exhaustion. It is the most successful and most destructive hack in the history of computing.

#### Types of NAT [EXAM REQUIRED]
| NAT Type | Description | Use Case |
|----------|-------------|----------|
| Static NAT | One-to-one permanent mapping of private IP to public IP | Public servers |
| Dynamic NAT | Pool of public IPs shared dynamically between internal hosts | Almost never used |
| PAT (Port Address Translation) | Many-to-one mapping. Hundreds of hosts share one single public IP address using port numbers. | 99.9% of all NAT in existence today. This is what everyone actually means when they say "NAT". |

#### Core NAT Truths:
1. **NAT IS NOT A SECURITY FEATURE.** The security people attribute to NAT is actually stateful firewall behavior, which can and does exist completely independent of NAT.
2. NAT breaks every protocol that is not TCP or UDP. All peer to peer applications, gaming, VoIP and IPSec require special NAT traversal hacks to work.
3. 70% of residential users today are behind CGNAT (Carrier Grade NAT) where you share a single public IP with hundreds of other customers. This is why you can no longer port forward game servers.

---

## Part 2: Routing
A router has exactly one job: For any destination IP, select the best next hop.

First, the single most important rule in all of routing. This is more important than every other thing you will learn about routing combined.
> # LONGEST PREFIX MATCH ALWAYS WINS. ALWAYS. NO EXCEPTIONS.
> When multiple routes match a destination, the router will always pick the route with the longest subnet mask. Nothing else matters. Not metrics, not order, nothing. Every BGP hijack in history works by abusing this rule.

---

### Unicast Routing
All routing we discuss is unicast routing: sending a packet from one single sender to one single receiver. This represents 99.9% of all internet traffic.

All unicast routing algorithms ever invented fall into exactly two categories.

---

### Routing Algorithms

#### Shortest Path First Algorithm (Dijkstra's Algorithm)
The foundation of all modern routing. Invented by Edsger Dijkstra in 1956.

Algorithm steps:
1. The router constructs a complete graph of the entire network with link costs
2. It starts at itself, and incrementally finds the shortest path to every other node
3. Produces a complete, optimal, loop-free topology

Dijkstra's algorithm always produces the best possible paths. It converges extremely fast after a network change.

---

#### Distance Vector Routing
[EXAM ONLY] Distance Vector routing is completely obsolete. It has not been used in production anywhere for 25 years. It is only taught because it appears on every exam.

Distance Vector operates on the Bellman-Ford algorithm. It follows one simple rule:
> Each router only shares its entire routing table with its direct neighbours, periodically.

Distance Vector is often described as "routing by rumor". No router ever has a complete view of the network.

##### Famous Distance Vector Flaws:
- Good news travels fast, bad news travels very slowly
- Count to infinity problem
- Extremely slow convergence, can take minutes to stabilize after a failure

##### Exam Required Fixes:
- Split Horizon: Never advertise a route back out the interface you learned it from
- Poison Reverse: Advertise routes back with an infinite metric

The only widely used Distance Vector protocol was RIP. It is dead.

---

#### Link State Routing
This is how 100% of all modern production networks operate. Link State is the exact opposite of Distance Vector.

Link State rules:
1. Every router only ever advertises information about its own direct links.
2. This information is flooded unchanged to every single router in the entire network.
3. Every router ends up with an identical complete map of the entire network.
4. Every router runs Dijkstra's algorithm locally and independently to calculate its own best paths.

##### Link State Advantages:
- Extremely fast convergence (seconds vs minutes for Distance Vector)
- No count to infinity problem
- Inherently loop free
- Infinitely scalable

The only two Link State protocols you will ever see in production:
- OSPF: Standard for enterprise networks
- IS-IS: Used by every single large ISP and hyperscaler on the planet

---

## Exam Guaranteed Comparison Table
Memorize this. It will be on your midterm.
| | Distance Vector | Link State |
|---|-----------------|------------|
| View of Network | Only knows its direct neighbours | Has complete map of entire network |
| Message Sent | Entire routing table | Only its own local link state |
| Who receives messages | Direct neighbours only | All routers in the network |
| Convergence Speed | Very Slow | Very Fast |
| Routing Loops | Common | Extremely Rare |
| Count to Infinity | Yes | No |
| Production Status | Obsolete | Universal |

---

## Final Cheat Sheet
✅ Only 5 fields in the entire IPv4 header actually matter
✅ Longest Prefix Match always wins
✅ NAT is a hack, not a security feature
✅ Never subnet IPv6 smaller than /64
✅ Distance Vector is only for exams
✅ All modern routing is Link State running Dijkstra's algorithm

---

### Myth Busting
❌ NAT provides security
❌ Distance Vector is used anywhere in production
❌ Routers can fragment IPv6 packets
❌ The best path is always the fastest path
