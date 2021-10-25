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
    typedef tuple<int,int,int> T;
    vector<int> val;
    vector<vector<int>> path;
    map<T,P> m1;

    void setp(P& p1,P p2){
        p1.first=min(p1.first,p2.first);
        p1.second=max(p1.second,p2.second);
    }

    P dfs2(int pos,int al,int be,int used,int n){
        int i,j;
        P pa,ps={INF,-INF};
        if(__builtin_popcount(used)<n){
            for(i=0;i<n;i++){
                if(used&1<<i)continue;
                pa=dfs(pos,al,be);
                setp(ps,dfs2(pos,al,be,))
            }
        }
    }

    P dfs(int pos,int al,int be){
        auto itr=m1.find({pos,al,be});
        if(itr!=m1.end())return itr->second;
        if(path[pos].empty())return {1,1};
        int n=path[pos].size();
        int i,j,k;
        int a,b,c;
        vector<vector<P>> dp(1<<n,vector<P>(n,{INF,-INF}));
        for(i=0;i<n;i++){
            dp[1<<i][i]=dfs(path[pos][i],al,be);
        }
        int s1=INF,s2=-INF;
        return {s1,s2};
    }

    int negmax(int pos){
        if(path[pos].empty())return val[pos];
        val[pos]=-INF;
        for(auto to:path[pos]){
            val[pos]=max(val[pos],-negmax(to));
        }
        return val[pos];
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        val.resize(n);
        path.resize(n);
        cin>>val;
        for(i=0;i<n;i++){
            cin>>a;
            for(j=0;j<a;j++){
                cin>>b;
                b--;
                path[i].push_back(b);
            }
        }
        negmax(0);
        cout<<dfs(0,-INF,INF)<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}