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
    const int N=26;
    vector<int> calc(string sa){
        int i,j;
        vector<int> v1(N);
        for(i=0;i<sa.size();i++){
            v1[sa[i]-'a']++;
        }
        return v1;
    }
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        vector<int> v1=calc(word1),v2=calc(word2);
        for(int i=0;i<N;i++){
            if(abs(v1[i]-v2[i])>3)return false;
        }
        return true;
    }
};