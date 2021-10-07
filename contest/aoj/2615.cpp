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
typedef pair<LL,LL> LP;
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
template<typename T> ostream& operator<<(ostream& os,const vector<T>& v1){
	int n=v1.size();
	for(int i=0;i<n;i++){
		if(i)os<<" ";
		os<<v1[i];
	}
	return os;
}
template<typename T1,typename T2> ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	os<<p.first<<" "<<p.second;
	return os;
}
template<typename T> istream& operator>>(istream& is,vector<T>& v1){
	int n=v1.size();
	for(int i=0;i<n;i++)is>>v1[i];
	return is;
}
template<typename T1,typename T2> istream& operator>>(istream& is,pair<T1,T2>& p){
	is>>p.first>>p.second;
	return is;
}

template<typename T> class bit{
private:
	vector<T> bit_vec;
	int bit_N=20;

	T bit_comp(T a,T b){
		return a+b;
	}

public:

	bit(int n){
		for(bit_N=0;bit_N<30;bit_N++){
			if(n<(1<<bit_N))break;
		}
		bit_vec.assign((1<<bit_N),0);
	}

	void set(int pos,T x){
		bit_vec[pos]=bit_comp(bit_vec[pos],x);
		for(int i=0;i<bit_N;i++){
			if(pos&(1<<i))continue;
			pos|=(1<<i);
			bit_vec[pos]=bit_comp(bit_vec[pos],x);
		}
	}

	T search(int pos){
		T s=bit_vec[pos];
		for(int i=0;pos>=(1<<i);i++){
			if(pos&(1<<i))continue;
			pos-=(1<<i);
			s=bit_comp(s,bit_vec[pos]);
		}
		return s;
	}
};

namespace sol{
	const int N=3e5+7;
	vector<int> va,vb,vc(N,-1);
	vector<set<int>> ss(3);
	set<int> s1;
	bit<int> bt(N);

	vector<int> str2vec(string sa){
		vector<int> vs(N);
		int dif=N-sa.size();
		for(int i=0;i<sa.size();i++){
			vs[dif+i]=sa[i]-'0';
		}
		return vs;
	}

	void setbit(int pos){
		if(vc[pos]!=-1)ss[vc[pos]].erase(pos);
		vc[pos]=va[pos]+vb[pos];
		ss[vc[pos]].insert(pos);
	}

	void solve(){
		int n,m;
		int i,j,k;
		int a,b,c;
		string sa,sb;
		char ca;
		cin>>n>>sa>>sb;
		va=str2vec(sa);
		vb=str2vec(sb);
		for(i=0;i<N;i++){
			setbit(i);
			bt.set(i,va[i]);
			if(vb[i]==1)s1.insert(i);
		}
		ss[0].insert(N);
		ss[2].insert(N);
		for(i=0;i<n;i++){
			cin>>ca;
			if(ca=='A'){
				cin>>a;
				a=N-a-1;
				va[a]^=1;
				setbit(a);
				if(va[a]==1)bt.set(a,1);
				else bt.set(a,-1);
				continue;
			}
			if(ca=='B'){
				cin>>a;
				a=N-a-1;
				vb[a]^=1;
				setbit(a);
				if(vb[a]==1)s1.insert(a);
				else s1.erase(a);
				continue;
			}
			a=*(s1.lower_bound(0));
			b=*(ss[0].lower_bound(a));
			c=*(ss[2].lower_bound(a));
			if(b>c){
				auto itr=ss[0].lower_bound(a);
				assert(itr!=ss[0].begin());
				itr--;
				a=*itr;
			}
			int s=bt.search(a)+N-a-1;
			cout<<s<<endl;
		}
	}
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	sol::solve();
}