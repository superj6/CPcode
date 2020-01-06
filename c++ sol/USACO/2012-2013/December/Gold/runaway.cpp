#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, long long>

const int maxn = 200000, k = 18;
long long n, m;
int dp[maxn];
pi p[maxn][k];
vector<int> graph[maxn];

int dfs(int c){
	for(int i : graph[c]){
		dp[c] += dfs(i);
	}	
	return dp[c];
}

int main(){
	freopen("runaway.in", "r", stdin);
	freopen("runaway.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	p[0][0] = {-1, 0};
	for(int i = 1; i < n; i++){
		cin >> p[i][0].first >> p[i][0].second;
		p[i][0].first--;
		graph[p[i][0].first].push_back(i);
	}
	
	for(int j = 1; j < k; j++){
		for(int i = 0; i < n; i++){
			p[i][j] = p[i][j - 1].first == -1 ? (pi){-1, p[i][j - 1].second} : (pi){p[p[i][j - 1].first][j - 1].first, p[p[i][j - 1].first][j - 1].second + p[i][j - 1].second};
		}
	}
	
	for(int i = 0; i < n; i++){
		pi cur = {i, 0};
		for(int j = k - 1; j >= 0 && cur.first != -1; j--){
			if(cur.second + p[cur.first][j].second <= m) cur = {p[cur.first][j].first, cur.second + p[cur.first][j].second};
		}
		dp[i]++;
		if(cur.first != -1 && p[cur.first][0].first != -1) dp[p[cur.first][0].first]--;
	}
	
	dfs(0);
	
	for(int i = 0; i < n; i++) cout << dp[i] << endl;

	return 0;
}