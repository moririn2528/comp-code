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

    int pos(vector<string>& grid,vector<vector<int>>& vs,int i,int j){
        if(i<0 || j<0 || n<=i || m<=j)return -1;
        char ca=grid[i][j];
        if('1'<=ca && ca<='5')return ca-'1';
        return vs[i][j];
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<string> grid(n);
        vector<vector<int>> vs(n,vector<int>(m,-1));
        cin>>grid;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(grid[i][j]!='.'){
                    cout<<grid[i][j];
                    continue;
                }
                vector<char> used(5);
                for(a=-1;a<=1;a++){
                    for(b=-1;b<=1;b++){
                        if((a+b+2)%2==0)continue;
                        c=pos(grid,vs,i+a,j+b);
                        if(c!=-1)used[c]=1;
                    }
                }
                for(k=0;k<5;k++){
                    if(!used[k]){
                        cout<<k+1;
                        vs[i][j]=k;
                        break;
                    }
                }
            }
            cout<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}