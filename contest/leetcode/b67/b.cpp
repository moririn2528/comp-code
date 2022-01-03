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
#include <numeric>
using namespace std;

class Solution {
    const int INF=1<<30;
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n=security.size();
        int i,j,k;
        int a,b,c;
        vector<char> va(n);
        if(time==0){
            vector<int> vs(n);
            iota(vs.begin(),vs.end(),0);
            return vs;
        }
        a=0;
        for(i=1;i<n;i++){
            if(security[i-1]>=security[i]){
                a++;
            }else{
                a=0;
            }
            if(a>=time)va[i]++;
        }
        a=0;
        for(i=n-2;i>=0;i--){
            if(security[i+1]>=security[i]){
                a++;
            }else{
                a=0;
            }
            if(a>=time)va[i]++;
        }
        vector<int> vs;
        for(i=0;i<n;i++){
            if(va[i]==2)vs.push_back(i);
        }
        return vs;
    }
};