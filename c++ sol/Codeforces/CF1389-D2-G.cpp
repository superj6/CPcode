/*
  Realize only edges that matter are bridges, all others can always be directed and not affect answer because each biconnected
component can be turned into scc. Turn into tree and solve dp dependent on whether you direct edge based on if you want to have
nodes saturated or not and if there are no or all special nodes in one branch. Lastly do basic tree rerooting to get answer for all
roots.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 300000;
int n, m, k;
int a[mxn], b[mxn], f[mxn], u[mxn], v[mxn];
int it[mxn], lt[mxn], id[mxn];
ll ff[mxn], dp[mxn], ans[mxn];
vector<int> g[mxn];
vector<pi> gr[mxn];
int s, t;

//bridge
void dfsb2(int c, int p){
	id[c] = s;
	dp[s] += a[c];
	ff[s] += f[c];
	for(int i : g[c]){
		if(i == p) continue;
		int j = u[i] ^ v[i] ^ c;
		if(!~id[j]){
			dfsb2(j, i);
		}else if(id[j] != s){
			gr[id[c]].push_back({id[j], b[i]});
			gr[id[j]].push_back({id[c], b[i]});
		}
	}
}

void dfsb(int c, int p){
	it[c] = lt[c] = t++;
	for(int i : g[c]){
		int j = u[i] ^ v[i] ^ c;
		if(!~it[j]){
			dfsb(j, i);
			lt[c] = min(lt[c], lt[j]);
			if(lt[j] > it[c]) dfsb2(j, i), s++;
		}else if(i != p){
			lt[c] = min(lt[c], it[j]);
		}
	}
	if(!~p) dfsb2(c, p), s++;
}
//end bridge

ll val(int x, int y){
	return max(0ll, dp[x] - (!!ff[x] && ff[x] != k) * y);
}

void dfs(int c, int p){
	for(pi i : gr[c]){
		if(i.f == p) continue;
		dfs(i.f, c);
		ff[c] += ff[i.f];
		dp[c] += val(i.f, i.s);
	}
}

void dfs2(int c, int p){
	ans[c] = dp[c];
	for(pi i : gr[c]){
		if(i.f == p) continue;
		dp[c] -= val(i.f, i.s);
		ff[c] -= ff[i.f];
		ff[i.f] += ff[c];
		dp[i.f] += val(c, i.s);
		
		dfs2(i.f, c);
		
		dp[i.f] -= val(c, i.s);
		ff[i.f] -= ff[c];
		ff[c] += ff[i.f];
		dp[c] += val(i.f, i.s);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < k; i++){
		int x;
		cin >> x;
		f[--x]++;
	}
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> b[i];
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		g[--u[i]].push_back(i);
		g[--v[i]].push_back(i);
	}
	
	memset(it, -1, sizeof(it));
	memset(id, -1, sizeof(id));
	dfsb(0, -1);
	
	dfs(0, -1);
	dfs2(0, -1);
	
	cout << ans[id[0]];
	for(int i = 1; i < n; i++) cout << " " << ans[id[i]];
	cout << endl;

	return 0;
}
