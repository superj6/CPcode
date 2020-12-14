#include "paint.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

struct mque{
	stack<pi> s1, s2;
	
	int mn(stack<pi> &s){
		return s.empty() ? 0x3f3f3f3f : s.top().s;
	}
	
	void add(int x){
		s1.push({x, min(x, mn(s1))});
	}
	
	void del(){
		if(s2.empty()) for(; !s1.empty(); s1.pop()) s2.push({s1.top().f, min(s1.top().f, mn(s2))});
		s2.pop();
	}
	
	int qry(){
		return min(mn(s1), mn(s2));
	}
};

const int mxn = 100001;
int n;
int f1[mxn], f2[mxn], f3[mxn];
mque q;
vi v[mxn];

int minimumInstructions(int n, int m, int k, vi a, vi w, vector<vi> b){
	for(int i = 0; i < m; i++)
	for(int j : b[i]){
		v[j].push_back(i);
	}
	
	int dp;
	q.add(0);
	for(int i = 1; i <= n; i++){
		for(int j : v[a[i - 1]]){
			int x = (m + j - 1) % m;
			f3[j] = 1 + (f2[x] == i - 1) * f1[x];
		}
		bool t = 0;
		for(int j : v[a[i - 1]]){
			f2[j] = i;
			t |= (f1[j] = f3[j]) >= m;
		}
		q.add(dp = t ? q.qry() + 1 : 0x3f3f3f3f);
		if(i >= m) q.del();
	}
	
	return dp <= n ? dp : -1;
}

/*
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vi a(n), w(m);
	vector<vi> b(m);
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> w[i];
	for(int i = 0; i < m; i++){
		b[i].resize(w[i]);
		for(int &j : b[i]) cin >> j;
	}
	
	cout << minimumInstructions(n, m, k, a, w, b) << endl;

	return 0;
}
*/