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
    typedef tuple<int,int,int> T;

    void solve(){
        int n,m;
        int st,en;
        int i,j,k;
        int a,b,c;
        char ca;
        while(cin>>n>>m>>st>>en){
            if(n==0)return;
            vector<vector<int>> v1(n,vector<int>(n,0));
            vector<vector<vector<char>>> used(n,vector<vector<char>>(n,vector<char>(10)));
            //()[]a+*
            st--,en--;
            queue<T> q1;
            for(i=0;i<m;i++){
                cin>>a>>b>>ca;
                a--,b--;
                if(ca=='(')c=1;
                if(ca==')')c=2;
                if(ca=='[')c=4;
                if(ca==']')c=8;
                if(ca=='a')c=16;
                if(ca=='+')c=32;
                if(ca=='*')c=64;
                v1[a][b]|=c;
                if(ca=='a'){
                    q1.push({a,b,2});
                }
            }
            while(!q1.empty()){
                tie(a,b,c)=q1.front();q1.pop();
                if(used[a][b][c])continue;
                used[a][b][c]=1;
                for(i=0;i<n;i++){
                    if(c==0){
                        if(v1[i][a]&1)q1.push({i,b,5});
                        if(v1[i][a]&4)q1.push({i,b,6});
                        if(used[b][i][3])q1.push({a,i,0});
                    }
                    if(c==1){
                        if(v1[i][a]&32)q1.push({i,b,3});
                        if(used[b][i][4])q1.push({a,i,1});
                    }
                    if(c==2 && (v1[i][a]&64))q1.push({i,b,4});
                    if(c==3 && (used[i][a][0]))q1.push({i,b,0});
                    if(c==4 && (used[i][a][1]))q1.push({i,b,1});
                    if(c==5 && (v1[b][i]&2))q1.push({a,i,2});
                    if(c==6 && (v1[b][i]&8))q1.push({a,i,2});
                }
                if(c==1)q1.push({a,b,0});
                if(c==2)q1.push({a,b,1});
            }
            if(used[st][en][0])cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}