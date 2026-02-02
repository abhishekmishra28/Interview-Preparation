# B-Trees - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [What is a B-Tree?](#what-is-a-btree)
- [Properties](#properties)
- [Intuition](#intuition)
- [Structure](#structure)
- [Operations](#operations)
  - [Search](#search)
  - [Insertion](#insertion)
  - [Deletion](#deletion)
- [Implementation](#implementation)
- [Complexity Analysis](#complexity-analysis)
- [Variations](#variations)
- [Applications](#applications)
- [Complete C++ Program](#complete-cpp-program)
- [Practice Problems](#practice-problems)

---

# Introduction

A **B-Tree** is a self-balancing search tree designed for systems that read and write large blocks of data. Unlike binary search trees, B-Trees can have multiple keys per node and multiple children, making them ideal for disk-based storage systems.

**Invented by:** Rudolf Bayer and Edward M. McCreight (1972)  
**Primary Use:** Database indexing and file systems

---

# What is a B-Tree?

A B-Tree is a generalization of a binary search tree where:
- Each node can contain **multiple keys** (not just one)
- Each node can have **multiple children** (not just two)
- All leaf nodes are at the **same level**
- Tree remains **balanced** after insertions and deletions

### Why B-Trees?
Traditional binary search trees have issues with disk storage:
- Each node access requires a disk read
- BSTs can become unbalanced
- Poor locality of reference

B-Trees solve these problems by:
- Storing multiple keys per node (fewer disk accesses)
- Guaranteeing balanced structure
- Optimizing for block-based storage

---

# Properties

A B-Tree of order **m** (or minimum degree **t**) has the following properties:

## Formal Properties

1. **Every node has at most m children** (m-1 keys)
2. **Every non-leaf node (except root) has at least ⌈m/2⌉ children**
3. **Root has at least 2 children** (if not a leaf)
4. **All leaves are at the same level**
5. **A non-leaf node with k children contains k-1 keys**
6. **Keys in a node are sorted** in ascending order

## Using Minimum Degree 't'

More commonly defined using minimum degree **t** (where t ≥ 2):

1. Every node (except root) must contain **at least t-1 keys**
2. Every node can contain **at most 2t-1 keys**
3. Root must have **at least 1 key**
4. Every internal node has **at least t children**
5. Every internal node has **at most 2t children**
6. All leaves are at the **same depth**

### Example: B-Tree with t = 3
- Min keys per node: 2
- Max keys per node: 5
- Min children: 3
- Max children: 6

---

# Intuition

Think of a B-Tree like a **multi-level index** in a book:

**Binary Search Tree:** Like a book with a single index entry per page
```
Each page → One entry → Two sub-pages
```

**B-Tree:** Like a book with multiple index entries per page
```
Each page → Multiple entries → Multiple sub-pages
Fewer page turns needed!
```

### Visual Comparison

**Binary Search Tree:**
```
        10
       /  \
      5    15
     / \   / \
    3   7 12  20
```
Height = 3, Nodes = 7

**B-Tree (t=3):**
```
        [10, 20]
       /    |    \
    [5,7]  [15]  [25,30]
```
Height = 2, Same data organized differently

### Key Insight
B-Trees reduce height by increasing branching factor, which means:
- **Fewer disk accesses** (each level = one disk read)
- **Better cache performance**
- **Optimal for external storage**

---

# Structure

## Node Structure

Each B-Tree node contains:
1. **Array of keys** (sorted)
2. **Array of child pointers**
3. **Number of keys** currently stored
4. **Leaf flag** (is this a leaf node?)

```
Node Structure:
┌─────────────────────────────────────┐
│ n (number of keys)                  │
├─────────────────────────────────────┤
│ keys[0] | keys[1] | ... | keys[n-1] │
├─────────────────────────────────────┤
│ C[0] | C[1] | ... | C[n]            │
├─────────────────────────────────────┤
│ leaf (boolean)                      │
└─────────────────────────────────────┘
```

## Example B-Tree (t = 3)

```
                    [G, M, P, X]
                    /  |  |  |  \
                   /   |  |  |   \
        [A,C,D,E] [J,K,L] [N,O] [R,S,T,U,V] [Y,Z]
```

**Properties:**
- Min keys per node: 2 (except root)
- Max keys per node: 5
- All leaves at same level
- Keys within nodes are sorted

---

# Operations

## Search

Searching in a B-Tree is similar to binary search tree, but within each node:

### Algorithm:
1. Start at root
2. Perform binary/linear search within current node
3. If key found, return success
4. If leaf node and key not found, return failure
5. Otherwise, follow appropriate child pointer
6. Repeat from step 2

### Visualization:
```
Search for 'R' in B-Tree:

Step 1: At root [G, M, P, X]
        R > P, R < X → Go to 4th child

Step 2: At [R,S,T,U,V]
        Found R! ✓
```

### Pseudocode:
```
Search(node, key):
    i = 0
    while i < node.n and key > node.keys[i]:
        i++
    
    if i < node.n and key == node.keys[i]:
        return (node, i)  // Found
    
    if node.leaf:
        return NULL  // Not found
    
    return Search(node.C[i], key)
```

## Insertion

Insertion is more complex to maintain B-Tree properties:

### Key Idea:
- Insert into appropriate leaf node
- If node becomes full, **split** it
- Promote middle key to parent
- Recursively handle parent splits if needed

### Algorithm Steps:

1. **Find correct leaf** for insertion
2. **Insert key** into leaf (if not full)
3. **If leaf is full:**
   - Split leaf into two nodes
   - Move median key up to parent
   - If parent is full, split parent recursively
4. **If root splits:**
   - Create new root (tree height increases)

### Split Operation:

When a node with 2t-1 keys gets one more key:

```
Before Split (t=3, node full with 5 keys):
[10, 20, 30, 40, 50]

After Split:
Parent gets: [30]
       /          \
[10, 20]      [40, 50]
```

### Example: Insert 55

```
Initial:           [30]
                  /    \
            [10,20]  [40,50]

Insert 55:
Step 1: 55 > 30, go right
Step 2: Insert into [40,50] → [40,50,55]

Result:            [30]
                  /    \
            [10,20]  [40,50,55]
```

### Example: Insert 60 (causes split)

```
Current:           [30]
                  /    \
            [10,20]  [40,50,55]

Insert 60:
Step 1: [40,50,55] + 60 → [40,50,55,60]
Step 2: Still under limit (t=3, max=5)

Result:            [30]
                  /    \
            [10,20]  [40,50,55,60]
```

### Example: Insert 65 (causes split)

```
Current:              [30]
                     /    \
               [10,20]  [40,50,55,60]

Insert 65:
Step 1: [40,50,55,60] + 65 → [40,50,55,60,65] (FULL!)
Step 2: Split at median (55)

Result:           [30, 55]
                 /    |    \
          [10,20] [40,50] [60,65]
```

## Deletion

Deletion is the most complex operation in B-Trees.

### Cases:

#### Case 1: Key in leaf node
- **Simple deletion** if node has > t-1 keys
- **Borrow from sibling** if sibling has > t-1 keys
- **Merge with sibling** otherwise

#### Case 2: Key in internal node
- **Replace with predecessor/successor**
- Delete predecessor/successor recursively

#### Case 3: Key not in node
- **Recursively delete** from appropriate child
- **Ensure child has ≥ t keys** before recursion

### Deletion Strategies:

**Borrow from Left Sibling:**
```
Before:
Parent: [30, 50]
       /    |    \
   [10,20] [35] [60,70]  (Delete 35, borrow from left)

After:
Parent: [20, 50]
       /    |    \
    [10]  [30] [60,70]
```

**Borrow from Right Sibling:**
```
Before:
Parent: [30, 50]
       /    |    \
    [10]  [35] [60,70]  (Delete 35, borrow from right)

After:
Parent: [30, 60]
       /    |    \
    [10]  [50] [70]
```

**Merge with Sibling:**
```
Before:
Parent: [30, 50]
       /    |    \
   [10]  [35] [60]  (Delete 35, merge)

After:
Parent: [50]
       /    \
  [10,30]  [60]
```

### Algorithm Steps:

1. **Locate key** to delete
2. **If in leaf:**
   - Remove if node has enough keys
   - Otherwise, borrow or merge
3. **If in internal node:**
   - Replace with predecessor/successor
   - Delete predecessor/successor
4. **Fix violations** bottom-up

---

# Implementation

## Node Structure

```cpp
class BTreeNode {
public:
    int* keys;          // Array of keys
    int t;              // Minimum degree (t)
    BTreeNode** C;      // Array of child pointers
    int n;              // Current number of keys
    bool leaf;          // Is true when node is leaf
    
    BTreeNode(int _t, bool _leaf);
    
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void remove(int k);
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    
    friend class BTree;
};
```

## B-Tree Class

```cpp
class BTree {
private:
    BTreeNode* root;
    int t;  // Minimum degree
    
public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }
    
    void traverse() {
        if (root != NULL) root->traverse();
    }
    
    BTreeNode* search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }
    
    void insert(int k);
    void remove(int k);
};
```

## Search Implementation

```cpp
BTreeNode* BTreeNode::search(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    
    // If the found key is equal to k, return this node
    if (i < n && keys[i] == k)
        return this;
    
    // If key is not found and this is a leaf node
    if (leaf)
        return NULL;
    
    // Recur to the appropriate child
    return C[i]->search(k);
}
```

## Insert Implementation

```cpp
void BTree::insert(int k) {
    // If tree is empty
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        // If root is full, tree grows in height
        if (root->n == 2*t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    
    if (leaf) {
        // Insert key into sorted order
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        // Find child to insert
        while (i >= 0 && keys[i] > k)
            i--;
        
        if (C[i + 1]->n == 2*t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    
    // Copy the last t children of y to z
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    
    y->n = t - 1;
    
    // Create space for new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    
    C[i + 1] = z;
    
    // Move key from y to this node
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    
    keys[i] = y->keys[t - 1];
    n = n + 1;
}
```

## Deletion Implementation

```cpp
void BTree::remove(int k) {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    
    root->remove(k);
    
    // If root is empty, make its only child the new root
    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
        delete tmp;
    }
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    
    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "Key " << k << " not found\n";
            return;
        }
        
        bool flag = (idx == n);
        
        if (C[idx]->n < t)
            fill(idx);
        
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    
    if (C[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];
    
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }
    
    child->keys[0] = keys[idx - 1];
    
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];
    
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    
    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];
    
    child->keys[child->n] = keys[idx];
    
    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];
    
    keys[idx] = sibling->keys[0];
    
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }
    
    child->n += 1;
    sibling->n -= 1;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];
    
    child->keys[t - 1] = keys[idx];
    
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];
    
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }
    
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];
    
    child->n += sibling->n + 1;
    n--;
    
    delete sibling;
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}
```

## Traverse Implementation

```cpp
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    
    if (!leaf)
        C[i]->traverse();
}
```

---

# Complexity Analysis

## Time Complexity

| Operation | Time Complexity | Explanation |
|-----------|----------------|-------------|
| **Search** | O(log n) | Height is O(log n), search within node is O(t) |
| **Insert** | O(log n) | Height traversal + splits |
| **Delete** | O(log n) | Height traversal + merges/borrows |
| **Traverse** | O(n) | Visit all nodes |

**Detailed Analysis:**
- Height of B-Tree: h ≤ log_t((n+1)/2)
- At each level: O(t) comparisons
- Total: O(t × log_t n) = O(log n) when t is constant

## Space Complexity

| Aspect | Space |
|--------|-------|
| **Storage per node** | O(t) |
| **Total storage** | O(n) |
| **Recursion stack** | O(log n) |

## Comparison with Binary Search Tree

| Property | BST | B-Tree |
|----------|-----|--------|
| **Height** | O(n) worst, O(log n) balanced | O(log n) guaranteed |
| **Keys per node** | 1 | Multiple (up to 2t-1) |
| **Disk accesses** | O(h) | O(log_t n) - much fewer! |
| **Cache efficiency** | Poor | Excellent |

---

# Variations

## B+ Tree
- All values stored in leaf nodes
- Internal nodes only store keys for routing
- Leaf nodes linked together (range queries)
- **Used in:** Databases, file systems

```
B+ Tree Structure:
         [30, 60]
        /    |    \
      /      |      \
   [10,20,30] [40,50,60] [70,80,90]
      ↔          ↔           ↔
   (Linked list of leaves)
```

## B* Tree
- Delays splits by redistributing to siblings
- Minimum 2/3 full (instead of 1/2)
- Better space utilization
- Fewer splits needed

## 2-3 Tree
- B-Tree with t = 2
- Each node has 2 or 3 children
- Simpler implementation
- Educational purposes

## 2-3-4 Tree
- B-Tree with t = 2
- Each node has 2, 3, or 4 children
- Isomorphic to Red-Black Tree
- **Used in:** Java TreeMap

---

# Applications

## 1. Database Indexing
**Why:** Minimize disk I/O operations
- MySQL InnoDB uses B+ Trees
- PostgreSQL uses B-Trees
- Each node = one disk block
- Fewer disk reads needed

## 2. File Systems
**Why:** Efficient file lookup and range queries
- NTFS (Windows)
- HFS+, APFS (macOS)
- ext4 (Linux) - for directories
- ReiserFS

## 3. Multilevel Indexing
**Why:** Handle large datasets
- Primary index: B-Tree
- Secondary index: B+ Tree
- Sparse vs dense indexing

## 4. Real-world Systems
- **MongoDB:** Uses B-Trees for indexes
- **Oracle Database:** B-Tree indexes
- **SQLite:** B-Tree for tables and indexes
- **Cassandra:** SSTables use B-Tree-like structures

## Why B-Trees Excel:

### Disk-Based Storage
- **Block-oriented:** Matches disk block size
- **Sequential access:** Better than random
- **Reduced seeks:** Fewer disk head movements

### Memory Hierarchy
- **Cache-friendly:** Nodes fit in cache lines
- **Locality:** Related data stored together
- **Prefetching:** Sequential reads optimized

### Scalability
- **Logarithmic height:** Even for billions of keys
- **Configurable t:** Tune for block size
- **Balanced:** Guaranteed performance

---

# Complete C++ Program

```cpp
#include <iostream>
using namespace std;

class BTreeNode {
    int* keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;

public:
    BTreeNode(int _t, bool _leaf);
    
    void traverse();
    BTreeNode* search(int k);
    int findKey(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    
    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }
    
    void traverse() {
        if (root != NULL) {
            root->traverse();
        }
    }
    
    BTreeNode* search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }
    
    void insert(int k);
    void remove(int k);
};

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode*[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    
    if (leaf == false)
        C[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    
    if (i < n && keys[i] == k)
        return this;
    
    if (leaf == true)
        return NULL;
    
    return C[i]->search(k);
}

void BTree::insert(int k) {
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    
    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    
    y->n = t - 1;
    
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    
    C[i + 1] = z;
    
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    
    keys[i] = y->keys[t - 1];
    n = n + 1;
}

void BTree::remove(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }
    
    root->remove(k);
    
    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
        
        delete tmp;
    }
    return;
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    
    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "The key " << k << " does not exist in the tree\n";
            return;
        }
        
        bool flag = ((idx == n) ? true : false);
        
        if (C[idx]->n < t)
            fill(idx);
        
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
    return;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    
    if (C[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];
    
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }
    
    child->keys[0] = keys[idx - 1];
    
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];
    
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    
    child->n += 1;
    sibling->n -= 1;
    
    return;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];
    
    child->keys[child->n] = keys[idx];
    
    if (!child->leaf)
        child->C[child->n + 1] = sibling->C[0];
    
    keys[idx] = sibling->keys[0];
    
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }
    
    child->n += 1;
    sibling->n -= 1;
    
    return;
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];
    
    child->keys[t - 1] = keys[idx];
    
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];
    
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }
    
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    
    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];
    
    child->n += sibling->n + 1;
    n--;
    
    delete sibling;
    return;
}

int main() {
    BTree t(3); // A B-Tree with minimum degree 3
    
    cout << "Inserting keys: 10, 20, 5, 6, 12, 30, 7, 17\n";
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    
    cout << "Traversal of the constructed tree is: ";
    t.traverse();
    cout << endl;
    
    int k = 6;
    BTreeNode* result = t.search(k);
    (result != NULL) ? cout << "\nKey " << k << " is present in tree"
                     : cout << "\nKey " << k << " is NOT present in tree";
    
    k = 15;
    result = t.search(k);
    (result != NULL) ? cout << "\nKey " << k << " is present in tree"
                     : cout << "\nKey " << k << " is NOT present in tree";
    
    cout << "\n\nDeleting key 6\n";
    t.remove(6);
    cout << "Traversal after deletion: ";
    t.traverse();
    cout << endl;
    
    cout << "\nDeleting key 13 (not in tree)\n";
    t.remove(13);
    
    cout << "\nDeleting key 7\n";
    t.remove(7);
    cout << "Traversal after deletion: ";
    t.traverse();
    cout << endl;
    
    cout << "\nDeleting key 20\n";
    t.remove(20);
    cout << "Traversal after deletion: ";
    t.traverse();
    cout << endl;
    
    return 0;
}
```

### Sample Output
```
Inserting keys: 10, 20, 5, 6, 12, 30, 7, 17
Traversal of the constructed tree is:  5 6 7 10 12 17 20 30

Key 6 is present in tree
Key 15 is NOT present in tree

Deleting key 6
Traversal after deletion:  5 7 10 12 17 20 30

Deleting key 13 (not in tree)
The key 13 does not exist in the tree

Deleting key 7
Traversal after deletion:  5 10 12 17 20 30

Deleting key 20
Traversal after deletion:  5 10 12 17 30
```

---

# Practice Problems

## Easy Level
1. Implement search in B-Tree
2. Count total keys in B-Tree
3. Find height of B-Tree
4. Check if B-Tree is valid
5. Print all leaf nodes

## Medium Level
6. **Range Query** - Find all keys in range [a, b]
7. **Level Order Traversal** - Print B-Tree level by level
8. **Minimum/Maximum** - Find min/max key in B-Tree
9. **Predecessor/Successor** - Find predecessor and successor
10. **Serialize/Deserialize** - Convert B-Tree to array and back

## Hard Level
11. **Bulk Loading** - Build B-Tree from sorted array efficiently
12. **Concurrent B-Tree** - Thread-safe B-Tree operations
13. **B+ Tree Implementation** - Implement B+ Tree variant
14. **Disk-based B-Tree** - Implement with actual file I/O
15. **Optimize Space** - Implement space-efficient B-Tree

## Interview Questions
- Explain why databases use B-Trees over Binary Search Trees
- How does B-Tree maintain balance?
- Compare B-Tree vs Hash Index
- Design a file system using B-Trees
- Optimize B-Tree for SSDs vs HDDs

## LeetCode-style Problems
- Design and implement a B-Tree from scratch
- Implement range queries efficiently
- Convert BST to B-Tree
- Merge two B-Trees
- Find kth smallest element in B-Tree

---

# Key Takeaways

## Core Concepts
1. **Multiple keys per node** - Reduces tree height
2. **Balanced structure** - All leaves at same level
3. **Disk-optimized** - Minimizes I/O operations
4. **Self-balancing** - Maintains properties after insert/delete

## When to Use B-Trees
✅ **Database indexing** - Primary use case  
✅ **File systems** - Directory structures  
✅ **Large datasets** - That don't fit in memory  
✅ **Block-oriented storage** - Disks, SSDs  
✅ **Range queries** - Efficient sequential access  

## Advantages
- Guaranteed O(log n) operations
- Minimizes disk I/O
- Excellent cache performance
- Scalable to billions of records
- Self-balancing

## Disadvantages
- Complex implementation (especially deletion)
- Overhead for small datasets
- Not ideal for in-memory data
- Requires careful tuning of 't'

## Real-World Impact
B-Trees power most modern databases and file systems, handling trillions of queries daily across the internet. Understanding B-Trees is essential for:
- Database engineers
- Systems programmers
- Storage system designers
- Performance optimization

---

**Master B-Trees, Master Databases! 🚀**
