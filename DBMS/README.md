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

## What is Normalization?
**Definition:** Process of organizing database tables to minimize redundancy and dependency

**Goals:**
- Eliminate redundant data
- Ensure data dependencies make sense
- Prevent insertion, update, and deletion anomalies
- Improve data integrity

## Functional Dependencies (FD)

### Basic Concept
```
X → Y (X determines Y)
If two tuples have same X values, they must have same Y values
```

### Example
```
StudentID → StudentName
(StudentID determines StudentName)
```

### Armstrong's Axioms
```
1. Reflexivity: If Y ⊆ X, then X → Y
2. Augmentation: If X → Y, then XZ → YZ  
3. Transitivity: If X → Y and Y → Z, then X → Z
```

## Types of Keys

```
Super Key: Set of attributes that uniquely identifies tuples
Candidate Key: Minimal super key (no redundant attributes)
Primary Key: Chosen candidate key
Foreign Key: References primary key of another table
```

### Example
```
Student(ID, Email, Phone, Name)
Super Keys: {ID, Email}, {ID, Phone}, {ID, Email, Phone}
Candidate Keys: {ID}, {Email}
Primary Key: {ID}
```

## Normal Forms

### 1NF (First Normal Form)

**Requirements:**
- Each column contains atomic values
- No repeating groups or arrays
- Each record is unique

**Before 1NF:**
```
Employee(EmpID, Name, PhoneNumbers)
101, John, "9876543210, 9876543211"  ❌
```

**After 1NF:**
```
Employee(EmpID, Name, PhoneNumber)
101, John, 9876543210
101, John, 9876543211  ✓
```

### 2NF (Second Normal Form)

**Requirements:**
- Must be in 1NF
- No partial dependencies (non-key attributes depend on entire primary key)

**Before 2NF:**
```
OrderDetails(OrderID, ProductID, ProductName, Quantity)
Primary Key: (OrderID, ProductID)
ProductName depends only on ProductID ❌
```

**After 2NF:**
```
OrderDetails(OrderID, ProductID, Quantity)
Product(ProductID, ProductName) ✓
```

### 3NF (Third Normal Form)

**Requirements:**
- Must be in 2NF
- No transitive dependencies (non-key depends on non-key)

**Before 3NF:**
```
Employee(EmpID, Name, DeptID, DeptName, DeptLocation)
EmpID → DeptID → DeptName (transitive) ❌
```

**After 3NF:**
```
Employee(EmpID, Name, DeptID)
Department(DeptID, DeptName, DeptLocation) ✓
```

### BCNF (Boyce-Codd Normal Form)

**Requirements:**
- Must be in 3NF
- Every determinant must be a candidate key

**Before BCNF:**
```
TeacherSubject(StudentID, Subject, Teacher)
FD: (StudentID, Subject) → Teacher
FD: Teacher → Subject
Teacher is not a candidate key ❌
```

**After BCNF:**
```
StudentTeacher(StudentID, Teacher)
TeacherSubject(Teacher, Subject) ✓
```

### 4NF (Fourth Normal Form)

**Requirements:**
- Must be in BCNF
- No multi-valued dependencies

**Before 4NF:**
```
StudentInfo(StudentID, Course, Sport)
Student can have multiple courses and sports independently ❌
```

**After 4NF:**
```
StudentCourse(StudentID, Course)
StudentSport(StudentID, Sport) ✓
```

### 5NF (Fifth Normal Form)

**Requirements:**
- Must be in 4NF
- No join dependencies

**Example:**
```
SupplyInfo(Supplier, Product, Customer)
Decompose if independent relationships exist
```

## Database Anomalies

### Update Anomaly
```
Problem: Updating data requires changes in multiple places
Example: Changing department name needs updating all employee records
```

### Insert Anomaly
```
Problem: Cannot insert data without unrelated information
Example: Cannot add new department without an employee
```

### Delete Anomaly
```
Problem: Deleting a record causes loss of other valuable data
Example: Deleting last employee removes department information
```

---

# MCQs on Normalization

## Fundamental Concepts

**Q1.** The primary goal of normalization is to:
```
a) Increase storage space
b) Eliminate data redundancy ✓
c) Make queries faster
d) Create more tables
```

**Q2.** A functional dependency X → Y means:
```
a) Y determines X
b) X uniquely determines Y ✓
c) X and Y are the same
d) Y is a subset of X
```

**Q3.** Which of the following is NOT a valid normal form?
```
a) 1NF
b) 2NF
c) 2.5NF ✓
d) 3NF
```

## First Normal Form (1NF)

**Q4.** Which violates 1NF?
```
a) Customer(ID, Name, Email)
b) Customer(ID, Name, Phone1, Phone2)
c) Customer(ID, Name, Orders) where Orders = "101,102,103" ✓
d) Customer(ID, FirstName, LastName)
```

**Q5.** To achieve 1NF, we must eliminate:
```
a) Partial dependencies
b) Transitive dependencies
c) Repeating groups ✓
d) All dependencies
```

## Second Normal Form (2NF)

**Q6.** 2NF eliminates which type of dependency?
```
a) Partial dependency ✓
b) Transitive dependency
c) Multi-valued dependency
d) Join dependency
```

**Q7.** Given R(A,B,C,D) with primary key (A,B) and FD: A → C, this violates:
```
a) 1NF
b) 2NF ✓
c) 3NF
d) BCNF
```

## Third Normal Form (3NF)

**Q8.** A transitive dependency exists when:
```
a) A → B and B → C where B is not a key ✓
b) AB → C
c) A → BC
d) A → B and C → D
```

**Q9.** Employee(EmpID, Name, DeptID, DeptName) violates which normal form?
```
a) 1NF
b) 2NF
c) 3NF ✓
d) None
```

## BCNF

**Q10.** BCNF is stricter than 3NF because:
```
a) It eliminates partial dependencies
b) Every determinant must be a superkey ✓
c) It eliminates repeating groups
d) It requires fewer tables
```

**Q11.** A relation in BCNF is always in:
```
a) 1NF only
b) 2NF only
c) 3NF ✓
d) 4NF
```

## Higher Normal Forms

**Q12.** 4NF deals with:
```
a) Partial dependencies
b) Transitive dependencies
c) Multi-valued dependencies ✓
d) Functional dependencies
```

**Q13.** 5NF is also known as:
```
a) Domain-Key Normal Form
b) Project-Join Normal Form ✓
c) Boyce-Codd Normal Form
d) Elementary Normal Form
```

## Keys and Dependencies

**Q14.** A candidate key is:
```
a) Any superkey
b) Minimal superkey ✓
c) Foreign key
d) Primary key only
```

**Q15.** Given R(A,B,C) with FDs: A → B and B → C, the candidate key is:
```
a) A ✓
b) B
c) C
d) ABC
```

## Practical Applications

**Q16.** Order(OrderID, Date, CustomerID, CustomerName) is in:
```
a) 1NF only
b) 2NF only ✓
c) 3NF
d) BCNF
```

**Q17.** The main disadvantage of over-normalization is:
```
a) Data redundancy
b) Storage waste
c) Complex queries with many joins ✓
d) Data inconsistency
```

**Q18.** Which anomaly occurs when we cannot insert a record without unrelated data?
```
a) Update anomaly
b) Insert anomaly ✓
c) Delete anomaly
d) Read anomaly
```

**Q19.** Denormalization is done primarily for:
```
a) Saving storage space
b) Performance optimization ✓
c) Better data integrity
d) Eliminating redundancy
```

**Q20.** A prime attribute is:
```
a) The first attribute in a relation
b) Part of some candidate key ✓
c) Always unique
d) Never NULL
```

## Advanced Questions

**Q21.** Lossless decomposition ensures:
```
a) No data redundancy
b) Original relation can be reconstructed ✓
c) Faster queries
d) Fewer tables
```

**Q22.** Given Student(SID, Sname, CID, Cname, Grade) with key (SID,CID), which FD violates 2NF?
```
a) (SID,CID) → Grade
b) SID → Sname ✓
c) (SID,CID) → Sname
d) Grade → CID
```

**Q23.** Armstrong's axiom of augmentation states:
```
a) If X → Y then X → XY
b) If X → Y then XZ → YZ ✓
c) If X → Y and Y → Z then X → Z
d) If X → Y then Y → X
```

**Q24.** The closure of attribute set X (denoted X+) contains:
```
a) Only X
b) All attributes determined by X ✓
c) All candidate keys
d) All superkeys
```

**Q25.** A relation R is decomposed into R1 and R2. The decomposition is dependency preserving if:
```
a) R1 ∪ R2 = R
b) R1 ∩ R2 ≠ φ
c) All FDs can be checked without joining ✓
d) R1 ∩ R2 is a superkey
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

**Ensured by:** Write-ahead logging, checkpoint

---

# Database Design

## ER Model Concepts

### Entities
```
Strong Entity: Has primary key (e.g., Employee, Department)
Weak Entity: Depends on strong entity for identification (e.g., Dependent)

Example:
┌──────────────┐         ┌──────────────┐
│   Employee   │─────────│  Dependent   │
│  (Strong)    │         │   (Weak)     │
│  EmpID (PK)  │         │  DepName     │
│  Name        │         │  Age         │
│  Salary      │         │  Relation    │
└──────────────┘         └──────────────┘
Dependent identified by (EmpID + DepName)
```

### Attributes

```
Simple Attribute:     Name, Age
Composite Attribute:  Address → (Street, City, State, ZIP)
Multivalued Attribute: Phone Numbers (multiple values)
Derived Attribute:    Age (derived from Date of Birth)
Key Attribute:        EmpID (underlined in ER diagram)

Example:
         ┌─────────┐
    Name─┤         ├─DOB
   Email─┤ Student ├─Age (derived, shown as dashed oval)
      ID─┤         ├─Phone (multivalued, shown as double oval)
         └─────────┘
              │
         Address (composite)
         /    |     \
     Street  City   ZIP
```

### Relationships

```
One-to-One (1:1):
┌──────────┐  1     1  ┌──────────┐
│ Employee ├────────────┤ Passport │
└──────────┘            └──────────┘
Each employee has exactly one passport

One-to-Many (1:N):
┌────────────┐  1     N  ┌──────────┐
│ Department ├───────────┤ Employee │
└────────────┘            └──────────┘
One department has many employees

Many-to-Many (M:N):
┌──────────┐  M     N  ┌──────────┐
│ Student  ├────────────┤  Course  │
└──────────┘            └──────────┘
Many students enroll in many courses
```

### Participation Constraints

```
Total Participation (double line): Every entity MUST participate
Partial Participation (single line): Entity MAY participate

Example:
┌──────────┐          ┌────────────┐
│ Employee ├══════════┤ Department │
└──────────┘  works   └────────────┘
              in
(Every employee MUST belong to a department → total participation)
(Some departments MAY have no employees → partial participation)
```

## ER to Relational Mapping

### Strong Entity → Table
```sql
-- Entity: Student(StudentID, Name, Age)
CREATE TABLE Student (
    StudentID INT PRIMARY KEY,
    Name VARCHAR(100),
    Age INT
);
```

### Weak Entity → Table with Foreign Key
```sql
-- Weak Entity: Dependent(DepName, Age, Relation)
-- Owner: Employee
CREATE TABLE Dependent (
    EmpID INT,
    DepName VARCHAR(100),
    Age INT,
    Relation VARCHAR(50),
    PRIMARY KEY (EmpID, DepName),
    FOREIGN KEY (EmpID) REFERENCES Employee(EmpID) ON DELETE CASCADE
);
```

### 1:1 Relationship
```sql
-- Merge into one table or add FK to either side
CREATE TABLE Employee (
    EmpID INT PRIMARY KEY,
    Name VARCHAR(100),
    PassportID INT UNIQUE,
    FOREIGN KEY (PassportID) REFERENCES Passport(PassportID)
);
```

### 1:N Relationship
```sql
-- Add FK on the "many" side
CREATE TABLE Employee (
    EmpID INT PRIMARY KEY,
    Name VARCHAR(100),
    DeptID INT,
    FOREIGN KEY (DeptID) REFERENCES Department(DeptID)
);
```

### M:N Relationship
```sql
-- Create junction/bridge table
CREATE TABLE Enrollment (
    StudentID INT,
    CourseID INT,
    EnrollDate DATE,
    Grade CHAR(2),
    PRIMARY KEY (StudentID, CourseID),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Course(CourseID)
);
```

### Multivalued Attribute → Separate Table
```sql
-- Multivalued: Student has multiple phone numbers
CREATE TABLE StudentPhone (
    StudentID INT,
    PhoneNumber VARCHAR(15),
    PRIMARY KEY (StudentID, PhoneNumber),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID)
);
```

### Composite Attribute → Flatten
```sql
CREATE TABLE Employee (
    EmpID INT PRIMARY KEY,
    Street VARCHAR(100),
    City VARCHAR(50),
    State VARCHAR(50),
    ZIP VARCHAR(10)
);
```

## EER (Enhanced ER) Model

### Generalization / Specialization
```
          ┌──────────┐
          │  Person   │
          │ PersonID  │
          │ Name      │
          └─────┬─────┘
            ISA (d or o)
           /          \
  ┌──────────┐  ┌──────────┐
  │ Student  │  │ Employee │
  │ GPA      │  │ Salary   │
  └──────────┘  └──────────┘

d = disjoint (person is EITHER student OR employee)
o = overlapping (person can be BOTH)
```

```sql
-- Method 1: Single table (with type column)
CREATE TABLE Person (
    PersonID INT PRIMARY KEY,
    Name VARCHAR(100),
    Type ENUM('Student', 'Employee', 'Both'),
    GPA DECIMAL(3,2),      -- NULL for employees
    Salary DECIMAL(10,2)   -- NULL for students
);

-- Method 2: Separate tables
CREATE TABLE Person (
    PersonID INT PRIMARY KEY,
    Name VARCHAR(100)
);

CREATE TABLE Student (
    PersonID INT PRIMARY KEY,
    GPA DECIMAL(3,2),
    FOREIGN KEY (PersonID) REFERENCES Person(PersonID)
);

CREATE TABLE Employee (
    PersonID INT PRIMARY KEY,
    Salary DECIMAL(10,2),
    FOREIGN KEY (PersonID) REFERENCES Person(PersonID)
);
```

---

# Functional Dependencies

## Definition

**Functional Dependency (FD):** X → Y means Y is functionally determined by X

```
If two tuples have same X value, they MUST have same Y value

Example:
EmpID → EmpName     (Employee ID determines Employee Name)
EmpID → Dept        (Employee ID determines Department)
DeptID → DeptName   (Department ID determines Department Name)
```

## Types of Functional Dependencies

### Trivial FD
```
X → Y where Y ⊆ X
Example: {EmpID, Name} → Name  (trivial)
```

### Non-Trivial FD
```
X → Y where Y ⊄ X
Example: EmpID → Name  (non-trivial)
```

### Partial FD
```
Part of candidate key determines non-key attribute
Example: {StudentID, CourseID} → StudentName
StudentID alone → StudentName (partial dependency)
```

### Transitive FD
```
X → Y → Z (X determines Z through Y)
Example: EmpID → DeptID → DeptName
```

## Armstrong's Axioms

```
1. Reflexivity:   If Y ⊆ X, then X → Y
2. Augmentation:  If X → Y, then XZ → YZ
3. Transitivity:  If X → Y and Y → Z, then X → Z

Derived Rules:
4. Union:         If X → Y and X → Z, then X → YZ
5. Decomposition: If X → YZ, then X → Y and X → Z
6. Pseudo-transitivity: If X → Y and WY → Z, then WX → Z
```

## Closure of Attributes

```
Finding all attributes determined by a set of attributes

Given FDs:
A → B
B → C
C → D
AB → E

Closure of A (A+):
Start: {A}
A → B: {A, B}
B → C: {A, B, C}
C → D: {A, B, C, D}
AB → E: {A, B, C, D, E}

A+ = {A, B, C, D, E}
A is a candidate key (determines all attributes)
```

## Canonical Cover (Minimal Cover)

```
Steps:
1. Decompose FDs to single attribute on right side
2. Remove extraneous attributes from left side
3. Remove redundant FDs

Example:
FDs: {A → BC, B → C, AB → D}

Step 1: A → B, A → C, B → C, AB → D
Step 2: A → C is redundant (A → B → C via transitivity)
        AB → D: Can we remove B? A+ = {A,B,C} → A → D? No. Keep AB → D
        AB → D: Can we remove A? B+ = {B,C} → B → D? No. Keep AB → D

Minimal Cover: {A → B, B → C, AB → D}
```

---

# File Organization

## Heap File (Unordered)
```
Records stored in insertion order
+ Fast insertion
- Slow search (linear scan)

Example:
Block 1: [Rec3, Rec1, Rec7]
Block 2: [Rec2, Rec9, Rec4]
Block 3: [Rec5, Rec8, Rec6]
```

## Sequential File (Ordered)
```
Records sorted by search key
+ Fast range queries
+ Binary search possible
- Slow insertion (need to shift)

Example (sorted by ID):
Block 1: [1, 2, 3]
Block 2: [4, 5, 6]
Block 3: [7, 8, 9]
```

## Hash File
```
Hash function maps key to bucket
+ Very fast equality search O(1)
- No range queries
- Overflow handling needed

Example:
h(key) = key mod 4
Bucket 0: [4, 8, 12]
Bucket 1: [1, 5, 9]
Bucket 2: [2, 6, 10]
Bucket 3: [3, 7, 11]
```

## B-Tree vs B+ Tree

### B-Tree
```
          [30, 60]
         /   |    \
    [10,20] [40,50] [70,80]
    
- Keys and data at all nodes
- No duplicate keys
- Less storage efficient
```

### B+ Tree
```
          [30, 60]
         /   |    \
    [10,20] [30,50] [60,80]
     ↕   ↕   ↕   ↕   ↕   ↕
    data data data data data data
    
    Leaf level: [10]↔[20]↔[30]↔[50]↔[60]↔[80]
    
- Data only at leaf nodes
- Leaf nodes linked (great for range queries)
- Internal nodes have only keys (more keys per node)
- More storage efficient
- Preferred in DBMS
```

### B+ Tree Properties
```
Order m:
- Each node has at most m children
- Each node (except root) has at least ⌈m/2⌉ children
- Root has at least 2 children
- Leaf nodes at same level

For order 4 (m=4):
- Max children: 4
- Max keys per node: 3
- Min children (non-root): 2
- Min keys (non-root): 1
```

---

# Recovery System

## Log-Based Recovery

### Write-Ahead Logging (WAL)
```
Rule: Log record must be written BEFORE the actual data modification

Log Format: <TransactionID, DataItem, OldValue, NewValue>

Example:
<T1, START>
<T1, A, 100, 200>     -- A changed from 100 to 200
<T1, B, 300, 250>     -- B changed from 300 to 250
<T1, COMMIT>
```

### Undo Recovery
```
If transaction not committed before crash → UNDO changes
Use old values from log to restore

Log:
<T1, START>
<T1, A, 100, 200>
<T1, B, 300, 250>
── CRASH ──

Recovery:
B = 300 (restore old value)
A = 100 (restore old value)
```

### Redo Recovery
```
If transaction committed but changes not written to disk → REDO changes
Use new values from log to apply

Log:
<T1, START>
<T1, A, 100, 200>
<T1, B, 300, 250>
<T1, COMMIT>
── CRASH ──

Recovery:
A = 200 (apply new value)
B = 250 (apply new value)
```

### Undo-Redo Recovery
```
Combines both approaches
- Undo uncommitted transactions
- Redo committed transactions

Log:
<T1, START>
<T1, A, 100, 200>
<T2, START>
<T2, C, 400, 500>
<T1, B, 300, 250>
<T1, COMMIT>
── CRASH ──

Recovery:
Redo T1: A=200, B=250 (committed)
Undo T2: C=400 (not committed)
```

## Checkpoints

```
Reduces recovery time by marking a known good state

Log:
<T1, START>
<T1, A, 100, 200>
<T1, COMMIT>
<CHECKPOINT>           ← Everything before this is safe
<T2, START>
<T2, B, 300, 400>
<T3, START>
<T3, C, 500, 600>
<T2, COMMIT>
── CRASH ──

Recovery (only process after checkpoint):
Redo T2: B=400 (committed after checkpoint)
Undo T3: C=500 (not committed)
T1: No action needed (committed before checkpoint)
```

---

# Distributed Databases

## Concepts

```
Distributed Database: Data spread across multiple locations

Site 1 (New York)     Site 2 (London)     Site 3 (Tokyo)
┌─────────────┐      ┌─────────────┐     ┌─────────────┐
│ Employees   │      │ Employees   │     │ Employees   │
│ (US region) │      │ (EU region) │     │ (Asia)      │
└─────────────┘      └─────────────┘     └─────────────┘
```

## Fragmentation

### Horizontal Fragmentation
```sql
-- Split by rows
-- Fragment 1: US employees
SELECT * FROM Employees WHERE country = 'US';

-- Fragment 2: UK employees
SELECT * FROM Employees WHERE country = 'UK';
```

### Vertical Fragmentation
```sql
-- Split by columns
-- Fragment 1: Employee basic info
SELECT EmpID, Name, Dept FROM Employees;

-- Fragment 2: Employee salary info
SELECT EmpID, Salary, Bonus FROM Employees;
```

## CAP Theorem

```
In a distributed system, you can only guarantee 2 out of 3:

C - Consistency:    Every read gets most recent write
A - Availability:   Every request gets a response
P - Partition Tolerance: System works despite network failures

       C
      / \
     /   \
    /     \
   A ───── P

CA: Traditional RDBMS (PostgreSQL, MySQL)
CP: MongoDB, HBase
AP: Cassandra, DynamoDB
```

## Two-Phase Commit (2PC)

```
Ensures atomicity in distributed transactions

Phase 1: Prepare (Voting)
Coordinator → All Participants: "Can you commit?"
Participant 1: "Yes (VOTE COMMIT)"
Participant 2: "Yes (VOTE COMMIT)"

Phase 2: Commit (Decision)
If ALL voted YES:
    Coordinator → All: "COMMIT"
If ANY voted NO:
    Coordinator → All: "ABORT"

Timeline:
Coordinator:  PREPARE ──→ (collect votes) ──→ COMMIT/ABORT
Participant1: ──→ VOTE YES ──→ (wait) ──→ COMMIT/ABORT
Participant2: ──→ VOTE YES ──→ (wait) ──→ COMMIT/ABORT
```

---

# NoSQL Databases

## Types of NoSQL

### 1. Key-Value Store
```
Key → Value

Example (Redis):
"user:1001" → {"name": "Alice", "age": 25}
"session:abc" → {"userId": 1001, "expires": "2024-12-31"}

Use cases: Caching, session management
```

### 2. Document Store
```json
// Example (MongoDB):
{
    "_id": ObjectId("507f1f77bcf86cd799439011"),
    "name": "Alice",
    "age": 25,
    "address": {
        "street": "123 Main St",
        "city": "New York"
    },
    "courses": ["Math", "Physics", "CS"]
}

Use cases: Content management, catalogs
```

### 3. Column-Family Store
```
// Example (Cassandra):
Row Key: "user1001"
    Column Family: "personal"
        name: "Alice"
        age: 25
    Column Family: "academic"
        gpa: 3.8
        major: "CS"

Use cases: Analytics, time-series data
```

### 4. Graph Database
```
// Example (Neo4j):
(Alice)-[:FRIENDS_WITH]->(Bob)
(Alice)-[:ENROLLED_IN]->(CS101)
(Bob)-[:ENROLLED_IN]->(CS101)
(CS101)-[:TAUGHT_BY]->(Prof. Smith)

Use cases: Social networks, recommendation engines
```

## SQL vs NoSQL

| Feature | SQL | NoSQL |
|---------|-----|-------|
| **Schema** | Fixed schema | Dynamic/flexible schema |
| **Scaling** | Vertical (scale up) | Horizontal (scale out) |
| **ACID** | Strong ACID | Eventual consistency (BASE) |
| **Query** | SQL | Database-specific APIs |
| **Data Model** | Tables | Documents, key-value, graphs |
| **Best For** | Complex queries, transactions | Large scale, flexible data |
| **Examples** | MySQL, PostgreSQL, Oracle | MongoDB, Redis, Cassandra |

## BASE Properties (NoSQL)

```
BA - Basically Available: System guarantees availability
S  - Soft State: State may change over time (even without input)
E  - Eventually Consistent: System will become consistent eventually

Contrast with ACID:
ACID → Strong consistency, used in banking/finance
BASE → Eventual consistency, used in social media/streaming
```

---

# Data Warehousing

## OLTP vs OLAP

| Feature | OLTP | OLAP |
|---------|------|------|
| **Purpose** | Daily operations | Analysis & reporting |
| **Queries** | Simple, short | Complex, analytical |
| **Data** | Current, detailed | Historical, summarized |
| **Users** | Clerks, customers | Analysts, managers |
| **Normalization** | Highly normalized | Denormalized |
| **Example** | Banking transactions | Sales trend analysis |

## Star Schema

```
              ┌─────────────┐
              │  Date_Dim   │
              │ date_id     │
              │ day         │
              │ month       │
              │ year        │
              └──────┬──────┘
                     │
┌─────────────┐  ┌───┴────────┐  ┌─────────────┐
│ Product_Dim │──│ Sales_Fact │──│ Store_Dim   │
│ product_id  │  │ date_id    │  │ store_id    │
│ name        │  │ product_id │  │ location    │
│ category    │  │ store_id   │  │ manager     │
└─────────────┘  │ quantity   │  └─────────────┘
                 │ revenue    │
                 └────────────┘

- Central fact table (measurable data)
- Surrounded by dimension tables (descriptive data)
- Simple joins, fast queries
```

## Snowflake Schema

```
┌────────────┐   ┌─────────────┐
│ Category   │───│ Product_Dim │
│ cat_id     │   │ product_id  │
│ cat_name   │   │ name        │──┐
└────────────┘   │ cat_id      │  │
                 └─────────────┘  │  ┌────────────┐
                              ┌───┴──┤ Sales_Fact │
                              │      │ date_id    │
                              │      │ product_id │
                              │      │ quantity   │
                              │      └────────────┘

- Normalized dimension tables
- More tables, more joins
- Less storage, more complex queries
```

---

# SQL Practice Problems

## Easy Level

### 1. Second Highest Salary
```sql
-- Method 1: LIMIT OFFSET
SELECT DISTINCT salary FROM employees
ORDER BY salary DESC
LIMIT 1 OFFSET 1;

-- Method 2: Subquery
SELECT MAX(salary) FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);

-- Method 3: Dense Rank
SELECT salary FROM (
    SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) as rnk
    FROM employees
) t WHERE rnk = 2;
```

### 2. Nth Highest Salary
```sql
-- Generic solution for Nth highest
SELECT DISTINCT salary FROM employees
ORDER BY salary DESC
LIMIT 1 OFFSET N-1;

-- Using CTE
WITH ranked AS (
    SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) as rnk
    FROM employees
)
SELECT DISTINCT salary FROM ranked WHERE rnk = N;
```

### 3. Duplicate Records
```sql
-- Find duplicates
SELECT email, COUNT(*) as cnt
FROM employees
GROUP BY email
HAVING COUNT(*) > 1;

-- Delete duplicates (keep one)
DELETE e1 FROM employees e1
INNER JOIN employees e2
WHERE e1.id > e2.id AND e1.email = e2.email;

-- Alternative using CTE
WITH duplicates AS (
    SELECT id, ROW_NUMBER() OVER (PARTITION BY email ORDER BY id) as rn
    FROM employees
)
DELETE FROM employees WHERE id IN (
    SELECT id FROM duplicates WHERE rn > 1
);
```

### 4. Employees Earning More Than Manager
```sql
SELECT e.name as Employee
FROM employees e
JOIN employees m ON e.manager_id = m.id
WHERE e.salary > m.salary;
```

### 5. Consecutive Numbers
```sql
-- Find numbers appearing 3 times consecutively
SELECT DISTINCT l1.num as ConsecutiveNums
FROM logs l1
JOIN logs l2 ON l1.id = l2.id - 1
JOIN logs l3 ON l2.id = l3.id - 1
WHERE l1.num = l2.num AND l2.num = l3.num;
```

## Medium Level

### 6. Department Top 3 Salaries
```sql
SELECT d.name as Department, e.name as Employee, e.salary
FROM (
    SELECT *, DENSE_RANK() OVER (PARTITION BY dept_id ORDER BY salary DESC) as rnk
    FROM employees
) e
JOIN departments d ON e.dept_id = d.id
WHERE e.rnk <= 3;
```

### 7. Running Total
```sql
SELECT 
    order_date,
    amount,
    SUM(amount) OVER (ORDER BY order_date) as running_total,
    AVG(amount) OVER (ORDER BY order_date ROWS BETWEEN 2 PRECEDING AND CURRENT ROW) as moving_avg
FROM orders;
```

### 8. Year-over-Year Growth
```sql
WITH yearly_sales AS (
    SELECT 
        YEAR(order_date) as year,
        SUM(amount) as total_sales
    FROM orders
    GROUP BY YEAR(order_date)
)
SELECT 
    year,
    total_sales,
    LAG(total_sales) OVER (ORDER BY year) as prev_year_sales,
    ROUND((total_sales - LAG(total_sales) OVER (ORDER BY year)) * 100.0 
          / LAG(total_sales) OVER (ORDER BY year), 2) as growth_pct
FROM yearly_sales;
```

### 9. Pivot Table
```sql
-- Convert rows to columns
SELECT 
    student_name,
    MAX(CASE WHEN subject = 'Math' THEN marks END) as Math,
    MAX(CASE WHEN subject = 'Science' THEN marks END) as Science,
    MAX(CASE WHEN subject = 'English' THEN marks END) as English
FROM student_marks
GROUP BY student_name;
```

### 10. Gap Analysis (Missing IDs)
```sql
SELECT t1.id + 1 as gap_start,
       MIN(t2.id) - 1 as gap_end
FROM my_table t1
JOIN my_table t2 ON t2.id > t1.id
GROUP BY t1.id
HAVING t1.id + 1 < MIN(t2.id);
```

## Hard Level

### 11. Median Salary
```sql
-- Method 1
WITH ordered AS (
    SELECT salary,
           ROW_NUMBER() OVER (ORDER BY salary) as rn,
           COUNT(*) OVER () as total
    FROM employees
)
SELECT AVG(salary) as median
FROM ordered
WHERE rn IN (FLOOR((total + 1) / 2), CEIL((total + 1) / 2));
```

### 12. Cumulative Distribution
```sql
SELECT 
    dept,
    salary,
    CUME_DIST() OVER (PARTITION BY dept ORDER BY salary) as cumulative_dist,
    PERCENT_RANK() OVER (PARTITION BY dept ORDER BY salary) as percent_rank,
    NTILE(4) OVER (PARTITION BY dept ORDER BY salary) as quartile
FROM employees;
```

### 13. Recursive Hierarchy (Org Chart)
```sql
WITH RECURSIVE org_chart AS (
    -- CEO (no manager)
    SELECT emp_id, name, manager_id, 1 as level,
           CAST(name AS CHAR(1000)) as path
    FROM employees
    WHERE manager_id IS NULL
    
    UNION ALL
    
    -- All reports
    SELECT e.emp_id, e.name, e.manager_id, oc.level + 1,
           CONCAT(oc.path, ' → ', e.name)
    FROM employees e
    JOIN org_chart oc ON e.manager_id = oc.emp_id
)
SELECT * FROM org_chart ORDER BY level, name;
```

### 14. Island and Gap Problem
```sql
-- Find consecutive date ranges (islands)
WITH numbered AS (
    SELECT login_date,
           login_date - INTERVAL ROW_NUMBER() OVER (ORDER BY login_date) DAY as grp
    FROM user_logins
    WHERE user_id = 1
)
SELECT MIN(login_date) as streak_start,
       MAX(login_date) as streak_end,
       COUNT(*) as streak_length
FROM numbered
GROUP BY grp
ORDER BY streak_start;
```

---

# Interview Questions

## Conceptual Questions

### Q1: What is the difference between DELETE, TRUNCATE, and DROP?

```
DELETE:
- DML command
- Removes specific rows (WHERE clause)
- Can be rolled back
- Fires triggers
- Slower (row-by-row logging)
- Does NOT reset AUTO_INCREMENT

TRUNCATE:
- DDL command
- Removes ALL rows
- Cannot be rolled back (in most DBMS)
- Does NOT fire triggers
- Faster (deallocates pages)
- Resets AUTO_INCREMENT

DROP:
- DDL command
- Removes table structure + data
- Cannot be rolled back
- Table no longer exists
```

### Q2: What is the difference between WHERE and HAVING?

```sql
-- WHERE: Filters rows BEFORE grouping
SELECT dept, AVG(salary)
FROM employees
WHERE salary > 30000      -- Filters individual rows
GROUP BY dept;

-- HAVING: Filters groups AFTER grouping
SELECT dept, AVG(salary) as avg_sal
FROM employees
GROUP BY dept
HAVING AVG(salary) > 50000;  -- Filters groups

-- Combined
SELECT dept, AVG(salary) as avg_sal
FROM employees
WHERE hire_date > '2020-01-01'   -- Filter rows first
GROUP BY dept
HAVING AVG(salary) > 50000;      -- Then filter groups
```

### Q3: What is the difference between UNION and UNION ALL?

```sql
-- UNION: Removes duplicates (slower)
SELECT name FROM employees
UNION
SELECT name FROM contractors;

-- UNION ALL: Keeps duplicates (faster)
SELECT name FROM employees
UNION ALL
SELECT name FROM contractors;

-- Both require same number of columns and compatible types
```

### Q4: What is a deadlock? How to prevent it?

```
Deadlock: Two or more transactions waiting for each other's locks

Prevention:
1. Lock ordering: Always acquire locks in same order
2. Lock timeout: Set maximum wait time
3. Deadlock detection: Wait-for graph cycle detection
4. Two-phase locking with deadlock detection

Example:
-- Use consistent ordering
T1: Lock(A), Lock(B)  -- Always lock A before B
T2: Lock(A), Lock(B)  -- Same order prevents deadlock
```

### Q5: Explain different types of indexes

```
1. Clustered Index:
   - Physical order = index order
   - One per table
   - Primary key by default
   - Leaf nodes contain actual data

2. Non-Clustered Index:
   - Separate structure from data
   - Multiple per table
   - Leaf nodes contain pointers to data
   - Extra lookup needed (bookmark lookup)

3. Covering Index:
   - Contains all columns needed by query
   - No need to access actual table
   
   CREATE INDEX idx_cover ON employees(dept, salary, name);
   SELECT name, salary FROM employees WHERE dept = 'IT';
   -- Satisfied entirely from index

4. Filtered Index:
   CREATE INDEX idx_active ON employees(name) WHERE status = 'active';
```

### Q6: What is normalization vs denormalization?

```
Normalization:
- Break tables into smaller tables
- Reduce redundancy
- Improve data integrity
- More joins needed
- Used in OLTP systems

Denormalization:
- Combine tables to reduce joins
- Intentionally add redundancy
- Improve read performance
- Used in OLAP/data warehouse systems

Example:
Normalized:
  Orders(OrderID, CustomerID, OrderDate)
  Customers(CustomerID, Name, City)

Denormalized:
  Orders(OrderID, CustomerID, CustomerName, CustomerCity, OrderDate)
  -- Redundant but faster for queries needing customer info with orders
```

### Q7: What is MVCC (Multi-Version Concurrency Control)?

```
MVCC: Each transaction sees a snapshot of data at a point in time

How it works:
- Multiple versions of each row maintained
- Readers don't block writers
- Writers don't block readers
- Each transaction sees consistent snapshot

Example (PostgreSQL):
T1 starts at time 10
T2 starts at time 15

T2 updates row X (creates new version)
T1 still sees old version of row X (snapshot at time 10)

Used by: PostgreSQL, MySQL InnoDB, Oracle
```

### Q8: Explain the SQL query execution order

```
Written Order:        Execution Order:
1. SELECT            1. FROM / JOIN
2. FROM              2. WHERE
3. WHERE             3. GROUP BY
4. GROUP BY          4. HAVING
5. HAVING            5. SELECT
6. ORDER BY          6. DISTINCT
7. LIMIT             7. ORDER BY
                     8. LIMIT/OFFSET

This is why you CAN'T use column aliases in WHERE:
SELECT salary * 12 AS annual_salary
FROM employees
WHERE annual_salary > 100000;  -- ❌ ERROR!

But you CAN use them in ORDER BY:
SELECT salary * 12 AS annual_salary
FROM employees
ORDER BY annual_salary DESC;   -- ✓ Works!

And you CAN use them in HAVING (in MySQL):
SELECT dept, AVG(salary) AS avg_sal
FROM employees
GROUP BY dept
HAVING avg_sal > 50000;        -- ✓ Works in MySQL
```

### Q9: What are phantom reads and how to prevent them?

```
Phantom Read: New rows appear in repeated queries within same transaction

Example:
T1: SELECT COUNT(*) FROM employees WHERE dept='IT' → 5
T2: INSERT INTO employees (name, dept) VALUES ('New', 'IT')
T2: COMMIT
T1: SELECT COUNT(*) FROM employees WHERE dept='IT' → 6  ← Phantom!

Prevention:
1. Serializable isolation level
2. Range locks (lock the range of values)
3. Predicate locking
4. Gap locks (InnoDB)

SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
```

### Q10: Design a database for an e-commerce application

```sql
-- Users
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Categories
CREATE TABLE categories (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    parent_category_id INT,
    FOREIGN KEY (parent_category_id) REFERENCES categories(category_id)
);

-- Products
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(200) NOT NULL,
    description TEXT,
    price DECIMAL(10,2) NOT NULL CHECK (price > 0),
    stock_quantity INT DEFAULT 0 CHECK (stock_quantity >= 0),
    category_id INT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(category_id)
);

-- Orders
CREATE TABLE orders (
    order_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending',
    total_amount DECIMAL(12,2) NOT NULL,
    shipping_address TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Order Items
CREATE TABLE order_items (
    order_item_id INT PRIMARY KEY AUTO_INCREMENT,
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    unit_price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);

-- Reviews
CREATE TABLE reviews (
    review_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    product_id INT NOT NULL,
    rating INT CHECK (rating BETWEEN 1 AND 5),
    comment TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    UNIQUE (user_id, product_id)  -- One review per user per product
);

-- Shopping Cart
CREATE TABLE cart (
    cart_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (product_id) REFERENCES products(product_id),
    UNIQUE (user_id, product_id)
);

-- Useful indexes
CREATE INDEX idx_products_category ON products(category_id);
CREATE INDEX idx_orders_user ON orders(user_id);
CREATE INDEX idx_orders_date ON orders(order_date);
CREATE INDEX idx_order_items_order ON order_items(order_id);
CREATE INDEX idx_reviews_product ON reviews(product_id);
```

---

# Quick Reference Cheat Sheet

## SQL Command Categories

```
DDL: CREATE, ALTER, DROP, TRUNCATE, RENAME
DML: SELECT, INSERT, UPDATE, DELETE, MERGE
DCL: GRANT, REVOKE
TCL: COMMIT, ROLLBACK, SAVEPOINT
```

## Join Types Visual

```
INNER JOIN:      A ∩ B         (matching rows only)
LEFT JOIN:       A              (all from A + matching from B)
RIGHT JOIN:            B        (all from B + matching from A)
FULL OUTER JOIN: A ∪ B         (all from both)
CROSS JOIN:      A × B         (cartesian product)
SELF JOIN:       A ⋈ A         (table with itself)
```

## Normalization Summary

```
1NF: Atomic values, no repeating groups
2NF: 1NF + No partial dependencies
3NF: 2NF + No transitive dependencies
BCNF: Every determinant is a candidate key
4NF: No multivalued dependencies
5NF: No join dependencies
```

## ACID Quick Reference

```
A - Atomicity:    All or nothing
C - Consistency:  Valid state to valid state
I - Isolation:    Concurrent transactions don't interfere
D - Durability:   Committed data persists
```

## Isolation Levels

```
                    Dirty Read  Unrepeatable Read  Phantom Read
Read Uncommitted       ✓              ✓                ✓
Read Committed         ✗              ✓                ✓
Repeatable Read        ✗              ✗                ✓
Serializable           ✗              ✗                ✗
```

## Key Types

```
Super Key:     Any set of attributes that uniquely identifies tuple
Candidate Key: Minimal super key
Primary Key:   Selected candidate key (NOT NULL, unique)
Alternate Key: Candidate keys not selected as primary
Foreign Key:   References primary key of another table
Composite Key: Key with multiple attributes
Unique Key:    Ensures uniqueness (allows one NULL)
```

## Important SQL Patterns

```sql
-- Top N per group
WITH ranked AS (
    SELECT *, ROW_NUMBER() OVER (PARTITION BY group_col ORDER BY val DESC) as rn
    FROM table_name
)
SELECT * FROM ranked WHERE rn <= N;

-- Running total
SUM(col) OVER (ORDER BY date_col)

-- Previous/Next row
LAG(col) OVER (ORDER BY date_col)
LEAD(col) OVER (ORDER BY date_col)

-- Deduplication
WITH deduped AS (
    SELECT *, ROW_NUMBER() OVER (PARTITION BY dup_cols ORDER BY id) as rn
    FROM table_name
)
SELECT * FROM deduped WHERE rn = 1;

-- Conditional aggregation
SUM(CASE WHEN condition THEN value ELSE 0 END)
COUNT(CASE WHEN condition THEN 1 END)
```

---

**End of Complete DBMS & SQL Guide**
