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

class Fraction{
    typedef long long int ll;
    long long int gcd(long long int a,long long int b){
        if(a<b)swap(a,b);
        if(b==0)return a;
        return gcd(b,a%b);
    }

public:
    ll x,y;
    Fraction(){};
    Fraction(ll _x, ll _y):x(_x),y(_y){
        if(x==0 && y==0)return;
        if(y<0)x=-x,y=-y;
        ll d=gcd(abs(x),abs(y));
        x/=d,y/=d;
    }
    template<typename T> Fraction(pair<T,T> p){
        Fraction(p.first,p.second);
    }

    bool operator==(const Fraction f)const{
        return x==f.x && y==f.y;
    }
    bool operator<(const Fraction f)const{
        return x*f.y<f.x*y;
    }
    bool operator<=(const Fraction f)const{
        return x*f.y<=f.x*y;
    }
    bool operator>(const Fraction f)const{return !((*this)<=f);}
    bool operator>=(const Fraction f)const{return !((*this)<f);}
};

namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<vector<char>> grid(n+2,vector<char>(m+2));
        string sa;
        for(i=0;i<n;i++){
            cin>>sa;
            for(j=0;j<m;j++){
                if(sa[j]=='#')grid[i+1][j+1]=1;
            }
        }
        vector<pair<Fraction,int>> v1;
        for(i=0;i<=n;i++){
            for(j=0;j<=m;j++){
                c=0;
                for(a=0;a<2;a++){
                    for(b=0;b<2;b++){
                        c+=grid[i+a][j+b];
                    }
                }
                if(c%2==0)continue;
                c=1-c/2;
                if(grid[i][j]==c)v1.push_back({Fraction(n-i,j),1});
                if(grid[i+1][j+1]==c)v1.push_back({Fraction(n-i,j),-1});
            }
        }
        sort(v1.begin(),v1.end());
        int s=0;
        int cnt=1;
        for(i=0;i<v1.size();i++){
            Fraction f=v1[i].first;
            a=v1[i].second;
            cnt+=a;
            if(i+1<v1.size() && f==v1[i+1].first)continue;
            s=max(s,cnt);
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}