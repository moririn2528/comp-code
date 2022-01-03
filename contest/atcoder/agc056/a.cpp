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

    void output(vector<vector<char>>& grid){
        int n=grid.size();
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(grid[i][j])cout<<"#";
                else cout<<".";
            }
            cout<<endl;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        vector<vector<char>> v1(n,vector<char>(n));
        auto grid=[&](int x,int y){
            for(int p=0;p<3;p++){
                v1[x][(y+p)%n]=1;
            }
        };
        if(n%3==0){
            for(i=0;i<n;i++){
                grid(i,3*i);
            }
            output(v1);
            return;
        }
        for(i=n%3,k=0;i+2<n;i+=3){
            grid(k++,i);
        }
        for(i=0;i+2<n;i+=3){
            grid(k++,i);
        }
        grid(k++,n-1);
        grid(k++,n-2);
        for(i=3-n%3;i+2<n;i+=3){
            grid(k++,i);
        }
        output(v1);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}