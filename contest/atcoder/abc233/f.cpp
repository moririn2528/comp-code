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

class union_find_tree{
private:
    static constexpr int N=100005;
    int n;
    queue<int> q1;
    vector<int> parent;
    vector<int> num;
public:
    void init(){
        parent.assign(n,-1);
        num.assign(n,1);
    }
    union_find_tree(int n_init){
        assert(n_init>=0);
        n=n_init;
        init();
    }
    union_find_tree(){
        n=N;
        init();
    }

    int check_parent(int x){
        assert(x>=0 && x<n);
        if(parent[x]!=-1){
            q1.push(x);
            return check_parent(parent[x]);
        }
        int a;
        while(!q1.empty()){
            a=q1.front(),q1.pop();
            parent[a]=x;
        }
        return x;
    }

    bool connect(int x,int y){
        assert(x>=0 && x<n);
        assert(y>=0 && y<n);
        x=check_parent(x),y=check_parent(y);
        if(x==y)return true;
        if(num[x]>num[y])swap(x,y);
        parent[x]=y;
        num[y]+=num[x];
        return false;
    }

    int size(int pos){
        pos=check_parent(pos);
        return num[pos];
    }

    bool check(int x,int y){//connect:true
        assert(x>=0 && x<n);
        assert(y>=0 && y<n);
        return check_parent(x)==check_parent(y);
    }
};

namespace sol{
    vector<vector<P>> path;

    vector<char> used,used2;
    vector<int> vp,ve;
    bool dfs(int pos,int g){
        if(used[pos])return false;
        if(used2[pos])return false;
        used[pos]=1;
        vp.push_back(pos);
        if(pos==g)return true;
        for(auto node:path[pos]){
            int to=node.first,e=node.second;
            ve.push_back(e);
            if(dfs(to,g))return true;
            ve.pop_back();
        }
        vp.pop_back();
        return false;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n;
        vector<int> v1(n),v2(n);
        path.resize(n);
        cin>>v1;
        cin>>m;
        for(i=0;i<n;i++){
            v1[i]--;
            v2[v1[i]]=i;
        }
        vector<int> deg(n);
        union_find_tree ua(n);
        for(i=0;i<m;i++){
            cin>>a>>b;
            a--,b--;
            if(ua.check(a,b))continue;
            ua.connect(a,b);
            path[a].push_back({b,i});
            path[b].push_back({a,i});
            deg[a]++,deg[b]++;
        }
        vector<int> vs;
        used2.assign(n,0);
        for(i=0;i<n;i++){
            for(j=0,a=-1;j<n;j++){
                if(used2[j])continue;
                if(a==-1 || deg[a]>deg[j])a=j;
            }
            for(auto node:path[a]){
                int to=node.first;
                deg[to]--;
            }
            if(a==v1[a]){
                used2[a]=1;
                continue;
            }   
            vp.clear();
            ve.clear();
            used.assign(n,0);
            if(!dfs(v2[a],a)){
                cout<<-1<<endl;
                return;
            }
            used2[a]=1;
            for(j=0;j<ve.size();j++){
                vs.push_back(ve[j]+1);
                a=vp[j],b=vp[j+1];
                swap(v1[a],v1[b]);
                swap(v2[v1[a]],v2[v1[b]]);
            }
        }
        cout<<vs.size()<<endl;
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}