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
    int mostWordsFound(vector<string>& sentences) {
        int s=0;
        for(string sa:sentences){
            int a=1;
            for(char ca:sa){
                if(ca==' ')a++;
            }
            s=max(s,a);
        }
        return s;
    }
};