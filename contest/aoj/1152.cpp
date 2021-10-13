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

vector<P> tree;
vector<string> str;
vector<set<string>> vs;
vector<double> vsim;

void read(string& sa,int& x,int id){
    assert(x<sa.size());
    if(sa[x]=='x'){
        x++;
        return;
    }
    assert(sa[x]=='(');
    x++;
    int a=tree.size();
    tree.push_back({-1,-1});
    read(sa,x,a);
    tree[id].first=a;
    assert(sa[x]==' ');
    x++;
    a=tree.size();
    tree.push_back({-1,-1});
    read(sa,x,a);
    assert(sa[x]==')');
    tree[id].second=a;
    x++;
}

int check(int x,int y,bool xl,bool yl){
    if(vsim[x]<vsim[y])return 1;
    if(vsim[x]>vsim[y])return -1;
    if(tree[x].first==-1 && tree[y].first==-1)return 0;
    int xa,xb,ya,yb;
    bool xal,yal;
    if(xl)xa=tree[x].first,xal=true;
    else xa=tree[x].second,xal=false;
    if(yl)ya=tree[y].first,yal=true;
    else ya=tree[y].second,yal=false;
    xb=tree[x].first+tree[x].second-xa;
    yb=tree[y].first+tree[y].second-ya;
    int s=check(xa,ya,xal,yal);
    if(s)return s;
    return check(xb,yb,!xal,!yal);
}

void swap_tree(int x){
    if(tree[x].first==-1)return;
    swap(tree[x].first,tree[x].second);
    swap_tree(tree[x].first);
    swap_tree(tree[x].second);
}

int dfs(int x,bool left=true){
    if(tree[x].first==-1){
        str[x]="0";
        vs[x].insert("0");
        return 0;
    }
    int a=tree[x].first,b=tree[x].second;
    int t=max(dfs(a,true),dfs(b,false))+1;
    string sa=str[a],sb=str[b];
    if(sa>sb)swap(sa,sb);
    str[x]=sa+","+to_string(t)+","+sb;
    for(string sa:vs[a])vs[x].insert(sa);
    for(string sa:vs[b])vs[x].insert(sa);
    int cnt=0;
    for(string sa:vs[a]){
        if(vs[b].find(sa)!=vs[b].end())cnt++;
    }
    vsim[x]=(double)cnt/vs[x].size();
    vs[x].insert(str[x]);
    int s=check(a,b,true,false);
    if((left && s==-1)||(!left && s==1))swap_tree(x);
    return t;
}

string tree2str(int x){
    if(tree[x].first==-1)return "x";
    return "("+tree2str(tree[x].first)+" "+tree2str(tree[x].second)+")";
}

namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa;
        while(getline(cin,sa)){
            if(sa=="0")return;
            a=0;
            tree.clear();
            tree.push_back({-1,-1});
            read(sa,a,0);
            n=tree.size();
            str.assign(n,"");
            vs.assign(n,set<string>());
            vsim.assign(n,0);
            dfs(0);
            cout<<tree2str(0)<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}