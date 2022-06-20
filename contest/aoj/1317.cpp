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
    const int N=26;
    vector<int> vt;
    vector<string> v1,v2;
    vector<char> used;
    vector<int> used2;

    bool check(string sa,string sb,int p){
        if(sa.size()!=sb.size())return false;
        for(int i=0;i<sa.size();i++){
            int a=sa[i]-'A',b=sb[i]-'A';
            if(vt[a]==-1 && vt[b]==-1){
                vt[a]=b,vt[b]=a;
                used2[a]=p,used2[b]=p;
            }
            if(vt[a]!=b || vt[b]!=a)return false;
        }
        return true;
    }

    void check_rev(int p){
        for(int i=0;i<N;i++){
            if(used2[i]==p)used2[i]=-1,vt[i]=-1;
        }
    }

    int dfs(int pos,int max_cnt){
        if(pos==v2.size())return 1;
        int s=0;
        for(int i=0;i<v1.size();i++){
            if(used[i])continue;
            if(!check(v1[i],v2[pos],pos)){
                check_rev(pos);
                continue;
            }
            s+=dfs(pos+1,max_cnt);
            if(s>=max_cnt)return s;
            check_rev(pos);
        }
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        while(cin>>n){
            if(n==0)return;
            v1.resize(n);
            cin>>v1;
            string sa,sb;
            vector<int> va;
            vector<string> vs;
            bool flag=false;
            v2.clear();
            while(cin>>sa){
                if(sa.back()=='.'){
                    sa.pop_back();
                    flag=true;
                }
                vs.push_back(sa);
                for(j=0;j<v2.size();j++){
                    if(v2[j]==sa){
                        break;
                    }
                }
                if(j==v2.size())v2.push_back(sa);
                if(flag)break;
            }
            auto cnt=[](string s1){
                vector<char> v(N,0);
                int s=0;
                for(int i=0;i<s1.size();i++){
                    int a=s1[i]-'A';
                    if(!v[a])v[a]=1,s++;
                }
                return s;
            };
            sort(v2.begin(),v2.end(),[&](string s1,string s2){
                return cnt(s1)>cnt(s2);
            });
            used.assign(v1.size(),0);
            used2.assign(N,-1);
            vt.assign(N,-1);
            a=dfs(0,2);
            if(a>=2){
                cout<<"-."<<endl;
                continue;
            }
            dfs(0,1);
            for(auto& s:vs){
                for(auto& ca:s){
                    a=ca-'A';
                    ca='A'+vt[a];
                }
            }
            cout<<vs<<"."<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}