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
const LL INF=1LL<<60;
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
        cin>>n;
        vector<LL> v1(n),v2(n+1);
        vector<vector<LL>> dp(n+3,vector<LL>(n+3,-1));
        vector<vector<int>> bef(n+3,vector<int>(n+3));
        cin>>v1;
        for(i=0;i<n;i++){
            v2[i+1]=v2[i]+v1[i];
        }
        for(i=0;i<n;i++){
            vector<LL> va(n+4,INF),vb(n+4,-2);
            if(i==0)va[0]=-INF,vb[0]=-1;
            for(j=0;j<i;j++){
                if(dp[j][i]==-1)continue;
                b=v2[i]-v2[j]+v2[i]+1;
                c=dp[j][i]+1;
                if(va[c]>b){
                    va[c]=b;
                    vb[c]=j;
                }
            }
            for(j=n-1;j>=0;j--){
                if(va[j+1]<va[j]){
                    va[j]=va[j+1];
                    vb[j]=-1;
                }
            }
            for(j=i+1;j<=n;j++){
                auto itr=upper_bound(va.begin(),va.end(),v2[j]);
                if(itr==va.begin())continue;
                assert(itr!=va.end());
                itr--;
                k=itr-va.begin();
                assert(vb[k]!=-2);
                dp[i][j]=k;
                bef[i][j]=vb[k];
            }
        }
        int s=-1;
        a=-1;
        for(i=0;i<n;i++){
            if(s<dp[i][n]){
                s=dp[i][n];
                a=i,b=n;
            }
        }
        assert(a!=-1);
        vector<int> vs;
        for(i=0;i<n && a>0;i++){
            vs.push_back(a);
            c=bef[a][b];
            b=a,a=c;
        }
        assert(a==0);
        assert(vs.size()==s);
        reverse(vs.begin(),vs.end());
        cout<<s+1<<endl;
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}