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
    vector<vector<int>> path;
    vector<vector<mint>> dp,comb;
    vector<int> sz;

    void vec_rev(vector<mint>& v1,int n){
        int i;
        for(i=0;i<n/2;i++){
            swap(v1[i],v1[n-i-1]);
        }
    }

    mint calc(int pos,int bef,bool big){
        int cnt=0;
        int i,j,k;
        sz[pos]=1;
        dp[pos][0]=1;
        for(auto to:path[pos]){
            if(to==bef)continue;
            calc(to,pos,!big);
            if(!big)vec_rev(dp[to],sz[to]);
            for(i=sz[pos]-1;i>=0;i--){
                mint t=0;
                for(j=0;j<sz[to];j++){
                    t+=dp[to][j];
                    int p=sz[to]-(j+1),q=sz[pos]-(i+1);
                    dp[pos][i+j+1]+=comb[i+j+1][i]*comb[p+q][p]*t*dp[pos][i];
                }
                dp[pos][i]=0;
            }
            sz[pos]+=sz[to];
        }
        if(!big)vec_rev(dp[pos],sz[pos]);
        mint s=0;
        for(i=0;i<sz[pos];i++){
            s+=dp[pos][i];
        }
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        path.resize(n);
        sz.assign(n,0);
        dp.assign(n,vector<mint>(n+10));
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        comb.assign(n+10,vector<mint>(n+10));
        for(i=0;i<n+7;i++){
            mint t=1;
            for(j=0;j<=i;j++){
                if(j){
                    t*=i-j+1;
                    t/=j;
                }
                comb[i][j]=t;
            }
        }
        mint s=calc(0,-1,true);
        s*=2;
        cout<<s.val()<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}