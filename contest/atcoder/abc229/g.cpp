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
    LL n,m;
    string sa;

    bool check(LL x){
        vector<LL> v1(n+7),v2(n+7);
        int i,j,k;
        LL a,b,c;
        LL s=0;
        for(i=0,j=0;i<x && j<n;j++){
            if(sa[j]=='Y'){
                i++;
                continue;
            }
            if(i<=x/2){
                v1[0]+=i;
                a=i-x;
                v2[0]--,v2[a+x]++;
            }else{
                v1[0]+=x-i;
                a=i-x;
                v2[0]++,v2[a+x/2]--;
                v2[a+x-x/2]--,v2[a+x]++;
            }
        }
        if(i<x)return false;
        for(;j<n;j++){
            if(sa[j]=='Y'){
                i++;
                continue;
            }
            a=i-x;
            v2[a]++,v2[a+x/2]--;
            v2[a+x-x/2]--,v2[a+x]++;
        }
        c=i;
        for(i=0;i<=n;i++){
            v2[i+1]+=v2[i];
        }
        for(i=0;i<=c-x;i++){
            v1[i+1]=v1[i]+v2[i];
            if(v1[i]<=m)return true;
        }
        return false;
    }

    void solve(){
        int i,j,k;
        LL a,b,c;
        cin>>sa>>m;
        n=sa.size();
        LL z[3]={0,n+1};
        while(z[1]-z[0]>1){
            z[2]=(z[0]+z[1])/2;
            if(check(z[2]))z[0]=z[2];
            else z[1]=z[2];
        }
        cout<<z[0]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}