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
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        vector<int> v1,v2;
        sort(tasks.rbegin(),tasks.rend());
        sort(workers.rbegin(),workers.rend());
        int n=tasks.size(),m=workers.size();
        int i,j,k;
        int s=0;
        for(i=0,j=0,k=0;i<m;i++){
            for(;j<n && workers[i]<tasks[j];j++){
                v1.push_back(tasks[j]);
            }
            for(;k<v1.size() && workers[i]+strength<v1[k];k++);
            if(k<v1.size() && pills>0){
                pills--,k++,s++;
                continue;
            }
            if(j<n)s++,j++;
        }
        return s;
    }
};