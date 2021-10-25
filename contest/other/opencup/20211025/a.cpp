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

    void create(vector<LL>& vx,vector<LL>& v1){
        int n=vx.size();
        assert(vx.size()==v1.size());
        int i;
        LL a,b;
        LL p=0;
        for(i=1;i+1<n;i++){
            a=v1[i]-v1[i-1],b=v1[i+1]-v1[i];
            vx[i]=(b-a)/2;
            p+=vx[i];
        }
        a=v1[n-1]-v1[n-2]-p;
        if(a<0)vx[n-1]=-a;
        else vx[0]=a;
    }

    LL sum(vector<LL>& v1){
        LL s=0;
        for(LL num:v1)s+=num;
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        cin>>n;
        vector<vector<LL>> grid(n,vector<LL>(n));
        cin>>grid;
        vector<LL> vx(n),vy(n),v1;
        for(i=0;i<n;i++){
            v1.push_back(grid[i][0]);
        }
        create(vx,v1);
        create(vy,grid[0]);
        a=sum(vx),b=sum(vy);
        assert(abs(b-a)%2==0);
        c=abs(b-a)/2;
        if(a<b)vx[0]+=c,vx[n-1]+=c;
        else vy[0]+=c,vy[n-1]+=c;
        a=0;
        for(i=0;i<n;i++){
            a+=vx[i]*i+vy[i]*i;
        }
        a=grid[0][0]-a;
        assert(a%(2*(n-1))==0);
        a/=2*(n-1);
        vx[0]+=a,vx[n-1]+=a;
        vy[0]+=a,vy[n-1]+=a;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                a=min(vx[i],vy[j]);
                grid[i][j]=a;
                vx[i]-=a,vy[j]-=a;
            }
            cout<<grid[i]<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}