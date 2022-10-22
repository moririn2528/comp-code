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
    int n,m;
    vector<vector<int>> path;
    vector<LL> weight;

    bool check(LL t){
        int i,j,k;
        int a;
        vector<LL> v1(n,0);
        for(i=0;i<n;i++){
            for(auto to:path[i]){
                v1[to]+=weight[i];
            }
        }
        queue<int> q1;
        for(i=0;i<n;i++){
            if(v1[i]<=t)q1.push(i);
        }
        for(i=0;i<n;i++){
            if(q1.empty())return false;
            a=q1.front();q1.pop();
            for(auto to:path[a]){
                if(v1[to]<=t)continue;
                v1[to]-=weight[a];
                if(v1[to]<=t)q1.push(to);
            }
        }
        return true;
    }

    void solve(){
        int i,j,k;
        LL a,b,c;
        cin>>n>>m;
        weight.resize(n);
        cin>>weight;
        path.assign(n,vector<int>());
        for(i=0;i<m;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        LL z[3]={-1,1LL<<60};
        while(z[1]-z[0]>1LL){
            z[2]=(z[0]+z[1])/2;
            if(check(z[2]))z[1]=z[2];
            else z[0]=z[2];
        }
        cout<<z[1]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}