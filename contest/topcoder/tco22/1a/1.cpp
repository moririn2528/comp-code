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

class SkyscraperReconstruction{
public:
    vector <int> reconstruct(string visibility){
        int n=visibility.size();
        vector<int> vs(n);
        int i;
        int a=n,b=1;
        for(i=n-1;i>=0;i--){
            if(visibility[i]=='O')vs[i]=a--;
            else vs[i]=b++;
        }
        return vs;
    }
};