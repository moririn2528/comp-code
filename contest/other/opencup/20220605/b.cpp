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

    vector<P> vp;
    
    void assign(string& sa,vector<int>& poss){
        if(vp.empty() || vp[0].first==0)return;
        if(poss.empty())return;
        if(poss.size()<=2 || (poss.size()==3 && vp[0].first==1)){
            for(int i=0;i<poss.size() && i<vp.size();i++){
                if(vp[i].first==0)continue;
                int p=poss[i];
                sa[p]=vp[i].second+'a';
                vp[i].first--;
            }
        }else{
            for(int i=0;i<3;i++){
                int p=poss[i];
                int j=i%2;
                if(vp.size()<=j)continue;
                if(vp[j].first==0)continue;
                sa[p]=vp[j].second+'a';
                vp[j].first--;
            }
        }
        sort(vp.rbegin(),vp.rend());
    }

    void assign(vector<string>& vs,int sz){
        int i,j,k;
        for(i=0;i<vs.size();i++){
            vector<int> poss;
            for(j=0;j<vs[i].size();j++){
                if(vs[i][j]=='X'){
                    if(poss.size()==sz)assign(vs[i],poss);
                    poss.clear();
                    continue;
                }
                poss.push_back(j);
            }
            if(poss.size()==sz)assign(vs[i],poss);
        }
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa,sb;
        cin>>n;
        vector<string> v1,v2;
        for(i=0;i<n;i++){
            cin>>sa>>sb;
            v1.push_back(sa);
            v2.push_back(sb);
        }
        cin>>m;
        for(i=0;i<m;i++){
            cin>>a;
            vp.push_back({a,i});
        }
        sort(vp.rbegin(),vp.rend());
        for(i=3;i>0;i--){
            assign(v1,i);
            assign(v2,i);
        }
        if(!vp.empty() && vp[0].first>0){
            cout<<"NO"<<endl;
            return;
        }
        cout<<"YES"<<endl;
        for(i=0;i<n;i++){
            cout<<v1[i]<<" "<<v2[i]<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}