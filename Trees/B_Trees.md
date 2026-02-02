<<<<<<< HEAD
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
=======
# Binary Trees - Complete Guide

## Table of Contents
- [Introduction](#introduction)
- [What is a Binary Tree?](#what-is-a-binary-tree)
- [Types of Binary Trees](#types-of-binary-trees)
- [Tree Terminology](#tree-terminology)
- [Implementation](#implementation)
- [Tree Traversals](#tree-traversals)
- [Binary Tree Operations](#binary-tree-operations)
- [Properties and Formulas](#properties-and-formulas)
- [Special Binary Trees](#special-binary-trees)
- [Common Problems](#common-problems)
- [Advanced Concepts](#advanced-concepts)
- [Complete C++ Implementation](#complete-c++-implementation)
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661
- [Practice Problems](#practice-problems)

---

# Introduction

<<<<<<< HEAD
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
=======
A **Binary Tree** is a hierarchical data structure in which each node has at most two children, referred to as the **left child** and **right child**.

**Key Characteristics:**
- Non-linear data structure
- Hierarchical organization
- Each node has at most 2 children
- Used in searching, sorting, and hierarchical data representation

---

# What is a Binary Tree?

## Structure

```
         1          ← Root
       /   \
      2     3       ← Level 1
     / \   / \
    4   5 6   7     ← Level 2 (Leaf nodes)
```

## Node Structure

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
```

## Visual Representation

```
           10
          /  \
         5    15
        / \     \
       3   7    20
```

**Components:**
- **Node 10**: Root
- **Nodes 5, 15**: Children of root
- **Nodes 3, 7, 20**: Leaf nodes
- **Left subtree**: {5, 3, 7}
- **Right subtree**: {15, 20}

---

# Types of Binary Trees

## 1. Full Binary Tree

**Definition:** Every node has either 0 or 2 children (no node has only 1 child).

```
        1
       / \
      2   3
     / \
    4   5
```

✅ Valid Full Binary Tree
```
        1
       / \
      2   3
         / \
        4   5
```

❌ Not Full (node 3 has only 1 child)
```
        1
       / \
      2   3
           \
            4
```

## 2. Complete Binary Tree

**Definition:** All levels are completely filled except possibly the last level, which is filled from left to right.

✅ Valid Complete Binary Tree
```
        1
       / \
      2   3
     / \  /
    4  5 6
```

❌ Not Complete (last level not filled left to right)
```
        1
       / \
      2   3
     /     \
    4       5
```

**Properties:**
- Used in Heap data structure
- Efficient array representation
- Height is ⌊log₂(n)⌋

## 3. Perfect Binary Tree

**Definition:** All internal nodes have exactly 2 children and all leaf nodes are at the same level.

```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

**Properties:**
- Total nodes = 2^(h+1) - 1, where h is height
- Leaf nodes = 2^h
- Most balanced form

## 4. Balanced Binary Tree

**Definition:** Height of left and right subtrees of every node differ by at most 1.

✅ Balanced
```
        1
       / \
      2   3
     / \
    4   5
```

❌ Not Balanced
```
        1
       / 
      2   
     / 
    3
   /
  4
```

**Examples:** AVL Tree, Red-Black Tree

## 5. Degenerate (Skewed) Binary Tree

**Definition:** Every internal node has only one child.

**Left Skewed:**
```
    1
   /
  2
 /
3
```

**Right Skewed:**
```
1
 \
  2
   \
    3
```

**Properties:**
- Behaves like a linked list
- Height = n - 1
- Worst case for operations

## 6. Binary Search Tree (BST)

**Definition:** Left subtree contains nodes with values less than parent, right subtree contains nodes greater than parent.

```
        8
       / \
      3   10
     / \    \
    1   6   14
       / \  /
      4  7 13
```

**Property:** Inorder traversal gives sorted sequence

---

# Tree Terminology

## Basic Terms

```
           A          ← Root
          / \
         B   C        ← Siblings
        / \   \
       D   E   F      ← Leaf Nodes
```

| Term | Definition | Example |
|------|------------|---------|
| **Root** | Topmost node | A |
| **Parent** | Node with children | B is parent of D, E |
| **Child** | Node connected below | D, E are children of B |
| **Leaf** | Node with no children | D, E, F |
| **Internal Node** | Node with at least one child | A, B, C |
| **Siblings** | Nodes with same parent | B and C |
| **Ancestor** | Nodes on path from root to node | A, B are ancestors of D |
| **Descendant** | Nodes in subtree | D, E are descendants of B |
| **Depth** | Distance from root | Depth of D = 2 |
| **Height** | Distance to farthest leaf | Height of B = 1 |
| **Level** | Depth + 1 | Level of D = 3 |
| **Subtree** | Tree formed by node and descendants | Subtree rooted at B |

## Measurements

```
        1           ← Level 0, Depth 0
       / \
      2   3         ← Level 1, Depth 1
     / \
    4   5           ← Level 2, Depth 2
```

**Height of tree:** Maximum depth = 2
**Height of node 2:** 1
**Height of node 4:** 0
**Depth of node 5:** 2
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661

---

# Implementation

## Node Structure

```cpp
<<<<<<< HEAD
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
=======
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    // Constructor
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

## Binary Tree Class

```cpp
class BinaryTree {
private:
    TreeNode* root;

public:
    BinaryTree() : root(nullptr) {}
    
    // Create root node
    void createRoot(int data) {
        root = new TreeNode(data);
    }
    
    // Get root
    TreeNode* getRoot() {
        return root;
    }
    
    // Insert left child
    TreeNode* insertLeft(TreeNode* parent, int data) {
        if (parent == nullptr) return nullptr;
        parent->left = new TreeNode(data);
        return parent->left;
    }
    
    // Insert right child
    TreeNode* insertRight(TreeNode* parent, int data) {
        if (parent == nullptr) return nullptr;
        parent->right = new TreeNode(data);
        return parent->right;
    }
};
```

## Creating a Binary Tree

```cpp
int main() {
    BinaryTree tree;
    
    // Create tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    tree.createRoot(1);
    TreeNode* root = tree.getRoot();
    
    TreeNode* node2 = tree.insertLeft(root, 2);
    TreeNode* node3 = tree.insertRight(root, 3);
    
    tree.insertLeft(node2, 4);
    tree.insertRight(node2, 5);
    
    return 0;
}
```

---

# Tree Traversals

## 1. Inorder Traversal (Left → Root → Right)

```cpp
void inorder(TreeNode* root) {
    if (root == nullptr) return;
    
    inorder(root->left);        // Visit left subtree
    cout << root->data << " ";  // Visit root
    inorder(root->right);       // Visit right subtree
}
```

**Example:**
```
Tree:       1
           / \
          2   3
         / \
        4   5

Inorder: 4 2 5 1 3
```

**Use Cases:**
- Get sorted sequence in BST
- Expression tree evaluation

## 2. Preorder Traversal (Root → Left → Right)

```cpp
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    
    cout << root->data << " ";  // Visit root
    preorder(root->left);       // Visit left subtree
    preorder(root->right);      // Visit right subtree
}
```

**Example:**
```
Tree:       1
           / \
          2   3
         / \
        4   5

Preorder: 1 2 4 5 3
```

**Use Cases:**
- Create copy of tree
- Get prefix expression
- Tree serialization

## 3. Postorder Traversal (Left → Right → Root)

```cpp
void postorder(TreeNode* root) {
    if (root == nullptr) return;
    
    postorder(root->left);      // Visit left subtree
    postorder(root->right);     // Visit right subtree
    cout << root->data << " ";  // Visit root
}
```

**Example:**
```
Tree:       1
           / \
          2   3
         / \
        4   5

Postorder: 4 5 2 3 1
```

**Use Cases:**
- Delete tree (delete children before parent)
- Get postfix expression
- Calculate directory size

## 4. Level Order Traversal (Breadth-First)

```cpp
void levelOrder(TreeNode* root) {
    if (root == nullptr) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        cout << node->data << " ";
        
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

**Example:**
```
Tree:       1
           / \
          2   3
         / \
        4   5

Level Order: 1 2 3 4 5
```

**Use Cases:**
- Level-by-level processing
- Find shortest path in unweighted tree
- Serialize tree level-wise

## Traversal Comparison

```
Tree:       1
           / \
          2   3
         / \   \
        4   5   6

Inorder:    4 2 5 1 3 6
Preorder:   1 2 4 5 3 6
Postorder:  4 5 2 6 3 1
Level:      1 2 3 4 5 6
```

---

# Binary Tree Operations

## 1. Height of Binary Tree

```cpp
int height(TreeNode* root) {
    if (root == nullptr) return -1;  // or 0 depending on definition
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + max(leftHeight, rightHeight);
}
```

**Example:**
```
        1           Height = 2
       / \
      2   3         Height of node 2 = 1
     / \            Height of node 4 = 0
    4   5
```

## 2. Count Nodes

```cpp
int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}
```

## 3. Count Leaf Nodes

```cpp
int countLeaves(TreeNode* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}
```

## 4. Sum of All Nodes

```cpp
int sumNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}
```

## 5. Search Element

```cpp
bool search(TreeNode* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    return search(root->left, key) || search(root->right, key);
}
```

## 6. Maximum Element

```cpp
int findMax(TreeNode* root) {
    if (root == nullptr) return INT_MIN;
    
    int maxVal = root->data;
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    
    return max(maxVal, max(leftMax, rightMax));
}
```

## 7. Diameter of Tree

```cpp
int diameter(TreeNode* root, int& maxDiameter) {
    if (root == nullptr) return 0;
    
    int leftHeight = diameter(root->left, maxDiameter);
    int rightHeight = diameter(root->right, maxDiameter);
    
    // Update diameter (path through current node)
    maxDiameter = max(maxDiameter, leftHeight + rightHeight);
    
    // Return height
    return 1 + max(leftHeight, rightHeight);
}

int getDiameter(TreeNode* root) {
    int maxDiameter = 0;
    diameter(root, maxDiameter);
    return maxDiameter;
}
```

**Example:**
```
        1
       / \
      2   3
     / \
    4   5
   /
  6

Diameter = 4 (path: 6 → 4 → 2 → 5)
```

## 8. Mirror/Invert Tree

```cpp
void mirror(TreeNode* root) {
    if (root == nullptr) return;
    
    // Swap children
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively mirror subtrees
    mirror(root->left);
    mirror(root->right);
}
```

**Example:**
```
Original:       1              Mirror:         1
               / \                            / \
              2   3                          3   2
             / \                                / \
            4   5                              5   4
```

## 9. Check if Two Trees are Identical

```cpp
bool isIdentical(TreeNode* root1, TreeNode* root2) {
    // Both null
    if (root1 == nullptr && root2 == nullptr) return true;
    
    // One null, other not
    if (root1 == nullptr || root2 == nullptr) return false;
    
    // Check data and recursively check subtrees
    return (root1->data == root2->data) &&
           isIdentical(root1->left, root2->left) &&
           isIdentical(root1->right, root2->right);
}
```

## 10. Level of a Node

```cpp
int getLevel(TreeNode* root, int key, int level = 0) {
    if (root == nullptr) return -1;
    if (root->data == key) return level;
    
    int leftLevel = getLevel(root->left, key, level + 1);
    if (leftLevel != -1) return leftLevel;
    
    return getLevel(root->right, key, level + 1);
}
```

---

# Properties and Formulas

## Important Properties

| Property | Formula | Description |
|----------|---------|-------------|
| **Max nodes at level L** | 2^L | Level starts from 0 |
| **Max nodes (height h)** | 2^(h+1) - 1 | Perfect binary tree |
| **Min height** | ⌊log₂(n)⌋ | n = number of nodes |
| **Max height** | n - 1 | Skewed tree |
| **Leaf nodes** | ⌈n/2⌉ | In complete binary tree |
| **Internal nodes** | ⌊n/2⌋ | Non-leaf nodes |

## Examples

**For n = 7 nodes:**
- Min height = ⌊log₂(7)⌋ = 2
- Max height = 7 - 1 = 6
- Leaf nodes ≈ 4
- Internal nodes ≈ 3

**For height h = 3:**
- Max nodes = 2^4 - 1 = 15
- Nodes at level 3 = 2^3 = 8

## Relationship Between Nodes

```
For a binary tree with:
- n = total nodes
- n₀ = leaf nodes
- n₁ = nodes with 1 child
- n₂ = nodes with 2 children

Formulas:
1. n = n₀ + n₁ + n₂
2. n₀ = n₂ + 1  (leaf nodes = internal nodes with 2 children + 1)
```

---

# Special Binary Trees

## 1. Binary Search Tree (BST)

```cpp
class BST {
private:
    TreeNode* root;
    
    TreeNode* insertRec(TreeNode* node, int data) {
        if (node == nullptr) {
            return new TreeNode(data);
        }
        
        if (data < node->data) {
            node->left = insertRec(node->left, data);
        } else if (data > node->data) {
            node->right = insertRec(node->right, data);
        }
        
        return node;
    }
    
    TreeNode* searchRec(TreeNode* node, int key) {
        if (node == nullptr || node->data == key) {
            return node;
        }
        
        if (key < node->data) {
            return searchRec(node->left, key);
        }
        return searchRec(node->right, key);
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int data) {
        root = insertRec(root, data);
    }
    
    bool search(int key) {
        return searchRec(root, key) != nullptr;
    }
};
```

## 2. Threaded Binary Tree

```cpp
struct ThreadedNode {
    int data;
    ThreadedNode* left;
    ThreadedNode* right;
    bool rightThread;  // true if right points to inorder successor
    
    ThreadedNode(int val) : data(val), left(nullptr), 
                            right(nullptr), rightThread(false) {}
};
```

**Advantage:** Inorder traversal without stack or recursion

## 3. Expression Tree

```cpp
// Tree for expression: (a + b) * (c - d)
//         *
//        / \
//       +   -
//      / \ / \
//     a  b c  d

int evaluate(TreeNode* root) {
    if (root == nullptr) return 0;
    
    // Leaf node (operand)
    if (root->left == nullptr && root->right == nullptr) {
        return root->data;
    }
    
    // Evaluate left and right subtrees
    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);
    
    // Apply operator
    switch(root->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
    }
    
    return 0;
}
```

---

# Common Problems

## 1. Lowest Common Ancestor (LCA)

```cpp
TreeNode* LCA(TreeNode* root, int n1, int n2) {
    if (root == nullptr) return nullptr;
    
    // If either n1 or n2 matches root
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    
    // Look for keys in left and right subtrees
    TreeNode* leftLCA = LCA(root->left, n1, n2);
    TreeNode* rightLCA = LCA(root->right, n1, n2);
    
    // If both return non-null, root is LCA
    if (leftLCA && rightLCA) {
        return root;
    }
    
    // Otherwise return non-null value
    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}
```

**Example:**
```
        1
       / \
      2   3
     / \
    4   5

LCA(4, 5) = 2
LCA(4, 3) = 1
LCA(2, 3) = 1
```

## 2. Check if Tree is Balanced

```cpp
int checkHeight(TreeNode* root) {
    if (root == nullptr) return 0;
    
    int leftHeight = checkHeight(root->left);
    if (leftHeight == -1) return -1;  // Left subtree not balanced
    
    int rightHeight = checkHeight(root->right);
    if (rightHeight == -1) return -1;  // Right subtree not balanced
    
    // Check if current node is balanced
    if (abs(leftHeight - rightHeight) > 1) return -1;
    
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
}
```

## 3. Path Sum

```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    
    // Leaf node
    if (root->left == nullptr && root->right == nullptr) {
        return targetSum == root->data;
    }
    
    return hasPathSum(root->left, targetSum - root->data) ||
           hasPathSum(root->right, targetSum - root->data);
}
```

## 4. Print All Paths from Root to Leaf

```cpp
void printPaths(TreeNode* root, vector<int>& path) {
    if (root == nullptr) return;
    
    path.push_back(root->data);
    
    // Leaf node - print path
    if (root->left == nullptr && root->right == nullptr) {
        for (int val : path) {
            cout << val << " ";
        }
        cout << endl;
    } else {
        printPaths(root->left, path);
        printPaths(root->right, path);
    }
    
    path.pop_back();  // Backtrack
}
```

## 5. Zigzag Level Order Traversal

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Find position to fill
            int index = leftToRight ? i : (size - 1 - i);
            level[index] = node->data;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        leftToRight = !leftToRight;
        result.push_back(level);
    }
    
    return result;
}
```

**Example:**
```
Tree:       1
           / \
          2   3
         / \   \
        4   5   6

Zigzag: [[1], [3, 2], [4, 5, 6]]
```

## 6. Vertical Order Traversal

```cpp
void getVerticalOrder(TreeNode* root, int hd, 
                      map<int, vector<int>>& m) {
    if (root == nullptr) return;
    
    m[hd].push_back(root->data);
    
    getVerticalOrder(root->left, hd - 1, m);
    getVerticalOrder(root->right, hd + 1, m);
}

void printVerticalOrder(TreeNode* root) {
    map<int, vector<int>> m;
    getVerticalOrder(root, 0, m);
    
    for (auto it : m) {
        for (int val : it.second) {
            cout << val << " ";
        }
        cout << endl;
    }
}
```

## 7. Construct Tree from Traversals

### From Inorder and Preorder

```cpp
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, 
                    int preStart, int preEnd, int inStart, int inEnd,
                    unordered_map<int, int>& inMap) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;
    
    TreeNode* root = new TreeNode(preorder[preStart]);
    int inRoot = inMap[root->data];
    int numsLeft = inRoot - inStart;
    
    root->left = buildTree(preorder, inorder, 
                           preStart + 1, preStart + numsLeft,
                           inStart, inRoot - 1, inMap);
    
    root->right = buildTree(preorder, inorder,
                            preStart + numsLeft + 1, preEnd,
                            inRoot + 1, inEnd, inMap);
    
    return root;
}
```

---

# Advanced Concepts

## 1. Morris Traversal (Inorder without Stack/Recursion)

```cpp
void morrisInorder(TreeNode* root) {
    TreeNode* current = root;
    
    while (current != nullptr) {
        if (current->left == nullptr) {
            cout << current->data << " ";
            current = current->right;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = current->left;
            while (predecessor->right != nullptr && 
                   predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                // Create thread
                predecessor->right = current;
                current = current->left;
            } else {
                // Remove thread
                predecessor->right = nullptr;
                cout << current->data << " ";
                current = current->right;
            }
        }
    }
}
```

**Space Complexity:** O(1)

## 2. Serialize and Deserialize

```cpp
class Codec {
public:
    // Serialize tree to string
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->data) + "," + 
               serialize(root->left) + "," + 
               serialize(root->right);
    }
    
    // Deserialize string to tree
    TreeNode* deserialize(string data) {
        queue<string> nodes;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            nodes.push(token);
        }
        
        return deserializeHelper(nodes);
    }
    
private:
    TreeNode* deserializeHelper(queue<string>& nodes) {
        string val = nodes.front();
        nodes.pop();
        
        if (val == "#") return nullptr;
        
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserializeHelper(nodes);
        root->right = deserializeHelper(nodes);
        
        return root;
    }
};
```

## 3. Binary Tree to Doubly Linked List

```cpp
class Solution {
    TreeNode* prev = nullptr;
    TreeNode* head = nullptr;
    
    void convert(TreeNode* root) {
        if (root == nullptr) return;
        
        convert(root->left);
        
        if (prev == nullptr) {
            head = root;  // First node
        } else {
            root->left = prev;
            prev->right = root;
        }
        prev = root;
        
        convert(root->right);
    }
    
public:
    TreeNode* treeToDoublyList(TreeNode* root) {
        if (root == nullptr) return nullptr;
        
        convert(root);
        
        // Make circular
        head->left = prev;
        prev->right = head;
        
        return head;
    }
};
```

## 4. Maximum Path Sum

```cpp
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if (root == nullptr) return 0;
    
    // Get maximum sum from left and right subtrees
    int leftSum = max(0, maxPathSumHelper(root->left, maxSum));
    int rightSum = max(0, maxPathSumHelper(root->right, maxSum));
    
    // Update global maximum (path through current node)
    maxSum = max(maxSum, leftSum + rightSum + root->data);
    
    // Return maximum path sum including current node
    return root->data + max(leftSum, rightSum);
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661
}
```

---

<<<<<<< HEAD
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
=======
# Complete C++ Implementation

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ==================== NODE STRUCTURE ====================

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ==================== BINARY TREE CLASS ====================

class BinaryTree {
private:
    TreeNode* root;

public:
    BinaryTree() : root(nullptr) {}
    
    void createRoot(int data) {
        root = new TreeNode(data);
    }
    
    TreeNode* getRoot() {
        return root;
    }
    
    TreeNode* insertLeft(TreeNode* parent, int data) {
        if (parent == nullptr) return nullptr;
        parent->left = new TreeNode(data);
        return parent->left;
    }
    
    TreeNode* insertRight(TreeNode* parent, int data) {
        if (parent == nullptr) return nullptr;
        parent->right = new TreeNode(data);
        return parent->right;
    }
    
    // ==================== TRAVERSALS ====================
    
    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    
    void preorder(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    
    void postorder(TreeNode* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
    
    void levelOrder(TreeNode* node) {
        if (node == nullptr) return;
        
        queue<TreeNode*> q;
        q.push(node);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->data << " ";
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    
    // ==================== OPERATIONS ====================
    
    int height(TreeNode* node) {
        if (node == nullptr) return -1;
        return 1 + max(height(node->left), height(node->right));
    }
    
    int countNodes(TreeNode* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    int countLeaves(TreeNode* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }
    
    int sumNodes(TreeNode* node) {
        if (node == nullptr) return 0;
        return node->data + sumNodes(node->left) + sumNodes(node->right);
    }
    
    bool search(TreeNode* node, int key) {
        if (node == nullptr) return false;
        if (node->data == key) return true;
        return search(node->left, key) || search(node->right, key);
    }
    
    int findMax(TreeNode* node) {
        if (node == nullptr) return INT_MIN;
        int maxVal = node->data;
        int leftMax = findMax(node->left);
        int rightMax = findMax(node->right);
        return max(maxVal, max(leftMax, rightMax));
    }
    
    void mirror(TreeNode* node) {
        if (node == nullptr) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }
    
    bool isIdentical(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) return true;
        if (root1 == nullptr || root2 == nullptr) return false;
        return (root1->data == root2->data) &&
               isIdentical(root1->left, root2->left) &&
               isIdentical(root1->right, root2->right);
    }
    
    // ==================== PUBLIC METHODS ====================
    
    void printInorder() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
    
    void printPreorder() {
        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }
    
    void printPostorder() {
        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }
    
    void printLevelOrder() {
        cout << "Level Order: ";
        levelOrder(root);
        cout << endl;
    }
    
    int getHeight() {
        return height(root);
    }
    
    int getTotalNodes() {
        return countNodes(root);
    }
    
    int getLeafNodes() {
        return countLeaves(root);
    }
    
    int getSum() {
        return sumNodes(root);
    }
    
    bool searchElement(int key) {
        return search(root, key);
    }
    
    int getMax() {
        return findMax(root);
    }
    
    void mirrorTree() {
        mirror(root);
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    BinaryTree tree;
    
    // Create tree:
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    
    tree.createRoot(1);
    TreeNode* root = tree.getRoot();
    
    TreeNode* node2 = tree.insertLeft(root, 2);
    TreeNode* node3 = tree.insertRight(root, 3);
    
    tree.insertLeft(node2, 4);
    tree.insertRight(node2, 5);
    tree.insertRight(node3, 6);
    
    cout << "========== TREE TRAVERSALS ==========\n";
    tree.printInorder();
    tree.printPreorder();
    tree.printPostorder();
    tree.printLevelOrder();
    
    cout << "\n========== TREE PROPERTIES ==========\n";
    cout << "Height: " << tree.getHeight() << endl;
    cout << "Total Nodes: " << tree.getTotalNodes() << endl;
    cout << "Leaf Nodes: " << tree.getLeafNodes() << endl;
    cout << "Sum of Nodes: " << tree.getSum() << endl;
    cout << "Maximum Element: " << tree.getMax() << endl;
    
    cout << "\n========== SEARCH OPERATION ==========\n";
    int searchKey = 5;
    cout << "Search for " << searchKey << ": " 
         << (tree.searchElement(searchKey) ? "Found" : "Not Found") << endl;
    
    searchKey = 10;
    cout << "Search for " << searchKey << ": " 
         << (tree.searchElement(searchKey) ? "Found" : "Not Found") << endl;
    
    cout << "\n========== MIRROR TREE ==========\n";
    cout << "Before Mirror - Inorder: ";
    tree.printInorder();
    tree.mirrorTree();
    cout << "After Mirror - Inorder: ";
    tree.printInorder();
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661
    
    return 0;
}
```

### Sample Output
```
<<<<<<< HEAD
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
=======
========== TREE TRAVERSALS ==========
Inorder: 4 2 5 1 3 6 
Preorder: 1 2 4 5 3 6 
Postorder: 4 5 2 6 3 1 
Level Order: 1 2 3 4 5 6 

========== TREE PROPERTIES ==========
Height: 2
Total Nodes: 6
Leaf Nodes: 3
Sum of Nodes: 21
Maximum Element: 6

========== SEARCH OPERATION ==========
Search for 5: Found
Search for 10: Not Found

========== MIRROR TREE ==========
Before Mirror - Inorder: 4 2 5 1 3 6 
After Mirror - Inorder: 6 3 1 5 2 4 
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661
```

---

# Practice Problems

## Easy Level
<<<<<<< HEAD
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
=======

1. **Binary Tree Traversals**
   - Implement all four traversals (Inorder, Preorder, Postorder, Level Order)

2. **Maximum Depth of Binary Tree** (LeetCode 104)
   ```cpp
   Input: [3,9,20,null,null,15,7]
   Output: 3
   ```

3. **Same Tree** (LeetCode 100)
   - Check if two trees are identical

4. **Invert Binary Tree** (LeetCode 226)
   - Mirror the binary tree

5. **Sum of Left Leaves** (LeetCode 404)
   ```cpp
   Input:     3
             / \
            9  20
              /  \
             15   7
   Output: 24 (9 + 15)
   ```

6. **Path Sum** (LeetCode 112)
   - Check if tree has root-to-leaf path with given sum

7. **Symmetric Tree** (LeetCode 101)
   - Check if tree is mirror of itself

8. **Minimum Depth of Binary Tree** (LeetCode 111)

9. **Count Complete Tree Nodes** (LeetCode 222)

10. **Binary Tree Paths** (LeetCode 257)
    - Return all root-to-leaf paths

## Medium Level

11. **Binary Tree Level Order Traversal** (LeetCode 102)
    ```cpp
    Input:     3
              / \
             9  20
               /  \
              15   7
    Output: [[3],[9,20],[15,7]]
    ```

12. **Binary Tree Zigzag Level Order** (LeetCode 103)

13. **Binary Tree Right Side View** (LeetCode 199)
    - Return values of nodes visible from right side

14. **Validate Binary Search Tree** (LeetCode 98)

15. **Construct Binary Tree from Preorder and Inorder** (LeetCode 105)

16. **Construct Binary Tree from Inorder and Postorder** (LeetCode 106)

17. **Flatten Binary Tree to Linked List** (LeetCode 114)

18. **Populating Next Right Pointers** (LeetCode 116)

19. **Sum Root to Leaf Numbers** (LeetCode 129)

20. **Binary Tree Maximum Path Sum** (LeetCode 124)

21. **Lowest Common Ancestor** (LeetCode 236)

22. **Kth Smallest Element in BST** (LeetCode 230)

23. **Count Good Nodes in Binary Tree** (LeetCode 1448)

24. **Even Odd Tree** (LeetCode 1609)

25. **Find Duplicate Subtrees** (LeetCode 652)

## Hard Level

26. **Binary Tree Maximum Path Sum** (LeetCode 124)
    ```cpp
    Input:    -10
              / \
             9  20
               /  \
              15   7
    Output: 42 (15 + 20 + 7)
    ```

27. **Serialize and Deserialize Binary Tree** (LeetCode 297)

28. **Binary Tree Cameras** (LeetCode 968)

29. **Recover Binary Search Tree** (LeetCode 99)

30. **Vertical Order Traversal** (LeetCode 987)

31. **All Nodes Distance K** (LeetCode 863)

32. **Maximum Width of Binary Tree** (LeetCode 662)

33. **Binary Tree Postorder Traversal** (Iterative) (LeetCode 145)

34. **Morris Traversal Implementation**

35. **Burn Binary Tree from Leaf**

## LeetCode Problem Links

- [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
- [100. Same Tree](https://leetcode.com/problems/same-tree/)
- [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/)
- [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)
- [105. Construct Binary Tree from Preorder and Inorder](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
- [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
- [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)
- [236. Lowest Common Ancestor](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661

---

# Key Takeaways

<<<<<<< HEAD
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
=======
## When to Use Binary Trees

✅ **Use Binary Trees when:**
- Hierarchical data representation (file systems, org charts)
- Expression parsing and evaluation
- Implementing search/sort operations
- Decision trees and game trees
- Huffman coding (data compression)
- BST for ordered data with O(log n) operations

## Complexity Summary

### Time Complexity

| Operation | Average | Worst Case |
|-----------|---------|------------|
| **Search** | O(log n) | O(n) |
| **Insert** | O(log n) | O(n) |
| **Delete** | O(log n) | O(n) |
| **Traversal** | O(n) | O(n) |
| **Height** | O(n) | O(n) |

### Space Complexity

| Operation | Space |
|-----------|-------|
| **Recursive Traversal** | O(h) - recursion stack |
| **Iterative Traversal** | O(w) - queue (w = max width) |
| **Morris Traversal** | O(1) |

Where:
- h = height of tree
- w = maximum width of tree
- n = number of nodes

## Important Patterns

### 1. Recursion Pattern
```cpp
// Base case
if (root == nullptr) return;

// Process current node
// ...

// Recurse on children
function(root->left);
function(root->right);
```

### 2. Level Order Pattern (BFS)
```cpp
queue<TreeNode*> q;
q.push(root);

while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();
    
    // Process node
    
    if (node->left) q.push(node->left);
    if (node->right) q.push(node->right);
}
```

### 3. DFS Pattern (Stack)
```cpp
stack<TreeNode*> s;
s.push(root);

while (!s.empty()) {
    TreeNode* node = s.top();
    s.pop();
    
    // Process node
    
    if (node->right) s.push(node->right);
    if (node->left) s.push(node->left);
}
```

### 4. Path Tracking Pattern
```cpp
void findPaths(TreeNode* root, vector<int>& path) {
    if (root == nullptr) return;
    
    path.push_back(root->data);
    
    if (isLeaf(root)) {
        // Process complete path
    }
    
    findPaths(root->left, path);
    findPaths(root->right, path);
    
    path.pop_back();  // Backtrack
}
```

## Common Mistakes to Avoid

❌ **Not checking for nullptr** before accessing node  
❌ **Confusing tree height and depth** (height starts from bottom)  
❌ **Memory leaks** in tree deletion  
❌ **Wrong base case** in recursion  
❌ **Not handling empty tree** edge case  
❌ **Modifying tree during traversal** without care  

## Best Practices

✅ **Always validate input** (check for null pointers)  
✅ **Use helper functions** for recursive solutions  
✅ **Draw diagrams** for complex problems  
✅ **Consider iterative solutions** to save stack space  
✅ **Think about edge cases:** empty tree, single node, skewed tree  
✅ **Use appropriate traversal** for the problem  
✅ **Clean up memory** (implement destructor)  

## Interview Tips

### Problem-Solving Strategy

1. **Understand the problem**
   - Draw the tree
   - Identify pattern (traversal, path, level, etc.)

2. **Choose approach**
   - Recursive or iterative?
   - Which traversal fits best?
   - Need extra space (queue, stack)?

3. **Handle edge cases**
   - Empty tree
   - Single node
   - Skewed tree
   - All nodes same value

4. **Optimize**
   - Can you reduce space complexity?
   - Is there a better traversal?
   - Can you combine operations?

5. **Test thoroughly**
   - Normal cases
   - Edge cases
   - Large trees

### Common Interview Questions

**Q: "Explain tree traversals"**
- Inorder: Left → Root → Right (gives sorted in BST)
- Preorder: Root → Left → Right (copy tree)
- Postorder: Left → Right → Root (delete tree)
- Level Order: Level by level (BFS)

**Q: "Difference between height and depth?"**
- **Depth:** Distance from root to node
- **Height:** Distance from node to farthest leaf

**Q: "When to use recursion vs iteration?"**
- **Recursion:** Cleaner code, natural for trees
- **Iteration:** Better space complexity, avoids stack overflow

**Q: "What's time complexity of tree traversal?"**
- **O(n)** - must visit all nodes

**Q: "Binary Tree vs Binary Search Tree?"**
- **Binary Tree:** No ordering constraint
- **BST:** Left < Root < Right (enables faster search)

---

# Comparison: Tree Types

| Type | Property | Search | Insert | Use Case |
|------|----------|--------|--------|----------|
| **Binary Tree** | Max 2 children | O(n) | O(1) | General hierarchy |
| **BST** | Ordered | O(log n)* | O(log n)* | Searching, sorting |
| **AVL Tree** | Balanced BST | O(log n) | O(log n) | Frequent searches |
| **Red-Black Tree** | Balanced BST | O(log n) | O(log n) | Frequent inserts |
| **Complete BT** | All levels filled | O(n) | O(1) | Heaps |
| **Perfect BT** | All levels full | O(n) | - | Theoretical |

*Average case; worst case O(n) for skewed tree

---

**Master Binary Trees, Master Tree Algorithms! 🌳**

## Additional Resources

- **Books:**
  - "Introduction to Algorithms" (CLRS) - Chapter on Trees
  - "Cracking the Coding Interview" - Trees and Graphs

- **Online:**
  - VisuAlgo Tree Visualization
  - LeetCode Tree Problems
  - GeeksforGeeks Binary Tree Section

- **Practice Strategy:**
  1. Master all traversals (recursive and iterative)
  2. Solve 10 easy problems
  3. Solve 15 medium problems
  4. Solve 5 hard problems
  5. Implement BST operations
  6. Learn tree construction from traversals

**Remember:** Trees are recursive structures - master recursion, master trees!
>>>>>>> e5e8482646c8756429817cc015417fbc548e6661
