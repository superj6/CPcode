#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
ll n, m, k;
vector<ll> v, dp;
unordered_map<ll, int> mp;
 
int main(){
	freopen("desc.in", "r", stdin);
	freopen("desc.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(ll i = 1; i * i <= n; i++){
		if(n % i == 0){
			v.push_back(i);
			if(i * i != n) v.push_back(n / i);
		}
	}
	
	m = v.size();
	dp.resize(m);
	sort(v.begin(), v.end());
	for(int i = 0; i < m; i++) mp[v[i]] = i;
	
	dp[0] = 1;
	for(int i = 1; i < m; i++)
	for(int j = m - 1; ~j; j--)
	for(ll l = v[i]; mp.count(v[j] * l); l *= v[i]){
		dp[mp[v[j] * l]] += dp[j];
	}
	
	cout << dp[m - 1] << endl;
	
	k = dp[m - 1] - k + 1;
	for(int i = 1, c = m - 1; i < m && c; i++){
		for(int j = 0; j < m; j++)
		for(ll l = v[i]; mp.count(v[j] * l); l *= v[i]){
			dp[mp[v[j] * l]] -= dp[j];
		}
		for(; dp[c] < k; c = mp[v[c] / v[i]]){
			k -= dp[c];
			cout << v[i];
			if(k) cout << " ";
		}
	}
	cout << endl;
 
	return 0;
}