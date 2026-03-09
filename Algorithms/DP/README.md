# 🧠 Dynamic Programming — Zero to Advanced (C++ & LeetCode)

> Complete guide: intuition, patterns, C++ implementations, and LeetCode problems.

---

## Table of Contents

1. [What is Dynamic Programming?](#1-what-is-dynamic-programming)
2. [The Two Approaches](#2-the-two-approaches)
3. [Recognizing DP Problems](#3-recognizing-dp-problems)
4. [Pattern 01 — 1D Linear DP](#4-pattern-01--1d-linear-dp)
5. [Pattern 02 — 2D Grid DP](#5-pattern-02--2d-grid-dp)
6. [Pattern 03 — Knapsack Variants](#6-pattern-03--knapsack-variants)
7. [Pattern 04 — Subsequence DP](#7-pattern-04--subsequence-dp)
8. [Pattern 05 — Interval DP](#8-pattern-05--interval-dp)
9. [Pattern 06 — Tree DP](#9-pattern-06--tree-dp)
10. [Pattern 07 — Digit DP](#10-pattern-07--digit-dp)
11. [Pattern 08 — Bitmask DP](#11-pattern-08--bitmask-dp)
12. [Pattern 09 — DP on Strings](#12-pattern-09--dp-on-strings)
13. [Pattern 10 — Partition DP](#13-pattern-10--partition-dp)
14. [Space Optimization Techniques](#14-space-optimization-techniques)
15. [Advanced Techniques](#15-advanced-techniques)
16. [LeetCode Problem Index](#16-leetcode-problem-index)
17. [Common Mistakes & Debugging](#17-common-mistakes--debugging)
18. [Quick Reference](#18-quick-reference)

---

## 1. What is Dynamic Programming?

**Dynamic Programming (DP)** is an optimization technique that solves complex problems by breaking them into overlapping subproblems and storing results to avoid redundant computation.

### The Core Idea

```
Brute Force:  Recompute everything  →  Exponential time
Memoization:  Compute + cache       →  Polynomial time
Tabulation:   Build bottom-up       →  Polynomial time
```

### Two Pillars of DP

#### 1. Optimal Substructure
The optimal solution to a problem is built from optimal solutions to its subproblems.

```
shortest(A, C) = shortest(A, B) + shortest(B, C)
```

#### 2. Overlapping Subproblems
The same subproblems recur multiple times in naive recursion.

```
fib(5)
├── fib(4)
│   ├── fib(3)  ← computed again below
│   └── fib(2)
└── fib(3)      ← duplicate!
    ├── fib(2)  ← duplicate!
    └── fib(1)
```

### DP vs Greedy vs Divide & Conquer

| Technique | Subproblems | Overlap | Strategy |
|-----------|-------------|---------|----------|
| Divide & Conquer | Independent | No | Solve all subproblems |
| Greedy | Dependent | N/A | Pick local optimum |
| DP | Overlapping | Yes | Explore all, pick best |

---

## 2. The Two Approaches

### Approach 1: Top-Down (Memoization)

Recurse from original problem, cache every result.

#### C++ Template

```cpp
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, long long> memo;

long long dp(int state) {
    // 1. Check cache
    if (memo.count(state)) return memo[state];
    // 2. Base case
    if (state <= 1) return state;
    // 3. Recurrence
    long long result = dp(state - 1) + dp(state - 2);
    // 4. Store & return
    return memo[state] = result;
}
```

#### Fibonacci — Top-Down (LC 509)

```cpp
class Solution {
    unordered_map<int, int> memo;
public:
    int fib(int n) {
        if (n <= 1) return n;
        if (memo.count(n)) return memo[n];
        return memo[n] = fib(n - 1) + fib(n - 2);
    }
};
// Time: O(n)   Space: O(n)
```

---

### Approach 2: Bottom-Up (Tabulation)

Fill a table starting from smallest subproblems.

#### C++ Template

```cpp
int solve(int n) {
    vector<int> dp(n + 1, 0);
    // Base cases
    dp[0] = 0;
    dp[1] = 1;
    // Fill in order
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];   // recurrence
    }
    return dp[n];
}
```

#### Fibonacci — Bottom-Up (LC 509)

```cpp
class Solution {
public:
    int fib(int n) {
        if (n <= 1) return n;
        vector<int> dp(n + 1);
        dp[0] = 0; dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};
// Time: O(n)   Space: O(n) → O(1) with two variables
```

### Comparison

| Feature | Top-Down | Bottom-Up |
|---------|----------|-----------|
| Style | Recursive | Iterative |
| Ease | Close to brute force | Requires order insight |
| Stack overflow risk | Yes | No |
| Solves only needed states | Yes | No (fills all) |
| Cache locality | Worse | Better |
| Space optimization | Harder | Easier |

### The 5-Step Framework

```
Step 1 — DEFINE:      What does dp[i] (or dp[i][j]) represent?
Step 2 — BASE CASE:   What are the smallest valid states?
Step 3 — RECURRENCE:  How does dp[i] relate to smaller subproblems?
Step 4 — ORDER:       In what order do we fill the table?
Step 5 — ANSWER:      Which cell holds the final answer?
```

---

## 3. Recognizing DP Problems

### Signal Phrases

| Phrase in Problem | Likely DP Pattern |
|-------------------|-------------------|
| "Maximum / minimum" | Optimization DP |
| "Number of ways" | Counting DP |
| "Is it possible" | Boolean DP |
| "Longest / shortest subsequence" | Subsequence DP |
| "Partition into…" | Partition DP |
| "Optimal game strategy" | Game Theory DP |
| "All subsets / combinations" | Knapsack / Bitmask DP |
| "On a tree" | Tree DP |

### Decision Flowchart

```
Can the problem be broken into subproblems?
            ↓ Yes
Do subproblems overlap?
            ↓ Yes
Does optimal solution use optimal subproblems?
            ↓ Yes
    → USE DYNAMIC PROGRAMMING
```

### Choosing Your State

> "What information do I need to fully describe where I am in the problem?"

```
1D:      dp[i]         → single index, value, position
2D:      dp[i][j]      → two indices, two strings, row+col
3D:      dp[i][j][k]   → three variables (use sparingly)
Bitmask: dp[mask]      → subset of chosen items
```

---

## 4. Pattern 01 — 1D Linear DP

### Concept

Process array left to right; each state depends on prior states.

```
dp[i] = f(dp[i-1], dp[i-2], ..., dp[0])
```

---

### 🔗 LC 70 — Climbing Stairs

**Problem**: Count ways to reach step n using 1 or 2 steps.

**State**: `dp[i]` = number of distinct ways to reach step i  
**Recurrence**: `dp[i] = dp[i-1] + dp[i-2]`

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> dp(n + 1);
        dp[1] = 1; dp[2] = 2;
        for (int i = 3; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};
// Time: O(n)   Space: O(n) → O(1) possible
```

---

### 🔗 LC 198 — House Robber

**Problem**: Rob houses, cannot rob two adjacent. Maximize amount.

**State**: `dp[i]` = max money from houses 0..i  
**Recurrence**: `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`

```cpp
/*
 * Problem: 198. House Robber
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * You are given an integer array nums where:
 *   nums[i] represents the amount of money in house i.
 *
 * You cannot rob two adjacent houses.
 *
 * Return the maximum amount of money you can rob.
 *
 * ------------------------------------------------------------
 * APPROACH: Dynamic Programming (Space Optimized)
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ At each house i, we have two choices:
 *
 *    - Do NOT rob current house:
 *        profit = prev1
 *
 *    - Rob current house:
 *        profit = prev2 + nums[i]
 *
 * 2️⃣ So recurrence becomes:
 *
 *    dp[i] = max(dp[i-1], dp[i-2] + nums[i])
 *
 * 3️⃣ Instead of full dp array,
 *    we only need last two values.
 *
 * ------------------------------------------------------------
 * VARIABLES:
 *
 * prev1 → dp[i-1]
 * prev2 → dp[i-2]
 *
 * ------------------------------------------------------------
 * STRATEGY:
 *
 * Initialize:
 *   prev1 = 0
 *   prev2 = 0
 *
 * For each house:
 *
 *   temp = max(prev1, prev2 + nums[i])
 *   prev2 = prev1
 *   prev1 = temp
 *
 * Final answer = prev1
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [2,7,9,3,1]
 *
 * Step-by-step:
 *
 * i=0 → 2
 * i=1 → max(2,7)=7
 * i=2 → max(7,2+9=11)=11
 * i=3 → max(11,7+3=10)=11
 * i=4 → max(11,11+1=12)=12
 *
 * Answer = 12
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 * - O(n)
 *
 * Space Complexity:
 * - O(1)
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Classic 1D DP problem.
 * - Key idea: choose or skip.
 * - Extension: House Robber II (circular houses).
 */

class Solution {
public:
    int rob(vector<int>& nums) {

        int n = nums.size();

        int prev1 = 0;  // dp[i-1]
        int prev2 = 0;  // dp[i-2]

        for (int i = 0; i < n; i++) {

            int temp = max(prev1,
                           prev2 + nums[i]);

            prev2 = prev1;
            prev1 = temp;
        }

        return prev1;
    }
};
```

---

### 🔗 LC 213 — House Robber II (Circular)

**Problem**: Houses in a circle — first and last are adjacent.

```cpp
/*
 * Problem: 213. House Robber II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * You are given an integer array nums where:
 *      nums[i] = amount of money in house i.
 *
 * Houses are arranged in a CIRCLE.
 *
 * You cannot rob two adjacent houses.
 *
 * Return the maximum amount of money you can rob.
 *
 * ------------------------------------------------------------
 * KEY DIFFERENCE FROM HOUSE ROBBER I:
 *
 * In House Robber I, houses are in a straight line.
 *
 * Here houses form a circle, meaning:
 *
 *      house 0 and house n-1 are adjacent.
 *
 * So you cannot rob both of them together.
 *
 * ------------------------------------------------------------
 * CORE IDEA:
 *
 * Break the circular problem into two linear problems.
 *
 * Case 1:
 *      Rob houses from index 0 → n-2
 *      (exclude last house)
 *
 * Case 2:
 *      Rob houses from index 1 → n-1
 *      (exclude first house)
 *
 * Take the maximum of the two results.
 *
 * ------------------------------------------------------------
 * WHY THIS WORKS:
 *
 * Since house 0 and house n-1 cannot both be robbed,
 * every valid solution must fall into one of these cases:
 *
 *      • first house included → last excluded
 *      • last house included → first excluded
 *
 * ------------------------------------------------------------
 * SUBPROBLEM:
 *
 * Each case becomes the classic
 * "House Robber I" dynamic programming problem.
 *
 * Recurrence:
 *
 *      dp[i] = max(
 *                  dp[i-1],             // skip house
 *                  nums[i] + dp[i-2]    // rob house
 *                 )
 *
 * ------------------------------------------------------------
 * ALGORITHM STEPS:
 *
 * 1️⃣ Handle edge case:
 *      If only one house → return nums[0].
 *
 * 2️⃣ Solve two linear rob problems:
 *
 *      rob(0 → n-2)
 *      rob(1 → n-1)
 *
 * 3️⃣ Return the maximum.
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [2,3,2]
 *
 * Case 1:
 *      [2,3] → rob = 3
 *
 * Case 2:
 *      [3,2] → rob = 3
 *
 * Answer = 3
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time Complexity:
 *      O(n)
 *
 * Space Complexity:
 *      O(n)
 *
 * (can be optimized to O(1) space)
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * Very common follow-up to House Robber I.
 *
 * Key trick:
 *      Convert circular constraint
 *      into two linear DP problems.
 */

class Solution {
private:

    int houseRob(vector<int> &nums, int l, int r){

        if(l == r)
            return nums[l];

        vector<int> dp(r - l + 1);

        dp[0] = nums[l];
        dp[1] = max(nums[l + 1], nums[l]);

        for(int i = 2; i <= r - l; i++){

            dp[i] = max(
                        dp[i - 1],
                        nums[l + i] + dp[i - 2]
                      );
        }

        return dp[r - l];
    }

public:

    int rob(vector<int>& nums) {

        int n = nums.size();

        if(n == 1)
            return nums[0];

        return max(
                    houseRob(nums, 0, n - 2),
                    houseRob(nums, 1, n - 1)
                  );
    }
};
```

---

### 🔗 LC 53 — Maximum Subarray (Kadane's Algorithm)

**Problem**: Find contiguous subarray with maximum sum.

**State**: `dp[i]` = max subarray sum ending at index i  
**Recurrence**: `dp[i] = max(nums[i], dp[i-1] + nums[i])`

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = nums[0], best = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cur  = max(nums[i], cur + nums[i]);
            best = max(best, cur);
        }
        return best;
    }
};
// Time: O(n)   Space: O(1)
```

---

### 🔗 LC 746 — Min Cost Climbing Stairs

**Problem**: Pay cost[i] to step from i. Reach beyond last step with min cost.

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; i++)
            dp[i] = min(dp[i-1] + cost[i-1],
                        dp[i-2] + cost[i-2]);
        return dp[n];
    }
};
// Time: O(n)   Space: O(n)
```

---

### 🔗 LC 45 — Jump Game II

**Problem**: Minimum jumps to reach last index.

```cpp
/*
 * Problem: 45. Jump Game II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * You are given an integer array nums where:
 *
 *      nums[i] = maximum jump length from index i
 *
 * Starting from index 0,
 * return the minimum number of jumps needed
 * to reach the last index.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Dynamic Programming (Tabulation)
 *
 * ------------------------------------------------------------
 * CORE IDEA:
 *
 * dp[i] → minimum jumps required to reach index i.
 *
 * Initialize:
 *
 *      dp[0] = 0
 *
 * For each index i,
 * update all reachable positions from i.
 *
 * If we can jump from i to j:
 *
 *      dp[j] = min(dp[j], dp[i] + 1)
 *
 * ------------------------------------------------------------
 * TRANSITION:
 *
 * For index i:
 *
 *      reachable indices =
 *          i+1 → min(n-1, i + nums[i])
 *
 * Update dp values accordingly.
 *
 * ------------------------------------------------------------
 * DRY RUN EXAMPLE:
 *
 * nums = [2,3,1,1,4]
 *
 * Start:
 *
 * dp = [0,∞,∞,∞,∞]
 *
 * i=0 (jump=2):
 * dp[1] = 1
 * dp[2] = 1
 *
 * i=1 (jump=3):
 * dp[2] = 1
 * dp[3] = 2
 * dp[4] = 2
 *
 * Answer = 2
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY (DP):
 *
 * Time Complexity:
 *      O(n²)
 *
 * Space Complexity:
 *      O(n)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Greedy (Optimal Solution)
 *
 * ------------------------------------------------------------
 * CORE IDEA:
 *
 * Think of the array as BFS levels.
 *
 * Variables:
 *
 *      maxReach → farthest index reachable so far
 *      currEnd  → boundary of current jump
 *      jumps    → number of jumps taken
 *
 * When we reach currEnd,
 * we must make another jump.
 *
 * ------------------------------------------------------------
 * GREEDY ALGORITHM:
 *
 * 1️⃣ Track the farthest reachable index.
 *
 * 2️⃣ When current index reaches currEnd:
 *
 *        jump++
 *        currEnd = maxReach
 *
 * 3️⃣ Continue until the end.
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY (GREEDY):
 *
 * Time Complexity:
 *      O(n)
 *
 * Space Complexity:
 *      O(1)
 *
 * ------------------------------------------------------------
 * INTERVIEW NOTES:
 *
 * - Greedy solution is the optimal one.
 * - DP solution helps understand the transitions.
 */

class Solution {
public:
    int jump(vector<int>& nums) {

        int n = nums.size();

        // DP array
        vector<int> dp(n, INT_MAX);

        dp[0] = 0;

        for(int i = 0; i < n; i++){

            for(int j = i + 1;
                j <= min(n - 1, nums[i] + i);
                j++){

                dp[j] = min(dp[j], dp[i] + 1);
            }
        }

        return dp[n - 1];

        /*
        ----------- GREEDY SOLUTION (OPTIMAL) -----------

        int jumps = 0;
        int currEnd = 0;
        int maxReach = 0;

        for(int i = 0; i < nums.size() - 1; i++){

            maxReach = max(maxReach, i + nums[i]);

            if(i == currEnd){

                jumps++;
                currEnd = maxReach;
            }
        }

        return jumps;
        */
    }
};
```

---

### 🔗 LC 300 — Longest Increasing Subsequence

**State**: `dp[i]` = length of LIS ending at index i

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int ans = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
// Time: O(n²)   Space: O(n)
```

#### O(n log n) with Binary Search (Patience Sorting)

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) tails.push_back(x);
            else *it = x;
        }
        return tails.size();
    }
};
// Time: O(n log n)   Space: O(n)
```

---

## 5. Pattern 02 — 2D Grid DP

### Concept

Navigate a 2D grid; each cell depends on adjacent cells (usually top/left).

```
dp[i][j] = f(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
```

---

### 🔗 LC 62 — Unique Paths

**Problem**: Count paths from top-left to bottom-right (right/down only).

**State**: `dp[i][j]` = number of paths to reach (i, j)  
**Recurrence**: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        return dp[m-1][n-1];
    }
};
// Time: O(m*n)   Space: O(m*n) → O(n) with 1D array
```

---

### 🔗 LC 63 — Unique Paths II (With Obstacles)

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        for (int i = 0; i < m && grid[i][0] == 0; i++) dp[i][0] = 1;
        for (int j = 0; j < n && grid[0][j] == 0; j++) dp[0][j] = 1;
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (grid[i][j] == 0)
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
        return dp[m-1][n-1];
    }
};
```

---

### 🔗 LC 64 — Minimum Path Sum

**Problem**: Find path from top-left to bottom-right minimizing sum.

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m) dp[i][0] = dp[i-1][0] + grid[i][0];
        for (int j = 1; j < n) dp[0][j] = dp[0][j-1] + grid[0][j];
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        return dp[m-1][n-1];
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 221 — Maximal Square

**Problem**: Largest square of all 1s in binary matrix.

**State**: `dp[i][j]` = side length of largest square with (i,j) as bottom-right corner  
**Recurrence**: `dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1`  (if matrix[i][j]=='1')

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), best = 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = (i == 0 || j == 0) ? 1 :
                        min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    best = max(best, dp[i][j]);
                }
            }
        }
        return best * best;
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 120 — Triangle

**Problem**: Minimum path sum from top to bottom of triangle.

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp = triangle[n-1];    // start from bottom row
        for (int i = n-2; i >= 0; i--)
            for (int j = 0; j <= i; j++)
                dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];
        return dp[0];
    }
};
// Time: O(n²)   Space: O(n)
```

---

## 6. Pattern 03 — Knapsack Variants

### The Classic 0/1 Knapsack

n items with weights/values, capacity W, each item used **at most once**. Maximize value.

**State**: `dp[w]` = max value achievable with capacity w  
**Key**: Iterate capacity in **reverse** to prevent item reuse.

```cpp
int knapsack01(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int w = W; w >= wt[i]; w--)        // REVERSE
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}
// Time: O(n*W)   Space: O(W)
```

---

### 🔗 LC 416 — Partition Equal Subset Sum

**Problem**: Split array into two equal-sum subsets?

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0) return false;
        int target = total / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums)
            for (int j = target; j >= num; j--)   // REVERSE (0/1)
                dp[j] = dp[j] || dp[j - num];
        return dp[target];
    }
};
// Time: O(n * target)   Space: O(target)
```

---

### 🔗 LC 322 — Coin Change (Minimum Coins)

**Problem**: Min coins to make amount. Coins reusable (unbounded).

**State**: `dp[i]` = min coins to make amount i  
**Recurrence**: `dp[i] = min(dp[i - coin] + 1)` for each coin ≤ i

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);    // sentinel > any valid answer
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
            for (int coin : coins)
                if (coin <= i)
                    dp[i] = min(dp[i], dp[i - coin] + 1);
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
// Time: O(amount * coins)   Space: O(amount)
```

---

### 🔗 LC 518 — Coin Change II (Number of Combinations)

**Problem**: Count distinct combinations to make amount.

```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<long long> dp(amount + 1, 0);
        dp[0] = 1;                                 // one way to make 0
        for (int coin : coins)                     // coin OUTER → combinations
            for (int i = coin; i <= amount; i++)   // FORWARD → reuse allowed
                dp[i] += dp[i - coin];
        return dp[amount];
    }
};
// Time: O(amount * coins)   Space: O(amount)
// NOTE: Swap loop order for permutations (count ordered ways)
```

---

### 🔗 LC 494 — Target Sum

**Problem**: Assign + or − to each number to reach target. Count ways.

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        // Math reduction: sum(+) - sum(-) = target
        // sum(+) = (target + total) / 2 = S
        int total = accumulate(nums.begin(), nums.end(), 0);
        if ((total + target) % 2 != 0 || abs(target) > total) return 0;
        int S = (total + target) / 2;
        vector<int> dp(S + 1, 0);
        dp[0] = 1;
        for (int num : nums)
            for (int j = S; j >= num; j--)         // REVERSE (0/1)
                dp[j] += dp[j - num];
        return dp[S];
    }
};
// Time: O(n * S)   Space: O(S)
```

---

### 🔗 LC 474 — Ones and Zeroes (2D Knapsack)

**Problem**: Max strings from strs using at most m 0s and n 1s.

```cpp
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (auto& s : strs) {
            int zeros = count(s.begin(), s.end(), '0');
            int ones  = s.size() - zeros;
            for (int i = m; i >= zeros; i--)       // REVERSE both dims
                for (int j = n; j >= ones; j--)
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
        }
        return dp[m][n];
    }
};
// Time: O(len * m * n)   Space: O(m * n)
```

---

### Knapsack Variants Summary

| Problem | LC | Item Reuse | Capacity Loop | Goal |
|---------|----|------------|---------------|------|
| 0/1 Knapsack | — | Once | Reverse | Max value |
| Partition Equal Subset | 416 | Once | Reverse | Boolean |
| Target Sum | 494 | Once | Reverse | Count ways |
| Coin Change (min) | 322 | Unlimited | Forward | Min count |
| Coin Change II | 518 | Unlimited | Forward | Count combos |
| Ones and Zeroes | 474 | Once | Reverse (2D) | Max items |

---

## 7. Pattern 04 — Subsequence DP

### 🔗 LC 1143 — Longest Common Subsequence (LCS)

**State**: `dp[i][j]` = LCS length of s1[0..i-1] and s2[0..j-1]

```
if s1[i-1] == s2[j-1]:   dp[i][j] = dp[i-1][j-1] + 1
else:                     dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (text1[i-1] == text2[j-1])
                          ? dp[i-1][j-1] + 1
                          : max(dp[i-1][j], dp[i][j-1]);
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n) → O(min(m,n)) possible
```

---

### 🔗 LC 72 — Edit Distance (Levenshtein)

**Problem**: Min operations (insert, delete, replace) to convert word1 to word2.

```
if word1[i-1] == word2[j-1]:   dp[i][j] = dp[i-1][j-1]
else:                           dp[i][j] = 1 + min(dp[i-1][j],    // delete
                                                    dp[i][j-1],    // insert
                                                    dp[i-1][j-1])  // replace
```

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (word1[i-1] == word2[j-1])
                          ? dp[i-1][j-1]
                          : 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 516 — Longest Palindromic Subsequence

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        // LPS(s) = LCS(s, reverse(s))
        string t = string(s.rbegin(), s.rend());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (s[i-1] == t[j-1])
                          ? dp[i-1][j-1] + 1
                          : max(dp[i-1][j], dp[i][j-1]);
        return dp[n][n];
    }
};
// Time: O(n²)   Space: O(n²)
```

---

### 🔗 LC 115 — Distinct Subsequences

**Problem**: Count distinct ways s is a subsequence of t.

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= m; i++) dp[i][0] = 1;  // empty t always matched
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i-1][j];               // skip s[i-1]
                if (s[i-1] == t[j-1])
                    dp[i][j] += dp[i-1][j-1];        // use s[i-1]
            }
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 1092 — Shortest Common Supersequence

**Problem**: Shortest string containing both s1 and s2 as subsequences.

```
Length = len(s1) + len(s2) - LCS(s1, s2)
```

```cpp
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (s1[i-1] == s2[j-1])
                          ? dp[i-1][j-1] + 1
                          : max(dp[i-1][j], dp[i][j-1]);
        // Reconstruct
        string result;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (s1[i-1] == s2[j-1]) { result += s1[i-1]; i--; j--; }
            else if (dp[i-1][j] > dp[i][j-1]) result += s1[--i];
            else result += s2[--j];
        }
        while (i > 0) result += s1[--i];
        while (j > 0) result += s2[--j];
        reverse(result.begin(), result.end());
        return result;
    }
};
```

---

## 8. Pattern 05 — Interval DP

### Concept

Solve problems on subarrays/substrings by iterating over interval lengths.

```cpp
// Template
for (int len = 2; len <= n; len++) {         // length of interval
    for (int i = 0; i <= n - len; i++) {     // start index
        int j = i + len - 1;                 // end index
        for (int k = i; k < j; k++) {        // split point
            dp[i][j] = min/max(...);
        }
    }
}
```

---

### 🔗 LC 312 — Burst Balloons

**Problem**: Burst all balloons, earn `nums[left]*nums[i]*nums[right]` each burst. Maximize coins.

**Key insight**: Think of k as the **last** balloon burst in range (left, right).

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);                    // sentinel boundaries
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 2; len < n; len++) {
            for (int left = 0; left < n - len; left++) {
                int right = left + len;
                for (int k = left + 1; k < right; k++) {
                    int coins = nums[left] * nums[k] * nums[right];
                    dp[left][right] = max(dp[left][right],
                                         dp[left][k] + coins + dp[k][right]);
                }
            }
        }
        return dp[0][n-1];
    }
};
// Time: O(n³)   Space: O(n²)
```

---

### 🔗 LC 1039 — Minimum Score Triangulation of Polygon

**Problem**: Triangulate polygon to minimize sum of triangle weights.

```cpp
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 2; len < n; len++) {
            for (int i = 0; i < n - len; i++) {
                int j = i + len;
                dp[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++)
                    dp[i][j] = min(dp[i][j],
                                   dp[i][k] + dp[k][j] + values[i]*values[k]*values[j]);
            }
        }
        return dp[0][n-1];
    }
};
// Time: O(n³)   Space: O(n²)
```

---

### 🔗 LC 647 — Palindromic Substrings (Count All)

```cpp
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), count = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) dp[i][i] = true, count++;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = (len == 2) ? true : dp[i+1][j-1];
                    if (dp[i][j]) count++;
                }
            }
        }
        return count;
    }
};
// Time: O(n²)   Space: O(n²)
// Expand-around-center approach also O(n²) time, O(1) space
```

---

### 🔗 LC 5 — Longest Palindromic Substring

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), start = 0, maxLen = 1;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) dp[i][i] = true;
        for (int i = 0; i < n - 1; i++)
            if (s[i] == s[i+1]) { dp[i][i+1] = true; start = i; maxLen = 2; }
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && dp[i+1][j-1]) {
                    dp[i][j] = true;
                    if (len > maxLen) { start = i; maxLen = len; }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};
// Time: O(n²)   Space: O(n²)
```

---

### 🔗 LC 132 — Palindrome Partitioning II (Min Cuts)

```cpp
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) pal[i][i] = true;
        for (int len = 2; len <= n; len++)
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                pal[i][j] = (s[i] == s[j]) && (len == 2 || pal[i+1][j-1]);
            }
        vector<int> dp(n);
        iota(dp.begin(), dp.end(), 0);     // dp[i] = i (max cuts)
        for (int i = 1; i < n; i++) {
            if (pal[0][i]) { dp[i] = 0; continue; }
            for (int j = 1; j <= i; j++)
                if (pal[j][i])
                    dp[i] = min(dp[i], dp[j-1] + 1);
        }
        return dp[n-1];
    }
};
// Time: O(n²)   Space: O(n²)
```

---

## 9. Pattern 06 — Tree DP

### Concept

Post-order DFS: compute answers for subtrees, combine at each node.

```cpp
// Template
pair<int,int> dfs(TreeNode* node) {
    if (!node) return {base, base};
    auto [lVal1, lVal2] = dfs(node->left);
    auto [rVal1, rVal2] = dfs(node->right);
    int take = node->val + lVal2 + rVal2;
    int skip = max(lVal1, lVal2) + max(rVal1, rVal2);
    return {take, skip};
}
```

---

### 🔗 LC 543 — Diameter of Binary Tree

```cpp
class Solution {
    int best = 0;
    int depth(TreeNode* node) {
        if (!node) return 0;
        int l = depth(node->left), r = depth(node->right);
        best = max(best, l + r);          // path through this node
        return max(l, r) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return best;
    }
};
// Time: O(n)   Space: O(h)
```

---

### 🔗 LC 124 — Binary Tree Maximum Path Sum

```cpp
class Solution {
    int best = INT_MIN;
    int gain(TreeNode* node) {
        if (!node) return 0;
        int l = max(gain(node->left),  0);   // discard negative paths
        int r = max(gain(node->right), 0);
        best = max(best, l + r + node->val); // path through this node
        return max(l, r) + node->val;        // best single branch
    }
public:
    int maxPathSum(TreeNode* root) {
        gain(root);
        return best;
    }
};
// Time: O(n)   Space: O(h)
```

---

### 🔗 LC 337 — House Robber III (Tree)

**Problem**: Can't rob a node and its parent. Maximize sum.

```cpp
class Solution {
    // Returns {rob_this_node, skip_this_node}
    pair<int,int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        auto [lRob, lSkip] = dfs(node->left);
        auto [rRob, rSkip] = dfs(node->right);
        int rob  = node->val + lSkip + rSkip;
        int skip = max(lRob, lSkip) + max(rRob, rSkip);
        return {rob, skip};
    }
public:
    int rob(TreeNode* root) {
        auto [r, s] = dfs(root);
        return max(r, s);
    }
};
// Time: O(n)   Space: O(h)
```

---

### 🔗 LC 1245 — Tree Diameter (General Tree)

```cpp
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n);
        for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
        int best = 0;
        function<int(int, int)> dfs = [&](int u, int par) -> int {
            int top1 = 0, top2 = 0;
            for (int v : adj[u]) {
                if (v == par) continue;
                int d = dfs(v, u) + 1;
                if (d > top1) { top2 = top1; top1 = d; }
                else if (d > top2) top2 = d;
            }
            best = max(best, top1 + top2);
            return top1;
        };
        dfs(0, -1);
        return best;
    }
};
```

---

## 10. Pattern 07 — Digit DP

### Concept

Count numbers in [0, N] satisfying digit-based constraints. Process digit by digit with a `tight` flag.

### C++ Template with Memoization

```cpp
string num;
int dp[20][2][2];   // [pos][tight][started]  — adjust dims per problem

int solve(int pos, bool tight, bool started) {
    if (pos == num.size()) return started ? 1 : 0;
    if (dp[pos][tight][started] != -1) return dp[pos][tight][started];
    
    int limit = tight ? (num[pos] - '0') : 9;
    int result = 0;
    for (int d = 0; d <= limit; d++) {
        bool newTight   = tight && (d == limit);
        bool newStarted = started || (d > 0);
        result += solve(pos + 1, newTight, newStarted);
    }
    return dp[pos][tight][started] = result;
}
```

---

### 🔗 LC 233 — Number of Digit One

**Problem**: Count total occurrences of digit 1 in all numbers from 1 to n.

```cpp
class Solution {
    string s;
    int memo[11][2];
    int dfs(int pos, bool tight, int count) {
        if (pos == s.size()) return count;
        if (memo[pos][tight] != -1) return memo[pos][tight];
        int limit = tight ? (s[pos] - '0') : 9, res = 0;
        for (int d = 0; d <= limit; d++)
            res += dfs(pos + 1, tight && d == limit, count + (d == 1));
        return memo[pos][tight] = res;
    }
public:
    int countDigitOne(int n) {
        s = to_string(n);
        memset(memo, -1, sizeof(memo));
        return dfs(0, true, 0);
    }
};
```

---

### 🔗 LC 357 — Count Numbers with Unique Digits

```cpp
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        // dp[i] = count of i-digit numbers with all unique digits
        vector<int> dp(n + 1);
        dp[0] = 1; dp[1] = 10;
        int available = 9;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + (dp[i-1] - dp[i-2]) * available;
            available--;
        }
        return dp[n];
    }
};
```

---

### 🔗 LC 1012 — Numbers With Repeated Digits

```cpp
class Solution {
    string s;
    // dp[pos][mask][tight][started]
    int dp[11][1024][2][2];
    int dfs(int pos, int mask, bool tight, bool started) {
        if (pos == s.size()) return started ? 1 : 0;
        int& ret = dp[pos][mask][tight][started];
        if (ret != -1) return ret;
        int limit = tight ? s[pos]-'0' : 9, res = 0;
        for (int d = 0; d <= limit; d++) {
            if (started && (mask >> d & 1)) continue;   // repeated digit
            res += dfs(pos+1, started||d ? mask|(1<<d) : 0,
                       tight&&d==limit, started||d);
        }
        return ret = res;
    }
public:
    int numDupDigitsAtMostN(int n) {
        s = to_string(n);
        memset(dp, -1, sizeof(dp));
        return n - dfs(0, 0, true, false);  // total - no-repeat count
    }
};
```

---

## 11. Pattern 08 — Bitmask DP

### Concept

Use an integer bitmask to represent a subset of n items. Iterate all 2^n subsets.

```cpp
// Bit operations
(mask >> i) & 1      // is item i in mask?
mask | (1 << i)      // add item i to mask
mask ^ (1 << i)      // remove item i from mask
__builtin_popcount(mask)   // count set bits
```

---

### 🔗 LC 847 — Shortest Path Visiting All Nodes

**State**: `dp[mask][node]` = min steps to visit nodes in mask, ending at node

```cpp
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size(), full = (1 << n) - 1;
        vector<vector<int>> dist(1<<n, vector<int>(n, INT_MAX));
        queue<pair<int,int>> q;
        for (int i = 0; i < n; i++) {
            dist[1<<i][i] = 0;
            q.push({1<<i, i});
        }
        while (!q.empty()) {
            auto [mask, u] = q.front(); q.pop();
            if (mask == full) return dist[mask][u];
            for (int v : graph[u]) {
                int nm = mask | (1 << v);
                if (dist[nm][v] > dist[mask][u] + 1) {
                    dist[nm][v] = dist[mask][u] + 1;
                    q.push({nm, v});
                }
            }
        }
        return -1;
    }
};
// Time: O(2^n * n)   Space: O(2^n * n)
```

---

### 🔗 LC 1986 — Minimum Number of Work Sessions

```cpp
class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size(), full = (1 << n) - 1;
        vector<int> dp(full + 1, INT_MAX);
        vector<int> rem(full + 1, 0);   // remaining time in current session
        dp[0] = 1; rem[0] = sessionTime;
        for (int mask = 1; mask <= full; mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask >> i & 1)) continue;
                int prev = mask ^ (1 << i);
                if (dp[prev] == INT_MAX) continue;
                if (rem[prev] >= tasks[i]) {
                    if (dp[mask] > dp[prev] ||
                       (dp[mask] == dp[prev] && rem[mask] < rem[prev] - tasks[i])) {
                        dp[mask] = dp[prev];
                        rem[mask] = rem[prev] - tasks[i];
                    }
                } else {
                    if (dp[mask] > dp[prev] + 1) {
                        dp[mask] = dp[prev] + 1;
                        rem[mask] = sessionTime - tasks[i];
                    }
                }
            }
        }
        return dp[full];
    }
};
```

---

### 🔗 LC 691 — Stickers to Spell Word

```cpp
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size(), full = (1 << n) - 1;
        vector<int> dp(full + 1, -1);
        dp[0] = 0;
        for (int mask = 0; mask <= full; mask++) {
            if (dp[mask] == -1) continue;
            for (auto& s : stickers) {
                int cur = mask;
                for (char c : s)
                    for (int i = 0; i < n; i++)
                        if (!(cur >> i & 1) && target[i] == c) { cur |= 1<<i; break; }
                if (dp[cur] == -1 || dp[cur] > dp[mask] + 1)
                    dp[cur] = dp[mask] + 1;
            }
        }
        return dp[full];
    }
};
// Time: O(2^n * |stickers| * |s|)
```

---

## 12. Pattern 09 — DP on Strings

### 🔗 LC 44 — Wildcard Matching

**Pattern**: `?` matches any single char, `*` matches any sequence.

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int j = 1; j <= n; j++)
            if (p[j-1] == '*') dp[0][j] = dp[0][j-1];
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*')
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                else if (p[j-1] == '?' || p[j-1] == s[i-1])
                    dp[i][j] = dp[i-1][j-1];
            }
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 10 — Regular Expression Matching

**Pattern**: `.` matches any single char, `*` matches zero or more of previous element.

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int j = 2; j <= n; j++)
            if (p[j-1] == '*') dp[0][j] = dp[0][j-2];  // x* = empty
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*') {
                    dp[i][j] = dp[i][j-2];              // zero occurrences
                    if (p[j-2] == '.' || p[j-2] == s[i-1])
                        dp[i][j] = dp[i][j] || dp[i-1][j]; // one+ occurrences
                } else if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n)
```

---

### 🔗 LC 97 — Interleaving String

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size()) return false;
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int i = 1; i <= m; i++) dp[i][0] = dp[i-1][0] && s1[i-1]==s3[i-1];
        for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] && s2[j-1]==s3[j-1];
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = (dp[i-1][j] && s1[i-1]==s3[i+j-1]) ||
                            (dp[i][j-1] && s2[j-1]==s3[i+j-1]);
        return dp[m][n];
    }
};
// Time: O(m*n)   Space: O(m*n) → O(n) with rolling row
```

---

## 13. Pattern 10 — Partition DP

### 🔗 LC 139 — Word Break

**Problem**: Can s be segmented using words from dictionary?

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> ws(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if (dp[j] && ws.count(s.substr(j, i - j))) {
                    dp[i] = true; break;
                }
        return dp[n];
    }
};
// Time: O(n² * L)   Space: O(n)
```

---

### 🔗 LC 140 — Word Break II (All Sentences)

```cpp
class Solution {
    unordered_set<string> ws;
    unordered_map<int, vector<string>> memo;
    vector<string> dfs(const string& s, int start) {
        if (memo.count(start)) return memo[start];
        if (start == s.size()) return {""};
        vector<string> res;
        for (int end = start + 1; end <= s.size(); end++) {
            string word = s.substr(start, end - start);
            if (ws.count(word))
                for (auto& rest : dfs(s, end))
                    res.push_back(word + (rest.empty() ? "" : " ") + rest);
        }
        return memo[start] = res;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        ws = {wordDict.begin(), wordDict.end()};
        return dfs(s, 0);
    }
};
```

---

### 🔗 LC 91 — Decode Ways

**Problem**: Count ways to decode digit string (1=A, ..., 26=Z).

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = (s[0] != '0') ? 1 : 0;
        for (int i = 2; i <= n; i++) {
            int one = s[i-1] - '0';
            int two = stoi(s.substr(i-2, 2));
            if (one >= 1)          dp[i] += dp[i-1];  // single digit decode
            if (two >= 10 && two <= 26) dp[i] += dp[i-2];  // double digit decode
        }
        return dp[n];
    }
};
// Time: O(n)   Space: O(n) → O(1) with 3 vars
```

---

### 🔗 LC 343 — Integer Break

**Problem**: Break n into ≥2 positive integers maximizing their product.

```cpp
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++)
                dp[i] = max({dp[i], j*(i-j), j*dp[i-j]});
        return dp[n];
    }
};
// Time: O(n²)   Space: O(n)
// Math insight: only need to break into 3s and 2s → O(1) possible
```

---

### 🔗 LC 1547 — Minimum Cost to Cut a Stick

```cpp
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0); cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));
        for (int len = 2; len < m; len++)
            for (int i = 0; i < m - len; i++) {
                int j = i + len;
                dp[i][j] = INT_MAX;
                for (int k = i+1; k < j; k++)
                    dp[i][j] = min(dp[i][j],
                                   dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
            }
        return dp[0][m-1];
    }
};
// Time: O(m³)   Space: O(m²)
```

---

## 14. Space Optimization Techniques

### Technique 1: Two Variables Instead of Array

When `dp[i]` depends only on `dp[i-1]` and `dp[i-2]`:

```cpp
// Before: O(n) space
vector<int> dp(n + 1);

// After: O(1) space
int prev2 = 0, prev1 = 1;
for (int i = 2; i <= n; i++) {
    int cur = prev1 + prev2;
    prev2 = prev1;
    prev1 = cur;
}
// Applies to: LC 70, 198, 509, 746
```

---

### Technique 2: Rolling Row for 2D DP

When `dp[i][j]` depends only on row `i-1`:

```cpp
// Before: O(m*n) space
vector<vector<int>> dp(m, vector<int>(n));

// After: O(n) space  
vector<int> prev(n, 0), curr(n, 0);
for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
        curr[j] = compute(prev, curr, i, j);
    swap(prev, curr);
}
// Applies to: LC 62, 64, 1143
```

---

### Technique 3: 1D Knapsack (Reverse for 0/1)

```cpp
// 2D Knapsack → 1D
// Key: reverse capacity loop for 0/1 (prevents reuse)
vector<int> dp(W + 1, 0);
for (int i = 0; i < n; i++)
    for (int w = W; w >= weight[i]; w--)    // REVERSE
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);

// Forward for unbounded (allows reuse)
for (int coin : coins)
    for (int i = coin; i <= amount; i++)    // FORWARD
        dp[i] = min(dp[i], dp[i - coin] + 1);
```

---

### Technique 4: Space-Optimized LCS

```cpp
// O(min(m,n)) instead of O(m*n)
int lcs(string& s1, string& s2) {
    if (s1.size() < s2.size()) swap(s1, s2);
    int m = s1.size(), n = s2.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++)
            curr[j] = (s1[i-1] == s2[j-1])
                    ? prev[j-1] + 1
                    : max(prev[j], curr[j-1]);
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }
    return prev[n];
}
```

---

## 15. Advanced Techniques

### Technique 1: DP + Binary Search (LIS O(n log n))

```cpp
// LC 300 — O(n log n) with patience sorting
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// LC 354 — Russian Doll Envelopes (2D LIS)
int maxEnvelopes(vector<vector<int>>& e) {
    sort(e.begin(), e.end(), [](auto& a, auto& b){
        return a[0] != b[0] ? a[0] < b[0] : b[1] < a[1]; // desc height for same width
    });
    vector<int> tails;
    for (auto& env : e) {
        int h = env[1];
        auto it = lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) tails.push_back(h);
        else *it = h;
    }
    return tails.size();
}
```

---

### Technique 2: Matrix Exponentiation (O(k³ log n))

For linear recurrences. Compute Fibonacci in O(log n):

```cpp
typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix matpow(Matrix M, long long p) {
    int n = M.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1;  // identity
    while (p) {
        if (p & 1) result = multiply(result, M);
        M = multiply(M, M);
        p >>= 1;
    }
    return result;
}

// fib(n) using matrix exponentiation
long long fib(long long n) {
    if (n <= 1) return n;
    Matrix M = {{1, 1}, {1, 0}};
    return matpow(M, n)[0][1];
}
// Time: O(k³ log n) where k = matrix size (2 for Fibonacci)
```

---

### Technique 3: Divide & Conquer DP Optimization

Reduces O(n³) to O(n² log n) when the optimal split point is **monotone**: `opt[i] ≤ opt[i+1]`.

```cpp
// dp[i] = min cost to assign first i items to groups
// dp_new[i] = min over j in [opt_lo..opt_hi] of dp[j] + cost(j+1, i)

vector<int> dp_prev, dp_curr;

void solve(int lo, int hi, int opt_lo, int opt_hi) {
    if (lo > hi) return;
    int mid = (lo + hi) / 2;
    int best_opt = opt_lo;
    dp_curr[mid] = INT_MAX;
    for (int m = opt_lo; m <= min(opt_hi, mid); m++) {
        long long val = (long long)dp_prev[m] + cost(m + 1, mid);
        if (val < dp_curr[mid]) { dp_curr[mid] = val; best_opt = m; }
    }
    solve(lo, mid - 1, opt_lo,    best_opt);
    solve(mid + 1, hi, best_opt,  opt_hi);
}
// Applies to: LC 1246, Knuth's optimization
```

---

### Technique 4: Sum over Subsets (SOS DP)

Compute `f[mask] = sum of g[submask]` for all submasks in O(n · 2^n).

```cpp
// g[mask] is given; compute f[mask] = sum over all submasks
vector<int> sos_dp(vector<int>& g, int n) {
    vector<int> f = g;
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask >> i & 1)
                f[mask] += f[mask ^ (1 << i)];
    return f;
}
// Time: O(n * 2^n)  vs brute-force O(3^n)
// Applies to: LC 1986, competitive AND/OR subset problems
```

---

### Technique 5: Convex Hull Trick (CHT)

For DPs of the form `dp[i] = min over j<i of (dp[j] + b[j]*a[i] + c[i])` — treat as lines, query minimum with a convex hull.

```cpp
struct Line {
    long long m, b;
    long long eval(long long x) { return m * x + b; }
};

struct CHT {
    deque<Line> hull;
    bool bad(Line l1, Line l2, Line l3) {
        return (__int128)(l3.b-l1.b)*(l1.m-l2.m) <= (__int128)(l2.b-l1.b)*(l1.m-l3.m);
    }
    void add(Line line) {
        while (hull.size() >= 2 && bad(hull[hull.size()-2], hull[hull.size()-1], line))
            hull.pop_back();
        hull.push_back(line);
    }
    long long query(long long x) {
        while (hull.size() > 1 && hull[0].eval(x) >= hull[1].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }
};
// Reduces O(n²) DP to O(n) when lines are added in order of slope
// Applies to: LC 1235 (Job Scheduling), competitive geometry DP
```

---

## 16. LeetCode Problem Index

### By Pattern

| Pattern | LC # | Title | Difficulty |
|---------|------|-------|------------|
| 1D Linear | 509 | Fibonacci Number | Easy |
| 1D Linear | 70 | Climbing Stairs | Easy |
| 1D Linear | 746 | Min Cost Climbing Stairs | Easy |
| 1D Linear | 198 | House Robber | Medium |
| 1D Linear | 213 | House Robber II | Medium |
| 1D Linear | 53 | Maximum Subarray | Medium |
| 1D Linear | 45 | Jump Game II | Medium |
| 1D Linear | 300 | Longest Increasing Subsequence | Medium |
| 1D Linear | 354 | Russian Doll Envelopes | Hard |
| 2D Grid | 62 | Unique Paths | Medium |
| 2D Grid | 63 | Unique Paths II | Medium |
| 2D Grid | 64 | Minimum Path Sum | Medium |
| 2D Grid | 221 | Maximal Square | Medium |
| 2D Grid | 120 | Triangle | Medium |
| Knapsack | 416 | Partition Equal Subset Sum | Medium |
| Knapsack | 322 | Coin Change | Medium |
| Knapsack | 518 | Coin Change II | Medium |
| Knapsack | 494 | Target Sum | Medium |
| Knapsack | 474 | Ones and Zeroes | Medium |
| Knapsack | 1049 | Last Stone Weight II | Medium |
| Subsequence | 1143 | Longest Common Subsequence | Medium |
| Subsequence | 72 | Edit Distance | Medium |
| Subsequence | 516 | Longest Palindromic Subsequence | Medium |
| Subsequence | 115 | Distinct Subsequences | Hard |
| Subsequence | 1092 | Shortest Common Supersequence | Hard |
| Interval | 5 | Longest Palindromic Substring | Medium |
| Interval | 647 | Palindromic Substrings | Medium |
| Interval | 132 | Palindrome Partitioning II | Hard |
| Interval | 312 | Burst Balloons | Hard |
| Interval | 1039 | Min Score Triangulation | Medium |
| Tree DP | 543 | Diameter of Binary Tree | Easy |
| Tree DP | 124 | Binary Tree Max Path Sum | Hard |
| Tree DP | 337 | House Robber III | Medium |
| Tree DP | 1245 | Tree Diameter | Medium |
| Digit DP | 233 | Number of Digit One | Hard |
| Digit DP | 357 | Count Numbers Unique Digits | Medium |
| Digit DP | 1012 | Numbers With Repeated Digits | Hard |
| Bitmask | 847 | Shortest Path Visiting All Nodes | Hard |
| Bitmask | 1986 | Min Work Sessions | Medium |
| Bitmask | 691 | Stickers to Spell Word | Hard |
| String DP | 44 | Wildcard Matching | Hard |
| String DP | 10 | Regular Expression Matching | Hard |
| String DP | 97 | Interleaving String | Medium |
| Partition | 139 | Word Break | Medium |
| Partition | 140 | Word Break II | Hard |
| Partition | 91 | Decode Ways | Medium |
| Partition | 343 | Integer Break | Medium |
| Partition | 1547 | Min Cost to Cut a Stick | Hard |

### By Difficulty

#### Easy (Master These First)
| LC # | Title | Key Concept |
|------|-------|-------------|
| 509 | Fibonacci Number | Basic recurrence |
| 70 | Climbing Stairs | 1D DP, Fib variant |
| 746 | Min Cost Climbing Stairs | Base case clarity |
| 543 | Diameter of Binary Tree | Tree DFS return |
| 121 | Best Time to Buy & Sell Stock | Track running min |

#### Medium (Core Patterns)
| LC # | Title | Key Concept |
|------|-------|-------------|
| 198 | House Robber | Skip/take decision |
| 300 | Longest Increasing Subsequence | O(n²) then O(n log n) |
| 1143 | Longest Common Subsequence | 2D DP, match/skip |
| 72 | Edit Distance | 3-way recurrence |
| 322 | Coin Change | Unbounded knapsack |
| 416 | Partition Equal Subset Sum | 0/1 knapsack boolean |
| 62 | Unique Paths | 2D grid, path counting |
| 221 | Maximal Square | 2D DP, elegant recurrence |
| 139 | Word Break | Partition DP |
| 91 | Decode Ways | Careful base cases |
| 494 | Target Sum | Knapsack reduction |
| 518 | Coin Change II | Combo vs permutation loop order |

#### Hard (Advanced)
| LC # | Title | Key Concept |
|------|-------|-------------|
| 312 | Burst Balloons | Interval DP, reverse thinking |
| 132 | Palindrome Partitioning II | Interval + 1D DP |
| 124 | Binary Tree Max Path Sum | Tree DP, ignore negatives |
| 115 | Distinct Subsequences | 2D DP, careful transitions |
| 44 | Wildcard Matching | String DP, `*` handling |
| 10 | Regular Expression Matching | String DP, `x*` handling |
| 354 | Russian Doll Envelopes | 2D LIS with sorting trick |
| 847 | Shortest Path Visiting All Nodes | BFS + Bitmask DP |

---

## 17. Common Mistakes & Debugging

### Mistake 1: Wrong Base Case

```cpp
// WRONG — for counting problems
vector<int> dp(amount + 1, 0);

// RIGHT — 1 way to make 0: use nothing
vector<int> dp(amount + 1, 0);
dp[0] = 1;
```

### Mistake 2: Wrong Loop Direction (Knapsack)

```cpp
// WRONG for 0/1 — forward allows reuse
for (int w = weight; w <= W; w++)      // ← item used multiple times!
    dp[w] = max(dp[w], dp[w-weight] + value);

// CORRECT for 0/1 — reverse prevents reuse
for (int w = W; w >= weight; w--)
    dp[w] = max(dp[w], dp[w-weight] + value);
```

### Mistake 3: Off-By-One on 1-Indexed DP

```cpp
// dp[i] = answer for first i elements, array is 0-indexed
for (int i = 1; i <= n; i++) {
    dp[i] = something_using(arr[i-1]);   // arr[i-1], NOT arr[i]
}
```

### Mistake 4: Wrong Sentinel for Min/Max DP

```cpp
// For minimization — use large value, NOT 0
vector<int> dp(n + 1, INT_MAX);     // correct
vector<int> dp(n + 1, 0);           // wrong! 0 is a valid minimum

// Guard against INT_MAX overflow
if (dp[j] != INT_MAX)
    dp[i] = min(dp[i], dp[j] + cost);
```

### Mistake 5: Forgetting Dimension in 2D DP

```cpp
// State dp[i][j] but forgot what j represents
// ALWAYS write it out:
// dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]
```

### Mistake 6: Coins II — Wrong Loop Order

```cpp
// COMBINATIONS (order doesn't matter) — coin outer:
for (int coin : coins)
    for (int i = coin; i <= amount; i++)
        dp[i] += dp[i - coin];

// PERMUTATIONS (order matters) — amount outer:
for (int i = 1; i <= amount; i++)
    for (int coin : coins)
        if (i >= coin) dp[i] += dp[i - coin];
```

### Debugging Checklist

```
☐ Is dp[i] (or dp[i][j]) definition written out clearly?
☐ Are base cases correct and sufficient?
☐ Does recurrence correctly reference smaller subproblems?
☐ Is loop order correct (dependencies always computed first)?
☐ Is table size correct? (n+1 for 1-indexed DP)
☐ Is initialization correct? (0 vs INT_MAX vs INT_MIN)
☐ Is knapsack loop direction correct? (reverse vs forward)
☐ Is the answer read from the right cell?
☐ Are there potential INT_MAX/INT_MIN overflow issues?
```

---

## 18. Quick Reference

### Recurrence Cheat Sheet

| Problem (LC) | Recurrence |
|--------------|-----------|
| Fibonacci (509) | `dp[i] = dp[i-1] + dp[i-2]` |
| Climbing Stairs (70) | `dp[i] = dp[i-1] + dp[i-2]` |
| House Robber (198) | `dp[i] = max(dp[i-1], dp[i-2]+nums[i])` |
| Max Subarray (53) | `dp[i] = max(nums[i], dp[i-1]+nums[i])` |
| Unique Paths (62) | `dp[i][j] = dp[i-1][j] + dp[i][j-1]` |
| Min Path Sum (64) | `dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]` |
| Maximal Square (221) | `dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1` |
| Knapsack 0/1 | `dp[w] = max(dp[w], dp[w-wt]+val)` (reverse w) |
| Coin Change (322) | `dp[i] = min(dp[i], dp[i-coin]+1)` |
| LCS (1143) | `dp[i][j] = dp[i-1][j-1]+1` or `max(dp[i-1][j], dp[i][j-1])` |
| Edit Distance (72) | `dp[i][j] = dp[i-1][j-1]` or `1+min(3 neighbors)` |
| LIS (300) | `dp[i] = max(dp[j]+1)` for j<i, nums[j]<nums[i] |
| Palindrome Sub (647) | `dp[i][j] = s[i]==s[j] && dp[i+1][j-1]` |
| Burst Balloons (312) | `dp[l][r] = max(dp[l][k]+nums[l]*nums[k]*nums[r]+dp[k][r])` |
| Decode Ways (91) | `dp[i] += dp[i-1]` if valid 1-dig; `+= dp[i-2]` if valid 2-dig |

### Knuth's Optimization Reference

| Optimization | Condition | Complexity Gain |
|--------------|-----------|-----------------|
| 1D space for 2D DP | Only prev row needed | O(m*n) → O(n) space |
| Reverse loop (0/1) | Each item used once | Prevents reuse |
| Binary search (LIS) | Patience sorting | O(n²) → O(n log n) |
| D&C DP | Monotone opt split | O(n³) → O(n² log n) |
| CHT | Linear DP as lines | O(n²) → O(n) |
| Matrix expo | Linear recurrence | O(n) → O(k³ log n) |
| SOS DP | Subset sum queries | O(3^n) → O(n·2^n) |

### Golden Rules

```
1.  Define state precisely   — write "dp[i] = ..." in plain English first
2.  Base cases matter        — wrong base case = wrong everything
3.  Write recurrence first   — top-down is easier to derive
4.  Check loop order         — dependencies must be computed before use
5.  Reverse for 0/1          — forward for unbounded knapsack
6.  Coin outer = combos      — amount outer = permutations
7.  Init to INF for min DP   — init to -INF/0 for max DP
8.  Space optimize last      — get correctness first, then optimize
9.  Interval DP: len outer   — always iterate by interval length
10. Tree DP: post-order DFS  — children before parent
```

---

*End of Dynamic Programming — Zero to Advanced (C++ & LeetCode)*
