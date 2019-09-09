#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 100000, maxm = 200000;
int n, m;
int par[maxn], rnk[maxn];
pair<int, pair<int, int>> edges[maxm];

int find(int x){
	return par[x] == x ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) par[i] = i;
	
	for(int i = 0; i < m; i++){
		cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
		edges[i].second.first--, edges[i].second.second--;
	}
	
	sort(edges, edges + m);
	
	long amt = 0, ans = 0;
	
	for(int i = 0; i < m && amt < n - 1; i++){
		int a = edges[i].second.first, b = edges[i].second.second, c = edges[i].first;
		a = find(a), b = find(b);
		
		if(a != b){
			amt++;
			ans += c;
			unionf(a, b);
		}
	}
	
	if(amt < n - 1) cout << "IMPOSSIBLE" << endl;
	else cout << ans << endl;

	return 0;
}