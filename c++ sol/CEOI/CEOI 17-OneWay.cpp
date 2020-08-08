/*

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100000;
int n, m, k;
pi e[maxn];
int t[maxn], l[maxn], p[maxn], dp[maxn];
bool used[maxn], used2[maxn];
vector<pi> graph[maxn], graph2[maxn];
vector<int> b[maxn];
int s;
string ret;
 
void dfs2(int c){
	p[c] = s;
	b[s].push_back(c);
	for(pi i : graph[c]){
		if(p[i.f] != -1){
			if(p[i.f] != -2 && p[i.f] != s){
				graph2[s].push_back({p[i.f], i.s});
				graph2[p[i.f]].push_back({s, i.s});
			}
			continue;
		} 
		dfs2(i.f);
	}
}
 
int x;
void dfs(int c){
	used[c] = 1;
	t[c] = l[c] = x++;
	for(pi i : graph[c]){
		if(used2[i.s]) continue;
		used2[i.s] = 1;
		if(used[i.f]){
			l[c] = min(l[c], t[i.f]);
		}else{
			dfs(i.f);
			l[c] = min(l[c], l[i.f]);
			if(l[i.f] > t[c]){
				p[c] = -2;
				dfs2(i.f);
				s++;
				p[c] = -1;
			}
		}
	}
	if(!t[c]){
		dfs2(c);
		s++;
	}
}
 
int dfs3(int c){
	used[c] = 1;
	for(pi i : graph2[c]){
		if(used[i.f]) continue;
		dp[c] += dfs3(i.f);
		if(dp[i.f] < 0){
			ret[i.s] = p[e[i.s].f] == c ? 'L' : 'R';
		}
		if(dp[i.f] > 0){
			ret[i.s] = p[e[i.s].f] == c ? 'R' : 'L';
		}
	}
	return dp[c];
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> e[i].f >> e[i].s;
		e[i].f--, e[i].s--;
		graph[e[i].f].push_back({e[i].s, i});
		graph[e[i].s].push_back({e[i].f, i});
	}
	
	memset(p, -1, sizeof(p));
	for(int i = 0; i < n; i++){
		if(!used[i]){
			x = 0;
			dfs(i);
		}
	}
	
	cin >> k;
	
	for(int i = 0; i < k; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		dp[p[a]]--;
		dp[p[b]]++;
	}
	
	ret = string(m, 'B');
	memset(used, 0, sizeof(used));
	for(int i = 0; i < s; i++) if(!used[i]) dfs3(i);
	
	cout << ret << endl;
 
	return 0;
}
