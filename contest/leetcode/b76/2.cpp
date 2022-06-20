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
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
        long long int i;
        long long int s=0;
        for(i=0;i<1e6+5;i++){
            if(total<cost1*i)continue;
            s+=(total-cost1*i)/cost2+1;
        }
        return s;
    }
};