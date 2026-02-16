# Graph Data Structure - Complete Guide

## Table of Contents
- [Graph Fundamentals](#graph-fundamentals)
- [Graph Representations](#graph-representations)
- [Graph Traversal Algorithms](#graph-traversal-algorithms)
- [Shortest Path Algorithms](#shortest-path-algorithms)
- [Minimum Spanning Tree](#minimum-spanning-tree)
- [Topological Sort](#topological-sort)
- [Cycle Detection](#cycle-detection)
- [Advanced Graph Algorithms](#advanced-graph-algorithms)
- [LeetCode Problems - Easy](#leetcode-problems---easy)
- [LeetCode Problems - Medium](#leetcode-problems---medium)
- [LeetCode Problems - Hard](#leetcode-problems---hard)

---

# Graph Fundamentals

## What is a Graph?

**Graph:** Collection of nodes (vertices) connected by edges.

**Components:**
- **Vertices (V):** Nodes
- **Edges (E):** Connections between nodes

## Visual Representation

```
Undirected Graph:
    1 --- 2
    |     |
    3 --- 4

Directed Graph:
    1 → 2
    ↓   ↓
    3 → 4
```

## Types of Graphs

### 1. Based on Direction

**Undirected Graph:**
```
A --- B
  \   /
    C
```
- Edges have no direction
- If A→B exists, B→A also exists

**Directed Graph (Digraph):**
```
A → B
  ↘ ↓
    C
```
- Edges have direction
- A→B doesn't mean B→A

### 2. Based on Weights

**Unweighted Graph:**
```
A --- B
|     |
C --- D
```

**Weighted Graph:**
```
    5
A ----- B
|       |
3       2
|       |
C ----- D
    4
```

### 3. Based on Connectivity

**Connected Graph:** Path exists between every pair of vertices

**Disconnected Graph:**
```
A --- B    C --- D
```

**Complete Graph:** Every vertex connected to every other vertex
```
    A
   /|\
  B-C-D
   \|/
```

**Cyclic Graph:** Contains at least one cycle
```
A → B
↑   ↓
D ← C
```

**Acyclic Graph:** No cycles

**DAG (Directed Acyclic Graph):**
```
A → B → D
↓   ↓
C → E
```

## Graph Terminology

| Term | Definition |
|------|------------|
| **Vertex/Node** | Point in graph |
| **Edge** | Connection between vertices |
| **Degree** | Number of edges connected to vertex |
| **In-degree** | Number of incoming edges (directed) |
| **Out-degree** | Number of outgoing edges (directed) |
| **Path** | Sequence of vertices connected by edges |
| **Cycle** | Path that starts and ends at same vertex |
| **Connected** | Path exists between every vertex pair |
| **Component** | Maximal connected subgraph |
| **Spanning Tree** | Subgraph that is a tree and includes all vertices |

---

# Graph Representations

## 1. Adjacency Matrix

**2D array where matrix[i][j] = 1 if edge exists**

```cpp
// Undirected Graph
    0   1   2   3
0 [ 0   1   1   0 ]
1 [ 1   0   1   1 ]
2 [ 1   1   0   1 ]
3 [ 0   1   1   0 ]

Graph:
    0 --- 1
    |     |
    2 --- 3

// Implementation
class GraphMatrix {
    vector<vector<int>> adj;
    int V;
    
public:
    GraphMatrix(int vertices) : V(vertices) {
        adj.resize(V, vector<int>(V, 0));
    }
    
    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;  // For undirected graph
    }
    
    void addEdgeDirected(int u, int v) {
        adj[u][v] = 1;  // For directed graph
    }
    
    void addWeightedEdge(int u, int v, int weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;
    }
    
    void print() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
};
```

**Advantages:**
- O(1) edge lookup
- Easy to implement

**Disadvantages:**
- O(V²) space
- Inefficient for sparse graphs

## 2. Adjacency List

**Array of lists where list[i] contains neighbors of vertex i**

```cpp
Graph:
    0 --- 1
    |     |
    2 --- 3

Adjacency List:
0 → [1, 2]
1 → [0, 2, 3]
2 → [0, 1, 3]
3 → [1, 2]

// Implementation
class GraphList {
    vector<vector<int>> adj;
    int V;
    
public:
    GraphList(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // For undirected
    }
    
    void addEdgeDirected(int u, int v) {
        adj[u].push_back(v);  // For directed
    }
    
    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << " → ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    vector<int>& getNeighbors(int v) {
        return adj[v];
    }
};

// Weighted Graph
class WeightedGraph {
    vector<vector<pair<int, int>>> adj;  // {neighbor, weight}
    int V;
    
public:
    WeightedGraph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
};
```

**Advantages:**
- O(V + E) space
- Efficient for sparse graphs
- Easy to iterate neighbors

**Disadvantages:**
- O(V) edge lookup in worst case

## 3. Edge List

```cpp
struct Edge {
    int src, dest, weight;
};

class EdgeList {
    vector<Edge> edges;
    int V;
    
public:
    EdgeList(int vertices) : V(vertices) {}
    
    void addEdge(int u, int v, int w = 1) {
        edges.push_back({u, v, w});
    }
    
    vector<Edge>& getEdges() {
        return edges;
    }
};
```

**Use Cases:** Kruskal's algorithm, edge-centric operations

---

# Graph Traversal Algorithms

## 1. Breadth-First Search (BFS)

**Level-by-level traversal using queue**

```cpp
class Solution {
public:
    // BFS from source
    void BFS(vector<vector<int>>& adj, int start) {
        int n = adj.size();
        vector<bool> visited(n, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            
            // Visit all neighbors
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
    
    // BFS with levels
    vector<vector<int>> BFSLevels(vector<vector<int>>& adj, int start) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<vector<int>> levels;
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();
                currentLevel.push_back(node);
                
                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            levels.push_back(currentLevel);
        }
        
        return levels;
    }
    
    // BFS for disconnected graph
    void BFSComplete(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                BFSComponent(adj, i, visited);
            }
        }
    }
    
    void BFSComponent(vector<vector<int>>& adj, int start, vector<bool>& visited) {
        queue<int> q;
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

// Time: O(V + E)
// Space: O(V)
```

**BFS Applications:**
- Shortest path in unweighted graph
- Level order traversal
- Check if graph is bipartite
- Find connected components

## 2. Depth-First Search (DFS)

**Explores as far as possible before backtracking**

```cpp
class Solution {
public:
    // DFS Recursive
    void DFS(vector<vector<int>>& adj, int start) {
        int n = adj.size();
        vector<bool> visited(n, false);
        DFSUtil(adj, start, visited);
    }
    
    void DFSUtil(vector<vector<int>>& adj, int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DFSUtil(adj, neighbor, visited);
            }
        }
    }
    
    // DFS Iterative (using stack)
    void DFSIterative(vector<vector<int>>& adj, int start) {
        int n = adj.size();
        vector<bool> visited(n, false);
        stack<int> st;
        
        st.push(start);
        
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (visited[node]) continue;
            
            visited[node] = true;
            cout << node << " ";
            
            // Push neighbors in reverse order for same order as recursive
            for (int i = adj[node].size() - 1; i >= 0; i--) {
                if (!visited[adj[node][i]]) {
                    st.push(adj[node][i]);
                }
            }
        }
    }
    
    // DFS for disconnected graph
    void DFSComplete(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFSUtil(adj, i, visited);
                cout << endl;
            }
        }
    }
    
    // DFS with path tracking
    void DFSPath(vector<vector<int>>& adj, int start, int end) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> path;
        
        if (DFSPathUtil(adj, start, end, visited, path)) {
            cout << "Path found: ";
            for (int node : path) cout << node << " ";
            cout << endl;
        } else {
            cout << "No path exists" << endl;
        }
    }
    
    bool DFSPathUtil(vector<vector<int>>& adj, int current, int end,
                     vector<bool>& visited, vector<int>& path) {
        visited[current] = true;
        path.push_back(current);
        
        if (current == end) return true;
        
        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                if (DFSPathUtil(adj, neighbor, end, visited, path)) {
                    return true;
                }
            }
        }
        
        path.pop_back();
        return false;
    }
};

// Time: O(V + E)
// Space: O(V) for recursion stack
```

**DFS Applications:**
- Cycle detection
- Topological sorting
- Finding connected components
- Path finding
- Solving puzzles (mazes)

---

# Shortest Path Algorithms

## 1. Dijkstra's Algorithm

**Shortest path from source to all vertices (non-negative weights)**

```cpp
class Dijkstra {
public:
    vector<int> dijkstra(vector<vector<pair<int, int>>>& adj, int src) {
        int n = adj.size();
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        
        dist[src] = 0;
        pq.push({0, src});  // {distance, node}
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // With path reconstruction
    pair<vector<int>, vector<int>> dijkstraWithPath(
        vector<vector<pair<int, int>>>& adj, int src) {
        int n = adj.size();
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return {dist, parent};
    }
    
    vector<int> getPath(vector<int>& parent, int dest) {
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

// Time: O((V + E) log V)
// Space: O(V)
```

## 2. Bellman-Ford Algorithm

**Shortest path with negative weights (detects negative cycles)**

```cpp
class BellmanFord {
public:
    vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < n - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0], v = edge[1], w = edge[2];
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        // Check for negative cycle
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                cout << "Negative cycle detected!" << endl;
                return {};
            }
        }
        
        return dist;
    }
};

// Time: O(V × E)
// Space: O(V)
```

## 3. Floyd-Warshall Algorithm

**All pairs shortest paths**

```cpp
class FloydWarshall {
public:
    vector<vector<int>> floydWarshall(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> dist = graph;
        
        // Initialize
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) dist[i][j] = 0;
                else if (dist[i][j] == 0) dist[i][j] = INT_MAX;
            }
        }
        
        // Floyd-Warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        return dist;
    }
};

// Time: O(V³)
// Space: O(V²)
```

---

# Minimum Spanning Tree

## 1. Kruskal's Algorithm

**Uses Union-Find (Disjoint Set)**

```cpp
class UnionFind {
    vector<int> parent, rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

class Kruskal {
public:
    int kruskalMST(int n, vector<vector<int>>& edges) {
        // Sort edges by weight
        sort(edges.begin(), edges.end(), 
             [](auto& a, auto& b) { return a[2] < b[2]; });
        
        UnionFind uf(n);
        int mstWeight = 0;
        int edgesUsed = 0;
        
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            
            if (uf.unite(u, v)) {
                mstWeight += w;
                edgesUsed++;
                
                if (edgesUsed == n - 1) break;
            }
        }
        
        return mstWeight;
    }
};

// Time: O(E log E)
// Space: O(V)
```

## 2. Prim's Algorithm

```cpp
class Prim {
public:
    int primMST(vector<vector<pair<int, int>>>& adj) {
        int n = adj.size();
        vector<bool> inMST(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        
        int mstWeight = 0;
        pq.push({0, 0});  // {weight, node}
        
        while (!pq.empty()) {
            auto [weight, u] = pq.top();
            pq.pop();
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            mstWeight += weight;
            
            for (auto [v, w] : adj[u]) {
                if (!inMST[v]) {
                    pq.push({w, v});
                }
            }
        }
        
        return mstWeight;
    }
};

// Time: O((V + E) log V)
// Space: O(V)
```

---

# Topological Sort

**Linear ordering of vertices in DAG**

```cpp
class TopologicalSort {
public:
    // Using DFS
    vector<int> topologicalSortDFS(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, i, visited, st);
            }
        }
        
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        return result;
    }
    
    void dfs(vector<vector<int>>& adj, int node, 
             vector<bool>& visited, stack<int>& st) {
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(adj, neighbor, visited, st);
            }
        }
        
        st.push(node);
    }
    
    // Using BFS (Kahn's Algorithm)
    vector<int> topologicalSortBFS(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<int> indegree(n, 0);
        
        // Calculate indegree
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);
            
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Check for cycle
        if (result.size() != n) {
            return {};  // Cycle detected
        }
        
        return result;
    }
};

// Time: O(V + E)
// Space: O(V)
```

---

# Cycle Detection

## Undirected Graph

```cpp
class CycleDetection {
public:
    // Using DFS
    bool hasCycleDFS(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(adj, i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool dfs(vector<vector<int>>& adj, int node, 
             vector<bool>& visited, int parent) {
        visited[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(adj, neighbor, visited, node)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;  // Cycle found
            }
        }
        return false;
    }
    
    // Using BFS
    bool hasCycleBFS(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (bfs(adj, i, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool bfs(vector<vector<int>>& adj, int start, vector<bool>& visited) {
        queue<pair<int, int>> q;  // {node, parent}
        visited[start] = true;
        q.push({start, -1});
        
        while (!q.empty()) {
            auto [node, parent] = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, node});
                } else if (neighbor != parent) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

## Directed Graph

```cpp
class DirectedCycleDetection {
public:
    bool hasCycle(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<bool> recStack(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(adj, i, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool dfs(vector<vector<int>>& adj, int node,
             vector<bool>& visited, vector<bool>& recStack) {
        visited[node] = true;
        recStack[node] = true;
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (dfs(adj, neighbor, visited, recStack)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                return true;  // Back edge found
            }
        }
        
        recStack[node] = false;
        return false;
    }
};
```

---

# Advanced Graph Algorithms

## Strongly Connected Components (Kosaraju's Algorithm)

```cpp
class SCC {
public:
    vector<vector<int>> findSCCs(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        stack<int> st;
        
        // Step 1: Fill stack with finish times
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs1(adj, i, visited, st);
            }
        }
        
        // Step 2: Create transpose graph
        vector<vector<int>> transpose(n);
        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                transpose[v].push_back(u);
            }
        }
        
        // Step 3: DFS on transpose in stack order
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (!visited[node]) {
                vector<int> component;
                dfs2(transpose, node, visited, component);
                sccs.push_back(component);
            }
        }
        
        return sccs;
    }
    
    void dfs1(vector<vector<int>>& adj, int node,
              vector<bool>& visited, stack<int>& st) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs1(adj, neighbor, visited, st);
            }
        }
        st.push(node);
    }
    
    void dfs2(vector<vector<int>>& adj, int node,
              vector<bool>& visited, vector<int>& component) {
        visited[node] = true;
        component.push_back(node);
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs2(adj, neighbor, visited, component);
            }
        }
    }
};
```

## Bridges in Graph

```cpp
class Bridges {
    int timer = 0;
    
public:
    vector<vector<int>> findBridges(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> disc(n), low(n);
        vector<vector<int>> bridges;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, i, -1, visited, disc, low, bridges);
            }
        }
        
        return bridges;
    }
    
    void dfs(vector<vector<int>>& adj, int u, int parent,
             vector<bool>& visited, vector<int>& disc, vector<int>& low,
             vector<vector<int>>& bridges) {
        visited[u] = true;
        disc[u] = low[u] = timer++;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (visited[v]) {
                low[u] = min(low[u], disc[v]);
            } else {
                dfs(adj, v, u, visited, disc, low, bridges);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
        }
    }
};
```

## Articulation Points

```cpp
class ArticulationPoints {
    int timer = 0;
    
public:
    vector<int> findArticulationPoints(vector<vector<int>>& adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> disc(n), low(n);
        vector<bool> isAP(n, false);
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, i, -1, visited, disc, low, isAP);
            }
        }
        
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (isAP[i]) result.push_back(i);
        }
        return result;
    }
    
    void dfs(vector<vector<int>>& adj, int u, int parent,
             vector<bool>& visited, vector<int>& disc, vector<int>& low,
             vector<bool>& isAP) {
        visited[u] = true;
        disc[u] = low[u] = timer++;
        int children = 0;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (visited[v]) {
                low[u] = min(low[u], disc[v]);
            } else {
                children++;
                dfs(adj, v, u, visited, disc, low, isAP);
                low[u] = min(low[u], low[v]);
                
                // Check if u is articulation point
                if (parent != -1 && low[v] >= disc[u]) {
                    isAP[u] = true;
                }
            }
        }
        
        // Root is AP if it has more than one child
        if (parent == -1 && children > 1) {
            isAP[u] = true;
        }
    }
};
```

---

# LeetCode Problems - Easy

## 1. Find Center of Star Graph (LeetCode 1791)

```cpp
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        // Center appears in all edges
        // Check first two edges
        if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) {
            return edges[0][0];
        }
        return edges[0][1];
    }
};

// Time: O(1)
// Space: O(1)
```

## 2. Find if Path Exists in Graph (LeetCode 1971)

```cpp
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        // BFS
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            if (node == destination) return true;
            
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return false;
    }
};

// Time: O(V + E)
// Space: O(V + E)
```

## 3. Find the Town Judge (LeetCode 997)

```cpp
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> trustCount(n + 1, 0);
        
        for (auto& t : trust) {
            trustCount[t[0]]--;  // Trusts someone
            trustCount[t[1]]++;  // Is trusted
        }
        
        for (int i = 1; i <= n; i++) {
            if (trustCount[i] == n - 1) {
                return i;
            }
        }
        
        return -1;
    }
};

// Time: O(E + V)
// Space: O(V)
```

## 4. Number of Connected Components (LeetCode 323)

```cpp
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, i, visited);
                count++;
            }
        }
        
        return count;
    }
    
    void dfs(vector<vector<int>>& adj, int node, vector<bool>& visited) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(adj, neighbor, visited);
            }
        }
    }
};

// Time: O(V + E)
// Space: O(V + E)
```

---

# LeetCode Problems - Medium

## 5. Number of Islands (LeetCode 200)

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    count++;
                }
            }
        }
        
        return count;
    }
    
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() ||
            grid[i][j] == '0') {
            return;
        }
        
        grid[i][j] = '0';  // Mark as visited
        
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }
};

// Time: O(M × N)
// Space: O(M × N) for recursion
```

## 6. Clone Graph (LeetCode 133)

```cpp
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> cloned;
        return dfs(node, cloned);
    }
    
    Node* dfs(Node* node, unordered_map<Node*, Node*>& cloned) {
        if (cloned.count(node)) return cloned[node];
        
        Node* clone = new Node(node->val);
        cloned[node] = clone;
        
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfs(neighbor, cloned));
        }
        
        return clone;
    }
};

// Time: O(V + E)
// Space: O(V)
```

## 7. Course Schedule (LeetCode 207)

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        int completed = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            completed++;
            
            for (int next : adj[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return completed == numCourses;
    }
};

// Time: O(V + E)
// Space: O(V + E)
```

## 8. Course Schedule II (LeetCode 210)

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int next : adj[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return order.size() == numCourses ? order : vector<int>{};
    }
};

// Time: O(V + E)
// Space: O(V + E)
```

## 9. Pacific Atlantic Water Flow (LeetCode 417)

```cpp
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty()) return {};
        
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        // DFS from Pacific Ocean borders
        for (int i = 0; i < m; i++) {
            dfs(heights, pacific, i, 0);
            dfs(heights, atlantic, i, n - 1);
        }
        
        for (int j = 0; j < n; j++) {
            dfs(heights, pacific, 0, j);
            dfs(heights, atlantic, m - 1, j);
        }
        
        // Find cells reachable by both oceans
        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        
        return result;
    }
    
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited,
             int i, int j) {
        visited[i][j] = true;
        
        int dirs[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (auto& dir : dirs) {
            int ni = i + dir[0], nj = j + dir[1];
            if (ni >= 0 && ni < heights.size() && nj >= 0 && nj < heights[0].size() &&
                !visited[ni][nj] && heights[ni][nj] >= heights[i][j]) {
                dfs(heights, visited, ni, nj);
            }
        }
    }
};

// Time: O(M × N)
// Space: O(M × N)
```

## 10. Network Delay Time (LeetCode 743)

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& time : times) {
            adj[time[0]].push_back({time[1], time[2]});
        }
        
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        
        dist[k] = 0;
        pq.push({0, k});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        int maxDist = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) return -1;
            maxDist = max(maxDist, dist[i]);
        }
        
        return maxDist;
    }
};

// Time: O((V + E) log V)
// Space: O(V + E)
```

---

# LeetCode Problems - Hard

## 11. Alien Dictionary (LeetCode 269)

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> indegree;
        
        // Initialize
        for (string& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }
        
        // Build graph
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i], word2 = words[i + 1];
            int minLen = min(word1.size(), word2.size());
            
            // Check invalid case
            if (word1.size() > word2.size() && 
                word1.substr(0, minLen) == word2.substr(0, minLen)) {
                return "";
            }
            
            for (int j = 0; j < minLen; j++) {
                if (word1[j] != word2[j]) {
                    if (!adj[word1[j]].count(word2[j])) {
                        adj[word1[j]].insert(word2[j]);
                        indegree[word2[j]]++;
                    }
                    break;
                }
            }
        }
        
        // Topological sort
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }
        
        string result;
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;
            
            for (char next : adj[c]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return result.size() == indegree.size() ? result : "";
    }
};

// Time: O(C) where C is total chars in all words
// Space: O(1) since at most 26 chars
```

## 12. Word Ladder (LeetCode 127)

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        while (!q.empty()) {
            auto [word, level] = q.front();
            q.pop();
            
            if (word == endWord) return level;
            
            for (int i = 0; i < word.size(); i++) {
                string temp = word;
                for (char c = 'a'; c <= 'z'; c++) {
                    temp[i] = c;
                    if (wordSet.count(temp)) {
                        q.push({temp, level + 1});
                        wordSet.erase(temp);
                    }
                }
            }
        }
        
        return 0;
    }
};

// Time: O(M² × N) where M is word length, N is wordList size
// Space: O(M × N)
```

## 13. Critical Connections (LeetCode 1192)

```cpp
class Solution {
    int timer = 0;
    
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        vector<bool> visited(n, false);
        vector<int> disc(n), low(n);
        vector<vector<int>> bridges;
        
        dfs(adj, 0, -1, visited, disc, low, bridges);
        
        return bridges;
    }
    
    void dfs(vector<vector<int>>& adj, int u, int parent,
             vector<bool>& visited, vector<int>& disc, vector<int>& low,
             vector<vector<int>>& bridges) {
        visited[u] = true;
        disc[u] = low[u] = timer++;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (visited[v]) {
                low[u] = min(low[u], disc[v]);
            } else {
                dfs(adj, v, u, visited, disc, low, bridges);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
        }
    }
};

// Time: O(V + E)
// Space: O(V + E)
```

---

**Master Graphs, Master Connections! 🌐**

## Key Takeaways

### Graph Problem Patterns

1. **Shortest Path:** BFS (unweighted), Dijkstra (weighted)
2. **Cycle Detection:** DFS with recursion stack
3. **Connected Components:** DFS/BFS with visited array
4. **Topological Sort:** Kahn's algorithm or DFS
5. **Minimum Spanning Tree:** Kruskal or Prim
6. **Bridges/Articulation Points:** Tarjan's algorithm

### Time Complexity Summary

| Algorithm | Time | Use Case |
|-----------|------|----------|
| BFS/DFS | O(V + E) | Traversal, Components |
| Dijkstra | O((V+E) log V) | Shortest path (non-negative) |
| Bellman-Ford | O(VE) | Shortest path (negative weights) |
| Floyd-Warshall | O(V³) | All pairs shortest path |
| Kruskal | O(E log E) | MST |
| Prim | O((V+E) log V) | MST |
| Topological Sort | O(V + E) | DAG ordering |

**Remember:** Choose the right graph representation and algorithm based on the problem constraints!
