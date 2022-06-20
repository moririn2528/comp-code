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
    const int N=1e6+7;

    vector<char> calc1(vector<P>& v1){
        int i,j;
        int n=v1.size();
        int a,b,c;
        vector<int> va,vb;
        vector<char> vs(N);
        va.push_back(0);
        for(i=0;i<n;i++){
            vb.clear();
            for(auto num:va){
                for(j=v1[i].first;j<=v1[i].second;j++){
                    if(j<10)a=num*10;
                    else a=num*100;
                    vb.push_back(a+j);
                }
            }
            va=vb;
        }
        for(auto num:va){
            vs[num]=1;
        }
        return vs;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        while(cin>>n){
            if(n==0)break;
            m=n/2;
            vector<P> v1(m),v2(n-m);
            cin>>v1>>v2;
            vector<char> vx=calc1(v1),vy=calc1(v2);
            vector<int> vt(N),vq(N);
            a=0;
            for(i=0;i<N;i++){
                if(!vy[i])continue;
                a++;
                for(j=10;j<=i;j*=10){
                    if(i%j<j/10)continue;
                    if(!vy[i%j])continue;
                    vt[i/j]++;
                }
            }
            LL s=0;
            for(i=N-1;i>=0;i--){
                if(!vx[i])continue;
                s+=a;
                if(vq[i])continue;
                for(j=10;j<=i;j*=10){
                    if(i%j<j/10)continue;
                    if(!vx[i/j])continue;
                    s-=vt[i%j];
                    vq[i/j]=1;
                }
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