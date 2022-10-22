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
    vector<int> erase(vector<int> v1, int p){
        priority_queue<P,vector<P>,greater<P>> q1;
        vector<int> vs;
        int i,j=0;
        for(i=0;i<p && i<v1.size();i++){
            q1.push({v1[i],i});
        }
        for(;i<v1.size();i++){
            q1.push({v1[i],i});
            while(q1.top().second<j)q1.pop();
            j=q1.top().second;
            vs.push_back(q1.top().first);
            q1.pop();
        }
        return vs;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<int> v1(n);
        cin>>v1;
        vector<int> va=erase(v1,m);
        a=n;
        for(i=n-1;i>=n-m;i--){
            if(a==n || v1[i]<v1[a])a=i;
        }
        vector<int> v2(a);
        copy(v1.begin(), v1.begin()+a, v2.begin());
        vector<int> vb=erase(v2,m-(n-a));
        vector<int> vc;
        for(i=a;i<n;i++){
            while(!vc.empty() && v1[i]<vc.back()){
                vc.pop_back();
            }
            vc.push_back(v1[i]);
        }
        while(!vc.empty() && vb[0]<vc.back()){
            vc.pop_back();
        }
        copy(vb.begin(),vb.end(),back_inserter(vc));
        if(va<vc)cout<<va<<endl;
        else cout<<vc<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}