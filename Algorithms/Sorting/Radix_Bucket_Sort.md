# Bucket Sort & Radix Sort - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Bucket Sort](#bucket-sort)
  - [Intuition](#bucket-sort-intuition)
  - [Algorithm Steps](#bucket-sort-steps)
  - [Implementation](#bucket-sort-implementation)
  - [Complexity Analysis](#bucket-sort-complexity)
  - [When to Use](#bucket-sort-when-to-use)
- [Radix Sort](#radix-sort)
  - [Intuition](#radix-sort-intuition)
  - [Algorithm Steps](#radix-sort-steps)
  - [Implementation](#radix-sort-implementation)
  - [Complexity Analysis](#radix-sort-complexity)
  - [When to Use](#radix-sort-when-to-use)
- [Comparison](#comparison)
- [Complete C++ Program](#complete-cpp-program)
- [Practice Problems](#practice-problems)

---

# Introduction

**Bucket Sort** and **Radix Sort** are non-comparison based sorting algorithms that can achieve **linear time complexity** under certain conditions.

Unlike comparison-based sorts (Quick Sort, Merge Sort) which have a lower bound of O(n log n), these algorithms can sort in O(n) by making assumptions about the input data.

## Key Differences from Comparison Sorts

| Aspect | Comparison Sorts | Bucket/Radix Sort |
|--------|------------------|-------------------|
| **Method** | Compare elements | Distribute elements |
| **Lower Bound** | O(n log n) | O(n) possible |
| **Data Requirement** | Any comparable data | Specific distributions |
| **Adaptability** | General purpose | Domain-specific |

---

# Bucket Sort

## Bucket Sort Intuition

Imagine sorting a deck of playing cards:
1. Create 13 buckets (one for each rank: A, 2, 3, ..., K)
2. Distribute cards into buckets based on rank
3. Sort each bucket (if needed)
4. Concatenate all buckets

**Key Idea:** Divide the data range into buckets, distribute elements, sort each bucket, and combine.

### Visual Example

**Sorting: [0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]**

```
Range: [0.0, 1.0) divided into 10 buckets

Bucket 0 [0.0-0.1): 
Bucket 1 [0.1-0.2): [0.17, 0.12]
Bucket 2 [0.2-0.3): [0.26, 0.21, 0.23]
Bucket 3 [0.3-0.4): [0.39]
Bucket 4 [0.4-0.5): 
Bucket 5 [0.5-0.6): 
Bucket 6 [0.6-0.7): [0.68]
Bucket 7 [0.7-0.8): [0.78, 0.72]
Bucket 8 [0.8-0.9): 
Bucket 9 [0.9-1.0): [0.94]

After sorting each bucket:
Bucket 1: [0.12, 0.17]
Bucket 2: [0.21, 0.23, 0.26]
Bucket 3: [0.39]
Bucket 6: [0.68]
Bucket 7: [0.72, 0.78]
Bucket 9: [0.94]

Final Result: [0.12, 0.17, 0.21, 0.23, 0.26, 0.39, 0.68, 0.72, 0.78, 0.94]
```

## Bucket Sort Steps

### Algorithm:
1. **Find range:** Determine minimum and maximum values
2. **Create buckets:** Initialize empty buckets (usually n buckets)
3. **Distribute:** Place each element in appropriate bucket using formula:
   ```
   bucketIndex = (element - min) × numBuckets / (max - min + 1)
   ```
4. **Sort buckets:** Sort each bucket individually (using any sorting algorithm)
5. **Concatenate:** Combine all buckets in order

### Detailed Walkthrough

**Input:** [29, 25, 3, 49, 9, 37, 21, 43]

**Step 1: Find Range**
- min = 3, max = 49
- range = 49 - 3 = 46

**Step 2: Create Buckets** (let's use 5 buckets)
```
Bucket 0: []
Bucket 1: []
Bucket 2: []
Bucket 3: []
Bucket 4: []
```

**Step 3: Distribute Elements**
```
For 29: index = (29-3) × 5 / 47 ≈ 2 → Bucket 2
For 25: index = (25-3) × 5 / 47 ≈ 2 → Bucket 2
For 3:  index = (3-3) × 5 / 47 = 0  → Bucket 0
For 49: index = (49-3) × 5 / 47 ≈ 4 → Bucket 4
For 9:  index = (9-3) × 5 / 47 ≈ 0  → Bucket 0
For 37: index = (37-3) × 5 / 47 ≈ 3 → Bucket 3
For 21: index = (21-3) × 5 / 47 ≈ 1 → Bucket 1
For 43: index = (43-3) × 5 / 47 ≈ 4 → Bucket 4

Result:
Bucket 0: [3, 9]
Bucket 1: [21]
Bucket 2: [29, 25]
Bucket 3: [37]
Bucket 4: [49, 43]
```

**Step 4: Sort Each Bucket**
```
Bucket 0: [3, 9]
Bucket 1: [21]
Bucket 2: [25, 29]
Bucket 3: [37]
Bucket 4: [43, 49]
```

**Step 5: Concatenate**
```
Final: [3, 9, 21, 25, 29, 37, 43, 49]
```

## Bucket Sort Implementation

### Standard Implementation (for floating point numbers)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(float arr[], int n) {
    // 1. Create n empty buckets
    vector<float> buckets[n];
    
    // 2. Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i];  // For range [0, 1)
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // 3. Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // 4. Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    printArray(arr, n);
    
    bucketSort(arr, n);
    
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}
```

### Implementation for Integer Arrays

```cpp
void bucketSortIntegers(int arr[], int n) {
    if (n <= 0) return;
    
    // Find maximum and minimum values
    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; i++) {
        maxVal = max(maxVal, arr[i]);
        minVal = min(minVal, arr[i]);
    }
    
    // Calculate range and bucket size
    int range = maxVal - minVal + 1;
    int bucketCount = n;  // Number of buckets
    int bucketRange = (range + bucketCount - 1) / bucketCount;
    
    // Create buckets
    vector<int> buckets[bucketCount];
    
    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] - minVal) / bucketRange;
        if (bucketIndex >= bucketCount) 
            bucketIndex = bucketCount - 1;
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sort individual buckets
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate buckets
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}
```

### Optimized Version with Custom Bucket Sort

```cpp
// Insertion sort for small buckets
void insertionSort(vector<int>& bucket) {
    for (int i = 1; i < bucket.size(); i++) {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSortOptimized(int arr[], int n) {
    if (n <= 0) return;
    
    int maxVal = *max_element(arr, arr + n);
    int minVal = *min_element(arr, arr + n);
    int range = maxVal - minVal + 1;
    int bucketCount = n;
    
    vector<int> buckets[bucketCount];
    
    // Distribute
    for (int i = 0; i < n; i++) {
        int idx = (bucketCount * (arr[i] - minVal)) / range;
        if (idx >= bucketCount) idx = bucketCount - 1;
        buckets[idx].push_back(arr[i]);
    }
    
    // Sort each bucket using insertion sort (better for small sizes)
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i]);
    }
    
    // Concatenate
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int val : buckets[i]) {
            arr[index++] = val;
        }
    }
}
```

### Generic Template Version

```cpp
template <typename T>
void bucketSortGeneric(vector<T>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    
    T minVal = *min_element(arr.begin(), arr.end());
    T maxVal = *max_element(arr.begin(), arr.end());
    
    // Create buckets
    vector<vector<T>> buckets(n);
    
    // Distribute elements
    for (const T& element : arr) {
        int idx = (n * (element - minVal)) / (maxVal - minVal + 1);
        if (idx >= n) idx = n - 1;
        buckets[idx].push_back(element);
    }
    
    // Sort each bucket
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }
    
    // Concatenate
    arr.clear();
    for (const auto& bucket : buckets) {
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}
```

## Bucket Sort Complexity

### Time Complexity

| Case | Complexity | Condition |
|------|-----------|-----------|
| **Best** | O(n + k) | Uniform distribution, k buckets |
| **Average** | O(n + k) | Elements evenly distributed |
| **Worst** | O(n²) | All elements in one bucket |

**Detailed Analysis:**
- Creating buckets: O(k) where k is number of buckets
- Distributing elements: O(n)
- Sorting buckets: O(Σ(n_i²)) where n_i is size of bucket i
- If uniform distribution: each bucket has ~n/k elements
- Sorting each bucket: O((n/k)² × k) = O(n²/k)
- If k = n: O(n²/n) = O(n)
- **Total Best/Average: O(n + k)**
- **Worst case (all in one bucket): O(n²)** using comparison sort

### Space Complexity

- **Space: O(n + k)**
  - n for storing elements in buckets
  - k for bucket arrays

### When Does Bucket Sort Achieve O(n)?

**Conditions:**
1. Elements are **uniformly distributed** across the range
2. Number of buckets **proportional to n** (typically k = n)
3. Each bucket has **O(1) elements** on average

**Example where it's O(n):**
- Sorting 1000 random floats in [0, 1)
- Each of 1000 buckets gets ~1 element
- Total: O(1000) = O(n)

**Example where it's O(n²):**
- Sorting [1, 2, 3, ..., 1000] with only 1 bucket
- One bucket gets all 1000 elements
- Total: O(1000²) = O(n²)

## Bucket Sort When to Use

### ✅ Best Use Cases

1. **Uniformly distributed data**
   - Random floating-point numbers
   - Hash values
   - Normalized data

2. **Known range**
   - Data within specific bounds
   - Limited value range
   - Predictable distribution

3. **External sorting**
   - Data doesn't fit in memory
   - Can process buckets separately
   - Distributed systems

4. **Real-world examples:**
   - Sorting student grades (0-100)
   - Sorting ages (0-120)
   - Processing sensor data (known range)

### ❌ Avoid When

1. **Highly skewed data** - Most elements in few buckets
2. **Unknown distribution** - Can't predict bucket allocation
3. **Large range, few elements** - Wastes memory
4. **Need stability** - Implementation-dependent
5. **Comparison-only data** - Can't map to buckets easily

---

# Radix Sort

## Radix Sort Intuition

Think of how you'd sort a stack of index cards with numbers:
1. Sort by the **last digit** (ones place)
2. Then by the **second-to-last digit** (tens place)
3. Then by the **third-to-last digit** (hundreds place)
4. Continue until all digits processed

**Key Idea:** Sort digit by digit, starting from least significant digit (LSD) or most significant digit (MSD).

### Visual Example

**Sorting: [170, 45, 75, 90, 802, 24, 2, 66]**

```
Original:  170, 45, 75, 90, 802, 24, 2, 66

Pass 1 (Ones place):
0: 170, 90
2: 802, 2
4: 24
5: 45, 75
6: 66
Result: 170, 90, 802, 2, 24, 45, 75, 66

Pass 2 (Tens place):
0: 802, 2
2: 24
4: 45
6: 66
7: 170, 75
9: 90
Result: 802, 2, 24, 45, 66, 170, 75, 90

Pass 3 (Hundreds place):
0: 002, 024, 045, 066, 075, 090
1: 170
8: 802
Result: 2, 24, 45, 66, 75, 90, 170, 802

Final: [2, 24, 45, 66, 75, 90, 170, 802]
```

## Radix Sort Steps

### LSD (Least Significant Digit) Radix Sort

1. **Find maximum:** Determine number of digits in largest number
2. **For each digit position** (from rightmost to leftmost):
   - Use **counting sort** or **bucket sort** to sort by current digit
   - Maintain stability (order of equal elements preserved)
3. **After all digits processed:** Array is sorted

### Algorithm Pseudocode

```
RadixSort(arr):
    max = findMax(arr)
    
    for exp = 1; max / exp > 0; exp *= 10:
        countingSort(arr, exp)  // Sort by digit at position exp
```

### Detailed Walkthrough

**Input:** [329, 457, 657, 839, 436, 720, 355]

**Step 1: Find max = 839 (3 digits)**

**Step 2: Sort by ones place (exp = 1)**
```
Digit:  [9, 7, 7, 9, 6, 0, 5]
After:  [720, 355, 436, 457, 657, 329, 839]
```

**Step 3: Sort by tens place (exp = 10)**
```
Digit:  [2, 5, 3, 5, 5, 2, 3]
After:  [720, 329, 436, 839, 355, 457, 657]
```

**Step 4: Sort by hundreds place (exp = 100)**
```
Digit:  [7, 3, 4, 8, 3, 4, 6]
After:  [329, 355, 436, 457, 657, 720, 839]
```

**Final:** [329, 355, 436, 457, 657, 720, 839]

## Radix Sort Implementation

### Standard LSD Radix Sort

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Counting sort by specific digit
void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    
    // Store count of occurrences
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    
    // Change count[i] to actual position
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array (traverse from right to maintain stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copy output array to arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    // Find maximum number to know number of digits
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    
    // Do counting sort for every digit
    // exp is 10^i where i is current digit position
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    printArray(arr, n);
    
    radixSort(arr, n);
    
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}
```

### Radix Sort with Negative Numbers

```cpp
void countingSortSigned(int arr[], int n, int exp) {
    int output[n];
    int count[19] = {0};  // -9 to 9 mapped to 0-18
    
    // Count occurrences
    for (int i = 0; i < n; i++) {
        int digit = ((arr[i] / exp) % 10) + 9;  // Shift by 9
        count[digit]++;
    }
    
    // Cumulative count
    for (int i = 1; i < 19; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output
    for (int i = n - 1; i >= 0; i--) {
        int digit = ((arr[i] / exp) % 10) + 9;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copy to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSortSigned(int arr[], int n) {
    // Separate positive and negative numbers
    vector<int> negative, positive;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negative.push_back(-arr[i]);  // Store absolute value
        } else {
            positive.push_back(arr[i]);
        }
    }
    
    // Sort both arrays
    if (!negative.empty()) {
        int negArr[negative.size()];
        copy(negative.begin(), negative.end(), negArr);
        radixSort(negArr, negative.size());
        
        // Copy back in reverse and negate
        int idx = 0;
        for (int i = negative.size() - 1; i >= 0; i--) {
            arr[idx++] = -negArr[i];
        }
    }
    
    if (!positive.empty()) {
        int posArr[positive.size()];
        copy(positive.begin(), positive.end(), posArr);
        radixSort(posArr, positive.size());
        
        // Copy back
        int idx = negative.size();
        for (int i = 0; i < positive.size(); i++) {
            arr[idx++] = posArr[i];
        }
    }
}
```

### MSD (Most Significant Digit) Radix Sort

```cpp
void msdRadixSort(int arr[], int left, int right, int exp) {
    if (left >= right || exp < 1) return;
    
    // Create buckets for each digit (0-9)
    vector<int> buckets[10];
    
    // Distribute elements into buckets
    for (int i = left; i <= right; i++) {
        int digit = (arr[i] / exp) % 10;
        buckets[digit].push_back(arr[i]);
    }
    
    // Copy back to array and recursively sort each bucket
    int index = left;
    for (int i = 0; i < 10; i++) {
        int bucketStart = index;
        for (int val : buckets[i]) {
            arr[index++] = val;
        }
        int bucketEnd = index - 1;
        
        // Recursively sort this bucket with next digit
        if (bucketStart < bucketEnd) {
            msdRadixSort(arr, bucketStart, bucketEnd, exp / 10);
        }
    }
}

void msdRadixSortWrapper(int arr[], int n) {
    if (n <= 1) return;
    
    int maxVal = *max_element(arr, arr + n);
    int exp = 1;
    while (maxVal / exp >= 10) {
        exp *= 10;
    }
    
    msdRadixSort(arr, 0, n - 1, exp);
}
```

### Radix Sort for Strings

```cpp
void radixSortStrings(vector<string>& arr) {
    if (arr.empty()) return;
    
    // Find maximum length
    int maxLen = 0;
    for (const string& s : arr) {
        maxLen = max(maxLen, (int)s.length());
    }
    
    // Sort from rightmost character to leftmost
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        vector<string> buckets[256];  // ASCII characters
        
        for (const string& s : arr) {
            int charCode = (pos < s.length()) ? s[pos] : 0;
            buckets[charCode].push_back(s);
        }
        
        // Concatenate buckets
        arr.clear();
        for (int i = 0; i < 256; i++) {
            arr.insert(arr.end(), buckets[i].begin(), buckets[i].end());
        }
    }
}
```

## Radix Sort Complexity

### Time Complexity

| Case | Complexity | Explanation |
|------|-----------|-------------|
| **Best** | O(d × (n + k)) | d digits, n elements, k = 10 (base) |
| **Average** | O(d × (n + k)) | Same as best |
| **Worst** | O(d × (n + k)) | Same as best |

**Where:**
- **d** = number of digits in maximum number
- **n** = number of elements
- **k** = range of each digit (10 for decimal, 256 for ASCII, etc.)

**Simplified:**
- For decimal numbers: O(d × n) since k = 10 is constant
- If d is constant: **O(n)**
- If d = O(log n): **O(n log n)**

**Detailed Analysis:**
- Finding max: O(n)
- For each digit (d iterations):
  - Counting sort: O(n + k)
- Total: O(n) + d × O(n + k) = O(d × (n + k))

### Space Complexity

- **Space: O(n + k)**
  - Output array: O(n)
  - Count array: O(k)
  - For k = 10: O(n + 10) = O(n)

### Comparison with Other Sorts

| Algorithm | Time | Space | Stable | In-place |
|-----------|------|-------|--------|----------|
| Radix Sort | O(d×n) | O(n+k) | Yes | No |
| Quick Sort | O(n log n) | O(log n) | No | Yes |
| Merge Sort | O(n log n) | O(n) | Yes | No |
| Heap Sort | O(n log n) | O(1) | No | Yes |

## Radix Sort When to Use

### ✅ Best Use Cases

1. **Integer sorting with limited range**
   - Small number of digits (d is small)
   - Large number of elements (n is large)
   - Example: Sorting 1 million numbers with ≤ 6 digits

2. **Fixed-length strings**
   - Words of same length
   - IDs, codes, serial numbers
   - Example: Sorting zip codes

3. **When stability matters**
   - Radix sort is stable
   - Preserves order of equal elements
   - Good for multi-key sorting

4. **Real-world examples:**
   - Sorting dates (YYYYMMDD)
   - Sorting IP addresses
   - Sorting card numbers
   - Processing large datasets in databases

### ❌ Avoid When

1. **Floating-point numbers** - Need special handling
2. **Variable-length data** - Padding needed, inefficient
3. **Small datasets** - Overhead not worth it
4. **Large digit count** - d becomes large, loses advantage
5. **Memory constrained** - Needs O(n) extra space

---

# Comparison

## Bucket Sort vs Radix Sort

| Aspect | Bucket Sort | Radix Sort |
|--------|-------------|------------|
| **Method** | Divide into buckets by value range | Sort digit by digit |
| **Best for** | Uniformly distributed data | Integers, fixed-length strings |
| **Time (best)** | O(n + k) | O(d × (n + k)) |
| **Time (worst)** | O(n²) | O(d × (n + k)) |
| **Space** | O(n + k) | O(n + k) |
| **Stability** | Implementation-dependent | Yes (with stable counting sort) |
| **Distribution** | Requires uniform distribution | Works with any distribution |
| **Predictability** | Performance varies | Consistent performance |

## When to Use Which?

### Use Bucket Sort When:
- Data is **uniformly distributed**
- You know the **range** of values
- Working with **floating-point** numbers
- Need **parallel processing** (buckets can be sorted independently)

### Use Radix Sort When:
- Sorting **integers** or **fixed-length strings**
- Number of digits **d is small**
- Have **large number of elements**
- Need **stable** sorting
- Distribution doesn't matter

### Example Scenarios

**Scenario 1: Sort 1 million random floats in [0, 1)**
- **Use:** Bucket Sort
- **Why:** Uniform distribution, known range, floats

**Scenario 2: Sort 1 million 6-digit integers**
- **Use:** Radix Sort
- **Why:** Fixed digits (d=6), large n, integers

**Scenario 3: Sort 100 student grades (0-100)**
- **Use:** Either (but Bucket Sort might be simpler)
- **Why:** Small dataset, both work well

**Scenario 4: Sort variable-length names**
- **Use:** Neither (use comparison sort like Merge Sort)
- **Why:** Variable length, not numeric

---

# Complete C++ Program

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ==================== BUCKET SORT ====================

void bucketSort(float arr[], int n) {
    vector<float> buckets[n];
    
    // Put elements in buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i];
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sort individual buckets
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate buckets
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void bucketSortIntegers(int arr[], int n) {
    if (n <= 0) return;
    
    int maxVal = *max_element(arr, arr + n);
    int minVal = *min_element(arr, arr + n);
    int range = maxVal - minVal + 1;
    int bucketCount = n;
    
    vector<int> buckets[bucketCount];
    
    // Distribute elements
    for (int i = 0; i < n; i++) {
        int idx = (bucketCount * (arr[i] - minVal)) / range;
        if (idx >= bucketCount) idx = bucketCount - 1;
        buckets[idx].push_back(arr[i]);
    }
    
    // Sort buckets
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    // Concatenate
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

// ==================== RADIX SORT ====================

void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    
    // Store count of occurrences
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    
    // Change count[i] to actual position
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array (from right to maintain stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // Copy to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    // Find maximum to determine number of digits
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    
    // Do counting sort for every digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

// ==================== UTILITY FUNCTIONS ====================

void printArrayFloat(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printArrayInt(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "========== BUCKET SORT (Float) ==========\n";
    float floatArr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n1 = sizeof(floatArr) / sizeof(floatArr[0]);
    
    cout << "Original array: ";
    printArrayFloat(floatArr, n1);
    
    bucketSort(floatArr, n1);
    
    cout << "Sorted array:   ";
    printArrayFloat(floatArr, n1);
    
    cout << "\n========== BUCKET SORT (Integer) ==========\n";
    int intArr1[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n2 = sizeof(intArr1) / sizeof(intArr1[0]);
    
    cout << "Original array: ";
    printArrayInt(intArr1, n2);
    
    bucketSortIntegers(intArr1, n2);
    
    cout << "Sorted array:   ";
    printArrayInt(intArr1, n2);
    
    cout << "\n========== RADIX SORT ==========\n";
    int intArr2[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n3 = sizeof(intArr2) / sizeof(intArr2[0]);
    
    cout << "Original array: ";
    printArrayInt(intArr2, n3);
    
    radixSort(intArr2, n3);
    
    cout << "Sorted array:   ";
    printArrayInt(intArr2, n3);
    
    cout << "\n========== RADIX SORT (Large Numbers) ==========\n";
    int intArr3[] = {329, 457, 657, 839, 436, 720, 355};
    int n4 = sizeof(intArr3) / sizeof(intArr3[0]);
    
    cout << "Original array: ";
    printArrayInt(intArr3, n4);
    
    radixSort(intArr3, n4);
    
    cout << "Sorted array:   ";
    printArrayInt(intArr3, n4);
    
    return 0;
}
```

### Sample Output
```
========== BUCKET SORT (Float) ==========
Original array: 0.897 0.565 0.656 0.1234 0.665 0.3434 
Sorted array:   0.1234 0.3434 0.565 0.656 0.665 0.897 

========== BUCKET SORT (Integer) ==========
Original array: 29 25 3 49 9 37 21 43 
Sorted array:   3 9 21 25 29 37 43 49 

========== RADIX SORT ==========
Original array: 170 45 75 90 802 24 2 66 
Sorted array:   2 24 45 66 75 90 170 802 

========== RADIX SORT (Large Numbers) ==========
Original array: 329 457 657 839 436 720 355 
Sorted array:   329 355 436 457 657 720 839 
```

---

# Practice Problems

## Easy Level

### Problem 1: Basic Bucket Sort
**Question:** Implement bucket sort for an array of floats in range [0, 1).
```cpp
Input: [0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51]
Output: [0.23, 0.25, 0.32, 0.42, 0.47, 0.51, 0.52]
```

### Problem 2: Basic Radix Sort
**Question:** Sort an array of positive integers using radix sort.
```cpp
Input: [121, 432, 564, 23, 1, 45, 788]
Output: [1, 23, 45, 121, 432, 564, 788]
```

### Problem 3: Count Digits
**Question:** Write a function to count the number of digits in a number.
```cpp
int countDigits(int num) {
    // Your implementation
}
```

### Problem 4: Get Digit at Position
**Question:** Extract the digit at a specific position (0 = ones, 1 = tens, etc.).
```cpp
int getDigit(int num, int pos) {
    // Return digit at position pos
}
```

### Problem 5: Bucket Sort for Limited Range
**Question:** Sort integers in range [0, 100] using bucket sort.
```cpp
Input: [29, 25, 3, 49, 9, 37, 21, 43]
Output: [3, 9, 21, 25, 29, 37, 43, 49]
```

## Medium Level

### Problem 6: Sort Colors (LeetCode 75)
**Question:** Sort an array with only 0s, 1s, and 2s using bucket/counting sort.
```cpp
Input: [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]
```
**Hint:** Use counting sort (single pass bucket sort).

### Problem 7: Maximum Gap (LeetCode 164)
**Question:** Find maximum difference between successive elements in sorted form using bucket sort.
```cpp
Input: [3, 6, 9, 1]
Output: 3 (between 6 and 9)
```
**Hint:** Use bucket sort with buckets of size (max-min)/n.

### Problem 8: Sort with Negative Numbers
**Question:** Extend radix sort to handle negative integers.
```cpp
Input: [170, -45, 75, -90, 802, 24, -2, 66]
Output: [-90, -45, -2, 24, 66, 75, 170, 802]
```

### Problem 9: Top K Frequent Elements
**Question:** Use bucket sort to find k most frequent elements.
```cpp
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
```
**Hint:** Create buckets by frequency.

### Problem 10: Sort String Characters
**Question:** Sort characters in a string using radix/bucket sort.
```cpp
Input: "dcba"
Output: "abcd"
```

## Hard Level

### Problem 11: Radix Sort for Strings
**Question:** Implement radix sort for variable-length strings.
```cpp
Input: ["abc", "ab", "a", "abcd", "abcde"]
Output: ["a", "ab", "abc", "abcd", "abcde"]
```

### Problem 12: Custom Comparator Bucket Sort
**Question:** Sort 2D points by distance from origin using bucket sort.
```cpp
Input: [[1,3], [3,4], [2,3], [5,5]]
Output: [[1,3], [2,3], [3,4], [5,5]]
```

### Problem 13: External Sorting
**Question:** Implement bucket sort for data that doesn't fit in memory.
**Hint:** Use disk-based buckets.

### Problem 14: Parallel Bucket Sort
**Question:** Implement multithreaded bucket sort.
**Hint:** Each thread sorts different buckets.

### Problem 15: Adaptive Bucket Count
**Question:** Dynamically determine optimal number of buckets based on input distribution.
```cpp
int optimalBucketCount(int arr[], int n) {
    // Return optimal bucket count
}
```

## LeetCode Problems

- [75. Sort Colors](https://leetcode.com/problems/sort-colors/) - Bucket/Counting Sort
- [164. Maximum Gap](https://leetcode.com/problems/maximum-gap/) - Bucket Sort
- [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) - Bucket Sort
- [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) - Bucket Sort
- [1122. Relative Sort Array](https://leetcode.com/problems/relative-sort-array/) - Counting Sort

---

# Advanced Topics

## Optimizations

### 1. Adaptive Bucket Size
```cpp
int calculateOptimalBuckets(int arr[], int n) {
    // Use square root for general case
    return (int)sqrt(n);
}
```

### 2. Hybrid Approach
```cpp
void hybridBucketSort(int arr[], int n) {
    // Use bucket sort for large n
    // Use insertion sort for small buckets
    if (n < 50) {
        insertionSort(arr, n);
    } else {
        bucketSort(arr, n);
    }
}
```

### 3. In-place Radix Sort
```cpp
// Reduce space by modifying array in-place
void inPlaceRadixSort(int arr[], int n) {
    // More complex but uses O(1) extra space
    // Trade-off: more cache misses
}
```

## Parallel Implementations

### Parallel Bucket Sort
```cpp
#include <thread>
#include <vector>

void parallelBucketSort(int arr[], int n) {
    int numThreads = 4;
    vector<thread> threads;
    
    // Create buckets
    vector<int> buckets[n];
    
    // Distribute (parallel)
    // ... distribution logic
    
    // Sort buckets in parallel
    for (int i = 0; i < n; i++) {
        threads.push_back(thread([&, i]() {
            sort(buckets[i].begin(), buckets[i].end());
        }));
        
        if (threads.size() >= numThreads) {
            for (auto& t : threads) t.join();
            threads.clear();
        }
    }
    
    // Concatenate
    // ... concatenation logic
}
```

## Real-World Applications

### 1. Database Indexing
```cpp
// B-tree nodes often use radix sort for keys
void sortDatabaseKeys(vector<int>& keys) {
    radixSort(keys.data(), keys.size());
}
```

### 2. Network Packet Sorting
```cpp
// Sort packets by priority (0-7)
void sortPackets(Packet packets[], int n) {
    // Use counting sort (special case of bucket sort)
    vector<Packet> buckets[8];
    
    for (int i = 0; i < n; i++) {
        buckets[packets[i].priority].push_back(packets[i]);
    }
    
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (Packet p : buckets[i]) {
            packets[index++] = p;
        }
    }
}
```

### 3. Log File Processing
```cpp
// Sort log entries by timestamp
struct LogEntry {
    long timestamp;
    string message;
};

void sortLogs(vector<LogEntry>& logs) {
    // Extract timestamps
    vector<long> timestamps;
    for (auto& log : logs) {
        timestamps.push_back(log.timestamp);
    }
    
    // Radix sort timestamps
    // Then rearrange logs
}
```

---

# Key Takeaways

## Bucket Sort

### ✅ Advantages
- **O(n) time** with uniform distribution
- Simple to implement
- Works well with floating-point numbers
- Parallelizable (independent buckets)

### ❌ Disadvantages
- **O(n²) worst case** (all in one bucket)
- Requires knowledge of data distribution
- Extra space O(n)
- Performance depends on data distribution

### Remember
- Works best with **uniform distribution**
- Number of buckets ≈ number of elements
- Each bucket should have ~1 element on average

## Radix Sort

### ✅ Advantages
- **Stable** sorting algorithm
- **O(d×n)** time complexity
- Doesn't depend on data distribution
- Predictable performance
- Good for integers and fixed-length strings

### ❌ Disadvantages
- **Not in-place** (needs O(n) space)
- Limited to specific data types
- Poor for variable-length data
- Overhead for small datasets
- Number of digits matters

### Remember
- Works digit by digit (LSD or MSD)
- Each pass must be **stable**
- Best when **d is small** relative to log n
- O(n) when d is constant

## When to Use What?

| Scenario | Use | Why |
|----------|-----|-----|
| Random floats [0,1) | Bucket Sort | Uniform distribution |
| 6-digit integers | Radix Sort | Fixed digits, large n |
| Unknown distribution | Comparison sort | Can't guarantee O(n) |
| Need stability | Radix Sort | Inherently stable |
| Parallel processing | Bucket Sort | Independent buckets |
| Memory constrained | Comparison sort | These need O(n) space |

---

# Interview Tips

## Common Questions

### Q1: "Explain when bucket sort is O(n)."
**Answer:** When elements are uniformly distributed across buckets and we have n buckets for n elements, each bucket gets ~1 element. Sorting 1 element is O(1), so total is O(n).

### Q2: "Why is radix sort stable?"
**Answer:** Because we use counting sort (stable) for each digit pass, and process from least to most significant digit, preserving order from previous passes.

### Q3: "Can radix sort be used for floats?"
**Answer:** Yes, but requires special handling. Convert to integers by multiplying by 10^d, or use bucket sort instead which naturally handles floats.

### Q4: "What's the space complexity trade-off?"
**Answer:** Both need O(n) extra space. This is the cost of achieving O(n) time - we trade space for speed.

### Q5: "When would you choose these over Quick Sort?"
**Answer:** When data fits specific patterns (uniform distribution for bucket, fixed digits for radix) and n is large enough that O(n) beats O(n log n).

---

**Master Non-Comparison Sorts, Master Linear-Time Sorting! 🚀**
