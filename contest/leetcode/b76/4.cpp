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
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n=scores.size();
        int a,b,c;
        int i,j,k;
        vector<vector<int>> path(n);
        vector<vector<P>> v1(n);
        for(auto v:edges){
            a=v[0],b=v[1];
            path[a].push_back(b);
            path[b].push_back(a);
            v1[a].push_back({scores[b],b});
            v1[b].push_back({scores[a],a});
        }
        for(i=0;i<n;i++){
            if(v1[i].empty())continue;
            sort(v1[i].rbegin(),v1[i].rend());
        }
        auto f=[&](int pos,int bef1,int bef2) -> int{
            for(auto node:v1[pos]){
                if(node.second!=bef1 && node.second!=bef2){
                    return node.second;
                }
            }
            return -1;
        };
        int s=-1;
        for(i=0;i<n;i++){
            for(auto to:path[i]){
                a=f(i,to,-1);
                b=f(to,i,a);
                if(a==-1 || b==-1)continue;
                s=max(s,scores[a]+scores[b]+scores[i]+scores[to]);
            }
        }
        return s;
    }
};