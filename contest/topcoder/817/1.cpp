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

class DogsInAGrid{
    const int n=40;
public:
    vector<string> construct(int N){
        vector<string> grid(n,string(n,'D'));
        int i,j;
        int a;
        string sa;
        for(i=0;i<n;i++){
            if(N==0)break;
            for(j=0;j<n;j++){
                if(i%2){
                    grid[i][j]='O';
                    continue;
                }
                a=1;
                if(2<=j)a++;
                if(j<n-2)a++;
                if(i<2)a=0;
                if(i%4)sa="DG";
                else sa="GD";
                if(a<=N){
                    N-=a;
                    grid[i][j]=sa[0];
                }else grid[i][j]=sa[1];
            }
        }
        assert(2*N<n);
        sa="GD";
        for(i=0;i<N;i++){
            grid[n-1][2*i+1]='O';
            grid[n-1][2*i+2]=sa[i%2];

        }
        return grid;
    }
};