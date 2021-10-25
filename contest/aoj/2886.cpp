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
const LL INF=1LL<<60;
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

    bool check(vector<LL>& v1,LL z,LL t){
        int n=v1.size();
        int i,j,k;
        LL l=0,r=n-1;
        LL a;
        for(i=0;i<n;i++){
            if(t<z-v1[i])return false;
            if(z<=v1[i])continue;
            a=sqrt(t-(z-v1[i]));
            l=max(l,i-a);
            r=min(r,i+a);
        }
        return l<=r;
    }

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        while(cin>>n>>m){
            if(n==0 && m==0)return;
            vector<LL> v1(n),v2,v3,v4;
            vector<LP> vq;
            for(i=0;i<m-1;i++){
                cin>>a>>b;
                b--;
                vq.push_back({a,b});
            }
            for(i=0;i<2;i++){
                v2.assign(n+5,0);
                v3.assign(n+5,0);
                v4.assign(n+5,0);
                for(j=0;j<m-1;j++){
                    a=vq[j].second;
                    b=vq[j].second+sqrt(vq[j].first);
                    v2[a]+=vq[j].first,v3[a]++,v4[a]++;
                    if(b<=n){
                        v2[b+1]-=vq[j].first-(b-a)*(b-a);
                        v3[b]-=2*(b-a)+1;
                        v4[b]--;
                    }
                }
                for(j=0;j<n;j++){
                    v2[j+1]+=v2[j];
                    v3[j+1]+=v3[j];
                    v4[j+1]+=v4[j];
                    v3[j+1]+=2*v4[j];
                    v2[j+1]-=v3[j];
                }
                for(j=0;j<n;j++)v1[j]+=v2[j];
                reverse(v1.begin(),v1.end());
                for(j=0;j<m-1;j++){
                    vq[j].second=n-1-vq[j].second;
                }
            }
            for(i=0;i<m-1;i++){
                a=vq[i].first,b=vq[i].second;
                v1[b]-=a;
            }
            cin>>a;
            LL z[3]={0,INF};
            while(z[1]-z[0]>1){
                z[2]=(z[0]+z[1])/2;
                if(check(v1,z[2],a))z[0]=z[2];
                else z[1]=z[2];
            }
            cout<<z[0]<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}