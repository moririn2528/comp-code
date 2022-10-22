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
#include<random>
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

    vector<int> calc(int n){
        const int N=20;
        int m;
        int i,j,k;
        for(m=0;(1<<m)<n;m++);
        vector<int> vn({-1});
        if(n==(1<<m)){
            return vn;
        }
        vector<int> vs;
        for(;n%2==0;n/=2){
            vs.push_back((1<<N)-1);
        }
        int a,b,c;
        b=0;
        for(i=N-1;i>=2;i--){
            a=(1<<i)-1;
            if()
        }
        return vs;
    }

    int check(vector<int> v1){
        int i;
        int a,b,c;
        map<int,int> m1;
        m1[(1<<20)-1]=1;
        for(i=0;i<v1.size();i++){
            vector<P> va;
            for(auto itr:m1){
                va.push_back(P(itr.first,itr.second));
            }
            for(auto p:va){
                a=p.first&v1[i];
                m1[a]+=p.second;
            }
        }
        return m1[0];
    }

    void test(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        mt19937 rnd(234);
        a=2e5;
        for(i=0;i<n;i++){
            b=rnd()%a+1;
            vector<int> res=calc(b);
            if(res[0]==-1)continue;
            if(check(res)!=b){
                cout<<b<<" "<<check(res)<<endl;
                cout<<res<<endl;
            }
        }
    }
    
    void solve(){
        int n;
        cin>>n;
        vector<int> res=calc(n);
        cout<<res.size()<<endl;
        cout<<res<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    //sol::test();
    sol::solve();
}