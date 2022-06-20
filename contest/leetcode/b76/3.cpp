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

class ATM {
    typedef long long int ll;
    static const int N=5;
    vector<ll> v;
    vector<ll> m={20,50,100,200,500};
public:
    ATM() {
        v.assign(N,0);
    }
    
    void deposit(vector<int> banknotesCount) {
        int i;
        for(i=0;i<N;i++){
            v[i]+=banknotesCount[i];
        }
    }
    
    vector<int> withdraw(int amount) {
        vector<int> vs(5,0);
        int a,b,c;
        int i;
        for(i=N-1;i>=0;i--){
            a=min(amount/m[i],v[i]);
            amount-=m[i]*a;
            vs[i]=a;
        }
        if(amount>0)return vector<int>({-1});
        for(i=0;i<N;i++){
            v[i]-=vs[i];
        }
        return vs;
    }
};

/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */