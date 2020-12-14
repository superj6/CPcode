#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 10001;
int n, m;
ll dp[maxn], lcp[maxn];
vector<int> p;

void init(){
	for(int i = 2; i <= n; i++){
		if(!lcp[i]){
			lcp[i] = i;
			p.push_back(i);
		}
		for(int j = 0; j < p.size() && p[j] <= lcp[i] && i * p[j] <= n; j++){
			lcp[i * p[j]] = p[j];
		}
	}
}

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	init();
	
	dp[0] = 1;
	for(int i : p)
	for(int j = n; j; j--)
	for(int k = i; k <= j; k *= i){
		(dp[j] += dp[j - k] * k) %= m;
	}
	
	ll ret = 0;
	for(int i = 0; i <= n; i++) (ret += dp[i]) %= m;
	
	cout << ret << endl;

	return 0;
}