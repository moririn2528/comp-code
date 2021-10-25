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
        mint ms=0;
        mint m2=2,m10=10;
        mint ma,mb;
        string sa;
        cin>>sa;
        n=sa.size();
        vector<int> v1;
        vector<mint> v2(n+1);
        for(i=0;i<n;i++){
            a=sa[i]-'0';
            v1.push_back(a);
        }
        for(i=0,ma=0;i<n-1;i++){
            ma*=10,ma+=v1[i];
            ms+=ma*m2.pow(n-i-2);
        }
        ma*=10,ma+=v1.back();
        ms+=ma;
        v2[n]=ma;
        for(i=n-1,ma=0;i>0;i--){
            ma+=m10.pow(n-1-i)*v1[i];
            ms+=ma*m2.pow(i-1);
            v2[n-i]=ma;
        }
        ma=0;
        for(i=1;i<n-1;i++)ma+=v1[i];
        mb=ma;
        ma+=v1[n-1];
        for(i=0;i<n-2;i++){
            ms+=mb*m2.pow(n-i-3);
            mb*=10;
            ma-=v1[i+1];
            mb+=ma;
            mb-=v2[i+2];
        }
        cout<<ms.val()<<endl;
    }
}

int main(){
    sol::solve();
}