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

template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}


template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}


template<typename T> class Polygon{
	typedef complex<T> C;
public:
	vector<C> points;

    void order(){
        if(points.size()<=2)return;
        C d1,d2;
        int n=points.size();
        d1=points[0]-points[n-1];
        int s=0;
        for(i=0;i<n;i++,d1=d2){
            j=(i+1)%n;
            d2=points[j]-points[i];
            bool positive=(cross_product(d1,d2)>0);
            T y1=d1.imag(),y2=d2.imag();
            if((y1<=0 && y2>0) || (y1>0 && y2<=0)){
                if(positive)s++;
                else s--;
            }
        }
        assert(s!=0);
        if(s<0)reverse(points.begin(),points.end());
    }

	Polygon(vector<C>& p,bool ordered=false){
		points=p;
		if(!ordered)order();
	}
	Polygon(vector<pair<T,T>>& p,bool ordered=false){
        points.clear();
		for(auto pa:p){
			points.push_back(C(pa.first,pa.second));
		}
		if(!ordered)order();
	}

    template<typename TP> TP area(){
        TP s=0;
        for(i=1;i+1<(int)points.size();i++){
            C ca=points[i]-points[0];
            C cb=points[i+1]-points[0];
            s+=cross_product(ca,cb);
        }
        return abs(s)/2;
    }

    bool in(C p){
        assert(!points.empty());
        C d1,d2;
        int n=points.size();
        d1=points[n-1]-p;
        int s=0;
        for(i=0;i<n;i++,d1=d2){
            d2=points[i]-p;
            bool positive=(cross_product(d1,d2)>0);
            T y1=d1.imag(),y2=d2.imag();
            if((y1<=0 && y2>0) || (y1>0 && y2<=0)){
                if(positive)s++;
                else s--;
            }
        }
        return s!=0;
    }

    Polygon cross(Polygon& p){
        
    }
};


namespace sol{

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}