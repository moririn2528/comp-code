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

template<typename T> class bit{
private:
    vector<T> bit_vec;
    int bit_N=20;

    T bit_comp(T a,T b){
        return a+b;
    }

public:

    bit(int n){
        for(bit_N=0;bit_N<30;bit_N++){
            if(n<(1<<bit_N))break;
        }
        bit_vec.assign((1<<bit_N),0);
    }

    void set(int pos,T x){
        bit_vec[pos]=bit_comp(bit_vec[pos],x);
        for(int i=0;i<bit_N;i++){
            if(pos&(1<<i))continue;
            pos|=(1<<i);
            bit_vec[pos]=bit_comp(bit_vec[pos],x);
        }
    }

    T search(int pos){
        T s=bit_vec[pos];
        for(int i=0;pos>=(1<<i);i++){
            if(pos&(1<<i))continue;
            pos-=(1<<i);
            s=bit_comp(s,bit_vec[pos]);
        }
        return s;
    }
};

template <typename T> class seg_tree{
    //monoid
private:
    function<T(T,T)> func;
    T e;
    int N,n=-1;
    vector<T> seg;

    void init(){
        assert(n>=0);
        int i;
        for(i=0;(1<<i)<n;i++);
        N=(1<<i)-1;
        seg.assign(2*(N+1),e);
    }

    void init_reload(){
        for(int i=N-1;i>=0;i--){
            seg[i]=func(seg[2*i+1],seg[2*i+2]);
        }
    }
    
    void update(int pos){
        T a=func(seg[pos*2+1],seg[pos*2+2]);
        if(seg[pos]==a)return;
        seg[pos]=a;
        if(pos==0)return;
        update((pos-1)/2);
    }

public:
    seg_tree(function<T(T,T)> _func,T _e,int _n):func(_func),e(_e),n(_n){
        init();
    }
    seg_tree(function<T(T,T)> _func,T _e,vector<T> vec):func(_func),e(_e){
        n=vec.size();
        init();
        for(int i=0;i<n;i++){
            seg[N+i]=vec[i];
        }
        init_reload();
    }
    seg_tree(function<T(T,T)> _func,T _e,int _n,T a):func(_func),e(_e),n(_n){
        init(e);
        for(int i=0;i<n;i++){
            seg[N+i]=a;
        }
        init_reload();
    }

    int size()const{
        return n;
    }

    void set(int pos,T a){
        assert(pos>=0 && pos<=N);
        pos+=N;
        seg[pos]=a;
        update((pos-1)/2);
    }

    T get(const int pos)const{
        return seg[N+pos];
    }

    T search(int a,int b,int l,int r,int x){//[a,b) search
        if(a<=l && r<=b)return seg[x];
        int m=(l+r)/2;
        if(b<=m)return search(a,b,l,m,2*x+1);
        if(m<=a)return search(a,b,m,r,2*x+2);
        return func(search(a,m,l,m,2*x+1),search(m,b,m,r,2*x+2));
    }
    T search(int a,int b){
        assert(a<b);
        return search(a,b,0,N+1,0);
    }
    T search(){
        return search(0,size());
    }

    int max_right(function<bool(T)>& g,int pos,int l,int r,int x,T& y){
        //suppose that S is return value, g(func(pos,..,S-1))=true,g(func(pos,..,S))=false
        if(pos<=l && g(func(y,seg[x]))){
            y=func(y,seg[x]);
            return r;
        }
        if(l+1==r)return l;
        int m=(l+r)/2;
        if(pos<m){
            int s=max_right(g,pos,l,m,2*x+1,y);
            if(s<m)return s;
        }
        return max_right(g,pos,m,r,2*x+2,y);
    }
    int max_right(function<bool(T)> g,int pos){
        T y=e;
        int s=max_right(g,pos,0,N+1,0,y);
        return min(s,n);
    }

    int min_left(function<bool(T)>& g,int pos,int l,int r,int x,T& y){
        //suppose that S is return value, g(func(S,..,pos-1))=true,g(func(S-1,..,pos-1))=false
        int s;
        if(r<=pos && g(func(seg[x],y))){
            y=func(seg[x],y);
            return l;
        }
        if(l+1==r)return r;
        int m=(l+r)/2;
        if(m<pos){
            s=min_left(g,pos,m,r,2*x+2,y);
            if(m<s)return s;
        }
        return min_left(g,pos,l,m,2*x+1,y);
    }
    int min_left(function<bool(T)> g,int pos){
        assert(pos>=0);
        if(pos==0)return 0;
        T y=e;
        return min_left(g,pos,0,N+1,0,y);
    }
};

namespace sol{

    void solve(){
        LL n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n>>m;
        vector<LL> v1(n),v2(n),vs(n);
        cin>>v1;
        bit<LL> bt(n),bs(n);
        seg_tree<P> seg([](P a,P b){
            if(a.first<b.first)return a;
            else return b;
        },{INF,0},n);
        for(i=0;i<n;i++){
            v1[i]--;
            m-=i-bt.search(v1[i]);
            bt.set(v1[i],1);
            v2[v1[i]]=i;
        }
        m=-m;
        for(i=0;i<n && 0<m;i++){
            a=v2[i]-bs.search(v2[i]);
            if(m<a)break;
            m-=a;
            bs.set(v2[i],1);
            vs[i]=i;
        }
        for(j=0,k=i;j<n;j++){
            if(v1[j]<i)continue;
            vs[k++]=v1[j];
        }
        for(i=0;i<n;i++){
            seg.set(i,{vs[i],i});
        }
        for(i=0;m>0 && i<n;i++){
            P pa=seg.search(i,i+m+1);
            m-=pa.second-i;
            for(j=pa.second-1;j>=i;j--){
                swap(vs[j],vs[j+1]);
            }
            for(j=i;j<=pa.second;j++){
                seg.set(j,{vs[j],j});
            }
        }
        for(i=0;i<vs.size();i++){
            cout<<vs[i]+1<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}