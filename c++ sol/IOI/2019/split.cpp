//#include "split.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int maxn = 100000;
int n, m;
pi a[3];
int l[maxn], h[maxn], sz[maxn], p[maxn];
vi graph[maxn], g[maxn];
vi ans;
int r, s, t;

void dfs(int c){
	sz[c] = 1;
	l[c] = h[c] = ++t;
	int amt = 0;
	for(int i : graph[c]){
		if(i == p[c]) continue;
		if(!l[i]){
			p[i] = c;
			dfs(i);
			sz[c] += sz[i];
			h[c] = min(h[c], h[i]);
			g[c].push_back(i);
			amt++;
		}else{
			h[c] = min(h[c], l[i]);
		}
	}
}

void dfs1(int c){
	s--;
	ans[c] = r;
	for(int i : g[c]) if(s) dfs1(i);
}

void dfs2(int c){
	s--;
	ans[c] = r;
	for(int i : graph[c]) if(s && ans[i] == a[2].s) dfs2(i);
}

vi find_split(int N, int A, int B, int C, vi P, vi Q){
	n = N, m = P.size();
	a[0] = {A, 1}, a[1] = {B, 2}, a[2] = {C, 3};
	sort(a, a + 3);
	
	for(int i = 0; i < m; i++){
		graph[P[i]].push_back(Q[i]);
		graph[Q[i]].push_back(P[i]);
	}
	
	p[0] = -1;
	dfs(0);
	
	int x = 0;
	for(bool f = 1; f;){
		f = 0;
		for(int i : g[x]){
			if(sz[i] >= a[0].f){
				f = 1;
				x = i;
				break;
			}
		}
	}
	
	ans = vector<int>(n, a[2].s);
	if(sz[x] + a[1].f <= n){
		s = a[0].f, r = a[0].s;
		dfs1(x);
		s = a[1].f, r = a[1].s;
		dfs2(p[x]);
	}else{
		s = a[1].f - 1, r = a[1].s;
		ans[x] = r;
		for(int i : g[x]){
			if(!s || h[i] < l[x]) continue;
			dfs1(i);
		}
		for(int i : g[x]){
			if(!s || h[i] >= l[x]) continue;
			dfs1(i);
		}
		s = a[0].f, r = a[0].s;
		if(p[x] != -1) dfs2(p[x]);
		if(s) ans = vector<int>(n, 0);
	}
	
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, a, b, c;
	cin >> n >> m >> a >> b >> c;
	vi p(m), q(m);
	for(int i = 0; i < m; i++) cin >> p[i] >> q[i];
	
	vi ans = find_split(n, a, b, c, p, q);
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}