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
    typedef vector<int> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
    typedef vector<V3> V4;
    typedef tuple<int,int,int> T;
    V2 vw;

    P mid(P a,P b){
        if(a>b)swap(a,b);
        if(a.first==b.first)return {2*a.first,a.second};
        return {2*a.first+1,a.second};
    }
    bool is_wall(P a,P b){
        P pa=mid(a,b);
        return vw[pa.first][pa.second];
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int p,q,r;
        while(cin>>n>>m){
            if(n==0)return;
            vw.assign(2*n-1,vector<int>(m));
            for(i=0;i<2*n-1;i++){
                for(j=0;j<m-1+i%2;j++){
                    cin>>vw[i][j];
                }
            }
            V4 dp1(2*n,V3(m,V2(n,V1(m,INF))));
            queue<P> q1;
            for(i=0;i<2*n-1;i++){
                for(j=0;j<m-1+i%2;j++){
                    q1.push({n-1,m-1});
                    for(k=0;!q1.empty();k++){
                        for(p=q1.size();p>0;p--){
                            P pa=q1.front();q1.pop();
                            if(dp1[i][j][pa.first][pa.second]!=INF)continue;
                            dp1[i][j][pa.first][pa.second]=k;
                            for(q=-1;q<=1;q++){
                                for(r=-1;r<=1;r++){
                                    if((q+r+2)%2==0)continue;
                                    int x=pa.first+q,y=pa.second+r;
                                    if(x<0 || y<0 || n<=x || m<=y)continue;
                                    if(is_wall(pa,{x,y}))continue;
                                    if(mid(pa,{x,y})==P(i,j))continue;
                                    q1.push({x,y});
                                }
                            }
                        }
                    }
                }
            }
            V2 dis(n,V1(m,INF));
            priority_queue<T,vector<T>,greater<T>> q2;
            q2.push({0,n-1,m-1});
            while(!q2.empty()){
                tie(a,b,c)=q2.top();q2.pop();
                if(dis[b][c]!=INF || a>=INF)continue;
                dis[b][c]=a;
                for(q=-1;q<=1;q++){
                    for(r=-1;r<=1;r++){
                        if((q+r+2)%2==0)continue;
                        int x=b+q,y=c+r;
                        if(x<0 || y<0 || n<=x || m<=y)continue;
                        if(is_wall({b,c},{x,y}))continue;
                        P pa=mid({b,c},{x,y});
                        int cost=max(a+1,dp1[pa.first][pa.second][x][y]);
                        q2.push({cost,x,y});
                    }
                }
            }
            int s=dis[0][0];
            if(s>=INF)s=-1;
            cout<<s<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}