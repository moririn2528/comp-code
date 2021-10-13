#include<bits/stdc++.h>
using namespace std;


class Solution {
    const int N=105;
    vector<int> v1;

    void calc(vector<int>& va){
        set<int> s1;
        for(int num:va){
            if(s1.find(num)!=s1.end())continue;
            s1.insert(num);
            v1[num]++;
        }
    }
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        v1.assign(N,0);
        calc(nums1);
        calc(nums2);
        calc(nums3);
        vector<int> vs;
        for(int i=0;i<N;i++){
            if(v1[i]>=2)vs.push_back(i);
        }
        return vs;
    }
};