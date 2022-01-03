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
public:
    bool canBeValid(string s, string locked) {
        int n=s.size();
        int i,j,k;
        int a=n/2,b=n/2;
        if(n%2)return false;
        for(i=0;i<n;i++){
            if(locked[i]=='0')continue;
            if(s[i]=='(')a--;
            else b--;
        }
        if(a<0 || b<0)return false;
        for(i=0,j=0;i<n;i++){
            if(locked[i]=='1')continue;
            if(j<a)s[i]='(';
            else s[i]=')';
            j++;
        }
        cout<<s<<endl;
        for(i=0;i<n;i++){
            if(s[i]=='(')a++;
            else a--;
            if(a<0)return false;
        }
        return true;
    }
};