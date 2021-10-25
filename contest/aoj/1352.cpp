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

#include<bits/stdc++.h>
using namespace std;

namespace geometory{
	const double eps=1e-9;
	const double pi=acos(-1);
}

template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}

template<typename T> class Line{
protected:
	int sign(T a)const{
		if(abs(a)<=geometory::eps)return 0;
		if(a<0)return -1;
		else return 1;
	}

public:
    complex<T> st,en;

	Line(){}
	Line(complex<T> a,complex<T> b):st(a),en(b){}
	Line(T x1,T y1,T x2,T y2){
		st=complex<T>(x1,y1);
		en=complex<T>(x2,y2);
	}
	Line(pair<T,T> p1,pair<T,T> p2){
		st=complex<T>(p1.first,p1.second);
		en=complex<T>(p2.first,p2.second);
	}

	complex<T> direction()const{
		complex<T> a=en-st;
		return a/abs(a);
	}

	complex<T> mirror(const complex<T> pos)const{
		complex<T> dir=direction();
		complex<T> a=pos-st;
		complex<T> b=2*inner_product(dir,a)*dir;
		return st+b-a;
	}

	Line mirror(const Line& line)const{
		return Line(mirror(line.st),mirror(line.en));
	}

	int is_parallel(const Line& line)const{
		//0: not parallel
		//1: parallel without direction
		//2: parallel with direction
		complex<T> c1=en-st,c2=line.en-line.st;
		if(abs(cross_product(c1,c2))>abs(c1)*abs(c2)*geometory::eps)return 0;
		if(inner_product(c1,c2)>0)return 2;
		else return 1;
	}

	virtual T distance(const complex<T>& point)const{
		complex<T> cl=en-st;
		T a=cl.imag(),b=-cl.real();
		T c=-(a*st.real()+b*st.imag());
		T d=abs(a*point.real()+b*point.imag()+c)/abs(cl);
		return d;
	}

	bool in(const complex<T>& point)const{
		return distance(point)<=geometory::eps;
	}

	bool different_side(const complex<T>& p1,const complex<T>& p2)const{
		return sign(cross_product(en-st,p1-st))*sign(cross_product(en-st,p2-st))==-1;
	}
	bool different_side(const Line& line)const{
		return different_side(line.st,line.en);
	}

	virtual T distance(const Line& line)const{
		if(is_parallel(line))return distance(line.st);
		return 0;
	}

	virtual complex<T> cross_point(const Line& line)const{
		assert(!is_parallel(line));
		complex<T> d=direction();
		T a=cross_product(d,line.st-st)/cross_product(d,line.en-line.st);
		return line.st-(line.en-line.st)*a;
	}
};

template<typename T> class SegLine: public Line<T>{
	using Line<T>::Line;
	using Line<T>::st;
	using Line<T>::en;
	using Line<T>::sign;
public:

    T length()const{
        return abs(en-st);
    }

	T distance(const complex<T>& point)const override{
		if(sign(cross_product(en-st,point-st))*sign(cross_product(en-st,point-en))==-1){
			return Line<T>::distance(point);
		}
		return min(abs(point-st),abs(point-en));
	}

	int is_cross(const Line<T>& line)const{
		//0: not cross
		//1: cross end point
		//2: cross inside
		if(this->is_parallel(line))return 0;
		if(line.in(st) || line.in(en))return 1;
		if(line.different_side(st,en))return 2;
		return 0;
	}
	int is_cross(const SegLine& line)const{
		if(this->is_parallel(line))return 0;
		if(line.in(st) || line.in(en))return 1;
		if(in(line.st) || in(line.en))return 1;
		if(line.different_side(st,en) && different_side(line))return 2;
		return 0;
	}

	T distance(const Line<T>& line)const override{
		if(is_cross(line))return 0;
		min(line.distance(st),line.distance(en));
	}
	T distance(const SegLine& line)const{
		if(is_cross(line))return 0;
		min(distance(line.st),distance(line.en));
	}

	complex<T> cross_point(const Line<T>& line)const override{
		assert(is_cross(line));
		return Line<T>::cross_point(line);
	}
	complex<T> cross_point(const SegLine& line)const{
		assert(is_cross(line));
		return Line<T>::cross_point(line);
	}
};

template<typename T> class Circle{
	typedef complex<T> C;
	T area(T a,T b,T c){
		T s=(a+b+c)/2;
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
	T area_direc(T base,T to,T c,bool upside){
		T s=area(base,to,c);
		T ang=asin(s*2/base/to);
		if(pow(base,2)+pow(to,2)<pow(c,2))ang=geometory::pi-ang;
		if(!upside)ang=-ang;
		return polar(to,ang)/base;
	}


public:
	complex<T> p;
	T r;
	Circle(complex<T> _p,T _r):p(_p),r(_r){}
	Circle(T x,T y,T _r):p(x,y),r(_r){}

	int is_cross(const Circle& c)const{
		//s: cross s point
		using geometory::eps;
		T dis=abs(c.p-p);
		if(abs(dis-abs(r-c.r))<=eps || abs(r+c.r-dis)<=eps)return 1;
		if(abs(r-c.r)<dis && dis<r+c.r)return 2;
		return 0;
	}
	int is_cross(const Line<T>& line)const{
		if(abs(line.disrance(p)-r)<geometory::eps)return 1;
		if(abs(line.disrance(p))<r)return 2;
		return 0;
	}
	int is_cross(const SegLine<T>& line)const{
		if(abs(line.disrance(p)-r)<geometory::eps)return 1;
		if(r<abs(line.disrance(p)))return 0;
		if(abs(p-line.st)<r || abs(p-line.en)<r)return 1;
		return 2;
	}

	int in(const Circle& c)const{
		// c in *this
		//1: touch edge
		//2: completely inner side
		T d=abs(c.p-p);
		if(abs(d-(r-c.r))<=geometory::eps)return 1;
		if(d<(r-c.r))return 2;
		return 0;
	}
	int in(const complex<T>& point)const{
		if(abs(abs(point-p)-r)<=geometory::eps)return 1;
		if(abs(point-p)<r)return 2;
		return 0;
	}
	
	vector<complex<T>> cross_point(const Line<T>& line)const{
		vector<complex<T>> vs;
		if(!is_cross(line))return vs;
		C cd=(line.en-line.st)*C(0,1);
		cd*=r/abs(cd);
		if(SegLine(p,p+cd).is_cross(line)==0)cd=-cd;
		T d=line.distance(p);
		T ang=acos(d/r);
		if(ang<=geometory::eps){
			vs.push_back(cd);
			return vs;
		}
		C ca=polar(1,ang);
		vs.push_back(cd*ca),vs.push_back(cd/ca);
		return vs;
	}
	vector<complex<T>> cross_point(const Circle& c)const{
		vector<complex<T>> vs;
		int cr=is_cross(c);
		if(cr==0)return vs;
		C cd=c.p-p;
		if(cr==1){
			vs.push_back(cd/abs(cd)*r);
			return vs;
		}
		vs.push_back(p+cd*area_direc(abs(cd),r,c.r,true));
		vs.push_back(p+cd*area_direc(abs(cd),r,c.r,false));
		return vs;
	}

    complex<T> cross1point(const Line<T>& line)const{
        assert(is_cross(line)==1);
        vector<complex<T>> vs=cross_point(line);
        return vs[0];
    }
    complex<T> cross1point(const Circle& c)const{
        assert(is_cross(c)==1);
        vector<complex<T>> vs=cross_point(c);
        return vs[0];
    }

	vector<Line<T>> tangent_line(Circle& c)const{
		vector<Line<T>> vs;
		int cr=is_cross(c);
		if(cr==1){
			vector<C> vc=cross_point(c);
			assert(vc.size()==1);
			C ca=(vc[0]-p)*C(0,1);
			vs.push_back(Line<T>(vc[0],vc[0]+ca));
		}
		if(c.in(*this) || in(c))return vs;
		C cd=c.p-p;
		T ang=acos(abs(c.r-r)/abs(cd));
		if(r<c.r)cd=-cd;
		cd/=abs(cd);
		for(int i=-1;i<=1;i+=2){
			C dir=cd*polar(1,i*ang);
			vs.push_back(Line<T>(p+dir*r,c.p+dir*c.r));
		}
		if(is_cross(c))return vs;
		cd=c.p-p;
		ang=acos((c.r+r)/abs(cd));
		cd/=abs(cd);
		for(int i=-1;i<=1;i+=2){
			C dir=cd*polar(1,i*ang);
			vs.push_back(Line<T>(p+dir*r,c.p-dir*c.r));
		}
		return vs;
	}
	vector<Line<T>> tangent_line(complex<T>& point)const{
		vector<Line<T>> vs;
		if(in(point)==2)return vs;
		if(in(point)==1){
			vs.push_back(Line<T>(point,point+(point-p)*C(0,1)));
			return vs;
		}
		C cd=p-point;
		T ang=asin(r/abs(cd));
		for(int i=-1;i<=1;i+=2){
			C dir=cd/abs(cd)*polar(1.0,i*ang);
			vs.push_back(Line<T>(point,point+inner_product(cd,dir)*dir));
		}
		return vs;
	}
};

namespace sol{
    typedef pair<double,double> DP;
    typedef complex<double> C;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        double r=100;
        double gx,gy;
        cin>>n;
        cin>>gx>>gy;
        vector<DP> vp;
        vector<Circle<double>> vc;
        for(i=0;i<n;i++){
            cin>>a>>b;
            vp.push_back({a,b});
            vc.push_back(Circle<double>(a,b,r));
        }
        int cnt=2;
        vector<C> vpp;
        vector<tuple<int,int,double>> vq;
        vector<Line<double>> va;
        vpp.push_back(C(0,0));
        vpp.push_back(C(gx,gy));
        for(i=0;i<n;i++){
            for(j=0;j<2;j++){
                if(vc[i].in(vpp[j]))continue;
                va=vc[i].tangent_line(vpp[i]);
                for(Line<double>& l:va){
                    SegLine<double> p(vpp[i],vc[i].cross1point(l));
                    for(k=0;k<n;k++){
                
                    }
                }
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}