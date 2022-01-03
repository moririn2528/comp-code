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

template<typename T> class Compress{
    //Compress<int> ca({5,1,2,3});
    //ca.id(5) //=3
private:
    vector<T> vec;
    vector<int> id_perm;//v1 index -> vec index
public:
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

    void init(){
        
    }

    vector<P> input(int n){
        int i;
        vector<int> v1(n);
        vector<int> v2(n);
        vector<P> vs;
        for(i=0;i<n;i++){
            scanf("%d",&v1[i]);
        }
        for(i=0;i<n;i++){
            scanf("%d",&v2[i]);
        }
        for(i=0;i<n;i++){
            if(i%2)vs.push_back({v2[i],v1[i]});
            else vs.push_back({v1[i],v2[i]});
        }
        return vs;
    }

    bool check(vector<P> v1,vector<P> v2){
        sort(v1.begin(),v1.end());
        sort(v2.begin(),v2.end());
        int n=v1.size();
        for(int i=0;i<n;i++){
            if(v1[i].first!=v2[i].first)return false;
            if(v1[i].second!=v2[i].second)return false;
        }
        return true;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        scanf("%d",&n); 
        vector<P> v1=input(n);
        vector<P> v2=input(n);
        vector<vector<int>> v3(n);
        Compress<P> ca(v2);
        for(i=0;i<n;i++){
            a=ca.id(v2[i]);
            v3[a].push_back(i);
        }
        if(!check(v1,v2)){
            printf("-1\n");
            return;
        }
        vector<int> va(n);
        for(i=n-1;i>=0;i--){
            a=ca.id(v1[i]);
            assert(!v3[a].empty());
            va[i]=v3[a].back();
            v3[a].pop_back();
        }
        bit<int> bt(n);
        LL s=0;
        for(i=0;i<n;i++){
            s+=i-bt.search(va[i]);
            bt.set(va[i],1);
        }
        printf("%lld\n",s);
    }
}

int main(){
    int n,i;
    sol::init();
    scanf("%d",&n);
    for(i=0;i<n;i++){
        sol::solve();
    }
}