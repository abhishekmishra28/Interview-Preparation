# Graph Roadmap (LeetCode)

A strong progression is:

1. Graph Representation & Traversal  
2. BFS / DFS Patterns  
3. Grid & Matrix Graphs  
4. Topological Sort & DAG  
5. Shortest Path Algorithms  
6. Union Find (DSU)  
7. Advanced Graph Algorithms  
8. Hard Graph + DP Problems  

---

# EASY LEVEL

These build graph intuition, traversal understanding, and BFS/DFS basics.

## Graph Traversal Basics

1. Find if Path Exists in Graph (LC 1971)      [Done]
2. Flood Fill (LC 733)                         [Done]
3. Number of Islands (LC 200)                  [Done]
4. Max Area of Island (LC 695)                 [Done]

## DFS Basics

5. Clone Graph (LC 133)                        [Done]
6. All Paths From Source to Target (LC 797)    [Done]
7. Find Center of Star Graph (LC 1791)         [Done]

## BFS Basics

8. Shortest Path in Binary Matrix (LC 1091)
9. Rotting Oranges (LC 994)
10. Nearest Exit from Entrance in Maze (LC 1926)

## Grid Traversal

11. Island Perimeter (LC 463)
12. Surrounded Regions (LC 130)

---

# MEDIUM LEVEL

This is where interview-level graph understanding starts.

## DFS / BFS Core Patterns

13. Number of Connected Components in an Undirected Graph (LC 323)
14. Keys and Rooms (LC 841)
15. Pacific Atlantic Water Flow (LC 417)
16. Course Schedule (LC 207)
17. Course Schedule II (LC 210)

## Topological Sort

18. Alien Dictionary (Premium)
19. Parallel Courses (LC 1136)
20. Find Eventual Safe States (LC 802)

## Multi-Source BFS

21. Walls and Gates (Premium)
22. 01 Matrix (LC 542)
23. As Far from Land as Possible (LC 1162)

## Union Find (DSU)

24. Redundant Connection (LC 684)
25. Number of Provinces (LC 547)
26. Accounts Merge (LC 721)

## Shortest Path Intro

27. Network Delay Time (LC 743)
28. Cheapest Flights Within K Stops (LC 787)
29. Path With Minimum Effort (LC 1631)

## Graph + Grid Harder DFS

30. Word Search (LC 79)
31. Open the Lock (LC 752)
32. Detonate the Maximum Bombs (LC 2101)

## Bipartite / Coloring

33. Is Graph Bipartite? (LC 785)
34. Possible Bipartition (LC 886)

---

# HARD LEVEL

These are advanced interview-level graph concepts.

## Advanced Shortest Path

35. Word Ladder (LC 127)
36. Word Ladder II (LC 126)
37. Swim in Rising Water (LC 778)
38. Minimum Cost to Make at Least One Valid Path in a Grid (LC 1368)

## Advanced Union Find

39. Remove Max Number of Edges to Keep Graph Fully Traversable (LC 1579)
40. Similar String Groups (LC 839)

## DAG + DP

41. Longest Increasing Path in a Matrix (LC 329)
42. Reconstruct Itinerary (LC 332)
43. Largest Color Value in a Directed Graph (LC 1857)

## Hard BFS / State Graphs

44. Sliding Puzzle (LC 773)
45. Bus Routes (LC 815)
46. Shortest Path Visiting All Nodes (LC 847)

## MST (Minimum Spanning Tree)

47. Min Cost to Connect All Points (LC 1584)
48. Optimize Water Distribution in a Village (LC 1168)

## Advanced Graph Thinking

49. Critical Connections in a Network (LC 1192)
50. Alien Dictionary (Premium)
51. Making A Large Island (LC 827)

---

# Recommended Solving Order

## Phase 1 — Traversal Basics
1971 → 733 → 200 → 695 → 463

## Phase 2 — BFS/DFS Confidence
994 → 1091 → 130 → 841 → 417

## Phase 3 — Topological Sort & DAG
207 → 210 → 802 → Alien Dictionary

## Phase 4 — Union Find Mastery
547 → 684 → 721 → 1579

## Phase 5 — Shortest Path Algorithms
743 → 787 → 1631 → 778

## Phase 6 — Advanced Graphs
127 → 847 → 1192 → 332 → 1857

---

# Core Graph Patterns You Must Master

## 1. DFS

Used for:
- Connected components
- Cycle detection
- Backtracking
- Graph traversal

Key problems:
- LC 200
- LC 417
- LC 79

---

## 2. BFS

Used for:
- Shortest path in unweighted graphs
- Multi-source traversal
- Level-based expansion

Key problems:
- LC 994
- LC 1091
- LC 752

---

## 3. Topological Sort

Used for:
- Dependency ordering
- DAG processing
- Scheduling problems

Algorithms:
- Kahn’s BFS
- DFS topo sort

Key problems:
- LC 207
- LC 210
- Alien Dictionary

---

## 4. Union Find (DSU)

Used for:
- Dynamic connectivity
- Cycle detection
- Components merging

Concepts:
- Path compression
- Union by rank/size

Key problems:
- LC 547
- LC 684
- LC 721

---

## 5. Dijkstra Algorithm

Used for:
- Shortest weighted path
- Priority queue graphs

Key problems:
- LC 743
- LC 787
- LC 1631

---

## 6. Minimum Spanning Tree

Algorithms:
- Kruskal
- Prim

Key problems:
- LC 1584
- LC 1168

---

# Most Important Interview Problems

- Number of Islands (LC 200)
- Clone Graph (LC 133)
- Course Schedule (LC 207)
- Course Schedule II (LC 210)
- Number of Provinces (LC 547)
- Redundant Connection (LC 684)
- Network Delay Time (LC 743)
- Cheapest Flights Within K Stops (LC 787)
- Word Ladder (LC 127)
- Critical Connections in a Network (LC 1192)

These cover almost every major graph pattern asked in interviews.

## High-Level Pattern Mapping

| Pattern | Core Problems |
|---|---|
| DFS | 200, 417, 79 |
| BFS | 994, 1091, 752 |
| Topological Sort | 207, 210 |
| DSU | 547, 684 |
| Dijkstra | 743, 787 |
| MST | 1584 |
| Backtracking + Graph | 79, 332 |
| Tarjan Algorithm | 1192 |
| State Compression BFS | 847 |

# Best Preparation Strategy

1. Learn graph representation properly  
   - Adjacency list
   - Matrix
   - Edge list

2. Master DFS and BFS first  
   Most graph problems reduce to traversal.

3. Then learn:
   - Topological Sort
   - Union Find
   - Dijkstra

4. Finally move to:
   - MST
   - Tarjan
   - State graph BFS
   - Graph DP

A lot of hard graph problems become easy once you identify:
- “Is this BFS?”
- “Is this shortest path?”
- “Is this connectivity?”
- “Is this DAG?”
- “Is this DSU?”
