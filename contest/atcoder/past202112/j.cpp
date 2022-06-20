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
    vector<vector<char>> grid;
    int tlx=0,tly=0;
    int mx[2]={1,0},my[2]={0,1};
    
    void rotateP(int *m){
        swap(m[0],m[1]);
        m[0]=-m[0];
    }
    void rotateN(int *m){
        swap(m[0],m[1]);
        m[1]=-m[1];
    }

    void pos(int& x,int& y){
        int p=x-tlx,q=y-tly;
        x=p*mx[0]+q*mx[1];
        y=p*my[0]+q*my[1];
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        grid.assign(n,vector<char>(n,0));
        string sa;
        for(i=0;i<m;i++){
            cin>>a;
            if(a==1){
                cin>>b>>c;
                b--,c--;
                pos(b,c);
                grid[b][c]=!grid[b][c];
                continue;
            }
            if(a==2){
                cin>>sa;
                if(sa=="A"){
                    swap(tlx,tly);
                    tly=n-1-tly;
                    rotateN(mx);
                    rotateN(my);
                }else{
                    swap(tlx,tly);
                    tlx=n-1-tlx;
                    rotateP(mx);
                    rotateP(my);
                }
                continue;
            }
            cin>>sa;
            if(sa=="A"){
                tlx=n-1-tlx;
                mx[0]=-mx[0];
                my[0]=-my[0];
            }else{
                tly=n-1-tly;
                mx[1]=-mx[1];
                my[1]=-my[1];
            }
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                a=i,b=j;
                pos(a,b);
                if(grid[a][b])cout<<1;
                else cout<<0;
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