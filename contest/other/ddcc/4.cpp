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
        if(i)os<<",";
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
    typedef tuple<int,int,int,int,int> T;

    int solve(istringstream is){
        int n,m;
        int i,j,k;
        int a,b,c,d,w;
        is>>n>>m;
        string sa;
        is>>sa;
        swap(n,m);
        int sx,sy;
        V2 we(n,V1(m));
        V2 idx(n,V1(m,-1));

        for(i=0,k=0;i<n;i++){
            for(j=0;j<m;j++){
                char ca=sa[i*m+j];
                if(ca=='R')sx=i,sy=j;
                if('1'<=ca && ca<='9'){
                    we[i][j]=ca-'0';
                    idx[i][j]=k++;
                }
                if(ca=='X')we[i][j]=-1;
            }
        }
        int p=k;
        V3 cost(n,V2(m,V1(1<<p,-1)));
        priority_queue<T,vector<T>,greater<T>> q1;
        q1.push({0,sx,sy,0,1000});
        while(!q1.empty()){
            tie(d,a,b,c,w)=q1.top();q1.pop();
            if(cost[a][b][c]!=-1)continue;
            cost[a][b][c]=d;
            for(i=-1;i<=1;i++){
                for(j=-1;j<=1;j++){
                    if((i+j+2)%2==0)continue;
                    int x=a+i,y=b+j;
                    if(x<0 || n<=x || y<0 || m<=y)continue;
                    if(we[x][y]==-1)continue;
                    int co=d+w;
                    q1.push({co,x,y,c,w});
                    if(we[x][y]==0)continue;
                    if(c&1<<idx[x][y])continue;
                    q1.push({co,x,y,c|1<<idx[x][y],w+we[x][y]});
                }
            }
        }
        return cost[sx][sy][(1<<p)-1];
    }
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    vector<int> vs;
    for(int i=0;i<3;i++){
        string sa;
        getline(cin,sa);
        sa.erase(sa.begin());
        if(sa.back()==',')sa.pop_back();
        sa.pop_back();
        vs.push_back(
            sol::solve(istringstream(sa))
        );
    }
    cout<<vs<<endl;
}