# Pointer Patterns — Complete C++ Guide
## Two Pointers · Slow-Fast Pointers · Three Pointers

## Table of Contents
- [What Are Pointer Patterns?](#what-are-pointer-patterns)
- [PART 1 — Two Pointers](#part-1--two-pointers)
  - [Intuition & Mental Model](#intuition--mental-model)
  - [Core Patterns](#core-patterns)
  - [Easy Problems (10)](#easy-problems)
  - [Medium Problems (10)](#medium-problems)
  - [Hard Problems (10)](#hard-problems)
- [PART 2 — Slow & Fast Pointers](#part-2--slow--fast-pointers)
  - [Intuition & Mental Model](#intuition--mental-model-1)
  - [Core Patterns](#core-patterns-1)
  - [Easy Problems (10)](#easy-problems-1)
  - [Medium Problems (10)](#medium-problems-1)
  - [Hard Problems (10)](#hard-problems-1)
- [PART 3 — Three Pointers](#part-3--three-pointers)
  - [Intuition & Mental Model](#intuition--mental-model-2)
  - [Core Patterns](#core-patterns-2)
  - [Easy Problems (10)](#easy-problems-2)
  - [Medium Problems (10)](#medium-problems-2)
  - [Hard Problems (10)](#hard-problems-2)
- [Pattern Recognition Cheat Sheet](#pattern-recognition-cheat-sheet)
- [Common Mistakes & How to Avoid Them](#common-mistakes--how-to-avoid-them)
- [Practice Strategy](#practice-strategy)

---

# What Are Pointer Patterns?

**Pointer patterns** are algorithmic techniques where you maintain two or more index variables
(pointers) that traverse a data structure — usually an array or linked list — to reduce an
O(n²) brute-force search into a single O(n) pass.

## Why They Work

```
Brute Force:  Try every pair (i, j) where i < j
              → n × (n-1) / 2 comparisons = O(n²)

Two Pointers: Use sorted order or a known relationship
              to ELIMINATE impossible pairs at every step
              → Each pointer moves at most n steps = O(n)
```

## The Three Families

| Pattern | Pointers | Move Style | Best For |
| :--- | :--- | :--- | :--- |
| **Two Pointers** | left, right | Opposite or same direction | Sorted arrays, pairs, subarrays |
| **Slow-Fast** | slow, fast | Same direction, different speeds | Cycles, middle, nth-from-end |
| **Three Pointers** | i, j, k | Various | 3Sum, Dutch flag, merging |

---

# PART 1 — Two Pointers

---

## Intuition & Mental Model

Imagine two people walking along a sorted number line:
- **Person L** starts at the left (smallest values)
- **Person R** starts at the right (largest values)
- Their **sum** is too small → move L right (increase sum)
- Their **sum** is too large → move R left (decrease sum)
- **Equal to target** → found the answer

```
Array: [1, 3, 5, 7, 9, 11]  Target: 12

Step 1:  L=1  R=11  sum=12 ✅ Found!

Array: [1, 3, 5, 7, 9, 11]  Target: 10

Step 1:  L=1  R=11  sum=12 > 10 → move R left
Step 2:  L=1  R=9   sum=10 ✅ Found!

Array: [1, 3, 5, 7, 9, 11]  Target: 20

Step 1:  L=1  R=11  sum=12 < 20 → move L right
Step 2:  L=3  R=11  sum=14 < 20 → move L right
Step 3:  L=5  R=11  sum=16 < 20 → move L right
Step 4:  L=7  R=11  sum=18 < 20 → move L right
Step 5:  L=9  R=11  sum=20 ✅ Found!
```

**Key Insight:** Because the array is sorted, moving left pointer right
**always increases** the sum, and moving right pointer left **always decreases** it.
This gives us guaranteed progress toward the answer.

---

## Core Patterns

### Pattern A: Opposite-End Two Pointers

```
Start: L at index 0, R at index n-1
Move:  Based on comparison of current values vs target
Stop:  When L >= R
```

```cpp
// TEMPLATE: Opposite-End Two Pointers
void twoPointers_OppositeEnd(vector<int>& arr) {
    int left  = 0;
    int right = arr.size() - 1;

    while (left < right) {
        // Compute something with arr[left] and arr[right]
        int val = arr[left] + arr[right];   // example

        if (val == target) {
            // Found answer — process and decide to continue or stop
            left++;
            right--;
        } else if (val < target) {
            left++;   // Need larger values → move left pointer right
        } else {
            right--;  // Need smaller values → move right pointer left
        }
    }
}
```

### Pattern B: Same-Direction Two Pointers (Read-Write)

```
Start: Both at 0 (or reader at 0, writer at 0)
Move:  Reader always moves forward; writer moves only on valid element
Stop:  When reader reaches end
```

```cpp
// TEMPLATE: Same-Direction (In-place filter / compress)
int twoPointers_SameDirection(vector<int>& arr) {
    int writer = 0;  // Position to write next valid element

    for (int reader = 0; reader < arr.size(); reader++) {
        if (isValid(arr[reader])) {           // Keep this element?
            arr[writer] = arr[reader];
            writer++;
        }
        // reader always advances; writer only advances on valid
    }

    return writer;  // New length after filtering
}
```

### Pattern C: Sliding Window (Variable Size)

```
Start: Both at 0
Move:  Right always expands; left shrinks when window is invalid
Stop:  When right reaches end
```

```cpp
// TEMPLATE: Variable Sliding Window
int slidingWindow(vector<int>& arr, int k) {
    int left = 0, result = 0;
    int windowVal = 0;

    for (int right = 0; right < arr.size(); right++) {
        windowVal += arr[right];             // Expand: add right element

        while (windowVal > k) {              // Shrink: while invalid
            windowVal -= arr[left];
            left++;
        }

        result = max(result, right - left + 1);  // Update answer
    }

    return result;
}
```

---

## Visual: When to Move Which Pointer

```
SORTED ARRAY, looking for target sum:

[  1,  2,  4,  6,  8,  10  ]
   L                    R

sum = L + R

  sum < target  →  move L right  (increase sum)
  sum > target  →  move R left   (decrease sum)
  sum = target  →  ANSWER FOUND

WHY IS THIS CORRECT?
If sum < target and we move R left instead:
  New sum = L + R' where R' < R
  New sum < old sum < target  →  moves AWAY from answer
  So moving R left when sum < target is ALWAYS wrong
  Therefore moving L right is the ONLY valid move
```

---

## Easy Problems

---

### E1. Valid Palindrome (LeetCode 125)

```cpp
/*
 * Problem: 125. Valid Palindrome
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * A phrase is a palindrome if, after converting all uppercase
 * letters to lowercase and removing all non-alphanumeric
 * characters, it reads the same forward and backward.
 *
 * Given string s, return true if it is a palindrome.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * A palindrome reads the same from both ends.
 * → Place one pointer at the start, one at the end.
 * → Skip non-alphanumeric characters (they don't count).
 * → Compare characters case-insensitively.
 * → If any mismatch → not palindrome.
 *
 * ─────────────────────────────────────────────────────────
 * APPROACH: Opposite-End Two Pointers
 *
 * 1. left = 0, right = n-1
 * 2. While left < right:
 *    a. Skip non-alnum from left
 *    b. Skip non-alnum from right
 *    c. Compare tolower(s[left]) vs tolower(s[right])
 *    d. If mismatch → false
 *    e. Move both inward
 * 3. Return true
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * s = "A man, a plan, a canal: Panama"
 *
 * left=0  right=29: 'A' vs 'a' → match → move inward
 * left=2  right=27: 'm' vs 'm' → match
 * left=3  right=25: 'a' vs 'a' → match
 * ... all match → true
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) — each character visited once
 * SPACE: O(1) — no extra data structure
 */

class Solution {
public:
    bool isPalindrome(string s) {
        int left  = 0;
        int right = (int)s.size() - 1;

        while (left < right) {
            // Skip non-alphanumeric from left
            while (left < right && !isalnum(s[left]))  left++;
            // Skip non-alphanumeric from right
            while (left < right && !isalnum(s[right])) right--;

            // Compare case-insensitively
            if (tolower(s[left]) != tolower(s[right])) return false;

            left++;
            right--;
        }

        return true;
    }
};
```

---

### E2. Reverse String (LeetCode 344)

```cpp
/*
 * Problem: 344. Reverse String
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Write a function that reverses a string (char array) in-place.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Think of it as "swapping mirrors":
 * The first and last characters swap, then second and second-last, etc.
 * Two pointers from opposite ends, swap and march inward.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * s = ['h','e','l','l','o']
 *
 * left=0 right=4: swap 'h'↔'o' → ['o','e','l','l','h']
 * left=1 right=3: swap 'e'↔'l' → ['o','l','l','e','h']
 * left=2 right=2: left >= right → STOP
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left  = 0;
        int right = (int)s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
```

---

### E3. Squares of a Sorted Array (LeetCode 977)

```cpp
/*
 * Problem: 977. Squares of a Sorted Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an integer array nums sorted in non-decreasing order,
 * return an array of the squares of each number sorted in
 * non-decreasing order.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * The array has negatives on the left and positives on the right.
 * After squaring, the largest squares are at the ENDS.
 *
 * Example: [-4, -1, 0, 3, 10]
 * Squares:  [16,  1, 0, 9, 100]
 * Largest squares: 16 (at left) and 100 (at right)
 *
 * → Two pointers from both ends.
 * → Always place the LARGER square at the BACK of result array.
 * → Fill result from right to left.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [-4, -1, 0, 3, 10]
 * result = [_, _, _, _, _]
 * pos = 4 (fill from right)
 *
 * L=-4(sq=16), R=10(sq=100) → 100>16 → result[4]=100, R--
 * L=-4(sq=16), R=3(sq=9)   → 16>9  → result[3]=16,  L++
 * L=-1(sq=1),  R=3(sq=9)   → 9>1   → result[2]=9,   R--
 * L=-1(sq=1),  R=0(sq=0)   → 1>0   → result[1]=1,   L++
 * L=0(sq=0),  R=0(sq=0)    → equal → result[0]=0,   L++
 *
 * result = [0, 1, 9, 16, 100] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(n) for result array
 */

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        int left  = 0;
        int right = n - 1;
        int pos   = n - 1;  // Fill result from the back

        while (left <= right) {
            int lSq = nums[left]  * nums[left];
            int rSq = nums[right] * nums[right];

            if (lSq > rSq) {
                result[pos] = lSq;
                left++;
            } else {
                result[pos] = rSq;
                right--;
            }
            pos--;
        }

        return result;
    }
};
```

---

### E4. Merge Sorted Array (LeetCode 88)

```cpp
/*
 * Problem: 88. Merge Sorted Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given two sorted integer arrays nums1 (with extra space) and nums2,
 * merge nums2 into nums1 in-place in sorted order.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Merging from the front would require shifting elements.
 * Instead, merge from the BACK — fill the largest positions first.
 * This uses the extra space in nums1 without overwriting unread data.
 *
 * Three pointers:
 * - p1: last valid element in nums1 (index m-1)
 * - p2: last element in nums2 (index n-1)
 * - p:  current fill position (index m+n-1)
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums1 = [1,2,3,0,0,0], m=3
 * nums2 = [2,5,6],       n=3
 *
 * p1=2, p2=2, p=5
 * nums1[2]=3 vs nums2[2]=6 → 6 bigger → nums1[5]=6, p2=1, p=4
 * nums1[2]=3 vs nums2[1]=5 → 5 bigger → nums1[4]=5, p2=0, p=3
 * nums1[2]=3 vs nums2[0]=2 → 3 bigger → nums1[3]=3, p1=1, p=2
 * nums1[1]=2 vs nums2[0]=2 → equal   → nums1[2]=2, p2=-1, p=1
 * p2 < 0 → done
 * Result: [1,2,2,3,5,6] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m + n)
 * SPACE: O(1)
 */

class Solution {
public:
    void merge(vector<int>& nums1, int m,
               vector<int>& nums2, int n) {
        int p1 = m - 1;          // Pointer for nums1
        int p2 = n - 1;          // Pointer for nums2
        int p  = m + n - 1;      // Fill position (back of nums1)

        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }

        // If nums2 still has elements, copy them
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
        // No need to copy nums1 remainder — it's already there
    }
};
```

---

### E5. Remove Duplicates from Sorted Array (LeetCode 26)

```cpp
/*
 * Problem: 26. Remove Duplicates from Sorted Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a sorted array nums, remove duplicates in-place such
 * that each unique element appears only once.
 * Return the number of unique elements k.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * "Read-Write" two pointers:
 * - READER scans every element (always moves forward)
 * - WRITER records only new unique values
 *
 * Since array is sorted, duplicates are always adjacent.
 * A new unique element is one that differs from the last written.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [1,1,2,3,3,3,4]
 *
 * writer=0 (points to 1)
 * reader=1: nums[1]=1 == nums[0]=1 → skip
 * reader=2: nums[2]=2 != nums[0]=1 → write: nums[1]=2, writer=1
 * reader=3: nums[3]=3 != nums[1]=2 → write: nums[2]=3, writer=2
 * reader=4: nums[4]=3 == nums[2]=3 → skip
 * reader=5: nums[5]=3 == nums[2]=3 → skip
 * reader=6: nums[6]=4 != nums[2]=3 → write: nums[3]=4, writer=3
 *
 * Result: [1,2,3,4,...] k=4 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int writer = 0;  // Points to last written unique element

        for (int reader = 1; reader < (int)nums.size(); reader++) {
            if (nums[reader] != nums[writer]) {
                writer++;
                nums[writer] = nums[reader];
            }
        }

        return writer + 1;  // writer is index, so length = index + 1
    }
};
```

---

### E6. Remove Element (LeetCode 27)

```cpp
/*
 * Problem: 27. Remove Element
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given array nums and integer val, remove all occurrences
 * of val in-place. Return the count of remaining elements.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Same Read-Write pattern.
 * Writer advances ONLY when we see an element != val.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [3, 2, 2, 3], val = 3
 *
 * writer=0
 * reader=0: nums[0]=3 == val → skip
 * reader=1: nums[1]=2 != val → nums[0]=2, writer=1
 * reader=2: nums[2]=2 != val → nums[1]=2, writer=2
 * reader=3: nums[3]=3 == val → skip
 *
 * Result: [2, 2, ...] k=2 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int writer = 0;

        for (int reader = 0; reader < (int)nums.size(); reader++) {
            if (nums[reader] != val) {
                nums[writer] = nums[reader];
                writer++;
            }
        }

        return writer;
    }
};
```

---

### E7. Two Sum II — Input Array Is Sorted (LeetCode 167)

```cpp
/*
 * Problem: 167. Two Sum II — Input Array Is Sorted
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a 1-indexed sorted array and a target,
 * find two numbers that add up to target.
 * Return their 1-based indices.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * This is the classic "why two pointers work" problem.
 * The sorted order gives us a guarantee:
 *
 *   sum too small → left pointer can only help by moving RIGHT
 *   sum too large → right pointer can only help by moving LEFT
 *
 * Every step eliminates ENTIRE rows/columns of the search space.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * numbers = [2, 7, 11, 15], target = 9
 *
 * L=2,  R=15  sum=17 > 9 → R--
 * L=2,  R=11  sum=13 > 9 → R--
 * L=2,  R=7   sum=9  = 9 → return [1, 2] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left  = 0;
        int right = (int)numbers.size() - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                return {left + 1, right + 1};  // 1-indexed
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }

        return {};  // Guaranteed to have a solution per problem statement
    }
};
```

---

### E8. Move Zeroes (LeetCode 283)

```cpp
/*
 * Problem: 283. Move Zeroes
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an integer array nums, move all 0s to the end while
 * maintaining the relative order of non-zero elements. In-place.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Read-Write pointers:
 * - Writer points to the next position for a non-zero element
 * - Reader scans forward
 * - On finding non-zero: swap with writer position, advance writer
 *
 * The swap (instead of overwrite) naturally places zeros at the back.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [0, 1, 0, 3, 12]
 *
 * writer=0
 * reader=0: 0    → skip
 * reader=1: 1≠0  → swap(nums[1], nums[0]) → [1,0,0,3,12], writer=1
 * reader=2: 0    → skip
 * reader=3: 3≠0  → swap(nums[3], nums[1]) → [1,3,0,0,12], writer=2
 * reader=4: 12≠0 → swap(nums[4], nums[2]) → [1,3,12,0,0], writer=3
 *
 * Result: [1, 3, 12, 0, 0] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int writer = 0;

        for (int reader = 0; reader < (int)nums.size(); reader++) {
            if (nums[reader] != 0) {
                swap(nums[writer], nums[reader]);
                writer++;
            }
        }
    }
};
```

---

### E9. Reverse Vowels of a String (LeetCode 345)

```cpp
/*
 * Problem: 345. Reverse Vowels of a String
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a string s, reverse only all the vowels in the string.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Modified palindrome check:
 * - Two pointers from both ends
 * - Skip non-vowels on both sides
 * - Swap only when BOTH pointers land on vowels
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * s = "hello"
 * Vowels: e(1), o(4)
 *
 * L=0 'h' → skip, L=1
 * R=4 'o' → vowel
 * L=1 'e' → vowel, R=4 'o' → vowel
 * swap('e','o') → "holle"
 * L=2, R=3 → 'l','l' → skip both → L>R, done
 *
 * Result: "holle" ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1) (modifying in place)
 */

class Solution {
public:
    string reverseVowels(string s) {
        auto isVowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };

        int left  = 0;
        int right = (int)s.size() - 1;

        while (left < right) {
            while (left < right && !isVowel(s[left]))  left++;
            while (left < right && !isVowel(s[right])) right--;

            if (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;
    }
};
```

---

### E10. Is Subsequence (LeetCode 392)

```cpp
/*
 * Problem: 392. Is Subsequence
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given strings s and t, return true if s is a subsequence of t.
 * (Can delete characters from t without changing relative order)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Greedy two pointers on different strings:
 * - Pointer i scans s (the pattern to match)
 * - Pointer j scans t (the source)
 *
 * Match s[i] greedily in t:
 * - If s[i] == t[j] → match found, advance both
 * - Else → advance only j (skip t character)
 *
 * If i reaches end of s → all characters matched → true
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * s = "ace", t = "abcde"
 *
 * i=0 'a', j=0 'a' → match, i=1, j=1
 * i=1 'c', j=1 'b' → no match, j=2
 * i=1 'c', j=2 'c' → match, i=2, j=3
 * i=2 'e', j=3 'd' → no match, j=4
 * i=2 'e', j=4 'e' → match, i=3, j=5
 * i=3 == s.size() → return true ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) where n = t.length()
 * SPACE: O(1)
 */

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0;  // Pointer for s
        int j = 0;  // Pointer for t

        while (i < (int)s.size() && j < (int)t.size()) {
            if (s[i] == t[j]) {
                i++;  // Character matched, advance s pointer
            }
            j++;  // Always advance t pointer
        }

        return i == (int)s.size();  // Did we match all of s?
    }
};
```

---

## Medium Problems

---

### M1. 3Sum (LeetCode 15)

```cpp
/*
 * Problem: 15. 3Sum
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an integer array nums, return all triplets
 * [nums[i], nums[j], nums[k]] such that i, j, k are distinct
 * and nums[i] + nums[j] + nums[k] == 0.
 * Solution must not contain duplicate triplets.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Reduce 3Sum to multiple 2Sum problems:
 * - Fix one element nums[i]
 * - Use two pointers to find pairs that sum to -nums[i]
 *
 * To avoid duplicates:
 * - Sort first (so duplicates are adjacent)
 * - Skip duplicate values for i (outer loop)
 * - Skip duplicate values for left and right (inner search)
 *
 * ─────────────────────────────────────────────────────────
 * APPROACH:
 *
 * 1. Sort nums
 * 2. For i from 0 to n-3:
 *    - Skip duplicates: if nums[i] == nums[i-1], continue
 *    - If nums[i] > 0: break (can't sum to 0 with all positives)
 *    - Two pointers: left = i+1, right = n-1
 *    - Find pairs summing to -nums[i]
 *    - Skip duplicates after each found pair
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [-4,-1,-1,0,1,2]  (after sort)
 *
 * i=0 (val=-4): target=4
 *   L=1(-1), R=5(2): sum=1 < 4 → L++
 *   L=2(-1), R=5(2): sum=1 < 4 → L++
 *   L=3(0),  R=5(2): sum=2 < 4 → L++
 *   L=4(1),  R=5(2): sum=3 < 4 → L++
 *   L=5 >= R → end
 *
 * i=1 (val=-1): target=1
 *   L=2(-1), R=5(2): sum=1 = 1 → add [-1,-1,2], L++,R--
 *   L=3(0),  R=4(1): sum=1 = 1 → add [-1,0,1],  L++,R--
 *   L=4 >= R → end
 *
 * i=2: nums[2]==nums[1]==-1 → skip
 * i=3 (val=0): target=0
 *   L=4(1),  R=5(2): sum=3 > 0 → R--
 *   L=4 >= R → end
 *
 * Result: [[-1,-1,2],[-1,0,1]] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n²) — O(n log n) sort + O(n) × O(n) two pointers
 * SPACE: O(1) extra (excluding output)
 */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            // Skip duplicate values for i
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // Optimization: if smallest possible triplet sum > 0
            if (nums[i] > 0) break;

            int left  = i + 1;
            int right = n - 1;
            int target = -nums[i];

            while (left < right) {
                int sum = nums[left] + nums[right];

                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates
                    while (left < right && nums[left]  == nums[left + 1])  left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }
};
```

---

### M2. Container With Most Water (LeetCode 11)

```cpp
/*
 * Problem: 11. Container With Most Water
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given n non-negative integers where each represents a vertical
 * line at position i with height height[i], find two lines that
 * together form a container that holds the most water.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Water held = width × min(height[L], height[R])
 * Width decreases as pointers move inward.
 *
 * KEY INSIGHT: When should we move a pointer?
 * If we move the TALLER side inward:
 *   - Width decreases
 *   - New min height ≤ old min height (still limited by shorter)
 *   - Area can only DECREASE → never beneficial
 *
 * Therefore: ALWAYS move the SHORTER side inward.
 * This gives us a chance to find a taller boundary that
 * compensates for the lost width.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * height = [1,8,6,2,5,4,8,3,7]
 *
 * L=0(h=1), R=8(h=7): area=1×1=1,  move L (shorter)
 * L=1(h=8), R=8(h=7): area=7×7=49, move R (shorter)
 * L=1(h=8), R=7(h=3): area=3×6=18, move R
 * L=1(h=8), R=6(h=8): area=8×5=40, move either (L)
 * L=2(h=6), R=6(h=8): area=6×4=24, move L
 * ...
 * max = 49 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left  = 0;
        int right = (int)height.size() - 1;
        int maxWater = 0;

        while (left < right) {
            int h     = min(height[left], height[right]);
            int width = right - left;
            maxWater  = max(maxWater, h * width);

            // Move the shorter side (the one limiting the water)
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxWater;
    }
};
```

---

### M3. 3Sum Closest (LeetCode 16)

```cpp
/*
 * Problem: 16. 3Sum Closest
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums and integer target, find three integers
 * whose sum is closest to target. Return the sum.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Same structure as 3Sum but instead of finding exact 0,
 * we track the closest sum to target.
 *
 * For each fixed i, two pointers find closest pair.
 * Move based on whether current sum is above/below target.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n²)
 * SPACE: O(1)
 */

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            int left  = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                // Update closest if this sum is nearer to target
                if (abs(sum - target) < abs(closest - target)) {
                    closest = sum;
                }

                if (sum < target) {
                    left++;   // Sum too small, increase it
                } else if (sum > target) {
                    right--;  // Sum too large, decrease it
                } else {
                    return sum;  // Exact match — can't get closer
                }
            }
        }

        return closest;
    }
};
```

---

### M4. Sort Colors (LeetCode 75) — Dutch National Flag

```cpp
/*
 * Problem: 75. Sort Colors
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an array with only 0s, 1s, and 2s,
 * sort it in-place in one pass without using sort library.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Dutch National Flag Algorithm
 *
 * Maintain three regions:
 * [0..low-1]   → all 0s (red)
 * [low..mid-1] → all 1s (white)
 * [mid..high]  → unexplored
 * [high+1..n-1]→ all 2s (blue)
 *
 * Process element at mid:
 * - 0 → swap with low, advance both low and mid
 * - 1 → already in correct region, advance mid
 * - 2 → swap with high, retreat high (don't advance mid!)
 *        Why? We don't know what came from high yet.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [2, 0, 2, 1, 1, 0]
 * low=0, mid=0, high=5
 *
 * mid=0: 2 → swap(0,5)=[0,0,2,1,1,2], high=4
 * mid=0: 0 → swap(0,0)=[0,0,2,1,1,2], low=1, mid=1
 * mid=1: 0 → swap(1,1)=[0,0,2,1,1,2], low=2, mid=2
 * mid=2: 2 → swap(2,4)=[0,0,1,1,2,2], high=3
 * mid=2: 1 → mid=3
 * mid=3: 1 → mid=4
 * mid=4 > high=3 → DONE
 *
 * Result: [0, 0, 1, 1, 2, 2] ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low  = 0;
        int mid  = 0;
        int high = (int)nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {   // nums[mid] == 2
                swap(nums[mid], nums[high]);
                high--;
                // DON'T increment mid — re-examine the swapped element
            }
        }
    }
};
```

---

### M5. Longest Mountain in Array (LeetCode 845)

```cpp
/*
 * Problem: 845. Longest Mountain in Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array arr, return the length of the longest
 * subarray that is a mountain (goes up then down, at least
 * one element on each side of the peak).
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Two-pointer expansion from each valley-to-peak transition:
 * Find each potential peak (arr[i-1] < arr[i] > arr[i+1]).
 * From the peak, expand left to find the start of the ascent
 * and right to find the end of the descent.
 *
 * Alternative: Single pass with left and right "slope" arrays.
 * Or direct two-pointer scan.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = nums.size();
        if (n < 3) return 0;

        int maxLen = 0;
        int i = 1;

        while (i < n - 1) {
            // Check if arr[i] is a peak
            if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1]) {
                int left  = i - 1;
                int right = i + 1;

                // Expand left while ascending
                while (left > 0 && arr[left - 1] < arr[left]) left--;

                // Expand right while descending
                while (right < n - 1 && arr[right] > arr[right + 1]) right++;

                maxLen = max(maxLen, right - left + 1);
                i = right;  // Jump to end of this mountain
            } else {
                i++;
            }
        }

        return maxLen;
    }
};
```

---

### M6. Subarray Product Less Than K (LeetCode 713)

```cpp
/*
 * Problem: 713. Subarray Product Less Than K
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given array nums and integer k, return the number of contiguous
 * subarrays where the product of all elements is strictly less than k.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sliding window with product:
 * - Expand right, multiply product
 * - If product >= k, shrink from left (divide)
 * - Every valid window ending at 'right' contributes
 *   (right - left + 1) new subarrays
 *   (each ending at right, starting at left, left+1, ..., right)
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [10, 5, 2, 6], k = 100
 *
 * right=0: prod=10 < 100, count += 0-0+1=1
 * right=1: prod=50 < 100, count += 1-0+1=2
 * right=2: prod=100 ≥ 100
 *   shrink: prod=100/10=10, left=1
 *           prod=10 < 100, count += 2-1+1=2
 * right=3: prod=10*6=60 < 100, count += 3-1+1=3
 *
 * Total = 1+2+2+3 = 8 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;  // Product is always >= 1

        int left    = 0;
        int product = 1;
        int count   = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            product *= nums[right];

            // Shrink window while product is too large
            while (product >= k) {
                product /= nums[left];
                left++;
            }

            // All subarrays [left..right], [left+1..right], ..., [right..right]
            count += right - left + 1;
        }

        return count;
    }
};
```

---

### M7. Longest Subarray of 1s After Deleting One Element (LeetCode 1493)

```cpp
/*
 * Problem: 1493. Longest Subarray of 1's After Deleting One Element
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given binary array nums, delete one element from it.
 * Return the size of the longest non-empty subarray containing
 * only 1s in the resulting array.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sliding window with at most ONE zero allowed.
 * Window is valid if it contains at most 1 zero.
 * When a second zero is encountered, shrink from left
 * until the first zero is removed.
 *
 * Answer = window size - 1 (we always "delete" one element)
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left    = 0;
        int zeros   = 0;
        int maxLen  = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            if (nums[right] == 0) zeros++;

            // More than 1 zero → shrink window
            while (zeros > 1) {
                if (nums[left] == 0) zeros--;
                left++;
            }

            // -1 because we must delete one element
            maxLen = max(maxLen, right - left);
        }

        return maxLen;
    }
};
```

---

### M8. Minimum Size Subarray Sum (LeetCode 209)

```cpp
/*
 * Problem: 209. Minimum Size Subarray Sum
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an array of positive integers nums and a positive integer
 * target, return the minimal length of a contiguous subarray of
 * which the sum is greater than or equal to target.
 * Return 0 if no such subarray exists.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Variable-size sliding window:
 * - Expand right to increase sum
 * - Once sum >= target: try to SHRINK from left
 *   (minimize the window while keeping sum valid)
 * - Track minimum window size
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [2,3,1,2,4,3], target = 7
 *
 * R=0: sum=2  < 7
 * R=1: sum=5  < 7
 * R=2: sum=6  < 7
 * R=3: sum=8  ≥ 7 → minLen=4, shrink: sum=6 < 7, left=1
 * R=4: sum=10 ≥ 7 → minLen=4, shrink: sum=7 ≥ 7, minLen=4, shrink: sum=4 < 7, left=3
 * R=5: sum=7  ≥ 7 → minLen=min(4,3)=3, shrink: sum=4 < 7, left=4
 *
 * Result: 2 (subarray [4,3]) ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) — each element added/removed at most once
 * SPACE: O(1)
 */

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left   = 0;
        int sum    = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < (int)nums.size(); right++) {
            sum += nums[right];

            // Shrink window while sum is sufficient
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return (minLen == INT_MAX) ? 0 : minLen;
    }
};
```

---

### M9. Bag of Tokens (LeetCode 948)

```cpp
/*
 * Problem: 948. Bag of Tokens
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * You have an initial power, a bag of tokens with different
 * values. You can play a token face-up (cost power, gain point)
 * or face-down (gain power, cost point). Maximize points.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Greedy + Two Pointers on sorted array:
 * - To gain a point cheaply: play the SMALLEST token (left)
 * - To gain power generously: sacrifice the LARGEST token (right)
 *
 * Greedily buy cheap tokens (to gain points),
 * sell expensive tokens (to gain power when stuck).
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(1)
 */

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());

        int left  = 0;
        int right = (int)tokens.size() - 1;
        int score = 0;
        int maxScore = 0;

        while (left <= right) {
            if (power >= tokens[left]) {
                // Can afford cheapest token → gain 1 point
                power -= tokens[left];
                score++;
                left++;
                maxScore = max(maxScore, score);
            } else if (score > 0) {
                // Can't afford any token but have points → trade point for power
                power += tokens[right];
                score--;
                right--;
            } else {
                break;  // No power, no points → stuck
            }
        }

        return maxScore;
    }
};
```

---

### M10. Boats to Save People (LeetCode 881)

```cpp
/*
 * Problem: 881. Boats to Save People
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given people[i] = weight of person i, and every boat can
 * carry at most 2 people with sum weight ≤ limit.
 * Return the minimum number of boats needed.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Greedy + Two Pointers on sorted array:
 * - Try to pair the HEAVIEST person with the LIGHTEST
 * - If they fit together → both board one boat
 * - If not → heaviest goes alone (can't pair with anyone lighter)
 *
 * This greedy works because pairing heaviest with lightest
 * minimizes wasted boat capacity.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * people = [1, 2, 2, 3], limit = 3 (after sort)
 *
 * L=1, R=3: 1+3=4 > 3 → heaviest goes alone, R--, boats=1
 * L=1, R=2: 1+2=3 = 3 → together, L++, R--, boats=2
 * L=2, R=2: L==R → one boat, boats=3
 *
 * Result: 3 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(1)
 */

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int left  = 0;
        int right = (int)people.size() - 1;
        int boats = 0;

        while (left <= right) {
            if (people[left] + people[right] <= limit) {
                // Lightest and heaviest can share
                left++;
            }
            // Heaviest always takes a boat (alone or shared)
            right--;
            boats++;
        }

        return boats;
    }
};
```

---

## Hard Problems

---

### H1. Trapping Rain Water (LeetCode 42)

```cpp
/*
 * Problem: 42. Trapping Rain Water
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given n non-negative integers representing an elevation map,
 * compute how much water it can trap after raining.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Water at position i = min(maxLeft[i], maxRight[i]) - height[i]
 *
 * Two-Pointer Approach (avoids O(n) space for prefix arrays):
 *
 * Key insight: Water level at any position is determined by
 * the SMALLER of the two boundaries.
 *
 * Maintain leftMax and rightMax as we go:
 * - If leftMax < rightMax:
 *   → water at left is guaranteed = leftMax - height[left]
 *     (right boundary is already taller, won't change min)
 *   → process left, advance left pointer
 * - Else:
 *   → process right, advance right pointer
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * height = [0,1,0,2,1,0,1,3,2,1,2,1]
 *
 * L=0, R=11, leftMax=0, rightMax=0
 *
 * h[0]=0: leftMax=0, leftMax≤rightMax → water=0-0=0,  L=1
 * h[1]=1: leftMax=1, leftMax>rightMax → water=0-1<0=0, R=10 wait
 *   actually leftMax=1, rightMax=max(0,h[11])=1, equal → process right
 *   h[11]=1, rightMax=1, water=1-1=0, R=10
 * ...continues...
 * Total water = 6 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int trap(vector<int>& height) {
        int left     = 0;
        int right    = (int)height.size() - 1;
        int leftMax  = 0;
        int rightMax = 0;
        int water    = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                // Left boundary is the limiting factor
                if (height[left] >= leftMax) {
                    leftMax = height[left];  // Update left max
                } else {
                    water += leftMax - height[left];  // Trap water
                }
                left++;
            } else {
                // Right boundary is the limiting factor
                if (height[right] >= rightMax) {
                    rightMax = height[right];  // Update right max
                } else {
                    water += rightMax - height[right];  // Trap water
                }
                right--;
            }
        }

        return water;
    }
};
```

---

### H2. 4Sum (LeetCode 18)

```cpp
/*
 * Problem: 18. 4Sum
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given array nums and target, return all unique quadruplets
 * [a,b,c,d] such that a + b + c + d = target.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Extend 3Sum: fix two outer pointers (i, j),
 * use two inner pointers for the last pair.
 *
 * Sort + skip duplicates at EVERY pointer level.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n³)
 * SPACE: O(1) extra
 */

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip dup i

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // skip dup j

                int left  = j + 1;
                int right = n - 1;
                long long need = (long long)target - nums[i] - nums[j];

                while (left < right) {
                    long long sum = (long long)nums[left] + nums[right];

                    if (sum == need) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});

                        while (left < right && nums[left]  == nums[left + 1])  left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;

                        left++;
                        right--;
                    } else if (sum < need) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }

        return result;
    }
};
```

---

### H3. Find K Closest Elements (LeetCode 658)

```cpp
/*
 * Problem: 658. Find K Closest Elements
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given sorted array arr, two integers k and x,
 * return the k closest integers to x in arr.
 * (Result should also be sorted)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Binary search to find window start, or two-pointer elimination.
 *
 * Two-pointer approach:
 * Start with the entire array [left=0, right=n-1].
 * Keep shrinking by eliminating the FARTHER endpoint:
 * - If |arr[left] - x| > |arr[right] - x|: arr[left] is farther → left++
 * - Else: arr[right] is farther → right--
 * Stop when window size == k.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n - k) two pointers, or O(log(n-k) + k) binary search
 * SPACE: O(1)
 */

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left  = 0;
        int right = (int)arr.size() - 1;

        // Eliminate n-k elements (one at a time from farther end)
        while (right - left + 1 > k) {
            if (abs(arr[left] - x) > abs(arr[right] - x)) {
                left++;   // Left is farther, remove it
            } else {
                right--;  // Right is farther (or equal), remove it
            }
        }

        return vector<int>(arr.begin() + left, arr.begin() + right + 1);
    }
};
```

---

### H4. Minimum Window Substring (LeetCode 76)

```cpp
/*
 * Problem: 76. Minimum Window Substring
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given strings s and t, return the minimum window substring
 * of s such that every character in t is included.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sliding window with character frequency tracking:
 * - Expand right until window contains all chars of t
 * - Then shrink left to minimize window (while still valid)
 * - Track minimum valid window throughout
 *
 * Use a 'formed' counter to know when window is valid.
 * A character "forms" when its window count reaches required count.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(|s| + |t|)
 * SPACE: O(|s| + |t|) for hashmaps
 */

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> need;
        for (char c : t) need[c]++;

        int required = need.size();   // Unique chars needed
        int formed   = 0;             // Unique chars currently satisfied

        unordered_map<char, int> window;
        int left   = 0;
        int minLen = INT_MAX;
        int minL   = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            char c = s[right];
            window[c]++;

            // Check if this char's requirement is now met
            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }

            // Try to shrink window while it remains valid
            while (formed == required && left <= right) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minL   = left;
                }

                char lc = s[left];
                window[lc]--;
                if (need.count(lc) && window[lc] < need[lc]) {
                    formed--;
                }
                left++;
            }
        }

        return (minLen == INT_MAX) ? "" : s.substr(minL, minLen);
    }
};
```

---

### H5. Sliding Window Maximum (LeetCode 239)

```cpp
/*
 * Problem: 239. Sliding Window Maximum
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums and window size k,
 * return an array of the maximum value in each sliding window.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Use a MONOTONIC DEQUE (decreasing order of values).
 * The deque stores INDICES (not values) in a window.
 *
 * Key invariant: deque front = index of maximum in current window
 *
 * For each new element right:
 * 1. Remove from BACK: pop all indices with smaller values
 *    (they can never be max while right is in window)
 * 2. Remove from FRONT: pop index if it's out of window (< right-k+1)
 * 3. Push right to back
 * 4. If window is full (right >= k-1): record front as max
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) — each element pushed/popped once
 * SPACE: O(k) for deque
 */

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;   // Stores indices, decreasing values
        vector<int> result;

        for (int right = 0; right < (int)nums.size(); right++) {
            // Remove indices that are out of the current window
            while (!dq.empty() && dq.front() < right - k + 1) {
                dq.pop_front();
            }

            // Maintain decreasing order: remove smaller elements from back
            while (!dq.empty() && nums[dq.back()] < nums[right]) {
                dq.pop_back();
            }

            dq.push_back(right);

            // Window is full: record the maximum (front of deque)
            if (right >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }

        return result;
    }
};
```

---

### H6. Subarrays with K Different Integers (LeetCode 992)

```cpp
/*
 * Problem: 992. Subarrays with K Different Integers
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums and integer k,
 * return the number of good subarrays (with exactly k distinct integers).
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * KEY TRICK: exactly(k) = atMost(k) - atMost(k-1)
 *
 * "At most k distinct" is easy with sliding window.
 * "Exactly k distinct" is hard directly.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(k)
 */

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

private:
    int atMost(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left  = 0;
        int count = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            freq[nums[right]]++;

            // Shrink if more than k distinct
            while ((int)freq.size() > k) {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0) freq.erase(nums[left]);
                left++;
            }

            count += right - left + 1;
        }

        return count;
    }
};
```

---

### H7. Max Consecutive Ones III (LeetCode 1004)

```cpp
/*
 * Problem: 1004. Max Consecutive Ones III
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given binary array nums and integer k,
 * return the max number of consecutive 1s if you can flip at most k 0s.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sliding window: allow at most k zeros in the window.
 * Window is valid while zeros ≤ k.
 * When zeros > k: shrink from left.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left  = 0;
        int zeros = 0;
        int maxLen = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            if (nums[right] == 0) zeros++;

            while (zeros > k) {
                if (nums[left] == 0) zeros--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
```

---

### H8. Number of Substrings Containing All Three Characters (LeetCode 1358)

```cpp
/*
 * Problem: 1358. Number of Substrings Containing All Three Characters
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a string s consisting only of 'a', 'b', 'c',
 * return the number of substrings containing at least one
 * occurrence of each of 'a', 'b', 'c'.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sliding window: find smallest window from left that has a,b,c.
 * Once found, ALL substrings extending to the right also valid.
 * → count += (n - right) for each valid left.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int numberOfSubstrings(string s) {
        int freq[3] = {0, 0, 0};  // a=0, b=1, c=2
        int left  = 0;
        int count = 0;
        int n     = s.size();

        for (int right = 0; right < n; right++) {
            freq[s[right] - 'a']++;

            // Shrink while window has all three chars
            while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
                // All substrings [left..right], [left..right+1], ..., [left..n-1] are valid
                count += n - right;
                freq[s[left] - 'a']--;
                left++;
            }
        }

        return count;
    }
};
```

---

### H9. Longest Substring with At Most K Distinct Characters (LeetCode 340)

```cpp
/*
 * Problem: 340. Longest Substring with At Most K Distinct Characters
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a string s and an integer k, return the length of the
 * longest substring that contains at most k distinct characters.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Classic variable sliding window with a HashMap.
 * Expand right freely, shrink left when distinct chars > k.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(k)
 */

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> freq;
        int left   = 0;
        int maxLen = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            freq[s[right]]++;

            while ((int)freq.size() > k) {
                freq[s[left]]--;
                if (freq[s[left]] == 0) freq.erase(s[left]);
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};
```

---

### H10. Palindrome Pairs (LeetCode 336)

```cpp
/*
 * Problem: 336. Palindrome Pairs
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a list of unique words, find all pairs of distinct
 * indices (i, j) such that words[i] + words[j] is a palindrome.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * For words[i] + words[j] to be palindrome, consider:
 * Case 1: words[j] = reverse(words[i])           → entire concatenation palindrome
 * Case 2: words[i] has extra prefix that is palindrome
 *         → prefix of words[i] is palindrome, suffix reversed = words[j]
 * Case 3: words[i] has extra suffix that is palindrome
 *         → suffix of words[i] is palindrome, prefix reversed = words[j]
 *
 * Use HashMap for O(1) reverse lookup.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n × k²) where k = max word length
 * SPACE: O(n × k) for hashmap
 */

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordIndex;
        for (int i = 0; i < (int)words.size(); i++) {
            wordIndex[words[i]] = i;
        }

        vector<vector<int>> result;

        for (int i = 0; i < (int)words.size(); i++) {
            string word = words[i];
            int n = word.size();

            for (int cut = 0; cut <= n; cut++) {
                string prefix = word.substr(0, cut);
                string suffix = word.substr(cut);

                // Case 1 & 2: prefix is palindrome, reverse(suffix) exists
                if (isPalin(prefix)) {
                    string revSuffix = suffix;
                    reverse(revSuffix.begin(), revSuffix.end());
                    if (wordIndex.count(revSuffix) && wordIndex[revSuffix] != i) {
                        result.push_back({wordIndex[revSuffix], i});
                    }
                }

                // Case 3: suffix is palindrome, reverse(prefix) exists
                // Avoid duplicates (cut=0 would repeat case 1 full reverse)
                if (cut != n && isPalin(suffix)) {
                    string revPrefix = prefix;
                    reverse(revPrefix.begin(), revPrefix.end());
                    if (wordIndex.count(revPrefix) && wordIndex[revPrefix] != i) {
                        result.push_back({i, wordIndex[revPrefix]});
                    }
                }
            }
        }

        return result;
    }

private:
    bool isPalin(const string& s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }
};
```

---

# PART 2 — Slow & Fast Pointers

---

## Intuition & Mental Model

Imagine two runners on a circular track:
- **Slow runner** takes 1 step per second
- **Fast runner** takes 2 steps per second

If the track is circular, the fast runner will eventually **lap** the slow runner — they WILL meet inside the cycle.

If the track is a straight line (no cycle), the fast runner reaches the end first and they never meet.

This is Floyd's Cycle Detection Algorithm and it powers an entire family of problems.

```
CYCLE DETECTION:

    1 → 2 → 3 → 4 → 5
                ↑   ↓
                8 ← 6
                    ↓
                    7

Step 0:  slow=1,  fast=1
Step 1:  slow=2,  fast=3   (fast moves 2 steps)
Step 2:  slow=3,  fast=5
Step 3:  slow=4,  fast=7
Step 4:  slow=5,  fast=5   ← THEY MEET! Cycle confirmed!

NO CYCLE:

    1 → 2 → 3 → 4 → null

Step 1:  slow=2,  fast=3
Step 2:  slow=3,  fast=null  ← fast hits null → no cycle
```

## The Four Core Applications

```
┌─────────────────────────────────────────────────────────────┐
│  Application         │ Speed    │ Key Property               │
├─────────────────────────────────────────────────────────────┤
│  Cycle Detection     │ 1x vs 2x │ Meet inside cycle          │
│  Middle of List      │ 1x vs 2x │ Fast at end → slow at mid  │
│  Nth from End        │ n gap    │ Fixed distance maintained   │
│  Cycle Start (Entry) │ 1x vs 2x │ Meet point + head = entry  │
└─────────────────────────────────────────────────────────────┘
```

---

## Core Patterns

### Pattern A: Cycle Detection

```cpp
// TEMPLATE: Detect cycle in linked list
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;           // Move 1 step
        fast = fast->next->next;     // Move 2 steps

        if (slow == fast) return true;  // Met → cycle!
    }

    return false;  // Fast hit null → no cycle
}
```

### Pattern B: Find Middle of List

```cpp
// TEMPLATE: Find middle node
// When fast reaches end, slow is at middle
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;  // Middle (or second middle for even length)
}

/*
 * For ODD  length: 1 → 2 → 3 → 4 → 5
 *                              ^slow (index 2, true middle)
 *
 * For EVEN length: 1 → 2 → 3 → 4
 *                          ^slow (index 2, second of two middles)
 *
 * For first middle of even: stop when fast->next == null
 * while (fast->next && fast->next->next)
 */
```

### Pattern C: Nth Node From End

```cpp
// TEMPLATE: Remove Nth from end
// Move fast n steps ahead, then move both until fast hits end
ListNode* nthFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    ListNode* slow = head;

    // Advance fast by n steps
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    // Move both until fast reaches end
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;  // Nth from end
}
```

### Pattern D: Find Cycle Start

```cpp
// TEMPLATE: Find where cycle begins
// Phase 1: Detect cycle (find meeting point)
// Phase 2: Reset one pointer to head, move both at speed 1
//          → they meet at cycle entry point
ListNode* detectCycleStart(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Phase 1: Find meeting point
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (fast == nullptr || fast->next == nullptr) return nullptr;

    // Phase 2: Find cycle start
    slow = head;  // Reset slow to head
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;  // Now fast also moves 1 step
    }

    return slow;  // Both point to cycle start
}
```

### Why Phase 2 Works — Mathematical Proof

```
Let:
  F = distance from head to cycle start
  C = cycle length
  k = distance from cycle start to meeting point

After Phase 1, slow traveled: F + k
Fast traveled: F + k + m×C (m full cycles extra)

Since fast = 2 × slow:
  2(F + k) = F + k + m×C
  F + k = m×C
  F = m×C - k

When slow is reset to head and both move at speed 1:
  Slow travels F to reach cycle start
  Fast travels m×C - k = F from meeting point
  → Both arrive at cycle start simultaneously! ✅
```

---

## Easy Problems

---

### E1. Linked List Cycle (LeetCode 141)

```cpp
/*
 * Problem: 141. Linked List Cycle
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list, determine if it has a cycle.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Two runners on a track
 *
 * If a cycle exists, fast runner MUST eventually lap slow runner.
 * If no cycle, fast runner reaches the end (null).
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 3 → 2 → 0 → -4 → (back to 2)
 *
 * Step 0: slow=3, fast=3
 * Step 1: slow=2, fast=0   (fast: 3→2→0)
 * Step 2: slow=0, fast=2   (fast: 0→-4→2)
 * Step 3: slow=-4, fast=-4 ← MEET! cycle exists ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) return true;
        }

        return false;
    }
};
```

---

### E2. Middle of the Linked List (LeetCode 876)

```cpp
/*
 * Problem: 876. Middle of the Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a singly linked list, return the middle node.
 * If there are two middle nodes, return the SECOND middle node.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Fast pointer moves twice as fast.
 * When fast reaches end → slow is at middle.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * [1, 2, 3, 4, 5]
 *
 * Start: slow=1, fast=1
 * Step 1: slow=2, fast=3
 * Step 2: slow=3, fast=5
 * fast->next=null → stop, return slow=3 ✅
 *
 * [1, 2, 3, 4, 5, 6]
 *
 * Start: slow=1, fast=1
 * Step 1: slow=2, fast=3
 * Step 2: slow=3, fast=5
 * Step 3: slow=4, fast=null (6->next=null) → stop, return slow=4 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
```

---

### E3. Palindrome Linked List (LeetCode 234)

```cpp
/*
 * Problem: 234. Palindrome Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a singly linked list, return true if it
 * is a palindrome, or false otherwise.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Phase 1: Find middle (slow-fast pointers)
 * Phase 2: Reverse second half
 * Phase 3: Compare first half and reversed second half
 * Phase 4: (Optional) Restore list
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * List: 1 → 2 → 2 → 1
 *
 * Phase 1: Find middle
 * slow=1, fast=1 → slow=2(idx1), fast=2(idx2) → slow=2(idx2), fast=null
 * Middle = 2 (second half starts at index 2)
 *
 * Phase 2: Reverse second half [2, 1] → [1, 2]
 *
 * Phase 3: Compare
 * First:  1 → 2
 * Second: 1 → 2
 * All match → true ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        // Phase 1: Find middle using slow-fast
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Phase 2: Reverse second half
        ListNode* secondHalf = reverseList(slow->next);

        // Phase 3: Compare both halves
        ListNode* p1 = head;
        ListNode* p2 = secondHalf;
        bool isPalin = true;

        while (p2 != nullptr) {
            if (p1->val != p2->val) {
                isPalin = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // Phase 4: Restore (good practice)
        slow->next = reverseList(secondHalf);

        return isPalin;
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};
```

---

### E4. Remove Duplicates from Sorted List (LeetCode 83)

```cpp
/*
 * Problem: 83. Remove Duplicates from Sorted List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a sorted linked list, delete all duplicates
 * such that each element appears only once.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Two pointers (current, next):
 * If current.val == current.next.val → skip the next node
 * Else → advance current
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 1 → 1 → 2 → 3 → 3
 *
 * curr=1: next=1, same → curr.next = 1.next=2
 * curr=1: next=2, diff → curr = 2
 * curr=2: next=3, diff → curr = 3
 * curr=3: next=3, same → curr.next = 3.next=null
 * curr=3: next=null → stop
 *
 * Result: 1 → 2 → 3 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;

        while (curr != nullptr && curr->next != nullptr) {
            if (curr->val == curr->next->val) {
                curr->next = curr->next->next;  // Skip duplicate
            } else {
                curr = curr->next;  // Advance
            }
        }

        return head;
    }
};
```

---

### E5. Happy Number (LeetCode 202)

```cpp
/*
 * Problem: 202. Happy Number
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * A happy number is defined by the process:
 * - Replace number with sum of squares of its digits
 * - Repeat until number = 1 (happy) or enters a cycle (not happy)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * This is a CYCLE DETECTION problem in disguise!
 * The sequence of numbers either:
 * - Reaches 1 (happy)
 * - Enters a cycle (unhappy)
 *
 * Use Floyd's cycle detection:
 * - Slow: one step (one digit-square-sum)
 * - Fast: two steps
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * n = 19
 * 19 → 1²+9²=82 → 8²+2²=68 → 6²+8²=100 → 1²+0+0=1 ✅ Happy
 *
 * n = 4
 * 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 (cycle!) → unhappy
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(log n)
 * SPACE: O(1)
 */

class Solution {
public:
    bool isHappy(int n) {
        int slow = n;
        int fast = n;

        do {
            slow = digitSquareSum(slow);               // 1 step
            fast = digitSquareSum(digitSquareSum(fast)); // 2 steps
        } while (slow != fast);

        return slow == 1;  // Cycle at 1 → happy; any other cycle → unhappy
    }

private:
    int digitSquareSum(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
};
```

---

### E6. Find the Duplicate Number (LeetCode 287) — Easy entry, Hard variant

```cpp
/*
 * Problem: 287. Find the Duplicate Number
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given array nums of n+1 integers where each integer is in [1,n],
 * there is only ONE repeated number. Find it.
 * Cannot modify array. Must use O(1) space.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Floyd's Cycle Detection on array as linked list
 *
 * Treat the array as a linked list where:
 * - node i points to node nums[i]
 * - Since a value is repeated, two different indices point to
 *   the same node → cycle!
 *
 * The CYCLE ENTRY = the duplicate number.
 *
 * Phase 1: Find meeting point (cycle exists because of duplicate)
 * Phase 2: Find cycle entry (= duplicate)
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [1, 3, 4, 2, 2]
 * index:   0  1  2  3  4
 *
 * Treat as: 0→1→3→2→4→2→4→2→... (cycle at 2!)
 *
 * Phase 1:
 * slow=0→1, fast=0→3
 * slow=1→3, fast=3→4→2 → fast=2
 * slow=3→2, fast=2→4   → ...
 * slow=2,   fast=2      ← MEET at 2
 *
 * Phase 2: Reset slow to 0
 * slow=0→1, fast=2→4
 * slow=1→3, fast=4→2
 * slow=3→2, fast=2→4
 * slow=2,   fast=2 → wait actually...
 *           (both converge at entry = 2) ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Phase 1: Detect cycle
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find entry point (duplicate)
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
```

---

### E7. Intersection of Two Linked Lists (LeetCode 160)

```cpp
/*
 * Problem: 160. Intersection of Two Linked Lists
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given heads of two linked lists, return the node where they intersect.
 * Return null if they don't intersect.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Two-pointer path switching
 *
 * Let a = length of list A before intersection
 * Let b = length of list B before intersection
 * Let c = length of common tail
 *
 * pA travels: a + c + b (then meets pB at intersection)
 * pB travels: b + c + a (then meets pA at intersection)
 * Both travel a+b+c total → meet at intersection! ✅
 *
 * If no intersection: both reach null at same time.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * A: 4 → 1 → 8 → 4 → 5
 * B:      5 → 6 → 1 → 8 → 4 → 5
 *
 * pA: 4,1,8,4,5,null → 5,6,1,8...
 * pB: 5,6,1,8,4,5,null → 4,1,8...
 * Both reach node(8) simultaneously ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m + n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (!headA || !headB) return nullptr;

        ListNode* pA = headA;
        ListNode* pB = headB;

        // When a pointer reaches end, redirect to other list's head
        while (pA != pB) {
            pA = (pA == nullptr) ? headB : pA->next;
            pB = (pB == nullptr) ? headA : pB->next;
        }

        return pA;  // Either intersection node, or null
    }
};
```

---

### E8. Reorder List (LeetCode 143)

```cpp
/*
 * Problem: 143. Reorder List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given list L0→L1→…→Ln-1→Ln, reorder it to:
 * L0→Ln→L1→Ln-1→L2→Ln-2→…
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Three steps:
 * 1. Find middle using slow-fast pointers
 * 2. Reverse the second half
 * 3. Merge the two halves (interleaving)
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 1 → 2 → 3 → 4 → 5
 *
 * Step 1: Middle = 3. First half: 1→2→3. Second half: 4→5
 * Step 2: Reverse second half: 5→4
 * Step 3: Merge: 1→5→2→4→3 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half
        ListNode* secondHalf = reverseList(slow->next);
        slow->next = nullptr;  // Split the list

        // Step 3: Merge the two halves
        ListNode* p1 = head;
        ListNode* p2 = secondHalf;

        while (p2 != nullptr) {
            ListNode* next1 = p1->next;
            ListNode* next2 = p2->next;

            p1->next = p2;
            p2->next = next1;

            p1 = next1;
            p2 = next2;
        }
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
```

---

### E9. Delete N nodes after M nodes of a Linked List (LeetCode 1474)

```cpp
/*
 * Problem: 1474. Delete N Nodes After M Nodes of a Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list and two integers m and n,
 * traverse the linked list and remove some nodes.
 * Keep m nodes, delete n nodes, repeatedly until end.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Two-pointer style traversal:
 * - Keep pointer moves m steps forward (keeping nodes)
 * - Delete pointer moves n steps forward (counting deletions)
 * - After deletion, relink to continue
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode* curr = head;

        while (curr != nullptr) {
            // Keep m nodes
            for (int i = 1; i < m && curr != nullptr; i++) {
                curr = curr->next;
            }

            if (curr == nullptr) break;

            // Delete n nodes
            ListNode* tail = curr;
            for (int i = 0; i < n && tail != nullptr; i++) {
                tail = tail->next;
            }

            // Relink
            curr->next = (tail != nullptr) ? tail->next : nullptr;
            curr = curr->next;
        }

        return head;
    }
};
```

---

### E10. Check If a String Is a Valid Sequence (Floyd-style on array)

```cpp
/*
 * Problem: Is Array a Subsequence of Another (Variant)
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Check if arr is a valid sequence of a binary tree at a given
 * root (traversal). Here we demonstrate slow-fast on arrays.
 *
 * Application: Counting elements using step pointers.
 *
 * ─────────────────────────────────────────────────────────
 * FLOYD'S ON ARRAY — Detect cycle in number sequence
 *
 * f(x) = nums[x]
 * Find cycle start in the sequence x → f(x) → f(f(x)) → ...
 */

// Demonstration: Count array elements that are "self-referential"
// i.e., nums[nums[i]] == i (pointing back to themselves)
int countSelfReferential(vector<int>& nums) {
    int count = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] < (int)nums.size() && nums[nums[i]] == i) {
            count++;
        }
    }
    return count;
}
```

---

## Medium Problems

---

### M1. Linked List Cycle II (LeetCode 142)

```cpp
/*
 * Problem: 142. Linked List Cycle II
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a linked list, return the node where the cycle begins.
 * If no cycle, return null.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Floyd's Algorithm Phase 1 + Phase 2
 *
 * Phase 1: Find meeting point (proof already shown above)
 * Phase 2: Reset one pointer to head.
 *          Move BOTH at speed 1. They meet at cycle start.
 *
 * MATHEMATICAL PROOF:
 * Let F = distance head to cycle start
 * Let a = distance cycle start to meeting point
 * Let C = cycle length
 *
 * slow total = F + a
 * fast total = F + a + nC
 * 2(F+a) = F + a + nC
 * F + a = nC
 * F = nC - a
 *
 * After reset: slow from head moves F steps.
 *              fast from meeting point moves F = nC - a steps
 *              → fast completes remaining cycle to reach start.
 * Both reach cycle start simultaneously.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Phase 1: Detect cycle
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // Phase 2: Find cycle start
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;  // Cycle start
            }
        }

        return nullptr;  // No cycle
    }
};
```

---

### M2. Remove Nth Node From End of List (LeetCode 19)

```cpp
/*
 * Problem: 19. Remove Nth Node From End of List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list, remove the nth node from
 * the end of the list and return its head.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Create a gap of n between fast and slow.
 * When fast reaches null, slow is AT the target node.
 * We need the node BEFORE target to delete, so:
 * Use a dummy node and let fast start n+1 steps ahead.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * List: 1→2→3→4→5, n=2
 * dummy→1→2→3→4→5
 *
 * Advance fast n+1=3 steps from dummy:
 * fast = dummy → 1 → 2 → 3 (fast points to node 3)
 *
 * Move both until fast->next = null:
 * slow=dummy→1, fast=3→4
 * slow=1→2,    fast=4→5
 * slow=2→3,    fast=5→null stop
 *
 * slow is at node 3 (node BEFORE 4th node, which is 2nd from end)
 * slow->next = slow->next->next → remove node 4
 *
 * Result: 1→2→3→5 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Advance fast by n+1 steps
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // Move both until fast hits null
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        // Delete the target node
        slow->next = slow->next->next;

        return dummy.next;
    }
};
```

---

### M3. Sort List (LeetCode 148)

```cpp
/*
 * Problem: 148. Sort List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list, sort it in O(n log n) time
 * using O(1) space (constant extra memory).
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Merge Sort on Linked List
 *
 * Step 1: Find middle using slow-fast pointers → split into two halves
 * Step 2: Recursively sort each half
 * Step 3: Merge the two sorted halves
 *
 * Middle finding is the key slow-fast application here.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n) — mergesort
 * SPACE: O(log n) recursion stack, O(1) if iterative
 */

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // Step 1: Find middle and split
        ListNode* mid   = findMiddle(head);
        ListNode* right = mid->next;
        mid->next = nullptr;  // Split

        // Step 2: Recursively sort
        ListNode* leftSorted  = sortList(head);
        ListNode* rightSorted = sortList(right);

        // Step 3: Merge
        return merge(leftSorted, rightSorted);
    }

private:
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Move to first middle (for even: first of two middles)
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }

        curr->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
```

---

### M4. Rotate List (LeetCode 61)

```cpp
/*
 * Problem: 61. Rotate List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list, rotate the list to the right by k places.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * A right rotation by k means the last k nodes move to the front.
 * Find the (n-k)th node (new tail) using slow-fast gap technique:
 *
 * 1. Find length n
 * 2. k = k % n (avoid full rotations)
 * 3. Find (n-k-1)th node: the new tail
 * 4. New head = new_tail->next
 * 5. Connect old tail to old head
 * 6. Cut at new tail
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 1→2→3→4→5, k=2
 * n=5, k=2 (no change since 2<5)
 * New tail is at position n-k-1=2 (0-indexed) = node 3
 * New head = node 4
 * Connect 5 to 1
 * Cut after 3: 3->next = null
 *
 * Result: 4→5→1→2→3 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // Find length and tail
        ListNode* tail = head;
        int n = 1;
        while (tail->next) {
            tail = tail->next;
            n++;
        }

        k = k % n;
        if (k == 0) return head;

        // Find new tail (n-k-1 steps from head)
        ListNode* newTail = head;
        for (int i = 0; i < n - k - 1; i++) {
            newTail = newTail->next;
        }

        // Rearrange
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;
        tail->next = head;

        return newHead;
    }
};
```

---

### M5. Linked List Random Node (LeetCode 382) — Reservoir Sampling

```cpp
/*
 * Problem: 382. Linked List Random Node
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a singly-linked list, return a random node's value.
 * Each node must have equal probability of being chosen.
 * (Unknown length)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Reservoir Sampling
 *
 * Process nodes one at a time. For node i (1-indexed):
 * Replace current selection with probability 1/i.
 *
 * This ensures every node has equal 1/n probability.
 *
 * Uses one pointer scanning through — slow pointer variant.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) per call
 * SPACE: O(1)
 */

class Solution {
    ListNode* head;
public:
    Solution(ListNode* head) : head(head) {}

    int getRandom() {
        ListNode* curr = head;
        int chosen = curr->val;
        int i = 1;

        while (curr->next) {
            curr = curr->next;
            i++;
            // Replace with probability 1/i
            if (rand() % i == 0) {
                chosen = curr->val;
            }
        }

        return chosen;
    }
};
```

---

### M6. Odd Even Linked List (LeetCode 328)

```cpp
/*
 * Problem: 328. Odd Even Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a singly linked list, group all nodes
 * with odd indices together followed by even indices.
 * (1-indexed, preserve relative order within each group)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Two pointers advancing at the same speed but on alternating nodes:
 * - odd pointer: 1st, 3rd, 5th... nodes
 * - even pointer: 2nd, 4th, 6th... nodes
 *
 * Connect odds chain to even chain at the end.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 1 → 2 → 3 → 4 → 5
 * odd=1, even=2, evenHead=2
 *
 * iter 1: odd=1→3, even=2→4
 * iter 2: odd=3→5, even=4→null
 * even is null → stop
 * odd(5)->next = evenHead(2)
 *
 * Result: 1→3→5→2→4 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* odd      = head;
        ListNode* even     = head->next;
        ListNode* evenHead = even;  // Save even head for reconnection

        while (even != nullptr && even->next != nullptr) {
            odd->next  = even->next;    // Link to next odd
            odd        = odd->next;

            even->next = odd->next;     // Link to next even
            even       = even->next;
        }

        odd->next = evenHead;  // Connect odd chain to even chain

        return head;
    }
};
```

---

### M7. Longest Substring Without Repeating Characters (LeetCode 3) — Slow-Fast on String

```cpp
/*
 * Problem: 3. Longest Substring Without Repeating Characters
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a string s, find the length of the longest substring
 * without repeating characters.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Slow-Fast pointers on string
 *
 * - Slow pointer (left): start of current valid window
 * - Fast pointer (right): always expanding
 * - When duplicate found at right: advance slow past previous occurrence
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(min(n, alphabet))
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastSeen;
        int slow   = 0;  // Left boundary of window
        int maxLen = 0;

        for (int fast = 0; fast < (int)s.size(); fast++) {
            char c = s[fast];

            // If char seen and within window, jump slow forward
            if (lastSeen.count(c) && lastSeen[c] >= slow) {
                slow = lastSeen[c] + 1;
            }

            lastSeen[c] = fast;
            maxLen = max(maxLen, fast - slow + 1);
        }

        return maxLen;
    }
};
```

---

### M8. Maximum Twin Sum of a Linked List (LeetCode 2130)

```cpp
/*
 * Problem: 2130. Maximum Twin Sum of a Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * In a linked list of even length n, the twin of node i is
 * node (n-1-i). Return the maximum twin sum.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Twins are symmetric: first↔last, second↔second-last, etc.
 * 1. Find middle (slow-fast)
 * 2. Reverse second half
 * 3. Pair-sum first half with reversed second half
 * 4. Track maximum
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int pairSum(ListNode* head) {
        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // Step 3: Find max twin sum
        ListNode* p1 = head;
        ListNode* p2 = prev;  // Head of reversed second half
        int maxSum = 0;

        while (p2) {
            maxSum = max(maxSum, p1->val + p2->val);
            p1 = p1->next;
            p2 = p2->next;
        }

        return maxSum;
    }
};
```

---

### M9. Swapping Nodes in a Linked List (LeetCode 1721)

```cpp
/*
 * Problem: 1721. Swapping Nodes in a Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a linked list head and integer k, swap the values of
 * the kth node from the beginning and kth node from the end.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Find kth from beginning: advance k steps from head.
 * Find kth from end: use slow-fast gap of k.
 * Then just swap values (no actual node movement needed).
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* front = head;  // kth from beginning
        ListNode* back  = head;  // kth from end

        // Advance front k steps
        for (int i = 1; i < k; i++) {
            front = front->next;
        }

        // Use gap to find kth from end
        ListNode* curr = front->next;
        while (curr != nullptr) {
            back = back->next;
            curr = curr->next;
        }

        // Swap values (not nodes)
        swap(front->val, back->val);

        return head;
    }
};
```

---

### M10. Circular Array Loop (LeetCode 457)

```cpp
/*
 * Problem: 457. Circular Array Loop
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * You have a circular array nums. A cycle exists if:
 * - Same direction (all positive or all negative in cycle)
 * - Length > 1
 * Return true if any such cycle exists.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Apply Floyd's cycle detection to each starting position.
 * next(i) = (i + nums[i] + n) % n
 *
 * A valid cycle must:
 * - All moves in same direction (same sign)
 * - Length > 1 (no self-loops)
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();

        auto next = [&](int i) {
            return ((i + nums[i]) % n + n) % n;
        };

        for (int i = 0; i < n; i++) {
            int slow = i;
            int fast = i;

            // Check same direction
            while (nums[slow] * nums[fast] > 0 &&
                   nums[slow] * nums[next(fast)] > 0) {
                slow = next(slow);
                fast = next(next(fast));

                if (slow == fast) {
                    // Check cycle length > 1
                    if (slow == next(slow)) break;  // Self-loop
                    return true;
                }
            }
        }

        return false;
    }
};
```

---

## Hard Problems

---

### H1. Find the Duplicate Number — O(1) Space (LeetCode 287)

```cpp
/*
 * Full Floyd's solution already shown in Easy section (E6).
 * Here we extend it to count duplicates with follow-up constraints.
 *
 * FOLLOW-UP: What if there can be multiple duplicates?
 * → Use bit manipulation or counting sort (different approach)
 *
 * This is the definitive Floyd's on array implementation.
 */

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Phase 1: Find intersection point
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find cycle entrance
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
```

---

### H2. Reverse Nodes in k-Group (LeetCode 25)

```cpp
/*
 * Problem: 25. Reverse Nodes in k-Group
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list, reverse the nodes of the
 * list k at a time, and return the modified list.
 * If remaining nodes < k, leave them as is.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Use a "fast" pointer to check if k nodes exist.
 * If yes, reverse the k-group and recurse on remainder.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * 1→2→3→4→5, k=2
 *
 * Group 1: [1,2] → reverse → [2,1], then process 3→4→5
 * Group 2: [3,4] → reverse → [4,3], then process 5
 * Remainder: [5] < k → leave as is
 *
 * Result: 2→1→4→3→5 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(n/k) recursion
 */

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // Check if k nodes exist
        ListNode* check = head;
        for (int i = 0; i < k; i++) {
            if (!check) return head;  // Fewer than k nodes, return as-is
            check = check->next;
        }

        // Reverse k nodes
        ListNode* prev = nullptr;
        ListNode* curr = head;
        for (int i = 0; i < k; i++) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // head is now the tail of reversed group
        // Recursively process remaining
        head->next = reverseKGroup(curr, k);

        return prev;  // New head of this group
    }
};
```

---

### H3. Split Linked List in Parts (LeetCode 725)

```cpp
/*
 * Problem: 725. Split Linked List in Parts
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given the head of a linked list and integer k,
 * split the list into k consecutive parts. Parts that are
 * shorter come AFTER longer parts. Return array of k parts.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Step 1: Find total length n with one pointer pass
 * Step 2: base = n/k, extra = n%k
 *         First 'extra' parts have (base+1) nodes
 *         Remaining parts have 'base' nodes
 * Step 3: Use pointer to cut and collect each part
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n + k)
 * SPACE: O(k) for result
 */

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // Find length
        int n = 0;
        ListNode* curr = head;
        while (curr) { n++; curr = curr->next; }

        int base  = n / k;
        int extra = n % k;

        vector<ListNode*> result(k, nullptr);
        curr = head;

        for (int i = 0; i < k && curr; i++) {
            result[i] = curr;
            int partSize = base + (i < extra ? 1 : 0);

            for (int j = 0; j < partSize - 1; j++) {
                curr = curr->next;
            }

            ListNode* next = curr->next;
            curr->next = nullptr;  // Cut
            curr = next;
        }

        return result;
    }
};
```

---

### H4. Merge k Sorted Lists (LeetCode 23)

```cpp
/*
 * Problem: 23. Merge k Sorted Lists
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an array of k linked lists, each sorted in ascending
 * order, merge all lists into one sorted list.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Divide and Conquer with merge (slow-fast style)
 *
 * Instead of merging one by one (O(kn) total),
 * use merge sort approach: pair-wise merge lists.
 * Halve the problem at each step → O(n log k)
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log k) where n = total nodes
 * SPACE: O(log k) recursion
 */

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeRange(lists, 0, (int)lists.size() - 1);
    }

private:
    ListNode* mergeRange(vector<ListNode*>& lists, int lo, int hi) {
        if (lo == hi) return lists[lo];

        int mid = lo + (hi - lo) / 2;
        ListNode* left  = mergeRange(lists, lo, mid);
        ListNode* right = mergeRange(lists, mid + 1, hi);
        return mergeTwoLists(left, right);
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (l1 && l2) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }

        curr->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
```

---

### H5. Flatten a Multilevel Doubly Linked List (LeetCode 430)

```cpp
/*
 * Problem: 430. Flatten a Multilevel Doubly Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * A doubly linked list node also has a 'child' pointer.
 * Flatten all the child levels into a single-level doubly linked list.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: DFS with two pointers (curr, next)
 *
 * When we find a node with child:
 * 1. Save next
 * 2. Attach child after curr
 * 3. Find tail of child chain
 * 4. Attach saved next after tail
 * 5. Continue scanning
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) total nodes
 * SPACE: O(1)
 */

class Solution {
public:
    Node* flatten(Node* head) {
        Node* curr = head;

        while (curr) {
            if (curr->child) {
                Node* child     = curr->child;
                Node* next      = curr->next;

                // Connect curr to child
                curr->next  = child;
                child->prev = curr;
                curr->child = nullptr;

                // Find tail of child chain
                Node* tail = child;
                while (tail->next) tail = tail->next;

                // Connect tail to saved next
                tail->next = next;
                if (next) next->prev = tail;
            }

            curr = curr->next;
        }

        return head;
    }
};
```

---

### H6. LRU Cache (LeetCode 146)

```cpp
/*
 * Problem: 146. LRU Cache
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Design a data structure that follows the LRU (Least Recently Used)
 * cache eviction policy. Implement get and put in O(1).
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Doubly Linked List + HashMap
 *
 * Doubly linked list: O(1) insertion/deletion anywhere
 * HashMap: O(1) lookup by key
 *
 * Keep head = most recently used, tail = least recently used
 * On every get/put: move accessed node to head
 * On overflow: remove tail node
 *
 * Two special sentinel nodes (dummy head, dummy tail) simplify edge cases.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(1) for get and put
 * SPACE: O(capacity)
 */

class LRUCache {
    struct Node {
        int key, val;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    int cap;
    unordered_map<int, Node*> map;
    Node* head;  // Dummy: most recent side
    Node* tail;  // Dummy: least recent side

    void insertFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!map.count(key)) return -1;

        Node* node = map[key];
        removeNode(node);
        insertFront(node);
        return node->val;
    }

    void put(int key, int value) {
        if (map.count(key)) {
            Node* node = map[key];
            node->val = value;
            removeNode(node);
            insertFront(node);
        } else {
            Node* node = new Node(key, value);
            map[key] = node;
            insertFront(node);

            if ((int)map.size() > cap) {
                Node* lru = tail->prev;
                removeNode(lru);
                map.erase(lru->key);
                delete lru;
            }
        }
    }
};
```

---

### H7. Copy List with Random Pointer (LeetCode 138)

```cpp
/*
 * Problem: 138. Copy List with Random Pointer
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * A linked list of nodes has a random pointer. Make a deep copy.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pass with interleaving (O(1) space)
 *
 * Pass 1: Interleave copies between original nodes
 *         1 → 1' → 2 → 2' → 3 → 3'
 * Pass 2: Set random pointers for copies
 *         node->next->random = node->random->next
 * Pass 3: Separate the two lists
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1) — or O(n) with HashMap approach
 */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Pass 1: Interleave copies
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // Pass 2: Set random pointers
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // Pass 3: Separate lists
        curr = head;
        Node* copyHead = head->next;
        Node* copyCurr = copyHead;

        while (curr) {
            curr->next = copyCurr->next;
            curr = curr->next;
            if (curr) {
                copyCurr->next = curr->next;
                copyCurr = copyCurr->next;
            }
        }

        return copyHead;
    }
};
```

---

### H8. Design Linked List (LeetCode 707)

```cpp
/*
 * Problem: 707. Design Linked List
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Design and implement a linked list.
 * Implement get, addAtHead, addAtTail, addAtIndex, deleteAtIndex.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Doubly linked list with sentinel nodes
 *
 * Dummy head and tail simplify boundary conditions.
 * Any operation uses pointer traversal.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n) for index-based operations, O(1) for head/tail
 * SPACE: O(n)
 */

class MyLinkedList {
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int v) : val(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;  // Dummy head
    Node* tail;  // Dummy tail
    int size;

public:
    MyLinkedList() {
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* curr = head->next;
        for (int i = 0; i < index; i++) curr = curr->next;
        return curr->val;
    }

    void addAtHead(int val) { addBetween(head, head->next, val); }
    void addAtTail(int val) { addBetween(tail->prev, tail, val); }

    void addAtIndex(int index, int val) {
        if (index > size) return;
        Node* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        addBetween(curr, curr->next, val);
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        Node* curr = head->next;
        for (int i = 0; i < index; i++) curr = curr->next;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
    }

private:
    void addBetween(Node* prev, Node* next, int val) {
        Node* node = new Node(val);
        node->prev = prev;
        node->next = next;
        prev->next = node;
        next->prev = node;
        size++;
    }
};
```

---

### H9. Linked List in Binary Tree (LeetCode 1367)

```cpp
/*
 * Problem: 1367. Linked List in Binary Tree
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a linked list and binary tree, return true if all
 * linked list values appear as a downward path in the tree.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: DFS on tree with slow-fast style matching
 *
 * For each tree node, try starting a match.
 * Use a helper that matches from current list node and tree node.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(T × L) where T = tree nodes, L = list length
 * SPACE: O(H + L) where H = tree height
 */

class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!root) return false;

        return match(head, root) ||
               isSubPath(head, root->left) ||
               isSubPath(head, root->right);
    }

private:
    bool match(ListNode* list, TreeNode* tree) {
        if (!list) return true;   // All list nodes matched
        if (!tree) return false;  // Tree ended before list
        if (list->val != tree->val) return false;

        return match(list->next, tree->left) ||
               match(list->next, tree->right);
    }
};
```

---

### H10. First Missing Positive (LeetCode 41) — Pointer-based cycle sort

```cpp
/*
 * Problem: 41. First Missing Positive
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given unsorted integer array nums, return the smallest missing
 * positive integer. Must run in O(n) time and O(1) space.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Cycle Sort with read-write pointers
 *
 * Positive integers in range [1, n] should be at index [0, n-1].
 * Place nums[i] at index nums[i]-1 (cycle sort).
 * Then scan for first position where nums[i] != i+1.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [3, 4, -1, 1]
 *
 * Cycle sort:
 * i=0: 3 should be at idx 2 → swap(0,2) → [-1,4,3,1]
 * i=0: -1 < 1, skip
 * i=1: 4 should be at idx 3 → swap(1,3) → [-1,1,3,4]
 * i=1: 1 should be at idx 0 → swap(1,0) → [1,-1,3,4]
 * i=1: -1 < 1, skip
 * i=2: 3 at idx 2 ✓
 * i=3: 4 at idx 3 ✓
 *
 * Scan: idx0=1✓, idx1=-1≠2 → answer = 2 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        // Cycle sort: place each value at its correct index
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n &&
                   nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // Find first missing
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) return i + 1;
        }

        return n + 1;  // All [1..n] present, missing is n+1
    }
};
```

---

# PART 3 — Three Pointers

---

## Intuition & Mental Model

Three pointers go beyond the two-pointer paradigm when you need to:
- Fix one element and search for a pair (3Sum family)
- Partition into three regions simultaneously (Dutch Flag)
- Maintain a leading, middle, and trailing position at once
- Merge three or more sorted sequences

Think of three pointers as controlling **three simultaneous constraints**.

```
THREE-REGION PARTITION (Dutch National Flag):

Before processing:
[ unknown elements ]
  ^low ^mid              ^high

Invariant after each step:
[ 0s | 1s | unknown | 2s ]
       ^low ^mid     ^high

When mid processes:
  nums[mid] == 0  →  expand 0-region (swap low↔mid, advance both)
  nums[mid] == 1  →  expand 1-region (advance mid only)
  nums[mid] == 2  →  expand 2-region (swap mid↔high, retreat high)
                                      (don't advance mid!)
```

---

## Core Patterns

### Pattern A: Fix One + Two Pointers (k-Sum Family)

```cpp
// TEMPLATE: kSum → reduce to 2Sum with two pointers
void kSum(vector<int>& nums, int k, int start, long target,
          vector<int>& current, vector<vector<int>>& result) {

    if (k == 2) {
        // Base case: two pointers
        int left  = start;
        int right = (int)nums.size() - 1;

        while (left < right) {
            long sum = nums[left] + nums[right];
            if (sum == target) {
                current.push_back(nums[left]);
                current.push_back(nums[right]);
                result.push_back(current);
                current.pop_back();
                current.pop_back();

                while (left < right && nums[left]  == nums[left + 1])  left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return;
    }

    // Recursive: fix nums[i] and reduce to (k-1)-Sum
    for (int i = start; i <= (int)nums.size() - k; i++) {
        if (i > start && nums[i] == nums[i - 1]) continue;  // Skip dup

        current.push_back(nums[i]);
        kSum(nums, k - 1, i + 1, target - nums[i], current, result);
        current.pop_back();
    }
}
```

### Pattern B: Dutch National Flag (Three Regions)

```cpp
// TEMPLATE: Partition array into 3 groups
void threeWayPartition(vector<int>& arr, int pivot) {
    int low  = 0;             // Boundary of "less" region
    int mid  = 0;             // Current element to classify
    int high = arr.size()-1;  // Boundary of "greater" region

    while (mid <= high) {
        if (arr[mid] < pivot) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == pivot) {
            mid++;            // Already in correct region
        } else {
            swap(arr[mid], arr[high]);
            high--;
            // DON'T increment mid: we don't know what we swapped in
        }
    }
    // Result: [<pivot | ==pivot | >pivot]
}
```

### Pattern C: Three Pointer Merge

```cpp
// TEMPLATE: Merge operations involving 3 sources
// Example: merge two sorted arrays into third
void mergeIntoThird(vector<int>& a, vector<int>& b, vector<int>& c) {
    int i = 0;  // pointer for a
    int j = 0;  // pointer for b
    int k = 0;  // pointer for c (write position)

    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }

    while (i < a.size()) c[k++] = a[i++];
    while (j < b.size()) c[k++] = b[j++];
}
```

### Pattern D: Previous-Current-Next Triple

```cpp
// TEMPLATE: Sliding window of 3 consecutive elements
for (int i = 1; i < n - 1; i++) {
    int prev = arr[i - 1];
    int curr = arr[i];
    int next = arr[i + 1];

    // Process the triple (prev, curr, next)
    // Example: check if curr is a local max/min
    if (curr > prev && curr > next) {
        // curr is a local maximum
    }
}
```

---

## Easy Problems

---

### E1. Sort Colors (LeetCode 75) — Dutch National Flag

*(Full solution in Two Pointers Medium M4 — canonical reference)*

```cpp
// Shown earlier — the definitive three-pointer Dutch Flag problem.
// low=0, mid=0, high=n-1
// Process: 0→expand left, 1→advance, 2→expand right
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = (int)nums.size() - 1;
        while (mid <= high) {
            if      (nums[mid] == 0) { swap(nums[low++], nums[mid++]); }
            else if (nums[mid] == 1) { mid++; }
            else                    { swap(nums[mid], nums[high--]); }
        }
    }
};
```

---

### E2. Merge Sorted Array (LeetCode 88) — Three Write Pointers

*(Full solution in Two Pointers Easy E4)*

```cpp
// Three pointer merge: p1 (nums1 end), p2 (nums2 end), p (write position)
// Merge from back to front → no overwrite of unread data
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m-1, p2 = n-1, p = m+n-1;
        while (p1 >= 0 && p2 >= 0) {
            nums1[p--] = (nums1[p1] > nums2[p2]) ? nums1[p1--] : nums2[p2--];
        }
        while (p2 >= 0) nums1[p--] = nums2[p2--];
    }
};
```

---

### E3. 3Sum Equals Zero — Counting (LeetCode variant)

```cpp
/*
 * Problem: Count triplets with sum = 0 (no dedup needed variant)
 *
 * ─────────────────────────────────────────────────────────
 * This demonstrates the fix-one, two-pointer scan pattern
 * without deduplication — simpler for counting tasks.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n²)
 * SPACE: O(1)
 */

int countTriplets(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size(), count = 0;

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1, right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if      (sum == 0) { count++; left++; right--; }
            else if (sum < 0)  { left++;  }
            else               { right--; }
        }
    }
    return count;
}
```

---

### E4. Move Zeroes to a Specific Section (Three Groups)

```cpp
/*
 * Problem: Partition array into negatives, zeros, positives
 *
 * ─────────────────────────────────────────────────────────
 * Dutch National Flag with custom pivot (0).
 * Three pointers: neg, mid, pos
 * ─────────────────────────────────────────────────────────
 */

void partitionThreeWay(vector<int>& nums) {
    int neg = 0, mid = 0, pos = (int)nums.size() - 1;

    while (mid <= pos) {
        if      (nums[mid] < 0)  { swap(nums[neg++], nums[mid++]); }
        else if (nums[mid] == 0) { mid++; }
        else                     { swap(nums[mid], nums[pos--]); }
    }
}
```

---

### E5. Check If Array Is Sorted and Rotated (LeetCode 1752)

```cpp
/*
 * Problem: 1752. Check if Array Is Sorted and Rotated
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an array nums, return true if it could become non-decreasing
 * after some rotation. (Array was originally sorted then rotated)
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * In a sorted-and-rotated array, there is at most ONE "drop"
 * (position where nums[i] > nums[i+1]).
 * Use a three-pointer window (prev, curr, next style) to count drops.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    bool check(vector<int>& nums) {
        int n    = nums.size();
        int drops = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] > nums[(i + 1) % n]) {
                drops++;
            }
        }

        return drops <= 1;
    }
};
```

---

### E6. Longest Turbulent Subarray (LeetCode 978)

```cpp
/*
 * Problem: 978. Longest Turbulent Subarray
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Return the length of the longest turbulent subarray.
 * Turbulent: alternating > and < comparisons.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pointer sliding window (prev, curr, next)
 *
 * Use anchor (start of current turbulent segment) and i (current).
 * At each step compare sign(arr[i]-arr[i-1]) with sign(arr[i-1]-arr[i-2]).
 * If pattern breaks → reset anchor to i-1.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) return n;

        int anchor = 0, maxLen = 1;

        for (int i = 1; i < n; i++) {
            int cmp = (arr[i] > arr[i-1]) - (arr[i] < arr[i-1]); // sign

            if (cmp == 0) {
                anchor = i;           // Flat: reset
            } else if (i == n-1 || cmp * ((arr[i+1] > arr[i]) - (arr[i+1] < arr[i])) != -1) {
                maxLen = max(maxLen, i - anchor + 1);
                anchor = i;           // Pattern breaks at next step
            }
        }

        return maxLen;
    }
};

// Cleaner version:
class Solution2 {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        int maxLen = 1, cur = 1;

        for (int i = 1; i < n; i++) {
            bool shouldAlt = (i == 1) ||
                (arr[i-1] > arr[i-2]) != (arr[i] > arr[i-1]);

            if (arr[i] != arr[i-1] && shouldAlt) {
                cur++;
            } else {
                cur = (arr[i] != arr[i-1]) ? 2 : 1;
            }
            maxLen = max(maxLen, cur);
        }

        return maxLen;
    }
};
```

---

### E7. Third Maximum Number (LeetCode 414)

```cpp
/*
 * Problem: 414. Third Maximum Number
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums, return the third distinct maximum.
 * If the third maximum doesn't exist, return the maximum.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three "pointer" variables tracking top-3 values
 *
 * Maintain three variables: first, second, third
 * (using LLONG_MIN as "not set" sentinel)
 * Update them in order on each element.
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [3, 2, 1]
 * Init: first=LLONG_MIN, second=LLONG_MIN, third=LLONG_MIN
 *
 * 3: > first → third=second=LLONG_MIN, second=first=LLONG_MIN, first=3
 * 2: > second, < first → third=second=LLONG_MIN, second=2
 * 1: > third, < second → third=1
 *
 * third != LLONG_MIN → return 1 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long long first  = LLONG_MIN;
        long long second = LLONG_MIN;
        long long third  = LLONG_MIN;

        for (int num : nums) {
            long long n = num;

            // Skip duplicates
            if (n == first || n == second || n == third) continue;

            if (n > first) {
                third  = second;
                second = first;
                first  = n;
            } else if (n > second) {
                third  = second;
                second = n;
            } else if (n > third) {
                third = n;
            }
        }

        return (third == LLONG_MIN) ? (int)first : (int)third;
    }
};
```

---

### E8. Find All Numbers Disappeared in an Array (LeetCode 448)

```cpp
/*
 * Problem: 448. Find All Numbers Disappeared in an Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given array nums of n integers where each is in [1, n],
 * return all integers in [1, n] that do not appear.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pointer cycle sort variant
 *
 * Place each number at its correct index using swap.
 * Then scan for positions where nums[i] != i+1.
 * Those missing values are the answer.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1) extra
 */

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();

        // Place each number at its correct index
        for (int i = 0; i < n; i++) {
            while (nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // Collect missing numbers
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) result.push_back(i + 1);
        }

        return result;
    }
};
```

---

### E9. Reverse String II (LeetCode 541)

```cpp
/*
 * Problem: 541. Reverse String II
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a string s and integer k, reverse the first k characters
 * for every 2k characters. If fewer than k characters remain,
 * reverse all remaining.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pointer within blocks
 *
 * Use i (start of block), left (start of reverse range),
 * right (end of reverse range) within each 2k-block.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();

        for (int i = 0; i < n; i += 2 * k) {
            int left  = i;
            int right = min(i + k - 1, n - 1);  // Don't go past end

            while (left < right) {
                swap(s[left++], s[right--]);
            }
        }

        return s;
    }
};
```

---

### E10. Minimum Difference Between Highest and Lowest of K Scores (LeetCode 1984)

```cpp
/*
 * Problem: 1984. Minimum Difference Between Highest and Lowest of K Scores
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * You want to choose a set of k scores that minimizes the
 * difference between the highest and lowest score in the set.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Sliding window of size k (two endpoint pointers)
 *
 * After sorting, the minimum difference window of size k
 * consists of CONSECUTIVE elements (no gaps needed).
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(1)
 */

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int minDiff = INT_MAX;
        int n = nums.size();

        for (int i = 0; i + k - 1 < n; i++) {
            int left  = i;
            int right = i + k - 1;           // Fixed-size window of k
            minDiff = min(minDiff, nums[right] - nums[left]);
        }

        return minDiff;
    }
};
```

---

## Medium Problems

---

### M1. 3Sum (LeetCode 15)

*(Full solution in Two Pointers Medium M1 — this is the canonical three-pointer problem)*

```cpp
// Sort + fix i + two pointers (left, right)
// See Two Pointers M1 for complete solution with dry run
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();

        for (int i = 0; i < n-2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            if (nums[i] > 0) break;

            int left = i+1, right = n-1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left]  == nums[left+1])  left++;
                    while (left < right && nums[right] == nums[right-1]) right--;
                    left++; right--;
                } else if (sum < 0) { left++;
                } else              { right--; }
            }
        }
        return res;
    }
};
```

---

### M2. 3Sum Closest (LeetCode 16)

*(Full solution in Two Pointers Medium M3)*

---

### M3. 4Sum (LeetCode 18)

*(Full solution in Two Pointers Hard H2)*

---

### M4. Count Triangles with Positive Area (LeetCode variant)

```cpp
/*
 * Problem: Valid Triangle Number (LeetCode 611)
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an integer array nums, return the number of triplets
 * chosen from the array that can make a valid triangle.
 * Triangle inequality: sum of any two sides > third side.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION:
 *
 * Sort array. Fix the largest side (nums[k], rightmost).
 * Use two pointers left=0, right=k-1 to find pairs where
 * nums[left] + nums[right] > nums[k].
 *
 * KEY INSIGHT: If nums[left] + nums[right] > nums[k]:
 * → ALL pairs (left, left+1, ..., right-1) with right are valid
 * → Add (right - left) to count, then decrease right
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [2, 2, 3, 4]
 *
 * k=3 (nums[k]=4): left=0, right=2
 *   2+3=5 > 4 → count += 2-0=2, right=1
 *   2+2=4 > 4? No → left++
 *   left >= right → end
 *
 * k=2 (nums[k]=3): left=0, right=1
 *   2+2=4 > 3 → count += 1-0=1, right=0
 *   left >= right → end
 *
 * Total: 3 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n²)
 * SPACE: O(1)
 */

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;
        int n = nums.size();

        for (int k = n - 1; k >= 2; k--) {
            int left  = 0;
            int right = k - 1;

            while (left < right) {
                if (nums[left] + nums[right] > nums[k]) {
                    count += right - left;  // All [left..right-1] work with right
                    right--;
                } else {
                    left++;
                }
            }
        }

        return count;
    }
};
```

---

### M5. Remove Duplicates from Sorted Array II (LeetCode 80)

```cpp
/*
 * Problem: 80. Remove Duplicates from Sorted Array II
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given sorted array nums, remove some duplicates in-place
 * such that each unique element appears at most twice.
 * Return the new length.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pointer read-write pattern
 *
 * Writer pointer: position to write next element
 * Reader pointer: scanning forward
 * Count pointer: how many times current value has been written
 *
 * Generalized: allow at most 'k' copies of each value.
 * Write nums[reader] only if writer < k OR nums[writer-k] != nums[reader]
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * nums = [1,1,1,2,2,3], k=2
 *
 * writer=0, reader=0: write 1, writer=1
 * writer=1, reader=1: write 1, writer=2
 * writer=2, reader=2: nums[writer-2]=nums[0]=1 == nums[2]=1 → SKIP
 * writer=2, reader=3: write 2, writer=3
 * writer=3, reader=4: write 2, writer=4
 * writer=4, reader=5: nums[writer-2]=nums[2]=1 != nums[5]=3 → write 3, writer=5
 *
 * Result: [1,1,2,2,3,...] len=5 ✅
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 2;  // Allow at most 2 copies
        int writer = 0;

        for (int reader = 0; reader < (int)nums.size(); reader++) {
            // Write if: fewer than k elements written, OR
            //           current element != the element k positions back
            if (writer < k || nums[reader] != nums[writer - k]) {
                nums[writer] = nums[reader];
                writer++;
            }
        }

        return writer;
    }
};
```

---

### M6. Partition Array According to Given Pivot (LeetCode 2161)

```cpp
/*
 * Problem: 2161. Partition Array According to Given Pivot
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Rearrange so all elements < pivot come before all == pivot,
 * which come before all > pivot. Preserve relative order.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three-pass stable partition
 *
 * Unlike Dutch Flag (unstable), here we need relative order preserved.
 * Use three passes: collect less, equal, greater, then combine.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(n)
 */

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> less, equal, greater;

        for (int x : nums) {
            if      (x < pivot)  less.push_back(x);
            else if (x == pivot) equal.push_back(x);
            else                 greater.push_back(x);
        }

        // Combine three lists
        vector<int> result;
        for (int x : less)    result.push_back(x);
        for (int x : equal)   result.push_back(x);
        for (int x : greater) result.push_back(x);

        return result;
    }
};
```

---

### M7. Interval List Intersections (LeetCode 986)

```cpp
/*
 * Problem: 986. Interval List Intersections
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given two lists of closed intervals firstList and secondList,
 * return the intersection of these two interval lists.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Two pointers (one per list) + third for comparison
 *
 * i scans firstList, j scans secondList.
 * At each step, compute overlap of current pair.
 * Advance the pointer whose interval ends first (done with it).
 *
 * ─────────────────────────────────────────────────────────
 * DRY RUN:
 * A = [[0,2],[5,10],[13,23],[24,25]]
 * B = [[1,5],[8,12],[15,24],[25,26]]
 *
 * i=0,j=0: A=[0,2],B=[1,5] → overlap=[1,2], A ends first → i++
 * i=1,j=0: A=[5,10],B=[1,5] → overlap=[5,5], B ends first → j++
 * i=1,j=1: A=[5,10],B=[8,12] → overlap=[8,10], A ends first → i++
 * ...
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m + n)
 * SPACE: O(m + n) for result
 */

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A,
                                              vector<vector<int>>& B) {
        vector<vector<int>> result;
        int i = 0, j = 0;

        while (i < (int)A.size() && j < (int)B.size()) {
            // Intersection: [max of starts, min of ends]
            int lo = max(A[i][0], B[j][0]);
            int hi = min(A[i][1], B[j][1]);

            if (lo <= hi) {
                result.push_back({lo, hi});
            }

            // Move pointer whose interval ends first
            if (A[i][1] < B[j][1]) {
                i++;
            } else {
                j++;
            }
        }

        return result;
    }
};
```

---

### M8. Maximum Length of Repeated Subarray (LeetCode 718)

```cpp
/*
 * Problem: 718. Maximum Length of Repeated Subarray
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given two integer arrays nums1 and nums2, return the maximum
 * length of a subarray that appears in both arrays.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: DP with two-pointer indices
 *
 * dp[i][j] = length of longest common subarray ending at
 *            nums1[i-1] and nums2[j-1]
 *
 * Three "pointers": i (nums1 index), j (nums2 index), dp state
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m × n)
 * SPACE: O(m × n), optimizable to O(min(m,n))
 */

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLen = 0;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i-1] == nums2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                }
            }
        }

        return maxLen;
    }
};
```

---

### M9. 3Sum With Multiplicity (LeetCode 923)

```cpp
/*
 * Problem: 923. 3Sum With Multiplicity
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array arr and target, return the number of
 * tuples i < j < k such that arr[i] + arr[j] + arr[k] == target.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Sort + three pointers with multiplicity counting
 *
 * Sort arr. For each i, use two pointers left=i+1, right=n-1.
 * When sum equals target:
 *   - If left and right are different values: multiply their frequencies
 *   - If left == right: it's C(count, 2) = count*(count-1)/2
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n²)
 * SPACE: O(1)
 */

class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        long long count = 0;
        int n = arr.size();
        const int MOD = 1e9 + 7;

        for (int i = 0; i < n - 2; i++) {
            int left  = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                if (sum == target) {
                    if (arr[left] == arr[right]) {
                        // All elements between left and right are equal
                        long long span = right - left + 1;
                        count += span * (span - 1) / 2;
                        break;
                    } else {
                        // Count consecutive equals from left and right
                        int leftCount  = 1;
                        int rightCount = 1;
                        while (left + 1 < right && arr[left] == arr[left + 1]) {
                            leftCount++;
                            left++;
                        }
                        while (right - 1 > left && arr[right] == arr[right - 1]) {
                            rightCount++;
                            right--;
                        }
                        count += (long long)leftCount * rightCount;
                        left++;
                        right--;
                    }
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return count % MOD;
    }
};
```

---

### M10. Sort Array By Parity II (LeetCode 922)

```cpp
/*
 * Problem: 922. Sort Array By Parity II
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an array of integers nums, half of which are even,
 * rearrange so that nums[i] is even if i is even, and odd if i is odd.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Two interleaved pointers + one scan pointer
 *
 * evenPtr starts at 0 (even indices: 0, 2, 4, ...)
 * oddPtr starts at 1 (odd indices: 1, 3, 5, ...)
 *
 * Scan through:
 * If even index has odd number → find next misplaced odd index → swap
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size();
        int j = 1;  // Pointer for odd positions

        for (int i = 0; i < n; i += 2) {
            if (nums[i] % 2 != 0) {
                // Even position has odd number: find odd position with even number
                while (nums[j] % 2 != 0) j += 2;
                swap(nums[i], nums[j]);
            }
        }

        return nums;
    }
};
```

---

## Hard Problems

---

### H1. Trapping Rain Water II (LeetCode 407)

```cpp
/*
 * Problem: 407. Trapping Rain Water II
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an m×n matrix of non-negative integers representing
 * elevation heights, compute total water trapped.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: BFS from boundaries with min-heap
 *
 * Water level at any interior cell is determined by the minimum
 * boundary height on any path from cell to outside.
 *
 * Extend the "smaller boundary" insight from 1D to 2D using a
 * min-heap of boundary cells.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m × n × log(m + n))
 * SPACE: O(m × n)
 */

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        if (m < 3 || n < 3) return 0;

        // Min-heap: {height, row, col}
        priority_queue<tuple<int,int,int>,
                       vector<tuple<int,int,int>>,
                       greater<>> pq;

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Add all border cells
        for (int i = 0; i < m; i++) {
            for (int j : {0, n-1}) {
                pq.push({heightMap[i][j], i, j});
                visited[i][j] = true;
            }
        }
        for (int j = 0; j < n; j++) {
            for (int i : {0, m-1}) {
                pq.push({heightMap[i][j], i, j});
                visited[i][j] = true;
            }
        }

        int water = 0;
        int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        while (!pq.empty()) {
            auto [h, r, c] = pq.top();
            pq.pop();

            for (auto& d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc])
                    continue;

                // Water trapped = max(0, boundary_height - cell_height)
                water += max(0, h - heightMap[nr][nc]);

                // The effective boundary height for this neighbor is max(h, neighbor)
                pq.push({max(h, heightMap[nr][nc]), nr, nc});
                visited[nr][nc] = true;
            }
        }

        return water;
    }
};
```

---

### H2. Find K-th Smallest Pair Distance (LeetCode 719)

```cpp
/*
 * Problem: 719. Find K-th Smallest Pair Distance
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums, find the kth smallest absolute
 * difference of all pairs.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Binary search on answer + sliding window (three pointers)
 *
 * Binary search on the distance value d.
 * For each candidate d: count pairs with distance ≤ d.
 * Use sliding window (left, right) + outer loop (pointer k) to count.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n + n log W) where W = max-min
 * SPACE: O(1)
 */

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int lo = 0;
        int hi = nums[n-1] - nums[0];

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // Count pairs with distance ≤ mid
            if (countPairs(nums, mid) >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return lo;
    }

private:
    int countPairs(vector<int>& nums, int maxDist) {
        int count = 0;
        int left  = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            while (nums[right] - nums[left] > maxDist) {
                left++;
            }
            count += right - left;
        }

        return count;
    }
};
```

---

### H3. Minimum Absolute Difference (Count of k-diff pairs) (LeetCode 532)

```cpp
/*
 * Problem: 532. K-diff Pairs in an Array
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given an integer array nums and an integer k, return the number
 * of unique k-diff pairs in the array.
 * A k-diff pair is an integer pair (nums[i], nums[j]) where
 * |nums[i] - nums[j]| == k.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Sort + two pointers (left, right) + skip duplicates
 *
 * After sorting, for each left pointer find right where diff == k.
 * Since sorted: nums[right] - nums[left] == k.
 * One pointer per unique pair value.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(1)
 */

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0;

        sort(nums.begin(), nums.end());
        int left = 0, right = 1, count = 0;
        int n = nums.size();

        while (right < n) {
            if (left == right || nums[right] - nums[left] < k) {
                right++;
            } else if (nums[right] - nums[left] > k) {
                left++;
            } else {
                count++;
                left++;
                // Skip duplicates for left
                while (left < right && nums[left] == nums[left-1]) left++;
            }
        }

        return count;
    }
};
```

---

### H4. Count of Smaller Numbers After Self (LeetCode 315)

```cpp
/*
 * Problem: 315. Count of Smaller Numbers After Self
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums, return an array counts where
 * counts[i] = number of smaller elements to the right of nums[i].
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Merge Sort with index tracking (three-pointer merge)
 *
 * Modify merge sort to count inversions:
 * - During merge, when right element is placed before left elements,
 *   all remaining left elements are "larger" → add to their counts.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(n)
 */

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> counts(n, 0);
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);  // [0, 1, 2, ..., n-1]

        mergeSort(nums, indices, counts, 0, n - 1);
        return counts;
    }

private:
    void mergeSort(vector<int>& nums, vector<int>& indices,
                   vector<int>& counts, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        mergeSort(nums, indices, counts, left, mid);
        mergeSort(nums, indices, counts, mid + 1, right);

        // Three-pointer merge
        vector<int> merged;
        int i = left, j = mid + 1;

        while (i <= mid && j <= right) {
            if (nums[indices[i]] <= nums[indices[j]]) {
                // Right elements already placed are smaller than nums[indices[i]]
                counts[indices[i]] += j - (mid + 1);
                merged.push_back(indices[i++]);
            } else {
                merged.push_back(indices[j++]);
            }
        }

        while (i <= mid) {
            counts[indices[i]] += j - (mid + 1);
            merged.push_back(indices[i++]);
        }

        while (j <= right) {
            merged.push_back(indices[j++]);
        }

        for (int k = left; k <= right; k++) {
            indices[k] = merged[k - left];
        }
    }
};
```

---

### H5. Max Sum of Rectangle No Larger Than K (LeetCode 363)

```cpp
/*
 * Problem: 363. Max Sum of Rectangle No Larger Than K
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given m×n matrix and integer k, find the rectangle with the
 * largest sum no larger than k.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three pointer layers (row1, row2, col)
 *
 * Fix top and bottom row boundaries (row1, row2).
 * Compute column sums between these rows.
 * Find max subarray sum ≤ k in 1D using sorted set.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(m² × n log n)
 * SPACE: O(n)
 */

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int result = INT_MIN;

        for (int row1 = 0; row1 < m; row1++) {
            vector<int> colSum(n, 0);

            for (int row2 = row1; row2 < m; row2++) {
                for (int c = 0; c < n; c++) {
                    colSum[c] += matrix[row2][c];
                }

                // Find max subarray sum ≤ k in colSum
                result = max(result, maxSumNoLargerThanK(colSum, k));
            }
        }

        return result;
    }

private:
    int maxSumNoLargerThanK(vector<int>& arr, int k) {
        set<int> prefixSums;
        prefixSums.insert(0);
        int prefixSum = 0, result = INT_MIN;

        for (int x : arr) {
            prefixSum += x;

            // Find smallest prefix sum ≥ (prefixSum - k)
            auto it = prefixSums.lower_bound(prefixSum - k);
            if (it != prefixSums.end()) {
                result = max(result, prefixSum - *it);
            }

            prefixSums.insert(prefixSum);
        }

        return result;
    }
};
```

---

### H6. Shortest Subarray with Sum at Least K (LeetCode 862)

```cpp
/*
 * Problem: 862. Shortest Subarray with Sum at Least K
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums (may contain negatives) and integer k,
 * return the length of the shortest subarray with sum ≥ k.
 * Return -1 if no such subarray.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Prefix sums + Monotonic deque (three pointers implicitly)
 *
 * For non-negative arrays, sliding window works.
 * With negatives, we need prefix sums + deque.
 *
 * Use a monotonic increasing deque of prefix sum indices.
 * For each right, pop from front while prefix[right] - prefix[front] ≥ k.
 * Pop from back while prefix[right] ≤ prefix[back] (maintain monotone).
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n)
 * SPACE: O(n)
 */

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        deque<int> dq;  // Indices into prefix array
        int result = INT_MAX;

        for (int right = 0; right <= n; right++) {
            // Try to find valid subarrays ending at right
            while (!dq.empty() && prefix[right] - prefix[dq.front()] >= k) {
                result = min(result, right - dq.front());
                dq.pop_front();
            }

            // Maintain monotonic increasing deque
            while (!dq.empty() && prefix[right] <= prefix[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(right);
        }

        return (result == INT_MAX) ? -1 : result;
    }
};
```

---

### H7. Minimum Window Subsequence (LeetCode 727)

```cpp
/*
 * Problem: 727. Minimum Window Subsequence
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given strings s and t, find the minimum (contiguous) substring
 * of s such that t is a subsequence of it.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Three pointers (i for s forward, j for t, k for s backward)
 *
 * Phase 1: Move i forward through s until all of t matched (j reaches end)
 * Phase 2: Move i backward to find the tightest left boundary
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(|s| × |t|)
 * SPACE: O(1)
 */

class Solution {
public:
    string minWindow(string s, string t) {
        int si = 0;
        int minLen = INT_MAX;
        string result = "";

        while (si < (int)s.size()) {
            // Phase 1: Forward scan — match all of t
            int ti = 0;
            while (si < (int)s.size() && ti < (int)t.size()) {
                if (s[si] == t[ti]) ti++;
                si++;
            }

            if (ti < (int)t.size()) break;  // t not fully matched

            // Phase 2: Backward scan — tighten left boundary
            int end = si;  // si is one past the last matched position
            ti = (int)t.size() - 1;
            si--;  // Step back to last matched char

            while (ti >= 0) {
                if (s[si] == t[ti]) ti--;
                si--;
            }
            si++;  // si is now at the tight left boundary

            // Update result
            if (end - si < minLen) {
                minLen = end - si;
                result = s.substr(si, minLen);
            }

            si++;  // Advance to search for next window
        }

        return result;
    }
};
```

---

### H8. Count of Range Sum (LeetCode 327)

```cpp
/*
 * Problem: 327. Count of Range Sum
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums and [lower, upper], return the number
 * of range sums that lie in [lower, upper] inclusive.
 * Range sum S(i, j) = sum of nums[i..j].
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Merge sort on prefix sums (three pointers)
 *
 * Count pairs (i, j) where lower ≤ prefix[j] - prefix[i] ≤ upper.
 * During merge sort, for each right half element, find valid
 * left half elements using two pointers (lo, hi).
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n)
 * SPACE: O(n)
 */

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        return mergeCount(prefix, 0, n, lower, upper);
    }

private:
    int mergeCount(vector<long long>& prefix, int left, int right,
                   int lower, int upper) {
        if (right - left <= 0) return 0;

        int mid = left + (right - left) / 2;
        int count = mergeCount(prefix, left, mid, lower, upper)
                  + mergeCount(prefix, mid + 1, right, lower, upper);

        // Count cross pairs: i in [left,mid], j in [mid+1,right]
        // lower ≤ prefix[j] - prefix[i] ≤ upper
        int lo = mid + 1, hi = mid + 1;  // Two pointers into right half

        for (int i = left; i <= mid; i++) {
            while (lo <= right && prefix[lo] - prefix[i] <  lower) lo++;
            while (hi <= right && prefix[hi] - prefix[i] <= upper) hi++;
            count += hi - lo;
        }

        // Standard merge
        inplace_merge(prefix.begin() + left,
                      prefix.begin() + mid + 1,
                      prefix.begin() + right + 1);

        return count;
    }
};
```

---

### H9. Partition to K Equal Sum Subsets (LeetCode 698)

```cpp
/*
 * Problem: 698. Partition to K Equal Sum Subsets
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given integer array nums and integer k, return true if it is
 * possible to divide this array into k non-empty subsets
 * whose sums are all equal.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Backtracking with bucket pointers
 *
 * Maintain k buckets (each needs to reach target = sum/k).
 * Try placing each number into a bucket (three pointer: element, bucket, position).
 *
 * Pruning: if two buckets have same current sum, they're symmetric → skip.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(k × 2^n) worst case
 * SPACE: O(n)
 */

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;

        int target = total / k;
        sort(nums.begin(), nums.end(), greater<int>());  // Sort descending (pruning)

        if (nums[0] > target) return false;

        vector<int> buckets(k, 0);
        return backtrack(nums, buckets, 0, target);
    }

private:
    bool backtrack(vector<int>& nums, vector<int>& buckets,
                   int idx, int target) {
        if (idx == (int)nums.size()) return true;

        set<int> tried;  // Skip identical bucket states

        for (int i = 0; i < (int)buckets.size(); i++) {
            if (tried.count(buckets[i])) continue;
            if (buckets[i] + nums[idx] > target) continue;

            tried.insert(buckets[i]);
            buckets[i] += nums[idx];

            if (backtrack(nums, buckets, idx + 1, target)) return true;

            buckets[i] -= nums[idx];
        }

        return false;
    }
};
```

---

### H10. Minimize Maximum of Subarrays After Splits (LeetCode 2616)

```cpp
/*
 * Problem: 2616. Minimize the Maximum Difference of Pairs
 *
 * ─────────────────────────────────────────────────────────
 * STATEMENT:
 * Given a 0-indexed integer array nums and integer p, find p pairs
 * of indices that minimize the maximum difference among all pairs.
 * Return the minimum maximum difference.
 *
 * ─────────────────────────────────────────────────────────
 * INTUITION: Binary search + greedy with two pointers
 *
 * Binary search on the answer (max difference d).
 * Greedy: scan sorted array with one pointer, greedily pick pairs
 * where consecutive difference ≤ d. Count pairs formed.
 *
 * ─────────────────────────────────────────────────────────
 * TIME:  O(n log n + n log W) where W = max-min
 * SPACE: O(1)
 */

class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = nums.back() - nums.front();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (canFormPairs(nums, mid, p)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return lo;
    }

private:
    bool canFormPairs(vector<int>& nums, int maxDiff, int p) {
        int pairs = 0;
        int i     = 0;

        while (i < (int)nums.size() - 1) {
            if (nums[i + 1] - nums[i] <= maxDiff) {
                pairs++;
                i += 2;  // This pair is used, skip both
            } else {
                i++;
            }
        }

        return pairs >= p;
    }
};
```

---

# Pattern Recognition Cheat Sheet

## Which Pattern to Use?

```
PROBLEM SIGNALS                         → PATTERN
────────────────────────────────────────────────────────────
"find pair summing to target"           → Two Pointers (sorted)
"palindrome check"                      → Two Pointers (opposite ends)
"remove duplicates in-place"            → Two Pointers (read-write)
"longest/shortest substring with..."   → Sliding Window
"at most k distinct characters"         → Sliding Window + HashMap
"cycle in linked list"                  → Slow-Fast Pointers
"middle of linked list"                 → Slow-Fast Pointers
"nth from end"                          → Fast pointer n ahead
"reverse / reorder linked list"         → Slow-Fast + reverse
"3Sum / 4Sum / triplets"                → Sort + Fix One + Two Pointers
"sort 0s 1s 2s / three-way partition"  → Dutch National Flag (3 Pointers)
"count inversions"                      → Merge Sort (3-pointer merge)
"max subarray product < k"              → Sliding Window + product
"exactly k distinct"                    → atMost(k) - atMost(k-1)
"k-th smallest/largest pair distance"  → Binary Search + Two Pointers
```

## Complexity Summary

| Pattern | Time | Space | Sorted? |
| :--- | :--- | :--- | :--- |
| Two Pointers — Pair Sum | O(n) | O(1) | Required |
| Two Pointers — In-place | O(n) | O(1) | No |
| Sliding Window | O(n) | O(k) | No |
| Slow-Fast Cycle | O(n) | O(1) | No |
| Slow-Fast Middle | O(n) | O(1) | No |
| 3Sum / kSum | O(n²) | O(1) | Required |
| Dutch Flag | O(n) | O(1) | No |
| Merge Sort | O(n log n) | O(n) | No |

---

# Common Mistakes & How to Avoid Them

## Two Pointers Mistakes

### 1. Forgetting to Sort

```cpp
// ❌ WRONG: Two-pointer pair sum WITHOUT sorting
int left = 0, right = n - 1;
// Result will be incorrect on unsorted array

// ✅ CORRECT: Sort first
sort(nums.begin(), nums.end());
int left = 0, right = n - 1;
```

### 2. Duplicate Handling in 3Sum

```cpp
// ❌ WRONG: Missing duplicate skip → duplicate triplets in output
if (sum == 0) {
    result.push_back({...});
    left++;
    right--;
}

// ✅ CORRECT: Skip duplicates after finding a triplet
if (sum == 0) {
    result.push_back({...});
    while (left < right && nums[left]  == nums[left + 1])  left++;
    while (left < right && nums[right] == nums[right - 1]) right--;
    left++;
    right--;
}
```

### 3. Off-by-One in Sliding Window

```cpp
// ❌ WRONG: Window size is right - left, not right - left + 1
maxLen = max(maxLen, right - left);

// ✅ CORRECT: Window [left, right] has (right - left + 1) elements
maxLen = max(maxLen, right - left + 1);
```

### 4. Integer Overflow in 4Sum

```cpp
// ❌ WRONG: Sum of 4 ints can overflow int
int sum = nums[i] + nums[j] + nums[left] + nums[right];

// ✅ CORRECT: Cast to long long
long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
```

---

## Slow-Fast Pointer Mistakes

### 5. Wrong Loop Condition for Middle-Finding

```cpp
// ❌ WRONG: fast != nullptr misses even-length lists correctly
while (fast != nullptr) { ... }

// ✅ CORRECT: Check both fast and fast->next
while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
}
```

### 6. Not Using Dummy Node for Deletion

```cpp
// ❌ WRONG: Can't delete the head node
ListNode* slow = head;
ListNode* fast = head;
// ...
slow->next = slow->next->next;  // Works ONLY if not deleting head

// ✅ CORRECT: Use dummy node
ListNode dummy(0);
dummy.next = head;
ListNode* slow = &dummy;
ListNode* fast = &dummy;
// ...
slow->next = slow->next->next;  // Works even for head deletion
return dummy.next;
```

### 7. Phase 2 of Floyd's — Wrong Reset

```cpp
// ❌ WRONG: Resetting both pointers to head
slow = head;
fast = head;  // WRONG: fast should stay at meeting point

// ✅ CORRECT: Only reset slow, keep fast at meeting point
slow = head;
// fast stays at meeting point
while (slow != fast) {
    slow = slow->next;
    fast = fast->next;  // BOTH move at speed 1 in phase 2
}
```

---

## Three Pointer Mistakes

### 8. Dutch Flag: Advancing Mid After Swapping with High

```cpp
// ❌ WRONG: Don't advance mid after swapping with high
if (nums[mid] == 2) {
    swap(nums[mid], nums[high]);
    high--;
    mid++;  // WRONG! We don't know what we just got from high
}

// ✅ CORRECT: Only advance high, not mid
if (nums[mid] == 2) {
    swap(nums[mid], nums[high]);
    high--;
    // mid stays — re-examine the newly placed element
}
```

### 9. kSum Recursion: Wrong Base Case

```cpp
// ❌ WRONG: Forgetting to pass start index in recursive kSum
for (int i = 0; i < n; i++) {  // Should start from 'start'
    kSum(nums, k-1, 0, target - nums[i], ...);  // 0 causes duplicates
}

// ✅ CORRECT:
for (int i = start; i < n; i++) {
    if (i > start && nums[i] == nums[i-1]) continue;  // Dedup
    kSum(nums, k-1, i+1, target - nums[i], ...);
}
```

---

# Practice Strategy

## Phase 1 — Foundation (Week 1-2)

**Goal:** Master the core templates. Write each from memory.

| Priority | Problem | Pattern | Why |
| :--- | :--- | :--- | :--- |
| 🔴 | 167. Two Sum II | Two Ptr | Classic sorted pair |
| 🔴 | 344. Reverse String | Two Ptr | Simplest two-ptr |
| 🔴 | 26. Remove Duplicates | Read-Write | In-place filter |
| 🔴 | 141. Linked List Cycle | Slow-Fast | Floyd's basics |
| 🔴 | 876. Middle of Linked List | Slow-Fast | Middle finding |
| 🔴 | 75. Sort Colors | Dutch Flag | Three-region |
| 🟡 | 125. Valid Palindrome | Two Ptr | Skip & compare |
| 🟡 | 283. Move Zeroes | Read-Write | Swap variant |
| 🟡 | 977. Squares of Sorted | Two Ptr | Fill from back |
| 🟡 | 392. Is Subsequence | Two Ptr (diff arrays) | Greedy match |

## Phase 2 — Core Problems (Week 3-4)

**Goal:** Apply patterns under time pressure.

| Priority | Problem | Pattern | Why |
| :--- | :--- | :--- | :--- |
| 🔴 | 15. 3Sum | Fix+TwoPtr | Must-know |
| 🔴 | 11. Container Most Water | Two Ptr | Greedy elimination |
| 🔴 | 3. Longest No-Repeat | Sliding Window | Classic |
| 🔴 | 142. Cycle II | Slow-Fast Phase 2 | Math insight |
| 🔴 | 19. Remove Nth from End | Fast-Slow Gap | Practical |
| 🔴 | 234. Palindrome List | Slow-Fast + Reverse | Multi-step |
| 🟡 | 424. Char Replacement | Sliding Window | maxFreq trick |
| 🟡 | 209. Min Size Subarray | Sliding Window | Shrink on valid |
| 🟡 | 16. 3Sum Closest | Fix+TwoPtr | Track closest |
| 🟡 | 611. Valid Triangle | Fix+TwoPtr | Count variant |

## Phase 3 — Advanced (Week 5-6)

**Goal:** Tackle hard problems, recognize pattern combinations.

| Priority | Problem | Pattern | Why |
| :--- | :--- | :--- | :--- |
| 🔴 | 42. Trapping Rain Water | Two Ptr + maxL/R | Elegant O(1) space |
| 🔴 | 76. Minimum Window | Sliding + 2 maps | Complex window |
| 🔴 | 287. Find Duplicate | Floyd's on array | Non-obvious application |
| 🔴 | 25. Reverse k-Group | Slow-Fast + reverse | List manipulation |
| 🟡 | 239. Sliding Window Max | Deque + window | Monotonic deque |
| 🟡 | 992. Subarrays K Distinct | atMost trick | Clever reduction |
| 🟡 | 719. K-th Smallest Distance | BinSearch + TwoPtr | Two patterns |
| 🟡 | 327. Count Range Sum | MergeSort + 3ptr | Inversion counting |
| ⚪ | 407. Trapping Rain 2D | BFS + min-heap | 2D extension |
| ⚪ | 315. Count Smaller | Merge + track idx | Advanced merge |

## Decision Tree for New Problems

```
1. Does the problem involve PAIRS or RANGES?
   → YES: Consider Two Pointers or Sliding Window
      Is array SORTED or can be sorted?
        → YES: Two Pointers (opposite ends)
        → NO:  Sliding Window
   → NO: Continue

2. Does it involve a LINKED LIST?
   → Finding middle/palindrome/reorder? → Slow-Fast Pointers
   → Finding cycle/entry?               → Floyd's Algorithm
   → Nth from end?                      → Gap technique

3. Does it require PARTITIONING into 3 groups?
   → Dutch National Flag (3 Pointers)

4. Is it a kSUM problem?
   → Sort + Fix (k-2) pointers + Two Pointers

5. Does it need COUNTING inversions or ranked pairs?
   → Merge Sort with 3-pointer merge
```

## Interview Tips

**Before coding:**
- Confirm if array is sorted (enables two pointers directly)
- Ask if negatives are present (affects product/sum windows)
- Clarify if linked list can have cycles

**During coding:**
- Two pointers → initialize at 0 and n-1 (or both at 0 for sliding window)
- Slow-fast → check `fast && fast->next` BEFORE advancing
- Dutch flag → remember: don't advance mid after swap with high
- kSum → sort first, always skip duplicates at EACH level

**Complexity goals:**
- Two pointers: O(n) time, O(1) space
- Sliding window: O(n) time, O(k) space (k = distinct elements)
- Slow-fast: O(n) time, O(1) space
- kSum: O(n^(k-1)) time, O(1) extra space

---

**End of Pointer Patterns — Complete C++ Guide** 🚀

*Two Pointers (30 problems) · Slow-Fast Pointers (30 problems) · Three Pointers (30 problems)*
