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
        int n,m,p;
        int i,j,k;
        LL a,b,c;
        string sa="NS";
        cin>>n>>m>>p;
        vector<LL> v1(n),dis(n,-1);
        vector<vector<int>> path(n);
        string ss(n,'q');
        cin>>v1;
        for(i=0;i<m;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        priority_queue<LP,vector<LP>,greater<LP>> q1;
        q1.push({0,0});
        while(!q1.empty()){
            a=q1.top().first,b=q1.top().second;q1.pop();
            if(dis[b]!=-1)continue;
            dis[b]=a+v1[b];
            for(auto to:path[b]){
                q1.push({a+v1[b],to});
            }
        }
        if(dis[n-1]!=v1[0]+v1[n-1]){
            if(p)p--,ss[0]=sa[0];
            for(auto to:path[0]){
                if(p)p--,ss[to]=sa[0];
            }
            for(i=0;i<n;i++){
                if(ss[i]!='q')continue;
                if(p)p--,ss[i]=sa[0];
                else ss[i]=sa[1];
            }
            cout<<ss<<endl;
            return;
        }
        if(p<2 && n-p<2){
            cout<<"impossible"<<endl;
            return;
        }
        if(p<2){
            p=n-p;
            swap(sa[0],sa[1]);
        }
        ss[0]=ss[n-1]=sa[0];
        p-=2;
        for(i=0;i<n;i++){
            if(ss[i]!='q')continue;
            if(p)p--,ss[i]=sa[0];
            else ss[i]=sa[1];
        }
        cout<<ss<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}