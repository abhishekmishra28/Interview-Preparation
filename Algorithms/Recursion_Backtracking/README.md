Here is the complete, consolidated Markdown guide. I have integrated your new code snippets, fixed syntax formatting issues (like `cppclass`), completed the cut-off Trie logic, and structured the final sections logically.

```markdown
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
class Solution {
public:
    // Method 1: Pure Recursion (Exponential)
    int fib(int n) {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    }
    
    // Method 2: Memoization (Top-Down DP)
    int fib(int n) {
        vector<int> memo(n + 1, -1);
        return fibMemo(n, memo);
    }
    
    int fibMemo(int n, vector<int>& memo) {
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n];
        memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
        return memo[n];
    }
};

// Time: O(2^n) → O(n) with memoization
// Space: O(n) stack + O(n) memo
```

## 2. Power of Two (LeetCode 231)

**Problem:** Check if n is power of 2

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Base cases
        if (n <= 0) return false;
        if (n == 1) return true;
        
        // If odd and not 1, cannot be power of 2
        if (n % 2 == 1) return false;
        
        // Recursive case
        return isPowerOfTwo(n / 2);
    }
    
    // Iterative approach
    bool isPowerOfTwoIterative(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
    }
};

// Time: O(log n)
// Space: O(log n) for recursion stack
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
class Solution {
public:
    // Pure recursion
    int climbStairs(int n) {
        if (n <= 2) return n;
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
    
    // With memoization
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }
    
    int helper(int n, vector<int>& memo) {
        if (n <= 2) return n;
        if (memo[n] != -1) return memo[n];
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
        return memo[n];
    }
};

// Time: O(2^n) → O(n) with memo
// Space: O(n)
```

---

# LeetCode Problems - Medium

## 7. Subsets (LeetCode 78)

**Problem:** Generate all subsets of given array

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
    void backtrack(vector<int>& nums, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Add current subset
        result.push_back(current);
        
        // Try adding each remaining element
        for (int i = start; i < nums.size(); i++) {
            // Choose
            current.push_back(nums[i]);
            
            // Explore
            backtrack(nums, i + 1, current, result);
            
            // Un-choose
            current.pop_back();
        }
    }
};

// Example: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

// Time: O(2^n)
// Space: O(n) for recursion depth
```

## 8. Subsets II (LeetCode 90)

**Problem:** Generate all unique subsets (with duplicates in input)

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Sort to handle duplicates
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
    void backtrack(vector<int>& nums, int start, 
                   vector<int>& current, vector<vector<int>>& result) {
        result.push_back(current);
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates
            if (i > start && nums[i] == nums[i-1]) continue;
            
            current.push_back(nums[i]);
            backtrack(nums, i + 1, current, result);
            current.pop_back();
        }
    }
};

// Time: O(2^n)
// Space: O(n)
```

## 9. Permutations (LeetCode 46)

**Problem:** Generate all permutations of array

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, current, used, result);
        return result;
    }
    
    void backtrack(vector<int>& nums, vector<int>& current,
                   vector<bool>& used, vector<vector<int>>& result) {
        // Base case: permutation complete
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            // Skip if already used
            if (used[i]) continue;
            
            // Choose
            current.push_back(nums[i]);
            used[i] = true;
            
            // Explore
            backtrack(nums, current, used, result);
            
            // Un-choose
            current.pop_back();
            used[i] = false;
        }
    }
};

// Example: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

// Time: O(n! × n)
// Space: O(n)
```

## 10. Permutations II (LeetCode 47)

**Problem:** Generate unique permutations (with duplicates)

```cpp
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Sort for duplicate handling
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, current, used, result);
        return result;
    }
    
    void backtrack(vector<int>& nums, vector<int>& current,
                   vector<bool>& used, vector<vector<int>>& result) {
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            
            // Skip duplicates
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            current.push_back(nums[i]);
            used[i] = true;
            backtrack(nums, current, used, result);
            current.pop_back();
            used[i] = false;
        }
    }
};

// Time: O(n! × n)
// Space: O(n)
```

## 11. Combination Sum (LeetCode 39)

**Problem:** Find combinations that sum to target (can reuse elements)

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
    void backtrack(vector<int>& candidates, int target, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        // Base cases
        if (target == 0) {
            result.push_back(current);
            return;
        }
        if (target < 0) return;
        
        for (int i = start; i < candidates.size(); i++) {
            // Choose
            current.push_back(candidates[i]);
            
            // Explore (i, not i+1, because we can reuse)
            backtrack(candidates, target - candidates[i], i, current, result);
            
            // Un-choose
            current.pop_back();
        }
    }
};

// Example: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]

// Time: O(n^(target/min))
// Space: O(target/min)
```

## 12. Combination Sum II (LeetCode 40)

**Problem:** Find unique combinations that sum to target (no reuse)

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
    void backtrack(vector<int>& candidates, int target, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(current);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates
            if (i > start && candidates[i] == candidates[i-1]) continue;
            
            // Pruning: if current number > target, no point continuing
            if (candidates[i] > target) break;
            
            current.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i + 1, current, result);
            current.pop_back();
        }
    }
};

// Time: O(2^n)
// Space: O(n)
```

## 13. Combinations (LeetCode 77)

**Problem:** Generate all combinations of k numbers from 1 to n

```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(n, k, 1, current, result);
        return result;
    }
    
    void backtrack(int n, int k, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        // Base case: combination complete
        if (current.size() == k) {
            result.push_back(current);
            return;
        }
        
        // Pruning: if remaining numbers < needed numbers
        for (int i = start; i <= n - (k - current.size()) + 1; i++) {
            current.push_back(i);
            backtrack(n, k, i + 1, current, result);
            current.pop_back();
        }
    }
};

// Example: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

// Time: O(C(n,k)) = O(n!/(k!(n-k)!))
// Space: O(k)
```

## 14. Letter Combinations of Phone Number (LeetCode 17)

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> mapping = {
            "",     // 0
            "",     // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz"  // 9
        };
        
        vector<string> result;
        string current;
        backtrack(digits, 0, current, mapping, result);
        return result;
    }
    
    void backtrack(string& digits, int index, string& current,
                   vector<string>& mapping, vector<string>& result) {
        // Base case
        if (index == digits.size()) {
            result.push_back(current);
            return;
        }
        
        // Get letters for current digit
        string letters = mapping[digits[index] - '0'];
        
        // Try each letter
        for (char c : letters) {
            current.push_back(c);
            backtrack(digits, index + 1, current, mapping, result);
            current.pop_back();
        }
    }
};

// Example: digits = "23"
// Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

// Time: O(4^n) worst case
// Space: O(n)
```

## 15. Generate Parentheses (LeetCode 22)

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(n, 0, 0, current, result);
        return result;
    }
    
    void backtrack(int n, int open, int close,
                   string& current, vector<string>& result) {
        // Base case: valid combination complete
        if (current.size() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        // Add opening parenthesis if possible
        if (open < n) {
            current.push_back('(');
            backtrack(n, open + 1, close, current, result);
            current.pop_back();
        }
        
        // Add closing parenthesis if valid
        if (close < open) {
            current.push_back(')');
            backtrack(n, open, close + 1, current, result);
            current.pop_back();
        }
    }
};

// Example: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]

// Time: O(4^n / √n) - Catalan number
// Space: O(n)
```

## 16. Word Search (LeetCode 79)

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool backtrack(vector<vector<char>>& board, string& word,
                   int i, int j, int index) {
        // Base case: found word
        if (index == word.size()) return true;
        
        // Boundary checks
        if (i < 0 || i >= board.size() || 
            j < 0 || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }
        
        // Mark as visited
        char temp = board[i][j];
        board[i][j] = '#';
        
        // Explore 4 directions
        bool found = backtrack(board, word, i + 1, j, index + 1) ||
                    backtrack(board, word, i - 1, j, index + 1) ||
                    backtrack(board, word, i, j + 1, index + 1) ||
                    backtrack(board, word, i, j - 1, index + 1);
        
        // Un-mark (backtrack)
        board[i][j] = temp;
        
        return found;
    }
};

// Time: O(m × n × 4^L) where L is word length
// Space: O(L)
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
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0, result);
        return result;
    }
    
    void backtrack(vector<string>& board, int row,
                   vector<vector<string>>& result) {
        // Base case: all queens placed
        if (row == board.size()) {
            result.push_back(board);
            return;
        }
        
        // Try placing queen in each column
        for (int col = 0; col < board.size(); col++) {
            if (isValid(board, row, col)) {
                // Choose
                board[row][col] = 'Q';
                
                // Explore
                backtrack(board, row + 1, result);
                
                // Un-choose
                board[row][col] = '.';
            }
        }
    }
    
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();
        
        // Check column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }
        
        // Check diagonal (top-left)
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        
        // Check diagonal (top-right)
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        
        return true;
    }
};

// Time: O(n!)
// Space: O(n²)
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
```
