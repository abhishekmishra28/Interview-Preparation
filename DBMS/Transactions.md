# DATABASE TRANSACTIONS & ACID PROPERTIES — INTERVIEW SUMMARY

## 1. What is a Transaction?
A transaction is a group of one or more database operations executed as a single logical unit of work.

A transaction ensures:
- data consistency
- reliability
- correctness

Either:
- ALL operations succeed
OR
- NONE of them are applied

---

## 2. Real-Life Example

### Bank Transfer Example
Suppose:
- ₹1000 transferred from Account A → Account B

Operations:
```sql
UPDATE accounts
SET balance = balance - 1000
WHERE id = 1;

UPDATE accounts
SET balance = balance + 1000
WHERE id = 2;
```

If system crashes after deducting money from A but before adding to B:
- database becomes inconsistent

Transactions prevent this problem.

---

## 3. Transaction Commands

### BEGIN TRANSACTION
Starts a transaction.

```sql
BEGIN;
```

### COMMIT
Permanently saves all changes.

```sql
COMMIT;
```

### ROLLBACK
Undo all changes if error occurs.

```sql
ROLLBACK;
```

---

## 4. ACID Properties

ACID properties ensure reliable transaction processing.

---

# A — Atomicity

### Definition
A transaction is treated as a single indivisible unit.

Either:
- all operations execute successfully
OR
- none execute

### Example
Bank transfer:
- debit money
- credit money

If one step fails:
- entire transaction rolls back

### Key Idea
```text
ALL or NOTHING
```

---

# C — Consistency

### Definition
Transaction must move database from one valid state to another valid state.

Database rules and constraints should never break.

### Example
If total bank balance before transaction:
```text
₹10,000
```

After transaction:
```text
₹10,000
```

Money should neither disappear nor get created accidentally.

### Key Idea
```text
Data integrity is maintained
```

---

# I — Isolation

### Definition
Multiple transactions should not interfere with each other.

Transactions execute independently.

### Example
Two users booking same seat simultaneously.

Without isolation:
- both may get same seat

Isolation prevents such conflicts.

### Key Idea
```text
Concurrent transactions behave safely
```

---

# D — Durability

### Definition
Once transaction is committed, changes remain permanent even after:
- crash
- power failure
- restart

### Example
After successful payment:
- data should remain saved permanently

### Key Idea
```text
Committed data survives failures
```

---

## 5. Transaction Lifecycle

```text
BEGIN
   ↓
Execute Queries
   ↓
COMMIT → Save permanently
OR
ROLLBACK → Undo changes
```

---

## 6. Example Transaction

```sql
BEGIN;

UPDATE accounts
SET balance = balance - 1000
WHERE id = 1;

UPDATE accounts
SET balance = balance + 1000
WHERE id = 2;

COMMIT;
```

If any query fails:
```sql
ROLLBACK;
```

---

## 7. Problems Without Transactions

Without transactions:
- partial updates
- inconsistent data
- duplicate operations
- lost updates
- corruption

---

## 8. Concurrency Problems

### A. Dirty Read
Reading uncommitted data from another transaction.

### B. Non-Repeatable Read
Same query gives different result inside same transaction.

### C. Phantom Read
New rows appear during same transaction execution.

---

## 9. Isolation Levels

Databases provide different isolation levels.

### Read Uncommitted
- Fastest
- Least safe

### Read Committed
- Prevents dirty reads

### Repeatable Read
- Prevents non-repeatable reads

### Serializable
- Highest isolation
- Slowest but safest

---

## 10. Why Transactions are Important

Transactions are critical in:
- banking systems
- payment gateways
- e-commerce
- ticket booking
- inventory systems

Anywhere data consistency matters.

---

## 11. Important Interview Questions

### Q1. What is a transaction?
A logical unit of work containing one or more database operations executed together.

---

### Q2. What is Atomicity?
Either all operations succeed or none execute.

---

### Q3. Difference Between COMMIT and ROLLBACK?

| COMMIT | ROLLBACK |
|---|---|
| Saves changes permanently | Undoes changes |
| Successful transaction | Failed transaction |

---

### Q4. Why is Isolation important?
Prevents concurrent transactions from interfering with each other.

---

### Q5. What is Durability?
Committed data remains permanent even after system failure.

---

## 12. Golden Interview Line

> “Transactions ensure reliable and consistent database operations using ACID properties — Atomicity, Consistency, Isolation, and Durability — so that concurrent operations execute safely and data integrity is preserved even during failures.”
