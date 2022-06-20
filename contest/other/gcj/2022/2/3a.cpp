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
        LL n,m;
        LL i,j,k;
        LL a,b,c;
        cin>>n;
        vector<LP> vc(n),vt(n);
        LL p,q;
        cin>>vc;
        cin>>p>>q;
        cin>>vt;
        vt.push_back({p,q});
        vector<char> ok(1<<(2*n));
        ok[0]=1;
        vector<vector<LP>> v1(n);
        for(i=0;i<n;i++){
            for(j=0;j<=n;j++){
                a=(vc[i].first-vt[j].first)*(vc[i].first-vt[j].first)+(vc[i].second-vt[j].second)*(vc[i].second-vt[j].second);
                v1[i].push_back({a,j});
            }
            sort(v1[i].begin(),v1[i].end());
        }
        vector<vector<LL>> va(n,vector<LL>(1<<n,-1));
        for(i=0;i<n;i++){
            for(j=0;j<(1<<n);j++){
                for(k=0;k<=n;k++){
                    c=v1[i][k].second;
                    if(c==n)break;
                    if(j&1<<c)continue;
                    va[i][j]=k;
                    break;
                }
            }
        }
        vector<LP> bef(1<<(2*n));
        for(i=0;i<(1<<(2*n));i++){
            if(!ok[i])continue;
            for(j=0;j<n;j++){
                if(i&1<<(n+j))continue;
                a=i&((1<<n)-1);
                if(va[j][a]==-1)continue;
                k=va[j][a];
                b=v1[j][k].first;
                for(;k<=n && b==v1[j][k].first;k++){
                    c=v1[j][k].second;
                    if(c==n)break;
                    if(i&1<<c)continue;
                    ok[i|1<<(n+j)|1<<c]=1;
                    bef[i|1<<(n+j)|1<<c]={j,c};
                }
            }
        }
        a=(1<<(2*n))-1;
        if(ok[a])cout<<"POSSIBLE"<<endl;
        else{
            cout<<"IMPOSSIBLE"<<endl;
            return;
        }
        vector<LP> vs;
        for(i=0;i<n;i++){
            b=bef[a].first,c=bef[a].second;
            vs.push_back({b+1,c+2});
            assert(a&1<<(n+b));
            assert(a&1<<c);
            a^=1<<(n+b)|1<<c;
        }
        assert(a==0);
        reverse(vs.begin(),vs.end());
        cout<<vs<<endl;
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