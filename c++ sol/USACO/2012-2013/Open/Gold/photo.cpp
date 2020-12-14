#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct mxq{
	stack<pi> l, r;
	
	void add(int x){
		l.push({x, max(x, l.empty() ? -1 : l.top().s)});
	}
	
	void del(){
		if(r.empty()){
			while(!l.empty()){
				r.push({l.top().f, max(l.top().f, r.empty() ? -1 : r.top().s)});
				l.pop();
			}
		}
		r.pop();
	}
	
	int mx(){
		return max(l.empty() ? -1 : l.top().s, r.empty() ? -1 : r.top().s);
	}
	
	bool empty(){
		return l.empty() && r.empty();
	}
};

const int maxn = 200002;
int n, m;
int mn[maxn], mx[maxn], dp[maxn];
mxq q;

int main(){
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i <= n + 1; i++) mn[i] = i;
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		mn[y] = min(mn[y], x);
		mx[y] = max(mx[y], x);
	}
	
	for(int i = n; ~i; i--) mn[i] = min(mn[i], mn[i + 1]);
	for(int i = 1, l = -1, r = -1; i <= n + 1; i++){
		mx[i] = max(mx[i], mx[i - 1]);
		for(; l < mx[i - 1]; l++) if(!q.empty()) q.del();
		for(r = max(r, l); r < mn[i]; r++) q.add(dp[r]);
		dp[i] = q.empty() ? -1 : !~q.mx() ? -1 : q.mx() + 1;
	} 
	
	cout << max(-1, dp[n + 1] - 1) << endl;

	return 0;
}