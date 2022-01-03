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

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        int x1,y1,x2,y2;
        cin>>n>>m;
        vector<vector<LL>> grid(n,vector<LL>(m));
        vector<vector<LL>> su(n+1,vector<LL>(m+1));
        vector<vector<LL>> v1(n+1,vector<LL>(m+1));
        cin>>x1>>y1>>x2>>y2;
        x2=min(x1,x2),y2=min(y1,y2);
        cin>>grid;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                su[i+1][j+1]=su[i][j+1]+su[i+1][j]-su[i][j]+grid[i][j];
            }
        }
        for(i=0;i<=n-x2;i++){
            for(j=0;j<=m-y2;j++){
                v1[i][j]=su[i][j]+su[i+x2][j+y2]-su[i][j+y2]-su[i+x2][j];
            }
        }
        for(i=0;i<n;i++){
            priority_queue<LP> q1;
            for(j=0;j<=y1-y2;j++){
                q1.push({v1[i][j],j});
            }
            k=y1-y2+1;
            for(j=0;j<=m-y1;j++){
                while(q1.top().second<j)q1.pop();
                v1[i][j]=q1.top().first;
                q1.push({v1[i][j+k],j+k});
            }
        }
        for(j=0;j<m;j++){
            priority_queue<LP> q1;
            for(i=0;i<=x1-x2;i++){
                q1.push({v1[i][j],i});
            }
            k=x1-x2+1;
            for(i=0;i<=n-x1;i++){
                while(q1.top().second<i)q1.pop();
                v1[i][j]=q1.top().first;
                q1.push({v1[i+k][j],i+k});
            }
        }
        a=0;
        for(i=0;i<=n-x1;i++){
            for(j=0;j<=m-y1;j++){
                b=su[i+x1][j+y1]+su[i][j]-su[i][j+y1]-su[i+x1][j];
                b-=v1[i][j];
                a=max(b,a);
            }
        }
        cout<<a<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}