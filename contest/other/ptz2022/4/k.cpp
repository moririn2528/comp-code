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
    const double eps=1e-7;
    typedef pair<double,double> DP;

    double dis(DP a,DP b){
        return sqrtl(powl(b.first-a.first,2)+powl(b.second-a.second,2));
    }

    bool equal(double a,double b){
        return abs(a-b)<eps;
    }

    DP check(DP a,DP b,DP to,double dl){
        DP mid=a,from=a;
        int i;
        double d;
        for(i=0;i<100;i++){
            mid=DP((a.first+b.first)/2,(a.second+b.second)/2);
            d=dis(from,mid)+dis(mid,to);
            if(equal(d,dl))return mid;
            if(d<dl)a=mid;
            else b=mid;
        }
        return a;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        double dl,da,db;
        cin>>n>>m;
        cin>>dl;
        a=0;
        vector<DP> poss;
        poss.push_back(DP(0,0));
        for(i=0;i<m;i++){
            if(equal(dis(poss.back(),DP(n,m)),dl)){
                break;
            }
            b=n-a;
            if(dl<n+dis(DP(b,i),DP(n,m))+eps){
                poss.push_back(check(DP(a,i),DP(b,i),DP(n,m),dl));
                break;
            }
            dl-=n;
            poss.push_back(DP(b,i));
            if(dl<1+dis(DP(b,i+1),DP(n,m))+eps){
                poss.push_back(check(DP(b,i),DP(b,i+1),DP(n,m),dl));
                break;
            }
            dl-=1;
            poss.push_back(DP(b,i+1));
            a=b;
        }
        assert(i<m);
        poss.push_back(DP(n,m));
        cout<<poss.size()<<endl;
        cout<<fixed<<setprecision(10);
        for(auto pos:poss){
            cout<<pos.first<<" "<<pos.second<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}