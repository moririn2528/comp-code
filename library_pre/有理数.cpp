#include<bits/stdc++.h>
using namespace std;

class Fraction{
    typedef long long int ll;
    long long int gcd(long long int a,long long int b){
        if(a<b)swap(a,b);
        if(b==0)return a;
        return gcd(b,a%b);
    }

public:
    ll x,y;
    Fraction(){};
    Fraction(ll _x, ll _y):x(_x),y(_y){
        if(x==0 && y==0)return;
        if(y<0)x=-x,y=-y;
        ll d=gcd(abs(x),abs(y));
        x/=d,y/=d;
    }
    template<typename T> Fraction(pair<T,T> p){
        Fraction(p.first,p.second);
    }

    bool operator==(const Fraction f)const{
        return x==f.x && y==f.y;
    }
    bool operator<(const Fraction f)const{
        return x*f.y<f.x*y;
    }
    bool operator<=(const Fraction f)const{
        return x*f.y<=f.x*y;
    }
    bool operator>(const Fraction f)const{return !((*this)<=f);}
    bool operator>=(const Fraction f)const{return !((*this)<f);}
};