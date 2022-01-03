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
const LL INF=1LL<<60;
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
    int n,m,p;
    vector<vector<LL>> v1;
    LL check(LL t){
        int i,j,k;
        LL a,b,c;
        vector<vector<vector<LL>>> dp(n+1,vector<vector<LL>>(m+1,vector<LL>(n+m+2,INF)));
        dp[0][0][0]=0;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                for(k=0;k<=n+m-1;k++){
                    if(v1[i][j]>=t)a=dp[i][j][k]+v1[i][j],b=k+1;
                    else a=dp[i][j][k],b=k;
                    dp[i+1][j][b]=min(dp[i+1][j][b],a);
                    dp[i][j+1][b]=min(dp[i][j+1][b],a);
                }
            }
        }
        LL s=INF;
        for(i=p;i<=n+m-1;i++){
            s=min(s,dp[n][m-1][i]-(i-p)*t);
        }
        return s;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m>>p;
        v1.assign(n,vector<LL>(m));
        cin>>v1;
        LL s=INF;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                s=min(s,check(v1[i][j]));
            }
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}