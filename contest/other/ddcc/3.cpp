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

    int solve(istringstream is){
        int n,m;
        int i,j,k;
        int a,b,c;
        int c1,c2;
        int hp1,hp2;
        int at;
        const int N=100;
        vector<int> dam(N);
        is>>c1>>c2;
        is>>hp1>>hp2;
        is>>at>>dam;
        int dif_hp=-hp1+1;
        int s=1e9;
        for(i=0;i<N;i++){
            if(i>0){
                dif_hp+=dam[i-1];
            }
            if(2*(i+1)*at<hp2)continue;
            a=(hp2-1)/at+1-(i+1);
            if(a<0)a=0;
            else a*=c1;
            a+=max(dif_hp,0)*c2;
            s=min(s,a);
        }
        return s;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n,i;
    sol::init();
    vector<int> vs;
    for(i=0;i<3;i++){
        string sa;
        cin>>sa;
        sa.erase(sa.begin());
        if(sa.back()==',')sa.pop_back();
        sa.pop_back();
        for(auto& ca:sa){
            if(ca==',')ca=' ';
        }
        vs.push_back(
            sol::solve(istringstream(sa))
        );
    }
    cout<<vs<<endl;
}