/*
	The first step in this problem is to compute the number of lines possible for each rhyme class. You can do this by 
computing the number of combinations possible for each length up to k with dp[length], then for each word add to the count for
the number of lines possible for its rhyme class, f[i], dp[k - length of word]. Next, compute the frequency of each the amount
of times a line ends in the same rhyme class. Now, for every group of equivalent line endings, compute the sum of f[i] raised
to the power of the rhyme scheme ending frequency for each i in the rhyme classes. Make sure to use fast exponentiation. This
will result in a runtime of O(nk + 26 * n * logm).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int mod = 1000000007;

int modpow(int base, int expn){
	int res = 1;
	while(expn != 0){
		if(expn & 1) res = ((long long)base * res) % mod;
		base = ((long long)base * base) % mod;
		expn >>= 1;
	}
	
	return res;
}

int main(){
	freopen("poetry.in", "r", stdin);
	freopen("poetry.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	int length[n], rhyme[n], amt[n];;
	
	for(int i = 0; i < n; i++){
		cin >> length[i] >> rhyme[i];
		rhyme[i]--;
		
		amt[i] = 0;
	} 
	
	int dp[k + 1];
	dp[0] = 1;
	
	for(int i = 1; i <= k; i++){
		dp[i] = 0;
		
		for(int j = 0; j < n; j++){
			if(i < length[j]) continue;
			dp[i] += dp[i - length[j]];
			dp[i] %= mod;
		}
	}
	
	for(int i = 0; i < n; i++){
		if(k < length[i]) continue;
		amt[rhyme[i]] += dp[k - length[i]];
		amt[rhyme[i]] %= mod;
	}
	
	int freq[26];
	for(int i = 0; i < 26; i++) freq[i] = 0;
	
	for(int i = 0; i < m; i++){
		char c;
		cin >> c;
		
		freq[c - 'A']++;
	}
	
	int res = 1;
	
	for(int i = 0; i < 26; i++){
		if(freq[i] == 0) continue;
		int sum = 0;
		for(int j = 0; j < n; j++){
			sum += 	modpow(amt[j], freq[i]);
			sum %= mod;
		}
		
		res = ((long long)res * sum) % mod;
	}
	
	cout << res << endl;

	return 0;
}
