template<typename T> vector<complex<T>> fft(vector<complex<T>>& vx,int sign){
    //DFT: X-array = fft(x-array,-1)
    const T pi=acosl(-1);
    int i,j,k;
    int N=vx.size();
    int n;
    int a,b;
    for(n=0;(1<<n)<(int)vx.size();n++);
    assert((int)vx.size()==1<<n);
    vector<complex<T>> vs(1<<n);
    complex<T> x,y,w;
    for(i=0;i<N;i++){
        for(j=0,k=0;j<n;j++){
            if(i&1<<j)k|=1<<(n-j-1);
        }
        vs[k]=vx[i];
    }
    for(i=0;i<n;i++){
        for(j=0;j<N;j++){
            if(j&1<<i)continue;
            x=vs[j],y=vs[j|1<<i];
            a=1<<(i+1);
            b=j&((1<<i)-1);
            w=polar(1.0,sign*2*pi*b/a);
            vs[j]=x+w*y;
            vs[j|1<<i]=x-w*y;
        }
    }
    return vs;
}