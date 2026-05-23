# 📊 Graph Data Structure — Complete Interview Questions Guide

> From **Scratch to Advanced** | With Follow-up Questions & Answers  
> Ideal for: FAANG / Product-Based Company Interviews

---

## 📚 Table of Contents

1. [Basics & Fundamentals](#1-basics--fundamentals)
2. [Graph Representation](#2-graph-representation)
3. [Graph Traversals](#3-graph-traversals-bfs--dfs)
4. [Cycle Detection](#4-cycle-detection)
5. [Topological Sort](#5-topological-sort)
6. [Shortest Path Algorithms](#6-shortest-path-algorithms)
7. [Minimum Spanning Tree](#7-minimum-spanning-tree-mst)
8. [Connected Components](#8-connected-components)
9. [Bipartite Graphs](#9-bipartite-graphs)
10. [Advanced Topics](#10-advanced-topics)
11. [Classic Coding Problems](#11-classic-coding-problems)
12. [System Design with Graphs](#12-system-design-with-graphs)

---

## 1. Basics & Fundamentals

---

### Q1. What is a Graph? How is it different from a Tree?

**Answer:**

A **Graph** is a non-linear data structure consisting of:
- **Vertices (V)** — nodes
- **Edges (E)** — connections between nodes

```
Graph: A — B — C
           |
           D

Tree:    A
        / \
       B   C
      / \
     D   E
```

| Feature | Tree | Graph |
|---|---|---|
| Cycles | No cycles | Can have cycles |
| Parent | Every node has 1 parent (except root) | No parent-child restriction |
| Root | Has a single root | No mandatory root |
| Connected | Always connected | May be disconnected |
| Edges | N-1 edges for N nodes | Can have any number |

> **Follow-up:** Is every tree a graph?  
> **Answer:** Yes. A tree is a special case of a graph — it is a connected, undirected, acyclic graph with N nodes and exactly N-1 edges.

---

### Q2. What are the types of graphs?

**Answer:**

| Type | Description |
|---|---|
| **Undirected** | Edges have no direction (A—B means A↔B) |
| **Directed (Digraph)** | Edges have direction (A→B) |
| **Weighted** | Edges carry a cost/weight |
| **Unweighted** | All edges are equal |
| **Cyclic** | Contains at least one cycle |
| **Acyclic** | No cycles (DAG = Directed Acyclic Graph) |
| **Connected** | Every node is reachable from every other |
| **Disconnected** | Some nodes are unreachable from others |
| **Bipartite** | Nodes split into 2 groups, edges only between groups |
| **Complete** | Every pair of nodes has an edge |
| **Sparse** | Few edges (E << V²) |
| **Dense** | Many edges (E ≈ V²) |

> **Follow-up:** What is a DAG? Give a real-world example.  
> **Answer:** A DAG (Directed Acyclic Graph) is a directed graph with no cycles. Examples: task scheduling, Git commit history, package dependency trees, spreadsheet formula evaluation.

---

### Q3. What is the difference between in-degree and out-degree?

**Answer:**

- **Degree** (undirected graph): Total number of edges connected to a node.
- **In-degree** (directed graph): Number of edges **coming into** a node.
- **Out-degree** (directed graph): Number of edges **going out of** a node.

```
A → B → C
    ↓
    D

In-degree:  A=0, B=1, C=1, D=1
Out-degree: A=1, B=2, C=0, D=0
```

> **Follow-up:** What is the sum of all degrees in an undirected graph?  
> **Answer:** The sum of all degrees = 2 × (number of edges). This is the **Handshaking Lemma** — every edge contributes 2 to the total degree count.

---

### Q4. What is a sparse vs dense graph? Which representation suits which?

**Answer:**

- **Sparse Graph:** E ≈ O(V) — few edges relative to nodes  
  → Use **Adjacency List** (space-efficient: O(V + E))

- **Dense Graph:** E ≈ O(V²) — many edges  
  → Use **Adjacency Matrix** (fast O(1) edge lookup, space O(V²))

---

## 2. Graph Representation

---

### Q5. Explain the different ways to represent a graph.

**Answer:**

#### ✅ 1. Adjacency Matrix

A 2D boolean/integer array where `matrix[i][j] = 1` means edge from i to j.

```python
# Undirected Graph: 4 nodes
adj = [
    [0, 1, 1, 0],  # Node 0
    [1, 0, 1, 0],  # Node 1
    [1, 1, 0, 1],  # Node 2
    [0, 0, 1, 0]   # Node 3
]
```

| | Space | Add Edge | Remove Edge | Check Edge | Get Neighbors |
|---|---|---|---|---|---|
| Matrix | O(V²) | O(1) | O(1) | O(1) | O(V) |

#### ✅ 2. Adjacency List

An array/dictionary of lists. Each index stores the list of neighbors.

```python
from collections import defaultdict

graph = defaultdict(list)
graph[0] = [1, 2]
graph[1] = [0, 2]
graph[2] = [0, 1, 3]
graph[3] = [2]
```

| | Space | Add Edge | Remove Edge | Check Edge | Get Neighbors |
|---|---|---|---|---|---|
| List | O(V+E) | O(1) | O(E) | O(V) | O(degree) |

#### ✅ 3. Edge List

A simple list of all edges.

```python
edges = [(0, 1), (0, 2), (1, 2), (2, 3)]
# Weighted: [(0, 1, 4), (0, 2, 2), ...]
```

> **Follow-up:** Which is better for BFS/DFS — matrix or list?  
> **Answer:** Adjacency List is better for BFS/DFS because getting all neighbors of a node is O(degree) vs O(V) for a matrix. For sparse graphs, list is significantly faster.

---

### Q6. How do you build a graph from an edge list in code?

**Answer:**

```python
def build_graph(n, edges, directed=False):
    """
    n: number of nodes (0 to n-1)
    edges: list of (u, v) tuples
    """
    graph = [[] for _ in range(n)]
    
    for u, v in edges:
        graph[u].append(v)
        if not directed:
            graph[v].append(u)  # undirected
    
    return graph

# Example
n = 5
edges = [(0, 1), (0, 2), (1, 3), (2, 4)]
g = build_graph(n, edges)
# g[0] = [1, 2], g[1] = [0, 3], etc.
```

---

## 3. Graph Traversals (BFS & DFS)

---

### Q7. Explain BFS (Breadth-First Search) with code.

**Answer:**

BFS explores nodes **level by level** using a queue. It is ideal for:
- Shortest path in unweighted graphs
- Level-order traversal
- Finding connected components

```python
from collections import deque

def bfs(graph, start, n):
    visited = [False] * n
    order = []
    
    queue = deque([start])
    visited[start] = True
    
    while queue:
        node = queue.popleft()
        order.append(node)
        
        for neighbor in graph[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                queue.append(neighbor)
    
    return order

# Time:  O(V + E)
# Space: O(V)
```

> **Follow-up:** Why do we mark a node as visited when we enqueue, not when we dequeue?  
> **Answer:** To prevent the same node from being added to the queue multiple times, which would cause redundant processing and potentially infinite loops. Marking on enqueue is the correct approach.

---

### Q8. Explain DFS (Depth-First Search) with code — both recursive and iterative.

**Answer:**

DFS explores as **deep as possible** before backtracking. Ideal for:
- Cycle detection
- Topological sort
- Path finding
- Connected components

```python
# --- Recursive DFS ---
def dfs_recursive(graph, node, visited, order):
    visited[node] = True
    order.append(node)
    
    for neighbor in graph[node]:
        if not visited[neighbor]:
            dfs_recursive(graph, neighbor, visited, order)

def dfs(graph, start, n):
    visited = [False] * n
    order = []
    dfs_recursive(graph, start, visited, order)
    return order


# --- Iterative DFS (using stack) ---
def dfs_iterative(graph, start, n):
    visited = [False] * n
    order = []
    stack = [start]
    
    while stack:
        node = stack.pop()
        if not visited[node]:
            visited[node] = True
            order.append(node)
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    stack.append(neighbor)
    
    return order

# Time:  O(V + E)
# Space: O(V) — recursion stack or explicit stack
```

> **Follow-up:** What's the difference between BFS and DFS in terms of memory?  
> **Answer:** BFS stores an entire level of nodes in the queue — worst case O(V). DFS's stack depth equals the depth of the path — worst case O(V) too, but in practice is smaller for wide/shallow graphs. For very deep graphs, DFS may hit recursion limits.

> **Follow-up:** When would you prefer BFS over DFS?  
> **Answer:** Use BFS when you need the **shortest path** (in unweighted graphs), level-order traversal, or when the solution is likely near the start node. Use DFS when exploring all paths, doing backtracking, cycle detection, or topological sort.

---

## 4. Cycle Detection

---

### Q9. How do you detect a cycle in an undirected graph?

**Answer:**

Use DFS and track the **parent** of each node. If we visit a neighbor that is already visited and is **not** the parent, a cycle exists.

```python
def has_cycle_undirected(graph, n):
    visited = [False] * n
    
    def dfs(node, parent):
        visited[node] = True
        for neighbor in graph[node]:
            if not visited[neighbor]:
                if dfs(neighbor, node):
                    return True
            elif neighbor != parent:
                return True  # Back edge found = cycle
        return False
    
    for i in range(n):  # Handle disconnected graphs
        if not visited[i]:
            if dfs(i, -1):
                return True
    return False

# Time: O(V + E)  |  Space: O(V)
```

**Alternative:** Union-Find (DSU)

```python
def has_cycle_union_find(n, edges):
    parent = list(range(n))
    rank = [0] * n
    
    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])  # Path compression
        return parent[x]
    
    def union(x, y):
        px, py = find(x), find(y)
        if px == py:
            return False  # Same component → cycle!
        if rank[px] < rank[py]:
            px, py = py, px
        parent[py] = px
        if rank[px] == rank[py]:
            rank[px] += 1
        return True
    
    for u, v in edges:
        if not union(u, v):
            return True
    return False
```

> **Follow-up:** Why doesn't the undirected cycle detection use a color/state array?  
> **Answer:** For undirected graphs, the parent tracking is sufficient — a back edge (visiting an already-visited non-parent node) confirms a cycle. Color arrays (WHITE/GRAY/BLACK) are used in directed graphs where parent alone is insufficient.

---

### Q10. How do you detect a cycle in a directed graph?

**Answer:**

Use DFS with **3 states** (colors):
- `0 = WHITE` — not visited
- `1 = GRAY` — currently in DFS stack (being processed)
- `2 = BLACK` — fully processed

A cycle exists if we encounter a **GRAY** node during DFS.

```python
def has_cycle_directed(graph, n):
    color = [0] * n  # 0=white, 1=gray, 2=black
    
    def dfs(node):
        color[node] = 1  # Mark as in-progress (GRAY)
        
        for neighbor in graph[node]:
            if color[neighbor] == 1:
                return True   # Back edge → cycle!
            if color[neighbor] == 0:
                if dfs(neighbor):
                    return True
        
        color[node] = 2  # Mark as done (BLACK)
        return False
    
    for i in range(n):
        if color[i] == 0:
            if dfs(i):
                return True
    return False

# Time: O(V + E)  |  Space: O(V)
```

> **Follow-up:** What is a back edge in a directed graph?  
> **Answer:** A back edge is an edge from a descendant node to an ancestor in the DFS tree. In directed graphs, a back edge always indicates a cycle. For undirected graphs, any edge returning to a visited node (other than parent) is a back edge.

---

## 5. Topological Sort

---

### Q11. What is Topological Sort? When is it applicable?

**Answer:**

Topological Sort produces a **linear ordering** of vertices in a **Directed Acyclic Graph (DAG)** such that for every directed edge `u → v`, vertex `u` comes before `v`.

**Real-world use cases:**
- Build systems (compile order)
- Task scheduling with dependencies
- Course prerequisites
- Package managers

> ⚠️ Topological sort is only possible on a **DAG** (no cycles).

---

### Q12. Implement Topological Sort using DFS (Kahn's Algorithm & DFS approach).

**Answer:**

#### Method 1: DFS + Stack (Post-order)

```python
def topo_sort_dfs(graph, n):
    visited = [False] * n
    stack = []
    
    def dfs(node):
        visited[node] = True
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor)
        stack.append(node)  # Add AFTER all descendants processed
    
    for i in range(n):
        if not visited[i]:
            dfs(i)
    
    return stack[::-1]  # Reverse for topological order
```

#### Method 2: Kahn's Algorithm (BFS-based, using In-degree)

```python
from collections import deque

def kahn_topo_sort(graph, n):
    in_degree = [0] * n
    
    # Calculate in-degrees
    for u in range(n):
        for v in graph[u]:
            in_degree[v] += 1
    
    # Start with all nodes having in-degree 0
    queue = deque([i for i in range(n) if in_degree[i] == 0])
    order = []
    
    while queue:
        node = queue.popleft()
        order.append(node)
        
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    # If order doesn't include all nodes → cycle exists
    if len(order) != n:
        return []  # Cycle detected
    return order

# Time: O(V + E)  |  Space: O(V)
```

> **Follow-up:** How does Kahn's algorithm detect a cycle?  
> **Answer:** If the topological order produced doesn't contain all V vertices, it means some nodes were never added to the queue (they always had in-degree > 0 due to a cycle). So `len(order) != n` signals a cycle.

> **Follow-up:** Is topological sort unique?  
> **Answer:** Not necessarily. Multiple valid topological orderings can exist if there are nodes with no dependency between them (multiple nodes with in-degree 0 at the same time).

---

## 6. Shortest Path Algorithms

---

### Q13. How does BFS find the shortest path in an unweighted graph?

**Answer:**

BFS naturally explores nodes level by level (by distance from source). The **first time** a node is reached by BFS is via the shortest path.

```python
from collections import deque

def shortest_path_bfs(graph, start, end, n):
    visited = [False] * n
    parent = [-1] * n
    dist = [-1] * n
    
    queue = deque([start])
    visited[start] = True
    dist[start] = 0
    
    while queue:
        node = queue.popleft()
        if node == end:
            break
        for neighbor in graph[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                dist[neighbor] = dist[node] + 1
                parent[neighbor] = node
                queue.append(neighbor)
    
    if not visited[end]:
        return -1, []  # No path
    
    # Reconstruct path
    path = []
    cur = end
    while cur != -1:
        path.append(cur)
        cur = parent[cur]
    return dist[end], path[::-1]
```

---

### Q14. Explain Dijkstra's Algorithm. What are its limitations?

**Answer:**

Dijkstra finds the **shortest path from a source to all nodes** in a **weighted graph with non-negative weights**.

```
Algorithm:
1. Set dist[source] = 0, all others = ∞
2. Use a min-heap (priority queue) to always process the closest node
3. For each neighbor, relax the edge: if dist[u] + w(u,v) < dist[v], update dist[v]
4. Repeat until all nodes processed
```

```python
import heapq

def dijkstra(graph, start, n):
    """
    graph[u] = [(v, weight), ...]
    """
    dist = [float('inf')] * n
    dist[start] = 0
    min_heap = [(0, start)]  # (distance, node)
    
    while min_heap:
        d, u = heapq.heappop(min_heap)
        
        if d > dist[u]:  # Outdated entry
            continue
        
        for v, weight in graph[u]:
            new_dist = dist[u] + weight
            if new_dist < dist[v]:
                dist[v] = new_dist
                heapq.heappush(min_heap, (new_dist, v))
    
    return dist

# Time: O((V + E) log V)  |  Space: O(V)
```

**Limitations:**
- ❌ Does **not** work with **negative weight edges**
- ❌ Does not detect negative weight cycles

> **Follow-up:** Why does Dijkstra fail with negative weights?  
> **Answer:** Dijkstra greedily assumes once a node is finalized (popped from min-heap), its distance is optimal. With negative edges, a later path through a negative edge could give a shorter distance to an already-finalized node, breaking the greedy assumption.

---

### Q15. Explain Bellman-Ford Algorithm. When do you use it over Dijkstra?

**Answer:**

Bellman-Ford finds shortest paths even with **negative weights** and can **detect negative cycles**.

```python
def bellman_ford(n, edges, source):
    """
    edges: [(u, v, weight), ...]
    """
    dist = [float('inf')] * n
    dist[source] = 0
    
    # Relax all edges V-1 times
    for _ in range(n - 1):
        updated = False
        for u, v, w in edges:
            if dist[u] != float('inf') and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                updated = True
        if not updated:
            break  # Early termination
    
    # Check for negative weight cycle
    for u, v, w in edges:
        if dist[u] != float('inf') and dist[u] + w < dist[v]:
            return None  # Negative cycle detected!
    
    return dist

# Time: O(V × E)  |  Space: O(V)
```

| | Dijkstra | Bellman-Ford |
|---|---|---|
| Negative weights | ❌ No | ✅ Yes |
| Negative cycle detection | ❌ No | ✅ Yes |
| Time Complexity | O((V+E) log V) | O(V×E) |
| Best for | Non-negative weights | Negative weights |

> **Follow-up:** How does Bellman-Ford detect negative cycles?  
> **Answer:** After V-1 relaxations, all shortest paths are finalized (a shortest path has at most V-1 edges). If any edge can still be relaxed on the Vth pass, a negative cycle exists.

---

### Q16. What is Floyd-Warshall Algorithm?

**Answer:**

Floyd-Warshall finds **all-pairs shortest paths** in a graph.

```python
def floyd_warshall(n, dist):
    """
    dist[i][j] = edge weight between i and j (inf if no edge)
    dist[i][i] = 0
    """
    for k in range(n):       # Intermediate node
        for i in range(n):   # Source
            for j in range(n): # Destination
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    
    # Detect negative cycles: dist[i][i] < 0
    for i in range(n):
        if dist[i][i] < 0:
            return None  # Negative cycle
    
    return dist

# Time: O(V³)  |  Space: O(V²)
```

> **Follow-up:** What is the key intuition behind Floyd-Warshall?  
> **Answer:** For each pair (i,j), we check: is there a shorter path going through intermediate node k? We progressively allow more and more intermediate nodes. The DP state is `dp[k][i][j]` = shortest path from i to j using only nodes 0..k as intermediates.

---

## 7. Minimum Spanning Tree (MST)

---

### Q17. What is a Minimum Spanning Tree?

**Answer:**

An MST of a connected, undirected, weighted graph is a **spanning tree** (connects all vertices) with the **minimum total edge weight**.

Properties:
- Has exactly **V-1 edges**
- No cycles
- May not be unique (if equal weight edges exist)

**Two classic algorithms:** Kruskal's and Prim's

---

### Q18. Implement Kruskal's Algorithm.

**Answer:**

Kruskal's uses a **greedy + Union-Find** approach: sort all edges by weight, add each edge if it doesn't form a cycle.

```python
def kruskal_mst(n, edges):
    """
    edges: [(weight, u, v), ...]
    Returns: (total_weight, mst_edges)
    """
    edges.sort()  # Sort by weight
    parent = list(range(n))
    rank = [0] * n
    
    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]
    
    def union(x, y):
        px, py = find(x), find(y)
        if px == py:
            return False  # Would form cycle
        if rank[px] < rank[py]:
            px, py = py, px
        parent[py] = px
        if rank[px] == rank[py]:
            rank[px] += 1
        return True
    
    mst = []
    total_weight = 0
    
    for weight, u, v in edges:
        if union(u, v):
            mst.append((u, v, weight))
            total_weight += weight
            if len(mst) == n - 1:
                break
    
    return total_weight, mst

# Time: O(E log E)  |  Space: O(V)
```

> **Follow-up:** What data structure makes Kruskal's efficient?  
> **Answer:** **Union-Find (Disjoint Set Union)** with path compression and union by rank. It makes `find` and `union` operations nearly O(1) (amortized O(α(n)), where α is the inverse Ackermann function).

---

### Q19. Implement Prim's Algorithm.

**Answer:**

Prim's grows the MST from a starting vertex, always adding the **cheapest edge** connecting the tree to a non-tree vertex.

```python
import heapq

def prim_mst(graph, n, start=0):
    """
    graph[u] = [(v, weight), ...]
    """
    visited = [False] * n
    min_heap = [(0, start, -1)]  # (weight, node, parent)
    total_weight = 0
    mst_edges = []
    
    while min_heap and len(mst_edges) < n - 1:
        weight, u, parent = heapq.heappop(min_heap)
        
        if visited[u]:
            continue
        
        visited[u] = True
        total_weight += weight
        if parent != -1:
            mst_edges.append((parent, u, weight))
        
        for v, w in graph[u]:
            if not visited[v]:
                heapq.heappush(min_heap, (w, v, u))
    
    return total_weight, mst_edges

# Time: O(E log V)  |  Space: O(V + E)
```

| | Kruskal's | Prim's |
|---|---|---|
| Approach | Edge-based | Vertex-based |
| Data Structure | Union-Find | Min-Heap |
| Best for | Sparse graphs | Dense graphs |
| Time | O(E log E) | O(E log V) |

---

## 8. Connected Components

---

### Q20. How do you find connected components in an undirected graph?

**Answer:**

Run DFS/BFS from every unvisited node — each new traversal finds a new component.

```python
def count_components(graph, n):
    visited = [False] * n
    component_id = [-1] * n
    count = 0
    
    def dfs(node, comp):
        visited[node] = True
        component_id[node] = comp
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor, comp)
    
    for i in range(n):
        if not visited[i]:
            dfs(i, count)
            count += 1
    
    return count, component_id

# Time: O(V + E)  |  Space: O(V)
```

> **Follow-up:** Can you solve this with Union-Find?  
> **Answer:** Yes. Union all connected nodes, then count distinct roots. This is often simpler for dynamic graphs where edges are added one by one.

---

### Q21. What are Strongly Connected Components (SCCs)? How do you find them?

**Answer:**

In a **directed graph**, an SCC is a maximal subgraph where every vertex is reachable from every other vertex.

**Kosaraju's Algorithm:**

```python
def kosaraju_scc(graph, n):
    """
    Step 1: Run DFS on original graph, push to stack in finish order
    Step 2: Transpose the graph (reverse all edges)
    Step 3: Run DFS on transposed graph in reverse finish order
    """
    visited = [False] * n
    finish_order = []
    
    def dfs1(node):
        visited[node] = True
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs1(neighbor)
        finish_order.append(node)
    
    for i in range(n):
        if not visited[i]:
            dfs1(i)
    
    # Build transposed graph
    transposed = [[] for _ in range(n)]
    for u in range(n):
        for v in graph[u]:
            transposed[v].append(u)
    
    visited = [False] * n
    sccs = []
    
    def dfs2(node, component):
        visited[node] = True
        component.append(node)
        for neighbor in transposed[node]:
            if not visited[neighbor]:
                dfs2(neighbor, component)
    
    while finish_order:
        node = finish_order.pop()
        if not visited[node]:
            component = []
            dfs2(node, component)
            sccs.append(component)
    
    return sccs

# Time: O(V + E)  |  Space: O(V)
```

> **Follow-up:** What's the difference between Kosaraju's and Tarjan's algorithm for SCCs?  
> **Answer:** Both run in O(V+E). Kosaraju's requires two DFS passes and a transposed graph. Tarjan's finds SCCs in a **single DFS pass** using a stack and low-link values — generally preferred in practice for its lower constant factor.

---

## 9. Bipartite Graphs

---

### Q22. How do you check if a graph is bipartite?

**Answer:**

A graph is **bipartite** if its nodes can be colored with **2 colors** such that no two adjacent nodes share the same color. It is bipartite if and only if it contains **no odd-length cycles**.

Use BFS/DFS with 2-coloring:

```python
from collections import deque

def is_bipartite(graph, n):
    color = [-1] * n
    
    def bfs(start):
        queue = deque([start])
        color[start] = 0
        
        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if color[neighbor] == -1:
                    color[neighbor] = 1 - color[node]  # Flip color
                    queue.append(neighbor)
                elif color[neighbor] == color[node]:
                    return False  # Same color → not bipartite
        return True
    
    for i in range(n):
        if color[i] == -1:
            if not bfs(i):
                return False
    return True

# Time: O(V + E)  |  Space: O(V)
```

> **Follow-up:** Is a tree always bipartite?  
> **Answer:** Yes! A tree has no cycles at all, so it can never have an odd-length cycle. You can always 2-color a tree by alternating colors level by level.

---

## 10. Advanced Topics

---

### Q23. What are Articulation Points and Bridges?

**Answer:**

- **Articulation Point (Cut Vertex):** A node whose removal disconnects the graph.
- **Bridge (Cut Edge):** An edge whose removal disconnects the graph.

Both are found using DFS with **discovery time** and **low values**:

```python
def find_bridges(graph, n):
    disc = [-1] * n
    low = [-1] * n
    bridges = []
    timer = [0]
    
    def dfs(u, parent):
        disc[u] = low[u] = timer[0]
        timer[0] += 1
        
        for v in graph[u]:
            if disc[v] == -1:  # Tree edge
                dfs(v, u)
                low[u] = min(low[u], low[v])
                if low[v] > disc[u]:
                    bridges.append((u, v))  # Bridge found
            elif v != parent:  # Back edge
                low[u] = min(low[u], disc[v])
    
    for i in range(n):
        if disc[i] == -1:
            dfs(i, -1)
    
    return bridges
```

> **Follow-up:** What is the significance of `low[v] > disc[u]` for bridge detection?  
> **Answer:** `low[v]` represents the earliest discovered ancestor reachable from v's subtree. If `low[v] > disc[u]`, the subtree rooted at v cannot reach u or anything before u without using the edge (u, v) — making it a bridge.

---

### Q24. Explain Euler Path and Euler Circuit.

**Answer:**

- **Euler Path:** A path that visits **every edge exactly once**.
- **Euler Circuit:** An Euler path that **starts and ends at the same vertex**.

**Conditions (Undirected):**
- Euler Circuit exists ↔ graph is connected + **all vertices have even degree**
- Euler Path exists ↔ graph is connected + **exactly 2 vertices have odd degree**

**Conditions (Directed):**
- Euler Circuit ↔ connected + `in-degree == out-degree` for all vertices
- Euler Path ↔ connected + exactly one vertex has `out-degree - in-degree = 1` (start) and one has `in-degree - out-degree = 1` (end)

> **Follow-up:** How is Euler Path different from Hamiltonian Path?  
> **Answer:** Euler Path visits every **edge** exactly once. Hamiltonian Path visits every **vertex** exactly once. Finding Euler paths is solvable in O(V+E) (Hierholzer's algorithm), but finding Hamiltonian paths is NP-complete.

---

### Q25. What is a Hamiltonian Path / TSP (Travelling Salesman Problem)?

**Answer:**

- **Hamiltonian Path:** Visits every **vertex** exactly once.
- **Hamiltonian Cycle:** Hamiltonian path that returns to the start.
- **TSP:** Find the **shortest Hamiltonian cycle** in a weighted graph.

TSP is **NP-hard**. Exact solution uses bitmask DP:

```python
def tsp_dp(dist, n):
    """
    dist[i][j] = distance from i to j
    Returns minimum cost to visit all nodes starting from 0
    """
    INF = float('inf')
    # dp[mask][i] = min cost to reach node i having visited nodes in mask
    dp = [[INF] * n for _ in range(1 << n)]
    dp[1][0] = 0  # Start at node 0, only node 0 visited
    
    for mask in range(1 << n):
        for u in range(n):
            if dp[mask][u] == INF:
                continue
            if not (mask >> u & 1):
                continue
            for v in range(n):
                if mask >> v & 1:
                    continue  # Already visited
                new_mask = mask | (1 << v)
                new_cost = dp[mask][u] + dist[u][v]
                if new_cost < dp[new_mask][v]:
                    dp[new_mask][v] = new_cost
    
    full_mask = (1 << n) - 1
    return min(dp[full_mask][i] + dist[i][0] for i in range(1, n))

# Time: O(2^V × V²)  |  Space: O(2^V × V)
```

---

## 11. Classic Coding Problems

---

### Q26. Number of Islands (LeetCode 200)

**Problem:** Count islands in a grid (connected groups of `'1'`s).

```python
def numIslands(grid):
    if not grid:
        return 0
    
    rows, cols = len(grid), len(grid[0])
    count = 0
    
    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != '1':
            return
        grid[r][c] = '0'  # Mark as visited
        dfs(r+1, c)
        dfs(r-1, c)
        dfs(r, c+1)
        dfs(r, c-1)
    
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                dfs(r, c)
                count += 1
    
    return count

# Time: O(M × N)  |  Space: O(M × N) stack
```

> **Follow-up:** How would you solve this with Union-Find?  
> **Answer:** Assign each `'1'` cell a node id = `r * cols + c`. Union adjacent `'1'` cells. Count distinct components. UF approach is preferred when you need to process cells dynamically (streaming input).

---

### Q27. Course Schedule (LeetCode 207) — Cycle Detection in Directed Graph

**Problem:** Can you finish all courses given prerequisites?

```python
from collections import deque

def canFinish(numCourses, prerequisites):
    graph = [[] for _ in range(numCourses)]
    in_degree = [0] * numCourses
    
    for course, prereq in prerequisites:
        graph[prereq].append(course)
        in_degree[course] += 1
    
    queue = deque([i for i in range(numCourses) if in_degree[i] == 0])
    completed = 0
    
    while queue:
        course = queue.popleft()
        completed += 1
        for next_course in graph[course]:
            in_degree[next_course] -= 1
            if in_degree[next_course] == 0:
                queue.append(next_course)
    
    return completed == numCourses  # True if no cycle

# Time: O(V + E)  |  Space: O(V + E)
```

---

### Q28. Word Ladder (LeetCode 127) — Shortest Transformation Sequence

```python
from collections import deque, defaultdict

def ladderLength(beginWord, endWord, wordList):
    word_set = set(wordList)
    if endWord not in word_set:
        return 0
    
    # Build pattern → words mapping
    pattern_map = defaultdict(list)
    all_words = wordList + [beginWord]
    for word in all_words:
        for i in range(len(word)):
            pattern = word[:i] + '*' + word[i+1:]
            pattern_map[pattern].append(word)
    
    visited = {beginWord}
    queue = deque([(beginWord, 1)])
    
    while queue:
        word, length = queue.popleft()
        for i in range(len(word)):
            pattern = word[:i] + '*' + word[i+1:]
            for neighbor in pattern_map[pattern]:
                if neighbor == endWord:
                    return length + 1
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, length + 1))
    
    return 0

# Time: O(M² × N)  |  Space: O(M² × N)  where M=word length, N=number of words
```

---

### Q29. Network Delay Time (LeetCode 743) — Dijkstra

```python
import heapq

def networkDelayTime(times, n, k):
    graph = [[] for _ in range(n + 1)]
    for u, v, w in times:
        graph[u].append((v, w))
    
    dist = [float('inf')] * (n + 1)
    dist[k] = 0
    heap = [(0, k)]
    
    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(heap, (dist[v], v))
    
    max_dist = max(dist[1:])
    return max_dist if max_dist != float('inf') else -1
```

---

### Q30. Clone Graph (LeetCode 133)

```python
def cloneGraph(node):
    if not node:
        return None
    
    cloned = {}
    
    def dfs(n):
        if n in cloned:
            return cloned[n]
        
        clone = Node(n.val)
        cloned[n] = clone
        
        for neighbor in n.neighbors:
            clone.neighbors.append(dfs(neighbor))
        
        return clone
    
    return dfs(node)
```

---

## 12. System Design with Graphs

---

### Q31. How are graphs used in real-world systems?

**Answer:**

| System | Graph Type | Use Case |
|---|---|---|
| **Google Maps / GPS** | Weighted Directed | Shortest path (Dijkstra/A*) |
| **Social Networks** | Undirected | Friend recommendations, communities |
| **Web Crawling** | Directed | PageRank, link analysis |
| **Dependency Managers** | DAG | Package install order (topo sort) |
| **Recommendation Systems** | Bipartite | User ↔ Product matching |
| **Fraud Detection** | Directed/Weighted | Anomalous transaction paths |
| **Flight Networks** | Weighted Directed | Route optimization |
| **Compiler** | DAG | Expression trees, CFG |
| **Git** | DAG | Commit history, merge branches |
| **Network Routing** | Weighted | OSPF uses Dijkstra |

---

### Q32. How would you design a "Shortest Path" feature in a maps app?

**Answer:**

**Key Design Decisions:**

1. **Graph Representation:** Adjacency list with road segments as edges, intersections as vertices. Weights = travel time or distance.

2. **Algorithm Choice:**
   - Basic: Dijkstra's O((V+E) log V)
   - Bidirectional Dijkstra for real maps (meet in middle)
   - **A\* with heuristic** (euclidean distance) for significantly faster performance

3. **Preprocessing for Scale:**
   - **Contraction Hierarchies:** Pre-process shortcuts between important nodes
   - Partition map into regions, precompute inter-region paths

4. **Real-time Updates:**
   - Traffic = dynamic edge weights
   - Use incremental re-computation, not full re-run

5. **Data Structure:**
   - Store road network in spatial databases (PostGIS)
   - In-memory graph for routing engine
   - Cache frequently-requested routes

---

## 📌 Quick Reference: Algorithm Complexity Summary

| Algorithm | Time | Space | Use Case |
|---|---|---|---|
| BFS | O(V+E) | O(V) | Shortest path (unweighted), levels |
| DFS | O(V+E) | O(V) | Cycle detection, topo sort, SCC |
| Dijkstra | O((V+E) log V) | O(V) | Shortest path (non-negative weights) |
| Bellman-Ford | O(V×E) | O(V) | Shortest path (negative weights) |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs shortest paths |
| Kruskal's | O(E log E) | O(V) | MST (sparse graphs) |
| Prim's | O(E log V) | O(V) | MST (dense graphs) |
| Topo Sort (DFS) | O(V+E) | O(V) | DAG ordering |
| Kahn's Algorithm | O(V+E) | O(V) | Topo sort + cycle detection |
| Kosaraju's SCC | O(V+E) | O(V) | Strongly connected components |
| TSP (Bitmask DP) | O(2^V × V²) | O(2^V × V) | Hamiltonian cycle (small V) |

---

## 🔑 Key Interview Tips

1. **Always clarify:** Is the graph directed or undirected? Weighted or unweighted? Can it have cycles?
2. **Handle disconnected graphs:** Always loop over all nodes for DFS/BFS, not just from node 0.
3. **Visited array is crucial:** Prevent infinite loops — always use it.
4. **Choose representation wisely:** Adjacency list for sparse (most interview problems), matrix for dense.
5. **Common graph patterns:**
   - Grid problems → BFS/DFS with 4-directional movement
   - "Minimum steps" → BFS
   - "All possible paths" → DFS + backtracking
   - "Dependencies / ordering" → Topological Sort
   - "Grouping / components" → Union-Find or DFS
6. **Edge cases:** Empty graph, single node, self-loops, multiple edges.

---

*Made for Interview Preparation — Graph DSA from Scratch to Advanced*
