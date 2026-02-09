# Computer Networks - Complete Guide for Placements

## Table of Contents
1. [Introduction to Computer Networks](#1-introduction-to-computer-networks)
2. [Network Models](#2-network-models)
3. [Physical Layer](#3-physical-layer)
4. [Data Link Layer](#4-data-link-layer)
5. [MAC Sub-Layer](#5-mac-sub-layer)
6. [Network Layer](#6-network-layer)
7. [Transport Layer](#7-transport-layer)
8. [Application Layer](#8-application-layer)
9. [Wireless Networks](#9-wireless-networks)

---

# 1. Introduction to Computer Networks

## What is a Computer Network?

**Computer Network:** Interconnected collection of autonomous computers that can exchange data and share resources.

**Purpose:**
- Resource sharing (files, printers, storage)
- Communication (email, chat, video calls)
- Reliability (backup systems)
- Cost efficiency

## Types of Networks

### Based on Geographic Scope

**1. PAN (Personal Area Network)**
- Range: ~10 meters
- Examples: Bluetooth devices, USB connections
- Use: Personal devices connectivity

**2. LAN (Local Area Network)**
- Range: Building or campus (~1 km)
- Speed: 10 Mbps to 10 Gbps
- Examples: Office network, home Wi-Fi
- Characteristics: High speed, low latency, privately owned

**3. MAN (Metropolitan Area Network)**
- Range: City (~10-100 km)
- Examples: Cable TV network, city-wide Wi-Fi
- Use: Connecting multiple LANs in a city

**4. WAN (Wide Area Network)**
- Range: Country/Continent (>100 km)
- Examples: Internet, corporate networks
- Characteristics: Lower speed than LAN, uses public infrastructure

### Based on Transmission Technology

**1. Broadcast Networks**
- Single communication channel shared by all devices
- Example: Ethernet, Wi-Fi
- Packet sent by any machine is received by all

**2. Point-to-Point Networks**
- Dedicated link between two devices
- Example: Telephone network
- May need routing through intermediate nodes

## Network Topologies

### 1. Bus Topology
```
Device1 ----+---- Device2 ----+---- Device3
            |                 |
         Device4           Device5
```
- All devices connected to single cable (bus)
- **Advantages:** Easy to install, less cable
- **Disadvantages:** If main cable fails, entire network fails

### 2. Ring Topology
```
    Device1
    /     \
Device2   Device5
    |     |
Device3---Device4
```
- Devices connected in circular fashion
- Data travels in one direction
- **Advantages:** Equal access, no collision
- **Disadvantages:** Failure of one device affects entire network

### 3. Star Topology
```
        Hub/Switch
       /  |  |  \
     D1  D2  D3  D4
```
- All devices connected to central hub/switch
- **Advantages:** Easy to add devices, failure of one device doesn't affect others
- **Disadvantages:** If hub fails, entire network fails

### 4. Mesh Topology
```
D1 ---- D2
 |\    /|
 | \  / |
 |  \/  |
 |  /\  |
 | /  \ |
 |/    \|
D3 ---- D4
```
- Every device connected to every other device
- **Advantages:** High reliability, no single point of failure
- **Disadvantages:** Expensive, complex wiring

### 5. Tree (Hierarchical) Topology
```
        Root
       /    \
    Node1  Node2
    /  \    /  \
   N3  N4  N5  N6
```
- Combination of star topologies
- **Advantages:** Scalable, easy to manage
- **Disadvantages:** If backbone fails, segment fails

## Network Devices

### 1. Hub (Physical Layer Device)
- **Function:** Broadcasts data to all connected devices
- **Type:** Passive device (no intelligence)
- **Collision Domain:** Single (all devices share)
- **Example:** 8-port hub connects 8 devices
```
Hub receives packet → Sends to ALL ports
```
**Disadvantage:** Unnecessary traffic, collisions

### 2. Switch (Data Link Layer Device)
- **Function:** Forwards data only to destination device
- **Intelligence:** Maintains MAC address table
- **Collision Domain:** Separate for each port
```
Switch receives packet → Checks MAC table → Sends to specific port
```
**Advantages:** Reduces traffic, fewer collisions, better performance

### 3. Router (Network Layer Device)
- **Function:** Connects different networks, routes packets
- **Intelligence:** Maintains routing table
- **Decision:** Based on IP addresses
```
Router receives packet → Checks routing table → Forwards to best path
```
**Use:** Connect LAN to WAN, connect to Internet

### 4. Gateway
- **Function:** Protocol converter, connects different network architectures
- **Example:** Email gateway, VoIP gateway
- **Operates:** All layers

### Comparison Table

| Device | Layer | Function | Intelligence |
|--------|-------|----------|-------------|
| Hub | Physical | Broadcast | No |
| Switch | Data Link | Selective forwarding | MAC table |
| Router | Network | Route between networks | Routing table |
| Gateway | All layers | Protocol conversion | High |

## Packets, IP Address, MAC Address

### Packet
**Packet:** Unit of data transmitted over network

**Structure:**
```
[Header | Payload | Trailer]
```
- **Header:** Source, destination, protocol info
- **Payload:** Actual data
- **Trailer:** Error checking (CRC)

**Packet Switching:** Data divided into packets, each routed independently

### IP Address (Internet Protocol Address)

**Purpose:** Logical address for network layer routing

**IPv4:**
- 32-bit address
- Format: `192.168.1.1`
- Example: `11000000.10101000.00000001.00000001`
- Total addresses: 2^32 ≈ 4.3 billion

**IPv6:**
- 128-bit address
- Format: `2001:0db8:85a3:0000:0000:8a2e:0370:7334`
- Total addresses: 2^128 (practically unlimited)

### MAC Address (Media Access Control Address)

**Purpose:** Physical address for data link layer

**Characteristics:**
- 48-bit address (6 bytes)
- Format: `AA:BB:CC:DD:EE:FF`
- Example: `00:1A:2B:3C:4D:5E`
- Burned into NIC (Network Interface Card)
- Unique globally

**Structure:**
```
24 bits (OUI - Manufacturer) | 24 bits (NIC specific)
```

### IP vs MAC Address

| IP Address | MAC Address |
|------------|-------------|
| Logical address | Physical address |
| Network layer | Data link layer |
| Can change | Permanent (usually) |
| Assigned by network | Assigned by manufacturer |
| Used for routing | Used for local delivery |

---

# 2. Network Models

## OSI Model (Open Systems Interconnection)

**7 Layers Model** - Theoretical framework

```
7. Application Layer    ← User Interface
6. Presentation Layer   ← Data Translation
5. Session Layer        ← Session Management
4. Transport Layer      ← End-to-End Communication
3. Network Layer        ← Routing
2. Data Link Layer      ← Frame Delivery
1. Physical Layer       ← Bits Transmission
```

### Layer Functions

**7. Application Layer**
- User interface and network services
- Protocols: HTTP, FTP, SMTP, DNS
- Example: Web browser, email client

**6. Presentation Layer**
- Data translation, encryption, compression
- Functions: Format conversion, encryption/decryption
- Example: JPEG, MPEG, SSL/TLS

**5. Session Layer**
- Establishes, manages, terminates sessions
- Functions: Session establishment, synchronization
- Example: RPC, NetBIOS

**4. Transport Layer**
- End-to-end communication, reliability
- Protocols: TCP, UDP
- Functions: Segmentation, flow control, error control

**3. Network Layer**
- Routing, logical addressing
- Protocols: IP, ICMP, ARP
- Device: Router

**2. Data Link Layer**
- Frame delivery, error detection, MAC addressing
- Sub-layers: LLC and MAC
- Device: Switch
- Protocols: Ethernet, PPP

**1. Physical Layer**
- Bit transmission over physical medium
- Defines: Cables, connectors, voltages
- Device: Hub, Repeater

## TCP/IP Model

**4 Layers Model** - Practical implementation (used in Internet)

```
4. Application Layer    ← Combines OSI layers 5, 6, 7
3. Transport Layer      ← TCP, UDP
2. Internet Layer       ← IP, ICMP, ARP
1. Network Access Layer ← Combines OSI layers 1, 2
```

### Comparison: OSI vs TCP/IP

| Feature | OSI Model | TCP/IP Model |
|---------|-----------|--------------|
| Layers | 7 | 4 |
| Type | Theoretical | Practical |
| Development | ISO | DoD (US Dept of Defense) |
| Protocol dependent | No | Yes |
| Usage | Reference model | Internet standard |

### Data Flow Through Layers

```
Sender Side:
Application → Transport → Network → Data Link → Physical
   (Data)   (Segment)   (Packet)   (Frame)      (Bits)

Receiver Side:
Physical → Data Link → Network → Transport → Application
 (Bits)    (Frame)    (Packet)  (Segment)    (Data)
```

### Encapsulation

```
Application Layer:        [Data]
Transport Layer:          [TCP Header | Data]
Network Layer:            [IP Header | TCP Header | Data]
Data Link Layer:          [Ethernet Header | IP Header | TCP Header | Data | Trailer]
Physical Layer:           Bits: 101010101...
```

---

# 3. Physical Layer

## Basics of Data Communication

### Data Communication Components

1. **Message:** Information to be communicated
2. **Sender:** Device sending message
3. **Receiver:** Device receiving message
4. **Medium:** Physical path (cable, wireless)
5. **Protocol:** Rules governing communication

### Data Transmission Modes

**1. Simplex**
- One-way communication
- Example: TV broadcast, keyboard to computer
```
Sender ──────→ Receiver
```

**2. Half-Duplex**
- Two-way, but one at a time
- Example: Walkie-talkie
```
Device A ←────→ Device B
```

**3. Full-Duplex**
- Two-way simultaneous
- Example: Telephone
```
Device A ⇄ Device B
```

## Transmission Media

### Guided Media (Wired)

**1. Twisted Pair Cable**

**Unshielded Twisted Pair (UTP)**
```
   Plastic
   Jacket
     |
  [Wire pairs twisted together]
```
- **Categories:** Cat5 (100 Mbps), Cat6 (1 Gbps), Cat7 (10 Gbps)
- **Use:** Ethernet, telephone lines
- **Advantages:** Cheap, easy to install
- **Disadvantages:** Limited distance (~100m), susceptible to interference

**Shielded Twisted Pair (STP)**
- Additional shielding for EMI protection
- More expensive than UTP

**2. Coaxial Cable**
```
[Inner conductor | Insulation | Shield | Outer jacket]
```
- **Use:** Cable TV, old Ethernet (10Base2, 10Base5)
- **Advantages:** Better shielding than twisted pair
- **Bandwidth:** Higher than twisted pair
- **Distance:** Up to 500m

**3. Fiber Optic Cable**
```
[Core | Cladding | Buffer | Jacket]
```
- **Transmission:** Light signals
- **Types:**
  - **Single-mode:** Single light path, long distance (100+ km), expensive
  - **Multi-mode:** Multiple light paths, short distance (2 km), cheaper
- **Advantages:** Very high bandwidth, immune to EMI, long distance
- **Disadvantages:** Expensive, difficult to install

### Unguided Media (Wireless)

**1. Radio Waves**
- Frequency: 3 kHz - 1 GHz
- Propagation: Omnidirectional
- Use: AM/FM radio, TV
- Range: Long distance

**2. Microwaves**
- Frequency: 1 GHz - 300 GHz
- Propagation: Line of sight
- Use: Satellite communication, cellular networks
- Characteristics: Can penetrate atmosphere

**3. Infrared**
- Frequency: 300 GHz - 400 THz
- Propagation: Short range, line of sight
- Use: TV remotes, short-range communication
- Characteristics: Cannot penetrate walls

### Comparison Table

| Media | Bandwidth | Distance | Cost | EMI Immunity |
|-------|-----------|----------|------|--------------|
| Twisted Pair | Low-Medium | 100m | Low | Low |
| Coaxial | Medium | 500m | Medium | Medium |
| Fiber Optic | Very High | 100+ km | High | Very High |
| Wireless | Varies | Varies | Medium | N/A |

## Transmission Impairments

### 1. Attenuation
- **Definition:** Signal strength decreases with distance
- **Solution:** Amplifiers, repeaters
```
Strong Signal ────────→ Weak Signal
```

### 2. Distortion
- **Definition:** Signal shape changes
- **Cause:** Different frequency components travel at different speeds
- **Effect:** Signal becomes unrecognizable

### 3. Noise
**Types:**
- **Thermal noise:** Random electron motion (unavoidable)
- **Induced noise:** External electromagnetic sources
- **Crosstalk:** Signal from one wire interferes with another
- **Impulse noise:** Sudden spikes (lightning, power surges)

**SNR (Signal-to-Noise Ratio):**
```
SNR (dB) = 10 log₁₀(Signal Power / Noise Power)
```
Higher SNR = Better quality

## Performance Metrics

### 1. Bandwidth
- **Definition:** Range of frequencies a channel can carry
- **Unit:** Hertz (Hz)
- **Example:** Twisted pair = 1 MHz, Fiber = 2 GHz

### 2. Throughput
- **Definition:** Actual data transfer rate
- **Unit:** bps (bits per second)
- **Formula:** Throughput ≤ Bandwidth

### 3. Latency (Delay)
**Components:**
- **Propagation delay:** Time for bit to travel
  ```
  Propagation delay = Distance / Propagation speed
  ```
- **Transmission delay:** Time to push all bits into wire
  ```
  Transmission delay = Packet size / Bandwidth
  ```
- **Queuing delay:** Time waiting in queue
- **Processing delay:** Time to process packet header

**Total Latency = Propagation + Transmission + Queuing + Processing**

### 4. Jitter
- Variation in packet arrival time
- Important for real-time applications (video calls)

---

# 4. Data Link Layer

## Functions of Data Link Layer

1. **Framing:** Divide bit stream into frames
2. **Physical Addressing:** Add MAC addresses
3. **Flow Control:** Prevent receiver overflow
4. **Error Control:** Detect and correct errors
5. **Access Control:** Determine which device has control

## Framing

**Frame:** Unit of data at data link layer

**Frame Structure:**
```
[Header | Data | Trailer]
```

**Header contains:**
- Source MAC address
- Destination MAC address
- Frame type

**Trailer contains:**
- Error detection code (CRC)

## Error Detection and Correction

### Why Errors Occur?
- Noise, interference
- Attenuation
- Crosstalk

### Error Detection Methods

**1. Parity Check**

**Single Bit Parity:**
- Add one parity bit to make total 1s even (even parity) or odd (odd parity)

**Example (Even Parity):**
```
Data: 1011001 (4 ones - even)
Parity bit: 0
Transmitted: 10110010

Data: 1011011 (5 ones - odd)
Parity bit: 1
Transmitted: 10110111
```

**Limitation:** Can detect odd number of bit errors, cannot detect even errors

**Two-Dimensional Parity:**
```
Data:
1 0 1 1 | 1 ← Row parity
0 1 0 1 | 0
1 1 0 0 | 0
---------
0 0 1 0   ← Column parity
```
Can detect and correct single-bit errors

**2. Checksum**

**Process:**
1. Divide data into segments
2. Add all segments
3. Take complement of sum
4. Append as checksum

**Example:**
```
Data segments: 10101010, 01010101
Sum: 11111111
Checksum: 00000000 (complement)

Receiver:
Add segments + checksum
If result = 11111111, no error
```

**3. Cyclic Redundancy Check (CRC)**

**Most powerful error detection method**

**Process:**
1. Treat data as polynomial
2. Choose divisor (generator polynomial)
3. Perform modulo-2 division
4. Remainder = CRC bits

**Example:**
```
Data: 1101 (13)
Generator: 1011 (x³ + x + 1)

Add 3 zeros (degree of generator - 1):
1101000

Divide:
       1100
     -------
1011 | 1101000
       1011
       ----
        0100
        0000
        ----
         1000
         1011
         ----
          011 ← Remainder (CRC)

Transmitted: 1101011
```

**Receiver:**
Divide received data by same generator
If remainder = 0, no error

**CRC Standards:**
- **CRC-8:** 8-bit CRC
- **CRC-16:** 16-bit CRC (used in Bluetooth)
- **CRC-32:** 32-bit CRC (used in Ethernet)

### Error Correction: Hamming Code

**Hamming Distance:** Number of bit positions where two codewords differ

**Hamming Code Properties:**
- Can detect d-1 errors if minimum distance = d
- Can correct (d-1)/2 errors

**Process:**

**Number of parity bits (r):**
```
2^r ≥ m + r + 1
where m = data bits
```

**Example:** For 4 data bits
```
2^r ≥ 4 + r + 1
r = 3 (minimum)
```

**Hamming Code Structure:**
```
Positions: 1  2  3  4  5  6  7
Bits:      P1 P2 D1 P4 D2 D3 D4
```
- P1, P2, P4 are parity bits (positions that are powers of 2)
- D1-D4 are data bits

**Parity Calculation:**
- P1 checks positions: 1, 3, 5, 7 (binary: xx1)
- P2 checks positions: 2, 3, 6, 7 (binary: x1x)
- P4 checks positions: 4, 5, 6, 7 (binary: 1xx)

**Example:**
```
Data: 1011

Position: 1  2  3  4  5  6  7
Bit:      P1 P2 1  P4 0  1  1

P1 (positions 1,3,5,7): 1,0,1 → P1 = 0
P2 (positions 2,3,6,7): 1,1,1 → P2 = 1
P4 (positions 4,5,6,7): 0,1,1 → P4 = 0

Hamming code: 0110011
```

**Error Detection:**
If error in position 5:
```
Received: 0111011 (bit 5 flipped)

Check P1: 0⊕1⊕1⊕1 = 1 (error)
Check P2: 1⊕1⊕1⊕1 = 0 (ok)
Check P4: 0⊕1⊕1⊕1 = 1 (error)

Error position: P1 + P4 = 1 + 4 = 5 ✓
```

## Elementary Data Link Protocols

### 1. Stop-and-Wait Protocol

**Process:**
1. Sender sends one frame
2. Waits for acknowledgment (ACK)
3. After ACK, sends next frame

```
Sender          Receiver
  |---Frame 0--->|
  |              |
  |<---ACK 0-----|
  |              |
  |---Frame 1--->|
  |              |
  |<---ACK 1-----|
```

**Efficiency:**
```
Efficiency = 1 / (1 + 2a)
where a = Propagation time / Transmission time
```

**Problem:** Low efficiency for high-latency networks

### 2. Sliding Window Protocol

**Concept:** Send multiple frames before waiting for ACK

**Window Size:** Number of frames that can be sent without ACK

**Go-Back-N:**
```
Window size = 7
Sender sends: F0, F1, F2, F3, F4, F5, F6
If F3 lost → Resend F3, F4, F5, F6, F7
```

**Selective Repeat:**
```
If F3 lost → Resend only F3
```

**Efficiency:**
```
Go-Back-N: Efficiency = N / (1 + 2a)
where N = window size
```

---

# 5. MAC Sub-Layer

## Multiple Access Protocols

**Problem:** How multiple devices share a single communication channel?

### Random Access Protocols

**1. ALOHA**

**Pure ALOHA:**
- Send whenever data is ready
- If collision, wait random time and retransmit

```
Station A: ----[Frame]----
Station B:      ----[Frame]---- ← Collision!
```

**Efficiency:** 18.4% (very low)

**Vulnerable Time:** 2 × Frame transmission time

**Slotted ALOHA:**
- Time divided into slots
- Transmission only at slot beginning
- Reduces collision probability

**Efficiency:** 36.8% (better)

**Vulnerable Time:** 1 × Frame transmission time

**2. CSMA (Carrier Sense Multiple Access)**

**Types:**

**1-Persistent CSMA:**
- If channel idle → Send immediately
- If channel busy → Wait, sense continuously
- When idle → Send with probability 1

**Non-Persistent CSMA:**
- If channel idle → Send
- If channel busy → Wait random time, sense again

**p-Persistent CSMA:**
- If channel idle → Send with probability p
- With probability (1-p) → Wait for next slot

**3. CSMA/CD (Collision Detection)**

**Used in:** Ethernet

**Process:**
1. Sense channel
2. If idle, start transmission
3. While transmitting, listen for collision
4. If collision detected, stop and send jam signal
5. Wait random backoff time
6. Retry

```
Time slots:
0  : A senses (idle), starts sending
1  : B senses (idle), starts sending
2  : Collision detected at A and B
3  : Both stop, send jam signal
4-7: Random backoff
8  : A retransmits successfully
```

**Minimum Frame Size:**
```
Frame transmission time ≥ 2 × Propagation delay
```

**Binary Exponential Backoff:**
```
After nth collision:
Wait random time between 0 and (2^n - 1) slot times
```

### Controlled Access Protocols

**1. Reservation**
- Time divided into intervals
- Each interval has reservation period and data transfer period
- Stations reserve slots in advance

**2. Polling**
- Central controller (primary) polls each station (secondary)
- If station has data, transmits
- If not, controller polls next

```
Primary → Poll Station 1 → Response (or no data)
Primary → Poll Station 2 → Response (or no data)
...
```

**3. Token Passing**
- Token (special frame) circulates in network
- Only station with token can transmit
- After transmission, passes token to next

```
Ring topology:
S1 → S2 → S3 → S4 → S1 (token circulates)
```

## Ethernet Protocol

**IEEE 802.3 Standard**

**Ethernet Frame Format:**
```
[Preamble | Destination MAC | Source MAC | Type | Data | CRC]
 7 bytes    6 bytes          6 bytes      2 bytes  46-1500  4 bytes
```

**Fields:**
- **Preamble:** 7 bytes of 10101010 (synchronization)
- **SFD:** Start Frame Delimiter (10101011)
- **Destination MAC:** 6 bytes
- **Source MAC:** 6 bytes
- **Type/Length:** Protocol type or frame length
- **Data:** 46-1500 bytes
- **CRC:** 4 bytes error detection

**Minimum Frame Size:** 64 bytes (ensures collision detection)
**Maximum Frame Size:** 1518 bytes

**Ethernet Standards:**

| Standard | Speed | Medium | Distance |
|----------|-------|--------|----------|
| 10Base-T | 10 Mbps | Twisted pair | 100m |
| 100Base-TX (Fast Ethernet) | 100 Mbps | Twisted pair | 100m |
| 1000Base-T (Gigabit) | 1 Gbps | Twisted pair | 100m |
| 10GBase-T | 10 Gbps | Twisted pair | 100m |

---

# 6. Network Layer

## Network Layer Services

1. **Logical Addressing:** IP addressing
2. **Routing:** Find best path
3. **Packet Forwarding:** Forward packets to destination
4. **Fragmentation:** Divide packets if too large
5. **Quality of Service (QoS):** Prioritize traffic

## IP Addressing

### IPv4 Addressing

**Format:** 32-bit address (4 bytes)
```
192.168.1.1
11000000.10101000.00000001.00000001
```

### Classful Addressing

**Class A:**
```
Format: 0 | Network (7 bits) | Host (24 bits)
Range: 0.0.0.0 to 127.255.255.255
Default mask: 255.0.0.0 (/8)
Networks: 128 (but 0 and 127 reserved)
Hosts per network: 2^24 - 2 = 16,777,214
```

**Class B:**
```
Format: 10 | Network (14 bits) | Host (16 bits)
Range: 128.0.0.0 to 191.255.255.255
Default mask: 255.255.0.0 (/16)
Networks: 16,384
Hosts per network: 2^16 - 2 = 65,534
```

**Class C:**
```
Format: 110 | Network (21 bits) | Host (8 bits)
Range: 192.0.0.0 to 223.255.255.255
Default mask: 255.255.255.0 (/24)
Networks: 2,097,152
Hosts per network: 2^8 - 2 = 254
```

**Class D (Multicast):**
```
Range: 224.0.0.0 to 239.255.255.255
```

**Class E (Reserved):**
```
Range: 240.0.0.0 to 255.255.255.255
```

**Special Addresses:**
- **Network Address:** All host bits = 0
- **Broadcast Address:** All host bits = 1
- **Loopback:** 127.0.0.1
- **Private addresses:**
  - Class A: 10.0.0.0/8
  - Class B: 172.16.0.0/12 to 172.31.0.0/12
  - Class C: 192.168.0.0/16

### Classless Addressing (CIDR)

**CIDR (Classless Inter-Domain Routing):**
- No fixed classes
- Variable-length subnet masking (VLSM)
- Notation: IP/prefix (e.g., 192.168.1.0/24)

**Example:**
```
192.168.1.0/26
Mask: 255.255.255.192 (26 ones)
Network bits: 26
Host bits: 6
Hosts: 2^6 - 2 = 62
```

### Subnetting

**Purpose:** Divide large network into smaller subnets

**Example:**
```
Given: 192.168.1.0/24
Create 4 subnets

Additional bits needed: 2 (because 2^2 = 4)
New mask: /24 + 2 = /26

Subnets:
1. 192.168.1.0/26    (192.168.1.0 to 192.168.1.63)
2. 192.168.1.64/26   (192.168.1.64 to 192.168.1.127)
3. 192.168.1.128/26  (192.168.1.128 to 192.168.1.191)
4. 192.168.1.192/26  (192.168.1.192 to 192.168.1.255)
```

**Subnetting Steps:**
1. Determine number of subnets needed
2. Calculate bits needed: 2^n ≥ subnets
3. Add bits to network portion
4. Calculate new subnet mask
5. Find subnet ranges

### Supernetting

**Purpose:** Combine multiple networks into single large network

**Example:**
```
Combine:
192.168.0.0/24
192.168.1.0/24
192.168.2.0/24
192.168.3.0/24

Result: 192.168.0.0/22
```

## IPv4 Header

```
0                   1                   2                   3   
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service|          Total Length         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|      Fragment Offset    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Time to Live |    Protocol   |         Header Checksum       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source Address                          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination Address                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

**Fields:**
- **Version (4 bits):** IP version (4 for IPv4)
- **IHL (4 bits):** Header length (min 20 bytes)
- **Type of Service (8 bits)
