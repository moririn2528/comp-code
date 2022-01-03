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
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        vector<P> v1,v2;
        int i,j,k;
        int a,b,c;
        int n=items.size(),m=queries.size();
        for(i=0;i<n;i++){
            v1.push_back({items[i][0],items[i][1]});
        }
        sort(v1.begin(),v1.end());
        for(i=0;i<n;i++){
            if(!v2.empty() && v2.back().second>=v1[i].second)continue;
            v2.push_back(v1[i]);
        }
        vector<int> vs;
        for(i=0;i<m;i++){
            auto itr=lower_bound(v2.begin(),v2.end(),P{queries[i]+1,-1});
            if(itr==v2.begin()){
                vs.push_back(0);
                continue;
            }
            itr--;
            vs.push_back(itr->second);
        }
        return vs;
    }
};