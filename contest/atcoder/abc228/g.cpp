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
#include<atcoder/all>
using namespace std;
using namespace atcoder;
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
    using mint=modint998244353;
    typedef vector<mint> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
    typedef vector<V3> V4;
    int n,m,p;

    V4 prod(V4& v1,V4& v2){
        int a,b,c,d,e,f;
        V4 vs(n,V3(n,V2(n,V1(n,0))));
        for(a=0;a<n;a++){
            for(b=0;b<n;b++){
                for(c=0;c<n;c++){
                    for(d=0;d<n;d++){
                        for(e=0;e<n;e++){
                            for(f=0;f<n;f++){
                                vs[a][b][c][d]+=v1[a][e][c][f]*v2[e][b][f][d];
                            }
                        }
                    }
                }
            }
        }
        return vs;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        int x,y,z;
        cin>>n>>m>>p;
        V4 v1(n,V3(n,V2(n,V1(n))));
        V4 v2(n,V3(n,V2(n,V1(n))));
        vector<vector<int>> grid(n,vector<int>(m));
        for(i=0;i<n;i++){
            string sa;
            cin>>sa;
            for(j=0;j<m;j++){
                grid[i][j]=sa[j]-'0';
            }
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                v1[i][i][j][j]=1;
            }
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<m;k++){
                    a=grid[i][k]*10+grid[j][k];
                    for(x=0;x<n;x++){
                        for(y=0;y<n;y++){
                            for(z=0;z<m;z++){
                                b=grid[x][z]*10+grid[y][z];
                                if(a==b)v2[i][j][x][y]++;
                            }
                        }
                    }
                }
            }
        }
        for(i=10;i>=0;i--){
            v1=prod(v1,v1);
            if(p&1<<i)v1=prod(v1,v2);
        }
        mint s=0,ma=n*m;
        s=ma.pow(p+1);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    s-=v1[i][j][i][k];
                }
            }
        }
        cout<<s.val()<<endl;
    }
}

int main(){
    sol::solve();
}