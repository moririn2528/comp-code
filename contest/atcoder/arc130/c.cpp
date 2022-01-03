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
    const int N=10;
    int t=0;

    vector<int> input(){
        string sa;
        cin>>sa;
        int i;
        vector<int> vs(N);
        for(i=0;i<sa.size();i++){
            int a=sa[i]-'0';
            vs[a]++;
            t+=a;
        }
        return vs;
    }

    int check(vector<int>& v1, vector<int>& v2){
        int a=0;
        int s=0;
        for(int i=0;i<N;i++){
            a+=v2[N-i-1];
            s+=min(v1[i],a);
            a-=min(v1[i],a);
        }
        return s;
    }

    int sumvec(vector<int>& v1){
        int s=0;
        for(auto num:v1)s+=num;
        return s;
    }

    void outputA(vector<int>& v1, vector<int>& v2,vector<int>& va, vector<int>& vb){
        int i,j,k;
        for(i=0,j=N-1;i<N;i++){
            for(;i+j>=N-1;j--){
                int a=min(v1[i],v2[j]);
                v1[i]-=a,v2[j]-=a;
                for(k=0;k<a;k++){
                    if(i)va.push_back(i);
                    if(j)vb.push_back(j);
                }
                if(v1[i]==0)break;
            }
        }
    }

    void output(vector<int>& v1, vector<int>& v2,int p,int q){
        int a=0;
        int s=0;
        int i,j,k;
        int x,y;
        vector<int> va,vb;
        vector<int> va2,vb2;
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
        cout<<va2<<va<<endl;
        cout<<vb2<<vb<<endl;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        vector<int> v1=input();
        vector<int> v2=input();
        a=sumvec(v1),b=sumvec(v2);
        if(a>b)v2[0]=a-b;
        else v1[0]=b-a;
        b=-1,c=-1;
        int s=-1;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(v1[i]==0 || v2[j]==0 || i+j<N)continue;
                v1[i]--,v2[j]--;
                a=check(v1,v2);
                if(s<a){
                    s=a,b=i,c=j;
                }
                v1[i]++,v2[j]++;
            }
        }
        output(v1,v2,b,c);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}