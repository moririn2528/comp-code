
typedef long double type;
typedef complex<type> C;
template<typename T> T cross_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).imag();
}

template<typename T> T inner_product(complex<T> ca,complex<T> cb){
    return (conj(ca)*cb).real();
}

void convex(vector<C>& vp,C pt){
    int a,b,c;
    if(!vp.empty() && vp.back()==pt)return;
    while(vp.size()>=2){
        a=vp.size()-1;
        C ca=vp[a]-vp[a-1],cb=pt-vp[a];
        if(cross_product(ca,cb)>0)break;
        vp.pop_back();
    }
    vp.push_back(pt);
}

vector<C> convex_full(vector<P>& v){
    sort(v.begin(),v.end());
    vector<C> vs,vs2;
    int n=v.size();
    for(int i=0;i<n;i++){
        convex(vs,C(v[i].first,v[i].second));
    }
    for(int i=n-1;i>=0;i--){
        convex(vs2,C(v[i].first,v[i].second));
    }
    assert(!vs.empty());
    vs.pop_back();
    vs.insert(vs.end(),vs2.begin(),vs2.end());
    return vs;
}