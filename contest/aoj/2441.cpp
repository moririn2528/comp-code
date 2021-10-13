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
const LL INF=1LL<<57;
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

    LL count(LL a){
        LL s=0;
        LL i,j;
        for(i=1,j=1;i<INF && i<a;i*=10,j++){
            LL b=min(a,10*i);
            LL x=(b-1)/3-(i-1)/3;
            LL y=(b-1)/5-(i-1)/5;
            LL z=(b-1)/15-(i-1)/15;
            s+=j*(b-i-x-y+z);
            s+=x*4+y*4;
            if(s>INF)return s;
        }
        return s;
    }

    void solve(){
        LL n,m;
        LL i,j,k;
        LL a,b,c;
        LL z[3]={1,INF};
        cin>>n;
        while(z[1]-z[0]>1){
            z[2]=(z[0]+z[1])/2;
            if(count(z[2])<n)z[0]=z[2];
            else z[1]=z[2];
        }
        a=z[0];
        n-=count(a)+1;
        string ss;
        for(i=a;i<a+50;i++){
            if(i%15==0)ss+="FizzBuzz";
            else if(i%3==0)ss+="Fizz";
            else if(i%5==0)ss+="Buzz";
            else ss+=to_string(i);
        }
        cout<<ss.substr(n,20)<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}