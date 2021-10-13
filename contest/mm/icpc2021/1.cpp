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
const LL INFLL=1LL<<60;
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

const int SFL=200,GFL=100,G=4501;
const int TIME_LIMIT=1900;
int N,E,C,F;

struct Edge{
    int group,start,end;
    int d,cap;
};
struct Flow{
    int start,end;
    int f;
};
struct Constrain{
    int node;
    int e1,e2;
};
vector<Edge> VE;
vector<Flow> VF;
vector<Constrain> VC;
vector<vector<int>> VSE;
vector<int> VSF;
vector<set<P>> constrain;
vector<vector<P>> path;
std::chrono::system_clock::time_point start_time,end_time;

void input(){
    cin>>N>>E>>C>>F;
    int a,b,c,d,e,f;
    int i;
    VE.resize(E);
    path.resize(N);
    for(i=0;i<E;i++){
        cin>>a>>b>>c>>d>>e>>f;
        Edge edge;
        edge.group=b,edge.start=c,edge.end=d;
        edge.d=e,edge.cap=f;
        VE[a]=edge;
        path[c].push_back({d,a});
        path[d].push_back({c,a});
    }
    constrain.resize(N);
    for(i=0;i<C;i++){
        cin>>a>>b>>c;
        Constrain con;
        con.node=a,con.e1=b,con.e2=c;
        VC.push_back(con);
        constrain[a].insert({b,c});
        constrain[a].insert({c,b});
    }
    VF.resize(F);
    for(i=0;i<F;i++){
        cin>>a>>b>>c>>d;
        Flow flow;
        flow.start=b,flow.end=c,flow.f=d;
        VF[a]=flow;
    }
}

void output(){
    int a,b;
    int i,j,k;
    assert(VSE.size()==VSF.size());
    int n=VSE.size();
    cout<<n<<endl;
    vector<int> used(E),used_group(G);
    LL dis_sum=0;
    for(i=0;i<n;i++){
        cout<<VSF[i]<<" "<<VSE[i]<<endl;
        unordered_set<int> s1;
        set<int> s2;
        // ensure that output edges make a line
        a=VF[VSF[i]].start;
        int r=VF[VSF[i]].f;
        for(j=0;j<VSE[i].size();j++){
            int edge_id=VSE[i][j];
            Edge& e=VE[edge_id];
            assert(e.start==a || e.end==a);
            assert(s1.find(edge_id)==s1.end());
            if(j+1<VSE[i].size()){
                int edge_next_id=VSE[i][j+1];
                assert(constrain[a].find({edge_id,edge_next_id})==constrain[a].end());
            }
            a=e.start+e.end-a;
            used[edge_id]+=r;
            
            s1.insert(edge_id);
            s2.insert(e.group);
            dis_sum+=e.d;
        }
        for(int node:s2)used_group[node]++;
        assert(a==VF[VSF[i]].end);
        assert(VSE[i].size()+1<=SFL);
    }
    for(i=0;i<E;i++){
        assert(used[i]<=VE[i].cap);
    }
    for(i=0;i<G;i++){
        assert(used_group[i]<=GFL);
    }
    
    double score=n+max(1-(double)dis_sum/n/1e6,0.0);
    cerr<<"score: "<<score<<endl;
    cerr<<n<<" "<<(double)dis_sum/n<<endl;
}

namespace sol{
    vector<int> used_cap,used_group;

    LL calc_edge_score(int id,int f,int cnt){
        if(VE[id].cap-used_cap[id]<f)return INF;
        return VE[id].cap-used_cap[id]-f+cnt+1;
    }

    void calc_flow(int id){
        vector<LL> cost(N,INFLL);
        vector<int> bef_edge(N,-1),path_count(N,-1);
        int st=VF[id].start,en=VF[id].end,f=VF[id].f;
        LL a,b,c;
        int i,j,k;
        cost[st]=0;
        path_count[st]=0;
        priority_queue<LP,vector<LP>,greater<LP>> q1;
        q1.push({0,st});
        while(!q1.empty()){
            a=q1.top().first,b=q1.top().second;q1.pop();
            if(cost[b]!=a)continue;
            if(SFL<=path_count[b]+1)continue;
            for(auto to_edge:path[b]){
                int to=to_edge.first,edge_id=to_edge.second;
                Edge& e=VE[edge_id];
                if(constrain[b].find({bef_edge[b],edge_id})!=constrain[b].end())continue;
                if(e.cap<used_cap[edge_id]+f)continue;
                if(GFL<=used_group[e.group])continue;
                c=a+calc_edge_score(edge_id,f,path_count[b]);
                if(c<cost[to]){
                    cost[to]=c,bef_edge[to]=edge_id;
                    path_count[to]=path_count[b]+1;
                    q1.push({c,to});
                }
            }
        }
        if(cost[en]>=INFLL)return;
        a=en;
        vector<int> ve;
        set<int> group;
        for(i=0;i<SFL && a!=st;i++){
            ve.push_back(bef_edge[a]);
            Edge& e=VE[bef_edge[a]];
            used_cap[bef_edge[a]]+=f;
            group.insert(e.group);
            a=e.start+e.end-a;
        }
        assert(i<SFL);
        reverse(ve.begin(),ve.end());
        VSF.push_back(id);
        VSE.push_back(ve);
        for(auto& g:group){
            used_group[g]++;
        }
        return;
    }

    void calc(){
        int n;
        int i,j;
        vector<P> vf;
        for(i=0;i<F;i++){
            vf.push_back({VF[i].f,i});
        }
        sort(vf.rbegin(),vf.rend());
        for(i=0;i<F;i++){
            int id=vf[i].second;
            calc_flow(id);
            end_time=chrono::system_clock::now();
            double elapsed=chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
            if(TIME_LIMIT<elapsed)return;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        start_time=chrono::system_clock::now();
        input();
        used_cap.assign(E,0);
        used_group.assign(G,0);

        calc();
        
        output();
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}