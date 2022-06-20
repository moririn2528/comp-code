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

class SingleOrDouble{
    
public:
    double probAlice(int N, int D, int A, int B){
        vector<long double> v1(N*D+2);
        int i,j,k;
        long double da,db;
        v1[0]=1;
        for(i=0;i<N;i++){
            for(j=N*D;j>=0;j--){
                for(k=1;k<=D && j+k<=N*D;k++){
                    v1[j+k]+=v1[j]/D;
                }
                v1[j]=0;
            }
        }
        da=1-v1[A]-v1[B];
        db=v1[B]*da;
        long double ds=v1[A]*(1+v1[B])/((1-da)*(1-db));
        return ds;
    }
};