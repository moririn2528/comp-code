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
#include<fstream>
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

char ca[1005];

int main(){
	ifstream ifs("in.txt");
	ofstream ofs("out.txt");
    for(int k=0;ifs.getline(ca,1000);k++){
		if(k!=0)ofs<<"\","<<endl;
		ofs<<"\"";
        for(int i=0;i<strlen(ca);i++){
			if(ca[i]=='\t')ofs<<"\\t";
			else if(ca[i]=='\"')ofs<<"\\\"";
			else if(ca[i]=='\\')ofs<<"\\\\";
			else ofs<<ca[i];
		}
    }
    ofs<<"\""<<endl;
}
