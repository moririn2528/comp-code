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
    vector<int> vs;

    void set1(LL a,LL l,LL r){
        for(LL i=l;i<r;i++){
            swap(vs[a],vs[a+i+1]);
        }
    }
    void set2(LL a,LL b,LL n){
        int i;
        vector<LL> va(b-a);
        for(i=0;i<b-a;i++){
            va[i]=vs[n-i-1];
        }
        for(i=n-1;i>=b;i--){
            vs[i]=vs[i-(b-a)];
        }
        for(i=0;i<b-a;i++){
            vs[a+i]=va[i];
        }
    }

    void solve(){
        LL n,m;
        LL l,r;
        int i,j,k;
        LL a,b,c;
        cin>>n>>l>>r;
        l--;
        for(i=0;i<n;i++){
            vs.push_back(i+1);
        }
        b=-1;
        for(i=0;i<n-1;i++){
            a=n-i-1;
            if(a<=l){
                l-=a,r-=a;
                continue;
            }
            if(r<=a){
                if(b!=-1 && b<i)set2(b,i,n);
                set1(i,max(l,0LL),r);
                break;
            }
            if(0<=l)set1(i,l,a);
            if(b==-1)b=i+1;
            l-=a,r-=a;
        }
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}