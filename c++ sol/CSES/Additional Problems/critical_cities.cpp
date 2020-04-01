#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000, k = 17;
int n, m;
int a[maxn], b[maxn], d[maxn];
int p[k][maxn];
bool h[maxn], w[maxn], used[maxn];
vector<int> graph[maxn], graph2[maxn];

void dfs(int c){
	used[c] = 1;
	for(int i = 1; i < k; i++) p[i][c] = p[i - 1][c] == -1 ? -1 : p[i - 1][p[i - 1][c]];
	if(c != n - 1) for(int i : graph[c]){
		if(!used[i]){
			d[i] = d[c] + 1;
			p[0][i] = c;
			dfs(i);
		}else{
			int t = c;
			for(int j = k - 1; j >= 0; j--) if(p[j][t] != -1 && d[p[j][t]] >= d[i]) t = p[j][t];
			if(t == i) continue;
		}
		if(h[i]){
			h[c] = 1;
			graph2[c].push_back(i);
			graph2[i].push_back(c);
		}
	}
}

int t;
void dfs2(int c, int p){
	used[c] = 0;
	a[c] = b[c] = t++;
	for(int i : graph2[c]){
		if(i == p) continue;
		if(!used[i]) b[c] = min(b[c], a[i]);
		else{
			dfs2(i, c);
			b[c] = min(b[c], b[i]);
			if(b[i] >= a[c]) w[c] = 1;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
	}
	
	p[0][0] = -1;
	h[n - 1] = 1;
	dfs(0);
	w[0] = w[n - 1] = 1;
	dfs2(0, -1);
	
	vector<int> ans;
	for(int i = 0; i < n; i++) if(w[i]) ans.push_back(i + 1);
	
	cout << ans.size() << endl;
	cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;
	
	return 0;
}