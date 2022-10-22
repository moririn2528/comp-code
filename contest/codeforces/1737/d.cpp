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

    void init(){
        
    }
    typedef tuple<LL,LL,LL> T;

    void dis(vector<int>& v1, vector<vector<int>>& path,int pos){
        queue<int> q1;
        q1.push(pos);
        int i,j,k;
        for(i=0;!q1.empty();i++){
            for(j=q1.size()-1;j>=0;j--){
                int now=q1.front();
                q1.pop();
                if(v1[now]!=-1)continue;
                v1[now]=i;
                for(k=0;k<path[now].size();k++){
                    q1.push(path[now][k]);
                }
            }
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n>>m;
        vector<vector<int>> path(n);
        vector<T> vt;
        for(i=0;i<m;i++){
            cin>>a>>b>>c;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
            vt.push_back(T(a,b,c));
        }
        vector<int> v1(n,-1),v2(n,-1);
        dis(v1,path,0);
        dis(v2,path,n-1);
        LL s=1LL<<60;
        for(i=0;i<m;i++){
            tie(a,b,c)=vt[i];
            s=min(s,min(v1[a]+v2[b]+1,v1[b]+v2[a]+1)*c);
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}