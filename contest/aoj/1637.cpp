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

    void solve(int n){
        int i,j,k;
        LL a,b,c;
        vector<vector<char>> br(n,vector<char>(n));
        vector<vector<LL>> cost(n,vector<LL>(n));
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                cin>>a;
                if(a>0)br[i][j]=1,br[j][i]=1;
                else a=-a;
                cost[i][j]=cost[j][i]=a;
            }
        }
        if(n==2){
            cout<<cost[0][1]<<endl;
            return;
        }
        vector<char> v1(n);
        auto is_red=[&](int x,int y)->bool{
            return v1[x]^v1[y]^br[x][y];
        };
        LL s=INF;
        for(int i1=0;i1<2;i1++){
            for(j=1;j<n;j++){
                for(int i2=0;i2<2;i2++){
                    v1.assign(n,0);
                    v1[0]=i1;
                    v1[j]=i2;
                    if(!is_red(0,j))continue;
                    for(k=1;k<n;k++){
                        if(j==k)continue;
                        a=0;
                        if(is_red(0,k))a++;
                        if(is_red(j,k))a++;
                        if(a==1)break;
                    }
                    if(k==n)continue;
                    a=k;
                    for(int i3=0;i3<2;i3++){
                        v1.assign(n,0);
                        v1[0]=i1;
                        v1[j]=i2;
                        v1[a]=i3;
                        for(k=1;k<n;k++){
                            if(k==j || k==a)continue;
                            b=0;
                            if(is_red(0,k))b++;
                            if(is_red(j,k))b++;
                            if(is_red(a,k))b++;
                            if(b>=2)v1[k]=1;
                        }
                        b=0,c=0;
                        union_find_tree ua(n);
                        for(i=0;i<n;i++){
                            for(k=i+1;k<n;k++){
                                if(is_red(i,k)){
                                    b++,c+=cost[i][k];
                                    if(ua.connect(i,k))b=n;
                                }
                            }
                        }
                        if(b==n-1)s=min(s,c);
                    }
                }
            }
        }
        if(s>=INF)s=-1;
        cout<<s<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n){
        if(n==0)return 0;
        sol::solve(n);
    }
}