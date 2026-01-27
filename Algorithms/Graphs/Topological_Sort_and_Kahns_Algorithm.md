# Topological Sort and Kahn's Algorithm - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [What is Topological Sort?](#what-is-topological-sort)
- [Prerequisites and Constraints](#prerequisites-and-constraints)
- [DFS-Based Topological Sort](#dfs-based-topological-sort)
- [Kahn's Algorithm (BFS-Based)](#kahns-algorithm-bfs-based)
- [DFS vs Kahn's Comparison](#dfs-vs-kahns-comparison)
- [Applications](#applications)
- [Practice Problems](#practice-problems)
- [Advanced Techniques](#advanced-techniques)

---

# Introduction

**Topological Sort** is a linear ordering of vertices in a Directed Acyclic Graph (DAG) such that for every directed edge (u, v), vertex u comes before vertex v in the ordering.

## Real-World Examples

1. **Course Prerequisites**
   ```
   Course C depends on Course B
   Course B depends on Course A
   Order: A → B → C
   ```

2. **Task Scheduling**
   ```
   Task 3 requires Task 1 and Task 2 to be completed
   Possible order: Task 1, Task 2, Task 3
   ```

3. **Build Systems**
   ```
   main.cpp depends on utils.h
   utils.h depends on types.h
   Compile order: types.h → utils.h → main.cpp
   ```

---

# What is Topological Sort?

## Visual Example

```
Graph (DAG):
    5 → 0 ← 4
    ↓       ↓
    2 → 3 → 1

Valid Topological Orders:
1. 5, 4, 2, 3, 1, 0
2. 4, 5, 2, 3, 1, 0
3. 5, 2, 4, 3, 1, 0
4. 4, 5, 0, 2, 3, 1
... and more!
```

## Key Properties

1. **Not Unique:** Multiple valid orderings may exist
2. **DAG Only:** Only works on Directed Acyclic Graphs
3. **Linear Order:** Output is a linear sequence
4. **Dependency Respected:** All dependencies come before dependent nodes

## Why Important?

- **Interview Favorite:** Common in tech interviews (Google, Amazon, Microsoft)
- **Real Applications:** Build systems, task scheduling, course planning
- **Foundation:** Understanding DAGs and graph algorithms
- **Two Approaches:** DFS-based and BFS-based (Kahn's)

---

# Prerequisites and Constraints

## Required: Directed Acyclic Graph (DAG)

### Valid DAG
```
    A → B → C
    ↓       ↑
    D ------┘

Topological order possible: A, D, B, C
```

### Invalid: Has Cycle
```
    A → B
    ↑   ↓
    └── C

No topological order (cycle exists)
```

### Invalid: Undirected Graph
```
    A -- B -- C

Not applicable (needs directed edges)
```

## How to Detect Cycles?

Topological sort algorithms can detect cycles:
- **DFS approach:** Track recursion stack
- **Kahn's approach:** Check if all nodes are processed

---

# DFS-Based Topological Sort

## Algorithm Concept

1. Perform DFS on the graph
2. When a vertex finishes (all descendants visited), push it to stack
3. Pop stack to get topological order

**Key Insight:** A vertex is pushed to stack only after all its descendants are processed, ensuring dependencies come after.

## Visual Walkthrough

```
Graph:
    0 → 1 → 2
    ↓       
    3 → 4

DFS from 0:
1. Visit 0 → Visit 1 → Visit 2
2. 2 finishes → push 2
3. 1 finishes → push 1
4. Visit 3 → Visit 4
5. 4 finishes → push 4
6. 3 finishes → push 3
7. 0 finishes → push 0

Stack (bottom to top): [2, 1, 4, 3, 0]
Topological order: 0, 3, 4, 1, 2 (or 0, 1, 3, 4, 2)
```

## Basic Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class TopologicalSort {
private:
    void DFS(int node, vector<int> graph[], vector<bool>& visited, 
             stack<int>& result) {
        visited[node] = true;
        
        // Visit all neighbors
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                DFS(neighbor, graph, visited, result);
            }
        }
        
        // Push to stack after all descendants are visited
        result.push(node);
    }
    
public:
    vector<int> topologicalSort(vector<int> graph[], int V) {
        vector<bool> visited(V, false);
        stack<int> result;
        
        // Handle disconnected components
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, graph, visited, result);
            }
        }
        
        // Extract from stack
        vector<int> order;
        while (!result.empty()) {
            order.push_back(result.top());
            result.pop();
        }
        
        return order;
    }
};

int main() {
    int V = 6;
    vector<int> graph[V];
    
    // Build graph: 5→0, 5→2, 4→0, 4→1, 2→3, 3→1
    graph[5].push_back(0);
    graph[5].push_back(2);
    graph[4].push_back(0);
    graph[4].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);
    
    TopologicalSort ts;
    vector<int> result = ts.topologicalSort(graph, V);
    
    cout << "Topological Order: ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}
```

**Output:** `5 4 2 3 1 0` (one possible ordering)

## With Cycle Detection

```cpp
class TopologicalSortWithCycleDetection {
private:
    bool DFS(int node, vector<int> graph[], 
             vector<int>& color, stack<int>& result) {
        // Color: 0 = white (unvisited), 1 = gray (visiting), 2 = black (done)
        color[node] = 1;  // Mark as visiting
        
        for (int neighbor : graph[node]) {
            if (color[neighbor] == 1) {
                // Back edge found = cycle!
                return true;
            }
            if (color[neighbor] == 0) {
                if (DFS(neighbor, graph, color, result)) {
                    return true;  // Cycle detected in recursion
                }
            }
        }
        
        color[node] = 2;  // Mark as done
        result.push(node);
        return false;
    }
    
public:
    vector<int> topologicalSort(vector<int> graph[], int V) {
        vector<int> color(V, 0);
        stack<int> result;
        
        for (int i = 0; i < V; i++) {
            if (color[i] == 0) {
                if (DFS(i, graph, color, result)) {
                    // Cycle detected!
                    cout << "Graph contains cycle. Topological sort not possible." << endl;
                    return {};
                }
            }
        }
        
        vector<int> order;
        while (!result.empty()) {
            order.push_back(result.top());
            result.pop();
        }
        
        return order;
    }
};
```

## Step-by-Step Example

```cpp
// Example with detailed output
void topologicalSortWithSteps(vector<int> graph[], int V) {
    vector<bool> visited(V, false);
    stack<int> result;
    int step = 1;
    
    function<void(int, int)> DFS = [&](int node, int depth) {
        visited[node] = true;
        cout << string(depth * 2, ' ') << "Step " << step++ 
             << ": Visiting node " << node << endl;
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                DFS(neighbor, depth + 1);
            }
        }
        
        result.push(node);
        cout << string(depth * 2, ' ') << "Pushing " << node 
             << " to stack" << endl;
    };
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, 0);
        }
    }
    
    cout << "\nTopological Order: ";
    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
    cout << endl;
}
```

## Complexity Analysis

**Time Complexity:** O(V + E)
- Visit each vertex once: O(V)
- Explore each edge once: O(E)
- Total: O(V + E)

**Space Complexity:** O(V)
- Recursion stack: O(V) in worst case
- Visited array: O(V)
- Result stack: O(V)

---

# Kahn's Algorithm (BFS-Based)

## Algorithm Concept

1. Calculate in-degree (number of incoming edges) for each vertex
2. Add all vertices with in-degree 0 to queue
3. While queue is not empty:
   - Remove vertex from queue
   - Add to result
   - Decrease in-degree of all neighbors
   - If any neighbor's in-degree becomes 0, add to queue
4. If result contains all vertices → valid topological order
5. Otherwise → cycle exists

**Key Insight:** A vertex with in-degree 0 has no dependencies, so it can be processed.

## Visual Walkthrough

```
Graph:
    5 → 0 ← 4
    ↓       ↓
    2 → 3 → 1

Initial in-degrees:
0: 2, 1: 2, 2: 1, 3: 1, 4: 0, 5: 0

Step 1: Queue = [4, 5], Result = []
Step 2: Process 4, Result = [4]
        Decrease in-degree: 0 (2→1), 1 (2→1)
        Queue = [5]
        
Step 3: Process 5, Result = [4, 5]
        Decrease in-degree: 0 (1→0), 2 (1→0)
        Queue = [0, 2]
        
Step 4: Process 0, Result = [4, 5, 0]
        No neighbors, Queue = [2]
        
Step 5: Process 2, Result = [4, 5, 0, 2]
        Decrease in-degree: 3 (1→0)
        Queue = [3]
        
Step 6: Process 3, Result = [4, 5, 0, 2, 3]
        Decrease in-degree: 1 (2→1)
        Queue = [1]
        
Step 7: Process 1, Result = [4, 5, 0, 2, 3, 1]
        Queue = []

Final order: 4, 5, 0, 2, 3, 1
```

## Basic Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class KahnsAlgorithm {
public:
    vector<int> topologicalSort(vector<int> graph[], int V) {
        // Step 1: Calculate in-degrees
        vector<int> indegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (int v : graph[u]) {
                indegree[v]++;
            }
        }
        
        // Step 2: Add all vertices with in-degree 0 to queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        // Step 3: Process vertices
        vector<int> result;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);
            
            // Decrease in-degree of neighbors
            for (int neighbor : graph[current]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Step 4: Check if all vertices are processed
        if (result.size() != V) {
            cout << "Graph contains cycle!" << endl;
            return {};
        }
        
        return result;
    }
};

int main() {
    int V = 6;
    vector<int> graph[V];
    
    graph[5].push_back(0);
    graph[5].push_back(2);
    graph[4].push_back(0);
    graph[4].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);
    
    KahnsAlgorithm ka;
    vector<int> result = ka.topologicalSort(graph, V);
    
    cout << "Topological Order: ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}
```

**Output:** `4 5 0 2 3 1` (one possible ordering)

## With Detailed Steps

```cpp
vector<int> kahnsWithSteps(vector<int> graph[], int V) {
    // Calculate in-degrees
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    // Print initial in-degrees
    cout << "Initial in-degrees: ";
    for (int i = 0; i < V; i++) {
        cout << i << ":" << indegree[i] << " ";
    }
    cout << endl << endl;
    
    // Initialize queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
            cout << "Added " << i << " to queue (in-degree = 0)" << endl;
        }
    }
    cout << endl;
    
    vector<int> result;
    int step = 1;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);
        
        cout << "Step " << step++ << ": Process " << current << endl;
        
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            cout << "  Decrease in-degree of " << neighbor 
                 << " to " << indegree[neighbor] << endl;
            
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
                cout << "  Added " << neighbor << " to queue" << endl;
            }
        }
        cout << endl;
    }
    
    if (result.size() != V) {
        cout << "Cycle detected! Only processed " << result.size() 
             << " out of " << V << " vertices." << endl;
        return {};
    }
    
    return result;
}
```

## Using Priority Queue (Lexicographically Smallest Order)

When multiple orderings exist, we might want the lexicographically smallest:

```cpp
vector<int> lexicographicalTopologicalSort(vector<int> graph[], int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    // Use min-heap instead of queue
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }
    
    vector<int> result;
    
    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();
        result.push_back(current);
        
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }
    
    return result;
}
```

## Complexity Analysis

**Time Complexity:** O(V + E)
- Calculate in-degrees: O(E)
- Process each vertex once: O(V)
- Process each edge once: O(E)
- Total: O(V + E)

**Space Complexity:** O(V)
- In-degree array: O(V)
- Queue: O(V)
- Result array: O(V)

---

# DFS vs Kahn's Comparison

## Side-by-Side Comparison

| Feature | DFS-Based | Kahn's Algorithm |
|---------|-----------|------------------|
| **Approach** | Recursive depth-first | Iterative breadth-first |
| **Data Structure** | Stack (implicit/explicit) | Queue |
| **Implementation** | Typically recursive | Always iterative |
| **Cycle Detection** | Using recursion stack colors | Count processed vertices |
| **Memory** | O(V) recursion stack | O(V) queue |
| **Order** | Reverse finish time | Process by in-degree |
| **Intuition** | Finish dependents first | Process ready nodes |
| **Code Complexity** | Simpler recursive code | More explicit steps |

## When to Use Each?

### Use DFS-Based When:
✅ You're comfortable with recursion
✅ You want simpler, more elegant code
✅ Graph is deeply nested
✅ You need to track finish times

### Use Kahn's When:
✅ You prefer iterative solutions
✅ You need to avoid stack overflow
✅ You want explicit cycle detection
✅ You need level-by-level processing
✅ You want lexicographical ordering (with priority queue)

## Example: Same Graph, Both Approaches

```cpp
int V = 4;
vector<int> graph[V];

// Graph: 0→1→2→3
graph[0].push_back(1);
graph[1].push_back(2);
graph[2].push_back(3);

// DFS Approach
TopologicalSort ts;
vector<int> dfs_result = ts.topologicalSort(graph, V);
// Output: 0, 1, 2, 3

// Kahn's Approach
KahnsAlgorithm ka;
vector<int> kahn_result = ka.topologicalSort(graph, V);
// Output: 0, 1, 2, 3

// Both give valid topological orderings!
```

## Performance Comparison

```cpp
// Both have same time complexity: O(V + E)
// Both have same space complexity: O(V)

// Benchmark example (pseudocode)
Graph with 10000 vertices, 50000 edges:
- DFS: ~15ms
- Kahn's: ~15ms
- Nearly identical performance

// Recursion depth matters for DFS
Linear chain of 10000 nodes:
- DFS: Stack overflow risk
- Kahn's: No problem
```

---

# Applications

## 1. Course Schedule (LeetCode 207)

**Problem:** Can you finish all courses given prerequisites?

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build graph
        vector<int> graph[numCourses];
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            graph[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        // Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int completed = 0;
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            completed++;
            
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return completed == numCourses;
    }
};
```

## 2. Course Schedule II (LeetCode 210)

**Problem:** Return the ordering of courses.

```cpp
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> graph[numCourses];
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        if (order.size() != numCourses) {
            return {};  // Cycle detected
        }
        
        return order;
    }
};
```

## 3. Alien Dictionary (LeetCode 269)

**Problem:** Find the order of characters in an alien language.

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Build graph
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;
        
        // Initialize all characters
        for (const string& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }
        
        // Build edges
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i], word2 = words[i + 1];
            int minLen = min(word1.length(), word2.length());
            
            // Invalid case: "abc" before "ab"
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
        
        // Kahn's algorithm
        queue<char> q;
        for (auto& [c, deg] : indegree) {
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
};
```

## 4. Parallel Courses (LeetCode 1136)

**Problem:** Minimum semesters to complete all courses.

```cpp
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<int> graph[n + 1];
        vector<int> indegree(n + 1, 0);
        
        for (auto& rel : relations) {
            graph[rel[0]].push_back(rel[1]);
            indegree[rel[1]]++;
        }
        
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int semesters = 0;
        int completed = 0;
        
        while (!q.empty()) {
            int size = q.size();
            semesters++;
            
            // Process all courses in current semester
            for (int i = 0; i < size; i++) {
                int course = q.front();
                q.pop();
                completed++;
                
                for (int next : graph[course]) {
                    indegree[next]--;
                    if (indegree[next] == 0) {
                        q.push(next);
                    }
                }
            }
        }
        
        return completed == n ? semesters : -1;
    }
};
```

## 5. Build Order (From Cracking the Coding Interview)

**Problem:** Given projects and dependencies, find a valid build order.

```cpp
class BuildOrder {
public:
    vector<string> findBuildOrder(vector<string>& projects, 
                                  vector<pair<string, string>>& dependencies) {
        // Map project names to indices
        unordered_map<string, int> projectIndex;
        for (int i = 0; i < projects.size(); i++) {
            projectIndex[projects[i]] = i;
        }
        
        // Build graph
        int n = projects.size();
        vector<int> graph[n];
        vector<int> indegree(n, 0);
        
        for (auto& [first, second] : dependencies) {
            // second depends on first
            int u = projectIndex[first];
            int v = projectIndex[second];
            graph[u].push_back(v);
            indegree[v]++;
        }
        
        // Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<string> order;
        
        while (!q.empty()) {
            int idx = q.front();
            q.pop();
            order.push_back(projects[idx]);
            
            for (int next : graph[idx]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        if (order.size() != n) {
            cout << "Circular dependency detected!" << endl;
            return {};
        }
        
        return order;
    }
};
```

## 6. Task Scheduler with Dependencies

**Problem:** Schedule tasks respecting dependencies and maximize parallelism.

```cpp
class TaskScheduler {
public:
    struct Task {
        int id;
        int duration;
        vector<int> dependencies;
    };
    
    int minimumTime(vector<Task>& tasks) {
        int n = tasks.size();
        vector<int> graph[n];
        vector<int> indegree(n, 0);
        vector<int> startTime(n, 0);
        
        // Build dependency graph
        for (int i = 0; i < n; i++) {
            for (int dep : tasks[i].dependencies) {
                graph[dep].push_back(i);
                indegree[i]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int totalTime = 0;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            int finishTime = startTime[current] + tasks[current].duration;
            totalTime = max(totalTime, finishTime);
            
            for (int next : graph[current]) {
                // Next task can start only after current finishes
                startTime[next] = max(startTime[next], finishTime);
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return totalTime;
    }
};
```

## 7. Sequence Reconstruction (LeetCode 444)

**Problem:** Check if sequence is the only valid topological sort.

```cpp
class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, 
                                vector<vector<int>>& sequences) {
        int n = nums.size();
        vector<unordered_set<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        
        // Build graph from sequences
        for (auto& seq : sequences) {
            for (int i = 0; i < seq.size() - 1; i++) {
                if (graph[seq[i]].find(seq[i + 1]) == graph[seq[i]].end()) {
                    graph[seq[i]].insert(seq[i + 1]);
                    indegree[seq[i + 1]]++;
                }
            }
        }
        
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int index = 0;
        
        while (!q.empty()) {
            // Must have exactly one node with in-degree 0 for unique order
            if (q.size() > 1) return false;
            
            int current = q.front();
            q.pop();
            
            // Must match the given sequence
            if (current != nums[index++]) return false;
            
            for (int next : graph[current]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return index == n;
    }
};
```

---

# Practice Problems

## Beginner Level

### 1. Basic Topological Sort

**Problem:** Implement topological sort for a given DAG.

```cpp
// Using DFS
vector<int> topSort_DFS(vector<int> graph[], int V) {
    vector<bool> visited(V, false);
    stack<int> st;
    
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
        st.push(node);
    };
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    vector<int> result;
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}

// Using Kahn's
vector<int> topSort_Kahn(vector<int> graph[], int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current);
        
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return result;
}
```

### 2. Detect Cycle in Directed Graph

**Problem:** Check if DAG has a cycle.

```cpp
bool hasCycle(vector<int> graph[], int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    int processed = 0;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        processed++;
        
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return processed != V;  // Cycle if not all vertices processed
}
```

### 3. Count All Valid Topological Sorts

**Problem:** Count all possible valid topological orderings.

```cpp
class CountTopSort {
private:
    void countUtil(vector<int> graph[], vector<int>& indegree,
                   vector<bool>& visited, vector<int>& result,
                   int& count, int V) {
        // If all vertices are included
        if (result.size() == V) {
            count++;
            return;
        }
        
        // Try all vertices with in-degree 0
        for (int i = 0; i < V; i++) {
            if (!visited[i] && indegree[i] == 0) {
                // Include this vertex
                visited[i] = true;
                result.push_back(i);
                
                // Reduce in-degree of neighbors
                for (int neighbor : graph[i]) {
                    indegree[neighbor]--;
                }
                
                // Recurse
                countUtil(graph, indegree, visited, result, count, V);
                
                // Backtrack
                visited[i] = false;
                result.pop_back();
                for (int neighbor : graph[i]) {
                    indegree[neighbor]++;
                }
            }
        }
    }
    
public:
    int countAllTopologicalSorts(vector<int> graph[], int V) {
        vector<int> indegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (int v : graph[u]) {
                indegree[v]++;
            }
        }
        
        vector<bool> visited(V, false);
        vector<int> result;
        int count = 0;
        
        countUtil(graph, indegree, visited, result, count, V);
        
        return count;
    }
};
```

## Intermediate Level

### 4. All Ancestors of a Node (LeetCode 2192)

**Problem:** Find all ancestors of each node in a DAG.

```cpp
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<int> graph[n];
        vector<int> indegree(n, 0);
        
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        
        // Kahn's algorithm with ancestor tracking
        queue<int> q;
        vector<set<int>> ancestors(n);
        
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            for (int child : graph[current]) {
                // Add current and all its ancestors to child's ancestors
                ancestors[child].insert(current);
                ancestors[child].insert(ancestors[current].begin(), 
                                       ancestors[current].end());
                
                indegree[child]--;
                if (indegree[child] == 0) {
                    q.push(child);
                }
            }
        }
        
        // Convert sets to vectors
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].assign(ancestors[i].begin(), ancestors[i].end());
        }
        
        return result;
    }
};
```

### 5. Longest Path in DAG

**Problem:** Find the longest path in a DAG.

```cpp
int longestPath(vector<pair<int, int>> graph[], int V) {
    // Topological sort with DP
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (auto [v, w] : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    vector<int> dist(V, 0);
    
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (auto [v, w] : graph[u]) {
            dist[v] = max(dist[v], dist[u] + w);
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return *max_element(dist.begin(), dist.end());
}
```

### 6. Print All Topological Sorts

**Problem:** Print all possible topological orderings.

```cpp
void printAllTopologicalSorts(vector<int> graph[], vector<int>& indegree,
                             vector<bool>& visited, vector<int>& result,
                             int V) {
    bool flag = false;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i] && indegree[i] == 0) {
            visited[i] = true;
            result.push_back(i);
            
            // Reduce in-degree
            for (int neighbor : graph[i]) {
                indegree[neighbor]--;
            }
            
            printAllTopologicalSorts(graph, indegree, visited, result, V);
            
            // Backtrack
            visited[i] = false;
            result.pop_back();
            for (int neighbor : graph[i]) {
                indegree[neighbor]++;
            }
            
            flag = true;
        }
    }
    
    // Print if complete ordering found
    if (!flag) {
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    }
}
```

## Advanced Level

### 7. Maximum Height by Stacking Cuboids (LeetCode 1691)

**Problem:** Stack cuboids to maximize height with constraints.

```cpp
class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        // Sort dimensions of each cuboid
        for (auto& c : cuboids) {
            sort(c.begin(), c.end());
        }
        
        // Sort cuboids
        sort(cuboids.begin(), cuboids.end());
        
        int n = cuboids.size();
        vector<int> dp(n);
        
        // DP with topological ordering
        for (int i = 0; i < n; i++) {
            dp[i] = cuboids[i][2];  // Height of current cuboid
            
            for (int j = 0; j < i; j++) {
                // Check if cuboid j can be placed under cuboid i
                if (cuboids[j][0] <= cuboids[i][0] &&
                    cuboids[j][1] <= cuboids[i][1] &&
                    cuboids[j][2] <= cuboids[i][2]) {
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2]);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
```

### 8. Sort Items by Groups Respecting Dependencies (LeetCode 1203)

**Problem:** Complex topological sort with grouping.

```cpp
class Solution {
private:
    vector<int> topologicalSort(vector<int> graph[], int n) {
        vector<int> indegree(n, 0);
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
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
            int current = q.front();
            q.pop();
            result.push_back(current);
            
            for (int neighbor : graph[current]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return result.size() == n ? result : vector<int>();
    }
    
public:
    vector<int> sortItems(int n, int m, vector<int>& group,
                         vector<vector<int>>& beforeItems) {
        // Assign group to items without group
        int groupId = m;
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = groupId++;
            }
        }
        
        // Build item and group graphs
        vector<int> itemGraph[n];
        vector<int> groupGraph[groupId];
        
        for (int i = 0; i < n; i++) {
            for (int j : beforeItems[i]) {
                itemGraph[j].push_back(i);
                
                if (group[i] != group[j]) {
                    groupGraph[group[j]].push_back(group[i]);
                }
            }
        }
        
        // Topological sort on groups
        vector<int> groupOrder = topologicalSort(groupGraph, groupId);
        if (groupOrder.empty()) return {};
        
        // Topological sort on items
        vector<int> itemOrder = topologicalSort(itemGraph, n);
        if (itemOrder.empty()) return {};
        
        // Group items by their group
        unordered_map<int, vector<int>> groupedItems;
        for (int item : itemOrder) {
            groupedItems[group[item]].push_back(item);
        }
        
        // Combine results
        vector<int> result;
        for (int g : groupOrder) {
            for (int item : groupedItems[g]) {
                result.push_back(item);
            }
        }
        
        return result;
    }
};
```

---

# Advanced Techniques

## 1. Lexicographical Topological Sort

Get the smallest lexicographical ordering:

```cpp
vector<int> lexicographicalTopSort(vector<int> graph[], int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    // Use min-heap for lexicographical order
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }
    
    vector<int> result;
    
    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();
        result.push_back(current);
        
        for (int neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }
    
    return result;
}
```

## 2. Topological Sort with Levels

Get nodes grouped by levels:

```cpp
vector<vector<int>> topologicalSortByLevels(vector<int> graph[], int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<vector<int>> levels;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < size; i++) {
            int current = q.front();
            q.pop();
            currentLevel.push_back(current);
            
            for (int neighbor : graph[current]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        levels.push_back(currentLevel);
    }
    
    return levels;
}
```

## 3. Parallel Task Execution

Calculate minimum time with parallel execution:

```cpp
int minimumTimeParallel(vector<int> graph[], vector<int>& duration, int V) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    vector<int> startTime(V, 0);
    
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    int totalTime = 0;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        int finishTime = startTime[current] + duration[current];
        totalTime = max(totalTime, finishTime);
        
        for (int neighbor : graph[current]) {
            startTime[neighbor] = max(startTime[neighbor], finishTime);
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return totalTime;
}
```

## 4. Finding All Cycles

Detect and report all cycles:

```cpp
class CycleFinder {
private:
    void findCyclesUtil(int node, vector<int> graph[], 
                       vector<int>& color, vector<int>& path,
                       vector<vector<int>>& cycles) {
        color[node] = 1;  // Gray
        path.push_back(node);
        
        for (int neighbor : graph[node]) {
            if (color[neighbor] == 1) {
                // Back edge - cycle found
                vector<int> cycle;
                auto it = find(path.begin(), path.end(), neighbor);
                cycle.insert(cycle.end(), it, path.end());
                cycles.push_back(cycle);
            }
            else if (color[neighbor] == 0) {
                findCyclesUtil(neighbor, graph, color, path, cycles);
            }
        }
        
        path.pop_back();
        color[node] = 2;  // Black
    }
    
public:
    vector<vector<int>> findAllCycles(vector<int> graph[], int V) {
        vector<int> color(V, 0);
        vector<int> path;
        vector<vector<int>> cycles;
        
        for (int i = 0; i < V; i++) {
            if (color[i] == 0) {
                findCyclesUtil(i, graph, color, path, cycles);
            }
        }
        
        return cycles;
    }
};
```

---

# Summary

## Quick Reference

| Feature | DFS-Based | Kahn's Algorithm |
|---------|-----------|------------------|
| **Time** | O(V + E) | O(V + E) |
| **Space** | O(V) | O(V) |
| **Type** | Recursive | Iterative |
| **Cycle Detection** | Color array | Count vertices |
| **Best For** | Simple cases | Level processing |

## Key Takeaways

1. **Topological sort only works on DAGs** (Directed Acyclic Graphs)
2. **Two main approaches:** DFS (recursive) and Kahn's (BFS-based)
3. **Both have O(V + E) complexity** - choose based on preference
4. **Cycle detection is built-in** - if sort fails, cycle exists
5. **Multiple orderings possible** - not unique unless constraints force it
6. **Real applications:** Course scheduling, build systems, task dependencies
7. **Kahn's better for levels** - natural when processing by "readiness"
8. **DFS simpler to code** - elegant recursive solution

## Common Patterns

1. **Course prerequisites** → Kahn's with count check
2. **Build dependencies** → Either approach works
3. **Lexicographical ordering** → Kahn's with priority queue
4. **Parallel execution** → Kahn's with level tracking
5. **All orderings** → Backtracking with in-degree

---

**Master Topological Sort and ace your interviews!** 🚀

**Practice Resources:**
- LeetCode: Course Schedule I & II
- LeetCode: Alien Dictionary
- LeetCode: Parallel Courses
- GeeksforGeeks: Topological Sort problems
