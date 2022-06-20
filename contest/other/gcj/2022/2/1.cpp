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
        if(i)os<<endl;
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

    void init(){
        
    }

    int grid(int x,int y,int n){
        int a=min({x,y,n-x-1,n-y-1});
        int s=n*n-(n-2*a)*(n-2*a);
        x-=a,y-=a,n-=2*a;
        if(y==0)return s+x+1;
        if(x==n-1)return s+n+y;
        if(y==n-1)return s+2*n-2+n-x;
        return s+3*n-3+n-y;
    }
    
    vector<P> vs;
    bool check(int& x,int& y,int i1,int j1,int i2,int j2,int n,int& m){
        int a=grid(x,y,n),b=grid(i1,j1,n),c=grid(i2,j2,n);
        if(b<a)return false;
        a=c-b-1;
        if(a==0)return false;
        assert(a>0);
        if(a<=m){
            m-=a;
            x=i2,y=j2;
            vs.push_back({b,c});
            return true;
        }
        return false;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        if(m<n-1 || m%2){
            cout<<"IMPOSSIBLE"<<endl;
            return;
        }
        m=n*n-1-m;
        vs.clear();
        a=0,b=0;
        for(i=0;i<n/2;i++){
            check(a,b,n/2,i,n/2,i+1,n,m);
            check(a,b,n-i-1,n/2,n-i-2,n/2,n,m);
            check(a,b,n/2,n-i-1,n/2,n-i-2,n,m);
            check(a,b,i,n/2,i+1,n/2,n,m);
        }
        cout<<vs.size()<<endl;
        cout<<vs<<endl;
        assert(m==0);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        cout<<"Case #"<<i+1<<": ";
        sol::solve();
    }
}