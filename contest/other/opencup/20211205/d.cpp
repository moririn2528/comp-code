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
const int INF=1<<20;
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

    void init(){
        
    }
    typedef vector<int> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;
    string mv_str="NSEW";
    int n,m,q;
    int mv[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
    int bx=-1,by=-1;
    vector<P> pos;

    int check(int dir,V3& acc){
        int s=INF;
        int mx=mv[dir][0],my=mv[dir][1];
        for(auto p:pos){
            int x=bx+p.first,y=by+p.second;
            if(0<=x && x<n && 0<=y && y<m){
                s=min(s,acc[x][y][dir]);
                continue;
            }
            if(my==0){
                if(y<0 || m<=y)continue;
                if(mx==-1){
                    if(x<0)continue;
                    s=min(s,acc[n-1][y][0]+x-(n-1));
                }
                if(mx==1){
                    if(n<=x)continue;
                    s=min(s,acc[0][y][1]-x);
                }
            }else{
                if(x<0 || n<=x)continue;
                if(my==1){
                    if(m<=y)continue;
                    s=min(s,acc[x][0][2]-y);
                }
                if(my==-1){
                    if(y<0)continue;
                    s=min(s,acc[x][m-1][3]+y-(m-1));
                }
            }
        }
        return s;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m>>q;
        vector<string> grid(n);
        V3 acc(n,V2(m,V1(4,INF)));
        cin>>grid;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                for(k=0;k<4;k++){
                    int x=i,y=j;
                    for(a=0;a<15;a++,x+=mv[k][0],y+=mv[k][1]){
                        if(x<0 || y<0 || n<=x || m<=y){
                            acc[i][j][k]=INF;
                            break;
                        }
                        if(grid[x][y]=='A'){
                            acc[i][j][k]=a-1;
                            break;
                        }
                    }
                }
            }
        }
        bx=-1;
        pos.clear();
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(grid[i][j]=='B'){
                    if(bx==-1)bx=i,by=j;
                    pos.push_back({i-bx,j-by});
                }
            }
        }
        string que;
        cin>>que;
        for(i=0;i<q;i++){
            int dir;
            for(dir=0;dir<4;dir++){
                if(que[i]==mv_str[dir]){
                    break;
                }
            }
            assert(dir<4);
            int s=check(dir,acc);
            if(s>=INF){
                cout<<"TAK"<<endl;
                return;
            }
            bx+=mv[dir][0]*s;
            by+=mv[dir][1]*s;
        }
        cout<<"NIE"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}