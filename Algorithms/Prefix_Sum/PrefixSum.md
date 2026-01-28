# Prefix Sum - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [Basic Concept](#basic-concept)
- [1D Prefix Sum](#1d-prefix-sum)
- [2D Prefix Sum](#2d-prefix-sum)
- [Advanced Techniques](#advanced-techniques)
- [LeetCode Problems with Dry Runs](#leetcode-problems-with-dry-runs)
- [Common Patterns](#common-patterns)
- [Practice Problems](#practice-problems)

---

# Introduction

**Prefix Sum** is a preprocessing technique that allows us to answer range sum queries in **O(1)** time after **O(n)** preprocessing.

## Why Learn Prefix Sum?

1. **Optimize range queries** from O(n) to O(1)
2. **Common in interviews** - appears in 20%+ of array problems
3. **Foundation for advanced topics** - segment trees, Fenwick trees
4. **Versatile technique** - works with sums, products, XOR, etc.

## Real-World Applications

- **Financial Analysis:** Calculate cumulative returns
- **Image Processing:** Compute region sums quickly
- **Data Analytics:** Running totals and averages
- **Game Development:** Range damage calculations

---

# Basic Concept

## The Problem

Given an array, answer multiple range sum queries efficiently.

```
Array: [3, 1, 4, 1, 5, 9, 2, 6]

Query 1: Sum of elements from index 2 to 5 → 4+1+5+9 = 19
Query 2: Sum of elements from index 0 to 3 → 3+1+4+1 = 9
Query 3: Sum of elements from index 4 to 7 → 5+9+2+6 = 22
```

## Naive Approach

```cpp
int rangeSum(vector<int>& arr, int left, int right) {
    int sum = 0;
    for (int i = left; i <= right; i++) {
        sum += arr[i];
    }
    return sum;
}
// Time: O(n) per query
// For q queries: O(q × n)
```

## Prefix Sum Approach

**Key Idea:** Precompute cumulative sums!

```
Original: [3,  1,  4,  1,  5,  9,  2,  6]
Prefix:   [3,  4,  8,  9, 14, 23, 25, 31]
          
prefix[i] = sum of all elements from index 0 to i
```

**Range Sum Formula:**
```
sum(left, right) = prefix[right] - prefix[left - 1]
```

**Time Complexity:**
- Preprocessing: O(n)
- Each query: O(1)
- For q queries: O(n + q)

---

# 1D Prefix Sum

## Basic Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

class PrefixSum {
private:
    vector<long long> prefix;
    
public:
    // Constructor: Build prefix sum array
    PrefixSum(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n);
        
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }
    }
    
    // Query: Sum from index left to right (0-indexed)
    long long rangeSum(int left, int right) {
        if (left == 0) {
            return prefix[right];
        }
        return prefix[right] - prefix[left - 1];
    }
};

int main() {
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    PrefixSum ps(arr);
    
    cout << "Sum [2, 5]: " << ps.rangeSum(2, 5) << endl;  // 19
    cout << "Sum [0, 3]: " << ps.rangeSum(0, 3) << endl;  // 9
    cout << "Sum [4, 7]: " << ps.rangeSum(4, 7) << endl;  // 22
    
    return 0;
}
```

## Dry Run Example

```
Array: [3, 1, 4, 1, 5, 9, 2, 6]
Index:  0  1  2  3  4  5  6  7

Building Prefix Sum:
Step 1: prefix[0] = arr[0] = 3
Step 2: prefix[1] = prefix[0] + arr[1] = 3 + 1 = 4
Step 3: prefix[2] = prefix[1] + arr[2] = 4 + 4 = 8
Step 4: prefix[3] = prefix[2] + arr[3] = 8 + 1 = 9
Step 5: prefix[4] = prefix[3] + arr[4] = 9 + 5 = 14
Step 6: prefix[5] = prefix[4] + arr[5] = 14 + 9 = 23
Step 7: prefix[6] = prefix[5] + arr[6] = 23 + 2 = 25
Step 8: prefix[7] = prefix[6] + arr[7] = 25 + 6 = 31

Prefix Array: [3, 4, 8, 9, 14, 23, 25, 31]

Query: Sum from index 2 to 5
Visual: [x, x, 4, 1, 5, 9, x, x]
Formula: prefix[5] - prefix[1]
       = 23 - 4 = 19 ✓

Query: Sum from index 0 to 3
Visual: [3, 1, 4, 1, x, x, x, x]
Formula: prefix[3] - prefix[-1]
       = prefix[3] = 9 ✓
```

## With 1-Based Indexing (Easier for Edge Cases)

```cpp
class PrefixSum1Based {
private:
    vector<long long> prefix;
    
public:
    PrefixSum1Based(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n + 1);
        
        prefix[0] = 0;  // Dummy element
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }
    
    // Query: Sum from index left to right (0-indexed input)
    long long rangeSum(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};
```

**Advantage:** No need to handle `left == 0` case separately!

## Variations

### 1. Prefix Product

```cpp
class PrefixProduct {
private:
    vector<long long> prefix;
    
public:
    PrefixProduct(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n);
        
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * arr[i];
        }
    }
    
    long long rangeProduct(int left, int right) {
        if (left == 0) return prefix[right];
        return prefix[right] / prefix[left - 1];
    }
};
```

**Note:** Division doesn't work if array contains zeros. Need different approach.

### 2. Prefix XOR

```cpp
class PrefixXOR {
private:
    vector<int> prefix;
    
public:
    PrefixXOR(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n);
        
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] ^ arr[i];
        }
    }
    
    int rangeXOR(int left, int right) {
        if (left == 0) return prefix[right];
        return prefix[right] ^ prefix[left - 1];
    }
};
```

**Property:** `a ^ a = 0`, so `prefix[right] ^ prefix[left-1]` cancels out elements before left.

### 3. Prefix Maximum/Minimum

```cpp
class PrefixMax {
private:
    vector<int> prefix;
    
public:
    PrefixMax(vector<int>& arr) {
        int n = arr.size();
        prefix.resize(n);
        
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = max(prefix[i - 1], arr[i]);
        }
    }
    
    int maxUpTo(int index) {
        return prefix[index];
    }
};
```

---

# 2D Prefix Sum

## Concept

For a 2D matrix, we want to answer range sum queries for any submatrix.

```
Matrix:
1  2  3
4  5  6
7  8  9

Query: Sum of submatrix from (1,1) to (2,2)
Answer: 5 + 6 + 8 + 9 = 28
```

## 2D Prefix Sum Formula

```
prefix[i][j] = sum of all elements in rectangle from (0,0) to (i,j)

prefix[i][j] = matrix[i][j] 
             + prefix[i-1][j]    // sum above
             + prefix[i][j-1]    // sum to left
             - prefix[i-1][j-1]  // subtract overlap
```

## Visual Representation

```
Building prefix[2][2]:

    0   1   2
  +---+---+---+
0 | 1 | 2 | 3 |
  +---+---+---+
1 | 4 | 5 | 6 |
  +---+---+---+
2 | 7 | 8 | 9 |
  +---+---+---+

prefix[2][2] = matrix[2][2] = 9
             + prefix[1][2] = 21  (sum of top rectangle)
             + prefix[2][1] = 20  (sum of left rectangle)
             - prefix[1][1] = 12  (subtracted twice, add back once)
             = 9 + 21 + 20 - 12 = 38
```

## Implementation

```cpp
class PrefixSum2D {
private:
    vector<vector<long long>> prefix;
    int rows, cols;
    
public:
    PrefixSum2D(vector<vector<int>>& matrix) {
        rows = matrix.size();
        cols = matrix[0].size();
        prefix.resize(rows + 1, vector<long long>(cols + 1, 0));
        
        // Build prefix sum (1-indexed for easier calculation)
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                prefix[i][j] = matrix[i - 1][j - 1]
                             + prefix[i - 1][j]
                             + prefix[i][j - 1]
                             - prefix[i - 1][j - 1];
            }
        }
    }
    
    // Query: Sum of submatrix from (r1,c1) to (r2,c2) - 0-indexed
    long long rangeSum(int r1, int c1, int r2, int c2) {
        r1++; c1++; r2++; c2++;  // Convert to 1-indexed
        
        return prefix[r2][c2]
             - prefix[r1 - 1][c2]
             - prefix[r2][c1 - 1]
             + prefix[r1 - 1][c1 - 1];
    }
};
```

## Dry Run: 2D Prefix Sum

```
Matrix (0-indexed):
    0   1   2
  +---+---+---+
0 | 1 | 2 | 3 |
  +---+---+---+
1 | 4 | 5 | 6 |
  +---+---+---+
2 | 7 | 8 | 9 |
  +---+---+---+

Building Prefix Sum (1-indexed for easier calculation):

       0   1   2   3
    +---+---+---+---+
  0 | 0 | 0 | 0 | 0 |
    +---+---+---+---+
  1 | 0 | 1 | 3 | 6 |
    +---+---+---+---+
  2 | 0 | 5 |12 |21 |
    +---+---+---+---+
  3 | 0 |12 |27 |45 |
    +---+---+---+---+

Step-by-step for prefix[2][2]:
prefix[2][2] = matrix[1][1]           = 5
             + prefix[1][2]           = 3
             + prefix[2][1]           = 5
             - prefix[1][1]           = 1
             = 5 + 3 + 5 - 1 = 12 ✓

Query: Sum from (1,1) to (2,2) in 0-indexed
Convert to 1-indexed: (2,2) to (3,3)

Visual of what we want:
    0   1   2
  +---+---+---+
0 | x | x | x |
  +---+---+---+
1 | x | 5 | 6 |
  +---+---+---+
2 | x | 8 | 9 |
  +---+---+---+

Formula:
sum = prefix[3][3]           = 45  (entire matrix)
    - prefix[1][3]           = 6   (top rectangle)
    - prefix[3][1]           = 12  (left rectangle)
    + prefix[1][1]           = 1   (top-left, added back)
    = 45 - 6 - 12 + 1 = 28 ✓

Verification: 5 + 6 + 8 + 9 = 28 ✓
```

---

# Advanced Techniques

## 1. Difference Array (Inverse of Prefix Sum)

**Use Case:** Apply range updates efficiently.

```cpp
class DifferenceArray {
private:
    vector<int> diff;
    
public:
    DifferenceArray(int n) {
        diff.resize(n + 1, 0);
    }
    
    // Add value to range [left, right]
    void rangeUpdate(int left, int right, int value) {
        diff[left] += value;
        diff[right + 1] -= value;
    }
    
    // Get final array after all updates
    vector<int> getArray() {
        int n = diff.size() - 1;
        vector<int> result(n);
        result[0] = diff[0];
        
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] + diff[i];
        }
        
        return result;
    }
};
```

**Dry Run:**
```
Initial: diff = [0, 0, 0, 0, 0, 0]  (size 6, represents array of size 5)

Update 1: Add 3 to range [1, 3]
diff[1] += 3  → diff = [0, 3, 0, 0, 0, 0]
diff[4] -= 3  → diff = [0, 3, 0, 0, -3, 0]

Update 2: Add 5 to range [0, 2]
diff[0] += 5  → diff = [5, 3, 0, 0, -3, 0]
diff[3] -= 5  → diff = [5, 3, 0, -5, -3, 0]

Get final array (apply prefix sum):
result[0] = diff[0] = 5
result[1] = result[0] + diff[1] = 5 + 3 = 8
result[2] = result[1] + diff[2] = 8 + 0 = 8
result[3] = result[2] + diff[3] = 8 + (-5) = 3
result[4] = result[3] + diff[4] = 3 + (-3) = 0

Final: [5, 8, 8, 3, 0] ✓

Verification:
Start: [0, 0, 0, 0, 0]
After Update 1 [1,3] += 3: [0, 3, 3, 3, 0]
After Update 2 [0,2] += 5: [5, 8, 8, 3, 0] ✓
```

## 2. Prefix Sum with HashMap (Subarray Sum Equals K)

**Pattern:** Find subarrays with sum = k

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // Empty prefix
    
    int prefixSum = 0;
    int count = 0;
    
    for (int num : nums) {
        prefixSum += num;
        
        // If (prefixSum - k) exists, we found subarray with sum k
        if (prefixCount.find(prefixSum - k) != prefixCount.end()) {
            count += prefixCount[prefixSum - k];
        }
        
        prefixCount[prefixSum]++;
    }
    
    return count;
}
```

**Why it works:**
```
If prefix[j] - prefix[i] = k
Then prefix[i] = prefix[j] - k

So we look for (currentPrefixSum - k) in our map!
```

## 3. 2D Difference Array

```cpp
class DifferenceArray2D {
private:
    vector<vector<int>> diff;
    int rows, cols;
    
public:
    DifferenceArray2D(int r, int c) : rows(r), cols(c) {
        diff.resize(r + 1, vector<int>(c + 1, 0));
    }
    
    // Add value to submatrix from (r1,c1) to (r2,c2)
    void rangeUpdate(int r1, int c1, int r2, int c2, int value) {
        diff[r1][c1] += value;
        diff[r1][c2 + 1] -= value;
        diff[r2 + 1][c1] -= value;
        diff[r2 + 1][c2 + 1] += value;
    }
    
    // Get final matrix
    vector<vector<int>> getMatrix() {
        vector<vector<int>> result(rows, vector<int>(cols));
        
        // Apply 2D prefix sum
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = diff[i][j];
                if (i > 0) result[i][j] += result[i - 1][j];
                if (j > 0) result[i][j] += result[i][j - 1];
                if (i > 0 && j > 0) result[i][j] -= result[i - 1][j - 1];
            }
        }
        
        return result;
    }
};
```

---

# LeetCode Problems with Dry Runs

## Problem 1: Range Sum Query - Immutable (LeetCode 303)

**Problem:** Given an integer array, find the sum of elements between indices left and right.

```cpp
class NumArray {
private:
    vector<int> prefix;
    
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};
```

**Dry Run:**
```
Input: nums = [-2, 0, 3, -5, 2, -1]

Building Prefix Sum:
prefix[0] = 0
prefix[1] = 0 + (-2) = -2
prefix[2] = -2 + 0 = -2
prefix[3] = -2 + 3 = 1
prefix[4] = 1 + (-5) = -4
prefix[5] = -4 + 2 = -2
prefix[6] = -2 + (-1) = -3

Prefix: [0, -2, -2, 1, -4, -2, -3]

Query 1: sumRange(0, 2)
Answer: prefix[3] - prefix[0] = 1 - 0 = 1
Verify: -2 + 0 + 3 = 1 ✓

Query 2: sumRange(2, 5)
Answer: prefix[6] - prefix[2] = -3 - (-2) = -1
Verify: 3 + (-5) + 2 + (-1) = -1 ✓

Query 3: sumRange(0, 5)
Answer: prefix[6] - prefix[0] = -3 - 0 = -3
Verify: -2 + 0 + 3 + (-5) + 2 + (-1) = -3 ✓
```

## Problem 2: Subarray Sum Equals K (LeetCode 560)

**Problem:** Find the total number of continuous subarrays whose sum equals k.

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;
        
        int prefixSum = 0;
        int count = 0;
        
        for (int num : nums) {
            prefixSum += num;
            
            // Check if (prefixSum - k) exists
            if (prefixCount.count(prefixSum - k)) {
                count += prefixCount[prefixSum - k];
            }
            
            prefixCount[prefixSum]++;
        }
        
        return count;
    }
};
```

**Detailed Dry Run:**
```
Input: nums = [1, 2, 3, 4, 5], k = 9

Index:       0   1   2   3   4
Array:       1   2   3   4   5
Prefix Sum:  1   3   6  10  15

Step-by-step:

Initial: prefixCount = {0: 1}, prefixSum = 0, count = 0

i = 0, num = 1:
  prefixSum = 0 + 1 = 1
  Look for: prefixSum - k = 1 - 9 = -8 (not found)
  prefixCount = {0: 1, 1: 1}
  count = 0

i = 1, num = 2:
  prefixSum = 1 + 2 = 3
  Look for: 3 - 9 = -6 (not found)
  prefixCount = {0: 1, 1: 1, 3: 1}
  count = 0

i = 2, num = 3:
  prefixSum = 3 + 3 = 6
  Look for: 6 - 9 = -3 (not found)
  prefixCount = {0: 1, 1: 1, 3: 1, 6: 1}
  count = 0

i = 3, num = 4:
  prefixSum = 6 + 4 = 10
  Look for: 10 - 9 = 1 (found! count = 1)
  This means: subarray from index 1 to 3 has sum 9
  prefixCount = {0: 1, 1: 1, 3: 1, 6: 1, 10: 1}
  count = 1

i = 4, num = 5:
  prefixSum = 10 + 5 = 15
  Look for: 15 - 9 = 6 (found! count = 1)
  This means: subarray from index 3 to 4 has sum 9
  prefixCount = {0: 1, 1: 1, 3: 1, 6: 1, 10: 1, 15: 1}
  count = 2

Answer: 2 subarrays
Subarrays: [2,3,4] and [4,5] ✓
```

## Problem 3: Contiguous Array (LeetCode 525)

**Problem:** Find the maximum length of a contiguous subarray with equal number of 0s and 1s.

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> firstOccurrence;
        firstOccurrence[0] = -1;  // Before array starts
        
        int balance = 0;
        int maxLen = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            balance += (nums[i] == 1) ? 1 : -1;
            
            if (firstOccurrence.count(balance)) {
                maxLen = max(maxLen, i - firstOccurrence[balance]);
            } else {
                firstOccurrence[balance] = i;
            }
        }
        
        return maxLen;
    }
};
```

**Dry Run:**
```
Input: nums = [0, 1, 0, 1, 1, 0]

Key Idea: Treat 0 as -1 and 1 as +1
If balance returns to same value, equal 0s and 1s in between!

Index:         0   1   2   3   4   5
Array:         0   1   0   1   1   0
Treat as:     -1  +1  -1  +1  +1  -1
Balance:      -1   0  -1   0   1   0

Step-by-step:

Initial: firstOccurrence = {0: -1}, balance = 0, maxLen = 0

i = 0, nums[0] = 0:
  balance = 0 + (-1) = -1
  -1 not in map
  firstOccurrence = {0: -1, -1: 0}
  maxLen = 0

i = 1, nums[1] = 1:
  balance = -1 + 1 = 0
  0 is in map at index -1!
  Length = 1 - (-1) = 2
  maxLen = max(0, 2) = 2
  firstOccurrence unchanged (0 already in map)

i = 2, nums[2] = 0:
  balance = 0 + (-1) = -1
  -1 is in map at index 0!
  Length = 2 - 0 = 2
  maxLen = max(2, 2) = 2

i = 3, nums[3] = 1:
  balance = -1 + 1 = 0
  0 is in map at index -1!
  Length = 3 - (-1) = 4
  maxLen = max(2, 4) = 4

i = 4, nums[4] = 1:
  balance = 0 + 1 = 1
  1 not in map
  firstOccurrence = {0: -1, -1: 0, 1: 4}
  maxLen = 4

i = 5, nums[5] = 0:
  balance = 1 + (-1) = 0
  0 is in map at index -1!
  Length = 5 - (-1) = 6
  maxLen = max(4, 6) = 6

Answer: 6 (entire array has equal 0s and 1s) ✓
```

## Problem 4: Product of Array Except Self (LeetCode 238)

**Problem:** Return an array where `output[i]` is the product of all elements except `nums[i]`.

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        // Build left products
        result[0] = 1;
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        
        // Build right products and multiply
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
};
```

**Dry Run:**
```
Input: nums = [1, 2, 3, 4]

Step 1: Build left products (product of all elements to the left)

i = 0: result[0] = 1 (no elements to left)
i = 1: result[1] = 1 * nums[0] = 1 * 1 = 1
i = 2: result[2] = 1 * nums[1] = 1 * 2 = 2
i = 3: result[3] = 2 * nums[2] = 2 * 3 = 6

After Step 1: result = [1, 1, 2, 6]

Step 2: Build right products and multiply

rightProduct = 1

i = 3:
  result[3] = result[3] * rightProduct = 6 * 1 = 6
  rightProduct = rightProduct * nums[3] = 1 * 4 = 4

i = 2:
  result[2] = result[2] * rightProduct = 2 * 4 = 8
  rightProduct = rightProduct * nums[2] = 4 * 3 = 12

i = 1:
  result[1] = result[1] * rightProduct = 1 * 12 = 12
  rightProduct = rightProduct * nums[1] = 12 * 2 = 24

i = 0:
  result[0] = result[0] * rightProduct = 1 * 24 = 24
  rightProduct = rightProduct * nums[0] = 24 * 1 = 24

Final result = [24, 12, 8, 6]

Verification:
result[0] = 2 * 3 * 4 = 24 ✓
result[1] = 1 * 3 * 4 = 12 ✓
result[2] = 1 * 2 * 4 = 8 ✓
result[3] = 1 * 2 * 3 = 6 ✓
```

## Problem 5: Range Sum Query 2D - Immutable (LeetCode 304)

**Problem:** Find the sum of elements in a rectangle defined by its upper left and lower right corners.

```cpp
class NumMatrix {
private:
    vector<vector<int>> prefix;
    
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        prefix.resize(rows + 1, vector<int>(cols + 1, 0));
        
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                prefix[i][j] = matrix[i - 1][j - 1]
                             + prefix[i - 1][j]
                             + prefix[i][j - 1]
                             - prefix[i - 1][j - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        row1++; col1++; row2++; col2++;
        
        return prefix[row2][col2]
             - prefix[row1 - 1][col2]
             - prefix[row2][col1 - 1]
             + prefix[row1 - 1][col1 - 1];
    }
};
```

**Dry Run:**
```
Input matrix (0-indexed):
    0   1   2   3
  +---+---+---+---+
0 | 3 | 0 | 1 | 4 |
  +---+---+---+---+
1 | 5 | 6 | 3 | 2 |
  +---+---+---+---+
2 | 1 | 2 | 0 | 1 |
  +---+---+---+---+
3 | 4 | 1 | 0 | 1 |
  +---+---+---+---+

Building prefix (1-indexed):
       0   1   2   3   4
    +---+---+---+---+---+
  0 | 0 | 0 | 0 | 0 | 0 |
    +---+---+---+---+---+
  1 | 0 | 3 | 3 | 4 | 8 |
    +---+---+---+---+---+
  2 | 0 | 8 |14 |18 |24 |
    +---+---+---+---+---+
  3 | 0 | 9 |17 |21 |28 |
    +---+---+---+---+---+
  4 | 0 |13 |22 |26 |34 |
    +---+---+---+---+---+

Let's build prefix[2][2] step by step:
prefix[2][2] = matrix[1][1]      = 6
             + prefix[1][2]      = 3
             + prefix[2][1]      = 8
             - prefix[1][1]      = 3
             = 6 + 3 + 8 - 3 = 14 ✓

Query: sumRegion(1, 1, 2, 2)  [0-indexed]
This asks for sum of:
    0   1   2   3
  +---+---+---+---+
0 | x | x | x | x |
  +---+---+---+---+
1 | x | 6 | 3 | x |
  +---+---+---+---+
2 | x | 2 | 0 | x |
  +---+---+---+---+
3 | x | x | x | x |
  +---+---+---+---+

Convert to 1-indexed: (2,2) to (3,3)

Formula:
sum = prefix[3][3]           = 21
    - prefix[1][3]           = 4
    - prefix[3][1]           = 9
    + prefix[1][1]           = 3
    = 21 - 4 - 9 + 3 = 11

Verify: 6 + 3 + 2 + 0 = 11 ✓
```

## Problem 6: Continuous Subarray Sum (LeetCode 523)

**Problem:** Check if array has a continuous subarray of size at least 2 that sums to a multiple of k.

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> remainderIndex;
        remainderIndex[0] = -1;
        
        int prefixSum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];
            int remainder = prefixSum % k;
            
            if (remainderIndex.count(remainder)) {
                // Check if subarray length >= 2
                if (i - remainderIndex[remainder] >= 2) {
                    return true;
                }
            } else {
                remainderIndex[remainder] = i;
            }
        }
        
        return false;
    }
};
```

**Dry Run:**
```
Input: nums = [23, 2, 4, 6, 7], k = 6

Key Idea: If prefix[j] % k == prefix[i] % k, 
          then (prefix[j] - prefix[i]) % k == 0

Index:         0   1   2   3   4
Array:        23   2   4   6   7
Prefix Sum:   23  25  29  35  42
Remainder %6:  5   1   5   5   0

Step-by-step:

Initial: remainderIndex = {0: -1}, prefixSum = 0

i = 0, nums[0] = 23:
  prefixSum = 0 + 23 = 23
  remainder = 23 % 6 = 5
  5 not in map
  remainderIndex = {0: -1, 5: 0}

i = 1, nums[1] = 2:
  prefixSum = 23 + 2 = 25
  remainder = 25 % 6 = 1
  1 not in map
  remainderIndex = {0: -1, 5: 0, 1: 1}

i = 2, nums[2] = 4:
  prefixSum = 25 + 4 = 29
  remainder = 29 % 6 = 5
  5 is in map at index 0!
  Length = 2 - 0 = 2 (>= 2) ✓
  Return TRUE

Subarray: [2, 4] from index 1 to 2
Sum: 2 + 4 = 6, which is divisible by 6 ✓
```

## Problem 7: Subarray Sums Divisible by K (LeetCode 974)

**Problem:** Count number of subarrays with sum divisible by k.

```cpp
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> remainderCount;
        remainderCount[0] = 1;
        
        int prefixSum = 0;
        int count = 0;
        
        for (int num : nums) {
            prefixSum += num;
            int remainder = ((prefixSum % k) + k) % k;  // Handle negative
            
            if (remainderCount.count(remainder)) {
                count += remainderCount[remainder];
            }
            
            remainderCount[remainder]++;
        }
        
        return count;
    }
};
```

**Dry Run:**
```
Input: nums = [4, 5, 0, -2, -3, 1], k = 5

Index:          0   1   2   3   4   5
Array:          4   5   0  -2  -3   1
Prefix Sum:     4   9   9   7   4   5
Remainder %5:   4   4   4   2   4   0

Step-by-step:

Initial: remainderCount = {0: 1}, prefixSum = 0, count = 0

i = 0, num = 4:
  prefixSum = 0 + 4 = 4
  remainder = 4 % 5 = 4
  4 not in map
  remainderCount = {0: 1, 4: 1}
  count = 0

i = 1, num = 5:
  prefixSum = 4 + 5 = 9
  remainder = 9 % 5 = 4
  4 is in map! count += 1
  remainderCount = {0: 1, 4: 2}
  count = 1
  Subarray found: [5] from index 1 to 1

i = 2, num = 0:
  prefixSum = 9 + 0 = 9
  remainder = 9 % 5 = 4
  4 is in map! count += 2
  remainderCount = {0: 1, 4: 3}
  count = 3
  Subarrays: [5,0] and [0]

i = 3, num = -2:
  prefixSum = 9 + (-2) = 7
  remainder = 7 % 5 = 2
  2 not in map
  remainderCount = {0: 1, 4: 3, 2: 1}
  count = 3

i = 4, num = -3:
  prefixSum = 7 + (-3) = 4
  remainder = 4 % 5 = 4
  4 is in map! count += 3
  remainderCount = {0: 1, 4: 4, 2: 1}
  count = 6
  Subarrays: [-2,-3], [5,0,-2,-3], [4,5,0,-2,-3]

i = 5, num = 1:
  prefixSum = 4 + 1 = 5
  remainder = 5 % 5 = 0
  0 is in map! count += 1
  remainderCount = {0: 2, 4: 4, 2: 1}
  count = 7
  Subarray: entire array [4,5,0,-2,-3,1]

Answer: 7 subarrays ✓
```

## Problem 8: Minimum Size Subarray Sum (LeetCode 209)

**Problem:** Find the minimal length of a subarray whose sum is greater than or equal to target.

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        int sum = 0;
        int left = 0;
        
        for (int right = 0; right < n; right++) {
            sum += nums[right];
            
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        
        return minLen == INT_MAX ? 0 : minLen;
    }
};
```

**Dry Run:**
```
Input: target = 7, nums = [2, 3, 1, 2, 4, 3]

Index:  0   1   2   3   4   5
Array:  2   3   1   2   4   3

Using sliding window with prefix sum concept:

Initial: left = 0, sum = 0, minLen = ∞

right = 0:
  sum = 0 + 2 = 2
  2 < 7, continue

right = 1:
  sum = 2 + 3 = 5
  5 < 7, continue

right = 2:
  sum = 5 + 1 = 6
  6 < 7, continue

right = 3:
  sum = 6 + 2 = 8
  8 >= 7! minLen = min(∞, 3-0+1) = 4
  Window: [2,3,1,2]
  
  Shrink window:
    sum = 8 - 2 = 6, left = 1
    6 < 7, stop shrinking

right = 4:
  sum = 6 + 4 = 10
  10 >= 7! minLen = min(4, 4-1+1) = 4
  Window: [3,1,2,4]
  
  Shrink window:
    sum = 10 - 3 = 7, left = 2
    7 >= 7! minLen = min(4, 4-2+1) = 3
    Window: [1,2,4]
    
    sum = 7 - 1 = 6, left = 3
    6 < 7, stop shrinking

right = 5:
  sum = 6 + 3 = 9
  9 >= 7! minLen = min(3, 5-3+1) = 3
  Window: [2,4,3]
  
  Shrink window:
    sum = 9 - 2 = 7, left = 4
    7 >= 7! minLen = min(3, 5-4+1) = 2
    Window: [4,3]
    
    sum = 7 - 4 = 3, left = 5
    3 < 7, stop shrinking

Answer: 2 (subarray [4,3]) ✓
```

---

# Common Patterns

## Pattern 1: Basic Range Sum Query

**Template:**
```cpp
// Preprocessing
vector<long long> prefix(n + 1, 0);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + arr[i];
}

// Query
int rangeSum(int left, int right) {
    return prefix[right + 1] - prefix[left];
}
```

## Pattern 2: Subarray Sum with HashMap

**Template:**
```cpp
unordered_map<int, int> prefixCount;
prefixCount[0] = 1;

int prefixSum = 0;
for (int i = 0; i < n; i++) {
    prefixSum += arr[i];
    
    // Look for (prefixSum - target)
    if (prefixCount.count(prefixSum - target)) {
        // Found subarray
    }
    
    prefixCount[prefixSum]++;
}
```

## Pattern 3: Prefix Sum with Modulo

**Template:**
```cpp
unordered_map<int, int> remainderCount;
remainderCount[0] = 1;

int prefixSum = 0;
for (int i = 0; i < n; i++) {
    prefixSum += arr[i];
    int remainder = ((prefixSum % k) + k) % k;
    
    // Same remainder means divisible by k
    count += remainderCount[remainder];
    remainderCount[remainder]++;
}
```

## Pattern 4: 2D Prefix Sum

**Template:**
```cpp
// Build
prefix[i][j] = matrix[i-1][j-1]
             + prefix[i-1][j]
             + prefix[i][j-1]
             - prefix[i-1][j-1];

// Query
sum = prefix[r2+1][c2+1]
    - prefix[r1][c2+1]
    - prefix[r2+1][c1]
    + prefix[r1][c1];
```

## Pattern 5: Difference Array for Range Updates

**Template:**
```cpp
vector<int> diff(n + 1, 0);

// Update range [left, right]
diff[left] += value;
diff[right + 1] -= value;

// Get final array
for (int i = 1; i < n; i++) {
    diff[i] += diff[i - 1];
}
```

---

# Practice Problems

## Beginner Level

1. **Running Sum of 1d Array (LeetCode 1480)**
   - Direct prefix sum application

2. **Find Pivot Index (LeetCode 724)**
   - Use prefix sum from both sides

3. **Range Sum Query - Immutable (LeetCode 303)**
   - Classic prefix sum

## Intermediate Level

4. **Subarray Sum Equals K (LeetCode 560)**
   - Prefix sum with HashMap

5. **Continuous Subarray Sum (LeetCode 523)**
   - Prefix sum with modulo

6. **Contiguous Array (LeetCode 525)**
   - Balance concept with prefix sum

7. **Product of Array Except Self (LeetCode 238)**
   - Prefix and suffix products

8. **Range Sum Query 2D (LeetCode 304)**
   - 2D prefix sum

## Advanced Level

9. **Subarray Sums Divisible by K (LeetCode 974)**
   - Modulo with negative numbers

10. **Maximum Size Subarray Sum Equals k (LeetCode 325)**
    - Find longest subarray

11. **Shortest Subarray with Sum at Least K (LeetCode 862)**
    - Monotonic deque + prefix sum

12. **Maximum Sum of 3 Non-Overlapping Subarrays (LeetCode 689)**
    - Multiple prefix sum arrays

---

# Summary

## Key Takeaways

1. **Prefix sum converts O(n) range queries to O(1)**
2. **Build in O(n), query in O(1)**
3. **Works with sum, product, XOR, max/min**
4. **2D prefix sum for matrix range queries**
5. **HashMap + prefix sum = powerful pattern**
6. **Difference array for efficient range updates**

## When to Use Prefix Sum?

✅ Multiple range sum queries  
✅ Subarray sum problems  
✅ Sliding window with sum condition  
✅ 2D matrix range queries  
✅ Problems with "continuous subarray"  

## Time Complexities

| Operation | Time | Space |
|-----------|------|-------|
| Build prefix sum | O(n) | O(n) |
| Range sum query | O(1) | O(1) |
| Build 2D prefix | O(m×n) | O(m×n) |
| 2D range query | O(1) | O(1) |

## Common Mistakes

❌ Forgetting 0-indexed vs 1-indexed  
❌ Not handling negative numbers in modulo  
❌ Off-by-one errors in range queries  
❌ Forgetting to initialize prefix[0]  
❌ Integer overflow (use long long)  

---

**Master Prefix Sum and unlock efficient solutions!** 🚀

**Next Steps:**
- Practice LeetCode prefix sum problems
- Learn Segment Trees (advanced range queries)
- Study Fenwick Trees (updates + queries)
