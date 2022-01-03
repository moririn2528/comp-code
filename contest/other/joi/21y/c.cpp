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
    int n,m;
    vector<vector<int>> su;
    bool check(int x,int y){
        int t=su[x][y];
        int i,j,k;
        int a,b;
        vector<int> v1,v2;
        for(i=0,j=0;i<=n;i++){
            if(su[i][y]==j*t)j++,v1.push_back(i);
        }
        for(i=0,j=0;i<=m;i++){
            if(su[x][i]==j*t)j++,v2.push_back(i);
        }
        if(v1.empty() || v2.empty())return false;
        if(v1.back()!=n || v2.back()!=m)return false;
        for(i=0;i<v1.size();i++){
            for(j=0;j<v2.size();j++){
                a=v1[i],b=v2[j];
                if(su[a][b]!=i*j*t)return false;
            }
        }
        return true;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<vector<int>> grid(n,vector<int>(m));
        su.assign(n+1,vector<int>(m+1));
        cin>>grid;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                su[i+1][j+1]=su[i][j+1]+su[i+1][j]-su[i][j]+grid[i][j];
            }
        }
        int s=-1;
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                if(check(i,j))s++;
            }
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}