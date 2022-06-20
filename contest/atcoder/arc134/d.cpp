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
    int n,m;
    vector<int> v1;

    void output(vector<int>& va){
        vector<int> vs;
        for(auto num:va)vs.push_back(v1[num]);
        for(auto num:va)vs.push_back(v1[num+n]);
        cout<<vs<<endl;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n;
        v1.resize(2*n);
        cin>>v1;
        map<int,vector<int>> m1;
        for(i=0;i<n;i++){
            a=v1[i];
            m1[a].push_back(i);
        }
        vector<int> va;
        auto itr=m1.begin();
        a=itr->first;
        b=INF;
        for(auto num:itr->second){
            if(v1[num+n]<b){
                b=v1[num+n];
                i=num;
            }
        }
        if(b<=a){
            va.push_back(i);
            output(va);
            return;
        }
        for(auto num:itr->second)va.push_back(num);
        for(auto node:m1){
            a=node.first;
            if(a==v1[va[0]])continue;
            if(v1[va[0]+n]<=a)break;
            for(auto num:node.second){
                if(num<va.back())continue;
                va.push_back(num);
            }
        }
        b=v1[va[0]+n];
        itr=m1.find(b);
        if(itr==m1.end()){
            output(va);
            return;
        }
        a=0;
        for(auto num:va){
            if(b<v1[num+n]){
                a=1;
                break;
            }
            if(v1[num+n]<b){
                a=-1;
                break;
            }
        }
        if(a<=0){
            output(va);
            return;
        }
        for(auto num:itr->second){
            if(num<va.back())continue;
            va.push_back(num);
        }
        output(va);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}