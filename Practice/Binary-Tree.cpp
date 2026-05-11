/*
================================================================================
BINARY TREE COMPLETE LEETCODE PRACTICE
================================================================================
Language  : C++17
Topic     : Complete Binary Tree
Note      : All solutions self-contained, TreeNode defined once at top
Author    : Abhishek Kumar Mishra
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Commonly used Macrons
#define vi vector<int>
#define vvi vector<vector<int>>
#define ll long long

// ============================================================================
// COMMON TREE NODE DEFINITION
// ============================================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
};

// ============================================================================
// HELPER: Build tree from level-order array (for testing)
// ============================================================================
TreeNode* buildTree(vi &vals){
    if(vals.empty() || vals[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i(1);
    while(!q.empty() && i<vals.size()){
        TreeNode* node = q.front();
        q.pop();
        if(i<vals.size() && vals[i]!=-1){
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        if(i<vals.size() && vals[i]!=-1){
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// ============================================================================
// PROBLEM 1: Binary Tree Inorder Traversal (LC 94)
//              Approach : Recursive DFS - Left -> Root -> Right
//              TC : O(n)   SC : O(h)
// ============================================================================
class Solution_LC94{
public:
    void solve(TreeNode* root, vi &res){
        if(!root) return;
        solve(root->left,res);
        res.push_back(root->val);
        solve(root->right,res);
    }
    vi inorderTraversal(TreeNode* root){
        if(!root) return {};
        vi res;
        solve(root,res);
        return res;
    }
};


// ============================================================================
// PROBLEM 2: Binary Tree Preorder Traversal (LC 144)
// ============================================================================
/*
   APPROACH: Root -> Left -> Right
   TIME: O(n)  SPACE: O(h)
*/
class Solution_LC144{
public:
    void helper(TreeNode* root, vi &ans){
        if(!root) return;
        ans.push_back(root->val);
        helper(root->left,ans);
        helper(root->right,ans);
    }
    vi preorderTraversal(TreeNode* root){
        vi ans;
        helper(root,ans);
        return ans;
    }
};


// ============================================================================
// PROBLEM 3: Binary Tree Postorder Traversal (LC 145)
// ============================================================================
/*
   APPROACH: Left -> Right -> Root
   TIME: O(n)  SPACE: O(h)
*/
class Solution_LC145{
public:
    void solve(TreeNode* root, vi &ans){
        if(!root) return;
        solve(root->left,ans);
        solve(root->right,ans);
        ans.push_back(root->val);
    }
    vi postorderTraversal(TreeNode* root){
        vi ans;
        solve(root,ans);
        return ans;
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
    vvi LevelOrderTraversal(TreeNode* root){
        vvi ans;
        if(!root) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            vi curr;
            for(int i=0;i<n;i++){
                auto node = q.front();
                q.pop();
                curr.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            ans.push_back(curr);
        }
        return ans;
    }
};

// ============================================================================
// PROBLEM 5: Maximum Depth of Binary Tree (LC 104)
// ============================================================================
/*
   APPROACH: DFS - depth = 1 + max(left depth, right depth)
   TIME: O(n)  SPACE: O(h)
*/
class Solution_LC104  {
public:
    int maxDepth(TreeNode* root){
        if(!root) return 0;
        int lh = maxDepth(root->left);
        int rh = maxDepth(root->right);
        return 1 + max(lh,rh);
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



int main(){
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
        cout<<"[LC94] Inorder : ";
        for(auto x : res) cout<<x<<" ";
        cout<<endl;
    }

    // --- LC 144: Preorder ---
    {
        Solution_LC144 sol;
        auto res = sol.preorderTraversal(root);
        cout<<"[LC144] Preorder : ";
        for(auto x : res) cout<<x<<" ";
        cout<<endl;
    }

    //  ---LC 145: Postorder ---
    {
        Solution_LC145 sol;
        auto res = sol.postorderTraversal(root);
        cout<<"[LC145] Postorder : ";
        for(auto x : res) cout<<x<<" ";
        cout<<endl;
    }

    // ---LC 102: LevelOrder ---
    {
        Solution_LC102 sol;
        auto res = sol.LevelOrderTraversal(root);
        cout<<"[LC102] LevelOrder : ";
        for(auto &x : res){
            for(auto &i : x){
                cout<<i<<" ";
            }
        }
        cout<<endl;
    }

    // -- LC 104: MaxDepth --
    {
        cout<<"[LC104] MaxDepth : ";
        Solution_LC104 sol;
        auto res = sol.maxDepth(root);
        cout<<res<<endl;
    }

    return 0;
}