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

template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}

namespace sol{
    const int N=40;
    const double pi=acos(-1);
    typedef complex<double> C;
    typedef tuple<int,int,int> T;
    int tris[2][3][2]={{{0,0},{1,0},{0,1}},{{0,0},{-1,0},{0,-1}}};

    C pos(int i,int j){
        i-=N,j-=N;
        return C(j*0.5+i,j*sqrt(3)/2);
    }
    bool in_line(C a,C b,C p){
        return cross_product(a,p)*cross_product(b,p)<0;
    }
    bool in(C a,C b,C c,C p){
        for(int i=0;i<3;i++){
            if(!in_line(b-a,c-a,p-a))return false;
            swap(a,b),swap(b,c);
        }
        return true;
    }
    vector<vector<int>> vert(2*N+2,vector<int>(2*N+2,-1));

    void check(int x,int y,int id,queue<T>& q1){
        int i,j;
        int a,b,c;
        int p=x,q=y;
        vector<char> used(4);
        for(i=0;i<3;i++){
            a=x+tris[id][i][0],b=y+tris[id][i][1];
            if(a<0 || b<0 || 2*N<a || 2*N<b)return;
            if(vert[a][b]==-1)return;
            assert(!used[vert[a][b]]);
            used[vert[a][b]]=1;
            p+=tris[id][i][0],q+=tris[id][i][1];
        }
        for(c=0;c<4 && used[c];c++);
        for(i=0;i<3;i++){
            q1.push({p-2*tris[id][i][0],q-2*tris[id][i][1],c});
        }
    }

    void solve(){
        int n,m;
        int i,j,k,l;
        int a,b,c;
        int x,y;
        queue<T> q1;
        string sa;
        double arg;
        q1.push({N,N,0});
        q1.push({N+1,N,1});
        q1.push({N,N+1,2});
        while(!q1.empty()){
            tie(a,b,c)=q1.front();q1.pop();
            if(a<0 || b<0 || 2*N<a || 2*N<b)continue;
            if(vert[a][b]!=-1)continue;
            vert[a][b]=c;
            for(i=0;i<2;i++){
                for(j=0;j<3;j++){
                    x=a-tris[i][j][0],y=b-tris[i][j][1];
                    check(x,y,i,q1);
                }
            }
        }
        vector<int> v1;
        for(i=0;i<2;i++){
            cin>>sa>>a>>b;
            c=sa[0]-'B';
            arg=c*60+a;
            arg*=pi/180;
            C p1=polar((double)b,arg);
            c=0;
            for(j=1;j<2*N;j++){
                for(k=1;k<2*N;k++){
                    for(l=0;l<2;l++){
                        if(in(pos(j,k),pos(j+tris[l][1][0],k+tris[l][1][1]),pos(j+tris[l][2][0],k+tris[l][2][1]),p1)){
                            c=0;
                            for(x=0;x<3;x++){
                                c|=1<<vert[j+tris[l][x][0]][k+tris[l][x][1]];
                            }
                        }
                    }
                }
            }
            v1.push_back(c);
        }
        if(v1[0]==v1[1])cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}