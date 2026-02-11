# **Network Topologies in Computer Networks**

Network topology refers to the **physical or logical arrangement** of nodes (devices) and connections in a computer network. It defines how data flows between devices, affecting **performance, scalability, fault tolerance, and cost**.

---

## **1. Types of Network Topologies**

### **A. Physical Topology**
Describes the **physical layout** of cables, switches, routers, and devices.

### **B. Logical Topology**
Describes how **data flows** within the network, regardless of physical connections.

---

## **2. Common Network Topologies**

### **1. Bus Topology**
- **Definition:** All devices are connected to a **single central cable (backbone)**.
- **Data Flow:** Data travels in **both directions** until it reaches the destination.
- **Terminators:** Required at both ends to prevent signal reflection.

#### **Advantages:**
✅ **Easy to install & cost-effective** (less cabling).
✅ **Good for small networks** (LANs).

#### **Disadvantages:**
❌ **Single point of failure** (if the backbone fails, the whole network fails).
❌ **Performance degrades with more devices** (collisions increase).
❌ **Difficult to troubleshoot** (finding faults is hard).

#### **Example:**
- **Ethernet (10Base-2, 10Base-5)** – Older LANs.

---

### **2. Star Topology**
- **Definition:** All devices are connected to a **central hub/switch**.
- **Data Flow:** Data passes through the **central node** before reaching the destination.

#### **Advantages:**
✅ **Easy to install & manage** (centralized control).
✅ **Fault-tolerant** (if one cable fails, others remain unaffected).
✅ **High performance** (no data collisions).
✅ **Scalable** (easy to add/remove devices).

#### **Disadvantages:**
❌ **Single point of failure** (if the central hub/switch fails, the whole network fails).
❌ **More cabling required** (higher cost).

#### **Example:**
- **Modern Ethernet LANs (10Base-T, 100Base-TX)**.
- **Home Wi-Fi networks (router as the central node)**.

---

### **3. Ring Topology**
- **Definition:** Devices are connected in a **closed loop**, where each device is connected to **two neighbors**.
- **Data Flow:** Data travels in **one direction (unidirectional)** or **both directions (bidirectional)**.

#### **Advantages:**
✅ **No central node** (no single point of failure).
✅ **Good for high-speed networks** (Token Ring).
✅ **Predictable performance** (no collisions).

#### **Disadvantages:**
❌ **If one node fails, the whole network can fail** (unless dual-ring is used).
❌ **Difficult to troubleshoot & reconfigure**.
❌ **Slower than star topology** (data must pass through multiple nodes).

#### **Example:**
- **Token Ring (IEEE 802.5)**.
- **Fiber Distributed Data Interface (FDDI)**.

---

### **4. Mesh Topology**
- **Definition:** Every device is connected to **every other device** (fully connected).
- **Data Flow:** Multiple paths exist for data transmission.

#### **Types:**
- **Full Mesh:** Every node is connected to every other node.
- **Partial Mesh:** Some nodes are connected to all, while others are connected to only a few.

#### **Advantages:**
✅ **Highly fault-tolerant** (multiple paths for data).
✅ **No single point of failure**.
✅ **High security & privacy** (direct connections).
✅ **Good for large networks** (WANs, Internet).

#### **Disadvantages:**
❌ **Expensive** (requires a lot of cabling & ports).
❌ **Complex to install & manage**.
❌ **High maintenance**.

#### **Example:**
- **Internet (partial mesh)**.
- **Military & banking networks (full mesh)**.

---

### **5. Tree (Hierarchical) Topology**
- **Definition:** A **hybrid of star and bus topologies**, where multiple star networks are connected to a **central bus backbone**.
- **Data Flow:** Data flows **hierarchically** (parent-child relationship).

#### **Advantages:**
✅ **Scalable** (easy to add more star networks).
✅ **Fault isolation** (if one branch fails, others remain unaffected).
✅ **Good for large networks** (corporate LANs).

#### **Disadvantages:**
❌ **If the backbone fails, the whole network fails**.
❌ **Complex to configure & maintain**.
❌ **Expensive** (more cabling & hardware).

#### **Example:**
- **Campus networks (multiple buildings connected via a backbone)**.
- **ISP networks**.

---

### **6. Hybrid Topology**
- **Definition:** A **combination of two or more topologies** (e.g., star + bus, star + ring).
- **Data Flow:** Depends on the combined topologies.

#### **Advantages:**
✅ **Flexible & scalable** (can be customized for needs).
✅ **Fault-tolerant** (if one part fails, others keep working).
✅ **Optimized performance** (can use the best features of each topology).

#### **Disadvantages:**
❌ **Complex to design & manage**.
❌ **Expensive** (requires more hardware & cabling).

#### **Example:**
- **Corporate networks (star + mesh)**.
- **University networks (tree + star)**.

---

## **3. Comparison of Network Topologies**

| **Topology**  | **Fault Tolerance** | **Scalability** | **Cost** | **Complexity** | **Best For** |
|--------------|-------------------|----------------|---------|---------------|-------------|
| **Bus**      | ❌ Low            | ❌ Low         | ✅ Low  | ✅ Low        | Small LANs  |
| **Star**     | ✅ High           | ✅ High        | ❌ High | ✅ Low        | Home/Office LANs |
| **Ring**     | ⚠️ Medium         | ⚠️ Medium      | ⚠️ Medium | ⚠️ Medium    | Token Ring, FDDI |
| **Mesh**     | ✅ Very High      | ✅ Very High   | ❌ Very High | ❌ High   | Internet, Military |
| **Tree**     | ⚠️ Medium         | ✅ High        | ❌ High | ⚠️ Medium    | Corporate LANs |
| **Hybrid**   | ✅ High           | ✅ High        | ❌ High | ❌ High       | Large Networks |

---

## **4. Logical vs. Physical Topology**

| **Aspect**       | **Physical Topology** | **Logical Topology** |
|-----------------|----------------------|----------------------|
| **Definition**  | How devices are **physically connected** (cables, switches). | How **data flows** in the network. |
| **Example**     | Star (devices connected to a switch). | Bus (data flows sequentially). |
| **Change Impact** | Requires rewiring. | Can be changed via software (e.g., VLANs). |
| **Common Types** | Bus, Star, Ring, Mesh, Tree. | Ethernet (Bus), Token Ring (Ring). |

---

## **5. 30 MCQs on Network Topologies**

### **Section 1: Basic Concepts**

**1. What is a network topology?**
a) The speed of data transmission
b) The arrangement of nodes and connections in a network
c) The type of cables used
d) The operating system of the network

**2. Which topology uses a single central cable to connect all devices?**
a) Star
b) Ring
c) Bus
d) Mesh

**3. In which topology does every device connect to a central hub/switch?**
a) Bus
b) Star
c) Ring
d) Mesh

**4. Which topology forms a closed loop where each device connects to two neighbors?**
a) Bus
b) Star
c) Ring
d) Tree

**5. What is the main disadvantage of a bus topology?**
a) High cost
b) Single point of failure (backbone)
c) Complex installation
d) Slow data transfer

**6. Which topology is the most fault-tolerant?**
a) Bus
b) Star
c) Ring
d) Mesh

**7. What is the primary advantage of a star topology?**
a) Low cost
b) Easy to install and manage
c) No central point of failure
d) Works without electricity

**8. Which topology is best for large networks like the Internet?**
a) Bus
b) Star
c) Mesh
d) Ring

**9. What happens if the central hub fails in a star topology?**
a) Only one device fails
b) The entire network fails
c) Data is rerouted automatically
d) The network switches to bus topology

**10. Which topology is a combination of star and bus topologies?**
a) Ring
b) Mesh
c) Tree
d) Hybrid

---

### **Section 2: Data Flow & Performance**

**11. In a bus topology, how does data travel?**
a) Through a central hub
b) In one direction only
c) In both directions until it reaches the destination
d) Only to the nearest neighbor

**12. Which topology uses a "token" to control data transmission?**
a) Bus
b) Star
c) Ring
d) Mesh

**13. What is the main advantage of a ring topology over a bus topology?**
a) Lower cost
b) No collisions (predictable performance)
c) Easier to install
d) Works with wireless networks

**14. In a mesh topology, how many connections does each device have in a fully connected network?**
a) 1
b) 2
c) Depends on the number of devices
d) None

**15. Which topology is most affected by network congestion?**
a) Star
b) Mesh
c) Bus
d) Tree

**16. What is the main disadvantage of a mesh topology?**
a) Low fault tolerance
b) High cost and complexity
c) Slow data transfer
d) Requires a central hub

**17. Which topology is best for a small office with 5 computers?**
a) Bus
b) Star
c) Ring
d) Mesh

**18. What is the role of terminators in a bus topology?**
a) To boost signal strength
b) To prevent signal reflection
c) To connect devices
d) To encrypt data

**19. Which topology allows data to take multiple paths?**
a) Bus
b) Star
c) Ring
d) Mesh

**20. What is the primary difference between physical and logical topology?**
a) Physical = cables, Logical = data flow
b) Physical = software, Logical = hardware
c) Physical = wireless, Logical = wired
d) No difference

---

### **Section 3: Advanced Concepts**

**21. Which topology is used in modern Ethernet LANs?**
a) Bus
b) Star
c) Ring
d) Mesh

**22. What is a "partial mesh" topology?**
a) Every device connects to every other device
b) Some devices connect to all, while others connect to only a few
c) Devices connect in a ring
d) Devices connect to a central hub

**23. Which topology is most commonly used in home Wi-Fi networks?**
a) Bus
b) Star
c) Ring
d) Mesh

**24. What is the main advantage of a tree topology?**
a) Low cost
b) Scalability and fault isolation
c) No central point of failure
d) Works without electricity

**25. Which topology is used in Token Ring networks?**
a) Bus
b) Star
c) Ring
d) Mesh

**26. What happens if one node fails in a ring topology?**
a) The entire network fails
b) Only that node is affected
c) Data is rerouted automatically
d) The network switches to bus mode

**27. Which topology is best for a university campus network?**
a) Bus
b) Star
c) Tree
d) Mesh

**28. What is the main disadvantage of a hybrid topology?**
a) Low fault tolerance
b) High cost and complexity
c) Slow data transfer
d) Requires a central hub

**29. Which topology is used in Fiber Distributed Data Interface (FDDI)?**
a) Bus
b) Star
c) Ring
d) Mesh

**30. What is the primary reason for using a mesh topology in military networks?**
a) Low cost
b) High fault tolerance and security
c) Easy installation
d) Works with wireless networks

---

### **Answer Key**

| Q | Ans | Q | Ans | Q | Ans |
|---|-----|---|-----|---|-----|
| 1 | b   | 11| c   | 21| b   |
| 2 | c   | 12| c   | 22| b   |
| 3 | b   | 13| b   | 23| b   |
| 4 | c   | 14| c   | 24| b   |
| 5 | b   | 15| c   | 25| c   |
| 6 | d   | 16| b   | 26| a   |
| 7 | b   | 17| b   | 27| c   |
| 8 | c   | 18| b   | 28| b   |
| 9 | b   | 19| d   | 29| c   |
| 10| c   | 20| a   | 30| b   |

---

## **6. Summary**
- **Bus:** Simple, cheap, but prone to failures.
- **Star:** Most common, easy to manage, but depends on a central hub.
- **Ring:** Predictable, but one failure can break the network.
- **Mesh:** Highly reliable, but expensive and complex.
- **Tree:** Scalable, but backbone failure affects the whole network.
- **Hybrid:** Flexible, but complex and costly.

Understanding these topologies helps in **designing, troubleshooting, and optimizing** computer networks effectively. 🚀
