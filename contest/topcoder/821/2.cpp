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

class KnapsackTweak{
    bool check(vector<int>& items, int target,int diff){
        vector<char> v1(2*target+1);
        int i,j;
        int a,b;
        int n=items.size();
        int t=0,t2=0;
        for(i=0;i<n && items[i]<=diff;i++){
            t+=items[i];
        }
        if(target<=t+diff*i)return true;
        t2=diff*i;
        for(;i<n;i++){
            a=-1;
            vector<char> va(2*target+1);
            for(j=0;j<=2*target;j++){
                b=j+items[i]-diff;
                if(v1[j] && b<=2*target)va[b]=1;
                if(va[j])a=j+2*diff;
                if(j<=a)v1[j]=1;
            }
        }
        for(i=0;i<=2*target;i++){
            if(v1[i] && t-t2<=target-i && target-i<=t+t2)return true;
        }
        return false;
    }

public:

    int smallest(vector <int> items, int target){
        sort(items.begin(),items.end());
        int z[3]={0,target+1};
        while(z[1]-z[0]>1){
            z[2]=(z[0]+z[1])/2;
            if(check(items,target,z[2]))z[0]=z[2];
            else z[1]=z[2];
        }
        return z[0];
    }
};