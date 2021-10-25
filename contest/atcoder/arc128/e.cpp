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
        os<<v1[i]+1;
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
    const int N=2e5+5;

    void solve(){
        int n,m,mm;
        int i,j,k,l;
        int a,b,c;
        cin>>n>>m;
        map<int,set<int>> m1;
        set<int> s1;
        vector<int> v2(n);
        int t=0,su=0;
        for(i=0;i<n;i++){
            cin>>a;
            t=max(t,a);
            m1[a].insert(i);
            v2[i]=a;
            su+=a;
            s1.insert(i);
        }
        int x=(su-1)/m+1,y=(su-1)%m+1;
        if(x<t || y<m1[x].size()){
            cout<<-1<<endl;
            return;
        }
        vector<int> vs(su,-1);
        mm=m;
        for(i=0,l=0;i<su;i++){
            if(mm<=i)s1.insert(vs[i-mm]);
            if(vs[i]!=-1)continue;
            if(i)y--;
            if(y==0)x--,y=m;
            assert(m1[x].size()<=y);
            if(m1[x].size()==y){
                for(j=0;j<y;j++){
                    auto itr=m1[x].begin();
                    a=*itr;
                    m1[x].erase(itr);
                    v2[a]=0;
                    for(k=i+j;k<su;k+=mm)vs[k]=a;
                }
                m-=y;
                y=1;
                continue;
            }
            auto itr=s1.begin();
            while(v2[*itr]==0){
                s1.erase(itr);
                itr=s1.begin();
            }
            a=*itr;
            vs[i]=a;
            m1[v2[a]].erase(a);
            v2[a]--;
            m1[v2[a]].insert(a);
            s1.erase(itr);
        }
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}