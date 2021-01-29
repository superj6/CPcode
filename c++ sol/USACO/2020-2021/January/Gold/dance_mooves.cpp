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

const int mxn = 200000;
ll n, m, k, w;
int a[mxn], b[mxn], p[mxn], q[mxn], vis[mxn], ans[mxn];
vector<pi> v[mxn];

void f(int &x, int &y){
	if(y + 1 == v[x].size()) x = a[x], y = 0;
	else y++;
}

int ff(int x, int y){
	int px = x, py = y;
	f(x, y);
	return v[x][y].s - v[px][py].s + m * !y;
}

void add(int x, int y, int z){
	w += !b[v[x][y].f] && !~-z;
	b[v[x][y].f] += z;
	w -= !b[v[x][y].f] && !~z;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) a[i] = i, v[i].push_back({i, 0});
	
	for(int i = 0; i < m; i++){
		cin >> p[i] >> q[i];
		p[i]--, q[i]--;
		swap(a[p[i]], a[q[i]]);
		v[a[p[i]]].push_back({p[i], i + 1});
		v[a[q[i]]].push_back({q[i], i + 1});
	}
	
	for(int i = 0; i < n; i++) a[i] = i;
	for(int i = m - 1; ~i; i--) swap(a[p[i]], a[q[i]]);
	
	for(int i = 0; i < n; i++){
		add(i, 0, 1);
		int x = i, y = 0;
		ll z = 0;
		for(int j = i; !vis[j]; j = a[j]){
			vis[j] = 1;
			while(z + ff(x, y) <= k && (x != j || y || !z)){
 				z += ff(x, y), f(x, y), add(x, y, 1);
			}
			ans[j] = w;
			for(int l = 0; l < v[j].size(); l++) z -= ff(j, l), add(j, l, -1);
		}
		add(i, 0, -1);
		int xx = i, yy = 0;
		while(z + ff(x, y) <= 0) z += ff(x, y), f(x, y), add(x, y, 1);
		while(z - ff(xx, yy) >= 0) z -= ff(xx, yy), f(xx, yy), add(xx, yy, -1);
	}
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;
	
	return 0;
}