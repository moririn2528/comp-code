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
#include<random>
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

class BalancedAirplane{
    LL B;
    LL hash(vector<int>& va){
        const LL A=200003,N=487611134617;
        LL s=0;
        for(int i=0;i<va.size();i++){
            s*=A;
            s+=B+va[i]+1e5;
            s%=N;
        }
        return s;
    }
public:
    long long count(LL S, LL R, vector<int> Aprefix){
        int L=Aprefix.size();
        vector<int> A(L);
        int i,j;
        LL a;
        LL s=0;
        for(i=0;i<L;i++){
            A[i] = Aprefix[i];
        }
        LL state = Aprefix[L-1];
        for(i=L;i<R;i++){
            state = (state * 1103515245 + 12345) % (1LL<<31);
            A[i] = state >> (31 - S);
        }
        if(S==1){
            return R*(R+1)/2;
        }
        random_device seed;
        mt19937 rnd(seed());
        B=rnd();
        map<LL,int> m1;
        vector<int> v1(S-1,0);
        m1[hash(v1)]++;
        for(i=0;i<R;i++){
            for(j=0;j<S-1;j++){
                if(A[i]&1<<(j+1))v1[j]++;
                if(A[i]&1)v1[j]--;
            }
            a=hash(v1);
            s+=m1[a];
            m1[a]++;
        }
        return s;
    }
};
