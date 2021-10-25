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

class IntrospectiveNumbers{
    typedef long long int ll;
    const int N=9,M=30;//M=30
    const ll INF=1LL<<60;

    long long int gcd(long long int a,long long int b){
        if(a<b)swap(a,b);
        if(b==0)return a;
        return gcd(b,a%b);
    }

    string mid(string& l,string& r){
        int i;
        assert(l.size()==r.size());
        string s(l.size(),'0');
        vector<int> v1(l.size());
        for(i=0;i<l.size();i++){
            v1[i]+=l[i]-'0';
            v1[i]+=r[i]-'0';
        }
        for(i=(int)l.size()-1;i>0;i--){
            if(v1[i]>=10)v1[i]-=10,v1[i-1]++;
        }
        for(i=0;i<l.size();i++){
            s[i]+=v1[i]/2;
            v1[i]%=2;
            if(i+1<l.size())v1[i+1]+=v1[i]*10;
        }
        return s;
    }

    ll count_all(vector<ll>& v1){
        ll i,j;
        ll a,b,c;
        ll s=1;
        for(i=0,a=1;i<v1.size();i++){
            for(j=1;j<=v1[i];j++,a++){
                b=a,c=gcd(s,j);
                s/=c;
                b/=j/c;
                if(INF/s<=b-1)return INF;
                s*=b;
                if(INF<=s)return INF;
            }
        }
        return s;
    }

public:

    ll count(string& sa){
        int i,j,k;
        ll a,b;
        ll s=0;
        for(i=1;i<(1<<N);i++){
            a=0;
            vector<ll> v1(N,0);
            for(j=0;j<N;j++){
                if(i&1<<j)a+=j+1,v1[j]=j+1;
            }
            if(sa.size()<a)continue;
            for(j=0,k=0;j+a<sa.size();j++){
                if(sa[j]=='0')continue;
                s+=count_all(v1);
                if(INF<=s)return INF;
                k=1;
                break;
            }
            if(k)continue;
            int off=(int)sa.size()-a;
            for(j=0;j<a;j++){
                b=sa[off+j]-'0';
                if(b==0)break;
                for(k=0;k+1<b;k++){
                    if(v1[k]==0)continue;
                    v1[k]--;
                    s+=count_all(v1);
                    if(INF<=s)return INF;
                    v1[k]++;
                }
                if(v1[b-1]==0)break;
                v1[b-1]--;
            }
        }
        return s;
    }
    
    string nth(long long index){
        string l(M,'0'),r(M,'9');
        string m;
        int i;
        for(i=0;i<4*M;i++){
            m=mid(l,r);
            if(m==l)break;
            if(index+1<=count(m))r=m;
            else l=m;
        }
        while(m.size()>1 && m[0]=='0')m.erase(0,1);
        return m;
    }
};


int main(){
    IntrospectiveNumbers a;
    string sa="2144424";
    cout<<a.count(sa)<<endl;
}