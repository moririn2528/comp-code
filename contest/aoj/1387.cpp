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
        int p,q,r;
        int i,j,k;
        int a,b,c;
        char ca;
        map<int,char> m1;
        cin>>n>>p>>q>>r;
        vector<pair<int,char>> v1;
        for(i=0;i<p;i++){
            cin>>a>>ca;
            a--;
            v1.push_back({a,ca});
        }
        vector<P> vp;
        for(i=0;i<q;i++){
            cin>>a>>b;
            if(b)b=a-b;
            a--;
            vp.push_back({a,b});
        }
        for(i=0;i<p;i++){
            a=v1[i].first;
            for(j=q-1;j>=0;j--){
                if(a<vp[j].first)continue;
                if(vp[j].second==0)break;
                a-=((a-vp[j].first)/vp[j].second+1)*vp[j].second;
            }
            v1[i].first=a;
        }
        sort(v1.begin(),v1.end());
        for(i=0;i<r;i++){
            cin>>a;
            a--;
            char cs='?';
            for(j=q-1,k=p-1;j>=0 && k>=0;j--){
                if(a<vp[j].first)continue;
                for(;k>=0;k--){
                    if(a<v1[k].first)continue;
                    if(v1[k].first<vp[j].first)break;
                    if(a==v1[k].first || (vp[j].second && (a-v1[k].first)%vp[j].second==0)){
                        cs=v1[k].second;
                        break;
                    }
                }
                if(cs!='?')break;
                if(vp[j].second==0)break;
                a-=((a-vp[j].first)/vp[j].second+1)*vp[j].second;
            }
            for(;k>=0;k--){
                if(a==v1[k].first)cs=v1[k].second;
            }
            cout<<cs;
        }
        cout<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}