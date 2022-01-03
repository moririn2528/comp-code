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
double init_member_ability=36.15739107142433;
double diff=1.5171349988361629;
//end hyper parameter

int N,M,K,R;
vector<int> task_cannot,task_start;
vector<vector<int>> task_difficulty,task_dep_tree;//task_dependency
vector<char> task_fin;
vector<int> member_status;
set<int> task_able;

vector<vector<double>> member_ability;

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
        return real_cost(member_id,task_id);
    }

    void guess(int member_id,int task_id,int during_time){
        double expect=real_cost(member_id,task_id);
        if(abs(expect-during_time)<eps)return;
        int sign=1;//higher ability than expect
        if(expect<during_time)sign=-1;
        for(int i=0;i<K;i++){
            if(member_ability[member_id][i]<task_difficulty[task_id][i] && sign==1){
                member_ability[member_id][i]+=diff;
            }
            if(member_ability[member_id][i]>task_difficulty[task_id][i] && sign==-1){
                member_ability[member_id][i]-=diff;
            }
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
            for(i=0;i<M;i++){
                if(member_status[i]!=-1)continue;
                int opt_id=-1;
                double opt_score=INF;
                for(int id:task_able){
                    da=cost(i,id);
                    if(da<opt_score){
                        opt_score=da;
                        opt_id=id;
                    }
                }
                if(opt_id==-1)continue;
                output.push_back(i+1);
                output.push_back(opt_id+1);
                task_start[opt_id]=day;
                member_status[i]=opt_id;
                task_able.erase(opt_id);
            }
            cout<<output.size()/2<<" ";
            cout<<output<<endl;
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
    bool flag=false;
    double da=0,db=0,dc=1;
    for(char ca:sa){
        if(ca=='.'){
            flag=true;
            continue;
        }
        assert('0'<=ca && ca<='9');
        if(!flag){
            da*=10;da+=ca-'0';
        }else{
            db*=10;db+=ca-'0';
            dc*=10;
        }
    }
    return da+db/dc;
}

int main(int argc,char* argv[]){
    #ifdef MORIRIN
    assert(argc>=3);
    init_member_ability=string2double(string(argv[1]));
    diff=string2double(string(argv[2]));
    #endif//MORIRIN
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}