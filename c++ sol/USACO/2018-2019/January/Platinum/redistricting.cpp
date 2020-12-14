#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	int dif[n + 1], dp[n + 1];
	
	dif[0] = 0;
	dp[0] = 0;
	
	for(int i = 1; i <= n; i++){
		char c;
		cin >> c;
		
		dif[i] = dif[i - 1] + (c == 'H' ? 1 : -1);
	}
	
	multiset<int> bestdp;
	multiset<int> bestdif[n + 1];
	bestdp.insert(0);
	bestdif[0].insert(0);
	
	for(int i = 1; i <= n; i++){
		int minv = *bestdp.begin();
		
		dp[i] = minv + (*bestdif[minv].begin() < dif[i] ? 0 : 1);
		
		bestdp.insert(dp[i]);
		bestdif[dp[i]].insert(dif[i]);
		
		if(i >= k){
			bestdp.erase(bestdp.find(dp[i - k]));
			bestdif[dp[i - k]].erase(bestdif[dp[i - k]].find(dif[i - k]));
		}
	}
	
	cout << dp[n] << endl;

	return 0;
}