#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const long long mod = 1000000007;
int n, k;
vector<pair<int, int>> a;

long long solve(int x, int l){
	x = mod - x - 7;
	long long p = 1;
	long long dp[l + 2];
	dp[0] = dp[1] = 1;
	for(int i = 1; i <= k; i++){
		p = (p * x) % mod;
	}
	for(int i = 1; i <= l; i++){
		dp[i + 1] = (dp[i] * (x + 1)) % mod;
		if(i >= k) dp[i + 1] = (dp[i + 1] - (dp[i - k] * p) % mod + mod) % mod;
	}
	return dp[l + 1];
}

int main(){
	freopen("tracking2.in", "r", stdin);
	freopen("tracking2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i <= n - k; i++){
		int x;
		cin >> x;
		if(a.size() > 0 && x == a.back().first) a.back().second++;
		else a.push_back({x, 1});
	}
	
	if(a.size() == 1){
		cout << solve(a[0].first, n) << endl;
		return 0;
	}
	
	long long ret = 1;
	for(int i = 0; i < a.size(); i++){
		int l;
		if(i == 0){
			if(a[i].first < a[i + 1].first){
				l = a[i].second - 1;
			}else{
				l = a[i].second + k - 1;
			}
		}else if(i == a.size() - 1){
			if(a[i].first < a[i - 1].first){
				l = a[i].second - 1;
			}else{
				l = a[i].second + k - 1;
			}
		}else{
			if(a[i].first < a[i - 1].first){
				if(a[i].first < a[i + 1].first){
					l = max(0, a[i].second - k - 1);
				}else{
					l = a[i].second - 1;
				}
			}else{
				if(a[i].first < a[i + 1].first){
					l = a[i].second - 1;
				}else{
					l = a[i].second + k - 1;
				}
			}
		}
		ret = (ret * solve(a[i].first, l)) % mod;
	}
	
	cout << ret << endl;

	return 0;
}