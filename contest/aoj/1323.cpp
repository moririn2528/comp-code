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
    typedef pair<double,double> DP;
    const double pi=acos(-1);

    double area(double a,double b,double c){
        double s=(a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    void fix_angle(double& a){
        while(a<0)a+=2*pi;
        while(a>=pi)a-=2*pi;
    }

    DP cross_range(DP a,DP b){
        double a1=a.first,a2=a.second;
        double b1=b.first,b2=b.second;
        if(a1<a2 && b1<b2)
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y,r;
        double da,db,dc;
        double dl=0,dr=0;
        double ds=0;
        vector<T> v1;
        while(cin>>n>>m){
            if(n==0)return;
            v1.clear();
            for(i=0;i<n;i++){
                cin>>x>>y>>a;
                v1.push_back({x,y,a});
            }
            if(n==1){
                if(m<a)cout<<0<<endl;
                else cout<<2*pi*(2*m-a)<<endl;
                continue;
            }
            ds=0;
            for(i=0;i<n;i++){
                dl=0,dr=2*pi;
                tie(x,y,r)=v1[i];
                for(j=0;j<n;j++){
                    if(i==j)continue;
                    tie(a,b,c)=v1[j];
                    da=sqrt(pow(a-x,2)+pow(b-y,2));
                    if(m<da+c+r)break;
                    db=2*m-c,dc=2*m-r;
                    db=area(da,db,dc)*2/db;
                    dc=cos(db/da);
                    da=atan2(b-y,a-x);
                    if(a-x<0)da+=pi;
                    db=da-dc,dc=da+dc;
                    fix_angle(da),fix_angle(db);
                    if(db<da)swap(da,db);
                    assert(db-da!=pi);
                    if(db-da>pi)swap(da,db);
                }
                if(j<n)break;
            }
            if(i<n){
                cout<<0<<endl;
                continue;
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<fixed<<setprecision(10);
    sol::solve();
}