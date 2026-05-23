# 🌳 Tree Data Structure — Complete Interview Questions Guide

> From **Scratch to Advanced** | Binary Trees, BSTs, N-ary Trees & More  
> With Follow-up Questions & Answers | Ideal for FAANG / Product-Based Interviews

---

## 📚 Table of Contents

1. [Basics & Fundamentals](#1-basics--fundamentals)
2. [Binary Tree Traversals](#2-binary-tree-traversals)
3. [Binary Tree Properties & Construction](#3-binary-tree-properties--construction)
4. [Binary Search Tree (BST)](#4-binary-search-tree-bst)
5. [Balanced Trees (AVL, Red-Black)](#5-balanced-trees)
6. [Heaps & Priority Queues](#6-heaps--priority-queues)
7. [Tries (Prefix Trees)](#7-tries-prefix-trees)
8. [Segment Trees & Fenwick Trees](#8-segment-trees--fenwick-trees)
9. [N-ary Trees](#9-n-ary-trees)
10. [Tree DP & Advanced Problems](#10-tree-dp--advanced-problems)
11. [Classic Coding Problems](#11-classic-coding-problems)
12. [System Design with Trees](#12-system-design-with-trees)

---

## 1. Basics & Fundamentals

---

### Q1. What is a Tree? Define its key terminology.

**Answer:**

A **Tree** is a hierarchical, non-linear data structure consisting of nodes connected by edges, with **no cycles**.

```
          1          ← Root
        /   \
       2     3       ← Internal nodes
      / \     \
     4   5     6     ← Leaf nodes (no children)
        / \
       7   8
```

**Key Terminology:**

| Term | Definition |
|---|---|
| **Root** | The topmost node; has no parent |
| **Leaf** | A node with no children |
| **Internal Node** | A node with at least one child |
| **Height of Node** | Longest path from node to a leaf |
| **Depth of Node** | Distance from root to the node |
| **Height of Tree** | Height of the root node |
| **Degree of Node** | Number of children of a node |
| **Subtree** | A node and all its descendants |
| **Ancestor** | Any node on path from root to a node |
| **Descendant** | Any node in a node's subtree |
| **Level** | Depth + 1 (root is level 1) |
| **Edge** | Connection between parent and child |
| **Path** | Sequence of nodes from one to another |
| **Sibling** | Nodes sharing the same parent |

> **Follow-up:** What is the difference between height and depth of a tree?  
> **Answer:** **Depth** is measured **top-down** — the distance from the root to a given node (root has depth 0). **Height** is measured **bottom-up** — the longest path from a node to a leaf (leaf has height 0). The height of the tree equals the height of its root.

---

### Q2. What are the properties of a Binary Tree?

**Answer:**

A **Binary Tree** is a tree where every node has **at most 2 children** (left and right).

**Structural properties:**
- Max nodes at level `L` = `2^L` (root is level 0)
- Max nodes in a tree of height `h` = `2^(h+1) - 1`
- Min height for `n` nodes = `⌊log₂(n)⌋`
- A tree with `n` internal nodes has `n+1` leaf nodes (for full binary trees)

**Types of Binary Trees:**

| Type | Definition |
|---|---|
| **Full** | Every node has 0 or 2 children |
| **Complete** | All levels filled except possibly last; last level filled left to right |
| **Perfect** | All internal nodes have 2 children; all leaves at same level |
| **Balanced** | Height difference between left and right subtrees ≤ 1 for every node |
| **Degenerate (Skewed)** | Every node has only one child (becomes a linked list) |

```
Full:          Perfect:       Complete:      Skewed:
    1              1              1              1
   / \           /   \          / \              \
  2   3         2     3        2   3               2
 / \           / \ / \        / \                   \
4   5         4  5 6  7      4   5                   3
```

> **Follow-up:** What is the relationship between a Perfect and Complete binary tree?  
> **Answer:** Every perfect binary tree is complete, but not every complete binary tree is perfect. A perfect tree has all leaves at the same level, while a complete tree only requires the last level to be filled left to right.

---

### Q3. How do you represent a Binary Tree in code?

**Answer:**

#### Node-based (most common):

```python
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Build:  1
#        / \
#       2   3
root = TreeNode(1)
root.left = TreeNode(2)
root.right = TreeNode(3)
```

#### Array-based (for complete/heap trees):

```python
# For node at index i:
# Left child  → 2*i + 1
# Right child → 2*i + 2
# Parent      → (i - 1) // 2

tree = [1, 2, 3, 4, 5, 6, 7]
#       0  1  2  3  4  5  6
# Node 1 (index 1): parent = 0, left = 3, right = 4
```

> **Follow-up:** When would you prefer array representation over node-based?  
> **Answer:** Array representation is preferred for **complete binary trees** (like heaps) because there's no wasted space and the parent/child index formulas give O(1) access. For general trees with gaps or non-complete structure, node-based is more memory-efficient.

---

## 2. Binary Tree Traversals

---

### Q4. Explain all four tree traversals with code and output.

**Answer:**

```
Tree:
      1
     / \
    2   3
   / \
  4   5
```

#### ✅ Inorder (Left → Root → Right) → `4 2 5 1 3`

```python
def inorder(root):
    if not root:
        return []
    return inorder(root.left) + [root.val] + inorder(root.right)

# Iterative:
def inorder_iterative(root):
    result, stack = [], []
    curr = root
    while curr or stack:
        while curr:
            stack.append(curr)
            curr = curr.left
        curr = stack.pop()
        result.append(curr.val)
        curr = curr.right
    return result
```

#### ✅ Preorder (Root → Left → Right) → `1 2 4 5 3`

```python
def preorder(root):
    if not root:
        return []
    return [root.val] + preorder(root.left) + preorder(root.right)

# Iterative:
def preorder_iterative(root):
    if not root:
        return []
    result, stack = [], [root]
    while stack:
        node = stack.pop()
        result.append(node.val)
        if node.right: stack.append(node.right)  # Right first (LIFO)
        if node.left:  stack.append(node.left)
    return result
```

#### ✅ Postorder (Left → Right → Root) → `4 5 2 3 1`

```python
def postorder(root):
    if not root:
        return []
    return postorder(root.left) + postorder(root.right) + [root.val]

# Iterative (reverse preorder trick):
def postorder_iterative(root):
    if not root:
        return []
    result, stack = [], [root]
    while stack:
        node = stack.pop()
        result.append(node.val)
        if node.left:  stack.append(node.left)
        if node.right: stack.append(node.right)
    return result[::-1]  # Reverse at end
```

#### ✅ Level Order / BFS → `[[1], [2, 3], [4, 5]]`

```python
from collections import deque

def level_order(root):
    if not root:
        return []
    result = []
    queue = deque([root])
    while queue:
        level = []
        for _ in range(len(queue)):   # Process one level at a time
            node = queue.popleft()
            level.append(node.val)
            if node.left:  queue.append(node.left)
            if node.right: queue.append(node.right)
        result.append(level)
    return result

# Time: O(N)  |  Space: O(N) — max queue size = widest level
```

> **Follow-up:** For a BST, which traversal gives sorted output?  
> **Answer:** **Inorder traversal** (Left → Root → Right) of a BST always produces nodes in **ascending sorted order**. This is a fundamental property used in many BST problems.

> **Follow-up:** Can you reconstruct a tree from just inorder traversal?  
> **Answer:** No. Inorder alone is insufficient — you need either **preorder + inorder** or **postorder + inorder** to uniquely reconstruct a binary tree (assuming no duplicates).

---

### Q5. What is Morris Traversal? Why is it significant?

**Answer:**

Morris Traversal performs inorder/preorder traversal in **O(N) time and O(1) space** (no stack, no recursion) by temporarily modifying the tree using **threaded binary tree** concept.

```python
def morris_inorder(root):
    result = []
    curr = root
    
    while curr:
        if not curr.left:
            result.append(curr.val)
            curr = curr.right
        else:
            # Find inorder predecessor
            predecessor = curr.left
            while predecessor.right and predecessor.right != curr:
                predecessor = predecessor.right
            
            if not predecessor.right:
                # Make thread: link predecessor's right to curr
                predecessor.right = curr
                curr = curr.left
            else:
                # Thread already exists: remove it, visit curr
                predecessor.right = None
                result.append(curr.val)
                curr = curr.right
    
    return result

# Time: O(N)  |  Space: O(1) ← key advantage
```

> **Follow-up:** Why is Morris Traversal O(N) despite the inner while loop?  
> **Answer:** Each node is visited at most twice (once to set the thread, once to remove it). The total work across all inner while loops is bounded by the number of edges = O(N). So the overall complexity remains O(N).

---

## 3. Binary Tree Properties & Construction

---

### Q6. How do you find the height/depth of a binary tree?

**Answer:**

```python
# Height (recursive)
def height(root):
    if not root:
        return -1   # or 0, depending on convention
    return 1 + max(height(root.left), height(root.right))

# Height (iterative BFS - count levels)
def height_bfs(root):
    if not root:
        return -1
    queue = deque([root])
    h = -1
    while queue:
        h += 1
        for _ in range(len(queue)):
            node = queue.popleft()
            if node.left:  queue.append(node.left)
            if node.right: queue.append(node.right)
    return h

# Time: O(N)  |  Space: O(N)
```

> **Follow-up:** What is the height of a single-node tree?  
> **Answer:** By convention, a single node (leaf) has height **0** (no edges below it). An empty tree has height **-1**. Some definitions use "number of nodes on longest path," giving a single node height of 1 — clarify the convention in interviews.

---

### Q7. How do you reconstruct a binary tree from traversals?

**Answer:**

#### From Preorder + Inorder:

```python
def build_from_pre_in(preorder, inorder):
    if not preorder or not inorder:
        return None
    
    root_val = preorder[0]
    root = TreeNode(root_val)
    mid = inorder.index(root_val)
    
    root.left  = build_from_pre_in(preorder[1:mid+1], inorder[:mid])
    root.right = build_from_pre_in(preorder[mid+1:],  inorder[mid+1:])
    
    return root

# Optimized with hashmap (O(N)):
def build_optimized(preorder, inorder):
    idx_map = {val: i for i, val in enumerate(inorder)}
    pre_idx = [0]
    
    def build(left, right):
        if left > right:
            return None
        root_val = preorder[pre_idx[0]]
        pre_idx[0] += 1
        root = TreeNode(root_val)
        mid = idx_map[root_val]
        root.left  = build(left, mid - 1)
        root.right = build(mid + 1, right)
        return root
    
    return build(0, len(inorder) - 1)

# Time: O(N)  |  Space: O(N)
```

#### From Postorder + Inorder:

```python
def build_from_post_in(postorder, inorder):
    if not postorder:
        return None
    root_val = postorder[-1]
    root = TreeNode(root_val)
    mid = inorder.index(root_val)
    root.left  = build_from_post_in(postorder[:mid],  inorder[:mid])
    root.right = build_from_post_in(postorder[mid:-1], inorder[mid+1:])
    return root
```

> **Follow-up:** Can you reconstruct a tree from preorder + postorder?  
> **Answer:** Not uniquely — unless it's a **full binary tree** (every node has 0 or 2 children). With preorder + postorder alone, there's ambiguity about which subtree is left vs right when a node has only one child.

---

### Q8. How do you check if two trees are identical / symmetric / mirror?

**Answer:**

```python
# Identical trees
def is_same(p, q):
    if not p and not q: return True
    if not p or not q:  return False
    return (p.val == q.val and
            is_same(p.left, q.left) and
            is_same(p.right, q.right))

# Symmetric tree (mirror of itself)
def is_symmetric(root):
    def is_mirror(left, right):
        if not left and not right: return True
        if not left or not right:  return False
        return (left.val == right.val and
                is_mirror(left.left,  right.right) and
                is_mirror(left.right, right.left))
    return is_mirror(root.left, root.right) if root else True

# Mirror of a tree (in-place)
def mirror(root):
    if not root:
        return
    root.left, root.right = root.right, root.left
    mirror(root.left)
    mirror(root.right)

# Time: O(N)  |  Space: O(H) — H = height
```

---

### Q9. How do you find the Lowest Common Ancestor (LCA)?

**Answer:**

```python
# LCA in a Binary Tree (not BST)
def lca(root, p, q):
    if not root or root == p or root == q:
        return root
    
    left  = lca(root.left,  p, q)
    right = lca(root.right, p, q)
    
    # If both sides return non-null, root is LCA
    if left and right:
        return root
    return left or right   # Return whichever found something

# Time: O(N)  |  Space: O(H)
```

```
Example:
       3
      / \
     5   1
    / \ / \
   6  2 0  8
     / \
    7   4

LCA(5, 1) = 3
LCA(5, 4) = 5  (5 is ancestor of 4)
LCA(6, 4) = 5
```

> **Follow-up:** How does LCA differ in a BST vs a generic binary tree?  
> **Answer:** In a **BST**, you can use the BST property: if both p and q are less than root, go left; if both are greater, go right; otherwise, root is the LCA. This runs in O(H) time and O(1) space (no recursion stack needed iteratively), whereas the generic approach requires O(N) time.

```python
# LCA in BST (faster)
def lca_bst(root, p, q):
    while root:
        if p.val < root.val and q.val < root.val:
            root = root.left
        elif p.val > root.val and q.val > root.val:
            root = root.right
        else:
            return root
```

---

### Q10. What is Diameter of a Binary Tree?

**Answer:**

The diameter is the **longest path between any two nodes** (may or may not pass through the root).

```python
def diameter(root):
    max_diameter = [0]
    
    def height(node):
        if not node:
            return 0
        left_h  = height(node.left)
        right_h = height(node.right)
        # Diameter through this node = left height + right height
        max_diameter[0] = max(max_diameter[0], left_h + right_h)
        return 1 + max(left_h, right_h)
    
    height(root)
    return max_diameter[0]

# Time: O(N)  |  Space: O(H)
```

> **Follow-up:** Why can't we just compute `height(left) + height(right)` at root?  
> **Answer:** The longest path might not pass through the root. Consider a tree where the left subtree itself contains a very deep, wide path. We must check every node as a potential "turning point" of the diameter path.

---

## 4. Binary Search Tree (BST)

---

### Q11. What are BST properties? How do you validate one?

**Answer:**

**BST Properties:**
- Left subtree contains only nodes with values **less than** the node
- Right subtree contains only nodes with values **greater than** the node
- Both subtrees are also valid BSTs
- Inorder traversal gives **sorted ascending** sequence

```python
# Validate BST
def is_valid_bst(root, min_val=float('-inf'), max_val=float('inf')):
    if not root:
        return True
    if not (min_val < root.val < max_val):
        return False
    return (is_valid_bst(root.left,  min_val, root.val) and
            is_valid_bst(root.right, root.val, max_val))

# Time: O(N)  |  Space: O(H)
```

> **Follow-up:** What's wrong with just checking `node.val > node.left.val and node.val < node.right.val`?  
> **Answer:** This only checks the immediate children, not the entire subtree constraint. Example: a node with value 10, left child 5, and left child's right child 15 would pass the local check but fail BST validity (15 > 10 but is in the left subtree).

---

### Q12. Implement BST Insert, Search, and Delete.

**Answer:**

```python
# Insert
def insert(root, val):
    if not root:
        return TreeNode(val)
    if val < root.val:
        root.left  = insert(root.left,  val)
    elif val > root.val:
        root.right = insert(root.right, val)
    return root   # val == root.val: no duplicate

# Search
def search(root, val):
    if not root or root.val == val:
        return root
    if val < root.val:
        return search(root.left,  val)
    return search(root.right, val)

# Delete
def delete(root, val):
    if not root:
        return None
    
    if val < root.val:
        root.left  = delete(root.left,  val)
    elif val > root.val:
        root.right = delete(root.right, val)
    else:
        # Node to delete found
        if not root.left:   return root.right  # Case 1 & 2
        if not root.right:  return root.left
        
        # Case 3: two children → replace with inorder successor
        successor = root.right
        while successor.left:
            successor = successor.left
        root.val   = successor.val
        root.right = delete(root.right, successor.val)
    
    return root

# Time: O(H) avg O(log N), worst O(N) for skewed BST
```

> **Follow-up:** Why do we use the inorder successor (not predecessor) for deletion?  
> **Answer:** Both work correctly. The inorder successor is the smallest node in the right subtree, which maintains BST property: it's larger than all nodes in the left subtree and smaller than all remaining nodes in the right subtree. Using the predecessor (largest in left subtree) is equally valid.

---

### Q13. What is BST's average vs worst-case complexity?

**Answer:**

| Operation | Average Case | Worst Case (Skewed) |
|---|---|---|
| Search | O(log N) | O(N) |
| Insert | O(log N) | O(N) |
| Delete | O(log N) | O(N) |
| Inorder | O(N) | O(N) |

The worst case occurs when the BST degenerates into a **linked list** (inserting already-sorted data). This motivates **self-balancing BSTs** (AVL, Red-Black).

---

### Q14. How do you find the Kth smallest/largest element in a BST?

**Answer:**

```python
# Kth Smallest — Inorder gives sorted order
def kth_smallest(root, k):
    stack = []
    curr = root
    count = 0
    
    while curr or stack:
        while curr:
            stack.append(curr)
            curr = curr.left
        curr = stack.pop()
        count += 1
        if count == k:
            return curr.val
        curr = curr.right
    return -1

# Kth Largest — Reverse Inorder (Right → Root → Left)
def kth_largest(root, k):
    stack = []
    curr = root
    count = 0
    
    while curr or stack:
        while curr:
            stack.append(curr)
            curr = curr.right     # Go right first
        curr = stack.pop()
        count += 1
        if count == k:
            return curr.val
        curr = curr.left
    return -1

# Time: O(H + K)  |  Space: O(H)
```

---

## 5. Balanced Trees

---

### Q15. What is an AVL Tree? How does it maintain balance?

**Answer:**

An **AVL Tree** (Adelson-Velsky and Landis) is a self-balancing BST where the **balance factor** (height difference between left and right subtrees) of every node is **-1, 0, or +1**.

```
Balance Factor = height(left) - height(right)
```

When a node becomes unbalanced (|bf| > 1) after insert/delete, **rotations** restore balance:

```
4 Cases:

Left-Left (LL):      Right-Right (RR):    Left-Right (LR):    Right-Left (RL):
    z                    z                    z                    z
   /                      \                  /                      \
  y          →→            y      →→        y          →→            y
 /          RR              \    LL           \          RL+RR        /
x                            x                x                      x

→ Single Right Rotation  → Single Left Rotation  → Left then Right  → Right then Left
```

```python
class AVLNode:
    def __init__(self, val):
        self.val = val
        self.left = self.right = None
        self.height = 1

def get_height(node):
    return node.height if node else 0

def get_balance(node):
    return get_height(node.left) - get_height(node.right) if node else 0

def right_rotate(z):
    y = z.left
    T3 = y.right
    y.right = z
    z.left = T3
    z.height = 1 + max(get_height(z.left), get_height(z.right))
    y.height = 1 + max(get_height(y.left), get_height(y.right))
    return y

def left_rotate(z):
    y = z.right
    T2 = y.left
    y.left = z
    z.right = T2
    z.height = 1 + max(get_height(z.left), get_height(z.right))
    y.height = 1 + max(get_height(y.left), get_height(y.right))
    return y
```

> **Follow-up:** How does AVL compare to Red-Black Tree?  
> **Answer:** AVL trees are **more strictly balanced** (height difference ≤ 1), giving slightly faster lookups. Red-Black trees allow slightly more imbalance but have **fewer rotations on insert/delete**, making them faster for write-heavy workloads. Most production systems (like C++ `std::map`, Java `TreeMap`) use Red-Black trees.

---

### Q16. What are the properties of a Red-Black Tree?

**Answer:**

A **Red-Black Tree** is a BST with coloring rules that ensure approximate balance:

1. Every node is **RED** or **BLACK**
2. Root is always **BLACK**
3. Every leaf (NIL node) is **BLACK**
4. A **RED** node's children must be **BLACK** (no two reds in a row)
5. Every path from a node to its descendant NIL nodes has the same number of **BLACK** nodes (**black-height**)

These rules guarantee height ≤ **2 × log(N+1)**, ensuring O(log N) operations.

> **Follow-up:** Why do we need both AVL and Red-Black Trees?  
> **Answer:** They optimize for different workloads. AVL is better when **reads dominate** (stricter balance = faster search). Red-Black is better when **writes dominate** (fewer rebalancing operations). In practice, Red-Black Trees are more commonly used in standard library implementations due to better overall performance.

---

## 6. Heaps & Priority Queues

---

### Q17. What is a Heap? Explain Min-Heap and Max-Heap.

**Answer:**

A **Heap** is a complete binary tree satisfying the **heap property**:
- **Min-Heap:** Parent ≤ children (minimum at root)
- **Max-Heap:** Parent ≥ children (maximum at root)

```
Min-Heap:        Max-Heap:
      1                9
     / \              / \
    3   2            7   8
   / \ / \          / \ / \
  6  5 4  7        2  6 3  1
```

```python
import heapq

# Python's heapq is a MIN-HEAP
heap = []
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappush(heap, 4)
print(heapq.heappop(heap))  # 1 (minimum)

# Max-heap: negate values
heapq.heappush(heap, -val)
max_val = -heapq.heappop(heap)

# Build heap from list: O(N) — more efficient than N pushes
nums = [3, 1, 4, 1, 5, 9, 2]
heapq.heapify(nums)   # In-place, O(N)
```

| Operation | Time |
|---|---|
| heappush | O(log N) |
| heappop  | O(log N) |
| peek (min/max) | O(1) |
| heapify | O(N) |
| search | O(N) |

> **Follow-up:** Why is heapify O(N) instead of O(N log N)?  
> **Answer:** The key insight is that most nodes are near the bottom and require very little "sifting down." Formally: the sum of work done at each level is `∑(h × N/2^h)` for h from 0 to log N, which telescopes to O(N). Building via N individual insertions would be O(N log N).

---

### Q18. Implement a Min-Heap from scratch.

**Answer:**

```python
class MinHeap:
    def __init__(self):
        self.heap = []
    
    def _parent(self, i): return (i - 1) // 2
    def _left(self, i):   return 2 * i + 1
    def _right(self, i):  return 2 * i + 2
    
    def push(self, val):
        self.heap.append(val)
        self._sift_up(len(self.heap) - 1)
    
    def pop(self):
        if len(self.heap) == 1:
            return self.heap.pop()
        root = self.heap[0]
        self.heap[0] = self.heap.pop()  # Move last to root
        self._sift_down(0)
        return root
    
    def peek(self):
        return self.heap[0] if self.heap else None
    
    def _sift_up(self, i):
        while i > 0 and self.heap[self._parent(i)] > self.heap[i]:
            p = self._parent(i)
            self.heap[i], self.heap[p] = self.heap[p], self.heap[i]
            i = p
    
    def _sift_down(self, i):
        n = len(self.heap)
        smallest = i
        l, r = self._left(i), self._right(i)
        if l < n and self.heap[l] < self.heap[smallest]: smallest = l
        if r < n and self.heap[r] < self.heap[smallest]: smallest = r
        if smallest != i:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self._sift_down(smallest)
```

---

## 7. Tries (Prefix Trees)

---

### Q19. What is a Trie? What are its use cases?

**Answer:**

A **Trie** (Prefix Tree / Digital Tree) is a tree-like data structure used for storing strings where each node represents a character. Paths from root to nodes spell out words/prefixes.

```
Insert: "cat", "car", "care", "card", "bat"

        root
       /    \
      c      b
      |      |
      a      a
     / \     |
    t   r    t
        |
        e*  d*
(*=end of word)
```

**Use cases:**
- Autocomplete / search suggestions
- Spell checking
- IP routing (longest prefix matching)
- Word games (Boggle, Scrabble)
- Dictionary implementations

```python
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True
    
    def search(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.is_end
    
    def starts_with(self, prefix):
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True
    
    def delete(self, word):
        def _delete(node, word, depth):
            if depth == len(word):
                if not node.is_end:
                    return False
                node.is_end = False
                return len(node.children) == 0
            ch = word[depth]
            if ch not in node.children:
                return False
            should_delete = _delete(node.children[ch], word, depth + 1)
            if should_delete:
                del node.children[ch]
                return not node.is_end and len(node.children) == 0
            return False
        _delete(self.root, word, 0)

# Time: O(L) for all ops, L = length of word
# Space: O(ALPHABET × N × L) worst case
```

> **Follow-up:** How does a Trie compare to a HashMap for storing strings?  
> **Answer:** A HashMap gives O(L) lookup per word but doesn't support prefix queries efficiently. A Trie also gives O(L) lookup and additionally supports **prefix searches**, **autocomplete**, and **lexicographic ordering** — all naturally. Tries use more memory but offer richer string operations.

---

## 8. Segment Trees & Fenwick Trees

---

### Q20. What is a Segment Tree? When do you use it?

**Answer:**

A **Segment Tree** is a tree used for storing information about intervals (segments) of an array, enabling efficient **range queries** and **point/range updates**.

```
Array: [1, 3, 5, 7, 9, 11]

Segment Tree (sum):
                [1,6] = 36
              /          \
         [1,3]=9       [4,6]=27
         /    \         /    \
      [1,2]=4 [3]=5  [4,5]=16 [6]=11
      /   \           /    \
   [1]=1 [2]=3     [4]=7  [5]=9
```

```python
class SegmentTree:
    def __init__(self, nums):
        self.n = len(nums)
        self.tree = [0] * (4 * self.n)
        if nums:
            self._build(nums, 0, 0, self.n - 1)
    
    def _build(self, nums, node, start, end):
        if start == end:
            self.tree[node] = nums[start]
        else:
            mid = (start + end) // 2
            self._build(nums, 2*node+1, start, mid)
            self._build(nums, 2*node+2, mid+1, end)
            self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
    
    def update(self, idx, val, node=0, start=0, end=None):
        if end is None: end = self.n - 1
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if idx <= mid:
                self.update(idx, val, 2*node+1, start, mid)
            else:
                self.update(idx, val, 2*node+2, mid+1, end)
            self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
    
    def query(self, l, r, node=0, start=0, end=None):
        if end is None: end = self.n - 1
        if r < start or end < l:
            return 0    # Out of range
        if l <= start and end <= r:
            return self.tree[node]   # Total overlap
        mid = (start + end) // 2
        return (self.query(l, r, 2*node+1, start, mid) +
                self.query(l, r, 2*node+2, mid+1, end))

# Build: O(N)  |  Query: O(log N)  |  Update: O(log N)
# Space: O(N)
```

---

### Q21. What is a Fenwick Tree (Binary Indexed Tree)?

**Answer:**

A **Fenwick Tree** (BIT) is a simpler alternative to segment trees for **prefix sum queries** and **point updates**, with less code and smaller constants.

```python
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def update(self, i, delta):
        """Add delta to index i (1-indexed)"""
        while i <= self.n:
            self.tree[i] += delta
            i += i & (-i)     # Move to next responsible node
    
    def prefix_sum(self, i):
        """Sum from index 1 to i"""
        total = 0
        while i > 0:
            total += self.tree[i]
            i -= i & (-i)     # Move to parent
        return total
    
    def range_sum(self, l, r):
        """Sum from index l to r"""
        return self.prefix_sum(r) - self.prefix_sum(l - 1)

# All operations: O(log N)
# Space: O(N)
```

> **Follow-up:** When would you use Fenwick Tree over Segment Tree?  
> **Answer:** Fenwick Tree is simpler to code and has smaller constants — prefer it for **simple prefix sum / point update** problems. Segment Tree is more versatile: it handles **range updates** (with lazy propagation), range min/max, and custom aggregate functions that Fenwick Trees can't easily support.

---

## 9. N-ary Trees

---

### Q22. What is an N-ary Tree? How do you represent it?

**Answer:**

An **N-ary Tree** is a tree where each node can have **at most N children** (or any number of children, variable per node).

```
        1
      / | \
     3  2  4
    / \
   5   6
```

```python
# Definition
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []

# Build the above tree:
root = Node(1, [
    Node(3, [Node(5), Node(6)]),
    Node(2),
    Node(4)
])
```

**Other representations:**

```python
# Left-Child Right-Sibling (LCRS) representation
# Converts N-ary to binary tree structure
class LCRSNode:
    def __init__(self, val):
        self.val = val
        self.left  = None   # First child
        self.right = None   # Next sibling

# Dictionary-based (parent map)
children = {
    1: [3, 2, 4],
    3: [5, 6],
    2: [],  4: [],  5: [],  6: []
}
```

> **Follow-up:** What is the Left-Child Right-Sibling representation and why is it useful?  
> **Answer:** LCRS converts an N-ary tree into a **binary tree** by making the first child the left child and the next sibling the right child. This allows binary tree algorithms to work on N-ary trees and is used in classic data structures like **leftist heaps** and **Fibonacci heaps**.

---

### Q23. Implement all traversals for N-ary Trees.

**Answer:**

```python
from collections import deque

# Preorder: Root → Children (left to right)
def preorder_nary(root):
    if not root:
        return []
    result = [root.val]
    for child in root.children:
        result.extend(preorder_nary(child))
    return result

# Iterative Preorder
def preorder_nary_iter(root):
    if not root:
        return []
    result, stack = [], [root]
    while stack:
        node = stack.pop()
        result.append(node.val)
        # Push children in reverse order so leftmost is processed first
        for child in reversed(node.children):
            stack.append(child)
    return result

# Postorder: Children → Root
def postorder_nary(root):
    if not root:
        return []
    result = []
    for child in root.children:
        result.extend(postorder_nary(child))
    result.append(root.val)
    return result

# Level Order BFS
def level_order_nary(root):
    if not root:
        return []
    result = []
    queue = deque([root])
    while queue:
        level = []
        for _ in range(len(queue)):
            node = queue.popleft()
            level.append(node.val)
            for child in node.children:
                queue.append(child)
        result.append(level)
    return result

# Time: O(N)  |  Space: O(N) for all traversals
```

---

### Q24. Find the height and depth of an N-ary Tree.

**Answer:**

```python
# Height of N-ary tree
def height_nary(root):
    if not root:
        return 0
    if not root.children:
        return 0   # Leaf node
    return 1 + max(height_nary(child) for child in root.children)

# Maximum depth (same as height from root)
def max_depth_nary(root):
    if not root:
        return 0
    if not root.children:
        return 1
    return 1 + max(max_depth_nary(child) for child in root.children)

# Iterative height using BFS (count levels)
def height_bfs_nary(root):
    if not root:
        return 0
    queue = deque([root])
    height = 0
    while queue:
        height += 1
        for _ in range(len(queue)):
            node = queue.popleft()
            for child in node.children:
                queue.append(child)
    return height - 1   # Height = levels - 1

# Time: O(N)  |  Space: O(N)
```

---

### Q25. Find the diameter of an N-ary Tree.

**Answer:**

The diameter is the longest path between any two nodes. At each node, the top-2 longest child paths form the longest path through that node.

```python
def diameter_nary(root):
    max_diameter = [0]
    
    def dfs(node):
        if not node:
            return 0
        
        top1 = top2 = 0   # Two longest depths among children
        
        for child in node.children:
            depth = dfs(child) + 1
            if depth > top1:
                top2 = top1
                top1 = depth
            elif depth > top2:
                top2 = depth
        
        # Path through this node = top1 + top2
        max_diameter[0] = max(max_diameter[0], top1 + top2)
        return top1  # Return max depth for parent
    
    dfs(root)
    return max_diameter[0]

# Time: O(N)  |  Space: O(H) — H = height of tree
```

---

### Q26. Serialize and Deserialize an N-ary Tree.

**Answer:**

```python
class Codec:
    def serialize(self, root):
        """
        Format: val num_children child1 child2 ...
        Example: 1 3 3 2 5 0 6 0 2 0 4 0
        """
        if not root:
            return ""
        
        result = []
        
        def dfs(node):
            result.append(str(node.val))
            result.append(str(len(node.children)))
            for child in node.children:
                dfs(child)
        
        dfs(root)
        return ' '.join(result)
    
    def deserialize(self, data):
        if not data:
            return None
        
        tokens = iter(data.split())
        
        def dfs():
            val = int(next(tokens))
            num_children = int(next(tokens))
            node = Node(val)
            for _ in range(num_children):
                node.children.append(dfs())
            return node
        
        return dfs()

# Time: O(N)  |  Space: O(N)
```

> **Follow-up:** How does serialization of N-ary trees differ from binary trees?  
> **Answer:** For binary trees, we can use `null` markers to distinguish left/right children (at most 2). For N-ary trees, we must explicitly store the **number of children** for each node since a node can have variable children count. Alternatively, a sentinel value (like `#`) can mark the end of a node's children list.

---

### Q27. Find LCA in an N-ary Tree.

**Answer:**

```python
def lca_nary(root, p, q):
    if not root:
        return None
    if root.val == p or root.val == q:
        return root
    
    found = []
    for child in root.children:
        result = lca_nary(child, p, q)
        if result:
            found.append(result)
    
    if len(found) >= 2:
        return root   # Found in two different subtrees → root is LCA
    
    return found[0] if found else None

# Time: O(N)  |  Space: O(H)
```

---

### Q28. Convert Binary Tree to N-ary Tree and vice versa (LCRS).

**Answer:**

```python
# Binary Tree Node (for LCRS)
class BTNode:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left  = left   # First child
        self.right = right  # Next sibling

# N-ary → Binary (LCRS encoding)
def nary_to_binary(root):
    if not root:
        return None
    bt_node = BTNode(root.val)
    if root.children:
        bt_node.left = nary_to_binary(root.children[0])
        curr = bt_node.left
        for child in root.children[1:]:
            curr.right = nary_to_binary(child)
            curr = curr.right
    return bt_node

# Binary → N-ary (LCRS decoding)
def binary_to_nary(root):
    if not root:
        return None
    nary_node = Node(root.val)
    curr = root.left  # First child
    while curr:
        nary_node.children.append(binary_to_nary(curr))
        curr = curr.right   # Next sibling
    return nary_node
```

---

## 10. Tree DP & Advanced Problems

---

### Q29. What is Tree DP? Give an example.

**Answer:**

**Tree DP** solves problems on trees by computing answers for subtrees bottom-up, combining child results at each node.

**Classic: Maximum Independent Set on a Tree**  
(Select maximum nodes such that no two adjacent nodes are selected)

```python
def max_independent_set(root):
    def dfs(node):
        if not node:
            return (0, 0)  # (include_node, exclude_node)
        
        left_inc,  left_exc  = dfs(node.left)
        right_inc, right_exc = dfs(node.right)
        
        # Include this node: can't include children
        include = 1 + left_exc + right_exc
        
        # Exclude this node: take best from each child
        exclude = max(left_inc, left_exc) + max(right_inc, right_exc)
        
        return (include, exclude)
    
    return max(dfs(root))
```

**Binary Tree Cameras (LeetCode 968):**

```python
def min_camera_cover(root):
    cameras = [0]
    
    # Returns: 0 = uncovered, 1 = covered (no camera), 2 = has camera
    def dfs(node):
        if not node:
            return 1   # Null nodes considered covered
        
        left  = dfs(node.left)
        right = dfs(node.right)
        
        if left == 0 or right == 0:
            cameras[0] += 1
            return 2   # Must place camera here
        
        if left == 2 or right == 2:
            return 1   # Covered by child's camera
        
        return 0       # Both children covered but no camera → parent must cover
    
    return cameras[0] + (1 if dfs(root) == 0 else 0)
```

---

### Q30. Path Sum problems in Trees.

**Answer:**

```python
# Has path with given sum (root to leaf)
def has_path_sum(root, target):
    if not root:
        return False
    if not root.left and not root.right:
        return root.val == target
    return (has_path_sum(root.left,  target - root.val) or
            has_path_sum(root.right, target - root.val))

# Maximum path sum (any node to any node)
def max_path_sum(root):
    max_sum = [float('-inf')]
    
    def dfs(node):
        if not node:
            return 0
        left  = max(dfs(node.left),  0)   # Ignore negative paths
        right = max(dfs(node.right), 0)
        
        # Path through this node
        max_sum[0] = max(max_sum[0], node.val + left + right)
        
        # Return max single-branch path for parent
        return node.val + max(left, right)
    
    dfs(root)
    return max_sum[0]

# All root-to-leaf paths summing to target
def path_sum_all(root, target):
    result = []
    
    def dfs(node, remaining, path):
        if not node:
            return
        path.append(node.val)
        if not node.left and not node.right and remaining == node.val:
            result.append(list(path))
        else:
            dfs(node.left,  remaining - node.val, path)
            dfs(node.right, remaining - node.val, path)
        path.pop()   # Backtrack
    
    dfs(root, target, [])
    return result
```

---

## 11. Classic Coding Problems

---

### Q31. Flatten Binary Tree to Linked List (LeetCode 114)

```python
def flatten(root):
    def dfs(node):
        if not node:
            return None
        if not node.left and not node.right:
            return node   # Leaf: return itself as tail
        
        left_tail  = dfs(node.left)
        right_tail = dfs(node.right)
        
        if left_tail:
            left_tail.right = node.right
            node.right = node.left
            node.left  = None
        
        return right_tail or left_tail
    
    dfs(root)
```

---

### Q32. Binary Tree Right Side View (LeetCode 199)

```python
def right_side_view(root):
    if not root:
        return []
    result = []
    queue = deque([root])
    while queue:
        for i in range(len(queue)):
            node = queue.popleft()
            if i == len(queue):   # Last node in level
                result.append(node.val)
            if node.left:  queue.append(node.left)
            if node.right: queue.append(node.right)
    # Simpler: just take the last node of each level
    return result

def right_side_view_clean(root):
    result = []
    queue = deque([root]) if root else deque()
    while queue:
        result.append(queue[-1].val)   # Rightmost of this level
        for _ in range(len(queue)):
            node = queue.popleft()
            if node.left:  queue.append(node.left)
            if node.right: queue.append(node.right)
    return result
```

---

### Q33. Serialize and Deserialize Binary Tree (LeetCode 297)

```python
class Codec:
    def serialize(self, root):
        result = []
        def dfs(node):
            if not node:
                result.append('#')
                return
            result.append(str(node.val))
            dfs(node.left)
            dfs(node.right)
        dfs(root)
        return ','.join(result)
    
    def deserialize(self, data):
        tokens = iter(data.split(','))
        def dfs():
            val = next(tokens)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left  = dfs()
            node.right = dfs()
            return node
        return dfs()
```

---

### Q34. Vertical Order Traversal (LeetCode 987)

```python
from collections import defaultdict

def vertical_traversal(root):
    nodes = []
    
    def dfs(node, row, col):
        if not node:
            return
        nodes.append((col, row, node.val))
        dfs(node.left,  row + 1, col - 1)
        dfs(node.right, row + 1, col + 1)
    
    dfs(root, 0, 0)
    nodes.sort()   # Sort by (col, row, val)
    
    result = []
    prev_col = float('-inf')
    for col, row, val in nodes:
        if col != prev_col:
            result.append([])
            prev_col = col
        result[-1].append(val)
    
    return result
```

---

### Q35. Word Search II using Trie + Backtracking (LeetCode 212)

```python
def find_words(board, words):
    # Build trie from words
    trie = {}
    for word in words:
        node = trie
        for ch in word:
            node = node.setdefault(ch, {})
        node['#'] = word   # Mark end
    
    rows, cols = len(board), len(board[0])
    found = set()
    
    def dfs(node, r, c):
        ch = board[r][c]
        if ch not in node:
            return
        next_node = node[ch]
        if '#' in next_node:
            found.add(next_node['#'])
        
        board[r][c] = '$'   # Mark visited
        for dr, dc in [(0,1),(0,-1),(1,0),(-1,0)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and board[nr][nc] != '$':
                dfs(next_node, nr, nc)
        board[r][c] = ch    # Restore
    
    for r in range(rows):
        for c in range(cols):
            dfs(trie, r, c)
    
    return list(found)
```

---

## 12. System Design with Trees

---

### Q36. How are trees used in real-world systems?

**Answer:**

| System | Tree Type | Use Case |
|---|---|---|
| **File Systems** | N-ary Tree | Directory hierarchy (folders & files) |
| **HTML/XML DOM** | N-ary Tree | Document structure parsing |
| **Databases (B-Tree/B+ Tree)** | Balanced N-ary | Index structures for fast disk lookups |
| **Compilers** | AST (Binary/N-ary) | Abstract Syntax Trees for code parsing |
| **Search Engines** | Trie | Prefix search, autocomplete |
| **OS Process Scheduling** | Heap | Priority queues for CPU scheduling |
| **DNS** | Trie-like | Domain name resolution hierarchy |
| **Game Trees** | N-ary | Minimax for chess/checkers AI |
| **Network Routing** | Trie | Longest prefix matching (CIDR) |
| **Compression** | Binary Tree | Huffman coding |
| **Range Queries (DB)** | Segment/B+ Tree | Interval index, aggregations |
| **Memory Allocators** | BST | Free block management |

---

### Q37. What is a B-Tree? Why do databases use it?

**Answer:**

A **B-Tree** is a self-balancing, sorted N-ary tree designed for **disk-based storage** where each node can have many keys and children (degree M means each node has M-1 keys and M children).

**Properties:**
- All leaves are at the same level
- Every node (except root) has at least ⌈M/2⌉ children
- A node with k keys has k+1 children
- Keys within a node are sorted

**Why databases choose B-Trees:**
- Designed to minimize **disk I/O**: one node = one disk page (4KB), so a single read loads many keys
- Height of B-Tree ≈ log_M(N) — extremely shallow for large M
- For M=1000, a B-Tree of height 3 stores **1 billion** keys
- B+ Trees (variant) store all data in leaves with leaf-level linked list, enabling fast **range scans**

> **Follow-up:** What is the difference between B-Tree and B+ Tree?  
> **Answer:** In a **B-Tree**, data pointers can exist at any node. In a **B+ Tree**, data is only stored at **leaf nodes**, and all leaves are linked in a doubly linked list. B+ Trees are preferred in databases because range queries are faster (just traverse the leaf list) and internal nodes can store more keys (no data pointers), making the tree shorter.

---

## 📌 Quick Reference: Complexity Summary

| Structure / Operation | Time (avg) | Time (worst) | Space |
|---|---|---|---|
| Binary Tree Traversal | O(N) | O(N) | O(H) |
| BST Search / Insert / Delete | O(log N) | O(N) skewed | O(H) |
| AVL / Red-Black Search | O(log N) | O(log N) | O(N) |
| Heap Push / Pop | O(log N) | O(log N) | O(N) |
| Heapify | O(N) | O(N) | O(1) |
| Trie Insert / Search | O(L) | O(L) | O(N×L) |
| Segment Tree Build | O(N) | O(N) | O(N) |
| Segment Tree Query/Update | O(log N) | O(log N) | — |
| Fenwick Tree Query/Update | O(log N) | O(log N) | O(N) |
| N-ary Tree Traversal | O(N) | O(N) | O(H) |
| LCA (Binary/N-ary) | O(N) | O(N) | O(H) |
| Tree Diameter | O(N) | O(N) | O(H) |

*H = height of tree, L = length of string/word, N = number of nodes*

---

## 🔑 Key Interview Tips for Trees

1. **Always handle the base case first:** `if not root: return ...`
2. **Think recursively:** Define what the function returns for a node in terms of its children.
3. **Identify the traversal pattern:** Most tree problems fit DFS (pre/in/post-order) or BFS (level-order).
4. **Top-down vs Bottom-up DFS:**
   - Top-down: pass state from parent to children (preorder style)
   - Bottom-up: collect results from children first (postorder style)
5. **Use helper functions:** Pass extra parameters (min/max bounds, depth, parent) via a nested helper.
6. **Diameter / LCA pattern:** Track global max in an array `[0]` or class variable.
7. **Balance vs BST:** Not every tree is balanced — always check if a BST operation is O(log N) or O(N).
8. **N-ary trees:** Iterate over `node.children` instead of checking `node.left` / `node.right`.
9. **Common edge cases:** Empty tree, single node, skewed tree (linked list), all same values.
10. **Coordinate systems for grid/tree problems:** Assign (row, col) or depth/column for vertical traversal.

---

*Made for Interview Preparation — Tree DSA from Scratch to Advanced (Binary, BST, AVL, Heap, Trie, Segment Tree, N-ary)*
