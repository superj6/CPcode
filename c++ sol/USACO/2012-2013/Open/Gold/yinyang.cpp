#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<int, 2> A;

A operator+(A a, A b){
	return {a[0] + b[0], a[1] + b[1]};
}

struct T{
	int st, ed;
	deque<A> dq;	
	
	void add(int x, A v){
		if(!v[0] && !v[1]) return;
		if(dq.empty()){
			st = ed = x;
			ed++;
			dq.push_back(v);
		}else{
			while(x < st) dq.push_front({0, 0}), st--;
			while(x >= ed) dq.push_back({0, 0}), ed++;
			dq[x - st] = dq[x - st] + v;
		}
	}
	
	A qry(int x){
		if(x < st || x >= ed) return {0, 0};
		return dq[x - st];
	}
	
	int sz(){
		return ed - st;
	}
};

const int maxn = 100000;
int n;
T a[maxn];
int s[maxn];
vector<pi> graph[maxn];

ll dfs(int c, int p){
	ll ret = 0;
	int h = -1;
	for(pi i : graph[c]){
		if(i.f == p) continue;
		s[i.f] = s[c] + i.s;
		ret += dfs(i.f, c);
		if(!~h || a[i.f].sz() > a[h].sz()) h = i.f;
	}
	
	if(~h) swap(a[c], a[h]);
	A f = a[c].qry(s[c]);
	ret += f[1];
	a[c].add(s[c], {1, f[0] - f[1]});

	for(pi i : graph[c]){
		if(i.f == p || i.f == h) continue;
		for(int j = a[i.f].st; j < a[i.f].ed; j++){
			A f = a[c].qry(2 * s[c] - j), g = a[i.f].qry(j);
			ret += f[0] * g[1];
			ret += f[1] * g[0];
			ret -= f[1] * g[1];
		}
		for(int j = a[i.f].st; j < a[i.f].ed; j++){
			A f = a[i.f].qry(j);
			a[c].add(j, {f[0], f[j != s[c]]});
		}
	}
	
	return ret;
}

int main(){
	freopen("yinyang.in", "r", stdin);
	freopen("yinyang.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--, w -= !w;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}

	cout << dfs(0, -1) << endl;

	return 0;
}