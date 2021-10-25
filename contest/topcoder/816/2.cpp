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

class OccupiedAirplane{
    typedef long long int ll;
    vector<int> v[3];
    vector<char> used;
    vector<int> pos;
    int r;

    ll seat(ll n,ll t){
        ll a,b,c;
        int i,j;
        ll s=0;
        if(n==1){
            for(i=0;i<3;i++){
                if(v[i].empty()){
                    a=v[i].back();
                    v[i].pop_back();
                    break;
                }
            }
            used[a]=1;
            return t*a;
        }
        if(n<=6){
            for(i=pos[t];i<6*r;i++){
                if(6-n<i%6){
                    i=(i/6+1)*6-1;
                    continue;
                }
                for(j=0;j<n;j++){
                    if(used[i+j])break;
                }
                if(j<n){
                    i+=j;
                    continue;
                }
                for(j=0;j<n;j++){
                    used[i+j]=1;
                    s+=(t+j)*(i+j);
                }
                pos[t]=i+n;
                return s;
            }
            pos[t]=6*r;
        }
        for(i=0;i<n;i++){
            s+=seat(1,t+i);
        }
        return s;
    }
public:
    long long seat(int R, vector <int> groups, int seed){
        int i,j;
        int a;
        r=R;
        for(i=R-1;i>=0;i--){
            v[0].push_back(6*i+5);
            v[2].push_back(6*i+4);
            v[1].push_back(6*i+3);
            v[1].push_back(6*i+2);
            v[2].push_back(6*i+1);
            v[0].push_back(6*i);
        }
        used.assign(6*R,0);
        pos.assign(10,0);
        ll state=seed;
        ll s=0;
        for(i=0,j=0;i<6*R;j++){
            if(j<groups.size())a=groups[j];
            else{
                state = (state * 1103515245 + 12345) % (1LL<<31);
                a = ((state >> 10) % 6) + 1;
            }
            if(6*R<=i+a)break;
            s+=seat(a,i+1);
            i+=a;
        }
        return s;
    }
};