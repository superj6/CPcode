#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	long long val = 0, lazy = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	long long value(){
		return val + lazy;
	}
	
	void push(){
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
	
	void add(int a, int b, long long v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy += v;
			return;
		}
		
		push();
		
		left->add(a, b, v);
		right->add(a, b, v);
		
		val = max(left->value(), right->value());
	}
};

const int maxn = 200000;
int n;
segTree *tre;
int l[maxn], r[maxn];
vector<int> graph[maxn];
int ans[maxn];
int cnt;

int dfs1(int c, int d, int p){
	l[c] = r[c] = cnt++;
	tre->add(l[c], l[c], d);
	for(int i : graph[c]){
		if(i == p) continue;
		r[c] = max(r[c], dfs1(i, d + 1, c));
	}
	return r[c];
}

void dfs2(int c, int p){
	ans[c] = tre->value();
	
	for(int i : graph[c]){
		if(i == p) continue;
		tre->add(0, n - 1, 1);
		tre->add(l[i], r[i], -2);
		
		dfs2(i, c);
		tre->add(0, n - 1, -1);
		tre->add(l[i], r[i], 2);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	tre = new segTree(0, n - 1);
	dfs1(0, 0, -1);
	dfs2(0, -1);
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}