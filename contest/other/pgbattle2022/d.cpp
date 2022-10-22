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

using mint=modint998244353;

namespace sol{
    int n,m;
    vector<int> v1;
    const int N=1e5;
    vector<mint> kai;
    mint comb(int a,int b){
        if(b<0 || a<b)return 0;
        return kai[a]/(kai[b]*kai[a-b]);
    }

    void dfs(int pos, int bef,vector<vector<int>>& path, vector<vector<mint>>& arr){
        int i,j,k;
        mint a,b,c;
        a=1;
        for(i=0;i<=m;i++,a*=v1[pos]){
            arr[pos][i]=a;
        }
        for(auto to:path[pos]){
            if(to==bef)continue;
            dfs(to,pos,path,arr);
            for(i=m;i>=0;i--){
                a=arr[pos][i];
                for(j=0;j<=i;j++){
                    a+=arr[pos][i-j]*arr[to][j]*comb(i,j);
                }
                arr[pos][i]=a;
            }
        }
    }
    void dfs2(int pos,int bef,vector<vector<int>>& path, vector<vector<mint>>& arr,vector<vector<mint>>& arr2){
        vector<int> tos;
        for(auto to:path[pos]){
            if(to==bef)continue;
            tos.push_back(to);
        }
        int p=tos.size();
        int i,j,k;
        mint a,b,c;
        if(p==0)return;
        vector<vector<mint>> va(p+1,vector<mint>(m+1));
        vector<vector<mint>> vb(p+1,vector<mint>(m+1));
        a=1;
        for(i=0;i<=m;i++,a*=v1[pos]){
            va[0][i]=a;
            vb[p-1][i]=arr[tos[p-1]][i];
        }
        int x,y;
        for(k=p-2;k>=0;k--){
            x=tos[k];
            for(i=m;i>=0;i--){
                a=vb[k+1][i];
                for(j=0;j<=i;j++){
                    a+=vb[k+1][i-j]*arr[x][j]*comb(i,j);
                }
                vb[k][i]=a;
            }
        }
        for(k=0;k<p;k++){
            x=tos[k];
            for(i=m;i>=0;i--){
                a=va[k][i];
                for(j=0;j<=i;j++){
                    a+=va[k][i-j]*arr[x][j]*comb(i,j);
                }
                va[k+1][i]=a;
            }
        }
        for(k=0;k<p;k++){
            x=tos[k];
            for(i=m;i>=0;i--){
                a=va[k][i];
                for(j=0;j<=i;j++){
                    a+=va[k][i-j]*vb[k+1][j]*comb(i,j);
                }
                arr2[x][i]=a;
            }
            for(i=m;i>=0;i--){
                a=arr[x][i];
                for(j=0;j<=i;j++){
                    a+=arr[x][i-j]*arr2[x][j]*comb(i,j);
                }
                arr[x][i]=a;
            }
        }
        for(auto to:path[pos]){
            if(to==bef)continue;
            dfs2(to,pos,path,arr,arr2);
        }
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        v1.resize(n);
        cin>>v1;
        kai.resize(N);
        kai[0]=1;
        for(i=1;i<N;i++){
            kai[i]=kai[i-1]*i;
        }
        vector<vector<int>> path(n);
        vector<vector<mint>> arr(n,vector<mint>(m+1));
        vector<vector<mint>> arr2(n,vector<mint>(m+1));
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        dfs(0,-1,path,arr);
        dfs2(0,-1,path,arr,arr2);
        for(i=0;i<n;i++){
            cout<<arr[i][m].val()<<endl;
        }
    }
}

int main(){
    sol::solve();
}