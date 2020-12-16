/*
	Realize the problem can be converted to you are given a set of ranges that have a value, and you want find
the max value you can get for placing i points where i ranges from 1 to m, and the value is equal to the sum of the
ranges values such that at least 1 point is held within the interval.
	I start out by converting the grid into ranges by grouping adjacent squares with union find and holding their
min and max position the group covers. I then compute f[i][j] which is the number of intervals that completely contain
the range f[i][j]. Now letting dp[i][j] be the max value when placing i points and the ith point is at j, you can
transition by having dp[i][j] = max(dp[i - 1][l] + f[j][j] - f[l][j]) for all l < j, since f[j][j] is the number of
intervals containing point j but you subtract f[l][j] to not overcount the ranges that cover both points. Doint this
naively is O(m^3).
	To further optimize this, realize for points l1 and l2 where l1 < l2, as j increases, f[l2][j] decreases by
at least as much as f[l1][j]. This is because there will be more intervals covering l2 and j then l1 and j since l2
is closer to j, so as j increases there will be more intervals in which an interval will no longer cover l2 and j than
l1 and j, but every time an interval no longer covers both l1 and j it will also no longer cover l2 and j since l1 and
l2 will be in the same position but j went out of the bounds. This means the optimial transition point l increases as
j increases, and we can do d&q dp opt, where we hold a range of values we need to compute the dp for still and find the
best transition point for the middle one, then recurse on the left and right half on the range while realizing the best
transition points for both the left and right half will be to the left and right respectively of the middle point's
transition spot. This makes the time go to O(m^2lgm), as for each level of recursion of a range of points you only try
transition values in distinct ranges that sum to m, and there are lgm levels
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 2002, mxk = mxn * mxn, w = 2;
const int dx[w] = {1, 0};
const int dy[w] = {0, 1};
int n, m, k;
int s[mxk], l[mxk], r[mxk], par[mxk], rnk[mxk];
int a[mxn][mxn], f[mxn][mxn], dp[mxn], p[mxn];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int sol(int x, int y, int l, int r){
	if(l > r) return 0;
	int mid = (l + r) / 2, z = x;
	for(int i = x; i <= min(y, mid - 1); i++){
		int dd = p[i] + f[mid][mid] - f[i][mid];
		if(dd > dp[mid]) dp[mid] = dd, z = i;
	}
	return max({dp[mid], sol(x, z, l, mid - 1), sol(z, y, mid + 1, r)});
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	memset(a, -1, sizeof(a));
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		char c;
		cin >> c;
		if(isdigit(c)){
			s[k] = c - '0', l[k] = r[k] = j, par[a[i][j] = k] = k;
			for(int p = 0; p < 2; p++){
				int x = i - dx[p], y = j - dy[p];
				if(~a[x][y]){
					int u = fnd(k), v = fnd(a[x][y]);
					if(u == v) continue;
					if(rnk[u] < rnk[v]) swap(u, v);
					rnk[u] += rnk[u] == rnk[v];
					par[v] = u, s[u] += s[v];
					l[u] = min(l[u], l[v]), r[u] = max(r[u], r[v]);
				}
			}
			k++;
		}
	}
	
	for(int i = 0; i < k; i++) if(fnd(i) == i) f[l[i]][r[i]] += s[i];
	
	for(int i = 1; i <= m; i++)
	for(int j = m; j; j--){
		f[i][j] += f[i - 1][j] + f[i][j + 1] - f[i - 1][j + 1];
	}
	
	for(int i = 1; i <= m; i++){
		cout << sol(0, m, 1, m) << endl;
		swap(dp, p);
	} 

	return 0;
}