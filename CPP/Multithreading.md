# Complete C++ Multithreading Guide
## From Zero to Thread-Safe: A Comprehensive Study Reference

> **Who this is for:** Anyone learning C++ multithreading from scratch. Every topic is explained with *why it exists*, *how it works*, *real code*, *common mistakes*, and *interview questions*. All 16 topics covered in depth.

---

## Table of Contents

1. [Threads in C++ — An Introduction](#1-threads-in-c--an-introduction)
2. [5 Different Ways to Create Threads in C++11](#2-5-different-ways-to-create-threads-in-c11)
3. [Join and Detach with Joinable](#3-join-and-detach-with-joinable)
4. [Mutex in C++ Threading](#4-mutex-in-c-threading)
5. [Mutex try_lock Member Function](#5-mutex-try_lock-member-function)
6. [std::try_lock in C++11 Threading](#6-stdtry_lock-in-c11-threading)
7. [Timed Mutex in C++ Threading](#7-timed-mutex-in-c-threading)
8. [Recursive Mutex in C++ Threading](#8-recursive-mutex-in-c-threading)
9. [Lock Guard in C++ Threading](#9-lock-guard-in-c-threading)
10. [Unique Lock in C++ Threading](#10-unique-lock-in-c-threading)
11. [Condition Variable and Its Usage](#11-condition-variable-and-its-usage)
12. [Deadlock in C++ Threading](#12-deadlock-in-c-threading)
13. [Thread / Process Synchronization](#13-thread--process-synchronization)
14. [std::lock in C++ Threading](#14-stdlock-in-c-threading)
15. [std::promise and std::future](#15-stdpromise-and-stdfuture)
16. [std::async — Create a Task](#16-stdasync--create-a-task)

---

## Quick-Reference Overview Table

| Topic | Header | Key Class/Function | One-Line Purpose |
|-------|--------|--------------------|------------------|
| Threads | `<thread>` | `std::thread` | Unit of concurrent execution |
| Mutex | `<mutex>` | `std::mutex` | Mutual exclusion lock |
| try_lock (member) | `<mutex>` | `mtx.try_lock()` | Non-blocking lock attempt |
| try_lock (free fn) | `<mutex>` | `std::try_lock()` | Lock multiple mutexes atomically |
| Timed Mutex | `<mutex>` | `std::timed_mutex` | Lock with timeout |
| Recursive Mutex | `<mutex>` | `std::recursive_mutex` | Re-entrant locking |
| Lock Guard | `<mutex>` | `std::lock_guard` | Scoped RAII mutex wrapper |
| Unique Lock | `<mutex>` | `std::unique_lock` | Flexible RAII mutex wrapper |
| Condition Variable | `<condition_variable>` | `std::condition_variable` | Thread wait/notify |
| Deadlock | — | — | Concept: circular wait |
| Synchronization | — | — | Concept: ordering threads |
| std::lock | `<mutex>` | `std::lock()` | Deadlock-free multi-lock |
| promise/future | `<future>` | `std::promise/future` | Pass value between threads |
| async | `<future>` | `std::async` | Run function asynchronously |

---

## 1. Threads in C++ — An Introduction

### 1.1 What is a Thread?

A **thread** is the smallest unit of execution within a process. Think of a process as a restaurant and threads as the individual cooks — they all share the same kitchen (memory), ingredients (global variables), and tools (heap), but each cook works on their own task simultaneously.

| Property | Process | Thread |
|----------|---------|--------|
| Memory | Own address space | Shared with other threads in same process |
| Creation cost | Heavy (fork system call) | Lightweight |
| Communication | IPC (pipes, sockets) | Shared memory (direct) |
| Crash impact | Isolated | One crash can kill all threads |

### 1.2 Why Threads?

- **Parallelism:** Do two things at once on multi-core CPUs (true simultaneous execution).
- **Concurrency:** Keep the program responsive while waiting (e.g., UI thread + background download thread).
- **Performance:** Divide a large task (e.g., sorting 10M elements) across N cores.

### 1.3 The C++ Memory Model

When threads run concurrently, they share:
- **Global/static variables** — accessible by all threads.
- **Heap memory** (anything created with `new`) — accessible if a pointer is shared.

Each thread has its own:
- **Stack** — local variables, function call frames.
- **Program counter** — which instruction it's executing.
- **Registers** — CPU working state.

### 1.4 Your First Thread

```cpp
#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello from thread!\n";
}

int main() {
    std::thread t(hello);   // Create and immediately start thread
    t.join();               // Wait for it to finish
    std::cout << "Main done.\n";
    return 0;
}
```

**Compilation:**
```bash
g++ -std=c++11 -pthread main.cpp -o main
```
> ⚠️ Always compile with `-pthread` on Linux/macOS. Without it, you'll get linker errors.

### 1.5 The Threading Problem — Race Conditions

```cpp
int counter = 0;   // shared variable

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;   // NOT ATOMIC: read → add → write (3 steps)
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << counter << "\n";  // Expected: 200000. Actual: RANDOM (150000-200000)
}
```

This is the core problem threading tools solve. Every subsequent topic is a tool to prevent this.

### 1.6 Key Concepts Summary

```
Thread Lifecycle:
  Created → Runnable → Running → Blocked/Waiting → Terminated

States:
  Runnable  = ready to run, waiting for CPU
  Running   = actually executing on a core
  Blocked   = waiting for I/O, mutex, or condition variable
  Terminated = function returned or thread was detached
```

### 1.7 Interview Questions

**Q: What is the difference between a thread and a process?**  
Threads share memory; processes have isolated memory. Threads are faster to create and communicate.

**Q: What happens if main() returns before a thread finishes?**  
Undefined behavior — the program terminates, potentially killing the thread mid-execution. Always `join()` or `detach()`.

**Q: Is `cout` thread-safe?**  
Individual calls to `cout` are thread-safe in C++11 (no crash), but output from multiple threads can interleave. Use a mutex to serialize output if order matters.

---

## 2. Five Different Ways to Create Threads in C++11

C++11 provides multiple ways to specify what a thread should execute. Understanding all five is essential.

### Method 1: Function Pointer

The simplest form — pass a regular function.

```cpp
#include <thread>
#include <iostream>

void printNum(int n) {
    std::cout << "Number: " << n << "\n";
}

int main() {
    std::thread t(printNum, 42);   // Pass function + arguments
    t.join();
}
```

### Method 2: Lambda Expression

Most common in modern C++. Allows capturing local variables.

```cpp
int main() {
    int x = 10;
    
    // Capture x by value
    std::thread t([x]() {
        std::cout << "x = " << x << "\n";
    });
    t.join();
    
    // Capture by reference — DANGEROUS if main ends before thread
    std::thread t2([&x]() {
        x = 20;   // Modifies main's x — need synchronization
    });
    t2.join();
    std::cout << "x is now: " << x << "\n";  // 20
}
```

> ⚠️ **Capture-by-reference danger:** If the thread outlives the captured variable's scope, you get undefined behavior (dangling reference).

### Method 3: Functor (Function Object)

A class with `operator()` overloaded. Useful for stateful thread logic.

```cpp
class Worker {
    int id;
public:
    Worker(int id) : id(id) {}
    
    void operator()() {
        std::cout << "Worker " << id << " running\n";
    }
};

int main() {
    Worker w(5);
    std::thread t(w);     // Copies the functor into the thread
    t.join();
    
    // Or directly:
    std::thread t2(Worker(7));   // ⚠️ Most Vexing Parse risk — use parentheses carefully
    t2.join();
}
```

> ⚠️ **Most Vexing Parse:** `std::thread t(Worker())` is parsed as a function declaration, not a variable. Use `std::thread t{Worker{}}` or `std::thread t((Worker()))`.

### Method 4: Member Function

To run a class method in a thread, you must pass the object (or pointer) explicitly.

```cpp
class Task {
public:
    void run(int n) {
        std::cout << "Task running with " << n << "\n";
    }
};

int main() {
    Task task;
    
    // Pass pointer to member function, then object (or pointer), then args
    std::thread t(&Task::run, &task, 42);
    t.join();
    
    // With a shared_ptr (safer for lifetime management)
    auto taskPtr = std::make_shared<Task>();
    std::thread t2(&Task::run, taskPtr, 99);
    t2.join();
}
```

### Method 5: std::bind

Wrap a callable + some arguments into a new callable. Useful for partial application.

```cpp
#include <functional>

void process(int a, int b, string label) {
    cout << label << ": " << a + b << "\n";
}

int main() {
    // Bind first argument, leave second free
    auto bound = std::bind(process, 10, std::placeholders::_1, "Sum");
    
    std::thread t(bound, 20);   // Passes 20 as b → "Sum: 30"
    t.join();
}
```

### Comparison Table

| Method | Syntax Complexity | State | Best Use |
|--------|------------------|-------|----------|
| Function pointer | Simple | Stateless | Simple tasks |
| Lambda | Medium | Captures scope | Most common, inline logic |
| Functor | Medium | Has state | Reusable thread workers |
| Member function | Verbose | Object state | OOP thread tasks |
| std::bind | Complex | Partial args | Adapting existing functions |

### Passing Arguments — Important Notes

```cpp
// BY VALUE (default) — thread gets a copy
void f(int x) { x = 99; }
int val = 1;
std::thread t(f, val);   // val remains 1 in main

// BY REFERENCE — must use std::ref
void g(int& x) { x = 99; }
std::thread t2(g, std::ref(val));   // val becomes 99 in main
t2.join();

// std::ref is necessary because thread constructor copies its arguments
// without std::ref, even reference parameters get copied
```

### Interview Questions

**Q: Why does `std::thread t(Worker())` not work as expected?**  
It's parsed as a function declaration returning `std::thread` and taking a `Worker(*)()` parameter. Use `std::thread t{Worker{}}` or `std::thread t((Worker()))`.

**Q: What happens to a captured reference if the thread outlives the scope?**  
Dangling reference → undefined behavior. Always ensure thread lifetime is shorter than captured variables, or capture by value, or use `shared_ptr`.

**Q: Why do you need `std::ref` to pass by reference?**  
`std::thread`'s constructor takes arguments by value (copies them). `std::ref` creates a `reference_wrapper` that the constructor copies, but which refers to the original.

---

## 3. Join and Detach with Joinable

### 3.1 The Problem

When you create a thread, the thread object needs to know what to do when it goes out of scope or when the program needs to end. C++ gives you two choices: **join** or **detach**.

If neither is called before the `std::thread` object is destroyed, **`std::terminate()` is called** — your program crashes.

### 3.2 join()

`join()` blocks the **calling thread** until the **joined thread** completes.

```cpp
void longTask() {
    // simulate work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Task complete\n";
}

int main() {
    std::thread t(longTask);
    
    std::cout << "Main doing other work...\n";
    
    t.join();   // Main BLOCKS here until longTask() finishes
    
    std::cout << "Main continues after join\n";
    return 0;
}
// Output order guaranteed:
// Main doing other work...
// Task complete
// Main continues after join
```

**Use `join()` when:**
- You need the result of the thread before continuing.
- You want to ensure cleanup before the program exits.

### 3.3 detach()

`detach()` lets the thread run independently. The thread object releases ownership — the thread becomes a **daemon thread** (runs in background, program doesn't wait for it).

```cpp
void backgroundLogger() {
    while (true) {
        // log something every second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Log entry\n";
    }
}

int main() {
    std::thread t(backgroundLogger);
    t.detach();   // Let it run independently, don't wait
    
    // Main continues immediately
    std::cout << "Main is free!\n";
    
    // ⚠️ When main() ends, ALL detached threads are killed immediately
    //    This can leave resources in inconsistent state
    return 0;
}
```

> ⚠️ **Danger of detach:** Once detached, you cannot `join()` the thread. If the thread accesses any variable from the launching scope and that scope ends, you get undefined behavior.

### 3.4 joinable()

`joinable()` returns `true` if the thread is associated with an execution context (i.e., it was started and not yet joined/detached).

```cpp
std::thread t(someFunc);

std::cout << t.joinable() << "\n";   // true — thread is running

t.join();

std::cout << t.joinable() << "\n";   // false — already joined
```

**Best practice — always check before joining:**
```cpp
if (t.joinable()) {
    t.join();
}
```

### 3.5 Exception Safety

What if an exception is thrown between thread creation and `join()`? The thread destructor calls `terminate()`.

```cpp
// BAD
std::thread t(task);
doSomethingThatMightThrow();   // Exception thrown here
t.join();                       // Never reached! terminate() called.

// GOOD — use RAII wrapper
class ThreadGuard {
    std::thread& t;
public:
    ThreadGuard(std::thread& t) : t(t) {}
    ~ThreadGuard() {
        if (t.joinable()) t.join();   // Always joins on scope exit
    }
};

std::thread t(task);
ThreadGuard guard(t);           // Destructor joins even if exception thrown
doSomethingThatMightThrow();    // Safe now
```

### 3.6 Thread ID and Sleep

```cpp
// Get thread ID
std::thread::id myId = std::this_thread::get_id();
std::cout << "Thread ID: " << myId << "\n";

// Pause a thread
std::this_thread::sleep_for(std::chrono::milliseconds(500));
std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

// Yield CPU to other threads
std::this_thread::yield();
```

### 3.7 Interview Questions

**Q: What happens if a `std::thread` object is destroyed without calling join or detach?**  
`std::terminate()` is called, crashing the program. This is by design — C++ forces you to explicitly decide the thread's fate.

**Q: Can you join a thread more than once?**  
No. The second `join()` throws `std::system_error`. Always check `joinable()` first.

**Q: When would you choose detach over join?**  
For long-running background tasks (logging, monitoring) that don't produce a result the main thread needs, and where you're confident they won't access scope-dependent resources after that scope ends.

**Q: Can you join a thread from a different thread?**  
Yes — any thread can call `join()` on a thread object, as long as the thread object is accessible. But the calling thread will block.

---

## 4. Mutex in C++ Threading

### 4.1 What is a Mutex?

**Mutex = Mutual Exclusion.** A mutex is a synchronization primitive that ensures only **one thread at a time** can execute a critical section of code.

Think of a mutex as a **single key** to a room. Before entering the room (critical section), a thread must pick up the key (lock). On exit, it puts the key back (unlock). If another thread wants to enter while the key is taken, it waits at the door.

### 4.2 The Problem Without Mutex

```cpp
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++;   // Read → Add → Write (not atomic, race condition!)
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join(); t2.join();
    std::cout << counter;   // Should be 200000, but isn't!
}
```

Why? `counter++` compiles to roughly:
```
MOV reg, [counter]    ; read counter into register
ADD reg, 1            ; increment register
MOV [counter], reg    ; write back
```
If T1 reads `counter=5`, T2 also reads `counter=5`, both write back `6` — but we expect `7`. This is the **lost update** problem.

### 4.3 std::mutex — Basic Usage

```cpp
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; i++) {
        mtx.lock();     // Acquire — blocks if another thread holds it
        counter++;      // CRITICAL SECTION — only one thread here at a time
        mtx.unlock();   // Release — other threads can now acquire
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join(); t2.join();
    std::cout << counter;   // Guaranteed: 200000
}
```

### 4.4 The Four Mutex Operations

```cpp
std::mutex mtx;

mtx.lock();     // Acquire. BLOCKS if held by another thread.
mtx.unlock();   // Release. Call only if you currently hold it.
mtx.try_lock(); // Non-blocking attempt. Returns true if acquired, false if not.
                // See Topic 5 for details.
```

### 4.5 Mutex Rules — Critical

```
1. A thread that calls lock() MUST eventually call unlock().
2. A thread must NOT call unlock() if it doesn't hold the mutex.
3. A thread must NOT call lock() if it already holds the mutex (use recursive_mutex for that).
4. Only ONE thread can hold the mutex at a time.
5. Undefined behavior if a mutex is destroyed while held.
```

### 4.6 Why Raw lock/unlock is Dangerous

```cpp
void riskyFunction() {
    mtx.lock();
    
    if (someCondition) {
        return;   // ⚠️ FORGOT TO UNLOCK! Mutex forever held — deadlock.
    }
    
    doWork();     // ⚠️ If this throws, unlock() is never reached!
    
    mtx.unlock();
}
```

**Solution:** Use RAII wrappers (`lock_guard` or `unique_lock`) — covered in Topics 9 and 10.

### 4.7 Mutex Overhead

Locking a mutex is NOT free. It involves:
- A system call or CPU atomic instruction.
- Potentially putting the thread to sleep (kernel involvement) if the mutex is contended.

**Minimize time spent inside critical sections.** Only protect the absolute minimum.

```cpp
// BAD — holding lock during expensive operation
mtx.lock();
result = expensiveComputation();  // Long operation inside lock!
sharedVar = result;
mtx.unlock();

// GOOD — compute outside, only lock for the write
result = expensiveComputation();  // No lock needed
mtx.lock();
sharedVar = result;               // Just the write
mtx.unlock();
```

### 4.8 Multiple Mutexes

When you need to protect multiple resources:

```cpp
std::mutex mtxA, mtxB;

// DANGEROUS — potential deadlock
// Thread 1: locks A then B
// Thread 2: locks B then A
// → Circular wait!

// SAFE — always lock in same order
void safeTransfer() {
    mtxA.lock();   // Always A first
    mtxB.lock();   // Then B
    // ... do work
    mtxB.unlock();
    mtxA.unlock();
}
```

See Topic 14 (`std::lock`) for the proper solution.

### 4.9 Interview Questions

**Q: What is a mutex and why do we need it?**  
A mutex ensures mutual exclusion — only one thread executes a critical section at a time, preventing race conditions on shared data.

**Q: What is the difference between a mutex and a semaphore?**  
A mutex is binary (locked/unlocked) and must be released by the same thread that locked it. A semaphore has a count and can be signaled by any thread. Mutexes are for mutual exclusion; semaphores are for signaling/resource counting.

**Q: What is a spurious wakeup?**  
Relevant with condition variables (Topic 11) — a thread wakes up from `wait()` without being notified. Always check condition in a loop, not an `if`.

**Q: Can two threads lock different mutexes simultaneously?**  
Yes — two mutexes are independent. Thread T1 can hold `mtxA` while T2 holds `mtxB` — no conflict. Conflict only occurs when both try to lock the **same** mutex.

---

## 5. Mutex try_lock Member Function

### 5.1 What is try_lock()?

`try_lock()` is a **non-blocking** version of `lock()`. Instead of waiting, it immediately returns:
- `true` — lock acquired successfully.
- `false` — lock was already held by another thread (you did NOT acquire it).

```cpp
std::mutex mtx;

if (mtx.try_lock()) {
    // We got the lock
    doWork();
    mtx.unlock();   // MUST unlock if try_lock returned true
} else {
    // Couldn't get the lock right now — do something else
    doAlternativeWork();
}
```

### 5.2 When to Use try_lock()

**Use case 1: Timeout/retry with fallback**
```cpp
void worker(std::mutex& mtx, int id) {
    int attempts = 0;
    while (true) {
        if (mtx.try_lock()) {
            std::cout << "Thread " << id << " acquired lock after " 
                      << attempts << " attempts\n";
            // do critical work
            mtx.unlock();
            break;
        } else {
            attempts++;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // Do non-critical work while waiting
        }
    }
}
```

**Use case 2: Avoiding deadlock (lock ordering)**
```cpp
std::mutex m1, m2;

void thread1() {
    m1.lock();
    if (m2.try_lock()) {
        // Got both — proceed
        doWork();
        m2.unlock();
    } else {
        // Couldn't get m2 — release m1 and retry later (avoids deadlock)
        m1.unlock();
        std::this_thread::yield();
    }
    m1.unlock();  // Only reached if try_lock succeeded
}
```

**Use case 3: Opportunistic work**
```cpp
// If we can get the lock now, update the cache. If not, skip — it's not critical.
if (cacheMutex.try_lock()) {
    updateCache();
    cacheMutex.unlock();
}
// Either way, continue
```

### 5.3 Critical Mistake

```cpp
// WRONG
mtx.try_lock();    // Result ignored! If it returned false, you don't have the lock
doWork();          // RACE CONDITION — might not be protected
mtx.unlock();      // UNDEFINED BEHAVIOR if you don't hold the lock

// CORRECT
if (mtx.try_lock()) {
    doWork();
    mtx.unlock();
}
```

### 5.4 try_lock vs lock

| Feature | `lock()` | `try_lock()` |
|---------|---------|-------------|
| Blocks? | Yes — waits indefinitely | No — returns immediately |
| Return value | void | bool (true = acquired) |
| Use when | You MUST have the lock | You CAN skip if busy |
| Deadlock risk | Higher | Lower (can back off) |

### 5.5 Interview Questions

**Q: If try_lock() returns false, do you need to call unlock()?**  
No! If it returns false, you don't hold the lock. Calling `unlock()` would be undefined behavior. Only call `unlock()` if `try_lock()` returned `true`.

**Q: Is try_lock() guaranteed to succeed if no other thread holds the lock?**  
No — it may spuriously fail even if the mutex is unlocked. Always handle the false case.

**Q: Give a scenario where try_lock() is better than lock().**  
A game's render loop: try to acquire the physics mutex to draw updated positions. If the physics thread has it, draw the last known positions instead of stalling the frame.

---

## 6. std::try_lock in C++11 Threading

### 6.1 std::try_lock vs mtx.try_lock()

There are two different try_lock things in C++:

| | `mtx.try_lock()` | `std::try_lock()` |
|--|-----------------|-------------------|
| Type | Member function of mutex | Free function in `<mutex>` |
| Arguments | None | Multiple Lockables |
| Returns | `bool` | `int` (-1 = success, 0-based index = failure) |
| Purpose | Try to lock ONE mutex | Try to lock MULTIPLE mutexes atomically |

### 6.2 std::try_lock — Signature

```cpp
template <class L1, class L2, class... Ln>
int std::try_lock(L1&, L2&, Ln&...);
```

**Returns:**
- `-1` — All mutexes successfully locked.
- `N` (0, 1, 2...) — Index of the first mutex that failed. All previously locked mutexes are automatically unlocked.

### 6.3 Full Example

```cpp
#include <mutex>
#include <thread>
#include <iostream>

std::mutex m1, m2, m3;

void attemptLockAll() {
    int result = std::try_lock(m1, m2, m3);
    
    if (result == -1) {
        std::cout << "Got all three locks!\n";
        // Do work with m1, m2, m3
        m1.unlock();
        m2.unlock();
        m3.unlock();
    } else {
        // result = index of first failure (0=m1, 1=m2, 2=m3)
        std::cout << "Failed at mutex index: " << result << "\n";
        // No need to unlock — std::try_lock undid all previous locks
    }
}
```

### 6.4 The Key Guarantee

If `std::try_lock(m1, m2, m3)` fails at `m2`:
- It **automatically unlocks `m1`** (which was locked first).
- `m2` and `m3` are NOT locked.
- You get a clean state — no partial locking mess.

This is the main advantage over manually calling `try_lock()` on each:

```cpp
// MANUAL — error-prone
if (m1.try_lock()) {
    if (m2.try_lock()) {
        if (m3.try_lock()) {
            // success
        } else {
            m1.unlock(); m2.unlock();  // Easy to forget!
        }
    } else {
        m1.unlock();  // Easy to forget!
    }
}

// std::try_lock — automatic cleanup
if (std::try_lock(m1, m2, m3) == -1) {
    // All locked, all automatically unlocked on failure
}
```

### 6.5 Practical Pattern — Deadlock-Free Locking with Retry

```cpp
void transferBetweenAccounts(Account& a, Account& b, double amount) {
    while (true) {
        int result = std::try_lock(a.mtx, b.mtx);
        if (result == -1) {
            // Got both locks
            a.balance -= amount;
            b.balance += amount;
            a.mtx.unlock();
            b.mtx.unlock();
            return;
        }
        // Couldn't get both — retry after yielding
        std::this_thread::yield();
    }
}
```

### 6.6 Interview Questions

**Q: What's the difference between `std::try_lock` and `std::lock`?**  
`std::try_lock` is non-blocking (returns immediately if any lock fails). `std::lock` blocks until all locks are acquired, using a deadlock-avoidance algorithm.

**Q: Why might you prefer `std::try_lock` over `std::lock` in a real-time system?**  
Real-time systems can't block indefinitely. `try_lock` lets you detect contention and take alternative action, maintaining responsiveness.

---

## 7. Timed Mutex in C++ Threading

### 7.1 What is a Timed Mutex?

A `std::timed_mutex` extends `std::mutex` with two additional operations:
- `try_lock_for(duration)` — Try to acquire for UP TO a given duration.
- `try_lock_until(time_point)` — Try to acquire UNTIL a specific clock time.

If the time expires without acquiring the lock, the function returns `false`.

### 7.2 Available Timed Mutex Types

```cpp
std::timed_mutex          // Basic timed mutex
std::recursive_timed_mutex  // Recursive + timed
```

### 7.3 try_lock_for — Example

```cpp
#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>

std::timed_mutex tmtx;

void worker(int id) {
    // Try to lock for up to 200 milliseconds
    if (tmtx.try_lock_for(std::chrono::milliseconds(200))) {
        std::cout << "Thread " << id << " acquired lock\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // hold it
        tmtx.unlock();
    } else {
        std::cout << "Thread " << id << " TIMEOUT — couldn't get lock\n";
    }
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join(); t2.join();
}
```

### 7.4 try_lock_until — Example

```cpp
void workerUntil(int id) {
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    
    if (tmtx.try_lock_until(deadline)) {
        // Got the lock before the deadline
        doWork();
        tmtx.unlock();
    } else {
        std::cout << "Deadline passed, skipping work\n";
    }
}
```

### 7.5 Difference Between the Two

| | `try_lock_for` | `try_lock_until` |
|--|---------------|-----------------|
| Parameter | Duration (relative) | Time point (absolute) |
| Clock | From now | From epoch |
| Use when | "Wait up to X ms" | "Wait until 3:00 PM" |

```cpp
// try_lock_for: relative to now
tmtx.try_lock_for(std::chrono::milliseconds(500));   // Wait up to 500ms

// try_lock_until: absolute time point
auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
tmtx.try_lock_until(t);   // Same effect here, but allows shared deadlines
```

### 7.6 Clock Types

```cpp
std::chrono::system_clock    // Wall clock (can be adjusted by NTP/admin)
std::chrono::steady_clock    // Monotonic — never goes backwards (preferred for timeouts)
std::chrono::high_resolution_clock  // Highest precision available
```

> For timeouts, always use `steady_clock`. `system_clock` can jump (daylight saving, NTP) and mess up your timeouts.

### 7.7 Practical Use Case — Connection Pool

```cpp
class ConnectionPool {
    std::timed_mutex poolMtx;
    std::vector<Connection> connections;

public:
    Connection* getConnection(int timeoutMs) {
        if (poolMtx.try_lock_for(std::chrono::milliseconds(timeoutMs))) {
            auto conn = connections.back();
            connections.pop_back();
            poolMtx.unlock();
            return &conn;
        }
        return nullptr;   // Timeout — no connection available
    }
};
```

### 7.8 Interview Questions

**Q: When would you use timed_mutex over regular mutex?**  
When you need to avoid indefinite blocking — e.g., real-time systems, network operations with SLA, UI threads that must remain responsive.

**Q: Which clock should you use for try_lock_for?**  
The implementation internally uses `steady_clock`. You specify a duration, not a clock. For `try_lock_until`, use `steady_clock::now()` to construct the time point to avoid issues with clock adjustments.

---

## 8. Recursive Mutex in C++ Threading

### 8.1 The Problem With Regular Mutex

A regular `std::mutex` has a strict rule: **a thread cannot lock a mutex it already holds**. If it tries, the behavior is undefined (usually deadlock).

```cpp
std::mutex mtx;

void inner() {
    mtx.lock();   // Thread already holds this! → Deadlock or undefined behavior
    // work
    mtx.unlock();
}

void outer() {
    mtx.lock();
    inner();      // ⚠️ Calls inner(), which tries to lock the same mutex again!
    mtx.unlock();
}
```

### 8.2 std::recursive_mutex — Solution

A `recursive_mutex` allows the **same thread** to lock it multiple times. It maintains a **lock count**. The mutex is only fully released when `unlock()` has been called the **same number of times** as `lock()`.

```cpp
#include <mutex>

std::recursive_mutex rmtx;

void inner() {
    rmtx.lock();     // Lock count: 2
    std::cout << "Inner work\n";
    rmtx.unlock();   // Lock count: 1 (NOT released yet!)
}

void outer() {
    rmtx.lock();     // Lock count: 1
    inner();
    rmtx.unlock();   // Lock count: 0 → FULLY RELEASED
}
```

### 8.3 Lock Count Tracking

```cpp
std::recursive_mutex rmtx;

rmtx.lock();    // count = 1
rmtx.lock();    // count = 2
rmtx.lock();    // count = 3

// Other threads CANNOT acquire rmtx until count reaches 0

rmtx.unlock();  // count = 2
rmtx.unlock();  // count = 1
rmtx.unlock();  // count = 0 → mutex released, other threads can acquire
```

### 8.4 Practical Example — Recursive Tree Traversal

```cpp
class ThreadSafeTree {
    std::recursive_mutex mtx;
    
    void processNode(Node* n) {
        std::lock_guard<std::recursive_mutex> lock(mtx);  // Lock each time
        
        // Process this node
        n->value++;
        
        // Recursive call — also locks mtx, but that's OK!
        for (auto child : n->children) {
            processNode(child);   // Recursive lock — fine with recursive_mutex
        }
    }

public:
    void process(Node* root) {
        processNode(root);
    }
};
```

### 8.5 When to Use recursive_mutex

```
Use recursive_mutex when:
  ✓ A function that holds a mutex needs to call another function that also locks the same mutex
  ✓ Recursive algorithms that need consistent locking throughout the call stack
  ✓ Refactoring legacy code where re-entrant locking happened by design

Do NOT use recursive_mutex when:
  ✗ You just want to simplify code (it hides design issues)
  ✗ Performance is critical (recursive_mutex is slower than regular mutex)
  ✗ You can refactor to avoid the re-entrant pattern
```

### 8.6 The Design Warning

> "Needing a `recursive_mutex` is often a sign of poor design. If possible, refactor to avoid the re-entrant pattern."

The better pattern is to split functions into public (locking) and private (non-locking) versions:

```cpp
// Better design — no recursive_mutex needed
class SafeClass {
    std::mutex mtx;
    
    void innerWork_nolock() {   // Private — does work, assumes lock is held
        data++;
    }
    
public:
    void outerMethod() {
        std::lock_guard<std::mutex> lock(mtx);
        innerWork_nolock();   // No locking — we already hold it
    }
    
    void directMethod() {
        std::lock_guard<std::mutex> lock(mtx);
        innerWork_nolock();
    }
};
```

### 8.7 Interview Questions

**Q: What happens if a thread calls lock() on a regular mutex it already holds?**  
Undefined behavior — typically results in a deadlock (the thread blocks waiting for itself).

**Q: What is the maximum recursion depth for recursive_mutex?**  
Implementation-defined (`std::numeric_limits<size_t>::max()` typically), but throwing `std::system_error` if exceeded.

**Q: Is recursive_mutex slower than mutex?**  
Yes — it needs to track the owning thread ID and lock count, requiring additional operations per lock/unlock.

---

## 9. Lock Guard in C++ Threading

### 9.1 The Problem — Forgetting to Unlock

```cpp
void badFunction() {
    mtx.lock();
    
    if (error) return;         // ⚠️ Lock never released!
    
    if (anotherError) throw;  // ⚠️ Exception skips unlock!
    
    doWork();
    mtx.unlock();   // Only reached in the happy path
}
```

Manual lock/unlock is fragile. Any early return or exception leaves the mutex permanently locked — **deadlock for all other threads**.

### 9.2 std::lock_guard — RAII Solution

`lock_guard` is a **scope-based RAII wrapper**. It:
- Acquires the mutex in its **constructor**.
- Releases the mutex in its **destructor** (which runs when it goes out of scope, including on exceptions).

```cpp
#include <mutex>

std::mutex mtx;

void safeFunction() {
    std::lock_guard<std::mutex> guard(mtx);  // Acquires lock HERE
    
    if (error) return;         // guard destructor runs → unlocks
    
    if (anotherError) throw;  // guard destructor runs → unlocks
    
    doWork();
    
}   // guard destructor runs here → unlocks
    // Mutex is ALWAYS released, no matter how we exit
```

### 9.3 RAII Concept

**Resource Acquisition Is Initialization:**
- Bind resource lifetime to object lifetime.
- Constructor acquires resource.
- Destructor releases resource.
- C++ guarantees destructors run on scope exit (even exceptions).

```cpp
// lock_guard is essentially:
template<class Mutex>
class lock_guard {
    Mutex& m;
public:
    lock_guard(Mutex& m) : m(m) { m.lock(); }    // Acquire
    ~lock_guard()               { m.unlock(); }   // Always release
    
    // Non-copyable, non-movable (you can't transfer ownership)
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
};
```

### 9.4 adopt_lock Tag — Lock Already Held

Sometimes the mutex is already locked (e.g., by `std::lock()`). You want RAII management without re-locking.

```cpp
std::mutex mtx;
mtx.lock();   // Already locked manually

// std::adopt_lock tells lock_guard: "I already have the lock, just manage it"
std::lock_guard<std::mutex> guard(mtx, std::adopt_lock);

// guard will unlock in destructor, but won't lock in constructor
```

### 9.5 Scope Tricks — Limiting Critical Section

```cpp
void function() {
    // Non-critical work
    prepareData();
    
    {   // Open new scope
        std::lock_guard<std::mutex> guard(mtx);
        sharedData = preparedData;    // Critical section — only these lines
    }   // Lock released here (smaller critical section = better parallelism)
    
    // More non-critical work
    postProcess();
}
```

### 9.6 lock_guard vs unique_lock Quick Preview

| Feature | `lock_guard` | `unique_lock` |
|---------|-------------|---------------|
| Overhead | Minimal | Slightly more |
| Lock on construction | Always | Optional |
| Manual unlock | ❌ No | ✅ Yes |
| Move semantics | ❌ No | ✅ Yes |
| Works with condition_variable | ❌ No | ✅ Yes |
| Use when | Simple scoped locking | Need flexibility |

**Rule of thumb:** Use `lock_guard` by default. Upgrade to `unique_lock` only when you need its extra features.

### 9.7 Interview Questions

**Q: What is RAII and how does lock_guard implement it?**  
RAII binds resource lifetime to object lifetime. `lock_guard` acquires the mutex in its constructor and releases it in its destructor, which C++ guarantees to run on scope exit — including during stack unwinding from exceptions.

**Q: Can you copy a lock_guard?**  
No — it's explicitly non-copyable. Copying would mean two guards trying to unlock the same mutex in their destructors — double-unlock is undefined behavior.

**Q: What is `std::adopt_lock` and when do you need it?**  
It's a tag that tells `lock_guard` not to acquire the mutex (it's already locked). Used after `std::lock()` or manual `lock()` calls to get RAII management of an already-acquired lock.

---

## 10. Unique Lock in C++ Threading

### 10.1 What is unique_lock?

`std::unique_lock` is a more flexible RAII mutex wrapper than `lock_guard`. It has all of `lock_guard`'s safety, plus:
- Can be **unlocked and re-locked** manually within scope.
- Can be **moved** (transferred to another scope).
- Required for use with **condition variables**.
- Supports **try_lock**, **timed locking**, and **deferred locking**.

### 10.2 Basic Usage

```cpp
#include <mutex>

std::mutex mtx;

void example() {
    std::unique_lock<std::mutex> lock(mtx);   // Acquires lock (same as lock_guard)
    doWork();
    // Destructor unlocks
}
```

### 10.3 Deferred Locking

```cpp
// Don't lock yet
std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

// Do some work that doesn't need the lock
prepareSomeData();

lock.lock();    // NOW acquire the lock
updateShared();
lock.unlock();  // Optional manual unlock before scope end

doMoreWork();   // Lock not held here

// Destructor: does nothing since lock was already released
```

### 10.4 try_lock with unique_lock

```cpp
std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);

if (lock.owns_lock()) {
    // Successfully acquired
    doWork();
} else {
    // Couldn't acquire — do fallback
    doFallback();
}
```

### 10.5 Timed Locking with unique_lock

```cpp
std::unique_lock<std::timed_mutex> lock(timedMtx, 
    std::chrono::milliseconds(100));  // Wait up to 100ms

if (lock.owns_lock()) {
    // Got it
} else {
    // Timeout
}
```

### 10.6 Moving unique_lock — Transfer of Ownership

```cpp
std::unique_lock<std::mutex> getLock() {
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // Do preparatory work while holding lock
    return lock;   // Transfer ownership — lock NOT released
}

void useLock() {
    auto lock = getLock();   // Receives the lock, still held
    doMoreWork();            // Protected by lock from getLock()
    // lock destructs here, releasing mutex
}
```

### 10.7 Initialization Tags Summary

```cpp
std::mutex mtx;

// Default: lock immediately
std::unique_lock<std::mutex> l1(mtx);

// defer_lock: don't lock yet, I'll call lock() manually
std::unique_lock<std::mutex> l2(mtx, std::defer_lock);

// try_to_lock: attempt lock, don't block, check owns_lock()
std::unique_lock<std::mutex> l3(mtx, std::try_to_lock);

// adopt_lock: mutex already locked, just manage it
mtx.lock();
std::unique_lock<std::mutex> l4(mtx, std::adopt_lock);
```

### 10.8 Member Functions

```cpp
lock.lock();           // Acquire the associated mutex
lock.unlock();         // Release (but don't destroy lock object)
lock.try_lock();       // Non-blocking acquire attempt
lock.owns_lock();      // Returns true if lock is held
lock.release();        // Releases mutex OWNERSHIP without unlocking (dangerous — you must unlock manually)
lock.mutex();          // Returns pointer to associated mutex
```

### 10.9 Interview Questions

**Q: When must you use unique_lock instead of lock_guard?**  
When using `condition_variable::wait()` (requires unique_lock), when you need to manually unlock/re-lock within a scope, or when you need to transfer lock ownership between functions.

**Q: What is the difference between `release()` and `unlock()`?**  
`unlock()` releases the mutex (unlocks it). `release()` gives up ownership of the mutex without unlocking it — you then own the mutex and must unlock it manually. `release()` is dangerous and rarely needed.

**Q: What is `defer_lock` used for?**  
Constructing a `unique_lock` that manages a mutex but doesn't acquire it yet. Common pattern: use `std::lock(l1, l2)` with two `defer_lock` unique_locks to acquire both atomically and avoid deadlock.

---

## 11. Condition Variable and Its Usage

### 11.1 The Problem — Busy Waiting

Imagine a producer-consumer scenario: Thread A produces data, Thread B consumes it. Without condition variables, B would need to busy-wait:

```cpp
while (data.empty()) {
    // Spin-check — burns CPU doing nothing useful
}
processData();
```

This wastes CPU. We need a way to say "wake me up when there's data."

### 11.2 What is a Condition Variable?

A **condition variable** lets a thread:
- **Wait** (sleep) until a condition becomes true.
- **Notify** other waiting threads when the condition changes.

It always works together with a `unique_lock` and a mutex.

### 11.3 Key Functions

```cpp
std::condition_variable cv;

cv.wait(lock);                    // Release lock, sleep, re-acquire lock on wake
cv.wait(lock, predicate);         // Sleep while predicate returns false (safe form)
cv.notify_one();                  // Wake ONE waiting thread
cv.notify_all();                  // Wake ALL waiting threads
cv.wait_for(lock, duration);      // Wait for up to duration
cv.wait_until(lock, time_point);  // Wait until time point
```

### 11.4 Producer-Consumer — Full Example

```cpp
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;
bool done = false;

void producer() {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced: " << i << "\n";
        }
        cv.notify_one();   // Wake one consumer
    }
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();   // Wake all consumers to check done flag
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait PREDICATE FORM — safe against spurious wakeups
        cv.wait(lock, [] { return !dataQueue.empty() || done; });
        
        if (dataQueue.empty() && done) break;   // No more data
        
        int val = dataQueue.front();
        dataQueue.pop();
        lock.unlock();   // Release before processing
        
        std::cout << "Consumer " << id << " got: " << val << "\n";
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);
    
    prod.join(); cons1.join(); cons2.join();
}
```

### 11.5 Spurious Wakeups — Critical Concept

A **spurious wakeup** is when a thread wakes from `wait()` without anyone calling `notify`. It happens due to OS/hardware reasons and is allowed by the standard.

```cpp
// WRONG — vulnerable to spurious wakeup
cv.wait(lock);
processData();   // Might run when queue is empty!

// CORRECT — predicate form handles spurious wakeup
cv.wait(lock, [] { return !queue.empty(); });
// Equivalent to:
while (queue.empty()) {
    cv.wait(lock);
}
processData();   // Guaranteed queue is not empty
```

**The predicate form of `wait()` is almost always what you want.**

### 11.6 What Happens Inside wait()

```
1. cv.wait(lock, pred) is called:
2. lock.unlock()          — releases mutex so other threads can proceed
3. Thread sleeps          — OS puts it to sleep
4. notify_one()/all()     — some other thread calls this
5. Thread wakes up
6. lock.lock()            — re-acquires mutex before returning
7. pred() checked         — if false (spurious), goes back to step 2
8. Returns                — pred() is true, mutex is held
```

### 11.7 notify_one vs notify_all

| | `notify_one()` | `notify_all()` |
|--|----------------|----------------|
| Wakes | One waiting thread | All waiting threads |
| Use when | One item produced, one consumer needed | State change affects all waiters |
| Efficiency | Better if one consumer per event | Needed for broadcast events |
| Risk | Wrong thread may wake (thundering herd) | All wake up, only one proceeds, rest re-wait |

### 11.8 Interview Questions

**Q: Why must condition_variable be used with unique_lock, not lock_guard?**  
`wait()` needs to unlock the mutex temporarily (to let other threads run). `lock_guard` has no `unlock()` method. `unique_lock` does.

**Q: What is a spurious wakeup and how do you handle it?**  
A thread waking from `wait()` without a `notify`. Always use the predicate form: `cv.wait(lock, predicate)`, which loops back to sleep if the condition isn't actually true.

**Q: What is the difference between notify_one and notify_all?**  
`notify_one` wakes one arbitrary waiting thread (efficient for producer-consumer). `notify_all` wakes every waiting thread (needed when a global state change is relevant to all, like shutdown).

**Q: Can you use condition_variable without a mutex?**  
No. The mutex protects the shared condition (e.g., the queue). Without it, you have a race between checking the condition and sleeping on the condition variable.

---

## 12. Deadlock in C++ Threading

### 12.1 What is a Deadlock?

A **deadlock** is a situation where two or more threads are each waiting for a resource held by the other — forming a circular wait that never resolves. All involved threads are permanently blocked.

```
Thread T1: holds Lock A, waiting for Lock B
Thread T2: holds Lock B, waiting for Lock A
→ Both wait forever. Neither can proceed. Deadlock.
```

### 12.2 The Four Conditions for Deadlock (Coffman Conditions)

All four must hold simultaneously for a deadlock to occur:

| Condition | Meaning |
|-----------|---------|
| **Mutual Exclusion** | Resources cannot be shared — only one thread at a time |
| **Hold and Wait** | A thread holds a resource while waiting for another |
| **No Preemption** | Resources cannot be forcibly taken from a thread |
| **Circular Wait** | T1 waits for T2, T2 waits for T3, T3 waits for T1 |

Break any one condition → deadlock cannot occur.

### 12.3 Simple Deadlock Example

```cpp
std::mutex m1, m2;

void thread1() {
    m1.lock();                                 // T1 holds m1
    std::this_thread::sleep_for(1ms);          // Let T2 run
    m2.lock();                                 // T1 waits for m2 ← STUCK
    // ...
    m2.unlock(); m1.unlock();
}

void thread2() {
    m2.lock();                                 // T2 holds m2
    std::this_thread::sleep_for(1ms);          // Let T1 run
    m1.lock();                                 // T2 waits for m1 ← STUCK
    // ...
    m1.unlock(); m2.unlock();
}
```

### 12.4 Preventing Deadlocks — Strategies

**Strategy 1: Lock Ordering (Most Common)**

Always acquire locks in the **same global order** across all threads.

```cpp
// BOTH threads lock m1 before m2 — deadlock impossible
void thread1() { m1.lock(); m2.lock(); /* work */ m2.unlock(); m1.unlock(); }
void thread2() { m1.lock(); m2.lock(); /* work */ m2.unlock(); m1.unlock(); }
```

**Strategy 2: Use std::lock() (Topic 14)**

Acquires multiple mutexes atomically, with built-in deadlock avoidance.

```cpp
std::lock(m1, m2);   // Acquires both, deadlock-free regardless of order
std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
```

**Strategy 3: Try-Lock with Backoff**

```cpp
void transfer(Account& from, Account& to) {
    while (true) {
        if (std::try_lock(from.mtx, to.mtx) == -1) {
            // Got both, do transfer
            from.balance -= amount;
            to.balance += amount;
            from.mtx.unlock(); to.mtx.unlock();
            return;
        }
        std::this_thread::yield();   // Give up CPU, retry
    }
}
```

**Strategy 4: Lock Timeout**

```cpp
std::timed_mutex m1, m2;

if (m1.try_lock_for(100ms)) {
    if (m2.try_lock_for(100ms)) {
        // Do work
        m2.unlock();
    }
    m1.unlock();
} 
// If timeout: retry or fail gracefully
```

### 12.5 Detecting Deadlocks

- **ThreadSanitizer (TSan):** `g++ -fsanitize=thread` — detects data races and deadlocks at runtime.
- **Valgrind (Helgrind):** `valgrind --tool=helgrind` — finds threading errors.
- **Logging:** Add timed waits and log if a lock takes longer than expected.

### 12.6 Livelock vs Starvation

| Concept | Definition |
|---------|-----------|
| **Deadlock** | All threads stuck, none progressing |
| **Livelock** | Threads keep responding to each other but no progress (like two people stepping aside for each other in a hallway) |
| **Starvation** | One thread can never acquire a lock because others always get it first |

```cpp
// Livelock example — both threads keep "politely" backing off
while (true) {
    if (try_lock(m1)) {
        if (try_lock(m2)) { /* work */ return; }
        m1.unlock();   // Back off
    }
    yield();
}
// If both threads do this with same timing, they keep yielding to each other
```

### 12.7 Interview Questions

**Q: What are the four necessary conditions for deadlock?**  
Mutual exclusion, hold-and-wait, no preemption, circular wait. Breaking any one prevents deadlock.

**Q: How do you prevent deadlock when you need to lock two mutexes?**  
Use consistent lock ordering (always lock m1 before m2), or use `std::lock()` which handles multiple mutexes with built-in deadlock avoidance.

**Q: What's the difference between deadlock and livelock?**  
In deadlock, threads are completely blocked (not running). In livelock, threads are actively running but cycling without making progress.

---

## 13. Thread / Process Synchronization in C++ Threading

### 13.1 What is Synchronization?

**Synchronization** is the coordination of threads to:
1. **Prevent race conditions** — ensure correct access to shared data.
2. **Establish ordering** — ensure thread A completes task X before thread B starts task Y.
3. **Communicate between threads** — signal events from one thread to another.

### 13.2 Synchronization Primitives Overview

```
MUTUAL EXCLUSION (prevent simultaneous access)
  ├── mutex           — Basic lock
  ├── timed_mutex     — Lock with timeout
  ├── recursive_mutex — Re-entrant lock
  └── shared_mutex    — Multiple readers / one writer (C++17)

SIGNALING (communicate between threads)
  ├── condition_variable  — Wait for condition
  └── semaphore           — C++20 counting semaphore

FUTURE/PROMISE (return values between threads)
  ├── promise/future  — One-time value passing
  └── async           — Async task execution

ATOMIC OPERATIONS (lock-free shared state)
  └── atomic<T>       — Hardware-level atomic read/write/modify
```

### 13.3 Memory Ordering — Why It Matters

Modern CPUs and compilers **reorder instructions** for performance. This can break threaded code even without race conditions.

```cpp
// Thread 1
data = 42;         // Write data first
ready = true;      // Signal ready

// Thread 2
while (!ready);    // Wait for signal
use(data);         // ⚠️ May see data = 0 if CPU reordered Thread 1's stores!
```

**Solution — Memory Barriers / std::atomic:**

```cpp
std::atomic<bool> ready{false};
std::atomic<int> data{0};

// Thread 1
data.store(42, std::memory_order_release);    // All prior stores visible before this
ready.store(true, std::memory_order_release);

// Thread 2
while (!ready.load(std::memory_order_acquire));  // Synchronizes with release store
use(data.load(std::memory_order_acquire));        // Guaranteed to see 42
```

### 13.4 std::atomic — Lock-Free Shared State

For simple types, `atomic<T>` provides thread-safe operations without a mutex.

```cpp
#include <atomic>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 100000; i++)
        counter++;        // Atomic: hardware-level read-modify-write
        // OR
        counter.fetch_add(1);  // Explicit atomic add
}

int main() {
    std::thread t1(increment), t2(increment);
    t1.join(); t2.join();
    std::cout << counter;   // Always 200000
}
```

**Common atomic operations:**
```cpp
counter.load()           // Atomic read
counter.store(val)       // Atomic write
counter.fetch_add(n)     // Atomic add, returns old value
counter.fetch_sub(n)     // Atomic subtract
counter.exchange(val)    // Atomic swap, returns old value
counter.compare_exchange_strong(expected, desired)  // CAS
```

### 13.5 Synchronization Patterns

**Pattern 1: Mutex + Shared Data**
```cpp
std::mutex mtx;
std::vector<int> results;

void worker(int val) {
    std::lock_guard<std::mutex> lock(mtx);
    results.push_back(val);
}
```

**Pattern 2: Condition Variable + Queue (Producer-Consumer)**
See Topic 11.

**Pattern 3: Barrier — Wait for All Threads**
```cpp
// C++20 std::barrier
#include <barrier>

std::barrier sync_point(4);   // 4 threads must reach it

void worker() {
    phase1Work();
    sync_point.arrive_and_wait();   // Wait for all 4 threads
    phase2Work();   // Only starts after ALL threads complete phase 1
}
```

**Pattern 4: Atomic Flag — Simple Signal**
```cpp
std::atomic<bool> stop{false};

void worker() {
    while (!stop.load()) {
        doWork();
    }
}

// From main:
stop.store(true);   // Signal all workers to stop
```

### 13.6 Process Synchronization vs Thread Synchronization

| | Thread Sync | Process Sync |
|--|-------------|-------------|
| Shared memory | Yes — same address space | No — separate processes |
| Primitives | mutex, condition_variable, atomic | Named mutexes, semaphores, shared memory |
| Speed | Fast | Slower (OS involvement) |
| Use case | Multi-threading within one program | Multiple independent programs |

### 13.7 Interview Questions

**Q: What is the difference between synchronization and mutual exclusion?**  
Mutual exclusion is one type of synchronization (preventing simultaneous access). Synchronization is broader — it also includes ordering (barrier, join) and communication (condition variable, future).

**Q: What is a memory barrier?**  
A hardware/compiler instruction that prevents reordering of memory operations across the barrier. `std::atomic` with appropriate memory orders provides this automatically.

**Q: When would you use atomic instead of a mutex?**  
For simple types (int, bool, pointer) where the operation is inherently atomic (increment, swap, CAS). Atomics are faster than mutexes (no kernel involvement for uncontended operations) but only work for individual simple operations.

---

## 14. std::lock in C++ Threading

### 14.1 What is std::lock?

`std::lock()` is a **free function** that acquires multiple mutexes **simultaneously**, using a deadlock-avoidance algorithm. It guarantees that all-or-nothing locking — either all mutexes are acquired, or none are (it backs off and retries if any fails).

```cpp
#include <mutex>

std::mutex m1, m2;

std::lock(m1, m2);   // Acquires BOTH — no deadlock, regardless of order
// Now m1 and m2 are both locked
m1.unlock();
m2.unlock();
```

### 14.2 The Problem It Solves

Without `std::lock`, two threads acquiring the same two mutexes in different orders can deadlock:

```cpp
// Thread 1: locks m1, then m2
// Thread 2: locks m2, then m1
// → Deadlock if both grab their first mutex simultaneously
```

`std::lock()` internally uses a try-and-backoff strategy:
1. Try to lock all mutexes.
2. If any fails, unlock all that were acquired, wait briefly, retry in different order.
3. Continue until all are acquired.

### 14.3 Correct Pattern — std::lock with lock_guard

```cpp
void safeTransfer(Account& from, Account& to, double amount) {
    // Acquire both locks atomically — deadlock-free
    std::lock(from.mtx, to.mtx);
    
    // Now manage them with RAII (adopt_lock = "I already locked these")
    std::lock_guard<std::mutex> lock1(from.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(to.mtx, std::adopt_lock);
    
    // Critical section
    from.balance -= amount;
    to.balance += amount;
    
    // Both locks auto-released by destructors
}
```

### 14.4 Modern C++17 — std::scoped_lock

C++17 introduced `std::scoped_lock` which combines `std::lock` + RAII in one step:

```cpp
// C++17 — cleaner syntax
void safeTransfer(Account& from, Account& to, double amount) {
    std::scoped_lock lock(from.mtx, to.mtx);   // Lock both, deadlock-free, RAII
    from.balance -= amount;
    to.balance += amount;
    // Both auto-released on scope exit
}
```

> **Prefer `std::scoped_lock` over `std::lock + lock_guard` in C++17 and later.**

### 14.5 std::lock vs std::try_lock

| | `std::lock` | `std::try_lock` |
|--|------------|----------------|
| Blocks? | Yes — until all acquired | No — returns immediately |
| Return type | void | int (-1 = success) |
| Algorithm | Deadlock-avoidance with retry | Single attempt |
| Use when | Must acquire all | Can skip if busy |

### 14.6 Edge Case — Same Mutex Twice

```cpp
std::mutex m;
std::lock(m, m);   // ⚠️ Undefined behavior — trying to lock same mutex twice
                   // Use recursive_mutex if same thread needs it twice
```

### 14.7 Interview Questions

**Q: How does std::lock prevent deadlock?**  
It uses a try-and-backoff algorithm: tries to lock all mutexes, and if any fails, it releases all previously acquired ones and retries. This breaks the "hold-and-wait" condition for deadlock.

**Q: What is scoped_lock and how does it differ from lock + lock_guard?**  
`scoped_lock` (C++17) is an RAII wrapper that accepts multiple mutexes, acquires all atomically (like `std::lock`), and releases all on destruction. It's a cleaner single-step replacement for the `std::lock` + `adopt_lock` + `lock_guard` pattern.

**Q: Can std::lock be used with different types of lockables?**  
Yes — any type that satisfies the Lockable concept (has `lock()`, `unlock()`, `try_lock()`). Works with `mutex`, `timed_mutex`, `recursive_mutex`, `shared_mutex`, and custom lockables.

---

## 15. std::promise and std::future

### 15.1 The Problem — Returning Values from Threads

`std::thread` has no built-in way to return a value. You'd typically use a shared variable + synchronization. But there's a cleaner way.

```cpp
// Clunky way with shared variable
int result = 0;
std::mutex mtx;

std::thread t([&]() {
    int val = expensiveComputation();
    std::lock_guard<std::mutex> lock(mtx);
    result = val;
});
t.join();
// Need mutex, shared variable, manual synchronization — messy
```

### 15.2 std::promise and std::future — The Clean Way

A `promise`-`future` pair is like a **one-time communication channel** between threads:
- **`promise<T>`** — the sender (writes the value).
- **`future<T>`** — the receiver (reads the value, waits if necessary).

```
Producer Thread          Consumer Thread
    promise<int>  ──────►  future<int>
    set_value(42)           get() → 42
```

### 15.3 Basic Example

```cpp
#include <future>
#include <thread>

void compute(std::promise<int>& prom) {
    int result = 42 * 2;           // Do work
    prom.set_value(result);        // Send result through promise
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();  // Get the future from promise
    
    std::thread t(compute, std::ref(prom));
    
    // Main thread can do other work here...
    
    int result = fut.get();   // BLOCKS until value is set, then returns it
    std::cout << "Result: " << result << "\n";  // 84
    
    t.join();
}
```

### 15.4 Exception Passing

Promises can also pass exceptions:

```cpp
void computeWithError(std::promise<int>& prom) {
    try {
        if (someError) throw std::runtime_error("Computation failed");
        prom.set_value(result);
    } catch (...) {
        prom.set_exception(std::current_exception());  // Pass exception to future
    }
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    
    std::thread t(computeWithError, std::ref(prom));
    t.join();
    
    try {
        int val = fut.get();   // Re-throws the exception here!
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
```

### 15.5 future States

```cpp
std::future<int> fut = prom.get_future();

fut.valid()         // true if future has a shared state (promise not broken)
fut.wait()          // Block until value is ready (don't retrieve)
fut.wait_for(dur)   // Wait up to duration → returns future_status
fut.wait_until(tp)  // Wait until time point → returns future_status
fut.get()           // Block until ready, retrieve value (can only call ONCE)
```

**future_status return values:**
```cpp
std::future_status::ready    // Value is available
std::future_status::timeout  // Time expired, not yet ready
std::future_status::deferred // Deferred execution (used with async + deferred policy)
```

### 15.6 shared_future — Multiple Readers

A `future` can only be read once. If multiple threads need the same result:

```cpp
std::promise<int> prom;
std::shared_future<int> sf = prom.get_future().share();  // Convert to shared_future

std::thread t1([sf]() { std::cout << sf.get() << "\n"; });  // Both can call get()
std::thread t2([sf]() { std::cout << sf.get() << "\n"; });

prom.set_value(99);
t1.join(); t2.join();
```

### 15.7 Promise-Future Lifecycle

```
1. Create promise<T>
2. Get future<T> via promise.get_future() — can only call ONCE
3. Give future to consumer, keep promise in producer
4. Producer calls set_value() or set_exception()
5. Consumer calls future.get() — blocks until step 4, then returns value
6. After get(), future is invalid (can't call get() again on regular future)
```

### 15.8 Interview Questions

**Q: What is the difference between future and promise?**  
`promise` is the write end (set_value/set_exception). `future` is the read end (get). They share an internal state. Think of it as a pipe: promise writes, future reads.

**Q: What happens if you call get() on a future twice?**  
Throws `std::future_error` (future already retrieved). Use `shared_future` if multiple threads need the same value.

**Q: Can you pass a future between threads?**  
Yes, via `std::move()` (futures are move-only, not copyable). Or use `shared_future` for copyable multi-consumer futures.

**Q: What happens if a promise is destroyed without setting a value?**  
The future will throw `std::future_error` with `broken_promise` error code when `get()` is called.

---

## 16. std::async — Create a Task

### 16.1 What is std::async?

`std::async` is the highest-level threading utility in C++11. It:
- **Runs a function asynchronously** (possibly in a new thread or deferred).
- **Returns a `std::future`** to get the result later.
- **Handles all threading boilerplate** — no manual thread management.

```cpp
#include <future>

// Run function asynchronously, get result via future
std::future<int> fut = std::async(std::launch::async, []() {
    return expensiveComputation();
});

// Do other work...

int result = fut.get();   // Get result (blocks if not ready)
```

### 16.2 Launch Policies

```cpp
std::launch::async     // Always create a new thread, run immediately
std::launch::deferred  // Don't run now — run lazily when .get() is called (same thread!)
std::launch::async | std::launch::deferred  // Implementation chooses (default if omitted)
```

```cpp
// Always async — definitely runs in a new thread
auto fut1 = std::async(std::launch::async, task);

// Deferred — runs in calling thread when get() is called
auto fut2 = std::async(std::launch::deferred, task);

// Default (may or may not create thread — avoid for predictability)
auto fut3 = std::async(task);
```

> ⚠️ **Default policy is implementation-defined.** In many implementations it's `deferred` when the system is under load. Use `std::launch::async` explicitly for guaranteed async execution.

### 16.3 Full Example — Parallel Computation

```cpp
#include <future>
#include <vector>
#include <numeric>

long long sumRange(int start, int end) {
    long long sum = 0;
    for (int i = start; i <= end; i++) sum += i;
    return sum;
}

int main() {
    // Split work across 4 async tasks
    auto f1 = std::async(std::launch::async, sumRange, 1, 25000000);
    auto f2 = std::async(std::launch::async, sumRange, 25000001, 50000000);
    auto f3 = std::async(std::launch::async, sumRange, 50000001, 75000000);
    auto f4 = std::async(std::launch::async, sumRange, 75000001, 100000000);
    
    // All four run in parallel
    long long total = f1.get() + f2.get() + f3.get() + f4.get();
    
    std::cout << "Sum 1 to 100M: " << total << "\n";
}
```

### 16.4 Exception Handling

```cpp
auto fut = std::async(std::launch::async, []() -> int {
    throw std::runtime_error("Task failed!");
    return 0;
});

try {
    int val = fut.get();   // Re-throws the exception
} catch (const std::exception& e) {
    std::cout << "Caught: " << e.what() << "\n";
}
```

### 16.5 Important: Destruction of Future from async

When a `std::future` returned by `std::async` is **destroyed** (not moved or returned), it **waits** for the task to complete. This is different from regular futures.

```cpp
// ⚠️ This BLOCKS! The temporary future immediately destructs, waiting for task
std::async(std::launch::async, longRunningTask);  // Blocks here until task finishes!

// ✅ Store the future to avoid blocking
auto fut = std::async(std::launch::async, longRunningTask);
// Program continues, can do other work
fut.get();  // Wait explicitly when needed
```

### 16.6 async vs thread — When to Use Each

| | `std::thread` | `std::async` |
|--|--------------|-------------|
| Return value | None (use promise/shared var) | Via future.get() |
| Exception propagation | Must handle manually | Automatically via get() |
| Thread management | Manual (join/detach) | Automatic |
| Control over scheduling | High | Low |
| Overhead | Lower for many tasks | Slightly higher |
| Use when | Low-level control needed | Simple task with return value |

```
Rule of thumb:
  → Want a result from concurrent work?  → std::async
  → Complex thread management?           → std::thread + promise/future
  → Fire-and-forget background task?     → std::thread + detach
```

### 16.7 Parallel Algorithms — C++17 Alternative

For common operations on containers, C++17 adds execution policies:

```cpp
#include <algorithm>
#include <execution>

std::vector<int> v(1000000);

// Parallel sort — no manual threading needed
std::sort(std::execution::par, v.begin(), v.end());

// Parallel transform
std::transform(std::execution::par_unseq, v.begin(), v.end(), v.begin(),
               [](int x) { return x * 2; });
```

### 16.8 Interview Questions

**Q: What is the default launch policy of std::async?**  
`std::launch::async | std::launch::deferred` — implementation-defined. The system may run it in a new thread or defer to the calling thread. Use `std::launch::async` explicitly for guaranteed concurrent execution.

**Q: What happens if you discard the future returned by std::async?**  
The destructor of the returned future blocks until the async task completes. This is unique to `async`-created futures. So `std::async(std::launch::async, task)` (without storing the future) is a blocking call.

**Q: How does async handle exceptions compared to std::thread?**  
With `std::thread`, uncaught exceptions call `std::terminate`. With `async`, exceptions are captured and stored in the future's shared state — rethrown when `future::get()` is called, giving you clean exception propagation.

**Q: When would you NOT use std::async?**  
When you need fine-grained control over thread count, affinity, or priority; when you're managing a thread pool; or in latency-critical systems where thread creation overhead is unacceptable.

---

## Final Quick-Revision Cheat Sheet

```
═══════════════════════════════════════════════════════════════
                  C++ THREADING CHEAT SHEET
═══════════════════════════════════════════════════════════════

THREAD CREATION
  std::thread t(func, args...);    // Start thread
  t.join();                        // Wait for thread
  t.detach();                      // Run independently
  t.joinable();                    // Check if can join

MUTEX FAMILY
  std::mutex              → Basic lock/unlock
  std::timed_mutex        → + try_lock_for, try_lock_until
  std::recursive_mutex    → Same thread can lock multiple times
  std::shared_mutex       → Multiple readers OR one writer (C++17)

MUTEX OPERATIONS
  mtx.lock()              → Block until acquired
  mtx.unlock()            → Release
  mtx.try_lock()          → Non-blocking attempt → bool

RAII WRAPPERS
  lock_guard<M> lg(m)              → Simple scoped lock
  unique_lock<M> ul(m)             → Flexible (unlock/relock, move)
  unique_lock<M> ul(m, defer_lock) → Don't lock yet
  unique_lock<M> ul(m, try_to_lock)→ Try, check owns_lock()
  scoped_lock<M1,M2> sl(m1,m2)     → Multi-mutex RAII (C++17)

MULTI-MUTEX FUNCTIONS
  std::lock(m1, m2)       → Acquire all, deadlock-free, returns void
  std::try_lock(m1, m2)   → Try all, -1=success, N=first failure index

CONDITION VARIABLE
  cv.wait(ul, pred)       → Sleep until pred() true (safe form)
  cv.notify_one()         → Wake one waiter
  cv.notify_all()         → Wake all waiters
  Always use predicate form to handle spurious wakeups!

FUTURE/PROMISE/ASYNC
  promise<T> p; future<T> f = p.get_future();
  p.set_value(val)        → Set result
  p.set_exception(eptr)   → Set exception
  f.get()                 → Block and retrieve (once only)
  f.wait_for(dur)         → Timed wait → future_status
  shared_future<T>        → Multiple get() calls allowed

  std::async(launch::async, func, args)  → Run async, returns future

ATOMIC
  atomic<int> a{0};
  a.fetch_add(1)          → Atomic increment
  a.load()                → Atomic read
  a.store(val)            → Atomic write
  a.compare_exchange_strong(expected, desired)  → CAS

DEADLOCK PREVENTION
  1. Always lock in same order
  2. Use std::lock() / scoped_lock for multiple mutexes
  3. Use try_lock with timeout and backoff
  4. Never hold a lock while acquiring another (or be consistent)

COMMON MISTAKES
  ✗ Forgetting to unlock        → Use lock_guard/unique_lock
  ✗ Locking same mutex twice    → Use recursive_mutex
  ✗ Using if instead of while   → Use cv.wait(lock, predicate)
  ✗ Ignoring try_lock return    → Always check the bool
  ✗ Discarding async future     → Blocks until task completes!
  ✗ Capturing by ref in thread  → Dangling reference if scope ends

COMPILE:  g++ -std=c++17 -pthread file.cpp -o out
DEBUG:    g++ -std=c++17 -pthread -fsanitize=thread file.cpp -o out
═══════════════════════════════════════════════════════════════
```

---

*This guide covers all 16 topics in depth. Study them in order — each topic builds on the previous. The most exam/interview-critical topics are: Mutex (4), lock_guard/unique_lock (9-10), Condition Variable (11), Deadlock (12), and async/future (15-16).*
