# 🌳 Segment Trees — Deep Dive (C++ & LeetCode)

> A thorough, intuition-first guide — how they work internally, why they exist, when to use them, and how to write them from scratch.

---

## Table of Contents

1. [What is a Segment Tree?](#1-what-is-a-segment-tree)
2. [Why Not Just Use a Prefix Sum Array?](#2-why-not-just-use-a-prefix-sum-array)
3. [Anatomy of a Segment Tree](#3-anatomy-of-a-segment-tree)
4. [The Four Core Operations Explained](#4-the-four-core-operations-explained)
5. [Building a Segment Tree in C++](#5-building-a-segment-tree-in-c)
6. [Array vs Pointer-Based Implementation](#6-array-vs-pointer-based-implementation)
7. [Lazy Propagation — The Critical Optimization](#7-lazy-propagation--the-critical-optimization)
8. [Complexity Analysis](#8-complexity-analysis)
9. [Segment Tree Variations](#9-segment-tree-variations)
10. [Common Segment Tree Patterns](#10-common-segment-tree-patterns)
11. [LeetCode Problems](#11-leetcode-problems)
12. [Common Mistakes & Debugging](#12-common-mistakes--debugging)
13. [Quick Reference](#13-quick-reference)

---

## 1. What is a Segment Tree?

A **Segment Tree** is a binary tree built on top of an array, where every node stores the answer to some query (sum, min, max, GCD, etc.) over a **contiguous segment (subarray)** of the original array.

### The Central Idea

Every node in the tree represents a range `[l, r]`:
- **Leaf nodes** represent individual elements: the range `[i, i]`
- **Internal nodes** represent merged ranges: a node for `[l, r]` has a left child for `[l, mid]` and a right child for `[mid+1, r]`
- The **root** covers the entire array `[0, n-1]`

```
Array: [2, 4, 3, 1, 6, 7, 2, 5]   (Sum Segment Tree)

                   [0,7] = 30
                 /            \
          [0,3] = 10        [4,7] = 20
          /      \           /       \
      [0,1]=6  [2,3]=4  [4,5]=13  [6,7]=7
      /   \    /   \    /    \    /    \
    [0]=2 [1]=4 [2]=3 [3]=1 [4]=6 [5]=7 [6]=2 [7]=5
```

Every parent is the **sum of its two children**. To query the sum of any subarray, instead of re-summing elements one by one, you **decompose the query range into a small number of pre-computed nodes** in the tree and combine them.

### Real-World Mental Model

Think of a Segment Tree like an **accounting ledger with department totals**:

```
Company (Total Revenue: $30M)
├── Division A ($10M)
│   ├── Team A1 ($6M): Alice $2M, Bob $4M
│   └── Team A2 ($4M): Carol $3M, Dave $1M
└── Division B ($20M)
    ├── Team B1 ($13M): Eve $6M, Frank $7M
    └── Team B2 ($7M): Grace $2M, Hank $5M
```

If you want "total revenue for employees 2 to 6", you don't re-add every person's number — you use pre-computed team/division totals where they fit entirely within your query range, and only go down to individual employees at the boundaries. This is exactly what a Segment Tree does.

---

## 2. Why Not Just Use a Prefix Sum Array?

A prefix sum array answers range sum queries in O(1):

```cpp
prefix[i] = arr[0] + arr[1] + ... + arr[i]
rangeSum(l, r) = prefix[r] - prefix[l-1]   // O(1)
```

So why do we need Segment Trees at all?

### The Fundamental Limitation of Prefix Sums

Prefix sums are **static** — they are computed once for a fixed array and break the moment any element is updated.

```
Array: [2, 4, 3, 1, 6]
Prefix: [2, 6, 9, 10, 16]

Update arr[2] from 3 to 10:
Now EVERY prefix[i] for i >= 2 must be recomputed: O(n)

With 1,000,000 elements and 1,000,000 updates, this is 10^12 operations — impossible.
```

### The Core Tradeoff

| Structure | Build | Point Update | Range Query |
|-----------|-------|--------------|-------------|
| Naive array | O(n) | O(1) | O(n) |
| Prefix sum | O(n) | **O(n)** — rebuild after update | **O(1)** |
| **Segment Tree** | **O(n)** | **O(log n)** | **O(log n)** |
| Fenwick Tree (BIT) | O(n) | O(log n) | O(log n) — sums only |

> **Rule of thumb**: If your problem requires **both** range queries **and** point (or range) updates on the same array, a Segment Tree is almost always the right structure. If updates never happen, a prefix sum is simpler and faster.

### What a Segment Tree Can Answer That Others Cannot

- Range **sum** / **product** / **XOR** with point updates
- Range **minimum** / **maximum** with point updates
- Range **GCD** / **LCM** with point updates
- Range **updates** (add a value to all elements in a range) — needs Lazy Propagation
- Count of elements satisfying a condition in a range
- First index in a range satisfying a condition (binary search on the tree)

---

## 3. Anatomy of a Segment Tree

### The Array Representation

A Segment Tree over n elements is stored in an array of size **4n** (to be safe). The indexing convention:

```
Node at index i:
  Left child  →  2*i
  Right child →  2*i + 1
  Parent      →  i/2

Root is at index 1 (1-indexed is cleaner for this structure).
```

```
tree[] array (1-indexed):
Index:  1      2      3      4    5    6    7    8  9  10 11 12 13 14 15
Value: [30]  [10]   [20]   [6] [4]  [13] [7]  [2][4][3][1][6][7][2][5]
        ↑root ↑[0,3] ↑[4,7]
```

This is elegant: no pointers, no heap allocation — just arithmetic to navigate parent/child relationships.

### What Each Node Stores

```cpp
// For a Range Sum Segment Tree:
int tree[4 * MAXN];   // tree[node] = sum of arr[l..r] for the segment this node covers

// For a Range Min Segment Tree:
int tree[4 * MAXN];   // tree[node] = min of arr[l..r]

// For Lazy Propagation (Range Update):
int tree[4 * MAXN];   // aggregate values
int lazy[4 * MAXN];   // pending updates not yet pushed to children
```

### The Two Key Invariants

1. **Leaf invariant**: `tree[node]` for a leaf (l == r) equals `arr[l]`
2. **Internal invariant**: `tree[node] = merge(tree[left_child], tree[right_child])`

Where `merge` is the operation you care about: `+` for sum, `min()` for range min, `max()` for range max, `__gcd()` for GCD, `&` for AND, `|` for OR, etc.

These two invariants must hold at all times — every operation we write must maintain them.

---

## 4. The Four Core Operations Explained

### Operation 1: Build

**What**: Construct the tree bottom-up from the original array.

**How it works**: Recursively split the range in half, build left and right subtrees, then combine their results at the current node. The recursion bottoms out when `l == r` (a leaf — store `arr[l]` directly).

```
Build for [2, 4, 3, 1]:

build(1, 0, 3)          ← root covers [0,3]
├── build(2, 0, 1)      ← left child covers [0,1]
│   ├── build(4, 0, 0)  ← leaf: tree[4] = arr[0] = 2
│   └── build(5, 1, 1)  ← leaf: tree[5] = arr[1] = 4
│   tree[2] = tree[4] + tree[5] = 6
└── build(3, 2, 3)      ← right child covers [2,3]
    ├── build(6, 2, 2)  ← leaf: tree[6] = arr[2] = 3
    └── build(7, 3, 3)  ← leaf: tree[7] = arr[3] = 1
    tree[3] = tree[6] + tree[7] = 4
tree[1] = tree[2] + tree[3] = 10
```

### Operation 2: Point Update

**What**: Change `arr[idx]` to a new value and reflect this in the tree.

**How it works**: Walk from the root to the leaf for `idx`, updating the leaf, then update all ancestor nodes on the way back up by recomputing them from their children. Only O(log n) nodes on the path from root to leaf need changing.

```
Update arr[1] from 4 to 10 (tree for [2, 4, 3, 1]):

Walk down: root [0,3] → [0,1] → leaf [1,1]
  tree[5] (leaf for index 1) = 10

Walk back up:
  tree[2] = tree[4] + tree[5] = 2 + 10 = 12
  tree[1] = tree[2] + tree[3] = 12 + 4 = 16
```

Only 3 nodes changed (log2(4) = 2 levels + root). All other nodes are untouched.

### Operation 3: Range Query

**What**: Compute the aggregate (sum, min, max, etc.) over `arr[l..r]`.

**How it works**: At each node, check the relationship between the **node's segment** and the **query range**:

```
Case 1: Node's segment is COMPLETELY OUTSIDE query range
  → Return identity value (0 for sum, INT_MAX for min, INT_MIN for max)
  → Do NOT recurse further — this entire subtree is irrelevant

Case 2: Node's segment is COMPLETELY INSIDE query range
  → Return tree[node] directly — no need to go deeper
  → This node was pre-computed to store exactly this aggregate

Case 3: Node's segment PARTIALLY OVERLAPS query range
  → Must recurse into BOTH children, then merge results
  → Split the problem: left child handles the left part, right child handles the right
```

```
Query sum of [1, 5] in array [2, 4, 3, 1, 6, 7, 2, 5]:

root [0,7]: partial overlap → recurse both children
├── [0,3]: partial overlap (query is [1,5], segment is [0,3]) → recurse
│   ├── [0,1]: partial overlap → recurse
│   │   ├── [0,0]: OUTSIDE [1,5] → return 0
│   │   └── [1,1]: INSIDE [1,5]  → return 4
│   │   result: 0 + 4 = 4
│   └── [2,3]: INSIDE [1,5]      → return 4 (no recursion!)
│   result: 4 + 4 = 8
└── [4,7]: partial overlap → recurse
    ├── [4,5]: INSIDE [1,5]      → return 13 (no recursion!)
    └── [6,7]: OUTSIDE [1,5]    → return 0
    result: 13 + 0 = 13
Total: 8 + 13 = 21
```

Notice how entire subtrees are either accepted or rejected wholesale — we touch at most O(log n) nodes despite querying across multiple elements.

### Operation 4: Range Update (with Lazy Propagation)

**What**: Add a value `val` to every element in `arr[l..r]`.

**Why this needs a new approach**: A naive range update would call point update once per element in the range — O(n) updates, each O(log n) — total O(n log n) for one range update. That's terrible.

**The lazy insight**: When a node's segment is **completely inside** the update range, instead of immediately pushing the update into all its descendants (which could cascade into millions of operations), we store the pending update in a **lazy array** and annotate the node: *"I've been updated, but I haven't told my children yet."* When we later need to visit a child, we first **push down** the pending lazy update to that child — on demand, not eagerly.

This defers work until it's actually needed, making range updates O(log n) instead of O(n log n).

---

## 5. Building a Segment Tree in C++

Let's build a complete, well-commented implementation. We'll use **Range Sum** as our example since it's the most instructive, but the structure generalizes directly to min/max/GCD by changing only the `merge` step.

### Version 1: Range Sum, Point Update (No Lazy Propagation)

```cpp
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int n;
    vector<int> tree;

    // Merge function — change this one line for min/max/GCD/etc.
    int merge(int left, int right) {
        return left + right;   // change to min(), max(), __gcd(), etc.
    }

    // Identity element for the merge operation
    // Sum → 0, Min → INT_MAX, Max → INT_MIN, GCD → 0
    int identity() { return 0; }

    // BUILD: recursively fills tree[] from arr[]
    // node = current node index in tree[]
    // l, r = segment this node is responsible for
    void build(vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];   // LEAF: store the element directly
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, 2*node,   l,     mid);   // build left child
        build(arr, 2*node+1, mid+1, r  );   // build right child
        tree[node] = merge(tree[2*node], tree[2*node+1]);   // pull up from children
    }

    // UPDATE: walk to the leaf for idx, update, then pull up on the way back
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;   // LEAF: set the new value
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid)
            update(2*node,   l,     mid, idx, val);   // idx is in left half
        else
            update(2*node+1, mid+1, r,   idx, val);   // idx is in right half
        tree[node] = merge(tree[2*node], tree[2*node+1]);   // pull up after child updated
    }

    // QUERY: return aggregate over [ql, qr]
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return identity();   // CASE 1: completely outside → return identity

        if (ql <= l && r <= qr)
            return tree[node];   // CASE 2: completely inside → return precomputed value

        // CASE 3: partial overlap → recurse both children
        int mid = l + (r - l) / 2;
        int leftResult  = query(2*node,   l,     mid, ql, qr);
        int rightResult = query(2*node+1, mid+1, r,   ql, qr);
        return merge(leftResult, rightResult);
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, identity());
        build(arr, 1, 0, n-1);   // root is node 1, covers [0, n-1]
    }

    void update(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }

    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};
```

### Walking Through the Code

```cpp
vector<int> arr = {2, 4, 3, 1, 6, 7, 2, 5};
SegmentTree st(arr);

st.query(0, 3);   // → 10  (sum of arr[0..3])
st.query(1, 5);   // → 21  (sum of arr[1..5])
st.update(2, 10); // arr[2] becomes 10
st.query(0, 3);   // → 17  (now 2+4+10+1)
```

### The Pull-Up Pattern

The line `tree[node] = merge(tree[2*node], tree[2*node+1])` appears in both `build` and `update`. This **pull-up** (also called **push-up** or **combine**) is the engine of the Segment Tree — it's how changes at leaf level propagate up to all ancestors. Never forget it in `update`.

---

## 6. Array vs Pointer-Based Implementation

There are two ways to structure a Segment Tree. Both are correct; each has a use case.

### Style A: Array-Based (Recommended for Interviews)

```cpp
// tree[] stores values; node indices are implicit via 2*node arithmetic
int tree[4 * MAXN];
int lazy[4 * MAXN];
```

**Pros**: No heap allocation, cache-friendly, simpler to write quickly, less code.  
**Cons**: Array must be pre-sized (4*n is the safe bound), slightly harder to store complex data per node.

### Style B: Pointer/Struct-Based (Better for Complex Nodes)

```cpp
struct Node {
    int sum, minVal, maxVal;   // multiple aggregates in one node
    Node* left = nullptr;
    Node* right = nullptr;
};
```

**Pros**: Flexible — node can store any data. Natural fit for **dynamic segment trees** (when coordinate values are huge, like up to 10^9, and you only build nodes that are actually accessed).

**Cons**: Heap allocation overhead, pointer chasing is less cache-friendly, more code.

### Dynamic Segment Tree (for large coordinate ranges)

When the value range is massive (e.g., queries on indices 0 to 10^9), a regular Segment Tree would require 4 × 10^9 nodes — impossible. A **dynamic (implicit) segment tree** creates nodes **only when visited**, keeping memory proportional to the number of operations, not the range size.

```cpp
struct Node {
    int val = 0;
    int left = 0, right = 0;   // indices into a node pool, 0 = null
};

const int MAXNODES = 4000000;
Node pool[MAXNODES];
int poolIdx = 0;

int newNode() { return ++poolIdx; }

void update(int node, int l, int r, int pos, int val) {
    if (l == r) { pool[node].val += val; return; }
    int mid = l + (r - l) / 2;
    if (pos <= mid) {
        if (!pool[node].left) pool[node].left = newNode();
        update(pool[node].left, l, mid, pos, val);
    } else {
        if (!pool[node].right) pool[node].right = newNode();
        update(pool[node].right, mid+1, r, pos, val);
    }
    int lv = pool[node].left  ? pool[pool[node].left].val  : 0;
    int rv = pool[node].right ? pool[pool[node].right].val : 0;
    pool[node].val = lv + rv;
}
```

---

## 7. Lazy Propagation — The Critical Optimization

Lazy propagation is what separates a basic Segment Tree from a fully capable one. It enables **O(log n) range updates** instead of O(n log n).

### The Mental Model

> "If a node's entire segment is covered by the update, mark the node's aggregate as updated and record the pending change in `lazy[]`. Do NOT touch children yet. Only propagate to children (`pushDown`) when you actually need to visit them."

This is the "lazy" in lazy propagation — defer work until it is demanded.

### The Three Rules

1. **When a node is completely inside the update range**: Apply the update to `tree[node]` directly, and store the pending update in `lazy[node]`. Do NOT recurse into children.

2. **Before you recurse into children** (partial overlap case): First call `pushDown` to pass any pending lazy update from the current node down to its children. This ensures children are up-to-date before you query or update them.

3. **After recursing**: Pull up from children as usual — `tree[node] = merge(left_child, right_child)`.

### How `pushDown` Works

When we push a lazy value from a parent down to its children:
- Apply the lazy update to each child's `tree[]` value (same formula we'd use in the update step)
- Move the lazy value into each child's `lazy[]`
- Clear the parent's `lazy[]` to 0 (it's been consumed)

```
Before pushDown:
  Parent [0,3]: tree=20, lazy=3   ← means "add 3 to all elements in [0,3]"
  Left   [0,1]: tree=6,  lazy=0   ← doesn't know about the +3 yet
  Right  [2,3]: tree=4,  lazy=0   ← doesn't know about the +3 yet

After pushDown:
  Parent [0,3]: tree=20, lazy=0   ← lazy cleared; parent's tree is already correct
  Left   [0,1]: tree=6 + 2*3=12, lazy=3  ← 2 elements in [0,1], so sum += 2*3=6
  Right  [2,3]: tree=4 + 2*3=10, lazy=3  ← similarly
```

The key formula for a **range add** on a sum segment tree:
```
tree[child] += lazy[parent] * (size of child's segment)
lazy[child] += lazy[parent]
```

For a **range set** (assign all elements in range to a value), it's simpler:
```
tree[child] = lazy[parent] * (size of child's segment)
lazy[child]  = lazy[parent]
```

### Full Implementation with Lazy Propagation (Range Add, Range Sum)

```cpp
class LazySegTree {
    int n;
    vector<long long> tree, lazy;

    void build(vector<int>& arr, int node, int l, int r) {
        lazy[node] = 0;
        if (l == r) { tree[node] = arr[l]; return; }
        int mid = l + (r - l) / 2;
        build(arr, 2*node,   l,     mid);
        build(arr, 2*node+1, mid+1, r  );
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    // Push the lazy value from node down to its two children
    void pushDown(int node, int l, int r) {
        if (lazy[node] == 0) return;   // nothing pending — skip
        int mid = l + (r - l) / 2;

        // Left child covers [l, mid] → (mid - l + 1) elements
        tree[2*node]   += lazy[node] * (mid - l + 1);
        lazy[2*node]   += lazy[node];

        // Right child covers [mid+1, r] → (r - mid) elements
        tree[2*node+1] += lazy[node] * (r - mid);
        lazy[2*node+1] += lazy[node];

        lazy[node] = 0;   // consumed — clear parent's lazy
    }

    // Add `val` to every element in [ul, ur]
    void update(int node, int l, int r, int ul, int ur, long long val) {
        if (ur < l || r < ul) return;   // completely outside — do nothing

        if (ul <= l && r <= ur) {
            // Completely inside — apply to this node's aggregate, mark lazy
            tree[node] += val * (r - l + 1);
            lazy[node] += val;
            return;
        }

        pushDown(node, l, r);   // MUST push before visiting children
        int mid = l + (r - l) / 2;
        update(2*node,   l,     mid, ul, ur, val);
        update(2*node+1, mid+1, r,   ul, ur, val);
        tree[node] = tree[2*node] + tree[2*node+1];   // pull up
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];

        pushDown(node, l, r);   // MUST push before visiting children
        int mid = l + (r - l) / 2;
        return query(2*node,   l,     mid, ql, qr)
             + query(2*node+1, mid+1, r,   ql, qr);
    }

public:
    LazySegTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
        build(arr, 1, 0, n-1);
    }

    void update(int l, int r, long long val) {
        update(1, 0, n-1, l, r, val);
    }

    long long query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }
};
```

### Why `pushDown` Must Come Before Recursing

Consider a range update [0,3] already stored in a node's `lazy`, and now we query [0,1] (the left child). If we recurse into the left child without first pushing down, the left child's `tree[]` value is **stale** — it doesn't reflect the pending range update. This would produce a wrong query answer. `pushDown` is the mechanism that ensures correctness: *"Resolve all pending work in this node before I use my children's values."*

---

## 8. Complexity Analysis

Let `n` = size of the original array.

| Operation | Time | Space |
|-----------|------|-------|
| Build | O(n) | O(n) |
| Point Update | O(log n) | — |
| Range Query | O(log n) | — |
| Range Update (with lazy) | O(log n) | O(n) extra for lazy array |
| Point Query (with lazy) | O(log n) | — |

### Why Range Query is O(log n)

At each level of the tree, a query range can intersect at most **4 nodes** (2 at the boundary, up to 2 that are completely inside). Since the tree has O(log n) levels, the total nodes visited is O(4 log n) = O(log n).

More precisely: a query over `[ql, qr]` touches at most `4 * log n` nodes. This is a standard result from the theory of interval trees and segment trees.

### Space

The tree array has size `4n`. Why 4 and not 2?

```
n = 5 (not a power of 2):
  Perfect binary tree for n=8 needs 16 nodes (2 * next_power_of_2(5))
  With padding: 2 * 8 = 16, but we index from 1, so 17 elements
  4 * 5 = 20 → safely covers all cases including non-power-of-2 sizes
```

Using `4n` is the safe universal bound. For competitive programming, many people use `4 * MAXN` as a global array.

---

## 9. Segment Tree Variations

### Variation 1: Range Minimum / Maximum Query (RMQ)

Change only the `merge` and `identity`:

```cpp
// Range Minimum
int merge(int a, int b) { return min(a, b); }
int identity() { return INT_MAX; }

// Range Maximum
int merge(int a, int b) { return max(a, b); }
int identity() { return INT_MIN; }
```

Everything else — build, update, query structure — stays exactly the same. This is one of the most powerful properties of the Segment Tree design.

---

### Variation 2: Storing Multiple Values Per Node

Sometimes one integer isn't enough. A node can store a struct:

```cpp
// Node for simultaneous min + max + sum queries
struct NodeVal {
    long long sum;
    int minV, maxV;
};

NodeVal merge(NodeVal left, NodeVal right) {
    return {
        left.sum + right.sum,
        min(left.minV, right.minV),
        max(left.maxV, right.maxV)
    };
}
```

---

### Variation 3: Segment Tree Beats (Ji Driver Segmentation)

A powerful advanced technique for operations like "replace each element x in [l,r] with min(x, v)". It uses a secondary maximum to efficiently decide whether a chmin operation can be applied to an entire segment or must be pushed deeper. Beyond interview scope, but good to know it exists.

---

### Variation 4: Persistent Segment Tree

Creates a **new version** of the Segment Tree after each update by reusing unchanged nodes. Enables "query the range [l,r] as it existed at time step k" — extremely powerful for offline range queries on version history. Uses O(log n) new nodes per update instead of O(n).

```
Version 0: [2, 4, 3, 1]
After update arr[2]=10, Version 1 shares all unchanged nodes from Version 0.
Only the path from root to the changed leaf is duplicated.
```

---

## 10. Common Segment Tree Patterns

### Pattern A: Classic Range Query + Point Update

> "Given an array, answer sum/min/max queries on subarrays, with updates to individual elements."

This is the baseline Segment Tree — see Section 5 for the complete implementation. This alone solves a large fraction of Segment Tree problems on LeetCode.

### Pattern B: Range Update + Range Query (Lazy Propagation)

> "Add a constant to every element in a range, then query the sum/min/max of a range."

Use lazy propagation — see Section 7 for the complete implementation. The key question to ask yourself when designing the lazy component:

```
What does lazy[node] = v mean?
  For range-add: "every element in this segment has a pending +v"
  For range-set: "every element in this segment should become v"

How does applying lazy to tree[node] look?
  Range-add + sum:  tree[node] += v * segment_size
  Range-set + sum:  tree[node] = v * segment_size
  Range-add + min:  tree[node] += v  (min of segment shifts by v)
  Range-set + min:  tree[node] = v
```

### Pattern C: Coordinate Compression + Segment Tree

> "Queries involve indices or values up to 10^9, but there are only 10^5 distinct values."

Compress coordinates first, then run a standard Segment Tree on the compressed indices.

```cpp
vector<int> vals = {1000000, 5, 999999, 5};
sort(vals.begin(), vals.end());
vals.erase(unique(vals.begin(), vals.end()), vals.end());
// vals = {5, 999999, 1000000}
// Now map: 5 → 0, 999999 → 1, 1000000 → 2
// Segment tree operates on indices 0..2 instead of 0..10^9
```

### Pattern D: Merge Sort Tree / Offline Queries

For questions like "how many elements in [l,r] are less than k" — build a Segment Tree where each node stores a **sorted list** of elements in its range. Query by binary searching within O(log n) nodes for O(log² n) total.

### Pattern E: Binary Search on Segment Tree

> "Find the leftmost index in [l, r] where the value is ≥ k" or "find the position of the k-th smallest element in a range."

Walk down the tree: at each node, decide whether to go left or right based on the left child's stored value, navigating to the answer in O(log n) without scanning linearly.

---

## 11. LeetCode Problems

A focused set covering each core pattern — each problem teaches a distinct skill.

---

### 🔗 LC 307 — Range Sum Query — Mutable

**Pattern**: A — the canonical Segment Tree problem. Point update + range sum query.

**Why this first**: This is the "LC 208 of Segment Trees" — the direct implementation problem that confirms you can write a correct Segment Tree.

```cpp
class NumArray {
    int n;
    vector<int> tree;

    void build(vector<int>& nums, int node, int l, int r) {
        if (l == r) { tree[node] = nums[l]; return; }
        int mid = l + (r - l) / 2;
        build(nums, 2*node,   l,     mid);
        build(nums, 2*node+1, mid+1, r  );
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) { tree[node] = val; return; }
        int mid = l + (r - l) / 2;
        if (idx <= mid) update(2*node,   l,     mid, idx, val);
        else            update(2*node+1, mid+1, r,   idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = l + (r - l) / 2;
        return query(2*node,   l,     mid, ql, qr)
             + query(2*node+1, mid+1, r,   ql, qr);
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, 0);
        build(nums, 1, 0, n-1);
    }

    void update(int index, int val) {
        update(1, 0, n-1, index, val);
    }

    int sumRange(int left, int right) {
        return query(1, 0, n-1, left, right);
    }
};
// Time: O(n) build, O(log n) per update/query   Space: O(n)
```

---

### 🔗 LC 2286 — Booking Concert Tickets in Groups

**Pattern**: A (range max + range sum) — two separate Segment Trees, or one storing both values.

**Problem**: n rows of seats, each row has `maxRow` seats. Support two queries:
- `gather(k, maxRow)` — find the **first** row with ≥ k consecutive seats available, seat k people there.
- `scatter(k, maxRow)` — seat k people across consecutive rows (in order), using whatever seats are available up to `maxRow`.

**Key insight**: Keep a Segment Tree for the **number of available seats in each row** (for range max — to find the first row with enough seats) and another for **prefix sums** (to quickly compute how many total seats are available in rows [0..r]).

```cpp
class BookMyShow {
    int n, m;
    vector<long long> sumTree;
    vector<int> maxTree;

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) { sumTree[node] = maxTree[node] = val; return; }
        int mid = l + (r - l) / 2;
        if (pos <= mid) update(2*node,   l,     mid, pos, val);
        else            update(2*node+1, mid+1, r,   pos, val);
        sumTree[node] = sumTree[2*node] + sumTree[2*node+1];
        maxTree[node] = max(maxTree[2*node], maxTree[2*node+1]);
    }

    long long querySum(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sumTree[node];
        int mid = l + (r - l) / 2;
        return querySum(2*node,   l,     mid, ql, qr)
             + querySum(2*node+1, mid+1, r,   ql, qr);
    }

    // Find leftmost position in [ql, qr] where maxTree >= k
    int queryFirst(int node, int l, int r, int ql, int qr, int k) {
        if (qr < l || r < ql || maxTree[node] < k) return -1;
        if (l == r) return l;
        int mid = l + (r - l) / 2;
        int leftResult = queryFirst(2*node, l, mid, ql, qr, k);
        if (leftResult != -1) return leftResult;   // found in left subtree first
        return queryFirst(2*node+1, mid+1, r, ql, qr, k);
    }

public:
    BookMyShow(int n, int m) : n(n), m(m),
        sumTree(4*n, 0), maxTree(4*n, 0) {
        // Initialize all rows to full capacity
        for (int i = 0; i < n; i++)
            update(1, 0, n-1, i, m);
    }

    vector<int> gather(int k, int maxRow) {
        int row = queryFirst(1, 0, n-1, 0, maxRow, k);
        if (row == -1) return {};
        int seatsTaken = m - (int)querySum(1, 0, n-1, row, row);
        update(1, 0, n-1, row, (int)querySum(1, 0, n-1, row, row) - k);
        return {row, seatsTaken};
    }

    bool scatter(int k, int maxRow) {
        if (querySum(1, 0, n-1, 0, maxRow) < k) return false;
        int remaining = k;
        // Greedily fill rows from top to bottom
        for (int row = 0; row <= maxRow && remaining > 0; row++) {
            int avail = (int)querySum(1, 0, n-1, row, row);
            if (avail > 0) {
                int take = min(avail, remaining);
                update(1, 0, n-1, row, avail - take);
                remaining -= take;
            }
        }
        return true;
    }
};
// Time: O(n log n) build, O(log n) gather, O(n log n) scatter worst case
```

---

### 🔗 LC 315 — Count of Smaller Numbers After Self

**Pattern**: C (coordinate compression + Segment Tree for counting).

**Problem**: For each element `nums[i]`, count how many elements to its **right** are smaller than `nums[i]`.

**Key insight**: Process elements **right to left**. Compress coordinates so all values map to indices 0..n-1. Maintain a Segment Tree that counts how many times each value has been seen so far (to the right of the current position). For each element, query "how many values in range [0, nums[i]-1] have been inserted?"

```cpp
class Solution {
    vector<int> tree;
    int N;

    void update(int pos) {
        for (pos++; pos <= N; pos += pos & (-pos))
            tree[pos]++;
    }

    int query(int pos) {
        int res = 0;
        for (pos++; pos > 0; pos -= pos & (-pos))
            res += tree[pos];
        return res;
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        // Coordinate compression
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        N = sorted.size();
        tree.assign(N + 1, 0);

        vector<int> result(nums.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            // Map value to compressed index
            int rank = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin();
            result[i] = (rank > 0) ? query(rank - 1) : 0;
            update(rank);
        }
        return result;
    }
};
// Time: O(n log n)   Space: O(n)
// Note: uses Fenwick Tree here (simpler for pure frequency counting)
// The Segment Tree version follows the exact same logic with the tree from Section 5
```

---

### 🔗 LC 699 — Falling Squares

**Pattern**: A (coordinate compression + range max + point update / range update).

**Problem**: Squares fall onto a number line. After each square falls, report the tallest stack height.

**Key insight**: Each fallen square occupies an interval `[left, right)` and sits on top of whatever is already there. We need the maximum existing height in `[left, right)` to compute the new stack height. Then update all positions in `[left, right)` to the new height. Coordinate-compress all left/right values first.

```cpp
class Solution {
    vector<int> tree, lazy;
    int N;

    void pushDown(int node) {
        if (lazy[node]) {
            tree[2*node]   = max(tree[2*node],   lazy[node]);
            tree[2*node+1] = max(tree[2*node+1], lazy[node]);
            lazy[2*node]   = max(lazy[2*node],   lazy[node]);
            lazy[2*node+1] = max(lazy[2*node+1], lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ul, int ur, int val) {
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            tree[node] = max(tree[node], val);
            lazy[node] = max(lazy[node], val);
            return;
        }
        pushDown(node);
        int mid = l + (r - l) / 2;
        update(2*node,   l,   mid, ul, ur, val);
        update(2*node+1, mid, r,   ul, ur, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        pushDown(node);
        int mid = l + (r - l) / 2;
        return max(query(2*node,   l,   mid, ql, qr),
                   query(2*node+1, mid, r,   ql, qr));
    }

public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // Coordinate compression
        vector<int> coords;
        for (auto& p : positions) {
            coords.push_back(p[0]);
            coords.push_back(p[0] + p[1]);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        N = coords.size();
        tree.assign(4*N, 0);
        lazy.assign(4*N, 0);

        auto compress = [&](int x) {
            return lower_bound(coords.begin(), coords.end(), x) - coords.begin();
        };

        vector<int> result;
        int maxH = 0;
        for (auto& p : positions) {
            int l = compress(p[0]), r = compress(p[0] + p[1]);
            int base = query(1, 0, N, l, r);   // max height in this interval
            int newH = base + p[1];
            update(1, 0, N, l, r, newH);
            maxH = max(maxH, newH);
            result.push_back(maxH);
        }
        return result;
    }
};
// Time: O(n log n)   Space: O(n)
```

---

### 🔗 LC 327 — Count of Range Sum

**Pattern**: C (merge-sort or Segment Tree + coordinate compression for range sum counting).

**Problem**: Count subarrays whose sum lies in `[lower, upper]`.

**Key insight**: Compute prefix sums. For each prefix sum `P[j]`, count how many previous prefix sums `P[i]` satisfy `lower <= P[j] - P[i] <= upper`, i.e., `P[j] - upper <= P[i] <= P[j] - lower`. Coordinate-compress all prefix sums, then use a Segment Tree to count prefix sums in a value range.

```cpp
class Solution {
    vector<int> tree;
    int N;

    void update(int node, int l, int r, int pos) {
        if (l == r) { tree[node]++; return; }
        int mid = l + (r - l) / 2;
        if (pos <= mid) update(2*node,   l,     mid, pos);
        else            update(2*node+1, mid+1, r,   pos);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > qr || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = l + (r - l) / 2;
        return query(2*node,   l,     mid, ql, qr)
             + query(2*node+1, mid+1, r,   ql, qr);
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + nums[i];

        // Coordinate compression on all prefix sums
        vector<long long> sorted_p = prefix;
        sort(sorted_p.begin(), sorted_p.end());
        sorted_p.erase(unique(sorted_p.begin(), sorted_p.end()), sorted_p.end());
        N = sorted_p.size();
        tree.assign(4*N, 0);

        auto compress = [&](long long val) {
            return (int)(lower_bound(sorted_p.begin(), sorted_p.end(), val) - sorted_p.begin());
        };

        int count = 0;
        for (long long p : prefix) {
            // Count previous prefix sums in [p - upper, p - lower]
            int lo = compress(p - upper);
            int hi = (int)(upper_bound(sorted_p.begin(), sorted_p.end(), p - lower) - sorted_p.begin()) - 1;
            if (lo <= hi) count += query(1, 0, N-1, lo, hi);
            update(1, 0, N-1, compress(p));
        }
        return count;
    }
};
// Time: O(n log n)   Space: O(n)
```

---

### 🔗 LC 2080 — Range Frequency Queries

**Pattern**: Segment Tree (or simpler: sorted indices per value) — highlights when a Segment Tree is and isn't the best tool.

**Problem**: Given an array, answer queries "how many times does `value` appear in subarray `[left, right]`?"

**Segment Tree approach**: Build a segment tree where each node stores a sorted list of indices where each value appears. For a query, find the value's occurrences in each of the O(log n) relevant nodes.

**Better approach for this problem**: Pre-group indices by value in a map, then binary search for count in [left, right] — O(log n) per query, O(n) space, much simpler.

```cpp
class RangeFreqQuery {
    unordered_map<int, vector<int>> positions;

public:
    RangeFreqQuery(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++)
            positions[arr[i]].push_back(i);
    }

    int query(int left, int right, int value) {
        auto it = positions.find(value);
        if (it == positions.end()) return 0;
        auto& v = it->second;
        // Count indices in [left, right]
        auto lo = lower_bound(v.begin(), v.end(), left);
        auto hi = upper_bound(v.begin(), v.end(), right);
        return hi - lo;
    }
};
// Time: O(n) build, O(log n) query   Space: O(n)
// Teaching point: Segment Tree is powerful, but sometimes simpler structures win.
```

---

### 🔗 LC 732 — My Calendar III

**Pattern**: B — Lazy Propagation (range add + range max query).

**Problem**: Count the maximum k such that there are k overlapping bookings at some point. Each booking adds 1 to all times in `[start, end)`.

**Key insight**: Maintain a Segment Tree over time with lazy range-add. For each booking, add 1 to the range `[start, end)`. The answer is `tree[root]` — the maximum value anywhere in the tree (which equals the maximum overlap count).

```cpp
class MyCalendarThree {
    map<int, int> tree, lazy;

    // Dynamic Segment Tree (coordinate range is huge: 0 to 10^9)
    void update(int l, int r, int lo, int hi, int val) {
        if (r < lo || hi < l) return;
        if (lo <= l && r <= hi) {
            tree[l] += val;
            lazy[l] += val;
            return;
        }
        int mid = l + (r - l) / 2;
        if (lazy.count(l)) {
            tree[mid+1] += lazy[l];   lazy[mid+1] += lazy[l];
            tree[mid]   += lazy[l];   lazy[mid]   += lazy[l];
            // Note: simplified push for this specific structure
        }
        update(l, mid, lo, hi, val);
        update(mid+1, r, lo, hi, val);
        tree[l] = max(tree.count(mid) ? tree[mid] : 0,
                      tree.count(mid+1) ? tree[mid+1] : 0) + lazy[l];
    }

public:
    // Cleaner approach for this problem: use a difference array with a map
    map<int, int> diff;

    int book(int start, int end) {
        diff[start]++;
        diff[end]--;
        int maxK = 0, cur = 0;
        for (auto& [t, d] : diff) {
            cur += d;
            maxK = max(maxK, cur);
        }
        return maxK;
    }
};
// Time: O(n log n) per booking (iterating sorted map)
// Space: O(n)
// Teaching note: The simple difference-array + sorted-map approach beats a full
// Lazy Segment Tree here because n is small (≤400). For larger n, use Lazy Seg Tree.
```

---

## 12. Common Mistakes & Debugging

### Mistake 1: Tree Array Too Small

```cpp
// WRONG — tree has 2*n nodes; doesn't work for non-power-of-2 sizes
vector<int> tree(2 * n, 0);

// RIGHT — 4*n is always safe
vector<int> tree(4 * n, 0);
```

The 4n bound exists because the tree must accommodate up to the next power of 2 above n, then doubled for 1-indexed storage.

### Mistake 2: Forgetting the Pull-Up After Update

```cpp
// WRONG — updated the leaf but forgot to update ancestors
void update(int node, int l, int r, int idx, int val) {
    if (l == r) { tree[node] = val; return; }
    int mid = l + (r - l) / 2;
    if (idx <= mid) update(2*node, l, mid, idx, val);
    else update(2*node+1, mid+1, r, idx, val);
    // MISSING: tree[node] = tree[2*node] + tree[2*node+1];
}

// RIGHT — always pull up after modifying children
void update(...) {
    ...recurse...
    tree[node] = tree[2*node] + tree[2*node+1];   // NEVER forget this
}
```

This is the single most common bug in Segment Tree implementations. After any recursive modification of a child, the parent must recompute its value.

### Mistake 3: Wrong Identity Element

```cpp
// For range SUM, identity is 0 — correct
// For range MIN, identity is INT_MAX — if you use 0, a non-visited node reports 0
//   which looks like a valid minimum and corrupts results!
// For range MAX, identity is INT_MIN (or 0 if values are non-negative)
// For range GCD, identity is 0 — gcd(0, x) = x for all x

// Always ask: "What value, when merged with any real value, leaves it unchanged?"
```

### Mistake 4: Forgetting `pushDown` in Lazy Propagation

```cpp
// WRONG — querying with lazy but not pushing down first
int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[node];
    // MISSING: pushDown(node, l, r);
    int mid = l + (r - l) / 2;
    return query(2*node, l, mid, ql, qr) + query(2*node+1, mid+1, r, ql, qr);
}

// RIGHT — pushDown BEFORE recursing into children, in BOTH update and query
int query(...) {
    ...
    pushDown(node, l, r);   // ALWAYS before touching children
    int mid = ...;
    return query(left child) + query(right child);
}
```

### Mistake 5: Wrong Segment Size in pushDown

```cpp
// WRONG — applying lazy without multiplying by segment size (for range-add + sum)
tree[2*node] += lazy[node];        // wrong — ignores how many elements are in left child

// RIGHT — left child covers [l, mid], which has (mid - l + 1) elements
tree[2*node]   += lazy[node] * (mid - l + 1);
tree[2*node+1] += lazy[node] * (r - mid);
```

### Mistake 6: Off-By-One in Mid Computation

```cpp
// SAFE: always use this form to avoid integer overflow
int mid = l + (r - l) / 2;   // equivalent to (l + r) / 2 but overflow-safe

// DANGEROUS for large l and r:
int mid = (l + r) / 2;       // l + r can overflow int if both are large!
```

### Debugging Checklist

```
☐ Is tree[] sized at least 4*n?
☐ Does every update() end with a pull-up: tree[node] = merge(left, right)?
☐ Is the identity element correct for my merge operation?
☐ For lazy propagation: does pushDown come BEFORE recursing into children?
☐ For lazy propagation: is the lazy value applied to tree[node] accounting for segment size?
☐ Is lazy[node] cleared to 0 after pushing down?
☐ Are range boundaries using half-open [l, r) vs closed [l, r] consistently throughout?
☐ Is the root at index 1 (not 0) in the tree array?
```

---

## 13. Quick Reference

### Core Templates

```cpp
// --- Segment Tree: Range Sum, Point Update ---
void build(int node, int l, int r)  // called as: build(1, 0, n-1)
void update(int node, int l, int r, int idx, int val)  // called: update(1, 0, n-1, idx, val)
int  query(int node, int l, int r, int ql, int qr)    // called: query(1, 0, n-1, ql, qr)

// --- Change only these two lines for different operations ---
int merge(int a, int b) { return a + b; }   // min(a,b) / max(a,b) / gcd(a,b) / a&b / a|b
int identity()          { return 0; }       // INT_MAX / INT_MIN / 0 / -1 / 0
```

### Node Index Arithmetic

```
Root:         index 1
Left child:   2 * node
Right child:  2 * node + 1
Parent:       node / 2

Segment split: mid = l + (r - l) / 2
Left child covers:  [l, mid]
Right child covers: [mid+1, r]
```

### Lazy Propagation Checklist

```
1. Apply lazy to tree[node]: tree[node] += lazy[node] * segment_size
2. Pass lazy to children:    lazy[child] += lazy[node]
3. Clear parent's lazy:      lazy[node] = 0
4. Call pushDown BEFORE recursing into children, in BOTH update() and query()
```

### Operation — Merge — Identity Table

| Operation | `merge(a, b)` | `identity()` |
|-----------|---------------|--------------|
| Sum | `a + b` | `0` |
| Min | `min(a, b)` | `INT_MAX` |
| Max | `max(a, b)` | `INT_MIN` |
| GCD | `__gcd(a, b)` | `0` |
| AND | `a & b` | `-1` (all bits 1) |
| OR | `a \| b` | `0` |
| XOR | `a ^ b` | `0` |

### Problem → Pattern Map

| LC # | Title | Pattern |
|------|-------|---------|
| 307 | Range Sum Query Mutable | Range query + point update |
| 699 | Falling Squares | Coordinate compress + range max + range update |
| 315 | Count of Smaller Numbers After Self | Coordinate compress + frequency counting |
| 327 | Count of Range Sum | Coordinate compress + prefix sum counting |
| 732 | My Calendar III | Range add + range max (Lazy propagation) |
| 2286 | Booking Concert Tickets | Range sum + range max + first-fit search |
| 2080 | Range Frequency Queries | Binary search on sorted indices (simpler wins) |

### When to Use a Segment Tree

```
✅ Range query (sum/min/max/GCD) + point updates
✅ Range query + range updates (add lazy propagation)
✅ Counting elements in a value range (coordinate compress first)
✅ Finding the first/last index satisfying a condition in a range
✅ Multiple different aggregates needed simultaneously (store struct in node)

❌ Only range queries, no updates → use prefix sums (simpler, faster)
❌ Only point queries, no range queries → use a plain array
❌ Only need sum/prefix queries on static data → prefix sums
❌ Simple frequency counting in a subarray → sorted positions + binary search
```

### Golden Rules

```
1. Tree array must be size 4*n — never 2*n or n.
2. Root is at index 1 — indexing from 1 makes left/right child arithmetic clean.
3. ALWAYS pull up after modifying children: tree[node] = merge(left, right).
4. For lazy propagation: pushDown BEFORE recursing, in BOTH update and query.
5. Segment size matters in pushDown: multiply lazy by (r - l + 1) for sum trees.
6. Change only merge() and identity() to switch between sum/min/max/GCD.
7. For huge index ranges (up to 10^9): coordinate compress or use dynamic Seg Tree.
8. Prefer Segment Tree over Fenwick Tree when you need range updates or non-invertible operations (min, max, GCD).
9. Write build() + update() + query() — test on small examples before submitting.
10. When in doubt, draw the tree for n=4 on paper and trace your code by hand.
```

---

*End of Segment Trees — Deep Dive*
