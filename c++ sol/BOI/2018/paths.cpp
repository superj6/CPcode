#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 300000, maxk = 5;
int n, m, k;
int col[maxn];
long long dp[1 << maxk][maxn];
vector<int> graph[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++){
		cin >> col[i];
		col[i]--;
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	long long ret = 0;
	for(int i = 1; i < (1 << k); i++){
		for(int j = 0; j < n; j++){
			if((i ^ (1 << col[j])) == 0) dp[i][j] = 1;
			else ret += dp[i][j];
			for(int l : graph[j]){
				if(~i & (1 << col[l])) dp[i | (1 << col[l])][l] += dp[i][j];
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}