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

class OneBattleship{
public:
    vector <string> hit(vector <string> grid){
        const int N=3;
        vector<int> cnt(N);
        int n=grid.size(),m=grid[0].size();
        int i,j,k;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(grid[i][j]=='.')cnt[(i+j)%N]++;
            }
        }
        for(i=0,k=0;i<N;i++){
            if(cnt[k]>cnt[i])k=i;
        }
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(grid[i][j]=='.' && (i+j)%N==k)grid[i][j]='*';
            }
        }
        return grid;
    }
};