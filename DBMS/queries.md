# SQL — MAANG-Level SDE Interview Questions

> Covers: Core SQL · Window Functions · Joins · Subqueries · Optimization · Real Company Questions · LeetCode & HackerRank Problems

---

## SECTION 1: FOUNDATIONS

---

### 1. What is the difference between WHERE and HAVING?

**Theory:**
- `WHERE` filters rows **before** aggregation — operates on raw row data
- `HAVING` filters groups **after** `GROUP BY` aggregation — operates on aggregated results
- `WHERE` cannot use aggregate functions (`SUM`, `COUNT`, etc.); `HAVING` can

```sql
-- WHERE: filter before grouping
SELECT department, COUNT(*) AS emp_count
FROM employees
WHERE salary > 50000          -- filters individual rows first
GROUP BY department;

-- HAVING: filter after grouping
SELECT department, COUNT(*) AS emp_count
FROM employees
GROUP BY department
HAVING COUNT(*) > 10;         -- filters groups after aggregation

-- Combined: both together
SELECT department, AVG(salary) AS avg_sal
FROM employees
WHERE status = 'ACTIVE'       -- step 1: filter rows
GROUP BY department
HAVING AVG(salary) > 70000;   -- step 2: filter groups
```

> **Asked at:** Amazon, Microsoft, Infosys, TCS  
> **HackerRank:** "Weather Observation Station" series

---

### 2. What are the types of JOINs?

**Theory:**
JOINs combine rows from two or more tables based on a related column.

| Join Type | Returns |
|---|---|
| `INNER JOIN` | Only matching rows in both tables |
| `LEFT JOIN` | All rows from left + matching from right (NULL if no match) |
| `RIGHT JOIN` | All rows from right + matching from left (NULL if no match) |
| `FULL OUTER JOIN` | All rows from both; NULLs where no match |
| `CROSS JOIN` | Cartesian product — every combination |
| `SELF JOIN` | Table joined with itself |

```sql
-- INNER JOIN: employees with departments
SELECT e.name, d.dept_name
FROM employees e
INNER JOIN departments d ON e.dept_id = d.id;

-- LEFT JOIN: all employees, even those with no department
SELECT e.name, d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.id;

-- SELF JOIN: find manager names
SELECT e.name AS employee, m.name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.id;

-- FULL OUTER JOIN (emulated in MySQL)
SELECT e.name, d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.id
UNION
SELECT e.name, d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.id;
```

> **Asked at:** Google, Amazon, Flipkart, Oracle  
> **LeetCode:** #175 Combine Two Tables, #181 Employees Earning More Than Managers

---

### 3. Find the second highest salary

**Theory:**
Classic ranking problem. Multiple approaches — understand all of them.

```sql
-- Approach 1: LIMIT + OFFSET (MySQL)
SELECT MAX(salary) AS SecondHighest
FROM employees
WHERE salary < (SELECT MAX(salary) FROM employees);

-- Approach 2: Using LIMIT OFFSET
SELECT salary AS SecondHighest
FROM employees
ORDER BY salary DESC
LIMIT 1 OFFSET 1;

-- Approach 3: DENSE_RANK (preferred — handles duplicates)
SELECT salary AS SecondHighest
FROM (
  SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) AS rnk
  FROM employees
) ranked
WHERE rnk = 2;

-- Approach 4: Handle NULL if only 1 unique salary exists
SELECT (
  SELECT DISTINCT salary
  FROM employees
  ORDER BY salary DESC
  LIMIT 1 OFFSET 1
) AS SecondHighest;
```

> **Asked at:** Amazon, Google, Microsoft, Adobe, Walmart  
> **LeetCode:** #176 Second Highest Salary ⭐ (very common)

---

### 4. Find the Nth highest salary (generalized)

**Theory:**
Extension of Q3. MAANG interviews often make this dynamic.

```sql
-- MySQL: Function approach
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N - 1;
  RETURN (
    SELECT DISTINCT salary
    FROM employees
    ORDER BY salary DESC
    LIMIT 1 OFFSET N
  );
END;

-- Universal approach using DENSE_RANK
SELECT salary
FROM (
  SELECT salary, DENSE_RANK() OVER (ORDER BY salary DESC) AS rnk
  FROM employees
) t
WHERE rnk = N;  -- replace N with desired rank
```

> **Asked at:** Microsoft, Paytm, Goldman Sachs  
> **LeetCode:** #177 Nth Highest Salary ⭐

---

### 5. What is the difference between DELETE, TRUNCATE, and DROP?

**Theory:**

| | DELETE | TRUNCATE | DROP |
|---|---|---|---|
| **Type** | DML | DDL | DDL |
| **Rolls back?** | ✅ Yes | ❌ No (in most DBs) | ❌ No |
| **WHERE clause** | ✅ Yes | ❌ No | ❌ No |
| **Triggers fired?** | ✅ Yes | ❌ No | ❌ No |
| **Removes structure?** | ❌ No | ❌ No | ✅ Yes |
| **Speed** | Slower | Faster | Fastest |
| **Resets identity/auto-increment?** | ❌ No | ✅ Yes | ✅ Yes |

```sql
DELETE FROM orders WHERE status = 'CANCELLED';  -- rows only, rollback possible
TRUNCATE TABLE temp_logs;                        -- all rows, fast, no rollback
DROP TABLE old_archive;                          -- entire table gone
```

> **Asked at:** TCS, Infosys, Cognizant, Wipro, Amazon

---

### 6. What is the difference between UNION and UNION ALL?

**Theory:**
- `UNION` — combines result sets and **removes duplicates** (sorts internally → slower)
- `UNION ALL` — combines result sets and **keeps all duplicates** (faster, no dedup step)

Use `UNION ALL` unless you explicitly need deduplication — it's significantly faster on large datasets.

```sql
-- UNION: returns distinct rows
SELECT city FROM customers
UNION
SELECT city FROM suppliers;

-- UNION ALL: returns all rows including duplicates
SELECT city FROM customers
UNION ALL
SELECT city FROM suppliers;

-- Real use case: combine this month + last month orders
SELECT order_id, 'current' AS period FROM orders_april
UNION ALL
SELECT order_id, 'previous' AS period FROM orders_march;
```

> **Asked at:** Accenture, Capgemini, Flipkart  
> **HackerRank:** "Symmetric Pairs"

---

### 7. What are Window Functions?

**Theory:**
Window functions perform calculations across a **set of rows related to the current row** without collapsing them into groups (unlike GROUP BY). The `OVER()` clause defines the window.

```sql
-- Syntax
function_name() OVER (
  PARTITION BY column    -- groups (like GROUP BY but doesn't collapse rows)
  ORDER BY column        -- order within each partition
  ROWS/RANGE BETWEEN ... -- optional frame specification
)
```

**Key window functions:**

```sql
-- ROW_NUMBER: unique sequential number per partition
SELECT name, salary, dept,
  ROW_NUMBER() OVER (PARTITION BY dept ORDER BY salary DESC) AS row_num
FROM employees;

-- RANK: gaps after ties (1, 2, 2, 4)
SELECT name, salary,
  RANK() OVER (ORDER BY salary DESC) AS rnk
FROM employees;

-- DENSE_RANK: no gaps after ties (1, 2, 2, 3)
SELECT name, salary,
  DENSE_RANK() OVER (ORDER BY salary DESC) AS dense_rnk
FROM employees;

-- LAG/LEAD: access previous/next row value
SELECT order_date, revenue,
  LAG(revenue, 1) OVER (ORDER BY order_date) AS prev_revenue,
  revenue - LAG(revenue, 1) OVER (ORDER BY order_date) AS change
FROM daily_sales;

-- Running total
SELECT order_date, revenue,
  SUM(revenue) OVER (ORDER BY order_date ROWS UNBOUNDED PRECEDING) AS running_total
FROM daily_sales;
```

> **Asked at:** Google, Amazon, Meta, Netflix  
> **LeetCode:** #184 Department Highest Salary, #185 Department Top Three Salaries ⭐⭐

---

### 8. Find duplicate records in a table

**Theory:**
Use `GROUP BY` + `HAVING COUNT(*) > 1` to identify duplicates. Classic data quality problem.

```sql
-- Find duplicate emails
SELECT email, COUNT(*) AS count
FROM users
GROUP BY email
HAVING COUNT(*) > 1;

-- Find all rows that are duplicates (show each duplicate row)
SELECT *
FROM users
WHERE email IN (
  SELECT email FROM users
  GROUP BY email
  HAVING COUNT(*) > 1
);

-- Delete duplicates, keep the one with lowest id
DELETE FROM users
WHERE id NOT IN (
  SELECT MIN(id)
  FROM users
  GROUP BY email
);
```

> **Asked at:** Amazon, Walmart, Accenture, HCL  
> **LeetCode:** #196 Delete Duplicate Emails ⭐

---

### 9. What is a subquery? Types?

**Theory:**
A subquery is a query nested inside another query.

| Type | Description | Where Used |
|---|---|---|
| **Scalar** | Returns single value | SELECT, WHERE |
| **Row** | Returns single row | WHERE with row comparison |
| **Column (IN)** | Returns single column | WHERE IN / NOT IN |
| **Table (Derived)** | Returns table | FROM clause |
| **Correlated** | References outer query | Re-executes per outer row |

```sql
-- Scalar subquery
SELECT name, salary,
  (SELECT AVG(salary) FROM employees) AS company_avg
FROM employees;

-- Column subquery with IN
SELECT name FROM employees
WHERE dept_id IN (SELECT id FROM departments WHERE location = 'NYC');

-- Correlated subquery (executes once per row — use carefully at scale)
SELECT name, salary FROM employees e
WHERE salary > (
  SELECT AVG(salary) FROM employees
  WHERE dept_id = e.dept_id    -- references outer query's dept_id
);

-- Derived table (subquery in FROM)
SELECT dept, avg_sal
FROM (
  SELECT dept_id AS dept, AVG(salary) AS avg_sal
  FROM employees
  GROUP BY dept_id
) dept_avg
WHERE avg_sal > 80000;
```

> **Asked at:** Oracle, SAP, Microsoft, Infosys  
> **LeetCode:** #183 Customers Who Never Order

---

### 10. Employees who earn more than their managers

**Theory:**
Classic self-join problem. Tests understanding of table aliases and self-referential relationships.

```sql
-- Schema: Employee(id, name, salary, managerId)

SELECT e.name AS Employee
FROM Employee e
JOIN Employee m ON e.managerId = m.id
WHERE e.salary > m.salary;
```

> **Asked at:** Google, Amazon, Uber, Microsoft  
> **LeetCode:** #181 Employees Earning More Than Their Managers ⭐⭐

---

## SECTION 2: INTERMEDIATE QUERIES

---

### 11. Find customers who never placed an order

**Theory:**
Use `LEFT JOIN ... WHERE IS NULL` or `NOT IN` / `NOT EXISTS`. Each has performance implications.

```sql
-- Approach 1: LEFT JOIN (most performant in most DBs)
SELECT c.customer_id, c.name
FROM customers c
LEFT JOIN orders o ON c.customer_id = o.customer_id
WHERE o.customer_id IS NULL;

-- Approach 2: NOT IN (avoid on large tables — NULLs can cause issues)
SELECT customer_id, name FROM customers
WHERE customer_id NOT IN (SELECT customer_id FROM orders);

-- Approach 3: NOT EXISTS (handles NULLs correctly, often best optimizer hint)
SELECT c.customer_id, c.name FROM customers c
WHERE NOT EXISTS (
  SELECT 1 FROM orders o WHERE o.customer_id = c.customer_id
);
```

> **Asked at:** Amazon, Flipkart, Walmart  
> **LeetCode:** #183 Customers Who Never Order ⭐

---

### 12. Department with the highest average salary

```sql
-- Basic
SELECT dept_id, AVG(salary) AS avg_salary
FROM employees
GROUP BY dept_id
ORDER BY avg_salary DESC
LIMIT 1;

-- With department name (join)
SELECT d.dept_name, AVG(e.salary) AS avg_salary
FROM employees e
JOIN departments d ON e.dept_id = d.id
GROUP BY d.dept_name
ORDER BY avg_salary DESC
LIMIT 1;

-- Handle ties — all departments with max avg
SELECT dept_id, AVG(salary) AS avg_salary
FROM employees
GROUP BY dept_id
HAVING AVG(salary) = (
  SELECT MAX(avg_sal) FROM (
    SELECT AVG(salary) AS avg_sal FROM employees GROUP BY dept_id
  ) t
);
```

> **Asked at:** Google, Adobe, Paytm

---

### 13. Top N employees per department (Department Top 3 Salaries)

**Theory:**
Use `DENSE_RANK()` partitioned by department. Do NOT use `RANK()` if you want to handle ties correctly.

```sql
SELECT dept_name, employee_name, salary
FROM (
  SELECT
    d.dept_name,
    e.name AS employee_name,
    e.salary,
    DENSE_RANK() OVER (PARTITION BY e.dept_id ORDER BY e.salary DESC) AS rnk
  FROM employees e
  JOIN departments d ON e.dept_id = d.id
) ranked
WHERE rnk <= 3;
```

> **Asked at:** Meta, Amazon, Microsoft, Goldman Sachs  
> **LeetCode:** #185 Department Top Three Salaries ⭐⭐⭐

---

### 14. Consecutive numbers (3 or more times in a row)

**Theory:**
Use `LAG()` / `LEAD()` to compare adjacent rows, or self-join on `id+1` and `id+2`.

```sql
-- Using window functions (preferred)
SELECT DISTINCT num AS ConsecutiveNums
FROM (
  SELECT num,
    LAG(num, 1) OVER (ORDER BY id) AS prev1,
    LAG(num, 2) OVER (ORDER BY id) AS prev2
  FROM Logs
) t
WHERE num = prev1 AND num = prev2;
```

> **Asked at:** Uber, LinkedIn, Amazon  
> **LeetCode:** #180 Consecutive Numbers ⭐⭐

---

### 15. Rising temperature — find dates warmer than previous day

```sql
-- Using LAG (clean approach)
SELECT id
FROM (
  SELECT id,
    temperature,
    LAG(temperature) OVER (ORDER BY recordDate) AS prev_temp,
    LAG(recordDate) OVER (ORDER BY recordDate) AS prev_date,
    recordDate
  FROM Weather
) t
WHERE temperature > prev_temp
  AND DATEDIFF(recordDate, prev_date) = 1;

-- Using self join (classic approach)
SELECT w1.id
FROM Weather w1
JOIN Weather w2
  ON DATEDIFF(w1.recordDate, w2.recordDate) = 1
WHERE w1.temperature > w2.temperature;
```

> **LeetCode:** #197 Rising Temperature ⭐

---

### 16. Find the median salary

**Theory:**
SQL doesn't have a native MEDIAN function in most databases. This tests creative problem-solving.

```sql
-- MySQL approach
SELECT AVG(salary) AS median_salary
FROM (
  SELECT salary,
    ROW_NUMBER() OVER (ORDER BY salary) AS rn,
    COUNT(*) OVER () AS total
  FROM employees
) t
WHERE rn IN (FLOOR((total + 1) / 2), CEIL((total + 1) / 2));
```

> **Asked at:** Amazon, Bloomberg, Citadel, DE Shaw

---

### 17. Running total / cumulative sum

```sql
-- Cumulative revenue by date
SELECT
  order_date,
  daily_revenue,
  SUM(daily_revenue) OVER (
    ORDER BY order_date
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
  ) AS cumulative_revenue
FROM daily_sales;

-- Running total per department
SELECT
  dept_id,
  employee_id,
  salary,
  SUM(salary) OVER (
    PARTITION BY dept_id
    ORDER BY employee_id
  ) AS dept_running_total
FROM employees;
```

> **Asked at:** Amazon, Walmart, Stripe

---

### 18. Month-over-month growth rate

**Theory:**
Classic business analytics query. Tests ability to use LAG() and percentage calculations.

```sql
SELECT
  month,
  revenue,
  LAG(revenue) OVER (ORDER BY month) AS prev_month_revenue,
  ROUND(
    (revenue - LAG(revenue) OVER (ORDER BY month)) * 100.0 /
    LAG(revenue) OVER (ORDER BY month),
    2
  ) AS growth_pct
FROM monthly_revenue;
```

> **Asked at:** Amazon, Flipkart, Myntra, Swiggy

---

### 19. Pivot table — rows to columns

**Theory:**
Use conditional aggregation with `CASE WHEN` inside `SUM()` / `COUNT()`.

```sql
-- Transform: (student, subject, score) → one row per student
SELECT
  student_id,
  SUM(CASE WHEN subject = 'Math'    THEN score ELSE 0 END) AS Math,
  SUM(CASE WHEN subject = 'Science' THEN score ELSE 0 END) AS Science,
  SUM(CASE WHEN subject = 'English' THEN score ELSE 0 END) AS English
FROM scores
GROUP BY student_id;
```

> **Asked at:** Microsoft, Oracle, SAP

---

### 20. Find users active on consecutive days (retention query)

**Theory:**
A real-world product analytics query. Tests understanding of `LEAD`/`LAG` and date arithmetic.

```sql
-- Users who were active on at least 2 consecutive days
SELECT DISTINCT user_id
FROM (
  SELECT
    user_id,
    activity_date,
    LEAD(activity_date) OVER (PARTITION BY user_id ORDER BY activity_date) AS next_date
  FROM user_activity
) t
WHERE DATEDIFF(next_date, activity_date) = 1;
```

> **Asked at:** Meta, LinkedIn, Twitter/X, Snapchat

---

## SECTION 3: ADVANCED SQL

---

### 21. What is a CTE (Common Table Expression)?

**Theory:**
A CTE (`WITH` clause) is a named temporary result set that exists only during the execution of a single statement. It improves readability and can be referenced multiple times.

```sql
-- Basic CTE
WITH dept_avg AS (
  SELECT dept_id, AVG(salary) AS avg_salary
  FROM employees
  GROUP BY dept_id
)
SELECT e.name, e.salary, d.avg_salary
FROM employees e
JOIN dept_avg d ON e.dept_id = d.dept_id
WHERE e.salary > d.avg_salary;

-- Multiple CTEs
WITH
high_value_orders AS (
  SELECT customer_id, SUM(amount) AS total
  FROM orders
  GROUP BY customer_id
  HAVING SUM(amount) > 10000
),
premium_customers AS (
  SELECT customer_id FROM customers
  WHERE tier = 'GOLD'
)
SELECT h.customer_id, h.total
FROM high_value_orders h
JOIN premium_customers p ON h.customer_id = p.customer_id;
```

> **Asked at:** Google, Meta, Amazon, Goldman Sachs

---

### 22. What is a Recursive CTE?

**Theory:**
Recursive CTEs reference themselves to process hierarchical data (org charts, file systems, category trees).

```sql
-- Print org hierarchy from CEO down
WITH RECURSIVE org_tree AS (
  -- Anchor: start with CEO (no manager)
  SELECT id, name, manager_id, 0 AS level
  FROM employees
  WHERE manager_id IS NULL

  UNION ALL

  -- Recursive: join employees to their managers
  SELECT e.id, e.name, e.manager_id, ot.level + 1
  FROM employees e
  JOIN org_tree ot ON e.manager_id = ot.id
)
SELECT id, name, level FROM org_tree
ORDER BY level, name;
```

> **Asked at:** Amazon, Microsoft, SAP, Oracle

---

### 23. What are indexes? How do they work?

**Theory:**
An index is a data structure (typically B-Tree) that speeds up data retrieval at the cost of additional storage and write overhead.

| Index Type | Description |
|---|---|
| **Clustered** | Data physically sorted by index key (1 per table — usually PK) |
| **Non-clustered** | Separate structure with pointer to actual row |
| **Composite** | Index on multiple columns; order matters |
| **Covering** | Index contains all columns needed by query (no table lookup needed) |
| **Unique** | Enforces uniqueness constraint |
| **Full-text** | For text search (`MATCH AGAINST`) |
| **Partial** | Index on a subset of rows (PostgreSQL) |

```sql
-- Create index
CREATE INDEX idx_emp_dept ON employees(dept_id);

-- Composite index (selectivity order matters — high cardinality first)
CREATE INDEX idx_order_cust_date ON orders(customer_id, order_date);

-- Covering index (query satisfied entirely by index)
CREATE INDEX idx_covering ON orders(customer_id, order_date, status);

-- Check if index is used (MySQL)
EXPLAIN SELECT * FROM employees WHERE dept_id = 5;
```

**When indexes are NOT used:**
- `WHERE YEAR(created_at) = 2024` → wrap function breaks index; use range instead
- `WHERE email LIKE '%gmail.com'` → leading wildcard bypasses index
- Low cardinality columns (e.g., boolean column indexed)

> **Asked at:** Google, Amazon, Uber, Microsoft (very common at senior level)

---

### 24. What is EXPLAIN / Query Execution Plan?

**Theory:**
`EXPLAIN` shows the query optimizer's execution plan — how it will fetch data.

```sql
EXPLAIN SELECT e.name, d.dept_name
FROM employees e
JOIN departments d ON e.dept_id = d.id
WHERE e.salary > 80000;
```

**Key columns to read:**
| Column | What to look for |
|---|---|
| `type` | `ALL` = full table scan (⚠️ bad); `ref`, `range`, `const` = index used (✅ good) |
| `key` | Which index is being used |
| `rows` | Estimated rows examined — lower is better |
| `Extra` | `Using filesort` or `Using temporary` = potential optimization needed |

> **Asked at:** Google, Uber, Stripe, Netflix (system design + SQL rounds)

---

### 25. What is normalization? 1NF, 2NF, 3NF, BCNF?

**Theory:**
Normalization eliminates redundancy and ensures data integrity.

| Form | Rule |
|---|---|
| **1NF** | Atomic values; no repeating groups; each column has one value |
| **2NF** | 1NF + No partial dependency (non-key column depends on entire PK) |
| **3NF** | 2NF + No transitive dependency (non-key column depends only on PK) |
| **BCNF** | 3NF + Every determinant is a candidate key |

**Example violation → fix:**
```
-- Violates 3NF: zip_code → city (transitive dependency on non-key)
Orders(order_id, customer_id, zip_code, city)

-- Fixed: separate city lookup
Orders(order_id, customer_id, zip_code)
ZipCodes(zip_code, city)
```

> **Asked at:** Microsoft, Oracle, SAP, IBM

---

### 26. What is denormalization? When to use it?

**Theory:**
Denormalization intentionally introduces redundancy to improve **read performance** at the cost of write complexity and storage.

**When to denormalize:**
- Read-heavy workloads (OLAP, analytics, reporting)
- Joins across many tables are too slow
- Data warehouse / data lake design (star schema, snowflake schema)

```sql
-- Normalized: join required for every product name lookup
SELECT o.order_id, p.product_name, o.quantity
FROM orders o
JOIN products p ON o.product_id = p.id;

-- Denormalized: product_name stored in orders table directly
-- Faster reads, but product name changes require updating both tables
SELECT order_id, product_name, quantity FROM orders;
```

> **Asked at:** Amazon (system design), Google, Walmart Data Engineering

---

### 27. Transactions, ACID properties

**Theory:**

| Property | Meaning |
|---|---|
| **Atomicity** | All operations succeed or all roll back — no partial transactions |
| **Consistency** | DB moves from one valid state to another; constraints always satisfied |
| **Isolation** | Concurrent transactions don't interfere with each other |
| **Durability** | Committed transactions survive crashes (written to disk) |

```sql
BEGIN TRANSACTION;

UPDATE accounts SET balance = balance - 500 WHERE id = 1;  -- debit
UPDATE accounts SET balance = balance + 500 WHERE id = 2;  -- credit

-- If any step fails:
ROLLBACK;

-- If all succeed:
COMMIT;
```

**Isolation Levels (from lowest to highest isolation):**

| Level | Dirty Read | Non-Repeatable Read | Phantom Read |
|---|---|---|---|
| READ UNCOMMITTED | ✅ Possible | ✅ Possible | ✅ Possible |
| READ COMMITTED | ❌ No | ✅ Possible | ✅ Possible |
| REPEATABLE READ | ❌ No | ❌ No | ✅ Possible |
| SERIALIZABLE | ❌ No | ❌ No | ❌ No |

> **Asked at:** Google, Amazon, Microsoft, Goldman Sachs, JPMorgan

---

### 28. What are stored procedures vs functions?

**Theory:**

| | Stored Procedure | Function |
|---|---|---|
| **Return value** | 0 or more (via OUT params) | Always returns 1 value |
| **Called in SQL?** | `CALL proc()` — cannot use in SELECT | `SELECT func()` — can use in SELECT |
| **Transactions** | Can contain | Cannot (in most DBs) |
| **Side effects** | Can modify DB | Should be side-effect free |

```sql
-- Stored Procedure
CREATE PROCEDURE GetDeptEmployees(IN dept_id INT)
BEGIN
  SELECT name, salary FROM employees WHERE department_id = dept_id;
END;

CALL GetDeptEmployees(3);

-- Function
CREATE FUNCTION GetFullName(first VARCHAR(50), last VARCHAR(50))
RETURNS VARCHAR(100)
BEGIN
  RETURN CONCAT(first, ' ', last);
END;

SELECT GetFullName(first_name, last_name) FROM employees;
```

> **Asked at:** Oracle, SAP, Microsoft, IBM

---

### 29. Rank vs Dense_Rank vs Row_Number

**Theory:**

| Function | Behavior on Ties | Gap after tie? |
|---|---|---|
| `ROW_NUMBER()` | Arbitrary unique number | N/A (always unique) |
| `RANK()` | Same rank for ties | ✅ Yes — skips next rank |
| `DENSE_RANK()` | Same rank for ties | ❌ No — consecutive |

```sql
-- Salary: 100, 90, 90, 80
SELECT salary,
  ROW_NUMBER()  OVER (ORDER BY salary DESC) AS row_num,    -- 1, 2, 3, 4
  RANK()        OVER (ORDER BY salary DESC) AS rnk,         -- 1, 2, 2, 4
  DENSE_RANK()  OVER (ORDER BY salary DESC) AS dense_rnk   -- 1, 2, 2, 3
FROM employees;
```

> **Asked at:** Amazon, Google, Uber, Microsoft ⭐⭐⭐ (extremely common)  
> **LeetCode:** #178 Rank Scores

---

### 30. What is a deadlock? How to prevent it?

**Theory:**
A deadlock occurs when two or more transactions hold locks and each waits for the other to release — circular wait.

```
Transaction A: locks Row 1 → waits for Row 2
Transaction B: locks Row 2 → waits for Row 1
→ Circular wait → deadlock
```

**Prevention strategies:**
1. Always acquire locks in the **same order** across transactions
2. Use **shorter transactions** — commit quickly
3. Use **lower isolation levels** where acceptable
4. Add appropriate **indexes** to reduce lock scope
5. Use **optimistic locking** (version/timestamp column) instead of pessimistic

```sql
-- Optimistic locking pattern
UPDATE orders
SET status = 'SHIPPED', version = version + 1
WHERE id = 99 AND version = 5;   -- fails if another transaction already updated
```

> **Asked at:** Amazon, Google, Uber, Netflix, Stripe

---

## SECTION 4: REAL COMPANY SQL QUESTIONS

---

### 31. [Meta/Facebook] Find friends who have more friends than average

```sql
WITH friend_counts AS (
  SELECT user_id, COUNT(*) AS friend_count
  FROM friendships
  GROUP BY user_id
)
SELECT user_id, friend_count
FROM friend_counts
WHERE friend_count > (SELECT AVG(friend_count) FROM friend_counts);
```

---

### 32. [Amazon] Find products never ordered

```sql
SELECT p.product_id, p.product_name
FROM products p
LEFT JOIN order_items oi ON p.product_id = oi.product_id
WHERE oi.product_id IS NULL;
```

> **LeetCode:** #1045 Customers Who Bought All Products ⭐

---

### 33. [Uber] Driver trips count per day with 7-day moving average

```sql
SELECT
  trip_date,
  daily_trips,
  AVG(daily_trips) OVER (
    ORDER BY trip_date
    ROWS BETWEEN 6 PRECEDING AND CURRENT ROW
  ) AS moving_avg_7day
FROM (
  SELECT DATE(start_time) AS trip_date, COUNT(*) AS daily_trips
  FROM trips
  GROUP BY DATE(start_time)
) daily;
```

---

### 34. [LinkedIn] Second most recent activity per user

```sql
SELECT username, activity
FROM (
  SELECT
    username,
    activity,
    ROW_NUMBER() OVER (PARTITION BY username ORDER BY startDate DESC) AS rn,
    COUNT(*) OVER (PARTITION BY username) AS total_activities
  FROM UserActivity
) t
WHERE (total_activities = 1 AND rn = 1)
   OR (total_activities > 1 AND rn = 2);
```

> **LeetCode:** #1454 Active Users ⭐

---

### 35. [Netflix] Find users who watched all movies in a category

```sql
SELECT user_id
FROM watch_history wh
JOIN movies m ON wh.movie_id = m.id
WHERE m.category = 'Action'
GROUP BY user_id
HAVING COUNT(DISTINCT wh.movie_id) = (
  SELECT COUNT(*) FROM movies WHERE category = 'Action'
);
```

> **LeetCode:** #1045 Customers Who Bought All Products (same pattern) ⭐

---

### 36. [Google] Report contiguous date ranges

**Theory:**
The "gaps and islands" problem — grouping consecutive rows.

```sql
-- Find contiguous date ranges of user activity
SELECT
  user_id,
  MIN(login_date) AS start_date,
  MAX(login_date) AS end_date
FROM (
  SELECT
    user_id,
    login_date,
    DATE_SUB(login_date, INTERVAL ROW_NUMBER() OVER (
      PARTITION BY user_id ORDER BY login_date
    ) DAY) AS grp
  FROM user_logins
) t
GROUP BY user_id, grp
ORDER BY user_id, start_date;
```

> **LeetCode:** #1225 Report Contiguous Dates ⭐⭐

---

### 37. [Twitter/X] Find tweets that got more likes than the tweeter's average

```sql
WITH user_avg AS (
  SELECT user_id, AVG(likes) AS avg_likes
  FROM tweets
  GROUP BY user_id
)
SELECT t.tweet_id, t.user_id, t.likes
FROM tweets t
JOIN user_avg u ON t.user_id = u.user_id
WHERE t.likes > u.avg_likes;
```

---

### 38. [Stripe/Fintech] Detect fraudulent transactions (same amount, same user, within 10 minutes)

```sql
SELECT t1.transaction_id AS fraud_id
FROM transactions t1
JOIN transactions t2
  ON t1.user_id = t2.user_id
  AND t1.amount = t2.amount
  AND t1.transaction_id <> t2.transaction_id
  AND ABS(TIMESTAMPDIFF(SECOND, t1.created_at, t2.created_at)) <= 600;
```

---

### 39. [Walmart/E-commerce] Find the most frequently bought together product pairs

```sql
SELECT
  a.product_id AS product1,
  b.product_id AS product2,
  COUNT(*) AS times_bought_together
FROM order_items a
JOIN order_items b
  ON a.order_id = b.order_id
  AND a.product_id < b.product_id    -- avoid duplicates (A,B) and (B,A)
GROUP BY a.product_id, b.product_id
ORDER BY times_bought_together DESC
LIMIT 10;
```

---

### 40. [Goldman Sachs / JPMorgan] Calculate portfolio daily P&L with running total

```sql
SELECT
  trade_date,
  daily_pnl,
  SUM(daily_pnl) OVER (
    ORDER BY trade_date
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
  ) AS cumulative_pnl,
  AVG(daily_pnl) OVER (
    ORDER BY trade_date
    ROWS BETWEEN 29 PRECEDING AND CURRENT ROW
  ) AS rolling_30day_avg
FROM portfolio_pnl
ORDER BY trade_date;
```

---

## QUICK REFERENCE: LeetCode SQL Problems by Topic

| Topic | LeetCode Problems |
|---|---|
| Basic SELECT | #175, #176, #177, #178 |
| JOINs | #175, #181, #183, #197 |
| Aggregation | #182, #184, #185, #262 |
| Window Functions | #178, #180, #184, #185, #1321 |
| Subqueries | #183, #184, #626 |
| CTEs | #1225, #1454, #1767 |
| Date Functions | #197, #1321, #1907 |
| Hard/Advanced | #185, #262, #601, #1225, #1767 |

---

## QUICK REFERENCE: SQL Clause Execution Order

```
FROM → JOIN → WHERE → GROUP BY → HAVING → SELECT → DISTINCT → ORDER BY → LIMIT
```

This is why:
- You **cannot** use a `SELECT` alias in `WHERE` (SELECT runs after WHERE)
- You **can** use a `SELECT` alias in `ORDER BY` (ORDER BY runs after SELECT)
- `HAVING` can use aggregate functions; `WHERE` cannot

---

## QUICK REFERENCE: Performance Checklist

| Issue | Fix |
|---|---|
| Full table scan | Add index on filter/join column |
| `SELECT *` | Select only needed columns |
| Correlated subquery per row | Rewrite as JOIN or CTE |
| `LIKE '%text'` | Use full-text index or search engine |
| `OR` in WHERE | Rewrite as `UNION ALL` or use composite index |
| `NOT IN` with NULLs | Use `NOT EXISTS` instead |
| Function on indexed column | Rewrite to avoid function (`WHERE created_at >= '2024-01-01'`) |
| No LIMIT on large tables | Always paginate large result sets |

---

*These notes cover SQL at the depth expected in MAANG SDE interviews, data engineering rounds, and backend system design discussions.*
