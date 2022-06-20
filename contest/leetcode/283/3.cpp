#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<tuple>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    const int N=1e5+7;
    vector<vector<pair<int,int>>> path;
    vector<TreeNode> vs;

    TreeNode* dfs(int pos){
        TreeNode *l,*r;
        for(auto p:path[pos]){
            TreeNode* a=dfs(p.first);
            if(p.second==1)l=a;
            else r=a;
        }
        TreeNode t=TreeNode(pos,l,r);
        vs[pos]=t;
        return &vs[pos];
    }
    
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        set<int> s1;
        path.resize(N);
        vs.resize(N);
        for(auto v:descriptions){
            s1.insert(v[1]);
            path[v[0]].push_back({v[1],v[2]});
        }
        int root;
        for(auto v:descriptions){
            if(s1.find(v[0])==s1.end()){
                root=v[0];
            }
        }
        return dfs(root);
    }
};