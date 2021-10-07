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
#include<random>
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

random_device seed;
mt19937 rnd(seed);

vector<vector<int>> create_tree(int n){
    vector<vector<int>> path(n);
    vector<int> v1(n);
    iota(v1.begin(),v1.end(),0);
    shuffle(v1.begin(),v1.end(),rnd);
    int i;
    int a,b;
    for(i=1;i<n;i++){
        a=i,b=rnd()&i;
        a=v1[a],b=v1[b];
        path[a].push_back(b);
        path[b].push_back(a);
    }
    return path;
}

vector<vector<int>> create_connect_graph(int n,int m){
    const int N=1000;
    assert(n-1<=m);
    vector<vector<int>> path=create_tree(n);
    int a,b;
    int i,j;
    if(n<N){
        vector<vector<char>> used(N,vector<char>(N));
        for(i=0;i<n;i++){
            used[i][i]=1;
            for(auto num:path[i])used[i][num]=1;
        }
        vector<P> v1;
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                if(!used[i][j])v1.push_back({i,j});
            }
        }
        shuffle(v1.begin(),v1.end(),rnd);
        assert(n-1+v1.size()<=m);
        for(i=0;i<m-(n-1);i++){
            a=v1[i].first,b=v1[i].second;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        return path;
    }
    unordered_set<LL> s1;
    for(i=0;i<n;i++){
        for(auto num:path[i]){
            if(i<num)s1.insert((LL)i*n+num);
        }
    }
    for(i=n-1;i<m;){
        a=rnd()%n,b=rnd()%n;
        if(a==b)continue;
        if(a>b)swap(a,b);
        if(s1.find((LL)a*n+b)!=s1.end())continue;
        i++;
        s1.insert((LL)a*n+b);
        path[a].push_back(b);
        path[b].push_back(a);
    }
    return path;
}

//mt19937 rnd(seed)
//vector<vector<int>> create_tree(int n)
//vector<vector<int>> create_connect_graph(int n,int m)

namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        
    }
}

int main(){
    sol::solve();
}