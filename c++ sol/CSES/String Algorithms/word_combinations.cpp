#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;

struct trie{
	int cnt;
	trie *child[26];
	
	trie(){
		cnt = 0;
		memset(child, NULL, sizeof(child));
	}
	
	void add(string s, int i){
		if(i == s.size()){
			cnt++;
			return;
		}
		
		if(!child[s[i] - 'a']) child[s[i] - 'a'] = new trie();
		child[s[i] - 'a']->add(s, i + 1);
	}
} rt;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	string s;
	cin >> s >> k;
	n = s.size();
	
	for(int i = 0; i < k; i++){
		string t;
		cin >> t;
		if(t.size() <= n) rt.add(t, 0);
	}
	
	long long dp[n + 1];
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for(int i = 0; i < n; i++){
		trie *cur = &rt;
		for(int j = 0; i + j < n && cur->child[s[i + j] - 'a']; j++){
			cur = cur->child[s[i + j] - 'a'];
			dp[i + j + 1] += (dp[i] * cur->cnt) % mod;
			dp[i + j + 1] %= mod;
		}
	}
	
	cout << dp[n] << endl;

	return 0;
}