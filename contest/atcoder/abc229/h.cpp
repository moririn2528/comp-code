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
    const int N=1e4;
    int n,m;

    int hash(vector<int>& v1){
        int s=0;
        for(int i=n-1;i>=0;i--){
            s*=3;
            s+=v1[i]+1;
        }
        return s;
    }
    vector<int> revhash(int a){
        vector<int> vs(n);
        int i;
        for(i=0;i<n;i++){
            vs[i]=a%3-1;
            a/=3;
        }
        return vs;
    }
    void rev(vector<int>& v1){
        for(auto& num:v1){
            num=-num;
        }
    }
    vector<int> vt(N),deg(N);
    vector<vector<int>> path(N),rpath(N);

    void connect_to(int a,int b){
        deg[a]++;
        path[a].push_back(b);
        rpath[b].push_back(a);
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n;
        m=pow(3,n);
        for(i=0;i<m;i++){
            vector<int> v1=revhash(i);
            for(j=1;j<n;j++){
                vector<int> v2=v1;
                if(v1[j]==1 && v1[j-1]==0){
                    v2[j]=0,v2[j-1]=1;
                    rev(v2);
                    a=hash(v2);
                    connect_to(i,a);
                }
            }
            for(j=0;j<n;j++){
                vector<int> v2=v1;
                if(v1[j]==-1){
                    v2[j]=0;
                    rev(v2);
                    a=hash(v2);
                    connect_to(i,a);
                }
            }
        }
        queue<int> q1;
        for(i=0;i<m;i++){
            if(deg[i]==0)q1.push(i);
        }
        while(!q1.empty()){
            a=q1.front(),q1.pop();
            b=path[a].size()+1;
            vector<char> va(b);
            for(auto to:path[a]){
                if(b<=vt[to])continue;
                va[vt[to]]=1;
            }
            for(i=0;i<b;i++){
                if(!va[i]){
                    vt[a]=i;
                    break;
                }
            }
            for(auto to:rpath[a]){
                deg[to]--;
                if(deg[to]==0)q1.push(to);
            }
        }
        vector<string> grid(n);
        cin>>grid;
        int s=0;
        for(i=0;i<n;i++){
            vector<int> v1(n,0);
            for(j=0;j<n;j++){
                if(grid[j][i]=='W')v1[j]=1;
                if(grid[j][i]=='B')v1[j]=-1;
            }
            a=hash(v1);
            s^=vt[a];
        }
        if(s)cout<<"Takahashi"<<endl;
        else cout<<"Snuke"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}