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

class SelectFromArrays{
    typedef long long int ll;
    const ll INF=1LL<<60;
    typedef vector<ll> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
public:
    int maxSum(vector <int> A, vector <int> B, vector <int> C, int NA, int NB, int NC){
        int n=A.size();
        V3 dp(NA+2,V2(NB+2,V1(NC+2,-INF)));
        int i,j,k;
        int a;
        dp[0][0][0]=0;
        for(a=0;a<n;a++){
            for(i=NA;i>=0;i--){
                for(j=NB;j>=0;j--){
                    for(k=NC;k>=0;k--){
                        dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]+A[a]);
                        dp[i][j+1][k]=max(dp[i][j+1][k],dp[i][j][k]+B[a]);
                        dp[i][j][k+1]=max(dp[i][j][k+1],dp[i][j][k]+C[a]);
                    }
                }
            }
        }
        return dp[NA][NB][NC];
    }
};