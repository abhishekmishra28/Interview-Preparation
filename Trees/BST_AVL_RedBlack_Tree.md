# Binary Search Tree, AVL Tree & Red-Black Tree - Complete Guide

## Table of Contents
- [Binary Search Tree (BST)](#binary-search-tree-bst)
  - [Introduction](#bst-introduction)
  - [Problems It Resolves](#bst-problems-it-resolves)
  - [Types](#bst-types)
  - [Terminology](#bst-terminology)
  - [Implementation](#bst-implementation)
  - [Operations](#bst-operations)
  - [Properties](#bst-properties)
  - [Applications](#bst-applications)
- [AVL Tree](#avl-tree)
  - [Introduction](#avl-introduction)
  - [Problems It Resolves](#avl-problems-it-resolves)
  - [Terminology](#avl-terminology)
  - [Implementation](#avl-implementation)
  - [Operations](#avl-operations)
  - [Properties](#avl-properties)
  - [Applications](#avl-applications)
- [Red-Black Tree](#red-black-tree)
  - [Introduction](#rbt-introduction)
  - [Problems It Resolves](#rbt-problems-it-resolves)
  - [Terminology](#rbt-terminology)
  - [Implementation](#rbt-implementation)
  - [Operations](#rbt-operations)
  - [Properties](#rbt-properties)
  - [Applications](#rbt-applications)
- [Comparison](#comparison)
- [Complete C++ Implementation](#complete-cpp-implementation)

---

# Binary Search Tree (BST)

## BST Introduction

A **Binary Search Tree (BST)** is a binary tree data structure where each node follows the ordering property:
- All nodes in the **left subtree** have values **less than** the node's value
- All nodes in the **right subtree** have values **greater than** the node's value
- Both left and right subtrees are also BSTs

### Visual Representation

```
Valid BST:              Not a BST:
       8                    8
      / \                  / \
     3   10               3   10
    / \    \             / \    \
   1   6   14           1   12   14
      / \  /               / \  /
     4  7 13              4  7 13
                             (7 > 3 but in left subtree)
```

### Key Characteristics

- **Ordered Structure**: Maintains elements in sorted order
- **Fast Operations**: Search, insert, delete in O(log n) average case
- **In-order Traversal**: Gives sorted sequence
- **Dynamic**: Size can grow/shrink dynamically

## BST Problems It Resolves

### 1. **Efficient Searching**
**Problem:** Linear search in unsorted array takes O(n)  
**Solution:** BST provides O(log n) average case search

```
Array search:     [5, 2, 8, 1, 9, 3, 7] - O(n)
BST search:       Follows binary search path - O(log n)
```

### 2. **Maintaining Sorted Data**
**Problem:** Keeping data sorted after each insertion in array is O(n)  
**Solution:** BST maintains order automatically with O(log n) insertion

### 3. **Range Queries**
**Problem:** Finding all elements in a range [x, y] in unsorted data is O(n)  
**Solution:** BST can efficiently find range elements

### 4. **Dynamic Ordered Set**
**Problem:** Need ordered collection that frequently changes  
**Solution:** BST supports efficient insert/delete while maintaining order

### 5. **Finding Kth Smallest/Largest**
**Problem:** Finding kth order statistic in unsorted array requires sorting  
**Solution:** BST can find kth smallest in O(h) where h is height

## BST Types

### 1. Standard BST
Basic BST without balancing - can become skewed

```
Balanced:           Skewed (worst case):
     4                   1
    / \                   \
   2   6                   2
  / \ / \                   \
 1  3 5  7                   3
                              \
                               4
```

### 2. Self-Balancing BST
Automatically maintains balance (AVL, Red-Black Trees)

### 3. Optimal BST
BST optimized for access frequencies of keys

### 4. Threaded BST
BST with threads pointing to inorder successor/predecessor

```
Inorder Threaded BST:
     4
    / \
   2   6
  / \ / \
 1  3 5  7

1.right → 2 (thread to inorder successor)
3.right → 4 (thread)
5.right → 6 (thread)
```

## BST Terminology

| Term | Definition |
|------|------------|
| **Key** | Value stored in node used for ordering |
| **Height** | Longest path from root to leaf |
| **Depth** | Distance from root to specific node |
| **Balanced** | Height difference of subtrees ≤ 1 |
| **Skewed** | All nodes have only left or right child |
| **Successor** | Next larger element (inorder successor) |
| **Predecessor** | Next smaller element (inorder predecessor) |

## BST Implementation

### Node Structure

```cpp
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

### BST Class

```cpp
class BST {
private:
    BSTNode* root;
    
    BSTNode* insertRec(BSTNode* node, int data) {
        // Base case: found position
        if (node == nullptr) {
            return new BSTNode(data);
        }
        
        // Recursive case
        if (data < node->data) {
            node->left = insertRec(node->left, data);
        } else if (data > node->data) {
            node->right = insertRec(node->right, data);
        }
        
        return node;
    }
    
    BSTNode* searchRec(BSTNode* node, int key) {
        // Base cases
        if (node == nullptr || node->data == key) {
            return node;
        }
        
        // Key is smaller - search left
        if (key < node->data) {
            return searchRec(node->left, key);
        }
        
        // Key is larger - search right
        return searchRec(node->right, key);
    }
    
    BSTNode* deleteRec(BSTNode* node, int key) {
        if (node == nullptr) return node;
        
        // Find node to delete
        if (key < node->data) {
            node->left = deleteRec(node->left, key);
        } else if (key > node->data) {
            node->right = deleteRec(node->right, key);
        } else {
            // Node found - handle 3 cases
            
            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            
            // Case 2: One child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 3: Two children
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteRec(node->right, temp->data);
        }
        
        return node;
    }
    
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    void inorderRec(BSTNode* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int data) {
        root = insertRec(root, data);
    }
    
    bool search(int key) {
        return searchRec(root, key) != nullptr;
    }
    
    void remove(int key) {
        root = deleteRec(root, key);
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
};
```

## BST Operations

### 1. Search

```cpp
bool search(BSTNode* root, int key) {
    if (root == nullptr) return false;
    
    if (root->data == key) return true;
    
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}
```

**Time Complexity:** O(h) where h is height
- Best: O(log n) - balanced tree
- Worst: O(n) - skewed tree

**Example:**
```
Search 6 in:
       8
      / \
     3   10
    / \    \
   1   6   14

Path: 8 → 3 → 6 (found)
Comparisons: 3
```

### 2. Insertion

```cpp
BSTNode* insert(BSTNode* root, int data) {
    if (root == nullptr) {
        return new BSTNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}
```

**Example:**
```
Insert 5:
Before:          After:
    8                8
   / \              / \
  3   10           3   10
 / \    \         / \    \
1   6   14       1   6   14
                    /
                   5
```

### 3. Deletion (Three Cases)

**Case 1: Node is Leaf**
```cpp
Simply delete the node

Before:          After:
    8                8
   / \              / \
  3   10           3   10
 / \    \         /     \
1   6   14       1       14
(Delete 6)
```

**Case 2: Node has One Child**
```cpp
Replace node with its child

Before:          After:
    8                8
   / \              / \
  3   10           3   14
 /      \         /
1       14       1
(Delete 10)
```

**Case 3: Node has Two Children**
```cpp
Replace with inorder successor (or predecessor)

Before:          After:
    8                10
   / \              /  \
  3   10           3    14
 / \    \         / \
1   6   14       1   6
(Delete 8, replace with 10)
```

### 4. Find Minimum/Maximum

```cpp
BSTNode* findMin(BSTNode* root) {
    if (root == nullptr) return nullptr;
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

BSTNode* findMax(BSTNode* root) {
    if (root == nullptr) return nullptr;
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}
```

### 5. Inorder Successor/Predecessor

```cpp
BSTNode* inorderSuccessor(BSTNode* root, int key) {
    BSTNode* successor = nullptr;
    
    while (root != nullptr) {
        if (key < root->data) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return successor;
}
```

**Example:**
```
       8
      / \
     3   10
    / \    \
   1   6   14

Inorder: 1, 3, 6, 8, 10, 14
Successor of 3 = 6
Successor of 8 = 10
Predecessor of 10 = 8
```

### 6. Range Query

```cpp
void rangeQuery(BSTNode* root, int k1, int k2) {
    if (root == nullptr) return;
    
    if (k1 < root->data) {
        rangeQuery(root->left, k1, k2);
    }
    
    if (k1 <= root->data && root->data <= k2) {
        cout << root->data << " ";
    }
    
    if (k2 > root->data) {
        rangeQuery(root->right, k1, k2);
    }
}
```

## BST Properties

### 1. Ordering Property
```
For every node:
- All keys in left subtree < node's key
- All keys in right subtree > node's key
```

### 2. Inorder Traversal
```
Inorder traversal of BST gives sorted sequence

       5
      / \
     3   7
    / \   \
   1   4   9

Inorder: 1, 3, 4, 5, 7, 9 (sorted)
```

### 3. Height
```
Minimum height: ⌊log₂(n)⌋  (balanced)
Maximum height: n - 1       (skewed)
```

### 4. Number of BSTs
```
For n distinct keys:
Number of different BSTs = Catalan number C(n)
C(n) = (2n)! / ((n+1)! × n!)

Examples:
n=1: 1 BST
n=2: 2 BSTs
n=3: 5 BSTs
n=4: 14 BSTs
```

### 5. Time Complexities

| Operation | Average | Worst |
|-----------|---------|-------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Find Min/Max | O(log n) | O(n) |
| Inorder | O(n) | O(n) |

### 6. Space Complexity
```
Space: O(n) for storing n nodes
Recursion stack: O(h) where h is height
```

## BST Applications

### 1. **Databases & Indexing**
- Database indexing for faster queries
- B-trees and B+ trees (variants of BST)
- File system organization

### 2. **Dictionaries & Symbol Tables**
- Compiler symbol tables
- Spell checkers
- Router tables in networks

### 3. **Priority Queues**
- Job scheduling
- Bandwidth management
- Event simulation systems

### 4. **Autocomplete Systems**
- Search suggestions
- Command completion
- Text prediction

### 5. **Range Queries**
- Finding elements in a range
- SQL WHERE clauses
- Geographic information systems

### 6. **Sorting**
- BST can sort elements (insert all, then inorder)
- Used in some sorting algorithms

### 7. **Expression Parsing**
- Expression trees
- Parse trees in compilers

---

# AVL Tree

## AVL Introduction

An **AVL Tree** (Adelson-Velsky and Landis Tree) is a **self-balancing Binary Search Tree** where the difference between heights of left and right subtrees (balance factor) cannot be more than 1 for all nodes.

### Balance Factor
```
Balance Factor = Height(Left Subtree) - Height(Right Subtree)

Balance Factor ∈ {-1, 0, 1}
```

### Visual Representation

```
Valid AVL Tree:          Not AVL (unbalanced):
       30                      30
      /  \                    /
     20   40                 20
    /  \    \               /
   10  25   50             10
                          /
                         5
BF at 30: 1-1 = 0       BF at 30: 2-0 = 2 ✗
```

### Key Characteristics

- **Always Balanced**: Height difference ≤ 1
- **Guaranteed O(log n)**: All operations
- **More Rotations**: Than Red-Black trees
- **Faster Lookups**: Better balanced than RBT

## AVL Problems It Resolves

### 1. **BST Worst Case Performance**
**Problem:** BST can degenerate to O(n) for skewed tree  
**Solution:** AVL maintains O(log n) by staying balanced

```
Skewed BST:        AVL Tree:
    1                 3
     \               / \
      2             2   5
       \           /     \
        3         1       7
         \
          4
           \
            5
             \
              7

Height: 6         Height: 3
```

### 2. **Predictable Performance**
**Problem:** BST performance depends on insertion order  
**Solution:** AVL guarantees O(log n) regardless of order

### 3. **Frequent Lookups**
**Problem:** Applications with many searches need fast access  
**Solution:** AVL is more strictly balanced, faster searches

## AVL Terminology

| Term | Definition |
|------|------------|
| **Balance Factor** | Height(left) - Height(right) |
| **Height** | Stored in each node for efficiency |
| **Rotation** | Operation to restore balance |
| **LL Rotation** | Right rotation for left-left case |
| **RR Rotation** | Left rotation for right-right case |
| **LR Rotation** | Left then right for left-right case |
| **RL Rotation** | Right then left for right-left case |

## AVL Implementation

### Node Structure

```cpp
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) : data(val), left(nullptr), 
                       right(nullptr), height(1) {}
};
```

### AVL Tree Class

```cpp
class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insert(AVLNode* node, int key) {
        // 1. Perform normal BST insertion
        if (node == nullptr) {
            return new AVLNode(key);
        }
        
        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node;  // Duplicate keys not allowed
        }
        
        // 2. Update height
        node->height = 1 + max(height(node->left), height(node->right));
        
        // 3. Get balance factor
        int balance = getBalance(node);
        
        // 4. Balance the node if needed
        
        // Left Left Case
        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inorderRec(AVLNode* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
};
```

## AVL Operations

### 1. Rotations

#### Right Rotation (LL Case)

```
Before:              After:
    y                  x
   / \                / \
  x   T3             T1  y
 / \                    / \
T1  T2                 T2  T3

Code:
x = y->left
T2 = x->right
x->right = y
y->left = T2
```

#### Left Rotation (RR Case)

```
Before:              After:
  x                    y
 / \                  / \
T1  y                x   T3
   / \              / \
  T2  T3           T1  T2

Code:
y = x->right
T2 = y->left
y->left = x
x->right = T2
```

#### Left-Right Rotation (LR Case)

```
Step 1: Left rotate on left child
Step 2: Right rotate on root

Before:       Step 1:        After:
    z            z              y
   / \          / \            / \
  x   T4       y   T4         x   z
 / \          / \            / \ / \
T1  y        x  T3          T1 T2 T3 T4
   / \      / \
  T2  T3   T1 T2
```

#### Right-Left Rotation (RL Case)

```
Step 1: Right rotate on right child
Step 2: Left rotate on root

Before:       Step 1:        After:
  z              z              y
 / \            / \            / \
T1  x          T1  y          z   x
   / \            / \        / \ / \
  y   T4         T2  x      T1 T2 T3 T4
 / \                / \
T2  T3             T3  T4
```

### 2. Insertion with Balancing

```cpp
Insert 10, 20, 30:

After 10:       After 20:       After 30 (unbalanced):
   10              10                  10
                    \                   \
                    20                  20
                                         \
                                         30
                    BF = -2 at 10 (RR case)
                    
After Left Rotation:
       20
      /  \
    10    30
```

### 3. Deletion with Balancing

```cpp
AVLNode* deleteNode(AVLNode* root, int key) {
    // 1. Perform standard BST delete
    if (root == nullptr) return root;
    
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            // Node with two children
            AVLNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    if (root == nullptr) return root;
    
    // 2. Update height
    root->height = 1 + max(height(root->left), height(root->right));
    
    // 3. Check balance and rotate if needed
    int balance = getBalance(root);
    
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}
```

## AVL Properties

### 1. Balance Factor Property
```
For every node:
Balance Factor ∈ {-1, 0, 1}

If BF > 1 or BF < -1: Tree needs rebalancing
```

### 2. Height Property
```
For AVL tree with n nodes:
Minimum height = ⌊log₂(n)⌋
Maximum height ≈ 1.44 × log₂(n)

Proof: Fibonacci relationship
AVL(h) >= Fib(h+3) - 1
```

### 3. Rotation Count
```
Insert: At most 2 rotations (one double rotation)
Delete: At most O(log n) rotations
```

### 4. Time Complexities

| Operation | Time Complexity |
|-----------|----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |
| Find Min/Max | O(log n) |

### 5. Space Complexity
```
Space: O(n) for storing n nodes + heights
Extra per node: O(1) for height field
```

## AVL Applications

### 1. **In-Memory Databases**
- Indexes for frequently searched data
- Better search performance than RBT

### 2. **File Systems**
- Directory structures
- Fast file lookup

### 3. **Real-Time Applications**
- Systems requiring predictable latency
- Hard real-time constraints

### 4. **Graphics & CAD**
- 2D range trees
- Computational geometry

### 5. **Network Routers**
- IP routing tables
- Fast packet forwarding

### 6. **Game Development**
- Spatial partitioning
- Collision detection systems

---

# Red-Black Tree

## RBT Introduction

A **Red-Black Tree** is a self-balancing BST where each node has an extra bit for color (red or black). It maintains balance through coloring rules and rotations, ensuring O(log n) time for operations.

### Visualization

```
Valid Red-Black Tree:

        B:11
       /    \
     R:2    B:14
    /  \      \
  B:1  B:7   R:15

B = Black, R = Red
```

### Key Characteristics

- **Relaxed Balancing**: Less strict than AVL
- **Fewer Rotations**: Better for insert-heavy workloads
- **Color Property**: Extra bit per node
- **Used Widely**: C++ STL map, Java TreeMap

## RBT Problems It Resolves

### 1. **AVL's Excessive Rebalancing**
**Problem:** AVL requires many rotations on insertion/deletion  
**Solution:** RBT requires at most 2 rotations for insertion

### 2. **Write-Heavy Workloads**
**Problem:** AVL slower for frequent inserts/deletes  
**Solution:** RBT optimized for modifications

### 3. **Memory vs Performance Trade-off**
**Problem:** Need balance between search and update speed  
**Solution:** RBT provides good compromise

## RBT Terminology

| Term | Definition |
|------|------------|
| **Red Node** | Node colored red |
| **Black Node** | Node colored black |
| **Black Height** | Number of black nodes from node to leaf |
| **NIL Node** | Null children (considered black) |
| **Double Black** | Temporary state during deletion |
| **Uncle** | Sibling of parent node |

## RBT Implementation

### Node Structure

```cpp
enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    
    RBNode(int val) : data(val), color(RED), 
                      left(nullptr), right(nullptr), parent(nullptr) {}
};
```

### Red-Black Tree Class

```cpp
class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;  // Sentinel node
    
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        
        if (y->left != NIL) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        
        if (x->right != NIL) {
            x->right->parent = y;
        }
        
        x->parent = y->parent;
        
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        
        x->right = y;
        y->parent = x;
    }
    
    void insertFixup(RBNode* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right;  // Uncle
                
                if (y && y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: z is right child
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left;  // Uncle
                
                if (y && y->color == RED) {
                    // Case 1: Uncle is red
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        // Case 2: z is left child
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3: z is right child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void insert(RBNode* z) {
        RBNode* y = nullptr;
        RBNode* x = root;
        
        // Find position for new node
        while (x != NIL && x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        z->parent = y;
        
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        
        z->left = NIL;
        z->right = NIL;
        z->color = RED;
        
        insertFixup(z);
    }
    
    void inorderRec(RBNode* node) {
        if (node == NIL || node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderRec(node->right);
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        root = NIL;
    }
    
    void insert(int data) {
        RBNode* node = new RBNode(data);
        insert(node);
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
};
```

## RBT Operations

### 1. Insertion Cases

#### Case 1: Uncle is Red

```
Before:                 After:
     B:g                  R:g
    /   \                /   \
  R:p   R:u    →       B:p   B:u
  /                    /
R:z                  R:z

Action: Recolor parent and uncle to black, grandparent to red
```

#### Case 2: Uncle is Black (Triangle)

```
Before:                 After:
     B:g                  B:g
    /   \                /   \
  R:p   B:u    →       R:z   B:u
    \                  /
    R:z              R:p

Action: Left rotate on parent, then apply Case 3
```

#### Case 3: Uncle is Black (Line)

```
Before:                 After:
     B:g                  B:p
    /   \                /   \
  R:p   B:u    →       R:z   R:g
  /                            \
R:z                            B:u

Action: Right rotate on grandparent, recolor
```

### 2. Complete Insertion Example

```cpp
Insert: 10, 20, 30, 15

Step 1: Insert 10
    B:10

Step 2: Insert 20
    B:10
      \
      R:20

Step 3: Insert 30 (violation!)
    B:10           After rebalance:
      \                 B:20
      R:20        →    /    \
        \            R:10   R:30
        R:30

Step 4: Insert 15
    B:20                After fixing:
   /    \                   B:20
 R:10   R:30          →    /    \
   \                     B:15   B:30
   R:15                  /
                       R:10
```

### 3. Deletion (Complex)

```cpp
void deleteFixup(RBNode* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;  // Sibling
            
            // Case 1: Sibling is red
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            
            // Case 2: Sibling's children are black
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                // Case 3: Sibling's right child is black
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4: Sibling's right child is red
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            // Mirror cases for right child
            // ... (symmetric to above)
        }
    }
    x->color = BLACK;
}
```

### 4. Search (Same as BST)

```cpp
RBNode* search(RBNode* node, int key) {
    if (node == NIL || node == nullptr || node->data == key) {
        return node;
    }
    
    if (key < node->data) {
        return search(node->left, key);
    }
    return search(node->right, key);
}
```

## RBT Properties

### 1. Five Red-Black Properties

```
Property 1: Every node is either red or black
Property 2: Root is always black
Property 3: All leaves (NIL) are black
Property 4: Red nodes have black children (no two red nodes in a row)
Property 5: All paths from node to descendant leaves contain 
            same number of black nodes (black height)
```

### 2. Black Height

```
Black Height: Number of black nodes on path to leaf (excluding node itself)

Example:
        B:7 (bh=2)
       /    \
     R:3    B:18 (bh=1)
    /  \    /   \
  B:1 B:5 B:12 B:20 (bh=0)

All paths have 2 black nodes (excluding root)
```

### 3. Height Bound

```
For Red-Black tree with n nodes:
Height h ≤ 2 × log₂(n + 1)

Proof:
- Shortest path has only black nodes
- Longest path alternates red and black
- Longest path ≤ 2 × shortest path (Property 4)
- Therefore: h ≤ 2 × log₂(n + 1)
```

### 4. Rotation and Recoloring

```
Insertion:
- At most 2 rotations
- O(log n) recolorings

Deletion:
- At most 3 rotations
- O(log n) recolorings
```

### 5. Time Complexities

| Operation | Time Complexity |
|-----------|----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |
| Min/Max | O(log n) |

### 6. Space Complexity

```
Space: O(n) for n nodes
Extra per node: 1 bit for color
Parent pointer: Optional but recommended
```

## RBT Applications

### 1. **Standard Template Libraries**
- C++ STL: `map`, `set`, `multimap`, `multiset`
- Java: `TreeMap`, `TreeSet`
- Linux Kernel: Process scheduling (CFS)

### 2. **Database Systems**
- MySQL: Index structures
- PostgreSQL: GIN indexes
- In-memory databases

### 3. **Operating Systems**
- Linux: Virtual memory management
- Process scheduling
- File system structures

### 4. **Computational Geometry**
- Sweep line algorithms
- Range trees
- Segment trees

### 5. **Network Applications**
- Packet scheduling
- QoS (Quality of Service) management
- Route tables

### 6. **Compilers**
- Symbol tables
- Syntax tree balancing
- Optimization passes

---

# Comparison

## BST vs AVL vs Red-Black Tree

### Feature Comparison

| Feature | BST | AVL Tree | Red-Black Tree |
|---------|-----|----------|----------------|
| **Balancing** | None | Strict | Relaxed |
| **Height** | O(n) worst | ≈ 1.44 log n | ≈ 2 log n |
| **Search** | O(n) worst | O(log n) | O(log n) |
| **Insert** | O(n) worst | O(log n) | O(log n) |
| **Delete** | O(n) worst | O(log n) | O(log n) |
| **Rotations (Insert)** | 0 | ≤ 2 | ≤ 2 |
| **Rotations (Delete)** | 0 | O(log n) | ≤ 3 |
| **Extra Space** | None | 1 int (height) | 1 bit (color) |
| **Best For** | Simple use | Frequent searches | Frequent updates |

### Performance Comparison

```
Search Performance:
AVL > Red-Black > BST

Insert Performance:
Red-Black > AVL > BST

Delete Performance:
Red-Black > AVL > BST

Memory Usage:
BST < Red-Black < AVL
```

### Balance Factor

```
BST:
Balance Factor: Can be anything
Example: Linear chain (height = n)

AVL:
Balance Factor: {-1, 0, 1}
Example:     4
           /   \
          2     6
         / \   / \
        1   3 5   7

Red-Black:
Balance Factor: Not explicitly tracked
Height constraint: h ≤ 2 log(n+1)
```

### Use Case Recommendations

```
Choose BST when:
✓ Simple implementation needed
✓ Data is mostly random
✓ Small dataset
✓ Memory is very limited

Choose AVL when:
✓ Search-intensive applications
✓ Read >> Write operations
✓ Need strictly balanced tree
✓ Predictable performance critical

Choose Red-Black when:
✓ Balanced read/write operations
✓ Insert/delete heavy workload
✓ Standard library implementations
✓ Operating system internals
```

### Real-World Usage

```
BST:
- Educational purposes
- Simple applications
- Prototyping

AVL:
- In-memory databases
- Look-up intensive apps
- Windows NT kernel

Red-Black:
- C++ STL (map, set)
- Java Collections (TreeMap)
- Linux kernel (CFS scheduler)
- Most production systems
```

---

# Complete C++ Implementation

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// ==================== BST IMPLEMENTATION ====================

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    
    BSTNode* insertRec(BSTNode* node, int data) {
        if (node == nullptr) return new BSTNode(data);
        
        if (data < node->data) {
            node->left = insertRec(node->left, data);
        } else if (data > node->data) {
            node->right = insertRec(node->right, data);
        }
        return node;
    }
    
    BSTNode* searchRec(BSTNode* node, int key) {
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return searchRec(node->left, key);
        return searchRec(node->right, key);
    }
    
    void inorderRec(BSTNode* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

public:
    BST() : root(nullptr) {}
    
    void insert(int data) {
        root = insertRec(root, data);
    }
    
    bool search(int key) {
        return searchRec(root, key) != nullptr;
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
};

// ==================== AVL TREE IMPLEMENTATION ====================

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insert(AVLNode* node, int key) {
        if (node == nullptr) return new AVLNode(key);
        
        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inorderRec(AVLNode* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
    
    int getHeight() {
        return height(root);
    }
};

// ==================== RED-BLACK TREE IMPLEMENTATION ====================

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    
    RBNode(int val) : data(val), color(RED), 
                      left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;
    
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        
        if (y->left != NIL) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        y->left = x->right;
        
        if (x->right != NIL) {
            x->right->parent = y;
        }
        
        x->parent = y->parent;
        
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        
        x->right = y;
        y->parent = x;
    }
    
    void insertFixup(RBNode* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right;
                
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left;
                
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void insert(RBNode* z) {
        RBNode* y = nullptr;
        RBNode* x = root;
        
        while (x != NIL && x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        z->parent = y;
        
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        
        z->left = NIL;
        z->right = NIL;
        z->color = RED;
        
        insertFixup(z);
    }
    
    void inorderRec(RBNode* node) {
        if (node == NIL || node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderRec(node->right);
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        root = NIL;
    }
    
    void insert(int data) {
        RBNode* node = new RBNode(data);
        insert(node);
    }
    
    void inorder() {
        inorderRec(root);
        cout << endl;
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "========== BINARY SEARCH TREE ==========\n";
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    cout << "BST Inorder: ";
    bst.inorder();
    
    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 25: " << (bst.search(25) ? "Found" : "Not Found") << endl;
    
    cout << "\n========== AVL TREE ==========\n";
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    
    cout << "AVL Inorder: ";
    avl.inorder();
    cout << "AVL Height: " << avl.getHeight() << endl;
    
    cout << "\n========== RED-BLACK TREE ==========\n";
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(5);
    
    cout << "RBT Inorder (with colors): ";
    rbt.inorder();
    
    return 0;
}
```

### Sample Output

```
========== BINARY SEARCH TREE ==========
BST Inorder: 20 30 40 50 60 70 80 
Search 40: Found
Search 25: Not Found

========== AVL TREE ==========
AVL Inorder: 10 20 25 30 40 50 
AVL Height: 3

========== RED-BLACK TREE ==========
RBT Inorder (with colors): 5(R) 10(B) 15(R) 20(B) 25(R) 30(B) 
```

---

**Master Balanced Trees, Master Efficient Data Structures! 🌳**

## Key Takeaways

### When to Use Which?

**Use BST when:**
- Learning tree concepts
- Simple, small applications
- Data is randomly ordered
- Memory is extremely limited

**Use AVL Tree when:**
- Search operations dominate (90%+ searches)
- Need predictable O(log n) performance
- Read-heavy applications
- Strict balance is required

**Use Red-Black Tree when:**
- Balanced read/write operations
- Insert/delete operations are frequent
- Using standard libraries (already implemented)
- Operating system level programming
- General-purpose balanced tree needed

**Remember:** In practice, most production systems use Red-Black Trees (C++ STL, Java Collections) due to their excellent balance between performance and implementation complexity!
