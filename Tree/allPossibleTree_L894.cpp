https://leetcode.com/problems/all-possible-full-binary-trees/
894. All Possible Full Binary Trees
A full binary tree is a binary tree where each node has exactly 0 or 2 children.
Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.
Each node of each tree in the answer must have node.val = 0.
You may return the final list of trees in any orde.
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
    // 1. Only odd value is valid
    // 2. Starting from root (N), its children are also odd values which split N-1 with all combination
    //    Patten:  Parent N : left (1, 3, ..., N-2) right (N-2, N-4, ... 1) 
    // 3. Create a vector to hold tree level with each combination through function parameter copy
    //    a. Fill 1st three values, pass next level pos/value to split child, last non-zero position
    //    b. For each value in the level after, handle per pos based combination
    // 4. Create tree when there is no more value left in the level (last non-zero position has passed)
    void buildTree(vector<int>& level, vector<TreeNode*>& res) {  
        // build tree from leveled array of node values
        // 1. For each value in the level create a tree node and push back to a list
        // 2. For each push back, if it is not leaf (val=1) update the front node's left or right child
        //    2.1 if both children are filled remove the front node from the list
        //    2.2 Remove leaf node unconditionally
        // 3. Clean up the list after all val has been feed to the list
        // 4. update node value to 0
        TreeNode* root=nullptr;
        list<TreeNode*> tList;
        int nullCount=0;
        for (auto it : level) {
            TreeNode* node=new TreeNode(it);
            tList.push_back(node);
            if (root==nullptr) {
                root=node;
                res.push_back(root);
                continue;
            }
            TreeNode* topNode;
            bool isLeaf=false;
            topNode=tList.front();
            while (topNode->val==1) {
                topNode->val=0; 
                tList.pop_front();
                topNode=tList.front();
            } 
            nullCount++;
            if (topNode) {
                if (nullCount==1)
                    topNode->left=node;
                else
                    topNode->right=node;
            }
            if (nullCount==2) {
                topNode->val=0;
                tList.pop_front();
                nullCount=0;
            }
        }
        while (tList.size()) {
            TreeNode* topNode=tList.front();
            topNode->val=0;
            tList.pop_front();
        }
    }
    void buildLevel(vector<int> level, int pos, int lastPos, vector<TreeNode*>& res) {
        int remain=level[pos]-1;
        int levelSize=level.size();
        if (level[pos]==0 || level[pos]==1) {
            // If there is no non-zero pos after current pos, we can build tree now 
            if (lastPos>pos)
                buildLevel(level, pos+1, lastPos, res);
            else 
                buildTree(level, res);
        } else {
            for (int i=1; i<remain; i+=2) {
                while (level.size()>levelSize)
                    level.pop_back();
                level.push_back(i);
                level.push_back(remain-i);  
                lastPos=level.size()-1;
                buildLevel(level, pos+1, lastPos, res);
            }
        }
    }
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<TreeNode*> res;
        if (N%2==0)
            return res;
        if (N==1) {
            res.push_back(new TreeNode(0));
            return res;
        }
        vector<int> level;
        level.push_back(N);
        for (int i=1; i<N; i+=2) {
            while (level.size()>1)
                level.pop_back();
            level.push_back(i);
            level.push_back(N-i-1);    
            // build level by passing next pos to process and last non-Zero pos
            buildLevel(level, 1, 2, res);
        }    
        return res;
    }
};
