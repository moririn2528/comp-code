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

const int N=400,M=1995;
vector<vector<int>> dis(N,vector<int>(N,-1));
vector<P> path;
vector<int> alt_path_cnt(M);
vector<int> input_dis(M);
vector<char> path_ban(M);

void input(){
    vector<P> vp(N);
    cin>>vp;
    int i,j,k;
    int a,b,c;
    int x,y;
    vector<P> v1;
    for(i=0;i<M;i++){
        cin>>a>>b;
        x=vp[a].first-vp[b].first;
        y=vp[a].second-vp[b].second;
        c=round(sqrt(x*x+y*y));
        dis[a][b]=dis[b][a]=c;
        path.push_back({a,b});
        v1.push_back({c,i});
    }
    sort(v1.begin(),v1.end());
    dsu ua(N);
    for(i=0;i<v1.size();i++){
        if(ua.size(0)==N)break;
        c=v1[i].first,j=v1[i].second;
        a=path[j].first,b=path[j].second;
        if(ua.same(a,b))continue;
        ua.merge(a,b);
    }
    for(;i<M;i++){
        a=v1[i].second;
        path_ban[a]=1;
    }
    for(i=M-1;i>=0;i--){
        mf_graph<int> g(N);
        for(j=M-1;j>i;j--){
            if(path_ban[j])continue;
            a=path[j].first,b=path[j].second;
            g.add_edge(a,b,1);
            g.add_edge(b,a,1);
        }
        a=path[i].first,b=path[i].second;
        alt_path_cnt[i]=g.flow(a,b);
    }
}

void score(vector<int>& used){
    #ifndef MORIRIN
    return;
    #endif //MORIRIN
    assert(used.size()==M);
    int i,j,k;
    int a,b;
    double A=0,B=0;
    dsu ua(N);
    dsu ub(N);
    vector<P> vp;
    for(i=0;i<M;i++){
        a=path[i].first,b=path[i].second;
        if(used[i]){
            A+=input_dis[i];
            assert(!ua.same(a,b));//error: loop exist
            ua.merge(a,b);
        }
        vp.push_back({input_dis[i],i});
    }
    assert(ua.size(0)==N);//error: connection error
    sort(vp.begin(),vp.end());
    for(i=0;i<M;i++){
        j=vp[i].second;
        a=path[j].first,b=path[j].second;
        if(ub.same(a,b))continue;
        ub.merge(a,b);
        B+=vp[i].first;
    }
    cerr<<"score: "<<round(1e8*B/A)<<endl;
}

namespace sol{

    void solve(){
        int i,j,k;
        int a,b,c;
        int l;
        input();
        vector<int> used(M);
        double start_coeff=1.3,end_coeff=1.8;
        int max_alt=4;
        for(i=0;i<M;i++){
            max_alt=max(max_alt,alt_path_cnt[i]);
        }
        for(i=0;i<M;cout<<used[i]<<endl,i++){
            cin>>l;
            input_dis[i]=l;
            dsu ua(N);
            a=path[i].first,b=path[i].second;
            if(path_ban[i])continue;
            for(j=0;j<i;j++){
                if(used[j])ua.merge(path[j].first,path[j].second);
            }
            if(ua.same(a,b))continue;
            for(j=i+1;j<M;j++){
                if(path_ban[j])continue;
                ua.merge(path[j].first,path[j].second);
            }
            if(!ua.same(a,b)){
                used[i]=1;
                continue;
            }
            double coeff=end_coeff-(end_coeff-start_coeff)*alt_path_cnt[i]/max_alt;
            if(l<=coeff*dis[a][b])used[i]=1;
        }
        //cerr<<alt_path_cnt<<endl;
        score(used);
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}