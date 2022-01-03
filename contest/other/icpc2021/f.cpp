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


vector<vector<int>> path;

class Lowlink: public union_find_tree{
public:
    vector<int> ord,lowlink;

private:
    int dfs(int pos,int bef,int& cnt){
        if(ord[pos]!=-1)return -1;
        lowlink[pos]=ord[pos]=cnt++;
        vector<int> v1;
        for(auto to:path[pos]){
            if(to==bef)continue;
            if(dfs(to,pos,cnt)==-1){
                lowlink[pos]=min(lowlink[pos],ord[to]);
            }else{
                lowlink[pos]=min(lowlink[pos],lowlink[to]);
                v1.push_back(to);
            }
        }
        for(auto to:v1){
            if(lowlink[to]<=ord[pos]){
                connect(pos,to);
            }
        }
        return 0;
    }

public:
    int init(int n){
        path.assign(n,vector<int>());
        ord.assign(n,-1);
        lowlink.assign(n,-1);
    }

    Lowlink(){}
    Lowlink(int n){
        init(n);
    }

    void reload(){
        int a=0;
        for(int i=0;i<path.size();i++){
            dfs(i,-1,a);
        }
    }
};

namespace sol{

    vector<int> cnt;

    void dfs(int pos,int bef){
        cnt[pos]=0;
        for(auto to:path[pos]){
            if(to==bef)continue;
            dfs(to,pos);
            cnt[pos]+=cnt[to];
        }
        if(path[pos].size()==1)cnt[pos]++;
    }

    vector<int> vert_a,vert_b,vert_n;

    void dfs_ab(int pos,int bef,vector<int>& deg,int n,vector<vector<int>>& vert){
        if(path[pos].size()!=1){
            for(auto to:path[pos]){
                if(to==bef)continue;
                dfs_ab(to,pos,deg,n,vert);
            }
            return;
        }
        if(deg[pos]==1){
            if(pos<n)vert_a.push_back(pos);
            else vert_b.push_back(pos);
            return;
        }
        int a=0,b=0;
        for(auto node:vert[pos]){
            if(node<n)a++;
            else b++;
        }
        if(a==0)vert_b.push_back(vert[pos][0]);
        else if(b==0)vert_a.push_back(vert[pos][0]);
        else vert_n.push_back(pos);
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        while(cin>>n>>m){
            if(n==0)return;
            vector<P> vp,vp_temp;
            union_find_tree ua(2*n);
            Lowlink link(2*n);
            vector<int> deg(2*n);
            vector<P> output;
            for(i=0;i<m;i++){
                cin>>a>>b;
                a--,b--;
                b+=n;
                vp_temp.push_back({a,b});
                deg[a]++,deg[b]++;
            }
            for(i=0;i<m;i++){
                a=vp[i].first,b=vp[i].second;
                if(deg[a]==1 && deg[b]==1)continue;
                path[a].push_back(b);
                path[b].push_back(a);
                link.connect(a,b);
                vp.push_back({a,b});
            }
            link.reload();
            path.assign(2*n,vector<int>());
            set<P> set_path;
            for(i=0;i<m;i++){
                a=vp[i].first,b=vp[i].second;
                a=link.check_parent(a);
                b=link.check_parent(b);
                if(a==b)return;
                if(a>b)swap(a,b);
                if(set_path.find({a,b})!=set_path.end())continue;
                set_path.insert({a,b});
                path[a].push_back(b);
                path[b].push_back(a);
                ua.connect(a,b);
            }
            vector<vector<int>> vert(2*n);
            for(i=0;i<2*n;i++){
                a=ua.check_parent(i);
                vert[a].push_back(i);
            }
            
            cnt.assign(2*n,0);
            for(int nest=0;nest<2*n;nest++){
                if(ua.check_parent(nest)!=nest)continue;
                if(ua.size(nest)==1)continue;
                dfs(nest,-1);
                a=cnt[nest];
                int bef=-1;
                for(i=0;i<2*n;i++){
                    bool flag=false;
                    for(auto to:path[nest]){
                        if(to==bef)continue;
                        if(2*cnt[to]>a){
                            bef=nest;
                            nest=to;
                            flag=true;
                            break;
                        }
                    }
                    if(!flag)break;
                }
                dfs(nest,-1);
                assert(cnt[nest]==a);

                a=0,b=0;
                vector<int> va,vb;
                vector<vector<int>> v1,v2;
                vp_temp.clear();
                for(i=0;i<path[nest].size();i++){
                    vert_a.clear(),vert_b.clear();
                    dfs_ab(path[nest][i],nest,deg,n,vert);
                    v1.push_back(vert_a);
                    v2.push_back(vert_b);
                    a+=vert_a.size(),b+=vert_b.size();
                }
                for(i=0;i<path[nest].size();i++){
                    vert_n.clear();
                    dfs_ab(path[nest][i],nest,deg,n,vert);
                    for(int node:vert_n){
                        int x=-1,y=-1;
                        for(int num:vert[node]){
                            if(num<n)x=num;
                            else y=num;
                        }
                        if(a<=b)v1[i].push_back(a);
                        else v2[i].push_back(b);
                    }
                    vp_temp.push_back({(int)v2[i].size()-(int)v1[i].size(),i});
                }
                sort(vp_temp.begin(),vp_temp.end());
                if(vp_temp.size()==1){
                    int x=-1,y=-1;
                    for(int num:vert[nest]){
                        if(num<n)x=num;
                        else y=num;
                    }
                    if(a==1)output.push_back({v1[i][0],y});
                    else output.push_back({x,v2[i][0]});
                }
                for(auto node:vp_temp){
                    i=node.second;
                }
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}