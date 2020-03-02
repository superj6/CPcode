#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define vi vector<int>

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
		if(b < l || r < a) return inf;
		if(a <= l && r <= b) return val;
		
		return min(left->qry(a, b), right->qry(a, b));
	}
};

const int maxn = 200000;
int n, m, q;
int s[2][maxn], rf[2][maxn];
int p[maxn], rnk[maxn], b[maxn]; 
int itl[2][maxn], itr[2][maxn], ot[2][maxn];
vector<int> graph[maxn];
vector<int> g[2][maxn], a[2][maxn], f[2][maxn];

int find(int x){
	return x == p[x] ? x : p[x] = find(p[x]);
}

int dfs(int c, int t){
	itr[t][c] = itl[t][c];
	ot[t][itl[t][c]] = c;
	for(int i : g[t][c]){
		itl[t][i] = itr[t][c] + 1;
		itr[t][c] = dfs(i, t);
	}
	return itr[t][c];
}

vi check_validity(int N, vi X, vi Y, vi S, vi E, vi L, vi R){
	n = N, m = X.size(), q = S.size();
	for(int i = 0; i < m; i++){
		graph[X[i]].push_back(Y[i]); 
		graph[Y[i]].push_back(X[i]);
	}
	for(int i = 0; i < q; i++){
		s[0][i] = S[i];
		s[1][i] = E[i];
		a[0][L[i]].push_back(i);
		a[1][R[i]].push_back(i);
	} 
	
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++) p[i] = b[i] = i, rnk[i] = 0;
		for(int c = !t * (n - 1); 0 <= c && c < n; c += 2 * t - 1){
			for(int i : graph[c]){
				int x = find(c), y = find(i);
				if((t ? c <= i : c >= i) || x == y) continue;
				g[t][c].push_back(b[y]);
				if(rnk[x] < rnk[y]) swap(rnk[x], rnk[y]);
				if(rnk[x] == rnk[y]) rnk[x]++;
				p[y] = x;
				b[x] = c;
			}
			for(int i : a[t][c]){
				int x = b[find(s[t][i])];
				f[t][x].push_back(i);
				rf[t][i] = x;
			}
		}
	}
	
	dfs(0, 0);
	dfs(n - 1, 1);
	
	vi ans(q);
	segTree tre(0, n - 1);
	for(int c = n - 1; c >= 0; c--){
		tre.add(itl[1][ot[0][c]], c);
		for(int i : f[0][ot[0][c]]){
			ans[i] = tre.qry(itl[1][rf[1][i]], itr[1][rf[1][i]]) <= itr[0][ot[0][c]];
		}
	}
	
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vi ans = check_validity(6, 
	{5, 1, 1, 3, 3, 5}, {1, 2, 3, 4, 0, 2},
	{4, 4, 5}, {2, 2, 4},
	{1, 2, 3}, {2, 2, 4});
	
	for(int i : ans) cout << i << endl; 

	return 0;
}