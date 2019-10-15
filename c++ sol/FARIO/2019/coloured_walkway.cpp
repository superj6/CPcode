#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000, mod = 1e9 + 7;
int n, c, p;
long long a[maxn], dp[maxn], col[maxn], deg[maxn];
vector<int> graph[maxn], graph2[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> c;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
	}
	
	cin >> p;
	
	for(int i = 0; i < p; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		graph[x].push_back(y);
		deg[x]++;
		if(x != y){
			graph[y].push_back(x);
			deg[y]++;
		}
	}
	
	for(int i = 0; i < c; i++){
		for(int j : graph[i]){
			if(deg[j] >= deg[i]){
				graph2[i].push_back(j);
			}
		}
	}
	
	dp[a[0]] = 1;
	for(int i : graph2[a[0]]){
		if(deg[i] > deg[a[0]]){
			col[i] = (col[i] + 1) % mod;
		}
	}
	
	for(int i = 1; i < n; i++){
		int cur = col[a[i]];
		
		for(int j : graph2[a[i]]){
			cur = (cur + dp[j]) % mod;
		} 
		
		dp[a[i]] = (dp[a[i]] + cur) % mod;
		
		for(int j : graph2[a[i]]){
			if(deg[j] > deg[a[i]]){
				col[j] = (col[j] + cur) % mod;
			}
		}
		
		if(i == n - 1) cout << cur << endl;
	}

	return 0;
}