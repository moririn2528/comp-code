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

template <typename T>
void fwt(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = x + y, f[j | i] = x - y;
            }
        }
    }
}
template <typename T>
void ifwt(vector<T>& f) {
    int n = f.size();
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if ((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = (x + y) / 2, f[j | i] = (x - y) / 2;
            }
        }
    }
}

namespace sol{

    int char2int(char ca){
        if(ca=='R')return 0;
        if(ca=='S')return 1;
        if(ca=='P')return 2;
        return -1;
    }

    void solve(){
        int n,m,q;
        int i,j,k;
        LL a,b,c;
        cin>>q>>n>>m;
        vector<LL> v1(1<<(2*q)),v2(1<<(2*q));
        string sa;
        for(i=0;i<n;i++){
            cin>>sa;
            a=0;
            for(j=0;j<q;j++){
                a*=3;
                a+=char2int(sa[j]);
            }
            v1[a]++;
        }
        for(i=0;i<m;i++){
            cin>>sa;
            a=0;
            for(j=0;j<q;j++){
                a*=3;
                a+=char2int(sa[j]);
            }
            v2[a]++;
        }
        fwt(v1);
        fwt(v2);
        for(i=0;i<v1.size();i++){
            v1[i]*=v2[i];
        }
        ifwt(v1);
        LL s=0;
        for(i=0;i<v1.size();i++){
            a=1;
            for(j=0;j<q;j++){
                if(i&3<<(2*j))a*=3;
                else a*=2;
            }
            s+=v1[i]*a;
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}