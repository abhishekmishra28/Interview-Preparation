# DATABASE INDEXING — INTERVIEW SUMMARY

## 1. What is Indexing?
Indexing is a technique used by databases to improve the speed of data retrieval operations. An index is a special data structure that helps the database find rows quickly without scanning the entire table.

### Example
```sql
SELECT * FROM users WHERE email = 'a@gmail.com';
```

Without index:
- Database performs Full Table Scan
- Time Complexity ≈ O(n)

With index:
- Database directly locates required rows
- Time Complexity ≈ O(log n)

---

## 2. How Indexing Works
Most databases use **B-Tree** or **B+ Tree** data structures for indexes.

Indexes store data in sorted order and use a divide-and-conquer approach similar to binary search.

### Why B+ Trees?
- Fast searching
- Efficient insert/delete
- Balanced structure
- Supports range queries
- Optimized for disk storage

---

## 3. Types of Indexes

### A. Primary Index
- Automatically created on `PRIMARY KEY`
- Unique and `NOT NULL`

### B. Unique Index
- Prevents duplicate values

### C. Composite Index
Index on multiple columns.

### Example
```sql
CREATE INDEX idx_name_age
ON users(name, age);
```

### Important: Leftmost Prefix Rule
`(name, age)` works for:
```sql
WHERE name='A'
WHERE name='A' AND age=20
```

Not efficient for:
```sql
WHERE age=20
```

### D. Clustered Index
- Physically stores table data in sorted order
- Only one clustered index possible

### E. Non-Clustered Index
- Separate structure storing pointers to actual rows
- Multiple allowed

---

## 4. Advantages of Indexing
- Faster `SELECT` queries
- Faster `JOIN` operations
- Improves `ORDER BY` and `GROUP BY`
- Better performance on large datasets

---

## 5. Disadvantages of Indexing
- Consumes extra storage
- Slows `INSERT/UPDATE/DELETE`
- Too many indexes reduce write performance

### Reason
Database must also update indexes whenever data changes.

---

## 6. When to Use Indexes

### Create indexes on:
- Frequently searched columns
- `WHERE` clause columns
- `JOIN` columns
- Foreign keys
- `ORDER BY` columns

### Avoid indexes on:
- Small tables
- Frequently updated columns
- Low-cardinality columns

### Low Cardinality Example
```text
gender (Male/Female)
```

### High Cardinality Example
```text
email
user_id
phone number
```

---

## 7. Covering Index
If all required query data exists inside the index itself, the database avoids accessing the main table.

### Example
```sql
SELECT name FROM users WHERE email='x';
```

Index:
```sql
(email, name)
```

This improves performance significantly.

---

## 8. EXPLAIN Command
Used to analyze query execution.

### Example
```sql
EXPLAIN SELECT * FROM users
WHERE email='a@gmail.com';
```

Shows:
- index usage
- table scan
- query cost

---

## 9. Important Tradeoff

```text
Faster Reads
vs
Slower Writes + Extra Storage
```

Indexes improve read performance but slow down write operations.

---

## 10. Golden Interview Line

> “Indexes improve query performance by using optimized data structures like B+ Trees to avoid full table scans, providing approximately O(log n) search time, but they increase storage usage and slightly slow down write operations because indexes also require maintenance.”
