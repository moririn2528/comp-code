#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
    const int N=1e6+6;
    char ca[N],cb[N];
    int cnt[N],dig[N],rcnt[N];
    set<int> s1;

    void split(int x,int y){
        int a=cnt[x]-(y-x),b=x+cnt[x];
        cnt[x]=y-x,rcnt[y]=y-x;
        dig[y]=dig[x],cnt[y]=a,rcnt[b]=a;
        s1.insert(-y);
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c,d;
        int x,y,z;
        scanf("%d%d",&n,&m);
        string sa,sb;
        vector<int> va(n),vb(n);
        scanf("%s%s",ca,cb);
        sa=ca,sb=cb;
        for(i=n-1,c=0;i>=0;i--){
            a=sa[i]-'0';
            b=sb[i]-'0';
            va[i]=a,vb[i]=b;
            cnt[i]=1,dig[i]=(a+b+c)%10;
            rcnt[i+1]=1;
            s1.insert(-i);
            c=(a+b+c)/10;
        }
        rcnt[0]=100;
        for(i=0;i<m;i++){
            scanf("%d%d%d",&a,&b,&c);
            b--;
            if(a==1){
                d=c-va[b];
                va[b]=c;
            }else{
                d=c-vb[b];
                vb[b]=c;
            }
            int s=2;
            auto itr=s1.lower_bound(-b);
            x=-(*itr);
            if(d==0){
                printf("%d %d\n",dig[x],0);
                continue;
            }
            if(x!=b)split(x,b);
            if(cnt[b]!=1)split(b,b+1);
            dig[b]+=d;
            if(dig[b]>=10){
                dig[b]-=10,x=9,y=0,z=1;
            }else if(dig[b]<0){
                dig[b]+=10,x=0,y=9,z=-1;
            }else{
                printf("%d %d\n",dig[b],2);
                continue;
            }
            a=0,c=b;
            while(c-rcnt[c]>=0 && dig[c-rcnt[c]]==x){
                if(c!=b)s1.erase(-c);
                c-=rcnt[c];
                a+=cnt[c];
            }
            s+=a;
            if(a>0){
                cnt[c]=a,rcnt[b]=a;
                dig[c]=y;
            }
            if(c>0){
                s++;
                d=c-rcnt[c];
                if(cnt[d]!=1)split(d,c-1);
                dig[c-1]+=z;
            }
            printf("%d %d\n",dig[b],s);
        }
    }
}

int main(){
    sol::solve();
}