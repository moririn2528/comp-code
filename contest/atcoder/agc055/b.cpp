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
    void fix(string& sa){
        string ss="A"+sa+"A";
        sa=ss;
    }

    bool check(string sa,string sb){
        int i,j;
        int a,b,c;
        int n=sa.size();
        fix(sa),fix(sb);
        vector<int> cnt(3);
        for(i=0;i<=n;i++){
            a=sa[i+1]-sa[i];
            b=sb[i+1]-sb[i];
            cnt[i%3]+=b-a;
        }
        for(i=0;i<3;i++){
            a=abs(cnt[i]);
            if(a%3)return false;
        }
        return true;
    }

    string res(string sa){
        string ss;
        int n=sa.size();
        int i,j;
        int a,b,c;
        for(i=0;i<n;i++){
            ss.push_back(sa[i]);
            j=(int)ss.size()-3;
            if(j<0)continue;
            a=ss[j+1]-ss[j];
            if(a<0)a+=3;
            if(0<=j && ss[j]!=ss[j+1] && ss[j+1]!=ss[j+2] && ss[j]!=ss[j+2] && a==1){
                for(j=0;j<3;j++){
                    ss.pop_back();
                }
            }
        }
        return ss;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        string sa,sb;
        cin>>sa>>sb;
        if(!check(sa,sb)){
            cout<<"NO"<<endl;
            return;
        }
        if(res(sa)==res(sb))cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}