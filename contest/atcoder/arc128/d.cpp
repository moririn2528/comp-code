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
        cin>>n;
        vector<P> v1;
        mint ma,mb;
        for(i=0;i<n;i++){
            cin>>a;
            if(v1.empty() || v1.back().first!=a)v1.push_back({a,0});
            else v1.back().second=1;
        }
        n=v1.size();
        fenwick_tree<mint> ft(n);
        ft.add(0,1);
        int t=-1,l=0;
        for(i=1;i<n;i++){
            ma=ft.sum(l,i);
            if(1<i && v1[i-2].first==v1[i].first){
                if(t!=-1){
                    ma=ft.sum(max(l,i-2),i);
                    if(l<t)ma+=ft.sum(l,t);
                }else t=i-2;
            }else t=-1;
            ft.add(i,ma);
            if(v1[i].second==1)l=i;
        }
        cout<<ft.sum(n-1,n).val()<<endl;
    }
}

int main(){
    sol::solve();
}