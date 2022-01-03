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
    typedef tuple<LL,LL,LL> T;

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n;
        vector<T> vt;
        vector<int> v1(n,-1);
        vector<int> vs(2*n+2);
        for(i=0;i<n;i++){
            cin>>a>>b;
            vt.push_back({a-1,b,i});
            vt.push_back({a,b-1,-i});
        }
        sort(vt.begin(),vt.end(),[](T a,T b){
            LL x1,y1,x2,y2,c1,c2;
            tie(x1,y1,c1)=a;
            tie(x2,y2,c2)=b;
            return x1*y2<x2*y1 || (x1*y2==x2*y1 && c1<c2);
        });
        for(i=0;i<2*n;i++){
            tie(ignore,ignore,a)=vt[i];
            a=abs(a);
            if(v1[a]==-1)v1[a]=i;
            else{
                vs[i]=max(vs[i],vs[v1[a]]+1);
            }
            vs[i+1]=vs[i];
        }
        cout<<vs[2*n]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}