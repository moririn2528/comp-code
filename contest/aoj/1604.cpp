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

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa;
        while(cin>>n){
            if(n==0)return;
            cin>>sa;
            vector<int> v1(10);
            vector<int> deg(10);
            b=-1;
            for(i=0;i<n;i++){
                if(sa[i]=='u'){
                    b=-1;
                    continue;
                }
                a=sa[i]-'0';
                if(b!=-1)v1[b]|=1<<a;
                b=a;
            }
            for(i=0;i<10;i++){
                for(j=0;j<10;j++){
                    if(v1[i]&1<<j)deg[j]++;
                }
            }
            queue<int> q1;
            for(i=0;i<10;i++){
                if(deg[i]==0)q1.push(i);
            }
            for(i=0;!q1.empty();i++){
                a=q1.front(),q1.pop();
                for(j=0;j<10;j++){
                    if(v1[a]&1<<j){
                        deg[j]--;
                        if(deg[j]==0)q1.push(j);
                    }
                }
            }
            if(i==10)cout<<"SAFE"<<endl;
            else cout<<"UNSAFE"<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}