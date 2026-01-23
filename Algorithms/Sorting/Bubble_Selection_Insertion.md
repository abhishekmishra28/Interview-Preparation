# Basic Sorting Algorithms - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Bubble Sort](#bubble-sort)
  - [Intuition](#bubble-sort-intuition)
  - [Algorithm Steps](#bubble-sort-steps)
  - [Implementation](#bubble-sort-implementation)
  - [Complexity](#bubble-sort-complexity)
- [Selection Sort](#selection-sort)
  - [Intuition](#selection-sort-intuition)
  - [Algorithm Steps](#selection-sort-steps)
  - [Implementation](#selection-sort-implementation)
  - [Complexity](#selection-sort-complexity)
- [Insertion Sort](#insertion-sort)
  - [Intuition](#insertion-sort-intuition)
  - [Algorithm Steps](#insertion-sort-steps)
  - [Implementation](#insertion-sort-implementation)
  - [Complexity](#insertion-sort-complexity)
- [Comparison](#comparison)
- [Complete C++ Program](#complete-cpp-program)
- [Practice Problems](#practice-problems)

---

# Bubble Sort

## Bubble Sort Intuition

Bubble Sort works by repeatedly stepping through the list, comparing adjacent elements and swapping them if they are in the wrong order. The algorithm gets its name because smaller elements "bubble" to the top while larger elements sink to the bottom.

**Key Idea:** In each pass, the largest unsorted element moves to its correct position at the end.

### Visual Example
```
Initial: [5, 3, 8, 4, 2]

Pass 1: [3, 5, 4, 2, 8] → 8 bubbled to end
Pass 2: [3, 4, 2, 5, 8] → 5 in position
Pass 3: [3, 2, 4, 5, 8] → 4 in position
Pass 4: [2, 3, 4, 5, 8] → Sorted!
```

## Bubble Sort Steps

1. Start from the first element
2. Compare adjacent elements
3. Swap if left > right
4. Move to next pair
5. Repeat until end of array (one pass complete)
6. Repeat n-1 passes
7. Optimize by reducing range (last elements are sorted)

## Bubble Sort Implementation

### Standard Version
```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

### Optimized Version (Early Termination)
```cpp
void bubbleSortOptimized(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no swaps occurred, array is sorted
        if (!swapped)
            break;
    }
}
```

### Recursive Version
```cpp
void bubbleSortRecursive(vector<int>& arr, int n) {
    // Base case
    if (n == 1)
        return;
    
    // One pass - bubble largest to end
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }
    
    // Recur for remaining elements
    bubbleSortRecursive(arr, n - 1);
}
```

## Bubble Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best** | O(n) | Already sorted (with optimization) |
| **Average** | O(n²) | Random order |
| **Worst** | O(n²) | Reverse sorted |
| **Space** | O(1) | In-place sorting |

**Stability:** ✅ Stable (maintains relative order of equal elements)

---

# Selection Sort

## Selection Sort Intuition

Selection Sort works by repeatedly finding the minimum element from the unsorted portion and placing it at the beginning. It divides the array into sorted and unsorted regions.

**Key Idea:** In each pass, find the minimum element and swap it to its correct position.

### Visual Example
```
Initial: [64, 25, 12, 22, 11]

Pass 1: [11, 25, 12, 22, 64] → Found min (11), swapped with first
Pass 2: [11, 12, 25, 22, 64] → Found min (12), swapped with second
Pass 3: [11, 12, 22, 25, 64] → Found min (22), swapped with third
Pass 4: [11, 12, 22, 25, 64] → Found min (25), already in place
Result: [11, 12, 22, 25, 64] → Sorted!
```

## Selection Sort Steps

1. Set current position to start of array
2. Find minimum element in unsorted portion
3. Swap minimum with current position
4. Move current position one step forward
5. Repeat until array is sorted
6. After n-1 passes, array is sorted

## Selection Sort Implementation

### Standard Version
```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        // Find minimum element in unsorted portion
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap minimum with current position
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}
```

### Finding Maximum (Descending Order)
```cpp
void selectionSortDescending(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        
        if (maxIndex != i) {
            swap(arr[i], arr[maxIndex]);
        }
    }
}
```

### Recursive Version
```cpp
void selectionSortRecursive(vector<int>& arr, int start, int n) {
    // Base case
    if (start >= n - 1)
        return;
    
    // Find minimum in remaining array
    int minIndex = start;
    for (int i = start + 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    
    // Swap with current position
    swap(arr[start], arr[minIndex]);
    
    // Recur for remaining elements
    selectionSortRecursive(arr, start + 1, n);
}
```

## Selection Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best** | O(n²) | Always scans entire unsorted portion |
| **Average** | O(n²) | Random order |
| **Worst** | O(n²) | Any order |
| **Space** | O(1) | In-place sorting |

**Stability:** ❌ Unstable (can change relative order of equal elements)

**Key Advantage:** Minimizes number of swaps - makes exactly n-1 swaps

---

# Insertion Sort

## Insertion Sort Intuition

Insertion Sort works like sorting playing cards in your hands. You pick each card and insert it into its correct position among the already sorted cards.

**Key Idea:** Build the sorted array one element at a time by inserting each element into its correct position.

### Visual Example
```
Initial: [12, 11, 13, 5, 6]

Pass 1: [12, 11, 13, 5, 6] → 12 already sorted
Pass 2: [11, 12, 13, 5, 6] → Insert 11 before 12
Pass 3: [11, 12, 13, 5, 6] → 13 already in place
Pass 4: [5, 11, 12, 13, 6] → Insert 5 at beginning
Pass 5: [5, 6, 11, 12, 13] → Insert 6 after 5
Result: [5, 6, 11, 12, 13] → Sorted!
```

## Insertion Sort Steps

1. Start with second element (first is considered sorted)
2. Store current element as key
3. Compare key with elements in sorted portion (moving backwards)
4. Shift larger elements one position to the right
5. Insert key at correct position
6. Repeat for all elements
7. Array is sorted after n-1 passes

## Insertion Sort Implementation

### Standard Version
```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert key at correct position
        arr[j + 1] = key;
    }
}
```

### Optimized with Binary Search
```cpp
void insertionSortBinary(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        
        // Find position using binary search
        int pos = upper_bound(arr.begin(), arr.begin() + i, key) - arr.begin();
        
        // Shift elements
        for (int j = i; j > pos; j--) {
            arr[j] = arr[j - 1];
        }
        
        // Insert key
        arr[pos] = key;
    }
}
```

### Recursive Version
```cpp
void insertionSortRecursive(vector<int>& arr, int n) {
    // Base case
    if (n <= 1)
        return;
    
    // Sort first n-1 elements
    insertionSortRecursive(arr, n - 1);
    
    // Insert last element at correct position
    int key = arr[n - 1];
    int j = n - 2;
    
    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = key;
}
```

### Descending Order
```cpp
void insertionSortDescending(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements smaller than key
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}
```

## Insertion Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best** | O(n) | Already sorted (no shifts needed) |
| **Average** | O(n²) | Random order |
| **Worst** | O(n²) | Reverse sorted |
| **Space** | O(1) | In-place sorting |

**Stability:** ✅ Stable (maintains relative order of equal elements)

**Key Advantage:** Very efficient for small datasets and nearly sorted data

---

# Comparison

## Quick Comparison Table

| Feature | Bubble Sort | Selection Sort | Insertion Sort |
|---------|-------------|----------------|----------------|
| **Best Case** | O(n) | O(n²) | O(n) |
| **Average Case** | O(n²) | O(n²) | O(n²) |
| **Worst Case** | O(n²) | O(n²) | O(n²) |
| **Space** | O(1) | O(1) | O(1) |
| **Stable** | ✅ Yes | ❌ No | ✅ Yes |
| **Adaptive** | ✅ Yes (optimized) | ❌ No | ✅ Yes |
| **Swaps** | O(n²) | O(n) | O(n²) |
| **Comparisons** | O(n²) | O(n²) | O(n²) |
| **Online** | ❌ No | ❌ No | ✅ Yes |

## When to Use Each Algorithm

### Bubble Sort
- **Use when:** Learning purposes, very small datasets (< 10 elements), nearly sorted data
- **Avoid when:** Large datasets, performance is critical
- **Best for:** Educational purposes, detecting if array is sorted

### Selection Sort
- **Use when:** Memory writes are costly (minimizes swaps), small datasets
- **Avoid when:** Stability is required, large datasets
- **Best for:** Situations where swap cost is high (e.g., large objects)

### Insertion Sort
- **Use when:** Small datasets, nearly sorted data, online sorting (new elements arrive)
- **Avoid when:** Large completely random datasets
- **Best for:** Small arrays, nearly sorted data, adaptive sorting

## Performance on Different Data

| Data Type | Bubble Sort | Selection Sort | Insertion Sort |
|-----------|-------------|----------------|----------------|
| **Random** | Poor | Poor | Poor |
| **Nearly Sorted** | Good* | Poor | Excellent |
| **Reverse Sorted** | Worst | Poor | Worst |
| **Few Unique** | Poor | Poor | Good |
| **Small (< 20)** | Acceptable | Acceptable | Best |

*with optimization

---

# Complete C++ Program

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ==================== BUBBLE SORT ====================

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortOptimized(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped)
            break;
    }
}

// ==================== SELECTION SORT ====================

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ==================== INSERTION SORT ====================

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

// ==================== UTILITY FUNCTIONS ====================

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

vector<int> copyVector(const vector<int>& original) {
    return vector<int>(original);
}

// ==================== MAIN FUNCTION ====================

int main() {
    vector<int> original = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original array: ";
    printArray(original);
    cout << "\n";
    
    // Test Bubble Sort
    vector<int> arr1 = copyVector(original);
    bubbleSortOptimized(arr1);
    cout << "After Bubble Sort: ";
    printArray(arr1);
    
    // Test Selection Sort
    vector<int> arr2 = copyVector(original);
    selectionSort(arr2);
    cout << "After Selection Sort: ";
    printArray(arr2);
    
    // Test Insertion Sort
    vector<int> arr3 = copyVector(original);
    insertionSort(arr3);
    cout << "After Insertion Sort: ";
    printArray(arr3);
    
    cout << "\n=== Testing with Nearly Sorted Array ===\n";
    vector<int> nearlySorted = {1, 2, 3, 5, 4, 6, 7};
    cout << "Original: ";
    printArray(nearlySorted);
    
    vector<int> arr4 = copyVector(nearlySorted);
    insertionSort(arr4);
    cout << "Insertion Sort (Best for nearly sorted): ";
    printArray(arr4);
    
    return 0;
}
```

### Sample Output
```
Original array: 64 34 25 12 22 11 90 

After Bubble Sort: 11 12 22 25 34 64 90 
After Selection Sort: 11 12 22 25 34 64 90 
After Insertion Sort: 11 12 22 25 34 64 90 

=== Testing with Nearly Sorted Array ===
Original: 1 2 3 5 4 6 7 
Insertion Sort (Best for nearly sorted): 1 2 3 4 5 6 7 
```

---

# Practice Problems

## Easy Level
1. Sort an array in ascending/descending order
2. Count number of swaps in each algorithm
3. Find if array is already sorted
4. Sort array of strings
5. Implement sorting for linked list

## Medium Level
6. **K Closest Elements** - Find k elements closest to target
7. **Sort Colors (Dutch Flag)** - Sort array with 0s, 1s, 2s
8. **Minimum Swaps to Sort** - Count minimum swaps needed
9. **Relative Sorting** - Sort based on another array
10. **Sort by Frequency** - Sort elements by their frequency

## Hard Level
11. **Count Inversions** - Count pairs where i < j but arr[i] > arr[j]
12. **Pancake Sorting** - Sort using only flip operation
13. **Wiggle Sort** - arr[0] <= arr[1] >= arr[2] <= arr[3]...
14. **Sort Nearly Sorted Array** - Each element is at most k positions away

## LeetCode Problems
- [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/)
- [75. Sort Colors](https://leetcode.com/problems/sort-colors/)
- [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)
- [147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)
- [insertion-sort-list](https://leetcode.com/problems/insertion-sort-list/)

---

## Key Takeaways

1. **All three are O(n²) algorithms** - suitable only for small datasets or educational purposes
2. **Insertion Sort** is generally the best among the three for practical use
3. **Selection Sort** minimizes swaps but is not stable
4. **Bubble Sort** is mainly for teaching, rarely used in practice
5. For production code, use **QuickSort, MergeSort, or built-in sort functions**

---

**Happy Coding! 🚀**
