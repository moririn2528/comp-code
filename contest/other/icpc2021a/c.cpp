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
    const int N=100;
    typedef vector<char> V1;
    typedef vector<V1> V2;
    typedef vector<V2> V3;

    int n,m;
    V3 can;
    V2 used;
    vector<int> vs;
    vector<vector<int>> dep;
    vector<P> to(N);
    bool dfs(int x,int y,int d){
        int i,j;
        int a,b;
        int tx,ty;
        assert(0<=x && x<=n && 0<=y && y<=n);
        if(dep[x][y]!=d)return false;
        if(used[x][y])return false;
        if(x==n && y==0)return true;
        used[x][y]=1;
        for(i=0;i<N;i++){
            if(!can[x][y][i])continue;
            a=i/10,b=i%10;
            vs.push_back(a);
            vs.push_back(b);
            if(dfs(x+to[i].first,y+to[i].second,d-1))return true;
            vs.pop_back();
            vs.pop_back();
        }
        return false;
    }

    void check(vector<int>& v1){
        vector<int> v2;
        int i,j,k;
        int a,b;
        for(i=0;i<vs.size();i+=2){
            a=vs[i],b=vs[i+1];
            if(a==0)v2.push_back(b);
            else if(b==0)continue;
            else if(v2.size()<a){
                assert(false);
            }else{
                for(j=0;j<b;j++){
                    k=v2.size()-a;
                    v2.push_back(v2[k]);
                }
            }
        }
        assert(v1.size()==v2.size());
        for(i=0;i<v1.size();i++){
            assert(v1[i]==v2[i]);
        }
        
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        int x,y;
        string sa;
        cin>>sa;
        n=sa.size();
        vector<int> v1;
        for(i=0;i<n;i++){
            v1.push_back(sa[i]-'0');
        }
        can.assign(n+5,V2(n+5,V1(N)));
        for(i=0;i<=n;i++){
            for(j=0;j<=n;j++){
                V2 fcan(10,V1(10)),bcan(10,V1(10));
                // front
                for(a=0;a<10;a++){
                    bool flag=true;
                    for(b=0;b<10;b++){
                        if(a==0){
                            if(i<n && v1[i]==b)fcan[a][b]=1;
                            continue;
                        }
                        if(b==0){
                            fcan[a][b]=1;
                            continue;
                        }
                        if(i<a)continue;
                        if(n<i+b)continue;
                        if(v1[i-a+b-1]!=v1[i+b-1])flag=false;
                        if(flag)fcan[a][b]=1;
                    }
                }

                // back
                for(a=0;a<10;a++){
                    bool flag=true;
                    for(b=0;b<10;b++){
                        if(a==0){
                            if(0<j && v1[j-1]==b)bcan[a][b]=1;
                            continue;
                        }
                        if(b==0){
                            bcan[a][b]=1;
                            continue;
                        }
                        if(j<a+b)continue;
                        if(v1[j-a-b]!=v1[j-b])flag=false;
                        if(flag)bcan[a][b]=1;
                    }
                }

                for(a=0;a<10;a++){
                    for(b=0;b<10;b++){
                        if(!fcan[a][b] || !bcan[b][a])continue;
                        can[i][j][a*10+b]=1;
                    }
                }
            }
        }
        for(i=0;i<N;i++){
            a=i/10,b=i%10;
            to[i]=P(0,0);
            if(a==0)to[i].first++;
            else if(b>0)to[i].first+=b;
            if(b==0)to[i].second--;
            else if(a>0)to[i].second-=a;
        }

        // // for test
        // for(i=0;i<=n;i++){
        //     for(j=0;j<=n;j++){
        //         for(k=0;k<N;k++){
        //             if(!can[i][j][k])continue;
        //             x=i+to[k].first;
        //             y=j+to[k].second;
        //             if(!(0<=x && x<=n && 0<=y && y<=n)){
        //                 cout<<i<<" "<<j<<" "<<k<<endl;
        //             }
        //         }
        //     }
        // }

        dep.assign(n+2,vector<int>(n+2,-1));
        queue<P> q1;
        q1.push({n,0});
        for(i=0;!q1.empty();i++){
            for(j=q1.size();j>0;j--){
                a=q1.front().first,b=q1.front().second;
                q1.pop();
                if(dep[a][b]!=-1)continue;
                dep[a][b]=i;
                for(k=0;k<N;k++){
                    x=a-to[k].first,y=b-to[k].second;
                    if(x<0 || n<x || y<0 || n<y)continue;
                    if(dep[x][y]!=-1)continue;
                    if(!can[x][y][k])continue;
                    q1.push({x,y});
                }
            }
        }

        used.assign(n+5,V1(n+5));
        assert(dfs(0,n,dep[0][n]));
        cout<<vs<<endl;

        check(v1);
        reverse(vs.begin(),vs.end());
        check(v1);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}