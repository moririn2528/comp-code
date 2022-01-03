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
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n=recipes.size();
        int i,j,k;
        map<string,vector<int>> m1;
        vector<int> deg(n);
        for(i=0;i<n;i++){
            for(auto sa:ingredients[i]){
                m1[sa].push_back(i);
            }
            deg[i]=ingredients[i].size();
        }
        queue<string> q1;
        vector<string> vs;
        for(auto sa:supplies){
            q1.push(sa);
        }
        while(!q1.empty()){
            string sa=q1.front();q1.pop();
            for(int a:m1[sa]){
                deg[a]--;
                if(deg[a]==0){
                    q1.push(recipes[a]);
                    vs.push_back(recipes[a]);
                }
            }
        }
        return vs;
    }
};