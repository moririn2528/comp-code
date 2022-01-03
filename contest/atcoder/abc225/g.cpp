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
#include<atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
const LL INF=1LL<<45;
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
        int n,m,p;
        int i,j,k;
        LL a,b,c;
        cin>>n>>m>>p;
        mf_graph<LL> g((n+2)*(m+2)+5);
        int start_pos=(n+2)*(m+2)+3,end_pos=(n+2)*(m+2)+4;
        LL s=0;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                cin>>a;
                g.add_edge(start_pos,(i+1)*(m+2)+j+1,a);
                s+=a;
            }
        }
        for(i=0;i<n+2;i++){
            for(j=0;j<m+2;j++){
                if(i+1<n+2 && j+1<m+2)g.add_edge(i*(m+2)+j,(i+1)*(m+2)+j+1,p);
                if(i+1<n+2 && 0<=j-1)g.add_edge(i*(m+2)+j,(i+1)*(m+2)+j-1,p);
                if(i==0 || i==n+1 || j==0 || j==m+1){
                    g.add_edge(i*(m+2)+j,end_pos,INF);
                }
            }
        }
        s-=g.flow(start_pos,end_pos);
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}