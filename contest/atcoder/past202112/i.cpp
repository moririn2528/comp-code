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
        n--;
        const int start_pos=2*m+1,end_pos=2*m+2;
        vector<vector<LP>> path(2*m+5);
        vector<LP> vp;
        for(i=0;i<m;i++){
            cin>>a>>b>>c;
            a--,b--;
            vp.push_back({a,2*i});
            vp.push_back({b,2*i+1});
            path[2*i].push_back({2*i+1,c});
            path[2*i+1].push_back({2*i,c});
        }
        vp.push_back({0,start_pos});
        vp.push_back({n,end_pos});
        sort(vp.begin(),vp.end());
        for(i=0;i+1<vp.size();i++){
            a=vp[i].second,b=vp[i+1].second;
            c=vp[i+1].first-vp[i].first;
            path[a].push_back({b,c});
            path[b].push_back({a,c});
        }
        priority_queue<LP,vector<LP>,greater<LP>> q1;
        q1.push({0,start_pos});
        vector<LL> dis(2*m+5,-1);
        while(!q1.empty()){
            a=q1.top().first,b=q1.top().second;q1.pop();
            if(dis[b]!=-1)continue;
            dis[b]=a;
            for(auto node:path[b]){
                LL to=node.first,d=node.second+a;
                q1.push({d,to});
            }
        }
        cout<<dis[end_pos]<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}