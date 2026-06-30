# 🌲 Tries (Prefix Trees) — Deep Dive (C++ & LeetCode)

> A thorough, intuition-first guide to Tries — how they work internally, why they exist, and how to wield them.

---

## Table of Contents

1. [What is a Trie?](#1-what-is-a-trie)
2. [Why Not Just Use a Hash Set?](#2-why-not-just-use-a-hash-set)
3. [Anatomy of a Trie Node](#3-anatomy-of-a-trie-node)
4. [Core Operations Explained](#4-core-operations-explained)
5. [Building a Trie From Scratch in C++](#5-building-a-trie-from-scratch-in-c)
6. [Array vs HashMap Children — Tradeoffs](#6-array-vs-hashmap-children--tradeoffs)
7. [Complexity Analysis](#7-complexity-analysis)
8. [Variations of Trie](#8-variations-of-trie)
9. [Common Trie Patterns](#9-common-trie-patterns)
10. [LeetCode Problems](#10-leetcode-problems)
11. [Common Mistakes & Debugging](#11-common-mistakes--debugging)
12. [Quick Reference](#12-quick-reference)

---

## 1. What is a Trie?

A **Trie** (pronounced "try", from re**trie**val) is a tree-like data structure used to store a dynamic set of strings, where each node represents a single character and paths from the root down to marked nodes spell out words.

### The Core Insight

Instead of storing each string as an independent blob (like a hash set does), a Trie stores strings **character by character**, and — crucially — **strings that share a common prefix share the same path** in the tree.

```
Insert: "cat", "car", "card", "dog"

                root
               /    \
              c      d
              |      |
              a      o
            /   \    |
           t     r   g*
          *       \
                    d*

* = end of a complete word
```

Notice "cat" and "car" share the path `c → a`, then diverge. "car" and "card" share `c → a → r`, then "card" continues to `d`. This shared-prefix structure is the entire point of a Trie.

### Real-World Mental Model

Think of a Trie exactly like the autocomplete dropdown in a search bar:

```
You type: "ca"
   ↓
Trie walks: root → c → a
   ↓
From this node, it explores all children to suggest:
   "cat", "car", "card", "cab", ...
```

This is precisely why Tries are the backbone of autocomplete systems, spell checkers, IP routing tables, and dictionary lookups — they are built to answer **prefix-based** questions extremely efficiently.

---

## 2. Why Not Just Use a Hash Set?

This is the question every learner should ask, because on the surface a `unordered_set<string>` seems to do the same job: insert words, check if a word exists.

### Where Hash Sets Fall Short

| Question | Hash Set | Trie |
|----------|----------|------|
| Does "apple" exist? | O(L) — fast | O(L) — fast |
| Does any word **start with** "app"? | O(n · L) — must scan everything | O(L) — just walk the prefix |
| List all words with prefix "app" | O(n · L) — scan + filter | O(L + k) — walk prefix, then collect k matches |
| Memory for "cat", "car", "card" | 3 separate full strings stored | Shared path `c-a` reused, more compact for dense prefixes |

A hash set has **no concept of order or shared structure** between strings — `"cat"` and `"car"` are two completely unrelated hash buckets. A Trie, by contrast, makes prefix relationships **explicit in its structure**, so prefix queries become a simple tree walk instead of a full scan.

### The Defining Use Case

> **Whenever a problem mentions "prefix" — searching by prefix, counting words with a prefix, autocomplete, or building words incrementally — a Trie is almost always the right tool.**

---

## 3. Anatomy of a Trie Node

Every Trie node needs to answer two questions:
1. "Where can I go from here?" → pointers to children (one per possible next character)
2. "Does a complete word end exactly here?" → a boolean flag

```cpp
struct TrieNode {
    TrieNode* children[26];   // one slot per lowercase letter 'a' to 'z'
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};
```

### Why `isEndOfWord` is Essential

Without this flag, you cannot distinguish between "a prefix exists" and "a complete word exists". Consider inserting only `"care"`:

```
root → c → a → r → e*

Walking to node 'r' (i.e., checking "car") would succeed —
the PATH exists — but "car" was never inserted as a word.
isEndOfWord lets us tell the difference between:
   - "car" is a valid PREFIX of something (path exists)
   - "car" is itself a complete WORD (isEndOfWord == true)
```

This distinction is the single most common source of bugs when people first implement Tries — conflating "the path exists" with "this is a real word".

### Visualizing Node State

```
Node for character 'r' in "car"/"card":

┌─────────────────────────┐
│ children['d'-'a'] → ●   │  (points to 'd' node, rest are nullptr)
│ isEndOfWord = true       │  (because "car" was inserted)
└─────────────────────────┘
```

---

## 4. Core Operations Explained

A Trie supports three fundamental operations. Let's reason through each one before writing code.

### Operation 1: Insert(word)

**Logic**: Start at the root. For each character in the word, check if a child for that character exists — if not, create it. Move into that child. After processing the last character, mark that node as `isEndOfWord = true`.

```
Insert "car":

root → walk 'c' (create if missing) → walk 'a' (create) → walk 'r' (create)
     → mark final node's isEndOfWord = true
```

### Operation 2: Search(word) — exact match

**Logic**: Walk the Trie character by character, exactly like insert, but **never create** nodes — if a child is missing at any point, the word doesn't exist, return false immediately. If you successfully walk the entire word, the answer depends on whether the final node's `isEndOfWord` is true.

```
Search "car" in a Trie containing "card":

root → 'c' exists → 'a' exists → 'r' exists
     → reached end of "car", but isEndOfWord at 'r' node?
     → If only "card" was inserted, isEndOfWord at 'r' is FALSE
     → "car" is a prefix of "card", but not itself a word → return false
```

### Operation 3: StartsWith(prefix) — prefix match

**Logic**: Identical walk to Search, **except** we don't care about `isEndOfWord` at all — we only care whether we successfully walked the entire prefix without hitting a missing child.

```
StartsWith "car" in a Trie containing "card":

root → 'c' exists → 'a' exists → 'r' exists
     → successfully walked the whole prefix → return true
     (we never even check isEndOfWord)
```

### Side-by-Side Comparison

| Operation | Stops early if child missing? | Checks `isEndOfWord`? |
|-----------|-------------------------------|------------------------|
| Insert | No — creates missing nodes | Sets it to true at the end |
| Search | Yes — returns false | Yes — must be true to return true |
| StartsWith | Yes — returns false | No — path existing is enough |

This table is the entire mental model of a basic Trie. Once this clicks, every Trie problem becomes a variation on these three walks.

---

## 5. Building a Trie From Scratch in C++

Now let's translate the logic above directly into code, annotated heavily.

```cpp
class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEndOfWord;
        TrieNode() : isEndOfWord(false) {
            for (int i = 0; i < 26; i++) children[i] = nullptr;
        }
    };

    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // INSERT: walk down, creating nodes as needed
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr)
                node->children[idx] = new TrieNode();   // create missing node
            node = node->children[idx];                  // descend
        }
        node->isEndOfWord = true;   // mark the END of this exact word
    }

    // SEARCH: walk down, fail fast if path breaks, check isEndOfWord at finish
    bool search(string word) {
        TrieNode* node = walk(word);
        return node != nullptr && node->isEndOfWord;
    }

    // STARTSWITH: walk down, fail fast if path breaks, don't check isEndOfWord
    bool startsWith(string prefix) {
        return walk(prefix) != nullptr;
    }

private:
    // Shared helper: walks the path for a string, returns nullptr if it breaks
    TrieNode* walk(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (node->children[idx] == nullptr) return nullptr;  // path broken
            node = node->children[idx];
        }
        return node;   // landed exactly on the node for the last character
    }
};
```

### Walking Through an Example

```cpp
Trie trie;
trie.insert("apple");
trie.search("apple");    // true  — "apple" was inserted, isEndOfWord = true
trie.search("app");      // false — "app" is only a PREFIX of "apple"
trie.startsWith("app");  // true  — path "a-p-p" exists
trie.insert("app");
trie.search("app");      // true  — now "app" was explicitly inserted too
```

This example is exactly **LeetCode 208 — Implement Trie (Prefix Tree)**, the canonical starting problem for this topic.

---

## 6. Array vs HashMap Children — Tradeoffs

The `children` array above assumes lowercase English letters only (`'a'`–`'z'`). This is a design decision with real tradeoffs.

### Option A: Fixed-Size Array (`TrieNode* children[26]`)

```cpp
TrieNode* children[26];   // index = c - 'a'
```

| Pros | Cons |
|------|------|
| O(1) child access — direct array index | Wastes memory if alphabet is large or sparse |
| Cache-friendly, fast in practice | Must know the character set in advance (lowercase only, digits only, etc.) |
| Simple, no hashing overhead | Doesn't easily support Unicode or mixed case |

### Option B: HashMap Children (`unordered_map<char, TrieNode*>`)

```cpp
unordered_map<char, TrieNode*> children;
```

| Pros | Cons |
|------|------|
| Memory-efficient for sparse branching | Slightly slower due to hashing overhead |
| Works for any character set (Unicode, mixed case, symbols) | Less cache-friendly |

### When to Choose Which

```
If the problem says "lowercase English letters" → use array[26]
If the problem allows digits, uppercase, symbols, or is unspecified → use unordered_map
If memory is a tight constraint and the trie is very sparse → use unordered_map
If you want maximum raw speed and alphabet is small/fixed → use array
```

> In interviews, defaulting to `array[26]` for lowercase-only problems is standard — it's simpler to write correctly under time pressure and has no hashing overhead.

---

## 7. Complexity Analysis

Let `L` = length of the word/prefix being inserted or searched, `N` = number of words stored, and `Σ` = alphabet size (e.g., 26).

| Operation | Time Complexity | Why |
|-----------|------------------|-----|
| Insert | O(L) | One step per character, O(1) work per step (array) |
| Search (exact) | O(L) | Same walk as insert, no creation |
| StartsWith (prefix) | O(L) | Same walk, stops as soon as prefix consumed |
| Space (worst case) | O(N · L · Σ) | Every node can have up to Σ children pointers |
| Space (practical) | Much less | Shared prefixes mean massive reuse — far below worst case for real dictionaries |

### Why This Beats Brute Force

A naive prefix search over N stored strings of average length L costs **O(N · L)** — you must check every string. A Trie answers the same prefix query in **O(L)** — independent of how many words are stored. This is the entire value proposition of the data structure: **the cost of a prefix lookup depends only on the length of the prefix, never on how many words exist in the dictionary.**

```
1,000,000 words in dictionary, prefix length 5:

Hash Set linear scan:  O(1,000,000 × 5)  =  5,000,000 operations
Trie prefix walk:      O(5)              =  5 operations

This is why Tries power real autocomplete systems at scale.
```

---

## 8. Variations of Trie

### Variation 1: Trie with Word Count

Sometimes you need to know **how many words** pass through or end at a node (e.g., counting prefix occurrences).

```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    int countEndHere = 0;     // how many words end exactly here
    int countPassThrough = 0; // how many words pass through this node
};

void insert(string word) {
    TrieNode* node = root;
    node->countPassThrough++;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->children[idx]) node->children[idx] = new TrieNode();
        node = node->children[idx];
        node->countPassThrough++;     // every word using this node increments it
    }
    node->countEndHere++;
}
```

This variant directly answers "how many words have prefix X?" in O(L) by reading `countPassThrough` at the end of the prefix walk.

---

### Variation 2: Trie Storing Additional Data (Indices, Frequencies)

Instead of just a boolean, store richer information at the terminal node — common when you need to map a word back to its original index or metadata.

```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    int wordIndex = -1;    // index into original input array, -1 if not a word end
};
```

---

### Variation 3: Binary Trie (Bit Trie) for XOR Problems

Instead of 26 letters, each node has exactly **2 children** — for bit 0 and bit 1. Numbers are inserted bit by bit (usually from most significant bit to least). This variant is the backbone of "maximum XOR pair" style problems.

```cpp
struct BitTrieNode {
    BitTrieNode* children[2] = {nullptr, nullptr};
};

class BitTrie {
    BitTrieNode* root = new BitTrieNode();
    static const int BITS = 31;     // enough for 32-bit ints

public:
    void insert(int num) {
        BitTrieNode* node = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) node->children[bit] = new BitTrieNode();
            node = node->children[bit];
        }
    }

    // Find the max XOR achievable with num against any inserted number
    int maxXor(int num) {
        BitTrieNode* node = root;
        int result = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int wantedBit = 1 - bit;   // we WANT the opposite bit to maximize XOR
            if (node->children[wantedBit]) {
                result |= (1 << i);
                node = node->children[wantedBit];
            } else {
                node = node->children[bit];   // forced to take same bit
            }
        }
        return result;
    }
};
```

The key intuition: XOR of two bits is maximized (`=1`) when the bits **differ**. So at every level, the Bit Trie greedily tries to walk toward the **opposite** bit of the query number, to maximize the resulting XOR value bit by bit, starting from the most significant bit (since higher bits contribute more to the final value).

---

## 9. Common Trie Patterns

Recognizing these patterns will let you identify a Trie problem within seconds of reading it.

### Pattern A: Exact Word + Prefix Lookup

> "Implement a data structure that supports insert, search (exact), and startsWith (prefix)."

This is the base case — see Section 5. Direct application of the three core operations.

### Pattern B: Word Search on a Grid (Trie + DFS/Backtracking)

> "Given a 2D board and a list of words, find all words present on the board."

**Why a Trie helps**: Instead of running a separate DFS for each word (which repeats work for shared prefixes), insert **all words into one Trie**, then do a **single DFS pass over the board**, walking the Trie alongside the DFS. The instant a board path no longer matches any Trie path, you prune that DFS branch immediately — this is far faster than checking each word independently.

```
Without Trie: DFS once per word → repeats identical prefix exploration
With Trie:    DFS once total    → Trie path tells DFS when to stop early
```

### Pattern C: Prefix-Based Counting / Aggregation

> "Count how many words share a given prefix" or "sum/score of all words with prefix X"

Use the **Variation 1** (countPassThrough) trick from Section 8 — annotate each node with aggregate info as you insert, then a single prefix walk retrieves the answer in O(L).

### Pattern D: Maximum/Optimal XOR Pair (Bit Trie)

> "Find the maximum XOR of two numbers in an array" or "maximum XOR of a number with a number in a changing set"

Use the **Binary Trie** from Section 8, Variation 3. Insert numbers bit-by-bit; query by greedily walking toward opposite bits.

### Pattern E: Replace Words / Shortest Root Matching

> "Given a dictionary of roots and a sentence, replace each word with its shortest root if one exists."

Insert all dictionary roots into a Trie. For each word in the sentence, walk the Trie character by character — the **moment** you hit `isEndOfWord == true`, you've found the shortest matching root (since you're walking shortest-prefix-first), and you can stop immediately.

---

## 10. LeetCode Problems

A focused set of problems covering each pattern above — moderate in number, but each one teaches a distinct skill.

---

### 🔗 LC 208 — Implement Trie (Prefix Tree)

**Pattern**: A — foundational implementation (same as Section 5).

```cpp
class Trie {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEndOfWord = false;
    };
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* node = find(word);
        return node && node->isEndOfWord;
    }

    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    TrieNode* find(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) return nullptr;
            node = node->children[idx];
        }
        return node;
    }
};
// Time: O(L) per operation   Space: O(N*L) worst case
```

---

### 🔗 LC 211 — Design Add and Search Words Data Structure

**Pattern**: A (extended) — search must support `.` as a wildcard matching **any single character**.

**Key idea**: This breaks the simple "fail fast on missing child" logic, because `.` means "try every child". Use **DFS/backtracking** inside search instead of a flat loop.

```cpp
class WordDictionary {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEndOfWord = false;
    };
    TrieNode* root;

public:
    WordDictionary() { root = new TrieNode(); }

    void addWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    bool search(string word) {
        return dfs(word, 0, root);
    }

private:
    bool dfs(const string& word, int i, TrieNode* node) {
        if (!node) return false;
        if (i == word.size()) return node->isEndOfWord;

        char c = word[i];
        if (c == '.') {
            // Wildcard: try ALL possible children at this position
            for (int idx = 0; idx < 26; idx++)
                if (node->children[idx] && dfs(word, i + 1, node->children[idx]))
                    return true;
            return false;
        } else {
            int idx = c - 'a';
            return dfs(word, i + 1, node->children[idx]);
        }
    }
};
// Time: O(L) average, O(26^L) worst case (all wildcards)   Space: O(N*L)
```

---

### 🔗 LC 79 — Word Search (Single Word, Grid DFS — Trie Foundation)

**Pattern**: B (foundation before the multi-word version below).

This version searches for **one** word on a grid using pure backtracking — included here to build intuition before LC 212 adds the Trie layer.

```cpp
class Solution {
    int rows, cols;
public:
    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size(); cols = board[0].size();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (dfs(board, word, i, j, 0)) return true;
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, string& word, int r, int c, int idx) {
        if (idx == word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx])
            return false;

        char temp = board[r][c];
        board[r][c] = '#';   // mark visited
        bool found = dfs(board, word, r+1, c, idx+1) ||
                     dfs(board, word, r-1, c, idx+1) ||
                     dfs(board, word, r, c+1, idx+1) ||
                     dfs(board, word, r, c-1, idx+1);
        board[r][c] = temp;  // backtrack
        return found;
    }
};
// Time: O(rows*cols*4^L)   Space: O(L) recursion depth
```

---

### 🔗 LC 212 — Word Search II

**Pattern**: B — the full Trie + DFS combination. This is the single most important "applied Trie" problem on LeetCode.

**Key idea**: Build one Trie from **all** target words. Run DFS from every grid cell **once**, walking the Trie in lockstep with the DFS. Prune immediately when the Trie has no matching child — this avoids re-exploring the grid once per word.

```cpp
class Solution {
    struct TrieNode {
        TrieNode* children[26] = {};
        string word = "";    // non-empty at nodes where a full word ends
    };

    int rows, cols;

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (string& w : words) {
            TrieNode* node = root;
            for (char c : w) {
                int idx = c - 'a';
                if (!node->children[idx]) node->children[idx] = new TrieNode();
                node = node->children[idx];
            }
            node->word = w;       // mark word at terminal node
        }

        rows = board.size(); cols = board[0].size();
        vector<string> result;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                dfs(board, i, j, root, result);
        return result;
    }

private:
    void dfs(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& result) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] == '#') return;

        char ch = board[r][c];
        int idx = ch - 'a';
        if (!node->children[idx]) return;        // PRUNE: no matching word continues this way

        node = node->children[idx];
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = "";       // avoid duplicate results
        }

        board[r][c] = '#';         // mark visited
        dfs(board, r+1, c, node, result);
        dfs(board, r-1, c, node, result);
        dfs(board, r, c+1, node, result);
        dfs(board, r, c-1, node, result);
        board[r][c] = ch;          // backtrack
    }
};
// Time: O(rows*cols*4^L)  but with heavy pruning via Trie
// Space: O(sum of word lengths) for the Trie
```

---

### 🔗 LC 648 — Replace Words

**Pattern**: E — shortest root matching.

**Key idea**: Insert all roots into a Trie. For each sentence word, walk the Trie; the instant you reach `isEndOfWord`, that's the shortest valid root (because you walked from the start, shortest prefix first).

```cpp
class Solution {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEndOfWord = false;
    };
    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

    // Returns the shortest root prefix of word, or word itself if none found
    string shortestRoot(const string& word) {
        TrieNode* node = root;
        string prefix = "";
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return word;   // no root matches, keep original
            prefix += c;
            node = node->children[idx];
            if (node->isEndOfWord) return prefix;     // found shortest root — stop immediately
        }
        return word;
    }

public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        for (string& root_word : dictionary) insert(root_word);

        stringstream ss(sentence);
        string word, result;
        while (ss >> word) {
            if (!result.empty()) result += " ";
            result += shortestRoot(word);
        }
        return result;
    }
};
// Time: O(sum of dictionary lengths + sentence length)   Space: O(sum of root lengths)
```

---

### 🔗 LC 421 — Maximum XOR of Two Numbers in an Array

**Pattern**: D — Binary Trie for maximum XOR.

**Key idea**: Insert every number's binary representation (MSB to LSB) into a Bit Trie. For each number, greedily walk toward the **opposite bit** at every level to maximize the XOR result, exactly as explained in Section 8 Variation 3.

```cpp
class Solution {
    struct BitNode {
        BitNode* children[2] = {nullptr, nullptr};
    };
    static const int BITS = 30;   // covers values up to 2^31 - 1

public:
    int findMaximumXOR(vector<int>& nums) {
        BitNode* root = new BitNode();

        // Insert all numbers
        for (int num : nums) {
            BitNode* node = root;
            for (int i = BITS; i >= 0; i--) {
                int bit = (num >> i) & 1;
                if (!node->children[bit]) node->children[bit] = new BitNode();
                node = node->children[bit];
            }
        }

        int maxXor = 0;
        for (int num : nums) {
            BitNode* node = root;
            int curXor = 0;
            for (int i = BITS; i >= 0; i--) {
                int bit = (num >> i) & 1;
                int wanted = 1 - bit;             // opposite bit maximizes XOR
                if (node->children[wanted]) {
                    curXor |= (1 << i);
                    node = node->children[wanted];
                } else {
                    node = node->children[bit];   // forced, no choice
                }
            }
            maxXor = max(maxXor, curXor);
        }
        return maxXor;
    }
};
// Time: O(n * BITS)   Space: O(n * BITS)
```

---

### 🔗 LC 14 — Longest Common Prefix

**Pattern**: A (lightweight) — Trie used as a clean alternative to the typical character-comparison approach.

**Key idea**: Insert all strings into a Trie. Walk from the root **as long as each node has exactly one child and is not an end of word** — the moment a node branches (more than one child) or marks a complete word, the common prefix has ended.

```cpp
class Solution {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEndOfWord = false;
        int childCount = 0;
    };
    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
                node->childCount++;
            }
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }

public:
    string longestCommonPrefix(vector<string>& strs) {
        for (string& s : strs) insert(s);

        string prefix = "";
        TrieNode* node = root;
        while (node->childCount == 1 && !node->isEndOfWord) {
            for (int i = 0; i < 26; i++) {
                if (node->children[i]) {
                    prefix += char('a' + i);
                    node = node->children[i];
                    break;
                }
            }
        }
        return prefix;
    }
};
// Time: O(sum of string lengths)   Space: O(sum of string lengths)
// Note: the simple character-by-character comparison approach is O(S) too and
// uses less code — this Trie version is shown for pattern-recognition practice.
```

---

### 🔗 LC 1268 — Search Suggestions System

**Pattern**: A + C — autocomplete-style prefix matching, returning top suggestions at each typed character.

**Key idea**: This is the most "real-world" Trie problem — it's literally implementing a simplified autocomplete dropdown. Insert all products, then for each prefix of `searchWord`, walk the Trie and collect up to 3 lexicographically smallest matches.

```cpp
class Solution {
    struct TrieNode {
        TrieNode* children[26] = {};
        vector<string> suggestions;   // up to 3 smallest words passing through here
    };
    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
            if (node->suggestions.size() < 3)
                node->suggestions.push_back(word);   // products inserted in sorted order
        }
    }

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());   // ensures suggestions stay lexicographically sorted
        for (string& p : products) insert(p);

        vector<vector<string>> result;
        TrieNode* node = root;
        for (char c : searchWord) {
            int idx = c - 'a';
            if (node) node = node->children[idx];   // walk one character further
            result.push_back(node ? node->suggestions : vector<string>{});
        }
        return result;
    }
};
// Time: O(N log N) sorting + O(sum of product lengths) building + O(L) querying
// Space: O(N * L)
```

---

## 11. Common Mistakes & Debugging

### Mistake 1: Confusing "Path Exists" with "Word Exists"

```cpp
// WRONG — checking if path exists is NOT the same as exact word search
bool search(string word) {
    return find(word) != nullptr;   // missing isEndOfWord check!
}

// RIGHT
bool search(string word) {
    TrieNode* node = find(word);
    return node != nullptr && node->isEndOfWord;
}
```

This is, by far, the most common Trie bug. Always re-read Section 4's comparison table when in doubt.

### Mistake 2: Forgetting to Initialize Children to `nullptr`

```cpp
// WRONG — raw array, children are garbage pointers, not nullptr
TrieNode* children[26];   // UNDEFINED behavior on check!

// RIGHT — explicitly zero-initialize
TrieNode* children[26] = {};   // all nullptr
// or initialize in constructor
```

Uninitialized pointers in C++ are **not** automatically null — skipping this leads to crashes or silent corruption that's hard to trace.

### Mistake 3: Memory Leaks (Not Freeing Nodes)

```cpp
// Tries allocate many small nodes with `new` — if the Trie is destroyed
// without a destructor, this leaks memory. For LeetCode this is fine
// (process exits), but in production code, always pair with a recursive destructor:

~TrieNode() {
    for (int i = 0; i < 26; i++)
        delete children[i];   // recursively deletes the whole subtree
}
```

### Mistake 4: Off-by-One on Character Index

```cpp
// WRONG — forgetting the offset entirely
int idx = c;              // 'a' becomes 97, way out of bounds for [26]!

// RIGHT
int idx = c - 'a';        // 'a' becomes 0, 'z' becomes 25
```

### Mistake 5: Wildcard Search Without Backtracking (LC 211 style problems)

```cpp
// WRONG — treating '.' like a normal character breaks immediately
int idx = c - 'a';   // if c == '.', this is garbage!

// RIGHT — explicitly branch on '.' and try all 26 children recursively
if (c == '.') {
    for (int idx = 0; idx < 26; idx++)
        if (node->children[idx] && dfs(word, i+1, node->children[idx]))
            return true;
    return false;
}
```

### Mistake 6: Not Marking Visited Cells in Grid + Trie Problems (LC 212 style)

```cpp
// WRONG — forgetting to mark/unmark visited cells causes the same cell
// to be reused within a single word's path, producing invalid matches

board[r][c] = '#';     // mark visited BEFORE recursing
// ... recurse into neighbors ...
board[r][c] = ch;      // ALWAYS restore AFTER recursing (backtrack)
```

### Debugging Checklist

```
☐ Did I initialize all children pointers to nullptr?
☐ Does search() check isEndOfWord, while startsWith() does not?
☐ Am I using (c - 'a') consistently as the array index?
☐ For wildcard problems, am I branching into ALL children on '.'?
☐ For grid problems, am I marking AND unmarking visited cells (backtracking)?
☐ For Bit Tries, am I processing bits from MOST significant to least significant?
☐ Am I building the Trie ONCE outside repeated query loops (not rebuilding per query)?
```

---

## 12. Quick Reference

### The Three Core Walks

| Operation | Stops on missing child? | Final check |
|-----------|--------------------------|--------------|
| `insert(word)` | No — creates nodes | Set `isEndOfWord = true` |
| `search(word)` | Yes — return false | Must have `isEndOfWord == true` |
| `startsWith(prefix)` | Yes — return false | Path existing is sufficient |

### Node Template (Lowercase Letters)

```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEndOfWord = false;
};
```

### Node Template (Bit Trie for XOR)

```cpp
struct BitNode {
    BitNode* children[2] = {nullptr, nullptr};
};
```

### Pattern → Problem Map

| Pattern | Representative LC Problems |
|---------|----------------------------|
| Basic insert/search/prefix | 208 |
| Wildcard search (DFS in Trie) | 211 |
| Grid + Trie (multi-word search) | 212 (built on 79) |
| Shortest prefix/root matching | 648 |
| Binary Trie for max XOR | 421 |
| Autocomplete / suggestions | 1268 |
| Common prefix via Trie structure | 14 |

### Complexity At a Glance

| Metric | Value |
|--------|-------|
| Insert | O(L) |
| Search / StartsWith | O(L) |
| Space (worst case) | O(N · L · Σ) |
| Grid+Trie search (LC 212) | O(rows·cols·4^L), pruned heavily in practice |
| Bit Trie XOR query | O(BITS) per number |

### Golden Rules

```
1. A Trie answers "prefix" questions in O(L) — independent of how many words exist.
2. isEndOfWord is the ONLY thing distinguishing a real word from a mere prefix path.
3. search() checks isEndOfWord; startsWith() does not — never confuse the two.
4. Use array[26] for fixed lowercase alphabets; unordered_map for anything broader.
5. For grid + multiple target words → build ONE Trie, do ONE DFS pass (LC 212 pattern).
6. For XOR problems → think Binary Trie, walk toward the OPPOSITE bit greedily.
7. Always initialize children to nullptr — uninitialized pointers cause silent bugs.
8. Build the Trie once; never rebuild it inside a query loop.
```

---

*End of Tries (Prefix Trees) — Deep Dive*
