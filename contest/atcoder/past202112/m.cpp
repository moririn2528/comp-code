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

template <typename T> struct Node{
    int left=-1,right=-1,par=-1;
    T val;
    int size=1,dep=1;
    int dep_diff=0;
    
    Node(){}
    Node(T v):val(v){}
    Node(int l,int r,int p,T v,int s,int d):
        left(l),right(r),par(p),val(v),size(s),dep(d){}
};

template <typename T> class AVL{
    typedef Node<T> Nd;
    const int LOOP_LIM=100;
public:
    vector<Nd> nodes;
    vector<int> erased;
    int nest=-1;

    bool in(T val){
        if(nest==-1)return false;
        int pos=nest;
        int i;
        for(i=0;i<LOOP_LIM && pos!=-1;i++){
            Nd& n=nodes[pos];
            if(n.val==val)return true;
            if(val<n.val)pos=n.left;
            else pos=n.right;
        }
        assert(i<LOOP_LIM);
        return false;
    }

    int getSize(int pos){
        if(pos==-1)return 0;
        return nodes[pos].size;
    }

    int index(T val){
        if(nest==-1)return -1;
        int pos=nest;
        int s=0;
        int i;
        for(i=0;i<LOOP_LIM && pos!=-1;i++){
            Nd& n=nodes[pos];
            if(n.val==val)return s+getSize(n.left);
            if(val<n.val)pos=n.left;
            else{
                s+=getSize(n.left)+1;
                pos=n.right;
            }
        }
        assert(i<LOOP_LIM);
        return -1;
    }

    T getVal(int id){
        int pos=nest;
        assert(nest!=-1);
        assert(0<=id && id<nodes[nest].size);
        int i;
        for(i=0;i<LOOP_LIM && pos!=-1;i++){
            Nd& n=nodes[pos];
            int l=getSize(n.left);
            if(l==id)return n.val;
            if(id<l)pos=n.left;
            else{
                id-=l+1;
                pos=n.right;
            }
        }
        assert(i<LOOP_LIM);
        assert(false);
        return T();
    }

    void alterChild(int pos,int bef_child,int new_child){
        if(pos==-1){
            assert(nest==bef_child);
            nest=new_child;
            return;
        }
        assert(0<=pos && pos<(int)nodes.size());
        Nd& n=nodes[pos];
        if(n.left==bef_child){
            n.left=new_child;
            return;
        }
        assert(n.right==bef_child);
        n.right=new_child;
    }

    void correctVar(int pos){
        if(pos==-1)return;
        assert(0<=pos && pos<(int)nodes.size());
        Nd& n=nodes[pos];
        int sz=1;
        int dl=0,dr=0;
        if(n.left!=-1){
            Nd& na=nodes[n.left];
            dl=na.dep;
            sz+=na.size;
        }
        if(n.right!=-1){
            Nd& na=nodes[n.right];
            dr=na.dep;
            sz+=na.size;
        }
        n.dep=max(dl,dr)+1;
        n.dep_diff=dl-dr;
        n.size=sz;
    }

    void rotateL(int pos){
        assert(0<=pos && pos<(int)nodes.size());
        Nd& na=nodes[pos];
        assert(na.right!=-1);
        int c=na.right;
        Nd& nb=nodes[c];
        int l=nb.left;
        int p=na.par;
        na.right=l;
        if(l!=-1)nodes[l].par=pos;
        nb.left=pos,na.par=c;
        nb.par=p;
        alterChild(p,pos,c);
        correctVar(c);
        correctVar(pos);
    }
    void rotateR(int pos){
        assert(0<=pos && pos<(int)nodes.size());
        Nd& na=nodes[pos];
        assert(na.left!=-1);
        int c=na.left;
        Nd& nb=nodes[c];
        int r=nb.right;
        int p=na.par;
        na.left=r;
        if(r!=-1)nodes[r].par=pos;
        nb.right=pos,na.par=c;
        nb.par=p;
        alterChild(p,pos,c);
        correctVar(c);
        correctVar(pos);
    }

    void correctTree(int pos){
        int i;
        for(i=0;pos!=-1 && i<LOOP_LIM;pos=nodes[pos].par,i++){
            correctVar(pos);
            Nd& n=nodes[pos];
            if(abs(n.dep_diff)<=1)continue;
            assert(abs(n.dep_diff)==2);
            if(n.dep_diff==2){
                if(nodes[n.left].dep_diff==-1)rotateL(n.left);
                rotateR(pos);
            }else{
                if(nodes[n.right].dep_diff==1)rotateR(n.right);
                rotateL(pos);
            }
        }
        assert(i<LOOP_LIM);
    }
    
    void insert(T val){
        if(in(val)){
            cerr<<"insert "<<val<<" skiped"<<endl;
            return;
        }
        Nd node(val);
        int id;
        if(erased.empty()){
            id=nodes.size();
            nodes.push_back(node);
        }else{
            id=erased.back();
            erased.pop_back();
            nodes[id]=node;
        }
        if(nest==-1){
            nest=id;
            return;
        }
        int pos=nest;
        int i;
        for(i=0;i<LOOP_LIM;i++){
            Nd& n=nodes[pos];
            if(val<n.val){
                if(n.left==-1){
                    n.left=id;
                    nodes[id].par=pos;
                    break;
                }
                pos=n.left;
            }else{
                if(n.right==-1){
                    n.right=id;
                    nodes[id].par=pos;
                    break;
                }
                pos=n.right;
            }
        }
        assert(i<LOOP_LIM);
        correctTree(id);
    }

    void connectParChild(int pos){
        Nd& node=nodes[pos];
        int p=node.par;
        int c=node.left+node.right+1;
        alterChild(p,pos,c);
        if(c!=-1)nodes[c].par=p;
    }

    void erase(T val){
        int i;
        int pos=nest;
        for(i=0;i<LOOP_LIM && pos!=-1;i++){
            Nd& n=nodes[pos];
            if(n.val==val)break;
            if(val<n.val)pos=n.left;
            else pos=n.right;
        }
        assert(pos!=-1);
        assert(i<LOOP_LIM);
        Nd& node=nodes[pos];
        int p=node.par;
        if(node.left==-1 || node.right==-1){
            connectParChild(pos);
        }else{
            int val_pos=pos;
            pos=node.left;
            for(i=0;i<LOOP_LIM;i++){
                int a=nodes[pos].right;
                if(a==-1)break;
                pos=a;
            }
            connectParChild(pos);
            p=nodes[pos].par;
            nodes[val_pos].val=nodes[pos].val;
        }
        nodes[pos]=Nd();
        erased.push_back(pos);
        correctTree(p);
    }
};

namespace sol{
    typedef pair<string,int> SP;

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        cin>>n>>m;
        string sa;
        AVL<SP> tree;
        for(i=0;i<n;i++){
            cin>>sa;
            tree.insert({sa,i});
        }
        for(i=0;i<m;i++){
            cin>>a>>sa;
            a--;
            SP p=tree.getVal(a);
            tree.erase(p);
            p.first=sa;
            tree.insert(p);
        }
        vector<string> vs(n);
        for(i=0;i<n;i++){
            SP p=tree.getVal(i);
            vs[p.second]=p.first;
        }
        cout<<vs<<endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    sol::solve();
}