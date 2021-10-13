#include<bits/stdc++.h>
using namespace std;

class Solution {
    typedef long long int ll;
public:
    int minimumDifference(vector<int>& nums) {
        int n=nums.size()/2;
        vector<ll> v1,v2;
        ll a,b,c;
        int i,j,k;
        set<ll> s1;
        for(i=0,c=0;i<2*n;i++){
            c+=nums[i];
        }
        ll s=1LL<<60;
        for(i=1;i<(1<<n);i++){
            a=0,b=0;
            for(j=0;j<n;j++){
                if(i&1<<j)a+=nums[j],b+=nums[n+j];
            }
            if(i+1<(1<<n)){
                v1.push_back(a);
                s1.insert(b);
            }
            s=min(s,abs(c-2*a));
            s=min(s,abs(c-2*b));
        }
        sort(v1.begin(),v1.end());
        for(i=0;i<v1.size();i++){
            auto itr=s1.lower_bound(c/2-v1[i]);
            if(itr!=s1.end()){
                b=v1[i]+*itr;
                s=min(s,abs(c-2*b));
            }
            if(itr!=s1.begin()){
                itr--;
                b=v1[i]+*itr;
                s=min(s,abs(c-2*b));
            }
        }
        return s;
    }
};

int main(){
    Solution sa;
    vector<int> v1={76,8,45,20,74,84,28,1};
    int s=sa.minimumDifference(v1);
}