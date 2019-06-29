BST sub-tree related must consider boundary

https://leetcode.com/problems/largest-bst-subtree/submissions/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // Solution:
    // 1. From root node, recursively move down to leafs
    // 2. If a node has no child, it is a BST with count 1
    // 3. For a node with child/children
    //    a. if there is no child, count 0, else call recursive function to get child BST
    //    b. if BST return -1, which means the child is not BST, 
    //          or child value is not less than(left) or greater than node value (right),
    //          or left child has right sub-child value > node value 
    //          or right child has left sub-child value < node value 
    //          => Current node is not a BST, return -1
    //       else 
    //          Sum left and right returns plus 1 for current node (X)
    //          => return X back to parent
    bool testLeft(TreeNode* node, int val) {
        if (!node)
            return true;
        if (node->val>=val)
            return false;
        return testLeft(node->right, val);
    }
    bool testRight(TreeNode* node, int val) {
        if (!node)
            return true;
        if (node->val<=val)
            return false;
        return testRight(node->left, val);
    }    
    int helper(TreeNode* node) {
        if (!node->left && !node->right) {
            res=max(res, 1);
            return 1; 
        }
        int left;
        int right;
        if (!node->left)
            left=0;
        else {
            left=helper(node->left);
            if (node->left->val>=node->val || !testLeft(node->left, node->val))
                left=-1;
        }
        if (!node->right)
            right=0;
        else {
            right=helper(node->right);
            if (node->right->val<=node->val || !testRight(node->right, node->val))
                right=-1;
        }
        if (left!=-1 && right!=-1) {
            int lbs=left+right+1;
            res=max(res, lbs);
            return lbs;
        }
        return -1;
    }
    int largestBSTSubtree(TreeNode* root) {
        if (!root) 
            return 0;
        helper(root);
        return res;
    }
    int res=0;
};
