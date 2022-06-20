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
    typedef vector<LL> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;

    void solve(){
        int n,m,p;
        int i,j,k;
        int a,b,c;
        cin>>n>>p;
        V3 dp(n+2,V2(n+2,V1(2)));
        dp[0][0][0]=1;
        dp[0][1][1]=1;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<2;k++){
                    dp[i][j][k]%=p;
                }
                dp[i+1][j+2][1]+=2*dp[i][j][0];
                dp[i+1][j+1][0]+=3*dp[i][j][0];
                dp[i+1][j][0]+=dp[i][j][0];
                dp[i+1][j+1][1]+=dp[i][j][1];
                dp[i+1][j][0]+=dp[i][j][1];
            }
        }
        vector<LL> vs;
        for(i=1;i<n;i++){
            vs.push_back(dp[n-1][i][0]%p);
        }
        cout<<vs<<endl;
    }
}

int main(){
    sol::solve();
}