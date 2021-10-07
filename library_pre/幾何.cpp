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
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,int> LP;
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

class GeometryBase{
public:
    typedef long double type;
    const type eps=1e-9;
};

class Vector;

class Point: public GeometryBase{
    complex<type> point;
public:
    Point():point(0){}
    Point(type a,type b){
        point.real(a),point.imag(b);
    }
    Point(complex<type> _point):point(_point){}

    complex<type> get_complex() const{
        return point;
    }

    type distance(Point pa) const{
        return abs(pa.get_complex()-point);
    }

    void print() const{
        cout<<"Point:"<<point.real()<<" "<<point.imag()<<endl;
    }

    bool in_range(type x1,type y1,type x2,type y2) const{
        assert(x1<=x2 && y1<=y2);
        if(x1-eps<point.real() && y1-eps<point.imag() && point.real()<x2+eps && point.imag()<y2+eps){
            return true;
        }else return false;
    }

    Point& operator = (complex<type> comp){
        point=comp;
        return *this;
    }

    Point operator -() const{
        return Point(-point);
    }

    Point& operator += (Vector vec);
    Point& operator -= (Vector vec);
    Point operator + (Vector vec);
    Point operator - (Vector vec);
};

class Vector: public GeometryBase{
    complex<type> vec;
    type dis=-1;
public:
    Vector(type x,type y){
        vec.real(x),vec.imag(y);
        dis=abs(vec);
    }
    Vector(Point start_point,Point end_point){
        vec=end_point.get_complex()-start_point.get_complex();
        dis=abs(vec);
    }
    Vector(complex<type> _vec):vec(_vec){
        dis=abs(vec);
    }

    complex<type> get_complex() const{
        return vec;
    }
    type get_dis() const{
        return dis;
    }

    type inner_product(Vector vec2_class) const{
        complex<type> vec2=vec2_class.get_complex();
        return vec.real()*vec2.real()+vec.imag()*vec2.imag();
    }

    type cross_product(Vector vec2_class) const{
        complex<type> vec2=vec2_class.get_complex();
        return vec.real()*vec2.imag()-vec.imag()*vec2.real();
    }

    bool similar(Vector vec2_class) const{
        complex<type> vec2=vec2_class.get_complex();
        if(abs(vec.real()*vec2.imag()-vec.imag()*vec2.real())<eps)return true;
        else return false;
    }

    Vector& rotate(type theta){
        complex<type> rot=polar((type)1.0,theta);
        vec*=rot;
        return *this;
    }

    Vector& rotate90(){
        vec=complex<type>(-vec.imag(),vec.real());
        return *this;
    }

    Vector& set_distance(type _dis){
        dis=abs(vec);
        assert(dis>0);
        type scale=_dis/dis;
        vec*=scale;
        return *this;
    }

    void print() const{
        cout<<"Vector:"<<vec.real()<<" "<<vec.imag()<<endl;
    }

    Vector operator -() const{
        return Vector(-vec);
    }
};

Point& Point::operator += (Vector vec){
    point+=vec.get_complex();
    return *this;
}
Point& Point::operator -= (Vector vec){
    point-=vec.get_complex();
    return *this;
}
Point Point::operator + (Vector vec){
    Point _point=*this;
    _point+=vec;
    return _point;
}
Point Point::operator - (Vector vec){
    Point _point=*this;
    _point-=vec;
    return _point;
}

class SegmentLine: public GeometryBase{
public:
    Point start_point,end_point;

    SegmentLine():start_point(),end_point(){}
    SegmentLine(Point _start_point,Point _end_point):start_point(_start_point),end_point(_end_point){}
    SegmentLine(Point _start_point,Vector _vec):start_point(_start_point){
        end_point=_start_point.get_complex()+_vec.get_complex();
    }

    Vector get_vec() const{
        return Vector(start_point,end_point);
    }

    bool is_cross(SegmentLine segline) const{
        Vector line_vec=get_vec();
        type da=line_vec.cross_product(Vector(start_point,segline.start_point));
        type db=line_vec.cross_product(Vector(start_point,segline.end_point));
        if(da*db>=0)return false;//////////////////////
        da=segline.get_vec().cross_product(Vector(segline.start_point,start_point));
        db=segline.get_vec().cross_product(Vector(segline.start_point,end_point));
        if(da*db>=0)return false;/////////////////////////////
        else return true;
    }

    Point internally_dividing_point(type da,type db) const{
        return Point((start_point.get_complex()*db+end_point.get_complex()*da)/(da+db));
    }

    Point cross_point(SegmentLine segline) const{
        if(is_cross(segline))return Point();
        Vector line_vec(start_point,end_point);
        type da=line_vec.cross_product(Vector(start_point,segline.start_point));
        type db=line_vec.cross_product(Vector(start_point,segline.end_point));
        if(da*db>0)return Point();
        return segline.internally_dividing_point(abs(da),abs(db));
    }

    void print() const{
        cout<<"SegmentLine"<<endl;
        cout<<"Start";
        start_point.print();
        cout<<"End";
        end_point.print();
    }

};

class Line: public GeometryBase{
    Vector vec;
    Point point;
public:

    Line(Point _start_point,Point _end_point):vec(_start_point,_end_point),point(_start_point){}
    Line(Vector _vec,Point _point):vec(_vec),point(_point){}

    Vector get_vec() const{
        return vec;
    }
    Point get_point() const{
        return point;
    }

    bool similar(Line line) const{
        return vec.similar(line.get_vec());
    }

    Point cross_point(Line line) const{
        if(similar(line))return Point();
        complex<type> ca,cb,cc;
        ca=vec.get_complex(),cb=-line.get_vec().get_complex();
        cc=line.get_point().get_complex()-point.get_complex();
        //ca s + cb t = cc
        //s = db/da
        type da=ca.real()*cb.imag()-ca.imag()*cb.real();
        type db=cc.real()*cb.imag()-cc.imag()*cb.real();
        assert(da!=0);
        type s=db/da;
        return Point(point.get_complex()+ca*s);
    }

    type distance(Point pt){
        Vector vec2=vec;
        vec2.rotate90();
        type a=vec2.get_complex().real(),b=vec2.get_complex().imag();
        type c=a*point.get_complex().real()+b*point.get_complex().imag();
        return abs(a*pt.get_complex().real()+b*pt.get_complex().imag()-c)/vec.get_dis();
    }

    void print(){
        cout<<"Line"<<endl;
        vec.print();
        point.print();
    }

    bool is_cross2(Point pt1,Point pt2) const{
        type da=vec.cross_product(Vector(point,pt1));
        type db=vec.cross_product(Vector(point,pt2));
        if(da*db>=0)return false;
        else return true;
    }
};

