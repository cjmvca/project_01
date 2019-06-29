https://leetcode.com/problems/path-sum-iii/
437. Path Sum III
You are given a binary tree in which each node contains an integer value.
Find the number of paths that sum to a given value.
The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,00.

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
    // Solution
    // From each node, create a vector to its parent for all sums in the path:
    // 1. !root => empty vector
    // 2. root->val => vector & test sum, update count
    // 3. Get children's return vectors
    //    3.1 for each sum from child, new sum=node->val + sum
    //    3.2 test sum and update count
    vector<int> helper(TreeNode* root, const int& sum, int& count) {
        vector<int> ret;
        if (!root)
            return ret;
        if (root->val==sum)
            count++;
        ret.push_back(root->val);
        vector<int> left=helper(root->left, sum, count);
        vector<int> right=helper(root->right, sum, count);
        for (auto it:left) {
            int val=root->val+it;
            if (val==sum)
                count++;
            ret.push_back(val);
        }
        for (auto it:right) {
            int val=root->val+it;
            if (val==sum)
                count++;
            ret.push_back(val);
        }
        return ret;
    }
    int pathSum(TreeNode* root, int sum) {
        int count=0;
        helper(root, sum, count);
        return count;
    }
};
