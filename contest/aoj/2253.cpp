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
    const int N=35;
    const int mv[6][2]={{1,1},{1,0},{0,1},{-1,-1},{-1,0},{0,-1}};

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y;
        while(cin>>m>>n){
            if(m==0 && n==0)return;
            vector<P> vp;
            for(i=0;i<n;i++){
                cin>>a>>b;
                vp.push_back({a,b});
            }
            cin>>x>>y;
            vector<vector<char>> used(2*N,vector<char>(2*N));
            for(i=0;i<n;i++){
                a=vp[i].first,b=vp[i].second;
                a-=x-N,b-=y-N;
                if(a<0 || a>=2*N || b<0 || b>=2*N)continue;
                used[a][b]=1;
            }
            queue<P> q1;
            int s=0;
            q1.push({N,N});
            for(i=0;i<=m;i++){
                for(j=q1.size();j>0;j--){
                    a=q1.front().first,b=q1.front().second;
                    q1.pop();
                    if(used[a][b])continue;
                    used[a][b]=1;
                    s++;
                    for(k=0;k<6;k++){
                        q1.push({a+mv[k][0],b+mv[k][1]});
                    }
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