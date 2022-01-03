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

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c,d;
        int x,y,z;
        map<int,P> m1;
        n=1e6,m=1e6;
        string sa(n,'5'),sb(n,'4');
        vector<int> va(n),vb(n);
        scanf("%s%s",&sa,&sb);
        for(i=n-1,c=0;i>=0;i--){
            a=sa[i]-'0';
            b=sb[i]-'0';
            va[i]=a,vb[i]=b;
            m1[-i]={(a+b+c)%10,1};
            c=(a+b+c)/10;
        }
        for(i=0;i<m;i++){
            a=1,b=m-i,c=6-2*(i%2);
            b--;
            if(a==1){
                d=c-va[b];
                va[b]=c;
            }else{
                d=c-vb[b];
                vb[b]=c;
            }
            int s=2;
            auto itr=m1.lower_bound(-b);
            if(d==0){
                cout<<itr->second.first<<" "<<0<<endl;
                continue;
            }
            x=itr->second.first,y=itr->second.second;
            if(itr->first!=-b){
                z=b+(itr->first);
                itr->second.second=z;
                m1[-b]={x,y-z};
            }
            if(m1[-b].second!=1){
                m1[-b-1]={m1[-b].first,m1[-b].second-1};
                m1[-b].second=1;
            }
            m1[-b].first+=d;
            if(m1[-b].first>=10){
                m1[-b].first-=10,x=9,y=0,z=1;
            }else if(m1[-b].first<0){
                m1[-b].first+=10,x=0,y=9,z=-1;
            }else{
                cout<<m1[-b].first<<" "<<2<<endl;
                continue;
            }
            itr=m1.upper_bound(-b);
            c=-b,a=0;
            while(itr!=m1.end() && itr->second.first==x){
                a+=itr->second.second,c=itr->first;
                m1.erase(itr);
                itr=m1.upper_bound(b);
            }
            s+=a;
            if(a>0)m1[c]={y,a};
            itr=m1.upper_bound(c);
            if(itr!=m1.end()){
                s++;
                if(itr->second.second!=1){
                    itr->second.second--;
                }
                m1[c+1]={itr->second.first+z,1};
            }
            cout<<m1[-b].first<<" "<<s<<endl;
        }
    }
}

int main(){
    sol::solve();
}