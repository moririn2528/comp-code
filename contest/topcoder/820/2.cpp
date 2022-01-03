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

class LogarithmCircuit{
    typedef tuple<int,int,int> T;
    vector<T> vt;
    const int OR=47, AND=48, XOR=49, NAND=50;
public:

    int create(vector<int>& v1,int N){
        vector<int> v2=v1;
        int i;
        int a;
        while(v2.size()>1){
            vector<int> va;
            for(i=0;2*i+1<v2.size();i++){
                a=vt.size()+N;
                vt.push_back(T(OR,v2[2*i],v2[2*i+1]));
                va.push_back(a);
            }
            if(2*i<v2.size())va.push_back(v2[2*i]);
            v2=va;
        }
        return v2[0];
    }

    vector<int> construct(int N){
        int i,j;
        int a,b,c;
        vector<int> v1(N);
        iota(v1.begin(),v1.end(),0);
        vt.clear();
        vector<int> v2=v1;
        b=1;
        while(v2.size()>1){
            b*=2;
            vector<int> va;
            for(i=0;2*i+1<v2.size();i++){
                a=vt.size()+N;
                vt.push_back(T(OR,v2[2*i],v2[2*i+1]));
                va.push_back(a);
            }
            if(2*i<v2.size())va.push_back(v2[2*i]);
            v2=va;
            for(i=0;i<N;i++){
                j=(i+b-1)/b;
                if(v2.size()<=j)break;
                a=vt.size()+N;
                vt.push_back(T(OR,v2[j],v1[i]));
                v1[i]=a;
            }
        }
        for(i=0;i+1<v1.size();i++){
            a=vt.size()+N;
            vt.push_back(T(XOR,v1[i],v1[i+1]));
            v1[i]=a;
        }
        const int outN=5;
        vector<int> vo;
        for(i=0;i<outN;i++){
            if(N<=(1<<i))break;
            vector<int> va;
            for(j=0;j<N;j++){
                if(j&1<<i)va.push_back(v1[j]);
            }
            a=create(va,N);
            vo.push_back(a);
        }
        vector<int> vs;
        vs.push_back(vt.size());
        for(auto node:vt){
            tie(a,b,c)=node;
            vs.push_back(a);
            vs.push_back(b);
            vs.push_back(c);
        }
        vs.push_back(vo.size());
        for(auto num:vo){
            vs.push_back(num);
        }
        return vs;
    }

    void judge(int N){
        const int M=300;
        int n,m;
        int i,j;
        int a,b,c;
        vector<int> vs=construct(N);
        vector<T> vt;
        vector<int> vo;
        n=vs[0];
        for(i=0;i<n;i++){
            vt.push_back(T(vs[3*i+1],vs[3*i+2],vs[3*i+3]));
        }
        a=3*n+1;
        m=vs[a];
        for(i=0;i<m;i++){
            vo.push_back(vs[a+i+1]);
        }
        for(i=1;i<(1<<N);i++){
            vector<char> va(M);
            int exp_ans=-1;
            for(j=0;j<N;j++){
                if(i&1<<j)va[j]=1,exp_ans=j;
            }
            for(j=0;j<vt.size();j++){
                tie(a,b,c)=vt[j];
                assert(a==OR || a==XOR);
                if(a==OR)va[N+j]=va[b]|va[c];
                else va[N+j]=va[b]^va[c];
            }
            int out_ans=0;
            for(j=0;j<vo.size();j++){
                if(va[vo[j]])out_ans|=1<<j;
            }
            if(out_ans!=exp_ans){
                cout<<"N: "<<N<<endl;
                cout<<"input: "<<i<<endl;
                cout<<exp_ans<<" "<<out_ans<<endl;
                cout<<vs<<endl;
            }
        }
    }

    void check(){
        int i;
        for(i=1;i<20;i++){
            judge(i);
        }
    }
};

#ifdef MORIRIN
int main(){
    LogarithmCircuit a;
    a.construct(3);
    a.check();
}
#endif // MORIRIN
