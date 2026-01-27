# Time & Space Complexity - Beginner to Advanced

## Table of Contents
- [Introduction](#introduction)
- [Why Study Complexity?](#why-study-complexity)
- [Big O Notation Basics](#big-o-notation-basics)
- [Common Time Complexities](#common-time-complexities)
- [Analyzing Code Examples](#analyzing-code-examples)
- [Space Complexity](#space-complexity)
- [Asymptotic Notations](#asymptotic-notations)
- [Advanced Topics](#advanced-topics)
- [Complexity of Data Structures](#complexity-of-data-structures)
- [Complexity of Algorithms](#complexity-of-algorithms)
- [Master Theorem](#master-theorem)
- [Amortized Analysis](#amortized-analysis)
- [Practice Problems](#practice-problems)

---

# Introduction

**Time Complexity** measures how the runtime of an algorithm grows as the input size increases.  
**Space Complexity** measures how much memory an algorithm uses as the input size increases.

## Key Concepts

- **Input Size (n):** The size of the input to the algorithm
- **Growth Rate:** How fast the runtime/memory grows with n
- **Worst Case:** Maximum time/space for any input of size n
- **Best Case:** Minimum time/space for any input of size n
- **Average Case:** Expected time/space over all inputs

---

# Why Study Complexity?

## 1. Performance Prediction
```cpp
// Algorithm A: O(n)
for (int i = 0; i < n; i++) {
    cout << i;
}

// Algorithm B: O(n²)
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        cout << i << j;
    }
}
```

**For n = 1,000:**
- Algorithm A: ~1,000 operations
- Algorithm B: ~1,000,000 operations (1000× slower!)

## 2. Scalability
| n | O(log n) | O(n) | O(n log n) | O(n²) | O(2ⁿ) |
|---|----------|------|------------|-------|-------|
| 10 | 3 | 10 | 33 | 100 | 1,024 |
| 100 | 7 | 100 | 664 | 10,000 | 1.27×10³⁰ |
| 1,000 | 10 | 1,000 | 9,966 | 1,000,000 | ∞ |
| 1,000,000 | 20 | 1,000,000 | 19,931,569 | 1,000,000,000,000 | ∞ |

## 3. Interview Success
- Most coding interviews focus on complexity analysis
- Expected to analyze your solution's time and space complexity
- Often asked to optimize from O(n²) to O(n log n) or O(n)

---

# Big O Notation Basics

## What is Big O?

Big O describes the **upper bound** of algorithm complexity. It tells us the **worst-case scenario**.

### Formal Definition
f(n) = O(g(n)) if there exist constants c and n₀ such that:
```
f(n) ≤ c × g(n) for all n ≥ n₀
```

### Informal Understanding
Big O describes how the algorithm scales with input size, **ignoring constants and lower-order terms**.

## Rules of Big O

### Rule 1: Drop Constants
```cpp
// Both are O(n), not O(2n) or O(3n)
void example1(int n) {
    for (int i = 0; i < n; i++) { }      // O(n)
    for (int i = 0; i < n; i++) { }      // O(n)
}  // Total: O(n) + O(n) = O(2n) = O(n)
```

### Rule 2: Drop Non-Dominant Terms
```cpp
// O(n² + n) = O(n²)
void example2(int n) {
    for (int i = 0; i < n; i++) {        // O(n)
        // single operation
    }
    for (int i = 0; i < n; i++) {        // O(n²)
        for (int j = 0; j < n; j++) {
            // operation
        }
    }
}  // Total: O(n) + O(n²) = O(n²)
```

### Rule 3: Different Inputs = Different Variables
```cpp
// O(a + b), NOT O(n)
void example3(int a, int b) {
    for (int i = 0; i < a; i++) { }      // O(a)
    for (int i = 0; i < b; i++) { }      // O(b)
}  // Total: O(a + b)

// O(a × b), NOT O(n²)
void example4(int a, int b) {
    for (int i = 0; i < a; i++) {        // O(a)
        for (int j = 0; j < b; j++) {    // O(b)
            // operation
        }
    }
}  // Total: O(a × b)
```

### Rule 4: Logarithms
```cpp
// O(log n)
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
// Each iteration halves the search space: n, n/2, n/4, ... 1
// Number of iterations = log₂(n)
```

---

# Common Time Complexities

## O(1) - Constant Time

**Definition:** Runtime doesn't depend on input size.

```cpp
// Example 1: Array access
int getElement(int arr[], int index) {
    return arr[index];  // O(1)
}

// Example 2: Hash table lookup
unordered_map<int, int> map;
int value = map[key];  // O(1) average

// Example 3: Mathematical operations
int add(int a, int b) {
    return a + b;  // O(1)
}
```

**Characteristics:**
- Most efficient
- Runtime is predictable
- No loops or recursion

## O(log n) - Logarithmic Time

**Definition:** Runtime grows logarithmically with input size.

```cpp
// Example 1: Binary Search
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Example 2: Finding power
int power(int base, int exp) {
    if (exp == 0) return 1;
    int half = power(base, exp / 2);
    if (exp % 2 == 0)
        return half * half;
    else
        return base * half * half;
}
```

**Characteristics:**
- Very efficient for large inputs
- Usually involves dividing problem in half
- Common in divide-and-conquer algorithms

## O(n) - Linear Time

**Definition:** Runtime grows linearly with input size.

```cpp
// Example 1: Linear search
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Example 2: Sum of array
int sum(vector<int>& arr) {
    int total = 0;
    for (int num : arr) {
        total += num;
    }
    return total;
}

// Example 3: Finding max
int findMax(vector<int>& arr) {
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}
```

**Characteristics:**
- Single loop through data
- Each element processed once
- Common baseline complexity

## O(n log n) - Linearithmic Time

**Definition:** Runtime is n × log n.

```cpp
// Example 1: Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    // Merge logic: O(n)
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);      // T(n/2)
        mergeSort(arr, m + 1, r);  // T(n/2)
        merge(arr, l, m, r);       // O(n)
    }
}
// T(n) = 2T(n/2) + O(n) = O(n log n)

// Example 2: Quick Sort (average case)
int partition(vector<int>& arr, int low, int high) {
    // Partition logic: O(n)
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Example 3: Heap Sort
void heapSort(vector<int>& arr) {
    // Build heap: O(n)
    // Extract elements: n × O(log n)
}  // Total: O(n log n)
```

**Characteristics:**
- Best achievable for comparison-based sorting
- Common in efficient divide-and-conquer algorithms
- Better than O(n²) for large inputs

## O(n²) - Quadratic Time

**Definition:** Runtime grows quadratically with input size.

```cpp
// Example 1: Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {           // O(n)
        for (int j = 0; j < n - i - 1; j++) {   // O(n)
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}  // O(n × n) = O(n²)

// Example 2: Nested loops
void printPairs(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {      // O(n)
        for (int j = 0; j < arr.size(); j++) {  // O(n)
            cout << arr[i] << ", " << arr[j] << endl;
        }
    }
}

// Example 3: Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

**Characteristics:**
- Nested loops of same size
- Acceptable for small inputs (n < 1000)
- Should be optimized for larger inputs

## O(n³) - Cubic Time

**Definition:** Runtime grows cubically with input size.

```cpp
// Example 1: Three nested loops
void printTriplets(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {           // O(n)
        for (int j = 0; j < n; j++) {       // O(n)
            for (int k = 0; k < n; k++) {   // O(n)
                cout << arr[i] << ", " << arr[j] << ", " << arr[k] << endl;
            }
        }
    }
}  // O(n³)

// Example 2: Matrix multiplication (naive)
void matrixMultiply(int A[][100], int B[][100], int C[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
```

**Characteristics:**
- Very slow for large inputs
- Rare in practical algorithms
- Often can be optimized

## O(2ⁿ) - Exponential Time

**Definition:** Runtime doubles with each additional input.

```cpp
// Example 1: Fibonacci (naive recursion)
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
// Each call makes 2 recursive calls
// Tree height = n, nodes ≈ 2ⁿ

// Example 2: Power set (all subsets)
void generateSubsets(vector<int>& arr, int index, vector<int>& current) {
    if (index == arr.size()) {
        printVector(current);
        return;
    }
    
    // Exclude current element
    generateSubsets(arr, index + 1, current);
    
    // Include current element
    current.push_back(arr[index]);
    generateSubsets(arr, index + 1, current);
    current.pop_back();
}
// Total subsets = 2ⁿ

// Example 3: Tower of Hanoi
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    towerOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towerOfHanoi(n - 1, aux, to, from);
}
// T(n) = 2T(n-1) + 1 = O(2ⁿ)
```

**Characteristics:**
- Extremely slow
- Impractical for n > 30
- Often requires memoization/DP optimization

## O(n!) - Factorial Time

**Definition:** Runtime is factorial of input size.

```cpp
// Example 1: Generate all permutations
void permute(string str, int l, int r) {
    if (l == r) {
        cout << str << endl;
        return;
    }
    
    for (int i = l; i <= r; i++) {
        swap(str[l], str[i]);
        permute(str, l + 1, r);
        swap(str[l], str[i]);  // backtrack
    }
}
// Total permutations = n!

// Example 2: Traveling Salesman (brute force)
int tsp(vector<vector<int>>& graph, int pos, int visited, int n) {
    if (visited == (1 << n) - 1) {
        return graph[pos][0];
    }
    
    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((visited & (1 << city)) == 0) {
            int newAns = graph[pos][city] + 
                        tsp(graph, city, visited | (1 << city), n);
            ans = min(ans, newAns);
        }
    }
    return ans;
}
```

**Characteristics:**
- Slowest common complexity
- Only feasible for n ≤ 10
- Usually requires optimization (DP, pruning)

---

# Analyzing Code Examples

## Example 1: Simple Loop
```cpp
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
```
**Analysis:** 
- Loop runs n times
- Each iteration does O(1) work
- **Time Complexity: O(n)**
- **Space Complexity: O(1)** (no extra space)

## Example 2: Nested Loops (Same Size)
```cpp
void printPairs(int arr[], int n) {
    for (int i = 0; i < n; i++) {           // O(n)
        for (int j = 0; j < n; j++) {       // O(n)
            cout << arr[i] << ", " << arr[j];
        }
    }
}
```
**Analysis:**
- Outer loop: n iterations
- Inner loop: n iterations for each outer iteration
- Total: n × n = n²
- **Time Complexity: O(n²)**

## Example 3: Nested Loops (Different Sizes)
```cpp
void example(int arr[], int n) {
    for (int i = 0; i < n; i++) {           // O(n)
        for (int j = i; j < n; j++) {       // O(n - i)
            cout << arr[i] << ", " << arr[j];
        }
    }
}
```
**Analysis:**
- Outer loop: n iterations
- Inner loop: (n-0) + (n-1) + ... + 1 = n(n+1)/2
- **Time Complexity: O(n²)**

## Example 4: Logarithmic Loop
```cpp
void example(int n) {
    for (int i = 1; i < n; i *= 2) {
        cout << i << " ";
    }
}
// Output for n=16: 1 2 4 8
```
**Analysis:**
- i doubles each iteration: 1, 2, 4, 8, ..., n
- Number of iterations until i ≥ n: log₂(n)
- **Time Complexity: O(log n)**

## Example 5: Logarithmic with Linear Work
```cpp
void example(int n) {
    for (int i = 1; i < n; i *= 2) {        // O(log n)
        for (int j = 0; j < n; j++) {       // O(n)
            cout << i << " " << j << endl;
        }
    }
}
```
**Analysis:**
- Outer loop: log n iterations
- Inner loop: n iterations each time
- **Time Complexity: O(n log n)**

## Example 6: Recursive Function
```cpp
void printN(int n) {
    if (n <= 0) return;
    cout << n << " ";
    printN(n - 1);
}
```
**Analysis:**
- Recurrence: T(n) = T(n-1) + O(1)
- Base case: T(0) = O(1)
- **Time Complexity: O(n)**
- **Space Complexity: O(n)** (recursion stack)

## Example 7: Binary Recursion
```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```
**Analysis:**
- Each call makes 2 recursive calls
- Recursion tree has ~2ⁿ nodes
- **Time Complexity: O(2ⁿ)**
- **Space Complexity: O(n)** (max recursion depth)

## Example 8: Multiple Loops
```cpp
void example(int arr[], int n) {
    // Loop 1
    for (int i = 0; i < n; i++) {
        cout << arr[i];
    }
    
    // Loop 2
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i] << arr[j];
        }
    }
}
```
**Analysis:**
- Loop 1: O(n)
- Loop 2: O(n²)
- Total: O(n) + O(n²) = O(n²)
- **Time Complexity: O(n²)** (drop lower order terms)

---

# Space Complexity

Space complexity measures memory usage as a function of input size.

## Components of Space Complexity

1. **Fixed Part:** Space for code, constants, variables (O(1))
2. **Variable Part:** Space that depends on input size

## Auxiliary Space vs Total Space

- **Auxiliary Space:** Extra space used by algorithm (excluding input)
- **Total Space:** Auxiliary space + Input space

## Examples

### O(1) - Constant Space
```cpp
int sum(int arr[], int n) {
    int total = 0;              // O(1) space
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}
// Auxiliary Space: O(1)
// Total Space: O(n) [input array]
```

### O(n) - Linear Space
```cpp
vector<int> doubleArray(vector<int>& arr) {
    vector<int> result(arr.size());  // O(n) space
    for (int i = 0; i < arr.size(); i++) {
        result[i] = arr[i] * 2;
    }
    return result;
}
// Auxiliary Space: O(n)
```

### O(n) - Recursion Stack
```cpp
void printN(int n) {
    if (n <= 0) return;
    cout << n << " ";
    printN(n - 1);  // O(n) recursive calls on stack
}
// Space: O(n) for recursion stack
```

### O(log n) - Binary Search
```cpp
int binarySearch(int arr[], int l, int r, int target) {
    if (l > r) return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target)
        return binarySearch(arr, l, mid - 1, target);
    return binarySearch(arr, mid + 1, r, target);
}
// Space: O(log n) for recursion stack (tree height)
```

### O(n²) - 2D Matrix
```cpp
void create2DArray(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];  // n × n matrix
    }
}
// Space: O(n²)
```

---

# Asymptotic Notations

## Big O (O) - Upper Bound

Represents **worst-case** or **upper bound** of algorithm.

```
f(n) = O(g(n)) means f(n) ≤ c × g(n) for large n
```

**Example:**
- 3n + 2 = O(n)
- n² + n = O(n²)

## Big Omega (Ω) - Lower Bound

Represents **best-case** or **lower bound** of algorithm.

```
f(n) = Ω(g(n)) means f(n) ≥ c × g(n) for large n
```

**Example:**
- Binary search: Ω(1) - might find element immediately
- Linear search: Ω(1) - element might be first

## Big Theta (Θ) - Tight Bound

Represents **average-case** or **tight bound**.

```
f(n) = Θ(g(n)) means c₁ × g(n) ≤ f(n) ≤ c₂ × g(n)
```

**Example:**
- Merge Sort: Θ(n log n) - always this complexity
- n² + n = Θ(n²)

## Little o (o) - Strict Upper Bound

```
f(n) = o(g(n)) means f(n) < c × g(n) for large n
```

**Example:**
- n = o(n²)
- log n = o(n)

## Little omega (ω) - Strict Lower Bound

```
f(n) = ω(g(n)) means f(n) > c × g(n) for large n
```

## Visual Representation

```
        Upper Bounds
            ↑
    o(g(n)) | O(g(n))
            |
    -----Θ(g(n))-----  Tight Bound
            |
    ω(g(n)) | Ω(g(n))
            ↓
        Lower Bounds
```

---

# Advanced Topics

## Recurrence Relations

### Method 1: Substitution Method

**Example:** T(n) = T(n-1) + n

```
T(n) = T(n-1) + n
     = [T(n-2) + (n-1)] + n
     = T(n-2) + (n-1) + n
     = T(n-3) + (n-2) + (n-1) + n
     = ...
     = T(1) + 2 + 3 + ... + n
     = 1 + 2 + 3 + ... + n
     = n(n+1)/2
     = O(n²)
```

### Method 2: Recursion Tree

**Example:** T(n) = 2T(n/2) + n

```
Level 0:              n              → n
                    /   \
Level 1:         n/2    n/2          → n
                / \     / \
Level 2:      n/4 n/4 n/4 n/4        → n
              ...

Height = log n
Work per level = n
Total = n × log n = O(n log n)
```

### Method 3: Master Theorem (see below)

## Best, Average, Worst Case

### Linear Search
```cpp
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

- **Best Case: O(1)** - Element at first position
- **Average Case: O(n/2) = O(n)** - Element in middle
- **Worst Case: O(n)** - Element not present or at end

### Quick Sort
- **Best Case: O(n log n)** - Pivot always divides evenly
- **Average Case: O(n log n)** - Random pivot selection
- **Worst Case: O(n²)** - Pivot always smallest/largest

## Amortized Analysis

Analyzes average cost per operation over a sequence of operations.

### Example: Dynamic Array

```cpp
class DynamicArray {
    int* arr;
    int capacity;
    int size;
    
public:
    void push_back(int val) {
        if (size == capacity) {
            // Resize: O(n)
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = val;  // O(1)
    }
};
```

**Analysis:**
- Most insertions: O(1)
- Occasional resize: O(n)
- **Amortized Cost: O(1) per insertion**

**Proof:**
- Insert n elements
- Resizes at: 1, 2, 4, 8, ..., n
- Total copy operations: 1 + 2 + 4 + ... + n = 2n - 1
- Average per insertion: (2n-1)/n ≈ 2 = O(1)

---

# Complexity of Data Structures

## Arrays
| Operation | Time | Space |
|-----------|------|-------|
| Access | O(1) | O(n) |
| Search | O(n) | O(1) |
| Insert (end) | O(1) | O(1) |
| Insert (arbitrary) | O(n) | O(1) |
| Delete (end) | O(1) | O(1) |
| Delete (arbitrary) | O(n) | O(1) |

## Linked List
| Operation | Time | Space |
|-----------|------|-------|
| Access | O(n) | O(n) |
| Search | O(n) | O(1) |
| Insert (beginning) | O(1) | O(1) |
| Insert (end) | O(n) | O(1) |
| Delete (beginning) | O(1) | O(1) |
| Delete (given node) | O(1) | O(1) |

## Stack
| Operation | Time | Space |
|-----------|------|-------|
| Push | O(1) | O(n) |
| Pop | O(1) | O(1) |
| Top | O(1) | O(1) |
| Search | O(n) | O(1) |

## Queue
| Operation | Time | Space |
|-----------|------|-------|
| Enqueue | O(1) | O(n) |
| Dequeue | O(1) | O(1) |
| Front | O(1) | O(1) |
| Search | O(n) | O(1) |

## Binary Search Tree (Balanced)
| Operation | Average | Worst | Space |
|-----------|---------|-------|-------|
| Search | O(log n) | O(n) | O(n) |
| Insert | O(log n) | O(n) | O(1) |
| Delete | O(log n) | O(n) | O(1) |

## Hash Table
| Operation | Average | Worst | Space |
|-----------|---------|-------|-------|
| Search | O(1) | O(n) | O(n) |
| Insert | O(1) | O(n) | O(1) |
| Delete | O(1) | O(n) | O(1) |

## Heap
| Operation | Time | Space |
|-----------|------|-------|
| Find Min/Max | O(1) | O(n) |
| Insert | O(log n) | O(1) |
| Delete Min/Max | O(log n) | O(1) |
| Build Heap | O(n) | O(1) |

## Graph (Adjacency List)
| Operation | Time | Space |
|-----------|------|-------|
| Add Vertex | O(1) | O(V+E) |
| Add Edge | O(1) | O(1) |
| Remove Vertex | O(V+E) | O(1) |
| Remove Edge | O(E) | O(1) |
| DFS/BFS | O(V+E) | O(V) |

---

# Complexity of Algorithms

## Sorting Algorithms
| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(k) | Yes |
| Radix Sort | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n) | Yes |

**Notes:**
- k = range of input values
- d = number of digits

## Searching Algorithms
| Algorithm | Best | Average | Worst | Space | Notes |
|-----------|------|---------|-------|-------|-------|
| Linear Search | O(1) | O(n) | O(n) | O(1) | Unsorted data |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) | Sorted data |
| Jump Search | O(1) | O(√n) | O(√n) | O(1) | Sorted data |
| Interpolation Search | O(1) | O(log log n) | O(n) | O(1) | Uniformly distributed |
| Exponential Search | O(1) | O(log n) | O(log n) | O(1) | Unbounded/infinite |

## Graph Algorithms
| Algorithm | Time Complexity | Space | Use Case |
|-----------|----------------|-------|----------|
| BFS | O(V+E) | O(V) | Shortest path (unweighted) |
| DFS | O(V+E) | O(V) | Cycle detection, topological sort |
| Dijkstra | O((V+E) log V) | O(V) | Shortest path (weighted, non-negative) |
| Bellman-Ford | O(VE) | O(V) | Shortest path (negative edges) |
| Floyd-Warshall | O(V³) | O(V²) | All pairs shortest path |
| Prim's | O((V+E) log V) | O(V) | Minimum spanning tree |
| Kruskal's | O(E log E) | O(V) | Minimum spanning tree |
| Topological Sort | O(V+E) | O(V) | DAG ordering |

## String Algorithms
| Algorithm | Time Complexity | Space | Use Case |
|-----------|----------------|-------|----------|
| Naive Pattern Match | O(nm) | O(1) | Simple pattern search |
| KMP | O(n+m) | O(m) | Pattern matching |
| Rabin-Karp | O(n+m) | O(1) | Multiple pattern search |
| Boyer-Moore | O(n/m) to O(nm) | O(m) | Fast pattern matching |
| Z-Algorithm | O(n+m) | O(n+m) | Pattern matching |
| Aho-Corasick | O(n+m+z) | O(m) | Multiple pattern matching |

## Dynamic Programming Problems
| Problem | Time Complexity | Space | Notes |
|---------|----------------|-------|-------|
| Fibonacci | O(n) | O(n) or O(1) | With memoization |
| Longest Common Subsequence | O(nm) | O(nm) | Can be optimized to O(min(n,m)) |
| Longest Increasing Subsequence | O(n log n) | O(n) | Binary search approach |
| 0/1 Knapsack | O(nW) | O(nW) | W = capacity |
| Matrix Chain Multiplication | O(n³) | O(n²) | |
| Edit Distance | O(nm) | O(nm) | |

---

# Master Theorem

The Master Theorem provides a shortcut for solving recurrence relations of the form:

```
T(n) = aT(n/b) + f(n)
```

Where:
- a ≥ 1 (number of subproblems)
- b > 1 (factor by which problem size is reduced)
- f(n) is the cost of work done outside recursive calls

## Three Cases

Let c = log_b(a)

### Case 1: f(n) = O(n^c - ε) for some ε > 0
**If work decreases geometrically:**
```
T(n) = Θ(n^c)
```

**Example:**
```
T(n) = 2T(n/2) + O(1)
a = 2, b = 2, c = log₂(2) = 1
f(n) = O(1) = O(n⁰) < O(n¹)
Therefore: T(n) = Θ(n)
```

### Case 2: f(n) = Θ(n^c × log^k n) for some k ≥ 0
**If work is equal at each level:**
```
T(n) = Θ(n^c × log^(k+1) n)
```

**Example:**
```
T(n) = 2T(n/2) + O(n)
a = 2, b = 2, c = log₂(2) = 1
f(n) = O(n) = Θ(n^c × log⁰ n)
Therefore: T(n) = Θ(n log n)  [Merge Sort]
```

### Case 3: f(n) = Ω(n^c + ε) for some ε > 0
**If work increases geometrically:**

AND if a × f(n/b) ≤ k × f(n) for some k < 1 (regularity condition):
```
T(n) = Θ(f(n))
```

**Example:**
```
T(n) = 2T(n/2) + O(n²)
a = 2, b = 2, c = log₂(2) = 1
f(n) = O(n²) > O(n¹)
Regularity: 2(n/2)² = n²/2 ≤ k×n² for k = 1/2 < 1 ✓
Therefore: T(n) = Θ(n²)
```

## Common Examples

| Recurrence | a | b | c | f(n) | Case | Result |
|------------|---|---|---|------|------|--------|
| T(n) = T(n/2) + O(1) | 1 | 2 | 0 | O(1) | 2 | O(log n) |
| T(n) = 2T(n/2) + O(n) | 2 | 2 | 1 | O(n) | 2 | O(n log n) |
| T(n) = 4T(n/2) + O(n) | 4 | 2 | 2 | O(n) | 1 | O(n²) |
| T(n) = 2T(n/2) + O(n²) | 2 | 2 | 1 | O(n²) | 3 | O(n²) |
| T(n) = T(n/2) + O(n) | 1 | 2 | 0 | O(n) | 3 | O(n) |
| T(n) = 3T(n/2) + O(n) | 3 | 2 | 1.58 | O(n) | 1 | O(n^1.58) |

## When Master Theorem Doesn't Apply

Master Theorem cannot be used when:
- f(n) is not polynomial (e.g., f(n) = n log n)
- Recurrence is not in the form T(n) = aT(n/b) + f(n)
- Subproblems are not equal size
- Examples: T(n) = T(n-1) + O(n), T(n) = T(√n) + O(1)

---

# Amortized Analysis

## Definition

Amortized analysis calculates the **average** time per operation over a sequence of operations, even if some individual operations are expensive.

## Three Methods

### 1. Aggregate Method

Calculate total cost of n operations and divide by n.

**Example: Stack with MultiPop**
```cpp
class Stack {
public:
    void push(int x) { /* O(1) */ }
    int pop() { /* O(1) */ }
    
    void multiPop(int k) {
        while (!empty() && k > 0) {
            pop();
            k--;
        }
    }
};
```

**Analysis:**
- n push operations: O(n)
- Each element can only be popped once
- Total pops ≤ n
- Total cost: O(2n) = O(n)
- **Amortized cost per operation: O(n)/n = O(1)**

### 2. Accounting Method

Assign different costs to operations such that:
- Amortized cost ≥ Actual cost
- Sum of (Amortized - Actual) ≥ 0 always

**Example: Dynamic Array**
```
Operation: Insert
Actual cost: 1 (if space), n (if resize)
Amortized cost: 3 per insert

Credit system:
- Each insert pays 3 units
- 1 unit for actual insert
- 2 units saved for future resize
```

When resize happens:
- Need to copy n elements (cost n)
- We've saved 2n units (from n previous inserts)
- Sufficient to pay for resize!

**Amortized cost: O(1) per insert**

### 3. Potential Method

Define a potential function Φ that measures "stored work".

```
Amortized cost = Actual cost + ΔΦ
```

**Example: Binary Counter**
```cpp
void increment(int bits[], int n) {
    int i = 0;
    while (i < n && bits[i] == 1) {
        bits[i] = 0;  // Flip 1 to 0
        i++;
    }
    if (i < n) bits[i] = 1;  // Flip 0 to 1
}
```

**Analysis:**
- Potential: Φ = number of 1's in counter
- Increment flips k 1's to 0 and one 0 to 1
- Actual cost: k + 1
- Change in potential: ΔΦ = -k + 1
- Amortized cost: (k + 1) + (-k + 1) = 2

**Amortized cost: O(1) per increment**

## Common Applications

### Dynamic Array Resizing
```
Amortized O(1) insert despite occasional O(n) resize
```

### Union-Find with Path Compression
```
Amortized O(α(n)) per operation (α is inverse Ackermann)
```

### Splay Trees
```
Amortized O(log n) per operation despite O(n) worst case
```

---

# Practice Problems

## Beginner Level

### Problem 1: Array Sum
```cpp
int sum(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}
```
**Question:** What is the time and space complexity?

<details>
<summary>Answer</summary>

**Time Complexity: O(n)**
- Single loop through n elements
- Each operation is O(1)

**Space Complexity: O(1)**
- Only using constant extra space (total, i)
</details>

### Problem 2: Find Duplicates
```cpp
bool hasDuplicates(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) return true;
        }
    }
    return false;
}
```
**Question:** What is the complexity? How can you optimize?

<details>
<summary>Answer</summary>

**Time Complexity: O(n²)**
- Nested loops: outer O(n), inner O(n)

**Space Complexity: O(1)**

**Optimization:** Use hash set
```cpp
bool hasDuplicates(int arr[], int n) {
    unordered_set<int> seen;
    for (int i = 0; i < n; i++) {
        if (seen.count(arr[i])) return true;
        seen.insert(arr[i]);
    }
    return false;
}
// Time: O(n), Space: O(n)
```
</details>

### Problem 3: String Reversal
```cpp
string reverse(string s) {
    string result = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }
    return result;
}
```
**Question:** What is the complexity?

<details>
<summary>Answer</summary>

**Time Complexity: O(n²)**
- Loop: O(n)
- String concatenation creates new string each time: O(n)
- Total: O(n × n) = O(n²)

**Space Complexity: O(n)**
- Result string

**Better approach:** Use two pointers, swap in place for O(n) time, O(1) space
</details>

## Intermediate Level

### Problem 4: Merge K Sorted Arrays
```cpp
vector<int> mergeKArrays(vector<vector<int>>& arrays) {
    vector<int> result;
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>,
                   greater<>> minHeap;
    
    // Add first element of each array
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], {i, 0}});
        }
    }
    
    while (!minHeap.empty()) {
        auto [val, pos] = minHeap.top();
        auto [arrayIdx, elemIdx] = pos;
        minHeap.pop();
        
        result.push_back(val);
        
        if (elemIdx + 1 < arrays[arrayIdx].size()) {
            minHeap.push({arrays[arrayIdx][elemIdx + 1], 
                         {arrayIdx, elemIdx + 1}});
        }
    }
    
    return result;
}
```
**Question:** Analyze the complexity where k = number of arrays, n = total elements.

<details>
<summary>Answer</summary>

**Time Complexity: O(n log k)**
- Process n total elements
- Each heap operation: O(log k) (heap size ≤ k)
- Total: n × O(log k) = O(n log k)

**Space Complexity: O(k)**
- Heap stores at most k elements
- Result array is O(n) but that's output, not auxiliary space
</details>

### Problem 5: Longest Palindromic Substring
```cpp
string longestPalindrome(string s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLen = 1, start = 0;
    
    // All single characters are palindromes
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // Check for length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }
    
    // Check for lengths > 2
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLen = len;
            }
        }
    }
    
    return s.substr(start, maxLen);
}
```
**Question:** What is the complexity?

<details>
<summary>Answer</summary>

**Time Complexity: O(n²)**
- Nested loops: outer O(n), inner O(n)
- Each cell computed once

**Space Complexity: O(n²)**
- 2D DP table

**Better approach:** Expand around center for O(n²) time, O(1) space
</details>

## Advanced Level

### Problem 6: Median of Two Sorted Arrays
```cpp
double findMedian(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedian(nums2, nums1);
    }
    
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    
    while (left <= right) {
        int partition1 = (left + right) / 2;
        int partition2 = (m + n + 1) / 2 - partition1;
        
        int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
        int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];
        
        int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
        int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];
        
        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            if ((m + n) % 2 == 0) {
                return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
            } else {
                return max(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            right = partition1 - 1;
        } else {
            left = partition1 + 1;
        }
    }
    
    return 0.0;
}
```
**Question:** Analyze the complexity.

<details>
<summary>Answer</summary>

**Time Complexity: O(log(min(m, n)))**
- Binary search on smaller array
- Each iteration: O(1) operations

**Space Complexity: O(1)**
- Only constant extra variables

This is optimal for this problem!
</details>

### Problem 7: Analyze This Complex Code
```cpp
void mysteryFunction(int n) {
    for (int i = 1; i < n; i *= 2) {           // Loop 1
        for (int j = 0; j < i; j++) {          // Loop 2
            for (int k = 0; k < n; k += 2) {   // Loop 3
                // O(1) operation
            }
        }
    }
}
```
**Question:** What is the time complexity?

<details>
<summary>Answer</summary>

**Analysis:**
- Loop 1: i = 1, 2, 4, 8, ..., n → log n iterations
- Loop 2: runs i times for each iteration of Loop 1
- Loop 3: runs n/2 times

**Detailed calculation:**
```
Iteration 1 (i=1): 1 × (n/2) = n/2
Iteration 2 (i=2): 2 × (n/2) = n
Iteration 3 (i=4): 4 × (n/2) = 2n
...
Iteration k (i=2^k): 2^k × (n/2) = 2^(k-1) × n

Total = n/2 + n + 2n + 4n + ... + 2^(log n - 1) × n
      = n × (1/2 + 1 + 2 + 4 + ... + n/2)
      = n × (n - 1)
      = O(n²)
```

**Time Complexity: O(n²)**
</details>

## Challenge Problems

### Problem 8: Skyline Problem
Given buildings with [left, right, height], find the skyline.

**Question:** What complexity can you achieve?

<details>
<summary>Answer</summary>

**Optimal Solution:**
- Use sweep line algorithm with priority queue
- **Time Complexity: O(n log n)**
  - Sort events: O(n log n)
  - Process events with multiset: O(n log n)
- **Space Complexity: O(n)**
  - Store events and active heights
</details>

### Problem 9: Design Twitter
Implement:
- postTweet(userId, tweetId)
- getNewsFeed(userId) - 10 most recent tweets
- follow(followerId, followeeId)
- unfollow(followerId, followeeId)

**Question:** Design with optimal complexity.

<details>
<summary>Answer</summary>

**Design:**
```
- User → List of tweets: O(1) post
- User → Set of followees: O(1) follow/unfollow
- getNewsFeed: Merge k sorted lists (k = followees)
```

**Complexity:**
- postTweet: O(1)
- follow/unfollow: O(1)
- getNewsFeed: O(k log k) where k = number of followees
  - Use min-heap to merge k sorted tweet lists
  - Get 10 tweets: O(10 log k) = O(log k)

**Space:**
- O(U + T + F) where U = users, T = tweets, F = follow relationships
</details>

---

## Tips for Solving Complexity Problems

1. **Identify loops:** Each loop usually multiplies complexity
2. **Look for recursion:** Draw recursion tree
3. **Check data structures:** Hash tables O(1), BST O(log n)
4. **Consider best/average/worst:** Sometimes they differ significantly
5. **Think about optimization:** Can you use better data structures or algorithms?
6. **Practice patterns:** Many problems follow similar patterns

## Common Mistakes to Avoid

1. **Forgetting base cases** in recursion
2. **Counting nested loops incorrectly** when they have dependencies
3. **Assuming hash table is always O(1)** - worst case is O(n)
4. **Ignoring hidden complexity** in library functions
5. **Confusing O(n²) with O(n log n)** - huge difference!
6. **Not considering space complexity** - time isn't everything

---

# Summary

## Complexity Hierarchy (from best to worst)
```
O(1) < O(log n) < O(√n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)
```

## Key Takeaways

1. **Big O measures scalability**, not absolute speed
2. **Drop constants and lower-order terms** in Big O analysis
3. **Different inputs need different variables** (e.g., O(a + b), not O(n))
4. **Recursion depth = space complexity** (call stack)
5. **Amortized analysis** averages expensive operations over time
6. **Master Theorem** is a shortcut for divide-and-conquer recurrences
7. **Know your data structures** - choosing the right one changes everything
8. **Practice, practice, practice** - complexity analysis is a skill

## Quick Reference Card

**When you see:**
- Single loop → O(n)
- Nested loops → Multiply complexities
- Halving input → O(log n)
- Recursion → Draw tree, apply Master Theorem
- Hash map lookup → O(1) average
- Sorting → O(n log n) minimum for comparison-based

**Red flags:**
- Nested loops with same variable → Often O(n²)
- Recursive calls without memoization → Could be exponential
- Creating new collections in loop → Hidden complexity
- String concatenation in loop → O(n²) instead of O(n)

---

**End of Guide**

For more practice:
- LeetCode Easy/Medium problems
- Cracking the Coding Interview
- Introduction to Algorithms (CLRS)
- Algorithm Design Manual (Skiena)

Good luck with your complexity analysis journey!
