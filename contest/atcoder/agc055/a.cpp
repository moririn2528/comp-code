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
#include<random>
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
    int t[6][3]={{0,1,2},{0,2,1},{1,2,0},{1,0,2},{2,0,1},{2,1,0}};

    void calc(string sa,int n){
        string ss(sa.size(),'0');
        int i,j,k;
        int a,b,c;
        vector<vector<int>> cnt(3,vector<int>(3));
        vector<int> v1(6);
        vector<vector<int>> vi(3);
        for(i=0;i<3;i++){
            for(j=i*n;j<(i+1)*n;j++){
                a=sa[j]-'A';
                cnt[i][a]++;
                vi[a].push_back(j);
            }
        }
        for(i=0;i<6;i++){
            a=n;
            for(j=0;j<3;j++){
                b=t[i][j];
                a=min(a,cnt[j][b]);
            }
            for(j=0;j<3;j++){
                b=t[i][j];
                cnt[j][b]-=a;
            }
            v1[i]=a;
        }
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                assert(cnt[i][j]==0);
            }
        }
        for(i=2;i>=0;i--){
            for(j=0;j<6;j++){
                for(k=0;k<v1[j];k++){
                    a=t[j][i];
                    assert(!vi[a].empty());
                    b=vi[a].back();
                    vi[a].pop_back();
                    ss[b]='1'+j;
                }
            }
        }
        cout<<ss<<endl;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        string sa;
        cin>>sa;
        calc(sa,n);
    }

    mt19937 rnd;

    void calc(){
        int n;
        const int N=1000;
        cin>>n;
        int i,j,k;
        for(k=0;k<N;k++){
            string sa(3*n,'A');
            for(i=0;i<n;i++){
                sa[i]='B';
                sa[i+n]='C';
            }
            for(i=3*n-1;i>=1;i--){
                j=rnd()%i;
                swap(sa[j],sa[i]);
            }
            cout<<sa<<endl;
            calc(sa,n);
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    //sol::calc();
    sol::solve();
}