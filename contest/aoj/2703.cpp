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
public:
    int A[N];
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

    void rotateZrev(){
        swap(A[2],A[1]);
        swap(A[3],A[2]);
        swap(A[4],A[3]);
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
    typedef tuple<int,int,int> T;
    const int N=1e4,offset=1111;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c,d,e,f;
        int x,y;
        while(cin>>n){
            if(n==0)return;
            vector<vector<T>> vt(n);
            for(i=0;i<n;i++){
                cin>>x>>y;
                x+=offset,y+=offset;
                cin>>a>>b>>c>>d>>e>>f;
                vector<int> v1={f,a,c,b,d,e};
                Dice dice(v1);
                string sa;
                cin>>sa;
                map<P,int> m1;
                m1[{x,y}]=dice.A[5];
                for(auto ca:sa){
                    if(ca=='L'){
                        x--;
                        dice.rotateYrev();
                    }
                    if(ca=='R'){
                        x++;
                        dice.rotateY();
                    }
                    if(ca=='F'){
                        y--;
                        dice.rotateX();
                    }
                    if(ca=='B'){
                        y++;
                        dice.rotateXrev();
                    }
                    m1[{x,y}]=dice.A[5];
                }
                for(auto node:m1){
                    vt[i].push_back({node.first.first,node.first.second,node.second});
                }
            }
            vector<int> score(1<<n);
            for(i=0;i<(1<<n);i++){
                unordered_set<int> s1;
                for(j=0;j<n;j++){
                    if(~i&1<<j)continue;
                    for(k=0;k<vt[j].size();k++){
                        tie(a,b,ignore)=vt[j][k];
                        s1.insert(a*N+b);
                    }
                }
                for(j=0;j<n;j++){
                    if(i&1<<j)continue;
                    d=score[i];
                    for(k=0;k<vt[j].size();k++){
                        tie(a,b,c)=vt[j][k];
                        if(s1.find(a*N+b)==s1.end())d+=c;
                    }
                    score[i|1<<j]=max(score[i|1<<j],d);
                }
            }
            cout<<score[(1<<n)-1]<<endl;
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}