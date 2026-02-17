# Strings DSA - Complete Java Guide with LeetCode

## Table of Contents
- [Java String Fundamentals](#java-string-fundamentals)
- [Java String vs StringBuilder vs StringBuffer](#java-string-vs-stringbuilder-vs-stringbuffer)
- [Complete Java String Method Reference](#complete-java-string-method-reference)
- [StringBuilder Method Reference](#stringbuilder-method-reference)
- [Character Utility Methods](#character-utility-methods)
- [String Patterns & Techniques](#string-patterns--techniques)
- [Two Pointer Technique](#two-pointer-technique)
- [Sliding Window](#sliding-window)
- [LeetCode Problems - Easy](#leetcode-problems---easy)
- [LeetCode Problems - Medium](#leetcode-problems---medium)
- [LeetCode Problems - Hard](#leetcode-problems---hard)
- [Classic String Algorithms](#classic-string-algorithms)
- [Problem Patterns Quick Reference](#problem-patterns-quick-reference)
- [Optimization & Common Mistakes](#optimization--common-mistakes)
- [Practice Strategy](#practice-strategy)

---

# Java String Fundamentals

## String Creation

```java
// String literal (stored in String Pool)
String s1 = "hello";

// Using new keyword (stored in Heap)
String s2 = new String("hello");

// From char array
char[] chars = {'h', 'e', 'l', 'l', 'o'};
String s3 = new String(chars);

// From StringBuilder
StringBuilder sb = new StringBuilder("hello");
String s4 = sb.toString();

// From char array with offset and count
String s5 = new String(chars, 0, 3);  // "hel"
```

## String Immutability

```java
// ⚠️ CRITICAL JAVA CONCEPT
// Strings are IMMUTABLE in Java
// Every modification creates a NEW String object

String s = "hello";
s.toUpperCase();     // ❌ Does NOT modify s
s = s.toUpperCase(); // ✅ Reassign the result
// s is now "HELLO"

// This is why StringBuilder is preferred for modification
```

## String Comparison - VERY IMPORTANT

```java
String s1 = new String("hello");
String s2 = new String("hello");

// ❌ WRONG: Compares object references
if (s1 == s2) { }       // FALSE! Different objects

// ✅ CORRECT: Compares content
if (s1.equals(s2)) { }  // TRUE

// ✅ Case-insensitive comparison
if (s1.equalsIgnoreCase(s2)) { }

// ✅ Lexicographic comparison
int cmp = s1.compareTo(s2);     // 0 if equal
int cmp2 = s1.compareToIgnoreCase(s2);
```

## String Pool

```java
// Literals share the same pool reference
String a = "hello";
String b = "hello";
System.out.println(a == b);        // TRUE (same pool object)
System.out.println(a.equals(b));   // TRUE

// new keyword always creates new object
String c = new String("hello");
System.out.println(a == c);        // FALSE (different object)
System.out.println(a.equals(c));   // TRUE

// intern() forces pool lookup
String d = c.intern();
System.out.println(a == d);        // TRUE (same pool object)
```

---

# Java String vs StringBuilder vs StringBuffer

## Comparison Table

| Feature            | String         | StringBuilder  | StringBuffer   |
| :----------------- | :------------- | :------------- | :------------- |
| Mutability         | Immutable      | Mutable        | Mutable        |
| Thread Safety      | Thread-safe    | Not thread-safe| Thread-safe    |
| Performance        | Slow (concat)  | Fast           | Slower (sync)  |
| Storage            | String Pool    | Heap           | Heap           |
| When to Use        | Read-only ops  | Single thread  | Multi-thread   |

## When to Use What

```java
// ✅ Use String when:
// - Value won't change
// - Simple operations
String name = "Alice";

// ✅ Use StringBuilder when:
// - Building strings in loops (MOST LeetCode problems)
// - Frequent modifications
// - Single-threaded (interviews)
StringBuilder sb = new StringBuilder();
for (int i = 0; i < n; i++) {
    sb.append(s.charAt(i));  // O(1) amortized
}
String result = sb.toString();

// ✅ Use StringBuffer when:
// - Multi-threaded applications (rare in interviews)
StringBuffer buffer = new StringBuffer();
```

---

# Complete Java String Method Reference

## 1. Length & Access

```java
String s = "Hello World";

// Length
int len = s.length();                    // 11

// Character access
char c = s.charAt(3);                    // 'l'
char first = s.charAt(0);               // 'H'
char last = s.charAt(s.length() - 1);   // 'd'

// Convert to char array
char[] arr = s.toCharArray();

// Convert to byte array
byte[] bytes = s.getBytes();

// codePoint (Unicode)
int cp = s.codePointAt(0);              // 72 (Unicode for 'H')
```

## 2. Substring

```java
String s = "Hello World";

// substring(startIndex) → from start to end
String sub1 = s.substring(6);           // "World"

// substring(startIndex, endIndex) → [start, end)
String sub2 = s.substring(0, 5);        // "Hello"
String sub3 = s.substring(6, 11);       // "World"

// ⚠️ NOTE: endIndex is EXCLUSIVE
// substring(0, 5) → indices 0,1,2,3,4
```

## 3. Comparison

```java
String s1 = "Hello";
String s2 = "hello";
String s3 = "Hello";

// Equals (case-sensitive)
s1.equals(s2);                   // false
s1.equals(s3);                   // true

// Equals (case-insensitive)
s1.equalsIgnoreCase(s2);         // true

// Lexicographic comparison
s1.compareTo(s2);                // negative (H < h in ASCII)
s1.compareTo(s3);                // 0 (equal)
s1.compareToIgnoreCase(s2);      // 0 (equal ignoring case)

// Content equals (String vs StringBuilder)
StringBuilder sb = new StringBuilder("Hello");
s1.contentEquals(sb);            // true

// Starts/ends with
s1.startsWith("He");             // true
s1.startsWith("he");             // false
s1.endsWith("lo");               // true
```

## 4. Search & Find

```java
String s = "Hello World Hello";

// indexOf → first occurrence (-1 if not found)
s.indexOf('l');                  // 2
s.indexOf("lo");                 // 3
s.indexOf('l', 5);               // 9  (search from index 5)
s.indexOf("Hello", 1);           // 12 (search from index 1)

// lastIndexOf → last occurrence
s.lastIndexOf('l');              // 15
s.lastIndexOf("Hello");          // 12

// contains → boolean check
s.contains("World");             // true
s.contains("world");             // false

// startsWith / endsWith
s.startsWith("Hello");           // true
s.endsWith("Hello");             // true
s.startsWith("World", 6);        // true (from index 6)

// matches → regex check
"hello123".matches("[a-z]+\\d+"); // true

// regionMatches
// (toffset, other, ooffset, len)
s.regionMatches(6, "World", 0, 5); // true
s.regionMatches(true, 6, "world", 0, 5); // true (ignore case)
```

## 5. Modification (Returns NEW String)

```java
String s = "  Hello World  ";

// Trim whitespace
s.trim();                        // "Hello World" (leading/trailing only)
s.strip();                       // "Hello World" (Unicode-aware, Java 11+)
s.stripLeading();                // "Hello World  " (Java 11+)
s.stripTrailing();               // "  Hello World" (Java 11+)

// Case conversion
"hello".toUpperCase();           // "HELLO"
"HELLO".toLowerCase();           // "hello"

// Replace
"Hello".replace('l', 'r');       // "Herro" (char replacement)
"Hello".replace("ll", "yy");     // "Heyyo" (string replacement)
"Hello World".replaceAll("l+", "r"); // "Hero Word" (regex)
"Hello".replaceFirst("l", "r");  // "Herlo" (first match only)

// Concatenation
"Hello".concat(" World");        // "Hello World"

// Repeat (Java 11+)
"abc".repeat(3);                 // "abcabcabc"

// Intern
"hello".intern();                // returns pool reference
```

## 6. Splitting & Joining

```java
// split(regex)
String csv = "a,b,c,d";
String[] parts = csv.split(",");     // ["a", "b", "c", "d"]
String[] parts2 = csv.split(",", 2); // ["a", "b,c,d"] (limit=2)

// split with special characters (need escape)
"a.b.c".split("\\.");            // ["a", "b", "c"]
"a|b|c".split("\\|");            // ["a", "b", "c"]

// join (Java 8+)
String.join(", ", "a", "b", "c");    // "a, b, c"
String.join("-", new String[]{"x","y","z"}); // "x-y-z"

// join with List
List<String> list = Arrays.asList("a", "b", "c");
String.join(", ", list);         // "a, b, c"
```

## 7. Conversion Methods

```java
// valueOf → String from other types
String.valueOf(42);              // "42"
String.valueOf(3.14);            // "3.14"
String.valueOf(true);            // "true"
String.valueOf('A');             // "A"
String.valueOf(new char[]{'h','i'}); // "hi"

// toString on primitives (auto-boxing)
Integer.toString(42);            // "42"
Integer.toBinaryString(5);       // "101"
Integer.toHexString(255);        // "ff"
Integer.toOctalString(8);        // "10"

// Parse from String
int i = Integer.parseInt("42");
long l = Long.parseLong("123456789");
double d = Double.parseDouble("3.14");
boolean b = Boolean.parseBoolean("true");

// char ↔ int
char c = 'A';
int ascii = (int) c;             // 65
char back = (char) 65;           // 'A'

// String ↔ char array
char[] arr = "hello".toCharArray();
String s = new String(arr);
```

## 8. Format & Check

```java
// format
String.format("Hello %s, you are %d years old", "Alice", 25);
// "Hello Alice, you are 25 years old"

String.format("%.2f", 3.14159);  // "3.14"
String.format("%05d", 42);       // "00042"
String.format("%10s", "hi");     // "        hi" (right-aligned)
String.format("%-10s", "hi");    // "hi        " (left-aligned)

// isEmpty / isBlank
"".isEmpty();                    // true
"  ".isEmpty();                  // false
"  ".isBlank();                  // true (Java 11+, includes whitespace)

// chars stream (Java 8+)
"hello".chars()                  // IntStream of char values
    .filter(c -> c == 'l')
    .count();                    // 2
```

---

# StringBuilder Method Reference

```java
StringBuilder sb = new StringBuilder();
StringBuilder sb2 = new StringBuilder("initial");
StringBuilder sb3 = new StringBuilder(100); // initial capacity

// Append (MOST USED in interviews)
sb.append("hello");              // append String
sb.append(' ');                  // append char
sb.append(42);                   // append int
sb.append(3.14);                 // append double
sb.append(true);                 // append boolean
sb.append(new char[]{'a','b'});  // append char array

// Insert
sb.insert(0, "Start: ");         // insert at index 0
sb.insert(5, 'X');               // insert char at index 5

// Delete
sb.delete(2, 5);                 // delete range [2, 5)
sb.deleteCharAt(3);              // delete single char

// Replace
sb.replace(0, 5, "New");         // replace range with new string

// Reverse
sb.reverse();                    // reverse the whole buffer

// Index and Search
sb.indexOf("hello");             // first occurrence
sb.lastIndexOf("hello");         // last occurrence
sb.charAt(2);                    // character at index
sb.length();                     // current length
sb.capacity();                   // buffer capacity

// Modify
sb.setCharAt(0, 'X');            // change character at index
sb.setLength(5);                 // truncate or pad with nulls

// Convert
sb.toString();                   // convert to String
sb.substring(2);                 // substring from index
sb.substring(1, 4);              // substring [1, 4)

// Chain calls (StringBuilder returns itself)
String result = new StringBuilder()
    .append("Hello")
    .append(" ")
    .append("World")
    .reverse()
    .toString();                 // "dlroW olleH"
```

---

# Character Utility Methods

```java
// All from java.lang.Character class

char c = 'A';

// Type checking
Character.isLetter(c);           // true
Character.isDigit('5');          // true
Character.isLetterOrDigit('3');  // true
Character.isWhitespace(' ');     // true (includes \t, \n)
Character.isSpaceChar(' ');      // true (Unicode spaces)
Character.isUpperCase('A');      // true
Character.isLowerCase('a');      // true
Character.isAlphabetic('A');     // true (includes Unicode letters)

// Conversion
Character.toUpperCase('a');      // 'A'
Character.toLowerCase('A');      // 'a'
Character.getNumericValue('5');  // 5
Character.getNumericValue('A');  // 10 (hex)

// Arithmetic trick for index calculation
'a' - 'a' = 0                   // index for 'a' in freq array
'z' - 'a' = 25                  // index for 'z'
'A' - 'A' = 0                   // index for 'A'

// Common pattern in problems
int idx = c - 'a';               // maps 'a'→0, 'b'→1, ..., 'z'→25
char back = (char)('a' + idx);   // maps 0→'a', 1→'b', ...

// ASCII values to remember
'0' = 48, '9' = 57
'A' = 65, 'Z' = 90
'a' = 97, 'z' = 122
' ' = 32
```

---

# String Patterns & Techniques

## Pattern 1: Frequency Array (26 lowercase letters)

```java
// Most efficient for lowercase letter problems
int[] freq = new int[26];
for (char c : s.toCharArray()) {
    freq[c - 'a']++;
}

// Check frequency of a character
int countOfA = freq['a' - 'a'];  // freq[0]

// Example: Check if all frequencies are same
boolean allSame = true;
int target = freq[0];
for (int count : freq) {
    if (count != 0 && count != target) {
        allSame = false;
        break;
    }
}
```

## Pattern 2: HashMap for Frequency

```java
// For general characters (digits, special chars, Unicode)
Map<Character, Integer> freq = new HashMap<>();
for (char c : s.toCharArray()) {
    freq.put(c, freq.getOrDefault(c, 0) + 1);
}

// Or using merge
for (char c : s.toCharArray()) {
    freq.merge(c, 1, Integer::sum);
}

// Check character
if (freq.containsKey('a') && freq.get('a') > 1) { }
```

## Pattern 3: Two Pointer for Palindrome

```java
boolean isPalindrome(String s, int left, int right) {
    while (left < right) {
        if (s.charAt(left) != s.charAt(right)) return false;
        left++;
        right--;
    }
    return true;
}
```

## Pattern 4: StringBuilder for Building Answer

```java
// Instead of string concatenation in loop
// ❌ Slow: O(n²) due to String immutability
String result = "";
for (char c : s.toCharArray()) {
    result += c;
}

// ✅ Fast: O(n) with StringBuilder
StringBuilder sb = new StringBuilder();
for (char c : s.toCharArray()) {
    sb.append(c);
}
String result = sb.toString();
```

---

# Two Pointer Technique

## Template

```java
int left = 0, right = s.length() - 1;

while (left < right) {
    // Process s.charAt(left) and s.charAt(right)
    
    if (someCondition) {
        left++;
    } else {
        right--;
    }
}
```

## Sliding Window Template

```java
// Variable size window
Map<Character, Integer> window = new HashMap<>();
int left = 0, maxLen = 0;

for (int right = 0; right < s.length(); right++) {
    // Expand: add s[right] to window
    char c = s.charAt(right);
    window.put(c, window.getOrDefault(c, 0) + 1);
    
    // Shrink: while constraint violated
    while (windowInvalid(window)) {
        char leftChar = s.charAt(left);
        window.put(leftChar, window.get(leftChar) - 1);
        if (window.get(leftChar) == 0) window.remove(leftChar);
        left++;
    }
    
    // Update result
    maxLen = Math.max(maxLen, right - left + 1);
}
```

---

# LeetCode Problems - Easy

## 1. Reverse String (LeetCode 344)

```java
/*
 * Problem: 344. Reverse String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Write a function that reverses a string.
 * The input string is given as an array of characters s.
 * Modify the input array in-place with O(1) extra memory.
 *
 * ------------------------------------------------------------
 * APPROACH: Two Pointer
 *
 * Key Insight:
 * - Swap characters from both ends, move toward center
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Input is char[] (not String)
 * - Direct index access s[i] works for char[]
 * - Use temp variable for swap
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(1)
 */

class Solution {
    public void reverseString(char[] s) {
        int left = 0;
        int right = s.length - 1;

        while (left < right) {
            // Swap characters
            char temp = s[left];
            s[left]   = s[right];
            s[right]  = temp;

            left++;
            right--;
        }
    }
}

/*
 * DRY RUN:
 * s = ['h','e','l','l','o']
 *
 * Step 1: left=0, right=4 → swap 'h' and 'o' → ['o','e','l','l','h']
 * Step 2: left=1, right=3 → swap 'e' and 'l' → ['o','l','l','e','h']
 * Step 3: left=2, right=2 → left >= right → STOP
 *
 * Result: ['o','l','l','e','h']
 */
```

## 2. Valid Anagram (LeetCode 242)

```java
/*
 * Problem: 242. Valid Anagram
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings s and t, return true if t is an anagram of s.
 *
 * Anagram: word formed by rearranging letters of another word.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Sort Both Strings
 *
 * - Sort both strings, compare equality
 * - Time: O(n log n) | Space: O(n) for char array
 *
 * APPROACH 2: Frequency Count (Optimal) ✅
 *
 * - Count char frequencies in s (increment)
 * - Verify against t (decrement)
 * - If any count != 0, not anagram
 * - Time: O(n) | Space: O(1) fixed 26-size array
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - s.toCharArray() → iterate efficiently
 * - c - 'a' maps character to array index
 * - Arrays.sort() works on char arrays
 * - Arrays.equals() compares sorted arrays
 */

class Solution {

    // APPROACH 1: Sorting
    public boolean isAnagram_Sort(String s, String t) {
        if (s.length() != t.length()) return false;

        char[] sArr = s.toCharArray();
        char[] tArr = t.toCharArray();

        Arrays.sort(sArr);
        Arrays.sort(tArr);

        return Arrays.equals(sArr, tArr);
    }

    // APPROACH 2: Frequency Count (Recommended) ✅
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;

        int[] freq = new int[26];

        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        for (char c : t.toCharArray()) {
            freq[c - 'a']--;
            // Early exit: negative count means extra character
            if (freq[c - 'a'] < 0) return false;
        }

        return true;
    }
}
```

## 3. Valid Palindrome (LeetCode 125)

```java
/*
 * Problem: 125. Valid Palindrome
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * After converting all uppercase to lowercase and removing
 * all non-alphanumeric characters, does it read the same
 * forward and backward?
 *
 * ------------------------------------------------------------
 * APPROACH: Two Pointer
 *
 * Steps:
 * 1. Use two pointers from both ends
 * 2. Skip non-alphanumeric characters
 * 3. Compare characters case-insensitively
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Character.isLetterOrDigit(c) → skip non-alnum
 * - Character.toLowerCase(c) → case-insensitive compare
 * - s.charAt(i) → access character at index
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(1) - no extra data structure
 */

class Solution {
    public boolean isPalindrome(String s) {
        int left  = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Skip non-alphanumeric from left
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }

            // Skip non-alphanumeric from right
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }

            // Compare case-insensitively
            if (Character.toLowerCase(s.charAt(left)) !=
                Character.toLowerCase(s.charAt(right))) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
}

/*
 * DRY RUN:
 * s = "A man, a plan, a canal: Panama"
 *
 * After cleaning: "amanaplanacanalpanama"
 * Two pointers compare from both ends → all match → true
 */
```

## 4. First Unique Character in a String (LeetCode 387)

```java
/*
 * Problem: 387. First Unique Character in a String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, find the first non-repeating character
 * and return its index. If none exists, return -1.
 *
 * ------------------------------------------------------------
 * APPROACH: Two-Pass Frequency Count
 *
 * Pass 1: Count frequency of each character
 * Pass 2: Return index of first char with frequency = 1
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - int[] freq = new int[26] → for lowercase letters
 * - s.toCharArray() for clean iteration
 * - c - 'a' for array indexing
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n) - two passes
 * Space: O(1) - fixed size 26-element array
 */

class Solution {
    public int firstUniqChar(String s) {
        // Pass 1: Count frequencies
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        // Pass 2: Find first with frequency 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s.charAt(i) - 'a'] == 1) {
                return i;
            }
        }

        return -1;
    }
}
```

## 5. Longest Common Prefix (LeetCode 14)

```java
/*
 * Problem: 14. Longest Common Prefix
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Write a function to find the longest common prefix string
 * amongst an array of strings. Return "" if none exists.
 *
 * ------------------------------------------------------------
 * APPROACH 1: Vertical Scanning ✅
 *
 * - Take first string as reference
 * - Compare character by character across all strings
 * - Stop when mismatch or string ends
 *
 * APPROACH 2: Sort + Compare First/Last
 *
 * - After sorting, only need to compare first and last string
 * - Their LCP is the answer
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - strs[0].charAt(i) for character access
 * - s.length() for each string length check
 * - substring(0, i) to return prefix
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Vertical: Time O(S) where S = total chars | Space O(1)
 * Sort:     Time O(n log n) | Space O(1)
 */

class Solution {

    // APPROACH 1: Vertical Scanning ✅
    public String longestCommonPrefix(String[] strs) {
        if (strs == null || strs.length == 0) return "";

        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0].charAt(i);

            for (int j = 1; j < strs.length; j++) {
                // Mismatch or out of bounds
                if (i >= strs[j].length() || strs[j].charAt(i) != c) {
                    return strs[0].substring(0, i);
                }
            }
        }

        return strs[0];
    }

    // APPROACH 2: Sort + Compare
    public String longestCommonPrefix_Sort(String[] strs) {
        if (strs == null || strs.length == 0) return "";

        Arrays.sort(strs);

        String first = strs[0];
        String last  = strs[strs.length - 1];

        int i = 0;
        while (i < first.length() && i < last.length()
               && first.charAt(i) == last.charAt(i)) {
            i++;
        }

        return first.substring(0, i);
    }
}
```

## 6. Valid Parentheses (LeetCode 20)

```java
/*
 * Problem: 20. Valid Parentheses
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s containing '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 *
 * Rules:
 * 1. Open brackets closed by same type
 * 2. Open brackets closed in correct order
 * 3. Every close bracket has a matching open bracket
 *
 * ------------------------------------------------------------
 * APPROACH: Stack
 *
 * - Push opening brackets
 * - For closing brackets: check if stack top matches
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Use Deque<Character> as stack (preferred over Stack class)
 * - ArrayDeque is most efficient implementation
 * - stack.push() / stack.pop() / stack.peek() / stack.isEmpty()
 *
 * ------------------------------------------------------------
 * WHY Deque over Stack in Java?
 * - Stack extends Vector (synchronized, slow)
 * - ArrayDeque is faster and preferred
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(n) - stack
 */

class Solution {
    public boolean isValid(String s) {
        // Use ArrayDeque as stack (preferred in Java)
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '{' || c == '[') {
                // Opening bracket: push
                stack.push(c);
            } else {
                // Closing bracket: check match
                if (stack.isEmpty()) return false;

                char top = stack.pop();

                if (c == ')' && top != '(') return false;
                if (c == '}' && top != '{') return false;
                if (c == ']' && top != '[') return false;
            }
        }

        // Stack should be empty if all matched
        return stack.isEmpty();
    }
}
```

## 7. Roman to Integer (LeetCode 13)

```java
/*
 * Problem: 13. Roman to Integer
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Convert a roman numeral string to an integer.
 *
 * Symbols: I=1, V=5, X=10, L=50, C=100, D=500, M=1000
 *
 * Subtraction rules:
 * - I before V or X → subtract 1
 * - X before L or C → subtract 10
 * - C before D or M → subtract 100
 *
 * ------------------------------------------------------------
 * APPROACH: HashMap + Greedy
 *
 * Key Insight:
 * - If current value < next value → subtract
 * - Otherwise → add
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Use HashMap<Character, Integer> for symbol values
 * - getOrDefault() for safe map access
 * - Iterate using index-based loop for lookahead
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(1) - fixed map size
 */

class Solution {
    public int romanToInt(String s) {
        Map<Character, Integer> roman = new HashMap<>();
        roman.put('I', 1);
        roman.put('V', 5);
        roman.put('X', 10);
        roman.put('L', 50);
        roman.put('C', 100);
        roman.put('D', 500);
        roman.put('M', 1000);

        int result = 0;

        for (int i = 0; i < s.length(); i++) {
            int curr = roman.get(s.charAt(i));

            // Look ahead: if next value is greater, subtract
            if (i + 1 < s.length() && curr < roman.get(s.charAt(i + 1))) {
                result -= curr;
            } else {
                result += curr;
            }
        }

        return result;
    }
}
```

## 8. Reverse Words in a String III (LeetCode 557)

```java
/*
 * Problem: 557. Reverse Words in a String III
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, reverse the order of characters in each
 * word within a sentence while preserving whitespace and
 * initial word order.
 *
 * Example:
 * Input:  "Let's take LeetCode contest"
 * Output: "s'teL ekat edoCteeL tsetno c"
 *
 * ------------------------------------------------------------
 * APPROACH 1: Split + Reverse + Join
 *
 * Time: O(n) | Space: O(n)
 *
 * APPROACH 2: Two Pointer on char array ✅
 *
 * - Convert to char array
 * - Find each word boundary
 * - Reverse word in-place
 *
 * Time: O(n) | Space: O(n) for char array
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - String.split(" ") splits by space
 * - new StringBuilder(word).reverse().toString()
 * - String.join(" ", words) to rejoin
 */

class Solution {

    // APPROACH 1: Split + Reverse + Join
    public String reverseWords_v1(String s) {
        String[] words = s.split(" ");

        for (int i = 0; i < words.length; i++) {
            words[i] = new StringBuilder(words[i]).reverse().toString();
        }

        return String.join(" ", words);
    }

    // APPROACH 2: Two Pointer (no split overhead)
    public String reverseWords(String s) {
        char[] arr = s.toCharArray();
        int start = 0;

        for (int i = 0; i <= arr.length; i++) {
            // At end of word (space or end of string)
            if (i == arr.length || arr[i] == ' ') {
                reverseRange(arr, start, i - 1);
                start = i + 1;
            }
        }

        return new String(arr);
    }

    private void reverseRange(char[] arr, int left, int right) {
        while (left < right) {
            char temp = arr[left];
            arr[left]  = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}
```

---

# LeetCode Problems - Medium

## 9. Longest Substring Without Repeating Characters (LeetCode 3)

```java
/*
 * Problem: 3. Longest Substring Without Repeating Characters
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, find the length of the longest substring
 * without repeating characters.
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1️⃣ Sliding Window + HashSet     → O(n) Time, O(n) Space
 * 2️⃣ Sliding Window + HashMap     → O(n) Time, O(n) Space
 * 3️⃣ Sliding Window + Array ✅     → O(n) Time, O(1) Space
 *    (optimal for lowercase letters)
 *
 * ------------------------------------------------------------
 * KEY INSIGHT:
 *
 * Window = substring with no repeating characters
 * Expand right → if duplicate found, shrink from left
 * Use HashMap to store last seen index of each char
 * Jump left pointer directly (no need to shrink one by one)
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - HashMap<Character, Integer> to store last index
 * - Math.max() for result update
 * - s.charAt(right) for character access
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n) - each character visited once
 * Space: O(min(n, 128)) - bounded by charset size
 */

class Solution {

    // APPROACH 1: HashSet (intuitive)
    public int lengthOfLongestSubstring_Set(String s) {
        Set<Character> window = new HashSet<>();
        int left = 0, maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            // Shrink until no duplicate
            while (window.contains(s.charAt(right))) {
                window.remove(s.charAt(left));
                left++;
            }

            window.add(s.charAt(right));
            maxLen = Math.max(maxLen, right - left + 1);
        }

        return maxLen;
    }

    // APPROACH 2: HashMap (optimized jump) ✅
    public int lengthOfLongestSubstring(String s) {
        Map<Character, Integer> lastIndex = new HashMap<>();
        int left = 0, maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);

            // If seen and within current window, jump left pointer
            if (lastIndex.containsKey(c) && lastIndex.get(c) >= left) {
                left = lastIndex.get(c) + 1;
            }

            lastIndex.put(c, right);
            maxLen = Math.max(maxLen, right - left + 1);
        }

        return maxLen;
    }
}

/*
 * DRY RUN (Approach 2):
 * s = "abcabcbb"
 *
 * right=0: c='a', lastIndex={a:0}, len=1, max=1
 * right=1: c='b', lastIndex={a:0,b:1}, len=2, max=2
 * right=2: c='c', lastIndex={...,c:2}, len=3, max=3
 * right=3: c='a', a seen at 0 ≥ left(0) → left=1, lastIndex={a:3,...}
 * right=4: c='b', b seen at 1 ≥ left(1) → left=2, lastIndex={b:4,...}
 * ... max stays 3
 */
```

## 10. Longest Palindromic Substring (LeetCode 5)

```java
/*
 * Problem: 5. Longest Palindromic Substring
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, return the longest palindromic substring.
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1️⃣ Brute Force: Check all substrings → O(n³)
 * 2️⃣ Dynamic Programming                → O(n²) Time, O(n²) Space
 * 3️⃣ Expand Around Center ✅             → O(n²) Time, O(1) Space
 * 4️⃣ Manacher's Algorithm               → O(n) Time, O(n) Space
 *
 * ------------------------------------------------------------
 * EXPAND AROUND CENTER APPROACH:
 *
 * Every palindrome has a center.
 * Two types:
 * - Odd length:  center is single char (e.g., "aba" → center 'b')
 * - Even length: center is between chars (e.g., "abba" → center "bb")
 *
 * For each position i, expand both ways while characters match.
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Use helper method for expand logic
 * - s.substring(start, start + maxLen) to extract result
 * - Track start index and maxLen globally
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n²) - n centers × O(n) expansion each
 * Space: O(1)
 */

class Solution {

    private int start = 0, maxLen = 1;

    // APPROACH: Expand Around Center ✅
    public String longestPalindrome(String s) {
        if (s.length() < 2) return s;

        for (int i = 0; i < s.length() - 1; i++) {
            // Odd length palindromes (center at i)
            expand(s, i, i);

            // Even length palindromes (center between i and i+1)
            expand(s, i, i + 1);
        }

        return s.substring(start, start + maxLen);
    }

    private void expand(String s, int left, int right) {
        while (left >= 0 && right < s.length()
               && s.charAt(left) == s.charAt(right)) {
            int len = right - left + 1;
            if (len > maxLen) {
                maxLen = len;
                start  = left;
            }
            left--;
            right++;
        }
    }
}

/*
 * DRY RUN:
 * s = "babad"
 *
 * i=0: expand(0,0)→"b"(1), expand(0,1)→s[0]≠s[1] stop
 * i=1: expand(1,1)→"aba"(3) ✅ maxLen=3, start=0
 *      expand(1,2)→s[1]≠s[2] stop
 * i=2: expand(2,2)→"bab"(3) same length
 *      expand(2,3)→s[2]≠s[3] stop
 * ...
 * Result: s.substring(0, 0+3) = "bab" (or "aba" depending on order)
 */
```

## 11. Group Anagrams (LeetCode 49)

```java
/*
 * Problem: 49. Group Anagrams
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array of strings strs, group the anagrams together.
 * You may return the answer in any order.
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1️⃣ Sort each string as key         → O(n × k log k)
 * 2️⃣ Character count as key ✅        → O(n × k)
 *
 * ------------------------------------------------------------
 * KEY INSIGHT:
 *
 * Anagrams have same characters with same frequencies.
 * Group by canonical key:
 * - Key = sorted string (e.g., "eat","tea","ate" → "aet")
 * - Key = count string (e.g., "#1#1#0...#1...#1" for a,e,t)
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Arrays.sort(charArr) for sorting
 * - new String(charArr) to convert back
 * - Map.computeIfAbsent() for cleaner grouping
 * - map.values() → Collection<List<String>> for result
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Sort approach:  Time O(n × k log k) | Space O(n × k)
 * Count approach: Time O(n × k)       | Space O(n × k)
 */

class Solution {

    // APPROACH 1: Sort as Key ✅
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();

        for (String s : strs) {
            char[] arr = s.toCharArray();
            Arrays.sort(arr);
            String key = new String(arr);

            // computeIfAbsent: create list if key doesn't exist
            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    // APPROACH 2: Count as Key (faster for long strings)
    public List<List<String>> groupAnagrams_Count(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();

        for (String s : strs) {
            String key = getCountKey(s);
            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    private String getCountKey(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) count[c - 'a']++;

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                sb.append((char)('a' + i));
                sb.append(count[i]);
            }
        }
        return sb.toString();
    }
}
```

## 12. Longest Repeating Character Replacement (LeetCode 424)

```java
/*
 * Problem: 424. Longest Repeating Character Replacement
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s and integer k, you can replace any character
 * at most k times. Return the length of the longest substring
 * containing the same letter after operations.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window
 *
 * Key Insight:
 * A window is valid if:
 *   (windowSize - maxFreq) <= k
 *
 * Where maxFreq = frequency of most common char in window.
 * We only need to replace (windowSize - maxFreq) characters.
 *
 * ------------------------------------------------------------
 * IMPORTANT NOTE:
 *
 * maxFreq might not decrease when window shrinks.
 * This is intentional - we want to grow (or maintain) window size.
 * maxFreq can only truly increase → only valid windows grow.
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - int[] freq = new int[26] for character frequencies
 * - c - 'A' for uppercase to index mapping
 * - Math.max() to update maxFreq
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(1) - fixed 26-size array
 */

class Solution {
    public int characterReplacement(String s, int k) {
        int[] freq   = new int[26];
        int left     = 0;
        int maxFreq  = 0;
        int maxLen   = 0;

        for (int right = 0; right < s.length(); right++) {
            int charIdx = s.charAt(right) - 'A';
            freq[charIdx]++;
            maxFreq = Math.max(maxFreq, freq[charIdx]);

            int windowSize   = right - left + 1;
            int replacements = windowSize - maxFreq;

            // If invalid window, shrink from left
            if (replacements > k) {
                freq[s.charAt(left) - 'A']--;
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }

        return maxLen;
    }
}
```

## 13. Minimum Window Substring (LeetCode 76)

```java
/*
 * Problem: 76. Minimum Window Substring
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given strings s and t, return the minimum window substring
 * of s containing every character of t (including duplicates).
 * Return "" if no such window exists.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window with Two HashMaps
 *
 * Track:
 * - required: character counts needed from t
 * - window:   character counts in current window
 * - formed:   how many unique chars from t are satisfied
 *
 * ------------------------------------------------------------
 * ALGORITHM:
 *
 * 1. Build required map from t
 * 2. Expand right pointer, update window
 * 3. When window satisfies all requirements:
 *    - Record current window if smaller
 *    - Shrink from left to minimize
 * 4. Return minimum window found
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Map.getOrDefault() for safe access
 * - Two separate HashMap objects
 * - Track formed count separately
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(|s| + |t|)
 * Space: O(|s| + |t|)
 */

class Solution {
    public String minWindow(String s, String t) {
        if (s.isEmpty() || t.isEmpty()) return "";

        // Count required characters from t
        Map<Character, Integer> required = new HashMap<>();
        for (char c : t.toCharArray()) {
            required.put(c, required.getOrDefault(c, 0) + 1);
        }

        Map<Character, Integer> window = new HashMap<>();
        int required_count = required.size(); // unique chars in t
        int formed = 0;

        int left  = 0;
        int minLen = Integer.MAX_VALUE;
        int minLeft = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            window.put(c, window.getOrDefault(c, 0) + 1);

            // Check if this character satisfies requirement
            if (required.containsKey(c) &&
                window.get(c).intValue() == required.get(c).intValue()) {
                formed++;
            }

            // Shrink window while all requirements satisfied
            while (formed == required_count && left <= right) {
                // Update minimum window
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }

                // Remove leftmost character
                char leftChar = s.charAt(left);
                window.put(leftChar, window.get(leftChar) - 1);

                if (required.containsKey(leftChar) &&
                    window.get(leftChar) < required.get(leftChar)) {
                    formed--;
                }

                left++;
            }
        }

        return (minLen == Integer.MAX_VALUE) ? "" : s.substring(minLeft, minLeft + minLen);
    }
}
```

## 14. String to Integer (atoi) (LeetCode 8)

```java
/*
 * Problem: 8. String to Integer (atoi)
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Implement the myAtoi function which converts a string to integer.
 *
 * Rules:
 * 1. Ignore leading whitespace
 * 2. Check optional '+' or '-'
 * 3. Read digits until non-digit or end
 * 4. Clamp to [Integer.MIN_VALUE, Integer.MAX_VALUE]
 *
 * ------------------------------------------------------------
 * APPROACH: Sequential State Machine
 *
 * States: WHITESPACE → SIGN → DIGITS → DONE
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Integer.MAX_VALUE = 2147483647
 * - Integer.MIN_VALUE = -2147483648
 * - Use long to detect overflow before clamping
 * - Character.isDigit(c) to check digit
 * - s.charAt(i) - '0' to get digit value
 *
 * ------------------------------------------------------------
 * OVERFLOW CHECK:
 *
 * If result > Integer.MAX_VALUE / 10 → overflow on multiply
 * If result == Integer.MAX_VALUE / 10 && digit > 7 → overflow
 * (MAX ends in ...7, so digit > 7 causes overflow)
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(1)
 */

class Solution {
    public int myAtoi(String s) {
        int i = 0;
        int n = s.length();
        int sign = 1;
        long result = 0;

        // Step 1: Skip leading whitespace
        while (i < n && s.charAt(i) == ' ') {
            i++;
        }

        // Step 2: Check sign
        if (i < n && (s.charAt(i) == '+' || s.charAt(i) == '-')) {
            sign = (s.charAt(i) == '-') ? -1 : 1;
            i++;
        }

        // Step 3: Parse digits
        while (i < n && Character.isDigit(s.charAt(i))) {
            int digit = s.charAt(i) - '0';

            // Overflow check
            if (result > (Integer.MAX_VALUE - digit) / 10) {
                return (sign == 1) ? Integer.MAX_VALUE : Integer.MIN_VALUE;
            }

            result = result * 10 + digit;
            i++;
        }

        return (int)(sign * result);
    }
}
```

## 15. Decode String (LeetCode 394)

```java
/*
 * Problem: 394. Decode String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Decode the string encoded with rule: k[encoded_string]
 *
 * Examples:
 * "3[a]2[bc]"   → "aaabcbc"
 * "3[a2[c]]"    → "accaccacc"
 * "2[abc]3[cd]" → "abcabccdcdcd"
 *
 * ------------------------------------------------------------
 * APPROACH: Stack-Based
 *
 * Use TWO stacks:
 * - countStack: stores repeat counts
 * - strStack:   stores previous strings
 *
 * When we see '[':
 *   Push current count and current string to stacks
 *   Reset both
 *
 * When we see ']':
 *   Pop count and previous string
 *   Repeat current string, append to previous
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Deque<Integer> for count stack
 * - Deque<StringBuilder> for string stack
 * - sb.append() for building strings
 * - String.repeat(k) or loop for repetition (Java 11+)
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(maxK × n) where maxK = max repeat factor
 * Space: O(n)
 */

class Solution {
    public String decodeString(String s) {
        Deque<Integer>       countStack = new ArrayDeque<>();
        Deque<StringBuilder> strStack   = new ArrayDeque<>();

        StringBuilder current = new StringBuilder();
        int k = 0;

        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                // Build multi-digit number
                k = k * 10 + (c - '0');

            } else if (c == '[') {
                // Save state and reset
                countStack.push(k);
                strStack.push(current);
                current = new StringBuilder();
                k = 0;

            } else if (c == ']') {
                // Restore state
                int repeat   = countStack.pop();
                StringBuilder prev = strStack.pop();

                // Repeat current string
                String repeated = current.toString().repeat(repeat);
                current = prev.append(repeated);

            } else {
                // Regular character
                current.append(c);
            }
        }

        return current.toString();
    }
}
```

## 16. Palindromic Substrings (LeetCode 647)

```java
/*
 * Problem: 647. Palindromic Substrings
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s, return the number of palindromic substrings.
 *
 * ------------------------------------------------------------
 * APPROACH: Expand Around Center
 *
 * For each position, expand outward and count palindromes.
 * 2n-1 possible centers (n single chars + n-1 between chars).
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Use a count variable (not field) to avoid instance issues
 * - Both odd and even expansion from same loop iteration
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n²)
 * Space: O(1)
 */

class Solution {
    public int countSubstrings(String s) {
        int count = 0;

        for (int center = 0; center < s.length(); center++) {
            // Odd length palindromes
            count += expand(s, center, center);

            // Even length palindromes
            count += expand(s, center, center + 1);
        }

        return count;
    }

    private int expand(String s, int left, int right) {
        int count = 0;

        while (left >= 0 && right < s.length()
               && s.charAt(left) == s.charAt(right)) {
            count++;
            left--;
            right++;
        }

        return count;
    }
}
```

## 17. Find All Anagrams in a String (LeetCode 438)

```java
/*
 * Problem: 438. Find All Anagrams in a String
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given strings s and p, return an array of all the start
 * indices of p's anagrams in s. Return indices in any order.
 *
 * ------------------------------------------------------------
 * APPROACH: Sliding Window with Fixed Size
 *
 * Window size = p.length()
 * Slide window, compare freq arrays at each position.
 *
 * Optimization:
 * - Use single diff counter instead of comparing arrays
 * - diff = number of characters with different frequencies
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - int[] of size 26 for char frequencies
 * - Arrays.equals(arr1, arr2) to compare freq arrays
 * - ArrayList<Integer> for result
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n) - each character visited once
 * Space: O(1) - fixed 26-size arrays
 */

class Solution {
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> result = new ArrayList<>();

        if (s.length() < p.length()) return result;

        int[] pFreq = new int[26];
        int[] wFreq = new int[26];

        // Initialize frequency arrays for first window
        for (int i = 0; i < p.length(); i++) {
            pFreq[p.charAt(i) - 'a']++;
            wFreq[s.charAt(i) - 'a']++;
        }

        if (Arrays.equals(pFreq, wFreq)) result.add(0);

        // Slide window
        for (int i = p.length(); i < s.length(); i++) {
            // Add new character (right end of window)
            wFreq[s.charAt(i) - 'a']++;

            // Remove old character (left end of window)
            wFreq[s.charAt(i - p.length()) - 'a']--;

            if (Arrays.equals(pFreq, wFreq)) {
                result.add(i - p.length() + 1);
            }
        }

        return result;
    }
}
```

---

# LeetCode Problems - Hard

## 18. Longest Valid Parentheses (LeetCode 32)

```java
/*
 * Problem: 32. Longest Valid Parentheses
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string containing just '(' and ')',
 * return the length of the longest valid parentheses substring.
 *
 * ------------------------------------------------------------
 * APPROACHES:
 *
 * 1️⃣ Dynamic Programming  → O(n) Time, O(n) Space
 * 2️⃣ Stack               → O(n) Time, O(n) Space
 * 3️⃣ Two Counters ✅      → O(n) Time, O(1) Space
 *
 * ------------------------------------------------------------
 * DP RECURRENCE:
 *
 * dp[i] = longest valid parentheses ending at index i
 *
 * If s[i] == ')':
 *   Case 1: s[i-1] == '('  → dp[i] = dp[i-2] + 2
 *   Case 2: s[i-1] == ')' and s[i-dp[i-1]-1] == '('
 *             → dp[i] = dp[i-1] + 2 + dp[i-dp[i-1]-2]
 *
 * ------------------------------------------------------------
 * STACK APPROACH:
 *
 * Push indices.
 * Start with -1 as base.
 * '(' → push index
 * ')' → pop; if empty, push current as base; else len = i - top
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - Deque<Integer> as stack of indices
 * - int[] dp for DP approach
 * - Math.max() for tracking maximum
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n)
 * Space: O(n) for DP/Stack, O(1) for Two-Counter
 */

class Solution {

    // APPROACH 1: Dynamic Programming
    public int longestValidParentheses_DP(String s) {
        int n = s.length();
        if (n < 2) return 0;

        int[] dp  = new int[n];
        int maxLen = 0;

        for (int i = 1; i < n; i++) {
            if (s.charAt(i) == ')') {
                if (s.charAt(i - 1) == '(') {
                    // Case 1: "...( )"
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else {
                    // Case 2: "... ) )"
                    int j = i - dp[i - 1] - 1;
                    if (j >= 0 && s.charAt(j) == '(') {
                        dp[i] = dp[i - 1] + 2;
                        if (j - 1 >= 0) dp[i] += dp[j - 1];
                    }
                }
                maxLen = Math.max(maxLen, dp[i]);
            }
        }

        return maxLen;
    }

    // APPROACH 2: Stack
    public int longestValidParentheses_Stack(String s) {
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(-1); // Base index

        int maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                stack.push(i);
            } else {
                stack.pop();

                if (stack.isEmpty()) {
                    stack.push(i); // New base
                } else {
                    maxLen = Math.max(maxLen, i - stack.peek());
                }
            }
        }

        return maxLen;
    }

    // APPROACH 3: Two Counters (O(1) space) ✅
    public int longestValidParentheses(String s) {
        int left = 0, right = 0, maxLen = 0;

        // Left to right
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') left++;
            else right++;

            if (left == right)  maxLen = Math.max(maxLen, 2 * right);
            else if (right > left) left = right = 0;
        }

        left = right = 0;

        // Right to left
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == '(') left++;
            else right++;

            if (left == right)  maxLen = Math.max(maxLen, 2 * left);
            else if (left > right) left = right = 0;
        }

        return maxLen;
    }
}
```

## 19. Edit Distance (LeetCode 72)

```java
/*
 * Problem: 72. Edit Distance
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given two strings word1 and word2, return the minimum number
 * of operations to convert word1 to word2.
 *
 * Operations: Insert, Delete, Replace
 *
 * ------------------------------------------------------------
 * APPROACH: Dynamic Programming
 *
 * ------------------------------------------------------------
 * DP DEFINITION:
 *
 * dp[i][j] = min operations to convert word1[0..i-1]
 *            to word2[0..j-1]
 *
 * BASE CASES:
 * dp[i][0] = i  (delete all i characters)
 * dp[0][j] = j  (insert all j characters)
 *
 * RECURRENCE:
 * If word1[i-1] == word2[j-1]:
 *   dp[i][j] = dp[i-1][j-1]           (no operation needed)
 * Else:
 *   dp[i][j] = 1 + min(
 *     dp[i-1][j],       // delete from word1
 *     dp[i][j-1],       // insert into word1
 *     dp[i-1][j-1]      // replace in word1
 *   )
 *
 * ------------------------------------------------------------
 * SPACE OPTIMIZATION:
 *
 * Since dp[i][j] only depends on row i-1 and column j,
 * we can reduce to 1D array.
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - int[][] dp = new int[m+1][n+1]
 * - Math.min with 3 values using nested calls
 * - word1.charAt(i-1) for character access
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(m × n)
 * Space: O(m × n), optimizable to O(min(m,n))
 */

class Solution {

    // APPROACH 1: Standard 2D DP
    public int minDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();

        int[][] dp = new int[m + 1][n + 1];

        // Base cases
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i - 1][j - 1],  // replace
                                   Math.min(dp[i - 1][j],       // delete
                                            dp[i][j - 1]));     // insert
                }
            }
        }

        return dp[m][n];
    }

    // APPROACH 2: Space-Optimized 1D DP
    public int minDistance_Optimized(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();

        int[] dp = new int[n + 1];
        for (int j = 0; j <= n; j++) dp[j] = j;

        for (int i = 1; i <= m; i++) {
            int prev = dp[0]; // stores dp[i-1][j-1]
            dp[0] = i;

            for (int j = 1; j <= n; j++) {
                int temp = dp[j];

                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[j] = prev;
                } else {
                    dp[j] = 1 + Math.min(prev,
                                Math.min(dp[j],
                                         dp[j - 1]));
                }

                prev = temp;
            }
        }

        return dp[n];
    }
}
```

## 20. Word Break II (LeetCode 140)

```java
/*
 * Problem: 140. Word Break II
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given a string s and dictionary wordDict, add spaces in s to
 * construct a sentence where each word is valid.
 * Return all such possible sentences in any order.
 *
 * Example:
 * s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 * ------------------------------------------------------------
 * APPROACH: Backtracking + Memoization
 *
 * For each starting index, try all words that match.
 * Memoize results for each starting position.
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - HashSet<String> for O(1) word lookup
 * - Map<Integer, List<String>> for memoization
 * - s.substring(start, end) for word extraction
 * - String.join(" ", parts) for sentence construction
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(n × 2^n) worst case (all possible sentences)
 * Space: O(n × 2^n) for memoization
 */

class Solution {
    private Set<String> dict;
    private Map<Integer, List<String>> memo;

    public List<String> wordBreak(String s, List<String> wordDict) {
        dict = new HashSet<>(wordDict);
        memo = new HashMap<>();
        return dfs(s, 0);
    }

    private List<String> dfs(String s, int start) {
        // Return memoized result
        if (memo.containsKey(start)) {
            return memo.get(start);
        }

        List<String> result = new ArrayList<>();

        // Base case: reached end of string
        if (start == s.length()) {
            result.add("");
            return result;
        }

        // Try all possible words starting at 'start'
        for (int end = start + 1; end <= s.length(); end++) {
            String word = s.substring(start, end);

            if (dict.contains(word)) {
                List<String> subResult = dfs(s, end);

                for (String sub : subResult) {
                    // Combine current word with sub-results
                    result.add(word + (sub.isEmpty() ? "" : " " + sub));
                }
            }
        }

        memo.put(start, result);
        return result;
    }
}
```

## 21. Regular Expression Matching (LeetCode 10)

```java
/*
 * Problem: 10. Regular Expression Matching
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an input string s and a pattern p, implement regular
 * expression matching with support for '.' and '*'.
 *
 * '.' matches any single character.
 * '*' matches zero or more of the preceding element.
 *
 * ------------------------------------------------------------
 * APPROACH: Dynamic Programming (Bottom-Up) ✅
 *
 * dp[i][j] = true if s[0..i-1] matches p[0..j-1]
 *
 * BASE CASES:
 * dp[0][0] = true (empty matches empty)
 * dp[0][j] = dp[0][j-2] if p[j-1] == '*' (star removes preceding)
 *
 * RECURRENCE:
 * If p[j-1] == s[i-1] or p[j-1] == '.':
 *   dp[i][j] = dp[i-1][j-1]
 *
 * If p[j-1] == '*':
 *   dp[i][j] = dp[i][j-2]        (use 0 occurrences)
 *   OR (if p[j-2] matches s[i-1]):
 *   dp[i][j] = dp[i-1][j]        (use 1+ occurrences)
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - boolean[][] dp for DP table
 * - Careful with 1-indexed DP vs 0-indexed string access
 * - p.charAt(j-1) == '*' and p.charAt(j-2) for look-behind
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(m × n)
 * Space: O(m × n)
 */

class Solution {
    public boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();

        boolean[][] dp = new boolean[m + 1][n + 1];

        // Base case: empty string matches empty pattern
        dp[0][0] = true;

        // Handle patterns like a*, a*b*, a*b*c* that match empty string
        for (int j = 2; j <= n; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Fill DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sc = s.charAt(i - 1);
                char pc = p.charAt(j - 1);

                if (pc == sc || pc == '.') {
                    // Direct match or wildcard '.'
                    dp[i][j] = dp[i - 1][j - 1];

                } else if (pc == '*') {
                    // Zero occurrences of preceding
                    dp[i][j] = dp[i][j - 2];

                    // One or more occurrences of preceding
                    char prev = p.charAt(j - 2);
                    if (prev == sc || prev == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }
}
```

## 22. Text Justification (LeetCode 68)

```java
/*
 * Problem: 68. Text Justification
 *
 * ------------------------------------------------------------
 * STATEMENT:
 * Given an array of strings words and a width maxWidth,
 * format text so each line has exactly maxWidth characters
 * and is fully left and right justified.
 *
 * Rules:
 * 1. Pack as many words as possible per line
 * 2. Distribute spaces evenly between words
 * 3. Extra spaces go to left gaps first
 * 4. Last line is left-justified
 *
 * ------------------------------------------------------------
 * APPROACH: Greedy + Line Building
 *
 * Phase 1: Greedily pack words into lines
 * Phase 2: Build each line with proper justification
 *
 * ------------------------------------------------------------
 * JAVA SPECIFICS:
 * - StringBuilder for line construction
 * - String.repeat() for spaces (Java 11+)
 * - Manually append spaces in loop for older Java
 * - " ".repeat(n) or manual loop
 *
 * ------------------------------------------------------------
 * TIME & SPACE COMPLEXITY:
 *
 * Time:  O(total characters)
 * Space: O(maxWidth) per line
 */

class Solution {
    public List<String> fullJustify(String[] words, int maxWidth) {
        List<String> result = new ArrayList<>();
        int i = 0;

        while (i < words.length) {
            // Determine words for current line
            int lineLen = words[i].length();
            int j = i + 1;

            while (j < words.length &&
                   lineLen + 1 + words[j].length() <= maxWidth) {
                lineLen += 1 + words[j].length();
                j++;
            }

            // Build the line
            result.add(buildLine(words, i, j, maxWidth));
            i = j;
        }

        return result;
    }

    private String buildLine(String[] words, int start, int end, int maxWidth) {
        int numWords  = end - start;
        int wordsLen  = 0;
        for (int k = start; k < end; k++) {
            wordsLen += words[k].length();
        }

        StringBuilder sb = new StringBuilder();
        sb.append(words[start]);

        // Last line or single word: left-justify
        if (end == words.length || numWords == 1) {
            for (int k = start + 1; k < end; k++) {
                sb.append(' ');
                sb.append(words[k]);
            }
            // Pad right with spaces
            while (sb.length() < maxWidth) sb.append(' ');
            return sb.toString();
        }

        // Middle lines: full justify
        int gaps        = numWords - 1;
        int totalSpaces = maxWidth - wordsLen;
        int spacePerGap = totalSpaces / gaps;
        int extraSpaces = totalSpaces % gaps;

        for (int k = start + 1; k < end; k++) {
            int spacesHere = spacePerGap + (k - start - 1 < extraSpaces ? 1 : 0);
            sb.append(" ".repeat(spacesHere));
            sb.append(words[k]);
        }

        return sb.toString();
    }
}
```

---

# Classic String Algorithms

## 1. KMP (Knuth-Morris-Pratt)

**Purpose:** Find pattern in text in O(n + m)

```java
class KMP {

    // Build LPS (Longest Proper Prefix which is also Suffix) array
    private int[] buildLPS(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];
        int len = 0;

        for (int i = 1; i < m; ) {
            if (pattern.charAt(i) == pattern.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // Don't increment i
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    // Search for all occurrences of pattern in text
    public List<Integer> search(String text, String pattern) {
        List<Integer> result = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        int[] lps = buildLPS(pattern);
        int i = 0; // index for text
        int j = 0; // index for pattern

        while (i < n) {
            if (text.charAt(i) == pattern.charAt(j)) {
                i++;
                j++;
            }

            if (j == m) {
                result.add(i - j);  // Found at index i-j
                j = lps[j - 1];    // Get next position from LPS
            } else if (i < n && text.charAt(i) != pattern.charAt(j)) {
                if (j != 0) {
                    j = lps[j - 1]; // Use LPS to skip comparisons
                } else {
                    i++;
                }
            }
        }
        return result;
    }
}

/*
 * EXAMPLE:
 * text    = "AABAACAADAABAABA"
 * pattern = "AABA"
 *
 * LPS for "AABA": [0, 1, 0, 1]
 *
 * Result: Occurrences at indices 0, 9, 12
 *
 * TIME:  O(n + m)
 * SPACE: O(m) for LPS array
 */
```

## 2. Rabin-Karp (Rolling Hash)

**Purpose:** Pattern matching using polynomial hashing

```java
class RabinKarp {
    private static final int BASE = 31;
    private static final long MOD  = 1_000_000_007L;

    public List<Integer> search(String text, String pattern) {
        List<Integer> result = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();
        if (m > n) return result;

        // Precompute BASE^(m-1) % MOD
        long h = 1;
        for (int i = 0; i < m - 1; i++) {
            h = (h * BASE) % MOD;
        }

        // Initial hash for pattern and first window
        long pHash = 0, wHash = 0;
        for (int i = 0; i < m; i++) {
            pHash = (pHash * BASE + (pattern.charAt(i) - 'a' + 1)) % MOD;
            wHash = (wHash  * BASE + (text.charAt(i)   - 'a' + 1)) % MOD;
        }

        // Slide window
        for (int i = 0; i <= n - m; i++) {
            if (pHash == wHash) {
                // Hash match: verify character by character
                if (text.substring(i, i + m).equals(pattern)) {
                    result.add(i);
                }
            }

            // Compute next window hash (rolling hash)
            if (i < n - m) {
                wHash = (BASE * (wHash - (text.charAt(i) - 'a' + 1) * h) +
                         (text.charAt(i + m) - 'a' + 1)) % MOD;
                if (wHash < 0) wHash += MOD;
            }
        }
        return result;
    }
}

/*
 * TIME:  O(n + m) average, O(n × m) worst (hash collisions)
 * SPACE: O(1)
 *
 * Best used for: Multi-pattern search (search multiple patterns simultaneously)
 */
```

## 3. Manacher's Algorithm

**Purpose:** Find longest palindromic substring in O(n)

```java
class Manacher {

    public String longestPalindrome(String s) {
        // Transform: "abc" → "^#a#b#c#$"
        String t = buildTransformed(s);
        int n = t.length();
        int[] p = new int[n]; // p[i] = radius of palindrome at i

        int center = 0, right = 0;

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;

            if (i < right) {
                p[i] = Math.min(right - i, p[mirror]);
            }

            // Expand around center i
            while (t.charAt(i + p[i] + 1) == t.charAt(i - p[i] - 1)) {
                p[i]++;
            }

            // Update center and right boundary
            if (i + p[i] > right) {
                center = i;
                right  = i + p[i];
            }
        }

        // Find maximum palindrome
        int maxLen = 0, centerIdx = 0;
        for (int i = 1; i < n - 1; i++) {
            if (p[i] > maxLen) {
                maxLen    = p[i];
                centerIdx = i;
            }
        }

        int start = (centerIdx - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    private String buildTransformed(String s) {
        StringBuilder sb = new StringBuilder("^");
        for (char c : s.toCharArray()) {
            sb.append('#').append(c);
        }
        sb.append("#$");
        return sb.toString();
    }
}

/*
 * TIME:  O(n) - each position expanded at most once
 * SPACE: O(n) for p[] array and transformed string
 */
```

## 4. Trie (Prefix Tree)

**Purpose:** Efficient string storage and prefix search

```java
class Trie {

    private static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        boolean isEnd = false;
    }

    private final TrieNode root = new TrieNode();

    // Insert word into trie
    public void insert(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            int idx = c - 'a';
            if (node.children[idx] == null) {
                node.children[idx] = new TrieNode();
            }
            node = node.children[idx];
        }
        node.isEnd = true;
    }

    // Search for exact word
    public boolean search(String word) {
        TrieNode node = find(word);
        return node != null && node.isEnd;
    }

    // Check if any word starts with prefix
    public boolean startsWith(String prefix) {
        return find(prefix) != null;
    }

    private TrieNode find(String s) {
        TrieNode node = root;
        for (char c : s.toCharArray()) {
            int idx = c - 'a';
            if (node.children[idx] == null) return null;
            node = node.children[idx];
        }
        return node;
    }

    // Get all words with given prefix
    public List<String> getWordsWithPrefix(String prefix) {
        List<String> result = new ArrayList<>();
        TrieNode node = find(prefix);
        if (node != null) {
            dfs(node, new StringBuilder(prefix), result);
        }
        return result;
    }

    private void dfs(TrieNode node, StringBuilder path, List<String> result) {
        if (node.isEnd) result.add(path.toString());
        for (int i = 0; i < 26; i++) {
            if (node.children[i] != null) {
                path.append((char)('a' + i));
                dfs(node.children[i], path, result);
                path.deleteCharAt(path.length() - 1);
            }
        }
    }
}

/*
 * TIME:
 * - insert:     O(L) where L = word length
 * - search:     O(L)
 * - startsWith: O(L)
 *
 * SPACE: O(ALPHABET_SIZE × L × N)
 *   where N = number of words
 */
```

## 5. Z-Algorithm

**Purpose:** Find all positions where pattern appears in text

```java
class ZAlgorithm {

    // Build Z-array: z[i] = length of longest substring starting at i
    // that is also a prefix of the string
    public int[] buildZ(String s) {
        int n = s.length();
        int[] z = new int[n];
        int l = 0, r = 0;

        for (int i = 1; i < n; i++) {
            if (i < r) {
                z[i] = Math.min(r - i, z[i - l]);
            }

            while (i + z[i] < n && s.charAt(z[i]) == s.charAt(i + z[i])) {
                z[i]++;
            }

            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }

    // Find all occurrences of pattern in text
    public List<Integer> search(String text, String pattern) {
        String combined = pattern + "$" + text; // $ is separator
        int[] z = buildZ(combined);
        List<Integer> result = new ArrayList<>();

        int m = pattern.length();
        for (int i = m + 1; i < combined.length(); i++) {
            if (z[i] == m) {
                result.add(i - m - 1); // Position in original text
            }
        }
        return result;
    }
}

/*
 * TIME:  O(n + m)
 * SPACE: O(n + m) for combined string and Z array
 */
```

---

# Problem Patterns Quick Reference

## Pattern 1: Sliding Window

| Use When | Key Signal | Example Problems |
| :--- | :--- | :--- |
| Substrings with constraint | "longest/shortest substring" | LC 3, 76, 424 |
| Fixed window size | "substring of length k" | LC 438, 30 |
| Window with at most/exactly k | "at most k distinct chars" | LC 340, 159 |

```java
// Template for variable window
int left = 0, result = 0;
Map<Character, Integer> window = new HashMap<>();

for (int right = 0; right < s.length(); right++) {
    // 1. Expand: add s[right]
    window.merge(s.charAt(right), 1, Integer::sum);

    // 2. Shrink: while invalid
    while (!isValid(window)) {
        window.merge(s.charAt(left), -1, Integer::sum);
        if (window.get(s.charAt(left)) == 0)
            window.remove(s.charAt(left));
        left++;
    }

    // 3. Update result
    result = Math.max(result, right - left + 1);
}
```

## Pattern 2: Two Pointer

| Use When | Key Signal | Example Problems |
| :--- | :--- | :--- |
| Palindrome check | "is palindrome" | LC 125, 680 |
| Reverse in-place | "reverse" | LC 344, 557 |
| Meet in middle | "find pair" | LC 167 |

```java
// Template: opposite ends
int left = 0, right = s.length() - 1;
while (left < right) {
    if (s.charAt(left) != s.charAt(right)) return false;
    left++;
    right--;
}
```

## Pattern 3: String DP

| Use When | Key Signal | Example Problems |
| :--- | :--- | :--- |
| 2 strings compared | "edit distance", "match" | LC 72, 10, 44 |
| Substring counting | "count palindromes", "subsequences" | LC 647, 115 |
| Optimal splitting | "word break" | LC 139, 140 |

```java
// Template: 2D DP on two strings
int[][] dp = new int[m + 1][n + 1];
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        if (s1.charAt(i-1) == s2.charAt(j-1)) {
            dp[i][j] = dp[i-1][j-1] + 1;
        } else {
            dp[i][j] = Math.max(dp[i-1][j], dp[i][j-1]);
        }
    }
}
```

## Pattern 4: Stack for String

| Use When | Key Signal | Example Problems |
| :--- | :--- | :--- |
| Matching brackets | "valid parentheses" | LC 20, 32 |
| Nested decoding | "k[string] format" | LC 394 |
| Remove patterns | "remove adjacent duplicates" | LC 1047, 1209 |

```java
// Template: bracket matching
Deque<Character> stack = new ArrayDeque<>();
for (char c : s.toCharArray()) {
    if (isOpen(c)) {
        stack.push(c);
    } else {
        if (stack.isEmpty() || !matches(stack.peek(), c))
            return false;
        stack.pop();
    }
}
return stack.isEmpty();
```

---

# Optimization & Common Mistakes

## Java-Specific Pitfalls

### 1. String Concatenation in Loop

```java
// ❌ O(n²) - creates new String object every iteration
String result = "";
for (int i = 0; i < n; i++) {
    result += s.charAt(i);   // BAD: n new objects created
}

// ✅ O(n) - StringBuilder reuses buffer
StringBuilder sb = new StringBuilder(n); // pre-allocate capacity
for (int i = 0; i < n; i++) {
    sb.append(s.charAt(i));
}
String result = sb.toString();
```

### 2. String Comparison with ==

```java
// ❌ WRONG: compares references, not content
String a = new String("hello");
String b = new String("hello");
if (a == b) { }          // FALSE! Never do this

// ✅ CORRECT: always use .equals()
if (a.equals(b)) { }     // TRUE

// ✅ Null-safe: use Objects.equals()
if (Objects.equals(a, b)) { }
```

### 3. char to int Conversion

```java
// ❌ WRONG: char '5' is ASCII 53, not integer 5
char c = '5';
int wrong = c;            // 53 (ASCII value)

// ✅ CORRECT: subtract '0'
int correct = c - '0';    // 5

// For letter to index
char letter = 'c';
int idx = letter - 'a';  // 2 (0-indexed)
```

### 4. Substring Index Bounds

```java
// ❌ Common mistake: substring(start, end) is EXCLUSIVE on end
String s = "Hello";
s.substring(1, 3);        // "el" (indices 1 and 2, NOT 3)

// Remember: substring(start, end) = s[start..end-1]
s.substring(0, s.length()); // Full string
s.substring(0, 1);          // First character only
```

### 5. Using Stack class (legacy)

```java
// ❌ Avoid: Stack extends Vector (synchronized, slow)
Stack<Character> stack = new Stack<>();

// ✅ Prefer: ArrayDeque is faster
Deque<Character> stack = new ArrayDeque<>();
stack.push('a');
stack.pop();
stack.peek();
```

### 6. toCharArray() vs charAt()

```java
// For simple iteration, both work
// charAt() has slight overhead (bounds check) but no extra memory

// ✅ toCharArray() - cleaner iteration, O(n) space
for (char c : s.toCharArray()) { }

// ✅ charAt() - no extra memory, use for index-based access
for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
}
```

## Time Complexity Reference

| Operation | String | StringBuilder |
| :--- | :--- | :--- |
| Length | O(1) | O(1) |
| charAt(i) | O(1) | O(1) |
| append/concat | O(n) new object | O(1) amortized |
| substring | O(n) copy | O(n) via toString |
| indexOf | O(n × m) | O(n × m) |
| replace | O(n) | O(n) |
| sort (as char[]) | O(n log n) | O(n log n) |

## Complexity Quick Reference for Problems

| Problem Type | Time | Space | Notes |
| :--- | :--- | :--- | :--- |
| Palindrome check | O(n) | O(1) | Two pointer |
| Anagram check | O(n) | O(1) | Freq array |
| Sliding window max | O(n) | O(k) | Deque |
| All substrings | O(n²) | O(1) | Two loops |
| Pattern matching (naive) | O(n×m) | O(1) | Two loops |
| Pattern matching (KMP) | O(n+m) | O(m) | LPS array |
| String DP (2 strings) | O(m×n) | O(m×n) | 2D table |
| Palindrome DP | O(n²) | O(n²) or O(1) | Expand center |
| Trie build | O(n×L) | O(n×L) | L=word length |

---

# Practice Strategy

## Beginner Problems (Easy - Week 1)

**Goal:** Master Java string API and two-pointer

| # | Problem | Key Concept |
| :--- | :--- | :--- |
| 1 | 344. Reverse String | char[], two pointer |
| 2 | 242. Valid Anagram | freq array |
| 3 | 125. Valid Palindrome | two pointer + isLetterOrDigit |
| 4 | 387. First Unique Character | freq array, two-pass |
| 5 | 14. Longest Common Prefix | vertical scan |
| 6 | 20. Valid Parentheses | Deque as stack |
| 7 | 13. Roman to Integer | HashMap |
| 8 | 557. Reverse Words III | split + StringBuilder |
| 9 | 412. Fizz Buzz | StringBuilder |
| 10 | 58. Length of Last Word | trim + split |

## Intermediate Problems (Medium - Week 2-3)

**Goal:** Master sliding window and frequency maps

| # | Problem | Key Concept |
| :--- | :--- | :--- |
| 1 | 3. Longest Substring No Repeat | Sliding window + HashMap |
| 2 | 5. Longest Palindromic Substring | Expand around center |
| 3 | 49. Group Anagrams | HashMap + sort/count key |
| 4 | 8. String to Integer | State machine |
| 5 | 6. Zigzag Conversion | Simulate rows |
| 6 | 424. Char Replacement | Sliding window |
| 7 | 647. Palindromic Substrings | Expand around center |
| 8 | 394. Decode String | Stack + StringBuilder |
| 9 | 438. Find All Anagrams | Fixed sliding window |
| 10 | 76. Minimum Window Substring | Two HashMaps |
| 11 | 151. Reverse Words in String | Split + rebuild |
| 12 | 567. Permutation in String | Sliding window |
| 13 | 139. Word Break | BFS / DP |
| 14 | 93. Restore IP Addresses | Backtracking |
| 15 | 1143. LCS | 2D DP |

## Advanced Problems (Hard - Week 4+)

**Goal:** Master string DP and classic algorithms

| # | Problem | Key Concept |
| :--- | :--- | :--- |
| 1 | 32. Longest Valid Parentheses | DP / Stack / Counter |
| 2 | 72. Edit Distance | 2D DP |
| 3 | 10. Regular Expression Matching | 2D DP with * handling |
| 4 | 44. Wildcard Matching | 2D DP |
| 5 | 115. Distinct Subsequences | 2D DP |
| 6 | 140. Word Break II | Backtracking + memo |
| 7 | 30. Substring Concatenation | Sliding window + map |
| 8 | 68. Text Justification | Greedy + build |
| 9 | 212. Word Search II | Trie + DFS |
| 10 | 336. Palindrome Pairs | Trie / HashMap |

## Core Algorithms to Implement from Scratch

1. **KMP** - For any "find pattern in text" problem
2. **Rabin-Karp** - For multi-pattern search
3. **Manacher's** - For O(n) palindrome problems
4. **Trie** - For prefix-based dictionary problems
5. **Z-Algorithm** - Alternative to KMP

## Interview Preparation Checklist

**Before starting any string problem:**
- [ ] Ask: Is input ASCII or Unicode?
- [ ] Ask: Case sensitive?
- [ ] Ask: Can input be empty or null?
- [ ] Ask: Can I use extra space?
- [ ] Ask: Does order matter in output?

**In solution:**
- [ ] Use `StringBuilder` for any string building
- [ ] Use `.equals()` not `==` for string comparison
- [ ] Use `char[] arr = s.toCharArray()` for frequent modification
- [ ] Use `int[] freq = new int[26]` for lowercase letter frequency
- [ ] Use `ArrayDeque` not `Stack` for stack operations
- [ ] Use `Character.isLetterOrDigit()` for alphanumeric checks

**Optimize:**
- [ ] Can you reduce O(n²) to O(n) with sliding window?
- [ ] Can you reduce O(n²) to O(n) with KMP?
- [ ] Can you reduce O(n²) space to O(n) in DP?

---

**End of Java Strings DSA Guide**

Good luck — master these patterns and no string problem can stop you! 🚀
