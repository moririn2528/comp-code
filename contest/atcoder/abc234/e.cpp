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

    vector<LL> ll2vec(LL a){
        vector<LL> va;
        while(a>0){
            va.push_back(a%10);
            a/=10;
        }
        reverse(va.begin(),va.end());
        return va;
    }

    LL vec2ll(vector<LL>& va){
        LL s=0;
        for(LL num:va){
            s*=10;
            s+=num;
        }
        return s;
    }

    bool check(vector<LL>& va,vector<LL>& vb){
        assert(va.size()==vb.size());
        int n=va.size();
        int i;
        int a=vb[1]-vb[0];
        for(i=2;i<n;i++){
            vb[i]=vb[i-1]+a;
            if(vb[i]<0 || 10<=vb[i])return false;
        }
        return vec2ll(va)<=vec2ll(vb);
    }

    void solve(){
        LL n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n;
        if(n<100){
            cout<<n<<endl;
            return;
        }
        vector<LL> v1=ll2vec(n);
        vector<LL> v2=v1;
        for(i=0;i<100;i++){
            if(check(v1,v2)){
                cout<<vec2ll(v2)<<endl;
                return;
            }
            v2[1]++;
            if(v2[1]==10)v2[0]++,v2[1]=0;
        }
        assert(false);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}