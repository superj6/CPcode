#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200001;
int n, m;
int a[maxn], l[maxn], r[maxn];
ll dp[maxn];
map<int, ll> ans[maxn];
vector<pi> p[maxn];
vector<int> stk;

void add(int x, int y, ll z){
	if((--ans[x].upper_bound(y))->s >= z) return;
	ans[x][y] = z;
	auto it = ans[x].upper_bound(y);
	while(it != ans[x].end() && it->s <= z) it = ans[x].erase(it);
}

void dfs(int c){
	if(!c) return;
	int l = ::l[c], r = ::r[c];
	dfs(l), dfs(r);
	
	ll x = dp[l] + (--ans[l].upper_bound(a[c]))->s;
	ll y = dp[r] + (--ans[r].upper_bound(a[c]))->s;
	dp[l] += y, dp[r] += x;
	
	if(ans[l].size() > ans[r].size()) swap(l, r);
	if(r) swap(ans[c], ans[r]), swap(dp[c], dp[r]);
	dp[0] = 0;
	
	for(auto i : ans[l]) add(c, i.f, i.s + dp[l] - dp[c]);
	for(auto i : p[c]) add(c, i.f, i.s + x + y - dp[c]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	ans[0][1] = 0;
	for(int i = 1; i <= n; i++){
		ans[i][1] = 0;
		cin >> a[i];
		while(!stk.empty() && a[stk.back()] < a[i]){
			l[i] = stk.back();
			stk.pop_back();
		}
		if(!stk.empty()) r[stk.back()] = i;
		stk.push_back(i);
	}
	
	cin >> m;
	
	ll ret = 0;
	for(int i = 0; i < m; i++){
		int x, y, z;
		cin >> x >> y >> z;
		ret += z;
		p[x].push_back({y, z});
	}
	
	dfs(stk[0]);
	ret -= dp[stk[0]] + (--ans[stk[0]].end())->s;
	
	cout << ret << endl;

	return 0;
}