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
        LL n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n>>m;
        vector<LP> vp,v1;
        set<LP> s1;
        for(i=0;i<n;i++){
            cin>>a>>b;
            vp.push_back({a,b});
            v1.push_back({b-m-1,i});
            v1.push_back({b+m+1,i});
            v1.push_back({b,i});
        }
        sort(v1.begin(),v1.end());
        auto dis_check=[&](int p,int q){
            LL x=vp[p].first-vp[q].first;
            LL y=vp[p].second-vp[q].second;
            return x*x+y*y<=m*m;
        };
        vector<P> vs;
        for(auto node:v1){
            a=node.second;
            b=vp[a].first;
            if(node.first<vp[a].second){
                s1.insert({b,a});
                continue;
            }
            if(vp[a].second<node.first){
                s1.erase({b,a});
                continue;
            }
            for(auto itr=s1.lower_bound({b-m,-1});itr!=s1.end();itr++){
                c=itr->second;
                if(b+m<vp[c].first)break;
                if(a<c && dis_check(a,c))vs.push_back({a,c});
            }
        }
        cout<<vs.size()<<endl;
        sort(vs.begin(),vs.end());
        for(auto node:vs){
            node.first++,node.second++;
            cout<<node<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}