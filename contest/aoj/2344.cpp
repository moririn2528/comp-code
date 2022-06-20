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
    int n,m;
    vector<vector<int>> path;
    vector<LL> v1,vc,ds;

    void dfs(int pos,int dep){
        LL s1=0,s2=0;
        for(auto to:path[pos]){
            if(to<n-1)dfs(to,dep+1);
            vc[pos]+=vc[to];
            ds[pos]+=vc[to]+ds[to];
            s1+=max(vc[to]*dep,v1[to]);
            s2+=vc[to]*dep;
        }
        if(s2<s1){
            v1[pos]=s1;
            return;
        }
        s2=INF;
        for(auto to:path[pos]){
            s2=min(s2,vc[to]*dep-v1[to]);
        }
        v1[pos]=s1-s2;
        return;
    }

    void solve(){
        int i,j,k;
        LL a,b,c;
        cin>>n;
        path.resize(n);
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[i].push_back(a);
            path[i].push_back(b);
        }
        v1.assign(n,0);
        vc.assign(n,0);
        ds.assign(n,0);
        vc[n-1]=1,ds[n-1]=0;
        dfs(0,0);
        cout<<ds[0]-v1[0]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}