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
const LL INF=1LL<<60;
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

typedef long long int type;
typedef complex<type> C;
template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}

void convex(vector<C>& vp,C pt){
    int a,b,c;
    if(!vp.empty() && vp.back()==pt)return;
    while(vp.size()>=2){
        a=vp.size()-1;
        C ca=vp[a]-vp[a-1],cb=pt-vp[a];
        if(cross_product(ca,cb)>0)break;
        vp.pop_back();
    }
    vp.push_back(pt);
}

vector<C> convex_full(vector<LP>& v){
    sort(v.begin(),v.end());
    vector<C> vs;
    int n=v.size();
    for(int i=0;i<n;i++){
        convex(vs,C(v[i].first,v[i].second));
    }
    return vs;
}

namespace sol{

    LL grad(int i,int j,vector<LL>& v1){
        LL dif=v1[j]-v1[i];
        LL x=j-i;
        assert(x>=0);
        if(dif<0)return -((-dif-1)/x+1);
        return dif/x;
    }

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n;
        vector<LL> v1(n);
        cin>>v1;
        vector<int> vi;
        for(i=0;i<n;i++){
            while(vi.size()>=2){
                a=vi[vi.size()-2];
                b=vi[vi.size()-1];
                if((b-a)*(v1[i]-v1[b])-(i-b)*(v1[b]-v1[a])<=0){
                    vi.pop_back();
                    continue;
                }
                if(grad(a,b,v1)<grad(b,i,v1))break;
                vi.pop_back();
            }
            vi.push_back(i);
        }
        a=-INF;
        
        for(i=0;i+1<vi.size();i++){
            a=vi[i],b=vi[i+1];
            c=grad(a,b,v1);
            for(j=a+1;j<b;j++){
                v1[j]=v1[j-1]+c;
                if(v1[b]-v1[j]==(b-j)*(c+1))c++;
            }
        }
        LL s=0;
        for(i=0;i<n;i++){
            s+=v1[i];
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}