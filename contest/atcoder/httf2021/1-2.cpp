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
#include<random>
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
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

const double INF=1e9;
const double eps=1e-5;

//hyper parameter
double init_member_ability=5.893986202209341;
double task_fast_cost1=4.991993978601366,task_fast_cost2=3.615935011496966;
double diff_a=0.5820164869756106,diff_b=0.19372099029033513,diff_c=0.9036478688548292;// diff=max(a-cnt*b,c)
double expect_th=7.799197871805806;
double task_rnd_init_per=0.212957246140369,task_rnd_lim_day=149.82450;
//end hyper parameter

int N,M,K,R;
vector<int> task_cannot,task_start;
vector<vector<int>> task_difficulty,task_dep_tree;//task_dependency
vector<char> task_fin;
vector<int> member_status;
set<int> task_able;
mt19937 rnd(12345);

vector<vector<double>> member_ability;
vector<int> guess_count;

double get_double_rnd(){
    return (double)rnd()/mt19937::max();
}

void input(){
    int i;
    int a,b;
    cin>>N>>M>>K>>R;
    task_difficulty.assign(N,vector<int>(K));
    cin>>task_difficulty;
    task_dep_tree.resize(N);
    task_cannot.assign(N,0);
    for(i=0;i<R;i++){
        cin>>a>>b;
        a--,b--;
        task_dep_tree[a].push_back(b);
        task_cannot[b]++;
    }
    task_fin.assign(N,0);
    member_status.assign(M,-1);
    task_start.assign(N,-1);
    member_ability.assign(M,vector<double>(K,init_member_ability));
    for(i=0;i<N;i++){
        if(!task_cannot[i])task_able.insert(i);
    }
    guess_count.assign(N,0);
}

namespace sol{

    double real_cost(int member_id,int task_id){
        double s=0;
        for(int i=0;i<K;i++){
            s+=max(0.0,task_difficulty[task_id][i]-member_ability[member_id][i]);
        }
        return s;
    }

    double cost(int member_id,int task_id){
        double s=0;
        for(auto to:task_dep_tree[task_id]){
            assert(task_cannot[to]>0);
            s+=1.0/task_cannot[to];
        }
        s*=K;
        if(guess_count[member_id]==0)s*=task_fast_cost1;
        else s*=task_fast_cost2;
        return -s+real_cost(member_id,task_id);
    }

    void guess(int member_id,int task_id,int during_time){
        int i;
        double expect=real_cost(member_id,task_id);
        if(abs(expect-during_time)<eps)return;
        double d=(expect-during_time)/expect;
        double diff=max(diff_a-diff_b*guess_count[member_id],diff_c);
        guess_count[member_id]++;
        vector<double> v1(K,0);
        int tash_high=0;
        for(i=0;i<K;i++){
            if(member_ability[member_id][i]<task_difficulty[task_id][i]){
                v1[i]=(task_difficulty[task_id][i]-member_ability[member_id][i])*d;
            }
            if(task_difficulty[task_id][tash_high]<task_difficulty[task_id][i]){
                tash_high=i;
            }
        }
        if(during_time-expect>expect_th*K){
            v1[tash_high]=-member_ability[member_id][tash_high];
        }
        for(i=0;i<K;i++){
            member_ability[member_id][i]=max(member_ability[member_id][i]+v1[i]*diff,0.0);
        }
    }

    void output_guess(int id){
        cout<<"#s "<<id+1;
        for(int j=0;j<K;j++){
            cout<<" "<<round(member_ability[id][j]);
        }
        cout<<endl;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        double da,db;

        #ifdef MORIRIN
        for(i=0;i<M;i++)output_guess(i);
        #endif//MORIRIN

        input();

        for(int day=0;;day++){
            vector<int> output;
            queue<int> member_queue;
            vector<int> task_assign_pre(N,-1),v1;
            vector<double> task_cost(N,INF);
            for(int id:task_able)v1.push_back(id);
            double rnd_per=0;
            if(day<task_rnd_lim_day)rnd_per=task_rnd_init_per*(1-day/task_rnd_lim_day);
            int max_rnd_task=v1.size()*rnd_per;
            auto assign_task=[&](int mem_id,int task_id)->void{
                output.push_back(mem_id+1);
                output.push_back(task_id+1);
                task_start[task_id]=day;
                member_status[mem_id]=task_id;
                task_able.erase(task_id);
            };
            for(i=0,j=0;i<M;i++){
                if(member_status[i]!=-1)continue;
                if(j<max_rnd_task && get_double_rnd()<rnd_per && !v1.empty()){
                    //random assign
                    k=rnd()%v1.size();
                    int task_id=v1[k];
                    assign_task(i,task_id);
                    j++;
                    v1.erase(v1.begin()+k);
                }else{
                    //optimize assign
                    member_queue.push(i);
                }
            }
            while(!member_queue.empty()){
                i=member_queue.front();
                member_queue.pop();
                int opt_id=-1;
                double opt_score=INF;
                for(int id:task_able){
                    da=cost(i,id);
                    if(task_cost[id]<=da+eps)continue;
                    if(da<opt_score){
                        opt_score=da;
                        opt_id=id;
                    }
                }
                if(opt_id==-1)continue;
                if(task_assign_pre[opt_id]!=-1){
                    member_queue.push(task_assign_pre[opt_id]);
                }
                task_assign_pre[opt_id]=i;
                task_cost[opt_id]=opt_score;
            }
            for(i=0;i<N;i++){
                if(task_assign_pre[i]==-1)continue;
                assign_task(task_assign_pre[i],i);
            }
            cout<<output.size()/2;
            if(!output.empty())cout<<" "<<output;
            cout<<endl;
            cin>>n;
            if(n==-1)return;
            for(i=0;i<n;i++){
                cin>>a;
                a--;//member id
                int task=member_status[a];
                task_fin[task]=1;
                member_status[a]=-1;
                int dur=day-task_start[task]+1;
                for(int to:task_dep_tree[task]){
                    task_cannot[to]--;
                    if(!task_cannot[to])task_able.insert(to);
                }
                guess(a,task,dur);
                #ifdef MORIRIN
                output_guess(a);
                #endif//MORIRIN
            }
        }
    }
}

double string2double(string sa){
    int cnt=0;
    double da=0,db=0,dc=1;
    double de;
    int asign=1,esign=1;
    for(char ca:sa){
        if(ca=='.'){
            cnt=1;
            continue;
        }
        if(ca=='e'){
            cnt=2;
            continue;
        }
        if(ca=='-'){
            assert(cnt==0 || cnt==2);
            if(cnt==0)asign=-1;
            else esign=-1;
            continue;
        }
        assert('0'<=ca && ca<='9');
        if(cnt==0){
            da*=10;da+=ca-'0';
        }else if(cnt==1){
            db*=10;db+=ca-'0';
            dc*=10;
        }else{
            de*=10,de+=ca-'0';
        }
    }
    double ds=da+db/dc;
    ds*=asign;
    de*=esign;
    ds*=pow(10.0,de);
    return ds;
}

int main(int argc,char* argv[]){
    #ifdef MORIRIN
    if(argc>=3){
        init_member_ability=string2double(string(argv[1]));
        task_fast_cost1=string2double(string(argv[2]));
        task_fast_cost2=string2double(string(argv[3]));
        diff_a=string2double(string(argv[4]));
        diff_b=string2double(string(argv[5]));
        diff_c=string2double(string(argv[6]));
        expect_th=string2double(string(argv[7]));
        task_rnd_init_per=string2double(string(argv[8]));
        task_rnd_lim_day=string2double(string(argv[9]));
    }
    #endif//MORIRIN
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::
    solve();
}