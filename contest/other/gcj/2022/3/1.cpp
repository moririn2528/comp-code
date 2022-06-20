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

namespace debug{
    bool flag=false;
    vector<int> col,ball;
    int N,K;
    int cnt=0;
    mt19937 rnd(123);

    void swaps(vector<int>& poss){
        int n=poss.size();
        int i,j;
        int a,b;
        for(i=0;i<n;i++){
            j=i+rnd()%(n-i);
            a=poss[i],b=poss[j];
            swap(ball[a],ball[b]);
        }
    }

    void init(){
        if(!flag)return;
        ball.resize(N);
        iota(ball.begin(),ball.end(),0);
        vector<int> poss(N);
        iota(poss.begin(),poss.end(),0);
        int i,j,k;
        swaps(poss);
    }

    int check(){
        cnt++;
        assert(cnt<=K);
        assert(col.size()==N);
        int i,j,k;
        vector<vector<int>> v1(N);
        for(i=0;i<N;i++){
            assert(col[i]!=-1);
            v1[col[i]].push_back(i);
        }
        for(i=0;i<N;i++){
            swaps(v1[i]);
        }
        for(i=0;i<N;i++){
            if(ball[i]!=i)return 0;
        }
        return 1;
    }
}

namespace sol{
    int N,K;
    int ques_count=0;

    void init(){
        cin>>N>>K;
        debug::N=N;
        debug::K=K;
    }

    int ques(vector<int>& col){
        ques_count++;
        if(debug::flag){
            debug::col=col;
            return debug::check();
        }
        for(int i=0;i<N;i++){
            col[i]++;
        }
        cout<<col<<endl;
        int s;
        cin>>s;
        if(s==-1)exit(s);
        return s;
    }

    vector<int> get(){
        if(debug::flag)return debug::ball;
        vector<int> vs(N);
        cin>>vs;
        for(int i=0;i<N;i++){
            vs[i]--;
        }
        return vs;
    }

    void put_col(vector<int>& col, int x,int y,int& c){
        col[x]=c,col[y]=c;
        c++;
    }

    void solve(){
        int i,j,k;
        int a,b,c;
        for(i=0;i<K;i++){
            vector<int> v1=get();
            vector<char> used(N);
            b=0;
            vector<int> col(N,-1);
            for(j=0;j<N;j++){
                if(used[j])continue;
                vector<int> va;
                for(a=j;!used[a];a=v1[a]){
                    used[a]=1;
                    va.push_back(a);
                }
                c=va.size();
                if(c==2){
                    put_col(col,va[0],va[1],b);
                    continue;
                }
                put_col(col,j,j,b);
                for(k=0;k<c/2;k++){
                    put_col(col,va[k+1],va[c-k-1],b);
                }
            }
            if(ques(col))return;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    cin>>n;
    sol::init();
    for(i=0;i<n;i++){
        debug::init();
        sol::solve();
    }
    if(debug::flag){
        cout<<sol::ques_count<<endl;
    }
}