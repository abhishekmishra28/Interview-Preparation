# 💻 35 Most Important Operating Systems Interview Questions

> **Target Audience:** Freshers to Experienced Developers  
> **Topics Covered:** Processes, Threads, Scheduling, Memory, Deadlocks, File Systems, Synchronization & More  
> **Interview Level:** SDE / Systems Engineer / Backend Developer

---

## Table of Contents

| # | Question |
|---|----------|
| 1 | [What is an Operating System and what are its functions?](#q1) |
| 2 | [What is a Process? Process States and PCB?](#q2) |
| 3 | [What is a Thread? Process vs Thread?](#q3) |
| 4 | [What are the types of Threads? User vs Kernel Threads?](#q4) |
| 5 | [What is Context Switching?](#q5) |
| 6 | [What is CPU Scheduling? Scheduling Criteria?](#q6) |
| 7 | [What are CPU Scheduling Algorithms?](#q7) |
| 8 | [What is a System Call?](#q8) |
| 9 | [What is Inter-Process Communication (IPC)?](#q9) |
| 10 | [What is a Critical Section Problem?](#q10) |
| 11 | [What is a Mutex vs Semaphore?](#q11) |
| 12 | [What is a Deadlock? Conditions and Prevention?](#q12) |
| 13 | [What is the Banker's Algorithm?](#q13) |
| 14 | [What is Memory Management?](#q14) |
| 15 | [What is Paging?](#q15) |
| 16 | [What is Segmentation?](#q16) |
| 17 | [What is Virtual Memory?](#q17) |
| 18 | [What is Demand Paging and Page Faults?](#q18) |
| 19 | [What are Page Replacement Algorithms?](#q19) |
| 20 | [What is Thrashing?](#q20) |
| 21 | [What is Fragmentation? Internal vs External?](#q21) |
| 22 | [What is a Cache? Cache Levels and Locality?](#q22) |
| 23 | [What is a File System?](#q23) |
| 24 | [What are File Allocation Methods?](#q24) |
| 25 | [What is Disk Scheduling? Algorithms?](#q25) |
| 26 | [What is RAID?](#q26) |
| 27 | [What are Kernel Types? Monolithic vs Microkernel?](#q27) |
| 28 | [What is a Boot Process?](#q28) |
| 29 | [What is a Fork vs Exec system call?](#q29) |
| 30 | [What are Signals in OS?](#q30) |
| 31 | [What is Spooling?](#q31) |
| 32 | [What is Starvation and Aging?](#q32) |
| 33 | [What is the Producer-Consumer Problem?](#q33) |
| 34 | [What is the Readers-Writers Problem?](#q34) |
| 35 | [What is the Dining Philosophers Problem?](#q35) |

---

<a name="q1"></a>
## Q1. What is an Operating System and what are its functions?

**Answer:**

An **Operating System (OS)** is system software that acts as an **intermediary between hardware and user applications**. It manages hardware resources and provides a platform for programs to run.

```
┌─────────────────────────────────────────────────────┐
│             User Applications                       │
│  (Browser, IDE, Games, Word Processor...)           │
├─────────────────────────────────────────────────────┤
│           Operating System (Kernel)                 │
│  Process Mgmt │ Memory Mgmt │ File System │ I/O     │
├─────────────────────────────────────────────────────┤
│               Hardware                              │
│   CPU  │  RAM  │  Disk  │  Network  │  GPU          │
└─────────────────────────────────────────────────────┘
```

### Core Functions of an OS

| Function | Description |
|----------|-------------|
| **Process Management** | Create, schedule, terminate processes and threads |
| **Memory Management** | Allocate/deallocate RAM, virtual memory, paging |
| **File System Management** | Files, directories, permissions, storage |
| **I/O Management** | Device drivers, buffering, spooling |
| **Security & Protection** | Access control, authentication, isolation |
| **Networking** | TCP/IP stack, sockets, inter-machine communication |
| **User Interface** | CLI (bash, zsh) or GUI (Windows, macOS) |

### Types of OS

| Type | Description | Examples |
|------|-------------|---------|
| **Batch OS** | Jobs collected and run in batches, no user interaction | IBM OS/360 |
| **Time-Sharing (Multitasking)** | Multiple users/processes share CPU via time slices | Unix, Linux |
| **Real-Time OS (RTOS)** | Strict timing guarantees, deterministic | FreeRTOS, VxWorks |
| **Distributed OS** | Manages a network of computers as a single system | Amoeba, Plan 9 |
| **Embedded OS** | Minimal OS for dedicated hardware | Android (base), iOS |
| **Mobile OS** | Optimized for mobile devices | Android, iOS |

### Dual Mode Operation
```
User Mode    → Restricted access, cannot directly access hardware
               (Applications run here)
Kernel Mode  → Full hardware access, privileged instructions
               (OS kernel runs here)

User App → System Call → [Mode Switch to Kernel] → Hardware → [Mode Switch back]
```

---

<a name="q2"></a>
## Q2. What is a Process? Process States and PCB?

**Answer:**

A **process** is a **program in execution** — an active instance of a program loaded into memory along with all the resources it needs (CPU time, memory, files, I/O).

```
Program (on disk)  ──── loaded into RAM ────►  Process (in execution)
   passive entity                                active entity
```

### Process Memory Layout

```
High Address ┌──────────────────┐
             │   Kernel Space   │ ← OS kernel, not accessible by user
             ├──────────────────┤
             │      Stack       │ ← Local variables, function call frames (grows ↓)
             │        ↓         │
             │    (free space)  │
             │        ↑         │
             │      Heap        │ ← Dynamic memory (malloc/new) (grows ↑)
             ├──────────────────┤
             │   BSS Segment    │ ← Uninitialized global/static variables
             ├──────────────────┤
             │   Data Segment   │ ← Initialized global/static variables
             ├──────────────────┤
             │   Text Segment   │ ← Program code (read-only)
Low Address  └──────────────────┘
```

### Process States

```
                  ┌──────────────────────────────────────┐
                  │             NEW                       │
                  │   Process created, loaded into memory │
                  └──────────────┬───────────────────────┘
                                 │ admitted
                                 ▼
┌────────────┐  scheduler  ┌───────────┐  I/O or event  ┌─────────────┐
│  RUNNING   │◄────────────│   READY   │◄───────────────│   WAITING   │
│(On CPU now)│─────────────►(In queue) │────────────────►(Blocked/I/O)│
└────────────┘  preempt /  └───────────┘  I/O request   └─────────────┘
      │         time slice
      │ exit
      ▼
┌────────────┐
│ TERMINATED │
│ (Zombie)   │
└────────────┘
```

| State | Description |
|-------|-------------|
| **New** | Process being created |
| **Ready** | Waiting for CPU assignment |
| **Running** | Currently executing on CPU |
| **Waiting / Blocked** | Waiting for I/O or event |
| **Terminated** | Execution finished |
| **Zombie** | Finished but not yet reaped by parent |
| **Suspended** | Swapped to disk to free RAM |

### Process Control Block (PCB)
The OS maintains a **PCB** (also called Task Control Block) for every process:

```
PCB for Process P1:
┌─────────────────────────────────────────┐
│ Process ID (PID)       : 1042           │
│ Process State          : RUNNING        │
│ Program Counter (PC)   : 0x00401A3F     │
│ CPU Registers          : eax=5, ebx=... │
│ Memory Limits          : 0x1000–0x9000  │
│ Open File Table        : [fd0, fd1, fd3]│
│ I/O Status             : Waiting on fd3 │
│ Priority               : 10             │
│ Parent PID             : 1001           │
│ CPU Time Used          : 0.34 sec       │
└─────────────────────────────────────────┘
```

---

<a name="q3"></a>
## Q3. What is a Thread? Process vs Thread?

**Answer:**

A **thread** is the smallest unit of CPU execution — a lightweight execution path within a process. A process can have **multiple threads**, all sharing the same memory space.

### Process vs Thread

```
Process A                           Process B
┌───────────────────────────┐       ┌───────────────────────────┐
│  Code  │  Data  │  Files  │       │  Code  │  Data  │  Files  │
│  (Shared by all threads)  │       │  (Shared by all threads)  │
├────────┬─────────┬────────┤       └───────────────────────────┘
│Thread 1│ Thread 2│Thread 3│
│Stack   │ Stack   │ Stack  │ ← each thread has its own
│Regs    │ Regs    │ Regs   │ ← each thread has its own
│PC      │ PC      │ PC     │ ← each thread has its own
└────────┴─────────┴────────┘
```

### Comparison Table

| Feature | Process | Thread |
|---------|---------|--------|
| Definition | Program in execution | Unit of execution within a process |
| Memory | Own address space | Shares process address space |
| Communication | Slow (IPC needed) | Fast (shared memory) |
| Creation overhead | High (fork, copy memory maps) | Low (just a new stack + registers) |
| Context switch | Expensive | Cheaper |
| Crash impact | Isolated (other processes safe) | One thread crash can kill the process |
| Resources | Own file handles, sockets | Shared with process |
| Example | Chrome tab = process | Chrome rendering, JS, network = threads |

### What Threads Share vs Own

| Shared (Process-wide) | Thread-private |
|----------------------|---------------|
| Code (text segment) | Program Counter (PC) |
| Global variables (data/BSS) | Stack |
| Heap | CPU Registers |
| Open file descriptors | Thread ID |
| Signal handlers | Thread-local storage |

### Multithreading Benefits
```
Single-threaded server:     [Request 1] → process → [Request 2] → process...
                             (sequential, one at a time)

Multi-threaded server:      [Request 1] → Thread 1 ─┐
                            [Request 2] → Thread 2  ├── all run concurrently
                            [Request 3] → Thread 3 ─┘
```

---

<a name="q4"></a>
## Q4. What are the types of Threads? User vs Kernel Threads?

**Answer:**

### User-Level Threads (ULT)
Managed entirely by a **user-space thread library** (e.g., POSIX pthreads in user mode, Java green threads). The kernel is unaware of them — it sees only one process.

```
User Space:  Thread 1  Thread 2  Thread 3
              └──────────┬──────────┘
                   Thread Library
─────────────────────────────────────────── (kernel boundary)
Kernel Space:        Process P
                   (one kernel thread)
```

| Pros | Cons |
|------|------|
| Fast creation and switching | One ULT blocks → entire process blocks |
| OS-independent | Cannot exploit multiple CPUs (no true parallelism) |
| Custom scheduling possible | Kernel can't schedule individual threads |

### Kernel-Level Threads (KLT)
Managed directly by the **OS kernel**. Each thread is known to and scheduled by the kernel.

```
User Space:  Thread 1  Thread 2  Thread 3
─────────────────────────────────────────── (kernel boundary)
Kernel Space: KThread1  KThread2  KThread3
              (each maps to a user thread)
```

| Pros | Cons |
|------|------|
| True parallelism on multi-core | Higher overhead (syscall for every operation) |
| One thread blocks → others run | Slower context switching |
| Kernel can optimize scheduling | |

### Threading Models

```
Many-to-One (M:1):     Many ULTs → One KLT    (old green threads)
One-to-One  (1:1):     Each ULT  → One KLT    (Linux pthreads, Windows threads)
Many-to-Many (M:N):    M ULTs    → N KLTs     (Solaris, Go goroutines)
Two-Level:             Both M:N + some 1:1     (HP-UX, IRIX)
```

### Modern Reality (Linux)
Linux uses **1:1 model** — each `pthread` maps to a kernel thread (`clone()` syscall). Go uses **M:N model** via goroutines with its own scheduler (G-M-P model).

---

<a name="q5"></a>
## Q5. What is Context Switching?

**Answer:**

**Context switching** is the process of saving the state of the currently running process/thread and loading the state of the next one to run. It enables **multitasking** — the illusion that multiple processes run simultaneously on a single CPU.

### What Gets Saved/Restored (the "Context")

```
CPU Registers saved to PCB:
┌────────────────────────────────────────┐
│  Program Counter (PC)                  │ ← where to resume
│  Stack Pointer (SP)                    │ ← current stack position
│  General-purpose registers (eax,...) │ ← computation state
│  Flags register (EFLAGS)              │ ← condition codes
│  Memory management registers (CR3)    │ ← page table pointer
└────────────────────────────────────────┘
```

### Context Switch Flow

```
Process P1 running on CPU
         │
   Interrupt / Syscall / Timer
         │
         ▼
┌─────────────────────────────┐
│  Save P1's context to PCB1  │  (registers, PC, stack pointer...)
│  Update P1 state → READY    │
│  Run scheduler              │  (pick P2)
│  Load P2's context from PCB2│
│  Update P2 state → RUNNING  │
└─────────────────────────────┘
         │
         ▼
Process P2 running on CPU
```

### Context Switch Triggers
- **Timer interrupt** (time slice expired)
- **System call** (process requests OS service)
- **I/O request** (process blocks waiting for I/O)
- **Higher-priority process** becomes ready (preemption)

### Cost of Context Switching
Context switching has **overhead** — it is "pure" wasted CPU time (no user code runs during the switch):

| Cost Component | Description |
|----------------|-------------|
| Direct cost | Save/restore registers, switch page tables |
| Indirect cost | TLB flush (cache misses after switch), cache warming |
| Frequency | Thousands of switches per second on a busy system |

> **Thread context switch** is cheaper than **process context switch** because threads within the same process share the same page table (no TLB flush needed).

---

<a name="q6"></a>
## Q6. What is CPU Scheduling? Scheduling Criteria?

**Answer:**

**CPU Scheduling** is the OS mechanism that decides **which process from the ready queue gets the CPU next** and for how long. It is essential for maximizing CPU utilization and system throughput.

### Scheduling Queues

```
New Process
     │
     ▼
┌──────────────┐      ┌─────────┐
│  Job Queue   │─────►│  Ready  │─────► CPU ──►  Terminated
│ (all processes)     │  Queue  │
└──────────────┘      └─────────┘
                           ▲
              I/O complete │
                      ┌────┴──────────┐
                      │ I/O Wait Queue│◄── Waiting for I/O
                      └───────────────┘
```

### Scheduling Criteria

| Criterion | Goal | From whose perspective |
|-----------|------|----------------------|
| **CPU Utilization** | Keep CPU as busy as possible (maximize) | System |
| **Throughput** | # processes completed per unit time (maximize) | System |
| **Turnaround Time** | Time from submission to completion (minimize) | Process |
| **Waiting Time** | Time spent in ready queue (minimize) | Process |
| **Response Time** | Time from request to first response (minimize) | Interactive User |
| **Fairness** | Equal CPU share to all processes | All |

### Key Time Definitions
```
Arrival Time (AT)    → When process enters ready queue
Burst Time (BT)      → Time needed on CPU
Completion Time (CT) → When process finishes
Turnaround Time (TAT)= CT - AT
Waiting Time (WT)    = TAT - BT
Response Time (RT)   = Time of first CPU access - AT
```

### Preemptive vs Non-Preemptive

| Type | Description | Example |
|------|-------------|---------|
| **Non-Preemptive** | Once CPU given, process runs until it voluntarily gives up | FCFS, SJF non-preemptive |
| **Preemptive** | OS can forcibly take CPU from running process | Round Robin, SRTF, Priority |

---

<a name="q7"></a>
## Q7. What are CPU Scheduling Algorithms?

**Answer:**

### 1. FCFS — First Come First Served
Processes scheduled in order of arrival. **Non-preemptive.**

```
Processes: P1(BT=24), P2(BT=3), P3(BT=3)  (all arrive at t=0)

Gantt: |──────────P1──────────|─P2─|─P3─|
Time:  0                     24   27   30

WT: P1=0, P2=24, P3=27   Average WT = 17
```
**Problem: Convoy Effect** — short processes wait behind one long process.

### 2. SJF — Shortest Job First
Picks process with **smallest burst time**. Optimal average waiting time. **Non-preemptive.**

```
Processes: P1(BT=6), P2(BT=8), P3(BT=7), P4(BT=3)

Gantt: |─P4─|──P1──|───P3───|────P2────|
Time:  0    3      9       16          24

Average WT = (3+16+9+0)/4 = 7
```

### 3. SRTF — Shortest Remaining Time First
**Preemptive** version of SJF. If a new process arrives with shorter remaining time, it preempts.

### 4. Round Robin (RR)
Each process gets a **fixed time quantum (q)**. After quantum expires, preempted and moved to back of queue. **Preemptive.**

```
Processes: P1(BT=24), P2(BT=3), P3(BT=3)  q=4

Gantt: |─P1─|─P2─|─P3─|─P1─|─P1─|─P1─|─P1─|─P1─|
Time:  0    4    7   10   14   18   22   26   30

Good for time-sharing, interactive systems.
```
- Small q → more context switches, less throughput
- Large q → degrades to FCFS

### 5. Priority Scheduling
Each process has a **priority number**. CPU allocated to highest priority. Can be **preemptive or non-preemptive.**

```
Problem: Starvation — low priority processes may never run.
Solution: Aging — gradually increase priority of waiting processes.
```

### 6. Multilevel Queue Scheduling
Ready queue divided into **separate queues** (foreground/interactive, background/batch), each with its own algorithm:
```
Queue 1 (Interactive): Round Robin   (highest priority)
Queue 2 (Batch):       FCFS          (lower priority)
```

### 7. Multilevel Feedback Queue (MLFQ)
Processes can **move between queues** based on behavior (most sophisticated, used in real OS like Linux):
```
Queue 1 (q=8ms):   New processes start here (high priority, short quantum)
      ↓ if not done
Queue 2 (q=16ms):  Gets more CPU time
      ↓ if not done
Queue 3 (FCFS):    Long-running/batch processes
```

### Comparison Summary

| Algorithm | Preemptive | Starvation | Overhead | Best For |
|-----------|:----------:|:----------:|:--------:|---------|
| FCFS | ❌ | ❌ | Low | Simple batch |
| SJF | ❌ | ✅ Possible | Medium | Batch (known BT) |
| SRTF | ✅ | ✅ Possible | High | Minimum avg WT |
| Round Robin | ✅ | ❌ | Medium | Time-sharing |
| Priority | Both | ✅ Possible | Medium | Real-time |
| MLFQ | ✅ | ❌ (with aging) | High | General OS |

---

<a name="q8"></a>
## Q8. What is a System Call?

**Answer:**

A **system call** is a programmatic interface through which a user-space application requests a **privileged service from the OS kernel**. It is the controlled gateway into kernel mode.

```
User Application
      │
      │  system call (e.g., read())
      │
      ▼  [CPU switches from User Mode → Kernel Mode]
┌─────────────────────────────────────────────────┐
│              OS Kernel                          │
│  Validates request → Performs operation         │
│  Returns result → Switches back to User Mode    │
└─────────────────────────────────────────────────┘
      │
      ▼
User Application resumes
```

### Categories of System Calls

| Category | Examples (Linux) | Purpose |
|----------|-----------------|---------|
| **Process Control** | `fork()`, `exec()`, `exit()`, `wait()`, `getpid()` | Create/manage processes |
| **File Management** | `open()`, `close()`, `read()`, `write()`, `lseek()` | File I/O |
| **Device Management** | `ioctl()`, `read()`, `write()` on device files | Hardware devices |
| **Information** | `getpid()`, `alarm()`, `sleep()`, `uname()` | System/process info |
| **Communication** | `pipe()`, `socket()`, `send()`, `recv()`, `mmap()` | IPC, networking |
| **Memory** | `mmap()`, `brk()`, `munmap()` | Memory allocation |

### System Call Flow (Linux x86-64)
```c
// User space: calling write()
ssize_t n = write(1, "Hello\n", 6);

// Under the hood:
// 1. Load syscall number into RAX (write = 1)
// 2. Load arguments into RDI, RSI, RDX
// 3. Execute SYSCALL instruction → trap to kernel
// 4. Kernel validates, performs write to stdout
// 5. SYSRET → back to user mode
// 6. Return value in RAX
```

### Library Function vs System Call
```
printf()   → C library function → internally calls write() → system call
malloc()   → C library function → internally calls brk()/mmap() → system call
           ↑                                                      ↑
      user space                                           kernel boundary
```

---

<a name="q9"></a>
## Q9. What is Inter-Process Communication (IPC)?

**Answer:**

**IPC** refers to mechanisms that allow processes to **communicate and synchronize** with each other. Since processes have separate memory spaces, they need OS-provided channels.

### IPC Mechanisms

#### 1. Pipes
```
[Process A] ──── write ────► [Pipe Buffer] ────► read ──── [Process B]
                             (FIFO, kernel buffer)

Anonymous Pipe: only between parent-child
Named Pipe (FIFO): unrelated processes, identified by file path

# Shell example (anonymous pipe):
ls -la | grep ".txt"   ← output of ls → input of grep
```

#### 2. Message Queues
```
[Process A] ──── msgsnd() ────► [Kernel Message Queue] ────► msgrcv() ──── [Process B]
                                 (messages persist in kernel until read)
```

#### 3. Shared Memory (Fastest IPC)
```
Process A address space:    Process B address space:
┌──────────────────────┐    ┌──────────────────────┐
│   Private memory     │    │   Private memory     │
├──────────────────────┤    ├──────────────────────┤
│  ┌────────────────┐  │    │  ┌────────────────┐  │
│  │ SHARED SEGMENT │◄─┼────┼─►│ SHARED SEGMENT │  │
│  └────────────────┘  │    │  └────────────────┘  │
└──────────────────────┘    └──────────────────────┘
Both processes map same physical memory page → direct read/write
Requires synchronization (semaphores/mutex) to avoid race conditions
```

#### 4. Sockets
```
[Process A] ──── send() ────► [OS Network Stack] ────► recv() ──── [Process B]
Works locally (Unix domain sockets) and across machines (TCP/UDP)
```

#### 5. Signals
```
kill(pid, SIGTERM)  → Send signal to process
Signal handlers     → Process defines how to react
Common: SIGKILL(9), SIGTERM(15), SIGINT(2), SIGSEGV(11), SIGCHLD
```

### IPC Comparison

| Method | Speed | Complexity | Scope | Synchronization |
|--------|-------|-----------|-------|----------------|
| Pipe | Medium | Low | Same machine | Built-in (blocking) |
| Message Queue | Medium | Medium | Same machine | Built-in |
| Shared Memory | **Fastest** | High | Same machine | Manual (semaphore) |
| Socket | Slowest | High | Network-wide | Manual |
| Signal | N/A | Low | Same machine | Asynchronous |

---

<a name="q10"></a>
## Q10. What is a Critical Section Problem?

**Answer:**

A **Critical Section** is a code segment that accesses **shared resources** (variables, files, data structures) that must not be accessed by more than one process/thread simultaneously.

### The Problem

```c
// Shared variable
int counter = 0;

// Thread 1 and Thread 2 both execute:
void increment() {
    counter++;   // NOT atomic! Translates to:
                 // 1. LOAD  register ← counter
                 // 2. ADD   register ← register + 1
                 // 3. STORE counter  ← register
}

// Race condition:
Thread 1: LOAD (reads 5)
Thread 2: LOAD (reads 5)       ← before T1 writes back
Thread 1: ADD → 6, STORE 6
Thread 2: ADD → 6, STORE 6     ← overwrites T1's update!
Result: counter = 6, expected: 7 ❌
```

### Requirements for a Valid Solution

```
1. Mutual Exclusion  → At most one process in CS at a time
2. Progress          → If no process is in CS, a process that wants to enter
                       must be allowed (no indefinite postponement)
3. Bounded Waiting   → A process waiting to enter CS must eventually be allowed
                       (no starvation — bounded number of others can enter first)
```

### Peterson's Algorithm (Two-Process Software Solution)
```c
// Shared:
bool flag[2] = {false, false};
int  turn    = 0;

// Process i (j = 1-i):
void enter_critical_section(int i) {
    int j = 1 - i;
    flag[i] = true;    // "I want to enter"
    turn = j;          // "But you go first"
    while (flag[j] && turn == j)
        ;              // Busy wait
    // --- CRITICAL SECTION ---
}

void exit_critical_section(int i) {
    flag[i] = false;   // "I'm done"
}
```
> **Note:** Peterson's algorithm works logically but requires **memory ordering guarantees** on modern CPUs — hardware uses compiler/CPU reordering which can violate assumptions without memory barriers.

---

<a name="q11"></a>
## Q11. What is a Mutex vs Semaphore?

**Answer:**

Both are synchronization primitives, but they differ in purpose and behavior.

### Mutex (Mutual Exclusion Lock)
- **Binary lock** — either locked or unlocked
- Only the **thread that locked it can unlock it** (ownership)
- Used to protect a **critical section**

```c
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void* increment(void* arg) {
    pthread_mutex_lock(&lock);      // Acquire lock
    counter++;                      // Critical section
    pthread_mutex_unlock(&lock);    // Release lock
    return NULL;
}
```

### Semaphore
- **Counter-based** synchronization — can be > 1
- Any thread can signal (release) a semaphore, regardless of who acquired it
- Two types: **Binary** (0 or 1) and **Counting** (0 to N)
- Used for **resource counting** and **signaling** between threads

```c
#include <semaphore.h>

sem_t sem;
sem_init(&sem, 0, 3);   // 3 threads can access simultaneously

void* worker(void* arg) {
    sem_wait(&sem);     // Decrement (P operation) — blocks if 0
    // Use shared resource (e.g., database connection pool of 3)
    sem_post(&sem);     // Increment (V operation) — wake blocked thread
    return NULL;
}
```

### Mutex vs Semaphore

| Feature | Mutex | Semaphore |
|---------|-------|-----------|
| Value | 0 or 1 (locked/unlocked) | Integer ≥ 0 |
| Ownership | Yes — only locker can unlock | No ownership |
| Purpose | Mutual exclusion (protect CS) | Signaling + resource counting |
| Release by | Same thread that locked | Any thread |
| Types | Standard, Recursive, Read-Write | Binary, Counting |
| Priority inversion | Addressed with priority inheritance | Not addressed |

### Spinlock vs Mutex

| | Spinlock | Mutex (Blocking) |
|-|----------|-----------------|
| Waiting | Busy-waits (wastes CPU) | Puts thread to sleep (context switch) |
| Best for | Very short critical sections | Long waits |
| Overhead | No context switch | Context switch overhead |

---

<a name="q12"></a>
## Q12. What is a Deadlock? Conditions and Prevention?

**Answer:**

A **deadlock** is a situation where a set of processes are **permanently blocked**, each waiting for a resource held by another process in the set — a circular wait with no way forward.

### Four Necessary Conditions (Coffman Conditions)

All four must hold simultaneously for a deadlock to occur:

```
1. Mutual Exclusion   → Resource held by at most one process at a time
2. Hold and Wait      → Process holds ≥1 resource and waits for more
3. No Preemption      → Resources cannot be forcibly taken away
4. Circular Wait      → P1 waits for P2, P2 waits for P3, P3 waits for P1
```

### Circular Wait Illustration
```
P1 ──holds──► R1          P1 ─── waiting for R2 ───────────┐
P2 ──holds──► R2          P2 ─── waiting for R1 ───────────┤
                                                            │
      R1◄──────P1◄──waits──P2──waits──►R2◄──P1  DEADLOCK ←┘
```

### Deadlock Handling Strategies

#### 1. Prevention (Break one Coffman condition)
```
Break Mutual Exclusion → Make resources sharable (read locks)
Break Hold & Wait      → Process must request ALL resources at once
Break No Preemption    → Forcibly take resources from waiting process
Break Circular Wait    → Impose global ordering on resource types
                         (always request R1 before R2 before R3)
```

#### 2. Avoidance — Banker's Algorithm
Dynamically check if granting a request leads to an **unsafe state** (see Q13).

#### 3. Detection + Recovery
Allow deadlocks to happen, then detect and recover:
```
Detection: Build a resource allocation graph (RAG), look for cycles
Recovery:
  a) Process termination — kill one or all deadlocked processes
  b) Resource preemption  — forcibly take resources, rollback process
```

#### 4. Ignorance (Ostrich Algorithm)
Pretend deadlocks don't happen — used in most general-purpose OS (Linux, Windows) because deadlocks are rare and prevention is expensive.

### Resource Allocation Graph (RAG)
```
Vertices: Processes (circles) + Resources (squares)
Edges:
  Request edge:    P → R  (process requests resource)
  Assignment edge: R → P  (resource assigned to process)

Cycle in RAG with single-instance resources → Deadlock ✅
Cycle in RAG with multi-instance resources  → Maybe deadlock (check further)
```

---

<a name="q13"></a>
## Q13. What is the Banker's Algorithm?

**Answer:**

The **Banker's Algorithm** (Dijkstra, 1965) is a **deadlock avoidance** algorithm. Before granting a resource request, it simulates the allocation and checks whether the system remains in a **safe state** — a state where all processes can eventually complete.

### Key Data Structures

```
n processes, m resource types

Allocation[n][m]  → Resources currently allocated to each process
Max[n][m]         → Maximum resources each process may ever request
Available[m]      → Currently available resources
Need[n][m]        → Remaining resources needed = Max - Allocation
```

### Example

```
Resources: A(10), B(5), C(7)    Available: A=3, B=3, C=2

         Allocation    Max       Need (Max-Alloc)
         A  B  C      A  B  C   A  B  C
P0:      0  1  0      7  5  3   7  4  3
P1:      2  0  0      3  2  2   1  2  2
P2:      3  0  2      9  0  2   6  0  0
P3:      2  1  1      2  2  2   0  1  1
P4:      0  0  2      4  3  3   4  3  1
```

### Safety Algorithm
```
Step 1: Work = Available = [3,3,2], Finish[all] = false
Step 2: Find process i where Finish[i]=false AND Need[i] ≤ Work

  Work=[3,3,2]:  P1 needs [1,2,2] ≤ [3,3,2] ✅ → run P1, Work = [3,3,2]+[2,0,0] = [5,3,2]
  Work=[5,3,2]:  P3 needs [0,1,1] ≤ [5,3,2] ✅ → run P3, Work = [5,3,2]+[2,1,1] = [7,4,3]
  Work=[7,4,3]:  P4 needs [4,3,1] ≤ [7,4,3] ✅ → run P4, Work = [7,4,3]+[0,0,2] = [7,4,5]
  Work=[7,4,5]:  P0 needs [7,4,3] ≤ [7,4,5] ✅ → run P0, Work = [7,4,5]+[0,1,0] = [7,5,5]
  Work=[7,5,5]:  P2 needs [6,0,0] ≤ [7,5,5] ✅ → run P2

Safe sequence: <P1, P3, P4, P0, P2> ✅ System is in SAFE STATE
```

### Resource Request Algorithm
When process Pi requests resources:
1. If Request[i] > Need[i] → Error (exceeded maximum claim)
2. If Request[i] > Available → Wait (resources unavailable)
3. **Tentatively** allocate: Available -= Request[i], Allocation[i] += Request[i], Need[i] -= Request[i]
4. Run Safety Algorithm → if safe, grant; if unsafe, **rollback and wait**

> **Limitation:** Requires knowing maximum resource needs in advance — not practical for general-purpose OS.

---

<a name="q14"></a>
## Q14. What is Memory Management?

**Answer:**

**Memory Management** is the OS function that manages the **allocation and deallocation of RAM** to processes, ensuring isolation, efficiency, and protection.

### Memory Hierarchy

```
     Fastest, smallest, most expensive
     ┌──────────────────────────────────┐
     │     CPU Registers (~1 ns)        │ ~few KB
     ├──────────────────────────────────┤
     │     L1 Cache (~4 ns)             │ ~32 KB
     ├──────────────────────────────────┤
     │     L2 Cache (~12 ns)            │ ~256 KB
     ├──────────────────────────────────┤
     │     L3 Cache (~40 ns)            │ ~8 MB
     ├──────────────────────────────────┤
     │     Main Memory / RAM (~100 ns)  │ ~8–64 GB
     ├──────────────────────────────────┤
     │     SSD (~100 µs)                │ ~256 GB–2 TB
     ├──────────────────────────────────┤
     │     HDD (~10 ms)                 │ ~1–10 TB
     └──────────────────────────────────┘
     Slowest, largest, least expensive
```

### Memory Allocation Techniques

#### Contiguous Allocation
Each process gets a **single contiguous block** of RAM:
```
RAM:  [OS] [P1: 100KB] [P2: 200KB] [Free: 50KB] [P3: 150KB]
```
- **Fixed partitioning** — RAM divided into fixed-size partitions (internal fragmentation)
- **Dynamic partitioning** — partitions created to fit each process (external fragmentation)

#### Allocation Strategies
| Strategy | Picks | Pros | Cons |
|----------|-------|------|------|
| **First Fit** | First hole that fits | Fast | Fragmentation at start |
| **Best Fit** | Smallest hole that fits | Less wasted space | Leaves tiny holes |
| **Worst Fit** | Largest hole | Leaves large remnants | Wastes large holes |
| **Next Fit** | Next hole from last allocation | Uniform distribution | Similar to first fit |

---

<a name="q15"></a>
## Q15. What is Paging?

**Answer:**

**Paging** is a memory management scheme that eliminates external fragmentation by dividing both **physical memory** into fixed-size **frames** and **logical (virtual) memory** into same-sized **pages**. The OS maintains a **page table** to map virtual pages to physical frames.

```
Virtual Address Space (Process)      Physical Memory (RAM)
┌──────────────────────┐             ┌──────────────────────┐
│  Page 0 (code)       │──────────►  │  Frame 3             │
│  Page 1 (data)       │──────────►  │  Frame 7             │
│  Page 2 (heap)       │──────────►  │  Frame 1             │
│  Page 3 (stack)      │──────────►  │  Frame 9             │
└──────────────────────┘             └──────────────────────┘
Pages and frames are the SAME size (e.g., 4KB)
Pages can map to ANY frame — contiguous logical, non-contiguous physical ✅
```

### Address Translation

```
Virtual Address = [Page Number (p) | Page Offset (d)]
                   ↓
              Page Table[p] → Frame Number (f)
                   ↓
Physical Address = [Frame Number (f) | Page Offset (d)]

Example (page size = 4KB = 2^12, so offset = 12 bits):
Virtual Address: 0x3A7C
  Page Number  = 0x3A7C >> 12 = 3
  Offset       = 0x3A7C & 0xFFF = 0xA7C
  Page Table[3] → Frame 9
Physical Address = (9 << 12) | 0xA7C = 0x9A7C
```

### Translation Lookaside Buffer (TLB)
Page table lookup requires an extra memory access — the **TLB** is a small hardware cache that stores recent page→frame mappings:

```
Virtual Address
      │
      ▼
   TLB Lookup
  ┌──────────┐
  │ TLB Hit? │──YES──► Physical Address (fast, ~1 cycle)
  └──────────┘
       │ NO (TLB Miss)
       ▼
  Page Table Walk in RAM (~100 cycles)
       │
       ▼
  Update TLB → Physical Address
```

**TLB Hit Rate** is typically >99% due to **temporal and spatial locality**.

### Page Table Size Problem
For a 32-bit address space with 4KB pages:
```
Number of pages = 2^32 / 2^12 = 2^20 = 1,048,576 entries
Each entry = 4 bytes
Page table size = 4MB per process ← too large!
```
**Solutions:**
- **Multi-level page tables** (2-level, 3-level, 4-level — used by x86-64)
- **Inverted page tables** (one entry per physical frame, not per virtual page)

---

<a name="q16"></a>
## Q16. What is Segmentation?

**Answer:**

**Segmentation** is a memory management technique that divides a process's virtual address space into **logical segments** of **variable size** corresponding to the program's logical structure (code, stack, heap, data).

```
Process Virtual Address Space:
┌─────────────────────┐
│   Code Segment      │ → Segment 0 (read-only, execute)
├─────────────────────┤
│   Data Segment      │ → Segment 1 (read-write)
├─────────────────────┤
│   Stack Segment     │ → Segment 2 (read-write, grows down)
├─────────────────────┤
│   Heap Segment      │ → Segment 3 (read-write, grows up)
└─────────────────────┘
```

### Segment Table
Each entry stores: **Base address** + **Limit** (size) + **Protection bits**

```
Segment Table:
Seg # │ Base    │ Limit  │ Protection
──────┼─────────┼────────┼───────────
  0   │ 0x4000  │ 0x600  │ R-X
  1   │ 0x1000  │ 0x400  │ RW-
  2   │ 0xF000  │ 0x800  │ RW-
```

### Address Translation
```
Logical Address = [Segment Number (s) | Offset (d)]

If d > Limit[s] → Segmentation Fault ❌
Else:
Physical Address = Base[s] + d ✅
```

### Paging vs Segmentation

| Feature | Paging | Segmentation |
|---------|--------|-------------|
| Division unit | Fixed-size pages | Variable-size segments |
| External fragmentation | None | Yes (variable sizes) |
| Internal fragmentation | Yes (last page may be partial) | None |
| Logical structure | No (OS-level only) | Yes (matches program structure) |
| Protection | Per page (uniform) | Per segment (code=RX, data=RW) |
| User visible | No | Yes (programmer sees segments) |
| Modern usage | Dominant | Combined with paging (x86 segments+paging) |

### Segmentation Fault
When a program accesses memory outside its segment limits or with wrong permissions:
```
char* ptr = NULL;
*ptr = 5;  → Accessing address 0 → outside any valid segment → SIGSEGV
```

---

<a name="q17"></a>
## Q17. What is Virtual Memory?

**Answer:**

**Virtual Memory** is a memory management technique that gives each process the illusion of having a **large, private, contiguous address space**, even if the physical RAM is smaller or fragmented. It uses disk storage (swap space) as an extension of RAM.

```
Process sees:          Reality:
┌──────────────────┐   ┌─────────────────────┐   ┌──────────────┐
│ Virtual Address  │   │   Physical RAM       │   │  Swap (Disk) │
│ Space (e.g. 4GB) │   │   (e.g. 2GB)        │   │  (e.g. 8GB)  │
│                  │   │  [Some pages here]   │   │[Other pages] │
│   (all 4GB seems │   │                      │   │              │
│    available)    │   └─────────────────────┘   └──────────────┘
└──────────────────┘         Page Table maps virtual → physical or swap
```

### Benefits of Virtual Memory

| Benefit | Description |
|---------|-------------|
| **Process isolation** | Each process has its own address space — can't corrupt others |
| **Memory overcommit** | Run programs larger than physical RAM |
| **Shared libraries** | Multiple processes map same physical pages (e.g., libc.so) |
| **Simplified programming** | Programs always start at virtual address 0 |
| **Security** | No direct hardware address exposure |

### Virtual Address Space Layout (64-bit Linux)

```
0xFFFFFFFFFFFFFFFF ┌──────────────────┐
                   │   Kernel Space   │  (128 TB, protected)
0xFFFF800000000000 ├──────────────────┤
                   │    (unmapped)    │
0x00007FFFFFFFFFFF ├──────────────────┤
                   │   User Stack     │ ← grows downward
                   │       ↓          │
                   │   mmap / libs    │ (shared libraries, mmap'd files)
                   │       ↑          │
                   │      Heap        │ ← grows upward (brk/mmap)
                   │   BSS / Data     │
                   │   Code (Text)    │
0x0000000000400000 └──────────────────┘
```

---

<a name="q18"></a>
## Q18. What is Demand Paging and Page Faults?

**Answer:**

**Demand Paging** is a virtual memory strategy where pages are loaded into RAM **only when they are actually needed** (on demand), not at process startup. This saves memory and speeds up program launch.

```
Process starts:  Only a few pages loaded
                 Rest of pages marked as NOT PRESENT in page table

Program accesses page 5:
  CPU checks page table → Page 5 NOT PRESENT → PAGE FAULT ← hardware interrupt

OS Page Fault Handler:
  1. Is this address valid? (in process's virtual address space?)
     No  → Segmentation fault (SIGSEGV), terminate process
     Yes → Continue
  2. Is there free frame in RAM?
     Yes → Load page from disk into frame, update page table
     No  → Page replacement algorithm (select victim page, swap out)
  3. Restart the faulting instruction

Program continues transparently ✅
```

### Types of Page Faults

| Type | Cause | Action |
|------|-------|--------|
| **Minor (soft) fault** | Page is in memory but not mapped in page table (e.g., shared pages) | Just update page table — no disk I/O |
| **Major (hard) fault** | Page must be loaded from disk | Disk I/O required — slow (~10ms) |
| **Invalid fault** | Access to unmapped / unauthorized address | Send SIGSEGV to process |

### Effective Access Time (EAT)
```
p = page fault rate (0 ≤ p ≤ 1)
Memory access time = 200 ns
Page fault service time = 10 ms = 10,000,000 ns

EAT = (1-p) × 200 + p × 10,000,000

For EAT ≤ 220 ns (less than 10% degradation):
  p < 0.000002 (less than 1 page fault per 500,000 accesses!)
```

### Copy-on-Write (COW)
After `fork()`, parent and child **share the same physical pages** (marked read-only). When either writes, the OS creates a private copy of just that page:
```
fork():   parent pages ──── shared (COW) ────► child pages
write():  OS detects write → copy page → each gets private copy
No copying at fork time → very fast ✅
```

---

<a name="q19"></a>
## Q19. What are Page Replacement Algorithms?

**Answer:**

When a page fault occurs and **no free frames exist**, the OS must **evict (replace)** an existing page from RAM to disk to make room. The choice of which page to evict is determined by a page replacement algorithm.

### Goal: Minimize the number of page faults.

### 1. FIFO — First In First Out
Evict the page that has been in memory the **longest**.

```
Reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Frames: 3

7 → [7,-,-]    fault
0 → [7,0,-]    fault
1 → [7,0,1]    fault
2 → [2,0,1]    fault (evict 7, oldest)
0 → hit
3 → [2,3,1]    fault (evict 0)
...
Total page faults = 15
```
**Belady's Anomaly:** More frames can cause MORE faults with FIFO.

### 2. OPT — Optimal Page Replacement
Evict the page that **will not be used for the longest time** in the future. Theoretical lower bound — not implementable (needs future knowledge).

```
Used to benchmark other algorithms.
Achieves minimum possible page faults.
```

### 3. LRU — Least Recently Used
Evict the page that **has not been used for the longest time** in the past. Approximates OPT using past as predictor of future.

```
Reference: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Frames: 3
Total faults = 12 (better than FIFO's 15)
```

**LRU Implementation:**
- **Counter-based:** Timestamp each access, evict smallest timestamp
- **Stack-based:** Keep accessed pages at top of stack; evict bottom
- **Hardware support needed:** Track every memory access → expensive

### 4. LRU Approximations (used in real OS)

**Clock Algorithm (Second Chance):**
```
Pages arranged in circular list, each has a Reference Bit (R)
Clock hand sweeps:
  R=1 → Set R=0, move hand (give second chance)
  R=0 → Evict this page ← victim

Simple to implement, approximates LRU well
Used by Linux (active/inactive page lists)
```

### Comparison

| Algorithm | Faults | Implementable | Notes |
|-----------|--------|:------------:|-------|
| FIFO | Most | ✅ | Simple, Belady's anomaly possible |
| OPT | Least (optimal) | ❌ | Theoretical benchmark |
| LRU | Near-optimal | ✅ (with HW) | Best practical performance |
| Clock | Near-LRU | ✅ | Used in real OS |
| NFU / Aging | Near-LRU | ✅ | Software LRU approximation |

---

<a name="q20"></a>
## Q20. What is Thrashing?

**Answer:**

**Thrashing** occurs when a process (or the OS) spends more time **swapping pages in and out** of disk than executing actual instructions — the system is so short on memory that it constantly services page faults with no useful progress.

```
Normal:    CPU executing ──────── occasional page fault ──────── back to executing
                                  (disk I/O)

Thrashing: [page fault → disk I/O → page fault → disk I/O → page fault → ...]
           CPU utilization → near 0%    Disk I/O → 100%
```

### Cause of Thrashing

```
Too many processes in memory → each process gets too few frames
→ Frequent page faults → OS spends all time on paging
→ CPU utilization drops → OS thinks: "need more processes!"
→ Adds more processes → even fewer frames each → more faults
→ Cascade collapse ❌
```

### CPU Utilization vs Degree of Multiprogramming

```
CPU
Util.
 │                    ●
 │                 ●     ●
 │              ●           ●  ← Thrashing begins
 │           ●                  ●
 │         ●                       ●
 │       ●
 └──────────────────────────────────────► # processes
              Optimal range   ↑ Avoid this
```

### Solutions to Thrashing

| Solution | Description |
|----------|-------------|
| **Working Set Model** | Track pages used in recent window (Δ); ensure each process has enough frames for its working set |
| **Page Fault Frequency (PFF)** | If page fault rate too high → give process more frames; if too low → reclaim frames |
| **Load Control** | Suspend/swap out some processes to reduce multiprogramming degree |
| **Increase RAM** | More physical memory reduces competition |

### Working Set
```
Working Set W(t, Δ) = set of pages referenced in the last Δ time units
Δ = working set window (e.g., last 10,000 references)

Allocate each process at least |W(t,Δ)| frames
If Σ|W| > total frames → suspend a process
```

---

<a name="q21"></a>
## Q21. What is Fragmentation? Internal vs External?

**Answer:**

**Fragmentation** is the wasted memory that cannot be used even though it exists, due to how memory is allocated.

### Internal Fragmentation
Wasted space **inside** an allocated memory block — occurs when allocated block is slightly larger than requested.

```
Partition size: 100 KB
Process needs:  94 KB
Internal fragmentation: 6 KB (allocated but unusable by process or anyone else)

Occurs with: Fixed partitioning, Paging
```

### External Fragmentation
Wasted space **outside** allocated blocks — there is enough total free memory, but it is scattered in non-contiguous chunks.

```
RAM:  [P1: 100KB][Free: 20KB][P2: 80KB][Free: 30KB][P3: 50KB][Free: 25KB]
Total free: 75KB, but no single contiguous block ≥ 75KB

New process needs: 60KB → Cannot allocate! ❌

Occurs with: Dynamic partitioning, Segmentation
```

### Solutions

| Problem | Solution |
|---------|----------|
| External Fragmentation | **Compaction** (move processes together) — expensive; **Paging** (eliminates external frag) |
| Internal Fragmentation | Smaller allocation units; **Slab Allocator** (kernel uses exact-sized caches) |

### 50% Rule
With first-fit allocation, statistically about **1/3 of memory** is lost to external fragmentation — for every 2 allocated blocks, ~1 block's worth is fragmented.

```
Compaction:
Before: [P1][Free][P2][Free][P3][Free]
After:  [P1][P2][P3][Large Free Block] ← processes relocated
Cost:   Must update all memory pointers — expensive!
```

---

<a name="q22"></a>
## Q22. What is a Cache? Cache Levels and Locality?

**Answer:**

A **cache** is a small, fast memory storage layer that holds copies of recently or frequently accessed data to reduce the time and cost of accessing slower memory (RAM or disk).

### Cache Hierarchy

```
         CPU Core
    ┌────────────────────┐
    │    Registers       │  ~1 cycle,   ~few bytes
    │    L1 Cache        │  ~4 cycles,  ~32 KB  (per core, private)
    │    L2 Cache        │  ~12 cycles, ~256 KB (per core, private)
    └────────────────────┘
         L3 Cache          ~40 cycles, ~8–32 MB (shared across cores)
         Main RAM          ~100–300 cycles, GBs
         SSD               ~100,000 cycles
         HDD               ~10,000,000 cycles
```

### Cache Hit vs Miss
```
Cache Hit:  Data found in cache → serve immediately (fast)
Cache Miss: Data NOT in cache → fetch from next level (slow)
            Types:
              Cold miss    → First access ever (unavoidable)
              Capacity miss → Cache too small to hold working set
              Conflict miss → Two data map to same cache line
```

### Locality of Reference

**Temporal Locality:** Recently accessed data will likely be accessed again soon.
```c
for (int i = 0; i < 1000000; i++) {
    sum += arr[i];   // 'sum' accessed repeatedly → stays in register/L1
}
```

**Spatial Locality:** Data near recently accessed locations will likely be accessed soon.
```c
// Good spatial locality (row-major = cache friendly):
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        sum += matrix[i][j];   // Sequential access → full cache line used ✅

// Bad spatial locality (column-major = cache unfriendly):
for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++)
        sum += matrix[i][j];   // Jumps by row size → constant cache misses ❌
```

### Cache Write Policies
| Policy | Behavior | Consistency |
|--------|----------|-------------|
| **Write-Through** | Write to cache AND memory simultaneously | Always consistent, slower |
| **Write-Back** | Write to cache only; write to memory when evicted | Faster, risk of data loss on crash |

---

<a name="q23"></a>
## Q23. What is a File System?

**Answer:**

A **File System** is the OS component that manages how data is **stored, organized, retrieved, and named** on storage devices. It provides the abstraction of files and directories.

### File System Responsibilities

| Function | Description |
|----------|-------------|
| **Naming** | Map human-readable names to data locations |
| **Organization** | Directory structure (tree hierarchy) |
| **Storage allocation** | Decide where on disk to place file data |
| **Access control** | Permissions (read/write/execute per user/group) |
| **Metadata** | Timestamps, size, owner, type |
| **Reliability** | Journaling, checksums, crash recovery |

### File Metadata — inode (Unix/Linux)
Every file has an **inode** storing all metadata (except the filename):

```
inode #4823:
┌─────────────────────────────────────────────┐
│ File type       : regular file              │
│ Permissions     : rw-r--r-- (644)           │
│ Owner / Group   : alice / developers        │
│ File size       : 4096 bytes                │
│ Timestamps      : created, modified, accessed│
│ Hard link count : 2                         │
│ Data block ptrs : [block 142, block 389...] │
└─────────────────────────────────────────────┘
```

### Directory Structure
A **directory** is a special file mapping filenames → inode numbers:
```
/home/alice/
  ├── inode 4821 → "documents" (directory)
  ├── inode 4823 → "notes.txt" (file)
  └── inode 4850 → "photo.jpg" (file)
```

### Popular File Systems

| File System | OS | Key Feature |
|-------------|-----|-------------|
| **ext4** | Linux | Journaling, extents, widely used |
| **XFS** | Linux | High-performance, large files |
| **Btrfs** | Linux | Snapshots, checksums, copy-on-write |
| **NTFS** | Windows | Journaling, permissions, compression |
| **FAT32** | Universal | Compatible, no permissions, 4GB file limit |
| **APFS** | macOS/iOS | Encryption, snapshots, copy-on-write |
| **ZFS** | FreeBSD/Linux | Built-in RAID, checksums, snapshots |

### Journaling
Prevents corruption on crash by **logging intended changes** before applying them:
```
Without journaling: partial write during crash → corrupted metadata
With journaling:
  1. Write changes to journal (log) → on disk
  2. Apply changes to file system
  3. Clear journal entry
  On crash: replay journal on next mount → guaranteed consistency ✅
```

---

<a name="q24"></a>
## Q24. What are File Allocation Methods?

**Answer:**

File allocation methods determine **how disk blocks are assigned** to files.

### 1. Contiguous Allocation
Each file occupies **consecutive blocks** on disk.

```
Disk:  [Free][file.txt: blocks 4-7][Free][doc.pdf: blocks 12-18][Free]
              ↑ start=4, length=4         ↑ start=12, length=7
```

| Pros | Cons |
|------|------|
| Simple, fast sequential access | External fragmentation |
| Supports random access easily | File growth is difficult |
| Minimal metadata | Must know file size at creation |

### 2. Linked Allocation
Each block contains a **pointer to the next block** — forming a linked list.

```
File = Block 5 → Block 12 → Block 17 → Block 3 → NULL
       [data|→12]  [data|→17]  [data|→3]  [data|NULL]
```

| Pros | Cons |
|------|------|
| No external fragmentation | No random access (must traverse) |
| File can grow dynamically | Pointer overhead per block |
| Simple | Poor reliability (broken pointer = lost file) |

**FAT (File Allocation Table)** — optimization: store all pointers in a separate table in memory → random access via table lookup.

### 3. Indexed Allocation
A special **index block** holds all block pointers for the file.

```
Index block for myfile.txt:
┌────────────────────────────┐
│ Block 0 pointer → 15       │
│ Block 1 pointer → 42       │
│ Block 2 pointer → 7        │
│ Block 3 pointer → 91       │
└────────────────────────────┘
→ Disk block 15: [data of block 0]
→ Disk block 42: [data of block 1]
...
```

| Pros | Cons |
|------|------|
| Supports random access | Index block overhead |
| No external fragmentation | Small index block limits file size |
| Dynamic growth | Extra disk access for index block |

**Unix inode — Multi-level Indexing:**
```
inode contains:
  12 direct block pointers            →  12 × 4KB = 48 KB
  1 single-indirect pointer           →  1024 × 4KB = 4 MB
  1 double-indirect pointer           →  1024² × 4KB = 4 GB
  1 triple-indirect pointer           →  1024³ × 4KB = 4 TB
```

---

<a name="q25"></a>
## Q25. What is Disk Scheduling? Algorithms?

**Answer:**

**Disk Scheduling** determines the **order in which disk I/O requests are serviced** to minimize the disk **seek time** (the time to move the read/write head to the correct track).

```
Disk Structure:
  Platters → Tracks (concentric circles) → Sectors
  
  Seek Time     = time to move head to correct TRACK   (dominant cost)
  Rotational Latency = time to wait for sector to spin under head
  Transfer Time = time to actually read/write data
```

### Scheduling Algorithms

**Assume requests queue: 82, 170, 43, 140, 24, 16, 190 | Head starts at: 50**

#### 1. FCFS — First Come First Served
```
Head: 50 → 82 → 170 → 43 → 140 → 24 → 16 → 190
Total movement: 32+88+127+97+116+8+174 = 642 cylinders
Simple but not optimal.
```

#### 2. SSTF — Shortest Seek Time First
Always service the request **closest** to current head position.
```
Head: 50 → 43 → 24 → 16 → 82 → 140 → 170 → 190
Total movement: 7+19+8+66+58+30+20 = 208 cylinders ✅
Problem: Starvation of far requests.
```

#### 3. SCAN (Elevator Algorithm)
Head moves in one direction, servicing all requests, then **reverses**.
```
Head: 50 → 82 → 140 → 170 → 190 → [end] → 43 → 24 → 16
Total movement = 319 cylinders
Fair — no starvation. Like an elevator.
```

#### 4. C-SCAN (Circular SCAN)
Like SCAN, but only services requests going in **one direction**, then jumps back to start.
```
Head: 50 → 82 → 140 → 170 → 190 → [jump to 0] → 16 → 24 → 43
More uniform wait times than SCAN.
```

#### 5. LOOK / C-LOOK
Like SCAN/C-SCAN but only goes as far as the **last request** in that direction (doesn't go to disk end).

### Comparison

| Algorithm | Performance | Starvation | Notes |
|-----------|-------------|:----------:|-------|
| FCFS | Poor | No | Fair but inefficient |
| SSTF | Better | Yes | Greedy, close requests favored |
| SCAN | Good | No | Like elevator |
| C-SCAN | Good | No | More uniform wait |
| LOOK/C-LOOK | Best | No | Used in practice |

> **SSD Note:** SSDs have no mechanical head — seek time is near-zero. Disk scheduling matters mainly for HDDs. SSDs use **FTL (Flash Translation Layer)** instead.

---

<a name="q26"></a>
## Q26. What is RAID?

**Answer:**

**RAID (Redundant Array of Independent Disks)** combines multiple physical disks into a logical unit for **performance**, **redundancy**, or **both**.

```
Single Disk:
  [Controller] → [Disk 1]    ← single point of failure, limited bandwidth

RAID:
  [Controller] → [Disk 1]
              → [Disk 2]     ← parallel reads, redundancy
              → [Disk 3]
```

### RAID Levels

#### RAID 0 — Striping (Performance only)
```
Data:  [A1][A2][A3][A4]
       ────────────────── Striped across 2 disks
Disk1: [A1][A3]
Disk2: [A2][A4]

Pros:  2× read/write speed
Cons:  ANY disk failure = total data loss (no redundancy!) ❌
```

#### RAID 1 — Mirroring (Redundancy only)
```
Disk1: [A1][A2][A3]   ← original
Disk2: [A1][A2][A3]   ← exact mirror

Pros:  Survives 1 disk failure, 2× read performance
Cons:  50% storage efficiency (need 2× space)
```

#### RAID 5 — Striping with Distributed Parity
```
Disk1: [A1][B1][C1][P_D]
Disk2: [A2][B2][P_C][D2]
Disk3: [A3][P_B][C3][D3]
Disk4: [P_A][B4][C4][D4]
Parity rotated across disks

Pros:  Survives 1 disk failure, good storage efficiency (N-1)/N
Cons:  Slow writes (parity calculation), complex recovery
Minimum: 3 disks
```

#### RAID 6 — Striping with Double Parity
- Two parity blocks → survives **2 simultaneous disk failures**
- Minimum 4 disks

#### RAID 10 (1+0) — Mirror + Stripe
```
[Disk1][Disk2] → mirrored pair 1
[Disk3][Disk4] → mirrored pair 2
Then stripe across the pairs

Best of both worlds: performance + redundancy
Minimum: 4 disks, 50% storage efficiency
```

### RAID Comparison

| Level | Min Disks | Fault Tolerance | Read Perf | Write Perf | Storage Efficiency |
|-------|:---------:|:---------------:|:---------:|:----------:|:-----------------:|
| RAID 0 | 2 | None | High | High | 100% |
| RAID 1 | 2 | 1 disk | High | Same | 50% |
| RAID 5 | 3 | 1 disk | High | Medium | (N-1)/N |
| RAID 6 | 4 | 2 disks | High | Low | (N-2)/N |
| RAID 10 | 4 | 1 per mirror | Very High | High | 50% |

---

<a name="q27"></a>
## Q27. What are Kernel Types? Monolithic vs Microkernel?

**Answer:**

The **kernel** is the core of the OS, running in privileged mode and managing all hardware resources. Kernel architecture defines which services run in kernel space vs user space.

### Monolithic Kernel
All OS services (file system, drivers, networking, memory, scheduling) run in **one large kernel space**.

```
┌─────────────────────────────────────────────────────────┐
│                   User Space                            │
│   Application A    Application B    Application C       │
└──────────────────────────┬──────────────────────────────┘
                           │ System Calls
┌──────────────────────────▼──────────────────────────────┐
│                 Kernel Space (ONE BIG MODULE)           │
│  Process Mgr │ Memory Mgr │ FS │ Drivers │ Network      │
│           All run with full kernel privileges           │
└─────────────────────────────────────────────────────────┘
│                     Hardware                            │
└─────────────────────────────────────────────────────────┘
Examples: Linux, Unix, MS-DOS
```

| Pros | Cons |
|------|------|
| Fast (no IPC overhead between services) | A bug in one service can crash entire OS |
| Simple communication between components | Hard to maintain and extend |
| High performance | Large attack surface |

### Microkernel
Only the **absolute minimum** (IPC, basic scheduling, memory management) runs in kernel space. Everything else (drivers, FS, networking) runs as user-space servers.

```
┌───────────────────────────────────────────────────────────────────┐
│                         User Space                                │
│  App A │ App B │ File System │ Device Driver │ Network Stack      │
└──────────────────────────────┬────────────────────────────────────┘
                               │ IPC Messages
┌──────────────────────────────▼────────────────────────────────────┐
│         Microkernel (tiny kernel space)                           │
│              IPC │ Basic Scheduling │ Memory                      │
└───────────────────────────────────────────────────────────────────┘
Examples: QNX, Minix, L4, seL4, GNU Hurd
```

| Pros | Cons |
|------|------|
| Fault isolation (crash a driver, not the OS) | Slower (IPC overhead for everything) |
| Easier to extend/port | Complex IPC mechanisms |
| Smaller trusted computing base | Performance-critical paths suffer |

### Hybrid Kernel
Combines monolithic and microkernel — most OS services in kernel for performance, but modular:
```
Windows NT kernel, macOS XNU (Mach microkernel + BSD monolithic layer)
```

### Kernel Module (Linux approach)
Linux is monolithic but supports **loadable kernel modules (LKM)** — drivers can be loaded/unloaded at runtime without rebooting:
```bash
lsmod          # list loaded modules
insmod foo.ko  # load a module
rmmod foo      # unload a module
```

---

<a name="q28"></a>
## Q28. What is the Boot Process?

**Answer:**

The **boot process** is the sequence of steps that occurs from pressing the power button to having a fully operational OS ready for user login.

### Boot Sequence (Modern x86 with UEFI)

```
1. Power On
      │
2. POST (Power-On Self Test)
      │ BIOS/UEFI firmware runs, checks hardware (CPU, RAM, disks)
      │
3. UEFI / BIOS Firmware
      │ Finds bootable device (disk, USB, network)
      │ Loads Boot Manager from EFI System Partition
      │
4. Bootloader (GRUB2 / Windows Boot Manager)
      │ Displays OS selection menu
      │ Loads kernel image into RAM
      │ Passes kernel parameters and initial RAM disk (initrd)
      │
5. Kernel Initialization
      │ Decompresses itself
      │ Detects hardware (CPU topology, memory map, devices)
      │ Sets up memory management (page tables, zones)
      │ Mounts initial RAM filesystem (initramfs/initrd)
      │
6. Init Process (PID 1)
      │ First user-space process
      │ Modern: systemd | Traditional: SysV init
      │
7. systemd / Init
      │ Starts system services (networking, logging, mounts)
      │ Reaches target runlevel / target unit
      │
8. Login Manager / Shell
      └── User logs in ✅
```

### BIOS vs UEFI

| Feature | BIOS | UEFI |
|---------|------|------|
| Age | 1970s | 2000s+ |
| Interface | 16-bit, text only | 32/64-bit, GUI possible |
| Disk support | MBR, max 2TB | GPT, max 9.4 ZB |
| Boot speed | Slower | Faster (parallel init) |
| Security | No | Secure Boot (verify bootloader signature) |

### Runlevels (SysV) vs Targets (systemd)

| Runlevel | systemd Target | Description |
|----------|----------------|-------------|
| 0 | poweroff.target | Shutdown |
| 1 | rescue.target | Single user (recovery) |
| 3 | multi-user.target | Multi-user, no GUI |
| 5 | graphical.target | Multi-user + GUI |
| 6 | reboot.target | Reboot |

---

<a name="q29"></a>
## Q29. What is Fork vs Exec?

**Answer:**

`fork()` and `exec()` are fundamental Unix/Linux system calls for process creation and execution.

### fork() — Duplicate a Process
Creates an **exact copy** of the calling (parent) process. Both parent and child continue execution from the point after `fork()`.

```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process (fork returns 0 to child)
        printf("I am child, PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        // Parent process (fork returns child's PID to parent)
        printf("I am parent, PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);   // Wait for child to finish
    }
    return 0;
}
```

**After fork():**
```
Parent Process                Child Process (clone of parent)
  PID = 1001                    PID = 1002
  Same code                     Same code
  Same data (copy-on-write)     Same data (copy-on-write)
  Same file descriptors         Same file descriptors
  fork() returns 1002           fork() returns 0
```

### exec() — Replace Process Image
Replaces the current process's code and data with a **new program**. The PID stays the same, but the program completely changes.

```c
#include <unistd.h>

// exec family variants:
execl("/bin/ls", "ls", "-la", NULL);   // path + arg list
execv("/bin/ls", argv);                // path + arg array
execvp("ls", argv);                    // search PATH + arg array

// After exec() succeeds, code below is NEVER reached
// The new program's main() starts executing
```

### fork + exec — The Shell Model

```
Shell process (bash):
   │
   ├── fork() ──────────────────────────────────► Child process (clone of bash)
   │                                                   │
   │                                              exec("/bin/ls")
   │                                                   │
   │                                             ls program runs
   │                                                   │
   │                                             ls exits → becomes zombie
   │◄── wait(NULL) ─────────────── SIGCHLD ─────── Parent reaps child
   │
   bash prompts again ✅
```

### Key Differences

| Feature | fork() | exec() |
|---------|--------|--------|
| Purpose | Create copy of process | Replace process image |
| PID | New PID for child | Same PID |
| Memory | Copy-on-write duplicate | Completely replaced |
| Returns | 0 (child) / child PID (parent) | Doesn't return on success |
| After call | Both processes run | Only new program runs |

### vfork()
Like `fork()` but **does NOT copy** the parent's address space — child shares parent's memory (parent is suspended until child calls exec or exits). Used for performance when exec immediately follows.

---

<a name="q30"></a>
## Q30. What are Signals in OS?

**Answer:**

**Signals** are software interrupts sent to a process to notify it of an **asynchronous event**. They are a basic form of IPC used for process control and error notification.

### Signal Lifecycle
```
Event occurs (e.g., Ctrl+C)
      │
OS sends SIGINT to foreground process
      │
Process handles signal:
  ├── Default action (terminate / ignore / stop / continue)
  ├── Custom handler (signal(SIGINT, my_handler))
  └── Ignore (signal(SIGINT, SIG_IGN))
```

### Important Signals

| Signal | Number | Default Action | Cause |
|--------|:------:|---------------|-------|
| **SIGHUP** | 1 | Terminate | Terminal disconnected |
| **SIGINT** | 2 | Terminate | Ctrl+C |
| **SIGQUIT** | 3 | Core dump | Ctrl+\ |
| **SIGILL** | 4 | Core dump | Illegal instruction |
| **SIGTRAP** | 5 | Core dump | Debugger breakpoint |
| **SIGABRT** | 6 | Core dump | abort() called |
| **SIGSEGV** | 11 | Core dump | Invalid memory access |
| **SIGPIPE** | 13 | Terminate | Broken pipe |
| **SIGALRM** | 14 | Terminate | alarm() expired |
| **SIGTERM** | 15 | Terminate | Graceful termination request |
| **SIGCHLD** | 17 | Ignore | Child process stopped/exited |
| **SIGSTOP** | 19 | Stop | Cannot be caught or ignored |
| **SIGKILL** | 9 | Terminate | Cannot be caught or ignored |
| **SIGCONT** | 18 | Continue | Resume stopped process |

### Custom Signal Handler
```c
#include <signal.h>
#include <stdio.h>

void sigint_handler(int sig) {
    printf("\nCaught SIGINT (signal %d). Cleaning up...\n", sig);
    // cleanup resources
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);   // Register handler
    // or using sigaction (preferred):
    struct sigaction sa = { .sa_handler = sigint_handler };
    sigaction(SIGINT, &sa, NULL);

    while(1) {
        printf("Running...\n");
        sleep(1);
    }
}
```

> **SIGKILL (9) and SIGSTOP (19)** cannot be caught, blocked, or ignored — they are handled directly by the kernel. Use `kill -9 PID` only as a last resort.

---

<a name="q31"></a>
## Q31. What is Spooling?

**Answer:**

**Spooling (Simultaneous Peripheral Operations On-Line)** is a technique where data is temporarily held in a buffer (usually on disk) to be consumed by a slower device at its own pace, allowing the CPU and applications to continue without waiting.

```
Classic Example — Print Spooling:

Application      OS Spooler (disk queue)     Printer
    │                    │                      │
    │── "print doc" ────►│                      │
    │◄─ returns ─────────│                      │
    │  (app continues)   │── sends to printer──►│
    │                    │  (at printer speed)   │
    │                    │◄── next job ─────────│
```

### How Spooling Works
```
1. Application sends output to spooler (fast — just writes to disk)
2. Application continues immediately (not blocked by slow printer)
3. Spooler daemon manages print queue: FIFO order, job management
4. Printer consumes jobs at its own speed
5. Multiple jobs queued, printer never goes idle if jobs available
```

### Benefits of Spooling

| Benefit | Description |
|---------|-------------|
| **CPU efficiency** | CPU not blocked waiting for slow I/O device |
| **Device sharing** | Multiple processes share a single printer |
| **Job management** | Cancel, reorder, prioritize print jobs |
| **Buffering** | Smooth rate mismatch between producer and consumer |

### Spooling vs Buffering vs Caching

| Technique | Purpose | Location | Persistence |
|-----------|---------|----------|-------------|
| **Buffering** | Rate mismatch, in-flight data | RAM | Temporary |
| **Caching** | Speed up future access | RAM | Until evicted |
| **Spooling** | Queue for slow device, enable concurrency | Disk | Until consumed |

---

<a name="q32"></a>
## Q32. What is Starvation and Aging?

**Answer:**

### Starvation
**Starvation** occurs when a process is **indefinitely denied** the resources it needs — it waits forever because other processes always get priority first.

```
Priority Scheduling with new high-priority jobs always arriving:

Time → ──────────────────────────────────────────────────────────►
         P_high P_high P_high P_high P_high P_high P_high ...
         P_low  (waiting... waiting... waiting... FOREVER) ❌
```

**Causes:**
- Priority scheduling with continuously arriving high-priority processes
- SSTF disk scheduling — requests near the head always served first
- Resource allocation favoring certain processes

### Aging — The Solution
**Aging** is a technique where the **priority of a waiting process is gradually increased** over time, ensuring it eventually gets served.

```
Process P_low starts at priority 5, waits too long:

t=0:   Priority = 5   (low)
t=10:  Priority = 6   (aging: +1 every 10 time units)
t=20:  Priority = 7
t=50:  Priority = 10  (now same as high-priority processes)
t=80:  Priority = 13  (now HIGHEST — guaranteed to run soon)
```

### Starvation in Other Contexts

| Context | Starvation Scenario | Solution |
|---------|--------------------|---------
| CPU Scheduling | Low-priority process never gets CPU | Aging (priority boost) |
| Disk Scheduling | Far disk requests never served (SSTF) | SCAN algorithm |
| Readers-Writers | Readers starve writers (or vice versa) | Fair queuing |
| Dining Philosophers | Philosopher never gets both forks | Asymmetric solution |
| Database | Low-priority transaction always aborted as victim | Wound-Wait scheme |

---

<a name="q33"></a>
## Q33. What is the Producer-Consumer Problem?

**Answer:**

The **Producer-Consumer** (Bounded Buffer) problem is a classic synchronization problem where:
- **Producer** generates data and puts it in a shared **bounded buffer**
- **Consumer** takes data from the buffer
- Both run concurrently and need synchronization

```
Producer:         Shared Buffer (size N):         Consumer:
[item] ──► PUT ──► [_][_][item][item][item] ──► GET ──► [item]
                    ↑                    ↑
                  empty                full
                  (signal consumer)   (signal producer to stop)
```

### Solution Using Semaphores

```c
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int    buffer[BUFFER_SIZE];
int    in = 0, out = 0;

sem_t  empty;    // counts empty slots (init = BUFFER_SIZE)
sem_t  full;     // counts filled slots (init = 0)
sem_t  mutex;    // binary semaphore for buffer access (init = 1)

void* producer(void* arg) {
    int item;
    while (1) {
        item = produce_item();       // Generate item
        sem_wait(&empty);            // Wait if buffer full
        sem_wait(&mutex);            // Enter critical section
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);            // Exit critical section
        sem_post(&full);             // Signal consumer: item available
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);             // Wait if buffer empty
        sem_wait(&mutex);            // Enter critical section
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);            // Exit critical section
        sem_post(&empty);            // Signal producer: slot available
        consume_item(item);
    }
}
```

### Key Points
- `empty` prevents producer from overwriting unread items
- `full` prevents consumer from reading from an empty buffer
- `mutex` ensures only one thread modifies buffer at a time
- **Order matters:** always acquire `mutex` AFTER `empty`/`full` to avoid deadlock

---

<a name="q34"></a>
## Q34. What is the Readers-Writers Problem?

**Answer:**

The **Readers-Writers Problem** models concurrent access to a shared resource (e.g., a database) where:
- **Multiple readers** can access simultaneously (read-only — safe to share)
- **Writers** need **exclusive access** (modifying — no reader or other writer allowed)

### Three Variants

| Variant | Priority | Risk |
|---------|----------|------|
| **First Readers-Writers** | Readers preferred | Writers may starve |
| **Second Readers-Writers** | Writers preferred | Readers may starve |
| **Third (Starve-free)** | Fair ordering (FIFO) | Neither starves |

### Solution (First Readers-Writers — Readers Preferred)

```c
int read_count = 0;           // Number of active readers
sem_t mutex;                  // Protects read_count (init=1)
sem_t write_lock;             // Exclusive write access (init=1)

void* reader(void* arg) {
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&write_lock);  // First reader blocks writers
        sem_post(&mutex);

        // ── READ shared data ──

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&write_lock);  // Last reader unblocks writers
        sem_post(&mutex);
    }
}

void* writer(void* arg) {
    while (1) {
        sem_wait(&write_lock);      // Exclusive access
        // ── WRITE shared data ──
        sem_post(&write_lock);
    }
}
```

### Access Matrix
```
         Reader2 waiting  Writer waiting
Reader1  ✅ Both can read  ❌ Writer waits
  in
access

Writer   ❌ Reader waits   ❌ Both wait
  in
access
```

### Real-World Analog
**Database:** `SELECT` queries = readers (many can run simultaneously), `UPDATE/INSERT/DELETE` = writers (need exclusive lock).  
SQL implements this with **shared locks** (reads) and **exclusive locks** (writes).

---

<a name="q35"></a>
## Q35. What is the Dining Philosophers Problem?

**Answer:**

The **Dining Philosophers Problem** (Dijkstra, 1965) is a classic synchronization problem illustrating **deadlock, starvation, and resource contention**.

### Setup
```
5 philosophers sit around a circular table.
5 forks placed between them (one between each pair).
Each philosopher alternates between THINKING and EATING.
To eat, a philosopher needs BOTH left and right forks.

         P0
        /  \
      F4    F0
      /        \
    P4          P1
    |            |
    F3          F1
      \        /
      P3──F2──P2
```

### The Deadlock Scenario
If all 5 philosophers pick up their **left fork simultaneously**:
```
P0 holds F4, waiting for F0
P1 holds F0, waiting for F1
P2 holds F1, waiting for F2
P3 holds F2, waiting for F3
P4 holds F3, waiting for F4   ← DEADLOCK (circular wait) ❌
```

### Solutions

#### 1. Asymmetric Solution (Odd/Even Rule)
```
Odd-numbered philosophers pick LEFT fork first, then RIGHT
Even-numbered philosophers pick RIGHT fork first, then LEFT
→ Breaks circular wait ✅
```

#### 2. Allow at Most N-1 Philosophers at Table
```
Only 4 of 5 philosophers may sit at once
→ At least one can always eat ✅
```

#### 3. Resource Hierarchy (Ordered Fork Pickup)
```
Number forks 0–4
Always pick up LOWER-numbered fork first
→ No circular dependency ✅
```

#### 4. Monitor / Semaphore Solution
```c
enum State { THINKING, HUNGRY, EATING };
State state[5];
sem_t mutex;        // init = 1
sem_t s[5];         // init = 0 for each philosopher

void pickup(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);                    // Can I eat now?
    sem_post(&mutex);
    sem_wait(&s[i]);            // Wait if can't eat
}

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i+4)%5] != EATING &&   // Left neighbor not eating
        state[(i+1)%5] != EATING) {   // Right neighbor not eating
        state[i] = EATING;
        sem_post(&s[i]);              // Philosopher i can eat
    }
}

void putdown(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    test((i+4)%5);   // Check if left neighbor can now eat
    test((i+1)%5);   // Check if right neighbor can now eat
    sem_post(&mutex);
}
```

### Lessons from Dining Philosophers

| Problem | What It Models |
|---------|---------------|
| Deadlock | All grab one resource, wait for another → cycle |
| Starvation | One philosopher never gets both forks |
| Mutual Exclusion | A fork can only be held by one philosopher |
| Concurrency | Philosophers can eat simultaneously if non-adjacent |

---

## 📌 Quick Revision Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────────┐
│                    Operating Systems — At a Glance                       │
├──────────────────────────┬───────────────────────────────────────────────┤
│ Process States           │ New→Ready→Running→Waiting→Terminated          │
│ PCB                      │ PID, state, PC, regs, memory, files, priority │
│ Process vs Thread        │ Own memory vs shared; heavy vs lightweight     │
│ Threading Models         │ M:1, 1:1 (Linux pthreads), M:N (Go)          │
│ Context Switch           │ Save/restore PCB; TLB flush cost              │
│ Scheduling               │ FCFS, SJF, SRTF, RR, Priority, MLFQ         │
│ System Call              │ User→Kernel mode gate; trap instruction        │
│ IPC                      │ Pipe, Msg Queue, Shared Mem, Socket, Signal   │
│ Critical Section         │ Mutex Excl + Progress + Bounded Wait          │
│ Mutex vs Semaphore       │ Ownership vs counter; CS vs signaling         │
│ Deadlock (4 conditions)  │ Mutual Excl + Hold&Wait + No Preempt + Circ  │
│ Banker's Algorithm       │ Safety check before granting resource         │
│ Paging                   │ Fixed pages, page table, TLB for speed        │
│ Segmentation             │ Variable segments, logical structure          │
│ Virtual Memory           │ Disk extends RAM, process isolation           │
│ Demand Paging            │ Load page only on access, page fault handler  │
│ Page Replacement         │ FIFO, OPT, LRU, Clock (used in Linux)        │
│ Thrashing                │ Too little RAM → constant paging → CPU~0%    │
│ Fragmentation            │ Internal (inside block), External (outside)   │
│ Cache Locality           │ Temporal (reuse), Spatial (nearby data)       │
│ File System              │ inode, directory, journaling, ext4/NTFS/APFS  │
│ File Allocation          │ Contiguous, Linked, Indexed (Unix inode)      │
│ Disk Scheduling          │ FCFS, SSTF, SCAN, C-SCAN, LOOK               │
│ RAID                     │ 0=stripe, 1=mirror, 5=parity, 10=mirror+stripe│
│ Kernel Types             │ Monolithic (Linux), Micro (QNX), Hybrid (Win) │
│ Boot Process             │ POST→UEFI→Bootloader→Kernel→Init→Login       │
│ fork() vs exec()         │ Clone process vs Replace program image        │
│ Signals                  │ SIGKILL(9), SIGTERM(15), SIGSEGV(11)         │
│ Classic Problems         │ Producer-Consumer, Readers-Writers, Dining    │
│ Starvation & Aging       │ Indefinite wait → fix by boosting priority    │
└──────────────────────────┴───────────────────────────────────────────────┘
```

---

> 💡 **Pro Interview Tips:**
> - For **process vs thread**, always mention memory sharing, context switch cost, and crash isolation
> - Know **all four Coffman conditions** for deadlock by heart — interviewers test this constantly
> - Explain **virtual memory** with the page table → TLB → physical address flow
> - For **scheduling algorithms**, be ready to calculate TAT/WT on a small example
> - **Classic sync problems** (Producer-Consumer, Readers-Writers, Dining Philosophers) — know the semaphore solutions
> - Mention **Copy-on-Write** when discussing `fork()` — shows deep understanding

---

*Happy Studying & Good Luck with your Interview! 🚀*
