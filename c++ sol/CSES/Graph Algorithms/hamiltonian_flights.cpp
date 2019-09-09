#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int mod = 1000000007;
queue<pair<int, int>> q;
int dp[20][1 << 20];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<int> graph[n];
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
	}
	
	dp[0][1] = 1;
	q.push({0, 1});
	
	while(!q.empty()){
		int c = q.front().first, d = q.front().second;
		q.pop();
		
		for(int i : graph[c]){
			if(d & (1 << i)) continue;
			int nd = d | (1 << i);
			
			if(!dp[i][nd]) q.push({i, nd});
			dp[i][nd] += dp[c][d];
			dp[i][nd] %= mod;
		}
	}
	
	cout << dp[n - 1][(1 << n) - 1] << endl;;

	return 0;
} 