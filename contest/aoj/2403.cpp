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
    const int N=20;
    vector<int> calc(int n,int x,vector<int>& u,vector<int>& v1){
        int i,j,k;
        int a,b,c;
        vector<int> vs(1<<n,-INF);
        for(i=0;i<(1<<n);i++){
            a=0,b=0;
            for(j=0;j<n;j++){
                if(~i&1<<j)continue;
                a+=v1[x+j];
                if(i&u[x+j])break;
                b|=1<<j|u[x+j];
            }
            if(j==n)vs[i]=a;
        }
        return vs;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa;
        while(cin>>n){
            if(n==0)return;
            int n1=min(n,N),n2=n-n1;
            int s=0;
            vector<int> v1;
            vector<vector<string>> va(n);
            vector<int> u1(n),u2(n);
            map<string,int> m1;
            for(i=0;i<n;i++){
                cin>>sa>>a>>b;
                v1.push_back(a);
                m1[sa]=i;
                for(j=0;j<b;j++){
                    cin>>sa;
                    va[i].push_back(sa);
                }
            }
            for(i=0;i<n;i++){
                for(j=0;j<va[i].size();j++){
                    a=m1[va[i][j]];
                    if(a<N)u1[i]|=1<<a;
                    else u2[i]|=1<<(a-N);
                }
            }
            vector<int> vt1=calc(n1,0,u1,v1),vt2=calc(n2,n1,u2,v1);
            for(i=0;i<n2;i++){
                for(j=0;j<(1<<n2);j++){
                    if(~j&1<<i)vt2[j|1<<i]=max(vt2[j|1<<i],vt2[j]);
                }
            }
            for(i=0;i<(1<<n1);i++){
                if(~i&1)continue;
                a=0;
                for(j=0;j<n1;j++){
                    if(i&1<<j)a|=u2[j];
                }
                a^=(1<<n2)-1;
                s=max(s,vt1[i]+vt2[a]);
            }
            cout<<s<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}