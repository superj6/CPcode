#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 40000;
struct segTree{
	int l, r;
	segTree *left, *right;
	int minv = 0, maxv = 0, lazy = 0;

	segTree(int a, int b){
    	l = a;
    	r = b;

    	if(l != r){
    		int mid = (l + r) / 2;
    		left = new segTree(l, mid);
    		right = new segTree(mid + 1, r);
    	}
	}	

	int minamt(){
    	return minv + lazy;
	}

	int maxamt(){
    	return maxv + lazy;
	}

	void push(){
    	left->lazy += lazy;
    	right->lazy += lazy;
    	minv += lazy;
    	maxv += lazy;
    	lazy = 0;
	}

	void pull(){
    	minv = min(left->minamt(), right->minamt());
    	maxv = max(left->maxamt(), right->maxamt());
	}

	void add(int a, int b, int x){
    	if(b < l || r < a) return;
    	if(a <= l && r <= b){
    		lazy += x;
    		return;
    	}

    	push();
    	left->add(a, b, x);
    	right->add(a, b, x);
    	pull();
	}

	int minqry(int a, int b){
    	if(b < l || r < a) return maxn;
    	if(a <= l && r <= b) return minamt();

    	push();

    	return min(left->minqry(a, b), right->minqry(a, b));
	}

	int maxqry(int a, int b){
    	if(b < l || r < a) return -maxn;
    	if(a <= l && r <= b) return maxamt();

    	push();

    	return max(left->maxqry(a, b), right->maxqry(a, b));
	}
};

int n;
int a[maxn], s[maxn], l[maxn], r[maxn];
vector<int> graph[maxn];
segTree tre(0, maxn);
int ret = 0;

int dfs1(int c){
	r[c] = l[c];
	s[c] += a[c];
	tre.add(l[c], l[c], s[c]);
	for(int i : graph[c]){
		l[i] = r[c] + 1;
		s[i] += s[c];
		r[c] = dfs1(i);
	}
	return r[c];
}

void dfs2(int c){
	ret = max(ret, min(-tre.minqry(l[c], r[c]), max(tre.maxqry(0, l[c] - 1), tre.maxqry(r[c] + 1, n - 1))));
	ret = max(ret, min(tre.maxqry(l[c], r[c]), -min(tre.minqry(0, l[c] - 1), tre.minqry(r[c] + 1, n - 1))));
	tre.add(0, l[c] - 1, a[c]);
	tre.add(r[c] + 1, n - 1, a[c]);
	
	for(int i : graph[c]){
		tre.add(l[i], r[i], -a[c]);
		dfs2(i);
		tre.add(l[i], r[i], a[c]);
	}
	
	tre.add(0, l[c] - 1, -a[c]);
	tre.add(r[c] + 1, n - 1, -a[c]);
}

int main() {
	freopen("btree.in", "r", stdin);
	freopen("btree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;

	for(int i = 1; i < n; i++){
    	int x;
    	cin >> x;
    	x--;
    	graph[x].push_back(i);
	}

	for(int i = 0; i < n; i++){
    	char c;
    	cin >> c;
    	a[i] = (c == '(' ? 1 : -1);
	}
	
	dfs1(0);
	dfs2(0);
	
	cout << ret << endl;

	return 0;
}