# Complete DBMS & SQL Guide - A to Z

## Table of Contents
- [Database Fundamentals](#database-fundamentals)
- [DBMS Architecture](#dbms-architecture)
- [Data Models](#data-models)
- [Relational Model](#relational-model)
- [SQL Basics](#sql-basics)
- [SQL Advanced](#sql-advanced)
- [Normalization](#normalization)
- [Transactions](#transactions)
- [Concurrency Control](#concurrency-control)
- [Indexing](#indexing)
- [Keys & Constraints](#keys--constraints)
- [Joins](#joins)
- [Functions & Procedures](#functions--procedures)
- [Query Optimization](#query-optimization)
- [ACID Properties](#acid-properties)
- [Database Design](#database-design)
- [Interview Questions](#interview-questions)

---

# Database Fundamentals

## What is Database?

**Database:** Organized collection of structured data stored electronically.

**Example:**
```
Student Database:
- Student records
- Course information
- Enrollment data
```

## What is DBMS?

**DBMS (Database Management System):** Software to create, manage, and manipulate databases.

**Examples:** MySQL, PostgreSQL, Oracle, MongoDB

**Advantages:**
- Data independence
- Efficient data access
- Data integrity and security
- Concurrent access
- Crash recovery
- Reduced redundancy

## File System vs DBMS

| Feature | File System | DBMS |
|---------|-------------|------|
| **Data Redundancy** | High | Low |
| **Data Consistency** | Low | High |
| **Data Isolation** | Difficult | Easy |
| **Security** | Limited | Strong |
| **Concurrent Access** | No | Yes |
| **Backup & Recovery** | Manual | Automated |

---

# DBMS Architecture

## 1-Tier Architecture

```
User ↔ Database
```
- Direct interaction
- Used for local applications
- Example: MS Access

## 2-Tier Architecture

```
Client (UI) ↔ Database Server
```
- Client-server model
- Business logic on client or server
- Example: Desktop applications

## 3-Tier Architecture

```
Client (UI) ↔ Application Server ↔ Database Server
```
- Presentation tier (UI)
- Application tier (Business logic)
- Data tier (Database)
- Example: Web applications

## Schema Levels

### 1. External Schema (View Level)
- User view of database
- Different users see different views
```sql
CREATE VIEW student_grades AS
SELECT name, course, grade FROM students;
```

### 2. Conceptual Schema (Logical Level)
- Overall logical structure
- Tables, relationships, constraints
```sql
CREATE TABLE Students (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    age INT
);
```

### 3. Internal Schema (Physical Level)
- Physical storage structure
- Indexes, file organization
- How data is actually stored on disk

## Data Independence

**Logical Independence:** Changes to logical schema don't affect external schema  
**Physical Independence:** Changes to physical schema don't affect logical schema

---

# Data Models

## Hierarchical Model

```
        Company
       /       \
   Dept1      Dept2
   /    \      /   \
 E1    E2    E3   E4
```
- Tree structure
- One-to-many relationships
- Example: IMS by IBM

## Network Model

```
Dept1 ← Employee1 → Project1
  ↓         ↓           ↓
Dept2 ← Employee2 → Project2
```
- Graph structure
- Many-to-many relationships
- More complex than hierarchical

## Relational Model

**Most popular model**

```
Students Table:
+----+-------+-----+
| ID | Name  | Age |
+----+-------+-----+
| 1  | Alice | 20  |
| 2  | Bob   | 22  |
+----+-------+-----+
```
- Data in tables (relations)
- Rows (tuples) and columns (attributes)
- SQL for querying

## Object-Oriented Model

- Data stored as objects
- Supports inheritance, encapsulation
- Used in complex applications

---

# Relational Model

## Key Concepts

**Relation:** Table  
**Tuple:** Row  
**Attribute:** Column  
**Degree:** Number of attributes  
**Cardinality:** Number of tuples  

**Example:**
```
Employee (ID, Name, Dept, Salary)
Degree = 4, Cardinality = 100 (if 100 employees)
```

## Relational Algebra

### Selection (σ)
Select rows satisfying condition
```
σ age>20 (Students)
```

### Projection (π)
Select specific columns
```
π name, age (Students)
```

### Union (∪)
Combine two relations
```
R ∪ S
```

### Set Difference (−)
Tuples in R but not in S
```
R − S
```

### Cartesian Product (×)
All combinations
```
R × S
```

### Join (⋈)
Combine based on condition
```
Students ⋈ Enrollments
```

---

# SQL Basics

## Data Types

```sql
-- Numeric
INT, SMALLINT, BIGINT
DECIMAL(10,2), FLOAT, DOUBLE

-- String
CHAR(10)      -- Fixed length
VARCHAR(100)  -- Variable length
TEXT          -- Large text

-- Date/Time
DATE          -- YYYY-MM-DD
TIME          -- HH:MM:SS
DATETIME      -- YYYY-MM-DD HH:MM:SS
TIMESTAMP     -- Auto-updated

-- Boolean
BOOLEAN       -- TRUE/FALSE
```

## DDL (Data Definition Language)

### CREATE
```sql
-- Create Database
CREATE DATABASE company;

-- Create Table
CREATE TABLE employees (
    emp_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    dept VARCHAR(50),
    salary DECIMAL(10,2),
    hire_date DATE DEFAULT CURRENT_DATE
);
```

### ALTER
```sql
-- Add Column
ALTER TABLE employees ADD email VARCHAR(100);

-- Modify Column
ALTER TABLE employees MODIFY salary DECIMAL(12,2);

-- Drop Column
ALTER TABLE employees DROP COLUMN email;

-- Rename Column
ALTER TABLE employees RENAME COLUMN name TO emp_name;
```

### DROP & TRUNCATE
```sql
-- Drop Table (remove structure + data)
DROP TABLE employees;

-- Truncate (remove data, keep structure)
TRUNCATE TABLE employees;
```

## DML (Data Manipulation Language)

### INSERT
```sql
-- Insert single row
INSERT INTO employees (name, dept, salary)
VALUES ('John', 'IT', 50000);

-- Insert multiple rows
INSERT INTO employees VALUES
(1, 'Alice', 'HR', 45000, '2023-01-15'),
(2, 'Bob', 'IT', 55000, '2023-02-20');

-- Insert from SELECT
INSERT INTO new_employees
SELECT * FROM employees WHERE dept = 'IT';
```

### SELECT
```sql
-- Basic SELECT
SELECT * FROM employees;
SELECT name, salary FROM employees;

-- WHERE Clause
SELECT * FROM employees WHERE salary > 50000;
SELECT * FROM employees WHERE dept = 'IT' AND salary > 45000;

-- DISTINCT
SELECT DISTINCT dept FROM employees;

-- ORDER BY
SELECT * FROM employees ORDER BY salary DESC;
SELECT * FROM employees ORDER BY dept ASC, salary DESC;

-- LIMIT
SELECT * FROM employees LIMIT 5;
SELECT * FROM employees LIMIT 5 OFFSET 10;  -- Skip 10, get 5
```

### UPDATE
```sql
-- Update single column
UPDATE employees SET salary = 55000 WHERE emp_id = 1;

-- Update multiple columns
UPDATE employees 
SET salary = salary * 1.1, dept = 'IT'
WHERE emp_id = 2;

-- Update all rows
UPDATE employees SET salary = salary * 1.05;
```

### DELETE
```sql
-- Delete specific rows
DELETE FROM employees WHERE emp_id = 1;

-- Delete with condition
DELETE FROM employees WHERE salary < 30000;

-- Delete all rows (but slower than TRUNCATE)
DELETE FROM employees;
```

## DCL (Data Control Language)

```sql
-- Grant permissions
GRANT SELECT, INSERT ON employees TO user1;
GRANT ALL PRIVILEGES ON database.* TO user1;

-- Revoke permissions
REVOKE INSERT ON employees FROM user1;
```

## TCL (Transaction Control Language)

```sql
-- Start transaction
START TRANSACTION;

-- Commit changes
COMMIT;

-- Rollback changes
ROLLBACK;

-- Savepoint
SAVEPOINT sp1;
ROLLBACK TO sp1;
```

---

# SQL Advanced

## Aggregate Functions

```sql
-- COUNT
SELECT COUNT(*) FROM employees;
SELECT COUNT(DISTINCT dept) FROM employees;

-- SUM
SELECT SUM(salary) FROM employees;

-- AVG
SELECT AVG(salary) FROM employees;

-- MIN/MAX
SELECT MIN(salary), MAX(salary) FROM employees;

-- GROUP BY
SELECT dept, COUNT(*), AVG(salary)
FROM employees
GROUP BY dept;

-- HAVING (filter after GROUP BY)
SELECT dept, AVG(salary) as avg_sal
FROM employees
GROUP BY dept
HAVING avg_sal > 50000;
```

## String Functions

```sql
-- CONCAT
SELECT CONCAT(first_name, ' ', last_name) as full_name FROM employees;

-- UPPER/LOWER
SELECT UPPER(name), LOWER(dept) FROM employees;

-- SUBSTRING
SELECT SUBSTRING(name, 1, 3) FROM employees;

-- LENGTH
SELECT name, LENGTH(name) FROM employees;

-- TRIM
SELECT TRIM('  hello  ');  -- 'hello'

-- REPLACE
SELECT REPLACE(name, 'a', 'A') FROM employees;
```

## Date Functions

```sql
-- Current date/time
SELECT NOW(), CURDATE(), CURTIME();

-- Extract parts
SELECT YEAR(hire_date), MONTH(hire_date), DAY(hire_date)
FROM employees;

-- Date arithmetic
SELECT DATE_ADD(hire_date, INTERVAL 1 YEAR) FROM employees;
SELECT DATEDIFF(NOW(), hire_date) as days_employed FROM employees;

-- Format date
SELECT DATE_FORMAT(hire_date, '%Y-%m-%d') FROM employees;
```

## Subqueries

```sql
-- Subquery in WHERE
SELECT name FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees);

-- Subquery in FROM
SELECT dept, avg_salary
FROM (SELECT dept, AVG(salary) as avg_salary 
      FROM employees 
      GROUP BY dept) as dept_avg;

-- Correlated subquery
SELECT e1.name, e1.salary
FROM employees e1
WHERE salary > (SELECT AVG(salary) 
                FROM employees e2 
                WHERE e1.dept = e2.dept);

-- EXISTS
SELECT name FROM employees e
WHERE EXISTS (SELECT 1 FROM projects p WHERE p.emp_id = e.emp_id);

-- IN
SELECT name FROM employees
WHERE dept IN ('IT', 'HR', 'Finance');
```

## CASE Statement

```sql
SELECT name, salary,
    CASE 
        WHEN salary < 30000 THEN 'Low'
        WHEN salary BETWEEN 30000 AND 60000 THEN 'Medium'
        ELSE 'High'
    END as salary_grade
FROM employees;
```

## Window Functions

```sql
-- ROW_NUMBER
SELECT name, salary,
       ROW_NUMBER() OVER (ORDER BY salary DESC) as rank
FROM employees;

-- RANK (allows ties)
SELECT name, salary,
       RANK() OVER (ORDER BY salary DESC) as rank
FROM employees;

-- DENSE_RANK (no gaps in ranking)
SELECT name, salary,
       DENSE_RANK() OVER (ORDER BY salary DESC) as rank
FROM employees;

-- PARTITION BY
SELECT name, dept, salary,
       ROW_NUMBER() OVER (PARTITION BY dept ORDER BY salary DESC) as dept_rank
FROM employees;

-- Running total
SELECT name, salary,
       SUM(salary) OVER (ORDER BY hire_date) as running_total
FROM employees;

-- LAG and LEAD
SELECT name, salary,
       LAG(salary) OVER (ORDER BY hire_date) as prev_salary,
       LEAD(salary) OVER (ORDER BY hire_date) as next_salary
FROM employees;
```

## Common Table Expressions (CTE)

```sql
-- Basic CTE
WITH high_earners AS (
    SELECT * FROM employees WHERE salary > 60000
)
SELECT dept, COUNT(*) FROM high_earners GROUP BY dept;

-- Recursive CTE (hierarchy)
WITH RECURSIVE employee_hierarchy AS (
    -- Anchor member
    SELECT emp_id, name, manager_id, 1 as level
    FROM employees
    WHERE manager_id IS NULL
    
    UNION ALL
    
    -- Recursive member
    SELECT e.emp_id, e.name, e.manager_id, eh.level + 1
    FROM employees e
    INNER JOIN employee_hierarchy eh ON e.manager_id = eh.emp_id
)
SELECT * FROM employee_hierarchy;
```

---

# Normalization

## Purpose
- Eliminate redundancy
- Avoid update anomalies
- Improve data integrity

## 1NF (First Normal Form)

**Rules:**
- Atomic values (no multivalued attributes)
- No repeating groups

**Violation:**
```
Student (ID, Name, Courses)
1, Alice, "Math, Physics"  ❌
```

**1NF:**
```
Student (ID, Name, Course)
1, Alice, Math
1, Alice, Physics  ✓
```

## 2NF (Second Normal Form)

**Rules:**
- Must be in 1NF
- No partial dependency (non-prime attributes fully dependent on primary key)

**Violation:**
```
StudentCourse (StudentID, CourseID, StudentName, CourseName)
PK: (StudentID, CourseID)
StudentName depends only on StudentID (partial dependency)  ❌
```

**2NF:**
```
Student (StudentID, StudentName)
Course (CourseID, CourseName)
Enrollment (StudentID, CourseID)  ✓
```

## 3NF (Third Normal Form)

**Rules:**
- Must be in 2NF
- No transitive dependency

**Violation:**
```
Employee (EmpID, EmpName, DeptID, DeptName)
EmpID → DeptID → DeptName (transitive)  ❌
```

**3NF:**
```
Employee (EmpID, EmpName, DeptID)
Department (DeptID, DeptName)  ✓
```

## BCNF (Boyce-Codd Normal Form)

**Rules:**
- Must be in 3NF
- For every functional dependency X→Y, X must be a super key

**Example:**
```
StudentAdvisor (StudentID, Subject, Advisor)
FD: (StudentID, Subject) → Advisor
FD: Advisor → Subject

If one advisor teaches only one subject:
Advisor → Subject violates BCNF
```

**BCNF:**
```
StudentAdvisor (StudentID, Advisor)
AdvisorSubject (Advisor, Subject)
```

## 4NF (Fourth Normal Form)

**Rules:**
- Must be in BCNF
- No multivalued dependencies

**Example:**
```
Student (StudentID, Course, Hobby)
One student can have multiple courses and hobbies independently
```

**4NF:**
```
StudentCourse (StudentID, Course)
StudentHobby (StudentID, Hobby)
```

---

# Transactions

## What is Transaction?

**Transaction:** Logical unit of work (sequence of operations)

**Example:**
```sql
START TRANSACTION;

UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;

COMMIT;
```

## Transaction States

```
Active → Partially Committed → Committed
  ↓
Failed → Aborted
```

**States:**
1. **Active:** Transaction executing
2. **Partially Committed:** After final statement
3. **Committed:** Successfully completed
4. **Failed:** Cannot proceed
5. **Aborted:** Rolled back

## Transaction Properties

### Example Scenario
```sql
-- Bank transfer: A transfers $100 to B

START TRANSACTION;

-- Step 1: Deduct from A
UPDATE accounts SET balance = balance - 100 WHERE account_id = 'A';

-- Step 2: Add to B  
UPDATE accounts SET balance = balance + 100 WHERE account_id = 'B';

COMMIT;
```

---

# Concurrency Control

## Problems Without Concurrency Control

### 1. Lost Update
```
T1: Read X (100)
T2: Read X (100)
T1: X = X + 50 = 150
T2: X = X + 30 = 130
T1: Write X (150)
T2: Write X (130)  ← T1's update lost!
```

### 2. Dirty Read
```
T1: Write X = 100
T2: Read X (100)   ← Reads uncommitted data
T1: ROLLBACK       ← T2 read dirty data!
```

### 3. Unrepeatable Read
```
T1: Read X (100)
T2: Update X = 200
T2: COMMIT
T1: Read X (200)   ← Different value in same transaction!
```

### 4. Phantom Read
```
T1: SELECT COUNT(*) WHERE age > 20  → 5 rows
T2: INSERT new row WHERE age = 25
T2: COMMIT
T1: SELECT COUNT(*) WHERE age > 20  → 6 rows ← Phantom!
```

## Locking Mechanisms

### Shared Lock (S)
- Read lock
- Multiple transactions can hold
```sql
SELECT * FROM accounts WHERE id = 1 LOCK IN SHARE MODE;
```

### Exclusive Lock (X)
- Write lock
- Only one transaction can hold
```sql
SELECT * FROM accounts WHERE id = 1 FOR UPDATE;
```

### Lock Compatibility Matrix
```
       S    X
S     ✓    ✗
X     ✗    ✗
```

## Two-Phase Locking (2PL)

**Phases:**
1. **Growing Phase:** Acquire locks, no release
2. **Shrinking Phase:** Release locks, no acquire

**Example:**
```
T1: Lock(A)  ← Growing
T1: Lock(B)  ← Growing
T1: Unlock(A) ← Shrinking
T1: Unlock(B) ← Shrinking
```

**Problem:** Can cause deadlock

## Deadlock

**Example:**
```
T1: Lock(A)
T2: Lock(B)
T1: Wait for Lock(B)  ← Blocked by T2
T2: Wait for Lock(A)  ← Blocked by T1
DEADLOCK!
```

**Detection:** Wait-for graph has cycle

**Prevention:**
- Lock all resources at once
- Ordered locking
- Timeouts

**Resolution:**
- Abort one transaction
- Rollback and restart

## Isolation Levels

```sql
-- Read Uncommitted (lowest isolation)
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
-- Allows: Dirty reads, unrepeatable reads, phantom reads

-- Read Committed
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
-- Prevents: Dirty reads
-- Allows: Unrepeatable reads, phantom reads

-- Repeatable Read
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
-- Prevents: Dirty reads, unrepeatable reads
-- Allows: Phantom reads

-- Serializable (highest isolation)
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
-- Prevents: All anomalies
```

---

# Indexing

## What is Index?

**Index:** Data structure to speed up data retrieval

**Example:**
```sql
CREATE INDEX idx_employee_name ON employees(name);
```

**Analogy:** Like index in a book - helps find information quickly

## Types of Indexes

### 1. Primary Index
- On primary key
- Automatically created
- Unique values

### 2. Clustered Index
- Physical order of data matches index order
- One per table
- Primary key is clustered by default

### 3. Non-Clustered Index
- Separate structure from data
- Pointers to actual data
- Multiple allowed per table

### 4. Unique Index
- Ensures uniqueness
```sql
CREATE UNIQUE INDEX idx_email ON employees(email);
```

### 5. Composite Index
- Multiple columns
```sql
CREATE INDEX idx_name_dept ON employees(name, dept);
```

### 6. Full-Text Index
- For text search
```sql
CREATE FULLTEXT INDEX idx_description ON products(description);
```

## Index Structures

### B-Tree Index
```
         [50]
       /      \
   [20,30]    [70,80]
   /  |  \    /  |  \
  10 25 35  60 75 90
```
- Balanced tree
- Good for range queries
- Default in most DBMS

### Hash Index
```
Hash(key) → Bucket → Data
```
- Fast for equality searches
- Not for range queries

### Bitmap Index
```
Gender Index:
Male:   1001010
Female: 0110101
```
- Good for low-cardinality columns
- Used in data warehousing

## When to Use Indexes

**Create Index:**
- Columns in WHERE clause
- Columns in JOIN conditions
- Columns in ORDER BY
- Foreign keys

**Avoid Index:**
- Small tables
- Frequently updated columns
- Low-cardinality columns (few unique values)

**Trade-offs:**
- ✅ Faster SELECT
- ❌ Slower INSERT/UPDATE/DELETE
- ❌ Extra storage space

---

# Keys & Constraints

## Types of Keys

### 1. Super Key
- Set of attributes that uniquely identifies tuple
- Example: {StudentID}, {StudentID, Name}

### 2. Candidate Key
- Minimal super key
- Example: {StudentID}, {Email}

### 3. Primary Key
- Selected candidate key
- Cannot be NULL
- Only one per table
```sql
CREATE TABLE students (
    id INT PRIMARY KEY,
    name VARCHAR(100)
);
```

### 4. Foreign Key
- References primary key of another table
```sql
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    FOREIGN KEY (student_id) REFERENCES students(id)
);
```

### 5. Composite Key
- Primary key with multiple columns
```sql
CREATE TABLE enrollments (
    student_id INT,
    course_id INT,
    PRIMARY KEY (student_id, course_id)
);
```

### 6. Alternate Key
- Candidate keys not chosen as primary key

### 7. Unique Key
- Ensures uniqueness, can be NULL
```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    email VARCHAR(100) UNIQUE
);
```

## Constraints

### NOT NULL
```sql
CREATE TABLE employees (
    id INT NOT NULL,
    name VARCHAR(100) NOT NULL
);
```

### UNIQUE
```sql
CREATE TABLE users (
    email VARCHAR(100) UNIQUE
);
```

### CHECK
```sql
CREATE TABLE employees (
    age INT CHECK (age >= 18),
    salary DECIMAL CHECK (salary > 0)
);
```

### DEFAULT
```sql
CREATE TABLE orders (
    order_date DATE DEFAULT CURRENT_DATE,
    status VARCHAR(20) DEFAULT 'pending'
);
```

### Foreign Key Actions

```sql
CREATE TABLE orders (
    id INT PRIMARY KEY,
    customer_id INT,
    FOREIGN KEY (customer_id) REFERENCES customers(id)
        ON DELETE CASCADE        -- Delete orders when customer deleted
        ON UPDATE CASCADE        -- Update orders when customer id updated
);

-- Other options:
-- ON DELETE SET NULL
-- ON DELETE NO ACTION (default)
-- ON DELETE RESTRICT
```

---

# Joins

## INNER JOIN

Returns matching rows from both tables

```sql
SELECT e.name, d.dept_name
FROM employees e
INNER JOIN departments d ON e.dept_id = d.id;
```

**Example:**
```
Employees:           Departments:
+----+------+--------+   +----+-----------+
| ID | Name | DeptID |   | ID | DeptName  |
+----+------+--------+   +----+-----------+
| 1  | Alice| 10     |   | 10 | IT        |
| 2  | Bob  | 20     |   | 20 | HR        |
| 3  | Carol| 10     |   | 30 | Finance   |
+----+------+--------+   +----+-----------+

Result:
+---------+------------+
| Name    | DeptName   |
+---------+------------+
| Alice   | IT         |
| Bob     | HR         |
| Carol   | IT         |
+---------+------------+
```

## LEFT JOIN (LEFT OUTER JOIN)

Returns all from left table, matching from right

```sql
SELECT e.name, d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.id;
```

**Result includes:**
- All employees
- NULL for dept_name if no match

## RIGHT JOIN (RIGHT OUTER JOIN)

Returns all from right table, matching from left

```sql
SELECT e.name, d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.id;
```

## FULL OUTER JOIN

Returns all rows from both tables

```sql
SELECT e.name, d.dept_name
FROM employees e
FULL OUTER JOIN departments d ON e.dept_id = d.id;
```

## CROSS JOIN

Cartesian product of both tables

```sql
SELECT e.name, d.dept_name
FROM employees e
CROSS JOIN departments d;
```

**Result:** Every employee with every department

## SELF JOIN

Table joined with itself

```sql
SELECT e1.name as Employee, e2.name as Manager
FROM employees e1
JOIN employees e2 ON e1.manager_id = e2.id;
```

---

# Functions & Procedures

## Stored Procedures

```sql
-- Create procedure
DELIMITER //
CREATE PROCEDURE GetEmployeesByDept(IN dept_name VARCHAR(50))
BEGIN
    SELECT * FROM employees WHERE dept = dept_name;
END //
DELIMITER ;

-- Call procedure
CALL GetEmployeesByDept('IT');

-- Procedure with OUT parameter
DELIMITER //
CREATE PROCEDURE GetEmployeeCount(IN dept_name VARCHAR(50), OUT emp_count INT)
BEGIN
    SELECT COUNT(*) INTO emp_count 
    FROM employees 
    WHERE dept = dept_name;
END //
DELIMITER ;

-- Call
CALL GetEmployeeCount('IT', @count);
SELECT @count;
```

## Functions

```sql
-- Create function
DELIMITER //
CREATE FUNCTION CalculateBonus(salary DECIMAL) 
RETURNS DECIMAL
DETERMINISTIC
BEGIN
    DECLARE bonus DECIMAL;
    IF salary < 50000 THEN
        SET bonus = salary * 0.1;
    ELSE
        SET bonus = salary * 0.15;
    END IF;
    RETURN bonus;
END //
DELIMITER ;

-- Use function
SELECT name, salary, CalculateBonus(salary) as bonus
FROM employees;
```

## Triggers

```sql
-- Create trigger
DELIMITER //
CREATE TRIGGER before_employee_insert
BEFORE INSERT ON employees
FOR EACH ROW
BEGIN
    IF NEW.salary < 0 THEN
        SET NEW.salary = 0;
    END IF;
END //
DELIMITER ;

-- Audit trigger
CREATE TRIGGER after_employee_update
AFTER UPDATE ON employees
FOR EACH ROW
BEGIN
    INSERT INTO audit_log (emp_id, old_salary, new_salary, change_date)
    VALUES (NEW.id, OLD.salary, NEW.salary, NOW());
END //
DELIMITER ;
```

## Views

```sql
-- Create view
CREATE VIEW high_earners AS
SELECT name, dept, salary
FROM employees
WHERE salary > 60000;

-- Use view
SELECT * FROM high_earners WHERE dept = 'IT';

-- Updatable view
CREATE VIEW it_employees AS
SELECT * FROM employees WHERE dept = 'IT'
WITH CHECK OPTION;  -- Ensures updates maintain WHERE condition

-- Materialized view (PostgreSQL)
CREATE MATERIALIZED VIEW dept_summary AS
SELECT dept, COUNT(*) as emp_count, AVG(salary) as avg_salary
FROM employees
GROUP BY dept;

-- Refresh materialized view
REFRESH MATERIALIZED VIEW dept_summary;
```

---

# Query Optimization

## Explain Plan

```sql
EXPLAIN SELECT * FROM employees WHERE dept = 'IT';

EXPLAIN ANALYZE 
SELECT e.name, d.dept_name
FROM employees e
JOIN departments d ON e.dept_id = d.id;
```

## Optimization Techniques

### 1. Use Indexes
```sql
-- Bad
SELECT * FROM employees WHERE YEAR(hire_date) = 2023;

-- Good
CREATE INDEX idx_hire_date ON employees(hire_date);
SELECT * FROM employees WHERE hire_date >= '2023-01-01' AND hire_date < '2024-01-01';
```

### 2. Avoid SELECT *
```sql
-- Bad
SELECT * FROM employees;

-- Good
SELECT id, name, salary FROM employees;
```

### 3. Use EXISTS instead of IN for subqueries
```sql
-- Slower
SELECT * FROM employees
WHERE dept_id IN (SELECT id FROM departments WHERE location = 'NY');

-- Faster
SELECT * FROM employees e
WHERE EXISTS (SELECT 1 FROM departments d WHERE d.id = e.dept_id AND d.location = 'NY');
```

### 4. Avoid Functions on Indexed Columns
```sql
-- Bad (index not used)
SELECT * FROM employees WHERE UPPER(name) = 'JOHN';

-- Good (index used)
SELECT * FROM employees WHERE name = 'John';
```

### 5. Use LIMIT
```sql
-- Get only needed rows
SELECT * FROM employees ORDER BY salary DESC LIMIT 10;
```

### 6. Avoid OR, use UNION
```sql
-- Slower
SELECT * FROM employees WHERE dept = 'IT' OR salary > 60000;

-- Faster
SELECT * FROM employees WHERE dept = 'IT'
UNION
SELECT * FROM employees WHERE salary > 60000;
```

### 7. Use JOIN instead of Subqueries
```sql
-- Slower
SELECT name FROM employees
WHERE dept_id = (SELECT id FROM departments WHERE name = 'IT');

-- Faster
SELECT e.name 
FROM employees e
JOIN departments d ON e.dept_id = d.id
WHERE d.name = 'IT';
```

---

# ACID Properties

## Atomicity

**All or Nothing** - Transaction either completes fully or not at all

```sql
START TRANSACTION;

UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;

-- If second UPDATE fails, first UPDATE is also rolled back
COMMIT;
```

**Ensured by:** Transaction management, logging

## Consistency

**Database remains in valid state** before and after transaction

**Example:**
```sql
-- Constraint: balance >= 0

START TRANSACTION;
UPDATE accounts SET balance = balance - 1000 WHERE id = 1;
-- If balance becomes negative, transaction fails
COMMIT;
```

**Ensured by:** Constraints, triggers, application logic

## Isolation

**Concurrent transactions don't interfere**

```sql
-- Transaction 1
START TRANSACTION;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
COMMIT;

-- Transaction 2 (concurrent)
START TRANSACTION;
SELECT balance FROM accounts WHERE id = 1;  -- Sees consistent data
COMMIT;
```

**Ensured by:** Locking, MVCC (Multi-Version Concurrency Control)

## Durability

**Committed changes persist** even after system failure

```sql
START TRANSACTION;
INSERT INTO orders VALUES (1, '2024-01-01', 100);
COMMIT;  -- Data persists even if system crashes after this
```

**Ensured by:** Write-ahead logging, checkpoints

---

# Database Design

## ER Model Concepts

### Entities
```
Strong Entity: Has primary key
Weak Entity: Depends on strong entity

Example
