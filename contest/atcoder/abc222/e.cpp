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
    vector<vector<P>> path;
    vector<int> cnt;

    bool dfs(int pos,int g,int bef){
        if(pos==g)return true;
        for(auto node:path[pos]){
            int to=node.first,id=node.second;
            if(to==bef)continue;
            cnt[id]++;
            if(dfs(to,g,pos))return true;
            cnt[id]--;
        }
        return false;
    }

    void solve(){
        const int N=1e5+7;
        int n,m,p;
        int i,j,k;
        int a,b,c;
        cin>>n>>m>>p;
        vector<int> va(m);
        cin>>va;
        path.resize(n);
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back({b,i});
            path[b].push_back({a,i});
        }
        cnt.assign(n,0);
        for(i=0;i+1<m;i++){
            assert(dfs(va[i]-1,va[i+1]-1,-1));
        }
        vector<vector<mint>> dp(n,vector<mint>(2*N));
        dp[0][N]=1;
        for(i=0;i<n-1;i++){
            for(j=0;j<2*N;j++){
                if(cnt[i]<=j)dp[i+1][j-cnt[i]]+=dp[i][j];
                if(j+cnt[i]<2*N)dp[i+1][j+cnt[i]]+=dp[i][j];
            }
        }
        cout<<dp[n-1][N+p].val()<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}