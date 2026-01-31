# Data Link Layer - Placement Oriented Guide

## Table of Contents
1. [Introduction to Data Link Layer](#introduction-to-data-link-layer)
2. [Functions of Data Link Layer](#functions-of-data-link-layer)
3. [Sub-layers of Data Link Layer](#sub-layers-of-data-link-layer)
4. [Framing](#framing)
5. [Error Detection](#error-detection)
6. [Error Correction](#error-correction)
7. [Flow Control](#flow-control)
8. [Sliding Window Protocols](#sliding-window-protocols)
9. [MAC (Medium Access Control)](#mac-medium-access-control)
10. [Ethernet](#ethernet)
11. [Switching](#switching)
12. [VLAN (Virtual LAN)](#vlan-virtual-lan)
13. [ARP (Address Resolution Protocol)](#arp-address-resolution-protocol)
14. [Data Link Layer Devices](#data-link-layer-devices)
15. [Important Formulas & Calculations](#important-formulas--calculations)
16. [Interview Questions & Answers](#interview-questions--answers)

---

## Introduction to Data Link Layer

### Definition
The **Data Link Layer** (Layer 2) is responsible for **node-to-node** data transfer and error-free transmission over the physical layer. It converts raw bits from the Physical Layer into **frames** and ensures reliable communication between adjacent network nodes.

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
│ ▶ DATA LINK LAYER ◀     │ Layer 2  ← Works with FRAMES
├─────────────────────────┤
│   Physical Layer        │ Layer 1  ← Works with BITS
└─────────────────────────┘
```

### Key Characteristics
- **PDU (Protocol Data Unit)**: **Frame**
- **Addressing**: **MAC Address** (48-bit physical address)
- **Scope**: **Hop-to-hop** (between adjacent nodes)
- **Main Focus**: Reliable data transfer between directly connected devices

### What Data Link Layer Does
✅ **Framing**: Encapsulates packets into frames
✅ **Physical Addressing**: Uses MAC addresses
✅ **Error Detection**: Detects errors in frames
✅ **Error Correction**: Corrects errors (optional)
✅ **Flow Control**: Manages data rate
✅ **Access Control**: Who transmits on shared medium

---

## Functions of Data Link Layer

### 1. **Framing**
- Breaks bit stream into manageable frames
- Adds header and trailer to each frame
- Provides frame boundaries

```
Network Layer Packet
        ↓
┌──────────────────────────────┐
│ Header │  Payload  │ Trailer │  ← Frame
└──────────────────────────────┘
   ↓          ↓           ↓
 Address,   Data from   Error
  Control   Network      Check
  Info      Layer
```

### 2. **Physical Addressing**
- Adds sender and receiver MAC addresses in frame header
- MAC address: 48-bit (6 bytes) unique identifier
- Format: XX:XX:XX:XX:XX:XX (hexadecimal)

**Example MAC**: `00:1A:2B:3C:4D:5E`

### 3. **Error Control**
- **Detection**: Identifies errors using techniques like CRC, checksum
- **Correction**: Retransmits corrupted frames
- Uses **ACK** (acknowledgment) and **NAK** (negative acknowledgment)

### 4. **Flow Control**
- Prevents fast sender from overwhelming slow receiver
- Mechanisms: Stop-and-Wait, Sliding Window

### 5. **Access Control**
- Determines which device has control over the link
- Important for shared medium (multiple devices)
- Protocols: CSMA/CD, CSMA/CA, Token Passing

---

## Sub-layers of Data Link Layer

The Data Link Layer is divided into two sub-layers:

```
┌─────────────────────────────────┐
│  LLC (Logical Link Control)     │  ← Upper sub-layer
├─────────────────────────────────┤
│  MAC (Media Access Control)     │  ← Lower sub-layer
└─────────────────────────────────┘
```

### 1. **LLC (Logical Link Control)** - IEEE 802.2

**Functions**:
- Interface between Network Layer and MAC sub-layer
- Flow control
- Error control
- Multiplexing protocols

**Services Provided**:
- **Unacknowledged Connectionless**: No ACK, best effort
- **Connection-Oriented**: Reliable, with ACK
- **Acknowledged Connectionless**: ACK without connection

**Not commonly discussed** in interviews but good to know.

---

### 2. **MAC (Media Access Control)**

**Functions**:
- Physical addressing (MAC addresses)
- Access control (who transmits when)
- Frame delimiting
- Error detection

**Responsibilities**:
- MAC addressing
- Channel access methods (CSMA/CD, Token Ring)
- Frame synchronization

**Most interview questions focus on MAC sub-layer!**

---

## Framing

### What is Framing?
**Framing** is the process of dividing the bit stream into frames (manageable data units).

### Why Framing?
- **Organization**: Structured data units
- **Error Detection**: Errors limited to individual frames
- **Flow Control**: Control on per-frame basis
- **Synchronization**: Frame boundaries help sync

### Frame Structure
```
┌───────────┬────────┬─────────┬─────────┬──────────┐
│   Flag    │ Header │ Payload │ Trailer │   Flag   │
└───────────┴────────┴─────────┴─────────┴──────────┘
     ↓         ↓         ↓          ↓         ↓
  Start    Addresses, Data from  Error    End
  Delimiter  Control   upper    Check   Delimiter
                       layers
```

**Components**:
1. **Flag/Delimiter**: Marks start and end of frame
2. **Header**: Source and destination MAC addresses, control info
3. **Payload**: Actual data from Network Layer
4. **Trailer**: Error detection code (CRC, Checksum)

---

### Framing Methods

#### 1. **Character Count**

**Method**: First field specifies number of characters in the frame.

```
Frame 1: [5][A][B][C][D]
         ↑
      5 characters total
```

**Problems**:
❌ If count is corrupted, framing lost
❌ Error in count causes loss of synchronization
❌ **Rarely used**

---

#### 2. **Character/Byte Stuffing**

**Method**: Use special characters (FLAG) to mark frame boundaries.

**Problem**: What if data contains FLAG character?
**Solution**: **Escape character (ESC)** before FLAG in data

```
Original Data: A B FLAG C D
                    ↑
              This is data, not delimiter

After Stuffing: A B ESC FLAG C D
                    ↑   ↑
                  Escape it!

Frame: FLAG | A B ESC FLAG C D | FLAG
       ↑                           ↑
    Start                        End
```

**Rules**:
- If FLAG appears in data → Insert ESC before it
- If ESC appears in data → Insert ESC before it (ESC ESC)

**Used in**: PPP (Point-to-Point Protocol)

**Advantages**:
✅ Simple
✅ Can handle any data

**Disadvantages**:
❌ Overhead (extra bytes)
❌ Character-oriented (not good for binary data)

---

#### 3. **Bit Stuffing**

**Method**: Use bit pattern (e.g., `01111110`) as flag.

**Problem**: What if data contains this pattern?
**Solution**: After five consecutive 1s in data, insert a 0

```
Flag Pattern: 01111110

Original Data: 0111111001111110
                   ↑       ↑
               5 ones!  6 ones!

After Stuffing: 01111101001111101010
                     ↑        ↑
                  Added 0  Added 0

Frame: 01111110 | 01111101001111101010 | 01111110
         ↑                                   ↑
       Start                               End
```

**Rules**:
- After 5 consecutive 1s in data → Stuff a 0
- Receiver removes stuffed 0s

**Used in**: HDLC (High-level Data Link Control), PPP

**Advantages**:
✅ Works for any data
✅ No dependency on character codes
✅ More efficient than byte stuffing

**Disadvantages**:
❌ Requires bit-level processing
❌ Variable frame size

---

#### 4. **Physical Layer Coding Violations**

**Method**: Use invalid signals at Physical Layer to mark boundaries.

**Example**: Manchester encoding
- Valid: High-to-Low (0) or Low-to-High (1)
- Invalid: High-to-High or Low-to-Low → Used as delimiter

**Used in**: Some LANs

**Advantage**: No overhead in data
**Disadvantage**: Dependent on physical layer encoding

---

### Most Important for Interviews: **Byte Stuffing** and **Bit Stuffing**

---

## Error Detection

Errors occur due to noise, interference, attenuation during transmission.

### Types of Errors

#### 1. **Single-Bit Error**
- Only one bit changed
- Rare in burst errors

```
Sent:     1 0 1 0 1 1 0 0
Received: 1 0 1 1 1 1 0 0
                ↑
          Single bit error
```

#### 2. **Burst Error**
- Multiple consecutive bits changed
- More common in practice

```
Sent:     1 0 1 0 1 1 0 0
Received: 1 0 0 1 0 1 0 0
              ↑ ↑ ↑ ↑
          Burst error (4 bits)
```

---

### Error Detection Techniques

```
Error Detection Methods
│
├── Parity Check
│   ├── Single Parity (VRC)
│   └── Two-Dimensional Parity (LRC)
├── Checksum
└── CRC (Cyclic Redundancy Check)
```

---

### 1. **Parity Check**

#### a) **Simple Parity (VRC - Vertical Redundancy Check)**

**Method**: Add one parity bit to make total number of 1s even (or odd).

**Even Parity**: Total 1s should be even
**Odd Parity**: Total 1s should be odd

**Example (Even Parity)**:
```
Data: 1011001
Count 1s: 4 (already even)
Parity bit: 0

Transmitted: 10110010
             ↑
          Parity bit

Data: 1011011
Count 1s: 5 (odd)
Parity bit: 1

Transmitted: 10110111
             ↑
          Parity bit (makes it even)
```

**Detection**:
- Receiver counts 1s
- If even → No error (assuming even parity)
- If odd → Error detected

**Limitations**:
❌ Can detect only **odd number** of bit errors (1, 3, 5, ...)
❌ Cannot detect **even number** of bit errors (2, 4, 6, ...)
❌ Cannot detect which bit is wrong
❌ **Not reliable**

---

#### b) **Two-Dimensional Parity (LRC - Longitudinal Redundancy Check)**

**Method**: Arrange data in table, add parity bit for each row and column.

```
        Columns
        ↓
Rows → 1 0 1 1 | 1  ← Row parity
       1 1 0 0 | 0
       0 1 1 0 | 0
       1 0 1 1 | 1
       ─────────────
       1 0 1 0 | 0  ← Column parity
```

**Advantages**:
✅ Can detect 2-bit errors
✅ Can detect some burst errors
✅ Better than simple parity

**Limitations**:
❌ Still can miss some errors
❌ Overhead (extra bits)

---

### 2. **Checksum**

**Method**: 
1. Divide data into equal segments (e.g., 16-bit words)
2. Add all segments using 1's complement arithmetic
3. Take 1's complement of sum → **Checksum**
4. Append checksum to data

**Sender**:
```
Data: 
Segment 1: 10110011 01100110
Segment 2: 11010101 01010011
Segment 3: 00111100 00110011

Sum (1's complement):
  10110011 01100110
+ 11010101 01010011
+ 00111100 00110011
─────────────────────
= 10101101 11001101

Checksum = 1's complement of sum
        = 01010010 00110010
```

**Receiver**:
1. Add all segments including checksum
2. If result is all 1s → No error
3. Otherwise → Error detected

**Used in**: 
- **TCP**: 16-bit checksum
- **UDP**: 16-bit checksum
- **IP**: 16-bit checksum (header only)

**Advantages**:
✅ Simple to implement
✅ Low overhead
✅ Can detect most errors

**Disadvantages**:
❌ Can miss some errors (if errors cancel out)
❌ Not as reliable as CRC

---

### 3. **CRC (Cyclic Redundancy Check)** ⭐

**Most Important for Interviews!**

**Method**: Uses polynomial division in binary.

**Concept**:
- Treat data as polynomial coefficients
- Divide by a **generator polynomial**
- Remainder = **CRC bits** (appended to data)

**Steps (Sender)**:

1. **Choose Generator (G)**: Predetermined polynomial
   - Must be one bit longer than desired CRC
   - Example: G = 1011 (4 bits) → 3-bit CRC

2. **Append zeros**: Add (n-1) zeros to data
   - If G has n bits, append (n-1) zeros

3. **Division**: Divide modified data by G using XOR (modulo-2 division)

4. **CRC**: Remainder from division

5. **Transmit**: Original data + CRC

**Example**:

```
Data (D): 1101011011
Generator (G): 1011 (4 bits → 3-bit CRC)

Step 1: Append 3 zeros
Modified Data: 1101011011000

Step 2: Modulo-2 Division

        1100001010  ← Quotient (discard)
     ──────────────────
1011 | 1101011011000
       1011
       ────
        1100
        1011
        ────
         1111
         1011
         ────
          1001
          1011
          ────
           0101
           0000
           ────
            1010
            1011
            ────
             0010
             0000
             ────
              0100
              0000
              ────
               1000
               1011
               ────
                011  ← Remainder = CRC

Step 3: Transmitted Data
Data + CRC: 1101011011011
                       ↑↑↑
                       CRC
```

**Receiver**:
- Divide received data (including CRC) by G
- If remainder = 0 → No error
- If remainder ≠ 0 → Error detected

**XOR Rules (Modulo-2)**:
```
0 ⊕ 0 = 0
0 ⊕ 1 = 1
1 ⊕ 0 = 1
1 ⊕ 1 = 0
(No carry/borrow)
```

**Common Generators**:
- **CRC-8**: x⁸ + x² + x + 1
- **CRC-16**: x¹⁶ + x¹⁵ + x² + 1
- **CRC-32**: x³² + x²⁶ + x²³ + ... (used in Ethernet, Wi-Fi)

**Advantages**:
✅ **Very reliable** (can detect >99.99% errors)
✅ Detects all single-bit errors
✅ Detects all double-bit errors
✅ Detects all burst errors ≤ (n-1) bits (n = generator bits)
✅ Detects most larger burst errors

**Disadvantages**:
❌ Cannot correct errors (only detect)
❌ Complex to calculate manually (but hardware does it easily)

**Used in**:
- **Ethernet** (CRC-32)
- **Wi-Fi** (CRC-32)
- **HDLC, PPP** (CRC-16)
- **Storage devices** (Hard drives, CDs)

**Interview Tip**: CRC is the **most reliable** error detection method among these three.

---

### Comparison: Error Detection Methods

| Method | Bits Added | Reliability | Complexity | Use Case |
|--------|------------|-------------|------------|----------|
| **Simple Parity** | 1 | Low | Very Low | Simple systems |
| **2D Parity** | Many | Medium | Low | Legacy systems |
| **Checksum** | 16-32 | Medium-High | Medium | TCP/UDP/IP |
| **CRC** | 8-32 | Very High | High | Ethernet, Wi-Fi |

**For Interviews**: Focus on **CRC** - most asked!

---

## Error Correction

Error correction **detects AND fixes** errors without retransmission.

### Error Correction Methods

```
Error Correction
│
├── Forward Error Correction (FEC)
│   ├── Hamming Code
│   ├── Reed-Solomon
│   └── Convolutional Codes
└── Backward Error Correction (BEC)
    └── ARQ (Automatic Repeat Request)
```

---

### 1. **Hamming Code** ⭐

**Most Important for Placement Interviews!**

**Purpose**: Detects and corrects **single-bit errors**. Detects (but cannot correct) **two-bit errors**.

#### **Hamming Distance**

**Definition**: Number of bit positions in which two codewords differ.

```
Codeword 1: 10101
Codeword 2: 10011
            ↑  ↑↑
Hamming Distance = 3
```

**Properties**:
- To detect d errors: Need Hamming distance ≥ d + 1
- To correct d errors: Need Hamming distance ≥ 2d + 1

#### **Hamming Code Construction**

**Step 1**: Determine number of parity bits (r)

Formula: **2^r ≥ m + r + 1**

where:
- m = number of data bits
- r = number of parity bits

**Example**: m = 7 data bits
- Try r = 3: 2³ = 8 ≥ 7 + 3 + 1 = 11? No
- Try r = 4: 2⁴ = 16 ≥ 7 + 4 + 1 = 12? **Yes** ✓

**Step 2**: Position parity bits at powers of 2

Positions: P1, P2, D1, P4, D2, D3, D4, P8, D5, D6, D7, ...
           1   2   3   4   5   6   7   8   9   10  11

**Parity bits**: Positions 1, 2, 4, 8, 16, 32, ...
**Data bits**: Remaining positions

**Step 3**: Calculate each parity bit

- **P1** (position 1): Checks positions with bit 1 in position 1, 3, 5, 7, 9, 11, ...
- **P2** (position 2): Checks positions with bit 2 in position 2, 3, 6, 7, 10, 11, ...
- **P4** (position 4): Checks positions with bit 4 in position 4, 5, 6, 7, 12, 13, ...
- **P8** (position 8): Checks positions with bit 8 in position 8, 9, 10, 11, 12, ...

#### **Example: Encode 1011**

Data: 1011 (4 bits)
Need: 2⁴ = 16 ≥ 4 + r + 1
      r = 3 ✓

**Positions**:
```
Position:  1   2   3   4   5   6   7
Bit:      P1  P2  D1  P4  D2  D3  D4
Data:      ?   ?   1   ?   0   1   1
```

**Calculate P1** (positions 1, 3, 5, 7):
- Checks: P1, 1, 0, 1
- Count 1s: 2 (even)
- P1 = 0 (for even parity)

**Calculate P2** (positions 2, 3, 6, 7):
- Checks: P2, 1, 1, 1
- Count 1s: 3 (odd)
- P2 = 1 (to make even)

**Calculate P4** (positions 4, 5, 6, 7):
- Checks: P4, 0, 1, 1
- Count 1s: 2 (even)
- P4 = 0 (for even parity)

**Final Codeword**: **0110011**

```
Position:  1   2   3   4   5   6   7
Bit:      P1  P2  D1  P4  D2  D3  D4
Value:     0   1   1   0   0   1   1
```

#### **Error Detection and Correction**

**Received**: 0111011 (error in position 3)

**Check P1**: Positions 1, 3, 5, 7 → 0, 1, 0, 1 → Even ✓
**Check P2**: Positions 2, 3, 6, 7 → 1, 1, 1, 1 → Even ✓
**Check P4**: Positions 4, 5, 6, 7 → 0, 0, 1, 1 → Even ✓

Wait, let me recalculate:

**Received**: 0101011 (error in position 2)

**Check P1**: 0, 1, 0, 1 → 2 (even) → 0
**Check P2**: 0, 1, 1, 1 → 3 (odd) → 1
**Check P4**: 0, 0, 1, 1 → 2 (even) → 0

**Error Position** = P4×4 + P2×2 + P1×1 = 0×4 + 1×2 + 0×1 = **2**

Error at position 2! Flip bit: 0101011 → 0**1**01011

**Corrected**: 0110011 ✓

**Advantages**:
✅ Can correct single-bit errors
✅ Can detect two-bit errors
✅ Automatic correction (no retransmission)

**Disadvantages**:
❌ Cannot correct multiple errors
❌ High overhead (for small data)
❌ Complex calculation

**Used in**:
- RAM (ECC memory)
- Satellites
- Deep space communication

---

### 2. **ARQ (Automatic Repeat Request)**

Error correction through **retransmission**.

**Types**:
1. **Stop-and-Wait ARQ**
2. **Go-Back-N ARQ**
3. **Selective Repeat ARQ**

(Covered in detail in Flow Control section)

---

## Flow Control

**Purpose**: Prevent fast sender from overwhelming slow receiver.

**Problem**:
- Sender transmits faster than receiver can process
- Receiver's buffer overflows
- Data loss

**Solution**: Flow control mechanisms

---

### Flow Control Protocols

```
Flow Control
│
├── Stop-and-Wait
├── Sliding Window
│   ├── Go-Back-N
│   └── Selective Repeat
```

---

### 1. **Stop-and-Wait Protocol**

**Mechanism**:
1. Sender sends one frame
2. Waits for ACK from receiver
3. Only after receiving ACK, sends next frame

```
Sender          Receiver
  │                │
  ├──Frame 0──────>│
  │                │ (Process)
  │<──────ACK 0────┤
  │                │
  ├──Frame 1──────>│
  │                │ (Process)
  │<──────ACK 1────┤
  │                │
```

**Efficiency**:

**Transmission Time (Tt)** = Frame size / Bandwidth

**Propagation Time (Tp)** = Distance / Speed

**Efficiency** = Tt / (Tt + 2×Tp)

**Example**:
- Frame size = 1000 bits
- Bandwidth = 1 Mbps → Tt = 1000/10⁶ = 1 ms
- Distance = 10,000 km, Speed = 2×10⁸ m/s → Tp = 50 ms
- Efficiency = 1 / (1 + 100) = **0.99%** ❌

**Piggybacking**: ACK can be attached to data frame going in opposite direction.

**Advantages**:
✅ Simple to implement
✅ Low overhead (only 1 frame at a time)

**Disadvantages**:
❌ **Very inefficient** (especially for long distances)
❌ Channel underutilized
❌ Wastes bandwidth

**Use Case**: Simple, low-speed networks

---

### 2. **Stop-and-Wait ARQ**

Extension of Stop-and-Wait with **error control**.

**Mechanisms**:
- **ACK**: Positive acknowledgment (frame received correctly)
- **NAK**: Negative acknowledgment (error detected)
- **Timeout**: Retransmit if no ACK received within time

**Scenarios**:

#### a) **Normal Operation**
```
Sender          Receiver
  │                │
  ├──Frame 0──────>│
  │                │ (OK)
  │<──────ACK──────┤
  │                │
```

#### b) **Damaged Frame**
```
Sender          Receiver
  │                │
  ├──Frame 0──────>│ (Damaged)
  │                │
  │<──────NAK──────┤
  │                │
  ├──Frame 0──────>│ (Retransmit)
  │                │ (OK)
  │<──────ACK──────┤
```

#### c) **Lost Frame**
```
Sender          Receiver
  │                │
  ├──Frame 0────X  │ (Lost)
  │                │
  │ (Timeout)      │
  ├──Frame 0──────>│ (Retransmit)
  │                │
  │<──────ACK──────┤
```

#### d) **Lost ACK**
```
Sender          Receiver
  │                │
  ├──Frame 0──────>│
  │                │
  │  X────ACK──────┤ (ACK lost)
  │ (Timeout)      │
  ├──Frame 0──────>│ (Retransmit)
  │                │ (Duplicate!)
  │<──────ACK──────┤
```

**Problem**: Duplicate frames!
**Solution**: **Sequence numbers** (0 and 1 alternating)

**Advantages**:
✅ Error control
✅ Simple

**Disadvantages**:
❌ Very inefficient
❌ Slow

---

## Sliding Window Protocols

**Concept**: Sender can transmit multiple frames before waiting for ACK.

**Window**: Set of consecutive sequence numbers

**Window Size (W)**:
- Sender window (Ws): Max frames sender can send without ACK
- Receiver window (Wr): Max frames receiver can accept

```
Sequence Numbers: 0 1 2 3 4 5 6 7 0 1 2 3 ...
                  [─────────]
                   Window (W=4)
```

**Efficiency** = W × Tt / (Tt + 2×Tp)

(Much better than Stop-and-Wait!)

---

### 1. **Go-Back-N ARQ** ⭐

**Mechanism**:
- Sender can send up to N frames without ACK
- Receiver accepts frames **in order only**
- If error detected, receiver discards frame and all subsequent frames
- Sender retransmits from the error frame onwards

**Sender Window (Ws)**: N
**Receiver Window (Wr)**: 1 (accepts only next expected frame)

**Example** (N = 4):

```
Sender                      Receiver
  ├──Frame 0──────────────>│ (OK, ACK 0)
  ├──Frame 1──────────────>│ (OK, ACK 1)
  ├──Frame 2──────────────>│ (OK, ACK 2)
  ├──Frame 3──────────────>│ (Error!)
  ├──Frame 4──────────────>│ (Discard - out of order)
  ├──Frame 5──────────────>│ (Discard - out of order)
  │                         │
  │<─────────NAK 3 / Timeout
  │                         │
  ├──Frame 3──────────────>│ (Retransmit from 3)
  ├──Frame 4──────────────>│
  ├──Frame 5──────────────>│
```

**Cumulative ACK**: ACK n means all frames up to n-1 received correctly.

**Sequence Numbers**: 
- Need **at least (Ws + 1)** sequence numbers
- If Ws = N, need **N + 1** sequence numbers
- Usually: **2^m** sequence numbers (m-bit sequence number)

**Example**: If Ws = 7, need 8 sequence numbers (0-7)

**Advantages**:
✅ Higher efficiency than Stop-and-Wait
✅ Simple at receiver (only 1 buffer)
✅ Cumulative ACK reduces traffic

**Disadvantages**:
❌ Retransmits even error-free frames (wasteful)
❌ Receiver discards out-of-order frames

**Used in**: 
- **TCP** (with modifications)
- **HDLC**

---

### 2. **Selective Repeat ARQ** ⭐

**Mechanism**:
- Sender can send up to N frames without ACK
- Receiver accepts frames **out of order**
- Only erroneous frames are retransmitted
- Receiver buffers out-of-order frames

**Sender Window (Ws)**: N
**Receiver Window (Wr)**: N (accepts out of order)

**Example** (N = 4):

```
Sender                      Receiver
  ├──Frame 0──────────────>│ (OK, ACK 0)
  ├──Frame 1──────────────>│ (OK, ACK 1)
  ├──Frame 2──────────────>│ (Error!)
  ├──Frame 3──────────────>│ (OK, Buffer it, ACK 3)
  ├──Frame 4──────────────>│ (OK, Buffer it, ACK 4)
  │                         │
  │<─────────NAK 2 / Timeout
  │                         │
  ├──Frame 2──────────────>│ (Retransmit ONLY frame 2)
  │                         │ (Now deliver 2,3,4 to upper layer)
  │<─────────ACK 4──────────┤ (Cumulative)
```

**Individual ACK**: Each frame ACKed separately.

**Sequence Numbers**:
- Need **at least 2×Ws** sequence numbers
- If Ws = N, need **2N** sequence numbers

**Example**: If Ws = 4, need 8 sequence numbers (0-7)

**Why 2N?** To avoid ambiguity between old and new frames.

**Advantages**:
✅ **Most efficient** among ARQ protocols
✅ Only retransmits erroneous frames
✅ No wastage of bandwidth

**Disadvantages**:
❌ Complex at receiver (multiple buffers)
❌ Requires more sequence numbers
❌ Individual ACKs (more overhead)

**Used in**:
- **TCP** (SACK - Selective ACK)
- Modern protocols

---

### Comparison: Flow Control Protocols

| Protocol | Efficiency | Complexity | Retransmission | Sequence Numbers |
|----------|-----------|------------|----------------|------------------|
| **Stop-and-Wait** | Very Low | Low | Entire frame | 2 (0, 1) |
| **Go-Back-N** | Medium-High | Medium | From error onward | Ws + 1 |
| **Selective Repeat** | Highest | High | Only error frames | 2 × Ws |

**For Interviews**:
- Understand **all three**
- **Go-Back-N** and **Selective Repeat** are most asked
- Know sequence number requirements

---

## MAC (Medium Access Control)

**Problem**: Multiple devices sharing the same medium (broadcast network).

**Question**: Who gets to transmit and when?

**Solution**: MAC protocols

---

### MAC Protocol Categories

```
MAC Protocols
│
├── Random Access (Contention)
│   ├── ALOHA
│   │   ├── Pure ALOHA
│   │   └── Slotted ALOHA
│   ├── CSMA (Carrier Sense Multiple Access)
│   │   ├── 1-Persistent CSMA
│   │   ├── Non-Persistent CSMA
│   │   └── P-Persistent CSMA
│   ├── CSMA/CD (Collision Detection) - Ethernet
│   └── CSMA/CA (Collision Avoidance) - Wi-Fi
│
├── Controlled Access
│   ├── Reservation
│   ├── Polling
│   └── Token Passing
│
└── Channelization
    ├── FDMA
    ├── TDMA
    └── CDMA
```

---

### 1. Random Access Protocols

No control, devices transmit whenever they want. Collisions possible.

---

#### A. **ALOHA**

##### **Pure ALOHA**

**Mechanism**:
- Station transmits whenever it has data
- If collision occurs, wait random time and retransmit
- No carrier sensing

```
Station A: ──────█████─────────
Station B: ────────████████────
                   ↑ ↑
              Collision!
```

**Vulnerable Time**: 2 × Frame Time
(Collision if another station transmits within 2 frames)

**Maximum Throughput**: **18.4%**

**Formula**:
```
Throughput = G × e^(-2G)
where G = Average number of frames generated per frame time

Maximum at G = 0.5 → S = 0.184 (18.4%)
```

**Advantages**:
✅ Simple
✅ No coordination needed
✅ Decentralized

**Disadvantages**:
❌ Very low efficiency (18.4%)
❌ High collision rate
❌ No carrier sensing

---

##### **Slotted ALOHA**

**Improvement**: Time divided into slots. Transmission only at slot boundaries.

```
Time Slots:  |──0──|──1──|──2──|──3──|
Station A:        ████
Station B:        ████
                   ↑
              Collision (but only in one slot)
```

**Vulnerable Time**: 1 × Frame Time
(Half of Pure ALOHA)

**Maximum Throughput**: **36.8%**

**Formula**:
```
Throughput = G × e^(-G)
Maximum at G = 1 → S = 0.368 (36.8%)
```

**Comparison**:

| Type | Vulnerable Time | Max Throughput |
|------|----------------|----------------|
| **Pure ALOHA** | 2 × Tfr | 18.4% |
| **Slotted ALOHA** | 1 × Tfr | 36.8% |

**Used in**: Early satellite networks (historical)

---

#### B. **CSMA (Carrier Sense Multiple Access)**

**Improvement over ALOHA**: Listen before transmitting!

**Rule**: **"Listen before you speak"**

**Types**:

##### **1-Persistent CSMA**

**Algorithm**:
1. If channel idle → Transmit immediately (probability = 1)
2. If channel busy → Wait until idle, then transmit immediately
3. If collision → Wait random time, repeat

**Problem**: If multiple stations waiting, collision guaranteed when channel becomes free.

**Collision Probability**: High

---

##### **Non-Persistent CSMA**

**Algorithm**:
1. If channel idle → Transmit immediately
2. If channel busy → Wait **random** time, then sense again
3. If collision → Wait random time, repeat

**Advantage**: Reduces collision (stations don't wait for idle)
**Disadvantage**: Channel may be idle while stations waiting

**Collision Probability**: Low
**Channel Utilization**: Lower

---

##### **P-Persistent CSMA**

**Algorithm**:
1. If channel idle → Transmit with probability P
   - If don't transmit, wait for next slot
2. If channel busy → Wait until idle, then apply step 1
3. If collision → Wait random time, repeat

**Balance**: Between 1-Persistent and Non-Persistent

**Example**: P = 0.5
- 50% chance to transmit when idle
- 50% chance to wait for next slot

**Used in**: Some wireless networks

---

#### C. **CSMA/CD (Collision Detection)** ⭐

**Full Form**: Carrier Sense Multiple Access with Collision Detection

**Used in**: **Ethernet** (Wired LANs)

**Mechanism**:
1. **Carrier Sense**: Listen before transmitting
2. **Multiple Access**: Multiple stations share medium
3. **Collision Detection**: Detect collision while transmitting
4. If collision detected → Stop immediately, send jam signal, wait random time

```
Station A: ████████ (detects collision, stops)
Station B:     ████████ (detects collision, stops)
           ↑
        Collision detected!
        Both stop and send JAM signal
```

**Algorithm**:

```
1. If channel idle:
   - Start transmitting
   - Monitor for collision while transmitting
2. If channel busy:
   - Wait until idle
3. If collision detected:
   - Stop transmission
   - Send JAM signal (48 bits)
   - Wait random backoff time (Binary Exponential Backoff)
   - Try again
```

**Binary Exponential Backoff**:
- After nth collision: Wait random time in range [0, 2^n - 1] slot times
- Example: After 3rd collision, wait 0-7 slot times
- Maximum n = 10, then give up after 16 attempts

**Minimum Frame Size**:

**Critical condition**: Station must detect collision before finishing transmission.

```
Minimum Frame Size = 2 × Propagation Time × Bandwidth

or

Min Frame Size ≥ 2 × (Distance / Speed) × Bandwidth
```

**Example** (Ethernet):
- Distance = 2500m
- Speed = 2 × 10⁸ m/s
- Bandwidth = 10 Mbps
- Tp = 2500 / (2×10⁸) = 12.5 μs
- Min Frame = 2 × 12.5 × 10⁶ = 250,000 bits

**Ethernet Standard**: 64 bytes (512 bits) minimum frame size

**Efficiency**:
```
Efficiency = 1 / (1 + 6.44 × a)

where a = Tp / Tt (propagation time / transmission time)
```

**Advantages**:
✅ Good efficiency (80-90% for low a)
✅ Simple
✅ Works well for wired LANs

**Disadvantages**:
❌ Efficiency decreases with distance
❌ Cannot be used in wireless (hidden terminal problem)
❌ Requires full-duplex detection

**Used in**: 
- **Classic Ethernet** (10BASE-T, 100BASE-TX with hubs)
- **NOT in modern switched Ethernet** (full-duplex, no collisions)

---

#### D. **CSMA/CA (Collision Avoidance)** ⭐

**Full Form**: Carrier Sense Multiple Access with Collision Avoidance

**Used in**: **Wi-Fi (IEEE 802.11)** - Wireless LANs

**Why not CSMA/CD in Wireless?**
1. **Hidden Terminal Problem**: A and C can't hear each other
2. **Cannot detect collision while transmitting** (wireless NIC can't listen while sending)
3. **Signal strength varies** greatly

**Mechanism**: **Avoid collisions before they occur**

**CSMA/CA Algorithm**:

```
1. Carrier Sense: Listen to channel
2. If channel idle for DIFS time:
   - Wait random backoff time
   - If still idle, transmit
3. If channel busy:
   - Wait until idle + DIFS
   - Wait random backoff time
4. After successful transmission:
   - Receiver sends ACK
```

**Timing**:
- **DIFS** (Distributed Inter-Frame Space): Minimum idle time before transmission
- **SIFS** (Short Inter-Frame Space): Shorter gap for ACK/CTS (higher priority)
- **Backoff Time**: Random time in [0, CW-1] slots (CW = Contention Window)

**RTS/CTS Mechanism** (for large frames):

```
Sender                    Receiver
  │                          │
  ├────RTS (Request to Send)─>│
  │                          │
  │<────CTS (Clear to Send)──┤
  │                          │
  ├────DATA────────────────>│
  │                          │
  │<────ACK──────────────────┤
```

**Purpose**: Solves **Hidden Terminal Problem**

**Hidden Terminal Problem**:
```
A ←──────→ B ←──────→ C
    Range      Range

A and C can't hear each other, but both can hear B.
If A and C both transmit to B → Collision at B!
```

**Solution (RTS/CTS)**:
- A sends RTS to B
- B sends CTS (heard by both A and C)
- C hears CTS, knows to wait
- A transmits data

**Exposed Terminal Problem**: Also solved by RTS/CTS

**Advantages**:
✅ Works in wireless
✅ Avoids collisions
✅ Solves hidden terminal problem

**Disadvantages**:
❌ Lower efficiency than CSMA/CD
❌ More overhead (RTS/CTS/ACK)
❌ Complex

**Used in**: 
- **Wi-Fi (802.11a/b/g/n/ac/ax)**
- Wireless networks

---

### 2. Controlled Access Protocols

Central control decides who transmits.

#### A. **Polling**

- **Primary station** (controller) polls each secondary station
- Secondary transmits only when polled
- No collisions

**Used in**: Some industrial networks, Bluetooth

#### B. **Token Passing**

- **Token** (special frame) circulates
- Station can transmit only when it has token
- After transmitting, passes token to next station

**Types**:
- **Token Ring** (IEEE 802.5) - Ring topology
- **Token Bus** (IEEE 802.4) - Bus topology

**Advantages**:
✅ No collisions
✅ Deterministic (bounded delay)
✅ Fair access

**Disadvantages**:
❌ Token overhead
❌ If token lost, network fails
❌ Complexity

**Used in**: 
- **Token Ring** (legacy)
- **FDDI** (Fiber Distributed Data Interface)

---

### 3. Channelization

Divide channel into sub-channels. (Covered in Physical Layer - Multiplexing)

---

### MAC Protocol Comparison

| Protocol | Type | Efficiency | Collision | Use |
|----------|------|-----------|-----------|-----|
| **Pure ALOHA** | Random | 18.4% | High | Satellite (legacy) |
| **Slotted ALOHA** | Random | 36.8% | Medium | Satellite (legacy) |
| **CSMA/CD** | Random | 80-90% | Low | Ethernet (wired) |
| **CSMA/CA** | Random | 50-70% | Very Low | Wi-Fi (wireless) |
| **Token Passing** | Controlled | High | None | Token Ring (legacy) |

---

## Ethernet

**Most important LAN technology!**

### What is Ethernet?

**Ethernet** is a family of LAN technologies defined by IEEE 802.3 standard.

**Characteristics**:
- **Topology**: Originally bus, now star (with switches)
- **Access Method**: CSMA/CD (in shared medium)
- **Addressing**: 48-bit MAC addresses
- **Frame Format**: Defined structure

---

### Ethernet Frame Format

```
┌─────────┬─────────┬──────┬──────┬─────────┬─────┬─────┐
│Preamble │ SFD     │ DA   │ SA   │ Type/   │Data │ FCS │
│ 7 bytes │ 1 byte  │6 bytes│6 bytes│ Length  │     │4 bytes│
│         │         │      │      │ 2 bytes │     │     │
└─────────┴─────────┴──────┴──────┴─────────┴─────┴─────┘
   ↓         ↓        ↓      ↓       ↓        ↓      ↓
Sync    Start   Dest   Source  Type   Payload  Error
       Frame   MAC     MAC     Code            Check
```

**Field Details**:

1. **Preamble** (7 bytes): 
   - Pattern: 10101010 (repeated 7 times)
   - Synchronization

2. **SFD** (Start Frame Delimiter) (1 byte):
   - Pattern: 10101011
   - Marks start of frame

3. **Destination Address (DA)** (6 bytes):
   - MAC address of receiver
   - Can be unicast, multicast, or broadcast

4. **Source Address (SA)** (6 bytes):
   - MAC address of sender
   - Always unicast

5. **Type/Length** (2 bytes):
   - **Type**: Protocol of payload (e.g., 0x0800 for IPv4, 0x0806 for ARP)
   - **Length**: Size of data field (in Ethernet II vs 802.3)

6. **Data** (46-1500 bytes):
   - Payload from upper layers
   - **Minimum**: 46 bytes (padded if less)
   - **Maximum**: 1500 bytes (MTU)

7. **FCS** (Frame Check Sequence) (4 bytes):
   - CRC-32 for error detection
   - Covers DA, SA, Type, and Data fields

**Total Frame Size**:
- **Minimum**: 64 bytes (including headers)
- **Maximum**: 1518 bytes (without VLAN tag)
- **With VLAN tag**: 1522 bytes

**MAC Address Format**:
```
00:1A:2B:3C:4D:5E
↑              ↑
First byte    Last byte

First byte:
Bit 0 (LSB): I/G (Individual/Group)
  0 = Unicast
  1 = Multicast
Bit 1: U/L (Universal/Local)
  0 = Globally unique (OUI assigned)
  1 = Locally administered
```

**Special Addresses**:
- **Broadcast**: FF:FF:FF:FF:FF:FF
- **Multicast**: First byte LSB = 1 (e.g., 01:00:5E:xx:xx:xx for IPv4 multicast)

---

### Ethernet Standards

| Standard | Speed | Cable | Max Distance | Notes |
|----------|-------|-------|--------------|-------|
| **10BASE-T** | 10 Mbps | Cat 3 UTP | 100m | Legacy |
| **100BASE-TX** | 100 Mbps | Cat 5 UTP | 100m | Fast Ethernet |
| **1000BASE-T** | 1 Gbps | Cat 5e UTP | 100m | Gigabit Ethernet |
| **10GBASE-T** | 10 Gbps | Cat 6a/7 | 100m | 10 Gigabit |
| **100BASE-FX** | 100 Mbps | Fiber | 2 km | Fast Ethernet |
| **1000BASE-LX** | 1 Gbps | Fiber | 10 km | Gigabit Ethernet |

**Naming Convention**:
- **Number**: Speed (10, 100, 1000, 10000 Mbps)
- **BASE**: Baseband (vs BROAD for broadband)
- **T**: Twisted Pair
- **F**: Fiber
- **Suffix**: Additional info (X, LX, etc.)

---

### MAC Address

**Format**: 48 bits = 6 bytes = 12 hexadecimal digits

**Structure**:
```
┌─────────────────┬─────────────────┐
│      OUI        │      NIC        │
│ (24 bits)       │   (24 bits)     │
└─────────────────┴─────────────────┘
     ↓                   ↓
Manufacturer      Unique ID
(IEEE assigned)   (Manufacturer assigned)
```

**OUI** (Organizationally Unique Identifier): First 3 bytes
- Assigned by IEEE to manufacturers
- Example: 00:1A:2B (Cisco)

**NIC** (Network Interface Controller): Last 3 bytes
- Assigned by manufacturer
- Should be unique

**Types**:
1. **Unicast**: Single destination (LSB of first byte = 0)
2. **Multicast**: Group destination (LSB of first byte = 1)
3. **Broadcast**: All devices (FF:FF:FF:FF:FF:FF)

**How to find MAC**:
- Windows: `ipconfig /all`
- Linux/Mac: `ifconfig` or `ip addr`

---

## Switching

**Switching** is the process of forwarding frames from source to destination.

### Types of Switching

```
Switching
│
├── Circuit Switching (Physical Layer)
└── Packet Switching (Data Link/Network)
    ├── Store-and-Forward
    └── Cut-Through
```

(Circuit Switching covered in Physical Layer)

---

### Data Link Layer Switching

#### 1. **Store-and-Forward Switching**

**Mechanism**:
1. Receive entire frame
2. Check FCS (error check)
3. Look up destination MAC in forwarding table
4. Forward frame to appropriate port

```
Port 1 ──> [Store] [Check] [Lookup] [Forward] ──> Port 3
              ↓       ↓        ↓         ↓
           Buffer   FCS     MAC Table   Transmit
```

**Advantages**:
✅ **Error detection** (checks FCS before forwarding)
✅ No corrupted frames forwarded
✅ Reliable

**Disadvantages**:
❌ **Latency** (must receive entire frame)
❌ Slower

**Used in**: Most **modern switches**

---

#### 2. **Cut-Through Switching**

**Mechanism**:
1. Read only destination MAC (first 6 bytes after preamble)
2. Immediately start forwarding (without checking FCS)
3. No error checking

**Types**:

##### a) **Fast-Forward**:
- Forwards as soon as destination MAC read
- Lowest latency
- No error checking

##### b) **Fragment-Free**:
- Reads first 64 bytes (collision window)
- Filters out collision fragments
- Some error detection

**Advantages**:
✅ **Very low latency**
✅ Fast

**Disadvantages**:
❌ No error detection (forwards corrupted frames)
❌ Can propagate errors

**Used in**: High-performance switches, data centers

---

### Switch Operation

#### **MAC Address Table (CAM Table)**

**Content Addressable Memory**: Maps MAC addresses to ports

```
┌─────────────────┬──────┬─────────┐
│  MAC Address    │ Port │  Age    │
├─────────────────┼──────┼─────────┤
│ 00:1A:2B:3C:4D:5E│  1  │  120s   │
│ 00:1A:2B:3C:4D:5F│  2  │   60s   │
│ 00:1A:2B:3C:4D:60│  3  │   90s   │
└─────────────────┴──────┴─────────┘
```

#### **Learning Process**:

1. **Frame arrives on Port 1**:
   - Read source MAC
   - Add to table: MAC ↔ Port 1

2. **Forward decision**:
   - Look up destination MAC
   - **If found**: Forward to that port only (unicast)
   - **If not found**: Flood to all ports except incoming (broadcast)

3. **Aging**:
   - Entries removed after timeout (typically 300s)
   - Prevents stale entries

**Example**:

```
Initial State: Empty table

Step 1: PC-A (MAC: AA) sends to PC-B (MAC: BB) via Port 1
  - Learn: AA → Port 1
  - Destination BB not in table → Flood to all ports (except 1)

Step 2: PC-B responds via Port 2
  - Learn: BB → Port 2
  - Destination AA in table → Forward to Port 1 only

Step 3: PC-A sends to PC-B again
  - AA already learned
  - BB in table → Forward to Port 2 only (unicast)

Table:
┌─────┬──────┐
│ MAC │ Port │
├─────┼──────┤
│ AA  │  1   │
│ BB  │  2   │
└─────┴──────┘
```

**Broadcast/Multicast**: Always flooded to all ports (except incoming)

---

### Collision Domain vs Broadcast Domain

#### **Collision Domain**

**Definition**: Network segment where collisions can occur.

**Devices**:
- **Hub**: Single collision domain (all ports)
- **Switch**: Separate collision domain per port
- **Router**: Separate collision domain per interface

```
Hub:
PC-A ──┐
       ├── HUB ── (All in same collision domain)
PC-B ──┘

Switch:
PC-A ──── Port 1 ──┐
                   ├── SWITCH (Each port = separate collision domain)
PC-B ──── Port 2 ──┘
```

#### **Broadcast Domain**

**Definition**: Network segment where broadcast reaches.

**Devices**:
- **Hub**: Single broadcast domain
- **Switch**: Single broadcast domain (all ports)
- **Router**: Separate broadcast domain per interface

```
Switch:
PC-A ──┐
       ├── SWITCH ── (All in same broadcast domain)
PC-B ──┘             (Broadcast reaches all)

Router:
LAN 1 ── Interface 1 ──┐
                       ├── ROUTER (Separates broadcast domains)
LAN 2 ── Interface 2 ──┘
```

**Summary**:

| Device | Collision Domains | Broadcast Domains |
|--------|------------------|-------------------|
| **Hub** | 1 (all ports) | 1 (all ports) |
| **Switch** | N (per port) | 1 (all ports) |
| **Router** | N (per interface) | N (per interface) |

---

### Spanning Tree Protocol (STP)

**Problem**: Loops in switched networks cause broadcast storms.

```
Switch A ──── Switch B
   │             │
   └── Switch C ─┘
   (Loop!)
```

**Broadcast Storm**:
1. PC sends broadcast
2. Switches forward to all ports
3. Broadcast circles forever (no TTL at Layer 2)
4. Network congested

**Solution**: **STP (IEEE 802.1D)**

**Mechanism**:
1. Elect **Root Bridge** (switch with lowest Bridge ID)
2. Calculate shortest path to root
3. **Block** redundant links
4. If primary link fails, unblock backup link

**Result**: Loop-free logical topology (tree structure)

**Newer Versions**:
- **RSTP** (Rapid STP, 802.1w): Faster convergence
- **MSTP** (Multiple STP, 802.1s): Multiple VLANs

**States**:
- **Blocking**: Receives BPDUs, doesn't forward
- **Listening**: Processes BPDUs
- **Learning**: Learns MAC addresses
- **Forwarding**: Normal operation
- **Disabled**: Shutdown

---

## VLAN (Virtual LAN)

### What is VLAN?

**VLAN** (Virtual LAN) is a logical grouping of devices in the same broadcast domain, **regardless of physical location**.

**Purpose**:
- **Segment network**: Separate broadcast domains
- **Security**: Isolate traffic
- **Flexibility**: Group users logically
- **Performance**: Reduce broadcast traffic

### Without VLAN vs With VLAN

**Without VLAN**:
```
Switch
├── Port 1: Sales PC
├── Port 2: Sales PC
├── Port 3: HR PC
└── Port 4: HR PC

All in same broadcast domain!
(HR sees Sales broadcasts)
```

**With VLAN**:
```
Switch
├── Port 1: VLAN 10 (Sales)
├── Port 2: VLAN 10 (Sales)
├── Port 3: VLAN 20 (HR)
└── Port 4: VLAN 20 (HR)

Separate broadcast domains!
(HR doesn't see Sales traffic)
```

### VLAN Types

#### 1. **Port-Based VLAN**
- Assign VLAN based on physical port
- Most common

#### 2. **MAC-Based VLAN**
- Assign VLAN based on MAC address
- Device keeps VLAN even if moved

#### 3. **Protocol-Based VLAN**
- Assign based on protocol (IP, IPX, etc.)

---

### VLAN Tagging - IEEE 802.1Q

**Problem**: How to carry VLAN info across switches?

**Solution**: **802.1Q Tag** inserted into Ethernet frame

**Frame Format (with 802.1Q tag)**:
```
┌─────────┬───┬────┬──────┬──────┬─────────┬─────┬─────┐
│Preamble │SFD│ DA │ SA   │802.1Q│Type/Len │Data │ FCS │
└─────────┴───┴────┴──────┴──────┴─────────┴─────┴─────┘
                           ↑
                      4-byte tag
```

**802.1Q Tag Structure** (4 bytes):
```
┌─────────┬─────┬─────┬──────────┐
│  TPID   │ PRI │ CFI │ VLAN ID  │
│ 2 bytes │3 bits│1 bit│ 12 bits  │
└─────────┴─────┴─────┴──────────┘
```

- **TPID** (Tag Protocol ID): 0x8100 (identifies 802.1Q)
- **PRI** (Priority): QoS priority (0-7)
- **CFI** (Canonical Format Indicator): Compatibility
- **VLAN ID**: 12 bits = 4096 VLANs (0-4095)
  - **0**: No VLAN
  - **1**: Default VLAN (usually management)
  - **2-1001**: Normal range (Ethernet)
  - **1002-1005**: Reserved (Token Ring, FDDI)
  - **1006-4094**: Extended range
  - **4095**: Reserved

### Trunk vs Access Ports

#### **Access Port**
- Connects to **end devices** (PCs, printers)
- Carries traffic for **one VLAN** only
- **Untags** frames (removes 802.1Q tag before sending)

#### **Trunk Port**
- Connects to **other switches or routers**
- Carries traffic for **multiple VLANs**
- **Tags** frames with VLAN ID
- Uses **Native VLAN** for untagged traffic

```
PC (VLAN 10) ──Access Port── Switch ──Trunk Port── Switch
                              ↓                      ↓
                        Untagged frames        Tagged frames
```

**Native VLAN**: Default VLAN for untagged traffic on trunk (usually VLAN 1)

---

### Inter-VLAN Routing

**Problem**: Devices in different VLANs cannot communicate (different broadcast domains).

**Solution**: **Router** or **Layer 3 Switch**

#### Method 1: **Router on a Stick**

```
         Router
           │
      Trunk Port
           │
         Switch
       ┌───┴───┐
    VLAN 10  VLAN 20
       │       │
      PC-A    PC-B
```

- Single physical interface
- Multiple sub-interfaces (one per VLAN)
- Router routes between VLANs

**Configuration (Concept)**:
```
Interface Gi0/0.10  → VLAN 10
Interface Gi0/0.20  → VLAN 20
```

#### Method 2: **Layer 3 Switch** (SVI - Switched Virtual Interface)

- Switch with routing capability
- Faster than router (hardware-based)

**Configuration (Concept)**:
```
VLAN 10: IP 192.168.10.1
VLAN 20: IP 192.168.20.1
Enable IP routing
```

---

### VLAN Advantages

✅ **Broadcast control**: Reduces broadcast domain size
✅ **Security**: Traffic isolation
✅ **Flexibility**: Logical grouping independent of location
✅ **Cost**: Single switch can replace multiple physical switches
✅ **Performance**: Reduced collisions and broadcasts

---

## ARP (Address Resolution Protocol)

**Purpose**: Map **IP address** (Layer 3) to **MAC address** (Layer 2).

**Problem**: 
- Network Layer uses IP addresses
- Data Link Layer uses MAC addresses
- How to find MAC address from IP?

**Solution**: **ARP**

---

### ARP Operation

**Scenario**: PC-A (192.168.1.10) wants to send packet to PC-B (192.168.1.20)

**Steps**:

1. **PC-A checks ARP cache**:
   - Is 192.168.1.20's MAC address known?
   - If yes → Use it
   - If no → Send ARP request

2. **ARP Request** (Broadcast):
   ```
   Sender: PC-A
   Source IP: 192.168.1.10
   Source MAC: AA:AA:AA:AA:AA:AA
   Target IP: 192.168.1.20
   Target MAC: FF:FF:FF:FF:FF:FF (broadcast)
   
   Message: "Who has 192.168.1.20? Tell 192.168.1.10"
   ```

3. **All devices receive** (broadcast)
   - PC-B recognizes its IP
   - Others ignore

4. **ARP Reply** (Unicast):
   ```
   Sender: PC-B
   Source IP: 192.168.1.20
   Source MAC: BB:BB:BB:BB:BB:BB
   Target IP: 192.168.1.10
   Target MAC: AA:AA:AA:AA:AA:AA
   
   Message: "192.168.1.20 is at BB:BB:BB:BB:BB:BB"
   ```

5. **PC-A updates ARP cache**:
   ```
   192.168.1.20 → BB:BB:BB:BB:BB:BB
   ```

6. **PC-A sends data** using MAC address

---

### ARP Packet Format

```
┌──────────────┬──────────────┬─────────────┬──────────────┐
│ Hardware Type│Protocol Type │HW Addr Len  │Proto Addr Len│
│   2 bytes    │  2 bytes     │  1 byte     │   1 byte     │
├──────────────┼──────────────┼─────────────┼──────────────┤
│  Operation   │ Sender HW Addr (6 bytes)                  │
│   2 bytes    │                                            │
├──────────────┼────────────────────────────────────────────┤
│ Sender Proto Addr (4 bytes) │ Target HW Addr (6 bytes)   │
├──────────────────────────────┼────────────────────────────┤
│ Target Proto Addr (4 bytes)  │
└──────────────────────────────┘
```

**Fields**:
- **Hardware Type**: 1 for Ethernet
- **Protocol Type**: 0x0800 for IPv4
- **Operation**: 1 = Request, 2 = Reply
- **Sender HW Address**: Sender's MAC
- **Sender Protocol Address**: Sender's IP
- **Target HW Address**: Target's MAC (unknown in request)
- **Target Protocol Address**: Target's IP

---

### ARP Cache

**Purpose**: Store recent IP-to-MAC mappings

**Types**:
- **Dynamic**: Learned via ARP (timeout: 2-20 minutes)
- **Static**: Manually configured (permanent)

**View ARP Cache**:
- Windows: `arp -a`
- Linux: `arp -n` or `ip neigh`

**Example**:
```
IP Address      MAC Address       Type
192.168.1.1     00:1A:2B:3C:4D:5E dynamic
192.168.1.20    AA:BB:CC:DD:EE:FF dynamic
```

---

### RARP (Reverse ARP)

**Purpose**: Opposite of ARP - Find **IP address** from **MAC address**

**Use Case**: Diskless workstations (no stored IP)

**Process**:
1. Device knows its MAC but not IP
2. Sends RARP request (broadcast): "My MAC is XX, what's my IP?"
3. RARP server responds with IP address

**Status**: **Obsolete** (replaced by DHCP, BOOTP)

---

### Proxy ARP

**Purpose**: Router responds to ARP requests on behalf of devices in another subnet

**Use Case**: 
- Device doesn't know it's in different subnet
- Router pretends to be destination, then forwards packet

**Example**:
```
PC-A (192.168.1.10/24) wants to reach PC-B (192.168.2.20/24)
PC-A thinks both are in same subnet (misconfigured)
Router intercepts ARP request for 192.168.2.20
Router responds with its own MAC
PC-A sends packet to router
Router forwards to PC-B
```

---

### Gratuitous ARP

**Purpose**: Announce/update IP-MAC mapping without being asked

**Use Cases**:
1. **IP conflict detection**: Check if IP already in use
2. **Update ARP caches**: After IP/MAC change
3. **High Availability**: VRRP/HSRP (virtual IP failover)

**Process**:
- Send ARP request for **own IP address**
- If reply received → IP conflict!
- Otherwise → Update all devices' ARP caches

---

### ARP Spoofing/Poisoning Attack

**Attack**: Attacker sends fake ARP replies to associate attacker's MAC with victim's IP

**Result**: Traffic meant for victim is sent to attacker (Man-in-the-Middle)

**Mitigation**:
- Static ARP entries
- ARP inspection (DHCP snooping)
- Network monitoring

---

## Data Link Layer Devices

### 1. **Bridge**

**Function**: Connects two LAN segments, filters traffic based on MAC addresses

**Characteristics**:
- **Layer**: 2 (Data Link)
- **Ports**: Typically 2
- **Operation**: Store-and-forward
- **Function**: Divides collision domains

**Types**:
- **Transparent Bridge**: Invisible to devices (automatic learning)
- **Source Routing Bridge**: Path embedded in frame

**Advantages**:
✅ Reduces collision domain
✅ Filters traffic
✅ Extends network distance

**Disadvantages**:
❌ Slower than switch (software-based)
❌ Limited ports

**Status**: Obsolete (replaced by switches)

---

### 2. **Switch** ⭐

**Function**: Multi-port bridge with hardware-based forwarding

**Characteristics**:
- **Layer**: 2 (Data Link) - can be Layer 3 for routing
- **Ports**: Many (8, 16, 24, 48, ...)
- **Operation**: Store-and-forward or Cut-through
- **MAC Table**: CAM (Content Addressable Memory)

**Types**:

#### **Unmanaged Switch**:
- Plug-and-play
- No configuration
- Basic functionality

#### **Managed Switch**:
- Configurable
- VLANs, QoS, Port mirroring
- SNMP monitoring

#### **Layer 3 Switch**:
- Switch + Router capabilities
- Hardware-based routing
- Inter-VLAN routing

**Advantages**:
✅ Separate collision domain per port
✅ Full-duplex
✅ High speed
✅ Intelligent forwarding

**Disadvantages**:
❌ Single broadcast domain (without VLANs)
❌ More expensive than hub

**Used in**: Modern LANs

---

### 3. **NIC (Network Interface Card)**

**Function**: Connects device to network

**Characteristics**:
- **Layer**: 1 and 2 (Physical and Data Link)
- **MAC Address**: Burned-in
- **Function**: Frame creation, MAC addressing

**Types**:
- Ethernet NIC (RJ-45)
- Wi-Fi adapter
- Fiber NIC

---

### Comparison: Hub vs Switch vs Router

| Feature | Hub | Switch | Router |
|---------|-----|--------|--------|
| **Layer** | 1 (Physical) | 2 (Data Link) | 3 (Network) |
| **Addressing** | None | MAC | IP |
| **Forwarding** | Broadcast | MAC table | Routing table |
| **Collision Domain** | 1 (all ports) | N (per port) | N (per interface) |
| **Broadcast Domain** | 1 (all ports) | 1 (all ports) | N (per interface) |
| **Intelligence** | Dumb | Smart | Very Smart |
| **Speed** | Slow | Fast | Medium |
| **Use** | Obsolete | LAN | Internet, WAN |

---

## Important Formulas & Calculations

### 1. **Efficiency (Stop-and-Wait)**

```
Efficiency (η) = Tt / (Tt + 2 × Tp)

where:
Tt = Transmission Time = Frame Size / Bandwidth
Tp = Propagation Time = Distance / Speed
```

**Example**:
- Frame = 1000 bits
- Bandwidth = 1 Mbps → Tt = 1 ms
- Distance = 10,000 km, Speed = 2×10⁸ m/s → Tp = 50 ms
- η = 1 / (1 + 100) = 0.99% (very inefficient!)

---

### 2. **Efficiency (Sliding Window)**

```
Efficiency (η) = W × Tt / (Tt + 2 × Tp)

where W = Window Size

If W × Tt ≥ Tt + 2 × Tp:
  η = 1 (100% - maximum efficiency)

Otherwise:
  η = W × Tt / (Tt + 2 × Tp)
```

**Example** (Same as above, W = 127):
- η = 127 × 1 / (1 + 100) = 127/101 > 1
- Therefore, η = 100% (full utilization)

---

### 3. **Minimum Frames for 100% Efficiency**

```
W_min = 1 + (2 × Tp / Tt)

or

W_min = 1 + 2a

where a = Tp / Tt
```

---

### 4. **Sequence Number Requirements**

**Go-Back-N**:
```
Sequence Numbers ≥ Ws + 1

where Ws = Sender Window Size
```

**Selective Repeat**:
```
Sequence Numbers ≥ 2 × Ws
```

**Example**: Ws = 7
- Go-Back-N: Need 8 sequence numbers (0-7)
- Selective Repeat: Need 14 sequence numbers (0-13)

---

### 5. **CRC Calculation**

```
Steps:
1. Append (n-1) zeros to data (n = generator bits)
2. Divide by generator using XOR (modulo-2)
3. Remainder = CRC
4. Transmit: Data + CRC
```

**At Receiver**:
```
Divide received data by generator
If remainder = 0 → No error
Otherwise → Error
```

---

### 6. **Hamming Code - Parity Bits**

```
2^r ≥ m + r + 1

where:
m = data bits
r = parity bits
```

**Example**: m = 4
- 2³ = 8 ≥ 4 + 3 + 1 = 8 ✓
- Need r = 3 parity bits

---

### 7. **CSMA/CD Minimum Frame Size**

```
Min Frame Size = 2 × Tp × Bandwidth

or

Min Frame Size = 2 × (Distance / Speed) × Bandwidth
```

**Example** (Ethernet 10 Mbps, 2.5 km):
- Tp = 2500 / (2×10⁸) = 12.5 μs
- Min = 2 × 12.5×10⁻⁶ × 10×10⁶ = 250 bits

**Standard**: 64 bytes = 512 bits (Ethernet minimum)

---

### 8. **ALOHA Throughput**

**Pure ALOHA**:
```
S = G × e^(-2G)

Maximum at G = 0.5 → S_max = 0.184 (18.4%)
```

**Slotted ALOHA**:
```
S = G × e^(-G)

Maximum at G = 1 → S_max = 0.368 (36.8%)
```

where:
- S = Throughput
- G = Offered load (frames per frame time)

---

## Interview Questions & Answers

### Q1: **Explain the difference between Error Detection and Error Correction.**

**Answer**:

**Error Detection**:
- Identifies if error occurred
- Cannot fix error
- Requires retransmission
- Examples: Parity, Checksum, **CRC**
- Lower overhead

**Error Correction** (FEC):
- Detects **and fixes** errors
- No retransmission needed
- Examples: **Hamming Code**, Reed-Solomon
- Higher overhead

**Comparison**:

| Feature | Detection | Correction |
|---------|-----------|------------|
| Fix errors | No | Yes |
| Retransmit | Yes | No |
| Overhead | Low | High |
| Use | High-speed links | Satellite, wireless |

---

### Q2: **What is the difference between Go-Back-N and Selective Repeat?**

**Answer**:

| Feature | Go-Back-N | Selective Repeat |
|---------|-----------|------------------|
| **Receiver Window** | 1 (in-order only) | N (out-of-order) |
| **Retransmission** | From error onward | Only error frame |
| **Efficiency** | Lower | Higher |
| **Complexity** | Simple | Complex |
| **Sequence Numbers** | Ws + 1 | 2 × Ws |
| **Buffering** | Minimal | More buffers |

**Example**: Window size = 4, Frame 2 has error

**Go-Back-N**: Retransmits 2, 3, 4, 5 (even if 3, 4, 5 were correct)

**Selective Repeat**: Retransmits only frame 2

**Selective Repeat is more efficient but complex.**

---

### Q3: **Explain CSMA/CD vs CSMA/CA. When is each used?**

**Answer**:

**CSMA/CD** (Collision Detection):
- **Detects** collision while transmitting
- Stops immediately when collision detected
- Used in **wired Ethernet**
- Higher efficiency (~80-90%)

**CSMA/CA** (Collision Avoidance):
- **Avoids** collision before occurring
- Uses RTS/CTS mechanism
- Used in **Wi-Fi (wireless)**
- Lower efficiency (~50-70%)

**Why not CSMA/CD in Wireless?**
1. Cannot detect collision while transmitting (wireless NIC limitation)
2. Hidden terminal problem
3. Signal strength varies

**Summary**:
- **Wired** → CSMA/CD
- **Wireless** → CSMA/CA

---

### Q4: **What is the purpose of Minimum Frame Size in Ethernet?**

**Answer**:

**Purpose**: Ensure collision detection works properly.

**Problem**:
- In CSMA/CD, station must detect collision before finishing transmission
- If frame too small, transmission finishes before collision signal returns

**Condition**:
```
Transmission Time ≥ 2 × Propagation Time

Frame Size / Bandwidth ≥ 2 × (Distance / Speed)
```

**Ethernet Standard**:
- **Minimum Frame**: 64 bytes (512 bits)
- Ensures collision detection up to 2.5 km at 10 Mbps

**If frame < 64 bytes**: Pad with zeros to reach minimum

---

### Q5: **Explain the difference between Hub, Switch, and Router.**

**Answer**:

| Device | Layer | Forwarding | Collision Domain | Broadcast Domain | Use |
|--------|-------|-----------|------------------|------------------|-----|
| **Hub** | 1 | Broadcast to all | 1 (all ports) | 1 (all ports) | Obsolete |
| **Switch** | 2 | MAC table | N (per port) | 1 (all ports) | LAN |
| **Router** | 3 | Routing table | N (per interface) | N (per interface) | WAN, Internet |

**Hub**: Dumb repeater
**Switch**: Intelligent forwarding based on MAC
**Router**: Connects different networks based on IP

---

### Q6: **What is a VLAN and why is it used?**

**Answer**:

**VLAN** (Virtual LAN): Logical grouping of devices in same broadcast domain, regardless of physical location.

**Benefits**:
1. **Broadcast Control**: Reduces broadcast domain size
2. **Security**: Traffic isolation between VLANs
3. **Flexibility**: Logical grouping (Sales, HR, etc.)
4. **Cost**: One switch can replace multiple switches
5. **Performance**: Reduced congestion

**Example**:
- Without VLAN: All devices in one broadcast domain
- With VLAN: Sales (VLAN 10), HR (VLAN 20) - separate domains

**802.1Q**: Standard for VLAN tagging (4-byte tag in frame)

---

### Q7: **Explain ARP. How does it work?**

**Answer**:

**ARP** (Address Resolution Protocol): Maps IP address to MAC address.

**Need**: 
- Network Layer uses IP
- Data Link Layer uses MAC
- ARP bridges the gap

**Process**:

1. **Check ARP cache**: Is MAC known?
2. **If not, send ARP Request** (broadcast):
   - "Who has IP 192.168.1.20? Tell 192.168.1.10"
3. **Target sends ARP Reply** (unicast):
   - "192.168.1.20 is at MAC BB:BB:BB:BB:BB:BB"
4. **Update ARP cache**
5. **Send data** using MAC address

**ARP Cache**: Stores recent mappings (timeout: 2-20 min)

---

### Q8: **What is CRC? How is it better than Checksum?**

**Answer**:

**CRC** (Cyclic Redundancy Check): Error detection using polynomial division.

**Process**:
1. Choose generator polynomial (G)
2. Append (n-1) zeros to data
3. Divide by G using XOR (modulo-2)
4. Remainder = CRC
5. Transmit data + CRC
6. Receiver divides by G; if remainder = 0 → No error

**CRC vs Checksum**:

| Feature | CRC | Checksum |
|---------|-----|----------|
| **Reliability** | Very high (>99.99%) | Medium-high |
| **Detection** | All single, double, burst errors | Most errors |
| **Complexity** | High | Medium |
| **Use** | Ethernet, Wi-Fi | TCP, UDP, IP |

**CRC is more reliable but computationally intensive (done in hardware).**

---

### Q9: **What is the difference between Store-and-Forward and Cut-Through switching?**

**Answer**:

**Store-and-Forward**:
- Receives **entire frame**
- **Checks FCS** (error detection)
- Then forwards
- **Higher latency**, but **no error propagation**

**Cut-Through**:
- Reads only **destination MAC**
- **Immediately forwards**
- **No error check**
- **Lower latency**, but **forwards corrupted frames**

**Types of Cut-Through**:
1. **Fast-Forward**: Forwards after reading dest MAC
2. **Fragment-Free**: Reads first 64 bytes (collision window)

**Use**:
- **Store-and-Forward**: Most switches (reliable)
- **Cut-Through**: High-performance, data centers (speed critical)

---

### Q10: **Explain Hamming Code with an example.**

**Answer**:

**Hamming Code**: Error correction code that can correct single-bit errors and detect two-bit errors.

**Steps**:

1. **Determine parity bits (r)**:
   ```
   2^r ≥ m + r + 1
   ```
   For m = 4 data bits → r = 3

2. **Position parity bits** at powers of 2 (1, 2, 4, 8, ...)

3. **Calculate each parity bit**:
   - P1 (pos 1): Checks positions 1, 3, 5, 7, ...
   - P2 (pos 2): Checks positions 2, 3, 6, 7, ...
   - P4 (pos 4): Checks positions 4, 5, 6, 7, ...

**Example**: Encode **1011**

```
Position:  1   2   3   4   5   6   7
Type:     P1  P2  D1  P4  D2  D3  D4
Data:      ?   ?   1   ?   0   1   1

P1 (1,3,5,7): 1,0,1 → 2 ones → P1 = 0
P2 (2,3,6,7): 1,1,1 → 3 ones → P2 = 1
P4 (4,5,6,7): 0,1,1 → 2 ones → P4 = 0

Codeword: 0110011
```

**Error Detection**: Calculate parity checks. Error position = P4×4 + P2×2 + P1×1

---

### Q11: **What is the difference between Collision Domain and Broadcast Domain?**

**Answer**:

**Collision Domain**: Network segment where collisions can occur.

**Broadcast Domain**: Network segment where broadcast reaches.

**Devices**:

| Device | Collision Domains | Broadcast Domains |
|--------|------------------|-------------------|
| Hub | 1 (shared) | 1 (shared) |
| Switch | N (per port) | 1 (all ports) |
| Router | N (per interface) | N (per interface) |

**Example**:
- **Switch**: Each port = separate collision domain, but all ports = same broadcast domain
- **Router**: Separates both collision and broadcast domains

---

### Q12: **What is MAC Address? How is it different from IP Address?**

**Answer**:

**MAC Address**:
- **Layer**: 2 (Data Link)
- **Size**: 48 bits (6 bytes)
- **Format**: XX:XX:XX:XX:XX:XX (hex)
- **Scope**: Local (hop-to-hop)
- **Assignment**: Burned into NIC (hardware)
- **Type**: Physical address

**IP Address**:
- **Layer**: 3 (Network)
- **Size**: 32 bits (IPv4) or 128 bits (IPv6)
- **Format**: Dotted decimal (192.168.1.1)
- **Scope**: End-to-end
- **Assignment**: Configured (software)
- **Type**: Logical address

**Key Difference**:
- **MAC**: Hardware, doesn't change, local scope
- **IP**: Software, can change, global scope

**Analogy**:
- MAC = House address (fixed location)
- IP = Postal code (logical grouping)

---

### Quick Tips for Interviews

1. **Focus on**:
   - **CRC** (calculation and concept)
   - **Go-Back-N vs Selective Repeat**
   - **CSMA/CD vs CSMA/CA**
   - **Hamming Code** (encoding and error correction)
   - **Switch operation** (MAC table learning)
   - **VLAN** (purpose and 802.1Q)

2. **Common Questions**:
   - Framing methods (byte/bit stuffing)
   - Error detection vs correction
   - Flow control protocols
   - MAC protocols comparison
   - Difference between Hub/Switch/Bridge
   - ARP working

3. **Practice**:
   - CRC calculations
   - Hamming code encoding/decoding
   - Efficiency calculations
   - Sliding window protocol examples

4. **Remember**:
   - Data Link Layer = **Frames**
   - Physical Layer = **Bits**
   - Network Layer = **Packets**
   - Layer 2 addressing = **MAC**
   - Layer 3 addressing = **IP**

---

### Summary

**Data Link Layer Responsibilities**:
✅ **Framing**: Organize bits into frames
✅ **Physical Addressing**: Use MAC addresses
✅ **Error Detection**: CRC, Checksum, Parity
✅ **Error Correction**: Hamming Code, ARQ
✅ **Flow Control**: Stop-and-Wait, Sliding Window
✅ **Access Control**: CSMA/CD, CSMA/CA, Token Passing

**Key Protocols**:
- **Ethernet**: LAN standard (IEEE 802.3)
- **Wi-Fi**: Wireless LAN (IEEE 802.11)
- **PPP**: Point-to-Point Protocol
- **HDLC**: High-level Data Link Control
- **ARP**: Address Resolution Protocol

**Key Devices**:
- **Switch**: Layer 2 forwarding (MAC-based)
- **Bridge**: Connects LAN segments (legacy)
- **NIC**: Network interface (Layer 1 & 2)

---

**All the best for your placements! 🚀**
