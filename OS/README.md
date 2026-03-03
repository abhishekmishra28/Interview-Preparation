# 🖥️ Operating Systems — Complete Reference

> A comprehensive guide to OS concepts, internals, and design principles.

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Process Management](#2-process-management)
3. [Threads & Concurrency](#3-threads--concurrency)
4. [CPU Scheduling](#4-cpu-scheduling)
5. [Synchronization](#5-synchronization)
6. [Deadlocks](#6-deadlocks)
7. [Memory Management](#7-memory-management)
8. [Virtual Memory](#8-virtual-memory)
9. [File Systems](#9-file-systems)
10. [I/O Management](#10-io-management)
11. [Storage & Disk Scheduling](#11-storage--disk-scheduling)
12. [Security & Protection](#12-security--protection)
13. [Virtualization](#13-virtualization)
14. [Distributed Systems Basics](#14-distributed-systems-basics)
15. [OS Types & Architectures](#15-os-types--architectures)

---

## 1. Introduction

### What is an Operating System?

An **Operating System (OS)** is system software that manages hardware resources and provides services to application programs. It acts as an intermediary between users/applications and the computer hardware.

### Core Goals

| Goal | Description |
|------|-------------|
| **Convenience** | Make the computer easier to use |
| **Efficiency** | Use hardware resources efficiently |
| **Ability to Evolve** | Permit development and testing of new functions without disrupting service |

### OS Roles

- **Resource Allocator** — Manages and allocates CPU, memory, I/O devices
- **Control Program** — Controls execution of programs to prevent errors
- **Kernel** — The one program always running (everything else is a system/application program)

### System Call Interface

```
User Applications
      ↓
System Call Interface  ← API boundary
      ↓
OS Kernel (privileged mode)
      ↓
Hardware
```

### Dual-Mode Operation

| Mode | Privilege | Usage |
|------|-----------|-------|
| **User Mode** | Restricted | Application code runs here |
| **Kernel Mode** | Full hardware access | OS code, interrupt handlers |

Mode switch occurs via **system calls**, **interrupts**, or **exceptions**.

### Types of System Calls

- **Process control** — `fork()`, `exec()`, `exit()`, `wait()`
- **File management** — `open()`, `read()`, `write()`, `close()`
- **Device management** — `ioctl()`, `read()`, `write()`
- **Information maintenance** — `getpid()`, `alarm()`, `sleep()`
- **Communication** — `pipe()`, `shmget()`, `mmap()`

---

## 2. Process Management

### What is a Process?

A **process** is a program in execution. It is the unit of work in a modern OS.

```
Program (passive)  →  Process (active)
  on disk               in memory
```

### Process Memory Layout

```
High Address
┌─────────────┐
│    Stack    │  ← function calls, local vars (grows downward)
├─────────────┤
│      ↓      │
│    (gap)    │
│      ↑      │
├─────────────┤
│    Heap     │  ← dynamic allocation (malloc/new)
├─────────────┤
│    Data     │  ← global/static variables
├─────────────┤
│    Text     │  ← compiled program code (read-only)
└─────────────┘
Low Address
```

### Process Control Block (PCB)

The OS stores all process info in a **PCB (Process Control Block)**:

| Field | Description |
|-------|-------------|
| Process State | new, ready, running, waiting, terminated |
| Program Counter | Address of next instruction |
| CPU Registers | All register values |
| CPU Scheduling Info | Priority, queue pointers |
| Memory Management Info | Page tables, segment tables |
| Accounting Info | CPU time used, time limits |
| I/O Status Info | List of open files, devices |

### Process States

```
        admit
new ──────────→ ready ←──────── interrupt
                  │                  ↑
        dispatch  ↓            scheduler
               running ─────────────┘
                  │
          I/O or event wait
                  ↓
               waiting ────────→ ready
                         I/O complete
                  │
               exit ↓
             terminated
```

### Process Creation

- Parent creates children processes → **process tree**
- `fork()` — creates child as copy of parent
- `exec()` — replaces process memory with new program
- `wait()` — parent waits for child to complete
- `exit()` — terminates process, returns status

```c
pid_t pid = fork();

if (pid == 0) {
    // Child process
    exec("/bin/ls", args);
} else {
    // Parent process
    wait(NULL);
}
```

### Process Termination

- Normal: `exit()` system call
- Abnormal: signal, exception, killed by OS/parent
- **Zombie process** — terminated but parent hasn't called `wait()` yet
- **Orphan process** — parent terminated without waiting; re-parented to `init`

### Inter-Process Communication (IPC)

#### Shared Memory
- Processes map a shared region into their address spaces
- Faster (no kernel involvement after setup)
- Requires synchronization

#### Message Passing
- `send(P, message)` / `receive(Q, message)`
- Via pipes, sockets, message queues
- Simpler but slower (kernel copies data)

---

## 3. Threads & Concurrency

### Thread vs Process

| Aspect | Process | Thread |
|--------|---------|--------|
| Memory | Own address space | Shared address space |
| Creation Cost | High | Low |
| Context Switch | Expensive | Cheap |
| Communication | IPC needed | Shared memory directly |
| Crash Impact | Isolated | Can crash entire process |

### Thread Components

Each thread has its own:
- **Program counter**
- **Register set**
- **Stack**

Threads share:
- Code section
- Data section
- OS resources (files, signals)

### Multithreading Benefits

- **Responsiveness** — UI thread remains active while worker threads compute
- **Resource sharing** — threads share process memory natively
- **Economy** — cheaper to create/switch than processes
- **Scalability** — can exploit multiple CPU cores

### User Threads vs Kernel Threads

| Type | Managed By | Speed | Parallelism |
|------|------------|-------|-------------|
| **User Threads** | Thread library (e.g., pthreads) | Fast | Limited — one at a time on multicore |
| **Kernel Threads** | OS kernel | Slower | True parallelism |

### Threading Models

#### Many-to-One
```
UThread UThread UThread
    \      |      /
     Kernel Thread
```
- One kernel thread per process
- No true parallelism

#### One-to-One (Linux, Windows)
```
UThread UThread UThread
   |       |       |
KThread KThread KThread
```
- Best parallelism
- Overhead of kernel threads

#### Many-to-Many
```
UThread UThread UThread UThread
      \   |       |   /
    KThread   KThread
```
- Flexible, best of both worlds

### Thread Pools

Pre-created pool of worker threads waiting for tasks. Avoids overhead of creating/destroying threads for each request.

```
Request → Queue → [Thread Pool: T1 T2 T3 T4] → Result
```

---

## 4. CPU Scheduling

### Scheduling Goals

| Metric | Goal | Meaning |
|--------|------|---------|
| **CPU Utilization** | Maximize | Keep CPU busy |
| **Throughput** | Maximize | Processes completed per unit time |
| **Turnaround Time** | Minimize | Total time from submit to completion |
| **Waiting Time** | Minimize | Time spent in ready queue |
| **Response Time** | Minimize | Time from request to first response |

### Key Formulas

```
Turnaround Time = Completion Time − Arrival Time
Waiting Time    = Turnaround Time − Burst Time
Response Time   = First CPU Time − Arrival Time
```

### Scheduling Algorithms

#### 1. First-Come First-Served (FCFS)
- Non-preemptive, simple FIFO queue
- **Convoy effect** — short processes wait behind long ones

```
Process  Burst
P1       24
P2        3
P3        3

Gantt: |  P1  |P2|P3|
       0     24 27 30

Avg Waiting = (0 + 24 + 27) / 3 = 17 ms
```

#### 2. Shortest Job First (SJF)
- Non-preemptive; picks process with shortest next CPU burst
- **Optimal** for minimizing average waiting time
- Problem: cannot know future burst length exactly

#### 3. Shortest Remaining Time First (SRTF)
- Preemptive version of SJF
- Preempts current process if new arrival has shorter remaining time

#### 4. Round Robin (RR)
- Each process gets a fixed **time quantum** (q), then preempted
- Fair, good for time-sharing
- Performance depends heavily on quantum size:
  - q too large → degrades to FCFS
  - q too small → too many context switches

#### 5. Priority Scheduling
- Each process has a priority; highest priority runs first
- **Starvation problem** — low-priority processes may never run
- **Solution**: Aging — gradually increase priority of waiting processes

#### 6. Multilevel Queue
- Ready queue partitioned into separate queues by process type
- Each queue has its own scheduling algorithm
- Fixed priorities between queues

#### 7. Multilevel Feedback Queue (MLFQ)
- Processes can move between queues based on behavior
- CPU-bound processes move to lower-priority queues
- I/O-bound processes stay in higher-priority queues
- Most flexible, approximates SJF adaptively

### Comparison Summary

| Algorithm | Preemptive | Starvation | Notes |
|-----------|-----------|------------|-------|
| FCFS | No | No | Simple, convoy effect |
| SJF | No | Yes | Optimal avg wait |
| SRTF | Yes | Yes | Best avg wait, preemptive |
| Round Robin | Yes | No | Fair, good response |
| Priority | Both | Yes | Needs aging |
| MLFQ | Yes | No | Most practical |

---

## 5. Synchronization

### The Critical Section Problem

A **critical section** is code that accesses shared resources. Three requirements:

1. **Mutual Exclusion** — Only one process in its critical section at a time
2. **Progress** — If no process is in CS, selection of next process cannot be postponed indefinitely
3. **Bounded Waiting** — Limit on how many times others can enter CS after a process requests entry

### Peterson's Solution (2 processes)

```c
// Shared
int turn;
bool flag[2];

// Process i
flag[i] = true;
turn = j;
while (flag[j] && turn == j);
    // Critical Section
flag[i] = false;
```

Satisfies all three requirements but not practical on modern hardware (memory reordering).

### Hardware Synchronization

#### Test-and-Set (TAS)
```c
bool test_and_set(bool *target) {
    bool rv = *target;
    *target = true;   // atomic
    return rv;
}

// Spinlock using TAS
while (test_and_set(&lock));  // busy-wait
// critical section
lock = false;
```

#### Compare-and-Swap (CAS)
```c
int compare_and_swap(int *value, int expected, int new_val) {
    int temp = *value;
    if (*value == expected) *value = new_val;  // atomic
    return temp;
}
```

### Mutex Locks

```c
acquire(mutex);
    // critical section
release(mutex);
```

- `acquire()` spins (busy-waits) until lock is free — **spinlock**
- Simple but wastes CPU cycles

### Semaphores

Integer variable accessed via two atomic operations:

```c
wait(S):   while (S <= 0); S--;   // P operation
signal(S): S++;                    // V operation
```

#### Binary Semaphore (Mutex)
```c
semaphore mutex = 1;
wait(mutex);
    // critical section
signal(mutex);
```

#### Counting Semaphore
- Tracks number of available resources
- Initialized to resource count

#### Semaphore for Ordering
```c
// Guarantee S2 runs after S1
semaphore sync = 0;

// Thread 1        // Thread 2
S1;                wait(sync);
signal(sync);      S2;
```

### Monitors

High-level synchronization construct — encapsulates shared data and operations:

```java
monitor BoundedBuffer {
    int buffer[N];
    condition full, empty;

    procedure insert(item) {
        if (count == N) wait(full);
        buffer[in] = item;
        signal(empty);
    }

    procedure remove() {
        if (count == 0) wait(empty);
        item = buffer[out];
        signal(full);
        return item;
    }
}
```

### Classic Synchronization Problems

#### Producer-Consumer (Bounded Buffer)

```c
semaphore mutex = 1, empty = N, full = 0;

// Producer
wait(empty);
wait(mutex);
add_to_buffer(item);
signal(mutex);
signal(full);

// Consumer
wait(full);
wait(mutex);
remove_from_buffer(item);
signal(mutex);
signal(empty);
```

#### Readers-Writers

- Multiple readers can read simultaneously
- Writers need exclusive access

```c
semaphore rw_mutex = 1, mutex = 1;
int read_count = 0;

// Writer
wait(rw_mutex);
    // write
signal(rw_mutex);

// Reader
wait(mutex);
read_count++;
if (read_count == 1) wait(rw_mutex);
signal(mutex);
    // read
wait(mutex);
read_count--;
if (read_count == 0) signal(rw_mutex);
signal(mutex);
```

#### Dining Philosophers

5 philosophers, 5 forks — each needs 2 forks to eat:

```c
// Naive solution deadlocks if all pick up left fork first
// Solution: use asymmetric rule, or allow at most 4 at table, or use monitor
```

---

## 6. Deadlocks

### Four Necessary Conditions (Coffman)

All four must hold simultaneously for deadlock:

| Condition | Description |
|-----------|-------------|
| **Mutual Exclusion** | Resource held in non-sharable mode |
| **Hold and Wait** | Process holding resources waits for more |
| **No Preemption** | Resources can't be forcibly taken |
| **Circular Wait** | P1→R1→P2→R2→P1 cycle exists |

### Resource Allocation Graph

```
Process = circle (○)
Resource = rectangle (□), dots = instances

○ → □   : process requests resource
□ → ○   : resource assigned to process

Deadlock iff cycle exists AND each resource has single instance
```

### Deadlock Strategies

#### 1. Prevention
Eliminate one of the four conditions:
- **Mutual Exclusion** — use sharable resources where possible
- **Hold and Wait** — request all resources at once, or release before requesting more
- **No Preemption** — allow OS to preempt resources
- **Circular Wait** — impose total ordering on resource types; always acquire in order

#### 2. Avoidance — Banker's Algorithm

OS checks if granting a resource keeps system in a **safe state**.

**Safe state**: There exists a sequence in which all processes can finish.

```
Need[i][j] = Max[i][j] - Allocation[i][j]

Safe if:
  Find process i where Need[i] ≤ Available
  Simulate completion: Available += Allocation[i]
  Repeat until all processes finish (safe) or stuck (unsafe)
```

#### 3. Detection & Recovery

Allow deadlock, detect cycles, then:
- **Terminate** one or more deadlocked processes
- **Preempt** resources from processes and roll back

#### 4. Ignore (Ostrich Algorithm)

Used by most OS (Windows, Linux) — deadlocks are rare enough that the overhead of prevention/avoidance isn't justified.

---

## 7. Memory Management

### Goals

- **Relocation** — program can run at any physical address
- **Protection** — processes can't access each other's memory
- **Sharing** — allow controlled sharing of memory regions
- **Efficiency** — maximize utilization, minimize fragmentation

### Address Types

| Type | Description |
|------|-------------|
| **Logical (Virtual)** | Generated by CPU; what program sees |
| **Physical** | Actual address in RAM |

**MMU (Memory Management Unit)** translates logical → physical at runtime.

### Contiguous Allocation

Each process occupies a single contiguous block of memory.

#### Fixed Partitioning
- Memory divided into fixed equal-sized partitions
- **Internal fragmentation** — process smaller than partition wastes space

#### Variable Partitioning
- Partitions sized to fit each process
- **External fragmentation** — free holes too small to use
- **Compaction** — shuffle processes to consolidate free space (expensive)

### Fragmentation

| Type | Cause | Solution |
|------|-------|---------|
| **Internal** | Allocated block larger than needed | Smaller blocks, paging |
| **External** | Free space scattered in small pieces | Compaction, paging, segmentation |

### Allocation Strategies

| Strategy | Picks | Notes |
|----------|-------|-------|
| **First Fit** | First hole big enough | Fast, tends to leave large holes at end |
| **Best Fit** | Smallest hole that fits | Minimizes wasted space, slow, many tiny holes |
| **Worst Fit** | Largest hole | Leaves largest leftover; generally poor |

### Paging

Divide physical memory into fixed-size **frames** and logical memory into **pages** of the same size.

```
Logical Address = [page number | page offset]
                       p             d

Physical Address = frame_base[page_table[p]] + d
```

- **No external fragmentation** (any frame can be used)
- Small internal fragmentation (last page of process)

#### Page Table

```
Page #  →  Frame #
  0         3
  1         7
  2         2
  3         5
```

#### Calculating Addresses

```
Page size = 2^n bytes
Logical address bits: top bits = page #, bottom n bits = offset

Example: 32-bit logical, 4KB pages (n=12)
  → 20-bit page number, 12-bit offset
  → Page table has 2^20 = 1M entries
```

### Segmentation

Divide memory into logical **segments** (code, data, stack, heap).

```
Logical Address = [segment number | offset]

Physical Address = segment_table[s].base + offset
  (if offset < segment_table[s].limit)
```

- Matches programmer's view of memory
- External fragmentation possible

### Paging vs Segmentation

| Feature | Paging | Segmentation |
|---------|--------|--------------|
| Unit | Fixed-size pages | Variable-size segments |
| External Fragmentation | No | Yes |
| Internal Fragmentation | Yes (last page) | No |
| Programmer Visible | No | Yes |

Many systems use **segmented paging** — segments divided into pages.

---

## 8. Virtual Memory

### Concept

Allow processes to use more memory than physically available by keeping only **active portions** in RAM and the rest on disk.

```
Virtual Address Space  (can be much larger than RAM)
         ↓
   Page Table
         ↓
RAM (resident pages) + Disk (swap space)
```

### Demand Paging

Pages loaded **only when needed** (not all at program start).

- **Page fault** — accessed page not in RAM
- OS loads page from disk → resumes process
- **Lazy allocation** strategy

#### Page Fault Handling

```
1. Reference to page → check page table
2. Invalid bit set → page fault trap to OS
3. Find free frame (or evict one)
4. Load page from disk into frame
5. Update page table, set valid bit
6. Restart instruction
```

### Page Replacement Algorithms

When no free frame exists, OS must evict a page.

#### FIFO (First-In First-Out)
- Evict oldest page in memory
- Simple but suffers **Belady's Anomaly** (more frames → more faults sometimes)

#### Optimal (OPT)
- Evict page that won't be used for longest time
- **Theoretically optimal**, but requires future knowledge (impossible in practice)
- Used as benchmark

#### LRU (Least Recently Used)
- Evict page not used for longest time
- Approximates OPT; no Belady's anomaly
- Expensive to implement exactly

#### LRU Approximations

| Method | Mechanism |
|--------|-----------|
| **Reference Bit** | Hardware sets bit on access; OS periodically clears |
| **Second Chance (Clock)** | FIFO + give page a second chance if reference bit set |
| **Aging** | Shift reference bits right; add new bit to MSB |

#### LFU (Least Frequently Used)
- Evict page with lowest access count
- Can retain old popular pages; needs counter management

### Thrashing

When a process spends more time paging than executing:

```
Low CPU utilization
  → OS loads more processes
    → Less frames per process
      → More page faults
        → CPU utilization drops further
          → (cycle worsens)
```

**Solutions:**
- **Working Set Model** — track pages used in last Δ time units; allocate enough frames
- **Page-Fault Frequency (PFF)** — monitor fault rate; add/remove frames dynamically

### Copy-on-Write (COW)

After `fork()`, parent and child share pages marked read-only. Only when one process writes is a private copy made.

```
fork() → shared pages (copy-on-write)
write → page fault → copy that page → modify copy
```

Efficient for `fork() + exec()` pattern.

---

## 9. File Systems

### File Concepts

A **file** is a named collection of related information stored on secondary storage.

#### File Attributes
- Name, Type, Location, Size
- Protection (permissions)
- Timestamps (created, modified, accessed)

#### File Operations
- `create`, `open`, `read`, `write`, `seek`, `truncate`, `close`, `delete`

#### File Types

| Extension | Type |
|-----------|------|
| `.exe`, `.out` | Executable |
| `.obj`, `.o` | Object code |
| `.txt`, `.md` | Text |
| `.mp3`, `.mp4` | Media |
| `.tar`, `.zip` | Archive |

### Directory Structure

#### Single-Level
- One directory for all files
- No subdirectories; naming conflicts

#### Two-Level
- Separate directories per user
- No sharing between users

#### Tree-Structured (Modern Standard)
```
/
├── bin/
├── etc/
├── home/
│   ├── alice/
│   │   └── file.txt
│   └── bob/
├── tmp/
└── var/
```

#### Acyclic-Graph (with links)
- Files/dirs can have multiple parents via **hard links** or **symbolic links**

### File System Implementation

#### Disk Layout
```
Boot Block | Superblock | Inode Table | Data Blocks
```

- **Superblock** — FS metadata (size, block size, free count, root inode)
- **Inode** — file metadata + data block pointers (NOT the filename)
- **Directory** — maps filenames to inode numbers

#### Inode Structure

```
Inode {
  mode, uid, gid, size, timestamps
  direct_blocks[12]        → blocks 0–11 (12 × 4KB = 48KB)
  single_indirect          → pointer to block of pointers (4MB)
  double_indirect          → pointer to block of single-indirect (4GB)
  triple_indirect          → pointer to block of double-indirect (huge)
}
```

#### File Allocation Methods

| Method | Description | Pros | Cons |
|--------|-------------|------|------|
| **Contiguous** | Sequential blocks on disk | Fast sequential, simple | External fragmentation, file growth hard |
| **Linked** | Each block has pointer to next | No fragmentation, easy growth | Slow random access, pointer overhead |
| **Indexed** | Index block holds all data block pointers | Fast random access, no fragmentation | Index block overhead |
| **Inode (Unix)** | Multi-level indexed | Handles small and large files | Complex |

#### Free Space Management

- **Bit Vector (Bitmap)** — 1 bit per block (1=free, 0=used); easy to find contiguous blocks
- **Linked List** — link all free blocks; hard to find contiguous space
- **Grouping** — first free block contains n free block addresses
- **Counting** — store (first free block, count) pairs

### Directory Implementation

- **Linear list** of (name, inode#) pairs — simple, slow search
- **Hash table** — fast lookup, collision handling

### Virtual File System (VFS)

Abstract layer between system calls and specific FS implementations:

```
User Process
    ↓  (open, read, write, close)
VFS Interface
    ↓           ↓           ↓
  ext4        FAT32       NFS (network)
```

Four key VFS objects:
- **superblock** — mounted FS
- **inode** — individual file
- **dentry** — directory entry (name → inode mapping)
- **file** — open file instance

### Journaling

Logs changes before committing them to prevent FS corruption on crash:

```
1. Write intent to journal (log)
2. Commit journal entry
3. Apply actual changes to FS
4. Clear journal entry

On crash: replay uncommitted journal entries
```

Examples: **ext3/4**, **NTFS**, **APFS**

---

## 10. I/O Management

### I/O Hardware

- **Port** — connection point for a device
- **Bus** — shared communication wire (PCI, USB, SATA)
- **Controller** — electronics that operate the device

### I/O Methods

| Method | Description | CPU Use |
|--------|-------------|---------|
| **Polling** | CPU repeatedly checks device status | High (busy wait) |
| **Interrupt-Driven** | Device interrupts CPU when ready | Low |
| **DMA** | Device transfers data directly to memory | Minimal (only start/end) |

### Direct Memory Access (DMA)

```
CPU tells DMA controller:
  - Source/destination address
  - Transfer size
  - Direction (read/write)

DMA transfers data directly between device and memory
DMA interrupts CPU only when done
```

### I/O Software Layers

```
User-Space I/O Software  (stdio, libc)
      ↓
Device-Independent OS Code  (buffering, caching, naming)
      ↓
Device Drivers  (device-specific, communicate with controller)
      ↓
Interrupt Handlers
      ↓
Hardware
```

### Buffering

Temporary storage of data during transfer:

- **Single buffer** — OS provides buffer between user and hardware
- **Double buffer** — two buffers alternate; one fills while other is processed
- **Circular buffer** — ring of buffers for streams

### Caching

Keep recently used data in fast storage:

- Disk cache (page cache in Linux) — dramatically reduces disk I/O
- Write-back vs write-through caching

### Spooling

Simultaneous Peripheral Operations Online:
- Buffer output for devices that can't accept interleaved data
- Classic example: print spooler — jobs queued, printer processes one at a time

---

## 11. Storage & Disk Scheduling

### Disk Structure

```
Platter → Surface → Track → Sector

Cylinder = same track across all platters
```

**Disk Access Time = Seek Time + Rotational Latency + Transfer Time**

- **Seek time** — move head to correct track (~5–15ms, dominant)
- **Rotational latency** — wait for sector to rotate under head
- **Transfer time** — actual data transfer

### Disk Scheduling Algorithms

Goal: minimize total head movement (seek time).

**Queue of requests**: 98, 183, 37, 122, 14, 124, 65, 67 | Head at: 53

#### FCFS
```
53 → 98 → 183 → 37 → 122 → 14 → 124 → 65 → 67
Total movement: 640 cylinders
```

#### SSTF (Shortest Seek Time First)
```
53 → 65 → 67 → 37 → 14 → 98 → 122 → 124 → 183
Total: 236 cylinders
May cause starvation of distant requests
```

#### SCAN (Elevator Algorithm)
- Head moves in one direction, services all requests, then reverses
```
53 → 65 → 67 → 98 → 122 → 124 → 183 → (reverse) → 37 → 14
Total: 208 cylinders
```

#### C-SCAN (Circular SCAN)
- Head moves one direction, jumps back to start without servicing on return
- More uniform wait times than SCAN

#### LOOK / C-LOOK
- Like SCAN/C-SCAN but only goes as far as last request (doesn't go to disk edge)
- Most practical; used in Linux

### RAID

**Redundant Array of Independent Disks**

| Level | Description | Redundancy | Performance |
|-------|-------------|-----------|-------------|
| RAID 0 | Striping | None | High (parallel reads/writes) |
| RAID 1 | Mirroring | Full copy | Good read, write ×2 |
| RAID 5 | Striping + parity | Single disk failure | Good read, moderate write |
| RAID 6 | Striping + dual parity | Two disk failures | Good read, slower write |
| RAID 10 | Mirror + stripe (1+0) | One per mirror pair | Excellent |

---

## 12. Security & Protection

### Goals

- **Protection** — mechanism to control access of processes/users to resources
- **Security** — defense against internal and external attacks

### Security Threats

| Threat | Description |
|--------|-------------|
| **Malware** | Viruses, worms, trojans, ransomware |
| **Code Injection** | Buffer overflow, SQL injection |
| **Privilege Escalation** | Gaining higher access than authorized |
| **Denial of Service** | Overwhelming system resources |
| **Eavesdropping** | Intercepting communications |

### Buffer Overflow

```c
void vulnerable(char *input) {
    char buf[64];
    strcpy(buf, input);  // No bounds check!
    // Overflow can overwrite return address
}
```

Defenses: **Stack canaries**, **ASLR**, **NX bit (DEP)**, **safe functions**

### Protection Mechanisms

#### Access Matrix

```
         File1   File2   Printer
Process1  r,w      r        —
Process2   r      r,w     print
Process3   —      r,w     print
```

Implemented as:
- **Access Control Lists (ACL)** — column-based; list of (subject, rights) per object
- **Capability Lists** — row-based; list of (object, rights) per subject

#### Unix File Permissions

```
-rwxr-xr--  1  alice  staff  4096  Jan 1  file.txt
 │││└──┘└──┘
 │││  │    └── Other: read only
 │││  └──────── Group: read + execute
 ││└──────────── Owner: read + write + execute
 │└───────────── Type: - file, d dir, l symlink
```

```
chmod 755 file.txt
# 7 = rwx (owner)
# 5 = r-x (group)
# 5 = r-x (other)
```

### Authentication

- **Something you know** — password, PIN
- **Something you have** — smart card, token
- **Something you are** — biometrics
- **Multi-Factor Authentication (MFA)** — combination of above

### Cryptography Basics

| Type | Key | Use Cases |
|------|-----|-----------|
| **Symmetric** | Same key encrypt/decrypt (AES) | Fast, bulk data |
| **Asymmetric** | Public/private key pair (RSA) | Key exchange, signatures |
| **Hash** | One-way function (SHA-256) | Integrity, passwords |

---

## 13. Virtualization

### Types of Virtualization

#### Type 1 Hypervisor (Bare-Metal)
```
Hardware
   ↓
Hypervisor (VMware ESXi, KVM, Xen)
   ↓
VMs (each with guest OS)
```
- Runs directly on hardware
- Better performance, used in data centers

#### Type 2 Hypervisor (Hosted)
```
Hardware
   ↓
Host OS
   ↓
Hypervisor (VirtualBox, VMware Workstation)
   ↓
VMs (guest OSes)
```
- Runs on top of host OS
- Easier to set up, used on desktops

### Containers vs VMs

| Feature | Virtual Machine | Container |
|---------|----------------|-----------|
| Isolation | Full OS isolation | Process isolation |
| Size | GBs | MBs |
| Startup | Minutes | Seconds |
| OS | Each has own guest OS | Shares host kernel |
| Examples | VirtualBox, VMware | Docker, Podman |

### Para-virtualization

Guest OS is modified to be aware of the hypervisor and uses hypercalls instead of privileged instructions → better performance than full virtualization.

---

## 14. Distributed Systems Basics

### Characteristics

- Multiple computers connected over a network
- Share resources and coordinate via message passing
- Appear as a single coherent system to users

### Challenges

| Challenge | Description |
|-----------|-------------|
| **Partial failure** | Some nodes fail while others run |
| **Latency** | Network delay varies |
| **Concurrency** | Multiple nodes act simultaneously |
| **Consistency** | All nodes see same data |
| **Security** | Communication over untrusted networks |

### CAP Theorem

A distributed system can guarantee at most **two** of:

- **Consistency** — every read receives the most recent write
- **Availability** — every request gets a response
- **Partition Tolerance** — system continues despite network partitions

```
         Consistency
            /\
           /  \
     CA   /    \  CP
         /      \
        /________\
   Availability  Partition Tolerance
         AP
```

Real-world systems must tolerate partitions → choose between **CP** or **AP**.

### Remote Procedure Call (RPC)

Call a function on a remote machine as if it were local:

```
Client → Stub → Marshal → Network → Unmarshal → Stub → Server
         (packs args)              (unpacks args)
```

---

## 15. OS Types & Architectures

### OS Architectures

#### Monolithic Kernel
- Entire OS runs in kernel mode as one large program
- Fast (no mode switches between modules)
- Hard to maintain, a bug anywhere crashes system
- Examples: **Linux** (mostly monolithic)

#### Microkernel
- Minimal kernel (IPC, basic scheduling, memory)
- Most services run as user-space processes
- More stable/secure (crashes in services don't crash kernel)
- Slower (many message passes)
- Examples: **Mach**, **QNX**, **MINIX**

```
Microkernel structure:
[User space: File Server | Device Driver | Network Stack]
[Kernel: IPC | Basic Scheduler | Memory]
[Hardware]
```

#### Modular Kernel (Hybrid)
- Monolithic base with loadable kernel modules
- Best of both worlds
- Examples: **Linux with modules**, **macOS (XNU)**

#### Exokernel
- Kernel only multiplexes hardware resources
- Applications implement their own abstractions
- Maximum flexibility, complex applications

### OS Types by Use

| Type | Examples | Characteristics |
|------|----------|----------------|
| **Desktop OS** | Windows, macOS, Linux | GUI, wide hardware support |
| **Server OS** | Linux Server, Windows Server | Reliability, throughput, no GUI needed |
| **Mobile OS** | Android, iOS | Touch, power efficiency, app sandboxing |
| **Real-Time OS (RTOS)** | FreeRTOS, VxWorks | Predictable timing guarantees |
| **Embedded OS** | RTOS variants, custom | Tiny footprint, single purpose |
| **Distributed OS** | Plan 9, Amoeba | Transparent distributed resources |

### Real-Time OS (RTOS)

- **Hard real-time** — missing a deadline is a system failure (airbags, flight control)
- **Soft real-time** — missing a deadline degrades quality (video streaming)

Key scheduler: **EDF (Earliest Deadline First)** — always run task with nearest deadline.

---

## Quick Reference: Key Algorithms

| Topic | Algorithm | Key Idea |
|-------|-----------|---------|
| CPU Scheduling | MLFQ | Multi-level feedback, adapts to behavior |
| Page Replacement | LRU | Evict least recently used page |
| Deadlock Avoidance | Banker's | Guarantee safe state before allocation |
| Disk Scheduling | C-LOOK | Move head one direction to last request |
| Synchronization | Monitor | Encapsulate shared state + condition vars |
| Memory Allocation | Buddy System | Split/merge power-of-2 blocks |

---

## Quick Reference: Key Terms

| Term | Definition |
|------|-----------|
| **PCB** | Process Control Block — all state for a process |
| **Context Switch** | Saving/restoring process state to switch CPU |
| **TLB** | Translation Lookaside Buffer — cache for page table |
| **Inode** | Unix file metadata structure |
| **Semaphore** | Integer synchronization primitive (wait/signal) |
| **Thrashing** | Excessive paging, near-zero useful work |
| **Deadlock** | Circular wait among processes for resources |
| **Spooling** | Buffering I/O for slow devices (e.g., printer) |
| **DMA** | Direct Memory Access — device transfers without CPU |
| **Hypervisor** | Software layer creating virtual machines |
| **RAID** | Disk redundancy/performance via multiple disks |
| **Journaling** | Write-ahead logging to protect FS integrity |

---

*End of Operating Systems Complete Reference*
