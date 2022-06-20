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
    int n,m;
    const int N=500;
    vector<int> cnt(N),ve;
    vector<vector<int>> grid,vs;

    bool set(int x,int y,int a){
        if(cnt[a]==0)return false;
        grid[x][y]=a;
        cnt[a]--;
        return true;
    }

    bool setx(int pos,int x,int y){
        int i;
        set(x,0,ve[pos]);
        for(i=1;i<y;i++){
            if(!set(x,i,grid[x][i-1]+grid[x-1][i]-grid[x-1][i-1])){
                return false;
            }
        }
        if(!set(x-1,n-x,grid[x-1][0]-grid[x][0]))return false;
        for(i=x-2;i>=0;i--){
            if(!set(i,n-x,grid[i+1][n-x]+grid[i][0]-grid[i+1][0])){
                return false;
            }
        }
        return true;
    }
    bool sety(int pos,int x,int y){
        int i;
        set(0,y,ve[pos]);
        for(i=1;i<x;i++){
            if(!set(i,y,grid[i-1][y]+grid[i][y-1]-grid[i-1][y-1])){
                return false;
            }
        }
        if(!set(n-y,y-1,grid[0][y-1]-grid[0][y]))return false;
        for(i=y-2;i>=0;i--){
            if(!set(n-y,i,grid[n-y][i+1]+grid[0][i]-grid[0][i+1])){
                return false;
            }
        }
        return true;
    }
    void clear(int x,int y){
        int a=grid[x][y];
        if(a==0)return;
        cnt[a]++;
        grid[x][y]=0;
    }
    void clearx(int x,int y){
        int i;
        for(i=0;i<y;i++){
            clear(x,i);
        }
        for(i=x-1;i>=0;i--){
            clear(i,n-x);
        }
    }
    void cleary(int x,int y){
        for(int i=0;i<x;i++){
            clear(i,y);
        }
        for(int i=y-1;i>=0;i--){
            clear(n-y,i);
        }
    }

    void dfs(int pos,int x,int y){
        for(;pos<ve.size() && cnt[ve[pos]]==0;pos++);
        int i;
        int a,b,c;
        if(pos==ve.size()){
            vector<int> v1;
            for(i=0;i<grid.size();i++){
                v1.push_back(grid[i][n-i-1]);
            }
            vs.push_back(v1);
            return;
        }
        if(setx(pos,x,y))dfs(pos,x+1,y);
        clearx(x,y);
        if(sety(pos,x,y))dfs(pos,x,y+1);
        cleary(x,y);
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        while(cin>>n){
            if(n==0)return;
            n--;
            m=(n+1)*n/2;
            vector<int> v1(m);
            cin>>v1;
            cnt.assign(N,0);
            for(i=0;i<m;i++){
                cnt[v1[i]]++;
            }
            ve.clear();
            for(i=N-1;i>=0;i--){
                if(cnt[i])ve.push_back(i);
            }
            grid.assign(n,vector<int>(n,0));
            vs.clear();
            set(0,0,ve[0]);
            dfs(0,1,1);
            sort(vs.begin(),vs.end(),[](vector<int>& v1, vector<int>& v2){
                for(int i=0;i<v1.size();i++){
                    if(v1[i]!=v2[i])return v1[i]<v2[i];
                }
                return false;
            });
            auto eq=[](vector<int>& v1, vector<int>& v2){
                for(int i=0;i<v1.size();i++){
                    if(v1[i]!=v2[i])return false;
                }
                return true;
            };
            for(i=0;i<vs.size();i++){
                if(i>0 && eq(vs[i],vs[i-1]))continue;
                cout<<vs[i]<<endl;
            }
            cout<<"-----"<<endl;
        }
        
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}