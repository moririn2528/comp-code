template<typename T>T ext_gcd(T a,T b,T& x,T& y){
    //ax+by=gcd(a,b)
    if(a<b)return ext_gcd(b,a,y,x);
    if(b==0){
        x=1,y=0;
        return a;
    }
    T gcd_val=ext_gcd(b,a%b,x,y);
    swap(x,y);
    y-=x*(a/b);
    if(x>b)y+=(x/b)*a,x%=b;
    if(y>a)x+=(y/a)*b,y%=a;
    return gcd_val;
}

class modint_variable{
private:
    using mint=modint_variable;
    typedef long long int ll;
    const ll mod;
    const bool prime;
    ll val;

    ll gcd(ll a,ll b){
        if(a<b)swap(a,b);
        if(b==0)return a;
        return gcd(b,a%b);
    }
public:
    modint_variable(const ll _mod,const bool _p):mod(_mod),prime(_p),val(0){}
    modint_variable(const ll _mod,const bool _p,const ll v):mod(_mod),prime(_p),val(v){}
    modint_variable(mint&& a)=default;
    modint_variable(const mint& a)=default;

    ll value()const{return val;}
    ll get_mod()const{return mod;}

    mint& operator++(){
        val++;
        if(val==mod)val=0;
        return *this;
    }
    mint operator++(int){
        mint ans=*this;
        ++*this;
        return ans;
    }
    mint& operator--(){
        if(val==0)val=mod;
        val--;
        return *this;
    }
    mint operator--(int){
        mint ans=*this;
        --*this;
        return ans;
    }

    mint& operator=(const ll a){
        val=a;
        if(val<0)val+=((-val)/mod+1)*mod;
        if(val>=mod)val%=mod;
        return *this;
    }

    mint& operator+=(const mint& a){
        val+=a.value();
        if(val>=mod)val-=mod;
        return *this;
    }
    mint& operator-=(const mint& a){
        val-=a.value();
        if(val<0)val+=mod;
        return *this;
    }
    mint& operator*=(const mint& a){
        val*=a.value();
        if(val>=mod)val%=mod;
        return *this;
    }

    mint pow(ll index)const{
        assert(index>=0);
        if(prime && index>=mod-1)index%=mod-1;
        mint a=*this,ans=*this;
        ans=1;
        for(ll i=1;i>=0 && i<=index;i<<=1){
            if(index&i)ans*=a;
            a*=a;
        }
        return ans;
    }

    mint inverse()const{
        if(prime){
            assert(val!=0);
            return pow(mod-2);
        }
        ll x,y;
        ll g=ext_gcd<ll>(val,mod,x,y);
        assert(g==1);
        return mint(mod,prime,g);
    }

    mint& operator/=(const mint& a){
        if(prime){
            *this*=a.inverse();
            return *this;
        }
        ll g=gcd(val,a.value());
        mint a2=*this;
        a2=a.value()/g;
        val/=g;
        *this*=a2.inverse();
        return *this;
    }

    friend mint operator-(const mint& a,const mint& b){return (mint)a-=b;}
    friend mint operator+(const mint& a,const mint& b){return (mint)a+=b;}
    friend mint operator*(const mint& a,const mint& b){return (mint)a*=b;}
    friend mint operator/(const mint& a,const mint& b){return (mint)a/=b;}
    friend bool operator==(const mint& a,const mint& b){return a.value()==b.value();}
    friend bool operator!=(const mint& a,const mint& b){return a.value()!=b.value();}
    
    friend mint pow(const mint& a,const ll b){return a.pow(b);}

    mint operator+() const{return *this;}
    mint operator-() const{return mint(mod,prime)-*this;}

    friend ostream& operator<<(ostream& os,const mint& a){
        os<<a.value();
        return os;
    }
    friend istream& operator>>(istream& is,mint& a){
        ll val;
        is>>val;
        a=val;
        return is;
    }
};

//要改造
//mint*int などができない