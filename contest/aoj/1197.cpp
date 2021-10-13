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

class Dice{
    // 0
    //1234
    // 5
    //top:0, front:2, x:13, y:24, z:50
    static const int N=6;
    int A[N];
public:
    Dice(const vector<int> v1){
        assert(v1.size()>=N);
        for(int i=0;i<N;i++){
            A[i]=v1[i];
        }
    }

    //rotate: clockwise
    void rotateX(){//0->2->5->4->0
        swap(A[0],A[4]);
        swap(A[4],A[5]);
        swap(A[5],A[2]);
    }

    void rotateXrev(){
        swap(A[5],A[2]);
        swap(A[4],A[5]);
        swap(A[0],A[4]);
    }

    void rotateY(){//0->3->5->1
        swap(A[0],A[1]);
        swap(A[1],A[5]);
        swap(A[5],A[3]);
    }

    void rotateYrev(){
        swap(A[5],A[3]);
        swap(A[1],A[5]);
        swap(A[0],A[1]);
    }

    void rotateZ(){//1->2->3->4
        swap(A[4],A[3]);
        swap(A[3],A[2]);
        swap(A[2],A[1]);
    }

    void rotateZrev(){//1->2->3->4
        swap(A[2],A[1]);
        swap(A[3],A[2]);
        swap(A[4],A[3]);
    }

    bool check(){
        int a=0;
        for(int i=0;i<N;i++){
            if(A[i]<0)return false;
            a+=A[i];
        }
        if((A[0]+A[5])*2>a)return false;
        if((A[1]+A[3])*2-1>a)return false;
        if((A[2]+A[4])*2-1>a)return false;
        return true;
    }

    string calc(){
        string sa="ENSW",ss="";
        int i,j;
        while(1){
            for(i=0;i<4;i++){
                if(i==0)rotateX();
                if(i==1)rotateY();
                if(i==2)rotateYrev();
                if(i==3)rotateXrev();
                A[5]--;
                if(check())break;
                A[5]++;
                if(i==0)rotateXrev();
                if(i==1)rotateYrev();
                if(i==2)rotateY();
                if(i==3)rotateX();
            }
            if(A[5]<0 || i==4)return "impossible";
            ss.push_back(sa[i]);
            for(i=0;i<N;i++){
                if(A[i]>0)break;
            }
            if(i==N)return ss;
        }
    }


    template<typename T> T hash(int base){
        T s=0;
        for(int i=0;i<N;i++){
            s*=base;
            s+=A[i];
        }
        return s;
    }

    template<typename T> vector<T> all_hash(int base){
        int i,j;
        vector<T> vs;
        const int M=4;
        for(i=0;i<2*M;i++){
            if(i<M)rotateX();
            else rotateY();
            if(i>=M && i%2)continue;
            for(j=0;j<4;j++){
                rotateZ();
                vs.push_back(hash<T>(base));
            }
        }
        return vs;
    }
};


namespace sol{
    const int N=6;
    string ss;
    vector<int> v1(N);
    vector<int> vi(N,-1);

    void dfs(int d){
        int i;
        if(d<N){
            for(i=0;i<N;i++){
                if(vi[i]!=-1)continue;
                vi[i]=d;
                dfs(d+1);
                vi[i]=-1;
            }
            return;
        }
        vector<int> v2(N);
        for(i=0;i<N;i++){
            v2[vi[i]]=v1[i];
        }
        Dice dice(v2);
        string sa=dice.calc();
        if(sa<ss)ss=sa;
    }

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        int p,q;
        while(cin>>v1){
            sort(v1.begin(),v1.end());
            if(v1.back()==0)return;
            cin>>p>>q;
            p--;
            vi.assign(N,-1);
            ss="z";
            dfs(0);
            if(ss=="impossible")cout<<ss<<endl;
            else cout<<ss.substr(p,q-p)<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}