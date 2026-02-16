# Strings DSA - Complete Guide with LeetCode

## Table of Contents
- [String Fundamentals](#string-fundamentals)
- [String Patterns & Techniques](#string-patterns--techniques)
- [Two Pointer Technique](#two-pointer-technique)
- [Sliding Window](#sliding-window)
- [String Manipulation](#string-manipulation)
- [Pattern Matching](#pattern-matching)
- [LeetCode Problems - Easy](#leetcode-problems---easy)
- [LeetCode Problems - Medium](#leetcode-problems---medium)
- [LeetCode Problems - Hard](#leetcode-problems---hard)
- [Problem Patterns](#problem-patterns)
- [Common String Algorithms](#common-string-algorithms)
- [Optimization & Common Mistakes](#optimization--common-mistakes)
- [Practice Strategy](#practice-strategy)

---

# String Fundamentals

## What is a String?

**String:** A sequence of characters. In C++, strings can be represented as:
- Character arrays: `char str[] = "hello"`
- STL string: `string str = "hello"`

## Key String Operations

### 1. Length/Size
```cpp
string s = "hello";
int len = s.length();    // or s.size()
```

### 2. Access Characters
```cpp
char ch = s[0];          // First character
char last = s[s.length()-1];  // Last character
```

### 3. Concatenation
```cpp
string s1 = "Hello";
string s2 = "World";
string s3 = s1 + " " + s2;  // "Hello World"
```

### 4. Substring
```cpp
string s = "Hello World";
string sub = s.substr(0, 5);  // "Hello"
// substr(start_index, length)
```

### 5. Compare
```cpp
string s1 = "abc";
string s2 = "abc";
if (s1 == s2) { }        // Equal
if (s1 < s2) { }         // Lexicographic comparison
```

## Important String Functions

```cpp
// Convert case
transform(s.begin(), s.end(), s.begin(), ::tolower);
transform(s.begin(), s.end(), s.begin(), ::toupper);

// Reverse
reverse(s.begin(), s.end());

// Find substring
size_t pos = s.find("sub");
if (pos != string::npos) { }

// Replace
s.replace(pos, len, "new");

// Erase
s.erase(pos, len);

// Insert
s.insert(pos, "text");

// Check if character is
isalpha(ch);   // letter
isdigit(ch);   // digit
isalnum(ch);   // alphanumeric
isspace(ch);   // whitespace
```

---

# String Patterns & Techniques

## Pattern 1: Character Frequency Count

**Use HashMap/Array to count character occurrences**

```cpp
// Using array (for lowercase letters)
int freq[26] = {0};
for (char c : s) {
    freq[c - 'a']++;
}

// Using unordered_map (for any characters)
unordered_map<char, int> freq;
for (char c : s) {
    freq[c]++;
}
```

## Pattern 2: Palindrome Check

```cpp
bool isPalindrome(string s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

## Pattern 3: Anagram Detection

```cpp
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    for (char c : t) {
        freq[c]--;
        if (freq[c] < 0) return false;
    }
    return true;
}
```

---

# Two Pointer Technique

## What is Two Pointer?

**Technique using two pointers to traverse string from different positions**

### Pattern 1: Opposite Ends
```cpp
// Pointers start from both ends, move toward center
int left = 0;
int right = s.length() - 1;

while (left < right) {
    // Process
    left++;
    right--;
}
```

### Pattern 2: Same Direction
```cpp
// Both pointers start from beginning, move at different speeds
int slow = 0;
int fast = 0;

while (fast < s.length()) {
    // Process
    slow++;
    fast++;
}
```

### Example: Remove Duplicates
```cpp
string removeDuplicates(string s) {
    int i = 0;  // Position to write
    
    for (int j = 0; j < s.length(); j++) {
        if (i == 0 || s[j] != s[i-1]) {
            s[i++] = s[j];
        }
    }
    
    return s.substr(0, i);
}
```

---

# Sliding Window

## What is Sliding Window?

**Technique for finding subarrays/substrings satisfying certain conditions**

## Fixed Size Window

```cpp
// Find max sum of k consecutive elements
int maxSum(string s, int k) {
    int windowSum = 0, maxSum = 0;
    
    // First window
    for (int i = 0; i < k; i++) {
        windowSum += s[i];
    }
    maxSum = windowSum;
    
    // Slide window
    for (int i = k; i < s.length(); i++) {
        windowSum = windowSum - s[i-k] + s[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

## Variable Size Window

```cpp
// Longest substring with at most k distinct characters
int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> freq;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        freq[s[right]]++;
        
        // Shrink window if constraint violated
        while (freq.size() > k) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) {
                freq.erase(s[left]);
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
```

---

# String Manipulation

## Common Transformations

### 1. Reverse Words
```cpp
string reverseWords(string s) {
    // Reverse entire string
    reverse(s.begin(), s.end());
    
    // Reverse each word
    int start = 0;
    for (int i = 0; i <= s.length(); i++) {
        if (i == s.length() || s[i] == ' ') {
            reverse(s.begin() + start, s.begin() + i);
            start = i + 1;
        }
    }
    
    return s;
}
```

### 2. Remove Spaces
```cpp
string removeSpaces(string s) {
    int i = 0;
    for (int j = 0; j < s.length(); j++) {
        if (s[j] != ' ') {
            s[i++] = s[j];
        }
    }
    return s.substr(0, i);
}
```

### 3. String Compression
```cpp
string compress(string s) {
    string result = "";
    int count = 1;
    
    for (int i = 1; i <= s.length(); i++) {
        if (i < s.length() && s[i] == s[i-1]) {
            count++;
        } else {
            result += s[i-1];
            if (count > 1) {
                result += to_string(count);
            }
            count = 1;
        }
    }
    
    return result;
}
```

---

# Pattern Matching

## Naive Pattern Matching

```cpp
vector<int> naiveSearch(string text, string pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            positions.push_back(i);
        }
    }
    
    return positions;
}
// Time: O(n × m)
```

## KMP Algorithm (Knuth-Morris-Pratt)

```cpp
vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

vector<int> KMPSearch(string text, string pattern) {
    vector<int> positions;
    vector<int> lps = computeLPS(pattern);
    
    int i = 0;  // index for text
    int j = 0;  // index for pattern
    
    while (i < text.length()) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == pattern.length()) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return positions;
}
// Time: O(n + m)
```

---

# LeetCode Problems - Easy

## 1. Reverse String (LeetCode 344)

**Problem:** Reverse a string in-place

```cpp
/*
 * Problem: 344. Reverse String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Write a function that reverses a string.
 * The input string is given as an array of characters s.
 *
 * You must do this by modifying the input array in-place
 * with O(1) extra memory.
 *
 * ------------------------------------------------------------
 * APPROACH: Two Pointer Technique
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Use two pointers: left and right
 * 2️⃣ Start from both ends
 * 3️⃣ Swap and move toward center
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Initialize left = 0, right = n-1
 * 2. While left < right:
 *    - Swap s[left] and s[right]
 *    - Increment left
 *    - Decrement right
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n) - single pass
 * Space: O(1) - in-place modification
 */

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {
            // Swap characters
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
```

## 2. Valid Anagram (LeetCode 242)

```cpp
/*
 * Problem: 242. Valid Anagram
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings s and t, return true if t is an anagram of s,
 * and false otherwise.
 *
 * An anagram is a word formed by rearranging the letters of another.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Sorting
 *
 * Idea: Anagrams have same characters in same frequency
 *
 * Steps:
 * 1. Sort both strings
 * 2. Compare if equal
 *
 * Time: O(n log n)
 * Space: O(1)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Frequency Count (Optimal)
 *
 * Idea: Count character frequencies and compare
 *
 * Steps:
 * 1. Use array/map to count frequencies
 * 2. Check if frequencies match
 *
 * Time: O(n)
 * Space: O(1) - fixed size array for 26 letters
 */

class Solution {
public:
    // Approach 1: Sorting
    bool isAnagram_Sort(string s, string t) {
        if (s.length() != t.length()) return false;
        
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        
        return s == t;
    }
    
    // Approach 2: Frequency Count (Optimal)
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        vector<int> freq(26, 0);
        
        for (int i = 0; i < s.length(); i++) {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }
        
        for (int count : freq) {
            if (count != 0) return false;
        }
        
        return true;
    }
};
```

## 3. Valid Palindrome (LeetCode 125)

```cpp
/*
 * Problem: 125. Valid Palindrome
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * A phrase is a palindrome if, after converting all uppercase
 * letters to lowercase and removing all non-alphanumeric characters,
 * it reads the same forward and backward.
 *
 * Given a string s, return true if it is a palindrome.
 *
 * ------------------------------------------------------------
 * APPROACH: Two Pointer
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Skip non-alphanumeric characters
 * 2️⃣ Compare characters case-insensitively
 * 3️⃣ Use two pointers from both ends
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Initialize left = 0, right = n-1
 * 2. While left < right:
 *    - Skip non-alphanumeric from left
 *    - Skip non-alphanumeric from right
 *    - Compare lowercase characters
 *    - If mismatch, return false
 * 3. Return true
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(1)
 */

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            
            // Skip non-alphanumeric from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare characters (case-insensitive)
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
};
```

## 4. First Unique Character (LeetCode 387)

```cpp
/*
 * Problem: 387. First Unique Character in a String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, find the first non-repeating character
 * and return its index. If it does not exist, return -1.
 *
 * ------------------------------------------------------------
 * APPROACH: Frequency Count
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Count frequency of each character
 * 2. Iterate through string again
 * 3. Return index of first character with frequency 1
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n) - two passes
 * Space: O(1) - fixed size array (26 letters)
 */

class Solution {
public:
    int firstUniqChar(string s) {
        // Count frequency
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Find first unique
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
```

## 5. Longest Common Prefix (LeetCode 14)

```cpp
/*
 * Problem: 14. Longest Common Prefix
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Write a function to find the longest common prefix string
 * amongst an array of strings.
 *
 * If there is no common prefix, return an empty string "".
 *
 * ------------------------------------------------------------
 * APPROACH 1: Vertical Scanning
 *
 * Compare characters column by column
 *
 * Time: O(S) where S is sum of all characters
 * Space: O(1)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Horizontal Scanning
 *
 * Find LCP of first two strings, then with third, and so on
 *
 * Time: O(S)
 * Space: O(1)
 */

class Solution {
public:
    // Approach 1: Vertical Scanning
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        
        // Check each column
        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0][i];
            
            // Check this character in all strings
            for (int j = 1; j < strs.size(); j++) {
                // If index out of bounds or character mismatch
                if (i >= strs[j].length() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0];
    }
    
    // Approach 2: Horizontal Scanning
    string longestCommonPrefix_v2(vector<string>& strs) {
        if (strs.empty()) return "";
        
        string prefix = strs[0];
        
        for (int i = 1; i < strs.size(); i++) {
            // Find common prefix with current string
            int j = 0;
            while (j < prefix.length() && j < strs[i].length() 
                   && prefix[j] == strs[i][j]) {
                j++;
            }
            
            prefix = prefix.substr(0, j);
            
            if (prefix.empty()) return "";
        }
        
        return prefix;
    }
};
```

## 6. Valid Parentheses (LeetCode 20)

```cpp
/*
 * Problem: 20. Valid Parentheses
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s containing just the characters
 * '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * Valid string conditions:
 * 1. Open brackets must be closed by same type
 * 2. Open brackets must be closed in correct order
 * 3. Every close bracket has corresponding open bracket
 *
 * ------------------------------------------------------------
 * APPROACH: Stack
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Last opened bracket should be first closed (LIFO)
 * 2️⃣ Use stack to track opening brackets
 * 3️⃣ For closing bracket, check if matches top of stack
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. For each character:
 *    - If opening bracket → push to stack
 *    - If closing bracket:
 *      • If stack empty → invalid
 *      • If top doesn't match → invalid
 *      • Otherwise → pop from stack
 * 2. At end, stack should be empty
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(n) - stack
 */

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                // Opening bracket
                st.push(c);
            } else {
                // Closing bracket
                if (st.empty()) return false;
                
                char top = st.top();
                
                // Check if matches
                if ((c == ')' && top == '(') ||
                    (c == '}' && top == '{') ||
                    (c == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        
        return st.empty();
    }
};
```

## 7. Implement strStr() (LeetCode 28)

```cpp
/*
 * Problem: 28. Find the Index of the First Occurrence in a String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings needle and haystack,
 * return the index of the first occurrence of needle in haystack,
 * or -1 if needle is not part of haystack.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Brute Force
 *
 * Check every position in haystack
 *
 * Time: O(n × m)
 * Space: O(1)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Built-in Function
 *
 * Use string::find()
 *
 * Time: O(n × m) worst case
 * Space: O(1)
 */

class Solution {
public:
    // Approach 1: Brute Force
    int strStr(string haystack, string needle) {
        int n = haystack.length();
        int m = needle.length();
        
        if (m == 0) return 0;
        if (m > n) return -1;
        
        for (int i = 0; i <= n - m; i++) {
            int j;
            for (j = 0; j < m; j++) {
                if (haystack[i + j] != needle[j]) {
                    break;
                }
            }
            
            if (j == m) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Approach 2: Using built-in
    int strStr_v2(string haystack, string needle) {
        size_t pos = haystack.find(needle);
        return (pos != string::npos) ? pos : -1;
    }
};
```

## 8. Roman to Integer (LeetCode 13)

```cpp
/*
 * Problem: 13. Roman to Integer
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Roman numerals are represented by seven symbols:
 * I=1, V=5, X=10, L=50, C=100, D=500, M=1000
 *
 * Special cases (subtraction):
 * I before V or X
 * X before L or C
 * C before D or M
 *
 * Convert roman numeral string to integer.
 *
 * ------------------------------------------------------------
 * APPROACH: HashMap + Iteration
 *
 * ------------------------------------------------------------
 * KEY OBSERVATION:
 *
 * If current value < next value → subtract current
 * Otherwise → add current
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Create map of roman to integer
 * 2. Iterate through string:
 *    - If current < next → subtract
 *    - Otherwise → add
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(1) - fixed map size
 */

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> roman = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        
        int result = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // If current < next, subtract
            if (i + 1 < s.length() && roman[s[i]] < roman[s[i + 1]]) {
                result -= roman[s[i]];
            } else {
                result += roman[s[i]];
            }
        }
        
        return result;
    }
};
```

---

# LeetCode Problems - Medium

## 9. Longest Substring Without Repeating Characters (LeetCode 3)

```cpp
/*
 * Problem: 3. Longest Substring Without Repeating Characters
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, find the length of the longest substring
 * without repeating characters.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window + HashSet
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Use sliding window with two pointers
 * 2️⃣ Expand window by moving right pointer
 * 3️⃣ Shrink window when duplicate found
 * 4️⃣ Use set to track characters in current window
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Initialize left = 0, maxLen = 0
 * 2. For right from 0 to n-1:
 *    - While s[right] exists in set:
 *      • Remove s[left] from set
 *      • Increment left
 *    - Add s[right] to set
 *    - Update maxLen
 *
 * ------------------------------------------------------------
 * OPTIMIZATION:
 *
 * Instead of set, use map to store last index of character
 * Jump left pointer directly to max(left, lastIndex[char] + 1)
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n) - each character visited at most twice
 * Space: O(min(n, m)) where m is charset size
 */

class Solution {
public:
    // Approach 1: Sliding Window with Set
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Shrink window while duplicate exists
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }
            
            // Add current character
            window.insert(s[right]);
            
            // Update max length
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
    // Approach 2: Optimized with HashMap
    int lengthOfLongestSubstring_v2(string s) {
        unordered_map<char, int> lastIndex;
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            
            // If character seen before and in current window
            if (lastIndex.count(c) && lastIndex[c] >= left) {
                left = lastIndex[c] + 1;
            }
            
            lastIndex[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```

## 10. Longest Palindromic Substring (LeetCode 5)

```cpp
/*
 * Problem: 5. Longest Palindromic Substring
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, return the longest palindromic substring in s.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Expand Around Center
 *
 * For each possible center, expand outward
 *
 * Palindrome centers:
 * - Single character (odd length)
 * - Between two characters (even length)
 *
 * Time: O(n²)
 * Space: O(1)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Dynamic Programming
 *
 * dp[i][j] = true if s[i...j] is palindrome
 *
 * Base cases:
 * - Single character: always palindrome
 * - Two characters: palindrome if same
 *
 * Recurrence:
 * dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]
 *
 * Time: O(n²)
 * Space: O(n²)
 */

class Solution {
public:
    // Approach 1: Expand Around Center (Optimal)
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < s.length(); i++) {
            // Odd length palindrome
            int len1 = expandAroundCenter(s, i, i);
            
            // Even length palindrome
            int len2 = expandAroundCenter(s, i, i + 1);
            
            int len = max(len1, len2);
            
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLen);
    }
    
private:
    int expandAroundCenter(string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
    
public:
    // Approach 2: Dynamic Programming
    string longestPalindrome_DP(string s) {
        int n = s.length();
        if (n < 2) return s;
        
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0, maxLen = 1;
        
        // Single character palindromes
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        
        // Two character palindromes
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                start = i;
                maxLen = 2;
            }
        }
        
        // Longer palindromes
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                
                if (s[i] == s[j] && dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                    start = i;
                    maxLen = len;
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
};
```

## 11. Group Anagrams (LeetCode 49)

```cpp
/*
 * Problem: 49. Group Anagrams
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array of strings strs,
 * group the anagrams together.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Sort as Key
 *
 * Anagrams produce same string when sorted
 * Use sorted string as key in hashmap
 *
 * Time: O(n × k log k) where k is max string length
 * Space: O(n × k)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Character Count as Key
 *
 * Create key from character frequency count
 * Anagrams have same character count
 *
 * Time: O(n × k)
 * Space: O(n × k)
 */

class Solution {
public:
    // Approach 1: Sort as Key
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (string& s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        
        return result;
    }
    
    // Approach 2: Character Count as Key
    vector<vector<string>> groupAnagrams_v2(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (string& s : strs) {
            string key = getKey(s);
            groups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        
        return result;
    }
    
private:
    string getKey(string& s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        string key = "";
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                key += string(1, 'a' + i) + to_string(count[i]);
            }
        }
        
        return key;
    }
};
```

## 12. String to Integer (atoi) (LeetCode 8)

```cpp
/*
 * Problem: 8. String to Integer (atoi)
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Implement the atoi function which converts a string to integer.
 *
 * Rules:
 * 1. Ignore leading whitespace
 * 2. Check for optional '+' or '-'
 * 3. Read digits until non-digit or end
 * 4. Return 0 if no valid conversion
 * 5. Clamp to [INT_MIN, INT_MAX] range
 *
 * ------------------------------------------------------------
 * APPROACH: State Machine
 *
 * States: whitespace → sign → number → done
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Handle overflow before it happens
 * 2️⃣ Check: result > INT_MAX/10 before multiplying
 * 3️⃣ Or: result == INT_MAX/10 and digit > 7
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(1)
 */

class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = s.length();
        int sign = 1;
        long result = 0;
        
        // Step 1: Skip leading whitespace
        while (i < n && s[i] == ' ') {
            i++;
        }
        
        // Step 2: Check sign
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Step 3: Convert digits
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // Check overflow before adding
            if (result > (INT_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        return sign * result;
    }
};
```

## 13. Zigzag Conversion (LeetCode 6)

```cpp
/*
 * Problem: 6. Zigzag Conversion
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * The string "PAYPALISHIRING" is written in zigzag pattern
 * on a given number of rows.
 *
 * Write code to convert string to zigzag pattern.
 *
 * Example:
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * Output: "PAHNAPLSIIGYIR"
 *
 * ------------------------------------------------------------
 * APPROACH: Simulate Zigzag Pattern
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Create numRows strings
 * 2️⃣ Traverse input and append to appropriate row
 * 3️⃣ Direction changes at first and last row
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Create array of strings for each row
 * 2. Initialize currentRow = 0, goingDown = false
 * 3. For each character:
 *    - Append to rows[currentRow]
 *    - If at top or bottom row, change direction
 *    - Move to next row based on direction
 * 4. Concatenate all rows
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(n)
 */

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || numRows >= s.length()) {
            return s;
        }
        
        vector<string> rows(min(numRows, (int)s.length()));
        int currentRow = 0;
        bool goingDown = false;
        
        for (char c : s) {
            rows[currentRow] += c;
            
            // Change direction at first and last row
            if (currentRow == 0 || currentRow == numRows - 1) {
                goingDown = !goingDown;
            }
            
            // Move to next row
            currentRow += goingDown ? 1 : -1;
        }
        
        // Concatenate all rows
        string result = "";
        for (string& row : rows) {
            result += row;
        }
        
        return result;
    }
};
```

## 14. Longest Repeating Character Replacement (LeetCode 424)

```cpp
/*
 * Problem: 424. Longest Repeating Character Replacement
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * You are given a string s and an integer k.
 * You can choose any character and change it to any other
 * uppercase English character at most k times.
 *
 * Return the length of the longest substring containing
 * the same letter after performing the operations.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Valid window: windowSize - maxFreq <= k
 * 2️⃣ windowSize = right - left + 1
 * 3️⃣ maxFreq = frequency of most common character in window
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Use sliding window with frequency map
 * 2. Expand window by moving right pointer
 * 3. Track max frequency in current window
 * 4. If window invalid (size - maxFreq > k):
 *    - Shrink from left
 * 5. Update max length
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n)
 * Space: O(1) - fixed size (26 letters)
 */

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0;
        int maxFreq = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Add current character to window
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            
            // Check if window is valid
            int windowSize = right - left + 1;
            int replacements = windowSize - maxFreq;
            
            // If invalid, shrink window
            if (replacements > k) {
                freq[s[left] - 'A']--;
                left++;
            }
            
            // Update max length
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
```

## 15. Minimum Window Substring (LeetCode 76)

```cpp
/*
 * Problem: 76. Minimum Window Substring
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings s and t,
 * return the minimum window substring of s such that
 * every character in t (including duplicates) is included.
 *
 * If no such substring exists, return "".
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window with Two Hashmaps
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Need to track:
 *    - Required characters (from t)
 *    - Characters in current window
 *
 * 2️⃣ Valid window: all characters from t are present
 *    with sufficient frequency
 *
 * 3️⃣ Once valid, try to minimize by shrinking from left
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Count characters in t
 * 2. Use two pointers: left, right
 * 3. Expand window (move right):
 *    - Add character to window
 *    - If character needed, increment formed count
 * 4. When window valid:
 *    - Update minimum window
 *    - Try to shrink from left
 * 5. Return minimum window found
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(|s| + |t|)
 * Space: O(|s| + |t|)
 */

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";
        
        // Count characters in t
        unordered_map<char, int> required;
        for (char c : t) {
            required[c]++;
        }
        
        int requiredChars = required.size();
        int formed = 0;
        
        // Window character counts
        unordered_map<char, int> window;
        
        int left = 0;
        int minLen = INT_MAX;
        int minLeft = 0;
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            window[c]++;
            
            // Check if current character satisfies requirement
            if (required.count(c) && window[c] == required[c]) {
                formed++;
            }
            
            // Try to shrink window while it's valid
            while (left <= right && formed == requiredChars) {
                // Update minimum window
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                // Shrink from left
                char leftChar = s[left];
                window[leftChar]--;
                
                if (required.count(leftChar) && 
                    window[leftChar] < required[leftChar]) {
                    formed--;
                }
                
                left++;
            }
        }
        
        return (minLen == INT_MAX) ? "" : s.substr(minLeft, minLen);
    }
};
```

## 16. Decode String (LeetCode 394)

```cpp
/*
 * Problem: 394. Decode String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an encoded string, return its decoded string.
 *
 * Encoding rule: k[encoded_string]
 * - encoded_string inside [] repeated k times
 *
 * Example:
 * "3[a2[c]]" → "accaccacc"
 * "3[a]2[bc]" → "aaabcbc"
 *
 * ------------------------------------------------------------
 * APPROACH: Stack
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Nested structure suggests stack
 * 2️⃣ Need to track:
 *    - Current number
 *    - Current string
 *    - Previous states when entering nested brackets
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Use stack to store (prevString, repeatCount)
 * 2. For each character:
 *    - Digit: build number
 *    - '[': push current state, reset
 *    - ']': pop state, repeat current string
 *    - Letter: add to current string
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(maxK × n) where maxK is max repeat count
 * Space: O(n)
 */

class Solution {
public:
    string decodeString(string s) {
        stack<string> strStack;
        stack<int> numStack;
        
        string currentStr = "";
        int currentNum = 0;
        
        for (char c : s) {
            if (isdigit(c)) {
                // Build number (can be multi-digit)
                currentNum = currentNum * 10 + (c - '0');
            } 
            else if (c == '[') {
                // Save current state
                strStack.push(currentStr);
                numStack.push(currentNum);
                
                // Reset for nested content
                currentStr = "";
                currentNum = 0;
            } 
            else if (c == ']') {
                // Pop previous state
                string prevStr = strStack.top();
                strStack.pop();
                int repeatCount = numStack.top();
                numStack.pop();
                
                // Repeat current string
                string repeated = "";
                for (int i = 0; i < repeatCount; i++) {
                    repeated += currentStr;
                }
                
                // Append to previous string
                currentStr = prevStr + repeated;
            } 
            else {
                // Regular character
                currentStr += c;
            }
        }
        
        return currentStr;
    }
};
```

## 17. Palindromic Substrings (LeetCode 647)

```cpp
/*
 * Problem: 647. Palindromic Substrings
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, return the number of palindromic substrings.
 *
 * A string is a palindrome when it reads the same backward as forward.
 *
 * ------------------------------------------------------------
 * APPROACH: Expand Around Center
 *
 * Similar to Longest Palindromic Substring,
 * but count all palindromes instead of finding longest.
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Every palindrome has a center
 * 2️⃣ Two types of centers:
 *    - Single character (odd length)
 *    - Between two characters (even length)
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * For each possible center:
 *   Expand outward while characters match
 *   Count each valid palindrome found
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n²)
 * Space: O(1)
 */

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Odd length palindromes (center = single char)
            count += expandAroundCenter(s, i, i);
            
            // Even length palindromes (center = between two chars)
            count += expandAroundCenter(s, i, i + 1);
        }
        
        return count;
    }
    
private:
    int expandAroundCenter(string& s, int left, int right) {
        int count = 0;
        
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        
        return count;
    }
};
```

---

# LeetCode Problems - Hard

## 18. Longest Valid Parentheses (LeetCode 32)

```cpp
/*
 * Problem: 32. Longest Valid Parentheses
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string containing just '(' and ')',
 * return the length of the longest valid parentheses substring.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Dynamic Programming
 *
 * dp[i] = length of longest valid parentheses ending at i
 *
 * Cases:
 * 1. s[i] == '(' → dp[i] = 0
 * 2. s[i] == ')':
 *    - If s[i-1] == '(' → dp[i] = dp[i-2] + 2
 *    - If s[i-1] == ')' and s[i-dp[i-1]-1] == '(':
 *      → dp[i] = dp[i-1] + 2 + dp[i-dp[i-1]-2]
 *
 * Time: O(n)
 * Space: O(n)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Stack
 *
 * Use stack to track indices of unmatched parentheses
 *
 * Time: O(n)
 * Space: O(n)
 *
 * ------------------------------------------------------------
 * APPROACH 3: Two Pass (Optimal Space)
 *
 * Scan left-to-right, then right-to-left
 *
 * Time: O(n)
 * Space: O(1)
 */

class Solution {
public:
    // Approach 1: Dynamic Programming
    int longestValidParentheses_DP(string s) {
        int n = s.length();
        if (n < 2) return 0;
        
        vector<int> dp(n, 0);
        int maxLen = 0;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    // Case: ...()
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } 
                else if (i - dp[i - 1] - 1 >= 0 && 
                         s[i - dp[i - 1] - 1] == '(') {
                    // Case: ...))
                    dp[i] = dp[i - 1] + 2;
                    if (i - dp[i - 1] - 2 >= 0) {
                        dp[i] += dp[i - dp[i - 1] - 2];
                    }
                }
                
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
    
    // Approach 2: Stack
    int longestValidParentheses_Stack(string s) {
        stack<int> st;
        st.push(-1);  // Base for valid substrings
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                
                if (st.empty()) {
                    st.push(i);  // New base
                } else {
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }
        
        return maxLen;
    }
    
    // Approach 3: Two Pass (Space Optimized)
    int longestValidParentheses(string s) {
        int left = 0, right = 0;
        int maxLen = 0;
        
        // Left to right
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            
            if (left == right) {
                maxLen = max(maxLen, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }
        
        left = right = 0;
        
        // Right to left
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '(') {
                left++;
            } else {
                right++;
            }
            
            if (left == right) {
                maxLen = max(maxLen, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }
        
        return maxLen;
    }
};
```

## 19. Edit Distance (LeetCode 72)

```cpp
/*
 * Problem: 72. Edit Distance
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings word1 and word2,
 * return the minimum number of operations required
 * to convert word1 to word2.
 *
 * Allowed operations:
 * 1. Insert a character
 * 2. Delete a character
 * 3. Replace a character
 *
 * ------------------------------------------------------------
 * APPROACH: Dynamic Programming
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * dp[i][j] = min operations to convert word1[0...i-1]
 *            to word2[0...j-1]
 *
 * Base cases:
 * - dp[0][j] = j (insert j characters)
 * - dp[i][0] = i (delete i characters)
 *
 * Recurrence:
 * If word1[i-1] == word2[j-1]:
 *   dp[i][j] = dp[i-1][j-1]
 * Else:
 *   dp[i][j] = 1 + min(
 *     dp[i-1][j],      // delete
 *     dp[i][j-1],      // insert
 *     dp[i-1][j-1]     // replace
 *   )
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(m × n)
 * Space: O(m × n) - can be optimized to O(min(m,n))
 */

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Base cases
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }
        
        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],      // delete
                        dp[i][j - 1],      // insert
                        dp[i - 1][j - 1]   // replace
                    });
                }
            }
        }
        
        return dp[m][n];
    }
};
```

## 20. Distinct Subsequences (LeetCode 115)

```cpp
/*
 * Problem: 115. Distinct Subsequences
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings s and t,
 * return the number of distinct subsequences of s which equals t.
 *
 * ------------------------------------------------------------
 * APPROACH: Dynamic Programming
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * dp[i][j] = number of ways to form t[0...j-1]
 *            using s[0...i-1]
 *
 * Base cases:
 * - dp[i][0] = 1 (empty string can be formed in 1 way)
 * - dp[0][j] = 0 for j > 0
 *
 * Recurrence:
 * If s[i-1] == t[j-1]:
 *   dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
 *   (use current char OR skip it)
 * Else:
 *   dp[i][j] = dp[i-1][j]
 *   (skip current char in s)
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(m × n)
 * Space: O(m × n) - can be optimized to O(n)
 */

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // Use long long to avoid overflow
        vector<vector<unsigned long long>> dp(m + 1, 
                                               vector<unsigned long long>(n + 1, 0));
        
        // Base case: empty t can be formed in 1 way
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        return dp[m][n];
    }
};
```

## 21. Word Break II (LeetCode 140)

```cpp
/*
 * Problem: 140. Word Break II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s and a dictionary wordDict,
 * add spaces in s to construct a sentence where each word
 * is a valid dictionary word.
 *
 * Return all such possible sentences in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking with Memoization
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ Use backtracking to try all word combinations
 * 2️⃣ Memoize results for substrings to avoid recomputation
 * 3️⃣ For each position, try all words that match
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Convert wordDict to set for O(1) lookup
 * 2. For each position in string:
 *    - Try all possible words starting at this position
 *    - If word found in dict:
 *      • Recursively solve for remaining substring
 *      • Combine current word with recursive results
 * 3. Memoize results for each starting index
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n × 2^n) worst case
 * Space: O(n × 2^n) for memoization
 */

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return backtrack(s, 0, dict, memo);
    }
    
private:
    vector<string> backtrack(string& s, int start,
                            unordered_set<string>& dict,
                            unordered_map<int, vector<string>>& memo) {
        // Check memo
        if (memo.count(start)) {
            return memo[start];
        }
        
        vector<string> result;
        
        // Base case
        if (start == s.length()) {
            result.push_back("");
            return result;
        }
        
        // Try all possible words
        for (int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            
            if (dict.count(word)) {
                // Recursively solve for remaining
                vector<string> sublist = backtrack(s, end, dict, memo);
                
                for (string& sub : sublist) {
                    result.push_back(word + (sub.empty() ? "" : " ") + sub);
                }
            }
        }
        
        memo[start] = result;
        return result;
    }
};
```

## 22. Substring with Concatenation of All Words (LeetCode 30)

```cpp
/*
 * Problem: 30. Substring with Concatenation of All Words
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s and an array of strings words (all same length),
 * return all starting indices of substring(s) in s that is
 * a concatenation of each word in words exactly once,
 * in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window with HashMap
 *
 * ------------------------------------------------------------
 * KEY OBSERVATIONS:
 *
 * 1️⃣ All words have same length (wordLen)
 * 2️⃣ Valid substring length = wordLen × numWords
 * 3️⃣ Use sliding window of size (wordLen × numWords)
 * 4️⃣ Check if window contains all words with correct frequency
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Count frequency of each word in words
 * 2. Try starting positions 0 to wordLen-1:
 *    - Use sliding window
 *    - Track words in current window
 *    - Compare with required word frequencies
 * 3. If match, add starting index to result
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n × m) where n = len(s), m = len(words)
 * Space: O(m)
 */

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int numWords = words.size();
        int totalLen = wordLen * numWords;
        
        if (s.length() < totalLen) return result;
        
        // Count word frequencies
        unordered_map<string, int> wordCount;
        for (string& word : words) {
            wordCount[word]++;
        }
        
        // Try different starting positions
        for (int i = 0; i < wordLen; i++) {
            int left = i;
            int count = 0;
            unordered_map<string, int> seen;
            
            for (int j = i; j <= s.length() - wordLen; j += wordLen) {
                string word = s.substr(j, wordLen);
                
                if (wordCount.count(word)) {
                    seen[word]++;
                    count++;
                    
                    // Too many occurrences of this word
                    while (seen[word] > wordCount[word]) {
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                    
                    // Found valid window
                    if (count == numWords) {
                        result.push_back(left);
                        
                        // Slide window
                        string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }
                } else {
                    // Reset window
                    seen.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        
        return result;
    }
};
```

## 23. Text Justification (LeetCode 68)

```cpp
/*
 * Problem: 68. Text Justification
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array of strings words and a width maxWidth,
 * format the text such that each line has exactly maxWidth
 * characters and is fully justified.
 *
 * Rules:
 * 1. Pack as many words as possible in each line
 * 2. Distribute extra spaces evenly between words
 * 3. If spaces can't be distributed evenly, add more to left
 * 4. Last line should be left-justified
 *
 * ------------------------------------------------------------
 * APPROACH: Greedy Line Packing
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. For each line:
 *    - Pack as many words as fit
 *    - Calculate number of spaces needed
 *    - Distribute spaces evenly
 *
 * 2. For last line:
 *    - Left-justify (single space between words)
 *    - Pad right with spaces
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time: O(n) where n is total characters
 * Space: O(n)
 */

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while (i < words.size()) {
            // Determine words for current line
            int lineLength = words[i].length();
            int j = i + 1;
            
            while (j < words.size()) {
                // +1 for mandatory space between words
                if (lineLength + 1 + words[j].length() > maxWidth) break;
                lineLength += 1 + words[j].length();
                j++;
            }
            
            // Build line
            int numWords = j - i;
            int numSpaces = maxWidth - lineLength;
            
            string line = "";
            
            // Last line or line with single word (left-justify)
            if (j == words.size() || numWords == 1) {
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) line += " ";
                }
                // Pad right with spaces
                while (line.length() < maxWidth) {
                    line += " ";
                }
            } 
            else {
                // Middle lines (fully justify)
                int gaps = numWords - 1;
                int spacesPerGap = (maxWidth - lineLength + gaps) / gaps;
                int extraSpaces = (maxWidth - lineLength + gaps) % gaps;
                
                for (int k = i; k < j; k++) {
                    line += words[k];
                    
                    if (k < j - 1) {
                        // Add spaces
                        int spaces = spacesPerGap;
                        if (k - i < extraSpaces) spaces++;
                        
                        line += string(spaces, ' ');
                    }
                }
            }
            
            result.push_back(line);
            i = j;
        }
        
        return result;
    }
};
```

---

# Problem Patterns

## Pattern 1: Two Pointer Technique

**When to use:**
- Palindrome problems
- Removing duplicates
- Finding pairs with target sum
- Reversing strings

**Common problems:**
- Valid Palindrome (125)
- Reverse String (344)
- Two Sum II (167)

**Template:**
```cpp
int left = 0, right = n - 1;
while (left < right) {
    // Process
    if (condition) {
        left++;
    } else {
        right--;
    }
}
```

## Pattern 2: Sliding Window

**When to use:**
- Substring problems
- Finding subarrays with condition
- "longest/shortest substring" problems

**Common problems:**
- Longest Substring Without Repeating Characters (3)
- Minimum Window Substring (76)
- Longest Repeating Character Replacement (424)

**Template:**
```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // Add s[right] to window
    
    while (window invalid) {
        // Remove s[left] from window
        left++;
    }
    
    // Update result
}
```

## Pattern 3: Character Frequency Count

**When to use:**
- Anagram problems
- Finding unique characters
- Character counting problems

**Common problems:**
- Valid Anagram (242)
- Group Anagrams (49)
- First Unique Character (387)

**Template:**
```cpp
unordered_map<char, int> freq;
for (char c : s) {
    freq[c]++;
}

// Or for lowercase letters only
int freq[26] = {0};
for (char c : s) {
    freq[c - 'a']++;
}
```

## Pattern 4: Dynamic Programming on Strings

**When to use:**
- Edit distance
- Longest common subsequence
- Palindrome problems
- String matching

**Common problems:**
- Longest Palindromic Substring (5)
- Edit Distance (72)
- Distinct Subsequences (115)

**Template:**
```cpp
vector<vector<int>> dp(m + 1, vector<int>(n + 1));

// Base cases
dp[0][0] = ...;

// Fill DP table
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        if (s1[i-1] == s2[j-1]) {
            dp[i][j] = dp[i-1][j-1] + ...;
        } else {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
}
```

## Pattern 5: Stack for String Problems

**When to use:**
- Nested structures (parentheses)
- Decoding problems
- Expression evaluation

**Common problems:**
- Valid Parentheses (20)
- Decode String (394)
- Longest Valid Parentheses (32)

**Template:**
```cpp
stack<char> st;
for (char c : s) {
    if (opening condition) {
        st.push(c);
    } else if (closing condition) {
        if (!st.empty() && matches(st.top(), c)) {
            st.pop();
        }
    }
}
```

---

# Common String Algorithms

## 1. KMP (Knuth-Morris-Pratt) Pattern Matching

**Purpose:** Find pattern in text efficiently

```cpp
vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    
    for (int i = 1; i < m; ) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

int KMPSearch(string text, string pattern) {
    vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;
    
    while (i < text.length()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        
        if (j == pattern.length()) {
            return i - j;  // Found at index i-j
        } else if (i < text.length() && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return -1;  // Not found
}
```

## 2. Manacher's Algorithm (Longest Palindrome)

**Purpose:** Find longest palindromic substring in O(n)

```cpp
string longestPalindrome_Manacher(string s) {
    // Transform string: "abc" → "^#a#b#c#$"
    string t = "^#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    t += '$';
    
    int n = t.length();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    
    for (int i = 1; i < n - 1; i++) {
        // Mirror of i
        int mirror = 2 * center - i;
        
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        // Expand around i
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }
        
        // Update center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }
    
    // Find maximum
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}
```

## 3. Rabin-Karp (Rolling Hash)

**Purpose:** Pattern matching using hashing

```cpp
class RabinKarp {
private:
    const int BASE = 256;
    const int MOD = 1e9 + 7;
    
public:
    vector<int> search(string text, string pattern) {
        vector<int> result;
        int m = pattern.length();
        int n = text.length();
        
        if (m > n) return result;
        
        long long patternHash = 0;
        long long textHash = 0;
        long long h = 1;
        
        // Calculate h = BASE^(m-1) % MOD
        for (int i = 0; i < m - 1; i++) {
            h = (h * BASE) % MOD;
        }
        
        // Calculate initial hashes
        for (int i = 0; i < m; i++) {
            patternHash = (BASE * patternHash + pattern[i]) % MOD;
            textHash = (BASE * textHash + text[i]) % MOD;
        }
        
        // Slide pattern over text
        for (int i = 0; i <= n - m; i++) {
            // Check if hashes match
            if (patternHash == textHash) {
                // Verify character by character
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) result.push_back(i);
            }
            
            // Calculate next hash
            if (i < n - m) {
                textHash = (BASE * (textHash - text[i] * h) + text[i + m]) % MOD;
                if (textHash < 0) textHash += MOD;
            }
        }
        
        return result;
    }
};
```

## 4. Trie (Prefix Tree)

**Purpose:** Efficient string storage and retrieval

```cpp
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};
```

---

# Optimization & Common Mistakes

## Optimization Techniques

### 1. Use StringBuilder for Concatenation

```cpp
// ❌ Inefficient - creates new string each time
string result = "";
for (char c : s) {
    result += c;  // O(n²) overall
}

// ✅ Efficient - amortized O(1) per append
string result;
result.reserve(s.length());  // Pre-allocate
for (char c : s) {
    result.push_back(c);
}
```

### 2. Character Array vs String

```cpp
// For frequent modifications
vector<char> chars(s.begin(), s.end());
// Modify chars
string result(chars.begin(), chars.end());
```

### 3. Use References to Avoid Copies

```cpp
// ❌ Creates copy
void process(string s) { }

// ✅ No copy
void process(const string& s) { }
```

### 4. Early Termination

```cpp
// Check length mismatch early
if (s1.length() != s2.length()) return false;

// Check impossible cases
if (s.empty() || pattern.empty()) return result;
```

## Common Mistakes

### 1. Off-by-One Errors

```cpp
// ❌ Wrong - may access s[n]
for (int i = 0; i <= s.length(); i++) {
    if (s[i] == 'a') { }
}

// ✅ Correct
for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'a') { }
}
```

### 2. String Modification During Iteration

```cpp
// ❌ Wrong - modifying while iterating
for (int i = 0; i < s.length(); i++) {
    s.erase(i, 1);  // Changes length
}

// ✅ Correct - iterate backwards or use two pointers
for (int i = s.length() - 1; i >= 0; i--) {
    if (condition) {
        s.erase(i, 1);
    }
}
```

### 3. Case Sensitivity

```cpp
// ❌ Wrong - case sensitive
if (s1 == s2) { }

// ✅ Correct - case insensitive
transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
if (s1 == s2) { }
```

### 4. Not Handling Empty Strings

```cpp
// ❌ Wrong - may cause issues
char first = s[0];

// ✅ Correct
if (!s.empty()) {
    char first = s[0];
}
```

### 5. Integer Overflow in String Problems

```cpp
// ❌ Wrong - may overflow
int hash = 0;
for (char c : s) {
    hash = hash * 31 + c;
}

// ✅ Correct - use modulo
long long hash = 0;
const int MOD = 1e9 + 7;
for (char c : s) {
    hash = (hash * 31 + c) % MOD;
}
```

---

# Practice Strategy

## Week 1: Fundamentals (Easy Problems)

**Focus:** Basic string operations, two pointers

**Problems to solve:**
1. Reverse String (344)
2. Valid Anagram (242)
3. Valid Palindrome (125)
4. First Unique Character (387)
5. Longest Common Prefix (14)
6. Valid Parentheses (20)
7. Implement strStr() (28)
8. Roman to Integer (13)

**Practice goals:**
- Master two pointer technique
- Get comfortable with character frequency counting
- Understand palindrome checking

## Week 2: Intermediate Patterns (Medium Problems)

**Focus:** Sliding window, hash maps

**Problems to solve:**
1. Longest Substring Without Repeating Characters (3)
2. Longest Palindromic Substring (5)
3. Group Anagrams (49)
4. String to Integer (8)
5. Zigzag Conversion (6)
6. Longest Repeating Character Replacement (424)
7. Palindromic Substrings (647)
8. Decode String (394)

**Practice goals:**
- Master sliding window technique
- Understand expand-around-center for palindromes
- Practice with hash maps for grouping

## Week 3: Advanced Techniques (Hard + Algorithms)

**Focus:** Dynamic programming, advanced algorithms

**Problems to solve:**
1. Minimum Window Substring (76)
2. Edit Distance (72)
3. Longest Valid Parentheses (32)
4. Distinct Subsequences (115)
5. Word Break II (140)
6. Substring with Concatenation of All Words (30)
7. Text Justification (68)

**Study algorithms:**
- KMP pattern matching
- Manacher's algorithm
- Rabin-Karp
- Trie implementation

**Practice goals:**
- Master string DP patterns
- Implement classic algorithms from scratch
- Optimize time and space complexity

## Additional Practice

### More Easy:
- LeetCode 709: To Lower Case
- LeetCode 771: Jewels and Stones
- LeetCode 804: Unique Morse Code Words
- LeetCode 657: Robot Return to Origin

### More Medium:
- LeetCode 151: Reverse Words in a String
- LeetCode 271: Encode and Decode Strings
- LeetCode 539: Minimum Time Difference
- LeetCode 791: Custom Sort String
- LeetCode 227: Basic Calculator II

### More Hard:
- LeetCode 44: Wildcard Matching
- LeetCode 10: Regular Expression Matching
- LeetCode 97: Interleaving String
- LeetCode 214: Shortest Palindrome

## Key Concepts to Master

1. **Two Pointer Technique**
   - Opposite ends
   - Same direction
   - Fast and slow pointers

2. **Sliding Window**
   - Fixed size window
   - Variable size window
   - Window with constraints

3. **String Matching**
   - Naive approach
   - KMP algorithm
   - Rabin-Karp

4. **Dynamic Programming**
   - LCS (Longest Common Subsequence)
   - Edit distance
   - Palindrome DP

5. **Data Structures**
   - Trie
   - Suffix array
   - Rolling hash

## Interview Preparation Tips

1. **Always clarify:**
   - Case sensitivity?
   - ASCII or Unicode?
   - Empty string handling?
   - In-place modification allowed?

2. **Optimize space:**
   - Can you use O(1) extra space?
   - Is character set limited (26 letters)?

3. **Time complexity:**
   - Avoid O(n²) string concatenation
   - Use StringBuilder/string reserve
   - Consider preprocessing

4. **Edge cases:**
   - Empty string
   - Single character
   - All same characters
   - Very long strings

---

**End of Strings DSA Guide**

Good luck with your string problem-solving journey! 🚀
