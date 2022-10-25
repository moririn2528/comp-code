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

typedef long double D;
typedef vector<D> V1;
typedef vector<V1> V2;
typedef vector<V2> V3;
namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        const D INF=1e18;
        V3 vs(m+2,V2(1<<(n+m),V1(n+m,INF)));
        D s=INF;
        D da;
        vector<P> pos(n+m);
        cin>>pos;
        for(i=0;i<n;i++){
            vs[0][1<<i][i]=sqrt(pos[i].first*pos[i].first+pos[i].second*pos[i].second);
        }
        for(i=n;i<n+m;i++){
            vs[1][1<<i][i]=sqrt(pos[i].first*pos[i].first+pos[i].second*pos[i].second);
        }
        for(i=0;i<=m;i++){
            for(j=0;j<(1<<(n+m));j++){
                for(k=0;k<n+m;k++){
                    if(vs[i][j][k]==INF)continue;
                    if((~j&((1<<n)-1))==0){
                        da=sqrt(pos[k].first*pos[k].first+pos[k].second*pos[k].second);
                        da/=1<<i;
                        s=min(s,vs[i][j][k]+da);
                    }
                    for(a=0;a<n+m;a++){
                        if(j&(1<<a))continue;
                        b=i;
                        if(n<=a)b++;
                        da=sqrt((pos[k].first-pos[a].first)*(pos[k].first-pos[a].first)+(pos[k].second-pos[a].second)*(pos[k].second-pos[a].second));
                        da/=1<<i;
                        vs[b][j|(1<<a)][a]=min(vs[b][j|(1<<a)][a],vs[i][j][k]+da);
                    }
                }
            }
        }
        cout<<fixed<<setprecision(20)<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}