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

template <typename T> class seg_tree{
private:
	static constexpr int seg_init_N=1e5+7;
	int seg_N;
	vector<T> seg;
	virtual T func(T seg_a,T seg_b){
		return min(seg_a,seg_b);// function
	}

	void init(int seg_n){
		assert(seg_n>=0);
		seg.assign(4*seg_n,0);
		int seg_i;
		for(seg_i=0;(1<<seg_i)<seg_n;seg_i++);
		seg_N=(1<<seg_i)-1;
	}

	void init_reload(){
		for(int seg_i=seg_N-1;seg_i>=0;seg_i--){
			seg[seg_i]=func(seg[2*seg_i+1],seg[2*seg_i+2]);
		}
	}
	
	void update(int seg_pos){
		T seg_a=func(seg[seg_pos*2+1],seg[seg_pos*2+2]);
		if(seg[seg_pos]==seg_a)return;
		seg[seg_pos]=seg_a;
		if(seg_pos==0)return;
		update((seg_pos-1)/2);
	}

public:
	seg_tree(int seg_n){
		init(seg_n);
	}
	seg_tree(){
		init(seg_init_N);
	}
	seg_tree(T *seg_t,int seg_n){
		init(seg_n);
		for(int seg_i=0;seg_i<seg_n;seg_i++){
			seg[seg_N+seg_i]=seg_t[seg_i];
		}
		init_reload();
	}
	seg_tree(T seg_a,int seg_n){
		init(seg_n);
		for(int seg_i=0;seg_i<seg_n;seg_i++){
			seg[seg_N+seg_i]=seg_a;
		}
		init_reload();
	}

	void set(int seg_pos,T seg_a){
		assert(seg_pos>=0 && seg_pos<=seg_N);
		seg_pos+=seg_N;
		seg[seg_pos]=seg_a;
		update((seg_pos-1)/2);
	}

	void set_only(int seg_pos,T seg_a){
		assert(seg_pos>=0 && seg_pos<=seg_N);
		seg_pos+=seg_N;
		seg[seg_pos]=seg_a;
	}

	T search(int seg_a,int seg_b,int seg_r,int seg_l,int seg_x){//[a,b) search
		if(seg_a<=seg_r && seg_l<=seg_b)return seg[seg_x];
		int seg_m=(seg_r+seg_l)/2;
		if(seg_b<=seg_m)return search(seg_a,seg_b,seg_r,seg_m,2*seg_x+1);
		if(seg_m<=seg_a)return search(seg_a,seg_b,seg_m,seg_l,2*seg_x+2);
		return func(search(seg_a,seg_m,seg_r,seg_m,2*seg_x+1),search(seg_m,seg_b,seg_m,seg_l,2*seg_x+2));
	}
	T search(int seg_a,int seg_b){
		return search(seg_a,seg_b,0,seg_N+1,0);
	}
};

//////////////// Heavy Light Decomposition //////////////////////////
const int N=1e5+7;
vector<int> path[N];
int parent[N];
int chnum[N];

int child_count(int pos){
	int a=0;
	for(auto to:path[pos])a+=child_count(to);
	chnum[pos]=a+1;
	return chnum[pos];
}

vector<vector<int> > paths;//HL
int belong_paths[N];

void paths_create(int pos){/// TODO nest (init)
	if(path[pos].empty())return;
	int ma=path[pos][0];//a child of main stream
	for(auto to:path[pos]){
		if(chnum[to]>chnum[ma])ma=to;
	}
	int a=belong_paths[pos];
	paths[a].push_back(pos);
	for(auto to:path[pos]){
		if(to==ma)continue;
		belong_paths[to]=paths.size();
		paths.push_back((vector<int>){to});
	}
}

void HL_init(int nest){
	child_count(nest);
	memset(belong_paths,0,sizeof(belong_paths));
	paths.push_back((vector<int>){nest});
	paths_create(nest);
}

int main(){
	int n,m;
	int i,j,k;
	int a,b,c;
	
}