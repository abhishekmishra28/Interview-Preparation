# Merge Sort & Quick Sort - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Merge Sort](#merge-sort)
  - [Intuition](#merge-sort-intuition)
  - [Algorithm Steps](#merge-sort-steps)
  - [Implementation](#merge-sort-implementation)
  - [Complexity](#merge-sort-complexity)
- [Quick Sort](#quick-sort)
  - [Intuition](#quick-sort-intuition)
  - [Algorithm Steps](#quick-sort-steps)
  - [Implementation](#quick-sort-implementation)
  - [Complexity](#quick-sort-complexity)
- [Comparison](#comparison)
- [Complete C++ Program](#complete-cpp-program)
- [Practice Problems](#practice-problems)

---

# Merge Sort

## Merge Sort Intuition

Merge Sort is a **Divide and Conquer** algorithm that divides the array into two halves, recursively sorts them, and then merges the sorted halves.

**Key Idea:** "Divide the problem into smaller subproblems, solve them, and combine the results."

Think of it like sorting a deck of cards:
1. Split the deck into two piles
2. Recursively split each pile until you have single cards
3. Merge pairs of cards in sorted order
4. Keep merging until you have one sorted deck

### Visual Example
```
Initial Array: [38, 27, 43, 3, 9, 82, 10]

         [38, 27, 43, 3, 9, 82, 10]
                    /  \
        [38, 27, 43, 3]  [9, 82, 10]
           /    \            /    \
      [38, 27] [43, 3]   [9, 82]  [10]
       /   \    /   \     /   \      |
     [38] [27] [43] [3]  [9] [82]  [10]
       \   /    \   /     \   /      |
      [27, 38] [3, 43]   [9, 82]  [10]
           \    /            \    /
        [3, 27, 38, 43]    [9, 10, 82]
                    \      /
          [3, 9, 10, 27, 38, 43, 82]
```

## Merge Sort Steps

### Divide Phase:
1. Find the middle point to divide array into two halves
2. Recursively divide left half
3. Recursively divide right half
4. Continue until subarrays have single element

### Conquer Phase (Merge):
1. Create temporary arrays for left and right halves
2. Compare elements from both halves
3. Place smaller element in original array
4. Continue until all elements are merged
5. Copy remaining elements (if any)

## Merge Sort Implementation

### Standard Implementation
```cpp
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    vector<int> L(n1), R(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Helper function to call merge sort
void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}
```

### Optimized Version (In-place for small arrays)
```cpp
void mergeSortOptimized(vector<int>& arr, int left, int right) {
    // Use insertion sort for small subarrays
    if (right - left <= 10) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortOptimized(arr, left, mid);
        mergeSortOptimized(arr, mid + 1, right);
        
        // Skip merge if already sorted
        if (arr[mid] <= arr[mid + 1])
            return;
            
        merge(arr, left, mid, right);
    }
}
```

### Iterative Merge Sort
```cpp
void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    
    // Start with merge subarrays of size 1, then 2, 4, 8...
    for (int currSize = 1; currSize < n; currSize *= 2) {
        // Pick starting index of left sub array
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}
```

### Counting Inversions using Merge Sort
```cpp
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    long long invCount = 0;
    
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            invCount += (L.size() - i); // Count inversions
        }
    }
    
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
    
    return invCount;
}

long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }
    return invCount;
}
```

## Merge Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best** | O(n log n) | Already sorted |
| **Average** | O(n log n) | Random order |
| **Worst** | O(n log n) | Reverse sorted |
| **Space** | O(n) | Requires auxiliary array |

**Recurrence Relation:** T(n) = 2T(n/2) + O(n)

**Why O(n log n)?**
- Height of recursion tree: log n
- Work at each level: O(n) for merging
- Total: O(n) × O(log n) = O(n log n)

### Characteristics
- **Stable:** ✅ Yes (maintains relative order)
- **Adaptive:** ❌ No (always O(n log n))
- **Online:** ❌ No
- **In-place:** ❌ No (needs O(n) space)

---

# Quick Sort

## Quick Sort Intuition

Quick Sort is a **Divide and Conquer** algorithm that picks a pivot element and partitions the array around it, placing smaller elements to the left and larger elements to the right.

**Key Idea:** "Pick a pivot, partition around it, and recursively sort the partitions."

Think of organizing a library:
1. Pick a book as reference (pivot)
2. Put all books that come before it on the left
3. Put all books that come after it on the right
4. Repeat for left and right sections

### Visual Example
```
Initial Array: [10, 7, 8, 9, 1, 5]
Pivot = 5 (last element)

Partitioning:
[1, 5, 8, 9, 10, 7]  → 5 in correct position
 L   P      R

Left: [1]  Right: [8, 9, 10, 7]
  ✓          Pivot = 7

Right partition: [7, 9, 10, 8]
                  P

Final: [1, 5, 7, 8, 9, 10]
```

## Quick Sort Steps

### Partition Phase:
1. Choose a pivot element (last, first, middle, or random)
2. Rearrange array: elements < pivot on left, > pivot on right
3. Place pivot in its correct position
4. Return pivot index

### Recursive Phase:
1. Recursively sort left partition (elements < pivot)
2. Recursively sort right partition (elements > pivot)
3. Base case: array of size 0 or 1

## Quick Sort Implementation

### Standard Implementation (Last Element as Pivot)
```cpp
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Choose last element as pivot
    int i = low - 1;        // Index of smaller element
    
    for (int j = low; j < high; j++) {
        // If current element is smaller than pivot
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Place pivot in correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper function
void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}
```

### Randomized Quick Sort
```cpp
int randomPartition(vector<int>& arr, int low, int high) {
    // Generate random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    
    // Swap random element with last element
    swap(arr[randomIndex], arr[high]);
    
    return partition(arr, low, high);
}

void quickSortRandomized(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}
```

### Three-Way Quick Sort (for duplicate elements)
```cpp
void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;
    
    int lt = low;           // Elements < pivot
    int gt = high;          // Elements > pivot
    int i = low;
    int pivot = arr[low];
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    
    // Now arr[low..lt-1] < pivot = arr[lt..gt] < arr[gt+1..high]
    quickSort3Way(arr, low, lt - 1);
    quickSort3Way(arr, gt + 1, high);
}
```

### Hoare's Partition Scheme
```cpp
int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    
    while (true) {
        // Find element >= pivot from left
        do {
            i++;
        } while (arr[i] < pivot);
        
        // Find element <= pivot from right
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j)
            return j;
        
        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);
        
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}
```

### Iterative Quick Sort
```cpp
void quickSortIterative(vector<int>& arr, int low, int high) {
    // Create auxiliary stack
    vector<int> stack(high - low + 1);
    int top = -1;
    
    // Push initial values
    stack[++top] = low;
    stack[++top] = high;
    
    while (top >= 0) {
        // Pop high and low
        high = stack[top--];
        low = stack[top--];
        
        // Set pivot element at correct position
        int pi = partition(arr, low, high);
        
        // If elements on left of pivot, push to stack
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
        
        // If elements on right of pivot, push to stack
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}
```

### Optimized Quick Sort (Hybrid with Insertion Sort)
```cpp
void quickSortOptimized(vector<int>& arr, int low, int high) {
    // Use insertion sort for small subarrays
    if (high - low <= 10) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        
        quickSortOptimized(arr, low, pi - 1);
        quickSortOptimized(arr, pi + 1, high);
    }
}
```

## Quick Sort Complexity

| Case | Time Complexity | Description |
|------|----------------|-------------|
| **Best** | O(n log n) | Pivot divides array evenly |
| **Average** | O(n log n) | Random pivot selection |
| **Worst** | O(n²) | Pivot is always smallest/largest |
| **Space** | O(log n) | Recursion stack space |

**Recurrence Relations:**
- Best/Average: T(n) = 2T(n/2) + O(n)
- Worst: T(n) = T(n-1) + O(n)

**Why O(n log n) average?**
- Average recursion depth: log n
- Partitioning at each level: O(n)
- Total: O(n log n)

**When does O(n²) occur?**
- Already sorted array (with naive pivot)
- Reverse sorted array
- All elements are same

### Characteristics
- **Stable:** ❌ No (relative order may change)
- **Adaptive:** ❌ No
- **Online:** ❌ No
- **In-place:** ✅ Yes (O(log n) stack space)

---

# Comparison

## Merge Sort vs Quick Sort

| Feature | Merge Sort | Quick Sort |
|---------|------------|------------|
| **Best Case** | O(n log n) | O(n log n) |
| **Average Case** | O(n log n) | O(n log n) |
| **Worst Case** | O(n log n) | O(n²) |
| **Space Complexity** | O(n) | O(log n) |
| **Stable** | ✅ Yes | ❌ No |
| **In-place** | ❌ No | ✅ Yes |
| **Cache Performance** | Poor | Good |
| **Parallelization** | Easy | Moderate |
| **Practical Performance** | Slower | Faster |
| **Worst Case Guarantee** | ✅ Yes | ❌ No |

## Detailed Comparison

### When to Use Merge Sort
✅ **Need guaranteed O(n log n)** performance  
✅ **Stability is required**  
✅ **Sorting linked lists** (no random access needed)  
✅ **External sorting** (large datasets on disk)  
✅ **Parallel processing** (easy to parallelize)  
❌ Space is limited  
❌ Need fastest practical performance  

### When to Use Quick Sort
✅ **Average case performance** is critical  
✅ **Space is limited** (in-place sorting)  
✅ **Cache performance** matters  
✅ **Arrays** (random access available)  
✅ **General-purpose sorting** (most languages use it)  
❌ Need stability  
❌ Worst-case guarantee required  
❌ Predictable performance needed  

## Performance Characteristics

### Merge Sort Advantages
1. Predictable O(n log n) performance
2. Stable sorting
3. Good for linked lists
4. External sorting capability
5. Easy to parallelize

### Quick Sort Advantages
1. Faster in practice (better cache performance)
2. In-place sorting (less memory)
3. Good locality of reference
4. Tail recursion optimization possible
5. Works well with virtual memory

### Merge Sort Disadvantages
1. Requires O(n) extra space
2. Slower in practice than Quick Sort
3. Not in-place
4. Poor cache performance

### Quick Sort Disadvantages
1. O(n²) worst case
2. Not stable
3. Vulnerable to adversarial input
4. Stack overflow risk (deep recursion)

---

# Complete C++ Program

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// ==================== MERGE SORT ====================

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// ==================== QUICK SORT ====================

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// ==================== RANDOMIZED QUICK SORT ====================

int randomPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

void quickSortRandomizedHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        
        quickSortRandomizedHelper(arr, low, pi - 1);
        quickSortRandomizedHelper(arr, pi + 1, high);
    }
}

void quickSortRandomized(vector<int>& arr) {
    srand(time(0));
    quickSortRandomizedHelper(arr, 0, arr.size() - 1);
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
    vector<int> original = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    
    cout << "Original array: ";
    printArray(original);
    cout << "\n";
    
    // Test Merge Sort
    vector<int> arr1 = copyVector(original);
    mergeSort(arr1);
    cout << "After Merge Sort: ";
    printArray(arr1);
    
    // Test Quick Sort
    vector<int> arr2 = copyVector(original);
    quickSort(arr2);
    cout << "After Quick Sort: ";
    printArray(arr2);
    
    // Test Randomized Quick Sort
    vector<int> arr3 = copyVector(original);
    quickSortRandomized(arr3);
    cout << "After Randomized Quick Sort: ";
    printArray(arr3);
    
    cout << "\n=== Testing with Worst Case for Quick Sort ===\n";
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Sorted array (worst for naive Quick Sort): ";
    printArray(sorted);
    
    vector<int> arr4 = copyVector(sorted);
    quickSortRandomized(arr4);
    cout << "After Randomized Quick Sort: ";
    printArray(arr4);
    
    cout << "\n=== Testing with Duplicates ===\n";
    vector<int> duplicates = {5, 2, 8, 2, 9, 1, 5, 5};
    cout << "Array with duplicates: ";
    printArray(duplicates);
    
    vector<int> arr5 = copyVector(duplicates);
    mergeSort(arr5);
    cout << "After Merge Sort (Stable): ";
    printArray(arr5);
    
    return 0;
}
```

### Sample Output
```
Original array: 64 34 25 12 22 11 90 88 45 50 

After Merge Sort: 11 12 22 25 34 45 50 64 88 90 
After Quick Sort: 11 12 22 25 34 45 50 64 88 90 
After Randomized Quick Sort: 11 12 22 25 34 45 50 64 88 90 

=== Testing with Worst Case for Quick Sort ===
Sorted array (worst for naive Quick Sort): 1 2 3 4 5 6 7 8 9 10 
After Randomized Quick Sort: 1 2 3 4 5 6 7 8 9 10 

=== Testing with Duplicates ===
Array with duplicates: 5 2 8 2 9 1 5 5 
After Merge Sort (Stable): 1 2 2 5 5 5 8 9 
```

---

# Practice Problems

## Easy Level
1. Implement merge sort for linked list
2. Sort array using merge sort (descending order)
3. Count inversions in array using merge sort
4. Find kth smallest element using quick sort
5. Check if merge sort is stable

## Medium Level
6. **Merge K Sorted Arrays** - Merge multiple sorted arrays
7. **Quick Select** - Find kth largest element in O(n) average
8. **Sort Colors** - Three-way partitioning (Dutch National Flag)
9. **Count Smaller After Self** - Count elements smaller to the right
10. **Sort List** - Sort linked list using merge sort

## Hard Level
11. **Merge Intervals** - Merge overlapping intervals
12. **Maximum Gap** - Find maximum difference in sorted array
13. **Reverse Pairs** - Count reverse pairs using merge sort
14. **Count Range Sum** - Count range sums using merge sort
15. **Quick Sort with Duplicate Keys** - Three-way partitioning

## LeetCode Problems
- [148. Sort List](https://leetcode.com/problems/sort-list/) - Merge Sort
- [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)
- [215. Kth Largest Element](https://leetcode.com/problems/kth-largest-element-in-an-array/) - Quick Select
- [75. Sort Colors](https://leetcode.com/problems/sort-colors/) - Three-way partition
- [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) - Merge Sort
- [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
- [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)

---

## Key Takeaways

### Merge Sort
1. **Always O(n log n)** - guaranteed performance
2. **Stable** - preserves relative order
3. **Not in-place** - requires O(n) extra space
4. **Best for:** Linked lists, external sorting, when stability matters

### Quick Sort
1. **Average O(n log n)** - faster in practice
2. **In-place** - O(log n) stack space
3. **Randomization helps** - avoids worst case
4. **Best for:** Arrays, general-purpose sorting, when space is limited

### General Guidelines
- **Use Merge Sort** when you need guaranteed performance or stability
- **Use Quick Sort** for general-purpose sorting (faster in practice)
- **Use Randomized Quick Sort** to avoid worst-case scenarios
- **Use 3-way Quick Sort** when many duplicate elements exist
- **Hybrid approaches** (Quick + Insertion for small arrays) work best

---

**Happy Sorting! 🚀**
