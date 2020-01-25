#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

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
	
	long long amt(){
		return val + lazy * (r - l + 1);
	}
	
	void push(){
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
	
	void pull(){
		val = left->amt() + right->amt();
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
		pull();
	}
	
	long long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return amt();;
		
		push();
		pull();
		
		return left->qry(a, b) + right->qry(a, b);
	}
};

const int maxn = 100000;
int n, q;
int l[maxn], r[maxn];
segTree tre(0, maxn);
vector<int> graph[maxn];
set<int> cur[maxn];

int dfs(int c, int p){
	r[l[c]] = l[c];
	for(int i : graph[c]){
		if(i == p) continue;
		l[i] = r[l[c]] + 1;
		r[l[c]] = dfs(i, c);
	}
	return r[l[c]];
}

int main(){
	freopen("snowcow.in", "r", stdin);
	freopen("snowcow.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	dfs(0, -1);
	
	for(int i = 0; i < q; i++){
		int t, x, c;
		cin >> t >> x;
		t--, x--;
		
		if(t){
			//cout << l[x] << " " << r[l[x]] << endl;
			cout << tre.qry(l[x], r[l[x]]) << endl;
		}else{
			//cout << "----------" << endl;
			cin >> c;
			c--;
			
			auto it = cur[c].upper_bound(l[x]);
			if(!cur[c].empty() && it != cur[c].begin()){
				it--;
				if(l[x] <= r[*it]) continue;
			}
			
			while(!cur[c].empty()){
				it = cur[c].lower_bound(l[x]);
				if(it == cur[c].end() || r[l[x]] < *it) break;
				tre.add(*it, r[*it], -1);
				cur[c].erase(it);
			}
			
			cur[c].insert(l[x]);
			tre.add(l[x], r[l[x]], 1);
		}
	}

	return 0;
}