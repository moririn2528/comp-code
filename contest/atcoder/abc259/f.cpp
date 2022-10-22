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
    vector<int> deg;
    vector<vector<LP>> path;
    vector<LL> v1,v2;

    LL dfs(int pos, int bef){
        LL s=0;
        vector<LL> va;
        for(auto node:path[pos]){
            int to=node.first;
            LL w=node.second;
            if(to==bef)continue;
            dfs(to,pos);
            s+=v1[to]+v2[to];
            if(deg[to]>0)va.push_back(w-v2[to]);
        }
        int i;
        sort(va.rbegin(),va.rend());
        for(i=0;i+1<deg[pos] && i<va.size();i++){
            s+=max(0LL,va[i]);
        }
        v1[pos]=s;
        i=deg[pos]-1;
        if(i<va.size())v2[pos]=max(0LL,va[i]);
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        deg.resize(n);
        cin>>deg;
        path.resize(n);
        for(i=0;i<n-1;i++){
            cin>>a>>b>>c;
            a--,b--;
            path[a].push_back({b,c});
            path[b].push_back({a,c});
        }
        v1.assign(n,0);
        v2.assign(n,0);
        LL s=dfs(0,-1);
        cout<<s+v2[0]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}