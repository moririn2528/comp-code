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

template<typename T> class Compress{
    //Compress<int> ca({5,1,2,3});
    //ca.id(5) //=3
private:
    vector<int> id_perm;//v1 index -> vec index
public:
    vector<T> vec;
    void init(const vector<T>& v1){
        int n=v1.size();
        int i,j;
        id_perm.assign(n,-1);
        vector<pair<T,int>> va;
        for(i=0;i<n;i++){
            va.push_back({v1[i],i});
        }
        sort(va.begin(),va.end());
        vec.clear();
        for(i=0,j=-1;i<n;i++){
            if(vec.empty() || vec.back()!=va[i].first){
                vec.push_back(va[i].first);
                j++;
            }
            id_perm[va[i].second]=j;
        }
    }

    Compress(const vector<T> v1){
        init(v1);
    }

    vector<int> get_id_perm()const{
        return id_perm;
    }

    int id(const T a){
        auto itr=lower_bound(vec.begin(),vec.end(),a);
        assert(itr!=vec.end());//return -1?
        assert(*itr==a);
        return itr-vec.begin();
    }
};

namespace sol{
    typedef tuple<LL,LL,LL> T;
    LL op(LL a,LL b){return max(a,b);}

    void solve(){
        LL n,m;
        int i,j,k;
        LL a,b,c;
        LL p,q,r;
        LL x,y;
        cin>>n>>m>>x>>y;
        seg_tree<LL> seg(op,-INF,2*m),seg2(op,-INF,2*m);
        vector<seg_tree<LL>> vse(3,seg_tree<LL>(op,-INF,2*m));
        vector<LL> va;
        vector<T> vt;
        for(i=0;i<m;i++){
            cin>>c>>a>>b;
            a--,c--;
            va.push_back(a),va.push_back(b);
            vt.push_back({a,b,c});
        }
        Compress com(va);
        for(i=0;i<m;i++){
            tie(a,b,c)=vt[i];
            a=com.id(a),b=com.id(b);
            vt[i]=T(b,a,c);
        }
        sort(vt.begin(),vt.end());
        for(i=0;i<m;i++){
            tie(b,a,c)=vt[i];
            q=com.vec[a],r=com.vec[b];
            p=(r-q)*x;
            p=max(p,seg2.search(0,a+1)+(r-q)*x);
            p=max(p,seg.search(a,b)+q*(x+y)+r*x);
            p=max(p,vse[c].search(a,b)+r*x);
            if(p<seg2.search(b,b+1))continue;
            seg.set(b,p-r*(2*x+y));
            seg2.set(b,p);
            vse[c].set(b,p-r*x);
        }
        cout<<seg2.search()<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}