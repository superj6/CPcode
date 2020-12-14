#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <chrono>
#include <string.h>
#include <queue>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define sq(x) ((x) * (x))

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 1000, w = 4;
const pi g[w] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, k;
pi s, f;
pi p[mxn * mxn];
int a[mxn][mxn], dp[mxn][mxn], vis[mxn][mxn];
auto cmp = [](pi x, pi y){ return dp[x.f][x.s] < dp[y.f][y.s];};
priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);

struct vpTree{
	vpTree *tl = 0, *tr = 0;
	int d;
	pi v;
	
	int dst(pi x, pi y){
		return sq(x.f - y.f) + sq(x.s - y.s);
	}
	
	vpTree(int l, int r){
		v = p[uniform_int_distribution<int>(l, r)(rng)];
		if(l != r){
			int mid = (l + r + 1) / 2;
			sort(p + l, p + r + 1, [&](pi x, pi y){
				return dst(v, x) < dst(v, y);
			});
			d = dst(v, p[mid]);
			tl = new vpTree(l + 1, mid);
			if(mid < r) tr = new vpTree(mid + 1, r);
		}
	}
	
	void qry(pi x, int &ret){
		int dd = dst(x, v);
		ret = min(ret, dd);
		vpTree *a = tl, *b = tr;
		if(b && dd > d) swap(a, b);
		if(a) a->qry(x, ret);
		if(b && sq((int)(sqrt(d) - sqrt(dd))) < ret) b->qry(x, ret);
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> s.f >> s.s >> f.f >> f.s >> k;
	s.f--, s.s--, f.f--, f.s--;
	
	for(int i = 0; i < k; i++){
		cin >> p[i].f >> p[i].s;
		p[i].f--, p[i].s--;
	} 
	
	vpTree tre(0, k - 1);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		tre.qry({i, j}, a[i][j] = 0x3f3f3f3f);
	}
	
	dp[s.f][s.s] = a[s.f][s.s];
	pq.push(s);
	while(!pq.empty()){
		pi c = pq.top();
		pq.pop();
		if(vis[c.f][c.s]) continue;
		vis[c.f][c.s] = 1;
		for(int i = 0; i < w; i++){
			pi v = c + g[i];
			if(v.f < 0 || v.s < 0 || v.f >= n || v.s >= m) continue;
			int dd = min(a[v.f][v.s], dp[c.f][c.s]);
			if(dp[v.f][v.s] < dd){
				dp[v.f][v.s] = dd;
				pq.push(v);
			}
		}
	}
	
	cout << dp[f.f][f.s] << endl;	

	return 0;
}