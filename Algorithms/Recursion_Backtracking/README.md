
# Recursion & Backtracking - Complete Guide with LeetCode

## Table of Contents
- [Recursion Fundamentals](#recursion-fundamentals)
- [Recursion Patterns](#recursion-patterns)
- [Backtracking Fundamentals](#backtracking-fundamentals)
- [Backtracking Template](#backtracking-template)
- [LeetCode Problems - Easy](#leetcode-problems---easy)
- [LeetCode Problems - Medium](#leetcode-problems---medium)
- [LeetCode Problems - Hard](#leetcode-problems---hard)
- [Problem Patterns](#problem-patterns)
- [Optimization & Common Mistakes](#optimization--common-mistakes)
- [Practice Strategy](#practice-strategy)

---

# Recursion Fundamentals

## What is Recursion?

**Recursion:** Function calling itself to solve smaller instances of the same problem.

## Key Components

1. **Base Case:** Stopping condition
2. **Recursive Case:** Function calls itself with modified input
3. **Progress:** Each call moves toward base case

## Basic Example

```cpp
// Calculate factorial: n! = n × (n-1)!
int factorial(int n) {
    // Base case
    if (n <= 1) return 1;
    
    // Recursive case
    return n * factorial(n - 1);
}

// Execution: factorial(4)
// 4 * factorial(3)
// 4 * (3 * factorial(2))
// 4 * (3 * (2 * factorial(1)))
// 4 * (3 * (2 * 1))
// 4 * (3 * 2)
// 4 * 6
// 24
```

## Recursion Tree

```
                factorial(4)
                     |
              4 * factorial(3)
                     |
              3 * factorial(2)
                     |
              2 * factorial(1)
                     |
                     1
```

---

# Recursion Patterns

## 1. Linear Recursion

One recursive call per execution

```cpp
// Sum of array elements
int sumArray(int arr[], int n) {
    if (n <= 0) return 0;
    return arr[n-1] + sumArray(arr, n-1);
}
```

## 2. Binary Recursion

Two recursive calls per execution

```cpp
// Fibonacci number
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// Recursion tree for fib(4):
//         fib(4)
//        /      \
//    fib(3)    fib(2)
//    /   \      /   \
// fib(2) fib(1) fib(1) fib(0)
// /   \
//fib(1) fib(0)
```

## 3. Multiple Recursion

More than two recursive calls

```cpp
// Tower of Hanoi
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    towerOfHanoi(n-1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towerOfHanoi(n-1, aux, to, from);
}
```

---

# Backtracking Fundamentals

## What is Backtracking?

**Backtracking:** Algorithmic technique that tries all possible solutions by building candidates incrementally and abandoning them if they don't satisfy constraints.

## Key Concepts

1. **Choice:** Make a choice
2. **Constraint:** Check if choice is valid
3. **Goal:** Check if we reached the solution
4. **Backtrack:** Undo choice and try another

## Visual Example - N-Queens

```
Try placing queen:
[Q _ _ _]     Valid? Yes → Continue
[_ _ Q _]     Valid? Yes → Continue
[_ _ _ _]     Valid? No  → Backtrack
[_ _ _ _]

Backtrack and try:
[Q _ _ _]
[_ _ _ Q]     Valid? No  → Backtrack

Continue exploring...
```

---

# Backtracking Template

## Standard Template

```cpp
void backtrack(state, choices, result) {
    // Base case: found solution
    if (isGoal(state)) {
        result.add(state);
        return;
    }
    
    // Try all choices
    for (choice in choices) {
        // 1. Make choice
        state.add(choice);
        
        // 2. Check constraint (pruning)
        if (isValid(state)) {
            // 3. Recurse
            backtrack(state, newChoices, result);
        }
        
        // 4. Undo choice (backtrack)
        state.remove(choice);
    }
}
```

## Template with Path Tracking

```cpp
void backtrack(vector<int>& nums, vector<int>& path, 
               vector<vector<int>>& result, vector<bool>& used) {
    // Base case
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    
    for (int i = 0; i < nums.size(); i++) {
        // Skip if already used
        if (used[i]) continue;
        
        // Make choice
        path.push_back(nums[i]);
        used[i] = true;
        
        // Recurse
        backtrack(nums, path, result, used);
        
        // Undo choice
        path.pop_back();
        used[i] = false;
    }
}
```

---

# LeetCode Problems - Easy

## 1. Fibonacci Number (LeetCode 509)

**Problem:** Calculate nth Fibonacci number

```cpp
/*
 * Problem: 509. Fibonacci Number
 *
 * Statement:
 * The Fibonacci numbers are defined as:
 *   fib(0) = 0
 *   fib(1) = 1
 *   fib(n) = fib(n-1) + fib(n-2) for n >= 2
 *
 * Given an integer n, return fib(n).
 *
 * ------------------------------------------------------------
 * APPROACH OVERVIEW
 *
 * We discuss 3 common approaches:
 *
 * 1️⃣ Pure Recursion (Brute Force)        → Exponential time
 * 2️⃣ Dynamic Programming (Bottom-Up)    → Linear time
 * 3️⃣ Memoization with Recursion (Top-Down) ✅ (Your Final Choice)
 *
 * ------------------------------------------------------------
 * APPROACH 1: Pure Recursive (Brute Force)
 *
 * Idea:
 * - Directly follow Fibonacci definition
 *
 * Code:
 *   fib(n) = fib(n-1) + fib(n-2)
 *
 * Problems:
 * - Recomputes same subproblems again and again
 * - Very slow for large n
 *
 * Time Complexity: O(2^n)
 * Space Complexity: O(n) (recursion stack)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Dynamic Programming (Bottom-Up)
 *
 * Idea:
 * - Store previously computed values
 * - Build solution iteratively from 0 → n
 *
 * Steps:
 * - dp[0] = 0
 * - dp[1] = 1
 * - dp[i] = dp[i-1] + dp[i-2]
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * ------------------------------------------------------------
 * APPROACH 3: Memoization + Recursion (Top-Down) ✅
 * (This is what your final code uses)
 *
 * Core Idea:
 * - Use recursion but store results to avoid recomputation
 * - Each Fibonacci value is computed only once
 *
 * ------------------------------------------------------------
 * Helper Function: fibo(n, memo)
 *
 * Logic:
 * - If n <= 1 → return n
 * - If memo[n] already computed → return memo[n]
 * - Else:
 *     memo[n] = fibo(n-1) + fibo(n-2)
 *
 * ------------------------------------------------------------
 * Why This Works:
 *
 * - Converts exponential recursion into linear recursion
 * - Retains clean recursive structure
 * - Avoids repeated subproblem computation
 *
 * ------------------------------------------------------------
 * Example:
 *
 * n = 5
 *
 * fib(5)
 *  ├─ fib(4)
 *  │   ├─ fib(3)
 *  │   │   ├─ fib(2)
 *  │   │   └─ fib(1)
 *  │   └─ fib(2)
 *  └─ fib(3)
 *
 * With memoization → each fib(x) computed once
 *
 * ------------------------------------------------------------
 * Time Complexity:
 *
 * - O(n)
 *
 * ------------------------------------------------------------
 * Space Complexity:
 *
 * - O(n) for memo array
 * - O(n) recursion stack
 *
 * ------------------------------------------------------------
 * Interview Notes:
 *
 * - Memoization is preferred when recursion is natural
 * - Bottom-up DP is preferred when recursion stack is a concern
 * - Both DP and memoization reduce time from exponential to linear
 */

class Solution {
private:
    // Helper function for memoized recursion
    int fibo(int n, vector<int> &memo) {
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n];

        memo[n] = fibo(n - 1, memo) + fibo(n - 2, memo);
        return memo[n];
    }

public:
    int fib(int n) {

        /*
        // ---------- APPROACH 1: Pure Recursion ----------
        if(n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
        */

        /*
        // ---------- APPROACH 2: Bottom-Up Dynamic Programming ----------
        if(n <= 1) return n;
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
        */

        // ---------- APPROACH 3: Memoization + Recursion (Chosen) ----------
        vector<int> memo(n + 1, -1);
        return fibo(n, memo);
    }
};
```

## 2. Power of Two (LeetCode 231)

**Problem:** Check if n is power of 2

```cpp
/*
 * Problem: 231. Power of Two
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an integer n, return true if it is a power of two.
 * Otherwise, return false.
 *
 * A number n is a power of two if:
 *   n = 2^k for some integer k ≥ 0
 *
 * ------------------------------------------------------------
 * APPROACH OVERVIEW:
 *
 * We include ALL commonly asked approaches in a single file:
 *
 * 1️⃣ Recursive Division by 2
 * 2️⃣ Iterative Division by 2
 * 3️⃣ Bit Manipulation (Optimal & Interview Favorite)
 *
 * ------------------------------------------------------------
 * APPROACH 1: Recursive Division by 2
 *
 * Idea:
 * - A power of two can be divided by 2 repeatedly
 * - If we finally reach 1 → it is a power of two
 *
 * Steps:
 * - If n == 0 → false
 * - If n == 1 → true
 * - If n is odd → false
 * - Else → recurse on n / 2
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) (recursion stack)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Iterative Division by 2
 *
 * Idea:
 * - Same logic as recursion
 * - Avoid recursion stack
 *
 * Steps:
 * - While n is divisible by 2 → divide by 2
 * - At the end check if n == 1
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 *
 * ------------------------------------------------------------
 * APPROACH 3: Bit Manipulation (Optimal)
 *
 * Key Insight:
 * - A power of two has exactly ONE set bit in binary
 *
 * Examples:
 *   1  → 0001
 *   2  → 0010
 *   4  → 0100
 *   8  → 1000
 *
 * Trick:
 *   n & (n - 1) removes the lowest set bit
 *
 * For powers of two:
 *   n & (n - 1) == 0
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTE:
 *
 * - Start with recursive explanation
 * - Optimize to iterative
 * - End with bit manipulation as final answer
 */

class Solution {
private:
    /* ========================================================
     * APPROACH 1: Recursive Division
     * ======================================================== */
    bool isPowerOfTwoRecursive(int n) {
        if (n == 0) return false;
        if (n == 1) return true;
        return (n % 2 == 0) && isPowerOfTwoRecursive(n / 2);
    }

    /* ========================================================
     * APPROACH 2: Iterative Division
     * ======================================================== */
    bool isPowerOfTwoIterative(int n) {
        if (n <= 0) return false;
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }

    /* ========================================================
     * APPROACH 3: Bit Manipulation (Optimal)
     * ======================================================== */
    bool isPowerOfTwoBitwise(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

public:
    bool isPowerOfTwo(int n) {

        // ======= Select ONE approach =======

        // return isPowerOfTwoRecursive(n);   // Approach 1
        // return isPowerOfTwoIterative(n);   // Approach 2
        return isPowerOfTwoBitwise(n);        // Approach 3 (Recommended)
    }
};
```

## 3. Power of Three (LeetCode 326)

```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 3 != 0) return false;
        return isPowerOfThree(n / 3);
    }
};
```

## 4. Power of Four (LeetCode 342)

```cpp
class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 4 != 0) return false;
        return isPowerOfFour(n / 4);
    }
};
```

## 5. Reverse String (LeetCode 344)

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        helper(s, 0, s.size() - 1);
    }
    
    void helper(vector<char>& s, int left, int right) {
        // Base case
        if (left >= right) return;
        
        // Swap
        swap(s[left], s[right]);
        
        // Recurse
        helper(s, left + 1, right - 1);
    }
};

// Time: O(n)
// Space: O(n) for recursion stack
```

## 6. Climbing Stairs (LeetCode 70)

**Problem:** How many ways to climb n stairs (1 or 2 steps at a time)

```cpp
/*
 * Problem: 70. Climbing Stairs
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * You are climbing a staircase. It takes `n` steps to reach the top.
 * Each time you can either climb 1 step or 2 steps.
 *
 * Return the number of distinct ways to reach the top.
 *
 * ------------------------------------------------------------
 * APPROACH: Recursion + Memoization (Top-Down DP)
 *
 * Core Observation:
 * - To reach step `n`, you must come from:
 *     • step (n - 1)  OR
 *     • step (n - 2)
 *
 * So,
 *   ways(n) = ways(n - 1) + ways(n - 2)
 *
 * This is exactly the Fibonacci pattern.
 *
 * ------------------------------------------------------------
 * WHY NOT PURE RECURSION?
 *
 * Pure recursion recalculates the same subproblems again and again,
 * leading to exponential time complexity.
 *
 * Memoization stores already computed results and avoids recomputation.
 *
 * ------------------------------------------------------------
 * STEP-BY-STEP EXPLANATION:
 *
 * 1️⃣ Define a helper function `helper(n, memo)`:
 *    - Returns number of ways to reach step `n`
 *
 * 2️⃣ Base Cases:
 *    - If n <= 2, return n directly
 *        • n = 1 → 1 way
 *        • n = 2 → 2 ways
 *
 * 3️⃣ Memoization Check:
 *    - If memo[n] is already computed, return it
 *
 * 4️⃣ Recursive Relation:
 *    - memo[n] = helper(n - 1) + helper(n - 2)
 *
 * 5️⃣ Final Answer:
 *    - Call helper(n) from `climbStairs`
 *
 * ------------------------------------------------------------
 * DRY RUN (n = 5):
 *
 * helper(5)
 *  = helper(4) + helper(3)
 *  = (helper(3) + helper(2)) + (helper(2) + helper(1))
 *  = (3 + 2) = 5
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(n) → Each value computed once
 *
 * Space Complexity:
 * - O(n) → Memo array + recursion stack
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - This is a classic DP introduction problem
 * - Fibonacci-based reasoning is expected
 * - Memoization shows optimization awareness
 * - Can be further optimized to O(1) space
 */

class Solution {
private:
    int helper(int n, vector<int> &memo) {
        // Base case
        if (n <= 2) return n;

        // If already computed, return stored value
        if (memo[n] != -1) return memo[n];

        // Compute and store result
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
        return memo[n];
    }

public:
    int climbStairs(int n) {
        // Memo array initialized with -1
        vector<int> memo(n + 1, -1);

        // Start recursion with memoization
        return helper(n, memo);
    }
};
```

---

# LeetCode Problems - Medium

## 7. Subsets (LeetCode 78)

**Problem:** Generate all subsets of given array

```cpp
/*
 * Problem: 78. Subsets
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an integer array nums, return all possible subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets.
 * You may return the solution in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (DFS)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATION:
 *
 * 1️⃣ For every element, we have TWO choices:
 *    - Include the element
 *    - Exclude the element
 *
 * 2️⃣ All subsets can be generated by exploring these choices
 *    recursively while maintaining order.
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * - Use backtracking to build subsets incrementally
 * - At every recursive call:
 *   → Current subset is a valid subset → add it to answer
 * - Move forward to avoid duplicates
 *
 * ------------------------------------------------------------
 * RECURSIVE FUNCTION PARAMETERS:
 *
 * backtrack(start, nums, curr, ans)
 *
 * start → index from where we can pick elements
 * nums  → input array
 * curr  → current subset being formed
 * ans   → stores all subsets
 *
 * ------------------------------------------------------------
 * ALGORITHM STEPS:
 *
 * 1️⃣ Start with an empty subset
 * 2️⃣ Add current subset to answer
 * 3️⃣ Loop from index = start to n-1:
 *    - Pick nums[i]
 *    - Recurse for next index (i + 1)
 *    - Backtrack by removing last element
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [1, 2]
 *
 * Subsets generated:
 * []
 * [1]
 * [1, 2]
 * [2]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(2^n)
 *   (Each element has include/exclude choice)
 *
 * Space Complexity:
 * - O(n) recursion stack
 * - O(2^n) to store all subsets
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic backtracking problem
 * - Always add current subset before branching
 * - Order of recursion ensures no duplicates
 */

class Solution {
private:
    void backtrack(int start,
                   vector<int> nums,
                   vector<int> &curr,
                   vector<vector<int>> &ans) {

        // Current subset is valid → add to answer
        ans.push_back(curr);

        // Explore further elements
        for (int i = start; i < nums.size(); i++) {

            // Choose the current element
            curr.push_back(nums[i]);

            // Recurse with next index
            backtrack(i + 1, nums, curr, ans);

            // Backtrack: remove last chosen element
            curr.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;   // stores all subsets
        vector<int> curr;          // current subset

        // Start backtracking from index 0
        backtrack(0, nums, curr, ans);

        return ans;
    }
};
```

## 8. Subsets II (LeetCode 90)

**Problem:** Generate all unique subsets (with duplicates in input)

```cpp
/*
 * Problem: 90. Subsets II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an integer array nums that may contain duplicates,
 * return all possible subsets (the power set).
 *
 * The solution set must NOT contain duplicate subsets.
 * You may return the solution in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking + Sorting
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ This is similar to the classic Subsets problem,
 *    BUT duplicates are allowed in the input.
 *
 * 2️⃣ To avoid duplicate subsets:
 *    - We must ensure the same number at the same recursive level
 *      is not chosen more than once.
 *
 * 3️⃣ Sorting is essential.
 *    - It groups equal elements together
 *    - Makes it easy to skip duplicates
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * - Sort the input array
 * - Use backtracking to generate subsets
 * - Skip duplicate elements at the same recursion level
 *
 * ------------------------------------------------------------
 * DUPLICATE SKIPPING LOGIC:
 *
 * if (i != start && nums[i] == nums[i - 1]) continue;
 *
 * Meaning:
 * - If current element is the same as the previous one
 * - AND we are at the same recursion level
 * - Then skip it to avoid duplicate subsets
 *
 * ------------------------------------------------------------
 * RECURSIVE FUNCTION PARAMETERS:
 *
 * backtrack(start, nums, curr, ans)
 *
 * start → index from where elements can be picked
 * nums  → sorted input array
 * curr  → current subset
 * ans   → stores all unique subsets
 *
 * ------------------------------------------------------------
 * ALGORITHM STEPS:
 *
 * 1️⃣ Sort nums
 * 2️⃣ Start backtracking from index 0
 * 3️⃣ Add current subset to answer
 * 4️⃣ Loop from index = start to n-1:
 *    - Skip duplicates at same recursion level
 *    - Pick nums[i]
 *    - Recurse with i + 1
 *    - Backtrack by removing last element
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [1, 2, 2]
 *
 * Subsets generated:
 * []
 * [1]
 * [1, 2]
 * [1, 2, 2]
 * [2]
 * [2, 2]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(2^n)
 *   (All possible subsets)
 *
 * Space Complexity:
 * - O(n) recursion stack
 * - O(2^n) to store subsets
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Sorting is mandatory to handle duplicates
 * - The skip condition is the key insight
 * - Very common backtracking interview problem
 */

class Solution {
public:
    void backtrack(int start,
                   vector<int>& nums,
                   vector<int>& curr,
                   vector<vector<int>>& ans) {

        // Current subset is valid → add to answer
        ans.push_back(curr);

        // Try picking elements starting from index 'start'
        for (int i = start; i < nums.size(); i++) {

            // Skip duplicates at the same recursion level
            if (i != start && nums[i] == nums[i - 1])
                continue;

            // Choose current element
            curr.push_back(nums[i]);

            // Recurse for the next index
            backtrack(i + 1, nums, curr, ans);

            // Backtrack: remove last element
            curr.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        // Sort to group duplicates together
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        vector<int> curr;

        // Start backtracking
        backtrack(0, nums, curr, ans);

        return ans;
    }
};
```

## 9. Permutations (LeetCode 46)

**Problem:** Generate all permutations of array

```cpp
/*
 * Problem: 46. Permutations
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array nums of distinct integers,
 * return all possible permutations.
 *
 * You may return the answer in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Swap-Based Permutation Generation)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ A permutation means arranging elements in all possible orders.
 *
 * 2️⃣ At index `idx`, we can choose any element from
 *    idx → n-1 to place at position `idx`.
 *
 * 3️⃣ After fixing one element at position `idx`,
 *    we recursively permute the remaining elements.
 *
 * 4️⃣ Swapping allows in-place generation
 *    → no extra visited array needed.
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * - Fix one position at a time
 * - Swap current index with all possible choices
 * - Recurse for next index
 * - Backtrack (swap back) to restore original state
 *
 * ------------------------------------------------------------
 * RECURSION TREE IDEA:
 *
 * For nums = [1,2,3]
 *
 * idx = 0:
 *   swap(0,0) → [1,2,3]
 *   swap(0,1) → [2,1,3]
 *   swap(0,2) → [3,2,1]
 *
 * Each branch recursively permutes remaining elements.
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If idx == nums.size():
 * → One full permutation is formed
 * → Push into answer
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [1,2]
 *
 * idx = 0:
 *   swap(0,0) → [1,2]
 *     idx = 1:
 *       swap(1,1) → [1,2]
 *       → push
 *
 *   swap(0,1) → [2,1]
 *     idx = 1:
 *       swap(1,1) → [2,1]
 *       → push
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(n!)
 *   (Total permutations)
 *
 * Space Complexity:
 * - O(n) recursion stack
 * - O(n!) for storing results
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Swap-based approach is memory efficient
 * - No extra visited array required
 * - Very common backtracking pattern
 */

class Solution {
private:
    void backtrack(int idx,
                   vector<int>& nums,
                   vector<vector<int>>& ans) {

        // Base case: one permutation formed
        if (idx == nums.size()) {
            ans.push_back(nums);
            return;
        }

        // Try placing every element at position idx
        for (int i = idx; i < nums.size(); i++) {

            // Choose element for current position
            swap(nums[i], nums[idx]);

            // Recurse for next index
            backtrack(idx + 1, nums, ans);

            // Backtrack: restore original order
            swap(nums[i], nums[idx]);
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {

        vector<vector<int>> ans;

        // Start permutation generation from index 0
        backtrack(0, nums, ans);

        return ans;
    }
};
```

## 10. Permutations II (LeetCode 47)

**Problem:** Generate unique permutations (with duplicates)

```cpp
/*
 * Problem: 47. Permutations II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a collection of numbers nums, that might contain duplicates,
 * return all possible unique permutations.
 *
 * You may return the answer in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Swap-Based) + Duplicate Pruning
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ This is similar to the classic Permutations problem,
 *    but nums may contain duplicate elements.
 *
 * 2️⃣ If we generate permutations normally,
 *    duplicate permutations will appear.
 *
 * 3️⃣ To avoid duplicates:
 *    - At each recursion level (fixed index),
 *      do not place the same value twice.
 *
 * ------------------------------------------------------------
 * CORE IDEA:
 *
 * At index `idx`, we try placing every element from
 * idx → n-1 at position `idx`.
 *
 * But before swapping:
 *   - Check whether the same value has already been used
 *     in this position during this recursion level.
 *
 * ------------------------------------------------------------
 * DUPLICATE CHECK LOGIC:
 *
 * bool alreadyUsed = false;
 * for (int j = idx; j < i; j++)
 *     if (nums[j] == nums[i])
 *         alreadyUsed = true;
 *
 * Meaning:
 * - If the same value already appeared between idx and i-1,
 *   skip it to prevent duplicate permutations.
 *
 * ------------------------------------------------------------
 * WHY SORTING?
 *
 * Sorting groups duplicates together.
 * Though this implementation uses manual checking,
 * sorting ensures consistent ordering and correctness.
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If idx == nums.size():
 * → A complete permutation is formed
 * → Add it to answer
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [1,1,2]
 *
 * idx = 0:
 *   i = 0 → use first 1
 *   i = 1 → skip (duplicate 1 already used at this level)
 *   i = 2 → use 2
 *
 * Final unique permutations:
 * [1,1,2]
 * [1,2,1]
 * [2,1,1]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(n! * n)
 *   (Permutation generation + duplicate checking)
 *
 * Space Complexity:
 * - O(n) recursion stack
 * - O(n!) for storing results
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Very common backtracking variation
 * - Key insight: avoid using same value twice at same depth
 * - Swap-based method avoids extra visited array
 */

class Solution {
private:
    void helper(int idx,
                vector<int>& nums,
                vector<vector<int>>& ans) {

        // Base case: full permutation formed
        if (idx == nums.size()) {
            ans.push_back(nums);
            return;
        }

        // Try placing elements at position idx
        for (int i = idx; i < nums.size(); i++) {

            // Check if this value was already used at this level
            bool alreadyUsed = false;
            for (int j = idx; j < i; j++) {
                if (nums[j] == nums[i]) {
                    alreadyUsed = true;
                    break;
                }
            }

            if (alreadyUsed)
                continue;

            // Choose element
            swap(nums[i], nums[idx]);

            // Recurse for next position
            helper(idx + 1, nums, ans);

            // Backtrack
            swap(nums[i], nums[idx]);
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {

        // Sorting helps maintain consistent ordering
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        helper(0, nums, ans);

        return ans;
    }
};
```

## 11. Combination Sum (LeetCode 39)

**Problem:** Find combinations that sum to target (can reuse elements)

```cpp
/*
 * Problem: Combination Sum (Unbounded Version – Pick / Not Pick Style)
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array of integers nums and an integer k (target),
 * return all possible combinations where:
 *
 * - The chosen numbers sum to k
 * - Each number may be used unlimited times
 *
 * The solution set must not contain duplicate combinations.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Pick / Skip Strategy)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ We can reuse the same element multiple times.
 *
 * 2️⃣ At every index i, we have TWO choices:
 *    - Take nums[i]
 *    - Skip nums[i]
 *
 * 3️⃣ If we take the element:
 *    - Reduce target by nums[i]
 *    - Stay at same index (since reuse allowed)
 *
 * 4️⃣ If we skip:
 *    - Move to next index
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * Recursive function:
 *
 * combSum(i, nums, k, comb, ans)
 *
 * i    → current index
 * k    → remaining target
 * comb → current combination
 * ans  → stores final results
 *
 * ------------------------------------------------------------
 * BASE CASES:
 *
 * 1️⃣ If k == 0:
 *    → Valid combination found
 *    → Add to answer
 *
 * 2️⃣ If i == nums.size() OR k < 0:
 *    → No valid solution from here
 *    → Return
 *
 * ------------------------------------------------------------
 * RECURSION TREE IDEA:
 *
 * At each step:
 *
 *         (i, k)
 *        /       \
 *   Take nums[i]   Skip nums[i]
 *     (i, k-x)      (i+1, k)
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [2,3]
 * k = 6
 *
 * Possible combinations:
 * [2,2,2]
 * [3,3]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - Exponential (backtracking)
 *
 * Space Complexity:
 * - O(k) recursion depth (in worst case)
 * - O(k) for current combination storage
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic pick / not-pick recursion pattern
 * - Staying at same index enables unlimited reuse
 * - Often asked as base version before introducing duplicates
 */

class Solution {
private:
    void combSum(int i,
                 vector<int>& nums,
                 int k,
                 vector<int>& comb,
                 vector<vector<int>>& ans) {

        // Valid combination found
        if (k == 0) {
            ans.push_back(comb);
            return;
        }

        // Out of bounds or negative target
        if (i == nums.size() || k < 0)
            return;

        // TAKE current element (stay at same index)
        comb.push_back(nums[i]);
        combSum(i, nums, k - nums[i], comb, ans);
        comb.pop_back();

        // SKIP current element
        combSum(i + 1, nums, k, comb, ans);
    }

public:
    vector<vector<int>> combinationSum(vector<int>& nums, int k) {

        vector<vector<int>> ans;
        vector<int> comb;

        combSum(0, nums, k, comb, ans);

        return ans;
    }
};
```

## 12. Combination Sum II (LeetCode 40)

**Problem:** Find unique combinations that sum to target (no reuse)

```cpp
/*
 * Problem: 40. Combination Sum II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array nums (may contain duplicates) and an integer target,
 * return all unique combinations where:
 *
 * - Each number is used AT MOST once.
 * - The chosen numbers sum to target.
 * - The solution set must not contain duplicate combinations.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking + Sorting + Duplicate Skipping
 *
 * ------------------------------------------------------------
 * KEY DIFFERENCE FROM Combination Sum I:
 *
 * 1️⃣ Each element can be used only once.
 * 2️⃣ Input may contain duplicates.
 * 3️⃣ We must carefully skip duplicates to avoid repeated combinations.
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Sorting is mandatory.
 *    - Groups duplicates together.
 *    - Enables early pruning.
 *    - Makes duplicate skipping easy.
 *
 * 2️⃣ Duplicate Skipping Condition:
 *
 *    if (i > idx && nums[i] == nums[i - 1])
 *        continue;
 *
 *    Meaning:
 *    - If same number appears again at the same recursion level,
 *      skip it to prevent duplicate combinations.
 *
 * 3️⃣ Early Pruning:
 *
 *    if (nums[i] > target)
 *        break;
 *
 *    Since array is sorted, further elements will also exceed target.
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * backtrack(idx, nums, target, curr, result)
 *
 * idx    → starting index for selection
 * target → remaining sum
 * curr   → current combination
 * result → stores valid combinations
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If target == 0:
 * → Valid combination found
 * → Add to result
 *
 * ------------------------------------------------------------
 * RECURSION FLOW:
 *
 * For each index i from idx to n-1:
 *
 *   1️⃣ Skip duplicates at same level
 *   2️⃣ Stop if nums[i] > target
 *   3️⃣ Choose nums[i]
 *   4️⃣ Recurse with i + 1 (since reuse not allowed)
 *   5️⃣ Backtrack
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [10,1,2,7,6,1,5]
 * target = 8
 *
 * After sorting:
 * [1,1,2,5,6,7,10]
 *
 * Output:
 * [1,1,6]
 * [1,2,5]
 * [1,7]
 * [2,6]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - Exponential (backtracking)
 *
 * Space Complexity:
 * - O(target) recursion depth (worst case)
 * - O(k) for storing current combination
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Sorting + duplicate skipping is the core trick
 * - Early pruning significantly reduces recursion
 * - Very common backtracking interview problem
 */

class Solution {
private:
    void backtrack(int idx,
                   vector<int>& nums,
                   int target,
                   vector<int>& curr,
                   vector<vector<int>>& result) {

        // Valid combination found
        if (target == 0) {
            result.push_back(curr);
            return;
        }

        // Explore choices starting from idx
        for (int i = idx; i < nums.size(); i++) {

            // Skip duplicates at the same recursion level
            if (i > idx && nums[i] == nums[i - 1])
                continue;

            // Early pruning
            if (nums[i] > target)
                break;

            // Choose current element
            curr.push_back(nums[i]);

            // Move to next index (no reuse allowed)
            backtrack(i + 1,
                      nums,
                      target - nums[i],
                      curr,
                      result);

            // Backtrack
            curr.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& nums,
                                        int target) {

        // Sort to handle duplicates and pruning
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        vector<int> curr;

        backtrack(0, nums, target, curr, result);

        return result;
    }
};
```

## 13. Combinations (LeetCode 77)

**Problem:** Generate all combinations of k numbers from 1 to n

```cpp
/*
 * Problem: 77. Combinations
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two integers n and k,
 * return all possible combinations of k numbers chosen
 * from the range [1, n].
 *
 * You may return the answer in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Combination Generation)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ We must choose exactly k numbers from 1 to n.
 *
 * 2️⃣ Order does NOT matter in combinations.
 *    [1,2] and [2,1] are the same combination.
 *
 * 3️⃣ To avoid duplicates:
 *    - Always move forward in the number range.
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * - Use backtracking
 * - At each step:
 *   → Pick a number from current start to n
 *   → Recurse with next start = i + 1
 * - Stop when current combination size == k
 *
 * ------------------------------------------------------------
 * RECURSIVE FUNCTION PARAMETERS:
 *
 * helper(start, n, k, ans, curr)
 *
 * start → next number we are allowed to pick
 * n     → upper limit
 * k     → required size
 * ans   → stores final combinations
 * curr  → current combination being built
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If curr.size() == k:
 * → Valid combination formed
 * → Add to answer
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * n = 4, k = 2
 *
 * Output:
 * [1,2]
 * [1,3]
 * [1,4]
 * [2,3]
 * [2,4]
 * [3,4]
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(C(n, k))
 *   (Total combinations generated)
 *
 * Space Complexity:
 * - O(k) recursion stack
 * - O(C(n, k)) to store results
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic backtracking problem
 * - Forward-only selection prevents duplicates
 * - Can be optimized with pruning:
 *   Loop upper bound can be:
 *   i <= n - (k - curr.size()) + 1
 */

class Solution {
private:
    void helper(int start,
                int n,
                int k,
                vector<vector<int>>& ans,
                vector<int>& curr) {

        // Base case: combination of size k formed
        if (curr.size() == k) {
            ans.push_back(curr);
            return;
        }

        // Try all possible next numbers
        for (int i = start; i <= n; i++) {

            // Choose number i
            curr.push_back(i);

            // Recurse with next start
            helper(i + 1, n, k, ans, curr);

            // Backtrack
            curr.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {

        vector<vector<int>> ans;
        vector<int> curr;

        // Start from 1
        helper(1, n, k, ans, curr);

        return ans;
    }
};
```

## 14. Letter Combinations of Phone Number (LeetCode 17)

```cpp
/*
 * Problem: 17. Letter Combinations of a Phone Number
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string digits containing digits from 2-9,
 * return all possible letter combinations that the number
 * could represent (like on a phone keypad).
 *
 * Mapping:
 * 2 → abc
 * 3 → def
 * 4 → ghi
 * 5 → jkl
 * 6 → mno
 * 7 → pqrs
 * 8 → tuv
 * 9 → wxyz
 *
 * Return the answer in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Cartesian Product Generation)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Each digit maps to multiple characters.
 *
 * 2️⃣ For each digit position:
 *    - We must try every possible mapped character.
 *
 * 3️⃣ This forms a recursive tree where:
 *    - Level = digit index
 *    - Branches = number of letters mapped to that digit
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * backtrack(idx, digits, mapping, curr, result)
 *
 * idx     → current position in digits
 * curr    → currently formed string
 * result  → stores final combinations
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If idx == digits.size():
 * → One full combination formed
 * → Add to result
 *
 * ------------------------------------------------------------
 * RECURSION FLOW:
 *
 * For current digit:
 *   1️⃣ Get mapped string
 *   2️⃣ For each character in mapped string:
 *        - Append character
 *        - Recurse for next index
 *        - Backtrack (remove character)
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * digits = "23"
 *
 * 2 → "abc"
 * 3 → "def"
 *
 * Output:
 * ad ae af
 * bd be bf
 * cd ce cf
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(4^n)
 *   (Each digit can map to at most 4 letters)
 *
 * Space Complexity:
 * - O(n) recursion depth
 * - O(4^n) to store results
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic backtracking problem
 * - Essentially generating Cartesian product
 * - Always check for empty input first
 */

class Solution {
private:
    void backtrack(int idx,
                   string digits,
                   vector<string> mapping,
                   string& curr,
                   vector<string>& result) {

        // Base case: full combination formed
        if (idx >= digits.size()) {
            result.push_back(curr);
            return;
        }

        // Get digit and its corresponding letters
        int num = digits[idx] - '0';
        string letters = mapping[num];

        // Try each possible letter
        for (int i = 0; i < letters.size(); i++) {

            curr.push_back(letters[i]);

            backtrack(idx + 1,
                      digits,
                      mapping,
                      curr,
                      result);

            // Backtrack
            curr.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {

        // Edge case: empty input
        if (digits.empty())
            return {};

        // Phone keypad mapping
        vector<string> mapping = {
            "",      // 0
            "",      // 1
            "abc",   // 2
            "def",   // 3
            "ghi",   // 4
            "jkl",   // 5
            "mno",   // 6
            "pqrs",  // 7
            "tuv",   // 8
            "wxyz"   // 9
        };

        vector<string> result;
        string curr;

        backtrack(0, digits, mapping, curr, result);

        return result;
    }
};
```

## 15. Generate Parentheses (LeetCode 22)

```cpp
/*
 * Problem: 22. Generate Parentheses
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an integer n, generate all combinations of
 * well-formed (valid) parentheses consisting of n pairs.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking with Validity Constraints
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Total length of a valid parentheses string = 2 * n.
 *
 * 2️⃣ We must maintain two conditions:
 *
 *    - Number of '(' used cannot exceed n.
 *    - Number of ')' used cannot exceed number of '(' used.
 *
 * 3️⃣ Instead of generating all strings and checking validity,
 *    we enforce validity during generation.
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * backtrack(n, open, close, curr, result)
 *
 * n      → total pairs required
 * open   → number of '(' used so far
 * close  → number of ')' used so far
 * curr   → current parentheses string
 * result → stores valid combinations
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If curr.size() == 2 * n:
 * → Valid parentheses string formed
 * → Add to result
 *
 * ------------------------------------------------------------
 * RECURSION RULES:
 *
 * 1️⃣ Add '(' if open < n
 *
 * 2️⃣ Add ')' if close < open
 *    (Ensures string remains valid at every step)
 *
 * ------------------------------------------------------------
 * RECURSION TREE IDEA:
 *
 * For n = 2:
 *
 * ""
 * ├── "("
 * │   ├── "(("
 * │   │   └── "(())"
 * │   └── "()"
 * │       └── "()()"
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * n = 3
 *
 * Output:
 * ((()))
 * (()())
 * (())()
 * ()(())
 * ()()()
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(Catalan(n))
 * - Approximately O(4^n / sqrt(n))
 *
 * Space Complexity:
 * - O(n) recursion depth
 * - O(Catalan(n)) to store results
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic backtracking problem
 * - Key trick: enforce validity while building string
 * - Do NOT generate all 2^(2n) strings
 * - Use constraints smartly
 */

class Solution {
private:
    void backtrack(int n,
                   int open,
                   int close,
                   string& curr,
                   vector<string>& result) {

        // Base case: valid parentheses string formed
        if (curr.size() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // Add '(' if we still can
        if (open < n) {
            curr.push_back('(');
            backtrack(n, open + 1, close, curr, result);
            curr.pop_back();
        }

        // Add ')' only if it won't invalidate the string
        if (close < open) {
            curr.push_back(')');
            backtrack(n, open, close + 1, curr, result);
            curr.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {

        vector<string> result;
        string curr;

        backtrack(n, 0, 0, curr, result);

        return result;
    }
};

```

## 16. Word Search (LeetCode 79)

```cpp
/*
 * Problem: 79. Word Search
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an m x n grid of characters board and a string word,
 * return true if the word exists in the grid.
 *
 * The word can be constructed from letters of sequentially
 * adjacent cells (up, down, left, right).
 *
 * The same cell may NOT be used more than once.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (DFS on Grid)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ This is a classic grid DFS problem.
 *
 * 2️⃣ From each cell, we can move in 4 directions:
 *    - Up
 *    - Down
 *    - Left
 *    - Right
 *
 * 3️⃣ We must:
 *    - Match characters sequentially
 *    - Mark visited cells temporarily
 *    - Restore the cell after recursion (backtracking)
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * 1️⃣ Try starting DFS from every cell.
 *
 * 2️⃣ Recursive function:
 *
 *    solve(board, word, i, j, idx)
 *
 *    i, j → current position
 *    idx  → index of word we are matching
 *
 * ------------------------------------------------------------
 * BASE CASE:
 *
 * If idx == word.size():
 * → Entire word matched
 * → Return true
 *
 * ------------------------------------------------------------
 * INVALID CONDITIONS:
 *
 * - Out of bounds
 * - Character mismatch
 *
 * ------------------------------------------------------------
 * BACKTRACKING STEP:
 *
 * 1️⃣ Store current character
 * 2️⃣ Mark cell as visited (e.g., '#')
 * 3️⃣ Explore all 4 directions
 * 4️⃣ Restore original character
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * board =
 * [
 *  ['A','B','C','E'],
 *  ['S','F','C','S'],
 *  ['A','D','E','E']
 * ]
 *
 * word = "ABCCED"
 *
 * Path:
 * A → B → C → C → E → D
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(m * n * 4^L)
 *   where L = length of word
 *
 * Space Complexity:
 * - O(L) recursion depth
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic DFS + Backtracking grid problem
 * - Mark and restore technique is crucial
 * - Avoid using extra visited matrix (in-place marking works)
 */

class Solution {
private:
    bool solve(vector<vector<char>>& board,
               string& word,
               int i,
               int j,
               int idx) {

        // All characters matched
        if (idx == word.size())
            return true;

        // Out of bounds or mismatch
        if (i < 0 || i >= board.size() ||
            j < 0 || j >= board[0].size() ||
            board[i][j] != word[idx])
            return false;

        // Store original character
        char temp = board[i][j];

        // Mark as visited
        board[i][j] = '#';

        // Explore all 4 directions
        bool found =
            solve(board, word, i + 1, j, idx + 1) ||
            solve(board, word, i - 1, j, idx + 1) ||
            solve(board, word, i, j + 1, idx + 1) ||
            solve(board, word, i, j - 1, idx + 1);

        // Restore original character (backtrack)
        board[i][j] = temp;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {

        int n = board.size();
        int m = board[0].size();

        // Try starting from each cell
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (solve(board, word, i, j, 0))
                    return true;
            }
        }

        return false;
    }
};

```

## 17. Palindrome Partitioning (LeetCode 131)

```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
    void backtrack(string& s, int start,
                   vector<string>& current, vector<vector<string>>& result) {
        // Base case
        if (start == s.size()) {
            result.push_back(current);
            return;
        }
        
        // Try all possible partitions
        for (int end = start; end < s.size(); end++) {
            if (isPalindrome(s, start, end)) {
                // Choose
                current.push_back(s.substr(start, end - start + 1));
                
                // Explore
                backtrack(s, end + 1, current, result);
                
                // Un-choose
                current.pop_back();
            }
        }
    }
    
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
};

// Example: s = "aab"
// Output: [["a","a","b"],["aa","b"]]

// Time: O(n × 2^n)
// Space: O(n)
```

---

# LeetCode Problems - Hard

## 18. N-Queens (LeetCode 51)

```cpp
/*
 * Problem: 51. N-Queens
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * The n-queens puzzle is the problem of placing n queens
 * on an n × n chessboard such that:
 *
 * - No two queens attack each other.
 *
 * Queens attack:
 * - Same row
 * - Same column
 * - Same diagonal
 *
 * Return all distinct solutions.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking (Column-by-Column Placement)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Place one queen per column.
 *    → This automatically avoids column conflicts.
 *
 * 2️⃣ Before placing a queen at (row, col),
 *    we must check:
 *       - Left row
 *       - Upper-left diagonal
 *       - Lower-left diagonal
 *
 * 3️⃣ We only check LEFT side because:
 *    - We place queens from left → right.
 *
 * ------------------------------------------------------------
 * SAFETY CHECK (isSafe):
 *
 * For position (r, c):
 *
 * 1️⃣ Check upper-left diagonal
 * 2️⃣ Check left row
 * 3️⃣ Check lower-left diagonal
 *
 * If any queen found → not safe.
 *
 * ------------------------------------------------------------
 * RECURSION STRATEGY:
 *
 * solve(col):
 *
 * If col == n:
 *    → Valid configuration found
 *    → Store board
 *
 * Otherwise:
 *    For each row in current column:
 *        - If safe:
 *            - Place queen
 *            - Recurse for next column
 *            - Backtrack
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * n = 4
 *
 * One solution:
 *
 * . Q . .
 * . . . Q
 * Q . . .
 * . . Q .
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(n!)
 *   (Backtracking with branching)
 *
 * Space Complexity:
 * - O(n) recursion stack
 * - O(n²) board storage
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic hard backtracking problem
 * - Optimize safety check using hash arrays for:
 *     row
 *     upper diagonal
 *     lower diagonal
 *   → reduces checking from O(n) to O(1)
 */

class Solution {
private:
    bool isSafe(int r, int c, vector<string> board, int n) {

        int rCopy = r;
        int cCopy = c;

        // Check upper-left diagonal (North-West)
        while (r >= 0 && c >= 0) {
            if (board[r][c] == 'Q')
                return false;
            r--;
            c--;
        }

        r = rCopy;
        c = cCopy;

        // Check left row
        while (c >= 0) {
            if (board[r][c] == 'Q')
                return false;
            c--;
        }

        r = rCopy;
        c = cCopy;

        // Check lower-left diagonal (South-West)
        while (r < n && c >= 0) {
            if (board[r][c] == 'Q')
                return false;
            r++;
            c--;
        }

        return true;
    }

    void solve(int col,
               vector<string>& board,
               vector<vector<string>>& result,
               int n) {

        // All queens placed
        if (col == n) {
            result.push_back(board);
            return;
        }

        // Try placing queen in each row of current column
        for (int row = 0; row < n; row++) {

            if (isSafe(row, col, board, n)) {

                board[row][col] = 'Q';

                solve(col + 1, board, result, n);

                // Backtrack
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {

        vector<vector<string>> result;

        // Initialize empty board
        vector<string> board(n);
        string rowString(n, '.');

        for (int i = 0; i < n; i++) {
            board[i] = rowString;
        }

        solve(0, board, result, n);

        return result;
    }
};

```

## 19. N-Queens II (LeetCode 52)

```cpp
class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<bool> cols(n, false);
        vector<bool> diag1(2*n-1, false);
        vector<bool> diag2(2*n-1, false);
        backtrack(n, 0, cols, diag1, diag2, count);
        return count;
    }
    
    void backtrack(int n, int row, vector<bool>& cols,
                   vector<bool>& diag1, vector<bool>& diag2, int& count) {
        if (row == n) {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n - 1;
            int d2 = row + col;
            
            if (cols[col] || diag1[d1] || diag2[d2]) continue;
            
            cols[col] = diag1[d1] = diag2[d2] = true;
            backtrack(n, row + 1, cols, diag1, diag2, count);
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
};

// Time: O(n!)
// Space: O(n)
```

## 20. Sudoku Solver (LeetCode 37)

```cpp
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board);
    }
    
    bool backtrack(vector<vector<char>>& board) {
        // Find next empty cell
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    // Try digits 1-9
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            // Choose
                            board[i][j] = c;
                            
                            // Explore
                            if (backtrack(board)) return true;
                            
                            // Un-choose
                            board[i][j] = '.';
                        }
                    }
                    return false;  // No valid digit found
                }
            }
        }
        return true;  // All cells filled
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == c) return false;
            
            // Check column
            if (board[i][col] == c) return false;
            
            // Check 3x3 box
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == c) return false;
        }
        return true;
    }
};

// Time: O(9^(n×n)) worst case
// Space: O(n×n)
```

## 21. Word Search II (LeetCode 212)

```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    string word = "";
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Build Trie
        TrieNode* root = new TrieNode();
        for (string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children[c - 'a']) {
                    node->children[c - 'a'] = new TrieNode();
                }
                node = node->children[c - 'a'];
            }
            node->word = word;
        }
        
        // Search board
        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                backtrack(board, i, j, root, result);
            }
        }
        return result;
    }
    
    void backtrack(vector<vector<char>>& board, int i, int j,
                   TrieNode* node, vector<string>& result) {
        char c = board[i][j];
        
        // Boundary checks
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            c == '#' || !node->children[c - 'a']) {
            return;
        }
        
        node = node->children[c - 'a'];
        
        // Found a word
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = "";  // Avoid duplicates
        }
        
        // Mark as visited
        board[i][j] = '#';
        
        // Explore 4 directions
        backtrack(board, i + 1, j, node, result);
        backtrack(board, i - 1, j, node, result);
        backtrack(board, i, j + 1, node, result);
        backtrack(board, i, j - 1, node, result);
        
        // Restore
        board[i][j] = c;
    }
};

// Time: O(m × n × 4^L) where L is max word length
// Space: O(total characters in all words)
```

## 22. Regular Expression Matching (LeetCode 10)

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return backtrack(s, p, 0, 0);
    }
    
    bool backtrack(string& s, string& p, int i, int j) {
        // Base cases
        if (j == p.size()) return i == s.size();
        
        bool firstMatch = (i < s.size() && 
                          (s[i] == p[j] || p[j] == '.'));
        
        // Handle '*' pattern
        if (j + 1 < p.size() && p[j + 1] == '*') {
            // Two choices:
            // 1. Don't use '*' (match zero occurrences)
            // 2. Use '*' if first character matches
            return backtrack(s, p, i, j + 2) ||
                   (firstMatch && backtrack(s, p, i + 1, j));
        }
        
        // No '*', must match current character
        return firstMatch && backtrack(s, p, i + 1, j + 1);
    }
    
    // With memoization
    bool isMatchMemo(string s, string p) {
        vector<vector<int>> memo(s.size() + 1, vector<int>(p.size() + 1, -1));
        return helper(s, p, 0, 0, memo);
    }
    
    bool helper(string& s, string& p, int i, int j,
                vector<vector<int>>& memo) {
        if (memo[i][j] != -1) return memo[i][j];
        
        bool result;
        if (j == p.size()) {
            result = (i == s.size());
        } else {
            bool firstMatch = (i < s.size() && 
                              (s[i] == p[j] || p[j] == '.'));
            
            if (j + 1 < p.size() && p[j + 1] == '*') {
                result = helper(s, p, i, j + 2, memo) ||
                        (firstMatch && helper(s, p, i + 1, j, memo));
            } else {
                result = firstMatch && helper(s, p, i + 1, j + 1, memo);
            }
        }
        
        memo[i][j] = result;
        return result;
    }
};

// Time: O(m × n) with memoization
// Space: O(m × n)
```

## 23. Wildcard Matching (LeetCode 44)

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns like "*", "**", "***"
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // '*' can match empty or any sequence
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// Time: O(m × n)
// Space: O(m × n)
```

---

# Problem Patterns

## Pattern 1: Generate All Solutions
**When to use:** "Find all", "generate all", "list all"  
**Examples:** Subsets (78), Permutations (46), Combinations (77), Letter Combinations (17)

**Template:**
```cpp
void backtrack(state, result) {
    if (isComplete(state)) {
        result.add(state);
        return;
    }
    
    for (choice in choices) {
        state.add(choice);
        backtrack(state, result);
        state.remove(choice);
    }
}
```

## Pattern 2: Find One Solution
**When to use:** "Find if exists", "determine if possible"  
**Examples:** Word Search (79), Sudoku Solver (37)

**Template:**
```cpp
bool backtrack(state) {
    if (isGoal(state)) return true;
    if (isInvalid(state)) return false;
    
    for (choice in choices) {
        state.add(choice);
        if (backtrack(state)) return true;
        state.remove(choice);
    }
    return false;
}
```

## Pattern 3: Count Solutions
**When to use:** "How many ways", "count total"  
**Examples:** N-Queens II (52), Climbing Stairs (70)

**Template:**
```cpp
int backtrack(state) {
    if (isGoal(state)) return 1;
    if (isInvalid(state)) return 0;
    
    int count = 0;
    for (choice in choices) {
        state.add(choice);
        count += backtrack(state);
        state.remove(choice);
    }
    return count;
}
```

## Pattern 4: Optimization Problems
**When to use:** "Find maximum", "find minimum", "best solution"  
**Examples:** Combination Sum (39), Word Break (139)

**Template:**
```cpp
int backtrack(state, best) {
    if (isGoal(state)) {
        best = max(best, evaluate(state));
        return best;
    }
    
    for (choice in choices) {
        if (isPrunable(choice, best)) continue;
        state.add(choice);
        best = backtrack(state, best);
        state.remove(choice);
    }
    return best;
}
```

---

# Optimization & Common Mistakes

## Key Optimization Techniques

### 1. Pruning
Skip branches that cannot lead to valid solutions:
```cpp
// In Combination Sum
if (target < 0) return;  // Prune invalid branches

// In N-Queens
if (!isValid(board, row, col)) continue;  // Skip invalid placements
```

### 2. Memoization
Cache results to avoid recomputation:
```cpp
// Fibonacci with memo
int fib(int n, vector<int>& memo) {
    if (memo[n] != -1) return memo[n];
    memo[n] = fib(n-1, memo) + fib(n-2, memo);
    return memo[n];
}
```

### 3. Early Termination
Stop as soon as solution is found:
```cpp
bool backtrack(state) {
    if (found) return true;  // Early exit
    // ... rest of logic
}
```

### 4. Sorting
Sort input to handle duplicates efficiently:
```cpp
sort(nums.begin(), nums.end());
if (i > start && nums[i] == nums[i-1]) continue;  // Skip duplicates
```

## Common Mistakes to Avoid

### 1. Forgetting Base Case
```cpp
// ❌ Wrong
int factorial(int n) {
    return n * factorial(n - 1);  // Stack overflow!
}

// ✅ Correct
int factorial(int n) {
    if (n <= 1) return 1;  // Base case
    return n * factorial(n - 1);
}
```

### 2. Not Backtracking
```cpp
// ❌ Wrong
void backtrack(vector<int>& path) {
    path.push_back(num);
    backtrack(path);
    // Missing: path.pop_back();
}

// ✅ Correct
void backtrack(vector<int>& path) {
    path.push_back(num);
    backtrack(path);
    path.pop_back();  // Restore state
}
```

### 3. Incorrect State Modification
```cpp
// ❌ Wrong - modifying by reference without restoration
void backtrack(vector<int> nums) {  // Should pass by reference
    nums.push_back(x);
    backtrack(nums);
    // nums still contains x
}

// ✅ Correct
void backtrack(vector<int>& nums) {
    nums.push_back(x);
    backtrack(nums);
    nums.pop_back();  // Restore
}
```

### 4. Duplicate Results
```cpp
// ❌ Wrong - allows duplicates
for (int i = start; i < nums.size(); i++) {
    backtrack(i + 1);
}

// ✅ Correct - handles duplicates
for (int i = start; i < nums.size(); i++) {
    if (i > start && nums[i] == nums[i-1]) continue;
    backtrack(i + 1);
}
```

## Time Complexity Quick Reference

| Problem Type | Time Complexity | Example |
| :--- | :--- | :--- |
| All Subsets | O(2^n) | Subsets |
| All Permutations | O(n!) | Permutations |
| All Combinations | O(C(n,k)) | Combinations |
| N-Queens | O(n!) | N-Queens |
| Sudoku | O(9^(n×n)) | Sudoku Solver |
| Word Search | O(m×n×4^L) | Word Search |
| Combination Sum | O(n^target) | Combination Sum |

---

# Practice Strategy

## Beginner (Easy Problems)
- Start with simple recursion (Fibonacci, Factorial)
- Practice with power functions (Power of Two/Three/Four)
- Try string reversal recursively
- Solve Climbing Stairs

## Intermediate (Medium Problems)
- Master subset generation (78, 90)
- Learn permutation generation (46, 47)
- Practice combination problems (39, 40, 77)
- Solve grid-based problems (79)
- Try string backtracking (17, 22, 131)

## Advanced (Hard Problems)
- N-Queens variants (51, 52)
- Sudoku Solver (37)
- Regular Expression Matching (10)
- Word Search II with Trie (212)

## Additional Resources

### More Easy:
- LeetCode 206: Reverse Linked List
- LeetCode 21: Merge Two Sorted Lists
- LeetCode 100: Same Tree

### More Medium:
- LeetCode 93: Restore IP Addresses
- LeetCode 784: Letter Case Permutation
- LeetCode 494: Target Sum

### More Hard:
- LeetCode 140: Word Break II
- LeetCode 301: Remove Invalid Parentheses
- LeetCode 679: 24 Game

## Key Takeaways
1. Always define base case first
2. Think about what choices you have at each step
3. Remember to backtrack (undo choices)
4. Use pruning to optimize
5. Draw recursion tree for complex problems
6. Practice, practice, practice!

---

**End of Guide**  
Good luck with your recursion and backtracking journey! 🚀
