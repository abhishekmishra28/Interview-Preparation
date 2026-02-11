# Different Network Architectures in Computer Networks
📌 **Network Architecture** is the complete structural and logical design of a computer network. It defines how devices are interconnected, how workloads are distributed between nodes, communication protocols to be used, and the flow of data across the network.

The choice of network architecture directly impacts the network's **performance, security, scalability, cost, and maintainability**.


---
## 📚 Broad Classification of Network Architectures
We can categorize all network architectures into 3 major groups:
| Category | Purpose |
|---|---|
| 🟢 **Core / Basic Architectures** | Foundational models that form the base of all networks |
| 🟡 **Tiered / Multi-layer Architectures** | Used for designing enterprise and web applications |
| 🔵 **Modern / Advanced Architectures** | New generation architectures used for cloud, IoT, security and large scale deployments |


---
# 🟢 Section 1: Core / Basic Network Architectures
These are the two fundamental models on which all networks are built.


---
### 1. Client-Server Architecture
> We have covered this architecture in detail in our previous lesson. Given below is a quick recap:
- It is an **asymmetric model** with 2 distinct types of nodes:
  ✅ **Client**: Initiates requests for resources
  ✅ **Server**: Listens to requests, processes them and returns response
- All clients are dependent on the central server for all resources.
#### ✅ Advantages
- Centralized data management, security and backups
- Low hardware requirement for clients (thin clients can be used)
- Easy to enforce access rules
#### ❌ Disadvantages
- Single point of failure if server goes down
- High server hardware and maintenance cost
- Network congestion if too many requests are sent to server
#### 🎯 Use Cases: Web browsing, online banking, email services, database systems.


---
### 2. Peer-to-Peer (P2P) Architecture
- It is a **symmetric model**, there is **NO CENTRAL SERVER**
- **All nodes (called peers) are equal**: every peer acts as both a client and a server. A peer can request resources from other peers, as well as serve resources to other peers.
#### Types of P2P Architecture:
| Type | Description |
|---|---|
| **Pure P2P** | No central entity at all, all peers communicate directly |
| **Hybrid P2P** | A central index server only keeps track of which peer has which file, actual file transfer happens between peers |

#### ✅ Advantages
- No single point of failure, if one peer goes down rest of the network works
- Very low setup cost, no need to buy expensive servers
- High bandwidth as load is distributed across all peers
#### ❌ Disadvantages
- No centralized security, data is distributed so risk of malware
- No guarantee of resource availability (peers can go offline)
- Difficult to take backups and enforce rules
#### 🎯 Use Cases: BitTorrent file sharing, Blockchain networks, WebRTC video calls, Tor network, Cryptocurrency networks.


---
### 3. Hybrid (Client-Server + P2P) Architecture
- Combines the best features of both Client-Server and P2P models
- Critical / sensitive operations are handled by central server, while high bandwidth operations like file transfer are done P2P between peers
#### ✅ Advantages
- High security for sensitive data from client server model
- Lower server load and cost from P2P model
#### 🎯 Use Cases: Legacy Skype calls, Spotify music streaming, modern multiplayer game servers.


---
# 🟡 Section 2: Tiered / Multi-Tier Architectures
These are layered architectures used to build enterprise applications and web services, where responsibilities are separated into different layers for easier maintenance and scalability.


---
### 1. 1-Tier (Single Tier / Monolithic) Architecture
- All 3 core components of an application: **Presentation Layer (UI), Business Logic, and Database** are installed and run on **a single physical machine**
- No network required to run the application
#### ✅ Advantages: Very fast, no network latency, extremely simple
#### ❌ Disadvantages: Not scalable, cannot be accessed by multiple users, difficult to update
#### 🎯 Use Cases: Old desktop applications, standalone ATM machines, legacy mainframe systems.


---
### 2. 2-Tier Architecture
- Split into **exactly 2 layers**:
  1.  **Client Tier (Tier 1)**: Handles UI as well as most / all of the business logic (also called Fat Client)
  2.  **Database Server (Tier 2)**: Only stores data
- Client directly communicates with the database, no middle layer.
#### ✅ Advantages: Simple to develop, fast for small number of users
#### ❌ Disadvantages: Security risks, difficult to update logic (needs update on every client machine), not scalable for thousands of users
#### 🎯 Use Cases: Old desktop based banking applications, Railway reservation systems used pre 2000s.


---
### 3. 3-Tier Architecture (Most Widely Used)
- The industry standard architecture for all modern web applications, it adds a middle layer between client and database:
  1.  🖥️ **Presentation Tier (Tier 1 / Client)**: Only handles user interface, no business logic (Thin Client e.g. Web Browser, Mobile App)
  2. ⚙️ **Application / Business Logic Tier (Tier 2 / Middle Tier)**: Handles all processing, business rules, validation, and acts as bridge between client and database
  3. 💾 **Data Tier (Tier 3)**: Stores all persistent data (Database Server)
#### ✅ Advantages
- Highly scalable, we can update business logic without touching client devices
- Better security, end users never get direct access to database
- Easy to maintain, separate teams can work on each layer
#### ❌ Disadvantages: Slightly higher latency due to extra layer, requires more hardware
#### 🎯 Use Cases: All modern websites, e-commerce platforms like Amazon, e-learning platforms.


---
### 4. N-Tier / Multi-Tier Architecture
- Extended version of 3-tier architecture, with additional specialized layers added for performance and scalability for very large scale applications.
Common additional layers include:
✅ Load Balancer layer
✅ CDN / Cache layer (Redis, Cloudflare)
✅ API Gateway layer
✅ Microservices layers
✅ Backup and Disaster recovery layer
#### ✅ Advantages: Extremely scalable, high fault tolerance, optimized performance
#### 🎯 Use Cases: Large scale platforms like Netflix, Google, Instagram, SaaS products.


---
# 🔵 Section 3: Modern / Advanced Network Architectures
These are new generation architectures used for modern deployments of cloud, IoT, security and 5G networks.


---
### 1. Software Defined Networking (SDN) Architecture
- Traditional network devices (routers, switches) have both **Control Plane** (takes routing / traffic management decisions) and **Data Plane** (forwards actual data packets) built into the hardware.
- SDN **separates these two planes**:
  - Control Plane is moved to a **centralized, programmable software controller**
  - All switches / routers only have Data Plane, they follow instructions sent by the central controller
#### ✅ Advantages: Fully programmable, easy to manage large networks, dynamic traffic routing, lower cost
#### 🎯 Use Cases: Data center networks, Cloud service provider networks, 5G core networks.


---
### 2. Zero Trust Architecture (ZTA)
- 📌 Core Principle: **Never Trust, Always Verify**
- Traditional network security trusts all devices inside the internal network by default. ZTA removes this implicit trust.
- Every device, user and request (even if coming from inside the office network) is authenticated and authorized before getting access to resources.
#### ✅ Advantages: Extremely secure, prevents internal data breaches, works well for remote work culture
#### 🎯 Use Cases: All modern enterprise networks, banking, government networks.


---
### 3. Microservices Architecture
- Instead of building the entire application as a single monolithic code, the application is broken into **small, independent, loosely coupled services**, each responsible for only one function.
- Each microservice runs on its own separate server, and all services communicate with each other using REST APIs or message queues.
#### ✅ Advantages: We can update / scale one service without affecting rest of the application, very high uptime
#### 🎯 Use Cases: Netflix, Amazon, Flipkart, all modern SaaS products.


---
### 4. Service Oriented Architecture (SOA)
- Predecessor of Microservices architecture, mostly used in enterprise systems.
- Applications are built using **reusable, platform independent services** that communicate with each other via a central component called **Enterprise Service Bus (ESB)**.


---
### 5. Edge Computing Architecture
- Instead of processing all data in a central cloud server located thousands of kilometers away, **data processing and storage is done as close as possible to the end user / end device**.
#### ✅ Advantages: Extremely low latency, reduces load on central cloud, lower bandwidth cost
#### 🎯 Use Cases: IoT devices, 5G applications, Live video streaming, Self driving cars, AR/VR.


---
### 6. Fog Computing Architecture
- An intermediate layer between Edge devices and Central Cloud.
- Fog nodes are deployed at the ISP / local network level to process time sensitive data, while non time sensitive data is sent to cloud for long term storage and analysis. Mostly used for large scale IoT deployments.


---
### 7. Cloud Network Architecture
- Network design for delivering computing resources over internet instead of local on premise servers. Classified based on deployment:
  - **Public Cloud**: Resources owned by third party provider (AWS, GCP, Azure)
  - **Private Cloud**: Cloud resources used exclusively by one organization
  - **Hybrid Cloud**: Combination of Public + Private cloud
  - **Multi Cloud**: Using services from multiple cloud providers.


---
## 📊 Quick Comparison: Client Server vs P2P
| Parameter | Client-Server | Peer to Peer |
|---|---|---|
| Central Server | Present | Absent |
| Node Roles | Asymmetric (Client requests, Server serves) | Symmetric (All nodes are both client and server) |
| Single Point of Failure | Yes (Server) | No |
| Security | High (Centralized) | Low (Distributed) |
| Cost | High (Server cost) | Low |
| Scalability | Vertically Scalable | Horizontally Scalable |
| Best for | Banking, Web services | File sharing, Blockchain |


---
# 🎯 30 Multiple Choice Questions (MCQs) on Network Architectures


---
### Basic Concepts
```
**1. Which of the following is an asymmetric network architecture where there is separate client and server nodes?**
a) P2P
b) Client-Server
c) Mesh
d) All of the above

**2. In Peer to Peer architecture:**
a) There is a central server
b) All nodes act as both client and server
c) Nodes cannot share resources with each other
d) All data is stored in central location

**3. Which architecture has no single point of failure?**
a) Client Server
b) P2P
c) 2 Tier
d) All of the above

**4. Hybrid network architecture is a combination of?**
a) Star and Bus topology
b) Client Server and P2P
c) SDN and Zero Trust
d) Edge and Fog computing

**5. 1 Tier Monolithic architecture has:**
a) All components UI, Logic, Database on same machine
b) Client and Database server
c) 3 separate layers
d) Multiple microservices

**6. How many layers are present in a standard 3-Tier architecture?**
a) 2
b) 3
c) 4
d) 7

**7. The middle layer in 3-Tier architecture is?**
a) Presentation layer
b) Business Logic / Application layer
c) Data layer
d) Cache layer

**8. Which tier in 3-tier architecture is accessed directly by the end user?**
a) Data Tier
b) Application Tier
c) Presentation Tier
d) All of the above

**9. Which of the following is a disadvantage of 2-Tier architecture?**
a) Very high latency
b) Business logic needs to be updated on every client machine
c) Requires 3 separate servers
d) Not usable for desktop applications

**10. N-Tier architecture is an extended version of:**
a) 1 Tier
b) 2 Tier
c) 3 Tier
d) P2P
```

---
### Advanced Concepts
```
**11. Software Defined Networking (SDN) separates:**
a) Client and Server
b) Control Plane and Data Plane
c) Edge and Cloud
d) Presentation and Logic layer

**12. What is the core principle of Zero Trust Architecture?**
a) Always trust devices inside internal network
b) Never Trust, Always Verify
c) All requests must be served from edge
d) All data must be stored in cloud

**13. In SDN architecture, the control plane is managed by:**
a) Router hardware
b) Centralized software controller
c) End user client
d) Database server

**14. Microservices architecture is best described as:**
a) Single monolithic application
b) Application split into small independent services communicating via APIs
c) 2 tier architecture
d) Pure P2P architecture

**15. Edge Computing processes data:**
a) In central cloud server
b) As close as possible to the end user / device
c) In fog nodes
d) In database server

**16. Fog computing is a layer between:**
a) Client and Server
b) Edge devices and Central Cloud
c) 2 tier and 3 tier architecture
d) SDN controller and switches

**17. Which of the following is an example of P2P application?**
a) Loading google.com
b) BitTorrent File Sharing
c) Online Net Banking
d) Checking email

**18. Which architecture is most suitable for very large web applications like Netflix?**
a) 1 Tier
b) 2 Tier
c) N-Tier / Microservices
d) Pure P2P

**19. In 3 Tier architecture, end user never gets direct access to:**
a) Presentation layer
b) Application layer
c) Database layer
d) All of the above

**20. Service Oriented Architecture (SOA) uses which central component for communication between services?**
a) API Gateway
b) Enterprise Service Bus (ESB)
c) Load Balancer
d) Cache Server
```

---
### Application based Questions
```
**21. Blockchain and Crypto currency networks use which architecture?**
a) Client Server
b) Peer to Peer
c) 3 Tier
d) SDN

**22. Old desktop based railway reservation system where client directly connects to database is an example of?**
a) 1 Tier
b) 2 Tier
c) 3 Tier
d) N Tier

**23. Self driving cars require very low latency processing, which architecture is best suited for this?**
a) Cloud Computing
b) Edge Computing
c) Fog Computing
d) Client Server

**24. Which architecture is used to prevent internal data breaches in enterprise networks?**
a) SDN
b) Zero Trust Architecture
c) Microservices
d) P2P

**25. BitTorrent uses which type of P2P architecture mostly?**
a) Pure P2P
b) Hybrid P2P
c) 3 Tier
d) Client Server

**26. Which of the following is NOT an advantage of Microservices architecture?**
a) We can scale individual services
b) Updating one service does not affect entire application
c) Very high uptime
d) Requires no network communication between services

**27. When you access an e-commerce website, which architecture are you most likely using?**
a) 2 Tier
b) 3 Tier / N Tier
c) Pure P2P
d) 1 Tier

**28. SDN is mostly used in:**
a) Home networks
b) Data center and cloud provider networks
c) Small office networks
d) P2P file sharing networks

**29. Which of the following is a disadvantage of P2P architecture?**
a) Single point of failure
b) No centralized security management
c) Very high cost
d) Low bandwidth

**30. The thin client model is a feature of which architecture?**
a) 2 Tier Architecture
b) 3 Tier Architecture
c) 1 Tier Architecture
d) P2P Architecture
```

---
## ✅ Answer Key
| Q | Answer | Q | Answer | Q | Answer |
|---|--------|---|--------|---|--------|
| 1 | b | 11 | b | 21 | b |
| 2 | b | 12 | b | 22 | b |
| 3 | b | 13 | b | 23 | b |
| 4 | b | 14 | b | 24 | b |
| 5 | a | 15 | b | 25 | b |
| 6 | b | 16 | b | 26 | d |
| 7 | b | 17 | b | 27 | b |
| 8 | c | 18 | c | 28 | b |
| 9 | b | 19 | c | 29 | b |
| 10 | c | 20 | b | 30 | b |
