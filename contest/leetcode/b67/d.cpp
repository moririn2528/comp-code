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

class SORTracker {
    typedef pair<int,string> P;
    set<P> s1;
    P p1;
public:
    SORTracker() {
        
    }
    
    void add(string name, int score) {
        P p=P(score,name);
        s1.insert(p);
        if(s1.size()==1){
            p1=p;
            return;
        }
        if(p<p1){
            auto itr=s1.find(p1);
            itr--;
            p1=*itr;
        }
    }
    
    string get() {
        string s=p1.second;
        auto itr=s1.find(p1);
        itr++;
        p1=*itr;
        return s;
    }
};
