/*
  Sort positions in non-increasing order based on their value, then use union find to combine them while keeping track of the largest
value, which is the only peak not connected to a higher one in the region. Also keep a count of how many peaks there are of the highest
peak, if you are combining to regions such that the highest peak equals current value that means it is flat region so count stays one,
otherwise you combine counts, and when you merge smaller peak with larger you add it to the answer the number of times stored in the
count with the least value along the path being the current one.
*/

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

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 2000, mxk = 100000, w = 8;
const pi d[w] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
int n, m, k;
pi a[mxk];
int b[mxn][mxn];
int par[mxk], rnk[mxk], mx[mxk], cn[mxk];
vector<pi> ans;

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int f(int x, int y){
	return x * m + y;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	k = n * m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		cin >> b[i][j];
		int x = f(i, j);
		a[x] = {i, j};
		mx[x] = b[i][j];
		cn[x] = 1;
		par[x] = x;
	}
	
	sort(a, a + k, [&](pi x, pi y){
		return b[x.f][x.s] > b[y.f][y.s];
	});
	
	for(int i = 0; i < k; i++)
	for(int j = 0; j < w; j++){
		pi p = a[i] + d[j];
		int c = b[a[i].f][a[i].s];
		if(p.f < 0 || p.s < 0 || p.f >= n || p.s >= m || b[p.f][p.s] < c) continue;

		int x = fnd(f(a[i].f, a[i].s)), y = fnd(f(p.f, p.s));
		if(x == y) continue;
		
		if(rnk[x] < rnk[y]) swap(rnk[x], rnk[y]);
		rnk[x] += rnk[x] == rnk[y];
		par[y] = x;
		
		if(mx[x] == mx[y]){
			cn[x] += (mx[x] != c) * cn[y];
		}else{
			if(mx[x] < mx[y]) swap(mx[x], mx[y]), swap(cn[x], cn[y]);
			if(mx[y] != c){
				for(int l = 0; l < cn[y]; l++) ans.push_back({mx[y], c});
			}
		}
	}
	
	int x = fnd(0);
	for(int i = 0; i < cn[x]; i++) ans.push_back({mx[x], 0});
	sort(ans.begin(), ans.end(), greater<pi>());
	
	cout << ans.size() << endl;
	for(pi i : ans) cout << i.f << " " << i.s << endl;

	return 0;
}
