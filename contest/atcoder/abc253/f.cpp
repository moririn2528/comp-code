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
    typedef tuple<LL,LL,LL> T;

    void solve(){
        LL n,m,q;
        LL i,j,k;
        LL a,b,c;
        LL x,y,z;
        cin>>n>>m>>q;
        vector<T> vq(q);
        vector<LP> v1(n);
        vector<T> va;
        vector<LL> vs(q);
        for(i=0;i<q;i++){
            cin>>a;
            if(a==1){
                cin>>a>>b>>c;
                a--;
                vq[i]={a,b,c};
                continue;
            }
            if(a==2){
                cin>>a>>b;
                a--;
                v1[a]={i,b};
                vq[i]={-2,0,0};
                continue;
            }
            cin>>a>>b;
            a--,b--;
            vq[i]={-3,a,b};
            vs[i]=v1[a].second;
            va.push_back({v1[a].first,-1,i});
            va.push_back({i,1,i});
        }
        sort(va.begin(),va.end());
        fenwick_tree<LL> seg(m+2);
        for(i=0,j=0;i<q;i++){
            tie(a,b,c)=vq[i];
            if(a<0)continue;
            for(;j<va.size() && get<0>(va[j])<=i;j++){
                tie(ignore,x,y)=va[j];
                tie(ignore,ignore,z)=vq[y];
                vs[y]+=x*seg.sum(0,z+1);
            }
            seg.add(a,c);
            seg.add(b,-c);
        }
        for(;j<va.size();j++){
            tie(ignore,x,y)=va[j];
            tie(ignore,ignore,z)=vq[y];
            vs[y]+=x*seg.sum(0,z+1);
        }
        for(i=0;i<q;i++){
            tie(a,b,c)=vq[i];
            if(a==-3)cout<<vs[i]<<endl;
            
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}