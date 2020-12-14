#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
#include <stack>
using namespace std;
#define endl '\n'
 
const int maxn = 60000, m = maxn * 21;
int n, k;
int a[maxn];
int g[maxn][2];
int v[m], dp[m << 1], dp2[m << 1];
int st = m;
 
// bimatch
int tt[maxn], pa[maxn], pb[maxn];
int it;

bool dfs(int c){
	tt[c] = it;
	
	for(int i = 0; i < 2; i++){
		if(pb[g[c][i]] == -1){
			pa[c] = g[c][i];
			pb[g[c][i]] = c;
			return 1;
		}
	}
	
	for(int i = 0; i < 2; i++){
		if(tt[pb[g[c][i]]] != it && dfs(pb[g[c][i]])){
			pa[c] = g[c][i];
			pb[g[c][i]] = c;
			return 1;
		}
	}
	
	return 0;
}
 
int match(){
	int ret = 0, cur;
	memset(pa, -1, sizeof(pa));
	memset(pb, -1, sizeof(pb));
	
	do{
		cur = 0;
		it++;
		
		for(int i = 0; i < 2 * n; i++){
			if(pa[i] == -1) cur += dfs(i);
		}
		
		ret += cur;
	} while(cur);
	
	return ret;
}
//end bimatch

//scc
bool used[maxn << 1];
vector<int> graph[2][maxn << 1];
stack<int> stk;
int w, z;

void scc(int t, int c){
	used[c] = !t;
	for(int i : graph[t][c]){
		if(used[i] == t) scc(t, i);
	}
	if(!t){
		stk.push(c);
	}else if(c < 2 * n){
		w += (2 * (g[c][0] == pa[c]) - 1) * a[c];
		z ^= 1;	
	} 
}
//end scc
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < 2 * n; i++){
		for(int j = 0; j < 2; j++){
			cin >> g[i][j];
			g[i][j] += j * n - 1;
			graph[0][2 * n + g[i][j]].push_back(i);
			graph[1][i].push_back(2 * n + g[i][j]);
		}
		cin >> a[i];
	}
	
	if(match() != 2 * n) goto die;
	
	for(int i = 0; i < 2 * n; i++){
		graph[0][i].push_back(2 * n + pa[i]);
		graph[1][2 * n + pa[i]].push_back(i);
	} 
	for(int i = 0; i < 2 * n; i++) if(!used[i]) scc(0, i);
	for(int i = 0; i < 4 * n; i++){
		int c = stk.top();
		stk.pop();
		if(used[c]){
			w = z = 0;
			scc(1, c);
			if(z) st += w;
			else v[abs(w)]++;
		}
	}
	
	dp[st] = 1;
	for(int c = 1, mx = st, mn = st; c < m; c++) if(v[c]){
		memcpy(dp2, dp, sizeof(dp));
		memset(dp, 0, sizeof(dp));
		for(int i = mx; i >= mn; i--) if(dp2[i]){
			for(int j = max((c * v[c] - i) / (2 * c), 0); 
				j <= min((2 * m - 1 - i - c * v[c]) / (2 * c), v[c]) && 
				!dp[i - c * v[c] + 2 * c * j]; j++){
					dp[i - c * v[c] + 2 * c * j] = 1;
					mx = max(mx, i - c * v[c] + 2 * c * j);
					mn = min(mn, i - c * v[c] + 2 * c * j);
				}
		}
	}
	
	for(int i = m - k; i <= m + k; i++){
		if(dp[i]){
			cout << "YES" << endl;
			return 0;
		}
	}
	
	die:
	cout << "NO" << endl;
	
	return 0;
}