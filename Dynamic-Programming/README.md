# Complete Dynamic Programming Guide — C++
## From Beginner to Advanced

## Table of Contents

### Part 1: Fundamentals
- [What is Dynamic Programming?](#what-is-dynamic-programming)
- [When to Use DP](#when-to-use-dp)
- [DP vs Recursion vs Greedy](#dp-vs-recursion-vs-greedy)
- [Core Concepts](#core-concepts)
- [Two Approaches: Top-Down vs Bottom-Up](#two-approaches)
- [How to Identify DP Problems](#how-to-identify-dp-problems)
- [Basic Patterns](#basic-patterns)
- [Easy Problems (15)](#easy-problems)

### Part 2: Intermediate Patterns
- [1D DP Problems](#1d-dp-problems)
- [2D DP Problems](#2d-dp-problems)
- [String DP](#string-dp)
- [Subsequence Problems](#subsequence-problems)
- [Medium Problems (20)](#medium-problems)

### Part 3: Advanced Patterns
- [Matrix Chain Multiplication](#matrix-chain-multiplication)
- [DP on Trees](#dp-on-trees)
- [DP with Bitmasking](#dp-with-bitmasking)
- [Digit DP](#digit-dp)
- [DP Optimizations](#dp-optimizations)
- [Hard Problems (15)](#hard-problems)

### Part 4: Practice & Strategy
- [Pattern Recognition Guide](#pattern-recognition-guide)
- [Common Mistakes](#common-mistakes)
- [Optimization Techniques](#optimization-techniques)
- [Practice Strategy](#practice-strategy)

---

# What is Dynamic Programming?

**Dynamic Programming (DP)** is an algorithmic technique that solves complex problems by:
1. Breaking them into **overlapping subproblems**
2. Solving each subproblem **only once**
3. **Storing** the results (memoization/tabulation)
4. **Reusing** stored results when needed

```
Without DP:  Solve same subproblem multiple times → Exponential time
With DP:     Solve each subproblem once, reuse result → Polynomial time

Example: Fibonacci
Without DP: fib(5) calls fib(4) and fib(3)
            fib(4) calls fib(3) and fib(2)
            fib(3) is computed TWICE! → O(2^n)

With DP:    Compute fib(3) once, store it, reuse → O(n)
```

---

# When to Use DP

## Problem Characteristics

```
✅ USE DP when problem has:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. OVERLAPPING SUBPROBLEMS
   Same subproblem solved multiple times
   
2. OPTIMAL SUBSTRUCTURE
   Optimal solution uses optimal solutions to subproblems
   
3. OPTIMIZATION (min/max)
   "Minimize cost", "Maximize profit", "Count ways"
   
4. SEQUENTIAL DECISIONS
   Decision at each step affects future decisions
```

## Keywords that Signal DP

```
"Count the number of ways"
"Minimum/Maximum cost"
"Longest/Shortest sequence"
"Can you reach/achieve X?"
"All possible combinations"
"Optimize something"
```

---

# DP vs Recursion vs Greedy

```c++
/* 
 * COMPARISON TABLE
 * 
 * Aspect        | Recursion  | DP          | Greedy
 * ══════════════╪════════════╪═════════════╪════════════════
 * Approach      | Top-down   | Both        | Local optimal
 * Subproblems   | Repeated   | Once        | No revisit
 * Time          | Often 2^n  | Polynomial  | Often O(n log n)
 * Space         | Call stack | Table       | O(1) or O(n)
 * Optimal?      | Yes        | Yes         | Not always
 * When to use   | Simple     | Overlapping | Greedy choice
 *               | problems   | subproblems | property
 */

// Example: Fibonacci

// 1. PURE RECURSION (Exponential time)
int fib_recursion(int n) {
    if (n <= 1) return n;
    return fib_recursion(n-1) + fib_recursion(n-2);
}

// 2. DP - MEMOIZATION (Linear time)
int fib_memo(int n, vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fib_memo(n-1, dp) + fib_memo(n-2, dp);
}

// 3. DP - TABULATION (Linear time)
int fib_tabulation(int n) {
    if (n <= 1) return n;
    vector<int> dp(n+1);
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// 4. DP - SPACE OPTIMIZED (Linear time, constant space)
int fib_optimized(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

---

# Core Concepts

## 1. Overlapping Subproblems

```
Problem: Compute fib(5)

Recursion Tree (notice repetitions):
                    fib(5)
                   /      \
              fib(4)      fib(3)
             /     \      /     \
        fib(3)   fib(2) fib(2) fib(1)
        /   \     /  \   /  \
    fib(2) fib(1) ...  ...  ...
    
fib(3) computed TWICE
fib(2) computed THREE times
This is OVERLAPPING SUBPROBLEMS!
```

## 2. Optimal Substructure

```
Problem: Shortest path from A to C through B

If:  A → B → C is optimal
Then: A → B must be optimal (for that segment)
      B → C must be optimal (for that segment)
      
If A → B wasn't optimal, we could replace it with 
a better path and improve A → B → C, contradicting 
that it was optimal.
```

## 3. State Definition

```c++
// DP state = what you need to track to solve subproblem

// Example 1: Fibonacci
// State: dp[i] = i-th Fibonacci number

// Example 2: Climbing Stairs (1 or 2 steps)
// State: dp[i] = ways to reach step i

// Example 3: Knapsack
// State: dp[i][w] = max value using first i items, weight limit w

// Example 4: Longest Common Subsequence
// State: dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]
```

## 4. Recurrence Relation

```c++
// Recurrence = formula relating current state to previous states

// Fibonacci: dp[i] = dp[i-1] + dp[i-2]
// Climbing:  dp[i] = dp[i-1] + dp[i-2]
// Knapsack:  dp[i][w] = max(dp[i-1][w], 
//                            dp[i-1][w-weight[i]] + value[i])
```

---

# Two Approaches

## Top-Down (Memoization)

```c++
/*
 * TOP-DOWN APPROACH
 * 
 * • Start from original problem
 * • Recursively break into subproblems
 * • Cache results to avoid recomputation
 * • Natural recursion flow
 * 
 * Pros: Intuitive, solves only needed subproblems
 * Cons: Recursion overhead, stack space
 */

class Solution {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }
    
private:
    int helper(int n, vector<int>& memo) {
        // Base cases
        if (n <= 2) return n;
        
        // Check if already computed
        if (memo[n] != -1) return memo[n];
        
        // Compute and store
        memo[n] = helper(n-1, memo) + helper(n-2, memo);
        return memo[n];
    }
};
```

## Bottom-Up (Tabulation)

```c++
/*
 * BOTTOM-UP APPROACH
 * 
 * • Start from smallest subproblems
 * • Build up to original problem
 * • Fill table iteratively
 * • No recursion
 * 
 * Pros: No recursion overhead, often faster
 * Cons: Must solve ALL subproblems
 */

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
};
```

---

# How to Identify DP Problems

## Step-by-Step Process

```
1. CHECK FOR OPTIMIZATION/COUNTING
   ❓ "Minimize", "Maximize", "Count ways"?
   
2. VERIFY SUBPROBLEM OVERLAP
   ❓ Will same subproblem be solved multiple times?
   
3. CONFIRM OPTIMAL SUBSTRUCTURE
   ❓ Can optimal solution be built from optimal subproblems?
   
4. DEFINE STATE
   ❓ What information uniquely identifies a subproblem?
   
5. FIND RECURRENCE RELATION
   ❓ How to compute state[i] from previous states?
   
6. IDENTIFY BASE CASES
   ❓ What are the smallest subproblems we know directly?
   
7. DETERMINE ORDER OF COMPUTATION
   ❓ What order ensures all dependencies are computed first?
```

## Example: Minimum Cost Climbing Stairs

```
Problem: Array cost[], step i costs cost[i]. 
         Start at 0 or 1, climb 1 or 2 steps at a time.
         Find minimum cost to reach top (beyond last step).

1. OPTIMIZATION? ✓ "Minimum cost"

2. OVERLAPPING? ✓ Cost to reach step i depends on i-1 and i-2
                  which are computed multiple times

3. OPTIMAL SUBSTRUCTURE? ✓ 
   If min cost to top is via step i, then:
   min cost to step i must be optimal

4. STATE DEFINITION:
   dp[i] = minimum cost to reach step i

5. RECURRENCE:
   dp[i] = cost[i] + min(dp[i-1], dp[i-2])

6. BASE CASES:
   dp[0] = cost[0]
   dp[1] = cost[1]

7. ORDER:
   Compute dp[0], dp[1], dp[2], ..., dp[n]
```

---

# Basic Patterns

## Pattern 1: 1D Linear DP

```c++
// Problems where dp[i] depends only on previous few elements
// Example: Fibonacci, Climbing Stairs, House Robber

// Template:
vector<int> dp(n);
dp[0] = base_case_0;
dp[1] = base_case_1;

for (int i = 2; i < n; i++) {
    dp[i] = f(dp[i-1], dp[i-2], ...);
}
```

## Pattern 2: 2D Grid DP

```c++
// Problems on 2D grid, dp[i][j] represents state at cell (i,j)
// Example: Unique Paths, Minimum Path Sum

// Template:
vector<vector<int>> dp(m, vector<int>(n));

// Base cases
for (int i = 0; i < m; i++) dp[i][0] = base;
for (int j = 0; j < n; j++) dp[0][j] = base;

// Fill table
for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
        dp[i][j] = f(dp[i-1][j], dp[i][j-1]);
    }
}
```

## Pattern 3: Subsequence DP

```c++
// Problems involving subsequences
// Example: Longest Increasing Subsequence, LCS

// Template:
vector<int> dp(n);
for (int i = 0; i < n; i++) {
    dp[i] = 1;  // Base case
    for (int j = 0; j < i; j++) {
        if (condition(arr[j], arr[i])) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
}
```

## Pattern 4: Knapsack Pattern

```c++
// Problems about choosing items with constraints
// Example: 0/1 Knapsack, Coin Change

// Template:
vector<vector<int>> dp(n+1, vector<int>(capacity+1, 0));

for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= capacity; w++) {
        // Don't take item i
        dp[i][w] = dp[i-1][w];
        
        // Take item i (if possible)
        if (weight[i] <= w) {
            dp[i][w] = max(dp[i][w], 
                          dp[i-1][w-weight[i]] + value[i]);
        }
    }
}
```

---

# Easy Problems

---

## E1. Climbing Stairs (LeetCode 70)

```cpp
/*
 * Problem: 70. Climbing Stairs
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * You are climbing a staircase. It takes n steps to reach top.
 * Each time you can climb 1 or 2 steps.
 * In how many distinct ways can you climb to the top?
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * At step n, you could have arrived from:
 * - Step n-1 (by taking 1 step)
 * - Step n-2 (by taking 2 steps)
 *
 * So: ways[n] = ways[n-1] + ways[n-2]
 * This is Fibonacci!
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH: Bottom-Up DP
 *
 * State: dp[i] = number of ways to reach step i
 * Recurrence: dp[i] = dp[i-1] + dp[i-2]
 * Base: dp[1] = 1, dp[2] = 2
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN: n = 5
 *
 * dp[1] = 1 (one way: 1)
 * dp[2] = 2 (two ways: 1+1, 2)
 * dp[3] = dp[2] + dp[1] = 2 + 1 = 3
 * dp[4] = dp[3] + dp[2] = 3 + 2 = 5
 * dp[5] = dp[4] + dp[3] = 5 + 3 = 8 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n) → can optimize to O(1)
 */

class Solution {
public:
    // Method 1: Bottom-Up DP
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
    
    // Method 2: Space Optimized O(1)
    int climbStairs_optimized(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1, prev1 = 2;
        
        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    // Method 3: Top-Down Memoization
    int climbStairs_memo(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }
    
private:
    int helper(int n, vector<int>& memo) {
        if (n <= 2) return n;
        if (memo[n] != -1) return memo[n];
        return memo[n] = helper(n-1, memo) + helper(n-2, memo);
    }
};
```

---

## E2. Fibonacci Number (LeetCode 509)

```cpp
/*
 * Problem: 509. Fibonacci Number
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * The Fibonacci numbers form a sequence where each number
 * is the sum of the two preceding ones, starting from 0 and 1.
 * Given n, calculate F(n).
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n) or O(1) optimized
 */

class Solution {
public:
    // Bottom-Up
    int fib(int n) {
        if (n <= 1) return n;
        
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
    
    // Space Optimized
    int fib_optimized(int n) {
        if (n <= 1) return n;
        
        int prev2 = 0, prev1 = 1;
        
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};
```

---

## E3. Min Cost Climbing Stairs (LeetCode 746)

```cpp
/*
 * Problem: 746. Min Cost Climbing Stairs
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array cost where cost[i] is cost of step i.
 * You can start at index 0 or 1.
 * Climb 1 or 2 steps at a time.
 * Return minimum cost to reach top (beyond last step).
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * To reach step i, you must pay cost[i].
 * You could arrive from step i-1 or i-2.
 * Choose the cheaper path.
 *
 * To reach "top" (beyond array), you can step from
 * last or second-last step without paying additional cost.
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH:
 *
 * State: dp[i] = min cost to reach step i
 * Recurrence: dp[i] = cost[i] + min(dp[i-1], dp[i-2])
 * Base: dp[0] = cost[0], dp[1] = cost[1]
 * Answer: min(dp[n-1], dp[n-2])
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN: cost = [10, 15, 20]
 *
 * dp[0] = 10
 * dp[1] = 15
 * dp[2] = 20 + min(10, 15) = 30
 * Answer = min(dp[1], dp[2]) = min(15, 30) = 15 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n) → O(1) optimized
 */

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        
        vector<int> dp(n);
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < n; i++) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        
        // Can reach top from last or second-last step
        return min(dp[n-1], dp[n-2]);
    }
    
    // Space Optimized
    int minCostClimbingStairs_optimized(vector<int>& cost) {
        int n = cost.size();
        int prev2 = cost[0];
        int prev1 = cost[1];
        
        for (int i = 2; i < n; i++) {
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return min(prev1, prev2);
    }
};
```

---

## E4. House Robber (LeetCode 198)

```cpp
/*
 * Problem: 198. House Robber
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums representing amount in each house,
 * you cannot rob two adjacent houses.
 * Return maximum amount you can rob.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * At house i, you have two choices:
 * 1. Rob house i: get nums[i] + max from houses up to i-2
 * 2. Don't rob house i: get max from houses up to i-1
 *
 * Choose the better option.
 *
 * ══════════════════════════════════════════════════════════
 * APPROACH:
 *
 * State: dp[i] = max money robbing houses 0 to i
 * Recurrence: dp[i] = max(dp[i-1], nums[i] + dp[i-2])
 * Base: dp[0] = nums[0], dp[1] = max(nums[0], nums[1])
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN: nums = [2, 7, 9, 3, 1]
 *
 * dp[0] = 2
 * dp[1] = max(2, 7) = 7
 * dp[2] = max(7, 9+2) = 11
 * dp[3] = max(11, 3+7) = 11
 * dp[4] = max(11, 1+11) = 12 ✓
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n) → O(1) optimized
 */

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
        }
        
        return dp[n-1];
    }
    
    // Space Optimized
    int rob_optimized(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; i++) {
            int curr = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};
```

---

## E5. Pascal's Triangle (LeetCode 118)

```cpp
/*
 * Problem: 118. Pascal's Triangle
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer numRows, return first numRows of Pascal's triangle.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Each element is sum of two elements above it.
 * triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j]
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n²)
 * SPACE: O(n²) for output
 */

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        
        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);  // Initialize with 1s
            
            for (int j = 1; j < i; j++) {
                row[j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
            
            triangle.push_back(row);
        }
        
        return triangle;
    }
};
```

---

## E6. Divisor Game (LeetCode 1025)

```cpp
/*
 * Problem: 1025. Divisor Game
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Alice and Bob play a game with number n.
 * On each turn, player chooses any x such that 0 < x < n
 * and n % x == 0, then replaces n with n - x.
 * Player who cannot make a move loses.
 * Alice starts first. Return true if Alice wins.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Mathematical insight: Alice wins if and only if n is even!
 * 
 * DP approach:
 * dp[i] = true if current player wins with number i
 * Try all possible moves x where i % x == 0
 * If any move leads to opponent losing, current player wins.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n²) DP approach, O(1) mathematical
 * SPACE: O(n) DP approach, O(1) mathematical
 */

class Solution {
public:
    // Mathematical solution
    bool divisorGame(int n) {
        return n % 2 == 0;
    }
    
    // DP solution
    bool divisorGame_dp(int n) {
        vector<bool> dp(n + 1, false);
        dp[1] = false;  // Lose with 1 (no valid move)
        
        for (int i = 2; i <= n; i++) {
            for (int x = 1; x < i; x++) {
                if (i % x == 0) {
                    // If opponent loses, current player wins
                    if (!dp[i - x]) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[n];
    }
};
```

---

## E7. Counting Bits (LeetCode 338)

```cpp
/*
 * Problem: 338. Counting Bits
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer n, return array ans of length n+1 where
 * ans[i] is number of 1's in binary representation of i.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Key observation: i & (i-1) removes rightmost 1 bit.
 * So: countBits(i) = countBits(i & (i-1)) + 1
 *
 * Or: i >> 1 is i/2, and i & 1 is last bit.
 * So: countBits(i) = countBits(i >> 1) + (i & 1)
 *
 * ══════════════════════════════════════════════════════════
 * DRY RUN: n = 5
 *
 * 0: 0000 → 0
 * 1: 0001 → 1
 * 2: 0010 → 1
 * 3: 0011 → 2
 * 4: 0100 → 1
 * 5: 0101 → 2
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(1) excluding output
 */

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1);
        ans[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i >> 1] + (i & 1);
        }
        
        return ans;
    }
    
    // Alternative using i & (i-1)
    vector<int> countBits_v2(int n) {
        vector<int> ans(n + 1);
        ans[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i & (i-1)] + 1;
        }
        
        return ans;
    }
};
```

---

## E8. N-th Tribonacci Number (LeetCode 1137)

```cpp
/*
 * Problem: 1137. N-th Tribonacci Number
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Tribonacci sequence: T(n) = T(n-1) + T(n-2) + T(n-3)
 * T(0) = 0, T(1) = 1, T(2) = 1
 * Given n, return T(n).
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n) or O(1) optimized
 */

class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;
        
        int t0 = 0, t1 = 1, t2 = 1;
        
        for (int i = 3; i <= n; i++) {
            int curr = t0 + t1 + t2;
            t0 = t1;
            t1 = t2;
            t2 = curr;
        }
        
        return t2;
    }
};
```

---

## E9. Get Maximum in Generated Array (LeetCode 1646)

```cpp
/*
 * Problem: 1646. Get Maximum in Generated Array
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer n, generate array nums where:
 * nums[0] = 0
 * nums[1] = 1
 * For i even: nums[i] = nums[i/2]
 * For i odd:  nums[i] = nums[i/2] + nums[i/2 + 1]
 * Return maximum integer in nums.
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n)
 * SPACE: O(n)
 */

class Solution {
public:
    int getMaximumGenerated(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        vector<int> nums(n + 1);
        nums[0] = 0;
        nums[1] = 1;
        int maxVal = 1;
        
        for (int i = 2; i <= n; i++) {
            if (i % 2 == 0) {
                nums[i] = nums[i / 2];
            } else {
                nums[i] = nums[i / 2] + nums[i / 2 + 1];
            }
            maxVal = max(maxVal, nums[i]);
        }
        
        return maxVal;
    }
};
```

---

## E10. Is Subsequence (LeetCode 392)

```cpp
/*
 * Problem: 392. Is Subsequence
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given strings s and t, return true if s is subsequence of t.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * Two pointer approach is simpler, but DP works too.
 * For DP: dp[i][j] = true if s[0..i-1] is subsequence of t[0..j-1]
 *
 * ══════════════════════════════════════════════════════════
 * TIME:  O(n) two pointers, O(m×n) DP
 * SPACE: O(1) two pointers, O(m×n) DP
 */

class Solution {
public:
    // Two Pointers (Preferred)
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        
        return i == s.size();
    }
    
    // DP approach
    bool isSubsequence_dp(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        // Base case: empty string is subsequence of any string
        for (int j = 0; j <= n; j++) {
            dp[0][j] = true;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        
        return dp[m][n];
    }
};
```

---

*[Easy problems 11-15 and Medium/Hard problems continue in next parts]*
# Dynamic Programming Guide - Part 2

## E11-E15: Remaining Easy Problems (Summary)

- **E11. Best Time to Buy/Sell Stock (LC 121)** — Track min price, max profit
- **E12. Maximum Subarray (LC 53)** — Kadane's algorithm, dp[i] = max subarray ending at i
- **E13. Range Sum Query - Immutable (LC 303)** — Prefix sum array
- **E14. Pascal's Triangle II (LC 119)** — Space-optimized row generation
- **E15. Unique Paths (LC 62)** — Grid DP, dp[i][j] = dp[i-1][j] + dp[i][j-1]

---

# Medium Problems

## M1. Coin Change (LeetCode 322)

```cpp
/*
 * Problem: 322. Coin Change
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given array coins and integer amount, return fewest number
 * of coins needed to make up that amount. Return -1 if not possible.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Unbounded Knapsack
 *
 * For amount i, try each coin:
 * - If coin ≤ i: dp[i] = min(dp[i], dp[i-coin] + 1)
 * - Use unlimited coins (unbounded)
 *
 * ══════════════════════════════════════════════════════════
 * TIME: O(amount × coins) | SPACE: O(amount)
 */

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
```

## M2. Longest Increasing Subsequence (LeetCode 300)

```cpp
/*
 * Problem: 300. Longest Increasing Subsequence
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given integer array nums, return length of longest strictly
 * increasing subsequence.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION:
 *
 * dp[i] = length of LIS ending at index i
 * For each i, check all j < i:
 *   If nums[j] < nums[i]: dp[i] = max(dp[i], dp[j] + 1)
 *
 * ══════════════════════════════════════════════════════════
 * TIME: O(n²) DP, O(n log n) with binary search
 * SPACE: O(n)
 */

class Solution {
public:
    // DP Solution O(n²)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        
        return maxLen;
    }
    
    // Binary Search Solution O(n log n)
    int lengthOfLIS_fast(vector<int>& nums) {
        vector<int> tails;
        
        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }
        
        return tails.size();
    }
};
```

## M3-M20: Additional Medium Problems (Summary with Key Concepts)

- **M3. Unique Paths II (LC 63)** — Grid DP with obstacles
- **M4. Minimum Path Sum (LC 64)** — Grid DP, dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
- **M5. Decode Ways (LC 91)** — String DP, check if 1 or 2 digits form valid decoding
- **M6. Longest Common Subsequence (LC 1143)** — 2D DP, match characters or skip
- **M7. Edit Distance (LC 72)** — 3 operations: insert, delete, replace
- **M8. House Robber II (LC 213)** — Circular array, solve twice (exclude first or last)
- **M9. Word Break (LC 139)** — dp[i] = can segment s[0..i-1]
- **M10. Partition Equal Subset Sum (LC 416)** — Subset sum variant of 0/1 knapsack
- **M11. Target Sum (LC 494)** — Count ways to assign +/- to reach target
- **M12. Perfect Squares (LC 279)** — Min squares that sum to n
- **M13. Maximal Square (LC 221)** — Largest square of 1s in matrix
- **M14. Palindromic Substrings (LC 647)** — Count all palindromes, expand around center
- **M15. Longest Palindromic Substring (LC 5)** — Expand around center or DP
- **M16. Triangle (LC 120)** — Min path sum from top to bottom
- **M17. Maximum Product Subarray (LC 152)** — Track both max and min (negative handling)
- **M18. Combination Sum IV (LC 377)** — Permutations count (order matters)
- **M19. Delete and Earn (LC 740)** — House Robber variant with frequencies
- **M20. Unique Binary Search Trees (LC 96)** — Catalan number, dp[i] = Σ dp[j] × dp[i-j-1]

---

# Hard Problems

## H1. Regular Expression Matching (LeetCode 10)

```cpp
/*
 * Problem: 10. Regular Expression Matching
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Implement regex matching with '.' and '*' where:
 * '.' matches any single character
 * '*' matches zero or more of preceding element
 *
 * ══════════════════════════════════════════════════════════
 * TIME: O(m×n) | SPACE: O(m×n)
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, etc
        for (int j = 2; j <= n; j++) {
            if (p[j-1] == '*') {
                dp[0][j] = dp[0][j-2];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*') {
                    // Zero occurrence OR one+ occurrence
                    dp[i][j] = dp[i][j-2] || 
                               (match(s[i-1], p[j-2]) && dp[i-1][j]);
                } else {
                    dp[i][j] = match(s[i-1], p[j-1]) && dp[i-1][j-1];
                }
            }
        }
        
        return dp[m][n];
    }
    
private:
    bool match(char s, char p) {
        return p == '.' || s == p;
    }
};
```

## H2. Wildcard Matching (LeetCode 44)

```cpp
/*
 * Problem: 44. Wildcard Matching
 * Similar to regex but '*' matches any sequence
 * TIME: O(m×n) | SPACE: O(m×n)
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                dp[0][j] = dp[0][j-1];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*') {
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                } else if (p[j-1] == '?' || s[i-1] == p[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        
        return dp[m][n];
    }
};
```

## H3. Burst Balloons (LeetCode 312)

```cpp
/*
 * Problem: 312. Burst Balloons
 *
 * ══════════════════════════════════════════════════════════
 * STATEMENT:
 * Given n balloons with nums[i] coins, burst balloons to
 * maximize coins. Bursting i gives nums[i-1]*nums[i]*nums[i+1] coins.
 *
 * ══════════════════════════════════════════════════════════
 * INTUITION: Interval DP
 *
 * Think backwards: which balloon to burst LAST in range [i,j]?
 * If k is last: dp[i][j] = dp[i][k-1] + nums[i-1]*nums[k]*nums[j+1] + dp[k+1][j]
 *
 * ══════════════════════════════════════════════════════════
 * TIME: O(n³) | SPACE: O(n²)
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        for (int len = 1; len <= n; len++) {
            for (int left = 1; left <= n - len + 1; left++) {
                int right = left + len - 1;
                
                for (int k = left; k <= right; k++) {
                    int coins = nums[left-1] * nums[k] * nums[right+1];
                    dp[left][right] = max(dp[left][right], 
                                         dp[left][k-1] + coins + dp[k+1][right]);
                }
            }
        }
        
        return dp[1][n];
    }
};
```

## H4-H15: Additional Hard Problems (Summary)

- **H4. Maximal Rectangle (LC 85)** — Use histogram for each row
- **H5. Distinct Subsequences (LC 115)** — Count ways s contains t as subsequence
- **H6. Interleaving String (LC 97)** — 2D DP checking if s3 is interleaving of s1, s2
- **H7. Scramble String (LC 87)** — Recursive partition check
- **H8. Best Time to Buy/Sell Stock III (LC 123)** — At most 2 transactions
- **H9. Best Time to Buy/Sell Stock IV (LC 188)** — At most k transactions
- **H10. Palindrome Partitioning II (LC 132)** — Min cuts for palindrome partitioning
- **H11. Longest Valid Parentheses (LC 32)** — Stack or DP for valid parens
- **H12. Dungeon Game (LC 174)** — Min initial health to reach princess
- **H13. Russian Doll Envelopes (LC 354)** — 2D LIS problem
- **H14. Frog Jump (LC 403)** — Stone jumping with varying steps
- **H15. Cherry Pickup (LC 741)** — Pick cherries on grid, two paths simultaneously

---

# Pattern Recognition Guide

## Decision Tree

```
┌─────────────────────────────────────────────────────┐
│ Is it an optimization/counting problem?             │
└─────────────────────────────────────────────────────┘
           │
           ▼
    ┌──────────────┐
    │ Check Pattern │
    └──────────────┘
           │
    ┌──────┴──────┐
    │             │
    ▼             ▼
[Linear]     [Grid/Path]
    │             │
    ▼             ▼
Fibonacci    Unique Paths
Stairs       Min Path Sum
House Rob    
    │             │
    ▼             ▼
[Sequence]   [Knapsack]
    │             │
    ▼             ▼
LIS/LCS      0/1 Knapsack
Edit Dist    Coin Change
             Subset Sum
```

## Signal → Pattern Table

```
SIGNALS                              → PATTERN
══════════════════════════════════════════════════════════════
"ways to reach"                      → 1D DP (Stairs)
"minimum/maximum cost"               → DP with optimization
"longest/shortest sequence"          → Subsequence DP
"can partition/split"                → Knapsack variant
"on grid, go right/down"             → 2D Grid DP
"match/align two strings"            → 2D String DP
"with at most k transactions"        → State machines
"burst/merge intervals"              → Interval DP
"on tree"                            → Tree DP (DFS + memo)
```

---

# Common Mistakes

## Mistake 1: Wrong Base Cases

```cpp
// ❌ WRONG
vector<int> dp(n);  // Uninitialized!
dp[0] = 1;
for (int i = 1; i < n; i++) { ... }

// ✅ CORRECT
vector<int> dp(n, 0);  // Initialize all
dp[0] = 1;
for (int i = 1; i < n; i++) { ... }
```

## Mistake 2: Off-by-One in Loops

```cpp
// ❌ WRONG
for (int i = 1; i < n; i++) {  // Misses last element!
    dp[i] = ...;
}

// ✅ CORRECT
for (int i = 1; i <= n; i++) {
    dp[i] = ...;
}
```

## Mistake 3: Not Handling Edge Cases

```cpp
// ❌ WRONG
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    // ... but what if amount is 0? Or coins empty?
}

// ✅ CORRECT
int coinChange(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (coins.empty()) return -1;
    // ... rest of logic
}
```

---

# Optimization Techniques

## Technique 1: Space Optimization

```cpp
// BEFORE: O(n) space
vector<int> dp(n);
for (int i = 0; i < n; i++) {
    dp[i] = dp[i-1] + dp[i-2];
}

// AFTER: O(1) space
int prev2 = 0, prev1 = 1;
for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
}
```

## Technique 2: 2D → 1D Space

```cpp
// BEFORE: O(m×n) space
vector<vector<int>> dp(m, vector<int>(n));

// AFTER: O(n) space (rolling array)
vector<int> prev(n), curr(n);
for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        curr[j] = prev[j] + curr[j-1];
    }
    swap(prev, curr);
}
```

## Technique 3: Memoization with Map (Sparse States)

```cpp
// When state space is large but only few states visited
unordered_map<string, int> memo;

int solve(int a, int b) {
    string key = to_string(a) + "," + to_string(b);
    if (memo.count(key)) return memo[key];
    // ... compute result
    return memo[key] = result;
}
```

---

# Practice Strategy

## Phase 1: Master Fundamentals (Week 1-2)

**Goal:** Understand core DP concepts

| Priority | Problem | Pattern | Why |
|:---------|:--------|:--------|:----|
| 🔴 | 70. Climbing Stairs | 1D DP | Foundation |
| 🔴 | 198. House Robber | 1D DP | Classic |
| 🔴 | 746. Min Cost Stairs | 1D DP | Variation |
| 🔴 | 509. Fibonacci | 1D DP | Simplest |
| 🔴 | 53. Maximum Subarray | 1D DP | Kadane's |

**Practice drill:**
- Code each 3 times: recursion, memo, tabulation
- Optimize space after mastering logic
- Explain recurrence relation out loud

---

## Phase 2: Pattern Recognition (Week 3-4)

**Goal:** Identify which pattern to use

| Pattern | Problems | Key Signal |
|:--------|:---------|:-----------|
| **1D DP** | 70, 198, 746, 91 | Single array, previous elements |
| **2D Grid** | 62, 63, 64, 221 | Matrix, right/down movement |
| **Knapsack** | 322, 416, 494, 377 | Choose/skip items, capacity |
| **Subsequence** | 300, 1143, 115, 647 | LIS, LCS, edit distance |

---

## Phase 3: Advanced Patterns (Week 5-6)

**Goal:** Master complex DP

| Priority | Problem | Technique | Why |
|:---------|:--------|:----------|:----|
| 🔴 | 322. Coin Change | Unbounded Knapsack | Most asked |
| 🔴 | 300. LIS | Subsequence | Classic |
| 🔴 | 1143. LCS | 2D String DP | Foundation |
| 🔴 | 72. Edit Distance | 2D String DP | Important |
| 🟡 | 312. Burst Balloons | Interval DP | Advanced |
| 🟡 | 10. Regex Match | 2D DP | Tricky |

---

## Phase 4: Interview Prep (Week 7-8)

**Practice goals:**
- Solve 50+ DP problems total
- Time yourself: 30 mins for medium, 45 for hard
- Explain approach before coding
- Optimize space after solving

---

# Quick Reference

## Complexity Cheatsheet

```
PATTERN                    TIME        SPACE
══════════════════════════════════════════════════════════
1D Linear DP              O(n)        O(n) → O(1)
2D Grid DP                O(m×n)      O(m×n) → O(n)
Knapsack                  O(n×W)      O(n×W) → O(W)
LIS (DP)                  O(n²)       O(n)
LIS (Binary Search)       O(n log n)  O(n)
LCS                       O(m×n)      O(m×n) → O(min(m,n))
Edit Distance             O(m×n)      O(m×n) → O(min(m,n))
Interval DP               O(n³)       O(n²)
Matrix Chain Mult         O(n³)       O(n²)
```

## DP Checklist

**Before coding:**
- [ ] Can I break into subproblems?
- [ ] Do subproblems overlap?
- [ ] Can I define state clearly?
- [ ] What's the recurrence relation?
- [ ] What are base cases?

**While coding:**
- [ ] Initialize DP table correctly
- [ ] Handle base cases first
- [ ] Fill table in correct order
- [ ] Check array bounds
- [ ] Consider space optimization

**After coding:**
- [ ] Test with small inputs
- [ ] Check edge cases (n=0, n=1)
- [ ] Verify time/space complexity
- [ ] Can I optimize space?

---

## Template Comparison

```cpp
// TOP-DOWN (Memoization)
int solve(int n, vector<int>& memo) {
    if (base_case) return base_value;
    if (memo[n] != -1) return memo[n];
    return memo[n] = recurrence(solve(n-1), solve(n-2), ...);
}

// BOTTOM-UP (Tabulation)
int solve(int n) {
    vector<int> dp(n+1);
    dp[0] = base_0;
    dp[1] = base_1;
    for (int i = 2; i <= n; i++) {
        dp[i] = recurrence(dp[i-1], dp[i-2], ...);
    }
    return dp[n];
}

// SPACE OPTIMIZED
int solve(int n) {
    int prev2 = base_0, prev1 = base_1;
    for (int i = 2; i <= n; i++) {
        int curr = recurrence(prev1, prev2, ...);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

---

**End of Complete Dynamic Programming Guide** 🚀

*50+ LeetCode Problems · All Major Patterns · Optimization Techniques*

## Key Takeaways

1. **DP = Recursion + Memoization** (or build table bottom-up)
2. **Always define state clearly** before coding
3. **Master basic patterns first** (1D, 2D, Knapsack, Subsequence)
4. **Space optimization** often possible (O(n) → O(1), O(n²) → O(n))
5. **Practice pattern recognition** more than memorizing solutions

**Most Important:** Understand WHY a solution is DP, not just HOW to code it!
