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
        while(cin>>n){
            if(n==0)return;
            vector<P> v1(n);
            cin>>v1;
            a=0;
            int s=0;
            for(i=0;i<n;i++){
                if(v1[i].first==v1[i].second)a++;
            }
            for(i=0;i<3*n;i++){
                b=-1;
                c=-1;
                for(j=0;j<n;j++){
                    if(v1[j].first==v1[j].second)continue;
                    if(c!=-1){
                        if(b==v1[j].first || b==v1[j].second){
                            b=v1[j].first+v1[j].second-b;
                            a++;
                            v1[j].first=v1[j].second=0;
                        }else{
                            if(v1[j].first<b)swap(b,v1[j].first);
                            if(v1[j].second<b)swap(b,v1[j].second);
                        }
                    }else{
                        c=j;
                        b=v1[j].first;
                        v1[j].first=0;
                        if(v1[j].second<b)swap(b,v1[j].second);
                    }
                    s++;
                }
                if(c==-1)break;
                v1[c].first=b;
                b=-1;
            }
            assert(i<3*n);
            cout<<s<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}