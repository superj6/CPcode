#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
#include <deque>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int inf = 1000000007;
struct segTree{
	int l, r;
	segTree *left, *right;
	int val = inf;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			val = v;
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		val = min(left->val, right->val);
	}
	
	int qry(int a, int b){
		if(r < a || b < l) return inf;
		if(a <= l && r <= b) return val;
		
		return min(left->qry(a, b), right->qry(a, b));
	}
};

const int maxn = 100000, m = 17, t = 2;
int n, k;
int par[maxn];
int a[t][m][maxn];
vector<int> rt[t];
vector<int> graph[t][maxn];

int getmin(int p, int l, int r){
	int j = log2(r - l + 1);
	return min(a[p][j][l], a[p][j][r - (1 << j) + 1]);
}

void init(){
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		cin >> a[0][0][i];
		a[1][0][i] = -a[0][0][i];
	}
	
	for(int i = 1; i < m; i++){
		for(int j = 0; j + (1 << i) <= n; j++){
			for(int p = 0; p < t; p++){
				a[p][i][j] = min(a[p][i - 1][j], a[p][i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	
	for(int p = 0; p < 2; p++){
		for(int i = 0; i < n; i++){
			int best = 2 * n;
			
			if(getmin(p, i, n - 1) < getmin(p, i, i)){
				int l = i, r = n - 1;
				while(r - l > 1){
					int mid = (l + r) / 2;
					if(getmin(p, i, mid) < getmin(p, i, i)) r = mid;
					else l = mid;
				}
				if(abs(r - i) < abs(best - i)) best = r;
			}
			
			if(getmin(p, 0, i) < getmin(p, i, i)){
				int l = 0, r = i;
				while(r - l > 1){
					int mid = (l + r) / 2;
					if(getmin(p, mid, i) < getmin(p, i, i)) l = mid;
					else r = mid;
				}
				if(abs(l - i) < abs(best - i)) best = l;
			}
			
			if(best == 2 * n){
				rt[p].push_back(i);
				if(p) par[i] = -1;
			}else{
				graph[p][best].push_back(i);
				if(p) par[i] = best;
			} 
		}
	}
}

int x;
int dist[maxn];
int l[maxn], r[maxn];
bool works[maxn];
deque<int> dq;
segTree tre(0, maxn);

int dfs1(int c){
	r[c] = l[c];
	for(int i : graph[0][c]){
		l[i] = r[c] + 1;
		dist[i] = dist[c] + 1;
		r[c] = dfs1(i);
	}
	return r[c];
}

void dfs(int c){
	works[c] = (tre.qry(l[c], r[c]) - dist[c] <= k);
	
	tre.add(l[c], dist[c]);
	dq.push_front(c);
	if(dq.size() > k){
		tre.add(l[dq.back()], inf);
		dq.pop_back();
	}
	
	for(int i : graph[1][c]) dfs(i);
	
	if(par[dq.back()] != -1){
		dq.push_back(par[dq.back()]);
		tre.add(l[dq.back()], dist[dq.back()]);
	}
	tre.add(l[c], inf);
	dq.pop_front();
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();
	
	for(int i : rt[0]){
		l[i] = x;
		x = dfs1(i) + 1;
	}
	
	for(int i : rt[1]) dfs(i);
	
	for(int i = 0; i < n; i++) cout << works[i];
	cout << endl;

	return 0;
}