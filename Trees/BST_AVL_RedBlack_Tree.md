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
                        z = z->
