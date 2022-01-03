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

class Robot {
    int n,m;
    int pos=-1;
public:
    Robot(int width, int height) {
        n=width,m=height;
    }
    
    void move(int num) {
        pos+=num;
        pos%=2*(n+m);
    }
    
    vector<int> getPos() {
        if(pos<n)return vector<int>{pos+1,0};
        if(pos<n+m)return vector<int>{n-1,pos-n};
        if(pos<2*n+m)return vector<int>{2*n+m-pos-1,m-1};
        return vector<int>{0,2*(n+m)-1-pos};
    }
    
    string getDir() {
        if(pos<n)return "East";
        if(pos<n+m)return "North";
        if(pos<2*n+m)return "West";
        return "South";
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->move(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */