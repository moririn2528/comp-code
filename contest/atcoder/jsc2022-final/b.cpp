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
#include<atcoder/all>
using namespace std;
using namespace atcoder;
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

namespace sol{

    LP op(LP a,LP b){return max(a,b);}
    LP e(){return LP(-INF,-1);}

    void solve(){
        LL n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n;
        vector<LL> v1(n);
        cin>>v1;
        segtree<LP,op,e> seg(2*n);
        set<int> s1;
        LL x,y,z;
        x=v1[0],z=v1[0];
        s1.insert(0);
        for(i=0;i<n;i++){
            seg.set(i,LP(v1[i],i));
            seg.set(n+i,LP(v1[i],n+i));
        }
        vector<char> va(n);
        va[n-1]=1;
        for(i=n-2;i>=0 && va[i+1];i--){
            if(v1[i]<=v1[i+1])va[i]=1;
        }
        for(i=1;i<n;i++){
            if(z<v1[i]){
                z=v1[i];
                s1.insert(i);
            }
            x+=z;
        }
        LL s=x;
        if(!va[0])s+=n;
        for(i=0;i+1<n;i++){
            s1.erase(i);
            if(s1.empty())a=n+i;
            else a=*(s1.lower_bound(i));
            x-=v1[i]*(a-i);
            while(i+1<a){
                LP p=seg.prod(i+1,a);
                x+=p.first*(a-p.second);
                a=p.second;
                s1.insert(a);
            }
            assert(!s1.empty());
            auto itr=s1.end();
            itr--;
            a=*itr;
            if(n<=a)a-=n;
            x+=max(v1[a],v1[i]);
            if(v1[a]<v1[i])s1.insert(n+i);
            y=x+i+1;
            if(!va[i+1])y+=n;
            s=min(s,y);
        }
        for(i=0;i<n;i++){
            s-=v1[i];
        }
        cout<<s<<endl;
        
    }
}

int main(){
    sol::solve();
}