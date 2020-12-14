#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 40000;
int n, m, k;
ll a1[maxn], a2[maxn], dp1[maxn], dp2[maxn];
vector<int> graph[maxn];

int main(){
	freopen("route.in", "r", stdin);
	freopen("route.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++){
		 cin >> a1[i];
		 dp1[i] = a1[i];
	}
	for(int i = 0; i < m; i++){
		cin >> a2[i];
		dp2[i] = a2[i];
	} 
	for(int i = 0; i < k; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
	}
	
	for(int i = 0; i < n; i++){
		sort(graph[i].begin(), graph[i].end());
		for(int j : graph[i]){
			ll f1 = max(dp1[i], dp2[j] + a1[i]);
			ll f2 = max(dp2[j], dp1[i] + a2[j]);
			dp1[i] = f1, dp2[j] = f2;
		}
	}
	
	ll ret = 0;
	for(int i = 0; i < n; i++) ret = max(ret, dp1[i]);
	for(int i = 0; i < m; i++) ret = max(ret, dp2[i]);
	
	cout << ret << endl;

	return 0;
}