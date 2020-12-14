#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second
 
const ll inf = 0x3f3f3f3f;
const int mxn = 100, mxk = 1000;
int n, m, k;
ll a[mxn][mxk][2];
pi g[mxn][mxn];
ll g2[mxn][mxn];
 
bool sol(ll x){
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		g2[i][j] = g[i][j].f - x * g[i][j].s;
	}
	for(int l = 0; l < n; l++)
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		g2[i][j] = max(g2[i][j], g2[i][l] + g2[l][j]);
	}
	for(int i = 0; i < n; i++) if(g2[i][i] >= 0) return 1;
	return 0;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < k; j++)
	for(int l = 0; l < 2; l++){
		cin >> a[i][j][l];
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		g[i][j] = {0, inf};
		for(int l = 0; l < k; l++){
			if(~a[i][l][0] && ~a[j][l][1]) g[i][j].f = max(g[i][j].f, a[j][l][1] - a[i][l][0]);
		}
	}
	
	for(int i = 0; i < m; i++){
		ll u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u][v].s = min(g[u][v].s, w);
	}
	
	for(int l = 0; l < n; l++)
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		g[i][j].s = min(g[i][j].s, g[i][l].s + g[l][j].s);
	}
	
	int l = 0, r = inf;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(sol(mid)) l = mid;
		else r = mid;
	}
	
	cout << l << endl;
 
	return 0;
}