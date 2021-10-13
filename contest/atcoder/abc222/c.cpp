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

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<vector<int>> v1(2*n,vector<int>(m));
        vector<int> sc(2*n);
        for(i=0;i<2*n;i++){
            string sa;
            cin>>sa;
            for(j=0;j<m;j++){
                if(sa[j]=='G')v1[i][j]=0;
                if(sa[j]=='C')v1[i][j]=1;
                if(sa[j]=='P')v1[i][j]=2;
            }
        }
        vector<P> vp;
        for(i=0;i<m;i++){
            vp.clear();
            for(j=0;j<2*n;j++){
                vp.push_back({-sc[j],j});
            }
            sort(vp.begin(),vp.end());
            for(j=0;j<2*n;j+=2){
                a=vp[j].second,b=vp[j+1].second;
                if((v1[a][i]+1)%3==v1[b][i])sc[a]++;
                if((v1[b][i]+1)%3==v1[a][i])sc[b]++;
            }
        }
        vp.clear();
        for(i=0;i<2*n;i++){
            vp.push_back({-sc[i],i});
        }
        sort(vp.begin(),vp.end());
        for(j=0;j<2*n;j++){
            cout<<vp[j].second+1<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}