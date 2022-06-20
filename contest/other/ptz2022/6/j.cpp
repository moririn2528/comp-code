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
    template<typename T> T cross_product(complex<T> ca,complex<T> cb){
        return (conj(ca)*cb).imag();
    }

    template<typename T> T inner_product(complex<T> ca,complex<T> cb){
        return (conj(ca)*cb).real();
    }

    void init(){
        
    }

    typedef long double D;
    typedef complex<D> C;
    const D eps=1e-15;
    const D pi=acosl(-1);
    struct Cir{
        C p;
        D r;
    };
    

    bool contain(Cir ca,Cir cb){
        if(ca.r<cb.r)return false;
        return (abs(ca.p-cb.p) < ca.r-cb.r+eps);
    }

    D arg_tri(C p1,C p2,C p3){
        D a=abs(p1-p2),b=abs(p2-p3),c=abs(p3-p1);
        D co=(a*a+b*b-c*c)/(2*a*b);
        return acosl(co);
    }
    D arg_tri(Cir c1,Cir c2,Cir c3){
        return arg_tri(c1.p,c2.p,c3.p);
    }
    D area_tri(C p1,C p2,C p3){
        D arg=arg_tri(p1,p2,p3);
        D l=abs(p1-p2),h=abs(p2-p3)*sinl(arg);
        return l*h/2;
    }
    D arg_trape(Cir c1,Cir c2){// in c1 arg
        D h=abs(c1.p-c2.p);
        D l=c1.r-c2.r;
        return acosl(l/h);
    }
    D area_trape(Cir c1,Cir c2){
        D arg=arg_trape(c1,c2);
        D h=abs(c1.p-c2.p)*sinl(arg);
        return (c1.r+c2.r)*h/2;
    }
    D area(Cir ca,D arg){
        D r=ca.r;
        return r*r*arg/2;
    }

    D area2(Cir ca,Cir cb){
        D arg=arg_trape(ca,cb);
        D s=2*area_trape(ca,cb);
        s+=area(ca,2*(pi-arg));
        s+=area(cb,2*arg);
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int x,y,z;
        int a,b,r;
        Cir c[3];
        for(i=0;i<3;i++){
            cin>>a>>b>>r;
            c[i].p=C(a,b);
            c[i].r=r;
        }
        cout<<fixed<<setprecision(10);
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(i==j)continue;
                if(!contain(c[i],c[j]))break;
            }
            if(j==3){
                cout<<area(c[i],2*pi)<<endl;
                return;
            }
        }
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(i==j)continue;
                k=3-i-j;
                if(contain(c[i],c[j])){
                    cout<<area2(c[i],c[k])<<endl;
                    return;
                }
            }
        }
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(i==j)continue;
                k=3-i-j;
                if(c[i].r+eps<c[j].r)continue;
                if(c[i].r+eps<c[k].r)continue;
                if(inner_product(c[j].p-c[i].p,c[k].p-c[i].p)<-eps)continue;
                D arg=arg_tri(c[j].p,c[i].p,c[k].p);
                if(arg_trape(c[i],c[j])+arg>arg_trape(c[i],c[k])+eps)continue;
                arg=arg_tri(c[j].p,c[k].p,c[i].p);
                if(arg_trape(c[k],c[j])+arg>arg_trape(c[k],c[i])+eps)continue;
                cout<<area2(c[i],c[k])<<endl;
                return;
            }
        }

        
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(i==j)continue;
                k=3-i-j;
                D arg=arg_tri(c[j],c[i],c[k]);
                arg-=arg_trape(c[i],c[j]);
                arg-=arg_trape(c[i],c[k]);
                if(arg<eps)continue;
                D s=2*(area_trape(c[i],c[j])+area_trape(c[i],c[k]));
                arg=2*(pi-arg_trape(c[i],c[j])-arg_trape(c[i],c[k]));
                s+=area(c[i],arg);
                s+=area(c[j],2*(pi-arg_trape(c[j],c[i])));
                s+=area(c[k],2*(pi-arg_trape(c[k],c[i])));
                cout<<s<<endl;
                return;
            }
        }

        D s=area_tri(c[0].p,c[1].p,c[2].p);
        for(i=0;i<3;i++){
            j=(i+1)%3;
            s+=area_trape(c[i],c[j]);
        }
        for(i=0;i<3;i++){
            j=(i+1)%3,k=(i+2)%3;
            D arg=2*pi;
            arg-=arg_tri(c[j].p,c[i].p,c[k].p);
            arg-=arg_trape(c[i],c[j]);
            arg-=arg_trape(c[i],c[k]);
            s+=area(c[i],arg);
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}