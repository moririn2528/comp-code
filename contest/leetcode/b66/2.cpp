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
    int minimumBuckets(string street) {
        bool f1=false,f2=false;
        int i,j,k;
        int n=street.size();
        int s=0;
        for(i=0;i+1<n;i++){
            if(street[i]=='.' || street[i+1]=='.')continue;
            if(i==0 || street[i-1]=='H')return -1;
            if(i+2==n || street[i+2]=='H')return -1;
            street[i]='.',street[i+1]='.';
            if(i-2>=0)street[i-2]='.';
            if(i+3<n)street[i+3]='.';
            s+=2;
        }
        for(i=0;i<n;i++){
            if(street[i]=='.')continue;
            if(i+1<n && street[i+1]=='.'){
                s++;
                if(i+2<n && street[i+2]=='H')street[i+2]='.';
                continue;
            }
            if(i>0 && street[i-1]=='.'){
                s++;
                continue;
            }
            return -1;
        }
        return s;
    }
};