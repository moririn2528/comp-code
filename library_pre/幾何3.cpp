#include<bits/stdc++.h>
using namespace std;

namespace geometory{
	const double eps=1e-9;
}

template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}

template<typename T> class Line{

	int sign(T a)const{
		if(abs(a)<geometory::eps)return 0;
		if(a<0)return -1;
		else return 1;
	}

public:
    complex<T> st,en;
	bool segment=true;

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

    T length()const{
        return abs(en-st);
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

	T distance(const complex<T>& point)const{
		complex<T> cl=en-st;
		T a=cl.imag(),b=-cl.real();
		T c=-(a*st.real()+b*st.imag());
		T d=abs(a*point.real()+b*point.imag()+c)/abs(cl);
		if(!segment)return d;
		return min({abs(point-st),abs(point-en),d});
	}

	bool in(const complex<T>& point)const{
		return distance(point)<geometory::eps;
	}

	bool different_side(const complex<T>& p1,const complex<T>& p2)const{
		return sign(cross_product(en-st,p1-st))*sign(cross_product(en-st,p2-st))==-1;
	}
	bool different_side(const Line& line)const{
		return different_side(line.st,line.en);
	}

	int is_cross(const Line& line)const{
		//0: not cross
		//1: cross outside
		//2: cross end point
		//3: cross inside
		if(is_parallel(line))return 0;
		if(in(line.st) || in(line.en))return 2;
		if(line.in(st) || line.in(en))return 2;
		if(different_side(line) && line.different_side(st,en)){
			return 3;
		}
		return 1;
	}

	T distance(const Line& line)const{
		if(is_cross(line)>=2)return 0;//want to change when use straight line
		if(!line.segment)return min(line.distance(st),line.distance(en));
		return min(distance(line.st),distance(line.en));
	}

	complex<T> cross_point(const Line& line)const{
		assert(!is_parallel(line));
		complex<T> d=direction();
		T a=cross_product(d,line.st-st)/cross_product(d,line.en-line.st);
		return line.st-(line.en-line.st)*a;
	}
};