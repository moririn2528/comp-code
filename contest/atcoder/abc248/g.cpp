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
    vector<int> v1;
    vector<vector<int>> path;
    vector<char> ban;
    vector<int> szmm;

    int gcd(int a,int b){
        if(a<b)swap(a,b);
        if(b==0)return a;
        return gcd(b,a%b);
    }

    int size(int pos,int bef){
        szmm[pos]=0;
        if(ban[pos])return 0;
        int s=1;
        for(auto to:path[pos]){
            if(to==bef)continue;
            s+=size(to,pos);
        }
        szmm[pos]=s;
        return s;
    }

    unordered_map<int,P> um1,um2;
    int dfs(int pos,int bef,int a){

    }
    
    int calc(int pos){
        assert(!ban[pos]);
        int a,b,c;
        int sz=size(pos,-1);
        bool flag=true;
        b=-1;
        while(flag){
            flag=false;
            for(auto to:path[pos]){
                if(to==b)c=sz-szmm[pos];
                else c=szmm[to];
                if(c*2>=sz){
                    flag=true;
                    b=pos;
                    pos=to;
                    break;
                }
            }
        }
        for(auto to:path[pos]){
            for(auto node:um2){
                um1[node.first]+=node.second;
            }
            um2.clear();
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        v1.resize(n);
        path.resize(n);
        ban.assign(n,0);
        szmm.assign(n,0);
        cin>>v1;
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}