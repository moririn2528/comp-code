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
typedef pair<LL,int> LP;
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

namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<int> v1,v2;
        int x=n,y=m;
        for(i=0;i<n;i++){
            cin>>a;
            v1.push_back(a);
            if(x==n && a!=0)x=i;
        }
        for(i=0;i<m;i++){
            cin>>a;
            v2.push_back(a);
            if(y==m && a!=0)y=i;
        }
        v1.push_back(INF);
        v2.push_back(INF);
        a=0,b=0;
        for(i=1;i<=n+m;i++){
            if(v1[x]==i){
                a++;
                for(x++;x<n && v1[x]==0;x++);
                continue;
            }
            if(v2[y]==i){
                b++;
                for(y++;y<m && v2[y]==0;y++);
                continue;
            }
            if((v1[x]<v2[y] && a<x) || b==y)v1[a]=i,a++;
            else v2[b]=i,b++;
        }
        v1.pop_back();
        v2.pop_back();
        array_show(v1);
        array_show(v2);
    }
}

int main(){
    sol::solve();
}