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
    const int N=26;
    
    vector<int> create_used(string sa){
        vector<int> vs(N);
        for(auto ca:sa){
            vs[ca-'a']=1;
        }
        return vs;
    }

    void check(vector<vector<int>>& v1,string sa,string sb){
        vector<int> va=create_used(sa),vb=create_used(sb);
        int i,j,k;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(va[i] && vb[j])v1[i][j]=1;
            }
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        vector<vector<int>> v1(N,vector<int>(N));
        vector<vector<int>> v2(N,vector<int>(N));
        string sa,sb;
        cin>>n;
        cin>>sa>>sb;
        check(v1,sa,sb);
        for(i=0;i<n;i++){
            cin>>sa>>sb;
            check(v2,sa,sb);
        }
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(v1[i][j] && !v2[i][j]){
                    cout<<"Yes"<<endl;
                    cout<<char('a'+i)<<char('a'+j)<<endl;
                    return;
                }
            }
        }
        cout<<"No"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}