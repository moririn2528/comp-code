#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<tuple>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
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

class Solution {
    vector<vector<int>> path;
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n=bombs.size();
        int i,j,k;
        int a,b,c,d;
        path.assign(n,vector<int>());
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                a=bombs[i][0]-bombs[j][0];
                b=bombs[i][1]-bombs[j][1];
                c=bombs[i][2],d=bombs[j][2];
                if(a*a+b*b<=c*c)path[i].push_back(j);
                if(a*a+b*b<=d*d)path[j].push_back(i);
            }
        }
        int s=0;
        for(i=0;i<n;i++){
            queue<int> q1;
            int cnt=0;
            q1.push(i);
            vector<char> used(n);
            while(!q1.empty()){
                a=q1.front();q1.pop();
                if(used[a])continue;
                used[a]=1;
                cnt++;
                for(auto to:path[a]){
                    if(used[to])continue;
                    q1.push(to);
                }
            }
            s=max(s,cnt);
        }
        return s;
    }
};