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
    const LL mod=1e9+7;
    LL A,B,C;
    LL N;
    map<P,LL> m1;
    int trans,xt,yt;
    vector<int> vx,vy;

    P pos(int x,int y){
        x--,y--;
        if(trans)swap(x,y);
        if(xt)x=N-x-1;
        if(yt)y=N-y-1;
        x=vx[x],y=vy[y];
        if(m1.find({x,y})==m1.end()){
            m1[{x,y}]=(A*(x+1)+B*(y+1))%C;
        }
        return {x,y};
    }

    void solve(){
        int m;
        int i,j,k;
        LL a,b,c,d;
        LL D,E,F,G;
        string sa;
        cin>>N>>m>>A>>B>>C>>D>>E>>F>>G;
        vx.resize(N),vy.resize(N);
        iota(vx.begin(),vx.end(),0);
        iota(vy.begin(),vy.end(),0);
        for(i=0;i<m;i++){

            // for(j=0;j<N;j++){
            //     for(k=0;k<N;k++){
            //         cout<<m1[pos(j+1,k+1)]<<" ";
            //     }
            //     cout<<endl;
            // }

            cin>>sa;
            if(sa=="WR"){
                cin>>a>>b>>c;
                m1[pos(a,b)]=c;
            }
            if(sa=="CP"){
                cin>>a>>b>>c>>d;
                m1[pos(c,d)]=m1[pos(a,b)];
            }
            if(sa=="SR" || sa=="SC"){
                cin>>a>>b;
                a--,b--,c=0;
                if(sa=="SC")c=1;
                c^=trans;
                if(c==0){
                    if(xt)a=N-a-1,b=N-b-1;
                    swap(vx[a],vx[b]);
                }else{
                    if(yt)a=N-a-1,b=N-b-1;
                    swap(vy[a],vy[b]);
                }
            }
            if(sa=="RH"||sa=="RV"){
                c=trans;
                if(sa=="RV")c^=1;
                if(c==0)xt^=1;
                else yt^=1;
            }
            if(sa=="RL"){
                if(!trans)yt^=1;
                else xt^=1;
                trans^=1;
                swap(xt,yt);
            }
            if(sa=="RR"){
                if(!trans)xt^=1;
                else yt^=1;
                trans^=1;
                swap(xt,yt);
            }
        }
        LL s=314159265;
        for(i=D;i<=E;i++){
            for(j=F;j<=G;j++){
                s=(31*s+m1[pos(i,j)])%mod;
            }
        }
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}