# 🌐 Graphs – Interview Preparation

This folder contains **graph-related problems and concepts** essential for
**Software Engineering interviews**.

The focus is on **understanding traversal techniques, graph representations,
and common interview patterns**, not just writing code.

---

## 🧠 What You’ll Learn Here

- How to represent graphs efficiently
- When to use **BFS vs DFS**
- Handling cycles, connectivity, and components
- Graph traversal patterns used in interviews
- Thinking in terms of **states, visited sets, and neighbors**

---

## 📌 Graph Representation

Graphs are generally represented using:

- **Adjacency List** (most common in interviews)
- **Adjacency Matrix** (rare, but useful conceptually)

Most solutions in this folder use **adjacency lists** due to:
- Better space efficiency
- Faster traversal for sparse graphs

---

## 🔁 Traversal Techniques

### 1️⃣ Breadth First Search (BFS)
- Uses a **queue**
- Explores level by level
- Best for:
  - Shortest path in unweighted graphs
  - Level-order traversal
  - Minimum steps problems

### 2️⃣ Depth First Search (DFS)
- Uses **recursion or stack**
- Goes as deep as possible
- Best for:
  - Connected components
  - Cycle detection
  - Backtracking-style graph problems

---

## 📂 Problems Covered

```text
Graphs/
│
├── BFS.cpp
├── DFS.cpp
├── Interview.txt
└── README.md
```
