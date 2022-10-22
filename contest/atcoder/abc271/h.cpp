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

    void init(){
        
    }
    const int N=8;
    vector<P> mv={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        LL x,y;
        LL s=INF;
        cin>>x>>y;
        string sa;
        cin>>sa;
        for(i=0;i<N;i++){
            if(sa[i]=='0')continue;
            for(j=i+1;j<N;j++){
                if(sa[j]=='0')continue;
                if(abs(i-j)==4)continue;
                for(k=-1;k<N;k++){
                    LL p,q;
                    if(k==-1){
                        p=x,q=y,c=0;
                    }else{
                        if(sa[k]=='0')continue;
                        p=x-mv[k].first,q=y-mv[k].second;
                        c=1;
                    }
                    a=0;
                    if(mv[i].first==0)b=p/mv[j].first;
                    if(mv[i].second==0)b=q/mv[j].second;
                    if(mv[i].first+mv[i].second==0)b=(p+q)/(mv[j].first+mv[j].second);
                    if(mv[i].first-mv[i].second==0)b=(p-q)/(mv[j].first-mv[j].second);
                    if(b<0)continue;
                    p-=mv[j].first*b;
                    q-=mv[j].second*b;
                    if(mv[i].first)a=p/mv[i].first;
                    else a=q/mv[i].second;
                    if(a<0)continue;
                    if(p==mv[i].first*a && q==mv[i].second*a)s=min(s,a+b+c);
                }
            }
        }
        for(i=0;i<N;i++){
            if(sa[i]=='0')continue;
            if(mv[i].first)a=x/mv[i].first;
            else a=y/mv[i].second;
            if(a<0)continue;
            if(x==mv[i].first*a && y==mv[i].second*a)s=min(s,a);
        }
        if(x==0 && y==0)s=0;
        if(s>=INF)s=-1;
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}