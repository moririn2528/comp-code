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
#include<chrono>
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

const int LIMIT_TIME=1900;
typedef tuple<int,int,int> T;
int N,K,B;

struct Poly{
    int n,m;
    int cost;
    vector<vector<char>> grid;
};
vector<Poly> VP;
vector<P> VA;
vector<T> VS,VS_saved;
int score_saved;
vector<vector<char>> grid,VAG;
int mv[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

vector<P> init_grid_pos;

void init(){
    grid.assign(N,vector<char>(N,0));
    VS.clear();
    init_grid_pos.clear();
}

void input(){
    cin>>N>>K>>B;
    int i,j,k;
    int a,b,c;
    VAG.assign(N,vector<char>(N,0));
    for(i=0;i<K;i++){
        cin>>a>>b;
        VA.push_back({a,b});
        VAG[a][b]=1;
    }
    for(i=0;i<B;i++){
        cin>>a>>b>>c;
        Poly pa;
        pa.n=a,pa.m=b;
        pa.cost=c;
        pa.grid.assign(a,vector<char>(b));
        vector<string> v1(a);
        cin>>v1;
        for(j=0;j<a;j++){
            for(k=0;k<b;k++){
                if(v1[j][k]=='#')pa.grid[j][k]=1;
            }
        }
        VP.push_back(pa);
    }
    grid.assign(N,vector<char>(N));
}

void put(int id,int x,int y){
    int i,j,k;
    assert(x+VP[id].n<=N && y+VP[id].m<=N);
    for(i=0;i<VP[id].n;i++){
        for(j=0;j<VP[id].m;j++){
            assert(!VP[id].grid[i][j] || !grid[x+i][y+j]);
            if(VP[id].grid[i][j])grid[x+i][y+j]=1;
        }
    }
    VS.push_back({id,x,y});
}

void erase(int id,int x,int y){
    int i,j,k;
    for(i=0;i<VS.size();i++){
        if(VS[i]!=T(id,x,y))continue;
        if(i+1!=VS.size())swap(VS[i],VS.back());
        VS.pop_back();
        for(j=0;j<VP[id].n;j++){
            for(k=0;k<VP[id].m;k++){
                if(!VP[id].grid[j][k])continue;
                assert(0<=x+j && x+j<N && 0<=y+k && y+k<N);
                assert(grid[x+j][y+k]);
                grid[x+j][y+k]=0;
            }
        }
        return;
    }
    assert(false);
}

int cost(vector<T>& va){
    int a,b,c;
    int s=0;
    for(auto& node:va){
        tie(a,b,c)=node;
        s+=VP[a].cost;
    }
    return s;
}

void output(){
    cout<<VS.size()<<endl;
    int a,b,c;
    for(auto& node:VS){
        tie(a,b,c)=node;
        cout<<a+1<<" "<<b<<" "<<c<<endl;
    }
    cerr<<"score: "<<1e8/cost(VS)<<endl;
}

void save(){
    if(VS_saved.empty() || cost(VS)<cost(VS_saved))VS_saved=VS;
    init();
}

void load(){
    init();
    for(auto node:VS_saved){
        int id,x,y;
        tie(id,x,y)=node;
        put(id,x,y);
    }
}

namespace sol{


    void create_init_grid(int id,int x,int y){
        int x1,x2,y1,y2;
        int a,b,c;
        int p,q;
        int i,j,k;
        int n=VP[id].n,m=VP[id].m;
        vector<vector<char>>& g=VP[id].grid;
        for(c=n,i=0;i<n;i++){
            if(!g[i][0])continue;
            for(j=0;j<n;j++){
                if(!g[j][m-1])continue;
                if(abs(i-j)<c)c=abs(i-j),x1=i,x2=j;
            }
        }
        for(c=m,i=0;i<m;i++){
            if(!g[0][i])continue;
            for(j=0;j<m;j++){
                if(!g[n-1][j])continue;
                if(abs(i-j)<c)c=abs(i-j),y1=i,y2=j;
            }
        }
        queue<P> q1,q2;
        q1.push({x,y}),q2.push({0,0});
        vector<vector<char>> used(N,vector<char>(N));
        while(!q1.empty()){
            a=q1.front().first,b=q1.front().second;q1.pop();
            p=q2.front().first,q=q2.front().second;q2.pop();
            if(a<0 || N<a+n || b<0 || N<b+m)continue;
            if(used[a][b])continue;
            used[a][b]=1;
            put(id,a,b);
            init_grid_pos.push_back({a,b});
            q1.push({a+x2-x1,b+m}),q2.push({p,q+1});
            q1.push({a-x2+x1,b-m}),q2.push({p,q-1});
            q1.push({a+n,b+y2-y1}),q2.push({p+1,q});
            q1.push({a-n,b-y2+y1}),q2.push({p-1,q});
        }
    }

    double check_cost;
    bool check(int id,int x,int y){
        int i,j,k;
        bool flag=false;
        int cnt=0;
        int a,b;
        if(x<0 || y<0 || N<x+VP[id].n || N<y+VP[id].m)return false;
        for(i=0;i<VP[id].n;i++){
            for(j=0;j<VP[id].m;j++){
                if(VP[id].grid[i][j] && grid[x+i][y+j])return false;
                if(!VP[id].grid[i][j])continue;
                if(VAG[x+i][y+j])cnt++;
                for(k=0;k<4;k++){
                    a=x+i+mv[k][0],b=y+j+mv[k][1];
                    if(a<0 || b<0 || N<=a || N<=b)continue;
                    if(grid[a][b])flag=true;
                }
            }
        }
        if(cnt)check_cost=(double)VP[id].cost/cnt;
        return flag;
    }

    int connect(int id){
        int x=VA[id].first,y=VA[id].second;
        int a,b,c;
        int p,q;
        int i,j,k;
        if(grid[x][y])return -1;
        double cost=1e9;
        int sid=-1,sx,sy;
        for(i=0;i<B;i++){
            for(j=0;j<VP[i].n;j++){
                for(k=0;k<VP[i].m;k++){
                    if(!VP[i].grid[j][k])continue;
                    a=x-j,b=y-k;
                    if(check(i,a,b) && check_cost<cost){
                        cost=check_cost;
                        sid=i,sx=a,sy=b;
                    }
                }
            }
        }
        if(sid!=-1){
            put(sid,sx,sy);
            return sid;
        }
        vector<vector<P>> bef(N,vector<P>(N,{-1,-1}));
        queue<P> q1;
        q1.push({x,y});
        while(!q1.empty()){
            P pa=q1.front();q1.pop();
            a=pa.first,b=pa.second;
            if(grid[a][b])break;
            for(i=0;i<4;i++){
                p=a+mv[i][0],q=b+mv[i][1];
                if(p<0 || q<0 || N<=p || N<=q)continue;
                if(bef[p][q].first!=-1)continue;
                bef[p][q]=pa;
                q1.push({p,q});
            }
        }
        while(a!=x || b!=y){
            P pa=bef[a][b];
            a=pa.first,b=pa.second;
            put(0,a,b);
        }
        return 0;
    }

    int dfs(int x,int y,vector<vector<char>>& used){
        if(x<0 || y<0 || N<=x || N<=y)return 0;
        if(used[x][y]==2 || !grid[x][y])return 0;
        int s=0;
        if(used[x][y]==1)s++;
        used[x][y]=2;
        for(int i=0;i<4;i++){
            s+=dfs(x+mv[i][0],y+mv[i][1],used);
        }
        return s;
    }
    bool check_connecting(){
        vector<vector<char>> used(N,vector<char>(N));
        for(int i=0;i<K;i++){
            used[VA[i].first][VA[i].second]=1;
        }
        int s=dfs(VA[0].first,VA[0].second,used);
        return s==VA.size();
    }

    void erase_extra_init_grid(int id){
        double cx=N-VP[id].n,cy=N-VP[id].m;
        cx/=2,cy/=2;
        vector<pair<double,int>> vi;
        int i,j,k;
        int a,b,c;
        double da,db;
        for(i=0;i<init_grid_pos.size();i++){
            da=init_grid_pos[i].first,db=init_grid_pos[i].second;
            vi.push_back({pow(da-cx,2)+pow(db-cy,2),i});
        }
        sort(vi.rbegin(),vi.rend());
        for(auto node:vi){
            i=node.second;
            a=init_grid_pos[i].first,b=init_grid_pos[i].second;
            erase(id,a,b);
            if(!check_connecting())put(id,a,b);
        }
        for(i=0;i<VS.size();){
            tie(a,b,c)=VS[i];
            if(a==id){
                i++;continue;
            }
            erase(a,b,c);
        }
    }

    void solve(){
        int n,m,p;
        int i,j,k;
        int a,b,c;
        chrono::system_clock::time_point start_time,end_time;
        start_time=chrono::system_clock::now();
        input();
        bool time_flag=false;
        for(i=B-1;i>0;i--){
            for(j=0;j<VP[i].n;j++){
                for(k=0;k<VP[i].m;k++){
                    create_init_grid(i,j,k);
                    vector<P> vp;
                    for(a=0;a<K;a++){
                        vp.push_back({connect(a),a});
                    }
                    erase_extra_init_grid(i);
                    sort(vp.rbegin(),vp.rend());
                    for(a=0;a<K;a++){
                        connect(vp[a].second);
                    }
                    save();
                    end_time=chrono::system_clock::now();
                    if(chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count()>LIMIT_TIME){
                        time_flag=true;
                        break;
                    }
                }
                if(time_flag)break;
            }
            if(time_flag)break;
        }
        cerr<<i<<" "<<j<<" "<<k<<endl;
        load();
        output();
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}