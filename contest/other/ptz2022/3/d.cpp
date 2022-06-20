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

namespace sol{

    void init(){
        
    }

    int query(int x1,int y1,int x2, int y2){
        cout<<"? "<<x1+1<<" "<<y1+1<<" "<<x2<<" "<<y2<<endl;
        int s;
        cin>>s;
        return s;
    }
    void answer(int x,int y){
        cout<<"! "<<x+1<<" "<<y+1<<endl;
    }

    P overlap(P a,P b){
        return P(max(a.first,b.first),min(a.second,b.second));
    }
    P except(P a,P b){
        P c=overlap(a,b);
        assert(c.first==a.first || c.second==a.second);
        if(a.first==c.first){
            return P(c.second,a.second);
        }else{
            return P(a.first,c.first);
        }
    }
    int size(P x){
        return x.second-x.first;
    }

    void check(int x1,int y1,int x2,int y2,P& px, P& py){
        assert(x2-x1!=y2-y1);
        int s=query(x1,y1,x2,y2);
        P x(x1,x2),y(y1,y2);
        if(y2-y1>1){
            if(s==0 || s==x2-x1)px=except(px,x);
            else px=overlap(px,x);
        }
        if(x2-x1>1){
            if(s==0 || s==y2-y1)py=except(py,y);
            else py=overlap(py,y);
        }
    }
    

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int x,y;
        cin>>n>>m;
        P px(0,n),py(0,m);
        a=max(n/2,2),b=max(m/2,2);
        if(a==b){
            if(n<m)b++;
            else a++;
        }
        check(0,0,a,b,px,py);
        int cnt=1;
        for(i=0;i<2;i++){
            if(size(px)<=2 && size(py)<=2)break;
            cnt++;
            a=max(size(px)/2,2),b=max(size(py)/2,2);
            int x1=min(px.first,n-a),y1=min(py.first,m-b);
            if(a==b){
                if(x1>0)x1--,a++;
                else if(px.second<n)x1=max(px.second-a,0),a++;
                else if(y1>0)y1--,b++;
                else y1=max(py.second-b,0),b++;
            }
            check(x1,y1,x1+a,y1+b,px,py);
        }
        assert(size(px)<=2 && size(py)<=2);
        if(n<6 && m<6){
            assert(cnt<=2);
            check(px.first,0,px.first+1,m,px,py);
            check(0,py.first,n,py.first+1,px,py);
        }else{
            a=3,b=2;
            if(n<6)swap(a,b);
            x=px.first-a+1,y=py.first-b+1;
            if(x<0)x=px.second-1;
            if(y<0)y=py.second-1;
            check(x,y,x+a,y+b,px,py);
        }
        assert(size(px)==1 && size(py)==1);
        answer(px.first,py.first);
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