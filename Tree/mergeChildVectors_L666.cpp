https://leetcode.com/problems/path-sum-iv/submissions/
666. Path Sum IV

Update (add more value) and merge vectors from children's collection (after calculation at lower layers)

class Solution {
public:
    // Solution
    // Trick: parent value may be calcuated multiple times if there are multiple paths (leafs)
    // 1. From each node:
    //    a. if it is a leaf, return leaf value in a return vector
    //    b. if it is a null, return empty vector
    //    c. if it has children, merge vectors from children and add node value on each value in the vectors
    // 2. After root return, sum up all values in the vector root returns 
    vector<int> helper(unordered_map<int, int>& level, int pos) {
        vector<int> res;
        if (level.count(pos)==0)
            return res;
        int posVal=level[pos];
        pos=pos*2;
        vector<int> left=helper(level, pos);
        vector<int> right=helper(level, pos+1);
        if (left.size()==0 && right.size()==0) {
            res.push_back(posVal);
            return res;
        }
        for (auto it : left) {
            res.push_back(it+posVal);
        }
        for (auto it : right) {
            res.push_back(it+posVal);
        }
        return res; 
    }
    int pathSum(vector<int>& nums) {
        unordered_map<int, int> level;  // pos, val
        for(auto val : nums) {
            int pos=(1<<(val/100-1))+(val/10)%10-1;
            int nv=val%10;
            level[pos]=nv;
        }
        vector<int> ret = helper(level, 1);
        int res=0;
        for (auto it : ret)
            res+=it;
        return res;
    }
    void display (unordered_map<int, int>& level) {
        for (auto it : level)
            printf("%d/%d ", it.first, it.second);
        printf("\n");
    }
};



