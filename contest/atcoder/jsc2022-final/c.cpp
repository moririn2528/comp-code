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

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<int> v1(n);
        cin>>v1;
        for(i=0;i+1<n;i++){
            if(v1[i]==v1[i+1])break;
        }
        if(i+1==n && (n-m)%2){
            cout<<"No"<<endl;
            return;
        }
        cout<<"Yes"<<endl;
        int su=0;
        for(i=0;i<n;i++){
            su+=v1[i];
        }
        vector<int> va,vb;
        a=0,b=0;
        for(i=0;i<m-1;i++){
            va.push_back(1);
            a+=v1[i];
            if(v1[i]==v1[i+1] && b==0){
                b=1;
                vb.push_back(2);
            }else vb.push_back(1);
        }
        va.push_back(n-m+1);
        vb.push_back(n-m);
        if((su-a)%3){
            cout<<va<<endl;
            return;
        }
        if(b){
            cout<<vb<<endl;
            return;
        }
        va.pop_back();
        va.pop_back();
        su-=a-v1[m-2];
        a=0;
        for(i=m-2;i+1<n;i++){
            a+=v1[i];
            if(a%3 && (su-a)%3){
                va.push_back(i-m+3);
                va.push_back(n-i-1);
                cout<<va<<endl;
                return;
            }
        }
        assert(false);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}