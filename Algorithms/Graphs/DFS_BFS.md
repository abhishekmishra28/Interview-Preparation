# DFS and BFS in Graphs - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Graph Representation](#graph-representation)
- [Breadth-First Search (BFS)](#breadth-first-search-bfs)
- [Depth-First Search (DFS)](#depth-first-search-dfs)
- [BFS vs DFS Comparison](#bfs-vs-dfs-comparison)
- [Applications](#applications)
- [Practice Problems](#practice-problems)
- [Advanced Techniques](#advanced-techniques)

---

# Introduction

**Graph Traversal** means visiting all vertices in a graph systematically. The two fundamental approaches are:

- **BFS (Breadth-First Search):** Explores neighbors level by level
- **DFS (Depth-First Search):** Explores as far as possible before backtracking

## Why Learn These?

1. **Foundation for graph algorithms:** Shortest path, cycle detection, connectivity
2. **Interview favorite:** Appears in 60%+ of graph problems
3. **Problem-solving patterns:** Many problems reduce to BFS/DFS variations

---

# Graph Representation

Before traversing, we need to represent the graph in code.

## 1. Adjacency Matrix

```cpp
// n × n matrix where matrix[i][j] = 1 if edge exists
int graph[100][100];

// Example: 4 vertices
int n = 4;
graph[0][1] = 1;  // Edge from 0 to 1
graph[0][2] = 1;  // Edge from 0 to 2
graph[1][2] = 1;  // Edge from 1 to 2
graph[2][3] = 1;  // Edge from 2 to 3

// For weighted graphs
graph[0][1] = 5;  // Edge from 0 to 1 with weight 5
```

**Pros:**
- Simple to implement
- O(1) edge lookup
- Good for dense graphs

**Cons:**
- O(n²) space (wasteful for sparse graphs)
- O(n) to find all neighbors

## 2. Adjacency List (Most Common)

```cpp
// Vector of vectors - most flexible
vector<int> graph[100];  // or vector<vector<int>> graph(n);

// Example: 4 vertices
graph[0].push_back(1);  // Edge from 0 to 1
graph[0].push_back(2);  // Edge from 0 to 2
graph[1].push_back(2);  // Edge from 1 to 2
graph[2].push_back(3);  // Edge from 2 to 3

// For weighted graphs
vector<pair<int, int>> graph[100];  // {neighbor, weight}
graph[0].push_back({1, 5});  // Edge to vertex 1 with weight 5
```

**Pros:**
- O(V + E) space - efficient for sparse graphs
- Fast neighbor iteration
- Industry standard

**Cons:**
- O(degree(v)) to check if edge exists
- Slightly more complex

## 3. Edge List

```cpp
vector<pair<int, int>> edges;  // {from, to}
edges.push_back({0, 1});
edges.push_back({0, 2});
edges.push_back({1, 2});
edges.push_back({2, 3});

// For weighted graphs
vector<tuple<int, int, int>> edges;  // {from, to, weight}
```

**Use case:** Kruskal's algorithm, edge processing

---

# Breadth-First Search (BFS)

## Concept

BFS explores the graph **level by level** using a **queue**:
1. Start from source vertex
2. Visit all neighbors (level 1)
3. Visit neighbors of neighbors (level 2)
4. Continue until all reachable vertices are visited

## Visual Example

```
Graph:       0
           / | \
          1  2  3
          |    / \
          4   5   6

BFS from 0:
Level 0: [0]
Level 1: [1, 2, 3]
Level 2: [4, 5, 6]

Visit order: 0 → 1 → 2 → 3 → 4 → 5 → 6
```

## Basic Implementation

### Using Adjacency List

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(vector<int> graph[], int start, int n) {
    // Track visited vertices
    vector<bool> visited(n, false);
    
    // Queue for BFS
    queue<int> q;
    
    // Start from source
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        cout << current << " ";
        
        // Visit all neighbors
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n = 7;  // Number of vertices
    vector<int> graph[n];
    
    // Build graph
    graph[0] = {1, 2, 3};
    graph[1] = {0, 4};
    graph[2] = {0};
    graph[3] = {0, 5, 6};
    graph[4] = {1};
    graph[5] = {3};
    graph[6] = {3};
    
    BFS(graph, 0, n);  // Output: 0 1 2 3 4 5 6
    
    return 0;
}
```

## BFS with Distance/Level Tracking

```cpp
void BFS_with_distance(vector<int> graph[], int start, int n) {
    vector<int> distance(n, -1);  // -1 means not visited
    queue<int> q;
    
    distance[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        cout << "Vertex " << current << " at distance " << distance[current] << endl;
        
        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {  // Not visited
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
}
```

## BFS for Shortest Path (Unweighted Graph)

```cpp
vector<int> shortestPath(vector<int> graph[], int start, int end, int n) {
    vector<int> distance(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    
    distance[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (current == end) break;  // Found destination
        
        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    if (distance[end] == -1) return path;  // No path exists
    
    int node = end;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
    }
    
    reverse(path.begin(), path.end());
    return path;
}
```

## BFS for Disconnected Graphs

```cpp
void BFS_all_components(vector<int> graph[], int n) {
    vector<bool> visited(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // New component found
            cout << "Component starting from " << i << ": ";
            
            queue<int> q;
            visited[i] = true;
            q.push(i);
            
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                cout << current << " ";
                
                for (int neighbor : graph[current]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            cout << endl;
        }
    }
}
```

## Multi-Source BFS

Used for problems like "distance from nearest 0" in matrix.

```cpp
void multiSourceBFS(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    vector<vector<int>> distance(m, vector<int>(n, -1));
    
    // Add all sources to queue
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {  // Source
                q.push({i, j});
                distance[i][j] = 0;
            }
        }
    }
    
    // Standard BFS
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && distance[nx][ny] == -1) {
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}
```

## BFS Complexity

**Time Complexity:** O(V + E)
- Visit each vertex once: O(V)
- Explore each edge once: O(E)
- Total: O(V + E)

**Space Complexity:** O(V)
- Queue can hold up to V vertices
- Visited array: O(V)

---

# Depth-First Search (DFS)

## Concept

DFS explores the graph by going **as deep as possible** before backtracking:
1. Start from source vertex
2. Visit an unvisited neighbor
3. Recursively visit that neighbor's unvisited neighbors
4. Backtrack when no unvisited neighbors remain

## Visual Example

```
Graph:       0
           / | \
          1  2  3
          |    / \
          4   5   6

DFS from 0:
Path: 0 → 1 → 4 (backtrack) → 2 (backtrack) → 3 → 5 (backtrack) → 6

Visit order: 0 → 1 → 4 → 2 → 3 → 5 → 6
```

## Basic Implementation - Recursive

```cpp
#include <iostream>
#include <vector>
using namespace std;

void DFS_recursive(vector<int> graph[], int current, vector<bool>& visited) {
    // Mark current vertex as visited
    visited[current] = true;
    cout << current << " ";
    
    // Visit all unvisited neighbors
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            DFS_recursive(graph, neighbor, visited);
        }
    }
}

void DFS(vector<int> graph[], int start, int n) {
    vector<bool> visited(n, false);
    DFS_recursive(graph, start, visited);
}

int main() {
    int n = 7;
    vector<int> graph[n];
    
    // Build graph (same as BFS example)
    graph[0] = {1, 2, 3};
    graph[1] = {0, 4};
    graph[2] = {0};
    graph[3] = {0, 5, 6};
    graph[4] = {1};
    graph[5] = {3};
    graph[6] = {3};
    
    DFS(graph, 0, n);  // Output: 0 1 4 2 3 5 6
    
    return 0;
}
```

## DFS - Iterative (Using Stack)

```cpp
void DFS_iterative(vector<int> graph[], int start, int n) {
    vector<bool> visited(n, false);
    stack<int> s;
    
    s.push(start);
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        
        if (visited[current]) continue;
        
        visited[current] = true;
        cout << current << " ";
        
        // Push neighbors to stack (reverse order for same output as recursive)
        for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it) {
            if (!visited[*it]) {
                s.push(*it);
            }
        }
    }
}
```

## DFS with Discovery and Finish Times

Used in topological sort, detecting back edges, etc.

```cpp
int timer = 0;

void DFS_with_times(vector<int> graph[], int current, 
                    vector<bool>& visited,
                    vector<int>& discovery,
                    vector<int>& finish) {
    visited[current] = true;
    discovery[current] = ++timer;
    
    cout << "Discovered " << current << " at time " << timer << endl;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            DFS_with_times(graph, neighbor, visited, discovery, finish);
        }
    }
    
    finish[current] = ++timer;
    cout << "Finished " << current << " at time " << timer << endl;
}
```

## DFS for Path Finding

```cpp
bool DFS_find_path(vector<int> graph[], int current, int target,
                   vector<bool>& visited, vector<int>& path) {
    visited[current] = true;
    path.push_back(current);
    
    if (current == target) {
        return true;  // Path found
    }
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (DFS_find_path(graph, neighbor, target, visited, path)) {
                return true;
            }
        }
    }
    
    // Backtrack
    path.pop_back();
    return false;
}

vector<int> findPath(vector<int> graph[], int start, int end, int n) {
    vector<bool> visited(n, false);
    vector<int> path;
    
    DFS_find_path(graph, start, end, visited, path);
    return path;
}
```

## DFS for Cycle Detection (Undirected Graph)

```cpp
bool hasCycle_undirected(vector<int> graph[], int current, int parent,
                         vector<bool>& visited) {
    visited[current] = true;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (hasCycle_undirected(graph, neighbor, current, visited)) {
                return true;
            }
        }
        else if (neighbor != parent) {
            // Visited neighbor that's not the parent = cycle
            return true;
        }
    }
    
    return false;
}

bool detectCycle(vector<int> graph[], int n) {
    vector<bool> visited(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycle_undirected(graph, i, -1, visited)) {
                return true;
            }
        }
    }
    
    return false;
}
```

## DFS for Cycle Detection (Directed Graph)

```cpp
bool hasCycle_directed(vector<int> graph[], int current,
                       vector<int>& color) {
    // Color: 0 = white (unvisited), 1 = gray (in progress), 2 = black (done)
    color[current] = 1;  // Mark as in progress
    
    for (int neighbor : graph[current]) {
        if (color[neighbor] == 1) {
            // Back edge found = cycle
            return true;
        }
        if (color[neighbor] == 0) {
            if (hasCycle_directed(graph, neighbor, color)) {
                return true;
            }
        }
    }
    
    color[current] = 2;  // Mark as done
    return false;
}

bool detectCycleDirected(vector<int> graph[], int n) {
    vector<int> color(n, 0);
    
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (hasCycle_directed(graph, i, color)) {
                return true;
            }
        }
    }
    
    return false;
}
```

## DFS for Connected Components

```cpp
void DFS_component(vector<int> graph[], int current, 
                   vector<bool>& visited, vector<int>& component) {
    visited[current] = true;
    component.push_back(current);
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            DFS_component(graph, neighbor, visited, component);
        }
    }
}

vector<vector<int>> findConnectedComponents(vector<int> graph[], int n) {
    vector<bool> visited(n, false);
    vector<vector<int>> components;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> component;
            DFS_component(graph, i, visited, component);
            components.push_back(component);
        }
    }
    
    return components;
}
```

## DFS Complexity

**Time Complexity:** O(V + E)
- Visit each vertex once: O(V)
- Explore each edge once: O(E)
- Total: O(V + E)

**Space Complexity:** O(V)
- Recursion stack depth: O(V) in worst case (linear graph)
- Visited array: O(V)

---

# BFS vs DFS Comparison

## Visual Comparison

```
Graph:
    0
   / \
  1   2
 / \   \
3   4   5

BFS Order: 0, 1, 2, 3, 4, 5 (level by level)
DFS Order: 0, 1, 3, 4, 2, 5 (depth first)
```

## Key Differences

| Feature | BFS | DFS |
|---------|-----|-----|
| **Data Structure** | Queue | Stack (or recursion) |
| **Exploration** | Level by level | As deep as possible |
| **Path Type** | Shortest path (unweighted) | Any path |
| **Memory** | More memory (all neighbors stored) | Less memory (only path) |
| **Completeness** | Yes (finds solution if exists) | Yes |
| **Optimality** | Yes (shortest path) | No |
| **Implementation** | Iterative (queue) | Recursive or iterative (stack) |

## When to Use BFS

✅ **Use BFS when you need:**

1. **Shortest path** in unweighted graph
   ```
   Example: Minimum steps to reach destination
   ```

2. **Level-order traversal**
   ```
   Example: Print nodes level by level
   ```

3. **Minimum depth/distance**
   ```
   Example: Minimum moves in a game
   ```

4. **Closest nodes first**
   ```
   Example: Find nearest hospital
   ```

5. **Connected components** (same as DFS, but BFS preferred for level info)

**Example Problems:**
- Word Ladder
- Shortest path in maze
- Minimum knight moves
- Rotting oranges
- Level order traversal

## When to Use DFS

✅ **Use DFS when you need:**

1. **Detect cycles**
   ```
   Example: Check if graph has a cycle
   ```

2. **Topological sorting**
   ```
   Example: Course schedule, task dependencies
   ```

3. **Find connected components**
   ```
   Example: Number of islands
   ```

4. **Backtracking problems**
   ```
   Example: All paths from source to destination
   ```

5. **Check if path exists**
   ```
   Example: Is there a path from A to B?
   ```

6. **Strongly connected components**
   ```
   Example: Kosaraju's algorithm
   ```

**Example Problems:**
- Number of islands
- Course schedule
- Path exists
- Clone graph
- All paths from source to target

## Side-by-Side Example

```cpp
// Problem: Check if path exists from start to end

// BFS Solution
bool hasPath_BFS(vector<int> graph[], int start, int end, int n) {
    if (start == end) return true;
    
    vector<bool> visited(n, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (current == end) return true;
        
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    return false;
}

// DFS Solution
bool hasPath_DFS(vector<int> graph[], int current, int end,
                 vector<bool>& visited) {
    if (current == end) return true;
    
    visited[current] = true;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (hasPath_DFS(graph, neighbor, end, visited)) {
                return true;
            }
        }
    }
    
    return false;
}
```

---

# Applications

## 1. Shortest Path in Unweighted Graph (BFS)

```cpp
int shortestDistance(vector<int> graph[], int start, int end, int n) {
    if (start == end) return 0;
    
    vector<int> distance(n, -1);
    queue<int> q;
    
    distance[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (current == end) {
            return distance[end];
        }
        
        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
    
    return -1;  // No path exists
}
```

## 2. Number of Islands (DFS)

```cpp
class Solution {
public:
    void DFS(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        
        // Boundary check and water check
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
            return;
        }
        
        // Mark as visited by changing to water
        grid[i][j] = '0';
        
        // Explore all 4 directions
        DFS(grid, i + 1, j);
        DFS(grid, i - 1, j);
        DFS(grid, i, j + 1);
        DFS(grid, i, j - 1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    DFS(grid, i, j);
                }
            }
        }
        
        return count;
    }
};
```

## 3. Topological Sort (DFS)

```cpp
void topologicalSort_DFS(vector<int> graph[], int current,
                         vector<bool>& visited, stack<int>& result) {
    visited[current] = true;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            topologicalSort_DFS(graph, neighbor, visited, result);
        }
    }
    
    // Push to stack after visiting all descendants
    result.push(current);
}

vector<int> topologicalSort(vector<int> graph[], int n) {
    vector<bool> visited(n, false);
    stack<int> result;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            topologicalSort_DFS(graph, i, visited, result);
        }
    }
    
    vector<int> order;
    while (!result.empty()) {
        order.push_back(result.top());
        result.pop();
    }
    
    return order;
}
```

## 4. Bipartite Graph Check (BFS)

```cpp
bool isBipartite(vector<int> graph[], int n) {
    vector<int> color(n, -1);  // -1: uncolored, 0: color1, 1: color2
    
    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                
                for (int neighbor : graph[current]) {
                    if (color[neighbor] == -1) {
                        // Color with opposite color
                        color[neighbor] = 1 - color[current];
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == color[current]) {
                        // Same color = not bipartite
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}
```

## 5. All Paths from Source to Target (DFS with Backtracking)

```cpp
void findAllPaths_DFS(vector<int> graph[], int current, int target,
                      vector<int>& path, vector<vector<int>>& result) {
    path.push_back(current);
    
    if (current == target) {
        result.push_back(path);
    } else {
        for (int neighbor : graph[current]) {
            findAllPaths_DFS(graph, neighbor, target, path, result);
        }
    }
    
    // Backtrack
    path.pop_back();
}

vector<vector<int>> allPaths(vector<int> graph[], int start, int end, int n) {
    vector<vector<int>> result;
    vector<int> path;
    findAllPaths_DFS(graph, start, end, path, result);
    return result;
}
```

## 6. Detect Cycle in Directed Graph (DFS)

```cpp
bool hasCycleDFS(vector<int> graph[], int current,
                 vector<bool>& visited, vector<bool>& recStack) {
    visited[current] = true;
    recStack[current] = true;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (hasCycleDFS(graph, neighbor, visited, recStack)) {
                return true;
            }
        }
        else if (recStack[neighbor]) {
            // Back edge to node in recursion stack = cycle
            return true;
        }
    }
    
    recStack[current] = false;  // Remove from recursion stack
    return false;
}

bool hasCycle(vector<int> graph[], int n) {
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycleDFS(graph, i, visited, recStack)) {
                return true;
            }
        }
    }
    
    return false;
}
```

## 7. Clone Graph (DFS)

```cpp
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node(int _val) : val(_val) {}
};

class Solution {
public:
    unordered_map<Node*, Node*> cloned;
    
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        if (cloned.find(node) != cloned.end()) {
            return cloned[node];
        }
        
        // Create new node
        Node* newNode = new Node(node->val);
        cloned[node] = newNode;
        
        // Clone all neighbors
        for (Node* neighbor : node->neighbors) {
            newNode->neighbors.push_back(cloneGraph(neighbor));
        }
        
        return newNode;
    }
};
```

## 8. Word Ladder (BFS)

```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;
    
    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    
    while (!q.empty()) {
        auto [word, steps] = q.front();
        q.pop();
        
        if (word == endWord) return steps;
        
        // Try changing each character
        for (int i = 0; i < word.length(); i++) {
            string temp = word;
            for (char c = 'a'; c <= 'z'; c++) {
                temp[i] = c;
                if (dict.find(temp) != dict.end()) {
                    q.push({temp, steps + 1});
                    dict.erase(temp);  // Mark as visited
                }
            }
        }
    }
    
    return 0;
}
```

---

# Practice Problems

## Beginner Level

### 1. Is Graph Connected? (DFS/BFS)

**Problem:** Check if all vertices are connected.

```cpp
bool isConnected(vector<int> graph[], int n) {
    if (n == 0) return true;
    
    vector<bool> visited(n, false);
    
    // DFS from vertex 0
    function<void(int)> dfs = [&](int v) {
        visited[v] = true;
        for (int neighbor : graph[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };
    
    dfs(0);
    
    // Check if all vertices were visited
    for (int i = 0; i < n; i++) {
        if (!visited[i]) return false;
    }
    
    return true;
}
```

### 2. Count Connected Components (DFS/BFS)

**Problem:** Count number of connected components.

```cpp
int countComponents(int n, vector<pair<int, int>>& edges) {
    vector<int> graph[n];
    
    // Build adjacency list
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    vector<bool> visited(n, false);
    int count = 0;
    
    function<void(int)> dfs = [&](int v) {
        visited[v] = true;
        for (int neighbor : graph[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i);
        }
    }
    
    return count;
}
```

### 3. Find Path Between Two Nodes (DFS/BFS)

**Problem:** Return true if path exists from start to end.

```cpp
bool hasPath(vector<int> graph[], int start, int end, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (current == end) return true;
        
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    return false;
}
```

## Intermediate Level

### 4. Shortest Path Length (BFS)

**Problem:** Find shortest path length between two nodes.

**Solution:** See "Shortest Distance" in Applications section.

### 5. Course Schedule (DFS - Cycle Detection)

**Problem:** Can you finish all courses given prerequisites?

```cpp
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> graph[numCourses];
    
    // Build graph: course -> prerequisites
    for (auto [course, prereq] : prerequisites) {
        graph[course].push_back(prereq);
    }
    
    vector<int> state(numCourses, 0);  // 0: unvisited, 1: visiting, 2: visited
    
    function<bool(int)> hasCycle = [&](int course) {
        if (state[course] == 1) return true;  // Cycle detected
        if (state[course] == 2) return false; // Already checked
        
        state[course] = 1;  // Mark as visiting
        
        for (int prereq : graph[course]) {
            if (hasCycle(prereq)) return true;
        }
        
        state[course] = 2;  // Mark as visited
        return false;
    };
    
    for (int i = 0; i < numCourses; i++) {
        if (hasCycle(i)) return false;
    }
    
    return true;
}
```

### 6. Surrounded Regions (DFS)

**Problem:** Capture all regions surrounded by 'X'.

```cpp
void solve(vector<vector<char>>& board) {
    if (board.empty()) return;
    int m = board.size(), n = board[0].size();
    
    function<void(int, int)> dfs = [&](int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != 'O') {
            return;
        }
        
        board[i][j] = 'T';  // Mark as temporary
        dfs(i + 1, j);
        dfs(i - 1, j);
        dfs(i, j + 1);
        dfs(i, j - 1);
    };
    
    // Mark 'O's on border and connected to border
    for (int i = 0; i < m; i++) {
        dfs(i, 0);
        dfs(i, n - 1);
    }
    for (int j = 0; j < n; j++) {
        dfs(0, j);
        dfs(m - 1, j);
    }
    
    // Flip remaining 'O's to 'X' and 'T's back to 'O'
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'T') board[i][j] = 'O';
        }
    }
}
```

### 7. Pacific Atlantic Water Flow (DFS)

**Problem:** Find cells where water can flow to both oceans.

```cpp
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    if (heights.empty()) return {};
    
    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));
    
    function<void(int, int, vector<vector<bool>>&)> dfs = 
        [&](int i, int j, vector<vector<bool>>& ocean) {
        ocean[i][j] = true;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int d = 0; d < 4; d++) {
            int ni = i + dx[d], nj = j + dy[d];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                !ocean[ni][nj] && heights[ni][nj] >= heights[i][j]) {
                dfs(ni, nj, ocean);
            }
        }
    };
    
    // Start DFS from ocean borders
    for (int i = 0; i < m; i++) {
        dfs(i, 0, pacific);
        dfs(i, n - 1, atlantic);
    }
    for (int j = 0; j < n; j++) {
        dfs(0, j, pacific);
        dfs(m - 1, j, atlantic);
    }
    
    // Find cells reachable from both oceans
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
```

## Advanced Level

### 8. Shortest Bridge (BFS + DFS)

**Problem:** Find shortest bridge connecting two islands.

```cpp
int shortestBridge(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int, int>> q;
    bool found = false;
    
    // DFS to find first island and mark it
    function<void(int, int)> dfs = [&](int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) {
            return;
        }
        
        grid[i][j] = 2;  // Mark as visited
        q.push({i, j});  // Add to queue for BFS
        
        dfs(i + 1, j);
        dfs(i - 1, j);
        dfs(i, j + 1);
        dfs(i, j - 1);
    };
    
    // Find first island
    for (int i = 0; i < n && !found; i++) {
        for (int j = 0; j < n && !found; j++) {
            if (grid[i][j] == 1) {
                dfs(i, j);
                found = true;
            }
        }
    }
    
    // BFS to find shortest path to second island
    int distance = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    if (grid[nx][ny] == 1) {
                        return distance;  // Found second island
                    }
                    if (grid[nx][ny] == 0) {
                        grid[nx][ny] = 2;  // Mark as visited
                        q.push({nx, ny});
                    }
                }
            }
        }
        
        distance++;
    }
    
    return -1;
}
```

### 9. Alien Dictionary (DFS - Topological Sort)

**Problem:** Find alien language character order from sorted words.

```cpp
string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> indegree;
    
    // Initialize all characters
    for (const string& word : words) {
        for (char c : word) {
            indegree[c] = 0;
        }
    }
    
    // Build graph
    for (int i = 0; i < words.size() - 1; i++) {
        string word1 = words[i], word2 = words[i + 1];
        int minLen = min(word1.length(), word2.length());
        
        // Check for invalid case
        if (word1.length() > word2.length() && 
            word1.substr(0, minLen) == word2.substr(0, minLen)) {
            return "";
        }
        
        // Find first different character
        for (int j = 0; j < minLen; j++) {
            if (word1[j] != word2[j]) {
                if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                    graph[word1[j]].insert(word2[j]);
                    indegree[word2[j]]++;
                }
                break;
            }
        }
    }
    
    // Topological sort using BFS
    queue<char> q;
    for (auto [c, deg] : indegree) {
        if (deg == 0) {
            q.push(c);
        }
    }
    
    string result;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        result += c;
        
        for (char next : graph[c]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return result.length() == indegree.size() ? result : "";
}
```

### 10. Critical Connections (Tarjan's Algorithm - DFS)

**Problem:** Find all critical edges in network.

```cpp
class Solution {
public:
    int timer = 0;
    
    void dfs(int node, int parent, vector<int> graph[], 
             vector<int>& discovery, vector<int>& low,
             vector<vector<int>>& result) {
        discovery[node] = low[node] = ++timer;
        
        for (int neighbor : graph[node]) {
            if (neighbor == parent) continue;
            
            if (discovery[neighbor] == 0) {  // Not visited
                dfs(neighbor, node, graph, discovery, low, result);
                
                low[node] = min(low[node], low[neighbor]);
                
                // Bridge condition
                if (low[neighbor] > discovery[node]) {
                    result.push_back({node, neighbor});
                }
            } else {
                // Back edge
                low[node] = min(low[node], discovery[neighbor]);
            }
        }
    }
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> graph[n];
        
        for (auto& edge : connections) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<int> discovery(n, 0), low(n, 0);
        vector<vector<int>> result;
        
        dfs(0, -1, graph, discovery, low, result);
        
        return result;
    }
};
```

---

# Advanced Techniques

## 1. Bidirectional BFS

**Use:** Find shortest path faster by searching from both ends.

```cpp
int bidirectionalBFS(int start, int end, vector<int> graph[], int n) {
    if (start == end) return 0;
    
    unordered_set<int> visitedStart, visitedEnd;
    queue<int> qStart, qEnd;
    
    visitedStart.insert(start);
    visitedEnd.insert(end);
    qStart.push(start);
    qEnd.push(end);
    
    int distance = 0;
    
    while (!qStart.empty() || !qEnd.empty()) {
        distance++;
        
        // Expand from start
        int sizeStart = qStart.size();
        for (int i = 0; i < sizeStart; i++) {
            int current = qStart.front();
            qStart.pop();
            
            for (int neighbor : graph[current]) {
                if (visitedEnd.count(neighbor)) {
                    return distance;  // Paths met!
                }
                if (!visitedStart.count(neighbor)) {
                    visitedStart.insert(neighbor);
                    qStart.push(neighbor);
                }
            }
        }
        
        distance++;
        
        // Expand from end
        int sizeEnd = qEnd.size();
        for (int i = 0; i < sizeEnd; i++) {
            int current = qEnd.front();
            qEnd.pop();
            
            for (int neighbor : graph[current]) {
                if (visitedStart.count(neighbor)) {
                    return distance;  // Paths met!
                }
                if (!visitedEnd.count(neighbor)) {
                    visitedEnd.insert(neighbor);
                    qEnd.push(neighbor);
                }
            }
        }
    }
    
    return -1;
}
```

## 2. DFS with Memoization (DP on Graphs)

```cpp
unordered_map<int, int> memo;

int longestPath(vector<int> graph[], int node, vector<bool>& visited) {
    if (memo.count(node)) return memo[node];
    
    int maxPath = 0;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            maxPath = max(maxPath, 1 + longestPath(graph, neighbor, visited));
            visited[neighbor] = false;  // Backtrack
        }
    }
    
    return memo[node] = maxPath;
}
```

## 3. Level-by-Level BFS with Size Tracking

```cpp
void levelOrderBFS(vector<int> graph[], int start, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();  // Number of nodes at current level
        
        cout << "Level " << level << ": ";
        
        for (int i = 0; i < size; i++) {
            int current = q.front();
            q.pop();
            
            cout << current << " ";
            
            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        cout << endl;
        level++;
    }
}
```

## 4. Parallel BFS (for large graphs)

```cpp
vector<int> parallelBFS(vector<int> graph[], vector<int> sources, int n) {
    vector<int> distance(n, -1);
    queue<int> q;
    
    // Add all sources
    for (int source : sources) {
        distance[source] = 0;
        q.push(source);
    }
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
    
    return distance;
}
```

## 5. Iterative Deepening DFS (IDDFS)

Combines benefits of BFS (completeness) and DFS (memory efficiency).

```cpp
bool DLS(vector<int> graph[], int current, int target, 
         int depth, vector<bool>& visited) {
    if (current == target) return true;
    if (depth == 0) return false;
    
    visited[current] = true;
    
    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            if (DLS(graph, neighbor, target, depth - 1, visited)) {
                return true;
            }
        }
    }
    
    visited[current] = false;  // Backtrack for next iteration
    return false;
}

bool IDDFS(vector<int> graph[], int start, int target, int n, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<bool> visited(n, false);
        if (DLS(graph, start, target, depth, visited)) {
            return true;
        }
    }
    return false;
}
```

---

# Common Pitfalls and Tips

## Pitfalls to Avoid

1. **Forgetting to mark nodes as visited**
   ```cpp
   // ❌ Wrong - infinite loop
   q.push(neighbor);
   
   // ✅ Correct
   if (!visited[neighbor]) {
       visited[neighbor] = true;
       q.push(neighbor);
   }
   ```

2. **Modifying graph during traversal**
   ```cpp
   // ❌ Dangerous
   for (int neighbor : graph[current]) {
       graph[current].erase(...);  // Don't modify while iterating
   }
   ```

3. **Not handling disconnected components**
   ```cpp
   // ❌ Only visits one component
   BFS(graph, 0, n);
   
   // ✅ Visits all components
   for (int i = 0; i < n; i++) {
       if (!visited[i]) {
           BFS(graph, i, n);
       }
   }
   ```

4. **Stack overflow in DFS (deep graphs)**
   ```cpp
   // ❌ Recursive DFS can overflow
   void dfs(int node) { ... dfs(neighbor); ... }
   
   // ✅ Use iterative DFS for deep graphs
   stack<int> s;
   // ... iterative implementation
   ```

5. **Not considering directed vs undirected graphs**
   ```cpp
   // Undirected: add edge both ways
   graph[u].push_back(v);
   graph[v].push_back(u);
   
   // Directed: add edge one way
   graph[u].push_back(v);
   ```

## Pro Tips

1. **Choose the right traversal**
   - Shortest path → BFS
   - Cycle detection → DFS
   - Topological sort → DFS
   - Level information → BFS

2. **Use appropriate data structures**
   - BFS → `queue<int>`
   - DFS → recursion or `stack<int>`
   - Visited tracking → `vector<bool>` or `unordered_set<int>`

3. **Optimize for sparse vs dense graphs**
   - Sparse (E << V²) → Adjacency list
   - Dense (E ≈ V²) → Adjacency matrix

4. **Handle edge cases**
   - Empty graph
   - Single node
   - Disconnected components
   - Cycles

5. **Debug visualization**
   ```cpp
   void printTraversal(int node, int level) {
       cout << string(level * 2, ' ') << node << endl;
   }
   ```

---

# Summary

## Quick Reference

| Task | Algorithm | Time | Space |
|------|-----------|------|-------|
| Shortest path (unweighted) | BFS | O(V+E) | O(V) |
| Check if path exists | BFS/DFS | O(V+E) | O(V) |
| Cycle detection (undirected) | DFS | O(V+E) | O(V) |
| Cycle detection (directed) | DFS | O(V+E) | O(V) |
| Topological sort | DFS | O(V+E) | O(V) |
| Connected components | BFS/DFS | O(V+E) | O(V) |
| Bipartite check | BFS | O(V+E) | O(V) |
| All paths | DFS | O(V! ) | O(V) |

## Key Takeaways

1. **BFS uses queue, DFS uses stack/recursion**
2. **BFS finds shortest path, DFS is better for backtracking**
3. **Always mark nodes as visited to avoid infinite loops**
4. **Handle disconnected components by iterating through all nodes**
5. **Choose adjacency list for most problems (sparse graphs)**
6. **Time complexity is O(V + E) for both BFS and DFS**
7. **Practice on real problems to master the patterns**

---

**Happy Graph Traversing!** 🚀

For more practice:
- LeetCode: Graph tag (Easy → Medium → Hard)
- Practice cycle detection, topological sort, and shortest path variations
- Understand when to use BFS vs DFS
