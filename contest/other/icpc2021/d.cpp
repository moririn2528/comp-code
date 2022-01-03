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
    const int N=1e4;
    int to(P pa){return pa.first*N+pa.second;}
    int to(int a,int b){return a*N+b;}

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        while(cin>>n){
            if(n==0)return;
            vector<int> v1(n);
            vector<unordered_set<int>> vs(n+1);
            cin>>v1;
            vs[0].insert(to(0,0));
            auto ins=[&](int x,int y,int z){
                vs[x].insert(to(min(y,z),max(y,z)));
            };
            for(i=0;i<n;i++){
                for(auto num:vs[i]){
                    a=num/N,b=num%N;
                    vs[i+1].insert(to(a,b+v1[i]));

                    c=a+v1[i];
                    ins(i+1,b,c);

                    if(v1[i]<=a)vs[i+1].insert(to(a-v1[i],b-v1[i]));
                    else ins(i+1,v1[i]-a,b-a);
                }
            }
            int s=N;
            for(auto num:vs[n]){
                a=num/N,b=num%N;
                s=min(s,a+b);
            }
            s=-s;
            for(i=0;i<n;i++){
                s+=v1[i];
            }
            assert(s%3==0);
            cout<<s/3<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}