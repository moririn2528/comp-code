#include<bits/stdc++.h>
using namespace std;

class StockPrice {
    typedef pair<int,int> P;
    map<int,int> m1;
    priority_queue<P> q1;
    priority_queue<P,vector<P>,greater<P>> q2;
public:
    StockPrice() {
        
    }
    
    void update(int timestamp, int price) {
        m1[timestamp]=price;
        q1.push({price,timestamp});
        q2.push({price,timestamp});
    }
    
    int current() {
        auto itr=m1.end();
        itr--;
        return itr->second;
    }
    
    int maximum() {
        int a,b;
        while(!q1.empty()){
            a=q1.top().first,b=q1.top().second;
            if(m1[b]!=a){
                q1.pop();
                continue;
            }
            return a;
        }
        return 0;
    }
    
    int minimum() {
        int a,b;
        while(!q2.empty()){
            a=q2.top().first,b=q2.top().second;
            if(m1[b]!=a){
                q2.pop();
                continue;
            }
            return a;
        }
        return 0;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */