# Heap Data Structure - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [What is a Heap?](#what-is-a-heap)
- [Problems It Resolves](#problems-it-resolves)
- [Types of Heaps](#types-of-heaps)
- [Terminology](#terminology)
- [Heap Properties](#heap-properties)
- [Implementation](#implementation)
- [Heap Operations](#heap-operations)
- [Applications](#applications)
- [Complete C++ Implementation](#complete-cpp-implementation)
- [LeetCode Problems](#leetcode-problems)

---

# Introduction

A **Heap** is a specialized tree-based data structure that satisfies the heap property. It is a complete binary tree where each node follows a specific ordering relationship with its children.

**Key Points:**
- Complete binary tree
- Can be efficiently represented as an array
- Two types: Min Heap and Max Heap
- Used in priority queues, sorting algorithms
- O(log n) insertion and deletion

---

# What is a Heap?

## Visual Representation

### Max Heap
```
         100
        /   \
       80    90
      / \   /  \
     40 60 70  50
    / \
   10 20

Property: Parent ≥ Children
```

### Min Heap
```
         10
        /   \
       20    30
      / \   /  \
     40 50 60  70
    / \
   80 90

Property: Parent ≤ Children
```

## Array Representation

```
Max Heap Tree:         100
                      /   \
                     80    90
                    / \   /  \
                   40 60 70  50

Array: [100, 80, 90, 40, 60, 70, 50]
Index:   0   1   2   3   4   5   6

For node at index i:
- Left child:  2*i + 1
- Right child: 2*i + 2
- Parent:      (i-1) / 2
```

## Key Characteristics

- **Complete Binary Tree**: All levels filled except possibly last (filled left to right)
- **Heap Property**: Relationship between parent and children
- **Efficient**: O(1) access to min/max element
- **Array-based**: No need for pointers

---

# Problems It Resolves

## 1. **Priority Queue Implementation**
**Problem:** Need efficient access to highest/lowest priority element  
**Solution:** Heap provides O(1) access to max/min

```
Use Case: Hospital Emergency Room
- Critical patients (priority 10) treated first
- Heap automatically maintains order
```

## 2. **Finding Kth Largest/Smallest Element**
**Problem:** Finding kth order statistic in unsorted array  
**Solution:** Heap-based solution in O(n log k)

```
Array: [7, 10, 4, 3, 20, 15]
Find 3rd largest:
Use min heap of size 3 → Answer: 10
```

## 3. **Merge K Sorted Lists/Arrays**
**Problem:** Efficiently merge multiple sorted sequences  
**Solution:** Min heap to track smallest elements

```
Lists: [1, 4, 5], [1, 3, 4], [2, 6]
Use min heap to get next smallest element efficiently
```

## 4. **Median Maintenance**
**Problem:** Find median of stream of numbers  
**Solution:** Two heaps (max heap for lower half, min heap for upper half)

```
Stream: 5, 15, 1, 3
Max Heap (lower): [3, 1]
Min Heap (upper): [5, 15]
Median = (3 + 5) / 2 = 4
```

## 5. **Heap Sort**
**Problem:** Sort array in O(n log n) without extra space  
**Solution:** Build heap, then repeatedly extract max/min

## 6. **Top K Frequent Elements**
**Problem:** Find k most/least frequent items  
**Solution:** Heap of size k with frequency as priority

---

# Types of Heaps

## 1. Min Heap

**Property:** Parent ≤ Children (smallest element at root)

```
         5
        / \
       10  15
      / \  / \
     20 30 40 50

Root = Minimum element = 5
```

**Use Cases:**
- Find minimum element
- Ascending priority queue
- Dijkstra's algorithm
- Prim's algorithm

## 2. Max Heap

**Property:** Parent ≥ Children (largest element at root)

```
         50
        / \
       40  30
      / \  / \
     20 15 10 5

Root = Maximum element = 50
```

**Use Cases:**
- Find maximum element
- Descending priority queue
- Heap sort
- Job scheduling

## 3. Min-Max Heap

**Property:** Min levels alternate with max levels

```
Level 0 (min):        10
Level 1 (max):      /    \
                   50      40
Level 2 (min):    / \     / \
                 30  25  35  20
```

**Use Cases:**
- Double-ended priority queue
- Both min and max in O(1)

## 4. Fibonacci Heap

**Property:** Collection of min-heap-ordered trees

**Advantages:**
- Amortized O(1) for insert, decrease-key
- Used in graph algorithms

## 5. Binomial Heap

**Property:** Collection of binomial trees

**Advantages:**
- Efficient mergeable heap
- Used when frequent merge operations

## 6. d-ary Heap

**Property:** Each node has d children instead of 2

```
3-ary (Ternary) Heap:
         10
       / | \
      20 30 40
```

**Trade-off:**
- Shallower tree (better cache)
- More comparisons per level

---

# Terminology

| Term | Definition |
|------|------------|
| **Root** | Top element (min/max) |
| **Leaf** | Node with no children |
| **Height** | Maximum depth = ⌊log₂(n)⌋ |
| **Complete Binary Tree** | All levels full except last (filled left to right) |
| **Heap Property** | Ordering between parent and children |
| **Heapify** | Process to restore heap property |
| **Bubble Up** | Move element upward to maintain heap |
| **Bubble Down** | Move element downward to maintain heap |
| **Build Heap** | Create heap from unsorted array |

---

# Heap Properties

## 1. Complete Binary Tree Property

```
Valid (Complete):        Invalid (Not Complete):
       1                        1
      / \                      / \
     2   3                    2   3
    / \                          / \
   4   5                        4   5

All levels filled,         Gap in level 2
left to right
```

## 2. Heap Order Property

### Max Heap
```
Every parent ≥ its children

       90
      /  \
     80   70
    / \   / \
   40 50 60 30

90 ≥ 80, 90 ≥ 70
80 ≥ 40, 80 ≥ 50
70 ≥ 60, 70 ≥ 30  ✓
```

### Min Heap
```
Every parent ≤ its children

       10
      /  \
     20   30
    / \   / \
   40 50 60 70

10 ≤ 20, 10 ≤ 30
20 ≤ 40, 20 ≤ 50
30 ≤ 60, 30 ≤ 70  ✓
```

## 3. Array Representation Properties

```
For node at index i (0-based):
- Parent:      (i - 1) / 2
- Left child:  2 * i + 1
- Right child: 2 * i + 2

Example: [50, 30, 40, 10, 20, 35, 25]

Node at i=1 (value=30):
- Parent: (1-1)/2 = 0 → 50
- Left:   2*1+1 = 3   → 10
- Right:  2*1+2 = 4   → 20
```

## 4. Height Property

```
For heap with n nodes:
Height = ⌊log₂(n)⌋

Examples:
n = 7  → height = 2
n = 15 → height = 3
n = 31 → height = 4
```

## 5. Number of Nodes at Each Level

```
Level k has at most 2^k nodes

Level 0: 1 node
Level 1: 2 nodes
Level 2: 4 nodes
Level 3: 8 nodes
```

---

# Implementation

## Min Heap Implementation

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }
        
        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }
        
        if (i != minIndex) {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap() {}
    
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    int getMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
    
    void print() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};
```

## Max Heap Implementation

```cpp
class MaxHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        
        if (right < heap.size() && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    MaxHeap() {}
    
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    int getMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
};
```

## Build Heap from Array

```cpp
void buildHeap(vector<int>& arr) {
    // Start from last non-leaf node
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
}

void heapifyDown(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDown(arr, n, largest);
    }
}
```

---

# Heap Operations

## 1. Insert (Push)

```cpp
void insert(int val) {
    // Add element at end
    heap.push_back(val);
    
    // Bubble up to maintain heap property
    int i = heap.size() - 1;
    while (i > 0 && heap[parent(i)] > heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}
```

**Time Complexity:** O(log n)

**Example (Min Heap):**
```
Insert 3:
Step 1:        10
              /  \
             20   30
            / \   /
           40 50 60  [3]

Step 2:        10
              /  \
             20   30
            / \   / \
           40 50 60  3

Step 3 (Bubble Up):
               10
              /  \
             20    3      ← Swap 3 with 30
            / \   / \
           40 50 60 30

Step 4:        3          ← Swap 3 with 10
              / \
             20  10
            / \  / \
           40 50 60 30
```

## 2. Extract Min/Max

```cpp
int extractMin() {
    if (heap.empty()) throw exception();
    
    // Store root
    int minVal = heap[0];
    
    // Move last element to root
    heap[0] = heap.back();
    heap.pop_back();
    
    // Bubble down to maintain heap property
    heapifyDown(0);
    
    return minVal;
}
```

**Time Complexity:** O(log n)

**Example (Min Heap):**
```
Extract Min:
Step 1:        10          Remove 10
              /  \
             20   30
            / \   / \
           40 50 60 70

Step 2:        70          Move 70 to root
              /  \
             20   30
            / \   /
           40 50 60

Step 3 (Heapify Down):
               20          Swap 70 with 20
              /  \
             70   30
            / \   /
           40 50 60

Step 4:        20
              /  \
             40   30       Swap 70 with 40
            / \   /
           70 50 60
```

## 3. Peek (Get Min/Max)

```cpp
int getMin() {
    if (heap.empty()) throw exception();
    return heap[0];
}
```

**Time Complexity:** O(1)

## 4. Delete Element

```cpp
void deleteElement(int i) {
    // Decrease value to -infinity
    heap[i] = INT_MIN;
    heapifyUp(i);
    
    // Extract min
    extractMin();
}
```

**Time Complexity:** O(log n)

## 5. Decrease/Increase Key

```cpp
void decreaseKey(int i, int newVal) {
    heap[i] = newVal;
    heapifyUp(i);
}

void increaseKey(int i, int newVal) {
    heap[i] = newVal;
    heapifyDown(i);
}
```

**Time Complexity:** O(log n)

## 6. Heapify (Build Heap)

```cpp
void buildHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from last non-leaf node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
}
```

**Time Complexity:** O(n)

**Example:**
```
Array: [4, 10, 3, 5, 1]

Step 1: Start from index 1 (parent of last element)
        [4, 10, 3, 5, 1]
         
Step 2: Heapify at index 1
        [4, 1, 3, 5, 10]  (swap 10 and 1)
        
Step 3: Heapify at index 0
        [1, 4, 3, 5, 10]  (swap 4 and 1)
        [1, 4, 3, 5, 10]  (heapify 4)

Result: Min Heap
         1
        / \
       4   3
      / \
     5  10
```

## 7. Heap Sort

```cpp
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyDown(arr, i, 0);
    }
}
```

**Time Complexity:** O(n log n)  
**Space Complexity:** O(1)

---

# Applications

## 1. Priority Queue

```cpp
// Min Priority Queue using Heap
class PriorityQueue {
    MinHeap heap;
    
public:
    void enqueue(int val, int priority) {
        heap.insert(priority);
    }
    
    int dequeue() {
        return heap.extractMin();
    }
    
    int peek() {
        return heap.getMin();
    }
};
```

**Use Cases:**
- CPU scheduling
- Dijkstra's shortest path
- A* search algorithm
- Event simulation

## 2. Find Median in Stream

```cpp
class MedianFinder {
    MaxHeap maxHeap;  // Lower half
    MinHeap minHeap;  // Upper half
    
public:
    void addNum(int num) {
        if (maxHeap.isEmpty() || num < maxHeap.getMax()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(maxHeap.extractMax());
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.insert(minHeap.extractMin());
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.getMax() + minHeap.getMin()) / 2.0;
        }
        return maxHeap.getMax();
    }
};
```

## 3. Merge K Sorted Lists

```cpp
struct Node {
    int val;
    int listIndex;
    int elementIndex;
    
    bool operator>(const Node& other) const {
        return val > other.val;
    }
};

vector<int> mergeKSortedLists(vector<vector<int>>& lists) {
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;
    vector<int> result;
    
    // Add first element of each list
    for (int i = 0; i < lists.size(); i++) {
        if (!lists[i].empty()) {
            minHeap.push({lists[i][0], i, 0});
        }
    }
    
    while (!minHeap.empty()) {
        Node curr = minHeap.top();
        minHeap.pop();
        result.push_back(curr.val);
        
        // Add next element from same list
        if (curr.elementIndex + 1 < lists[curr.listIndex].size()) {
            minHeap.push({
                lists[curr.listIndex][curr.elementIndex + 1],
                curr.listIndex,
                curr.elementIndex + 1
            });
        }
    }
    
    return result;
}
```

## 4. Top K Frequent Elements

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    // Min heap of size k
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> minHeap;
    
    for (auto& [num, count] : freq) {
        minHeap.push({count, num});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    
    return result;
}
```

## 5. Kth Largest Element

```cpp
int findKthLargest(vector<int>& nums, int k) {
    // Min heap of size k
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}
```

## 6. Task Scheduler

```cpp
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char task : tasks) {
        freq[task]++;
    }
    
    priority_queue<int> maxHeap;
    for (auto& [task, count] : freq) {
        maxHeap.push(count);
    }
    
    int time = 0;
    while (!maxHeap.empty()) {
        vector<int> temp;
        for (int i = 0; i <= n; i++) {
            if (!maxHeap.empty()) {
                temp.push_back(maxHeap.top() - 1);
                maxHeap.pop();
            }
        }
        
        for (int count : temp) {
            if (count > 0) {
                maxHeap.push(count);
            }
        }
        
        time += maxHeap.empty() ? temp.size() : n + 1;
    }
    
    return time;
}
```

---

# Complete C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// ==================== MIN HEAP ====================

class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int minIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }
        
        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }
        
        if (i != minIndex) {
            swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    int getMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }
    
    bool isEmpty() { return heap.empty(); }
    int size() { return heap.size(); }
    
    void print() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// ==================== MAX HEAP ====================

class MaxHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void heapifyDown(int i) {
        int maxIndex = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < heap.size() && heap[left] > heap[maxIndex]) {
            maxIndex = left;
        }
        
        if (right < heap.size() && heap[right] > heap[maxIndex]) {
            maxIndex = right;
        }
        
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    int getMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }
    
    bool isEmpty() { return heap.empty(); }
    int size() { return heap.size(); }
    
    void print() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// ==================== HEAP SORT ====================

void heapifyDownForSort(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDownForSort(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDownForSort(arr, n, i);
    }
    
    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyDownForSort(arr, i, 0);
    }
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "========== MIN HEAP ==========\n";
    MinHeap minHeap;
    minHeap.insert(10);
    minHeap.insert(5);
    minHeap.insert(20);
    minHeap.insert(1);
    minHeap.insert(15);
    
    cout << "Min Heap: ";
    minHeap.print();
    cout << "Min element: " << minHeap.getMin() << endl;
    
    cout << "Extract min: " << minHeap.extractMin() << endl;
    cout << "After extraction: ";
    minHeap.print();
    
    cout << "\n========== MAX HEAP ==========\n";
    MaxHeap maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(5);
    maxHeap.insert(20);
    maxHeap.insert(1);
    maxHeap.insert(15);
    
    cout << "Max Heap: ";
    maxHeap.print();
    cout << "Max element: " << maxHeap.getMax() << endl;
    
    cout << "Extract max: " << maxHeap.extractMax() << endl;
    cout << "After extraction: ";
    maxHeap.print();
    
    cout << "\n========== HEAP SORT ==========\n";
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Original array: ";
    for (int val : arr) cout << val << " ";
    cout << endl;
    
    heapSort(arr);
    
    cout << "Sorted array: ";
    for (int val : arr) cout << val << " ";
    cout << endl;
    
    cout << "\n========== STL PRIORITY QUEUE ==========\n";
    // Min heap using STL
    priority_queue<int, vector<int>, greater<int>> pqMin;
    pqMin.push(10);
    pqMin.push(5);
    pqMin.push(20);
    
    cout << "STL Min Heap top: " << pqMin.top() << endl;
    
    // Max heap using STL
    priority_queue<int> pqMax;
    pqMax.push(10);
    pqMax.push(5);
    pqMax.push(20);
    
    cout << "STL Max Heap top: " << pqMax.top() << endl;
    
    return 0;
}
```

### Sample Output
```
========== MIN HEAP ==========
Min Heap: 1 10 20 5 15 
Min element: 1
Extract min: 1
After extraction: 5 10 20 15 

========== MAX HEAP ==========
Max Heap: 20 15 10 1 5 
Max element: 20
Extract max: 20
After extraction: 15 10 5 1 

========== HEAP SORT ==========
Original array: 12 11 13 5 6 7 
Sorted array: 5 6 7 11 12 13 

========== STL PRIORITY QUEUE ==========
STL Min Heap top: 5
STL Max Heap top: 20
```

---

# LeetCode Problems

## Easy Level

### 1. Last Stone Weight (LeetCode 1046)
**Problem:** Return weight of last remaining stone after smashing heaviest stones.

```cpp
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> maxHeap(stones.begin(), stones.end());
    
    while (maxHeap.size() > 1) {
        int first = maxHeap.top(); maxHeap.pop();
        int second = maxHeap.top(); maxHeap.pop();
        
        if (first != second) {
            maxHeap.push(first - second);
        }
    }
    
    return maxHeap.empty() ? 0 : maxHeap.top();
}
```

**Example:**
```
Input: stones = [2,7,4,1,8,1]
Process: 8-7=1, 4-2=2, 2-1=1, 1-1=0, 1 remains
Output: 1
```

### 2. Kth Largest Element in Array (LeetCode 215)
**Problem:** Find kth largest element in unsorted array.

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}
```

**Example:**
```
Input: nums = [3,2,1,5,6,4], k = 2
Min heap keeps 2 largest: [5, 6]
Output: 5
```

### 3. Relative Ranks (LeetCode 506)
**Problem:** Assign gold, silver, bronze medals to top 3 scores.

```cpp
vector<string> findRelativeRanks(vector<int>& score) {
    priority_queue<pair<int, int>> maxHeap;
    
    for (int i = 0; i < score.size(); i++) {
        maxHeap.push({score[i], i});
    }
    
    vector<string> result(score.size());
    int rank = 1;
    
    while (!maxHeap.empty()) {
        int idx = maxHeap.top().second;
        maxHeap.pop();
        
        if (rank == 1) result[idx] = "Gold Medal";
        else if (rank == 2) result[idx] = "Silver Medal";
        else if (rank == 3) result[idx] = "Bronze Medal";
        else result[idx] = to_string(rank);
        
        rank++;
    }
    
    return result;
}
```

### 4. Take Gifts From Richest Pile (LeetCode 2558)
**Problem:** Leave behind floor(sqrt(pile)) gifts each second for k seconds.

```cpp
long long pickGifts(vector<int>& gifts, int k) {
    priority_queue<int> maxHeap(gifts.begin(), gifts.end());
    
    for (int i = 0; i < k; i++) {
        int maxGift = maxHeap.top();
        maxHeap.pop();
        maxHeap.push((int)sqrt(maxGift));
    }
    
    long long total = 0;
    while (!maxHeap.empty()) {
        total += maxHeap.top();
        maxHeap.pop();
    }
    
    return total;
}
```

## Medium Level

### 5. Top K Frequent Elements (LeetCode 347)
**Problem:** Return k most frequent elements.

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    priority_queue<pair<int, int>, 
                   vector<pair<int, int>>, 
                   greater<pair<int, int>>> minHeap;
    
    for (auto& [num, count] : freq) {
        minHeap.push({count, num});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    
    return result;
}
```

**Example:**
```
Input: nums = [1,1,1,2,2,3], k = 2
Frequencies: {1:3, 2:2, 3:1}
Output: [1,2]
```

### 6. Kth Largest Element in Stream (LeetCode 703)
**Problem:** Design class to find kth largest in stream.

```cpp
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
    
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};
```

### 7. K Closest Points to Origin (LeetCode 973)
**Problem:** Find k closest points to origin (0, 0).

```cpp
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
    };
    
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxHeap(cmp);
    
    for (auto& point : points) {
        maxHeap.push(point);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    
    return result;
}
```

### 8. Task Scheduler (LeetCode 621)
**Problem:** Find minimum units of time to complete all tasks with cooldown.

```cpp
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char task : tasks) {
        freq[task]++;
    }
    
    priority_queue<int> maxHeap;
    for (auto& [task, count] : freq) {
        maxHeap.push(count);
    }
    
    int time = 0;
    while (!maxHeap.empty()) {
        vector<int> temp;
        
        for (int i = 0; i <= n; i++) {
            if (!maxHeap.empty()) {
                temp.push_back(maxHeap.top() - 1);
                maxHeap.pop();
            }
        }
        
        for (int count : temp) {
            if (count > 0) {
                maxHeap.push(count);
            }
        }
        
        time += maxHeap.empty() ? temp.size() : n + 1;
    }
    
    return time;
}
```

### 9. Reorganize String (LeetCode 767)
**Problem:** Reorganize string so no two adjacent characters are same.

```cpp
string reorganizeString(string s) {
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    priority_queue<pair<int, char>> maxHeap;
    for (auto& [c, count] : freq) {
        maxHeap.push({count, c});
    }
    
    string result = "";
    pair<int, char> prev = {-1, '#'};
    
    while (!maxHeap.empty()) {
        auto curr = maxHeap.top();
        maxHeap.pop();
        
        result += curr.second;
        
        if (prev.first > 0) {
            maxHeap.push(prev);
        }
        
        curr.first--;
        prev = curr;
    }
    
    return result.length() == s.length() ? result : "";
}
```

### 10. Minimum Cost to Connect Sticks (LeetCode 1167)
**Problem:** Connect all sticks with minimum cost (cost = sum of stick lengths).

```cpp
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> minHeap(sticks.begin(), sticks.end());
    
    int totalCost = 0;
    
    while (minHeap.size() > 1) {
        int first = minHeap.top(); minHeap.pop();
        int second = minHeap.top(); minHeap.pop();
        
        int cost = first + second;
        totalCost += cost;
        minHeap.push(cost);
    }
    
    return totalCost;
}
```

### 11. Furthest Building You Can Reach (LeetCode 1642)
**Problem:** Use bricks and ladders optimally to reach furthest building.

```cpp
int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int i = 0; i < heights.size() - 1; i++) {
        int diff = heights[i + 1] - heights[i];
        
        if (diff <= 0) continue;
        
        minHeap.push(diff);
        
        if (minHeap.size() > ladders) {
            bricks -= minHeap.top();
            minHeap.pop();
        }
        
        if (bricks < 0) {
            return i;
        }
    }
    
    return heights.size() - 1;
}
```

### 12. Kth Smallest Element in Sorted Matrix (LeetCode 378)
**Problem:** Find kth smallest element in n×n matrix with sorted rows and columns.

```cpp
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>, 
                   greater<pair<int, pair<int, int>>>> minHeap;
    
    // Add first element of each row
    for (int i = 0; i < min(n, k); i++) {
        minHeap.push({matrix[i][0], {i, 0}});
    }
    
    int result = 0;
    for (int i = 0; i < k; i++) {
        auto [val, pos] = minHeap.top();
        minHeap.pop();
        result = val;
        
        int row = pos.first;
        int col = pos.second;
        
        if (col + 1 < n) {
            minHeap.push({matrix[row][col + 1], {row, col + 1}});
        }
    }
    
    return result;
}
```

## Hard Level

### 13. Find Median from Data Stream (LeetCode 295)
**Problem:** Find median efficiently as numbers are added.

```cpp
class MedianFinder {
    priority_queue<int> maxHeap;  // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Upper half
    
public:
    void addNum(int num) {
        if (maxHeap.empty() || num < maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};
```

**Example:**
```
addNum(1): maxHeap=[1], minHeap=[]
addNum(2): maxHeap=[1], minHeap=[2]
findMedian(): (1+2)/2 = 1.5

addNum(3): maxHeap=[2,1], minHeap=[3]
findMedian(): 2
```

### 14. Merge K Sorted Lists (LeetCode 23)
**Problem:** Merge k sorted linked lists into one sorted list.

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
    };
    
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);
    
    for (ListNode* list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }
    
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        
        curr->next = node;
        curr = curr->next;
        
        if (node->next) {
            minHeap.push(node->next);
        }
    }
    
    return dummy->next;
}
```

### 15. Sliding Window Median (LeetCode 480)
**Problem:** Find median in each sliding window of size k.

```cpp
class SlidingWindowMedian {
    multiset<int> minHeap, maxHeap;
    
    void addNum(int num) {
        if (maxHeap.empty() || num <= *maxHeap.rbegin()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }
        balance();
    }
    
    void removeNum(int num) {
        if (maxHeap.count(num)) {
            maxHeap.erase(maxHeap.find(num));
        } else {
            minHeap.erase(minHeap.find(num));
        }
        balance();
    }
    
    void balance() {
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(*maxHeap.rbegin());
            maxHeap.erase(prev(maxHeap.end()));
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.insert(*minHeap.begin());
            minHeap.erase(minHeap.begin());
        }
    }
    
    double getMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (*maxHeap.rbegin() + *minHeap.begin()) / 2.0;
        }
        return *maxHeap.rbegin();
    }
    
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        
        for (int i = 0; i < nums.size(); i++) {
            addNum(nums[i]);
            
            if (i >= k) {
                removeNum(nums[i - k]);
            }
            
            if (i >= k - 1) {
                result.push_back(getMedian());
            }
        }
        
        return result;
    }
};
```

### 16. IPO (LeetCode 502)
**Problem:** Maximize capital by completing at most k projects.

```cpp
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    vector<pair<int, int>> projects;
    for (int i = 0; i < profits.size(); i++) {
        projects.push_back({capital[i], profits[i]});
    }
    sort(projects.begin(), projects.end());
    
    priority_queue<int> maxHeap;
    int i = 0;
    
    for (int j = 0; j < k; j++) {
        // Add all affordable projects
        while (i < projects.size() && projects[i].first <= w) {
            maxHeap.push(projects[i].second);
            i++;
        }
        
        if (maxHeap.empty()) break;
        
        w += maxHeap.top();
        maxHeap.pop();
    }
    
    return w;
}
```

### 17. Smallest Range Covering K Lists (LeetCode 632)
**Problem:** Find smallest range that includes at least one number from each list.

```cpp
vector<int> smallestRange(vector<vector<int>>& nums) {
    auto cmp = [&](pair<int, int>& a, pair<int, int>& b) {
        return nums[a.first][a.second] > nums[b.first][b.second];
    };
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
    
    int maxVal = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        minHeap.push({i, 0});
        maxVal = max(maxVal, nums[i][0]);
    }
    
    int rangeStart = 0, rangeEnd = INT_MAX;
    
    while (minHeap.size() == nums.size()) {
        auto [listIdx, elemIdx] = minHeap.top();
        minHeap.pop();
        
        int minVal = nums[listIdx][elemIdx];
        
        if (maxVal - minVal < rangeEnd - rangeStart) {
            rangeStart = minVal;
            rangeEnd = maxVal;
        }
        
        if (elemIdx + 1 < nums[listIdx].size()) {
            minHeap.push({listIdx, elemIdx + 1});
            maxVal = max(maxVal, nums[listIdx][elemIdx + 1]);
        }
    }
    
    return {rangeStart, rangeEnd};
}
```

---

## Problem Categories Summary

### By Heap Type

**Min Heap Problems:**
- Kth Largest Element (215)
- Merge K Sorted Lists (23)
- K Closest Points (973)
- Find Median (295)

**Max Heap Problems:**
- Kth Smallest Element (378)
- Last Stone Weight (1046)
- Top K Frequent (347)

**Both Heaps:**
- Find Median from Stream (295)
- Sliding Window Median (480)

### By Technique

**Fixed Size Heap:**
- Kth Largest/Smallest
- Top K Frequent
- K Closest Points

**Multiple Heaps:**
- Median problems
- IPO
- Smallest Range

**Heap + HashMap:**
- Top K Frequent
- Task Scheduler
- Reorganize String

---

**Master Heaps, Master Priority-Based Problems! 📊**

## Key Takeaways

### When to Use Heap

✅ **Use Heap when you need:**
- Kth largest/smallest element
- Top K elements
- Median of stream
- Merge K sorted structures
- Priority-based scheduling
- Continuous min/max access

### Time Complexity Summary

| Operation | Time | Use Case |
|-----------|------|----------|
| Insert | O(log n) | Add element |
| Extract Min/Max | O(log n) | Remove top |
| Get Min/Max | O(1) | Peek top |
| Build Heap | O(n) | From array |
| Heap Sort | O(n log n) | Sort array |

### Common Patterns

1. **Kth Element Pattern**: Use heap of size k
2. **Median Pattern**: Use two heaps (max + min)
3. **Merge Pattern**: Use min heap with k pointers
4. **Frequency Pattern**: Heap + HashMap

**Remember:** Heaps are perfect when you need repeated access to the extreme (min/max) element!
