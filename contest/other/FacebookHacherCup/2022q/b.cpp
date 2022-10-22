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
        if(i)os<<endl;
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

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y;
        cin>>n>>m;
        vector<string> v1(n);
        cin>>v1;
        vector<vector<char>> grid(n+2,vector<char>(m+2));
        vector<vector<char>> deg(n+2,vector<char>(m+2));
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(v1[i][j]!='#')grid[i+1][j+1]=1;
            }
        }
        queue<P> q1;
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                a=0,b=1,c=0;
                for(k=0;k<4;k++,swap(b,c),b=-b){
                    a+=grid[i+b][j+c];
                }
                deg[i][j]=a;
                if(a<2)q1.push({i,j});
            }
        }
        while(!q1.empty()){
            a=q1.front().first,b=q1.front().second;q1.pop();
            if(v1[a-1][b-1]=='^'){
                cout<<"Impossible"<<endl;
                return;
            }
            grid[a][b]=0;
            x=1,y=0;
            for(k=0;k<4;k++,swap(x,y),x=-x){
                deg[a+x][b+y]--;
                if(deg[a+x][b+y]==1)q1.push({a+x,b+y});
            }
        }
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(grid[i+1][j+1])v1[i][j]='^';
            }
        }
        cout<<"Possible"<<endl;
        cout<<v1<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        cout<<"Case #"<<i+1<<": ";
        sol::solve();
    }
}