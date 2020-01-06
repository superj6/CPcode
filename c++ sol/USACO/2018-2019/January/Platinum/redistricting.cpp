/*
	For this problem, first compute prefix sums such that h is 1 and g is -1. Now you do dp with dp[i] being the value of
minimum districts guernsey majority or tied up to index i. If you were to iterate to the previous k states, the runtime would
be O(n * k) which is too large, so you have to instead do something slightly more clever. Hold a multiset of the kth most
recent dp values, and an array of multisets holding the prefix sums with the dp value as an index (I think you could just hold
a multiset of pairs with these values actually but whatever). As you iterate through, it is always optimal to use the smallest
dp value in the active dp multiset, and then use the smallest prefix sum in the active set with that dp value. If the prefix
sum is less that the current prefix sum u add 0, otherwise u add 1. This gives a time complexity of O(nlogn).
*/

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
