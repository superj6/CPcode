#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200000;
int n, m, k;
int a[maxn];
int par[maxn], rnk[maxn];
bool used[maxn];
pi e[maxn];
int ans[maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

int unionf(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return 0;
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++){
		cin >> e[i].f >> e[i].s;
		e[i].f--, e[i].s--;
		if(e[i].f > e[i].s) swap(e[i].f, e[i].s);
	}
	
	sort(e, e + m);
	
	for(int i = 0; i < k; i++){
		pi p;
		cin >> p.f >> p.s;
		if(p.f > p.s) swap(p.f, p.s);
		p.f--, p.s--;
		int it = lower_bound(e, e + m, p) - e;
		a[i] = it;
		used[it] = 1;
	}
	
	for(int i = 0; i < n; i++) par[i] = i;
	
	ans[k - 1] = n;
	for(int i = 0; i < m; i++){
		if(!used[i]) ans[k - 1] -= unionf(e[i].f, e[i].s);
	}
	for(int i = k - 1; i > 0; i--){
		ans[i - 1] = ans[i] - unionf(e[a[i]].f, e[a[i]].s);
	}
	
	cout << ans[0];
	for(int i = 1; i < k; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}