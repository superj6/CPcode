#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100001;
int n, m, k;
int p[maxn], d[maxn], w[maxn];
map<int, ll> dp[maxn];
int x;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 2; i <= n; i++) cin >> p[i];
	
	for(int i = 0; i < m; i++) cin >> x, cin >> d[x] >> w[x];
	
	for(int i = n; i; i--){
		if(d[i]){
			auto it = dp[i].insert({d[i], 0}).f;
			it->s += x = w[i];
			for(++it; it != dp[i].end() && x >= it->s; x -= it->s, it = dp[i].erase(it));
			if(it != dp[i].end()) it->s -= x;
		}
		if(dp[p[i]].size() < dp[i].size()) swap(dp[p[i]], dp[i]);
		for(auto j : dp[i]) dp[p[i]][j.f] += j.s;
	}
	
	ll ret = 0;
	for(auto i : dp[0]) ret += i.s;
	
	cout << ret << endl;

	return 0;
}