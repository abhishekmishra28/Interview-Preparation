# 📡 Computer Networks - Congestion Control & Network Layer Guide

## 🚦 TRANSPORT LAYER: CONGESTION CONTROL

### What is Congestion?
**Congestion** occurs when too many packets are present in a part of the network, causing packet loss, increased delay, and reduced throughput. It's like traffic jam in a network.

### Causes of Congestion:
1. **Insufficient Buffer Space** at routers
2. **Slow Processors** in routers
3. **Low Bandwidth** links
4. **Bursty Traffic** patterns
5. **Multiple Input Streams** converging

### Congestion vs Flow Control
| Aspect | Flow Control | Congestion Control |
|--------|--------------|-------------------|
| **Scope** | End-to-end (sender-receiver) | Network-wide |
| **Goal** | Prevent receiver overflow | Prevent network overload |
| **Mechanism** | Receiver window size | Reduce sending rate |
| **Responsibility** | Transport layer | Transport + Network layers |

---

## 🛠️ Network-Assisted Congestion Control

### Approaches to Congestion Control

#### 1. **End-to-End Congestion Control**
- Network provides **no explicit feedback**
- End systems infer congestion from:
  - Packet loss
  - Increased delay
- **Example**: TCP congestion control

#### 2. **Network-Assisted Congestion Control**
- Routers provide **explicit feedback** to senders
- Two approaches:
  - **Direct Feedback**: Router sends choke packets
  - **Indirect Feedback**: Mark packets (ECN)

### Explicit Congestion Notification (ECN)
- **Mechanism**: Routers mark packets instead of dropping them
- **TCP/IP Implementation**:
  - **ECE (ECN-Echo)**: Receiver informs sender of congestion
  - **CWR (Congestion Window Reduced)**: Sender reduces rate

**ECN Bits in IP Header:**
```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
┌─────────────────────────────────────────────────────────────────┐
│Version│  IHL  │Type of Service│          Total Length           │
├─────────────────────────────────────────────────────────────────┤
│         Identification        │Flags│      Fragment Offset      │
├─────────────────────────────────────────────────────────────────┤
│  Time to Live │    Protocol   │         Header Checksum         │
├─────────────────────────────────────────────────────────────────┤
│                       Source Address                            │
├─────────────────────────────────────────────────────────────────┤
│                    Destination Address                          │
├─────────────────────────────────────────────────────────────────┤
│                    Options (if any)                             │
└─────────────────────────────────────────────────────────────────┘

Type of Service Field (8 bits):
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│   DSCP (6 bits)   │ ECN (2 bits) │
└───────────────────────────────────┘

ECN Field:
00 = Not ECN-Capable Transport (Non-ECT)
01 = ECN Capable Transport (ECT(1))
10 = ECN Capable Transport (ECT(0))
11 = Congestion Experienced (CE)
```

### ECN Operation:
```
     Sender              Router              Receiver
        │                    │                    │
        │  IP: ECT(0/1)      │                    │
        │  TCP: SYN, ECE=1   │                    │
        │───────────────────▶│                    │
        │                    │                    │
        │                    │  IP: ECT(0/1)      │
        │                    │───────────────────▶│
        │                    │                    │
        │                    │    [Congestion]    │
        │                    │  IP: CE (Marked)   │
        │                    │───────────────────▶│
        │                    │                    │
        │                    │                    │
        │  IP: ECT(0/1)      │                    │
        │  TCP: ACK, ECE=1   │                    │
        │◀───────────────────│                    │
        │                    │                    │
        │  TCP: CWR=1        │                    │
        │  (Reduce rate)     │                    │
        │───────────────────▶│                    │
```

### Other Network-Assisted Mechanisms

#### **Source Quench (ICMP)**
- Router sends ICMP Source Quench message to sender
- **Problem**: Can cause more congestion (additional packets)
- **Status**: Deprecated in modern networks

#### **DECbit (Digital Equipment Corporation)**
- Router sets a bit in packet header when congested
- Receiver echoes this bit back to sender in ACK
- Sender adjusts transmission rate

#### **RED (Random Early Detection)**
- Router proactively drops/marks packets before queue fills
- **Algorithm**:
  1. Calculate average queue length
  2. If avg < min_threshold: No action
  3. If min_threshold ≤ avg < max_threshold: Mark/drop with probability p
  4. If avg ≥ max_threshold: Mark/drop all packets

**RED Parameters:**
- **min_th**: Minimum threshold (e.g., 5 packets)
- **max_th**: Maximum threshold (e.g., 15 packets)
- **max_p**: Maximum dropping probability (e.g., 0.1)

---

## 🔄 TCP Congestion Control

### TCP Congestion Control Principles
1. **A lost segment** = sign of congestion
2. **An ACKed segment** = sign that path is OK
3. **Probe for bandwidth** = increase rate until loss occurs
4. **React to loss** = decrease rate when loss detected

### TCP Congestion Control Components

#### 1. **Congestion Window (cwnd)**
- Maximum amount of data that can be in transit
- **Sender maintains**: `LastByteSent - LastByteAcked ≤ min(cwnd, rwnd)`
- Where `rwnd` = receiver's advertised window

#### 2. **Slow Start**
- **Purpose**: Quickly find available bandwidth
- **Algorithm**: 
  - Start with `cwnd = 1 MSS` (Maximum Segment Size)
  - Increase `cwnd` by 1 MSS for each ACK received
  - **Result**: Exponential growth (cwnd doubles every RTT)

```
cwnd growth in Slow Start:
RTT 1: cwnd = 1  → Send 1 segment
RTT 2: cwnd = 2  → Send 2 segments (get 2 ACKs, each adds 1)
RTT 3: cwnd = 4  → Send 4 segments
RTT 4: cwnd = 8  → Send 8 segments
RTT 5: cwnd = 16 → Send 16 segments
```

#### 3. **Congestion Avoidance**
- **Trigger**: When `cwnd ≥ ssthresh` (slow start threshold)
- **Algorithm**: 
  - Increase `cwnd` by 1 MSS per RTT
  - **Additive Increase**: `cwnd = cwnd + MSS*(MSS/cwnd)` per ACK

#### 4. **Fast Retransmit**
- **Trigger**: 3 duplicate ACKs received
- **Action**: Retransmit missing segment immediately (don't wait for timeout)
- **Reason**: Duplicate ACKs suggest segment lost (but later segments arrived)

#### 5. **Fast Recovery**
- **After Fast Retransmit**:
  - Set `ssthresh = cwnd/2`
  - Set `cwnd = ssthresh + 3*MSS` (for 3 duplicate ACKs)
  - Increase `cwnd` by 1 MSS for each additional duplicate ACK
  - When new ACK arrives: set `cwnd = ssthresh`

### TCP Congestion Control Algorithms

#### **TCP Tahoe (Original)**
```
State Machine:
[Slow Start] → [Congestion Avoidance]
      ↓              ↓
[Fast Retransmit] → [Slow Start] (on loss)
```

**Tahoe Behavior:**
- On 3 duplicate ACKs or timeout:
  1. Set `ssthresh = cwnd/2`
  2. Set `cwnd = 1 MSS`
  3. Enter Slow Start

#### **TCP Reno (Improved)**
```
State Machine:
[Slow Start] → [Congestion Avoidance]
      ↓              ↓
[Fast Retransmit] → [Fast Recovery] → [Congestion Avoidance]
```

**Reno Behavior:**
- On 3 duplicate ACKs:
  1. Set `ssthresh = cwnd/2`
  2. Set `cwnd = ssthresh + 3*MSS`
  3. Enter Fast Recovery
- On timeout:
  1. Set `ssthresh = cwnd/2`
  2. Set `cwnd = 1 MSS`
  3. Enter Slow Start

#### **TCP NewReno**
- Enhancement over Reno
- Handles multiple packet losses in same window
- Remains in Fast Recovery until all lost packets recovered

#### **TCP Vegas**
- **Proactive** (not reactive like Tahoe/Reno)
- **Mechanism**: 
  1. Measure BaseRTT (minimum RTT)
  2. Calculate Expected throughput = cwnd/BaseRTT
  3. Measure Actual throughput
  4. Adjust cwnd based on difference

**Vegas Algorithm:**
```
diff = (Expected - Actual) * BaseRTT
if diff < α: increase cwnd
if diff > β: decrease cwnd
otherwise: keep cwnd
(typically α=1, β=3)
```

#### **TCP CUBIC (Default in Linux, Windows)**
- **Key Idea**: Cubic function for window growth
- **Features**:
  - Fast recovery after loss
  - Fair to other flows
  - Scalable in high-speed networks

**CUBIC Window Growth:**
```
W(t) = C*(t-K)³ + Wmax
where:
W(t) = window size at time t
C = scaling constant
K = cube root of (Wmax*β/C)
Wmax = window size at last congestion event
β = multiplicative decrease factor
```

### TCP Congestion Control States
```
                    [Start]
                       │
                       ▼
                 [Slow Start]
                       │
                 cwnd ≥ ssthresh
                       │
                       ▼
            [Congestion Avoidance]
                 /           \
        3 dup ACKs       Timeout
               /               \
              ▼                 ▼
    [Fast Retransmit]      [Slow Start]
              │
              ▼
      [Fast Recovery]
              │
        New ACK received
              │
              ▼
    [Congestion Avoidance]
```

### TCP Congestion Control Parameters
- **MSS**: Maximum Segment Size (typically 1460 bytes for Ethernet)
- **RTT**: Round Trip Time (measured dynamically)
- **RTO**: Retransmission Timeout (typically 1-3 seconds)
- **ssthresh**: Slow Start Threshold (initial value often 65535 bytes)

### Example: TCP Reno Congestion Control
```
Time  RTT  Event                     cwnd   ssthresh  State
-----------------------------------------------------------
0     100  Start                     1      64        Slow Start
1     100  ACK received              2      64        Slow Start
2     100  2 ACKs received           4      64        Slow Start
3     100  4 ACKs received           8      64        Slow Start
4     100  8 ACKs received           16     64        Slow Start
5     100  16 ACKs received          32     64        Slow Start
6     100  32 ACKs received          64     64        Congestion Avoidance
7     100  Increase                  65     64        Congestion Avoidance
8     100  3 duplicate ACKs          33     32        Fast Recovery
9     100  New ACK                   32     32        Congestion Avoidance
```

---

## 🌐 NETWORK LAYER: IP ADDRESSING

### Introduction to Network Layer
The Network Layer is responsible for **logical addressing**, **routing**, and **forwarding** packets across different networks.

### Key Functions:
1. **Logical Addressing**: IP addresses
2. **Routing**: Determining best path
3. **Forwarding**: Moving packets to next hop
4. **Fragmentation**: Breaking packets if needed
5. **Error Handling**: ICMP messages

---

## 🔢 IP Addressing

### IPv4 Address Format
- **32-bit** binary number
- **Dotted Decimal Notation**: `192.168.1.1`
- Each octet: 0-255 (8 bits)

**Binary to Decimal Conversion:**
```
192.168.1.1 = 
11000000.10101000.00000001.00000001
 192   .  168   .   1    .   1
```

### IP Address Structure
```
┌─────────────────────────────────┐
│   Network Part   │ Host Part    │
└─────────────────────────────────┘
       n bits        (32-n) bits
```

### Classful Addressing (Obsolete but Important Concept)

#### **Class A**
- **Range**: 1.0.0.0 to 126.255.255.255
- **First bit**: 0
- **Network bits**: 8 (first octet)
- **Host bits**: 24
- **Default Mask**: 255.0.0.0 (/8)
- **Networks**: 126 (0 and 127 reserved)
- **Hosts per network**: 16,777,214

#### **Class B**
- **Range**: 128.0.0.0 to 191.255.255.255
- **First bits**: 10
- **Network bits**: 16 (first two octets)
- **Host bits**: 16
- **Default Mask**: 255.255.0.0 (/16)
- **Networks**: 16,384
- **Hosts per network**: 65,534

#### **Class C**
- **Range**: 192.0.0.0 to 223.255.255.255
- **First bits**: 110
- **Network bits**: 24 (first three octets)
- **Host bits**: 8
- **Default Mask**: 255.255.255.0 (/24)
- **Networks**: 2,097,152
- **Hosts per network**: 254

#### **Class D** (Multicast)
- **Range**: 224.0.0.0 to 239.255.255.255
- **First bits**: 1110
- **Purpose**: Multicast groups

#### **Class E** (Experimental)
- **Range**: 240.0.0.0 to 255.255.255.255
- **First bits**: 1111
- **Purpose**: Reserved for research

### Classful Addressing Summary
| Class | Range | Network Bits | Host Bits | Default Mask | Networks | Hosts/Net |
|-------|-------|--------------|-----------|--------------|----------|-----------|
| A | 1-126 | 8 | 24 | 255.0.0.0 | 126 | 16.7M |
| B | 128-191 | 16 | 16 | 255.255.0.0 | 16,384 | 65,534 |
| C | 192-223 | 24 | 8 | 255.255.255.0 | 2.1M | 254 |
| D | 224-239 | - | - | - | Multicast | - |
| E | 240-255 | - | - | - | Experimental | - |

**Problems with Classful Addressing:**
1. **Inefficient**: Fixed sizes don't match needs
2. **Wasteful**: Small organizations get Class A/B
3. **Exhaustion**: IPv4 addresses running out
4. **Routing Tables**: Too many entries

---

## 🎯 Classless Addressing (CIDR)

### CIDR (Classless Inter-Domain Routing)
- **Introduced**: 1993 (RFC 1519)
- **Key Idea**: Variable-length subnet masks
- **Notation**: IP/prefix-length (e.g., 192.168.1.0/24)

### CIDR Notation
```
192.168.1.0/24
    ↑         ↑
 IP Address   Prefix Length (24 bits for network)
 
Network: 192.168.1.0
Mask:    255.255.255.0  (24 ones followed by 8 zeros)
Hosts:   192.168.1.1 to 192.168.1.254
Broadcast: 192.168.1.255
```

### Subnet Mask
- **Purpose**: Distinguish network and host parts
- **Format**: 32 bits (1s for network, 0s for host)

**Common Subnet Masks:**
```
/8  = 255.0.0.0      = 11111111.00000000.00000000.00000000
/16 = 255.255.0.0    = 11111111.11111111.00000000.00000000
/24 = 255.255.255.0  = 11111111.11111111.11111111.00000000
/25 = 255.255.255.128= 11111111.11111111.11111111.10000000
/26 = 255.255.255.192= 11111111.11111111.11111111.11000000
/30 = 255.255.255.252= 11111111.11111111.11111111.11111100
```

### Calculating Network Address
```
Given: IP = 192.168.1.130, Mask = 255.255.255.192 (/26)

Step 1: Convert to binary
IP:   11000000.10101000.00000001.10000010
Mask: 11111111.11111111.11111111.11000000

Step 2: AND operation
Network: 11000000.10101000.00000001.10000000
         192      .168      .1        .128

Network Address: 192.168.1.128/26
```

### Calculating Broadcast Address
```
Network: 192.168.1.128/26
Host bits (last 6 bits): all 1s

Network: 11000000.10101000.00000001.10000000
Broadcast: Set host bits to 1:
          11000000.10101000.00000001.10111111
          192      .168      .1        .191

Broadcast Address: 192.168.1.191
```

### Calculating Host Range
```
Network: 192.168.1.128/26
First Host: Network + 1 = 192.168.1.129
Last Host: Broadcast - 1 = 192.168.1.190
Host Range: 192.168.1.129 - 192.168.1.190
Total Hosts: 2^6 - 2 = 62 hosts
```

---

## 🎨 Subnetting

### What is Subnetting?
Dividing a large network into smaller, manageable subnetworks.

### Reasons for Subnetting:
1. **Reduce broadcast traffic**
2. **Improve security** (isolate departments)
3. **Optimize performance**
4. **Simplify management**
5. **Match physical network structure**

### Subnetting Process

#### **Step 1: Determine Requirements**
- Number of subnets needed
- Number of hosts per subnet

#### **Step 2: Choose Subnet Mask**
- Borrow bits from host portion
- More borrowed bits = more subnets, fewer hosts

#### **Step 3: Calculate Subnet Details**
- Subnet addresses
- Host ranges
- Broadcast addresses

### Subnetting Example 1

**Given**: Network 192.168.1.0/24, need 4 subnets

**Step 1: Calculate bits needed**
- Need 4 subnets = 2² = 4 → Need 2 bits
- Current: /24 (24 network bits)
- New: /26 (24 + 2 = 26)

**Step 2: Subnet Mask**
- /26 = 255.255.255.192

**Step 3: Calculate Subnets**
```
Increment = 256 - 192 = 64

Subnet 1: 192.168.1.0/26
   Network: 192.168.1.0
   Hosts: 192.168.1.1 - 192.168.1.62
   Broadcast: 192.168.1.63

Subnet 2: 192.168.1.64/26
   Network: 192.168.1.64
   Hosts: 192.168.1.65 - 192.168.1.126
   Broadcast: 192.168.1.127

Subnet 3: 192.168.1.128/26
   Network: 192.168.1.128
   Hosts: 192.168.1.129 - 192.168.1.190
   Broadcast: 192.168.1.191

Subnet 4: 192.168.1.192/26
   Network: 192.168.1.192
   Hosts: 192.168.1.193 - 192.168.1.254
   Broadcast: 192.168.1.255
```

### Subnetting Example 2 (VLSM - Variable Length Subnet Mask)

**Given**: Network 172.16.0.0/16
**Requirements**:
- Subnet A: 1000 hosts
- Subnet B: 500 hosts
- Subnet C: 250 hosts
- Subnet D: 120 hosts

**Solution**:

**Subnet A (1000 hosts):**
- Need: 2¹⁰ = 1024 hosts → 10 host bits
- Mask: /22 (32 - 10 = 22)
- Subnet: 172.16.0.0/22
- Range: 172.16.0.1 - 172.16.3.254

**Subnet B (500 hosts):**
- Need: 2⁹ = 512 hosts → 9 host bits
- Mask: /23 (32 - 9 = 23)
- Next available: 172.16.4.0/23
- Range: 172.16.4.1 - 172.16.5.254

**Subnet C (250 hosts):**
- Need: 2⁸ = 256 hosts → 8 host bits
- Mask: /24
- Next available: 172.16.6.0/24
- Range: 172.16.6.1 - 172.16.6.254

**Subnet D (120 hosts):**
- Need: 2⁷ = 128 hosts → 7 host bits
- Mask: /25
- Next available: 172.16.7.0/25
- Range: 172.16.7.1 - 172.16.7.126

**Remaining**: 172.16.7.128/25 and beyond

### Subnetting Cheat Sheet
| Prefix | Mask | Subnets | Hosts | Increment |
|--------|------|---------|-------|-----------|
| /25 | 255.255.255.128 | 2 | 126 | 128 |
| /26 | 255.255.255.192 | 4 | 62 | 64 |
| /27 | 255.255.255.224 | 8 | 30 | 32 |
| /28 | 255.255.255.240 | 16 | 14 | 16 |
| /29 | 255.255.255.248 | 32 | 6 | 8 |
| /30 | 255.255.255.252 | 64 | 2 | 4 |
| /31 | 255.255.255.254 | 128 | 2* | 2 |
| /32 | 255.255.255.255 | 256 | 1 | 1 |

* /31 used for point-to-point links (RFC 3021)

---

## 🌉 Supernetting (Route Aggregation)

### What is Supernetting?
Combining multiple contiguous networks into one larger network announcement.

### Purpose:
1. **Reduce routing table size**
2. **Improve routing efficiency**
3. **Minimize routing updates**

### Supernetting Example

**Given Networks:**
- 192.168.0.0/24
- 192.168.1.0/24
- 192.168.2.0/24
- 192.168.3.0/24

**Step 1: Convert to binary**
```
192.168.0.0:   11000000.10101000.00000000.00000000
192.168.1.0:   11000000.10101000.00000001.00000000
192.168.2.0:   11000000.10101000.00000010.00000000
192.168.3.0:   11000000.10101000.00000011.00000000
```

**Step 2: Find common bits**
```
Common bits: 11000000.10101000.000000 (22 bits)
```

**Step 3: Create supernet**
- Supernet: 192.168.0.0/22
- Mask: 255.255.252.0
- Range: 192.168.0.0 - 192.168.3.255

### Supernetting Rules:
1. Networks must be **contiguous**
2. Number of networks must be **power of 2**
3. First network address must be **divisible** by number of networks

### CIDR Block Allocation Example
```
ISP gets: 200.100.0.0/16

Allocate to Company A: 200.100.0.0/20 (4096 addresses)
Allocate to Company B: 200.100.16.0/20 (4096 addresses)
Allocate to Company C: 200.100.32.0/19 (8192 addresses)

ISP advertises: 200.100.0.0/16 to upstream
```

---

## 🛠️ Network Layer Services

### 1. **Packetizing**
- Encapsulating transport layer segments into packets
- Adding IP header information

### 2. **Routing**
- Determining optimal path from source to destination
- **Types**:
  - **Static Routing**: Manual configuration
  - **Dynamic Routing**: Automatic (RIP, OSPF, BGP)

### 3. **Forwarding**
- Moving packets from input to output interface
- **Methods**:
  - **Destination-based**: Based on destination IP
  - **Label-based**: MPLS (Multi-Protocol Label Switching)

### 4. **Fragmentation and Reassembly**
- **MTU (Maximum Transmission Unit)**: Maximum packet size
- **Fragmentation**: Breaking packets if > MTU
- **Reassembly**: Putting fragments back together

**IP Header Fragmentation Fields:**
```
Identification (16 bits): Unique ID for original packet
Flags (3 bits): 
  - Bit 0: Reserved
  - Bit 1: Don't Fragment (DF)
  - Bit 2: More Fragments (MF)
Fragment Offset (13 bits): Position of fragment in original packet
```

### 5. **Error Reporting**
- **ICMP (Internet Control Message Protocol)**
- Messages: Destination Unreachable, Time Exceeded, Redirect

### 6. **Quality of Service (QoS)**
- Prioritizing certain types of traffic
- **Mechanisms**: DiffServ, IntServ

---

## 📊 Network Layer Performance

### Key Performance Metrics

#### 1. **Bandwidth**
- Maximum data transfer rate
- **Units**: bps, Kbps, Mbps, Gbps
- **Types**: 
  - **Theoretical**: Maximum possible
  - **Effective**: Actual achieved

#### 2. **Throughput**
- Actual data transfer rate
- **Formula**: `Throughput = Transfer Size / Transfer Time`
- **Factors**: Congestion, protocol overhead, errors

#### 3. **Latency (Delay)**
- Time for packet to travel from source to destination
- **Components**:
  - **Processing Delay**: Router processing time
  - **Queuing Delay**: Time in router queue
  - **Transmission Delay**: Time to push bits onto link
    ```
    Transmission Delay = Packet Size / Bandwidth
    ```
  - **Propagation Delay**: Time through medium
    ```
    Propagation Delay = Distance / Propagation Speed
    ```

**Total Delay:**
```
Total Delay = Processing + Queuing + Transmission + Propagation
```

#### 4. **Jitter**
- Variation in packet arrival times
- **Critical for**: VoIP, video streaming
- **Measurement**: Standard deviation of latency

#### 5. **Packet Loss**
- Percentage of packets that don't reach destination
- **Causes**: Congestion, errors, buffer overflow
- **Impact**: Retransmissions, reduced throughput

#### 6. **Availability**
- Percentage of time network is operational
- **Formula**: `Availability = Uptime / (Uptime + Downtime)`
- **Targets**: 99.9% ("three nines") = 8.76 hours downtime/year

### Performance Calculations

#### **Example 1: File Transfer Time**
```
File Size: 10 MB = 80,000,000 bits
Bandwidth: 10 Mbps = 10,000,000 bps
Theoretical Time = 80,000,000 / 10,000,000 = 8 seconds
Actual Time (with 20% overhead) = 8 * 1.2 = 9.6 seconds
```

#### **Example 2: End-to-End Delay**
```
Packet Size: 1500 bytes = 12,000 bits
Link Bandwidth: 100 Mbps = 100,000,000 bps
Distance: 1000 km
Propagation Speed: 2 × 10⁸ m/s (in fiber)

Transmission Delay = 12,000 / 100,000,000 = 0.00012 s = 0.12 ms
Propagation Delay = 1,000,000 / (2 × 10⁸) = 0.005 s = 5 ms
Processing + Queuing Delay (assume): 1 ms

Total Delay = 0.12 + 5 + 1 = 6.12 ms
```

### Bottleneck Analysis
```
Path: A → B → C → D
Bandwidths: 100 Mbps → 10 Mbps → 100 Mbps

Bottleneck: 10 Mbps link
End-to-end throughput ≤ 10 Mbps
```

### Network Performance Optimization

#### 1. **Reduce Latency**
- Use faster links
- Reduce hops (direct paths)
- Implement QoS
- Use CDN (Content Delivery Networks)

#### 2. **Increase Throughput**
- Upgrade bandwidth
- Use parallel paths (load balancing)
- Implement compression
- Optimize protocols (TCP tuning)

#### 3. **Reduce Packet Loss**
- Implement congestion control
- Increase buffer sizes
- Use error correction
- Implement redundancy

#### 4. **Improve Availability**
- Redundant links/paths
- Failover mechanisms
- Regular maintenance
- Monitoring and alerts

### Performance Monitoring Tools
- **ping**: Tests connectivity and measures RTT
- **traceroute/tracert**: Shows path and per-hop delays
- **iperf**: Measures bandwidth and throughput
- **Wireshark**: Packet analysis
- **SNMP**: Network monitoring protocol
- **NetFlow/sFlow**: Traffic analysis

### QoS Mechanisms

#### **DiffServ (Differentiated Services)**
- Classifies traffic into service classes
- **DSCP (Differentiated Services Code Point)**: 6-bit field in IP header
- **Classes**: EF (Expedited Forwarding), AF (Assured Forwarding), BE (Best Effort)

#### **IntServ (Integrated Services)**
- Resource reservation (RSVP protocol)
- Per-flow QoS guarantees
- More complex, less scalable

---

## 🎯 Summary

### Congestion Control:
- **TCP Congestion Control**: Slow Start, Congestion Avoidance, Fast Retransmit/Recovery
- **Network-Assisted**: ECN, RED, DECbit
- **Goals**: Maximize throughput, minimize loss, ensure fairness

### IP Addressing:
- **Classful**: Fixed classes (A, B, C, D, E) - obsolete
- **Classless (CIDR)**: Variable subnet masks, efficient allocation
- **Subnetting**: Divide network into smaller subnets
- **Supernetting**: Combine networks for efficient routing

### Network Layer Services:
- Routing, forwarding, fragmentation, error reporting
- Logical addressing (IP addresses)
- QoS support

### Network Performance:
- **Metrics**: Bandwidth, throughput, latency, jitter, packet loss, availability
- **Optimization**: Reduce bottlenecks, implement QoS, monitor continuously

### Key Formulas:
```
Total Hosts = 2^(host bits) - 2
Total Subnets = 2^(subnet bits)
Transmission Delay = Packet Size / Bandwidth
Propagation Delay = Distance / Propagation Speed
Throughput = min(bottleneck bandwidth, window size/RTT)
```

### Best Practices:
1. Use CIDR for efficient addressing
2. Implement proper subnetting for security and management
3. Enable ECN for better congestion control
4. Monitor performance metrics regularly
5. Implement QoS for critical applications
6. Use VLSM for efficient address allocation

---

*This guide covers essential concepts of congestion control and network layer fundamentals. Practice subnetting calculations and understand how TCP manages congestion for optimal network performance.*
