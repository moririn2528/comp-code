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
        if(i)os<<",";
        os<<"\""<<v1[i]<<"\"";
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

    P getend(string& sa, int l, int r, string sb, vector<char>& marks,bool mark){
        int t=0;
        int fir=0;
        vector<int> v1;
        for(int i=l;i<r;i++){
            if(sa[i]==sb[t]){
                if(t==0)fir=i;
                t++;
                v1.push_back(i);
            }
            if(t==sb.size()){
                if(mark){
                    for(auto a:v1)marks[a]=1;
                }
                return P(fir,i+1);
            }
        }
        return P(-1,-1);
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa,sb;
        vector<string> vs;
        for(k=0;k<3;k++){
            cin>>sa;
            sa.erase(sa.begin());
            if(sa.back()==',')sa.pop_back();
            sa.pop_back();
            n=sa.size();
            vector<P> v1,v2;
            vector<char> mark(n);
            for(a=0;a<n;){
                P p=getend(sa,a,sa.size(),"SABA",mark,false);
                if(p.first==-1)break;
                v1.push_back(p);
                a=p.second;
            }
            for(a=0;a<n;){
                P p=getend(sa,a,sa.size(),"kobone",mark,false);
                if(p.first==-1)break;
                v2.push_back(p);
                a=p.second;
            }
            c=0;
            for(auto p :v2){
                for(auto r: v1){
                    if(r.first<=p.first && p.second<=r.second){
                        getend(sa,p.first,p.second,"kobone",mark,true);
                        break;
                    }
                }
            }
            sb.clear();
            for(i=0;i<n;i++){
                if(!mark[i])sb.push_back(sa[i]);
            }
            vs.push_back(sb);
        }
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}