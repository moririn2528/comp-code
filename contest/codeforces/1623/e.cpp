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
    vector<P> child;
    vector<int> par,vid,vie;
    vector<char> dupl;
    string sa,ss;
    typedef tuple<char,int,int> T;

    void set_id(int pos,int& id,int& id2){
        if(pos==-1)return;
        vie[pos]=id2++;
        set_id(child[pos].first,id,id2);
        vid[pos]=id++;
        set_id(child[pos].second,id,id2);
    }

    void create_output(int pos){
        if(pos==-1)return;
        create_output(child[pos].first);
        ss+=sa[pos];
        if(dupl[pos])ss+=sa[pos];
        create_output(child[pos].second);
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        cin>>sa;
        child.resize(n);
        par.assign(n,-1);
        dupl.resize(n);
        for(i=0;i<n;i++){
            cin>>a>>b;
            a--,b--;
            child[i]={a,b};
            if(a!=-1)par[a]=i;
            if(b!=-1)par[b]=i;
        }
        a=b=0;
        set_id(0,a,b);
        priority_queue<T,vector<T>,greater<T>> q1;
        for(i=0;i!=-1;i=child[i].first){
            q1.push({sa[i],vid[i],i});
        }
        set<int> s1;
        s1.insert(-1);

        while(!q1.empty()){
            tie(ignore,ignore,a)=q1.top();q1.pop();
            auto itr=s1.lower_bound(vie[a]);
            itr--;
            b=vie[a]-*itr;
            if(m<b)continue;
            m-=b;
            for(;a!=-1 && !dupl[a];a=par[a]){
                dupl[a]=1;
                s1.insert(vie[a]);
                for(i=child[a].second;i!=-1;i=child[i].first){
                    q1.push({sa[i],vid[i],i});
                }
            }
        }
        create_output(0);
        cout<<ss<<endl;

    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}