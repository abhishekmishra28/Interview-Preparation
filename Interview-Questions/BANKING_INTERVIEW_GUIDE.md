# Comprehensive Interview Preparation Guide: C++ Banking System

This guide provides an exhaustive list of potential interview questions and answers based on your C++ Banking System project. It is specifically tailored for high-performance C++ backend roles, such as the **AlphaGrep Software Development Intern** position. 

Study these questions thoroughly. They cover both the high-level architecture and the low-level C++ mechanics used in your project.

---

## Part 1: Project Overview & System Design

### 1. "Tell me about this C++ Banking System project. What was the goal?"
**Answer:** "I built a high-performance C++ backend simulating a real-world banking engine. I started by designing a clean, OOP-based domain model with polymorphism for different account types. Then, I integrated an SQLite persistence layer using the Repository pattern to ensure the domain remained untouched (Open/Closed Principle).
To achieve high throughput, I implemented a custom thread pool and a thread-safe task queue to process transactions concurrently. I used fine-grained locking (`std::shared_mutex`) on individual accounts and `std::scoped_lock` to prevent deadlocks during multi-account transfers. Finally, I exposed the engine over a cross-platform TCP socket, wrote a synthetic benchmarking suite to measure p50/p99 latencies, and verified thread safety using GoogleTest and ThreadSanitizer."

### 2. "Walk me through the lifecycle of a `TRANSFER` request in your system."
**Answer:** 
1. **Network Layer:** The TCP server's `ClientHandler` thread receives the raw bytes (`TRANSFER SAV-1001 SAV-1002 500\n`). It tokenizes the string.
2. **Concurrency Layer:** The handler submits a `TransactionTask` to the `ConcurrentTransactionEngine`, which pushes it onto the thread-safe `TransactionQueue`.
3. **Execution Layer:** A worker thread from the `ThreadPool` pops the task and invokes `TransactionService::transfer()`.
4. **Domain Layer:** The `TransactionService` looks up both `Account` objects and calls `from.transfer(amount, to)`.
5. **Synchronization Layer:** The `transfer()` method uses `std::scoped_lock` to atomically lock both accounts' mutexes, preventing deadlocks. It then mutates their balances.
6. **Pipeline:** The `TransactionService` passes the transaction record to the `FraudDetectionService` (which holds its own mutex), triggers the `NotificationService`, and logs to `PersistentAuditLogs` (writing to SQLite).
7. **Response:** A future is resolved or the client handler writes back the success response over the socket.

### 3. "Why did you choose a layered architecture?"
**Answer:** "Layered architecture enforces the Separation of Concerns. By splitting the codebase into models, services, infrastructure, database, and network, I ensured that a change in one layer (like adding a TCP server or swapping out SQLite for PostgreSQL) wouldn't break the core business logic. It makes the system testable, maintainable, and scalable."

---

## Part 2: Concurrency, Multithreading, & Synchronization

### 4. "How did you ensure thread safety in the `Account` class?"
**Answer:** "I added a `mutable std::shared_mutex` to the base `Account` class. This allows multiple threads to read the balance concurrently using `std::shared_lock` (Reader lock). However, mutations like `deposit` and `withdraw` acquire a `std::unique_lock` (Writer lock), ensuring exclusive access. I made the mutex `mutable` so that `const` getters (like `getBalance()`) could still lock it."

### 5. "What is the classic 'Transfer Deadlock' problem, and how did you solve it?"
**Answer:** "A deadlock occurs if Thread A transfers from Account 1 to Account 2 (locking 1, then waiting for 2), while Thread B transfers from Account 2 to Account 1 (locking 2, then waiting for 1). 
I solved this by using C++17's `std::scoped_lock(mtx1, mtx2)` in the `transfer()` method. `std::scoped_lock` implements a deadlock-avoidance algorithm (typically locking mutexes in memory-address order or using a try-and-back-off strategy). This ensures both locks are acquired atomically without deadlocking, regardless of the order they are passed in."

### 6. "Why did you build a custom Thread Pool? Why not use `std::async` or spawn a new thread per transaction?"
**Answer:** "Spawning a thread per transaction is extremely expensive due to OS overhead and context switching. `std::async` doesn't guarantee a thread pool (it might spawn a new thread or run synchronously). 
By building a custom `ThreadPool`, I pre-allocated a fixed number of worker threads (e.g., matching the CPU core count). These workers sleep efficiently on a `std::condition_variable`. When a transaction is queued, a worker wakes up, processes it, and goes back to sleep. This bounds the number of threads and maximizes CPU utilization."

### 7. "Explain the mechanics of your `TransactionQueue`."
**Answer:** "It is a thread-safe wrapper around `std::queue`. 
- **Push:** Acquires a `std::lock_guard`, pushes the task, and calls `cv.notify_one()` to wake up exactly one sleeping worker thread.
- **Pop:** Acquires a `std::unique_lock` and calls `cv.wait()`. The `wait` releases the lock and puts the thread to sleep until `notify` is called. Once awakened, it re-acquires the lock, checks if the queue is empty (to handle spurious wakeups), pops the task, and returns it."

### 8. "How did you handle thread safety in the `FraudDetectionService`?"
**Answer:** "The `FraudDetectionService` maintains a `std::vector<TransactionRecord>` to track historical transactions for rapid-fire heuristics. Since vectors are not thread-safe, multiple threads appending to it would cause a data race (and potentially crash during reallocation). I added a `std::mutex` and locked it inside `analyse()` using `std::lock_guard` to serialize access to the history."

### 9. "What happens if a thread throws an exception inside your thread pool?"
**Answer:** "Inside the worker loop, the task execution is wrapped in a `try/catch(...)` block. If an exception is thrown, it is caught and logged, but it doesn't crash the worker thread itself. Furthermore, the `submit()` method wraps tasks in a `std::promise`, so any caught exceptions are passed to `promise->set_exception()`, allowing the caller to catch it when they call `.get()` on the returned `std::future`."

---

## Part 3: Object-Oriented Programming (OOP) & C++ Mechanics

### 10. "How did you use Polymorphism in this project?"
**Answer:** "The base `Account` class defines pure virtual functions: `virtual void deposit(double) = 0;`. `SavingsAccount` and `CurrentAccount` override these. The `TransactionService` accepts a generic `Account&`. At runtime, when `txnService.deposit()` is called, C++ uses the vtable to dynamically dispatch the call to the correct overridden method, allowing `SavingsAccount` to just add money, while `CurrentAccount` checks against an overdraft limit."

### 11. "How did you integrate SQLite without rewriting the domain models?"
**Answer:** "I strictly adhered to the **Open/Closed Principle**. Instead of adding SQL logic to the `Account` class, I created separate Repository classes (e.g., `AccountRepo`). To handle audit logs, I used inheritance: I created `PersistentAuditLogs` which inherits from `AuditLogs`. It overrides the `log()` method to write to the DB, and then calls `AuditLogs::log()` to maintain in-memory state. Because of the **Liskov Substitution Principle**, I could pass `PersistentAuditLogs` into the existing services without changing their code."

### 12. "What's the difference between `override` and `virtual`? Did you use them?"
**Answer:** "`virtual` in the base class tells the compiler to use dynamic binding. `override` in the derived class explicitly tells the compiler that I intend to override a base class virtual function. It prevents subtle bugs, like typos in method signatures, by throwing a compile-time error if no matching base method exists. I used `override` on all subclass methods."

### 13. "Why use `std::shared_ptr` for storing Accounts?"
**Answer:** "The `AccountService` manages the lifetime of `Account` objects. By storing them as `std::shared_ptr<Account>`, multiple components (like the Transaction Engine or a thread doing periodic interest application) can hold references to an account safely. It guarantees that an account won't be deleted while a transaction is actively processing it."

---

## Part 4: Networking & Sockets

### 14. "Walk me through how your TCP server is implemented."
**Answer:** "I used raw socket programming (Winsock on Windows, POSIX on Linux). 
1. **socket():** Create the listening socket.
2. **bind():** Bind it to a specific port (e.g., 9090).
3. **listen():** Mark the socket as a listening socket.
4. **accept():** Sit in a loop. When a client connects, `accept()` returns a new socket descriptor for that specific connection.
5. I then spawn a `ClientHandler` thread, passing it the new socket so the main thread can go back to `accept()`ing new clients."

### 15. "Why did you use TCP instead of UDP?"
**Answer:** "Banking requires absolute reliability and strict ordering. If a `WITHDRAW` packet drops over UDP, the user loses money or the system becomes inconsistent. TCP provides sequence numbers, acknowledgments, and retransmissions to guarantee that the data arrives intact and in order."

### 16. "What is TCP Backlog, and what did you set it to?"
**Answer:** "The backlog parameter in `listen()` defines the maximum length to which the queue of pending connections for the socket may grow. I set it to 16. If a connection request arrives when the queue is full, the client may receive an error (like `ECONNREFUSED`)."

---

## Part 5: Performance, Benchmarking, & Tooling

### 17. "How did you benchmark the system? What is p99 latency?"
**Answer:** "I built a `BenchmarkRunner` that generates a synthetic, randomized workload of (e.g., 10,000) transactions. 
I recorded the start and end times of each transaction using `std::chrono::high_resolution_clock`. 
Instead of just looking at the average latency, I sorted the latencies and extracted the 50th, 95th, and 99th percentiles (p50, p95, p99). 
**p99 latency** means that 99% of transactions completed faster than this time. In trading and banking, tail latency (p99) is critical because outliers indicate lock contention or scheduling issues."

### 18. "What were your benchmark results, and how well did the Thread Pool scale?"
**Answer:** "Running single-threaded, the system hit roughly ~300k TPS. When running multi-threaded with 8 workers, it scaled up to over ~600k TPS. It's not a perfect 8x scale because of lock contention on the accounts and shared resources (like the FraudDetection mutex and the Audit logs). However, the p99 latency stayed under 35 microseconds, proving the thread pool was efficient."

### 19. "How did you prove your system was thread-safe?"
**Answer:** "Two ways. First, I wrote **GoogleTest stress tests**. For example, I spawned 8 threads that all tried to withdraw from the same account 500 times concurrently, then I verified that the final balance never fell below zero and the math added up perfectly.
Second, I used **ThreadSanitizer** (`-fsanitize=thread` in CMake). I ran my concurrent tests through TSAN, which instruments memory accesses to mathematically prove there are no data races or deadlocks at runtime."

### 20. "Why did you use CMake?"
**Answer:** "CMake is the industry standard for C++ build systems. It allowed me to write cross-platform build scripts. With CMake, I could easily separate my project into 5 targets: the base app, the database app, the server, the benchmark, and the unit tests. It also handled fetching GoogleTest automatically via `FetchContent`."

---

## Part 6: AlphaGrep Specific / High-Frequency Trading (HFT) Concepts

*(If interviewing at AlphaGrep or a similar HFT firm, expect these rapid-fire follow-ups)*

### 21. "In an HFT environment, `std::mutex` is often considered too slow. How would you optimize the locking in this project?"
**Answer:** "If absolute microsecond performance was required, I would replace `std::mutex` with **Spinlocks** using `std::atomic_flag`. Since account transactions (simple math operations) are extremely fast, a spinlock avoids the heavy OS context-switch overhead of a sleeping mutex. I would also consider lock-free data structures for the `TransactionQueue`, using something like a ring buffer (e.g., LMAX Disruptor pattern) with `std::atomic` pointers."

### 22. "How would you eliminate dynamic dispatch overhead in C++?"
**Answer:** "Currently, the system uses virtual functions (`virtual void deposit()`). This requires an indirect lookup through a vtable, which can cause CPU pipeline stalls and cache misses. To optimize this, I could use **Curiously Recurring Template Pattern (CRTP)** or `std::variant` combined with `std::visit` to achieve static polymorphism, resolving the method calls at compile-time instead of runtime."

### 23. "Your `TransactionQueue` allocates memory dynamically. How is that bad for HFT?"
**Answer:** "Dynamic memory allocation (`new`/`delete` or `push_back` triggering vector resizes) requires taking locks inside the OS memory allocator, which is highly unpredictable. In HFT, we use **Memory Pools** or pre-allocated fixed-size ring buffers, ensuring zero dynamic allocations happen on the critical path."

---

## Part 7: Behavioral / Problem Solving

### 24. "What was the hardest bug you faced during this project?"
**Answer:** *(Adapt as needed)* "The hardest part was debugging recursive locking. Initially, when I built the `transfer` method, I locked the accounts in the `transfer` function, and then called `deposit` and `withdraw`. However, `deposit` and `withdraw` *also* attempted to lock the same mutexes. Since `std::mutex` is not re-entrant (unlike `std::recursive_mutex`), this caused an immediate self-deadlock. 
I solved it by refactoring. I created internal, unprotected helper methods (`depositUnlocked`, `withdrawUnlocked`) that the public methods call *after* acquiring the lock. The `transfer` method acquires both locks using `std::scoped_lock`, then safely calls the unlocked helpers."

### 25. "If you had 2 more weeks to work on this, what would you add?"
**Answer:** 
1. **Asynchronous Networking:** I'd replace the thread-per-client model in the TCP server with an event-driven architecture using `epoll` (Linux) or Boost.Asio, allowing it to handle 10,000+ concurrent connections effortlessly.
2. **Lock-Free Queues:** I'd upgrade the `TransactionQueue` to a lock-free ring buffer to push TPS into the millions.
3. **Database Connection Pooling:** Currently, the database is a singleton. I would add a connection pool so multiple worker threads could persist to SQLite simultaneously without bottle-necking on a single connection.
