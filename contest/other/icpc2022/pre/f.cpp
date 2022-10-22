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

    void init(){
        
    }

    int sum(vector<int>& v1){
        int s=0;
        for(auto a:v1){
            s+=a;
        }
        return s;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa,sb;
        cin>>sa;
        vector<vector<int>> v1={vector<int>()};
        vector<int> va(sa.size()+2),vb(sa.size()+2);
        a=0,b=0;
        for(i=0;i<sa.size();i++){
            if(sa[i]=='?'){
                va[a+1]=i;
                i++;
                if(b)v1[a].push_back(b);
                b=0;
                a++;
                if(v1.size()==a)v1.push_back(vector<int>());
                continue;
            }
            if(sa[i]==')'){
                c=b+sum(v1[a])-1;
                v1[a].clear();
                if(c<=0){
                    vb[va[a]]++;
                    vb[i+1]--;
                    b=0;
                }else b=c;
                a--;
                continue;
            }
            b++;
        }
        for(i=0;i<sa.size();i++){
            vb[i+1]+=vb[i];
            if(vb[i]==0)sb.push_back(sa[i]);
        }
        sa=sb;
        n=sa.size();
        m=b+sum(v1[0]);
        priority_queue<char,vector<char>,greater<char>> q1;
        sb.clear();
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                if(sa[j]=='?'){
                    a++;
                    j++;
                    continue;
                }
                if(sa[j]==')')continue;
                q1.push(sa[j]);
                a--;
                if(a<0){
                    a++;
                    sb.push_back(q1.top());
                    q1.pop();
                }
            }
        }
        cout<<sb<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    cin>>n;
    for(i=0;i<n;i++){
        sol::solve();
    }
}