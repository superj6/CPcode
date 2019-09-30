#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long inf = 1e9 + 7;

struct segTree{
	int l, r;
	segTree *left, *right;
	long val = -inf, lazy = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	long amt(){
		return val + lazy;
	}
	
	void push(){
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy += v;
			return;
		}
		
		push();
		
		left->add(a, b, v);
		right->add(a, b, v);
		val = max(left->amt(), right->amt());
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return amt();
		
		push();
		
		return max(left->qry(a, b), right->qry(a, b));
	}
};

const int maxn = 100000;
int n;
pi query[maxn];
int dist[maxn], top[maxn];
int l[maxn], r[maxn], par[maxn];
segTree tre(0, maxn);
vector<int> rt;
vector<int> graph[maxn];
int ans[maxn];
int m;

int dfs(int c){
	r[c] = l[c];
	for(int i : graph[c]){
		dist[i] = dist[c] + 1;
		l[i] = r[c] + 1;
		top[i] = top[c];
		r[c] = dfs(i);
	}
	return r[c];
}

void add(int c){
	tre.add(l[c], l[c], inf + dist[c]);
}

void recur(int c, int t){
	if(par[c] == -2) return;
	tre.add(l[c], r[c], t);
	recur(par[c], t);
}

void qry(int c){
    tre.add(l[top[c]], r[top[c]], dist[c]);
	recur(c, -2);
	cout << tre.qry(l[top[c]], r[top[c]]) << endl;
    tre.add(l[top[c]], r[top[c]], -dist[c]);
    recur(c, 2);
}

int main(){
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		char t;
		int x;
		cin >> t >> x;
		x--;
		
		query[i] = {(t == 'B'), (t == 'B' ? m : x)};
		
		if(query[i].first){
			par[m] = x;
			if(x != -2) graph[x].push_back(m);
			else rt.push_back(m);
			m++;
		}
	}
	
	m = 0;
	for(int i : rt){
        l[i] = m;
        top[i] = i;
        m = dfs(i) + 1;
	}
	
	for(int i = 0; i < n; i++){
		if(query[i].first){
			add(query[i].second);
		}else{
			qry(query[i].second);
		}
	}

	return 0;
}