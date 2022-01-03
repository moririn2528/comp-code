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
#include<atcoder/all>
using namespace std;
using namespace atcoder;
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
    using mint=modint998244353;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<char> v1(n),v2(n,1);
        for(i=0;i<n;i++){
            cin>>a;
            if(a==-1)v1[i]=1;
            else v2[a-1]=0;
        }
        const int N=11,M=5;
        vector<vector<mint>> dp(n+3,vector<mint>(1<<N,0));
        dp[0][0]=1;
        for(i=0;i<n;i++){
            if(!v1[i]){
                for(j=0;j<(1<<N);j++){
                    dp[i+1][j>>1]+=dp[i][j];
                }
                continue;
            }
            for(j=0;j<(1<<N);j++){
                for(k=-m;k<=m;k++){
                    if(j&1<<(M+k))continue;
                    if(i+k<0 || n<=i+k)continue;
                    if(!v2[i+k])continue;
                    dp[i+1][(j+(1<<(M+k)))>>1]+=dp[i][j];
                }
            }
        }
        mint s=0;
        for(i=0;i<(1<<N);i++){
            s+=dp[n][i];
        }
        cout<<s.val()<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}