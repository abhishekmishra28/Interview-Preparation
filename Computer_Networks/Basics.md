# Computer Networks - Basics

## Table of Contents
1. [What is a Network?](#what-is-a-network)
2. [Data Transmission Fundamentals](#data-transmission-fundamentals)
3. [Network Types](#network-types)
4. [Network Topologies](#network-topologies)
5. [OSI Model (Overview)](#osi-model-overview)
6. [TCP/IP Model (Overview)](#tcpip-model-overview)
7. [Network Devices](#network-devices)
8. [IP Addressing Basics](#ip-addressing-basics)
9. [Protocols Overview](#protocols-overview)
10. [Network Performance Metrics](#network-performance-metrics)

---

## What is a Network?

A **computer network** is a collection of interconnected devices (computers, servers, routers, switches, etc.) that can communicate and share resources with each other.

### Purpose of Networks:
- **Resource Sharing**: Share files, printers, and other hardware
- **Communication**: Email, messaging, video conferencing
- **Data Storage**: Centralized data storage and backup
- **Internet Access**: Connect to the global network

### Key Components:
- **Nodes**: Devices connected to the network (computers, phones, IoT devices)
- **Links**: Physical or wireless connections between nodes
- **Protocols**: Rules governing data transmission
- **Services**: Applications running on the network (web, email, file transfer)

---

## Data Transmission Fundamentals

### Bits and Bytes

- **Bit (b)**: The smallest unit of data in computing (0 or 1)
- **Byte (B)**: 8 bits = 1 Byte
- **Nibble**: 4 bits = 1 Nibble

### Common Data Units:
```
1 Byte (B) = 8 bits
1 Kilobyte (KB) = 1024 Bytes
1 Megabyte (MB) = 1024 KB
1 Gigabyte (GB) = 1024 MB
1 Terabyte (TB) = 1024 GB
```

### Bandwidth vs Throughput

- **Bandwidth**: Maximum data transfer rate of a network (theoretical capacity)
  - Measured in bps (bits per second), Kbps, Mbps, Gbps
  
- **Throughput**: Actual data transfer rate achieved in practice
  - Always ≤ Bandwidth due to overhead, latency, and losses

### Transmission Modes

1. **Simplex**: One-way communication (e.g., TV broadcast)
2. **Half-Duplex**: Two-way, but not simultaneous (e.g., walkie-talkie)
3. **Full-Duplex**: Two-way simultaneous communication (e.g., telephone)

### Transmission Media

**Guided Media (Wired):**
- Twisted Pair Cable (UTP, STP)
- Coaxial Cable
- Fiber Optic Cable

**Unguided Media (Wireless):**
- Radio Waves
- Microwaves
- Infrared
- Satellite

---

## Network Types

### 1. PAN (Personal Area Network)
- **Range**: Within 10 meters
- **Example**: Bluetooth connections, USB connections
- **Use Case**: Connecting personal devices (phone to earbuds, laptop to mouse)

### 2. LAN (Local Area Network)
- **Range**: Within a building or campus (up to a few kilometers)
- **Example**: Office network, home Wi-Fi
- **Characteristics**: 
  - High speed (100 Mbps to 10 Gbps)
  - Low latency
  - Privately owned

### 3. MAN (Metropolitan Area Network)
- **Range**: Across a city (up to 50 km)
- **Example**: Cable TV network, city-wide Wi-Fi
- **Characteristics**: 
  - Connects multiple LANs
  - Can be public or private

### 4. WAN (Wide Area Network)
- **Range**: Across countries or continents
- **Example**: The Internet, corporate networks across cities
- **Characteristics**: 
  - Lower speed compared to LAN
  - Higher latency
  - Uses leased lines, satellites

### 5. Other Network Types:
- **CAN (Campus Area Network)**: Multiple interconnected LANs within a campus
- **SAN (Storage Area Network)**: High-speed network for storage devices
- **VPN (Virtual Private Network)**: Secure network over public infrastructure

---

## Network Topologies

Network topology defines the physical or logical arrangement of network devices.

### 1. Bus Topology
- All devices connected to a single central cable (backbone)
- **Pros**: Easy to install, cost-effective
- **Cons**: Single point of failure, performance degrades with more devices

### 2. Star Topology
- All devices connected to a central hub/switch
- **Pros**: Easy to troubleshoot, failure of one device doesn't affect others
- **Cons**: Hub failure brings down entire network

### 3. Ring Topology
- Devices connected in a circular fashion
- **Pros**: Equal access for all devices
- **Cons**: Single device failure can disrupt the network

### 4. Mesh Topology
- Every device connected to every other device
- **Pros**: High redundancy and reliability
- **Cons**: Expensive, complex to install

### 5. Hybrid Topology
- Combination of two or more topologies
- **Example**: Star-Bus, Star-Ring

---

## OSI Model (Overview)

The **OSI (Open Systems Interconnection)** model is a conceptual framework with **7 layers** that standardizes network communication.

### The 7 Layers (Top to Bottom):

| Layer | Name | Function | Example Protocols/Devices |
|-------|------|----------|---------------------------|
| 7 | **Application** | User interface, network services | HTTP, FTP, SMTP, DNS |
| 6 | **Presentation** | Data formatting, encryption | SSL/TLS, JPEG, ASCII |
| 5 | **Session** | Session management | NetBIOS, RPC |
| 4 | **Transport** | End-to-end communication, reliability | TCP, UDP |
| 3 | **Network** | Routing, logical addressing | IP, ICMP, Routers |
| 2 | **Data Link** | Physical addressing, error detection | Ethernet, MAC, Switches |
| 1 | **Physical** | Bit transmission over medium | Cables, Hubs, Signals |

### Mnemonic to Remember:
**"All People Seem To Need Data Processing"** (Top to Bottom)
**"Please Do Not Throw Sausage Pizza Away"** (Bottom to Top)

### Key Concepts:
- **Encapsulation**: Each layer adds its header to data from the layer above
- **Decapsulation**: Each layer removes its header when receiving data
- **PDU (Protocol Data Unit)**: Data at each layer has a specific name
  - L7-L5: Data
  - L4: Segment (TCP) / Datagram (UDP)
  - L3: Packet
  - L2: Frame
  - L1: Bits

---

## TCP/IP Model (Overview)

The **TCP/IP (Transmission Control Protocol/Internet Protocol)** model is a practical, 4-layer model used in the Internet.

### The 4 Layers:

| Layer | Name | OSI Equivalent | Function |
|-------|------|----------------|----------|
| 4 | **Application** | L5, L6, L7 | Application services and protocols |
| 3 | **Transport** | L4 | End-to-end communication |
| 2 | **Internet** | L3 | Routing and logical addressing |
| 1 | **Network Access** | L1, L2 | Physical transmission and MAC addressing |

### Key Differences from OSI:
- More practical and widely implemented
- Fewer layers (4 vs 7)
- Developed before OSI model
- Used as the foundation of the Internet

---

## Network Devices

### 1. Hub (Layer 1)
- Broadcasts data to all connected devices
- No intelligence, no filtering
- **Use**: Legacy networks (rarely used now)

### 2. Switch (Layer 2)
- Forwards data only to the intended recipient using MAC addresses
- Creates separate collision domains
- **Use**: Modern LANs

### 3. Router (Layer 3)
- Routes data between different networks using IP addresses
- Makes intelligent forwarding decisions
- **Use**: Connecting LANs to WANs, Internet connectivity

### 4. Bridge (Layer 2)
- Connects two LANs and filters traffic
- Reduces collision domains
- **Use**: Extending network segments

### 5. Gateway (Layer 7)
- Connects networks with different protocols
- Protocol conversion
- **Use**: Connecting different network architectures

### 6. Modem
- Modulates and demodulates signals
- Converts digital to analog and vice versa
- **Use**: Internet connectivity via telephone/cable lines

### 7. Access Point (AP)
- Provides wireless connectivity
- Connects wireless devices to wired network
- **Use**: Wi-Fi networks

### 8. Firewall (Layer 3-7)
- Filters traffic based on security rules
- Protects network from unauthorized access
- **Use**: Network security

---

## IP Addressing Basics

### IPv4 (Internet Protocol version 4)

- **Format**: 32-bit address (4 bytes)
- **Notation**: Dotted decimal (e.g., 192.168.1.1)
- **Range**: 0.0.0.0 to 255.255.255.255
- **Total Addresses**: ~4.3 billion (2³²)

### IPv4 Address Classes:

| Class | Range | Default Mask | Use |
|-------|-------|--------------|-----|
| A | 1.0.0.0 - 126.255.255.255 | 255.0.0.0 (/8) | Large networks |
| B | 128.0.0.0 - 191.255.255.255 | 255.255.0.0 (/16) | Medium networks |
| C | 192.0.0.0 - 223.255.255.255 | 255.255.255.0 (/24) | Small networks |
| D | 224.0.0.0 - 239.255.255.255 | - | Multicast |
| E | 240.0.0.0 - 255.255.255.255 | - | Reserved |

### Special IP Addresses:

- **127.0.0.1**: Loopback address (localhost)
- **0.0.0.0**: Default route or unknown host
- **255.255.255.255**: Broadcast address
- **Private IP Ranges** (not routable on Internet):
  - 10.0.0.0 - 10.255.255.255 (Class A)
  - 172.16.0.0 - 172.31.255.255 (Class B)
  - 192.168.0.0 - 192.168.255.255 (Class C)

### IPv6 (Internet Protocol version 6)

- **Format**: 128-bit address (16 bytes)
- **Notation**: Hexadecimal, colon-separated (e.g., 2001:0db8:85a3::8a2e:0370:7334)
- **Total Addresses**: 340 undecillion (2¹²⁸)
- **Why IPv6?**: Address exhaustion in IPv4

### MAC Address (Physical Address)

- **Format**: 48-bit address (6 bytes)
- **Notation**: Hexadecimal (e.g., 00:1A:2B:3C:4D:5E)
- **Uniqueness**: Burned into network interface card (NIC)
- **Scope**: Layer 2 (Data Link layer)

---

## Protocols Overview

### What is a Protocol?
A set of rules and standards that define how data is transmitted and received over a network.

### Common Protocols:

**Application Layer:**
- **HTTP/HTTPS**: Web browsing
- **FTP**: File transfer
- **SMTP**: Email sending
- **POP3/IMAP**: Email receiving
- **DNS**: Domain name resolution
- **DHCP**: Dynamic IP assignment
- **SSH**: Secure remote login
- **Telnet**: Remote login (unsecure)

**Transport Layer:**
- **TCP**: Reliable, connection-oriented
- **UDP**: Unreliable, connectionless, faster

**Network Layer:**
- **IP**: Logical addressing and routing
- **ICMP**: Error reporting and diagnostics (ping)
- **ARP**: Maps IP to MAC address
- **RARP**: Maps MAC to IP address

**Data Link Layer:**
- **Ethernet**: Wired LAN protocol
- **Wi-Fi (802.11)**: Wireless LAN protocol
- **PPP**: Point-to-Point Protocol

---

## Network Performance Metrics

### 1. Bandwidth
- Maximum data transfer rate
- Measured in bps, Kbps, Mbps, Gbps

### 2. Latency (Delay)
- Time taken for data to travel from source to destination
- Measured in milliseconds (ms)
- **Types**:
  - Propagation delay
  - Transmission delay
  - Processing delay
  - Queuing delay

### 3. Throughput
- Actual data transfer rate
- Always ≤ Bandwidth

### 4. Jitter
- Variation in packet arrival time
- Important for real-time applications (VoIP, video streaming)

### 5. Packet Loss
- Percentage of packets lost during transmission
- Causes: Network congestion, errors, hardware issues

### 6. Round Trip Time (RTT)
- Time for a packet to go from source to destination and back
- Used by ping command

---

## Quick Comparison Tables

### TCP vs UDP

| Feature | TCP | UDP |
|---------|-----|-----|
| **Connection** | Connection-oriented | Connectionless |
| **Reliability** | Reliable (guaranteed delivery) | Unreliable |
| **Speed** | Slower | Faster |
| **Ordering** | Ordered delivery | No ordering |
| **Error Checking** | Extensive | Basic |
| **Use Cases** | HTTP, FTP, Email | DNS, VoIP, Gaming, Streaming |

### Circuit Switching vs Packet Switching

| Feature | Circuit Switching | Packet Switching |
|---------|-------------------|------------------|
| **Connection** | Dedicated path | Shared path |
| **Example** | Traditional telephone | Internet |
| **Efficiency** | Low (reserved bandwidth) | High (dynamic allocation) |
| **Delay** | Constant | Variable |

---

## Key Terminology

- **Protocol**: Set of rules for communication
- **Node**: Any device on a network
- **Host**: Computer or device with an IP address
- **Server**: Provides services to other devices
- **Client**: Requests services from servers
- **Peer**: Device in peer-to-peer network
- **Port**: Logical endpoint for communication (0-65535)
- **Socket**: IP address + Port number
- **Packet**: Unit of data transmitted over network
- **Frame**: Data unit at Layer 2
- **Segment**: Data unit at Layer 4
- **Collision Domain**: Network segment where collisions can occur
- **Broadcast Domain**: Network segment where broadcasts are received
- **Unicast**: One-to-one communication
- **Broadcast**: One-to-all communication
- **Multicast**: One-to-many communication
- **Subnet**: Logical subdivision of an IP network
- **Gateway**: Device connecting different networks
- **NAT (Network Address Translation)**: Maps private IPs to public IP

---

## Interview Quick Tips

### Most Asked Basics:
1. Difference between TCP and UDP
2. OSI model layers and their functions
3. Types of networks (LAN, WAN, MAN)
4. IPv4 vs IPv6
5. What is a MAC address?
6. Difference between Hub, Switch, and Router
7. What is DNS?
8. Private vs Public IP addresses
9. Network topologies

### Key Points to Remember:
- **Lower layers** (1-3) deal with hardware and routing
- **Upper layers** (4-7) deal with software and applications
- **Layer 3** (Network) uses IP addresses
- **Layer 2** (Data Link) uses MAC addresses
- **TCP** is reliable but slower; **UDP** is fast but unreliable
- **IPv4** has address exhaustion; **IPv6** solves this
- **Router** works at Layer 3; **Switch** works at Layer 2

---

## What's Next?

After mastering these basics, you should dive deeper into:
- Each OSI layer in detail
- Routing protocols (RIP, OSPF, BGP)
- Switching concepts (VLANs, STP)
- Network security (Firewalls, VPNs, encryption)
- Wireless networks (Wi-Fi standards, security)
- Advanced TCP/IP concepts (subnetting, NAT, DHCP)
- Network troubleshooting tools (ping, traceroute, netstat)

---

**Remember**: Computer Networks is a vast subject. These basics form the foundation. Understanding these concepts thoroughly will make advanced topics much easier to grasp.

**Good luck with your interview preparation! 🚀**
