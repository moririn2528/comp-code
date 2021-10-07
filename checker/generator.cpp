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

    void solve(){
        random_device seed;
        mt19937 rnd(seed());
        int i,j,k;
        int a,b,c;
        const int n=10;
        const int G=1000;
        cout<<n<<" 1 2"<<endl;
        vector<int> vx(n),vy(n);
        while(1){
            int dis;
            for(i=0;i<n;i++){
                vx[i]=rnd()%G+1;
                vy[i]=rnd()%G+1;
                if(2<=i && rnd()%2){
                    dis=abs(vx[0]-vx[1])+abs(vy[0]-vy[1]);
                    a=rnd()%dis,b=rnd()%2;
                    vx[i]=vx[b]+(rnd()%2*2-1)*a;
                    vy[i]=vy[b]+(rnd()%2*2-1)*(dis-a);
                }
            }
            for(i=0;i<n;i++){
                for(j=i+1;j<n;j++){
                    if(vx[i]==vx[j] && vy[i]==vy[j])break;
                }
                if(j<n)break;
            }
            if(i==n)break;
        }
        for(i=0;i<n;i++){
            cout<<vx[i]<<" "<<vy[i]<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}