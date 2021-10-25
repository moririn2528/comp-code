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

namespace sol{
    const int N=9;
    vector<vector<int>> path(N);
    vector<int> v1(N);
    unordered_set<LL> s1;

    LL hash(){
        LL s=0;
        for(int i=0;i<N;i++){
            s*=N;
            s+=v1[i];
        }
        return s;
    }
    
    void hash_rev(LL a){
        for(int i=N-1;i>=0;i--){
            v1[i]=a%N;
            a/=N;
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        LL a,b,c;
        cin>>m;
        for(i=0;i<m;i++){
            cin>>a>>b;
            a--,b--;
            path[a].push_back(b);
            path[b].push_back(a);
        }
        for(i=0;i<N-1;i++){
            cin>>a;
            v1[a-1]=i+1;
        }
        queue<LL> q1;
        q1.push(hash());
        s1.insert(hash());
        for(i=0;!q1.empty();i++){
            for(j=(int)q1.size()-1;j>=0;j--){
                a=q1.front();q1.pop();
                hash_rev(a);
                for(k=0;k<N-1;k++){
                    if(v1[k]!=k+1)break;
                }
                if(k==N-1){
                    cout<<i<<endl;
                    return;
                }
                for(k=0;k<N;k++){
                    if(v1[k]==0)break;
                }
                a=k;
                for(int to:path[a]){
                    swap(v1[to],v1[a]);
                    b=hash();
                    swap(v1[to],v1[a]);
                    if(s1.find(b)!=s1.end())continue;
                    s1.insert(b);
                    q1.push(b);
                }
            }
        }
        cout<<-1<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}