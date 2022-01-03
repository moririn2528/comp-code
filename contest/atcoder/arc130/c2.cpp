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
typedef pair<LL,LL> P;
const LL INF=1<<30;
const LL MAX=1e9+7;

template<typename T> ostream& operator<<(ostream& os,const vector<T>& v1){
    LL n=v1.size();
    for(LL i=0;i<n;i++){
        os<<v1[i];
    }
    return os;
}
template<typename T1,typename T2> ostream& operator<<(ostream& os,const pair<T1,T2>& p){
    os<<p.first<<" "<<p.second;
    return os;
}
template<typename T> istream& operator>>(istream& is,vector<T>& v1){
    LL n=v1.size();
    for(LL i=0;i<n;i++)is>>v1[i];
    return is;
}
template<typename T1,typename T2> istream& operator>>(istream& is,pair<T1,T2>& p){
    is>>p.first>>p.second;
    return is;
}

namespace sol{
    const LL N=10;
    LL t=0;

    vector<LL> input(LL p){
        LL i;
        vector<LL> vs(N);
        for(;p>0;p/=10){
            LL a=p%10;
            vs[a]++;
            t+=a;
        }
        return vs;
    }

    LL check(vector<LL>& v1, vector<LL>& v2){
        LL a=0;
        LL s=0;
        for(LL i=0;i<N;i++){
            a+=v2[N-i-1];
            s+=min(v1[i],a);
        }
        return s;
    }

    LL sumvec(vector<LL>& v1){
        LL s=0;
        for(auto num:v1)s+=num;
        return s;
    }

    void outputA(vector<LL>& v1, vector<LL>& v2,vector<LL>& va, vector<LL>& vb){
        LL i,j,k;
        for(i=0,j=N-1;i<N;i++){
            for(;i+j>=N-1;j--){
                LL a=min(v1[i],v2[j]);
                v1[i]-=a,v2[j]-=a;
                for(k=0;k<a;k++){
                    if(i)va.push_back(i);
                    if(j)vb.push_back(j);
                }
                if(v1[i]==0)break;
            }
        }
    }

    LL toLL(vector<LL>& v1, vector<LL>& v2){
        LL s=0;
        for(auto num:v1){
            s*=10;
            s+=num;
        }
        for(auto num:v2){
            s*=10;
            s+=num;
        }
        return s;
    }

    LL output(vector<LL>& v1, vector<LL>& v2,LL p,LL q){
        LL a=0;
        LL s=0;
        LL i,j,k;
        LL x,y;
        vector<LL> va,vb;
        vector<LL> va2,vb2;
        if(p!=-1){
            v1[p]--,v2[q]--;
            if(v1[0]>0)outputA(v1,v2,va,vb);
            else outputA(v2,v1,vb,va);
            va.push_back(p),vb.push_back(q);
        }
        v1[0]=0,v2[0]=0;
        a=min(sumvec(v1),sumvec(v2));
        for(i=1,x=0,y=0;i<N;i++){
            for(j=0;j<v1[i];j++,x++){
                if(x<a)va.push_back(i);
                else va2.push_back(i);
            }
            for(j=0;j<v2[i];j++,y++){
                if(y<a)vb.push_back(i);
                else vb2.push_back(i);
            }
        }
        // cout<<va2<<va<<endl;
        // cout<<vb2<<vb<<endl;
        return toLL(va2,va)+toLL(vb2,vb);
    }

    LL count(LL a){
        LL s=0;
        for(;a>0;a/=10)s+=a%10;
        return s;
    }

    LL solve(LL ina,LL inb){
        LL n,m;
        LL i,j,k;
        LL a,b,c;
        t=0;
        vector<LL> v1=input(ina);
        vector<LL> v2=input(inb);
        a=sumvec(v1),b=sumvec(v2);
        if(a>b)v2[0]=a-b;
        else v1[0]=b-a;
        b=-1,c=-1;
        LL s=0;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(v1[i]==0 || v2[j]==0 || i+j<10)continue;
                v1[i]--,v2[j]--;
                a=check(v1,v2);
                if(s<a){
                    s=a,b=i,c=j;
                }
                v1[i]++,v2[j]++;
            }
        }
        s=t-(s+1)*9;
        LL out=output(v1,v2,b,c);
        LL cou=count(out);
        if(cou!=s){
            cout<<"input"<<endl;
            cout<<ina<<endl;
            cout<<inb<<endl;
            cout<<"output"<<endl;
            cout<<b<<" "<<c<<endl;
            cout<<out<<endl;
            cout<<cou<<endl;
            cout<<s<<endl;
        }
    }

    mt19937 rnd(23);

    LL get_rand(){
        LL s;
        for(;;){
            s=rnd();
            s=abs(s);
            LL a=s;
            for(;a>0;a/=10){
                if(a%10==0)break;
            }
            if(a==0)return s;
        }
    }
    
    void check(){
        LL i,j,k;
        LL a,b,c;
        for(i=0;i<100;i++){
            cout<<"Case "<<i<<endl;
            a=get_rand(),b=get_rand();
            solve(abs(a),abs(b));
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::check();
}