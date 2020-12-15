/*
	Problem essentially boils to finding minimum sum of distances from set of intervals to 1 or 2 points. To
solve for k = 1, realize you can just find the median of all interval endpoints and take the sum of distances to
that point. Now to extend to k = 2, realize it is always optimal for a segment to be closer to the bridge that is
nearer to it's midpoint. This means you can sort segments by midpoints and solve for the prefix and suffix of the
segments by maintain median and points to left and right of median with point additions. Finally, you just find the
best combination of prefix and suffix.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int n, m, k;
pi a[mxn];
ll f[2][mxn];
vector<int> v;

ll sl[2], sr[2];
priority_queue<int> l, ql[2];
priority_queue<int, vector<int>, greater<int>> r, qr[2];

void add(int x, int y){
	if(l.empty() || x <= l.top()) l.push(x);
	else r.push(x);
	while(l.size() < r.size()) l.push(r.top()), r.pop();
	while(r.size() + 1 < l.size()) r.push(l.top()), l.pop();
	
	if(x <= l.top()) ql[y].push(x), sl[y] += x;
	else qr[y].push(x), sr[y] += x;
	for(int t = 0; t < 2; t++){
		while(!ql[t].empty() && ql[t].top() > l.top()){
			sl[t] -= ql[t].top();
			sr[t] += ql[t].top();
			qr[t].push(ql[t].top());
			ql[t].pop();
		}
		while(!qr[t].empty() && qr[t].top() <= l.top()){
			sr[t] -= qr[t].top();
			sl[t] += qr[t].top();
			ql[t].push(qr[t].top());
			qr[t].pop();
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k >> n;
	
	ll s = 0;
	for(int i = 0; i < n; i++){
		char c, d;
		int x, y;
		cin >> c >> x >> d >> y;
		if(x > y) swap(x, y);
		s += y - x;
		if(c != d) s++, a[m++] = {x, y};
	}
	
	sort(a, a + m, [&](pi x, pi y){
		return x.f + x.s < y.f + y.s;
	});
	
	for(int t = 0; t < 2; t++){
		while(!l.empty()) l.pop();
		while(!r.empty()) r.pop();
		for(int i = 0; i < 2; i++){
			sl[i] = sr[i] = 0;
			while(!ql[i].empty()) ql[i].pop();
			while(!qr[i].empty()) qr[i].pop();
		}
		for(int i = 0; i < m; i++){
			add(a[i].f, 0), add(a[i].s, 1);
			f[t][i] += sr[0] - (ll)l.top() * qr[0].size();
			f[t][i] += (ll)l.top() * ql[1].size() - sl[1];
		}
		reverse(a, a + m);
	}
	reverse(f[1], f[1] + m);
	
	ll ret = !!m * 0x3f3f3f3f3f3f3f3f;
	if(k & 1) ret = f[1][0];
	else for(int i = 1; i < m; i++) ret = min(ret, f[0][i - 1] + f[1][i]);
	ret = 2 * ret + s;
	
	cout << ret << endl;

	return 0;
}
