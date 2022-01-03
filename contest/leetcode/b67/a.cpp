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

class Solution {
    typedef pair<int,int> P;
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<P> vp;
        int i,j;
        int n=nums.size();
        for(i=0;i<n;i++){
            vp.push_back({nums[i],i});
        }
        sort(vp.rbegin(),vp.rend());
        vector<char> used(n);
        for(i=0;i<k;i++){
            int a=vp[i].second;
            used[a]=1;
        }
        vector<int> vs;
        for(i=0;i<n;i++){
            if(used[i])vs.push_back(nums[i]);
        }
        return vs;
    }
};