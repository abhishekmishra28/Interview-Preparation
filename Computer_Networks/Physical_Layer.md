# Physical Layer - In-Depth Notes

## Table of Contents
1. [Introduction to Physical Layer](#introduction-to-physical-layer)
2. [Functions of Physical Layer](#functions-of-physical-layer)
3. [Transmission Media](#transmission-media)
4. [Data Encoding and Modulation](#data-encoding-and-modulation)
5. [Transmission Modes](#transmission-modes)
6. [Transmission Impairments](#transmission-impairments)
7. [Switching Techniques](#switching-techniques)
8. [Multiplexing](#multiplexing)
9. [Casting Types](#casting-types)
10. [Physical Layer Devices](#physical-layer-devices)
11. [Standards and Protocols](#standards-and-protocols)
12. [Important Formulas and Calculations](#important-formulas-and-calculations)
13. [Interview Questions](#interview-questions)

---

## Introduction to Physical Layer

### Definition
The **Physical Layer** is the **first and lowest layer** of the OSI model. It deals with the physical connection between devices and the transmission of raw binary data (0s and 1s) over the physical medium.

### Position in OSI Model
```
┌─────────────────────────┐
│   Application Layer     │ Layer 7
├─────────────────────────┤
│   Presentation Layer    │ Layer 6
├─────────────────────────┤
│   Session Layer         │ Layer 5
├─────────────────────────┤
│   Transport Layer       │ Layer 4
├─────────────────────────┤
│   Network Layer         │ Layer 3
├─────────────────────────┤
│   Data Link Layer       │ Layer 2
├─────────────────────────┤
│ ▶ PHYSICAL LAYER ◀      │ Layer 1  ← Deals with BITS
└─────────────────────────┘
```

### Key Characteristics
- **PDU (Protocol Data Unit)**: **Bits** (0s and 1s)
- **Addressing**: No logical addressing (uses physical connections)
- **Main Focus**: How bits are transmitted over a medium
- **Hardware Level**: Deals with cables, connectors, voltages, frequencies

### What Physical Layer Does NOT Do
❌ Error correction
❌ Flow control
❌ Routing
❌ Logical addressing
✅ Only transmits raw bits

---

## Functions of Physical Layer

### 1. **Bit Representation**
- Defines how bits (0 and 1) are represented
- **Methods**:
  - Electrical signals (voltage levels) - for copper cables
  - Light pulses - for fiber optic cables
  - Radio waves - for wireless transmission

**Example**:
```
Bit 1 = +5V or High voltage
Bit 0 = 0V or Low voltage
```

### 2. **Data Rate (Bit Rate)**
- Determines the number of bits transmitted per second
- Measured in **bps (bits per second)**
- Also called **bandwidth** or **transmission speed**

**Examples**:
- Ethernet: 10 Mbps, 100 Mbps, 1 Gbps, 10 Gbps
- Wi-Fi 6: Up to 9.6 Gbps

### 3. **Synchronization**
- Ensures sender and receiver clocks are synchronized
- **Types**:
  - **Synchronous**: Sender and receiver share a common clock
  - **Asynchronous**: No shared clock; uses start and stop bits

### 4. **Physical Topology**
- Defines how devices are physically connected
- Types: Bus, Star, Ring, Mesh, Hybrid

### 5. **Transmission Mode**
- Defines the direction of data flow
- Types: Simplex, Half-Duplex, Full-Duplex

### 6. **Line Configuration**
- **Point-to-Point**: Direct connection between two devices
- **Multipoint**: Multiple devices share a single link

### 7. **Interface and Connector Specification**
- Defines mechanical and electrical specifications
- Examples: RJ-45, USB, HDMI, Fiber connectors (SC, ST, LC)

### 8. **Signal Conversion**
- Converts digital data to analog signals (modulation)
- Converts analog signals to digital data (demodulation)

---

## Transmission Media

Transmission media is the physical path through which data travels from sender to receiver.

### Classification

```
Transmission Media
│
├── Guided Media (Wired)
│   ├── Twisted Pair Cable
│   │   ├── UTP (Unshielded)
│   │   └── STP (Shielded)
│   ├── Coaxial Cable
│   └── Fiber Optic Cable
│       ├── Single Mode
│       └── Multi Mode
│
└── Unguided Media (Wireless)
    ├── Radio Waves
    ├── Microwaves
    │   ├── Terrestrial
    │   └── Satellite
    └── Infrared
```

---

### A. Guided Media (Wired)

#### 1. **Twisted Pair Cable**

**Structure**: Two insulated copper wires twisted together to reduce electromagnetic interference (EMI).

**Types**:

##### a) **UTP (Unshielded Twisted Pair)**
- No additional shielding
- Most common in LANs
- **Categories**:
  - **Cat 5**: 100 Mbps, 100 MHz
  - **Cat 5e**: 1 Gbps, 100 MHz (enhanced Cat 5)
  - **Cat 6**: 1 Gbps, 250 MHz
  - **Cat 6a**: 10 Gbps, 500 MHz
  - **Cat 7**: 10 Gbps, 600 MHz (shielded)
  - **Cat 8**: 40 Gbps, 2000 MHz

##### b) **STP (Shielded Twisted Pair)**
- Has metal foil or braided mesh covering
- Better protection against EMI
- More expensive than UTP
- Used in industrial environments

**Characteristics**:
- **Connector**: RJ-45 (8P8C)
- **Maximum Length**: 100 meters (for Ethernet)
- **Bandwidth**: Up to 1 GHz (Cat 8)
- **Cost**: Low to Medium

**Advantages**:
✅ Cheap and easy to install
✅ Flexible
✅ Wide compatibility

**Disadvantages**:
❌ Limited distance (100m)
❌ Susceptible to EMI (UTP)
❌ Lower bandwidth compared to fiber

**Use Cases**:
- Ethernet LANs
- Telephone lines
- Home and office networking

---

#### 2. **Coaxial Cable**

**Structure**: 
- Central copper conductor
- Insulating layer
- Metallic shield (braided or foil)
- Outer plastic jacket

```
   Outer Jacket
        │
   ┌────┴────┐
   │ Shield  │
   │ ┌───┐   │
   │ │Ins│   │
   │ │ ┌┴┐  │
   │ │ │C│  │  C = Conductor
   │ │ └─┘  │
   │ └───┘   │
   └─────────┘
```

**Types**:
- **Thinnet (10Base2)**: 185 meters max
- **Thicknet (10Base5)**: 500 meters max
- **RG-6**: Cable TV, Internet
- **RG-59**: CCTV cameras

**Characteristics**:
- **Connector**: BNC, F-type
- **Bandwidth**: Up to 1 GHz
- **Impedance**: 50Ω or 75Ω

**Advantages**:
✅ Better shielding than twisted pair
✅ Higher bandwidth
✅ Longer distance than twisted pair

**Disadvantages**:
❌ More expensive than twisted pair
❌ Less flexible
❌ Bulkier

**Use Cases**:
- Cable TV
- Broadband internet
- Legacy Ethernet (mostly replaced)

---

#### 3. **Fiber Optic Cable**

**Structure**: Uses light pulses to transmit data through glass or plastic fibers.

```
Core → Cladding → Buffer → Jacket
 │        │         │        │
 └─ Light travels here
```

**Components**:
1. **Core**: Central glass fiber (carries light)
2. **Cladding**: Surrounds core, reflects light back
3. **Buffer**: Protects fiber from damage
4. **Jacket**: Outer protective layer

**Types**:

##### a) **Single Mode Fiber (SMF)**
- **Core Diameter**: 8-10 micrometers (very thin)
- **Light Source**: Laser
- **Distance**: Up to 100+ km
- **Bandwidth**: Very high (up to 100 Gbps+)
- **Cost**: More expensive
- **Use**: Long-distance, WAN, Internet backbone

##### b) **Multi Mode Fiber (MMF)**
- **Core Diameter**: 50-62.5 micrometers
- **Light Source**: LED
- **Distance**: Up to 2 km
- **Bandwidth**: High (up to 10 Gbps)
- **Cost**: Less expensive than SMF
- **Use**: LANs, short-distance connections

**Comparison**:

| Feature | Single Mode | Multi Mode |
|---------|-------------|------------|
| Core Size | 8-10 μm | 50-62.5 μm |
| Light Source | Laser | LED |
| Distance | 100+ km | Up to 2 km |
| Bandwidth | Higher | Lower |
| Cost | High | Medium |
| Dispersion | Low | High |

**Advantages**:
✅ Immune to EMI
✅ Very high bandwidth
✅ Long-distance transmission
✅ Secure (difficult to tap)
✅ Low attenuation

**Disadvantages**:
❌ Expensive
❌ Difficult to install and splice
❌ Fragile
❌ Requires specialized equipment

**Connectors**:
- **SC (Subscriber Connector)**: Push-pull connector
- **ST (Straight Tip)**: Bayonet-style connector
- **LC (Lucent Connector)**: Small form-factor
- **MTRJ**: Small form-factor with dual fibers

**Use Cases**:
- Internet backbone
- Submarine cables
- Data centers
- High-speed LANs
- Telecom networks

---

### B. Unguided Media (Wireless)

Wireless transmission uses electromagnetic waves through air or space.

#### 1. **Radio Waves**

**Frequency Range**: 3 kHz to 1 GHz

**Characteristics**:
- Omnidirectional (travels in all directions)
- Can penetrate walls
- Long-distance transmission
- Susceptible to interference

**Types**:
- **AM Radio**: 540-1600 kHz
- **FM Radio**: 88-108 MHz
- **TV Broadcasting**: 54-890 MHz

**Advantages**:
✅ Long-range
✅ Can penetrate obstacles
✅ Easy to generate

**Disadvantages**:
❌ Interference from other sources
❌ Security concerns (easy to intercept)
❌ Licensing required for some bands

**Use Cases**:
- Radio broadcasting
- Amateur radio
- Paging systems
- Cordless phones

---

#### 2. **Microwaves**

**Frequency Range**: 1 GHz to 300 GHz

**Characteristics**:
- Unidirectional (requires line-of-sight)
- High frequency, high bandwidth
- Limited by curvature of Earth

**Types**:

##### a) **Terrestrial Microwave**
- Point-to-point communication
- Uses parabolic antennas (dishes)
- **Distance**: Up to 50 km between towers
- **Frequency**: 2-40 GHz

**Use Cases**:
- Telecommunication
- Mobile phone towers
- Television broadcasting

##### b) **Satellite Microwave**
- Communication via satellites
- Covers large geographical areas
- **Types of Satellites**:
  - **GEO (Geostationary)**: 36,000 km altitude, fixed position
  - **MEO (Medium Earth Orbit)**: 2,000-36,000 km
  - **LEO (Low Earth Orbit)**: 500-2,000 km

**Frequency Bands**:
- **C-Band**: 4-8 GHz
- **Ku-Band**: 12-18 GHz
- **Ka-Band**: 26-40 GHz

**Advantages**:
✅ High bandwidth
✅ Long-distance
✅ Wide coverage (satellites)

**Disadvantages**:
❌ Requires line-of-sight
❌ Expensive installation
❌ Weather-dependent
❌ High latency (satellites)

**Use Cases**:
- Satellite TV
- GPS
- Satellite internet
- Long-distance phone calls

---

#### 3. **Infrared**

**Frequency Range**: 300 GHz to 400 THz

**Characteristics**:
- Very short range (few meters)
- Cannot penetrate walls
- Unidirectional (requires alignment)
- High frequency

**Advantages**:
✅ Secure (cannot penetrate walls)
✅ No licensing required
✅ High bandwidth

**Disadvantages**:
❌ Short range
❌ Cannot penetrate obstacles
❌ Requires line-of-sight
❌ Affected by sunlight

**Use Cases**:
- TV remotes
- Wireless keyboards/mice
- IrDA (Infrared Data Association)
- Short-range data transfer

---

### Comparison: Guided vs Unguided Media

| Feature | Guided | Unguided |
|---------|--------|----------|
| **Medium** | Physical cables | Air/Space |
| **Direction** | Directed | Broadcast |
| **Security** | More secure | Less secure |
| **Installation** | Complex | Easy |
| **Cost** | Higher (cables) | Lower |
| **Interference** | Less susceptible | More susceptible |
| **Bandwidth** | Higher (fiber) | Lower |

---

## Data Encoding and Modulation

### Digital-to-Digital Encoding

Converts digital data to digital signals.

#### 1. **Unipolar Encoding**
- Only one voltage level
- Positive voltage = 1, Zero voltage = 0
- **Problem**: DC component, synchronization issues

```
   1    0    1    1    0
   ▄         ▄    ▄    
   █         █    █    
───┴─────────┴────┴────────
```

#### 2. **Polar Encoding**

Uses two voltage levels: positive and negative.

##### a) **NRZ (Non-Return to Zero)**

**NRZ-L (Level)**:
- Positive voltage = 0
- Negative voltage = 1
- **Problem**: Synchronization for long sequences

```
   0    1    1    0    1
   ▄              ▄    
───┴────▄▄▄▄▄▄────┴────▄▄
        █    █         █
```

**NRZ-I (Invert)**:
- Transition at start of bit = 1
- No transition = 0
- Better for synchronization

##### b) **RZ (Return to Zero)**
- Signal returns to zero in middle of bit period
- Better synchronization
- Requires more bandwidth

```
   1    0    1    1    0
   ▄         ▄    ▄    
   █▄        █▄   █▄   
───┴─────────┴────┴────────
```

##### c) **Manchester Encoding**
- Transition in middle of bit period
- 0 = High to Low
- 1 = Low to High
- **Used in**: Ethernet (10 Mbps)
- **Advantage**: Self-clocking (easy synchronization)

```
   0    1    1    0    1
   ▄    ▄▄   ▄▄   ▄    ▄▄
   █▄     █▄   █▄ █▄     █▄
───┴─────┴────┴───┴────┴───
   H→L  L→H  L→H H→L  L→H
```

##### d) **Differential Manchester**
- Transition at middle for clocking
- 0 = Transition at start
- 1 = No transition at start
- **Used in**: Token Ring

#### 3. **Bipolar Encoding (AMI)**

**AMI (Alternate Mark Inversion)**:
- 0 = Zero voltage
- 1 = Alternating positive and negative

```
   0    1    1    0    1
        ▄              ▄
────────┴────▄▄────────┴──
             █
   0   +V   -V    0   +V
```

**Advantages**:
✅ No DC component
✅ Error detection (consecutive same voltage)

---

### Digital-to-Analog Modulation

Converts digital data to analog signals (for transmission over analog medium like telephone lines).

#### Modulation Techniques:

#### 1. **ASK (Amplitude Shift Keying)**
- Varies amplitude of carrier signal
- 0 = Low amplitude or no signal
- 1 = High amplitude

```
Digital:  0    1    1    0    1
          ▄    ▄    ▄    ▄    
Analog:  ╱╲  ╱╲╱╲╱╲╱╲  ╱╲╱╲
         ╲╱  ╲     ╱  ╲╱
```

**Use**: Simple, but susceptible to noise

#### 2. **FSK (Frequency Shift Keying)**
- Varies frequency of carrier signal
- 0 = Low frequency
- 1 = High frequency

```
Digital:  0      1      1      0
         
Analog:  ╱╲╱╲  ╱╲╱╲╱╲  ╱╲╱╲╱╲  ╱╲╱╲
         ╲╱╲╱  ╲     ╱  ╲     ╱  ╲╱╲╱
        low f  high f  high f  low f
```

**Use**: More robust than ASK
**Example**: Modems, caller ID

#### 3. **PSK (Phase Shift Keying)**
- Varies phase of carrier signal
- 0 = 0° phase
- 1 = 180° phase shift

**BPSK (Binary PSK)**: 2 phases (0°, 180°)
**QPSK (Quadrature PSK)**: 4 phases (0°, 90°, 180°, 270°) - transmits 2 bits
**8-PSK**: 8 phases - transmits 3 bits

**Use**: Most efficient, used in Wi-Fi, satellite

#### 4. **QAM (Quadrature Amplitude Modulation)**
- Combines ASK and PSK
- Varies both amplitude and phase
- **Types**: 16-QAM, 64-QAM, 256-QAM, 1024-QAM

**Use**: Cable modems, Wi-Fi, 4G/5G

---

### Analog-to-Digital Conversion

#### **PCM (Pulse Code Modulation)**

Process:
1. **Sampling**: Convert continuous signal to discrete samples
   - **Nyquist Theorem**: Sampling rate ≥ 2 × Maximum frequency
2. **Quantization**: Round samples to discrete levels
3. **Encoding**: Convert to binary

**Example**:
- Voice signal: 4 kHz bandwidth
- Sampling rate: 8 kHz (2 × 4 kHz)
- 8 bits per sample
- **Bit rate** = 8,000 × 8 = 64 kbps

---

## Transmission Modes

### Based on Direction of Data Flow

#### 1. **Simplex**
- **One-way** communication only
- Data flows in only one direction
- No feedback channel

```
Sender ────────────────> Receiver
       (One direction only)
```

**Examples**:
- Keyboard to computer
- Mouse to computer
- Traditional TV broadcasting
- Radio broadcasting

**Characteristics**:
✅ Simple
❌ No acknowledgment
❌ No error recovery

---

#### 2. **Half-Duplex**
- **Two-way** communication
- **Not simultaneous** (one at a time)
- Uses entire bandwidth for one direction

```
Device A ←──────→ Device B
         (Alternating)
```

**Examples**:
- Walkie-talkie
- CB radio
- Some wireless networks
- Traditional Ethernet hubs

**Characteristics**:
✅ Two-way communication
❌ Cannot send and receive simultaneously
- Requires turn-taking protocol

---

#### 3. **Full-Duplex**
- **Two-way simultaneous** communication
- Both directions at the same time
- Requires two separate channels or frequencies

```
Device A ────────────→ Device B
         ←────────────
    (Simultaneous both ways)
```

**Examples**:
- Telephone
- Modern Ethernet switches
- Mobile phones
- Video conferencing

**Characteristics**:
✅ Simultaneous bidirectional
✅ Higher efficiency
✅ Better performance
❌ More complex
❌ Requires more bandwidth

---

### Comparison

| Feature | Simplex | Half-Duplex | Full-Duplex |
|---------|---------|-------------|-------------|
| **Direction** | One-way | Two-way | Two-way |
| **Simultaneous** | No | No | Yes |
| **Channel Usage** | 100% one way | 100% alternating | 50% each way |
| **Complexity** | Low | Medium | High |
| **Example** | TV broadcast | Walkie-talkie | Telephone |

---

## Transmission Impairments

Signal degradation during transmission.

### 1. **Attenuation**

**Definition**: Loss of signal strength as it travels through the medium.

**Causes**:
- Resistance in conductors
- Distance
- Medium properties

**Measurement**: Decibels (dB)

**Formula**:
```
Attenuation (dB) = 10 × log₁₀(P_input / P_output)
```

**Solution**:
- Amplifiers (analog signals)
- Repeaters (digital signals)
- Use better quality cables
- Reduce distance

```
Strong Signal ───────────────> Weak Signal
    ████                           ██
  (Source)                     (Destination)
```

---

### 2. **Distortion**

**Definition**: Change in signal shape.

**Causes**:
- Different frequency components travel at different speeds
- Non-linear medium characteristics

**Types**:
- **Harmonic Distortion**: Addition of harmonics
- **Intermodulation Distortion**: Mixing of frequencies

```
Sent:     ╱╲╱╲╱╲
          ╲╱╲╱╲╱

Received: ╱╲_╱╲╱╲
          ╲╱ ╲╱╲╱
          (Distorted)
```

**Solution**:
- Equalization techniques
- Use linear amplifiers
- Better quality cables

---

### 3. **Noise**

**Definition**: Unwanted signals that corrupt the original signal.

**Types**:

#### a) **Thermal Noise (White Noise)**
- Random electron movement due to heat
- Present in all electronic devices
- Cannot be eliminated, only reduced

#### b) **Induced Noise (Electromagnetic Interference - EMI)**
- External electromagnetic sources
- Motors, fluorescent lights, power lines
- **Solution**: Shielding, twisted pair cables

#### c) **Crosstalk**
- Signal from one wire interferes with another
- Common in parallel cables
- **Solution**: Proper cable shielding, spacing

#### d) **Impulse Noise (Spike)**
- Sudden, high-amplitude noise
- Lightning, power surges
- Most damaging type
- **Solution**: Surge protectors, proper grounding

```
Clean Signal:  ╱╲╱╲╱╲╱╲
               ╲╱╲╱╲╱╲╱

With Noise:    ╱╲╱╲╱⚡╲╱╲
               ╲╱╲╱╲╱╲╱
                   ↑
                 Noise
```

**SNR (Signal-to-Noise Ratio)**:
```
SNR (dB) = 10 × log₁₀(Signal Power / Noise Power)
```

Higher SNR = Better quality

---

## Switching Techniques

Switching establishes a path for data transfer between sender and receiver.

```
Switching Techniques
│
├── Circuit Switching
├── Packet Switching
│   ├── Datagram (Connectionless)
│   └── Virtual Circuit (Connection-oriented)
└── Message Switching
```

---

### 1. **Circuit Switching**

**Definition**: Dedicated physical path is established between sender and receiver for the entire communication session.

#### Working:

**Three Phases**:
1. **Connection Establishment**: Dedicated path is set up
2. **Data Transfer**: Data flows through the dedicated circuit
3. **Connection Termination**: Circuit is released

```
Phase 1: Setup
A ═══════════ Switch ═══════════ B
    (Dedicated path created)

Phase 2: Data Transfer
A ═══[DATA]══> Switch ═══[DATA]══> B

Phase 3: Teardown
A - - - - - - Switch - - - - - - B
    (Path released)
```

#### Characteristics:

**Advantages**:
✅ Guaranteed bandwidth (no congestion once connected)
✅ Low delay (after connection established)
✅ Fixed data rate
✅ Ordered delivery
✅ Suitable for real-time communication

**Disadvantages**:
❌ Inefficient bandwidth utilization (idle time wasted)
❌ Connection setup time (delay before transmission)
❌ Once established, capacity dedicated even if not used
❌ If any link fails, connection breaks
❌ Not suitable for bursty data

**Examples**:
- Traditional telephone network (PSTN)
- ISDN (Integrated Services Digital Network)

**Use Cases**:
- Voice calls
- Video conferencing
- Any continuous data transmission

---

### 2. **Packet Switching**

**Definition**: Data is broken into small packets. Each packet is transmitted independently through the network.

#### **Packet Structure**:
```
┌────────┬─────────┬──────────┐
│ Header │ Payload │ Trailer  │
└────────┴─────────┴──────────┘
   ↓         ↓          ↓
 Source,   Actual    Checksum,
 Dest,     Data      Error
 Seq No.             Detection
```

#### Types of Packet Switching:

---

#### A. **Datagram Approach (Connectionless)**

**Working**:
- Each packet treated independently
- Packets may take different routes
- No connection setup
- Packets may arrive out of order

```
Source sends packets:
Packet 1 ─┐
Packet 2 ─┼──→ [Network] ──→ Destination
Packet 3 ─┘    (Different routes)

Arrival order might be: 2, 1, 3
```

**Characteristics**:
- **Connection**: Connectionless
- **Route**: Each packet routed independently
- **Sequence**: Packets may arrive out of order
- **Header**: Contains full addressing information
- **Overhead**: Higher (due to routing decisions per packet)

**Advantages**:
✅ No connection setup delay
✅ More flexible (can route around failures)
✅ Better bandwidth utilization
✅ No single point of failure

**Disadvantages**:
❌ Packets may arrive out of order
❌ Each packet needs full addressing
❌ More processing at each router
❌ No guaranteed delivery

**Example**: **Internet Protocol (IP)**, UDP

---

#### B. **Virtual Circuit Approach (Connection-oriented)**

**Working**:
- Logical connection established before data transfer
- All packets follow the same path
- Connection identified by Virtual Circuit Identifier (VCI)

**Three Phases**:
1. **Setup**: Virtual circuit established, VCI assigned
2. **Data Transfer**: All packets follow same path using VCI
3. **Teardown**: Virtual circuit released

```
Setup Phase:
A ──[Request]──> Switches ──[Accept]──> B
    (VCI = 12 assigned)

Data Transfer:
A ══[12,Pkt1]══> Switches ══[12,Pkt1]══> B
  ══[12,Pkt2]══>          ══[12,Pkt2]══>
    (All packets use same path)
```

**Characteristics**:
- **Connection**: Connection-oriented
- **Route**: Fixed path for all packets
- **Sequence**: Ordered delivery
- **Header**: Contains VCI (smaller than full address)
- **Overhead**: Lower per packet (after setup)

**Types**:
1. **SVC (Switched Virtual Circuit)**: Temporary, created when needed
2. **PVC (Permanent Virtual Circuit)**: Permanent, always available

**Advantages**:
✅ Ordered delivery
✅ Lower overhead per packet (only VCI)
✅ Resources can be reserved
✅ Quality of Service (QoS) possible

**Disadvantages**:
❌ Connection setup delay
❌ Less flexible than datagram
❌ If path fails, connection breaks

**Examples**: 
- **ATM (Asynchronous Transfer Mode)**
- **Frame Relay**
- **MPLS (Multi-Protocol Label Switching)**
- **TCP** (at transport layer)

---

#### Comparison: Datagram vs Virtual Circuit

| Feature | Datagram | Virtual Circuit |
|---------|----------|-----------------|
| **Connection** | Connectionless | Connection-oriented |
| **Setup** | No setup | Setup required |
| **Route** | Independent per packet | Fixed path |
| **Order** | May be out of order | Ordered delivery |
| **Header Size** | Large (full address) | Small (VCI) |
| **Flexibility** | High | Low |
| **Overhead** | High per packet | High initially, low after |
| **Example** | IP, UDP | ATM, Frame Relay, TCP |

---

### 3. **Message Switching**

**Definition**: Entire message is transmitted as a complete unit from one node to another.

**Working**:
- Store and forward mechanism
- Each intermediate node stores entire message
- Then forwards to next node when link is available

```
Source ──[Complete Message]──> Node1 ──[Store]──> Node2 ──> Dest
                                 ↓
                            (Waits if busy)
```

**Characteristics**:
- No dedicated path
- Messages stored at intermediate nodes
- Uses store-and-forward
- No real-time transmission

**Advantages**:
✅ Efficient bandwidth usage
✅ Can handle priority messages
✅ Error control at each node
✅ Can store messages if destination busy

**Disadvantages**:
❌ High delay (store-and-forward)
❌ Requires large storage at nodes
❌ Not suitable for real-time
❌ Message size limitations

**Examples**:
- Email systems
- Telegraph systems (historical)

**Status**: Largely obsolete, replaced by packet switching

---

### Switching Techniques Comparison

| Feature | Circuit | Packet (Datagram) | Packet (VC) | Message |
|---------|---------|-------------------|-------------|---------|
| **Path** | Dedicated | Dynamic | Fixed after setup | Store-forward |
| **Setup** | Required | No | Required | No |
| **Bandwidth** | Fixed | Shared | Shared | Shared |
| **Delay** | Low (after setup) | Variable | Medium | High |
| **Ordering** | Yes | No | Yes | Yes |
| **Efficiency** | Low | High | High | Medium |
| **Use Case** | Voice calls | Internet | ATM | Email |

---

## Multiplexing

**Definition**: Combining multiple signals into a single medium to maximize utilization.

**Purpose**: Share expensive transmission medium among multiple users.

```
Multiplexing Types
│
├── FDM (Frequency Division)
├── WDM (Wavelength Division)
├── TDM (Time Division)
│   ├── Synchronous TDM
│   └── Statistical TDM
└── CDM (Code Division)
```

---

### 1. **FDM (Frequency Division Multiplexing)**

**Definition**: Multiple signals transmitted simultaneously over different frequency bands.

**Working**:
```
Signal 1 ──┐
Signal 2 ──┼── MUX ──[f1|f2|f3|f4]──> Channel ──> DEMUX ──┬── Signal 1
Signal 3 ──┤                                               ├── Signal 2
Signal 4 ──┘                                               ├── Signal 3
                                                           └── Signal 4
Frequency bands:
f1: 0-10 kHz
f2: 10-20 kHz
f3: 20-30 kHz
f4: 30-40 kHz
```

**Key Concepts**:
- Each signal assigned a frequency band
- **Guard bands** separate channels (prevent interference)
- All signals transmitted simultaneously
- Analog technique

**Advantages**:
✅ All channels used simultaneously
✅ No inter-channel interference (with proper guard bands)
✅ Simple to implement

**Disadvantages**:
❌ Requires guard bands (wastes bandwidth)
❌ Hardware more complex
❌ Inter-modulation distortion

**Examples**:
- Radio broadcasting (different stations on different frequencies)
- Cable TV
- First generation analog cellular (AMPS)
- ADSL (different frequencies for upload/download)

**Use Cases**:
- Broadcasting
- Telephone trunks
- Cable systems

---

### 2. **WDM (Wavelength Division Multiplexing)**

**Definition**: Similar to FDM but for optical fiber. Multiple light wavelengths (colors) used.

**Types**:
- **DWDM (Dense WDM)**: Many channels (40-80+), closely spaced
- **CWDM (Coarse WDM)**: Fewer channels (8-18), wider spacing

**Working**:
```
λ1 (1550 nm) ──┐
λ2 (1551 nm) ──┼── Optical MUX ──> Fiber ──> Optical DEMUX
λ3 (1552 nm) ──┤
λ4 (1553 nm) ──┘
```

**Advantages**:
✅ Massive bandwidth (Tbps possible)
✅ Efficient use of fiber
✅ Can add channels without new fiber

**Examples**:
- Long-haul fiber optic networks
- Submarine cables
- Backbone networks

---

### 3. **TDM (Time Division Multiplexing)**

**Definition**: Multiple signals share the same frequency by using different time slots.

```
Signal 1 ──┐
Signal 2 ──┼── MUX ──[1|2|3|4|1|2|3|4]──> Channel
Signal 3 ──┤     (Time slots)
Signal 4 ──┘

Timeline: |S1|S2|S3|S4|S1|S2|S3|S4|S1|...
```

---

#### A. **Synchronous TDM (Statistical TDM)**

**Characteristics**:
- Fixed time slots for each channel
- Slots allocated even if channel has no data
- All sources must have same data rate
- **Inefficient** if sources are idle

**Frame Structure**:
```
Frame = [Slot1|Slot2|Slot3|Slot4]
         ↓      ↓     ↓     ↓
        Ch1    Ch2   Ch3   Ch4
```

**Disadvantages**:
❌ Wastes bandwidth (empty slots for idle channels)
❌ Fixed allocation

---

#### B. **Asynchronous TDM (Statistical TDM)**

**Characteristics**:
- Slots allocated dynamically (only to active channels)
- More efficient bandwidth usage
- Requires addressing (to identify source)
- Variable slot allocation

**Frame Structure**:
```
Frame = [Addr|Data|Addr|Data|Addr|Data]
         ↓    ↓    ↓    ↓    ↓    ↓
        Ch2       Ch1       Ch4
     (Ch3 idle - no slot allocated)
```

**Advantages**:
✅ Higher efficiency
✅ Better for bursty traffic

**Disadvantages**:
❌ More complex
❌ Overhead for addressing

---

**Examples of TDM**:
- **T1 line**: 24 voice channels (each 64 kbps) = 1.544 Mbps
- **E1 line**: 30 voice channels = 2.048 Mbps
- **GSM**: Time slots for mobile channels
- **SONET/SDH**: Optical TDM

---

### 4. **CDM (Code Division Multiplexing) / CDMA**

**Definition**: All users transmit simultaneously on same frequency using unique codes.

**Working**:
- Each user assigned unique code (chip sequence)
- Signals encoded and transmitted together
- Receiver uses same code to extract signal

```
User 1: Data × Code1 ──┐
User 2: Data × Code2 ──┼──> Combined Signal ──> Receiver (extracts using Code1)
User 3: Data × Code3 ──┘
```

**Key Concept**:
- Codes are **orthogonal** (mathematically independent)
- Cross-correlation of different codes = 0

**Advantages**:
✅ All users use same frequency
✅ No time slots needed
✅ Soft capacity limit
✅ Good for wireless

**Disadvantages**:
❌ Complex to implement
❌ Requires power control
❌ Near-far problem

**Examples**:
- **3G cellular (CDMA2000, WCDMA)**
- **GPS**
- Military communications

---

### Multiplexing Comparison

| Technique | Division Basis | Type | Example |
|-----------|---------------|------|---------|
| **FDM** | Frequency | Analog | Radio, TV |
| **WDM** | Wavelength | Optical | Fiber networks |
| **TDM** | Time | Digital | T1, GSM |
| **CDM** | Code | Digital | 3G, GPS |

---

## Casting Types

Methods of transmitting data to one or more destinations.

```
Casting Types
│
├── Unicast (One-to-One)
├── Broadcast (One-to-All)
├── Multicast (One-to-Many)
└── Anycast (One-to-Nearest)
```

---

### 1. **Unicast**

**Definition**: One-to-one communication. Data sent from one sender to one specific receiver.

```
Sender ────────────────> Receiver
         (Single path)
```

**Characteristics**:
- Point-to-point transmission
- Dedicated connection
- Most common type
- Each receiver gets separate copy

**Example Protocols**:
- HTTP, FTP, SSH, Telnet
- TCP connections
- Most internet traffic

**Advantages**:
✅ Secure (only intended recipient)
✅ Reliable delivery
✅ Simple to implement

**Disadvantages**:
❌ Inefficient for same data to multiple receivers
❌ More bandwidth for multiple recipients
❌ Server load increases with number of clients

**Use Cases**:
- Web browsing
- Email
- File transfer
- One-on-one video calls

**Addressing**:
- IPv4: Normal IP address (e.g., 192.168.1.1)
- IPv6: Normal address (e.g., 2001:db8::1)

---

### 2. **Broadcast**

**Definition**: One-to-all communication. Data sent from one sender to all devices in the network.

```
                    Receiver 1
                   ↗
Sender ───────────┼────> Receiver 2
                   ↘
                    Receiver 3
    (All devices receive)
```

**Types**:

#### a) **Limited Broadcast**
- Within local network only
- **Address**: 255.255.255.255
- Not forwarded by routers

#### b) **Directed Broadcast**
- To specific network
- **Example**: 192.168.1.255 (to all hosts in 192.168.1.0/24)
- Can be forwarded by routers (often disabled)

**Characteristics**:
- All devices on network receive
- No selective delivery
- High network traffic
- Works at Layer 2 (MAC) and Layer 3 (IP)

**MAC Broadcast Address**: FF:FF:FF:FF:FF:FF

**Advantages**:
✅ Efficient for reaching all devices
✅ Simple discovery mechanisms
✅ Good for announcements

**Disadvantages**:
❌ Network congestion
❌ Security concerns
❌ Processes by all devices (CPU overhead)
❌ Not scalable

**Examples**:
- **ARP (Address Resolution Protocol)**: Find MAC from IP
- **DHCP Discovery**: Client finding DHCP server
- **Network discovery**
- **Wake-on-LAN**

**Use Cases**:
- Address resolution
- Service discovery
- Network announcements
- Emergency alerts

**IPv6 Note**: No broadcast in IPv6 (replaced by multicast)

---

### 3. **Multicast**

**Definition**: One-to-many communication. Data sent from one sender to a specific group of receivers.

```
                    Receiver 1 (subscribed)
                   ↗
Sender ───────────┤
                   ↘
                    Receiver 2 (subscribed)

    Receiver 3 (not subscribed - doesn't receive)
```

**Characteristics**:
- Selective group communication
- Receivers must "subscribe" to multicast group
- More efficient than multiple unicasts
- Uses special addressing

**IPv4 Multicast Addresses**: 
- **Range**: 224.0.0.0 to 239.255.255.255 (Class D)
- **Well-known**:
  - 224.0.0.1: All hosts on subnet
  - 224.0.0.2: All routers on subnet
  - 224.0.0.5: All OSPF routers
  - 224.0.0.9: All RIP routers

**IPv6 Multicast Addresses**:
- **Range**: FF00::/8
- **Example**: FF02::1 (all nodes on link)

**Multicast MAC Address**:
- **Range**: 01:00:5E:00:00:00 to 01:00:5E:7F:FF:FF

**Protocols**:
- **IGMP (Internet Group Management Protocol)**: Join/leave multicast groups
- **PIM (Protocol Independent Multicast)**: Multicast routing
- **DVMRP, MOSPF**: Older multicast routing

**Advantages**:
✅ Efficient bandwidth usage
✅ Reduces server load
✅ Scalable for large groups
✅ One transmission reaches multiple receivers

**Disadvantages**:
❌ Complex to configure
❌ Not all routers support it
❌ Best-effort delivery (UDP)
❌ No guaranteed delivery

**Examples**:
- **IPTV**: TV streaming to subscribers
- **Video conferencing**: Multiple participants
- **Stock ticker updates**
- **Online gaming**
- **Software updates** (for multiple machines)

**Use Cases**:
- Live video streaming
- Webinars
- Multiplayer games
- Financial data distribution
- Multimedia distribution

---

### 4. **Anycast**

**Definition**: One-to-nearest communication. Data sent to one member of a group (usually the nearest or best one).

```
          Receiver 1 (Los Angeles)
         ↗
Sender ──┤         
         ↘
          Receiver 2 (New York) ← Selected (nearest)

    (Both have same anycast address, 
     nearest one responds)
```

**Characteristics**:
- Multiple devices share same IP address
- Routing selects "nearest" (based on routing metrics)
- Used for load balancing and redundancy
- Primarily IPv6 feature (limited IPv4 support)

**How It Works**:
1. Multiple servers assigned same anycast IP
2. Client sends to anycast address
3. Network routes to topologically nearest server
4. "Nearest" determined by routing protocol (hop count, latency, etc.)

**Advantages**:
✅ Load balancing
✅ Fault tolerance (automatic failover)
✅ Reduced latency (nearest server)
✅ DDoS mitigation

**Disadvantages**:
❌ Complex routing
❌ May not always select truly nearest
❌ Connection state issues with TCP

**Examples**:
- **DNS Root Servers**: Many physical servers, same IP
- **CDN (Content Delivery Networks)**: Cloudflare, Akamai
- **6to4 relay routers**: IPv6 transition

**Use Cases**:
- DNS resolution
- Content delivery
- Load balancing
- Service redundancy

**Real-World Example**:
Google's DNS (8.8.8.8) is anycast - hundreds of servers worldwide share this IP, and you connect to the nearest one.

---

### Casting Comparison Table

| Type | Sender | Receiver(s) | Efficiency | Use Case |
|------|--------|-------------|------------|----------|
| **Unicast** | 1 | 1 | Low (for multiple) | Web, Email, FTP |
| **Broadcast** | 1 | All in network | Low (all process) | ARP, DHCP |
| **Multicast** | 1 | Group (subscribed) | High | IPTV, Conferencing |
| **Anycast** | 1 | Nearest (one of group) | High | DNS, CDN |

---

### Address Ranges Summary

| Type | IPv4 Range | IPv6 Range |
|------|-----------|------------|
| **Unicast** | All except below | All except FF00::/8 |
| **Broadcast** | 255.255.255.255 | N/A (no broadcast) |
| **Multicast** | 224.0.0.0 - 239.255.255.255 | FF00::/8 |
| **Anycast** | No specific range | Same as unicast |

---

## Physical Layer Devices

### 1. **Hub**

**Definition**: Multi-port repeater that broadcasts data to all connected ports.

**Characteristics**:
- **OSI Layer**: Layer 1 (Physical)
- **Operation**: Broadcasts to all ports
- **Intelligence**: No intelligence (dumb device)
- **Collision Domain**: Single (all ports share)
- **Broadcast Domain**: Single

**Types**:
- **Passive Hub**: No signal amplification
- **Active Hub**: Amplifies signals
- **Intelligent Hub**: Some management features

**Advantages**:
✅ Cheap
✅ Simple to install
✅ No configuration needed

**Disadvantages**:
❌ Inefficient (broadcasts to all)
❌ Security issues (all see all traffic)
❌ Performance degrades with more devices
❌ Single collision domain

**Use**: Obsolete, replaced by switches

---

### 2. **Repeater**

**Definition**: Amplifies or regenerates signals to extend transmission distance.

**Function**:
- Receives signal
- Cleans and amplifies it
- Retransmits

**Types**:
- **Analog Repeater**: Amplifies signal (also amplifies noise)
- **Digital Repeater**: Regenerates signal (removes noise)

**Characteristics**:
- **OSI Layer**: Layer 1
- **Ports**: 2 (in and out)
- **Distance Extension**: Yes

**Advantages**:
✅ Extends network range
✅ Cheap

**Disadvantages**:
❌ No filtering
❌ Propagates errors and noise (analog)

**Use**: Extending cable runs beyond limits

---

### 3. **Modem**

**Definition**: MOdulator/DEModulator - converts digital to analog and vice versa.

**Function**:
- **Modulation**: Digital → Analog (for transmission)
- **Demodulation**: Analog → Digital (for reception)

**Types**:
- **Dial-up Modem**: Uses telephone lines (56 kbps)
- **DSL Modem**: Digital Subscriber Line (up to 100 Mbps)
- **Cable Modem**: Uses coaxial cable (up to 1 Gbps)
- **Fiber Modem (ONT)**: Fiber to home

**Standards**:
- V.90: 56 kbps dial-up
- V.92: Enhanced dial-up

**Use**: Internet connectivity via telephone/cable lines

---

### 4. **NIC (Network Interface Card)**

**Definition**: Hardware that connects a device to a network.

**Function**:
- Provides physical connection (port)
- MAC address burned in
- Converts data to signals
- Handles media access

**Types**:
- **Ethernet NIC**: RJ-45 port
- **Wi-Fi NIC**: Wireless adapter
- **Fiber NIC**: SFP ports

**Characteristics**:
- **OSI Layer**: Layer 1 and Layer 2
- **MAC Address**: Unique 48-bit identifier

---

## Standards and Protocols

### Physical Layer Standards

#### IEEE 802.3 (Ethernet Standards)

| Standard | Speed | Cable | Max Distance |
|----------|-------|-------|--------------|
| 10Base-T | 10 Mbps | Cat 3 UTP | 100m |
| 100Base-TX | 100 Mbps | Cat 5 UTP | 100m |
| 1000Base-T | 1 Gbps | Cat 5e UTP | 100m |
| 10GBase-T | 10 Gbps | Cat 6a/7 | 100m |
| 100Base-FX | 100 Mbps | Multimode Fiber | 2km |
| 1000Base-LX | 1 Gbps | Single-mode Fiber | 10km |

**Naming Convention**:
- **Number**: Speed in Mbps
- **Base**: Baseband transmission
- **Suffix**: Media type (T=Twisted Pair, F=Fiber, etc.)

#### RS-232
- Serial communication standard
- Point-to-point
- Distance: Up to 15m
- Speed: Up to 115.2 kbps
- **Use**: Serial ports, modems

#### USB (Universal Serial Bus)
- **USB 1.1**: 12 Mbps
- **USB 2.0**: 480 Mbps
- **USB 3.0**: 5 Gbps
- **USB 3.1**: 10 Gbps
- **USB 4.0**: 40 Gbps

---

## Important Formulas and Calculations

### 1. **Bit Rate and Bandwidth**

**Bit Rate (R)**:
```
R = Number of bits transmitted / Time
Measured in bps (bits per second)
```

**Bandwidth (B)**:
```
For digital: B = Bit Rate / log₂(L)
where L = number of signal levels
```

**Nyquist Theorem** (Noiseless channel):
```
Maximum Bit Rate = 2 × B × log₂(L)

where:
B = Bandwidth in Hz
L = Number of signal levels
```

**Example**:
- Bandwidth = 3000 Hz
- Signal levels = 2 (binary)
- Max Bit Rate = 2 × 3000 × log₂(2) = 6000 bps

---

### 2. **Shannon Capacity** (Noisy channel):

```
C = B × log₂(1 + SNR)

where:
C = Channel capacity (bps)
B = Bandwidth (Hz)
SNR = Signal-to-Noise Ratio
```

**SNR in dB**:
```
SNR(dB) = 10 × log₁₀(SNR)

or

SNR = 10^(SNR(dB)/10)
```

**Example**:
- Bandwidth = 3000 Hz
- SNR = 30 dB
- SNR (ratio) = 10^(30/10) = 1000
- C = 3000 × log₂(1001) ≈ 30 Kbps

---

### 3. **Transmission Time**

```
Transmission Time = Data Size / Bit Rate
```

**Example**:
- File size = 10 MB = 10 × 8 = 80 Mb
- Bit rate = 10 Mbps
- Time = 80 / 10 = 8 seconds

---

### 4. **Propagation Delay**

```
Propagation Delay = Distance / Propagation Speed

Propagation Speed:
- Copper wire: ~2 × 10⁸ m/s
- Fiber optic: ~2 × 10⁸ m/s
- Air (wireless): ~3 × 10⁸ m/s
```

**Example**:
- Distance = 1000 km = 10⁶ m
- Speed = 2 × 10⁸ m/s
- Delay = 10⁶ / (2 × 10⁸) = 5 ms

---

### 5. **Attenuation (dB)**

```
Attenuation (dB) = 10 × log₁₀(P_in / P_out)

or

P_out = P_in × 10^(-Attenuation/10)
```

**Example**:
- Input power = 100 mW
- Attenuation = 20 dB
- Output = 100 × 10^(-20/10) = 100 × 0.01 = 1 mW

---

### 6. **Wavelength and Frequency**

```
c = λ × f

where:
c = Speed of light (3 × 10⁸ m/s)
λ = Wavelength (meters)
f = Frequency (Hz)
```

**Example**:
- Frequency = 2.4 GHz (Wi-Fi)
- λ = (3 × 10⁸) / (2.4 × 10⁹) = 0.125 m = 12.5 cm

---

## Interview Questions

### Frequently Asked Questions

#### 1. **What is the function of the Physical Layer?**
**Answer**: The Physical Layer is responsible for transmitting raw bits over a physical medium. It defines electrical, mechanical, and procedural specifications for activating, maintaining, and deactivating physical connections.

---

#### 2. **Difference between Guided and Unguided Media?**

| Feature | Guided | Unguided |
|---------|--------|----------|
| Medium | Physical cables | Air/space |
| Security | More secure | Less secure |
| Distance | Limited | Can be long |
| Installation | Complex | Easy |
| Example | Fiber, UTP | Wi-Fi, Radio |

---

#### 3. **Why is Manchester Encoding used in Ethernet?**
**Answer**: 
- Self-clocking (transition in every bit)
- Easy synchronization
- DC component elimination
- Good error detection

---

#### 4. **Circuit Switching vs Packet Switching?**

| Feature | Circuit | Packet |
|---------|---------|--------|
| Path | Dedicated | Shared |
| Setup | Required | No (datagram) |
| Delay | Low (fixed) | Variable |
| Efficiency | Low | High |
| Example | Phone call | Internet |

---

#### 5. **What is the difference between Multicast and Broadcast?**

**Broadcast**: 
- One-to-all
- All devices receive
- Address: 255.255.255.255
- High network traffic

**Multicast**:
- One-to-group
- Only subscribed devices receive
- Address: 224.0.0.0 - 239.255.255.255
- Efficient for group communication

---

#### 6. **Explain Nyquist and Shannon Theorems.**

**Nyquist** (Noiseless):
```
Max Bit Rate = 2 × B × log₂(L)
```
- Determines max bit rate based on bandwidth and signal levels
- Assumes no noise

**Shannon** (Noisy):
```
Capacity = B × log₂(1 + SNR)
```
- Determines max capacity in presence of noise
- More realistic

---

#### 7. **What is Attenuation? How to overcome it?**

**Attenuation**: Loss of signal strength during transmission.

**Solutions**:
- Use **amplifiers** (analog)
- Use **repeaters** (digital)
- Use better quality cables
- Reduce distance

---

#### 8. **Single Mode vs Multi Mode Fiber?**

| Feature | Single Mode | Multi Mode |
|---------|-------------|------------|
| Core | 8-10 μm | 50-62.5 μm |
| Light | Laser | LED |
| Distance | 100+ km | 2 km |
| Cost | High | Low |

---

#### 9. **What is Multiplexing? Types?**

**Definition**: Combining multiple signals into one medium.

**Types**:
1. **FDM**: Different frequencies (Radio, TV)
2. **TDM**: Different time slots (T1, GSM)
3. **WDM**: Different wavelengths (Fiber)
4. **CDM**: Different codes (3G cellular)

---

#### 10. **Simplex vs Half-Duplex vs Full-Duplex?**

| Type | Direction | Simultaneous | Example |
|------|-----------|--------------|---------|
| Simplex | One-way | N/A | TV |
| Half-Duplex | Both | No | Walkie-talkie |
| Full-Duplex | Both | Yes | Phone |

---

### Quick Tips for Interviews

**Remember**:
1. Physical Layer = **Layer 1** = Works with **Bits**
2. No error correction at Physical Layer
3. Hub works at Physical Layer (broadcasts)
4. Main functions: Bit transmission, data rate, synchronization
5. Fiber is best for long distance, high bandwidth
6. Circuit Switching = dedicated path
7. Packet Switching = shared path, more efficient
8. Multicast is efficient for group communication

---

### Key Takeaways

✅ Physical Layer transmits **raw bits**
✅ Deals with **physical medium** (cables, signals)
✅ **No addressing** at this layer
✅ **Guided media**: Twisted pair, coaxial, fiber
✅ **Unguided media**: Radio, microwave, infrared
✅ **Encoding**: How bits are represented
✅ **Switching**: Circuit, Packet, Message
✅ **Multiplexing**: FDM, TDM, WDM, CDM
✅ **Casting**: Unicast, Broadcast, Multicast, Anycast

---

**Good luck with your interviews! 🚀**
