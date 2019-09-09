#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("nochange.in", "r", stdin);
	freopen("nochange.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int k, n;
	cin >> k >> n;
	
	long coin[k], cost[n];
	
	for(int i = 0; i < k; i++) cin >> coin[i];
	
	for(int i = 0; i < n; i++){
		cin >> cost[i];
		if(i > 0) cost[i] += cost[i - 1];
	}
	
	long best = -1;
	long dp[1 << k];
	memset(dp, 0, sizeof(dp));
	
	queue<pair<int, long>> q;
	q.push(make_pair(0, 0));
	
	while(!q.empty()){
		int set = q.front().first;
		long spent = q.front().second;
		q.pop();
		
		if(dp[set] != spent) continue;
		if(dp[set] == cost[n - 1]){
			long coinval = 0;
			for(int i = 0; i < k; i++) if((~set >> i) & 1) coinval += coin[i];
			
			best = max(best, coinval);
			continue;
		}
		
		for(int i = 0; i < k; i++){
			int nset = set | (1 << i);
			if(nset == set) continue;
			
			long nspent = *prev(upper_bound(cost, cost+n, spent + coin[i]));
			
			if(nspent > spent && dp[nset] < nspent){
				dp[nset] = nspent;
				q.push(make_pair(nset, nspent));
			}
		}
	}
	
	cout << best << endl;

	return 0;
}