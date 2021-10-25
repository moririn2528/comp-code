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

    vector<vector<int>> path;
    vector<char> vrev;
    vector<int> vs,vp;
    vector<P> vq;

    void create(int id,int x,int y){
        char rev=vrev[id];
        int i,j,k;
        int a,b,c;
        int p,q;
        for(i=vq[id].first,j=0;i<vq[id].second;){
            if(j<path[id].size() && i==vq[path[id][j]].first){
                c=path[id][j];
                j++;
                p=vq[c].first-vq[id].first,q=vq[c].second-vq[c].first;
                if(rev)a=y-p-q,b=y-p;
                else a=x+p,b=x+p+q;
                create(c,a,b);
                i+=q;
                continue;
            }
            c=i-vq[id].first;
            if(rev)a=y-c-1;
            else a=x+c;
            vs[a]=vp[i];
            i++;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y;
        cin>>n>>m;
        m++;
        vector<int> vt(m);
        vector<P> v1;
        map<int,int> m1;
        vp.resize(n);
        cin>>vp;
        vq.push_back({0,n});
        v1.push_back({n,0});
        for(i=1;i<m;i++){
            cin>>a>>b;
            a--;
            vq.push_back({a,b});
            v1.push_back({b-a,i});
        }
        path.assign(m,vector<int>());
        vrev.assign(m,0);
        sort(v1.begin(),v1.end());
        for(i=0;i<m;i++){
            c=v1[i].second;
            a=vq[c].first,b=vq[c].second;
            auto itr=m1.lower_bound(a);
            x=vp[a],y=vp[b-1];
            for(j=0;itr!=m1.end() && itr->first<b;j++){
                int id=itr->second;
                path[c].push_back(id);
                if(vq[id].first==a)x=min(x,vt[id]);
                if(vq[id].second==b)y=min(y,vt[id]);
                m1.erase(itr);
                itr=m1.upper_bound(a);
            }
            m1[a]=c;
            if(y<x)vrev[c]=1,vt[c]=y;
            else vt[c]=x;
        }
        vs.resize(n);
        create(0,0,n);
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}