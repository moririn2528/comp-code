#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> v1;
        int i,j;
        for(i=0;i<grid.size();i++){
            for(j=0;j<grid[0].size();j++){
                v1.push_back(grid[i][j]);
            }
        }
        sort(v1.begin(),v1.end());
        int n=v1.size();
        int a=0,s=1e9+7;
        for(i=1;i<n;i++){
            if((v1[i]-v1[0])%x)return -1;
            a+=abs(v1[i]-v1[0])/x;
        }
        s=a;
        for(i=0;i+1<n;i++){
            int b=abs(v1[i+1]-v1[i])/x;
            a+=b;
            a-=(n-1-i)*b;
            s=min(s,a);
        }
        return s;
    }
};