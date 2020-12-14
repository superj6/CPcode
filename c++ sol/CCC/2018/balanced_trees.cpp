#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n;
unordered_map<int, ll> dp;

ll solve(int x){
	if(dp[x]) return dp[x];
	for(int i = 1; i * i <= x; i++){
		if(~-i && x / i != i) dp[x] += solve(x / i);
		dp[x] += ((x / i) - (x / (i + 1))) * solve(i);
	}
	return dp[x];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	dp[1] = 1;
	
	cout << solve(n) << endl;

	return 0;
}