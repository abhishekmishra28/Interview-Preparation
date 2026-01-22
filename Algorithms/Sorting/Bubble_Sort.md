# Bubble Sort Algorithm - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Intuition](#intuition)
- [How It Works](#how-it-works)
- [Algorithm Steps](#algorithm-steps)
- [Flowchart](#flowchart)
- [Implementation](#implementation)
- [Complexity Analysis](#complexity-analysis)
- [Optimization](#optimization)
- [Advantages and Disadvantages](#advantages-and-disadvantages)
- [When to Use Bubble Sort](#when-to-use-bubble-sort)
- [Practice Problems](#practice-problems)
- [Related Algorithms](#related-algorithms)

## Introduction

Bubble Sort is one of the simplest sorting algorithms that works by repeatedly stepping through the list, comparing adjacent elements and swapping them if they are in the wrong order. The algorithm gets its name because smaller elements "bubble" to the top of the list (beginning) while larger elements sink to the bottom (end), similar to how bubbles rise in water.

## Intuition

Imagine you have a deck of cards scattered on a table, and you want to arrange them in order. The bubble sort approach would be to:

1. Start from the beginning
2. Compare each pair of adjacent cards
3. If the left card is larger than the right card, swap them
4. Keep doing this until you reach the end
5. Repeat the entire process until no more swaps are needed

Think of it like this: in each complete pass through the array, the largest unsorted element "bubbles up" to its correct position at the end. After the first pass, the largest element is guaranteed to be in its final position. After the second pass, the second-largest element is in its final position, and so on.

## How It Works

Let's visualize bubble sort with an example array: `[5, 3, 8, 4, 2]`

### Pass 1:
- Compare 5 and 3 → Swap → `[3, 5, 8, 4, 2]`
- Compare 5 and 8 → No swap → `[3, 5, 8, 4, 2]`
- Compare 8 and 4 → Swap → `[3, 5, 4, 8, 2]`
- Compare 8 and 2 → Swap → `[3, 5, 4, 2, 8]` ✓ (8 is now in correct position)

### Pass 2:
- Compare 3 and 5 → No swap → `[3, 5, 4, 2, 8]`
- Compare 5 and 4 → Swap → `[3, 4, 5, 2, 8]`
- Compare 5 and 2 → Swap → `[3, 4, 2, 5, 8]` ✓ (5 is now in correct position)

### Pass 3:
- Compare 3 and 4 → No swap → `[3, 4, 2, 5, 8]`
- Compare 4 and 2 → Swap → `[3, 2, 4, 5, 8]` ✓ (4 is now in correct position)

### Pass 4:
- Compare 3 and 2 → Swap → `[2, 3, 4, 5, 8]` ✓ (All elements sorted)

## Algorithm Steps

1. **Start** with the first element of the array
2. **Compare** the current element with the next element
3. **Swap** them if the current element is greater than the next element
4. **Move** to the next pair of elements and repeat steps 2-3
5. **Continue** until you reach the end of the array (one pass complete)
6. **Repeat** passes 1-5 for (n-1) times, where n is the number of elements
7. **Optimize** by reducing the comparison range in each pass (last elements are already sorted)
8. **Stop** when no swaps occur in a complete pass (array is sorted)

## Flowchart

```
                    START
                      |
                      ↓
              Initialize i = 0
                      |
                      ↓
                Is i < n-1? ──No──→ END
                      |
                     Yes
                      ↓
              Initialize j = 0
                      |
                      ↓
           Is j < n-i-1? ──No──→ Increment i
                      |              ↓
                     Yes          Go back to
                      |          "Is i < n-1?"
                      ↓
         Is arr[j] > arr[j+1]?
                      |
              Yes ←──┴──→ No
               |              |
               ↓              |
    Swap arr[j] & arr[j+1]   |
               |              |
               └──────┬───────┘
                      ↓
                Increment j
                      ↓
              Go back to
           "Is j < n-i-1?"
```

## Implementation

### C++ (Standard Version)

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Standard bubble sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Optimized bubble sort
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
        
        // If no elements were swapped, break
        if (!swapped)
            break;
    }
}

// Print array
void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original array: ";
    printArray(arr);
    
    bubbleSortOptimized(arr);
    
    cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
```

### C++ (Recursive Version)

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Recursive bubble sort
void bubbleSortRecursive(vector<int>& arr, int n) {
    // Base case: if size is 1, array is sorted
    if (n == 1)
        return;
    
    // One pass of bubble sort
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }
    
    // Largest element is fixed, recur for remaining array
    bubbleSortRecursive(arr, n - 1);
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    int n = arr.size();
    
    cout << "Original array: ";
    printArray(arr);
    
    bubbleSortRecursive(arr, n);
    
    cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
```

## Complexity Analysis

### Time Complexity

| Case | Complexity | Description |
|------|------------|-------------|
| **Best Case** | O(n) | When the array is already sorted (optimized version with flag) |
| **Average Case** | O(n²) | When elements are in random order |
| **Worst Case** | O(n²) | When the array is sorted in reverse order |

**Detailed Analysis:**
- In the worst case, we make (n-1) comparisons in the first pass, (n-2) in the second pass, and so on
- Total comparisons = (n-1) + (n-2) + (n-3) + ... + 1 = n(n-1)/2 = O(n²)
- Number of swaps in worst case is also O(n²)

### Space Complexity

- **Space Complexity:** O(1)
- Bubble sort is an in-place sorting algorithm, requiring only a constant amount of extra space for temporary variables (for swapping)

### Stability

- **Stable:** Yes
- Bubble sort maintains the relative order of equal elements, making it a stable sorting algorithm

## Optimization

The standard bubble sort can be optimized in two main ways:

### 1. Early Termination (Swap Flag)
If no swaps occur during a complete pass, the array is already sorted, and we can terminate early.

```python
def bubble_sort_with_flag(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr
```

### 2. Reduce Comparison Range
After each pass, the largest element is in its correct position, so we don't need to compare it again.

```python
# This is already implemented in our standard version
# by using range(0, n - i - 1)
```

### 3. Cocktail Sort (Bidirectional Bubble Sort)
An advanced optimization where the algorithm alternates between forward and backward passes.

```cpp
void cocktailSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    
    while (swapped) {
        swapped = false;
        
        // Forward pass
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        if (!swapped)
            break;
        
        swapped = false;
        end--;
        
        // Backward pass
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        start++;
    }
}
```

## Advantages and Disadvantages

### Advantages ✅

1. **Simple to understand and implement** - Great for learning sorting concepts
2. **No extra memory required** - In-place sorting (O(1) space)
3. **Stable sorting** - Maintains relative order of equal elements
4. **Adaptive** - Efficient for nearly sorted data (with optimization)
5. **Good for small datasets** - Overhead is minimal

### Disadvantages ❌

1. **Very slow for large datasets** - O(n²) time complexity
2. **Not practical for production** - Much slower than advanced algorithms like QuickSort or MergeSort
3. **Many unnecessary comparisons** - Even when the array is partially sorted
4. **Poor performance** - Compared to other O(n²) algorithms like Insertion Sort

## When to Use Bubble Sort

Bubble Sort is suitable when:

- **Learning purposes** - Understanding basic sorting algorithms
- **Small datasets** - When n is very small (< 10-20 elements)
- **Nearly sorted data** - With optimization, it performs well on almost-sorted arrays
- **Memory is critical** - When you cannot afford extra space
- **Simplicity is key** - When code readability is more important than performance
- **Stable sort required** - When you need to maintain the order of equal elements

**Do NOT use Bubble Sort when:**
- Working with large datasets (use QuickSort, MergeSort, or HeapSort)
- Performance is critical (prefer O(n log n) algorithms)
- Production systems (use built-in sorting functions)

## Practice Problems

### Easy
1. Sort an array of integers in ascending order
2. Sort an array in descending order
3. Count the number of swaps needed to sort an array
4. Find if an array is already sorted
5. Sort an array of strings alphabetically

### Medium
6. **Minimum Adjacent Swaps** - Find minimum number of adjacent swaps to sort array
7. **Bubble Sort with Custom Comparator** - Sort based on custom criteria
8. **K Closest Elements** - Find k elements closest to a target value
9. **Sort Colors (Dutch National Flag)** - Sort array with only 0s, 1s, and 2s
10. **Relative Sorting** - Sort array based on another array's order

### Hard
11. **Count Inversions** - Count pairs (i, j) where i < j but arr[i] > arr[j]
12. **Minimum Swaps to Sort** - Find minimum swaps (not necessarily adjacent)
13. **Maximum Gap** - Find maximum difference between successive elements in sorted form
14. **Wiggle Sort** - Rearrange array such that arr[0] <= arr[1] >= arr[2] <= arr[3]...

### LeetCode Problems
- [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/)
- [75. Sort Colors](https://leetcode.com/problems/sort-colors/)
- [912. Sort an Array](https://leetcode.com/problems/sort-an-array/) (try with bubble sort for learning)
- [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)

## Related Algorithms

### Similar Sorting Algorithms

1. **Selection Sort**
   - Also O(n²) but makes fewer swaps
   - Finds minimum element and places it at the beginning

2. **Insertion Sort**
   - O(n²) but faster in practice than Bubble Sort
   - Better for nearly sorted data
   - More efficient than Bubble Sort

3. **Cocktail Sort (Shaker Sort)**
   - Bidirectional bubble sort
   - Slightly better performance than standard bubble sort

### Better Alternatives

1. **Quick Sort** - O(n log n) average case
2. **Merge Sort** - O(n log n) guaranteed, stable
3. **Heap Sort** - O(n log n) in-place
4. **Tim Sort** - O(n log n), used in Python's built-in sort

### Comparison Table

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | No |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |

---

## References and Further Reading

- [Sorting Algorithms Visualized](https://www.toptal.com/developers/sorting-algorithms)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)
- [GeeksforGeeks - Bubble Sort](https://www.geeksforgeeks.org/bubble-sort/)
- [Wikipedia - Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort)

---

## Contributing

Feel free to contribute to this guide by:
- Adding more examples
- Improving explanations
- Adding visualizations
- Fixing errors
- Adding more practice problems

---

**Happy Sorting! 🚀**
