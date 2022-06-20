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
    typedef tuple<LL,LL,LL> T;

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        LL x,y,z;
        cin>>n>>m;
        vector<T> v1,v2;
        for(i=0;i<n;i++){
            cin>>a>>b>>c;
            v1.push_back({a,1,i});
            v1.push_back({b,0,i});
            v2.push_back({a,b,c});
        }
        vector<LL> dp(2*n+2,INF);
        vector<char> val(n);
        dp[0]=0;
        map<int,int> m1;
        vector<int> cnt(2*n+5);
        sort(v1.begin(),v1.end());
        for(i=0,k=0;i<v1.size();k++){
            tie(a,b,c)=v1[i];
            m1[a]=k;
            cnt[k+1]=cnt[k];
            for(;i<v1.size() && get<0>(v1[i])==a;i++){
                tie(x,y,z)=v1[i];
                if(y)val[z]=1,cnt[k+1]++;
                else val[z]=0;
            }
            vector<LL> va(2*n+5),vb(2*n+5);
            x=cnt[k+1];
            for(j=0;j<n;j++){
                if(val[j]){
                    tie(a,b,c)=v2[j];
                    va[m1[a]]+=c;
                    vb[m1[a]+1]++;
                    x--;
                }
            }
            for(j=2*n;j>=0;j--){
                va[j]+=va[j+1];
            }
            LL s=INF;
            for(j=0;j<=k;j++){
                x+=vb[j];
                if(x-cnt[j]>m)continue;
                s=min(s,dp[j]+va[j]);
            }
            dp[k+1]=s;
        }
        cout<<dp[k]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}