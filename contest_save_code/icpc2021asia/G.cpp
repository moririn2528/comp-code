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
typedef pair<LL,int> LP;
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
    int n,m;

    vector<int> count(vector<vector<int>>& path,vector<P>& vp){
        int a,b,c;
        union_find_tree ua(n);
        int siz=0;
        vector<int> vs;
        int bef=-1;
        for(auto node:vp){
            int id=node.second;
            if(bef!=node.first){
                if(bef!=-1)vs.push_back(siz);
                bef=node.first;
            }
            siz++;
            for(auto to:path[id]){
                if(!ua.connect(id,to))siz--;
            }
        }
        return vs;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        vector<int> v1,vi;
        vector<P> vp;
        vector<vector<int>> path(n),rpath(n);
        for(i=0;i<n;i++){
            cin>>a;
            v1.push_back(a);
            vp.push_back(make_pair(a,i));
        }
        sort(vp.begin(),vp.end());
        for(i=0;i<m;i++){
            cin>>a>>b;
            a--,b--;
            if(make_pair(v1[a],a)>make_pair(v1[b],b))swap(a,b);
            path[b].push_back(a);
            rpath[a].push_back(b);
        }
        vector<int> va=count(path,vp);
        reverse(vp.begin(),vp.end());
        vector<int> vb=count(rpath,vp);
        reverse(vp.begin(),vp.end());
        reverse(vb.begin(),vb.end());
        assert(va.size()==vb.size());
        int bef=-1;
        for(i=0,j=-1;i<n;i++){
            if(bef==vp[i].first)continue;
            bef=vp[i].first;
            if(i==0)continue;
            j++;
            a=i-va[j],b=(n-i)-vb[j];
            if(a+1<vb[j])continue;
            if(b+1<va[j])continue;
            cout<<vp[i-1].first<<endl;
            return;
        }
        cout<<-1<<endl;
    }
}

int main(){
    sol::solve();
}