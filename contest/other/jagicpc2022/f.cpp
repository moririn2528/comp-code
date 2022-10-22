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
#include <array>
#include <type_traits>
#include <numeric>
#include <utility>
using namespace std;

typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
const LL INF=1LL<<60;
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
        LL n,m,p;
        LL i,j,k;
        LL a,b,c,d;
        while(cin>>n>>m>>p){
            if(n==0)break;
            vector<vector<T>> path(n);
            for(i=0;i<m;i++){
                cin>>a>>b>>c>>d;
                a--,b--;
                path[a].push_back({b,c,d});
            }
            vector<vector<LL>> v1(n);
            v1[n-1]=vector<LL>(p+1,0);
            for(i=n-2;i>=0;i--){
                vector<LL> va;
                for(auto node:path[i]){
                    LL to;
                    tie(to,c,d)=node;
                    if(v1[to].empty())continue;
                    vector<LL> vb(p+1);
                    vb[0]=INF;
                    for(j=1;j<=p;j++){
                        vb[j]=min(v1[to][j]+c*j+d*j*(j-1)/2,INF);
                    }
                    if(va.empty()){
                        copy(vb.begin(), vb.end(), back_inserter(va));
                        continue;
                    }
                    vector<LL> vc(va);
                    a=1;
                    va[0]=INF;
                    va[1]=INF;
                    for(j=2;j<=p;j++){
                        for(;a+1<=j && vb[j-a]<INF && vc[a]+vb[j-a]>vc[a+1]+vb[j-a-1];a++);
                        va[j]=vc[a]+vb[j-a];
                    }

                    // for debug
                    vector<LL> vd(p+1,INF);
                    for(j=0;j<=p;j++){
                        for(k=0;k<=j;k++){
                            vd[j]=min(vd[j],vc[k]+vb[j-k]);
                        }
                        if(vd[j]<INF)assert(vd[j]==va[j]);
                    }
                }
                if(va.empty())continue;
                copy(va.begin(), va.end(), back_inserter(v1[i]));
            }
            if(v1[0].empty())cout<<-1<<endl;
            else if(v1[0][p]>=INF)cout<<-1<<endl;
            else cout<<v1[0][p]<<endl;
        }
        
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}