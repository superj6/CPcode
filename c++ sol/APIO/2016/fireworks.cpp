#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 300000;
int n, m;
ll d[mxn], f[mxn], p[mxn], dp[mxn];
priority_queue<ll> pq[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i < n + m; i++){
		cin >> p[i] >> f[i];
		d[--p[i]]++;
		if(i >= n){
			dp[p[i]] -= f[i];
			for(int j = 0; j < 2; j++) pq[p[i]].push(f[i]);
		}
	}
	
	for(int i = n - 1; i; i--){
		for(int j = 0; j < d[i] - 1; j++) dp[i] += pq[i].top(), pq[i].pop();
		ll x[2];
		for(int j = 0; j < 2; j++) x[j] = pq[i].top(), pq[i].pop();
		for(int j = 0; j < 2; j++) pq[i].push(x[j] + f[i]);
		dp[i] -= f[i], dp[p[i]] += dp[i];
		if(pq[p[i]].size() < pq[i].size()) swap(pq[p[i]], pq[i]);
		while(!pq[i].empty()) pq[p[i]].push(pq[i].top()), pq[i].pop();
	}
	
	ll ret = dp[0];
	for(int i = 0; i < d[0]; i++) ret += pq[0].top(), pq[0].pop();
	
	cout << ret << endl;
	
	return 0;
}