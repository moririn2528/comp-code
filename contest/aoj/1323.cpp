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
    const double eps=1e-9;

    double area(double a,double b,double c){
        long double s=(a+b+c)/2;
        return sqrt(s*(s-a)*(s-b)*(s-c));
    }

    void fix_angle(double& a){
        while(a<0)a+=2*pi;
        while(a>=2*pi)a-=2*pi;
    }

    void cross_range(vector<DP>& va,DP tb){
        const DP NILL={-10,-10};
        double da,db;
        int i;
        int n=va.size();
        if(n==0){
            va.push_back(tb);
            return;
        }
        for(i=0;i<n;i++){
            DP a=va[i],b=tb;
            da=max(a.first,b.first),db=min(a.second,b.second);
            if(a.first<=a.second && b.first<=b.second){
                if(da<db)va[i]={da,db};
                else va.erase(va.begin()+i),i--,n--;
                continue;
            }
            if(a.second<=a.first && b.second<=b.first){
                va[i]={da,db};
                continue;
            }
            if(a.second<=a.first)swap(a,b);
            if(a.first<=b.second && b.first<=a.second){
                va[i]={a.first,db};
                va.push_back({da,a.second});
                continue;
            }
            if(a.first<b.second)va[i]={a.first,db};
            else if(b.first<a.second)va[i]={da,a.second};
            else va.erase(va.begin()+i),i--,n--;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y,r;
        double da,db,dc,dd;
        double ds,dsa;
        vector<T> v1;
        while(cin>>n>>m){
            if(n==0)return;
            bool flag=true;
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
            ds=0,dsa=0;
            for(i=0;i<n;i++){
                vector<DP> va;
                tie(x,y,r)=v1[i];
                for(j=0;j<n;j++){
                    if(i==j)continue;
                    tie(a,b,c)=v1[j];
                    da=sqrt(pow(a-x,2)+pow(b-y,2));
                    if(2*m<da+c+r || m<c || m<r){
                        flag=false;
                        break;
                    }
                    if(da<=r-c)continue;
                    if(da<=c-r)break;
                    db=m-r,dc=m-c;
                    dd=area(da,db,dc)*2.0/db;
                    dd=asin(dd/da);
                    if(pow(da,2)+pow(db,2)<pow(dc,2))dd=pi-dd;
                    da=atan2(b-y,a-x);
                    db=da-dd,dc=da+dd;
                    fix_angle(db),fix_angle(dc);
                    cross_range(va,{db,dc});
                    if(va.empty())break;
                }
                if(!flag)break;
                if(j<n)continue;
                if(va.empty())va.push_back({0,2*pi});
                for(j=0;j<va.size();j++){
                    DP& d=va[j];
                    da=d.second-d.first;
                    if(da<0)da+=2*pi;
                    ds+=(2*m-r)*da;
                    dsa+=da;
                }
            }
            if(!flag || dsa<eps){
                cout<<0<<endl;
                continue;
            }
            ds+=(2*pi-dsa)*m;
            cout<<ds<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout<<fixed<<setprecision(10);
    sol::solve();
}