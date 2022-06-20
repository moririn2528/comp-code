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
    int n;
    vector<vector<int>> path;
    vector<int> vi;

    bool dfs(int pos,int bef,int goal){
        vi.push_back(pos);
        if(pos==goal)return true;
        for(auto to:path[pos]){
            if(bef==to)continue;
            if(dfs(to,pos,goal))return true;
        }
        vi.pop_back();
        return false;
    }

    LL calc_tree(int pos,int bef1,int bef2,LL ca,LL mod){
        vector<LL> v1;
        LL s=0;
        for(auto to:path[pos]){
            if(to==bef1 || to==bef2)continue;
            v1.push_back(calc_tree(to,pos,-1,ca+1,mod));
        }
        if(v1.empty())return 1;
        sort(v1.begin(),v1.end());
        for(auto num:v1){
            s*=ca;
            s+=num;
            s%=mod;
        }
        return s;
    }

    vector<LL> calc(vector<P>& vp,LL ca,LL mod){
        int i,j,k;
        int a,b,c;
        path.assign(n,vector<int>());
        union_find_tree ua(n);
        vi.clear();
        for(i=0;i<n;i++){
            a=vp[i].first-1,b=vp[i].second-1;
            if(ua.connect(a,b)){
                dfs(a,-1,b);
            }
            path[a].push_back(b);
            path[b].push_back(a);
        }
        int m=vi.size();
        vector<LL> vs(m);
        for(i=0;i<m;i++){
            int pos=vi[i];
            a=vi[(i+m-1)%m],b=vi[(i+1)%m];
            vs[i]=calc_tree(pos,a,b,ca,mod);
        }
        return vs;
    }

    bool check(vector<P>& v1,vector<P>& v2,LL ca,LL mod){
        vector<LL> va=calc(v1,ca,mod);
        vector<LL> vb=calc(v2,ca,mod);
        if(va.size()!=vb.size())return false;
        int m=va.size();
        int i,j;
        for(j=0;j<2;j++){
            LL t=1,a=0,b=0;
            for(i=0;i<m;i++){
                t*=ca;
                t%=mod;
                a=(a*ca+va[i])%mod;
                b=(b*ca+vb[i])%mod;
            }
            for(i=0;i<m;i++){
                if(a==b)return true;
                a*=ca;
                a-=va[i]*t%mod;
                a=(a+va[i]+mod)%mod;
            }
            reverse(va.begin(),va.end());
        }
        return false;
    }

    bool checkall(vector<P>& v1, vector<P>& v2){
        if(!check(v1,v2,202859,1e9+7))return false;
        if(!check(v1,v2,213491,1e9+9))return false;
        if(!check(v1,v2,204613,998244353))return false;
        return true;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        cin>>n;
        vector<P> v1(n),v2(n);
        cin>>v1>>v2;
        if(checkall(v1,v2))cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}