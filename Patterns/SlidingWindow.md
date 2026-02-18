# Sliding Window Pattern — Complete C++ Guide

## Table of Contents
- [What is Sliding Window?](#what-is-sliding-window)
- [When to Use Sliding Window](#when-to-use-sliding-window)
- [Core Concepts & Intuition](#core-concepts--intuition)
- [Pattern Types](#pattern-types)
  - [Fixed-Size Window](#fixed-size-window)
  - [Variable-Size Window](#variable-size-window)
  - [Dynamic Window (Shrinkable)](#dynamic-window-shrinkable)
  - [Window with Constraints](#window-with-constraints)
- [Templates & Code Patterns](#templates--code-patterns)
- [Easy Problems (15)](#easy-problems)
- [Medium Problems (20)](#medium-problems)
- [Hard Problems (15)](#hard-problems)
- [Pattern Recognition Guide](#pattern-recognition-guide)
- [Common Mistakes & How to Avoid](#common-mistakes--how-to-avoid)
- [Optimization Techniques](#optimization-techniques)
- [Practice Strategy](#practice-strategy)

---

# What is Sliding Window?

**Sliding Window** is an algorithmic technique where you maintain a **contiguous subarray (or substring)** 
that "slides" over the data structure, expanding or contracting based on certain conditions.

Instead of checking every possible subarray (O(n²) or O(n³)), you maintain a window that moves in **one pass** (O(n)).

```
Brute Force:  Check all subarrays [i, j]
              → O(n²) iterations × O(n) check = O(n³)

Sliding Window:  Maintain window [left, right]
                 Move right to expand, left to contract
                 → O(n) because each element enters/exits at most once
```

## Visual Example

```
Array: [1, 3, -1, -3, 5, 3, 6, 7]
Window size k = 3

Initial:  [1, 3, -1] -3  5  3  6  7     max = 3
Slide:     1 [3, -1, -3] 5  3  6  7     max = 3
Slide:     1  3 [-1, -3, 5] 3  6  7     max = 5
Slide:     1  3  -1 [-3, 5, 3] 6  7     max = 5
Slide:     1  3  -1  -3 [5, 3, 6] 7     max = 6
Slide:     1  3  -1  -3  5 [3, 6, 7]    max = 7

Key insight: As window slides, we ADD new element, REMOVE old element.
This is O(1) per position → O(n) total.
```

---

# When to Use Sliding Window

## Problem Signals (Keywords)

```
✅ USE SLIDING WINDOW when you see:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"contiguous subarray"
"substring"
"consecutive elements"
"window of size k"
"longest/shortest substring/subarray with [condition]"
"maximum/minimum sum of k consecutive elements"
"at most k distinct characters"
"no repeating characters"
"all characters of pattern"
```

## NOT Sliding Window

```
❌ DON'T use sliding window when:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"subsequence" (non-contiguous) → Use DP or two pointers
"permutation of array" (order matters globally) → Use backtracking
"all pairs" → May need two pointers or hash map
"circular array" → May need special handling
```

---

# Core Concepts & Intuition

## The Window State

```cpp
// A window is defined by two pointers:
int left = 0;   // Left boundary (inclusive)
int right = 0;  // Right boundary (inclusive)

// Window = arr[left..right]
// Window size = right - left + 1
```

## Window Operations

```
EXPAND:  right++         → Add arr[right] to window
         Update window state

CONTRACT: Remove arr[left] from window
          left++

SLIDE:   Both operations in sequence (fixed-size window)
```

## The Golden Rule

```
Every element is:
  - ADDED to the window exactly ONCE (when right crosses it)
  - REMOVED from the window exactly ONCE (when left crosses it)

Therefore: O(2n) = O(n) time complexity
```

---

# Pattern Types

## Pattern 1: Fixed-Size Window

**Description:** Window size is constant throughout.

**Use when:** "Maximum sum of k consecutive elements", "Average of k elements"

**Template:**
```cpp
int fixedWindow(vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return -1;

    // Step 1: Build first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    int result = windowSum;

    // Step 2: Slide window
    for (int i = k; i < n; i++) {
        windowSum += arr[i];      // Add new element
        windowSum -= arr[i - k];  // Remove old element
        result = max(result, windowSum);
    }

    return result;
}
```

**Complexity:** O(n) time, O(1) space

---

## Pattern 2: Variable-Size Window (Expand Until Invalid)

**Description:** Window grows as long as valid, shrinks when invalid.

**Use when:** "Longest substring with at most k distinct", "Maximum consecutive 1s with k flips"

**Template:**
```cpp
int variableWindow(vector<int>& arr, int k) {
    int left = 0;
    int maxLen = 0;
    int windowState = 0;  // Track window validity

    for (int right = 0; right < arr.size(); right++) {
        // EXPAND: Add arr[right]
        windowState += arr[right];

        // CONTRACT: Shrink while invalid
        while (windowState > k) {
            windowState -= arr[left];
            left++;
        }

        // Update result
        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}
```

**Complexity:** O(n) time, O(1) space

---

## Pattern 3: Dynamic Window (Shrinkable - Find Minimum)

**Description:** Find the **smallest** window satisfying condition.

**Use when:** "Minimum window substring", "Shortest subarray with sum ≥ k"

**Template:**
```cpp
int minimumWindow(vector<int>& arr, int k) {
    int left = 0;
    int minLen = INT_MAX;
    int windowSum = 0;

    for (int right = 0; right < arr.size(); right++) {
        // EXPAND: Add arr[right]
        windowSum += arr[right];

        // CONTRACT: Shrink while STILL valid
        while (windowSum >= k && left <= right) {
            minLen = min(minLen, right - left + 1);
            windowSum -= arr[left];
            left++;
        }
    }

    return (minLen == INT_MAX) ? 0 : minLen;
}
```

**Key difference from Pattern 2:** Shrink while **STILL valid** (to minimize window).

---

## Pattern 4: Window with Constraints (Using HashMap)

**Description:** Track character/element frequencies within window.

**Use when:** "Longest substring without repeating", "Anagram in string"

**Template:**
```cpp
int windowWithMap(string s) {
    unordered_map<char, int> freq;
    int left = 0;
    int maxLen = 0;

    for (int right = 0; right < s.size(); right++) {
        // EXPAND: Add s[right]
        freq[s[right]]++;

        // CONTRACT: Shrink while constraint violated
        while (constraintViolated(freq)) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) {
                freq.erase(s[left]);
            }
            left++;
        }

        // Update result
        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}
```

**Common constraints:**
- `freq.size() > k` → too many distinct elements
- `freq[c] > 1` → duplicate found
- All required chars not present

---

# Templates & Code Patterns

## Master Template (Variable Window)

```cpp
/*
 * UNIVERSAL SLIDING WINDOW TEMPLATE
 * 
 * Works for:
 * - Longest/shortest substring
 * - At most/exactly k distinct
 * - With/without repeating characters
 * - Maximum/minimum sum/product
 */

int slidingWindow(vector<int>& arr, int constraint) {
    int left = 0;
    int result = 0;  // or INT_MAX for minimum
    
    // Window state (choose appropriate data structure)
    unordered_map<int, int> window;
    // OR: int windowSum = 0;
    // OR: int distinctCount = 0;

    for (int right = 0; right < arr.size(); right++) {
        // ═══════════════════════════════════════════════
        // STEP 1: EXPAND — Add arr[right] to window
        // ═══════════════════════════════════════════════
        window[arr[right]]++;
        // OR: windowSum += arr[right];

        // ═══════════════════════════════════════════════
        // STEP 2: CONTRACT — Shrink if invalid
        // ═══════════════════════════════════════════════
        while (isInvalid(window, constraint)) {
            window[arr[left]]--;
            if (window[arr[left]] == 0) {
                window.erase(arr[left]);
            }
            left++;
        }

        // ═══════════════════════════════════════════════
        // STEP 3: UPDATE RESULT
        // ═══════════════════════════════════════════════
        result = max(result, right - left + 1);  // For maximum
        // OR: result = min(result, right - left + 1);  // For minimum
    }

    return result;
}
```

## Fixed Window Template

```cpp
int fixedSizeWindow(vector<int>& arr, int k) {
    int result = 0;
    int windowSum = 0;

    // Build initial window
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    result = windowSum;

    // Slide window: remove left, add right
    for (int right = k; right < arr.size(); right++) {
        windowSum += arr[right];       // Add new
        windowSum -= arr[right - k];   // Remove old
        result = max(result, windowSum);
    }

    return result;
}
```

## Substring Pattern Template

```cpp
int substringPattern(string s, string pattern) {
    unordered_map<char, int> need;
    for (char c : pattern) need[c]++;

    unordered_map<char, int> window;
    int left = 0;
    int formed = 0;  // How many unique chars are satisfied
    int required = need.size();
    
    int minLen = INT_MAX;
    int minStart = 0;

    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        window[c]++;

        // Check if this character's requirement is met
        if (need.count(c) && window[c] == need[c]) {
            formed++;
        }

        // Try to shrink window while still valid
        while (formed == required && left <= right) {
            // Update result
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            // Shrink from left
            char leftChar = s[left];
            window[leftChar]--;
            if (need.count(leftChar) && window[leftChar] < need[leftChar]) {
                formed--;
            }
            left++;
        }
    }

    return (minLen == INT_MAX) ? 0 : minLen;
}
```

---

# Easy Problems

---

## E1. Maximum Average Subarray I (LeetCode 643)

```cpp
/*
 * Problem: 643. Maximum Average Subarray I
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums and integer k, find a contiguous
 * subarray of length k that has the maximum average value.
 * Return the maximum average.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Classic fixed-size sliding window.
 * Maximum average = maximum sum (since k is fixed).
 *
 * Build first window of size k, then slide one position at a time:
 * - Add new element on right
 * - Remove old element on left
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH: Fixed Window
 *
 * 1. Compute sum of first k elements
 * 2. Slide window: for i from k to n-1:
 *    - Add nums[i]
 *    - Subtract nums[i-k]
 *    - Track maximum sum
 * 3. Return maxSum / k
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * nums = [1,12,-5,-6,50,3], k = 4
 *
 * Initial window [1,12,-5,-6]: sum = 2
 * Slide to [12,-5,-6,50]: sum = 2 - 1 + 50 = 51 ✓ (max)
 * Slide to [-5,-6,50,3]: sum = 51 - 12 + 3 = 42
 *
 * Max sum = 51, average = 51/4 = 12.75 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        // Build initial window
        double windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
        }
        
        double maxSum = windowSum;
        
        // Slide window
        for (int i = k; i < nums.size(); i++) {
            windowSum += nums[i];       // Add new element
            windowSum -= nums[i - k];   // Remove old element
            maxSum = max(maxSum, windowSum);
        }
        
        return maxSum / k;
    }
};
```

---

## E2. Contains Duplicate II (LeetCode 219)

```cpp
/*
 * Problem: 219. Contains Duplicate II
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums and integer k, return true if there
 * are two distinct indices i and j such that nums[i] == nums[j]
 * and abs(i - j) <= k.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Maintain a window of size k.
 * Use a set to track elements in current window.
 * If we see a duplicate → return true.
 * Slide window: remove leftmost element when window exceeds size k.
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH: Fixed Window with Set
 *
 * 1. Use a set to track elements in window
 * 2. For each element:
 *    - If already in set → duplicate within k distance
 *    - Add to set
 *    - If window size > k → remove leftmost element
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * nums = [1,2,3,1], k = 3
 *
 * i=0: set={1}
 * i=1: set={1,2}
 * i=2: set={1,2,3}
 * i=3: 1 in set → return true ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(min(n, k))
 */

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window;
        
        for (int i = 0; i < nums.size(); i++) {
            // Check if current number already in window
            if (window.count(nums[i])) {
                return true;
            }
            
            // Add current number to window
            window.insert(nums[i]);
            
            // Maintain window size <= k
            if (window.size() > k) {
                window.erase(nums[i - k]);
            }
        }
        
        return false;
    }
};
```

---

## E3. Longest Nice Substring (LeetCode 1763)

```cpp
/*
 * Problem: 1763. Longest Nice Substring
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * A string is nice if every letter (both upper and lower case)
 * appears in it. Return the longest nice substring.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * For each possible starting position, expand window and check
 * if current window is nice.
 * A substring is nice if for each character, both its upper
 * and lower case variants exist in the substring.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n²)
 * SPACE: O(1) — constant alphabet size
 */

class Solution {
public:
    string longestNiceSubstring(string s) {
        string result = "";
        
        for (int i = 0; i < s.size(); i++) {
            unordered_set<char> seen;
            
            for (int j = i; j < s.size(); j++) {
                seen.insert(s[j]);
                
                // Check if current window [i, j] is nice
                if (isNice(seen)) {
                    if (j - i + 1 > result.size()) {
                        result = s.substr(i, j - i + 1);
                    }
                }
            }
        }
        
        return result;
    }
    
private:
    bool isNice(unordered_set<char>& seen) {
        for (char c : seen) {
            char opposite = (islower(c)) ? toupper(c) : tolower(c);
            if (!seen.count(opposite)) {
                return false;
            }
        }
        return true;
    }
};
```

---

## E4. Minimum Difference Between Highest and Lowest K Scores (LeetCode 1984)

```cpp
/*
 * Problem: 1984. Minimum Difference Between Highest and Lowest of K Scores
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums (student scores) and integer k,
 * pick k scores to minimize difference between highest and
 * lowest in the selected k scores.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * After sorting, the minimum difference will always be from
 * k CONSECUTIVE elements (no gaps).
 *
 * Use a fixed window of size k and track min difference.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * nums = [9,4,1,7], k = 2
 * After sort: [1,4,7,9]
 *
 * Window [1,4]: diff = 3
 * Window [4,7]: diff = 3
 * Window [7,9]: diff = 2 ✓ (minimum)
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n log n)
 * SPACE: O(1)
 */

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if (k == 1) return 0;
        
        sort(nums.begin(), nums.end());
        
        int minDiff = INT_MAX;
        
        // Fixed window of size k
        for (int i = 0; i + k - 1 < nums.size(); i++) {
            int diff = nums[i + k - 1] - nums[i];
            minDiff = min(minDiff, diff);
        }
        
        return minDiff;
    }
};
```

---

## E5. Defanging an IP Address (LeetCode 1108)

```cpp
/*
 * Problem: 1108. Defanging an IP Address
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given a valid IP address, return a defanged version where
 * every "." is replaced with "[.]".
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Not really sliding window, but demonstrates
 * single-pass string processing.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n)
 */

class Solution {
public:
    string defangIPaddr(string address) {
        string result;
        for (char c : address) {
            if (c == '.') {
                result += "[.]";
            } else {
                result += c;
            }
        }
        return result;
    }
};
```

---

## E6. Check if All Characters Have Equal Number of Occurrences (LeetCode 1941)

```cpp
/*
 * Problem: 1941. Check if All Characters Have Equal Number of Occurrences
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given a string s, return true if all characters have the
 * same frequency, false otherwise.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Single pass with frequency map.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1) — at most 26 letters
 */

class Solution {
public:
    bool areOccurrencesEqual(string s) {
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }
        
        int target = freq[s[0]];
        for (auto& [ch, count] : freq) {
            if (count != target) return false;
        }
        
        return true;
    }
};
```

---

## E7. Maximum Number of Vowels in a Substring (LeetCode 1456)

```cpp
/*
 * Problem: 1456. Maximum Number of Vowels in a Substring of Given Length
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given string s and integer k, return the maximum number of
 * vowel letters in any substring of s with length k.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Fixed window of size k, count vowels.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * s = "abciiidef", k = 3
 *
 * Window "abc": vowels = 1
 * Window "bci": vowels = 1
 * Window "cii": vowels = 2
 * Window "iii": vowels = 3 ✓ (max)
 * ...
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int maxVowels(string s, int k) {
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        
        // Build initial window
        int vowelCount = 0;
        for (int i = 0; i < k; i++) {
            if (isVowel(s[i])) vowelCount++;
        }
        
        int maxVowels = vowelCount;
        
        // Slide window
        for (int i = k; i < s.size(); i++) {
            if (isVowel(s[i])) vowelCount++;           // Add new
            if (isVowel(s[i - k])) vowelCount--;       // Remove old
            maxVowels = max(maxVowels, vowelCount);
        }
        
        return maxVowels;
    }
};
```

---

## E8. Number of Sub-arrays of Size K and Average ≥ Threshold (LeetCode 1343)

```cpp
/*
 * Problem: 1343. Number of Sub-arrays of Size K and Average >= Threshold
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given array arr, integers k and threshold, return the number
 * of subarrays of size k with average >= threshold.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Average >= threshold → Sum >= threshold * k
 * Fixed window, count how many windows satisfy the condition.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int targetSum = k * threshold;
        
        // Build initial window
        int windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        
        int count = (windowSum >= targetSum) ? 1 : 0;
        
        // Slide window
        for (int i = k; i < arr.size(); i++) {
            windowSum += arr[i];
            windowSum -= arr[i - k];
            
            if (windowSum >= targetSum) count++;
        }
        
        return count;
    }
};
```

---

## E9. Diet Plan Performance (LeetCode 1176)

```cpp
/*
 * Problem: 1176. Diet Plan Performance
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given calories array, integers k, lower, upper:
 * - Divide into consecutive sequences of k days
 * - For each sequence:
 *   • If sum < lower → lose 1 point
 *   • If sum > upper → gain 1 point
 * Return total points.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Fixed window of size k.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int dietPlanPerformance(vector<int>& calories, int k, 
                            int lower, int upper) {
        int points = 0;
        int windowSum = 0;
        
        // Build initial window
        for (int i = 0; i < k; i++) {
            windowSum += calories[i];
        }
        
        if (windowSum < lower) points--;
        else if (windowSum > upper) points++;
        
        // Slide window
        for (int i = k; i < calories.size(); i++) {
            windowSum += calories[i];
            windowSum -= calories[i - k];
            
            if (windowSum < lower) points--;
            else if (windowSum > upper) points++;
        }
        
        return points;
    }
};
```

---

## E10. Find K-Length Substrings With No Repeated Characters (LeetCode 1100)

```cpp
/*
 * Problem: 1100. Find K-Length Substrings With No Repeated Characters
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given string s and integer k, return the number of substrings
 * of length k with all unique characters.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Fixed window of size k with a set to track duplicates.
 * If set size == k → all unique.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * s = "havefunonleetcode", k = 5
 *
 * Window "havef": {h,a,v,e,f} size=5 → count++
 * Window "avefu": {a,v,e,f,u} size=5 → count++
 * ...
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n × k) worst case, O(n) average with early termination
 * SPACE: O(k)
 */

class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        if (k > s.size()) return 0;
        
        int count = 0;
        
        for (int i = 0; i + k <= s.size(); i++) {
            unordered_set<char> window;
            bool valid = true;
            
            for (int j = i; j < i + k; j++) {
                if (window.count(s[j])) {
                    valid = false;
                    break;
                }
                window.insert(s[j]);
            }
            
            if (valid) count++;
        }
        
        return count;
    }
    
    // Optimized version with sliding set
    int numKLenSubstrNoRepeats_v2(string s, int k) {
        if (k > s.size()) return 0;
        
        unordered_map<char, int> freq;
        int count = 0;
        
        // Build first window
        for (int i = 0; i < k; i++) {
            freq[s[i]]++;
        }
        
        if (freq.size() == k) count++;
        
        // Slide window
        for (int i = k; i < s.size(); i++) {
            freq[s[i]]++;
            freq[s[i - k]]--;
            if (freq[s[i - k]] == 0) {
                freq.erase(s[i - k]);
            }
            
            if (freq.size() == k) count++;
        }
        
        return count;
    }
};
```

---

## E11. Maximum Points You Can Obtain from Cards (LeetCode 1423)

```cpp
/*
 * Problem: 1423. Maximum Points You Can Obtain from Cards
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array cardPoints and integer k, in one step
 * you can take one card from the beginning or end of the row.
 * Find maximum score after exactly k steps.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Taking k cards from ends = leaving (n-k) cards in middle.
 * To MAXIMIZE taken cards = MINIMIZE middle cards.
 * Find minimum sum subarray of size (n-k).
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * cardPoints = [1,2,3,4,5,6,1], k = 3
 * n = 7, need to leave n-k=4 cards in middle
 *
 * Total = 22
 * Window [1,2,3,4]: sum=10, taken=22-10=12
 * Window [2,3,4,5]: sum=14, taken=22-14=8
 * Window [3,4,5,6]: sum=18, taken=22-18=4
 * Window [4,5,6,1]: sum=16, taken=22-16=6
 *
 * Maximum taken = 12 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int windowSize = n - k;
        
        if (windowSize == 0) {
            return accumulate(cardPoints.begin(), cardPoints.end(), 0);
        }
        
        // Total sum
        int total = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        
        // Find minimum sum of window size (n-k)
        int windowSum = 0;
        for (int i = 0; i < windowSize; i++) {
            windowSum += cardPoints[i];
        }
        
        int minWindowSum = windowSum;
        
        // Slide window
        for (int i = windowSize; i < n; i++) {
            windowSum += cardPoints[i];
            windowSum -= cardPoints[i - windowSize];
            minWindowSum = min(minWindowSum, windowSum);
        }
        
        return total - minWindowSum;
    }
};
```

---

## E12. Minimum Recolors to Get K Consecutive Black Blocks (LeetCode 2379)

```cpp
/*
 * Problem: 2379. Minimum Recolors to Get K Consecutive Black Blocks
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given string blocks consisting of 'W' and 'B' and integer k,
 * return minimum recolors to get k consecutive 'B' blocks.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Fixed window of size k.
 * Count 'W's in window → that's the recolor cost.
 * Find window with minimum 'W's.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        // Count whites in first window
        int whiteCount = 0;
        for (int i = 0; i < k; i++) {
            if (blocks[i] == 'W') whiteCount++;
        }
        
        int minRecolors = whiteCount;
        
        // Slide window
        for (int i = k; i < blocks.size(); i++) {
            if (blocks[i] == 'W') whiteCount++;
            if (blocks[i - k] == 'W') whiteCount--;
            minRecolors = min(minRecolors, whiteCount);
        }
        
        return minRecolors;
    }
};
```

---

## E13. Maximum Sum of Almost Unique Subarray (LeetCode 2461)

```cpp
/*
 * Problem: 2461. Maximum Sum of Almost Unique Subarray
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums, integers m and k, return maximum
 * sum of subarray of length m with at least k distinct elements.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Fixed window of size m, track distinct count with map.
 * If distinct >= k → valid, track max sum.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(m)
 */

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        // Note: This is the correct solution for the problem
        // where we need ALL distinct (k = window size)
        
        unordered_map<int, int> freq;
        long long windowSum = 0;
        long long maxSum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;
            windowSum += nums[i];
            
            // Maintain window size k
            if (i >= k) {
                freq[nums[i - k]]--;
                if (freq[nums[i - k]] == 0) {
                    freq.erase(nums[i - k]);
                }
                windowSum -= nums[i - k];
            }
            
            // Check if window has exactly k distinct elements
            if (i >= k - 1 && freq.size() == k) {
                maxSum = max(maxSum, windowSum);
            }
        }
        
        return maxSum;
    }
};
```

---

## E14. Find the K-Beauty of a Number (LeetCode 2269)

```cpp
/*
 * Problem: 2269. Find the K-Beauty of a Number
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * K-beauty of integer num = count of k-digit substrings that:
 * 1. Divide num evenly
 * 2. Have no leading zeros
 * Return k-beauty of num.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Convert to string, slide window of size k.
 * For each window: convert to int, check divisibility.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n) where n = number of digits
 * SPACE: O(n)
 */

class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int count = 0;
        
        for (int i = 0; i + k <= s.size(); i++) {
            string window = s.substr(i, k);
            int divisor = stoi(window);
            
            if (divisor != 0 && num % divisor == 0) {
                count++;
            }
        }
        
        return count;
    }
};
```

---

## E15. Count Number of Nice Subarrays (LeetCode 1248) — Easy/Medium boundary

```cpp
/*
 * Problem: 1248. Count Number of Nice Subarrays
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given array nums and integer k, return number of nice subarrays.
 * Nice subarray = subarray with exactly k odd numbers.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Exactly k = atMost(k) - atMost(k-1)
 *
 * atMost(k): Variable window, count how many subarrays have
 * at most k odd numbers.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
    
private:
    int atMost(vector<int>& nums, int k) {
        int left = 0;
        int oddCount = 0;
        int result = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] % 2 == 1) oddCount++;
            
            // Shrink while too many odds
            while (oddCount > k) {
                if (nums[left] % 2 == 1) oddCount--;
                left++;
            }
            
            // All subarrays ending at right are valid
            result += right - left + 1;
        }
        
        return result;
    }
};
```

---

# Medium Problems

---

## M1. Longest Substring Without Repeating Characters (LeetCode 3)

```cpp
/*
 * Problem: 3. Longest Substring Without Repeating Characters
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given string s, find length of longest substring without
 * repeating characters.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Variable window with HashMap.
 * Expand right, add character.
 * If duplicate found → shrink from left until duplicate removed.
 *
 * OPTIMIZATION:
 * Instead of shrinking one by one, jump left pointer directly
 * to position after previous occurrence of duplicate character.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * s = "abcabcbb"
 *
 * right=0 'a': window={a:0}, len=1
 * right=1 'b': window={a:0,b:1}, len=2
 * right=2 'c': window={a:0,b:1,c:2}, len=3
 * right=3 'a': duplicate! left jumps to 0+1=1
 *              window={b:1,c:2,a:3}, len=3
 * right=4 'b': duplicate! left jumps to 1+1=2
 *              window={c:2,a:3,b:4}, len=3
 * ...
 * Max length = 3 ("abc") ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(min(n, charset))
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastIndex;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            
            // If char seen before and within current window
            if (lastIndex.count(c) && lastIndex[c] >= left) {
                left = lastIndex[c] + 1;  // Jump left pointer
            }
            
            lastIndex[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```

---

## M2. Longest Repeating Character Replacement (LeetCode 424)

```cpp
/*
 * Problem: 424. Longest Repeating Character Replacement
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given string s and integer k, you can change at most k chars.
 * Return length of longest substring containing same letter.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * A window is valid if:
 *   (window_size - max_freq) <= k
 *
 * Where max_freq = frequency of most common char in window.
 * This means we need to replace at most k characters.
 *
 * KEY INSIGHT: We don't need to decrease maxFreq when shrinking!
 * We're looking for MAXIMUM window, so we only care when
 * maxFreq increases.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * s = "AABABBA", k = 1
 *
 * right=0 'A': freq={A:1}, maxFreq=1, size=1, need=0 ✓
 * right=1 'A': freq={A:2}, maxFreq=2, size=2, need=0 ✓
 * right=2 'B': freq={A:2,B:1}, maxFreq=2, size=3, need=1 ✓
 * right=3 'A': freq={A:3,B:1}, maxFreq=3, size=4, need=1 ✓
 * right=4 'B': freq={A:3,B:2}, maxFreq=3, size=5, need=2 > k
 *              shrink: left=1, size=4, need=1 ✓
 * ...
 * Max length = 4 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1) — at most 26 uppercase letters
 */

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.size(); right++) {
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            
            int windowSize = right - left + 1;
            int replacements = windowSize - maxFreq;
            
            // If too many replacements needed, shrink
            if (replacements > k) {
                freq[s[left] - 'A']--;
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```

---

## M3. Minimum Size Subarray Sum (LeetCode 209)

```cpp
/*
 * Problem: 209. Minimum Size Subarray Sum
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given array of positive integers nums and positive integer target,
 * return minimal length of contiguous subarray with sum >= target.
 * Return 0 if no such subarray.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Variable window for MINIMUM length.
 * Expand until sum >= target.
 * Then shrink as much as possible while maintaining sum >= target.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * nums = [2,3,1,2,4,3], target = 7
 *
 * right=0: sum=2 < 7
 * right=1: sum=5 < 7
 * right=2: sum=6 < 7
 * right=3: sum=8 >= 7 ✓ len=4
 *   shrink: sum=6 < 7, stop
 * right=4: sum=10 >= 7 ✓ len=4
 *   shrink: sum=8 >= 7 ✓ len=3
 *   shrink: sum=7 >= 7 ✓ len=2 (minimum!)
 *   shrink: sum=6 < 7, stop
 * ...
 * Min length = 2 ([4,3]) ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n) — each element added/removed once
 * SPACE: O(1)
 */

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int sum = 0;
        int minLen = INT_MAX;
        
        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];
            
            // Shrink while sum is still valid
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

## M4. Fruit Into Baskets (LeetCode 904)

```cpp
/*
 * Problem: 904. Fruit Into Baskets
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array fruits where fruits[i] is type of fruit.
 * You have 2 baskets, each basket can hold only 1 type.
 * Return maximum number of fruits you can collect.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * "2 baskets" = "at most 2 distinct types"
 * = Longest subarray with at most 2 distinct elements
 *
 * Variable window, shrink when > 2 distinct types.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * fruits = [1,2,1,2,3]
 *
 * Window [1,2,1,2]: distinct={1,2}, len=4 ✓
 * Add 3: [1,2,1,2,3] distinct={1,2,3} > 2
 *   Shrink: [2,1,2,3] distinct={1,2,3} > 2
 *   Shrink: [1,2,3] distinct={1,2,3} > 2
 *   Shrink: [2,3] distinct={2,3}, len=2
 *
 * Max = 4 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1) — at most 2 types in map
 */

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> basket;
        int left = 0;
        int maxFruits = 0;
        
        for (int right = 0; right < fruits.size(); right++) {
            basket[fruits[right]]++;
            
            // Shrink while more than 2 types
            while (basket.size() > 2) {
                basket[fruits[left]]--;
                if (basket[fruits[left]] == 0) {
                    basket.erase(fruits[left]);
                }
                left++;
            }
            
            maxFruits = max(maxFruits, right - left + 1);
        }
        
        return maxFruits;
    }
};
```

---

## M5. Max Consecutive Ones III (LeetCode 1004)

```cpp
/*
 * Problem: 1004. Max Consecutive Ones III
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given binary array nums and integer k, return maximum
 * number of consecutive 1s if you can flip at most k 0s.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Variable window: allow at most k zeros in window.
 * Shrink when zeros > k.
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN:
 * nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 *
 * Window [1,1,1,0,0]: zeros=2, len=5
 * Add 0: [1,1,1,0,0,0] zeros=3 > k
 *   Shrink until zeros<=2: [0,0,0,1,1,1,1], zeros=3
 *   Continue shrinking...
 * Window [0,1,1,1,1,0]: zeros=2, len=6 ✓
 *
 * Max = 6 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1)
 */

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int zeros = 0;
        int maxLen = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) zeros++;
            
            // Shrink while too many zeros
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

## M6. Longest Substring with At Most K Distinct Characters (LeetCode 340)

```cpp
/*
 * Problem: 340. Longest Substring with At Most K Distinct Characters
 * TIME: O(n) | SPACE: O(k)
 */
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> freq;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.size(); right++) {
            freq[s[right]]++;
            
            while (freq.size() > k) {
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

## M7-M15. Additional Medium Problems (Summary)

- **M7. Permutation in String (LeetCode 567)** — Fixed window + freq map
- **M8. Find All Anagrams (LeetCode 438)** — Fixed window, track matches
- **M9. Subarray Product Less Than K (LeetCode 713)** — Variable window with product
- **M10. Grumpy Bookstore Owner (LeetCode 1052)** — Fixed window to maximize satisfaction
- **M11. Longest Turbulent Subarray (LeetCode 978)** — Track alternating comparisons
- **M12. Get Equal Substrings Within Budget (LeetCode 1208)** — Variable window with cost
- **M13. Replace Substring for Balanced String (LeetCode 1234)** — Shrinkable window
- **M14. Longest Continuous Subarray (LeetCode 1438)** — Monotonic deque
- **M15. Number of Substrings (LeetCode 1358)** — Count all valid windows

---

# Hard Problems

## H1. Minimum Window Substring (LeetCode 76)

```cpp
/*
 * Problem: 76. Minimum Window Substring
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given strings s and t, return minimum window substring of s
 * containing all characters of t (including duplicates).
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Two HashMaps approach:
 * - need: character requirements from t
 * - window: current window character counts
 * - formed: how many unique chars have met requirement
 *
 * Expand until all chars satisfied.
 * Then shrink to minimize window.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(|s| + |t|)
 * SPACE: O(|s| + |t|)
 */

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";
        
        unordered_map<char, int> need;
        for (char c : t) need[c]++;
        
        unordered_map<char, int> window;
        int left = 0;
        int formed = 0;
        int required = need.size();
        
        int minLen = INT_MAX;
        int minStart = 0;
        
        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            window[c]++;
            
            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }
            
            // Shrink while still valid
            while (formed == required && left <= right) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }
                
                char leftChar = s[left];
                window[leftChar]--;
                if (need.count(leftChar) && window[leftChar] < need[leftChar]) {
                    formed--;
                }
                left++;
            }
        }
        
        return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
    }
};
```

## H2. Sliding Window Maximum (LeetCode 239)

```cpp
/*
 * Problem: 239. Sliding Window Maximum
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH: Monotonic Deque
 *
 * Maintain deque in DECREASING order of values.
 * Front always contains index of maximum in current window.
 *
 * TIME: O(n) | SPACE: O(k)
 */

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;  // Stores indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices outside window
            if (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            
            // Maintain decreasing order
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add to result when window is full
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
```

## H3-H15. Additional Hard Problems (Summary)

- **H3. Longest Substring with At Most Two Distinct (LeetCode 159)** — Similar to M6
- **H4. Subarrays with K Different Integers (LeetCode 992)** — Exactly K = atMost(K) - atMost(K-1)
- **H5. Shortest Subarray with Sum ≥ K (LeetCode 862)** — Prefix sums + monotonic deque
- **H6. Minimum Window Subsequence (LeetCode 727)** — Two-pointer with forward/backward scan
- **H7. Shortest Subarray to Remove (LeetCode 1574)** — Find longest non-decreasing subarray
- **H8. Constrained Subsequence Sum (LeetCode 1425)** — DP + monotonic deque
- **H9. Jump Game VI (LeetCode 1696)** — DP + sliding window max
- **H10. Frequency of Most Frequent Element (LeetCode 1838)** — Binary search + window
- **H11. Minimum Adjacent Swaps (LeetCode 1963)** — Two windows
- **H12. Count Subarrays With Score < K (LeetCode 2302)** — Binary search + window
- **H13. Maximum Elegance (LeetCode 2813)** — Greedy + window
- **H14. Count Substrings (LeetCode 2943)** — Complex frequency tracking
- **H15. Subsequence With Largest Sum (LeetCode 2945)** — DP + window

---

# Pattern Recognition Guide

## Decision Tree

```
┌─────────────────────────────────────────────────────────────┐
│ START: Does problem involve contiguous elements?            │
└─────────────────────────────────────────────────────────────┘
                         │
                         ▼
                    ┌─────────┐
                    │   YES   │
                    └─────────┘
                         │
          ┌──────────────┼──────────────┐
          │                             │
    [Fixed Size?]                [Variable Size?]
          │                             │
          ▼                             ▼
    ┌──────────────┐           ┌──────────────┐
    │ Template 1:  │           │ Template 2:  │
    │ Fixed Window │           │ Variable Win │
    └──────────────┘           └──────────────┘
          │                             │
    Examples:                     Examples:
    • Max/min of k               • Longest substring
    • Average                    • At most k distinct
    • K consecutive              • Without repeating
                                 • With constraint
```

## Signal → Pattern Mapping

```
SIGNALS                              → PATTERN
══════════════════════════════════════════════════════════════
"size k"                             → Fixed Window
"k consecutive elements"             → Fixed Window
"at most k distinct"                 → Variable Window
"longest substring with..."          → Variable Window (maximize)
"shortest subarray with..."          → Variable Window (minimize)
"without repeating"                  → Variable + HashMap
"all characters of pattern"          → Fixed + Two HashMaps
"exactly k"                          → atMost(k) - atMost(k-1)
"maximum/minimum in each window"     → Monotonic Deque
"all anagrams"                       → Fixed + Frequency Match
```

---

# Common Mistakes & How to Avoid

## Mistake 1: Wrong Window Size Calculation

```cpp
// ❌ WRONG
int windowSize = right - left;

// ✅ CORRECT
int windowSize = right - left + 1;
// Window [left, right] INCLUSIVE has (right - left + 1) elements
```

## Mistake 2: Not Updating Window State When Adding

```cpp
// ❌ WRONG
for (int right = 0; right < n; right++) {
    // Forgot to add nums[right] to window
    while (invalid) {
        left++;
    }
}

// ✅ CORRECT
for (int right = 0; right < n; right++) {
    windowSum += nums[right];  // ADD first!
    while (windowSum > target) {
        windowSum -= nums[left];
        left++;
    }
}
```

## Mistake 3: Fixed Window — Incorrect Sliding

```cpp
// ❌ WRONG
for (int i = 0; i < n - k; i++) {
    int sum = 0;
    for (int j = i; j < i + k; j++) {  // O(n×k) — recomputing each time!
        sum += nums[j];
    }
}

// ✅ CORRECT — O(n)
int sum = 0;
for (int i = 0; i < k; i++) sum += nums[i];  // Initial window
for (int i = k; i < n; i++) {
    sum += nums[i] - nums[i - k];  // Slide: add new, remove old
}
```

## Mistake 4: Off-by-One in Fixed Window Start

```cpp
// ❌ WRONG
for (int i = k; i < n; i++) {
    sum += nums[i];
    sum -= nums[i - k - 1];  // Wrong! Should be i - k
}

// ✅ CORRECT
for (int i = k; i < n; i++) {
    sum += nums[i];       // Add element at index i
    sum -= nums[i - k];   // Remove element k positions back
}
```

## Mistake 5: Forgetting to Clean Up HashMap

```cpp
// ❌ WRONG
while (freq.size() > k) {
    freq[s[left]]--;
    left++;  // Forgot to remove if count reaches 0
}

// ✅ CORRECT
while (freq.size() > k) {
    freq[s[left]]--;
    if (freq[s[left]] == 0) {
        freq.erase(s[left]);  // Remove entry when count is 0
    }
    left++;
}
```

## Mistake 6: Minimization — Updating Result Before Shrinking

```cpp
// ❌ WRONG — Updates too early
for (int right = 0; right < n; right++) {
    sum += nums[right];
    minLen = min(minLen, right - left + 1);  // Wrong position!
    while (sum >= target) {
        left++;
    }
}

// ✅ CORRECT — Update INSIDE shrink loop
for (int right = 0; right < n; right++) {
    sum += nums[right];
    while (sum >= target) {
        minLen = min(minLen, right - left + 1);  // Update here!
        sum -= nums[left];
        left++;
    }
}
```

---

# Optimization Techniques

## Technique 1: Monotonic Deque for Min/Max in Window

**Use when:** Need min/max of every window efficiently.

```cpp
// Maintain deque in INCREASING order for minimum
// Maintain deque in DECREASING order for maximum

deque<int> dq;  // Stores indices

for (int i = 0; i < n; i++) {
    // Remove out-of-window indices
    while (!dq.empty() && dq.front() < i - k + 1) {
        dq.pop_front();
    }
    
    // Maintain monotonic property
    while (!dq.empty() && nums[dq.back()] < nums[i]) {  // For max
        dq.pop_back();
    }
    
    dq.push_back(i);
    
    if (i >= k - 1) {
        result.push_back(nums[dq.front()]);  // Front is the max/min
    }
}
```

## Technique 2: Exactly K = atMost(K) - atMost(K-1)

**Use when:** Need "exactly k" distinct/odd/even elements.

```cpp
int exactlyK(vector<int>& nums, int k) {
    return atMostK(nums, k) - atMostK(nums, k - 1);
}

int atMostK(vector<int>& nums, int k) {
    // Standard variable window
    int left = 0, count = 0;
    unordered_map<int, int> freq;
    
    for (int right = 0; right < nums.size(); right++) {
        freq[nums[right]]++;
        
        while (freq.size() > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        
        count += right - left + 1;  // All subarrays ending at right
    }
    
    return count;
}
```

## Technique 3: Two-Pass for Bidirectional Constraints

**Use when:** Need to consider both left and right constraints.

```cpp
// Example: Longest subarray where |arr[i] - arr[j]| <= limit
int longestSubarray(vector<int>& nums, int limit) {
    multiset<int> window;  // Auto-sorted
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        window.insert(nums[right]);
        
        // Max - Min in window
        while (*window.rbegin() - *window.begin() > limit) {
            window.erase(window.find(nums[left]));
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

---

# Practice Strategy

## Phase 1: Master Templates (Week 1)

**Goal:** Write each template from memory without bugs.

| Priority | Problem | Type | Why |
|:---------|:--------|:-----|:----|
| 🔴 | 643. Max Average Subarray | Fixed | Simplest fixed window |
| 🔴 | 3. Longest No Repeat | Variable | Classic variable window |
| 🔴 | 209. Min Size Subarray | Variable (min) | Shrinkable pattern |
| 🔴 | 1456. Max Vowels | Fixed | Practice fixed window |
| 🔴 | 1004. Max Consecutive 1s | Variable | With constraint |

**Practice drill:**
- Code each problem 3 times from scratch
- Time yourself: should complete each in < 10 minutes
- Explain the pattern out loud before coding

---

## Phase 2: Pattern Recognition (Week 2)

**Goal:** Identify which template to use instantly.

| Priority | Problem | Pattern Signal | Template |
|:---------|:--------|:---------------|:---------|
| 🟡 | 904. Fruit Baskets | "at most 2 types" | Variable + Map |
| 🟡 | 424. Char Replacement | "change k chars" | Variable + Freq |
| 🟡 | 438. Find Anagrams | "anagrams" | Fixed + Two Maps |
| 🟡 | 567. Permutation String | "permutation" | Fixed + Two Maps |
| 🟡 | 713. Product < K | "product" | Variable + Product |

**Practice drill:**
- Read problem → identify pattern → choose template
- Don't code yet — just identify the pattern
- Build a "pattern recognition reflex"

---

## Phase 3: Advanced Techniques (Week 3-4)

**Goal:** Master optimizations and hard problems.

| Priority | Problem | Technique | Why |
|:---------|:--------|:----------|:----|
| 🔴 | 76. Min Window Substring | Two maps | Most asked |
| 🔴 | 239. Sliding Window Max | Monotonic deque | Essential trick |
| 🔴 | 992. K Distinct Subarrays | Exactly K trick | Common pattern |
| 🟡 | 862. Shortest Sum ≥ K | Prefix + Deque | Advanced |
| 🟡 | 1438. Absolute Diff ≤ Limit | Multiset/2 deques | Min-max tracking |

**Practice drill:**
- Implement monotonic deque from scratch
- Practice the "exactly K" transformation
- Time constraint: 30 mins per hard problem

---

## Common Interview Variations

```
BASE PROBLEM                      VARIATION TO PRACTICE
══════════════════════════════════════════════════════════════
Longest without repeating    →    Longest with at most k repeats
Fixed window max             →    Fixed window top-k elements
At most k distinct           →    Exactly k distinct
Subarray sum = k             →    Subarray sum divisible by k
Product < k                  →    Sum < k with negatives
```

---

## Complexity Cheat Sheet

```
PATTERN                          TIME       SPACE
══════════════════════════════════════════════════════════════
Fixed Window                     O(n)       O(1) or O(k)
Variable Window                  O(n)       O(1) or O(k)
Window + HashMap                 O(n)       O(k) distinct
Window + Two HashMaps            O(n)       O(|s| + |t|)
Monotonic Deque                  O(n)       O(k)
Exactly K Trick                  O(n)       O(k)
```

---

## Interview Checklist

**Before coding:**
- [ ] Is it CONTIGUOUS? (If not, not sliding window)
- [ ] Fixed or variable window size?
- [ ] Maximize or minimize?
- [ ] What data structure tracks window state?

**While coding:**
- [ ] Initialize left = 0, right in loop
- [ ] Update window state when adding right element
- [ ] Shrink condition correct?
- [ ] Update result at correct position?
- [ ] Window size = right - left + 1

**Edge cases:**
- [ ] Empty array/string
- [ ] Window size > array length
- [ ] All elements same
- [ ] k = 0 or k = n

---

## Quick Reference: When to Use What

```
FIXED WINDOW              VARIABLE WINDOW           MONOTONIC DEQUE
────────────────          ────────────────          ────────────────
✓ Size always k           ✓ "Longest/shortest"      ✓ "Max/min in each window"
✓ "k consecutive"         ✓ "At most k"             ✓ Need O(1) query per window
✓ Moving average          ✓ With constraint         ✓ Max of all k-size windows
✓ All k-size windows      ✓ Dynamic size            ✓ Jump game variants

Example:                  Example:                  Example:
Max avg of k elems        Longest no repeat         Sliding window max
```

---

**End of Sliding Window — Complete C++ Guide** 🚀

*50+ LeetCode Problems · 4 Core Templates · All Optimization Techniques*

---

# Additional Resources & Final Tips

## Template Quick Copy

```cpp
// FIXED WINDOW
int result = 0, sum = 0;
for (int i = 0; i < k; i++) sum += arr[i];
result = sum;
for (int i = k; i < n; i++) {
    sum += arr[i] - arr[i-k];
    result = max(result, sum);
}

// VARIABLE WINDOW (MAXIMIZE)
int left = 0, maxLen = 0;
for (int right = 0; right < n; right++) {
    // Add arr[right]
    while (invalid) {
        // Remove arr[left]
        left++;
    }
    maxLen = max(maxLen, right - left + 1);
}

// VARIABLE WINDOW (MINIMIZE)
int left = 0, minLen = INT_MAX;
for (int right = 0; right < n; right++) {
    // Add arr[right]
    while (still_valid) {
        minLen = min(minLen, right - left + 1);
        // Remove arr[left]
        left++;
    }
}
```

## Key Takeaways

1. **Every element enters and exits window exactly once** → O(n)
2. **Fixed window**: Add right, remove (right - k)
3. **Variable window**: Expand right, contract from left
4. **Maximize**: Track max AFTER expanding
5. **Minimize**: Track min INSIDE shrink loop
6. **Exactly K** = atMost(K) - atMost(K-1)
7. **Min/Max queries** → Monotonic deque

Remember: **Sliding window is about maintaining state efficiently as the window moves!**
