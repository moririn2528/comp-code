#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cassert>
#include<set>
#include<complex>
#include<numeric>
#include<functional>
#include<unordered_map>
#include<unordered_set>
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,int> LP;
const int INF=1<<30;
const LL MAX=1e9+7;

void array_show(int *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%d%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(LL *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%lld%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(vector<int> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%d%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
void array_show(vector<LL> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%lld%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}

class Zalgo{
private:
    string str;
    vector<int> pre_len;//length same to prefix
public:
    void calc_zalgo(){
        pre_len.assign(str.size(),0);
        int n=str.size();
        int i,j,k;
        pre_len[0]=str.size();
        for(i=1,j=0;i<n;){
            for(;i+j<n;j++){
                if(str[j]!=str[i+j])break;
            }
            pre_len[i]=j;
            if(j==0){
                i++;
                continue;
            }
            i++,j--;
            for(k=1;j>0 && i<n;i++,j--,k++){
                if(pre_len[k]>=j)break;
                pre_len[i]=pre_len[k];
            }
        }
    }

    void calc_zalgo(string str_temp){
        str=str_temp;
        calc_zalgo();
    }

    vector<int> get_pre_len(){
        return pre_len;
    }
};

namespace sol{

    int dp[2222][2222];

    void solve(){
        int n,m;
        int i,j,k;
        int a,b,c;
        string sa;
        cin>>sa;
        cin>>m;
        n=sa.size();
        Zalgo za;
        za.calc_zalgo(sa);
        vector<int> pre=za.get_pre_len();
        vector<int> leng(n+10),score(n+10);
        for(i=0;i<=n;i++){
            a=i;
            for(j=1;j<i;j++){
                if(pre[j]>=i-j)break;
                a+=pre[j];
            }
            leng[i]=j;
            score[i]=a;
        }
        leng[0]=1;
        score[0]=0;
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;
        for(i=0;i<=m;i++){
            for(j=0;j<=n;j++){
                dp[i][j+1]=max(dp[i][j+1],dp[i][j]);
                if(i+j>m)break;
                a=i+leng[j],b=max(j-leng[j],0);
                dp[a][b]=max(dp[a][b],dp[i][j]+score[j]);
            }
        }
        cout<<dp[m][0]<<endl;
    }
}

int main(){
    sol::solve();
}