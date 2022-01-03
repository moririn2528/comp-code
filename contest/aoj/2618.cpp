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
    typedef complex<double> C;
    const double eps=1e-9;

    bool xline(C& da){
        int a=(da.real()+eps)/10;
        return abs(da.real()-a*10)<eps;
    }
    
    double dis(C& da,C& db){
        int a,b;
        double d;
        if(abs(da.real()-db.real())<eps)return abs(da-db);
        if(abs(da.imag()-db.imag())<eps)return abs(da-db);
        if(xline(da)!=xline(db))return abs(da-db);
        if(xline(da)){
            a=(da.real()+eps)/10,b=(db.real()+eps)/10;
            if(a==b)return abs(da-db);
            a=(da.imag()+eps)/10,b=(db.imag()+eps)/10;
            if(a!=b)return abs(da-db);
            d=da.imag()-a*10+db.imag()-b*10;
            return abs(da.real()-db.real())+min(d,20-d);
        }else{
            a=(da.imag()+eps)/10,b=(db.imag()+eps)/10;
            if(a==b)return abs(da-db);
            a=(da.real()+eps)/10,b=(db.real()+eps)/10;
            if(a!=b)return abs(da-db);
            d=da.real()-a*10+db.real()-b*10;
            return abs(da.imag()-db.imag())+min(d,20-d);
        }
    }

    double dis(vector<C>& pos,C ca){
        double s=0;
        for(int i=0;i<pos.size();i++){
            s+=dis(pos[i],ca);
        }
        return s;
    }

    double calc(vector<C>& pos){
        int n=pos.size();
        int i,j,k;
        int a,b,c;
        unordered_set<int> s1;
        double s=1e15;
        for(i=0;i<n;i++){
            a=(pos[i].real()+eps)/10;
            s1.insert(a);
            s1.insert(a+10);
        }
        for(int num:s1){
            double z[5]={-2e8,2e8};
            for(i=0;i<100;i++){
                z[2]=(2*z[0]+z[1])/3;
                z[3]=(z[0]+2*z[1])/3;
                if(dis(pos,C(num,z[2]))<dis(pos,C(num,z[3]))){
                    z[1]=z[3];
                }else{
                    z[0]=z[2];
                }
            }
            s=min(s,dis(pos,C(num,z[0])));
        }
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        vector<C> pos(n);
        for(i=0;i<n;i++){
            cin>>a>>b;
            pos[i]=C(a,b);
        }
        double s=calc(pos);
        for(i=0;i<n;i++){
            double p=pos[i].real(),q=pos[i].imag();
            pos[i]=C(q,p);
        }
        s=min(s,calc(pos));
        cout<<fixed<<setprecision(20)<<endl;
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}