# 🗄️ 30 Most Important DBMS Interview Questions

> **Target Audience:** Freshers to Experienced Developers  
> **Topics Covered:** Fundamentals, SQL, Normalization, Transactions, Indexing, Concurrency, NoSQL & More  
> **Interview Level:** SDE / Database Engineer / Backend Developer

---

## Table of Contents

| # | Question |
|---|----------|
| 1 | [What is a DBMS and why is it used?](#q1) |
| 2 | [What is the difference between DBMS and RDBMS?](#q2) |
| 3 | [What are the different types of keys in a database?](#q3) |
| 4 | [What are the different types of SQL commands?](#q4) |
| 5 | [What are Joins and their types?](#q5) |
| 6 | [What is Normalization and its Normal Forms?](#q6) |
| 7 | [What is Denormalization?](#q7) |
| 8 | [What are ACID Properties?](#q8) |
| 9 | [What is a Transaction?](#q9) |
| 10 | [What are Transaction Isolation Levels?](#q10) |
| 11 | [What are Concurrency Problems?](#q11) |
| 12 | [What is Locking? Types of Locks?](#q12) |
| 13 | [What is Deadlock and how is it handled?](#q13) |
| 14 | [What is an Index? Types of Indexes?](#q14) |
| 15 | [What is a B-Tree and B+ Tree Index?](#q15) |
| 16 | [What is the difference between Clustered and Non-Clustered Index?](#q16) |
| 17 | [What is a View?](#q17) |
| 18 | [What is a Stored Procedure vs Function?](#q18) |
| 19 | [What is a Trigger?](#q19) |
| 20 | [What is the Entity-Relationship (ER) Model?](#q20) |
| 21 | [What is Relational Algebra?](#q21) |
| 22 | [What are Aggregate Functions and GROUP BY / HAVING?](#q22) |
| 23 | [What is a Subquery vs JOIN?](#q23) |
| 24 | [What is a Window Function?](#q24) |
| 25 | [What is Query Optimization and EXPLAIN?](#q25) |
| 26 | [What is Sharding and Partitioning?](#q26) |
| 27 | [What is Replication?](#q27) |
| 28 | [What is the CAP Theorem?](#q28) |
| 29 | [What is NoSQL? Types and when to use?](#q29) |
| 30 | [SQL vs NoSQL — When to use which?](#q30) |

---

<a name="q1"></a>
## Q1. What is a DBMS and why is it used?

**Answer:**

A **DBMS (Database Management System)** is software that enables users to **define, create, maintain, and control access** to a database. It acts as an interface between the application and the physical data stored on disk.

### Without DBMS — File System Problems
```
Application A → file1.txt  (data redundancy)
Application B → file2.txt  (same data duplicated)
Application C → file3.txt  (inconsistency if one file updated)

Problems:
  ✗ Data redundancy & inconsistency
  ✗ No concurrent access control
  ✗ No security / access control
  ✗ No crash recovery
  ✗ No query language — manual parsing
```

### With DBMS
```
Application A ─┐
Application B ─┤──► [DBMS] ──► Centralized Data Store
Application C ─┘
                ↑
         Single source of truth ✅
```

### Core Functions of a DBMS

| Function | Description |
|----------|-------------|
| **Data Definition** | Define schema, tables, constraints (DDL) |
| **Data Manipulation** | Insert, update, delete, query (DML) |
| **Data Security** | Role-based access control |
| **Concurrency Control** | Multiple users accessing data simultaneously |
| **Recovery** | Restore data after crash (WAL, checkpoints) |
| **Integrity** | Enforce constraints (PK, FK, NOT NULL) |

### Popular DBMS Products

```
Relational:  MySQL, PostgreSQL, Oracle, SQL Server, SQLite
NoSQL:       MongoDB, Cassandra, Redis, DynamoDB, Neo4j
NewSQL:      CockroachDB, Google Spanner, TiDB
```

---

<a name="q2"></a>
## Q2. What is the difference between DBMS and RDBMS?

**Answer:**

| Feature | DBMS | RDBMS |
|---------|------|-------|
| Data Storage | Files, hierarchical, network models | Tables (relations) with rows and columns |
| Relationships | Not enforced | Enforced via foreign keys |
| Normalization | Not supported | Supported |
| ACID | Not always | Fully supported |
| Query Language | No standard | SQL (standardized) |
| Integrity Constraints | Limited | PK, FK, UNIQUE, CHECK, NOT NULL |
| Examples | XML DB, IMS, dBASE | MySQL, PostgreSQL, Oracle, SQL Server |

### Relational Model — Core Concepts

```
TABLE (Relation):
┌──────────┬───────────────┬──────────┬──────────┐
│ emp_id   │ name          │ dept_id  │ salary   │
│ (PK)     │               │ (FK)     │          │
├──────────┼───────────────┼──────────┼──────────┤
│ 1        │ Alice         │ 10       │ 80000    │
│ 2        │ Bob           │ 20       │ 90000    │
│ 3        │ Carol         │ 10       │ 75000    │
└──────────┴───────────────┴──────────┴──────────┘
     ↑              ↑
  Attribute       Tuple (Row)
```

### Three-Schema Architecture (ANSI/SPARC)

```
External Level    → User views (what different apps/users see)
     ↓
Conceptual Level  → Logical schema (tables, relationships, constraints)
     ↓
Internal Level    → Physical storage (files, indexes, blocks)
```
This separation enables **data independence** — changing storage doesn't affect the logical schema.

---

<a name="q3"></a>
## Q3. What are the different types of keys in a database?

**Answer:**

Keys enforce uniqueness, establish relationships, and help identify records efficiently.

```
┌─────────────────────────────────────────────────────────────┐
│                      Types of Keys                          │
├──────────────────┬──────────────────────────────────────────┤
│ Super Key        │ Any set of attributes that uniquely      │
│                  │ identifies a row (superset of CK)        │
├──────────────────┼──────────────────────────────────────────┤
│ Candidate Key    │ Minimal super key — no redundant attrs   │
├──────────────────┼──────────────────────────────────────────┤
│ Primary Key      │ Chosen candidate key, NOT NULL + UNIQUE  │
├──────────────────┼──────────────────────────────────────────┤
│ Alternate Key    │ Candidate key NOT chosen as primary key  │
├──────────────────┼──────────────────────────────────────────┤
│ Foreign Key      │ Attribute referencing another table's PK │
├──────────────────┼──────────────────────────────────────────┤
│ Composite Key    │ PK made of two or more attributes        │
├──────────────────┼──────────────────────────────────────────┤
│ Surrogate Key    │ System-generated artificial key (auto-id)│
├──────────────────┼──────────────────────────────────────────┤
│ Unique Key       │ Like PK but allows one NULL value        │
└──────────────────┴──────────────────────────────────────────┘
```

### Example

```sql
CREATE TABLE orders (
    order_id    INT         PRIMARY KEY,          -- Primary Key
    customer_id INT         NOT NULL,
    email       VARCHAR(100) UNIQUE,              -- Alternate/Unique Key
    product_id  INT,
    quantity    INT,

    FOREIGN KEY (customer_id) REFERENCES customers(id),   -- Foreign Key
    FOREIGN KEY (product_id)  REFERENCES products(id)
);

-- Composite Key example:
CREATE TABLE enrollment (
    student_id  INT,
    course_id   INT,
    PRIMARY KEY (student_id, course_id)           -- Composite PK
);
```

### Key Relationships Hierarchy
```
Super Key ⊇ Candidate Key ⊇ Primary Key
```
Every primary key is a candidate key; every candidate key is a super key — but not vice versa.

---

<a name="q4"></a>
## Q4. What are the different types of SQL commands?

**Answer:**

SQL commands are grouped into five categories based on their purpose:

```
┌──────┬───────────────────────────────┬──────────────────────────────────────┐
│ Type │ Full Name                     │ Commands                             │
├──────┼───────────────────────────────┼──────────────────────────────────────┤
│ DDL  │ Data Definition Language      │ CREATE, ALTER, DROP, TRUNCATE, RENAME│
│ DML  │ Data Manipulation Language    │ SELECT, INSERT, UPDATE, DELETE       │
│ DCL  │ Data Control Language         │ GRANT, REVOKE                        │
│ TCL  │ Transaction Control Language  │ COMMIT, ROLLBACK, SAVEPOINT          │
│ DQL  │ Data Query Language           │ SELECT (sometimes separated)         │
└──────┴───────────────────────────────┴──────────────────────────────────────┘
```

### DDL Examples
```sql
-- CREATE
CREATE TABLE employees (
    id      INT PRIMARY KEY AUTO_INCREMENT,
    name    VARCHAR(100) NOT NULL,
    salary  DECIMAL(10,2),
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments(id)
);

-- ALTER
ALTER TABLE employees ADD COLUMN email VARCHAR(100);
ALTER TABLE employees MODIFY COLUMN salary DECIMAL(12,2);
ALTER TABLE employees DROP COLUMN email;

-- DROP vs TRUNCATE
DROP TABLE employees;         -- Removes table structure + data permanently
TRUNCATE TABLE employees;     -- Removes all rows, keeps structure (faster, no rollback)
DELETE FROM employees;        -- Removes rows, can be filtered, logged, rollback-able
```

### DML Examples
```sql
INSERT INTO employees (name, salary, dept_id) VALUES ('Alice', 80000, 1);

UPDATE employees SET salary = salary * 1.10 WHERE dept_id = 2;

DELETE FROM employees WHERE id = 5;
```

### TCL Examples
```sql
BEGIN;
    UPDATE accounts SET balance = balance - 500 WHERE id = 1;
    UPDATE accounts SET balance = balance + 500 WHERE id = 2;
COMMIT;        -- Make changes permanent

ROLLBACK;      -- Undo all changes since last COMMIT

SAVEPOINT sp1;
    DELETE FROM orders WHERE status = 'cancelled';
ROLLBACK TO sp1;  -- Undo only back to savepoint
```

---

<a name="q5"></a>
## Q5. What are Joins and their types?

**Answer:**

A **JOIN** combines rows from two or more tables based on a related column condition.

### Types of Joins

```
Tables:
employees:  id | name   | dept_id       departments: id | dept_name
            1  | Alice  | 10                          10 | Engineering
            2  | Bob    | 20                          20 | Marketing
            3  | Carol  | NULL                        30 | Finance (no employees)
```

#### INNER JOIN — only matching rows
```sql
SELECT e.name, d.dept_name
FROM employees e
INNER JOIN departments d ON e.dept_id = d.id;
-- Result: Alice/Engineering, Bob/Marketing  (Carol excluded — NULL dept_id)
```

#### LEFT JOIN — all left rows + matching right rows
```sql
SELECT e.name, d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.id;
-- Result: Alice/Engineering, Bob/Marketing, Carol/NULL  (Carol included)
```

#### RIGHT JOIN — all right rows + matching left rows
```sql
SELECT e.name, d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.id;
-- Result: Alice/Engineering, Bob/Marketing, NULL/Finance  (Finance included)
```

#### FULL OUTER JOIN — all rows from both tables
```sql
SELECT e.name, d.dept_name
FROM employees e
FULL OUTER JOIN departments d ON e.dept_id = d.id;
-- Result: Alice/Engineering, Bob/Marketing, Carol/NULL, NULL/Finance
```

#### CROSS JOIN — cartesian product
```sql
SELECT e.name, d.dept_name
FROM employees e
CROSS JOIN departments d;
-- Result: 3 employees × 3 departments = 9 rows
```

#### SELF JOIN — join table with itself
```sql
-- Find employees who share the same department
SELECT a.name AS emp1, b.name AS emp2, a.dept_id
FROM employees a
INNER JOIN employees b ON a.dept_id = b.dept_id AND a.id < b.id;
```

### Visual Summary
```
INNER JOIN    LEFT JOIN     RIGHT JOIN   FULL OUTER JOIN
   A∩B          A           B               A∪B
  ┌─┐          ┌──┐         ┌──┐          ┌────┐
 ─┤█├─        ─┤██├─       ─┤██├─        ─┤████├─
  └─┘          └──┘         └──┘          └────┘
```

---

<a name="q6"></a>
## Q6. What is Normalization and its Normal Forms?

**Answer:**

**Normalization** is the process of organizing a relational database to **reduce data redundancy** and **improve data integrity** by dividing large tables into smaller ones and defining relationships between them.

### Anomalies that Normalization Solves

```
Un-normalized table: Student_Course
┌────────────┬───────────────┬────────────┬─────────────────┐
│ student_id │ student_name  │ course_id  │ instructor      │
├────────────┼───────────────┼────────────┼─────────────────┤
│ 1          │ Alice         │ CS101      │ Prof. Smith     │
│ 1          │ Alice         │ CS102      │ Prof. Jones     │  ← Insertion anomaly
│ 2          │ Bob           │ CS101      │ Prof. Smith     │  ← Update anomaly (change instructor everywhere)
└────────────┴───────────────┴────────────┴─────────────────┘  ← Deletion anomaly (delete last enrollment → lose instructor)
```

### Normal Forms

#### 1NF — First Normal Form
- Each column holds **atomic** (indivisible) values
- No repeating groups or arrays
```sql
-- VIOLATES 1NF: phones = "9876, 8765"
-- SATISFIES 1NF: separate row per phone number
```

#### 2NF — Second Normal Form
- Must be in 1NF
- No **partial dependency** — every non-key attribute depends on the **whole** primary key (applies to composite keys)
```
Table: (student_id, course_id) → grade         ← full dependency ✅
       (student_id, course_id) → student_name  ← partial (depends only on student_id) ❌
Fix: Split into Students(student_id, name) and Enrollments(student_id, course_id, grade)
```

#### 3NF — Third Normal Form
- Must be in 2NF
- No **transitive dependency** — non-key attribute should not depend on another non-key attribute
```
emp_id → dept_id → dept_name   ← transitive ❌
Fix: Employees(emp_id, dept_id) and Departments(dept_id, dept_name)
```

#### BCNF — Boyce-Codd Normal Form (3.5NF)
- Stricter than 3NF
- For every functional dependency X → Y, X must be a **super key**
```
Courses(student, subject, teacher)
teacher → subject  (teacher determines subject — but teacher is not a super key) ❌
Fix: Split into (student, teacher) and (teacher, subject)
```

#### 4NF — Fourth Normal Form
- Must be in BCNF
- No **multi-valued dependencies** (one attribute shouldn't independently determine multiple values of two other attributes)

#### 5NF — Fifth Normal Form
- Must be in 4NF
- No **join dependencies** — table cannot be reconstructed from smaller projections

### Normalization Summary
```
1NF  → Atomic values, no repeating groups
  ↓
2NF  → No partial dependencies (on composite keys)
  ↓
3NF  → No transitive dependencies
  ↓
BCNF → Every determinant is a super key
  ↓
4NF  → No multi-valued dependencies
  ↓
5NF  → No join dependencies
```

---

<a name="q7"></a>
## Q7. What is Denormalization?

**Answer:**

**Denormalization** is the deliberate process of introducing **controlled redundancy** into a normalized database to **improve read performance**, at the cost of increased storage and write complexity.

### Why Denormalize?

In highly normalized schemas, complex queries require many JOINs, which can be expensive at scale:

```sql
-- Normalized: 4 JOINs to get order summary
SELECT o.id, c.name, p.title, p.price, oi.quantity
FROM orders o
JOIN customers c ON o.customer_id = c.id
JOIN order_items oi ON oi.order_id = o.id
JOIN products p ON oi.product_id = p.id;

-- Denormalized: store customer_name, product_title in order_items
SELECT order_id, customer_name, product_title, price, quantity
FROM order_items_denormalized;
-- Fast single-table scan ✅
```

### Denormalization Techniques

| Technique | Description |
|-----------|-------------|
| **Storing derived data** | Pre-compute total_price, order_count |
| **Duplicating columns** | Copy `customer_name` into `orders` table |
| **Pre-joining tables** | Merge frequently joined tables |
| **Adding redundant tables** | Summary/aggregate tables for reporting |

### Normalization vs Denormalization

| Aspect | Normalization | Denormalization |
|--------|--------------|-----------------|
| Redundancy | Minimal | Controlled redundancy |
| Read performance | Slower (many JOINs) | Faster (fewer JOINs) |
| Write performance | Faster (update once) | Slower (update everywhere) |
| Storage | Less | More |
| Data integrity | High | Risk of inconsistency |
| Use case | OLTP (transactional) | OLAP (analytical), read-heavy |

---

<a name="q8"></a>
## Q8. What are ACID Properties?

**Answer:**

**ACID** is a set of properties that guarantee database transactions are processed reliably, even in the event of system failures.

```
A — Atomicity
C — Consistency
I — Isolation
D — Durability
```

### Atomicity
> "All or nothing" — a transaction either completes fully or has no effect at all.

```sql
BEGIN;
  UPDATE accounts SET balance = balance - 500 WHERE id = 1;  -- Step 1
  UPDATE accounts SET balance = balance + 500 WHERE id = 2;  -- Step 2
COMMIT;

-- If Step 2 fails → ROLLBACK automatically undoes Step 1
-- Money never disappears ✅
```

### Consistency
> A transaction takes the database from one **valid state** to another valid state, respecting all defined rules and constraints.

```
Before: Account A = 1000, Account B = 500  (total = 1500)
After:  Account A = 500,  Account B = 1000 (total = 1500) ✅
Constraint: Total balance must remain constant
```

### Isolation
> Concurrent transactions execute as if they were **serial** — intermediate states are invisible to other transactions.

```
T1: Read balance (1000) → compute → write (1000 - 500 = 500)
T2: Read balance (1000) → compute → write (1000 - 200 = 800)  ← reads stale data!

Without isolation: both could read 1000, both write, final = 800 (lost T1's update)
With isolation: T2 waits or sees T1's committed result ✅
```

### Durability
> Once a transaction is **committed**, it persists — even if the system crashes immediately after.

```
Mechanism: Write-Ahead Log (WAL)
  1. Write changes to WAL (disk) before applying to data pages
  2. On crash recovery, replay WAL to restore committed transactions
  3. Committed data survives power outages ✅
```

### ACID in Practice

| Property | Mechanism |
|----------|-----------|
| Atomicity | Undo log / rollback segments |
| Consistency | Constraints, triggers, cascades |
| Isolation | Locks, MVCC |
| Durability | WAL (Write-Ahead Log), fsync |

---

<a name="q9"></a>
## Q9. What is a Transaction?

**Answer:**

A **transaction** is a logical unit of work — a sequence of one or more SQL operations that must be treated as a single, indivisible unit. It either **commits** (all changes applied) or **rolls back** (all changes undone).

### Transaction States

```
                 BEGIN
                   │
                   ▼
             ┌─────────────┐
             │   ACTIVE    │  ── executing operations
             └──────┬──────┘
                    │
           ┌────────┴──────────┐
           │ Partial Commit    │ ── all ops done, not yet written
           └────────┬──────────┘
                    │
           ┌────────┴──────────┐
           │   COMMITTED       │ ── durable, changes visible
           └───────────────────┘
                    OR
           ┌────────────────────┐
           │   FAILED / ABORTED │ ── rolled back, no effect
           └────────────────────┘
```

### Transaction Example — Bank Transfer

```sql
BEGIN TRANSACTION;

    -- Debit sender
    UPDATE accounts
    SET balance = balance - 1000
    WHERE account_no = 'ACC001';

    -- Check for sufficient funds
    IF (SELECT balance FROM accounts WHERE account_no = 'ACC001') < 0 THEN
        ROLLBACK;  -- Insufficient funds — undo everything
    END IF;

    -- Credit receiver
    UPDATE accounts
    SET balance = balance + 1000
    WHERE account_no = 'ACC002';

    -- Log the transaction
    INSERT INTO transaction_log (from_acc, to_acc, amount, ts)
    VALUES ('ACC001', 'ACC002', 1000, NOW());

COMMIT;  -- All or nothing ✅
```

### Implicit vs Explicit Transactions
```sql
-- Explicit (recommended for multi-statement)
BEGIN; ... COMMIT;

-- Implicit (each DML is auto-committed in MySQL by default)
UPDATE ...;  -- auto-committed immediately
```

---

<a name="q10"></a>
## Q10. What are Transaction Isolation Levels?

**Answer:**

**Isolation levels** define how much a transaction is isolated from the effects of other concurrent transactions. Higher isolation = fewer anomalies but more contention and lower performance.

### Four Standard Isolation Levels (SQL Standard)

```
READ UNCOMMITTED  ← Weakest / Fastest
READ COMMITTED
REPEATABLE READ
SERIALIZABLE      ← Strongest / Slowest
```

### Phenomena They Prevent

| Isolation Level | Dirty Read | Non-Repeatable Read | Phantom Read |
|-----------------|:----------:|:-------------------:|:------------:|
| READ UNCOMMITTED | ❌ Possible | ❌ Possible | ❌ Possible |
| READ COMMITTED | ✅ Prevented | ❌ Possible | ❌ Possible |
| REPEATABLE READ | ✅ Prevented | ✅ Prevented | ❌ Possible |
| SERIALIZABLE | ✅ Prevented | ✅ Prevented | ✅ Prevented |

### Anomaly Definitions

**Dirty Read** — Read uncommitted data from another transaction that may later be rolled back:
```
T1: UPDATE salary = 90000  (not committed)
T2: SELECT salary → reads 90000  ← dirty read!
T1: ROLLBACK  → salary reverts to 80000
T2 acted on wrong data ❌
```

**Non-Repeatable Read** — Same row read twice in a transaction gives different values:
```
T1: SELECT salary → 80000
T2: UPDATE salary = 90000; COMMIT
T1: SELECT salary → 90000  ← different! non-repeatable read ❌
```

**Phantom Read** — Re-executing a range query returns different rows:
```
T1: SELECT * FROM orders WHERE amount > 1000 → 5 rows
T2: INSERT INTO orders (amount=2000); COMMIT
T1: SELECT * FROM orders WHERE amount > 1000 → 6 rows  ← phantom! ❌
```

### Setting Isolation Level
```sql
-- MySQL / PostgreSQL
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- PostgreSQL default: READ COMMITTED
-- MySQL InnoDB default: REPEATABLE READ
```

---

<a name="q11"></a>
## Q11. What are Concurrency Problems?

**Answer:**

When multiple transactions execute concurrently without proper control, several problems can arise:

### 1. Lost Update
Two transactions read the same value and both write back updates — one update is overwritten:
```
T1: read(X=100) → X = 100 - 10 → write(X=90)
T2: read(X=100) → X = 100 - 20 → write(X=80)   ← T1's update LOST
Final: X = 80 (should be 70) ❌
```

### 2. Dirty Read
Reading uncommitted data (covered in Q10).

### 3. Non-Repeatable Read
Same query returns different results within a transaction (covered in Q10).

### 4. Phantom Read
New rows appear in a repeated range query (covered in Q10).

### 5. Unrepeatable Read vs Phantom Read
```
Non-Repeatable Read → same existing row returns DIFFERENT value
Phantom Read        → query returns DIFFERENT SET of rows (new/deleted rows)
```

### Solutions to Concurrency Problems

| Problem | Solution |
|---------|----------|
| Lost Update | Locking (exclusive lock on write) |
| Dirty Read | READ COMMITTED isolation level |
| Non-Repeatable Read | REPEATABLE READ isolation level |
| Phantom Read | SERIALIZABLE level or range locks |
| General | MVCC (Multi-Version Concurrency Control) |

### MVCC (Multi-Version Concurrency Control)
Used by PostgreSQL, MySQL InnoDB, Oracle:
```
Instead of locking rows for reads, maintain multiple versions:
  T1 reads version @ timestamp T
  T2 writes new version @ timestamp T+1
  T1 still sees version @ T → no blocking, no dirty reads ✅
  
Reads don't block writes; writes don't block reads
```

---

<a name="q12"></a>
## Q12. What is Locking? Types of Locks?

**Answer:**

**Locking** is the primary mechanism for ensuring isolation in concurrent transactions. A lock prevents other transactions from accessing a resource in a conflicting manner.

### Lock Types

```
┌─────────────────┬──────────────────────────────────────────────────────┐
│ Lock Type       │ Description                                          │
├─────────────────┼──────────────────────────────────────────────────────┤
│ Shared (S)      │ Read lock — multiple transactions can hold at once   │
│ Exclusive (X)   │ Write lock — only one transaction, blocks all others │
│ Update (U)      │ Intent to upgrade to X; prevents deadlock in upgrades│
│ Intent (IS/IX)  │ Signals intent to lock at lower granularity          │
└─────────────────┴──────────────────────────────────────────────────────┘
```

### Lock Compatibility Matrix
```
        S       X
S   ✅ Compatible  ❌ Conflict
X   ❌ Conflict    ❌ Conflict
```

### Lock Granularity

```
Database Level   ← coarse-grained (low concurrency, simple)
Table Level
Page Level
Row Level        ← fine-grained (high concurrency, complex)
Column Level
```

Row-level locking (used by InnoDB) maximizes concurrency — only the affected row is locked.

### Two-Phase Locking (2PL)
A protocol ensuring serializability:
```
Phase 1 — Growing:   Transaction acquires locks (no releases)
Phase 2 — Shrinking: Transaction releases locks (no acquisitions)

         Locks held
              ▲
              │    /\ 
              │   /  \
              │  /    \
              │ /      \
              └──────────────── time
              Growing  Shrinking
```

### Optimistic vs Pessimistic Locking

| Type | Approach | Best For |
|------|----------|----------|
| **Pessimistic** | Lock before reading/writing; assumes conflicts likely | High-contention, short transactions |
| **Optimistic** | No lock; check for conflict at commit time; retry if conflict | Low-contention, long reads |

```sql
-- Optimistic locking using version column
SELECT id, name, version FROM products WHERE id = 5;
-- (user edits...)
UPDATE products
SET name = 'New Name', version = version + 1
WHERE id = 5 AND version = 3;   -- fails if another TX changed it
```

---

<a name="q13"></a>
## Q13. What is Deadlock and how is it handled?

**Answer:**

A **deadlock** occurs when two or more transactions are **permanently waiting** for each other to release locks — a circular dependency with no way forward.

### Deadlock Illustration

```
T1 holds lock on Row A, wants lock on Row B
T2 holds lock on Row B, wants lock on Row A

T1: Lock(A) ──────────────────────────────────► waiting for Lock(B) ←──────┐
                                                                             │
T2: Lock(B) ──────────────────────────────────► waiting for Lock(A) ←──────┘

Both wait forever ← DEADLOCK ❌
```

### Deadlock Example in SQL
```sql
-- Transaction T1
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;  -- Lock row 1
UPDATE accounts SET balance = balance + 100 WHERE id = 2;  -- Wait for row 2

-- Transaction T2 (concurrent)
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 2;  -- Lock row 2
UPDATE accounts SET balance = balance + 100 WHERE id = 1;  -- Wait for row 1 → DEADLOCK
```

### Deadlock Handling Strategies

| Strategy | Mechanism | Description |
|----------|-----------|-------------|
| **Detection** | Wait-for graph | DB periodically checks for cycles; kills one victim transaction |
| **Prevention** | Lock ordering | Always acquire locks in same global order |
| **Prevention** | Timeout | Abort transaction if waiting too long |
| **Avoidance** | Wait-Die / Wound-Wait | Timestamp-based preemption schemes |

### MySQL/PostgreSQL Deadlock Handling
Both detect deadlocks automatically and **abort the transaction with less work done** (the "victim"), returning an error to the application. The application should then retry.

```
ERROR 1213: Deadlock found when trying to get lock; try restarting transaction
```

### Prevention — Lock Ordering
```sql
-- Always lock lower ID first:
-- T1 and T2 both lock id=1 first, then id=2
-- T2 will wait at step 1 instead of creating a cycle
```

---

<a name="q14"></a>
## Q14. What is an Index? Types of Indexes?

**Answer:**

An **index** is a data structure that improves the speed of data retrieval operations at the cost of additional storage and slower write operations. Think of it as a book's index — instead of scanning every page, you jump directly to the relevant page.

### Without Index vs With Index

```
Without Index (Full Table Scan):
SELECT * FROM employees WHERE emp_id = 9999;
→ Scans all 1,000,000 rows: O(n) ← slow

With Index on emp_id:
→ B+ Tree lookup: O(log n) ← fast
```

### Types of Indexes

#### 1. Single Column Index
```sql
CREATE INDEX idx_salary ON employees(salary);
```

#### 2. Composite (Multi-column) Index
```sql
CREATE INDEX idx_dept_salary ON employees(dept_id, salary);
-- Useful for: WHERE dept_id = 10 AND salary > 50000
-- Column order matters! Most selective column first.
```

#### 3. Unique Index
```sql
CREATE UNIQUE INDEX idx_email ON users(email);
-- Enforces uniqueness + speeds up lookups
```

#### 4. Full-Text Index
```sql
CREATE FULLTEXT INDEX idx_description ON products(description);
SELECT * FROM products WHERE MATCH(description) AGAINST('wireless keyboard');
-- For text search — not regular LIKE '%keyword%'
```

#### 5. Partial / Filtered Index (PostgreSQL)
```sql
CREATE INDEX idx_active_users ON users(email) WHERE is_active = TRUE;
-- Smaller index — only indexes active users
```

#### 6. Covering Index
```sql
-- Query only touches index, never reads main table
CREATE INDEX idx_covering ON orders(customer_id, order_date, total);
SELECT order_date, total FROM orders WHERE customer_id = 42;
-- All needed columns are IN the index → index-only scan ✅
```

### When NOT to Index
- Small tables (full scan often faster)
- Columns with very low cardinality (e.g., boolean: only 2 values)
- Tables with very heavy write operations
- Columns rarely used in WHERE / JOIN / ORDER BY

---

<a name="q15"></a>
## Q15. What is a B-Tree and B+ Tree Index?

**Answer:**

Most relational databases (MySQL InnoDB, PostgreSQL) use **B+ Trees** as the underlying index structure.

### B-Tree
- Self-balancing tree where every node can have multiple keys and children
- Keys **and data** are stored in all nodes (internal + leaf)
- All leaf nodes are at the same depth

```
B-Tree (order 3):
                  [30 | 70]
                 /    |    \
          [10|20]  [40|60]  [80|90]
```

### B+ Tree (used by most RDBMS)
- Keys in **internal nodes** are only routing guides — no data
- **All actual data** (or row pointers) stored in **leaf nodes only**
- Leaf nodes are **linked** as a doubly linked list → enables efficient range scans

```
B+ Tree:
              Internal: [30 | 70]
             /              |              \
Internal: [10|20]      [40|60]          [80|90]
             ↓              ↓               ↓
Leaf:   [10][20][30] ↔ [40][60][70] ↔ [80][90][100]
         └──────── linked list ──────────────────┘
```

### Why B+ Tree over B-Tree?

| Feature | B-Tree | B+ Tree |
|---------|--------|---------|
| Data stored | All nodes | Leaf nodes only |
| Range queries | Slow (traverse tree) | Fast (scan linked leaves) |
| Disk I/O | More (data in internal nodes wastes space) | Less (more keys per internal node) |
| Sequential scan | Inefficient | Very efficient (linked leaves) |

### B+ Tree Operations
```
Search:  O(log n)  — traverse from root to leaf
Insert:  O(log n)  — find leaf, insert, split if needed
Delete:  O(log n)  — find leaf, delete, rebalance if needed
Range:   O(log n + k) — find start, follow linked list for k results
```

---

<a name="q16"></a>
## Q16. What is the difference between Clustered and Non-Clustered Index?

**Answer:**

### Clustered Index
- The table's **physical data rows are stored in the order** of the index key
- Only **one clustered index per table** (data can only be sorted one way)
- In MySQL InnoDB, the **Primary Key IS the clustered index**

```
Clustered Index on emp_id:

Disk Storage (physically sorted by emp_id):
┌────────┬─────────┬────────┬──────────┐
│ emp_id │ name    │ salary │ dept_id  │
├────────┼─────────┼────────┼──────────┤
│ 1      │ Alice   │ 80000  │ 10       │  ← actual row
│ 2      │ Bob     │ 90000  │ 20       │  ← actual row
│ 3      │ Carol   │ 75000  │ 10       │  ← actual row
└────────┴─────────┴────────┴──────────┘
B+ Tree leaf nodes → directly ARE the data pages
```

### Non-Clustered Index (Secondary Index)
- A **separate structure** from the table — contains index key + pointer to the actual row
- **Multiple non-clustered indexes** per table allowed
- Lookup: traverse index B+ tree → get row pointer → fetch from data page (**double lookup**)

```
Non-Clustered Index on salary:

Index B+ Tree (sorted by salary):
┌────────┬──────────┐
│ salary │ row_ptr  │
├────────┼──────────┤
│ 75000  │ → row 3  │
│ 80000  │ → row 1  │
│ 90000  │ → row 2  │
└────────┴──────────┘
         ↓ pointer lookup ↓
         Actual data pages (unsorted by salary)
```

### Comparison

| Feature | Clustered | Non-Clustered |
|---------|-----------|---------------|
| Data storage | Index IS the table | Separate from table |
| Count per table | 1 (only one) | Many allowed |
| Range queries | Very fast | Moderate (pointer chasing) |
| Lookup speed | Fastest (1 I/O for leaf) | Slower (index + table I/O) |
| Storage | No extra | Extra space for index |
| MySQL InnoDB | Primary Key | All other indexes |

---

<a name="q17"></a>
## Q17. What is a View?

**Answer:**

A **View** is a **virtual table** based on the result of a stored SQL query. It does not physically store data — it fetches from underlying tables each time it is queried (unless it's a materialized view).

```sql
-- Create a view
CREATE VIEW employee_summary AS
SELECT
    e.emp_id,
    e.name,
    d.dept_name,
    e.salary,
    RANK() OVER (PARTITION BY e.dept_id ORDER BY e.salary DESC) AS salary_rank
FROM employees e
JOIN departments d ON e.dept_id = d.id;

-- Use the view like a table
SELECT * FROM employee_summary WHERE salary_rank = 1;
-- Gets highest-paid employee per department
```

### Benefits of Views

| Benefit | How |
|---------|-----|
| **Abstraction** | Hide complex queries behind a simple name |
| **Security** | Expose only specific columns/rows to certain users |
| **Reusability** | Define once, use everywhere |
| **Consistency** | Logic changes in one place |

### Updatable vs Non-Updatable Views
```sql
-- Updatable view (simple, single table, no aggregation)
CREATE VIEW active_employees AS
SELECT * FROM employees WHERE is_active = 1;

UPDATE active_employees SET salary = 90000 WHERE emp_id = 5;  -- Allowed ✅

-- Non-updatable view (aggregation, GROUP BY, DISTINCT, JOINs)
CREATE VIEW dept_stats AS
SELECT dept_id, AVG(salary) AS avg_salary FROM employees GROUP BY dept_id;

UPDATE dept_stats SET avg_salary = 90000;  -- ❌ Error
```

### Materialized View
- **Stores the result physically** on disk (not just the query)
- Must be **refreshed** manually or on a schedule
- Dramatically faster for expensive aggregation queries
```sql
-- PostgreSQL
CREATE MATERIALIZED VIEW monthly_sales AS
SELECT DATE_TRUNC('month', order_date) AS month, SUM(total) AS revenue
FROM orders GROUP BY 1;

REFRESH MATERIALIZED VIEW monthly_sales;  -- Update the snapshot
```

---

<a name="q18"></a>
## Q18. What is a Stored Procedure vs Function?

**Answer:**

Both are named, reusable blocks of SQL code stored in the database. They differ in how they're used and what they can do.

```
┌─────────────────┬────────────────────────────┬──────────────────────────────┐
│ Feature         │ Stored Procedure           │ Function (UDF)               │
├─────────────────┼────────────────────────────┼──────────────────────────────┤
│ Return value    │ Optional (OUT params)       │ Must return a value          │
│ Use in SELECT   │ Cannot use directly         │ Can use in SELECT/WHERE      │
│ DML inside      │ Yes (INSERT/UPDATE/DELETE)  │ Generally restricted         │
│ Transaction     │ Can manage transactions     │ Cannot                       │
│ Exception       │ Can handle                  │ Limited                      │
│ Called with     │ CALL / EXEC                 │ SELECT func() or in queries  │
└─────────────────┴────────────────────────────┴──────────────────────────────┘
```

### Stored Procedure Example
```sql
DELIMITER //
CREATE PROCEDURE transfer_funds(
    IN  from_acc INT,
    IN  to_acc   INT,
    IN  amount   DECIMAL(10,2),
    OUT status   VARCHAR(50)
)
BEGIN
    DECLARE current_balance DECIMAL(10,2);

    SELECT balance INTO current_balance FROM accounts WHERE id = from_acc;

    IF current_balance < amount THEN
        SET status = 'INSUFFICIENT_FUNDS';
    ELSE
        UPDATE accounts SET balance = balance - amount WHERE id = from_acc;
        UPDATE accounts SET balance = balance + amount WHERE id = to_acc;
        SET status = 'SUCCESS';
        COMMIT;
    END IF;
END //
DELIMITER ;

-- Call it:
CALL transfer_funds(1, 2, 500.00, @result);
SELECT @result;
```

### Function Example
```sql
CREATE FUNCTION calculate_tax(salary DECIMAL(10,2))
RETURNS DECIMAL(10,2)
DETERMINISTIC
BEGIN
    DECLARE tax DECIMAL(10,2);
    IF salary > 100000 THEN SET tax = salary * 0.30;
    ELSEIF salary > 50000 THEN SET tax = salary * 0.20;
    ELSE SET tax = salary * 0.10;
    END IF;
    RETURN tax;
END;

-- Use in SELECT:
SELECT name, salary, calculate_tax(salary) AS tax_owed FROM employees;
```

---

<a name="q19"></a>
## Q19. What is a Trigger?

**Answer:**

A **trigger** is a database object that **automatically executes** a predefined set of SQL statements in response to specific events (INSERT, UPDATE, DELETE) on a table.

```
Event on Table ──► Trigger fires automatically ──► Execute trigger body
```

### Trigger Syntax
```sql
CREATE TRIGGER trigger_name
    {BEFORE | AFTER}
    {INSERT | UPDATE | DELETE}
    ON table_name
    FOR EACH ROW
BEGIN
    -- trigger body
END;
```

### Example 1 — Audit Log Trigger
```sql
CREATE TABLE employee_audit (
    audit_id    INT AUTO_INCREMENT PRIMARY KEY,
    emp_id      INT,
    old_salary  DECIMAL(10,2),
    new_salary  DECIMAL(10,2),
    changed_at  TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    changed_by  VARCHAR(100)
);

CREATE TRIGGER after_salary_update
    AFTER UPDATE ON employees
    FOR EACH ROW
BEGIN
    IF OLD.salary <> NEW.salary THEN
        INSERT INTO employee_audit(emp_id, old_salary, new_salary, changed_by)
        VALUES (NEW.emp_id, OLD.salary, NEW.salary, USER());
    END IF;
END;
```

### Example 2 — Validation Trigger (BEFORE)
```sql
CREATE TRIGGER before_insert_employee
    BEFORE INSERT ON employees
    FOR EACH ROW
BEGIN
    IF NEW.salary < 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Salary cannot be negative';
    END IF;
END;
```

### Trigger Types

| Timing | Event | Use Case |
|--------|-------|----------|
| BEFORE INSERT | INSERT | Validate/transform data before saving |
| AFTER INSERT | INSERT | Audit log, update counts |
| BEFORE UPDATE | UPDATE | Validate, set timestamps |
| AFTER UPDATE | UPDATE | Propagate changes, audit |
| BEFORE DELETE | DELETE | Check dependencies |
| AFTER DELETE | DELETE | Cleanup, archive |

> ⚠️ **Pitfalls:** Triggers are hidden logic — hard to debug, can cause performance issues and cascading effects. Use sparingly.

---

<a name="q20"></a>
## Q20. What is the Entity-Relationship (ER) Model?

**Answer:**

The **ER Model** is a high-level **conceptual data model** used to design and visualize database schemas before implementation. It describes data in terms of entities, attributes, and relationships.

### Core Components

```
┌────────────────┬──────────────────────────────────────────────────┐
│ Component      │ Description                         │ Symbol     │
├────────────────┼─────────────────────────────────────┼────────────┤
│ Entity         │ Real-world object (table)            │ Rectangle  │
│ Attribute      │ Property of an entity (column)       │ Oval       │
│ Relationship   │ Association between entities         │ Diamond    │
│ Primary Key    │ Underlined attribute                 │ Underline  │
│ Weak Entity    │ Cannot exist without parent          │ Double rect│
└────────────────┴─────────────────────────────────────┴────────────┘
```

### ER Diagram Example
```
[CUSTOMER] ────── places ────── [ORDER] ────── contains ────── [PRODUCT]
    │                               │                                │
  cust_id                       order_id                        product_id
  name                          order_date                      name
  email                         total_amount                    price
                                                                stock_qty
```

### Cardinality (Relationship Ratios)

```
One-to-One   (1:1)  → Person ──── has ──── Passport
One-to-Many  (1:N)  → Department ──── has ──── Employees
Many-to-Many (M:N)  → Students ──── enroll in ──── Courses
                       (requires junction table: Enrollment)
```

### ER to Relational Mapping

| ER Concept | Relational Mapping |
|-----------|-------------------|
| Entity | Table |
| Attribute | Column |
| Primary Key | Primary Key column |
| 1:N Relationship | FK in the "many" side table |
| M:N Relationship | Junction/bridge table with two FKs |
| Weak Entity | Include parent PK as part of composite PK |

---

<a name="q21"></a>
## Q21. What is Relational Algebra?

**Answer:**

**Relational Algebra** is a procedural query language that forms the **theoretical foundation** of SQL. It operates on relations (tables) and produces new relations as output.

### Core Operations

| Operation | Symbol | SQL Equivalent | Description |
|-----------|--------|---------------|-------------|
| **Select** | σ | WHERE | Filter rows by condition |
| **Project** | π | SELECT columns | Select specific columns |
| **Union** | ∪ | UNION | Combine rows from two relations |
| **Intersection** | ∩ | INTERSECT | Common rows in both |
| **Difference** | − | EXCEPT / MINUS | Rows in first but not second |
| **Cartesian Product** | × | CROSS JOIN | All combinations of rows |
| **Join** | ⋈ | JOIN | Combine based on condition |
| **Rename** | ρ | AS | Rename relation or attributes |
| **Division** | ÷ | complex subquery | Find entities related to ALL of another set |

### Examples

```
-- Select (σ): Filter employees with salary > 50000
σ salary > 50000 (Employees)
SQL: SELECT * FROM Employees WHERE salary > 50000;

-- Project (π): Get only name and salary
π name, salary (Employees)
SQL: SELECT name, salary FROM Employees;

-- Natural Join (⋈): Combine Employees and Departments
Employees ⋈ Departments
SQL: SELECT * FROM Employees JOIN Departments ON dept_id = id;

-- Combining operations (find names of high-paid employees):
π name (σ salary > 80000 (Employees))
SQL: SELECT name FROM Employees WHERE salary > 80000;
```

---

<a name="q22"></a>
## Q22. What are Aggregate Functions and GROUP BY / HAVING?

**Answer:**

**Aggregate functions** perform calculations across a set of rows and return a single value.

### Aggregate Functions

| Function | Description |
|----------|-------------|
| `COUNT(*)` | Number of rows |
| `COUNT(col)` | Non-NULL values |
| `SUM(col)` | Total sum |
| `AVG(col)` | Average value |
| `MIN(col)` | Minimum value |
| `MAX(col)` | Maximum value |
| `GROUP_CONCAT` | Concatenate values (MySQL) |
| `STDDEV`, `VARIANCE` | Statistical functions |

### GROUP BY
Groups rows with the same values, then applies aggregate function per group:
```sql
-- Average salary per department
SELECT
    d.dept_name,
    COUNT(e.emp_id)   AS headcount,
    AVG(e.salary)     AS avg_salary,
    MAX(e.salary)     AS top_salary,
    SUM(e.salary)     AS total_payroll
FROM employees e
JOIN departments d ON e.dept_id = d.id
GROUP BY d.dept_name
ORDER BY avg_salary DESC;
```

### HAVING vs WHERE
```sql
-- WHERE filters rows BEFORE grouping
-- HAVING filters groups AFTER aggregation

SELECT dept_id, AVG(salary) AS avg_sal
FROM employees
WHERE is_active = 1               -- Filter rows first (uses index)
GROUP BY dept_id
HAVING AVG(salary) > 70000;       -- Filter groups after aggregation
```

### Common Pitfall — Non-Aggregated Columns
```sql
-- ❌ WRONG: name not in GROUP BY or aggregate
SELECT dept_id, name, MAX(salary) FROM employees GROUP BY dept_id;

-- ✅ CORRECT: only grouped/aggregated columns in SELECT
SELECT dept_id, MAX(salary) FROM employees GROUP BY dept_id;
```

### Execution Order of a SQL Query
```
FROM → JOIN → WHERE → GROUP BY → HAVING → SELECT → DISTINCT → ORDER BY → LIMIT
```

---

<a name="q23"></a>
## Q23. What is a Subquery vs JOIN?

**Answer:**

Both retrieve related data from multiple tables, but differ in approach and performance characteristics.

### Subquery (Nested Query)
A query nested inside another query:

```sql
-- Correlated Subquery: Find employees earning above their dept average
SELECT name, salary, dept_id
FROM employees e
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
    WHERE dept_id = e.dept_id   -- references outer query ← correlated
);

-- Non-Correlated Subquery: Find employees in the 'Engineering' dept
SELECT name FROM employees
WHERE dept_id = (
    SELECT id FROM departments WHERE dept_name = 'Engineering'
);

-- IN Subquery: Find customers who placed at least one order
SELECT name FROM customers
WHERE id IN (SELECT DISTINCT customer_id FROM orders);
```

### JOIN (same results, often faster)
```sql
-- Equivalent to IN subquery — but often more efficient
SELECT DISTINCT c.name
FROM customers c
INNER JOIN orders o ON c.id = o.customer_id;
```

### EXISTS vs IN vs JOIN

```sql
-- EXISTS: short-circuits at first match — best for large result sets
SELECT name FROM customers c
WHERE EXISTS (
    SELECT 1 FROM orders o WHERE o.customer_id = c.id
);

-- IN: evaluates all values — best when subquery result is small
SELECT name FROM customers
WHERE id IN (SELECT customer_id FROM orders WHERE total > 1000);

-- JOIN: generally fastest for large tables when indexes exist
SELECT DISTINCT c.name
FROM customers c JOIN orders o ON c.id = o.customer_id
WHERE o.total > 1000;
```

### When to Use Which

| Scenario | Recommendation |
|----------|---------------|
| Simple lookup from one table | Subquery (readable) |
| Need columns from both tables | JOIN (must use) |
| Checking existence only | EXISTS (fastest) |
| Large subquery result set | JOIN (better optimizer support) |
| Complex filtering logic | Subquery (clearer intent) |

---

<a name="q24"></a>
## Q24. What is a Window Function?

**Answer:**

A **window function** performs a calculation across a set of rows **related to the current row**, without collapsing rows like GROUP BY does. Each row retains its identity while gaining access to aggregated values.

```sql
function_name() OVER (
    [PARTITION BY column]   -- divide rows into groups
    [ORDER BY column]       -- order within each group
    [ROWS/RANGE frame]      -- define window frame
)
```

### Ranking Functions

```sql
SELECT
    name,
    dept_id,
    salary,
    ROW_NUMBER() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS row_num,
    RANK()       OVER (PARTITION BY dept_id ORDER BY salary DESC) AS rank,
    DENSE_RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) AS dense_rank
FROM employees;

-- ROW_NUMBER: unique sequential (1,2,3,4)
-- RANK:       gaps for ties (1,2,2,4)
-- DENSE_RANK: no gaps for ties (1,2,2,3)
```

### Aggregate Window Functions

```sql
-- Running total of salary ordered by hire date
SELECT
    name,
    hire_date,
    salary,
    SUM(salary) OVER (ORDER BY hire_date) AS running_total,
    AVG(salary) OVER (PARTITION BY dept_id) AS dept_avg_salary,
    salary - AVG(salary) OVER (PARTITION BY dept_id) AS diff_from_avg
FROM employees;
```

### LAG / LEAD — Access Adjacent Rows

```sql
-- Compare each month's revenue to previous month
SELECT
    month,
    revenue,
    LAG(revenue, 1)  OVER (ORDER BY month) AS prev_month,
    LEAD(revenue, 1) OVER (ORDER BY month) AS next_month,
    revenue - LAG(revenue, 1) OVER (ORDER BY month) AS month_over_month_change
FROM monthly_revenue;
```

### FIRST_VALUE / LAST_VALUE / NTH_VALUE

```sql
-- Get highest salary in dept alongside each employee row
SELECT
    name,
    salary,
    FIRST_VALUE(name) OVER (PARTITION BY dept_id ORDER BY salary DESC) AS top_earner
FROM employees;
```

### Window vs GROUP BY

```
GROUP BY:        5 rows → 2 groups → 2 result rows (rows collapsed)
Window Function: 5 rows → 5 result rows (rows preserved, extra computed column)
```

---

<a name="q25"></a>
## Q25. What is Query Optimization and EXPLAIN?

**Answer:**

**Query optimization** is the process the DBMS uses to determine the most efficient execution plan for a SQL query. The **query optimizer** evaluates multiple possible execution strategies and picks the lowest-cost one.

### Query Execution Pipeline

```
SQL Query (text)
      ↓
  [Parser]         → Syntax tree
      ↓
  [Semantic Check] → Validate tables/columns exist
      ↓
  [Query Optimizer] → Generate & evaluate execution plans
      ↓
  [Execution Engine] → Execute best plan
      ↓
  Result Set
```

### EXPLAIN / EXPLAIN ANALYZE

Use `EXPLAIN` to see the execution plan without running the query; `EXPLAIN ANALYZE` runs it and shows actual timings:

```sql
EXPLAIN SELECT e.name, d.dept_name
FROM employees e
JOIN departments d ON e.dept_id = d.id
WHERE e.salary > 80000;
```

```
┌────┬────────────┬───────────┬──────┬───────────┬────────────────────────────────┐
│ id │ table      │ type      │ key  │ rows      │ Extra                          │
├────┼────────────┼───────────┼──────┼───────────┼────────────────────────────────┤
│ 1  │ e(employees│ range     │ idx_ │ 1000      │ Using index condition          │
│ 1  │ d(depts)   │ eq_ref    │ PRI  │ 1         │                                │
└────┴────────────┴───────────┴──────┴───────────┴────────────────────────────────┘
```

### Key EXPLAIN Fields (MySQL)

| Field | What to Look For |
|-------|-----------------|
| **type** | `ALL` = full scan (bad), `ref`/`eq_ref`/`const` = good |
| **key** | Which index is being used (`NULL` = no index!) |
| **rows** | Estimated rows scanned (lower = better) |
| **Extra** | `Using filesort` / `Using temporary` = potential issues |

### Common Optimization Techniques

```sql
-- 1. Add index on filtered/joined columns
CREATE INDEX idx_salary ON employees(salary);

-- 2. Use covering index — avoid fetching from table
CREATE INDEX idx_cover ON employees(dept_id, salary, name);
SELECT name FROM employees WHERE dept_id = 10 AND salary > 50000;

-- 3. Avoid functions on indexed columns
-- ❌ Slow: function prevents index use
SELECT * FROM orders WHERE YEAR(order_date) = 2024;
-- ✅ Fast: range query uses index
SELECT * FROM orders WHERE order_date BETWEEN '2024-01-01' AND '2024-12-31';

-- 4. Avoid SELECT * — fetch only needed columns
-- ❌ SELECT * FROM employees
-- ✅ SELECT emp_id, name, salary FROM employees

-- 5. Use LIMIT for large result sets
SELECT * FROM logs ORDER BY created_at DESC LIMIT 20;
```

---

<a name="q26"></a>
## Q26. What is Sharding and Partitioning?

**Answer:**

Both techniques split data across multiple units for performance and scalability, but at different levels.

### Partitioning
Splitting a **single table** into smaller pieces **within the same database server**:

```sql
-- Range Partitioning by year (MySQL)
CREATE TABLE orders (
    order_id   INT,
    order_date DATE,
    total      DECIMAL(10,2)
)
PARTITION BY RANGE (YEAR(order_date)) (
    PARTITION p2022 VALUES LESS THAN (2023),
    PARTITION p2023 VALUES LESS THAN (2024),
    PARTITION p2024 VALUES LESS THAN (2025)
);
-- Queries with WHERE order_date = 2023 only scan p2023 partition (partition pruning)
```

| Partition Type | Based On | Example |
|----------------|----------|---------|
| **Range** | Column range | Dates, numeric ranges |
| **List** | Discrete values | Country codes, status |
| **Hash** | Hash of column value | Even distribution |
| **Composite** | Combination | Range + Hash |

### Sharding (Horizontal Partitioning across servers)
Data is split across **multiple independent database servers** (shards), each responsible for a subset of the data:

```
All Customers:
Shard 1 (DB Server 1): customer_id 1 – 1,000,000
Shard 2 (DB Server 2): customer_id 1,000,001 – 2,000,000
Shard 3 (DB Server 3): customer_id 2,000,001 – 3,000,000

Shard key: customer_id
```

### Sharding Strategies

| Strategy | Mechanism | Pro | Con |
|----------|-----------|-----|-----|
| **Range-based** | Shard by value range | Easy range queries | Hotspots if data skewed |
| **Hash-based** | Hash(key) % num_shards | Even distribution | Range queries scan all shards |
| **Directory-based** | Lookup table maps key to shard | Flexible | Lookup table bottleneck |
| **Geographic** | Shard by region | Low latency | Uneven sizes |

### Partitioning vs Sharding

| Feature | Partitioning | Sharding |
|---------|-------------|---------|
| Location | Same server | Multiple servers |
| Transparent | Yes (to app) | No (app must route) |
| Complexity | Low | High |
| Scale | Vertical | Horizontal |
| Cross-partition join | Supported | Very expensive |

---

<a name="q27"></a>
## Q27. What is Replication?

**Answer:**

**Database Replication** is the process of copying and maintaining database data across multiple servers to improve **availability, fault tolerance, and read performance**.

### Master-Replica (Primary-Secondary) Replication

```
          ┌─────────────┐
Writes ──►│   Primary   │──── replication log ────┐
          └─────────────┘                          │
                                         ┌─────────▼──────────┐
Reads ◄──────────────────────────────────│    Replica 1       │
                                         └────────────────────┘
                                         ┌────────────────────┐
Reads ◄──────────────────────────────────│    Replica 2       │
                                         └────────────────────┘
```

### Replication Types

| Type | Mechanism | Consistency | Performance |
|------|-----------|-------------|-------------|
| **Synchronous** | Primary waits for replica ACK before committing | Strong | Slower writes |
| **Asynchronous** | Primary commits immediately; replica catches up | Eventual | Faster writes |
| **Semi-Synchronous** | Wait for at least one replica ACK | Middle | Middle |

### Replication Topologies

```
Master-Slave:   Primary → Replica(s)        (most common)
Master-Master:  Primary ⇄ Primary           (both accept writes, risk of conflict)
Cascading:      Primary → Replica → Replica (reduces primary load)
```

### Use Cases

| Goal | How Replication Helps |
|------|-----------------------|
| **High Availability** | Failover to replica if primary crashes |
| **Read Scaling** | Route read queries to replicas |
| **Disaster Recovery** | Replica in different region/datacenter |
| **Analytics** | Run heavy queries on replica, no impact on primary |

### Replication Lag
In async replication, replicas may be slightly behind the primary — **replication lag**. This means:
- Reading your own write may miss the latest data
- Solution: Route reads to primary for critical operations, or use **read-your-writes consistency**

---

<a name="q28"></a>
## Q28. What is the CAP Theorem?

**Answer:**

The **CAP Theorem** (Brewer's Theorem, 2000) states that a distributed database can guarantee at most **two of three** properties simultaneously:

```
        Consistency (C)
           / \
          /   \
         /     \
        / CP   CA\
       /           \
      /─────────────\
Partition          Availability
Tolerance (P)  ────── (A)
               AP
```

### The Three Properties

**Consistency (C)**
> Every read receives the most recent write or an error — all nodes see the same data at the same time.

**Availability (A)**
> Every request receives a response (not necessarily the most recent data) — no timeout or error.

**Partition Tolerance (P)**
> The system continues operating even when network partitions (communication failures between nodes) occur.

### The Key Insight
In a real distributed system, **network partitions are unavoidable**. Therefore, the practical trade-off is:
- **CP** — choose Consistency over Availability during a partition
- **AP** — choose Availability over Consistency during a partition

### Database Classification

| Type | Examples | Trade-off |
|------|---------|-----------|
| **CP** | HBase, MongoDB (strong mode), Zookeeper | May reject reads/writes during partition |
| **AP** | Cassandra, DynamoDB, CouchDB | May return stale data |
| **CA** | Traditional RDBMS (MySQL, PostgreSQL) | Assumes no partitions (single node) |

### PACELC Theorem (Extension of CAP)
CAP only covers behavior **during partitions**. PACELC also considers the **normal operation** trade-off:

```
If Partition (P): trade-off between Availability (A) and Consistency (C)
Else (E):         trade-off between Latency (L) and Consistency (C)
```

---

<a name="q29"></a>
## Q29. What is NoSQL? Types and when to use?

**Answer:**

**NoSQL** ("Not Only SQL") refers to a broad class of database systems that store and retrieve data using models **other than relational tables**. Designed for horizontal scale, flexible schemas, and high throughput.

### Four Main Types of NoSQL Databases

#### 1. Key-Value Stores
```
Simple: key → value (value is opaque blob)

"user:1001" → { name: "Alice", age: 28, city: "Delhi" }

Use cases: Session storage, caching, shopping carts
Examples:  Redis, DynamoDB, Memcached
```

#### 2. Document Stores
```json
Flexible JSON/BSON documents — schema-free

{
  "_id": "order_12345",
  "customer": { "id": 1001, "name": "Alice" },
  "items": [
    { "product": "Laptop", "qty": 1, "price": 75000 },
    { "product": "Mouse",  "qty": 2, "price": 1500  }
  ],
  "total": 78000,
  "status": "shipped"
}

Use cases: Content management, catalogs, user profiles
Examples:  MongoDB, CouchDB, Firestore
```

#### 3. Column-Family (Wide Column) Stores
```
Rows with dynamic columns — optimized for reads/writes of specific columns

Row Key   │ Column Family: info       │ Column Family: stats
──────────┼───────────────────────────┼─────────────────────────
user:1001 │ name=Alice, city=Delhi    │ login_count=142, last_login=...
user:1002 │ name=Bob                  │ login_count=8

Use cases: Time-series, analytics, IoT sensor data, write-heavy
Examples:  Cassandra, HBase, Google Bigtable
```

#### 4. Graph Databases
```
Nodes (entities) + Edges (relationships) + Properties

(Alice)-[:FOLLOWS]->(Bob)
(Alice)-[:LIKES]->(Post:123)
(Bob)-[:AUTHORED]->(Post:123)

Use cases: Social networks, recommendation engines, fraud detection, knowledge graphs
Examples:  Neo4j, Amazon Neptune, ArangoDB
```

### Comparison

| Type | Data Model | Strengths | Weaknesses |
|------|-----------|-----------|------------|
| Key-Value | Hash map | Ultra-fast, simple | No queries on values |
| Document | JSON tree | Flexible schema, rich queries | Joins are hard |
| Column-Family | Wide columns | Write-heavy, time-series | Complex data modeling |
| Graph | Nodes + Edges | Relationship traversal | Not for simple lookups |

---

<a name="q30"></a>
## Q30. SQL vs NoSQL — When to use which?

**Answer:**

Choosing between SQL and NoSQL is a **design decision** based on data structure, scale, consistency needs, and query patterns — not a matter of one being "better."

### Detailed Comparison

```
┌─────────────────────┬──────────────────────────┬──────────────────────────────┐
│ Feature             │ SQL (Relational)          │ NoSQL                        │
├─────────────────────┼──────────────────────────┼──────────────────────────────┤
│ Schema              │ Fixed, predefined         │ Dynamic, flexible            │
│ Data model          │ Tables with rows/columns  │ Documents, K-V, Graph, etc.  │
│ Relationships       │ Foreign keys, JOINs       │ Embedded or application-side │
│ ACID                │ Full support              │ Varies (some BASE instead)   │
│ Horizontal scaling  │ Hard (sharding is complex)│ Built-in, native             │
│ Query language      │ SQL (standardized)        │ API-specific, varies         │
│ Consistency         │ Strong (ACID)             │ Often eventual               │
│ Joins               │ Native, optimized         │ Generally not supported      │
│ Write performance   │ Moderate                  │ Very high                    │
│ Read performance    │ High (with indexes)       │ Very high (simple queries)   │
│ Maturity            │ 50+ years                 │ 15–20 years                  │
└─────────────────────┴──────────────────────────┴──────────────────────────────┘
```

### Decision Guide

**Use SQL (Relational) when:**
```
✅ Data is highly structured with clear relationships
✅ ACID compliance is critical (banking, finance, ERP)
✅ Complex queries, reporting, analytics with JOINs
✅ Data integrity is paramount
✅ Team knows SQL well
✅ Medium scale — fits vertically (or manageable sharding)
Examples: Banking system, ERP, e-commerce (orders/inventory)
```

**Use NoSQL when:**
```
✅ Schema changes frequently or is unpredictable
✅ Massive scale — millions of writes/reads per second
✅ Horizontal scaling is required
✅ Simple access patterns (lookup by key, document fetch)
✅ Storing semi-structured/unstructured data (JSON, logs)
✅ Eventual consistency is acceptable
Examples: Social media feeds, real-time analytics, IoT, caching
```

### Hybrid (Polyglot Persistence) — Modern Best Practice
```
E-Commerce System:
├── PostgreSQL    → Orders, Payments, Inventory (ACID critical)
├── MongoDB       → Product catalog (flexible schema, rich docs)
├── Redis         → Sessions, caching, rate limiting (ultra-fast)
├── Elasticsearch → Product search, full-text (search optimized)
└── Neo4j         → "Customers also bought" recommendations (graph)
```

### BASE vs ACID

| | ACID (SQL) | BASE (NoSQL) |
|-|-----------|-------------|
| Full form | Atomicity, Consistency, Isolation, Durability | Basically Available, Soft state, Eventually consistent |
| Consistency | Immediate | Eventual |
| Availability | May sacrifice during partition | Always available |
| Use case | Financial, critical data | High-scale, tolerance for stale reads |

---

## 📌 Quick Revision Cheat Sheet

```
┌──────────────────────────────────────────────────────────────────────────┐
│                        DBMS — At a Glance                                │
├──────────────────────────┬───────────────────────────────────────────────┤
│ Keys                     │ PK (unique+notnull), FK, CK, SK, Composite    │
│ SQL Types                │ DDL, DML, DCL, TCL                            │
│ Joins                    │ INNER, LEFT, RIGHT, FULL, CROSS, SELF         │
│ Normalization            │ 1NF→2NF→3NF→BCNF→4NF→5NF                    │
│ ACID                     │ Atomicity, Consistency, Isolation, Durability  │
│ Isolation Levels         │ RU < RC < RR < Serializable                   │
│ Anomalies                │ Dirty Read, Non-Repeatable, Phantom            │
│ Locks                    │ Shared (read), Exclusive (write), 2PL          │
│ Deadlock                 │ Circular wait → victim rollback, lock ordering │
│ Index types              │ Clustered, Non-Clustered, Composite, Covering  │
│ B+ Tree                  │ O(log n) search, linked leaves = fast range    │
│ View                     │ Virtual table, no storage (unless materialized)│
│ Stored Proc vs Func      │ Proc=no return, Func=must return, used in SQL  │
│ Trigger                  │ BEFORE/AFTER INSERT/UPDATE/DELETE              │
│ Window Functions         │ ROW_NUMBER, RANK, LAG/LEAD, SUM OVER()        │
│ EXPLAIN                  │ type=ALL (bad), key=NULL (no index!), rows     │
│ Sharding                 │ Horizontal split across servers (range/hash)   │
│ Replication              │ Primary→Replica, sync vs async, read scaling   │
│ CAP Theorem              │ Only 2 of 3: Consistency/Availability/Partition│
│ NoSQL types              │ K-V, Document, Column, Graph                   │
│ SQL vs NoSQL             │ ACID+JOINs vs Scale+Flexibility                │
└──────────────────────────┴───────────────────────────────────────────────┘
```

---

> 💡 **Pro Interview Tips:**
> - Always explain **ACID** with the bank transfer analogy — interviewers love it
> - For **normalization**, know 1NF–BCNF with examples of what anomaly each solves
> - **Index internals** (B+ Tree, clustered vs non-clustered) are very commonly asked at senior levels
> - Know the difference between **RANK vs DENSE_RANK vs ROW_NUMBER** — a very common SQL round question
> - **CAP Theorem** + NoSQL types are standard in system design rounds
> - Always run `EXPLAIN` before optimizing — never guess

---

*Happy Querying & Good Luck with your Interview! 🚀*
