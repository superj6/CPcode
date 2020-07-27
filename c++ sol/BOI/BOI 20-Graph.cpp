/*
  Do each connected component independently. First find cycles, if there is even cycle with alternating sum not equal to 0, there
is no solution, if there is odd cycle that cycle only has one solution, so use alternating sum to get solution for one vertex and
see if the value works with everything else. If there are only even cycles that work or no cycles, you can ternary search on the
answer since because a component is connected there is n variables with n - 1 equations, so realize setting one variable causes
every other vertex to have a single solution, and because absolute value is a convex function, the sum of absolute value functions
are convex with the only part of the graph having 0 slope being range of minimal answers. Not too hard idea but decent impl.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define ld long double
#define pi pair<int, int>
#define f first
#define s second

const ld ep = 1e-10;
const int mxn = 100000;
int n, m;
int vis[mxn], p[mxn], d[mxn], d2[mxn];
vector<int> v;
vector<pi> g[mxn];
ld ans[mxn];
int t;

void die(){
	cout << "NO" << endl;
	exit(0);
}

void dfs(int c){
	for(pi i : g[c]){
		if(!vis[i.f]){
			p[i.f] = c;
			d[i.f] = d[c] + i.s * d2[c], d2[i.f] = -1 * d2[c];
			vis[i.f] = vis[c] ^ 3;
			dfs(i.f);
		}else if(vis[i.f] == vis[c] && v.empty()){
			for(int j = c; j != i.f; j = p[j]) v.push_back(j);
			v.push_back(i.f);
		}else if(vis[i.f] != vis[c] && (d[c] + i.s * d2[c] - d[i.f])){
			die();
		}
	}	
}

ld dfs2(int c){
	vis[c] = t;
	ld ret = abs(ans[c]);
	for(pi i : g[c]){
		if(vis[i.f] != t){
			ans[i.f] = i.s - ans[c];
			ret += dfs2(i.f);
		}else if(ans[i.f] < i.s - ans[c] - ep || ans[i.f] > i.s - ans[c] + ep){
			die();
		}
	}
	return ret;
}

ld sol(int c, ld x){
	t++;
	ans[c] = x;
	return dfs2(c);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	for(int i = 0; i < n; i++){
		if(!vis[i]){
			vis[i] = 1, d2[i] = 1, t = 3;
			v.clear();
			dfs(i);
			if(v.empty()){
				ld l = -mxn, r = mxn;
				while(r - l > ep){
					ld mid = (l + r) / 2;
					if(sol(i, mid) < sol(i, mid + ep)) r = mid;
					else l = mid;
				}
				sol(i, r);
			}else{
				for(int i = 0; i < v.size(); i++)
				for(pi j : g[v[i]]){
					if(j.f == v[(i + 1) % v.size()]){
						ans[v[0]] += (1 - 2 * (i & 1)) * j.s / 2.0;
						break;
					}
				}
				sol(v[0], ans[v[0]]);
			}
		}
	}
	
	cout << "YES" << endl;
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}
