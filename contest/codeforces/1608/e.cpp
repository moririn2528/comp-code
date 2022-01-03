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
    typedef tuple<int,int,int> T;
    void rotate(vector<T>& v1){
        int a,b,c;
        for(int i=0;i<v1.size();i++){
            tie(a,b,c)=v1[i];
            v1[i]={b,-a,c};
        }
    }

    void reverse(vector<T>& v1){
        int a,b,c;
        for(int i=0;i<v1.size();i++){
            tie(a,b,c)=v1[i];
            v1[i]={-a,b,c};
        }
    }

    bool check1(vector<T>& v1,int mid,int x){
        int n=v1.size();
        int l=0,r=1;
        if(mid==l)l++,r++;
        if(mid==r)r++;
        int i,j;
        int cnt=0;
        int a,b,c;
        for(i=0;i<n;i++){
            tie(a,b,c)=v1[i];
            if(mid==c)cnt++;
            if(cnt==x)break;
        }
        if(cnt<x)return false;
        int t=a;
        vector<P> v2;
        for(;i<n;i++){
            tie(a,b,c)=v1[i];
            if(t==a)continue;
            v2.push_back({b,c});
        }
        sort(v2.begin(),v2.end());
        int z[2]={l,r};
        int k=0,bef=-INF;
        cnt=0;
        for(i=0;i<v2.size();i++){
            a=v2[i].first,b=v2[i].second;
            if(bef<a && z[k]==b)cnt++;
            if(cnt==x)cnt=0,bef=a,k++;
            if(k==2)return true;
        }
        return false;
    }
    bool check2(vector<T>& v1,int mid,int x){
        int n=v1.size();
        int l=0,r=1;
        if(mid==l)l++,r++;
        if(mid==r)r++;
        int z[3]={l,mid,r};
        int i,j;
        int k=0,bef=-INF,cnt=0;
        int a,b,c;
        for(i=0;i<n;i++){
            tie(a,b,c)=v1[i];
            if(bef<a && z[k]==c)cnt++;
            if(cnt==x)cnt=0,bef=a,k++;
            if(k==3)return true;
        }
        return false;
    }

    bool check(vector<T>& v1,int x){
        int i,j,k;
        for(i=0;i<4;i++){
            sort(v1.begin(),v1.end());
            for(j=0;j<3;j++){
                if(check2(v1,j,x))return true;
            }
            for(j=0;j<2;j++){
                sort(v1.begin(),v1.end());
                for(k=0;k<3;k++){
                    if(check1(v1,k,x))return true;
                }
                reverse(v1);
            }
            rotate(v1);
        }
        return false;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        vector<T> vt(n);
        for(i=0;i<n;i++){
            cin>>a>>b>>c;
            vt.push_back({a,b,c-1});
        }
        int z[3]={0,n/3+1};
        while(z[1]-z[0]>1){
            z[2]=(z[0]+z[1])/2;
            if(check(vt,z[2]))z[0]=z[2];
            else z[1]=z[2];
        }
        cout<<z[0]*3<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}