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