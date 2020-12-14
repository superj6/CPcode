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

const int mxn = 200002;
int n, m;
pi a[mxn];
ll dp[mxn];
int dp2[mxn], lb[mxn], rb[mxn];
map<int, int, greater<int>> mp;
vector<int> v;
vector<int> vv[mxn];
stack<pi> stk;

auto cmpx = [](int x, int y){ return a[x].f < a[y].f;};
auto cmpy = [](int x, int y){ return a[x].s > a[y].s;};

ll cst(int x, int y){
	return dp[x] + (ll)(a[y].f - a[x].f) * (a[y].s - a[x].s);
}

int sol(int i, int x, int y){
	int l = -1, r = vv[i].size();
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(cst(x, vv[i][mid]) < cst(y, vv[i][mid])) r = mid;
		else l = mid;
	}
	return r;
}

int main(){
	freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	a[0] = {0, 0};
	for(int i = 1; i <= n; i++) cin >> a[i].f >> a[i].s;
	a[n + 1] = {m, m};
	n += 2;
	
	sort(a, a + n);
	
	mp[-1] = -1;
	for(int i = 0; i < n; i++){
		dp[i] = 0x3f3f3f3f3f3f3f3f;
		auto it = mp.upper_bound(a[i].s);
		dp2[i] = 1 + it->s;
		vv[dp2[i]].push_back(i);
		if(it == mp.begin() || dp2[i] >= (--it)->s){
			it = mp.insert({a[i].s, dp2[i]}).f;
			while(it != mp.begin() && (--it)->s <= dp2[i]) it = mp.erase(it);
		}
	}
	
	dp[0] = 0;
	for(int l = 0; l < dp2[n - 1]; l++){
		v.clear();
		for(int i : vv[l]){
			lb[i] = upper_bound(vv[l + 1].begin(), vv[l + 1].end(), i, cmpx) - vv[l + 1].begin();
			rb[i] = upper_bound(vv[l + 1].begin(), vv[l + 1].end(), i, cmpy) - vv[l + 1].begin();
			if(lb[i] < rb[i]) v.push_back(i);
		}
		
		for(int s = 0, e = 0; s < v.size(); s = e){
			while(e < v.size() && lb[v[e]] < rb[v[s]]) e++;

			while(!stk.empty()) stk.pop();
			for(int i = lb[v[s]], j = s; i < rb[v[s]]; i++){
				for(; j < e && lb[v[j]] <= i; j++){
					while(!stk.empty() && stk.top().s <= sol(l + 1, stk.top().f, v[j])) stk.pop();	
					stk.push({v[j], stk.empty() ? mxn : sol(l + 1, stk.top().f, v[j])});
				}
				while(stk.top().s <= i) stk.pop();
				dp[vv[l + 1][i]] = min(dp[vv[l + 1][i]], cst(stk.top().f, vv[l + 1][i]));
			}
			
			while(!stk.empty()) stk.pop();
			for(int i = rb[v[e - 1]] - 1, j = e - 1; i >= rb[v[s]]; i--){
				for(; j > s && rb[v[j]] > i; j--){
					while(!stk.empty() && stk.top().s >= sol(l + 1, v[j], stk.top().f)) stk.pop();	
					stk.push({v[j], stk.empty() ? -1 : sol(l + 1, v[j], stk.top().f)});
				}
				while(stk.top().s > i) stk.pop();
				dp[vv[l + 1][i]] = min(dp[vv[l + 1][i]], cst(stk.top().f, vv[l + 1][i]));
			}
		}
	}
	
	//for(int i = 0; i < n; i++) cout << dp[i] << endl;
	
	cout << dp[n - 1] << endl;

	return 0;
}