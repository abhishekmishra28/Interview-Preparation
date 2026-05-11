/*
================================================================================
BINARY TREE COMPLETE ROADMAP - ALL 50 SOLUTIONS
================================================================================
Language  : C++17
Author    : Complete Binary Tree Reference
Note      : All solutions self-contained, TreeNode defined once at top
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// COMMON TREE NODE DEFINITION
// ============================================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

// Node with next pointer (for LC 116, 117)
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int x, Node* left, Node* right, Node* next)
        : val(x), left(left), right(right), next(next) {}
};

// ============================================================================
// HELPER: Build tree from level-order array (for testing)
// ============================================================================

TreeNode* buildTree(vector<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)vals.size()) {
        TreeNode* node = q.front(); q.pop();
        if (i < (int)vals.size() && vals[i] != -1) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        if (i < (int)vals.size() && vals[i] != -1) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// ============================================================================
// PROBLEM 1: Binary Tree Inorder Traversal (LC 94)
// ============================================================================
/*
   APPROACH: Recursive DFS - Left -> Root -> Right
   TIME: O(n)  SPACE: O(h) where h = height
*/

class Solution_LC94 {
public:
    void inorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        inorderHelper(root->left, result);
        result.push_back(root->val);
        inorderHelper(root->right, result);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }

    // ITERATIVE version using stack
    vector<int> inorderIterative(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* curr = root;

        while (curr || !st.empty()) {
            // Go as left as possible
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            // Process node
            curr = st.top(); st.pop();
            result.push_back(curr->val);
            // Move to right subtree
            curr = curr->right;
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 2: Binary Tree Preorder Traversal (LC 144)
// ============================================================================
/*
   APPROACH: Root -> Left -> Right
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC144 {
public:
    void preorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        result.push_back(root->val);   // Process root first
        preorderHelper(root->left, result);
        preorderHelper(root->right, result);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorderHelper(root, result);
        return result;
    }

    // ITERATIVE version
    vector<int> preorderIterative(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top(); st.pop();
            result.push_back(node->val);
            // Push right first so left is processed first
            if (node->right) st.push(node->right);
            if (node->left)  st.push(node->left);
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 3: Binary Tree Postorder Traversal (LC 145)
// ============================================================================
/*
   APPROACH: Left -> Right -> Root
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC145 {
public:
    void postorderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        postorderHelper(root->left, result);
        postorderHelper(root->right, result);
        result.push_back(root->val);   // Process root last
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postorderHelper(root, result);
        return result;
    }

    // ITERATIVE: reverse of modified preorder (Root->Right->Left reversed)
    vector<int> postorderIterative(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top(); st.pop();
            result.push_back(node->val);
            // Push left first (will be processed after right)
            if (node->left)  st.push(node->left);
            if (node->right) st.push(node->right);
        }
        // Reverse gives Left->Right->Root
        reverse(result.begin(), result.end());
        return result;
    }
};

// ============================================================================
// PROBLEM 4: Binary Tree Level Order Traversal (LC 102)
// ============================================================================
/*
   APPROACH: BFS with queue, track level size
   TIME: O(n)  SPACE: O(n) for queue
*/

class Solution_LC102 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();        // Nodes at current level
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                currentLevel.push_back(node->val);

                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(currentLevel);
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 5: Maximum Depth of Binary Tree (LC 104)
// ============================================================================
/*
   APPROACH: DFS - depth = 1 + max(left depth, right depth)
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC104 {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        // Recursively get depth of left and right subtrees
        int leftDepth  = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return 1 + max(leftDepth, rightDepth);
    }

    // BFS approach - count levels
    int maxDepthBFS(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            depth++;
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return depth;
    }
};

// ============================================================================
// PROBLEM 6: Invert Binary Tree (LC 226)
// ============================================================================
/*
   APPROACH: Swap left and right children at every node recursively
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC226 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        // Swap children
        swap(root->left, root->right);
        // Recursively invert both subtrees
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }

    // BFS approach
    TreeNode* invertTreeBFS(TreeNode* root) {
        if (!root) return nullptr;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            swap(node->left, node->right);   // Swap at each node
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return root;
    }
};

// ============================================================================
// PROBLEM 7: Same Tree (LC 100)
// ============================================================================
/*
   APPROACH: Compare nodes recursively - both null, or same val + same subtrees
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC100 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Both null - same
        if (!p && !q) return true;
        // One null, one not - different
        if (!p || !q) return false;
        // Values differ - different
        if (p->val != q->val) return false;
        // Check both subtrees
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};

// ============================================================================
// PROBLEM 8: Symmetric Tree (LC 101)
// ============================================================================
/*
   APPROACH: Tree is symmetric if left subtree mirrors right subtree
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC101 {
public:
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (!left && !right) return true;
        if (!left || !right) return false;
        // Same value AND outer pairs match AND inner pairs match
        return (left->val == right->val) &&
               isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }

    // Iterative BFS approach
    bool isSymmetricBFS(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty()) {
            TreeNode* left  = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();

            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val != right->val) return false;

            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }
        return true;
    }
};

// ============================================================================
// PROBLEM 9: Subtree of Another Tree (LC 572)
// ============================================================================
/*
   APPROACH: For each node in main tree, check if subRoot matches using isSame
   TIME: O(m*n)  SPACE: O(h)
*/

class Solution_LC572 {
public:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        if (!s && !t) return true;
        if (!s || !t) return false;
        return (s->val == t->val) &&
               isSameTree(s->left, t->left) &&
               isSameTree(s->right, t->right);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) return false;
        // Check if current node matches
        if (isSameTree(root, subRoot)) return true;
        // Check left and right subtrees
        return isSubtree(root->left, subRoot) ||
               isSubtree(root->right, subRoot);
    }
};

// ============================================================================
// PROBLEM 10: Path Sum (LC 112)
// ============================================================================
/*
   APPROACH: Subtract node value from target, check if leaf with val==0
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC112 {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        // At leaf node, check remaining sum
        if (!root->left && !root->right) {
            return root->val == targetSum;
        }
        // Recurse with reduced target
        int remaining = targetSum - root->val;
        return hasPathSum(root->left, remaining) ||
               hasPathSum(root->right, remaining);
    }
};

// ============================================================================
// PROBLEM 11: Binary Tree Paths (LC 257)
// ============================================================================
/*
   APPROACH: DFS backtracking, build path string, add at leaf
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC257 {
public:
    void dfs(TreeNode* node, string path, vector<string>& result) {
        if (!node) return;
        path += to_string(node->val);

        if (!node->left && !node->right) {
            result.push_back(path);    // Leaf reached
            return;
        }
        path += "->";
        dfs(node->left, path, result);
        dfs(node->right, path, result);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        dfs(root, "", result);
        return result;
    }
};

// ============================================================================
// PROBLEM 12: Average of Levels in Binary Tree (LC 637)
// ============================================================================
/*
   APPROACH: BFS level order, compute average per level
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC637 {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            double levelSum = 0;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                levelSum += node->val;
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(levelSum / levelSize);
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 13: Minimum Depth of Binary Tree (LC 111)
// ============================================================================
/*
   APPROACH: BFS - first leaf node found gives minimum depth
   KEY INSIGHT: Must handle single-child nodes carefully
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC111 {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        // BFS finds shortest path first
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            depth++;
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                // First leaf = minimum depth
                if (!node->left && !node->right) return depth;
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return depth;
    }

    // DFS approach - careful with single child nodes
    int minDepthDFS(TreeNode* root) {
        if (!root) return 0;
        // If no left child, minimum is in right subtree
        if (!root->left) return 1 + minDepthDFS(root->right);
        // If no right child, minimum is in left subtree
        if (!root->right) return 1 + minDepthDFS(root->left);
        return 1 + min(minDepthDFS(root->left), minDepthDFS(root->right));
    }
};

// ============================================================================
// PROBLEM 14: Binary Tree Zigzag Level Order Traversal (LC 103)
// ============================================================================
/*
   APPROACH: BFS level order, alternate direction each level
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC103 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level(levelSize);

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                // Place in correct position based on direction
                int idx = leftToRight ? i : (levelSize - 1 - i);
                level[idx] = node->val;

                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(level);
            leftToRight = !leftToRight;    // Flip direction
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 15: Binary Tree Right Side View (LC 199)
// ============================================================================
/*
   APPROACH: BFS - last node at each level is visible from right
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC199 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                // Last node in level is rightmost visible
                if (i == levelSize - 1) result.push_back(node->val);
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return result;
    }

    // DFS approach - process right before left
    void dfs(TreeNode* node, int depth, vector<int>& result) {
        if (!node) return;
        if (depth == (int)result.size()) result.push_back(node->val);
        dfs(node->right, depth + 1, result);   // Right first
        dfs(node->left,  depth + 1, result);
    }

    vector<int> rightSideViewDFS(TreeNode* root) {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }
};

// ============================================================================
// PROBLEM 16: Count Good Nodes in Binary Tree (LC 1448)
// ============================================================================
/*
   APPROACH: DFS tracking max value on path from root
   A node is "good" if no value greater than it exists on path from root
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC1448 {
public:
    int dfs(TreeNode* node, int maxSoFar) {
        if (!node) return 0;
        // Good if current val >= max on path
        int good = (node->val >= maxSoFar) ? 1 : 0;
        int newMax = max(maxSoFar, node->val);
        return good +
               dfs(node->left,  newMax) +
               dfs(node->right, newMax);
    }

    int goodNodes(TreeNode* root) {
        return dfs(root, INT_MIN);
    }
};

// ============================================================================
// PROBLEM 17: Kth Smallest Element in a BST (LC 230)
// ============================================================================
/*
   APPROACH: Inorder traversal of BST gives sorted order
   Count nodes until we reach kth
   TIME: O(h+k)  SPACE: O(h)
*/

class Solution_LC230 {
public:
    int result = 0;
    int count  = 0;

    void inorder(TreeNode* node, int k) {
        if (!node) return;
        inorder(node->left, k);
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        inorder(node->right, k);
    }

    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return result;
    }

    // Iterative approach
    int kthSmallestIterative(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* curr = root;
        int n = 0;

        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            n++;
            if (n == k) return curr->val;
            curr = curr->right;
        }
        return -1;
    }
};

// ============================================================================
// PROBLEM 18: Validate Binary Search Tree (LC 98)
// ============================================================================
/*
   APPROACH: Pass min/max bounds, every node must be within its valid range
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC98 {
public:
    bool validate(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) return true;
        // Current node must be within (minVal, maxVal)
        if (node->val <= minVal || node->val >= maxVal) return false;
        // Left subtree: values must be < node->val
        // Right subtree: values must be > node->val
        return validate(node->left,  minVal,    node->val) &&
               validate(node->right, node->val, maxVal);
    }

    bool isValidBST(TreeNode* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
};

// ============================================================================
// PROBLEM 19: Construct Binary Tree from Preorder and Inorder (LC 105)
// ============================================================================
/*
   APPROACH:
   - Preorder[0] is always root
   - Find root in inorder to split left/right subtrees
   - Recurse for each subtree
   TIME: O(n)  SPACE: O(n) for hashmap
*/

class Solution_LC105 {
public:
    unordered_map<int, int> inorderIndex;

    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& inorder,  int inStart,  int inEnd) {
        if (preStart > preEnd) return nullptr;

        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        int mid = inorderIndex[rootVal];   // Position in inorder
        int leftSize = mid - inStart;       // Number of nodes in left subtree

        root->left = build(preorder, preStart + 1, preStart + leftSize,
                           inorder,  inStart,       mid - 1);
        root->right = build(preorder, preStart + leftSize + 1, preEnd,
                            inorder,  mid + 1,                 inEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < (int)inorder.size(); i++) {
            inorderIndex[inorder[i]] = i;
        }
        int n = preorder.size();
        return build(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};

// ============================================================================
// PROBLEM 20: Construct Binary Tree from Inorder and Postorder (LC 106)
// ============================================================================
/*
   APPROACH:
   - Postorder last element is root
   - Find root in inorder to split subtrees
   - Recurse
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC106 {
public:
    unordered_map<int, int> inorderIdx;

    TreeNode* build(vector<int>& inorder,  int inStart,  int inEnd,
                    vector<int>& postorder, int postStart, int postEnd) {
        if (postStart > postEnd) return nullptr;

        int rootVal = postorder[postEnd];   // Last in postorder is root
        TreeNode* root = new TreeNode(rootVal);

        int mid = inorderIdx[rootVal];
        int leftSize = mid - inStart;

        root->left = build(inorder, inStart, mid - 1,
                           postorder, postStart, postStart + leftSize - 1);
        root->right = build(inorder, mid + 1, inEnd,
                            postorder, postStart + leftSize, postEnd - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < (int)inorder.size(); i++) {
            inorderIdx[inorder[i]] = i;
        }
        int n = inorder.size();
        return build(inorder, 0, n - 1, postorder, 0, n - 1);
    }
};

// ============================================================================
// PROBLEM 21: Path Sum II (LC 113)
// ============================================================================
/*
   APPROACH: DFS backtracking, collect all root-to-leaf paths with target sum
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC113 {
public:
    void dfs(TreeNode* node, int target, vector<int>& path,
             vector<vector<int>>& result) {
        if (!node) return;
        path.push_back(node->val);

        if (!node->left && !node->right && node->val == target) {
            result.push_back(path);   // Valid path found
        }
        dfs(node->left,  target - node->val, path, result);
        dfs(node->right, target - node->val, path, result);

        path.pop_back();   // Backtrack
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(root, targetSum, path, result);
        return result;
    }
};

// ============================================================================
// PROBLEM 22: Sum Root to Leaf Numbers (LC 129)
// ============================================================================
/*
   APPROACH: DFS, build number as we go down (num = num*10 + node->val)
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC129 {
public:
    int dfs(TreeNode* node, int currentNum) {
        if (!node) return 0;
        currentNum = currentNum * 10 + node->val;
        // At leaf, return the number formed
        if (!node->left && !node->right) return currentNum;
        return dfs(node->left,  currentNum) +
               dfs(node->right, currentNum);
    }

    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
};

// ============================================================================
// PROBLEM 23: Pseudo-Palindromic Paths in a Binary Tree (LC 1457)
// ============================================================================
/*
   APPROACH: Use bitmask to track digit frequencies
   Path is pseudo-palindromic if at most one digit has odd count
   XOR with digit flips the bit - valid if bitmask has at most 1 bit set
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC1457 {
public:
    int dfs(TreeNode* node, int mask) {
        if (!node) return 0;
        // Flip bit for current digit
        mask ^= (1 << node->val);
        if (!node->left && !node->right) {
            // At most one odd-frequency digit: mask is 0 or power of 2
            return (mask & (mask - 1)) == 0 ? 1 : 0;
        }
        return dfs(node->left,  mask) +
               dfs(node->right, mask);
    }

    int pseudoPalindromicPaths(TreeNode* root) {
        return dfs(root, 0);
    }
};

// ============================================================================
// PROBLEM 24: Lowest Common Ancestor of a Binary Tree (LC 236)
// ============================================================================
/*
   APPROACH: If current node is p or q, return it.
   If p found in left and q in right (or vice versa), current is LCA.
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC236 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        // If root is p or q, it's the LCA
        if (root == p || root == q) return root;

        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // p and q found in different subtrees
        if (left && right) return root;
        // Return whichever side found something
        return left ? left : right;
    }
};

// ============================================================================
// PROBLEM 25: Lowest Common Ancestor of a BST (LC 235)
// ============================================================================
/*
   APPROACH: Use BST property
   - If both p,q < root: LCA is in left subtree
   - If both p,q > root: LCA is in right subtree
   - Otherwise: root is LCA
   TIME: O(h)  SPACE: O(1)
*/

class Solution_LC235 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;    // Both in left subtree
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;   // Both in right subtree
            } else {
                return root;          // Split point = LCA
            }
        }
        return nullptr;
    }
};

// ============================================================================
// PROBLEM 26: Balanced Binary Tree (LC 110)
// ============================================================================
/*
   APPROACH: Check height of each subtree, return -1 if unbalanced
   A tree is balanced if |left height - right height| <= 1 for all nodes
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC110 {
public:
    int checkHeight(TreeNode* node) {
        if (!node) return 0;

        int leftH  = checkHeight(node->left);
        if (leftH == -1) return -1;    // Left is unbalanced

        int rightH = checkHeight(node->right);
        if (rightH == -1) return -1;   // Right is unbalanced

        // Check balance at current node
        if (abs(leftH - rightH) > 1) return -1;

        return 1 + max(leftH, rightH);
    }

    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
};

// ============================================================================
// PROBLEM 27: Diameter of Binary Tree (LC 543)
// ============================================================================
/*
   APPROACH: At each node, diameter = leftHeight + rightHeight
   Track global maximum
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC543 {
public:
    int maxDiameter = 0;

    int height(TreeNode* node) {
        if (!node) return 0;
        int leftH  = height(node->left);
        int rightH = height(node->right);
        // Update max diameter at this node
        maxDiameter = max(maxDiameter, leftH + rightH);
        return 1 + max(leftH, rightH);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return maxDiameter;
    }
};

// ============================================================================
// PROBLEM 28: Binary Tree Level Order Traversal II (LC 107)
// ============================================================================
/*
   APPROACH: Same as LC 102 but reverse the result at end
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC107 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front(); q.pop();
                level.push_back(node->val);
                if (node->left)  q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(level);
        }
        reverse(result.begin(), result.end());   // Bottom-up
        return result;
    }
};

// ============================================================================
// PROBLEM 29: Populating Next Right Pointers in Each Node (LC 116)
// ============================================================================
/*
   APPROACH: Use already established next pointers at current level
   to set next pointers for next level (perfect binary tree)
   TIME: O(n)  SPACE: O(1)
*/

class Solution_LC116 {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        Node* leftmost = root;

        while (leftmost->left) {   // While not at last level
            Node* curr = leftmost;
            while (curr) {
                // Connect children of current node
                curr->left->next = curr->right;
                // Connect across parent boundary
                if (curr->next) curr->right->next = curr->next->left;
                curr = curr->next;
            }
            leftmost = leftmost->left;   // Move to next level
        }
        return root;
    }
};

// ============================================================================
// PROBLEM 30: Populating Next Right Pointers in Each Node II (LC 117)
// ============================================================================
/*
   APPROACH: Handle non-perfect tree using a dummy node to track next level
   TIME: O(n)  SPACE: O(1)
*/

class Solution_LC117 {
public:
    Node* connect(Node* root) {
        Node* curr = root;

        while (curr) {
            Node dummy(0);           // Dummy head for next level
            Node* tail = &dummy;     // Tail to build next level's next chain

            while (curr) {
                if (curr->left) {
                    tail->next = curr->left;
                    tail = tail->next;
                }
                if (curr->right) {
                    tail->next = curr->right;
                    tail = tail->next;
                }
                curr = curr->next;   // Move to next node in current level
            }
            curr = dummy.next;       // Move to next level
        }
        return root;
    }
};

// ============================================================================
// PROBLEM 31: Insert into a Binary Search Tree (LC 701)
// ============================================================================
/*
   APPROACH: BST property - go left if val < root, right if val > root
   Insert at null position
   TIME: O(h)  SPACE: O(h)
*/

class Solution_LC701 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);

        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};

// ============================================================================
// PROBLEM 32: Delete Node in a BST (LC 450)
// ============================================================================
/*
   APPROACH:
   1. Find node to delete
   2. If leaf: just remove
   3. If one child: replace with child
   4. If two children: replace with inorder successor (leftmost in right subtree)
   TIME: O(h)  SPACE: O(h)
*/

class Solution_LC450 {
public:
    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node to delete found
            if (!root->left) return root->right;    // No left child
            if (!root->right) return root->left;    // No right child

            // Two children: find inorder successor
            TreeNode* successor = findMin(root->right);
            root->val = successor->val;             // Copy successor value
            root->right = deleteNode(root->right, successor->val);
        }
        return root;
    }
};

// ============================================================================
// PROBLEM 33: Convert Sorted Array to Binary Search Tree (LC 108)
// ============================================================================
/*
   APPROACH: Always pick middle element as root for balanced tree
   Recurse on left half and right half
   TIME: O(n)  SPACE: O(log n) stack
*/

class Solution_LC108 {
public:
    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + (right - left) / 2;    // Middle element as root
        TreeNode* root = new TreeNode(nums[mid]);
        root->left  = build(nums, left, mid - 1);
        root->right = build(nums, mid + 1, right);
        return root;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
};

// ============================================================================
// PROBLEM 34: House Robber III (LC 337)
// ============================================================================
/*
   APPROACH: Tree DP - for each node return [rob_this, skip_this]
   If rob current: can't rob children
   If skip current: take max of robbing or skipping each child
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC337 {
public:
    // Returns {rob_current, skip_current}
    pair<int,int> dfs(TreeNode* node) {
        if (!node) return {0, 0};

        auto [leftRob,  leftSkip]  = dfs(node->left);
        auto [rightRob, rightSkip] = dfs(node->right);

        // Rob current: can't rob children
        int robCurrent  = node->val + leftSkip + rightSkip;
        // Skip current: take best of each child
        int skipCurrent = max(leftRob, leftSkip) + max(rightRob, rightSkip);

        return {robCurrent, skipCurrent};
    }

    int rob(TreeNode* root) {
        auto [robRoot, skipRoot] = dfs(root);
        return max(robRoot, skipRoot);
    }
};

// ============================================================================
// PROBLEM 35: Longest Univalue Path (LC 687)
// ============================================================================
/*
   APPROACH: At each node, find longest univalue path going left and right
   Can only extend path if child has same value
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC687 {
public:
    int maxLen = 0;

    int dfs(TreeNode* node) {
        if (!node) return 0;

        int leftLen  = dfs(node->left);
        int rightLen = dfs(node->right);

        // Extend only if same value
        int leftPath  = (node->left  && node->left->val  == node->val)
                            ? leftLen  + 1 : 0;
        int rightPath = (node->right && node->right->val == node->val)
                            ? rightLen + 1 : 0;

        maxLen = max(maxLen, leftPath + rightPath);   // Path through this node
        return max(leftPath, rightPath);               // Return longest single arm
    }

    int longestUnivaluePath(TreeNode* root) {
        dfs(root);
        return maxLen;
    }
};

// ============================================================================
// PROBLEM 36: Binary Tree Maximum Path Sum (LC 124)
// ============================================================================
/*
   APPROACH: At each node, max gain = node->val + max(0, left gain, right gain)
   But for the path sum, we can use both left and right arms
   Track global maximum
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC124 {
public:
    int maxSum = INT_MIN;

    int maxGain(TreeNode* node) {
        if (!node) return 0;

        // Max gain from left/right (ignore if negative)
        int leftGain  = max(0, maxGain(node->left));
        int rightGain = max(0, maxGain(node->right));

        // Path through this node (can use both arms)
        int pathSum = node->val + leftGain + rightGain;
        maxSum = max(maxSum, pathSum);

        // Return max single-arm gain (can only go one direction up)
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};

// ============================================================================
// PROBLEM 37: Serialize and Deserialize Binary Tree (LC 297)
// ============================================================================
/*
   APPROACH: Preorder DFS serialization with null markers
   Use "#" for null, "," as delimiter
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC297 {
public:
    string serialize(TreeNode* root) {
        if (!root) return "#,";
        return to_string(root->val) + "," +
               serialize(root->left) +
               serialize(root->right);
    }

    TreeNode* deserializeHelper(istringstream& ss) {
        string token;
        getline(ss, token, ',');
        if (token == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(token));
        node->left  = deserializeHelper(ss);
        node->right = deserializeHelper(ss);
        return node;
    }

    TreeNode* deserialize(string data) {
        istringstream ss(data);
        return deserializeHelper(ss);
    }
};

// ============================================================================
// PROBLEM 38: Recover Binary Search Tree (LC 99)
// ============================================================================
/*
   APPROACH: Inorder of BST should be sorted
   Find two swapped nodes during inorder traversal
   Swap their values back
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC99 {
public:
    TreeNode* first  = nullptr;   // First wrong node
    TreeNode* second = nullptr;   // Second wrong node
    TreeNode* prev   = nullptr;   // Previous node in inorder

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);

        // Found inversion (prev should be smaller than current)
        if (prev && prev->val > node->val) {
            if (!first) first = prev;    // First wrong node
            second = node;               // Always update second
        }
        prev = node;
        inorder(node->right);
    }

    void recoverTree(TreeNode* root) {
        inorder(root);
        swap(first->val, second->val);   // Fix the two swapped nodes
    }
};

// ============================================================================
// PROBLEM 39: Binary Tree Cameras (LC 968)
// ============================================================================
/*
   APPROACH: Greedy DFS - place cameras at leaves' parents
   State: 0 = uncovered, 1 = has camera, 2 = covered (no camera)
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC968 {
public:
    int cameras = 0;

    // Returns: 0=not covered, 1=has camera, 2=covered
    int dfs(TreeNode* node) {
        if (!node) return 2;   // Null = covered (no need for camera)

        int left  = dfs(node->left);
        int right = dfs(node->right);

        // If any child is uncovered, must place camera here
        if (left == 0 || right == 0) {
            cameras++;
            return 1;
        }
        // If any child has camera, this node is covered
        if (left == 1 || right == 1) return 2;

        // Both children are covered but no camera pointing up
        return 0;
    }

    int minCameraCover(TreeNode* root) {
        // If root itself is uncovered, add one more camera
        if (dfs(root) == 0) cameras++;
        return cameras;
    }
};

// ============================================================================
// PROBLEM 40: Distribute Coins in Binary Tree (LC 979)
// ============================================================================
/*
   APPROACH: Each node returns excess coins (positive = too many, negative = too few)
   Moves = sum of absolute excess at each node
   TIME: O(n)  SPACE: O(h)
*/

class Solution_LC979 {
public:
    int moves = 0;

    int dfs(TreeNode* node) {
        if (!node) return 0;

        int leftExcess  = dfs(node->left);
        int rightExcess = dfs(node->right);

        // Each excess coin needs one move
        moves += abs(leftExcess) + abs(rightExcess);

        // Return excess from this subtree: coins - 1 needed slot + from children
        return node->val - 1 + leftExcess + rightExcess;
    }

    int distributeCoins(TreeNode* root) {
        dfs(root);
        return moves;
    }
};

// ============================================================================
// PROBLEM 41: Vertical Order Traversal of a Binary Tree (LC 987)
// ============================================================================
/*
   APPROACH: Track (col, row) for each node
   Group by column, sort by row then value within same column
   TIME: O(n log n)  SPACE: O(n)
*/

class Solution_LC987 {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // {col, {row, val}} entries
        vector<tuple<int,int,int>> nodes;

        // DFS to collect all nodes with their positions
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node,
                                                        int row, int col) {
            if (!node) return;
            nodes.emplace_back(col, row, node->val);
            dfs(node->left,  row + 1, col - 1);
            dfs(node->right, row + 1, col + 1);
        };

        dfs(root, 0, 0);
        sort(nodes.begin(), nodes.end());   // Sort by col, then row, then val

        vector<vector<int>> result;
        int prevCol = INT_MIN;

        for (auto& [col, row, val] : nodes) {
            if (col != prevCol) {
                result.push_back({});
                prevCol = col;
            }
            result.back().push_back(val);
        }
        return result;
    }
};

// ============================================================================
// PROBLEM 42: Construct Binary Tree from Preorder and Postorder (LC 889)
// ============================================================================
/*
   APPROACH:
   - preorder[0] = root
   - preorder[1] = left subtree root
   - Find preorder[1] in postorder to determine left subtree size
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC889 {
public:
    unordered_map<int,int> postIdx;

    TreeNode* build(vector<int>& pre, int preL, int preR,
                    vector<int>& post, int postL, int postR) {
        if (preL > preR) return nullptr;

        TreeNode* root = new TreeNode(pre[preL]);
        if (preL == preR) return root;

        // Left subtree root is pre[preL+1]
        int leftRootVal  = pre[preL + 1];
        int leftRootPost = postIdx[leftRootVal];
        int leftSize     = leftRootPost - postL + 1;

        root->left = build(pre,  preL + 1, preL + leftSize,
                           post, postL,    leftRootPost);
        root->right = build(pre,  preL + leftSize + 1, preR,
                            post, leftRootPost + 1,    postR - 1);
        return root;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        for (int i = 0; i < n; i++) postIdx[postorder[i]] = i;
        return build(preorder, 0, n - 1, postorder, 0, n - 1);
    }
};

// ============================================================================
// PROBLEM 43: All Nodes Distance K in Binary Tree (LC 863)
// ============================================================================
/*
   APPROACH: Convert tree to undirected graph, then BFS from target
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC863 {
public:
    // Build adjacency list treating tree as undirected graph
    void buildGraph(TreeNode* node, unordered_map<int, vector<int>>& graph) {
        if (!node) return;
        if (node->left) {
            graph[node->val].push_back(node->left->val);
            graph[node->left->val].push_back(node->val);
            buildGraph(node->left, graph);
        }
        if (node->right) {
            graph[node->val].push_back(node->right->val);
            graph[node->right->val].push_back(node->val);
            buildGraph(node->right, graph);
        }
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<int, vector<int>> graph;
        buildGraph(root, graph);

        // BFS from target
        queue<int> q;
        unordered_set<int> visited;
        q.push(target->val);
        visited.insert(target->val);
        int dist = 0;

        while (!q.empty()) {
            if (dist == k) {
                vector<int> result;
                while (!q.empty()) {
                    result.push_back(q.front());
                    q.pop();
                }
                return result;
            }
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int node = q.front(); q.pop();
                for (int neighbor : graph[node]) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            dist++;
        }
        return {};
    }
};

// ============================================================================
// PROBLEM 44: Unique Binary Search Trees II (LC 95)
// ============================================================================
/*
   APPROACH: For each value i as root, left subtree from [1,i-1], right from [i+1,n]
   Combine all left and right possibilities
   TIME: O(Catalan(n))  SPACE: O(Catalan(n))
*/

class Solution_LC95 {
public:
    vector<TreeNode*> generate(int start, int end) {
        if (start > end) return {nullptr};

        vector<TreeNode*> allTrees;

        for (int i = start; i <= end; i++) {
            // Generate all left and right subtrees
            vector<TreeNode*> leftTrees  = generate(start, i - 1);
            vector<TreeNode*> rightTrees = generate(i + 1, end);

            // Combine each pair
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left  = left;
                    root->right = right;
                    allTrees.push_back(root);
                }
            }
        }
        return allTrees;
    }

    vector<TreeNode*> generateTrees(int n) {
        return generate(1, n);
    }
};

// ============================================================================
// PROBLEM 45: Binary Search Tree Iterator (LC 173)
// ============================================================================
/*
   APPROACH: Simulate inorder traversal using a stack
   next() and hasNext() both O(1) amortized
   TIME: O(1) amortized  SPACE: O(h)
*/

class BSTIterator {
private:
    stack<TreeNode*> st;

    void pushLeft(TreeNode* node) {
        // Push all left nodes from current node
        while (node) {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        pushLeft(root);
    }

    int next() {
        TreeNode* node = st.top(); st.pop();
        pushLeft(node->right);     // Push left spine of right subtree
        return node->val;
    }

    bool hasNext() {
        return !st.empty();
    }
};

// ============================================================================
// PROBLEM 46: Flatten Binary Tree to Linked List (LC 114)
// ============================================================================
/*
   APPROACH: Morris-like traversal
   For each node, attach right subtree to end of left subtree's rightmost node
   Then move left subtree to right
   TIME: O(n)  SPACE: O(1)
*/

class Solution_LC114 {
public:
    void flatten(TreeNode* root) {
        TreeNode* curr = root;

        while (curr) {
            if (curr->left) {
                // Find rightmost node of left subtree
                TreeNode* rightmost = curr->left;
                while (rightmost->right) rightmost = rightmost->right;

                // Attach current right subtree to rightmost
                rightmost->right = curr->right;
                // Move left subtree to right
                curr->right = curr->left;
                curr->left  = nullptr;
            }
            curr = curr->right;
        }
    }

    // Recursive approach (reverse postorder: right, left, root)
    TreeNode* prev = nullptr;

    void flattenRecursive(TreeNode* root) {
        if (!root) return;
        flattenRecursive(root->right);
        flattenRecursive(root->left);
        root->right = prev;
        root->left  = nullptr;
        prev = root;
    }
};

// ============================================================================
// PROBLEM 47: Delete Nodes And Return Forest (LC 1110)
// ============================================================================
/*
   APPROACH: DFS post-order
   If node to delete: its children become new roots
   Return nullptr to parent after deletion
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC1110 {
public:
    vector<TreeNode*> result;
    unordered_set<int> toDelete;

    TreeNode* dfs(TreeNode* node, bool isRoot) {
        if (!node) return nullptr;

        bool deleted = toDelete.count(node->val);
        // If this node is a root of a new tree, add to result
        if (isRoot && !deleted) result.push_back(node);

        // Children become roots if current node is deleted
        node->left  = dfs(node->left,  deleted);
        node->right = dfs(node->right, deleted);

        return deleted ? nullptr : node;
    }

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for (int x : to_delete) toDelete.insert(x);
        dfs(root, true);
        return result;
    }
};

// ============================================================================
// PROBLEM 48: Smallest String Starting From Leaf (LC 988)
// ============================================================================
/*
   APPROACH: DFS collecting path strings, compare at leaves
   Build string in reverse (leaf to root) and compare
   TIME: O(n * h)  SPACE: O(h)
*/

class Solution_LC988 {
public:
    string result = "";

    void dfs(TreeNode* node, string path) {
        if (!node) return;
        // Prepend current char (building leaf-to-root)
        path = char('a' + node->val) + path;

        if (!node->left && !node->right) {
            // At leaf, compare with current minimum
            if (result.empty() || path < result) result = path;
            return;
        }
        dfs(node->left,  path);
        dfs(node->right, path);
    }

    string smallestFromLeaf(TreeNode* root) {
        dfs(root, "");
        return result;
    }
};

// ============================================================================
// PROBLEM 49: Maximum Width of Binary Tree (LC 662)
// ============================================================================
/*
   APPROACH: BFS with position indices
   Width = rightmost_pos - leftmost_pos + 1 at each level
   Normalize indices to prevent overflow
   TIME: O(n)  SPACE: O(n)
*/

class Solution_LC662 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        int maxWidth = 0;
        // Queue stores {node, index} where left child = 2*i, right = 2*i+1
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 1});

        while (!q.empty()) {
            int sz = q.size();
            unsigned long long leftIdx  = q.front().second;
            unsigned long long rightIdx = leftIdx;

            for (int i = 0; i < sz; i++) {
                auto [node, idx] = q.front(); q.pop();
                // Normalize by subtracting leftIdx to prevent overflow
                unsigned long long normIdx = idx - leftIdx;
                rightIdx = normIdx;

                if (node->left)  q.push({node->left,  2 * normIdx});
                if (node->right) q.push({node->right, 2 * normIdx + 1});
            }
            maxWidth = max(maxWidth, (int)(rightIdx - 0 + 1));
        }
        return maxWidth;
    }
};

// ============================================================================
// PROBLEM 50: Count Complete Tree Nodes (LC 222)
// ============================================================================
/*
   APPROACH: Exploit complete tree property
   If left height == right height: left subtree is perfect, count = 2^h - 1
   Otherwise recurse, but O(log^2 n) due to height checks
   TIME: O(log^2 n)  SPACE: O(log n)
*/

class Solution_LC222 {
public:
    int getLeftHeight(TreeNode* node) {
        int h = 0;
        while (node) { h++; node = node->left; }
        return h;
    }

    int getRightHeight(TreeNode* node) {
        int h = 0;
        while (node) { h++; node = node->right; }
        return h;
    }

    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int leftH  = getLeftHeight(root);
        int rightH = getRightHeight(root);

        // Perfect binary tree: all leaves at same level
        if (leftH == rightH) {
            return (1 << leftH) - 1;   // 2^h - 1 nodes
        }
        // Not perfect: recurse on both subtrees
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

// ============================================================================
// MAIN: Test examples for each solution
// ============================================================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "========================================\n";
    cout << " Binary Tree - All 50 Solutions Tests\n";
    cout << "========================================\n\n";

    // Build test tree: [1,2,3,4,5,6,7]
    //         1
    //        / \
    //       2   3
    //      / \ / \
    //     4  5 6  7
    vector<int> vals = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root = buildTree(vals);

    // --- LC 94: Inorder ---
    {
        Solution_LC94 sol;
        auto res = sol.inorderTraversal(root);
        cout << "[LC94]  Inorder: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 144: Preorder ---
    {
        Solution_LC144 sol;
        auto res = sol.preorderTraversal(root);
        cout << "[LC144] Preorder: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 145: Postorder ---
    {
        Solution_LC145 sol;
        auto res = sol.postorderTraversal(root);
        cout << "[LC145] Postorder: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 102: Level Order ---
    {
        Solution_LC102 sol;
        auto res = sol.levelOrder(root);
        cout << "[LC102] Level Order: ";
        for (auto& level : res) {
            cout << "[";
            for (int x : level) cout << x << " ";
            cout << "] ";
        }
        cout << "\n";
    }

    // --- LC 104: Max Depth ---
    {
        Solution_LC104 sol;
        cout << "[LC104] Max Depth: " << sol.maxDepth(root) << "\n";
    }

    // --- LC 226: Invert Tree ---
    {
        vector<int> v2 = {4, 2, 7, 1, 3, 6, 9};
        TreeNode* t2 = buildTree(v2);
        Solution_LC226 sol;
        TreeNode* inv = sol.invertTree(t2);
        Solution_LC94 s94;
        auto res = s94.inorderTraversal(inv);
        cout << "[LC226] Inverted Inorder: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 100: Same Tree ---
    {
        Solution_LC100 sol;
        vector<int> v1 = {1,2,3}, v2 = {1,2,3};
        TreeNode* t1 = buildTree(v1);
        TreeNode* t2 = buildTree(v2);
        cout << "[LC100] Same Tree: " << (sol.isSameTree(t1,t2) ? "true" : "false") << "\n";
    }

    // --- LC 101: Symmetric ---
    {
        Solution_LC101 sol;
        vector<int> sv = {1, 2, 2, 3, 4, 4, 3};
        TreeNode* st = buildTree(sv);
        cout << "[LC101] Symmetric: " << (sol.isSymmetric(st) ? "true" : "false") << "\n";
    }

    // --- LC 572: Subtree ---
    {
        Solution_LC572 sol;
        vector<int> sub = {4, 1, 2};
        TreeNode* subRoot = buildTree(sub);
        vector<int> main_v = {3, 4, 5, 1, 2};
        TreeNode* mainRoot = buildTree(main_v);
        cout << "[LC572] Is Subtree: "
             << (sol.isSubtree(mainRoot, subRoot) ? "true" : "false") << "\n";
    }

    // --- LC 112: Path Sum ---
    {
        Solution_LC112 sol;
        vector<int> pv = {5, 4, 8, 11, -1, 13, 4, 7, 2};
        TreeNode* pt = buildTree(pv);
        cout << "[LC112] Has Path Sum 22: "
             << (sol.hasPathSum(pt, 22) ? "true" : "false") << "\n";
    }

    // --- LC 257: Binary Tree Paths ---
    {
        Solution_LC257 sol;
        vector<int> pv = {1, 2, 3, -1, 5};
        TreeNode* pt = buildTree(pv);
        auto paths = sol.binaryTreePaths(pt);
        cout << "[LC257] Paths: ";
        for (auto& p : paths) cout << p << "  ";
        cout << "\n";
    }

    // --- LC 637: Average of Levels ---
    {
        Solution_LC637 sol;
        auto avgs = sol.averageOfLevels(root);
        cout << "[LC637] Averages: ";
        for (double x : avgs) cout << x << " ";
        cout << "\n";
    }

    // --- LC 111: Min Depth ---
    {
        Solution_LC111 sol;
        cout << "[LC111] Min Depth: " << sol.minDepth(root) << "\n";
    }

    // --- LC 103: Zigzag ---
    {
        Solution_LC103 sol;
        auto res = sol.zigzagLevelOrder(root);
        cout << "[LC103] Zigzag: ";
        for (auto& lv : res) {
            cout << "[";
            for (int x : lv) cout << x << " ";
            cout << "]";
        }
        cout << "\n";
    }

    // --- LC 199: Right Side View ---
    {
        Solution_LC199 sol;
        auto res = sol.rightSideView(root);
        cout << "[LC199] Right View: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 1448: Good Nodes ---
    {
        Solution_LC1448 sol;
        vector<int> gv = {3, 1, 4, 3, -1, 1, 5};
        TreeNode* gt = buildTree(gv);
        cout << "[LC1448] Good Nodes: " << sol.goodNodes(gt) << "\n";
    }

    // --- LC 230: Kth Smallest BST ---
    {
        Solution_LC230 sol;
        // BST: [3,1,4,-1,2]
        vector<int> bv = {3, 1, 4, -1, 2};
        TreeNode* bt = buildTree(bv);
        cout << "[LC230] 1st Smallest in BST: " << sol.kthSmallest(bt, 1) << "\n";
    }

    // --- LC 98: Validate BST ---
    {
        Solution_LC98 sol;
        vector<int> bv = {2, 1, 3};
        TreeNode* bt = buildTree(bv);
        cout << "[LC98]  Valid BST: " << (sol.isValidBST(bt) ? "true" : "false") << "\n";
    }

    // --- LC 105: Build from Pre+Inorder ---
    {
        Solution_LC105 sol;
        vector<int> pre = {3,9,20,15,7}, ino = {9,3,15,20,7};
        TreeNode* bt = sol.buildTree(pre, ino);
        Solution_LC104 d;
        cout << "[LC105] Built tree depth: " << d.maxDepth(bt) << "\n";
    }

    // --- LC 106: Build from In+Postorder ---
    {
        Solution_LC106 sol;
        vector<int> ino = {9,3,15,20,7}, post = {9,15,7,20,3};
        TreeNode* bt = sol.buildTree(ino, post);
        Solution_LC104 d;
        cout << "[LC106] Built tree depth: " << d.maxDepth(bt) << "\n";
    }

    // --- LC 113: Path Sum II ---
    {
        Solution_LC113 sol;
        vector<int> pv = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, -1, 5, 1};
        TreeNode* pt = buildTree(pv);
        auto paths = sol.pathSum(pt, 22);
        cout << "[LC113] Path Sum II count: " << paths.size() << "\n";
    }

    // --- LC 129: Sum Root to Leaf ---
    {
        Solution_LC129 sol;
        vector<int> sv = {1, 2, 3};
        TreeNode* st = buildTree(sv);
        cout << "[LC129] Sum Root to Leaf: " << sol.sumNumbers(st) << "\n";
    }

    // --- LC 1457: Pseudo Palindromic Paths ---
    {
        Solution_LC1457 sol;
        vector<int> pv = {2, 3, 1, 3, 1, -1, 1};
        TreeNode* pt = buildTree(pv);
        cout << "[LC1457] Pseudo Palindromic Paths: "
             << sol.pseudoPalindromicPaths(pt) << "\n";
    }

    // --- LC 236: LCA ---
    {
        Solution_LC236 sol;
        vector<int> lv = {3, 5, 1, 6, 2, 0, 8};
        TreeNode* lt = buildTree(lv);
        // LCA(5,1) = 3 (root)
        cout << "[LC236] LCA: " << sol.lowestCommonAncestor(lt, lt->left, lt->right)->val << "\n";
    }

    // --- LC 235: LCA BST ---
    {
        Solution_LC235 sol;
        vector<int> lv = {6, 2, 8, 0, 4, 7, 9};
        TreeNode* lt = buildTree(lv);
        cout << "[LC235] LCA BST: "
             << sol.lowestCommonAncestor(lt, lt->left, lt->right)->val << "\n";
    }

    // --- LC 110: Balanced ---
    {
        Solution_LC110 sol;
        cout << "[LC110] Balanced: " << (sol.isBalanced(root) ? "true" : "false") << "\n";
    }

    // --- LC 543: Diameter ---
    {
        Solution_LC543 sol;
        cout << "[LC543] Diameter: " << sol.diameterOfBinaryTree(root) << "\n";
    }

    // --- LC 107: Level Order Bottom ---
    {
        Solution_LC107 sol;
        auto res = sol.levelOrderBottom(root);
        cout << "[LC107] Level Bottom: ";
        for (auto& lv : res) {
            cout << "[";
            for (int x : lv) cout << x << " ";
            cout << "]";
        }
        cout << "\n";
    }

    // --- LC 31: Insert BST ---
    {
        Solution_LC701 sol;
        vector<int> bv = {4, 2, 7, 1, 3};
        TreeNode* bt = buildTree(bv);
        bt = sol.insertIntoBST(bt, 5);
        Solution_LC94 s94;
        auto res = s94.inorderTraversal(bt);
        cout << "[LC701] BST after insert 5: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 450: Delete BST ---
    {
        Solution_LC450 sol;
        vector<int> bv = {5, 3, 6, 2, 4, -1, 7};
        TreeNode* bt = buildTree(bv);
        bt = sol.deleteNode(bt, 3);
        Solution_LC94 s94;
        auto res = s94.inorderTraversal(bt);
        cout << "[LC450] BST after delete 3: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 108: Sorted Array to BST ---
    {
        Solution_LC108 sol;
        vector<int> arr = {-10, -3, 0, 5, 9};
        TreeNode* bt = sol.sortedArrayToBST(arr);
        Solution_LC110 bal;
        cout << "[LC108] Balanced BST: " << (bal.isBalanced(bt) ? "true" : "false") << "\n";
    }

    // --- LC 337: House Robber III ---
    {
        Solution_LC337 sol;
        vector<int> hv = {3, 2, 3, -1, 3, -1, 1};
        TreeNode* ht = buildTree(hv);
        cout << "[LC337] House Robber III: " << sol.rob(ht) << "\n";
    }

    // --- LC 687: Longest Univalue Path ---
    {
        Solution_LC687 sol;
        vector<int> uv = {5, 4, 5, 1, 1, -1, 5};
        TreeNode* ut = buildTree(uv);
        cout << "[LC687] Longest Univalue Path: " << sol.longestUnivaluePath(ut) << "\n";
    }

    // --- LC 124: Max Path Sum ---
    {
        Solution_LC124 sol;
        vector<int> mv = {-10, 9, 20, -1, -1, 15, 7};
        TreeNode* mt = buildTree(mv);
        cout << "[LC124] Max Path Sum: " << sol.maxPathSum(mt) << "\n";
    }

    // --- LC 297: Serialize / Deserialize ---
    {
        Solution_LC297 sol;
        string serialized = sol.serialize(root);
        TreeNode* rebuilt  = sol.deserialize(serialized);
        Solution_LC104 dep;
        cout << "[LC297] Serialized depth: " << dep.maxDepth(rebuilt) << "\n";
    }

    // --- LC 99: Recover BST ---
    {
        Solution_LC99 sol;
        // Manually create swapped BST [1,3,null,null,2] (3 and 1 swapped)
        TreeNode* r99 = new TreeNode(1);
        r99->left = new TreeNode(3);
        r99->left->right = new TreeNode(2);
        sol.recoverTree(r99);
        Solution_LC94 s94;
        auto res = s94.inorderTraversal(r99);
        cout << "[LC99]  Recovered BST inorder: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 968: Binary Tree Cameras ---
    {
        Solution_LC968 sol;
        vector<int> cv = {0, 0, -1, 0, 0};
        TreeNode* ct = buildTree(cv);
        cout << "[LC968] Min Cameras: " << sol.minCameraCover(ct) << "\n";
    }

    // --- LC 979: Distribute Coins ---
    {
        Solution_LC979 sol;
        vector<int> dv = {3, 0, 0};
        TreeNode* dt = buildTree(dv);
        cout << "[LC979] Distribute Coins moves: " << sol.distributeCoins(dt) << "\n";
    }

    // --- LC 987: Vertical Order ---
    {
        Solution_LC987 sol;
        auto res = sol.verticalTraversal(root);
        cout << "[LC987] Vertical Order: ";
        for (auto& col : res) {
            cout << "[";
            for (int x : col) cout << x << " ";
            cout << "]";
        }
        cout << "\n";
    }

    // --- LC 889: Pre+Post Construct ---
    {
        Solution_LC889 sol;
        vector<int> pre = {1,2,4,5,3,6,7}, post = {4,5,2,6,7,3,1};
        TreeNode* bt = sol.constructFromPrePost(pre, post);
        Solution_LC104 dep;
        cout << "[LC889] Pre+Post tree depth: " << dep.maxDepth(bt) << "\n";
    }

    // --- LC 863: All Nodes Distance K ---
    {
        Solution_LC863 sol;
        vector<int> kv = {3, 5, 1, 6, 2, 0, 8};
        TreeNode* kt = buildTree(kv);
        auto res = sol.distanceK(kt, kt->left, 2);   // target = 5, k = 2
        cout << "[LC863] Nodes distance 2 from 5: ";
        for (int x : res) cout << x << " ";
        cout << "\n";
    }

    // --- LC 95: Unique BSTs II ---
    {
        Solution_LC95 sol;
        auto trees = sol.generateTrees(3);
        cout << "[LC95]  Unique BSTs for n=3: " << trees.size() << "\n";
    }

    // --- LC 173: BST Iterator ---
    {
        vector<int> bv = {7, 3, 15, -1, -1, 9, 20};
        TreeNode* bt = buildTree(bv);
        BSTIterator it(bt);
        cout << "[LC173] BST Iterator: ";
        while (it.hasNext()) cout << it.next() << " ";
        cout << "\n";
    }

    // --- LC 114: Flatten ---
    {
        vector<int> fv = {1, 2, 5, 3, 4, -1, 6};
        TreeNode* ft = buildTree(fv);
        Solution_LC114 sol;
        sol.flatten(ft);
        cout << "[LC114] Flattened: ";
        while (ft) { cout << ft->val << " "; ft = ft->right; }
        cout << "\n";
    }

    // --- LC 1110: Delete Nodes ---
    {
        Solution_LC1110 sol;
        vector<int> dv = {1, 2, 3, 4, 5, 6, 7};
        TreeNode* dt = buildTree(dv);
        vector<int> toDelete = {3, 5};
        auto forest = sol.delNodes(dt, toDelete);
        cout << "[LC1110] Forest roots: ";
        for (TreeNode* t : forest) cout << t->val << " ";
        cout << "\n";
    }

    // --- LC 988: Smallest String From Leaf ---
    {
        Solution_LC988 sol;
        // [0,1,2,3,4,3,4]
        vector<int> sv = {0, 1, 2, 3, 4, 3, 4};
        TreeNode* st = buildTree(sv);
        cout << "[LC988] Smallest From Leaf: " << sol.smallestFromLeaf(st) << "\n";
    }

    // --- LC 662: Max Width ---
    {
        Solution_LC662 sol;
        vector<int> wv = {1, 3, 2, 5, 3, -1, 9};
        TreeNode* wt = buildTree(wv);
        cout << "[LC662] Max Width: " << sol.widthOfBinaryTree(wt) << "\n";
    }

    // --- LC 222: Count Complete Nodes ---
    {
        Solution_LC222 sol;
        cout << "[LC222] Complete Tree Nodes: " << sol.countNodes(root) << "\n";
    }

    cout << "\n========================================\n";
    cout << " All 50 problems completed!\n";
    cout << "========================================\n";

    return 0;
}
