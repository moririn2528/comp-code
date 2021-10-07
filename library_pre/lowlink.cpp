#include<bits/stdc++.h>
using namespace std;
class union_find_tree{
private:
    static constexpr int N=100005;
    int n;
    queue<int> q1;
    vector<int> parent;
    vector<int> num;
public:
    void init(){
        parent.assign(n,-1);
        num.assign(n,1);
    }
    union_find_tree(int n_init){
        assert(n_init>=0);
        n=n_init;
        init();
    }
    union_find_tree(){
        n=N;
        init();
    }

    int check_parent(int x){
        assert(x>=0 && x<n);
        if(parent[x]!=-1){
            q1.push(x);
            return check_parent(parent[x]);
        }
        int a;
        while(!q1.empty()){
            a=q1.front(),q1.pop();
            parent[a]=x;
        }
        return x;
    }

    bool connect(int x,int y){
        assert(x>=0 && x<n);
        assert(y>=0 && y<n);
        x=check_parent(x),y=check_parent(y);
        if(x==y)return true;
        if(num[x]>num[y])swap(x,y);
        parent[x]=y;
        num[y]+=num[x];
        return false;
    }

    int size(int pos){
        pos=check_parent(pos);
        return num[pos];
    }

    bool check(int x,int y){//connect:true
        assert(x>=0 && x<n);
        assert(y>=0 && y<n);
        return check_parent(x)==check_parent(y);
    }
};



class Lowlink: public union_find_tree{
public:
    vector<vector<int>> path;
    vector<int> ord,lowlink;

private:
    int dfs(int pos,int bef,int& cnt){
        if(ord[pos]!=-1)return -1;
        lowlink[pos]=ord[pos]=cnt++;
        vector<int> v1;
        for(auto to:path[pos]){
            if(to==bef)continue;
            if(dfs(to,pos,cnt)==-1){
                lowlink[pos]=min(lowlink[pos],ord[to]);
            }else{
                lowlink[pos]=min(lowlink[pos],lowlink[to]);
                v1.push_back(to);
            }
        }
        for(auto to:v1){
            if(lowlink[to]<=ord[pos]){
                connect(pos,to);
            }
        }
        return 0;
    }

public:
    int init(int n){
        path.assign(n,vector<int>());
        ord.assign(n,-1);
        lowlink.assign(n,-1);
    }

    Lowlink(){}
    Lowlink(int n){
        init(n);
    }

    void reload(){
        int a=0;
        for(int i=0;i<path.size();i++){
            dfs(i,-1,a);
        }
    }
};