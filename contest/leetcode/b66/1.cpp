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
    const int N=2000;
    map<string,int> m1;
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        for(auto s:words1){
            m1[s]+=N;
        }
        for(auto s:words2){
            m1[s]++;
        }
        int s=0;
        for(auto node:m1){
            if(node.second==N+1)s++;
        }
        return s;
    }
};