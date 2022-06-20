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
        cin>>n>>m;
        vector<int> v1(m);
        cin>>v1;
        vector<vector<LL>> v2(m,vector<LL>(n));
        cin>>v2;
        vector<deque<LP>> que(m);
        vector<LL> dif(m);
        vector<LP> va={{0,-1}},vb;
        vector<vector<int>> bef1(n+2,vector<int>(m+2,-1));
        vector<vector<int>> bef2(n+2,vector<int>(m+2,-1));
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                a=va[0].first+dif[j];
                bef2[i][j]=va[0].second;
                if(va[0].second==j){
                    a=va[1].first+dif[j];
                    bef2[i][j]=va[1].second;
                }
                while(!que[j].empty() && a<=que[j].back().first){
                    que[j].pop_back();
                }
                que[j].push_back({a,i});

                dif[j]-=v2[j][i];
                while(!que[j].empty() && que[j].front().second+v1[j]<=i){
                    que[j].pop_front();
                }
                assert(!que[j].empty());
                a=que[j].front().first-dif[j];
                bef1[i+1][j]=que[j].front().second;
                vb.push_back({a,j});
                
            }
            swap(va,vb);
            vb.clear();
            sort(va.begin(),va.end());
        }
        cout<<va[0].first<<endl;
        vector<int> vs(n);
        a=n,b=va[0].second;
        for(i=0;i<n && a>0;i++){
            c=bef1[a][b];
            assert(c!=-1);
            for(j=c;j<a;j++){
                vs[j]=b+1;
            }
            a=c;
            b=bef2[a][b];
        }
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}