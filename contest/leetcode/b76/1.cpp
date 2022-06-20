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
public:
    int findClosestNumber(vector<int>& nums) {
        int s=1e9;
        for(auto num:nums){
            if(abs(num)<abs(s) || (abs(s)==abs(num) && s<0))s=num;
        }
        return s;
    }
};