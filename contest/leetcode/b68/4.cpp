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

class Solution {
    typedef long long int ll;
public:
    string getstring(ll a){
        string s=to_string(a);
        int t=5-s.size();
        if(t==0)return s;
        return string(t,'0')+s;
    }
    string abbreviateProduct(int left, int right) {
        ll suf=1;
        ll pre=1;
        const ll mod=1e5;
        const ll INF=1LL<<60;
        ll i,j,k;
        ll a,b,c;
        int cnt2=0,cnt5=0;
        for(i=left;i<=right;i++){
            for(a=i;a%2==0;cnt2++)a/=2;
            for(a=i;a%5==0;cnt5++)a/=5;
        }
        int cnt=min(cnt2,cnt5);
        cnt2=cnt5=cnt;
        bool flag=false;
        for(i=left;i<=right;i++){
            a=i;
            for(;a%2==0 && cnt2>0;cnt2--)a/=2;
            for(;a%5==0 && cnt5>0;cnt5--)a/=5;
            suf*=a;
            if(suf>=mod*mod){
                suf%=mod;
                flag=true;
            }
            while(INF<pre || INF/i<pre)pre/=10;
            pre*=a;
        }
        if(!flag){
            return to_string(suf)+"e"+to_string(cnt);
        }
        suf%=mod;
        while(pre>=mod)pre/=10;
        return getstring(pre)+"..."+getstring(suf)+"e"+to_string(cnt);
    }
};