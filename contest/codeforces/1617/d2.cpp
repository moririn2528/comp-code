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

    void init(){
        
    }
    
    char check(int a,int b,int c){
        int s;
        cout<<"? "<<a+1<<" "<<b+1<<" "<<c+1<<endl;
        cin>>s;
        if(s==-1)assert(false);
        return 1-s;
    }

    void output(vector<char>& v1){
        vector<int> vs;
        for(int i=0;i<v1.size();i++){
            if(v1[i])vs.push_back(i+1);
        }
        cout<<"! "<<vs.size()<<" "<<vs<<endl;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y,z;
        int p,q;
        cin>>n;
        vector<char> vs(n);
        vector<char> v1(n/3);
        a=-1,b=-1;
        for(i=0;i<n/3;i++){
            v1[i]=check(3*i,3*i+1,3*i+2);
            if(v1[i])a=i;
            else b=i;
        }
        for(i=0;i<3;i++)vs[3*b+i]=1;
        p=-1;
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                x=3*b+(i+1)%3;
                y=3*b+(i+2)%3;
                z=3*a+j;
                if(check(x,y,z)){
                    p=3*b+i,q=3*a+j;
                    vs[p]=0,vs[q]=1;
                }
            }
        }
        if(p==-1){
            p=3*b,q=3*a;
            for(i=0;i<3;i++)vs[3*b+i]=0;
            for(i=0;i<3;i++)vs[3*a+i]=1;
        }
        for(i=0;i<n/3;i++){
            if(i==a || i==b)continue;
            if(v1[i])c=p;
            else c=q;
            if(v1[i]==check(3*i,3*i+1,c)){
                vs[3*i]=vs[3*i+1]=v1[i];
                vs[3*i+2]=check(p,q,3*i+2);
            }else{
                vs[3*i+2]=v1[i];
                vs[3*i]=check(p,q,3*i);
                vs[3*i+1]=1-vs[3*i];
            }
        }
        output(vs);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}