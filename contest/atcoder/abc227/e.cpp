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
    const int N=500;
    typedef vector<LL> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
    typedef vector<V3> V4;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c,d;
        string sa,sb="KEY";
        cin>>sa;
        n=sa.size();
        cin>>m;
        V2 v1(n+2,V1(3,0));
        V2 va(3);
        for(i=0;i<n;i++){
            for(j=0;j<3;j++){
                v1[i+1][j]=v1[i][j];
                if(sa[i]==sb[j]){
                    v1[i+1][j]++;
                    va[j].push_back(i);
                }
            }
        }
        int x=v1[n][0],y=v1[n][1],z=v1[n][2];
        V4 dp(x+1,V3(y+1,V2(z+1,V1(N))));
        dp[0][0][0][0]=1;
        auto check=[&](int a,int b,int c,int na,int nb,int nc,int d)->void{
            int s=max(v1[d+1][0]-a,0LL);
            s+=max(v1[d+1][1]-b,0LL);
            s+=max(v1[d+1][2]-c,0LL);
            s--;
            for(int i=0;i<N-s;i++){
                dp[na][nb][nc][i+s]+=dp[a][b][c][i];
            }
        };
        for(i=0;i<=x;i++){
            for(j=0;j<=y;j++){
                for(k=0;k<=z;k++){
                    if(i<x)check(i,j,k,i+1,j,k,va[0][i]);
                    if(j<y)check(i,j,k,i,j+1,k,va[1][j]);
                    if(k<z)check(i,j,k,i,j,k+1,va[2][k]);
                }
            }
        }
        LL s=0;
        for(i=0;i<N && i<=m;i++){
            s+=dp[x][y][z][i];
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}