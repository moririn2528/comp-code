#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cassert>
#include<set>
#include<complex>
#include<numeric>
#include<functional>
#include<unordered_map>
#include<unordered_set>
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
const int INF=1<<30;
const LL MAX=1e9+7;

void array_show(int *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%d%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(LL *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%lld%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(vector<int> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%d%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
void array_show(vector<LL> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%lld%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
template<typename T> ostream& operator<<(ostream& os,const vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++){
        if(i)os<<" ";
        os<<v1[i];
    }
    return os;
}
template<typename T1,typename T2> ostream& operator<<(ostream& os,const pair<T1,T2>& p){
    os<<p.first<<" "<<p.second;
    return os;
}
template<typename T> istream& operator>>(istream& is,vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++)is>>v1[i];
    return is;
}
template<typename T1,typename T2> istream& operator>>(istream& is,pair<T1,T2>& p){
    is>>p.first>>p.second;
    return is;
}

namespace sol{
    typedef vector<int> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
    typedef vector<V3> V4;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        V4 dp(n+1,V3(n+1,V2(n+1,V1(n+1))));
        vector<string> grid(n);
        V2 su(n+1,V1(n+1));
        cin>>grid;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                su[i+1][j+1]=su[i+1][j]+su[i][j+1]-su[i][j];
                if(grid[i][j]=='#')su[i+1][j+1]++;
            }
        }
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                for(a=0;a+i<=n;a++){
                    for(b=0;b+j<=n;b++){
                        int s=max(i,j);
                        if(su[a+i][b+j]+su[a][b]-su[a+i][b]-su[a][b+j]==0)s=0;
                        for(k=1;k+1<=i;k++){
                            s=min(s,dp[a][b][k][j]+dp[a+k][b][i-k][j]);
                        }
                        for(k=1;k+1<=j;k++){
                            s=min(s,dp[a][b][i][k]+dp[a][b+k][i][j-k]);
                        }
                        dp[a][b][i][j]=s;
                    }
                }
            }
        }
        cout<<dp[0][0][n][n]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}