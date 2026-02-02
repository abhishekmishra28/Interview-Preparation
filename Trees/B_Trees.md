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
- [Complete C++ Implementation](#complete-cpp-implementation)
- [Practice Problems](#practice-problems)

---

# Introduction

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

---

# Implementation

## Node Structure

```cpp
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
}
```

---

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
            TreeNode* curr = q.front();
            q.pop();

            cout << curr->data << " ";

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    BinaryTree tree;

    // Create the tree:
    //           1
    //          / \
    //         2   3
    //        / \
    //       4   5

    tree.createRoot(1);
    TreeNode* root = tree.getRoot();

    TreeNode* node2 = tree.insertLeft(root, 2);
    TreeNode* node3 = tree.insertRight(root, 3);

    tree.insertLeft(node2, 4);
    tree.insertRight(node2, 5);

    cout << "Inorder Traversal: ";
    tree.inorder(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    tree.preorder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    tree.postorder(root);
    cout << endl;

    cout << "Level Order Traversal: ";
    tree.levelOrder(root);
    cout << endl;

    return 0;
}
```
