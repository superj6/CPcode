#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100000;
int n, m, k;
int dp[maxn], cnt[maxn];
vector<pi> graph[maxn];

int main(){
	freopen("timeline.in", "r", stdin);
	freopen("timeline.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> dp[i];
	
	for(int i = 0; i < k; i++){
		int x, y, z;
		cin >> x >> y >> z;
		x--, y--;
		graph[x].push_back({y, z});
		cnt[y]++;
	}
	
	queue<int> q;
	for(int i = 0; i < n; i++){
		if(!cnt[i]) q.push(i);
	}
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		
		for(pi i : graph[c]){
			dp[i.f] = max(dp[i.f], dp[c] + i.s);
			if(!--cnt[i.f]) q.push(i.f);
		}
	}
	
	for(int i = 0; i < n; i++) cout << dp[i] << endl;

	return 0;
}