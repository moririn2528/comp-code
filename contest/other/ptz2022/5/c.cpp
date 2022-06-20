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
const int INF=1<<20;
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
    const int M=3;
    const int N=1e6+7;
    int cost[N][M][2];
    vector<vector<int>> path;

    void dfs(int pos,int bef){
        int i,j;
        int a;
        int cnt=0;
        for(i=0;i<M;i++){
            for(j=0;j<2;j++){
                if(i==0)cost[pos][i][j]=0;
                else cost[pos][i][j]=INF;
            }
        }
        for(auto to:path[pos]){
            if(to==bef)continue;
            dfs(to,pos);
            cnt++;
            a=INF;
            int t[2]={INF,INF};
            for(i=0;i<M;i++){
                for(j=0;j<2;j++){
                    t[j]=min(t[j],cost[to][i][j]);
                    if(i<=1 && j==1)continue;
                    a=min(a,cost[to][i][j]+1);
                }
            }
            for(i=M-1;i>=0;i--){
                for(j=0;j<2;j++){
                    if(i==0)cost[pos][i][j]+=a;
                    else if(i<M-1)cost[pos][i][j]=min(cost[pos][i-1][j]+t[1-j],cost[pos][i][j]+a);
                    else cost[pos][i][j]=min(min(cost[pos][i-1][j],cost[pos][i][j])+t[1-j],cost[pos][i][j]+a);
                    cost[pos][i][j]=min(cost[pos][i][j],INF);
                }
            }
        }
        if(cnt==0){
            cost[pos][0][0]=0;
            cost[pos][0][1]=INF;
            return;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        path.resize(n);
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        dfs(0,-1);
        int s=INF;
        for(i=0;i<M;i++) s=min(s,cost[0][i][0]);
        for(i=2;i<M;i++) s=min(s,cost[0][i][1]);
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}
