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
    const int N=2222,M=3;
    vector<vector<vector<char>>> win(M,vector<vector<char>>(N,vector<char>(N)));
    vector<vector<vector<int>>> cnt(M,vector<vector<int>>(N,vector<int>(N)));
    typedef tuple<int,int,int> T;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y,z;
        cin>>n;
        auto inN=[](int x){return 0<=x && x<N;};
        for(i=0;i<M;i++){
            for(j=0;j<N;j++){
                for(k=0;k<N;k++){
                    x=j,y=k;
                    if(i==2)y++;
                    if(inN(x-1) && inN(y))cnt[i][j][k]++;
                    if(inN(x+1) && inN(y-1))cnt[i][j][k]++;
                    if(inN(x) && inN(y-1))cnt[i][j][k]++;
                }
            }
        }
        queue<T> q1;
        for(i=0;i<M;i++){
            q1.push({i,0,0});
        }
        auto push=[&](int f,int g,int h){
            if(!inN(g) || !inN(h))return;
            cnt[f][g][h]--;
            if(cnt[f][g][h]==0)q1.push({f,g,h});
        };
        while(!q1.empty()){
            tie(a,b,c)=q1.front();q1.pop();
            x=(a+1)%M,y=b,z=c;
            if(a==2)z++;
            if(b>0 || c>0){
                if(inN(y-1) && inN(z) && !win[x][y-1][z])win[a][b][c]=1;
                if(inN(y) && inN(z-1) && !win[x][y][z-1])win[a][b][c]=1;
                if(inN(y+1) && inN(z-1) && !win[x][y+1][z-1])win[a][b][c]=1;
            }
            x=(a+M-1)%M,y=b,z=c;
            if(a==0)z--;
            push(x,y+1,z),push(x,y,z+1),push(x,y-1,z+1);
        }
        if(win[0][0][n])cout<<"Alice"<<endl;
        else cout<<"Bob"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}