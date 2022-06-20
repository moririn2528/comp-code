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
    vector<string> cellsInRange(string s) {
        vector<string> vs;
        for(char ca=s[0];ca<=s[2];ca++){
            for(char cb=s[1];cb<=s[3];cb++){
                vs.push_back(""+ca+cb);
            }
        }
        return vs;
    }
};