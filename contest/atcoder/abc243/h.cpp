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
    const int N=111;

    int sign(int a){
        if(a>0)return 1;
        if(a==0)return 0;
        return -1;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int sx,sy,ex,ey;
        string sa;
        cin>>n>>m;
        vector<vector<char>> used(n+2,vector<char>(m+2));
        vector<vector<int>> col(n+2,vector<int>(m+2));
        for(i=0;i<n;i++){
            cin>>sa;
            for(j=0;j<m;j++){
                if(sa[j]=='.')continue;
                used[i+1][j+1]=1;
                if(sa[j]=='S')sx=i+1,sy=j+1;
                if(sa[j]=='G')ex=i+1,ey=j+1;
            }
        }
        for(i=0;i<n+2;i++)col[i][0]=col[i][m+1]=10;
        for(i=0;i<m+2;i++)col[0][i]=col[n+1][i]=10;
        a=sx,b=sy;
        vector<P> v1;
        while(a!=ex || b!=ey){
            if(a!=ex)a+=sign(ex-a);
            else b+=sign(ey-b);
            v1.push_back({a,b});
        }
        v1.pop_back();
        if(v1.empty()){
            cout<<"No"<<endl;
            return;
        }
        for(auto p:v1){
            col[p.first][p.second]=1;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}